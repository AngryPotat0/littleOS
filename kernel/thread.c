#include"../include/type.h"
#include"../include/thread.h"
#include"../include/pmm.h"
#include"../include/asm.h"
#include"../include/screen.h"

#define TIME_CONT 2
TCB *curThread;
TCB mainThread;

void threadInit()
{
    curThread = &mainThread;
    curThread->kernelStackTop = 0;
    curThread->status = TASK_RUNNING;
    curThread->timeCounter = 0;
    curThread->timeLeft = 0;
    curThread->next = curThread;
    curThread->pageCounte = 0;
    curThread->pageAddr = 0;
}

void threadCreate(uint32_t id,threadFunction func,void *args,uint32_t pageAddr,uint32_t pageCounte)
{
    cli();
    TCB *tcb = (TCB*)(pageAddr);
    tcb->kernelStackTop = pageAddr + pageCounte * 4096;
    tcb->status = TASK_RUNNING;
    tcb->timeCounter = 0;
    tcb->timeLeft = TIME_CONT;
    tcb->tid = id;
    tcb->pageAddr = pageAddr;
    tcb->pageCounte = pageCounte;
    *(--tcb->kernelStackTop) = args;
    *(--tcb->kernelStackTop) = exit;
    *(--tcb->kernelStackTop) = func;
    tcb->context.esp = tcb->kernelStackTop;
    tcb->context.eflags = 0x200;
    tcb->next = curThread->next;
    curThread->next = tcb;
    sti();
}

void schdule()
{
    if(curThread->next == curThread)
    {
        return;
    }
    TCB *cur = curThread,*next = curThread->next;
    next->timeLeft = TIME_CONT;
    curThread = next;
    getEsp();
    switchTo((void*)(&(cur->context)),(void*)(&(next->context)));
}

void threadRemove()
{
    cli();
    if(curThread->tid == 0)
    {
        printString("ERROR:main thread can't use exit()\n");
        return;
    }
    TCB * thread = curThread;
    for(;thread->next != curThread;thread = thread->next);
    thread->next = curThread->next;
}

void exit()
{
    threadRemove();
    TCB *cur = curThread;
    TCB *next = cur->next;
    next->timeLeft = TIME_CONT;
    switchTo((void*)(&(cur->context)),(void*)(&(next->context)));
    pmmFree(cur->pageAddr);
}

#undef TIME_CONT