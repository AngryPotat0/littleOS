#include"../include/screen.h"
#include"../include/util.h"
#include"../include/interrupt.h"
#include"../include/gdt.h"
#include"../include/asm.h"
#include"../include/keyboard.h"
#include"../include/timer.h"

void init()
{
    clearScreen();
    gdtInit();
    idtInit();
    timerInit(1000);
    keyboardInit();
}

void main()
{
    init();
    sti();
    printString("LittleOS:\n>");
    // int k = 3 / 0;
    // printString("asfsfsfsfsfcad\n");
}