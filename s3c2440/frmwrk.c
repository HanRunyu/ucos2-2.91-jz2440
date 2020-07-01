/**************************************************************************
*																		  *
*	PROJECT 	: ARM port for UCOS-II									  *
*																		  *
*	MODULE		: FRMWRK.c												  *
*																		  *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*   TOOLCHAIN   : gcc version 8.3.0 (crosstool-NG 1.24.0)                 *
*																		  *
*	DESCRIPTION :														  *
*	This is the Framework module. Creates an operating infrastructure. 	  *
*																		  *
**************************************************************************/



#include "includes.h"
#include "mmu.h"
#include "memcfg.h"
#include "consol.h"
#include "printf.h"
#include "app_main.h"


/* ********************************************************************* */
/* File local definitions */

extern int __end;
#define C_wRTMem      (&__end)
#define C_wRTMemLimit (STK_SADDR-1)


/* ********************************************************************* */
/* Local functions */

/*
*********************************************************************************************
*                                       __Haltx
*
* Description: These exception handlers are used to report a particular 
*			   exception on the CONSOL & halt.
*
* Arguments  : none.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

void __HaltUndef(void)
{
	CONSOL_Printf("Undefined instruction exception!!!\n");
    while(1);
}

void __HaltSwi(void)
{
	CONSOL_Printf("SWI exception!!!\n");
    while(1);
}

void __HaltPabort()
{
	CONSOL_Printf("Pabort exception!!!\n");
	while(1);
}

void __HaltDabort(void)
{
	CONSOL_Printf("Dabort exception !!!\n");
	while(1);
}

void __HaltFiq(void)
{
	CONSOL_Printf("FIQ exception!!!\n");
	while(1);
}

void __HaltIrq(void)
{
	CONSOL_Printf("IRQ exception!!!\n");
	while(1);
}

/*
*********************************************************************************************
*                                       __vInitHaltHandlers
*
* Description: This routine hooks all the Halt exception handlers. Exceptions which are to
*              be handled by the application can be overwritten with the new handler at the
*              appropriate Software hook location.
*
* Arguments  : none.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

static void __vInitHaltHandlers(void)
{
	pISR_UNDEF 	= (U32)__HaltUndef;
    pISR_SWI   	= (U32)__HaltSwi;
    pISR_PABORT	= (U32)__HaltPabort;
    pISR_DABORT	= (U32)__HaltDabort;
    pISR_FIQ   	= (U32)__HaltFiq;
    pISR_IRQ   	= (U32)__HaltIrq;
}

/*
*********************************************************************************************
*                                       __vLogo
*
* Description: This routine display the Logo on the CONSOL port.
*
* Arguments  : none.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

static void __vLogo(void)
{
	CONSOL_Printf("\n\nUCOS_FRAMEWORK Ver %s for %s :%s\n",
				   __mVer,__mProcessor,__mDate);
	CONSOL_Printf("Built using %s on %s   <%s>\n\n",
				   "gcc version 8.3.0 (crosstool-NG 1.24.0)"
				   ,__DATE__,__TIME__);
	CONSOL_Printf("Endian: %s\n",
#ifdef __BIG_ENDIAN
				   "BIG"
#else
				   "LITTLE"
#endif
				   );
	CONSOL_Printf("CONSOL: COM%d, %dbps, 8Bit, NP\n",__nConsolPort,__nConsolBaud);
	CONSOL_Printf("CPU Clk: %dMHz   MMU: %s   Cache: %s   Write Buf: %s\n",FCLK/1000000,
#ifdef MMU_enabled
				   "ON","ON","ON");
#else
				   "OFF","OFF","OFF");
#endif
	if(rBWSCON & 0x6)	// Nor∆Ù∂Ø
	{
		CONSOL_Printf("FLASH_SADDR:%08xh\tFLASH_SIZE:%08xh\n",FLASH_SADDR,FLASH_SIZE);
		CONSOL_Printf("NAND_SADDR:%08xh\tNAND_SIZE:%08xh\n",NAND_SADDR,NAND_SIZE);
		CONSOL_Printf("SRAM_SADDR:%08xh\tSRAM_SIZE:%08xh\n",0x40000000,SRAM_SIZE);
	}
	else				// Nand∆Ù∂Ø
	{
		CONSOL_Printf("NAND_SADDR:%08xh\tNAND_SIZE:%08xh\n",NAND_SADDR,NAND_SIZE);
		CONSOL_Printf("SRAM_SADDR:%08xh\tSRAM_SIZE:%08xh\n",0x00000000,SRAM_SIZE);
	}
	CONSOL_Printf("SDRAM_SADDR:%08xh\tSDRAM_SIZE:%08xh\n",SDRAM_SADDR,SDRAM_SIZE);

	CONSOL_Printf("MMUTT_SADDR:%08xh\tMMUTT_SIZE:%08xh\n",MMUTT_SADDR,MMUTT_SIZE);
	CONSOL_Printf("ISR_BADDR:%08xh\n\r",ISR_BADDR);
	CONSOL_Printf("STK_SADDR:%08xh\tSTK_SIZE:%08xh\n",STK_SADDR,STK_SIZE);

    CONSOL_Printf("Free RAM: %08xh ~ %08xh\n", C_wRTMem, C_wRTMemLimit);
    CONSOL_Printf("Developed by %s\n\n",__mAuthor);
}

/*
*********************************************************************************************
*                                       __vWDTInterrupt
*
* Description: This routine clears the pending WDT interrupt & calls the OS tick handler.
*
* Arguments  : none.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

static void __vWDTInterrupt(void)
{
	rSUBSRCPND |= BIT_SUB_WDT;
	rSRCPND |= BIT_WDT_AC97;
	rINTPND |= BIT_WDT_AC97;
        
	OSTimeTick();
}

/*
*********************************************************************************************
*                                       __vPortInit
*
* Description: This routine sets the default GPIO condition.
*
* Arguments  : none.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

static void __vPortInit(void)
{
	//CAUTION:Follow the configuration order for setting the ports. 
    // 1) setting value(GPnDAT) 
    // 2) setting control register  (GPnCON)
    // 3) configure pull-up resistor(GPnUP)  

    //32bit data bus configuration  
    //*** PORT A GROUP
    //Ports  : GPA22 GPA21  GPA20 GPA19 GPA18 GPA17 GPA16 GPA15 GPA14 GPA13 GPA12  
    //Signal : nFCE nRSTOUT nFRE   nFWE  ALE   CLE  nGCS5 nGCS4 nGCS3 nGCS2 nGCS1 
    //Binary :  1     1      1  , 1   1   1    1   ,  1     1     1     1
    //Ports  : GPA11   GPA10  GPA9   GPA8   GPA7   GPA6   GPA5   GPA4   GPA3   GPA2   GPA1  GPA0
    //Signal : ADDR26 ADDR25 ADDR24 ADDR23 ADDR22 ADDR21 ADDR20 ADDR19 ADDR18 ADDR17 ADDR16 ADDR0 
    //Binary :  1       1      1      1   , 1       1      1      1   ,  1       1     1      1         
    rGPACON = 0x007fffff; 

    //**** PORT B GROUP
    //Ports  : GPB10    GPB9    GPB8    GPB7    GPB6     GPB5    GPB4   GPB3   GPB2     GPB1      GPB0
    //Signal : nXDREQ0 nXDACK0 nXDREQ1 nXDACK1 nSS_KBD nDIS_OFF L3CLOCK L3DATA L3MODE nIrDATXDEN Keyboard
    //Setting: INPUT  OUTPUT   INPUT  OUTPUT   INPUT   OUTPUT   OUTPUT OUTPUT OUTPUT   OUTPUT    OUTPUT 
    //Binary :   00  ,  01       00  ,   01      00   ,  01       01  ,   01     01   ,  01        01  
    rGPBCON = 0x044555;
    rGPBUP  = 0x7ff;     // The pull up function is disabled GPB[10:0]

    //*** PORT C GROUP
    //Ports  : GPC15 GPC14 GPC13 GPC12 GPC11 GPC10 GPC9 GPC8  GPC7   GPC6   GPC5 GPC4 GPC3  GPC2  GPC1 GPC0
    //Signal : VD7   VD6   VD5   VD4   VD3   VD2   VD1  VD0 LCDVF2 LCDVF1 LCDVF0 VM VFRAME VLINE VCLK LEND  
    //Binary :  10   10  , 10    10  , 10    10  , 10   10  , 10     10  ,  10   10 , 10     10 , 10   10
    rGPCCON = 0xaaaaaaaa;       
    rGPCUP  = 0xffff;     // The pull up function is disabled GPC[15:0] 

    //*** PORT D GROUP
    //Ports  : GPD15 GPD14 GPD13 GPD12 GPD11 GPD10 GPD9 GPD8 GPD7 GPD6 GPD5 GPD4 GPD3 GPD2 GPD1 GPD0
    //Signal : VD23  VD22  VD21  VD20  VD19  VD18  VD17 VD16 VD15 VD14 VD13 VD12 VD11 VD10 VD9  VD8
    //Binary : 10    10  , 10    10  , 10    10  , 10   10 , 10   10 , 10   10 , 10   10 ,10   10
    rGPDCON = 0xaaaaaaaa;       
    rGPDUP  = 0xffff;         // The pull up function is disabled GPD[15:0]

    //*** PORT E GROUP
    //Ports  : GPE15  GPE14 GPE13   GPE12   GPE11   GPE10   GPE9    GPE8     GPE7  GPE6  GPE5   GPE4  
    //Signal : IICSDA IICSCL SPICLK SPIMOSI SPIMISO SDDATA3 SDDATA2 SDDATA1 SDDATA0 SDCMD SDCLK I2SSDO 
    //Binary :  10     10  ,  10      10  ,  10      10   ,  10      10   ,   10    10  , 10     10  ,     
    //-------------------------------------------------------------------------------------------------------
    //Ports  :  GPE3   GPE2  GPE1    GPE0    
    //Signal : I2SSDI CDCLK I2SSCLK I2SLRCK     
    //Binary :  10     10  ,  10      10 
    rGPECON = 0xaaaaaaaa;       
    rGPEUP  = 0xffff;     // The pull up function is disabled GPE[15:0]

    //*** PORT F GROUP
    //Ports  : GPF7   GPF6   GPF5   GPF4      GPF3     GPF2  GPF1   GPF0
    //Signal : nLED_8 nLED_4 nLED_2 nLED_1 nIRQ_PCMCIA EINT2 KBDINT EINT0
    //Setting: Output Output Output Output    EINT3    EINT2 EINT1  EINT0
    //Binary :  01      01 ,  01     01  ,     10       10  , 10     10
    rGPFCON = 0x55aa;
    rGPFUP  = 0xff;     // The pull up function is disabled GPF[7:0]

    //*** PORT G GROUP
    //Ports  : GPG15 GPG14 GPG13 GPG12  GPG11    GPG10    GPG9     GPG8     GPG7      GPG6    
    //Signal : nYPON  YMON nXPON EINT20 EINT19 DMAMODE1 DMAMODE0 DMASTART KBDSPICLK KBDSPIMOSI
    //Setting: nYPON  YMON nXPON XMON   EINT19  Output   Output   Output   SPICLK1    SPIMOSI1
    //Binary :   00    00 , 00    11  ,  10      01    ,   01       00   ,    11         11
    //-----------------------------------------------------------------------------------------
    //Ports  :    GPG5       GPG4    GPG3    GPG2    GPG1    GPG0    
    //Signal : KBDSPIMISO LCD_PWREN EINT11 nSS_SPI IRQ_LAN IRQ_PCMCIA
    //Setting:  SPIMISO1  LCD_PWRDN EINT11   nSS0   EINT9    EINT8
    //Binary :     11         01   ,  10      01  ,  01        01
    rGPGCON = 0x0394fd95;
    rGPGUP  = 0xffff;    // The pull up function is disabled GPG[15:0]

    //*** PORT H GROUP
    //Ports  :  GPH10    GPH9  GPH8 GPH7  GPH6  GPH5 GPH4 GPH3 GPH2 GPH1  GPH0 
    //Signal : CLKOUT1 CLKOUT0 UCLK RXD2 TXD2 RXD1 TXD1 RXD0 TXD0 nRTS0 nCTS0
    //Binary :   01   ,  01     01 , 10    10  , 10   10 , 10   10 , 10    10
    rGPHCON = 0x15aaaa;
    rGPHUP  = 0x7ff;    // The pull up function is disabled GPH[10:0]
    
    //External interrupt will be falling edge triggered. 
    rEXTINT0 = 0x22222222;    // EINT[7:0]
    rEXTINT1 = 0x22222222;    // EINT[15:8]
    rEXTINT2 = 0x22222222;    // EINT[23:16]
}




/* ********************************************************************* */
/* Global functions */

/*
*********************************************************************************************
*                                       C_IRQHandler
*
* Description: This routine is the IRQ handler. Handles all peripheral interrupts.
*
* Arguments  : none.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

void C_IRQHandler(void)
{
	U32 wTemp;

    wTemp = rINTOFFSET<<2;
    ((void(*)(void))(*((U32 *)(aISR_EINT0+wTemp))))();
}

/*
*********************************************************************************************
*                                       FRMWRK_vStartTicker
*
* Description: This routine starts Timer1 (TC1) in the Prescale mode for OS Tick.
*
* Arguments  : wTicksPerSec - Time ticks per second.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

void FRMWRK_vStartTicker(U32 wTicksPerSec)
{
#if OS_CRITICAL_METHOD == 3                         /* Allocate storage for CPU status register           */
	OS_CPU_SR  cpu_sr;
#endif

    OS_ENTER_CRITICAL();

    rWTCON = 0;                                 // Disable watchdog
	
	rSUBSRCPND |= BIT_SUB_WDT;
    rSRCPND |= BIT_WDT_AC97;
    rINTPND |= BIT_WDT_AC97;
	rINTMOD &= ~BIT_WDT_AC97;
	rINTMSK &= ~(BIT_WDT_AC97);
  	rINTSUBMSK &= ~(BIT_SUB_WDT);

    pISR_WDT_AC97 = (U32)__vWDTInterrupt;

    rWTDAT = rWTCNT = PCLK / 16 / wTicksPerSec; //set up the WDT for wTicksPerSec

    rWTCON = (0<<8)|(1<<5)|(0<<3)|(1<<2)|(0<<0);// Enable: WD, WD interrupts

    BIT_CLR(rINTMSK, BIT_WDT_AC97);              // Enable WatchDog interrupts

    OS_EXIT_CRITICAL();
}

/*
*********************************************************************************************
*                                       FRMWRK_vRamTest
*
* Description: This routine is used do RAM test.
*
* Arguments  : pbID   - Test identification string.
*              wSAddr - RAM starting address.
*              wEAddr - RAM end address.
*
* Return     : none.
*
* Note(s)    : Do not test the following areas using this routine:
*                       1. Stack
*                       2. Software vector table
*                       3. C Variables
*********************************************************************************************
*/

void FRMWRK_vRamTest(S8 *pbID,U32 wSAddr,U32 wEAddr)
{
	U32 wI,wJ;
	S8 bError=0;
        
    CONSOL_Printf("\n%s(%08xh-%08xh):WR",pbID,wSAddr,wEAddr);
    for(wI=wSAddr;wI<wEAddr;wI+=4)
    {
		*((volatile U32 *)wI)=wI;
    }
    CONSOL_Printf("\b\bRD");
    for(wI=wSAddr;wI<wEAddr;wI+=4)
    {
		 wJ=*((volatile U32 *)wI);
		if(wJ!=wI)bError=1;
    }

    if(bError==0)CONSOL_Printf("\b\bO.K.\n");
    else CONSOL_Printf("\b\bFAIL\n");
}

/*
*********************************************************************************************
*                                       C_vMain
*
* Description: This is the main C entry function.
*
* Arguments  : none.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

void C_vMain(void)
{
    __vInitHaltHandlers();

    pISR_IRQ = (U32)UCOS_IRQHandler;

    __vPortInit();

	CONSOL_Select(__nConsolPort);
    CONSOL_Init(__nConsolBaud);

	MMU_Init();

	__vLogo();

    APP_vMain();

    CONSOL_Printf("APP has ended...\n\r");
}

/* ********************************************************************* */
