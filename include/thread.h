#ifndef THREAD__
#define THREAD__

#include"../include/type.h"



#define LOCK_PREFIX    "lock;"  
#define __sync_bool_compare_and_swap(mem, oldval, newval) \  
  ({ __typeof (*mem) ret;                             \  
        __asm __volatile (LOCK_PREFIX "cmpxchgl %2, %1;sete %%al; movzbl %%al,%%eax"                \  
                        : "=a" (ret), "=m" (*mem)                  \  
                        : "r" (newval), "m" (*mem), "a" (oldval)\  
                        :"memory");         \  
                            ret; }) 



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

typedef struct mutex{
    int flags;   
}mutex;


typedef void *threadFunction(void *args);

extern void switchTo(void *curContext, void *nextContext);
extern uint32_t getEsp();

void threadInit();
void threadCreate(uint32_t *id,threadFunction func,void *args,uint32_t pageAddr,uint32_t pageCounte);
void schdule();
void exit();
void mutexInit(int *m);
void spinlock(int *m);
void spinUnlock(int volatile *m);

#endif