/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : APP_MAIN3.c                                             *
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
#include "printf.h"
#include "os_cpu.h"

/* ********************************************************************* */
/* Global definitions */


/* ********************************************************************* */
/* File local definitions */
#define  TASK_STK_SIZE 		1024                /* Size of each task's stacks (# of WORDs) */
#define  NO_TASKS              5                /* Number of identical tasks */


OS_STK   TaskStk[NO_TASKS][TASK_STK_SIZE];      /* Tasks stacks */
OS_STK   TaskStartStk[TASK_STK_SIZE];
S8     	 TaskData[NO_TASKS];                    /* Parameters to pass to each task */

OS_EVENT *AckMbox;
OS_EVENT *TxMbox;

/* ********************************************************************* */
/* Local functions */

void Task1(void *p_arg)
{
	U8 err;
	OS_STK_DATA data;
	U8 i;
	p_arg = p_arg;

	for(;;)
	{
		for(i = 0; i < 6; i++)
		{
			err = OSTaskStkChk(10+i, &data);
			if(err == OS_ERR_NONE)
			{
				printf("#%d\t\t%lu\t%lu\t%lu\n", 
					   i, data.OSFree + data.OSUsed, data.OSFree, data.OSUsed);
			}	
		}
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}

void Task2(void *p_arg)
{
	p_arg = p_arg;

	for(;;)
	{
		OSTimeDlyHMSM(0, 0, 0, 10);
	}
}

void Task3(void *p_arg)
{
	S8 s[500];
	U16 i;
	
	p_arg = p_arg;
	s[0]='1';
	for(i = 1; i < 499; i++)
	{
		s[i]=s[i-1]+1;
	}

	for(;;)
	{
		OSTimeDlyHMSM(0, 0, 0, 20);
	}
}

void Task4(void *p_arg)
{
	U8 err;
	S8 txmsg='A';
	
	p_arg = p_arg;

	for(;;)
	{
		OSMboxPost(TxMbox, &txmsg);
		OSMboxPend(AckMbox,0,&err);
		if(err == OS_ERR_NONE)
		{
			if(++txmsg == ('Z'+1))
				txmsg = 'A';
		}
		else
		{
			printf("ERROR!\n");
			err = OS_ERR_NONE;
		}
	}
}

void Task5(void *p_arg)
{
	U8 err;
	S8 *rxmsg;
	
	p_arg = p_arg;

	for(;;)
	{
		rxmsg = OSMboxPend(TxMbox,0,&err);

		if(err == OS_ERR_NONE)
		{
			printf("%c",*rxmsg);
		}
		else
		{
			printf("ERROR!\n");
			err = OS_ERR_NONE;
		}
		OSTimeDlyHMSM(0, 0, 0, 500);
		OSMboxPost(AckMbox, (void *)1);
	}
}


void TaskStartCreateTasks(void)
{
	U8 i;

    for (i = 0; i < NO_TASKS; i++)
    {                                       /* Create NO_TASKS identical tasks */
		TaskData[i] = '0' + i;              /* Each task will display its own letter */
    }
	OSTaskCreateExt(Task1,
					 (void *  )&TaskData[0], 
					 (OS_STK *)&TaskStk[0][TASK_STK_SIZE - 1],
					 (INT8U   )11, 
					 (INT16U  )11, 
					 (OS_STK *)&TaskStk[0][0], 
					 (INT32U  )TASK_STK_SIZE, 
					 (void *  )0, 
					 (INT16U  )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	OSTaskCreateExt(Task2,
					 (void *  )&TaskData[1], 
					 (OS_STK *)&TaskStk[1][TASK_STK_SIZE - 1],
					 (INT8U   )12, 
					 (INT16U  )12, 
					 (OS_STK *)&TaskStk[1][0], 
					 (INT32U  )TASK_STK_SIZE, 
					 (void *  )0, 
					 (INT16U  )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	OSTaskCreateExt(Task3,
					 (void *  )&TaskData[2], 
					 (OS_STK *)&TaskStk[2][TASK_STK_SIZE - 1],
					 (INT8U   )13, 
					 (INT16U  )13, 
					 (OS_STK *)&TaskStk[2][0], 
					 (INT32U  )TASK_STK_SIZE, 
					 (void *  )0, 
					 (INT16U  )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	OSTaskCreateExt(Task4,
					 (void *  )&TaskData[3], 
					 (OS_STK *)&TaskStk[3][TASK_STK_SIZE - 1],
					 (INT8U   )14, 
					 (INT16U  )14, 
					 (OS_STK *)&TaskStk[3][0], 
					 (INT32U  )TASK_STK_SIZE, 
					 (void *  )0, 
					 (INT16U  )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	OSTaskCreateExt(Task5,
					 (void *  )&TaskData[4], 
					 (OS_STK *)&TaskStk[4][TASK_STK_SIZE - 1],
					 (INT8U   )15, 
					 (INT16U  )15, 
					 (OS_STK *)&TaskStk[4][0], 
					 (INT32U  )TASK_STK_SIZE, 
					 (void *  )0, 
					 (INT16U  )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
}

void TaskStart(void *data)
{
    S8 key;

    data = data;                            /* Prevent compiler warning */

    printf("uC/OS-II, The Real-Time Kernel ARM Ported version\n");
    printf("EXAMPLE #3\n");

    OSStatInit();                           /* Initialize uC/OS-II's statistics */

	AckMbox = OSMboxCreate((void *)0);
	TxMbox = OSMboxCreate((void *)0);

	TaskStartCreateTasks();

    printf("\n# Parameter1: No. Tasks\n");
    printf("# Parameter2: CPU Usage in %%\n");
    printf("# Parameter3: No. Task switches/sec\n");
    printf("<-PRESS 'ESC' TO QUIT->\n");
    while(1)
    {
		printf(" %u", OSTaskCtr);      /* Display #tasks running */
        printf(" %u", OSCPUUsage);     /* Display CPU usage in % */
        printf(" %lu\n", OSCtxSwCtr);   /* Display #context switches per second */
        OSCtxSwCtr = 0;

        if(CONSOL_GetChar(&key) == True)
        {                               /* See if key has been pressed */         
			if(key == 0x1B)         	/* Yes, see if it's the ESCAPE key */
				while(1);       		/* Stay here for ever */
        }

        OSTimeDlyHMSM(0, 0, 1, 0);      /* Wait one second */
    }
}


/* ********************************************************************* */
/* Global functions */

void APP_vMain(void)
{
    OSInit();                               /* Initialize uC/OS-II                                      */
	OSTaskCreateExt(TaskStart,
                     (void   *)0,
                     (OS_STK *)&TaskStartStk[TASK_STK_SIZE - 1U],
                     (INT8U   )10,
                     (INT16U  )10,
                     (OS_STK *)&TaskStartStk[0],
                     (INT32U  )TASK_STK_SIZE,
                     (void   *)0,
                     (INT16U  )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    FRMWRK_vStartTicker(OS_TICKS_PER_SEC);  /* os_cfg_r.h */
    OSStart();                              /* Start multitasking                                       */
}


/* ********************************************************************* */

