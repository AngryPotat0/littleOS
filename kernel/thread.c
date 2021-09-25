#include"../include/type.h"
#include"../include/thread.h"
#include"../include/pmm.h"
#include"../include/asm.h"
#include"../include/printf.h"

#define TIME_CONT 2
TCB *curThread;
TCB mainThread;

static int threadID = 1;

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

void threadCreate(uint32_t *id,threadFunction func,void *args,uint32_t pageAddr,uint32_t pageCounte)
{
    cli();
    *id = (threadID++);
    TCB *tcb = (TCB*)(pageAddr);
    tcb->kernelStackTop = pageAddr + pageCounte * 4096;
    // printf("int threadCreate:%x\n",tcb->kernelStackTop);
    tcb->status = TASK_RUNNING;
    tcb->timeCounter = 0;
    tcb->timeLeft = TIME_CONT;
    tcb->tid = id;
    tcb->pageAddr = pageAddr;
    tcb->pageCounte = pageCounte;
    *(--tcb->kernelStackTop) = args;
    // printf("int threadCreate:%x\n",tcb->kernelStackTop);
    *(--tcb->kernelStackTop) = exit;
    // printf("int threadCreate:%x\n",tcb->kernelStackTop);
    *(--tcb->kernelStackTop) = func;
    // printf("int threadCreate:%x\n",tcb->kernelStackTop);
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
        printf("ERROR:main thread can't use exit()\n");
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

void mutexInit(int *m)
{
    *m = 0;
}

int testAndSet(int * src,int value)
{
    __asm__("xchg %0, %1" : "+q" (value), "+m" (*src));
    return value;
}

void spinlock(int *m)
{
    // while (testAndSet(m,1) == 1);
    while(!__sync_bool_compare_and_swap(m, 0, 1));
}

void spinUnlock(int volatile *m)
{
    // m->flags = 0;
    __asm__ __volatile__("":::"memory"); // acts as a memory barrier.
    *m = 0;
}