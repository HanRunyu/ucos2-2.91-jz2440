/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : MMU.c                                                   *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*   TOOLCHAIN   : gcc version 8.3.0 (crosstool-NG 1.24.0)                 *
*																		  *
*   DESCRIPTION :                                                         *
*   This is the MMU code file.                                            *
*                                                                         *
**************************************************************************/



#include "def.h"
#include "frmwrk.h"
#include "memcfg.h"
#include "s3c2440.h"
#include "mmulib.h"
#include "mmu.h"
#include "consol.h"


/* ********************************************************************* */
/* Global functions */


// 1) Only the section table is used. 
// 2) The cachable/non-cachable area can be changed by MMT_DEFAULT value.
//    The section size is 1MB.


/*
*********************************************************************************************
*                                       MMU_Init
*
* Description: This routine is used to initialize the MMU.
*
* Arguments  : none.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

void MMU_Init(void)
{
    U32 i,j;

	MMU_DisableDCache();
	MMU_DisableICache();
	
    //If write-back is used,the DCache should be cleared.
    for(i=0;i<64;i++)
        for(j=0;j<8;j++)
            MMU_CleanInvalidateDCacheIndex((i<<26)|(j<<5));
    MMU_InvalidateICache();

    MMU_DisableMMU();
    MMU_InvalidateTLB();

    //MMU_SetMTT(int wVSAddr,int wVEAddr,int wPSAddr,int wAttrib)
    MMU_SetMTT(0x00000000,0x07f00000,0x00000000,RW_NCNB);  		//bank0
    MMU_SetMTT(0x08000000,0x0ff00000,0x08000000,RW_NCNB);  		//bank1
    MMU_SetMTT(0x10000000,0x17f00000,0x10000000,RW_NCNB); 		//bank2
    MMU_SetMTT(0x18000000,0x1ff00000,0x18000000,RW_NCNB); 		//bank3
    MMU_SetMTT(0x20000000,0x27f00000,0x20000000,RW_NCNB); 		//bank4
    MMU_SetMTT(0x28000000,0x2ff00000,0x28000000,RW_NCNB); 		//bank5
    //MMU_SetMTT(0x30000000,0x30f00000,0x30000000,RW_CB);      	//bank6-1
    //MMU_SetMTT(0x31000000,0x33e00000,0x31000000,RW_NCNB); 	//bank6-2
    //MMU_SetMTT(0x33f00000,0x33f00000,0x33f00000,RW_CB);   	//bank6-3
    MMU_SetMTT(0x30000000,0x37f00000,0x30000000,RW_CNB); 		//bank6
    MMU_SetMTT(0x38000000,0x3ff00000,0x38000000,RW_CNB); 		//bank7
    MMU_SetMTT(0x40000000,0x5ff00000,0x40000000,RW_NCNB);		//SFR+StepSram    
    MMU_SetMTT(0x60000000,0xfff00000,0x60000000,RW_FAULT);		//not used

    MMU_SetTTBase(MMUTT_SADDR);
	//DOMAIN1: no_access, DOMAIN0,2~15=client(AP is checked)
    MMU_SetDomain(0x55555550|DOMAIN1_ATTR|DOMAIN0_ATTR); 

    MMU_SetProcessId(0x0);
    MMU_EnableAlignFault();
	
    MMU_EnableMMU();
    MMU_EnableICache();
    MMU_EnableDCache(); //DCache should be turned on after MMU is turned on.
}    

/*
*********************************************************************************************
*                                       MMU_SetMTT
*
* Description: This routine sets MMU mapping table for a range for virtual addresses.
*
* Arguments  : wVSAddr - Virtual address start.
*              wVEAddr - Virtual address end.
*              wPSAddr - Physical address start.
*              wAttrib - MMU Attribute.
*
* Return     : none.
*
* Note(s)    : 
*********************************************************************************************
*/

void MMU_SetMTT(U32 wVSAddr,U32 wVEAddr,U32 wPSAddr,U32 wAttrib)
{
    U32 *pTT;
    int i,nSec;
    pTT=(U32 *)MMUTT_SADDR+(wVSAddr>>20);
    nSec=(wVEAddr>>20)-(wVSAddr>>20);
    for(i=0;i<=nSec;i++)
		*pTT++=wAttrib |(((wPSAddr>>20)+i)<<20);
}


/* ********************************************************************* */
