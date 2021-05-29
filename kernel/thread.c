#include"../include/type.h"
#include"../include/thread.h"
#include"../include/pmm.h"

#define TIME_CONT 2
TCB *threadList;
TCB mainThread;

void threadInit()
{
    TCB * threadList = &mainThread;
    threadList->kernelStackTop = 0;
    threadList->status = TASK_RUNNING;
    threadList->timeCounter = 0;
    threadList->timeLeft = 0;
    threadList->next = threadList;
    threadList->pageCounte = 0;
    threadList->pageAddr = 0;
}

void threadCreate(uint32_t id,threadFunction func,void *args,uint32_t pageAddr,uint32_t pageCounte)
{

}