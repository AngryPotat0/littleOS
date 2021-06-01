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

void main()//TODO:
{
    int k = 0;
    init();
    sti();
    printString("LittleOS:\n>");
    // __asm__ __volatile__ ("xchg %bx, %bx");
    for(int i = 0;i < 100000;i++)
    {
        at += 1;
    }
    printInt(at);
    printString("\n");
    printInt(k);
}