/*
*********************************************************************************************************
*                                               uC/OS-II
*                                        The Real-Time Kernel
*
*                         (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                          All Rights Reserved
*
* File         : OS_CPU.H
* By           : HanRunyu
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                               ARM Port
*
*                 Target           : ARM (Includes ARM7, ARM9)
*                 Ported by        : HanRunyu
*                 URL              : http://github.com/HanRunyu
*********************************************************************************************************
*/

#ifndef __OS_CPU_H__
#define __OS_CPU_H__


#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */
typedef unsigned long  OS_STK;                   /* Each stack entry is 16-bit wide                    */
typedef unsigned long  OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) */

#define BYTE           INT8S                     /* Define data types for backward compatibility ...   */
#define UBYTE          INT8U                     /* ... to uC/OS V1.xx.  Not actually needed for ...   */
#define WORD           INT16S                    /* ... uC/OS-II.                                      */
#define UWORD          INT16U
#define LONG           INT32S
#define ULONG          INT32U


#define  OS_CRITICAL_METHOD    3

#if      OS_CRITICAL_METHOD == 2
#define  OS_ENTER_CRITICAL() IRQFIQDE                     /* Disable interrupts                        */
/* Note: R0 register need not be saved, for it gets saved outside. Refer SDT userguide 6-5 */
#define IRQFIQDE __asm                       \
{                                            \
        mrs r0,cpsr;                         \
        stmfd sp!,{r0};                      \
        orr r0,r0,#NOINT;                    \
        msr cpsr_c,r0;                       \
}

#define  OS_EXIT_CRITICAL() IRQFIQRE                      /* Restore  interrupts                       */
#define IRQFIQRE __asm                       \
{                                            \
        ldmfd sp!,{r0};                      \
        msr cpsr_c,r0;                       \
}
#endif

#if      OS_CRITICAL_METHOD == 3
#define  OS_ENTER_CRITICAL()  (cpu_sr = OSCPUSaveSR())    /* Disable interrupts                        */
#define  OS_EXIT_CRITICAL()   (OSCPURestoreSR(cpu_sr))    /* Restore  interrupts                       */
#endif

/*
*********************************************************************************************************
*                           ARM Miscellaneous
*********************************************************************************************************
*/

#define  OS_STK_GROWTH        1                       /* Stack grows from HIGH to LOW memory on 80x86  */

#define  OS_TASK_SW()         OSCtxSw()

/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

void OSStartHighRdy(void);
void OSCtxSw(void);
void OSIntCtxSw(void);
void UCOS_IRQHandler(void);


#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
OS_CPU_SR  OSCPUSaveSR(void);
void       OSCPURestoreSR(OS_CPU_SR cpu_sr);
#endif

#endif /*__OS_CPU_H__*/
