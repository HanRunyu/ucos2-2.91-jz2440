/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : APP_MAIN.c                                              *
*                                                                         *
*   AUTHOR      : HanRunyu                                                *
*                 URL  : http://github.com/HanRunyu                       *
*                                                                         *
*   PROCESSOR   : s3c2440  (32 bit ARM920T RISC core from Samsung)        *
*                                                                         *
*   TOOLCHAIN   : ANY								                      *
*                                                                         *
*   DESCRIPTION :                                                         *
*   This is a sample code to test UCOS-II.                                *
*                                                                         *
**************************************************************************/



#include "includes.h"
#include "consol.h"
#include "os_cpu.h"

/* ********************************************************************* */
/* Global definitions */


/* ********************************************************************* */
/* File local definitions */

#define  TASK_STK_SIZE 		1024                /* Size of each task's stacks (# of WORDs) */
#define  NO_TASKS              2                /* Number of identical tasks */

OS_STK   TaskStk[NO_TASKS][TASK_STK_SIZE];      /* Tasks stacks */

/* ********************************************************************* */
/* Local functions */

void  App_TaskPing (void *data)
{
    data=data;
    while (1)
    {
        if(TEST_BIT_SET(rGPFDAT,0x10))
			BIT_CLR(rGPFDAT,0x10);
		else
			BIT_SET(rGPFDAT,0x10);
        OSTimeDlyHMSM(0, 0, 0, 500);   // test   before is 300
    }
}
void  App_TaskPong (void *data)
{
    data=data;
    while (1)
    {
        if(TEST_BIT_SET(rGPFDAT,0x20))
			BIT_CLR(rGPFDAT,0x20);
		else
			BIT_SET(rGPFDAT,0x20);
        OSTimeDlyHMSM(0, 0, 0, 1000);   // test   before is 300
    }
}

/* ********************************************************************* */
/* Global functions */

void APP_vMain (void)
{
    OSInit();                               /* Initialize uC/OS-II                                      */
	OSTaskCreateExt(App_TaskPing,
                    (void   *)0,
                    (OS_STK *)&TaskStk[0][TASK_STK_SIZE - 1U],
                    (INT8U   )3,
                    (INT16U  )3,
                    (OS_STK *)&TaskStk[0][0],
                    (INT32U  )TASK_STK_SIZE,
                    (void   *)0,
                    (INT16U  )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    OSTaskCreateExt(App_TaskPong,
                    (void   *)0,
                    (OS_STK *)&TaskStk[1][TASK_STK_SIZE - 1u],
                    (INT8U   )4,
                    (INT16U  )4,
                    (OS_STK *)&TaskStk[1][0],
                    (INT32U  )TASK_STK_SIZE,
                    (void   *)0,
                    (INT16U  )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    FRMWRK_vStartTicker(OS_TICKS_PER_SEC);  /* os_cfg_r.h */
    OSStart();                              /* Start multitasking                                       */
}


/* ********************************************************************* */
