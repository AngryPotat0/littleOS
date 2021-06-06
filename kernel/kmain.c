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
    for(int i = 0;i < 10000;i++)
        at++;
    return;
}

void main()//TODO:
{
    init();
    sti();
    printf("LittleOS:\n>");
    for(int i = 0;i < 10000;i++)
        at++;
    printf("at=%d\n",at);
}