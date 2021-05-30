#include"../include/screen.h"
#include"../include/memory.h"
#include"../include/interrupt.h"
#include"../include/gdt.h"
#include"../include/asm.h"
#include"../include/keyboard.h"
#include"../include/timer.h"
#include"../include/vmm.h"
#include"../include/pmm.h"
#include"../include/thread.h"

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

int at = 0;

void *func(void *args)
{
    for(int i = 0;i < 1000;i++)
    {
        cli();
        printString("a");
        sti();
    }
}

void main()//TODO:
{
    init();
    sti();
    printString("LittleOS:\n>");
    threadCreate(1,func,NULL,pmmAlloc(),1);
    for(int i = 0;i < 1000;i++)
    {
        cli();
        printString("b");
        sti();
    }
    int k = 3 / 0;
    printString("asfsfsfsfsfcad\n");
}