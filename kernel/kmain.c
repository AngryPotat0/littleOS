#include"../include/screen.h"
#include"../include/memory.h"
#include"../include/interrupt.h"
#include"../include/gdt.h"
#include"../include/asm.h"
#include"../include/keyboard.h"
#include"../include/timer.h"
#include"../include/vmm.h"
#include"../include/pmm.h"

void init()
{
    clearScreen();
    gdtInit();
    idtInit();
    pmmInit();
    timerInit(1000);
    keyboardInit();
    vmmInit();
}

void main()//TODO:
{
    init();
    sti();
    printString("LittleOS:\n>");

    // int k = 3 / 0;
    // printString("asfsfsfsfsfcad\n");
}