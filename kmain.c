#include"screen.h"
#include"util.h"
void main()
{
    // char* video = (char*)0xb8000;
    // *video = 'X';
    // *(video + 2) = 'H';
    // printChar('G',-1,-1,0);
    clearScreen();
    char line[] = "Hello\nWorld";
    // for(int i = 0;line[i] != '\0';i++){
    //     printChar(line[i],-1,-1,0);
    // }
    printString(line);
    // printString("\nThat is");
}
