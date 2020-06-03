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


/* ********************************************************************* */
/* Global definitions */


/* ********************************************************************* */
/* File local definitions */

#define  TASK_STK_SIZE     256                  /* Size of each task's stacks (# of WORDs) */
#define  NO_TASKS           10                  /* Number of identical tasks */

OS_STK   TaskStk[NO_TASKS][TASK_STK_SIZE];      /* Tasks stacks */
OS_STK   TaskStartStk[TASK_STK_SIZE];
S8     	 TaskData[NO_TASKS];                    /* Parameters to pass to each task */
OS_EVENT *RandomSem;


/* ********************************************************************* */
/* Local functions */

void Task (void *data)
{
        U8 err;

        while(1)
        {
                OSSemPend(RandomSem, 0, &err);  /* Acquire semaphore to perform random numbers */
                OSSemPost(RandomSem);           /* Release semaphore */
                CONSOL_SendChar(*(S8 *)data); /* Display the task number on the screen */
                OSTimeDly(5);                   /* Delay 5 clock tick */
        }
}

void TaskStart (void *data)
{
        U8 i;
        S8 key;

        data = data;                            /* Prevent compiler warning */

        CONSOL_Printf("uC/OS-II, The Real-Time Kernel ARM Ported version\n");
        CONSOL_Printf("EXAMPLE #1\n");

        CONSOL_Printf("Determining  CPU's capacity ...\n");

//        FRMWRK_vStartTicker(OS_TICKS_PER_SEC);  /* The Tick timer is started much earlier */

        OSStatInit();                           /* Initialize uC/OS-II's statistics */

        for (i = 0; i < NO_TASKS; i++)
        {                                       /* Create NO_TASKS identical tasks */
                TaskData[i] = '0' + i;          /* Each task will display its own letter */
                CONSOL_Printf("#%d",i);
                OSTaskCreate(Task, (void *)&TaskData[i], (void *)&TaskStk[i][TASK_STK_SIZE - 1], i + 1);
        }

        CONSOL_Printf("\n# Parameter1: No. Tasks\n");
        CONSOL_Printf("# Parameter2: CPU Usage in %%\n");
        CONSOL_Printf("# Parameter3: No. Task switches/sec\n");
        CONSOL_Printf("<-PRESS 'ESC' TO QUIT->\n");
        while(1)
        {
                CONSOL_Printf(" %d", OSTaskCtr);    /* Display #tasks running */
                CONSOL_Printf(" %d", OSCPUUsage);   /* Display CPU usage in % */
                CONSOL_Printf(" %d\n", OSCtxSwCtr); /* Display #context switches per second */
                OSCtxSwCtr = 0;
            
                if(CONSOL_GetChar(&key) == True)
                {                               /* See if key has been pressed */         
                        if(key == 0x1B)         /* Yes, see if it's the ESCAPE key */
                                while(1);       /* Stay here for ever */
                }

                OSTimeDlyHMSM(0, 0, 1, 0);      /* Wait one second */
        }
}


/* ********************************************************************* */
/* Global functions */

void APP_vMain (void)
{
        OSInit();                               /* Initialize uC/OS-II                                      */
        RandomSem = OSSemCreate(1);             /* Random number semaphore                              */
        OSTaskCreate(TaskStart, (void *)0, (void *)&TaskStartStk[TASK_STK_SIZE - 1], 0);
        FRMWRK_vStartTicker(OS_TICKS_PER_SEC);  /* os_cfg_r.h */
        OSStart();                              /* Start multitasking                                       */
}


/* ********************************************************************* */
