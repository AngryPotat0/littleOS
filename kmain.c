#include"screen.h"
#include"util.h"
#include"interrupt.h"
#include"gdt.h"
void main()
{
    gdtInit();
    clearScreen();
    idtInit();//can't work now
    asm volatile("sti");
    printBin(101734532,4);
    while(1);
}