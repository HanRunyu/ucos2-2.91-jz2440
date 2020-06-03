/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : RELOCATE.c                                              *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*	TOOLCHAIN	: arm-linux-gnueabi-gcc(Linaro 7.5.0)					  *
*                                                                         *
*   DESCRIPTION :                                                         *
*   Nand flash driver and code copy and bss segment clearing program.     *
*                                                                         *
**************************************************************************/



#include "s3c2440.h"
#include "def.h"


void nand_init(void)
{
	/* 设置时序 */
	rNFCONF = (0<<12)|(1<<8)|(0<<4);
	/* 使能NAND Flash控制器, 初始化ECC, 禁止片选 */
	rNFCONT = (1<<4)|(1<<1)|(1<<0);	
}

static void nand_select(void)
{
	rNFCONT &= ~(1<<1);	
}

static void nand_deselect(void)
{
	rNFCONT |= (1<<1);	
}

static void nand_cmd(S8 cmd)
{
	volatile U32 i;
	rNFCMD = cmd;
	for (i = 0; i < 10; i++);
}

static void nand_addr(U32 addr)
{
	U32 col  = addr % 2048;
	U32 page = addr / 2048;
	volatile U32 i;

	rNFADDR = col & 0xff;
	for (i = 0; i < 10; i++);		/* K9F2G08U0C芯片twc最小为25ns，400MHz一个时钟为2.5ns */
	rNFADDR = (col >> 8) & 0xff;
	for (i = 0; i < 10; i++);
	
	rNFADDR  = page & 0xff;
	for (i = 0; i < 10; i++);
	rNFADDR  = (page >> 8) & 0xff;
	for (i = 0; i < 10; i++);
	rNFADDR  = (page >> 16) & 0xff;
	for (i = 0; i < 10; i++);	
}

static void nand_page(U32 page)
{
	volatile U32 i;
	
	rNFADDR  = page & 0xff;
	for (i = 0; i < 10; i++);
	rNFADDR  = (page >> 8) & 0xff;
	for (i = 0; i < 10; i++);
	rNFADDR  = (page >> 16) & 0xff;
	for (i = 0; i < 10; i++);	
}

static void nand_col(U32 col)
{
	volatile U32 i;

	rNFADDR = col & 0xff;
	for (i = 0; i < 10; i++);
	rNFADDR = (col >> 8) & 0xff;
	for (i = 0; i < 10; i++);
}

static void nand_wait_ready(void)
{
	while (!(rNFSTAT & 1));
}

static S8 nand_data(void)
{
	return rNFDATA;
}

static U32 nand_bad(U32 addr)
{
	U32 col  = 2048;
	U32 page = addr / 2048;
	S8 val;

	/* 1. 选中 */
	nand_select();
	
	/* 2. 发出读命令00h */
	nand_cmd(0x00);
	
	/* 3. 发出地址(分5步发出) */
	nand_col(col);
	nand_page(page);
	
	/* 4. 发出读命令30h */
	nand_cmd(0x30);
	
	/* 5. 判断状态 */
	nand_wait_ready();

	/* 6. 读数据 */
	val = nand_data();
	
	/* 7. 取消选中 */		
	nand_deselect();

	/* 读取block的第2048个字节,每一个block的检测数据存放在OOB区(2048字节处)，
	   如果这个block为坏块，则2048字节处读出的数据是0xff */
	if (val != 0xff)
		return 1;  /* bad blcok */
	else
		return 0;
}

void nand_read(U32 addr, S8 *buf, U32 len)
{
	U32 col = addr % 2048;
	U32 i = 0;
		
	while (i < len)
	{

		if (!(addr & 0x1FFFF) && nand_bad(addr)) /* 一个block只判断一次 */
		{
			addr += (128*1024);  /* 跳过当前block */
			continue;
		}

		/* 1. 选中 */
		nand_select();
		
		/* 2. 发出读命令00h */
		nand_cmd(0x00);

		/* 3. 发出地址(分5步发出) */
		nand_addr(addr);

		/* 4. 发出读命令30h */
		nand_cmd(0x30);

		/* 5. 判断状态 */
		nand_wait_ready();

		/* 6. 读数据 */
		for (; (col < 2048) && (i < len); col++)
		{
			buf[i] = nand_data();
			i++;
			addr++;
		}
		col = 0;

		/* 7. 取消选中 */		
		nand_deselect();
		
	}
}

U32 isBootFromNorFlash(void)
{
	// OM[1:0]只有两种状态01或者00,00表示NAND启动，01表示16bitNOR启动
	if(rBWSCON & 0x6)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void copy2sdram(void)
{
	/* 要从lds文件中获得 __code_start, __bss_start
	 * 然后从0地址把数据复制到__code_start
	 */
	extern U32 __code_start, __bss_start;

	volatile U32 *dest = (volatile U32 *)&__code_start;
	volatile U32 *end = (volatile U32 *)&__bss_start;
	volatile U32 *src = (volatile U32 *)0;
	U32 len = (U32)(&__bss_start) - (U32)(&__code_start);

	if (isBootFromNorFlash())
	{
		while (dest < end)
		{
			*dest++ = *src++;
		}
	}
	else
	{
		nand_init();
		nand_read((U32)src, (S8 *)dest, len);
	}
}

void clean_bss(void)
{
	/* 要从lds文件中获得 __bss_start, __end */
	extern U32 __bss_start,__end;

	volatile U32 *start = (volatile U32 *)&__bss_start;
	volatile U32 *end = (volatile U32 *)&__end;


	while (start <= end)
	{
		*start++ = 0;
	}
}
