/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : MMULIB.s                                                *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*   TOOLCHAIN   : gcc version 8.3.0 (crosstool-NG 1.24.0)                 *
*                                                                         *
*   DESCRIPTION :                                                         *
*   s3c2440  processor mmu assembly library file.                         *
*                                                                         *
**************************************************************************/



	.equ 	NOINT,0xc0

	.ifdef THUMBCODE
		.thumb
	.else
		.arm
	.endif

	.macro MOV_PC_LR
	.ifdef THUMBCODE
		bx lr
	.else
		mov pc,lr
	.endif
	.endm


    .text
@==============
@ CPSR I,F bit
@==============
@U32 SET_IF(void)@
@The return value is current CPSR.
    .global		SET_IF
SET_IF:
    @This function works only if the processor is in previliged mode.
    mrs r0,cpsr
    mov r1,r0
    orr r1,r1,#NOINT
    msr cpsr,r1        
    MOV_PC_LR

@void WR_IF(U32 cpsrValue)@
    .global		WR_IF
WR_IF:    
    @This function works only if the processor is in previliged mode.
    msr cpsr,r0        
    MOV_PC_LR


@void CLR_IF(void)@
    .global		CLR_IF
CLR_IF:
    @This function works only if the processor is in previliged mode.
    mrs r0,cpsr
    bic r0,r0,#NOINT
    msr cpsr,r0        
    MOV_PC_LR

@====================================
@ MMU Cache/TLB/etc on/off functions
@====================================
	.equ	R1_iA,(1<<31)
	.equ	R1_nF,(1<<30)
	.equ	R1_I ,(1<<12)
	.equ	R1_C ,(1<<2)
	.equ	R1_A ,(1<<1)
	.equ	R1_M ,(1)

@void MMU_EnableICache(void)
	.global		MMU_EnableICache
MMU_EnableICache:    
    mrc p15,0,r0,c1,c0,0
    orr r0,r0,#R1_I
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@void MMU_DisableICache(void)
	.global		MMU_DisableICache
MMU_DisableICache:    
    mrc p15,0,r0,c1,c0,0
    bic r0,r0,#R1_I
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@void MMU_EnableDCache(void)
	.Global		MMU_EnableDCache
MMU_EnableDCache:    
    mrc p15,0,r0,c1,c0,0
    orr r0,r0,#R1_C
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@void MMU_DisableDCache(void)
	.global		MMU_DisableDCache
MMU_DisableDCache:    
    mrc p15,0,r0,c1,c0,0
    bic r0,r0,#R1_C
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@void MMU_EnableAlignFault(void)
	.global		MMU_EnableAlignFault 
MMU_EnableAlignFault:
    mrc p15,0,r0,c1,c0,0
    orr r0,r0,#R1_A
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@void MMU_DisableAlignFault(void)
	.global		MMU_DisableAlignFault
MMU_DisableAlignFault:
    mrc p15,0,r0,c1,c0,0
    bic r0,r0,#R1_A
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@void MMU_EnableMMU(void)
	.global 	MMU_EnableMMU
MMU_EnableMMU:
    mrc p15,0,r0,c1,c0,0
    orr r0,r0,#R1_M
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@void MMU_DisableMMU(void)
	.global		MMU_DisableMMU
MMU_DisableMMU:
    mrc p15,0,r0,c1,c0,0
    bic r0,r0,#R1_M
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@void MMU_SetFastBusMode(void)
@ FCLK:HCLK= 1:1
	.global		MMU_SetFastBusMode
MMU_SetFastBusMode:
    mrc p15,0,r0,c1,c0,0
    bic r0,r0,#(R1_iA|R1_nF)
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@void MMU_SetAsyncBusMode(void) 
@ FCLK:HCLK= 1:2
	.global		MMU_SetAsyncBusMode
MMU_SetAsyncBusMode:
    mrc p15,0,r0,c1,c0,0
    orr r0,r0,#(R1_nF|R1_iA)
    mcr p15,0,r0,c1,c0,0
    MOV_PC_LR

@=========================
@ Set TTBase
@=========================
@void MMU_SetTTBase(U32 base)
	.global		MMU_SetTTBase
MMU_SetTTBase:
    @ro=TTBase
    mcr p15,0,r0,c2,c0,0
    MOV_PC_LR

@=========================
@ Set Domain
@=========================
@void MMU_SetDomain(U32 domain)
	.global 	MMU_SetDomain
MMU_SetDomain:
    @ro=domain
    mcr p15,0,r0,c3,c0,0
    MOV_PC_LR

@=========================
@ ICache/DCache functions
@=========================
@void MMU_InvalidateIDCache(void)
	.global 	MMU_InvalidateIDCache
MMU_InvalidateIDCache:
    mcr p15,0,r0,c7,c7,0
    MOV_PC_LR

@void MMU_InvalidateICache(void)
	.global		MMU_InvalidateICache
MMU_InvalidateICache:
    mcr p15,0,r0,c7,c5,0
    MOV_PC_LR

@void MMU_InvalidateICacheMVA(U32 mva)
	.global 	MMU_InvalidateICacheMVA
MMU_InvalidateICacheMVA:    
    @r0=mva
    mcr p15,0,r0,c7,c5,1
    MOV_PC_LR
    
@void MMU_PrefetchICacheMVA(U32 mva)
	.global 	MMU_PrefetchICacheMVA
MMU_PrefetchICacheMVA:
    @r0=mva
    mcr p15,0,r0,c7,c13,1
    MOV_PC_LR

@void MMU_InvalidateDCache(void)
	.global	 	MMU_InvalidateDCache
MMU_InvalidateDCache:
    mcr p15,0,r0,c7,c6,0
    MOV_PC_LR

@void MMU_InvalidateDCacheMVA(U32 mva)
	.global 	MMU_InvalidateDCacheMVA
MMU_InvalidateDCacheMVA:
    @r0=mva
    mcr p15,0,r0,c7,c6,1
    MOV_PC_LR

@void MMU_CleanDCacheMVA(U32 mva)
	.global 	MMU_CleanDCacheMVA
MMU_CleanDCacheMVA:
    @r0=mva
    mcr p15,0,r0,c7,c10,1
    MOV_PC_LR

@void MMU_CleanInvalidateDCacheMVA(U32 mva)
	.global 	MMU_CleanInvalidateDCacheMVA
MMU_CleanInvalidateDCacheMVA:
    @r0=mva
    mcr p15,0,r0,c7,c14,1
    MOV_PC_LR

@void MMU_CleanDCacheIndex(U32 index)
	.global 	MMU_CleanDCacheIndex
MMU_CleanDCacheIndex:
    @r0=index 
    mcr p15,0,r0,c7,c10,2
    MOV_PC_LR

@void MMU_CleanInvalidateDCacheIndex(U32 index)    
	.global 	MMU_CleanInvalidateDCacheIndex
MMU_CleanInvalidateDCacheIndex:    
    @r0=index
    mcr p15,0,r0,c7,c14,2
    MOV_PC_LR

@void MMU_DrainWriteBuffer(void)
	.global 	MMU_DrainWriteBuffer 
MMU_DrainWriteBuffer:	 
	mcr p15,0,r0,c7,c10,4
	MOV_PC_LR


@void MMU_WaitForInterrupt(void)
	.global 	MMU_WaitForInterrupt 
MMU_WaitForInterrupt:    
    mcr p15,0,r0,c7,c0,4
    MOV_PC_LR

@===============
@ TLB functions
@===============
@voic MMU_InvalidateTLB(void)
	.global 	MMU_InvalidateTLB
MMU_InvalidateTLB:    
    mcr p15,0,r0,c8,c7,0
    MOV_PC_LR

@void MMU_InvalidateITLB(void)
	.global 	MMU_InvalidateITLB
MMU_InvalidateITLB:    
    mcr p15,0,r0,c8,c5,0
    MOV_PC_LR

@void MMU_InvalidateITLBMVA(U32 mva)
    .global 	MMU_InvalidateITLBMVA
MMU_InvalidateITLBMVA:
    @ro=mva
    mcr p15,0,r0,c8,c5,1
    MOV_PC_LR

@void MMU_InvalidateDTLB(void)
	.global 	MMU_InvalidateDTLB
MMU_InvalidateDTLB:
    mcr p15,0,r0,c8,c6,0
    MOV_PC_LR

@void MMU_InvalidateDTLBMVA(U32 mva)
    .global  	MMU_InvalidateDTLBMVA 
MMU_InvalidateDTLBMVA:
    @r0=mva
    mcr p15,0,r0,c8,c6,1
    MOV_PC_LR

@=================
@ Cache lock down
@=================
@void MMU_SetDCacheLockdownBase(U32 base)
    .global 	MMU_SetDCacheLockdownBase 
MMU_SetDCacheLockdownBase:
    @r0= victim & lockdown base
    mcr p15,0,r0,c9,c0,0
    MOV_PC_LR
    
@void MMU_SetICacheLockdownBase(U32 base)
    .global	 	MMU_SetICacheLockdownBase
MMU_SetICacheLockdownBase:
    @r0= victim & lockdown base
    mcr p15,0,r0,c9,c0,1
    MOV_PC_LR

@=================
@ TLB lock down
@=================
@void MMU_SetDTLBLockdown(U32 baseVictim)
    .global 	MMU_SetDTLBLockdown
MMU_SetDTLBLockdown:
    @r0= baseVictim
    mcr p15,0,r0,c10,c0,0
    MOV_PC_LR
    
@void MMU_SetITLBLockdown(U32 baseVictim)
    .global 	MMU_SetITLBLockdown
MMU_SetITLBLockdown:
    @r0= baseVictim
    mcr p15,0,r0,c10,c0,1
    MOV_PC_LR

@============
@ Process ID
@============
@void MMU_SetProcessId(U32 pid)
    .global 	MMU_SetProcessId
MMU_SetProcessId:
    @r0= pid
    mcr p15,0,r0,c13,c0,0
    MOV_PC_LR

@
@*****************************************************************************
@
	.end
