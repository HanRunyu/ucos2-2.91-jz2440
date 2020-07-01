/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : MEMCFG.h                                                *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*   TOOLCHAIN   : gcc version 8.3.0 (crosstool-NG 1.24.0)                 *
*                                                                         *
*   DESCRIPTION :                                                         *
*   s3c2440  Memory bank configuration file.                              *
*                                                                         *
**************************************************************************/



/* note: Reflect the changes in init.s */
#define FLASH_SADDR  0x00000000 				/* Flash starting address */
#define FLASH_SIZE	 0x200000
#define FLASH_EADDR (FLASH_SADDR+FLASH_SIZE-1) /* Flash end address */

#define NAND_SADDR	 0x00000000
#define NAND_SIZE	 0x10000000
#define NAND_EADDR (NAND_SADDR+NAND_SIZE-1) 	/* NAND end address */

#define SRAM_SIZE    (4*1024)   				/* 4K internal SRAM */
#define SFR_BADDR    0x48000000 				/* SFR base address */

#define SDRAM_SADDR  0x30000000 				/* SDRAM starting address */
#define SDRAM_SIZE   (64*1024*1024)				/* 64M SDRAM */
#define SDRAM_EADDR  (SDRAM_SADDR+SDRAM_SIZE-1) /* SRAM end address */

#define MMUTT_EADDR  SDRAM_EADDR
#define MMUTT_SIZE   (16*1024) 					/* It has to be in multiples of 16K */
#define MMUTT_SADDR  (MMUTT_EADDR-MMUTT_SIZE+1) /* MMU Table start address */

#define ISR_BADDR    (MMUTT_SADDR-0x100) 		/* ISR vector table start address */

/* These are from init.s, for stack analysis */
#define	_USR_STKSIZE  (1024*16)
#define _SVC_STKSIZE  (1024*16)
#define _UND_STKSIZE  (1024)
#define _ABT_STKSIZE  (1024)
#define _IRQ_STKSIZE  (1024*8)
#define _FIQ_STKSIZE  (1024*8)

#define STK_EADDR	  (ISR_BADDR-1)
#define STK_SIZE      (_USR_STKSIZE+_SVC_STKSIZE+_UND_STKSIZE+_ABT_STKSIZE+_IRQ_STKSIZE+_FIQ_STKSIZE)
#define STK_SADDR     (ISR_BADDR-STK_SIZE)

#define STK_USR		  (STK_EADDR+1)
#define STK_SVC		  (STK_USR-_USR_STKSIZE)
#define	STK_UND		  (STK_SVC-_SVC_STKSIZE)
#define	STK_ABT		  (STK_UND-_UND_STKSIZE)
#define STK_IRQ		  (STK_ABT-_ABT_STKSIZE)
#define STK_FIQ		  (STK_IRQ-_IRQ_STKSIZE)



/* BWSCON */
#define DW8		 		(0x0)
#define DW16			(0x1)
#define DW32			(0x2)
#define WAIT			(0x1<<2)
#define UBLB			(0x1<<3)

#define B1_BWSCON		(DW16)
#define B2_BWSCON		(DW16)
#define B3_BWSCON		(DW16 + WAIT + UBLB)
#define B4_BWSCON		(DW16)
#define B5_BWSCON		(DW16)
#define B6_BWSCON		(DW32)
#define B7_BWSCON		(DW32)

/* BANK0CON */
#define B0_Tacs			0x0	/*  0clk */
#define B0_Tcos			0x0	/*  0clk */
#define B0_Tacc			0x7	/* 14clk */
#define B0_Tcoh			0x0	/*  0clk */
#define B0_Tah			0x0	/*  0clk */
#define B0_Tacp			0x0
#define B0_PMC			0x0	/* normal */

/* BANK1CON */
#define B1_Tacs			0x0	/*  0clk */
#define B1_Tcos			0x0	/*  0clk */
#define B1_Tacc			0x7	/* 14clk */
#define B1_Tcoh			0x0	/*  0clk */
#define B1_Tah			0x0	/*  0clk */
#define B1_Tacp			0x0
#define B1_PMC			0x0

#define B2_Tacs			0x0
#define B2_Tcos			0x0
#define B2_Tacc			0x7
#define B2_Tcoh			0x0
#define B2_Tah			0x0
#define B2_Tacp			0x0
#define B2_PMC			0x0

#define B3_Tacs			0x0	/*  0clk */
#define B3_Tcos			0x3	/*  4clk */
#define B3_Tacc			0x7	/* 14clk */
#define B3_Tcoh			0x1	/*  1clk */
#define B3_Tah			0x0	/*  0clk */
#define B3_Tacp			0x3	/*  6clk */
#define B3_PMC			0x0	/* normal */

#define B4_Tacs			0x0	/*  0clk */
#define B4_Tcos			0x0	/*  0clk */
#define B4_Tacc			0x7	/*14clk */
#define B4_Tcoh			0x1	/*  1clk */
#define B4_Tah			0x0	/*  0clk */
#define B4_Tacp			0x0
#define B4_PMC			0x0	/* normal */

#define B5_Tacs			0x0	/*  0clk */
#define B5_Tcos			0x0	/*  0clk */
#define B5_Tacc			0x7	/* 14clk */
#define B5_Tcoh			0x0	/*  0clk */
#define B5_Tah			0x0	/*  0clk */
#define B5_Tacp			0x0
#define B5_PMC			0x0	/* normal */

#define B6_MT			0x3	/* SDRAM */
#define B6_Trcd			0x0	/* 2clk */
#define B6_SCAN			0x1	/* 9bit */

#define B7_MT			0x3	/* SDRAM */
#define B7_Trcd			0x0	/* 2clk */
#define B7_SCAN			0x1	/* 9bit */

/* REFRESH parameter */
#define REFEN			0x1		/* Refresh enable */
#define TREFMD			0x0		/* CBR(CAS before RAS)/Auto refresh */
#define Trp				0x0		/* 2clk */
#define Tsrc			0x0		/* 4clk */
#define REFCNT			1269	/* period=7.8us, HCLK=100Mhz, (2^11+1-7.8*100) */
