@ ********************************************************************************************************
@                                               uC/OS-II
@                                         The Real-Time Kernel
@
@                          (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
@                                          All Rights Reserved
@
@ File : OS_CPU_A.ASM
@ By   : HanRunyu
@ ********************************************************************************************************



@ ********************************************************************************************************
@                                               ARM Port
@
@                 Target           : ARM (Includes ARM7, ARM9)
@				  Ported by 	   : HanRunyu
@				  URL			   : http://github.com/HanRunyu
@
@ ********************************************************************************************************

	.text

@ ********************************************************************************************************
@                                          START MULTITASKING
@                                       void OSStartHighRdy(void)
@
@ Note : OSStartHighRdy() MUST:
@           a) Call OSTaskSwHook() then,
@           b) Set OSRunning to TRUE,
@           c) Switch to the highest priority task.
@ ********************************************************************************************************

	.extern  OSTaskSwHook
	.extern  OSRunning
	.extern  OSTCBHighRdy

	.global  OSStartHighRdy
OSStartHighRdy:  

	bl OSTaskSwHook             @ Call user defined task switch hook

    ldr r4,=OSRunning           @ Indicate that multitasking has started
    mov r5,#1
    strb r5,[r4]

    ldr r4,=OSTCBHighRdy        @ Get highest priority task TCB address

    ldr r4,[r4]                 @ get stack pointer
    ldr sp,[r4]                 @ switch to the new stack

    ldmfd sp!,{r4}              @ pop new task`s spsr
    msr spsr,r4
    ldmfd sp!,{r4}              @ pop new task`s psr
    msr cpsr,r4
    ldmfd sp!,{r0-r12,lr,pc}    @ pop new task`s r0-r12,lr & pc

@*********************************************************************************************************
@                                PERFORM A CONTEXT SWITCH (From task level)
@                                           void OSCtxSw(void)
@
@ Note(s):    Upon entry, 
@             OSTCBCur     points to the OS_TCB of the task to suspend
@             OSTCBHighRdy points to the OS_TCB of the task to resume
@
@*********************************************************************************************************

	.extern  OSTCBCur
	.extern  OSTaskSwHook
	.extern  OSTCBHighRdy
	.extern  OSPrioCur
	.extern  OSPrioHighRdy

	.global  OSCtxSw
OSCtxSw:

	@ OS_CTX_SAVE
    stmfd sp!,{lr}              @ push pc (lr should be pushed in place of PC)
    stmfd sp!,{r0-r12,lr}       @ push lr & register file
    mrs r4,cpsr
    stmfd sp!,{r4}              @ push current psr
    mrs r4,spsr
    stmfd sp!,{r4}              @ push current spsr

    @ OSPrioCur = OSPrioHighRdy;
    ldr r4,=OSPrioCur
    ldr r5,=OSPrioHighRdy
    ldrb r6,[r5]
    strb r6,[r4]
    
    @ OSTCBCur->OSTCBStkPtr = SP;
    ldr r4,=OSTCBCur
    ldr r5,[r4]
    str sp,[r5]                 @ store sp in preempted tasks`s TCB

    bl OSTaskSwHook             @ call Task Switch Hook

    @ SP=OSTCBHighRdy->OSTCBStkPtr;
    ldr r6,=OSTCBHighRdy
    ldr r6,[r6]
    ldr sp,[r6]                 @ get new task`s stack pointer

    @ OSTCBCur = OSTCBHighRdy
    str r6,[r4]                 @ set new current task TCB address

	@ OS_CTX_RESTORE
    ldmfd sp!,{r4}              @ pop new task`s spsr
    msr spsr,r4
    ldmfd sp!,{r4}              @ pop new task`s psr
    msr cpsr,r4
    ldmfd sp!,{r0-r12,lr,pc}    @ pop new task`s r0-r12,lr & pc



@*********************************************************************************************************
@                                PERFORM A CONTEXT SWITCH (From an ISR)
@                                        void OSIntCtxSw(void)
@
@ Note(s): This function only flags a context switch to the ISR Handler
@
@*********************************************************************************************************

	.extern  OSIntCtxSwFlag

	.global  OSIntCtxSw
OSIntCtxSw:

    @OSIntCtxSwFlag = True
    ldr r0,=OSIntCtxSwFlag
    mov r1,#1
    str r1,[r0]
    mov pc,lr
        

@*********************************************************************************************************
@                                            IRQ HANDLER
@
@        This handles all the IRQs
@        Note: FIQ Handler should be written similar to this
@
@*********************************************************************************************************

	.extern  C_IRQHandler
	.extern  OSIntEnter
	.extern  OSIntExit

	.extern  OSIntCtxSwFlag
	.extern  OSTCBCur
	.extern  OSTaskSwHook
	.extern  OSTCBHighRdy
	.extern  OSPrioCur
	.extern  OSPrioHighRdy

	@NOINT   EQU 0xc0
	.equ	NOINT,0xc0

	.global  UCOS_IRQHandler
UCOS_IRQHandler:
	/* 执行到这里之前:
	 * 1. lr_irq保存有被中断模式中的下一条即将执行的指令的地址
	 * 2. SPSR_irq保存有被中断模式的CPSR
	 * 3. CPSR中的M4-M0被设置为10010, 进入到irq模式
	 * 4. 跳到0x18的地方执行程序 
	 */

	/* 保存现场 */
	/* 在irq异常处理函数中有可能会修改r0-r12, 所以先保存 */
	/* lr-4是异常处理完后的返回地址, 也要保存 */
	stmfd sp!,{r0-r3,r12,lr} 

    bl OSIntEnter

	/* 处理irq异常 */
    bl C_IRQHandler
    
    bl OSIntExit

	/* 原本应在OSIntCtxSw中的处理现在在_IntCtxSw处理，OSIntCtxSw中仅设置标志位，
	   从而避免了因OSIntExit临界区保存CPSR至堆栈导致堆栈改变的问题 */
	ldr r0,=OSIntCtxSwFlag
	ldr r1,[r0]
	cmp r1,#1
	beq _IntCtxSw

	/* 恢复现场 */
	ldmfd sp!,{r0-r3,r12,lr}
	subs pc,lr,#4

_IntCtxSw:
	@ OSIntCtxSwFlag = 0;
    mov r1,#0
    str r1,[r0]

    ldmfd sp!,{r0-r3,r12,lr}
    stmfd sp!,{r0-r3}
    mov r1,sp					@ 中断模式下和被中断前模式不同，其SP指针也不同
    add sp,sp,#16
    sub r2,lr,#4

    mrs r3,spsr					@ 关中断
    orr r0,r3,#NOINT
    msr spsr_c,r0

    ldr r0,=.+8
    movs pc,r0					@ CPSR会被SPSR覆盖,切换至中断前的模式

    stmfd sp!,{r2}              @ push old task`s pc
    stmfd sp!,{r4-r12,lr}       @ push old task`s lr,r12-r4
    mov r4,r1                   @ Special optimised code below
    mov r5,r3
    ldmfd r4!,{r0-r3}
    stmfd sp!,{r0-r3}           @ push old task`s r3-r0
    stmfd sp!,{r5}              @ push old task`s psr
    mrs r4,spsr
    stmfd sp!,{r4}              @ push old task`s spsr
    
    @ OSPrioCur = OSPrioHighRdy
    ldr r4,=OSPrioCur
    ldr r5,=OSPrioHighRdy
    ldrb r5,[r5]
    strb r5,[r4]
    
    @ OSTCBCur->OSTCBStkPtr=SP;
    ldr r4,=OSTCBCur
    ldr r5,[r4]
    str sp,[r5]                 @ store sp in preempted tasks`s TCB

    bl OSTaskSwHook             @ call Task Switch Hook

    @ SP=OSTCBHighRdy->OSTCBStkPtr;
    ldr r6,=OSTCBHighRdy
    ldr r6,[r6]
    ldr sp,[r6]                 @ get new task`s stack pointer

    @ OSTCBCur = OSTCBHighRdy
    str r6,[r4]                 @ set new current task TCB address

	@ OS_CTX_RESTORE
    ldmfd sp!,{r4}              @ pop new task`s spsr
    msr spsr,r4
    ldmfd sp!,{r4}              @ pop new task`s psr
    msr cpsr,r4
    ldmfd sp!,{r0-r12,lr,pc}    @ pop new task`s r0-r12,lr & pc

@*********************************************************************************************************
@                                   CRITICAL SECTION METHOD 3 FUNCTIONS
@
@ Description: Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
@              would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
@              disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to 
@              disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
@              into the CPU's status register.
@
@              OS_CPU_SR OSCPUSaveSR()
@ Arguments  : none
@
@ Returns    : OS_CPU_SR
@
@              OSCPURestoreSR(OS_CPU_SR cpu_sr)
@ Arguments  : OS_CPU_SR
@
@ Returns    : none
@
@ Note(s)    : These functions are used in general like this,
@
@            void Task (void *data)
@            {
@                    #if OS_CRITICAL_METHOD == 3 /* Allocate storage for CPU status register */
@                          OS_CPU_SR  cpu_sr@
@                    #endif
@                         :
@                         :
@                    OS_ENTER_CRITICAL()@ /* cpu_sr = OSCPUSaveSR()@ */
@                         :
@                         :
@                    OS_EXIT_CRITICAL()@  /* OSCPURestoreSR(cpu_sr)@ */
@                         :
@                         :
@            }
@*********************************************************************************************************

	.global  OSCPUSaveSR
OSCPUSaveSR:
	mrs r0,cpsr
    orr r1,r0,#NOINT
    msr cpsr_c,r1
    mov pc,lr

	.global  OSCPURestoreSR
OSCPURestoreSR:
    msr cpsr_c,r0
    mov pc,lr

	.end
