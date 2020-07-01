/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : MMULIB.h                                                *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*   TOOLCHAIN   : gcc version 8.3.0 (crosstool-NG 1.24.0)                 *
*                                                                         *
*   DESCRIPTION :                                                         *
*   External interface & Module configuration header for MMULIB.          *
*                                                                         *
**************************************************************************/



#ifndef __MMULIB_H__
#define __MMULIB_H__

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ********************************************************************* */
/* Interface function definition */


U32 SET_IF(void);
void WR_IF(U32 cpsrValue);
void CLR_IF(void);

void MMU_EnableICache(void);
void MMU_DisableICache(void);
void MMU_EnableDCache(void);
void MMU_DisableDCache(void);
void MMU_EnableAlignFault(void);
void MMU_DisableAlignFault(void);
void MMU_EnableMMU(void);
void MMU_DisableMMU(void);
void MMU_SetTTBase(U32 base);
void MMU_SetDomain(U32 domain);

void MMU_SetFastBusMode(void);  //GCLK=HCLK
void MMU_SetAsyncBusMode(void); //GCLK=FCLK @(FCLK>=HCLK)

void MMU_InvalidateIDCache(void);
void MMU_InvalidateICache(void);
void MMU_InvalidateICacheMVA(U32 mva);
void MMU_PrefetchICacheMVA(U32 mva);
void MMU_InvalidateDCache(void);
void MMU_InvalidateDCacheMVA(U32 mva);
void MMU_CleanDCacheMVA(U32 mva);
void MMU_CleanInvalidateDCacheMVA(U32 mva);
void MMU_CleanDCacheIndex(U32 index);
void MMU_CleanInvalidateDCacheIndex(U32 index);   
void MMU_DrainWriteBuffer(void);
void MMU_WaitForInterrupt(void);
    
void MMU_InvalidateTLB(void);
void MMU_InvalidateITLB(void);
void MMU_InvalidateITLBMVA(U32 mva);
void MMU_InvalidateDTLB(void);
void MMU_InvalidateDTLBMVA(U32 mva);

void MMU_SetDCacheLockdownBase(U32 base);
void MMU_SetICacheLockdownBase(U32 base);

void MMU_SetDTLBLockdown(U32 baseVictim);
void MMU_SetITLBLockdown(U32 baseVictim);

void MMU_SetProcessId(U32 pid);


/* ********************************************************************* */

#ifdef __cplusplus
}
#endif

#endif /*__MMULIB_H__*/
