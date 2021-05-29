#ifndef THREAD__
#define THREAD__

#include"../include/type.h"

typedef enum taskStatus{
    TASK_RUNNING,
    TASK_READY,
    TASK_BLOCKED,
    TASK_WAITING,
    TASK_HANGING,
    TASK_DIDE
}taskStatus;

typedef struct threadContext{
    uint32_t ebp;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t eflags;
    uint32_t esp;
}__attribute__((packed)) threadContext;

typedef struct TCB{
    uint32_t *kernelStackTop;
    taskStatus status;
    uint32_t timeCounter;
    uint32_t timeLeft;
    struct TCB *next;
    uint32_t tid;
    uint32_t pageCounte;
    uint32_t pageAddr;
    threadContext context;
}TCB;

typedef void *threadFunction(void *args);

extern void switchTo(void *curContext, void *nextContext);
extern uint32_t getEsp();

#endif