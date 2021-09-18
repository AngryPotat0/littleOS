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
    printf("running\n");
    for(int i = 0;i < 1000000;i++)
        at++;
}

void main()//TODO:
{
    init();
    sti();
    printf("LittleOS:\n>");
    uint32_t id;
    // threadCreate(&id,func,NULL,pmmAlloc(),1);
    // for(int i = 0;i < 100000000;i++);
        // at++;
    // at = s100;
    // sti();
    printf("at=%d\n",at);
}