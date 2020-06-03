/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : FRMWRK.h                                                *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*	TOOLCHAIN	: arm-linux-gnueabi-gcc(Linaro 7.5.0)					  *
*																		  *
*   DESCRIPTION :                                                         *
*   External interface & Module configuration header for FRMWRK           *
*   Infrastructure module.                                                *
*                                                                         *
**************************************************************************/



#ifndef __FRMWRK_H__
#define __FRMWRK_H__


#include "def.h"


#ifdef __cplusplus
extern "C" {
#endif


/* ********************************************************************* */
/* Module configuration */

#define __mDate "2020/05/26"           /* Revision date */
#define __mVer  "1.0"                  /* Revision number */

#define __mAuthor "HanRunyu, https://github.com/HanRunyu"
#define __mProcessor "s3c2440 (ARM920T from Samsung)"

#define __nConsolPort         0        /* Consol UART port number */
#define __nConsolBaud         115200   /* Consol Baud rate */
#define __nConsolFifoEn       True     /* FIFO Enable flag */

#define MMU_enabled                    /* This switch is included with the compiler flags */

#define FCLK (400000000)               /* 400Mhz */
#define HCLK (FCLK/4)
#define PCLK (FCLK/8)
#define UCLK 48000000


/* ********************************************************************* */
/* Interface function definition */

/*
***************************************************************************
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
*                       3. C Variables (RW & ZI)
***************************************************************************
*/
void FRMWRK_vRamTest(S8 *pbID,U32 wSAddr,U32 wEAddr);

/*
***************************************************************************
*                                       FRMWRK_vStartTicker
*
* Description: This routine starts Timer1 (TC1) in the Prescale mode for OS Tick.
*
* Arguments  : wTicksPerSec - Time ticks per second.
*
* Return     : none.
*
* Note(s)    : 
***************************************************************************
*/
void FRMWRK_vStartTicker(U32 wTicksPerSec); /* wTicksPerSec = 10...10000 ticks per sec */

/*
***************************************************************************
*                                       C_vMain
*
* Description: This is the FRMWRK main entry function.
*
* Arguments  : none.
*
* Return     : none.
*
* Note(s)    : 
***************************************************************************
*/
void C_vMain(void);


/* ********************************************************************* */

#ifdef __cplusplus
}
#endif

#endif /*__FRMWRK_H__*/
