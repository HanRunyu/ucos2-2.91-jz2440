/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : INIT.s                                                  *
*                                                                         *
*   AUTHOR      : HanRunyu                                                *
*                 URL  : http://github.com/HanRunyu                       *
*                                                                         *
*   PROCESSOR   : s3c2440  (32 bit ARM920T RISC core from Samsung)        *
*                                                                         *
*   TOOLCHAIN   : arm-linux-gnueabi-gcc(Linaro 7.5.0)                     *
*                                                                         *
*   DESCRIPTION :                                                         *
*   s3c2440  processor Start up assembly code file.                       *
*                                                                         *
**************************************************************************/



#include "memcfg.h"
#include "s3c2440.a"

	.macro HandlerLabel ISR_Entry
	sub sp,sp,#4	/* stm默认高寄存器先压栈，ldm默认低寄存器先出栈，与顺序无关，此位置空出放pc指针 */
	stmfd sp!,{r0}
	ldr r0,=\ISR_Entry
	ldr r0,[r0]
	str r0,[sp,#4]
	ldmfd sp!,{r0,pc}
	.endm


	.section ".vectors", "ax"	
	.global start
start:
	b reset 		 				/* vector 0 : reset */
	ldr pc, _undefined_instruction	/* vector 4 : und */
	ldr pc, _software_interrupt		/* vector 8 : swi */
	ldr pc, _prefetch_abort			/* vector 0x0c : prefetch aboot */
	ldr pc, _data_abort				/* vector 0x10 : data abort */
	b reset							/* vector 0x14 : reserved */
	ldr pc, _irq					/* vector 0x18 : irq */
	ldr pc, _fiq					/* vector 0x1c : fiq */

	.global		_undefined_instruction
	.global		_software_interrupt
	.global		_prefetch_abort
	.global		_data_abort
	.global		_irq
	.global		_fiq
	
	_undefined_instruction:	.word undefined_instruction
	_software_interrupt:	.word software_interrupt
	_prefetch_abort:		.word prefetch_abort
	_data_abort:			.word data_abort
	_irq:					.word irq
	_fiq:					.word fiq
	.balignl 64,0xdeadbeef


undefined_instruction:
	HandlerLabel ISR_UNDEF

software_interrupt:
	HandlerLabel ISR_SWI

prefetch_abort:
	HandlerLabel ISR_PABORT

data_abort:
	HandlerLabel ISR_DABORT
	
irq:
	HandlerLabel ISR_IRQ

fiq:
	HandlerLabel ISR_FIQ

	
	.global		reset
reset:
	/* 关闭看门狗 */
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]

	/* 关闭所有中断 */
	ldr    r0,=INTMSK
	ldr    r1,=BIT_ALLMSK
	str    r1,[r0]

	/* 关闭所有子中断 */
	ldr    r0,=INTSUBMSK
	ldr    r1,=BIT_SUB_ALLMSK
	str    r1,[r0]

	/* 设置MPLL, FCLK : HCLK : PCLK = 400m : 100m : 50m */
	/* LOCKTIME(0x4C000000) = 0x0E100E10 */
	ldr r0, =LOCKTIME
	ldr r1, =(3600<<16|3600)
	str r1, [r0]

	/* CLKDIVN(0x4C000014) = 0x5, tFCLK:tHCLK:tPCLK = 1:4:8  */
	ldr r0, =CLKDIVN
	ldr r1, =0x5
	str r1, [r0]

	/* 设置CPU工作于异步模式 */
	bl MMU_SetAsyncBusMode
	
	/* 设置MPLLCON(0x4C000004) = (92<<12)|(1<<4)|(1<<0) 
	 *	m = MDIV+8 = 92+8=100
	 *	p = PDIV+2 = 1+2 = 3
	 *	s = SDIV = 1
	 *	FCLK = 2*m*Fin/(p*2^s) = 2*100*12/(3*2^1)=400M
	 */
	/* 一旦设置PLL, 就会锁定lock time直到PLL输出稳定
	 * 然后CPU工作于新的频率FCLK
	 */
	ldr r0, =MPLLCON
	ldr r1, =(92<<12)|(1<<4)|(1<<0)
	str r1, [r0]

	/* Check if the boot is caused by the wake-up from POWER_OFF mode. */
    ldr		r1,=GSTATUS2
    ldr		r0,[r1]
    tst		r0,#0x2
    /* In case of the wake-up from POWER_OFF mode, go to POWER_OFF_WAKEUP handler. */ 
	bne		wakeup_power_off

	/* Set memory control registers */
	bl mem_init

    /* Initialize stacks */
    bl init_stacks

	/* 重定位text, rodata, data段整个程序 */
	.extern		copy2sdram
	bl copy2sdram

	/* 清除BSS段 */
	.extern		clean_bss
	bl clean_bss

program:
    /* Call the actual C program.Should never return. */
	.extern	C_vMain
	ldr lr,=halt
    ldr pc,=C_vMain
halt:
	b halt


wakeup_power_off:
	@ Release SCLKn after wake-up from the POWER_OFF mode.
	ldr 	r1,=MISCCR
	ldr    r0,[r1]
	bic    r0,r0,#(7<<17)			@ SCLK0:0->SCLK, SCLK1:0->SCLK, SCKE:L->H
	str    r0,[r1]

	@ Set memory control registers
	adr    r0,SMRDATA
	ldr    r1,=BWSCON				@ BWSCON Address
	add    r2, r0, #52				@ End address of SMRDATA
0:	
	ldr    r3, [r0], #4    
	str    r3, [r1], #4    
	cmp    r2, r0		 
	bne    0b

	mov r1,#256
1:	subs r1,r1,#1					@ 1) wait until the SelfRefresh is released.
	bne 1b 	   
	
	ldr r1,=GSTATUS3				@ GSTATUS3 has the start address just after POWER_OFF wake-up
	ldr r0,[r1]
	mov pc,r0

mem_init:
	adr    r0,SMRDATA
	ldr    r1,=BWSCON			@ BWSCON Address
	add    r2, r0, #52			@ End address of SMRDATA
2:		
	ldr    r3, [r0], #4    
	str    r3, [r1], #4    
	cmp    r2, r0		 
	bne    2b
	mov pc, lr

init_stacks:
        /* Don't use DRAM,such as stmfd,ldmfd......
         * SVCstack is initialized before
         * Under toolkit ver 2.50, 'msr cpsr,r1' can be used instead of 'msr cpsr_cxsf,r1' */
        mrs r0,cpsr
        bic r0,r0,#MODEMASK
        orr r1,r0,#(UNDEFMODE|NOINT)
        msr cpsr_cxsf,r1            @ UndefMode
        ldr sp,=STK_UND
        
        orr r1,r0,#(ABORTMODE|NOINT)
        msr cpsr_cxsf,r1            @ AbortMode
        ldr sp,=STK_ABT

        orr r1,r0,#(IRQMODE|NOINT)
        msr cpsr_cxsf,r1            @ IRQMode
        ldr sp,=STK_IRQ	
        
        orr r1,r0,#(FIQMODE|NOINT)
        msr cpsr_cxsf,r1            @ FIQMode
        ldr sp,=STK_FIQ

		bic r0,r0,#(MODEMASK|NOINT)
        orr r1,r0,#SVCMODE
        msr cpsr_cxsf,r1            @ SVCMode
        ldr sp,=STK_SVC

		//b stacks_return
        mov pc,lr                   @ The LR register may be not valid for the mode changes.


SMRDATA:
	.word (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28)) 	/* BWSCON   */
	.word ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC)) 							/* BANKCON0 */
	.word ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC)) 							/* BANKCON1 */
	.word ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC)) 							/* BANKCON2 */
	.word ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC)) 							/* BANKCON3 */
	.word ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC)) 							/* BANKCON4 */
	.word ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC)) 							/* BANKCON5 */
	.word ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))																					/* BANKCON6 */
	.word ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))																					/* BANKCON7 */
	.word ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Tsrc<<18)++REFCNT)																/* REFRESH  */
	.word 0xb1																													/* BANKSIZE */
	.word 0x20																													/* MRSRB6   */
	.word 0x20																													/* MRSRB7   */

	.end
