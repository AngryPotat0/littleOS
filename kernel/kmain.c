#include"../include/printf.h"
#include"../include/memory.h"
#include"../include/interrupt.h"
#include"../include/gdt.h"
#include"../include/asm.h"
#include"../include/keyboard.h"
#include"../include/timer.h"
#include"../include/vmm.h"
#include"../include/pmm.h"
#include"../include/thread.h"

int at = 0;
// mutex t;
int t;

void init()
{
    clearScreen();
    gdtInit();
    idtInit();
    pmmInit();
    timerInit(1000);
    keyboardInit();
    // vmmInit();
    threadInit();
}

void *func(void *args)
{
    // cli();
    // spinlock(&t);
    // printf("running\n");
    // for(int i = 0;i < 1000000;i++)
    //     at++;
    // spinUnlock(&t);
    printf("in func\n");
}

void *fun1(void *args)
{
    // cli();
    // spinlock(&t);
    // // printf("running\n");
    // for(int i = 0;i < 500000;i++)
    //     at++;
    // spinUnlock(&t);
    printf("in fun1\n");
}

void main()//TODO:
{
    init();
    sti();
    printf("LittleOS:\n>");
    mutexInit(&t);
    uint32_t id;
    uint32_t id2;
    threadCreate(&id,func,NULL,pmmAlloc(),1);
    threadCreate(&id2,fun1,NULL,pmmAlloc(),1);
    printf("main\n");
    // int a = pmmAlloc();
    // int b = pmmAlloc();

    // printf("%x,%x\n",a);
    
    // spinlock(&t);
    // for(int i = 0;i < 1000000;i++)
    //     at++;
    // spinUnlock(&t);

    // for(int i = 0;i < 10000000;i++);
        // at++;
    // at = s100;
    // sti();
    // printf("print at\n");
    printf("main2\n");
    printf("at=%d\n",at);
}