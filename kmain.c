#include"screen.h"
#include"util.h"
#include"interrupt.h"
#include"gdt.h"
#include"asm.h"
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