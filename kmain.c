#include"screen.h"
#include"util.h"
#include"interrupt.h"
#include"gdt.h"
void main()
{
    clearScreen();
    gdtInit();
    idtInit();
    asm volatile("sti");
    // printBin(101734532,4);
    int k = 3 / 0;
    // printString("asfsfsfsfsfcad\n");
}