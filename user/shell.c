#include"../include/string.h"
#include"../include/memory.h"
#include"../include/printf.h"
#include"../include/asm.h"

void userInput(char* inputBuffer)
{
    if(strcmp(inputBuffer,"END") == 0)
    {
        hlt();
    }
    printf("You said:%s\n>",inputBuffer);
}