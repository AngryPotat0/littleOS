#include"screen.h"
#include"util.h"
#include"idt.h"
void main()
{
    gdtInit();
    clearScreen();
    idtInit();//can't work now
    printBin(101734532,4);
}