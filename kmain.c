#include"screen.h"
#include"util.h"
void main()
{
    gdtInit();
    clearScreen();
    char line[] = "asdjoulfo fahwsifhrwifsdj hwaxaxasaxha  agha k hkshfh faeshob";
    printString(line);
    char* str = "egrsdfsdj owidju hoeh awif i fahwaxaxasaxha k hkshfh fasaho\n";
    printString(str);
    printString("\nSTK");
}