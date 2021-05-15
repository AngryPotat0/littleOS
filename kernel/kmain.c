#include"../include/screen.h"
#include"../include/util.h"
#include"../include/interrupt.h"
#include"../include/gdt.h"
#include"../include/asm.h"

void init()
{
    clearScreen();
    gdtInit();
    idtInit();
    sti();
}

void main()
{
    init();
    printString("Hello");
    int k = 3 / 0;
    // printString("asfsfsfsfsfcad\n");
}