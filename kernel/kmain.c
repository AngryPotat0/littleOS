#include"../include/screen.h"
#include"../include/util.h"
#include"../include/interrupt.h"
#include"../include/gdt.h"
#include"../include/asm.h"
void main()
{
    clearScreen();
    gdtInit();
    idtInit();
    sti();
    printString("Hello");
    int k = 3 / 0;
    // printString("asfsfsfsfsfcad\n");
}