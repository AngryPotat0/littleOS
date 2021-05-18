#include"../include/string.h"
#include"../include/util.h"
#include"../include/screen.h"
#include"../include/asm.h"

void userInput(char* inputBuffer)
{
    if(strcmp(inputBuffer,"END") == 0)
    {
        hlt();
    }
    printString("You said:");
    printString(inputBuffer);
    printString("\n>");
}