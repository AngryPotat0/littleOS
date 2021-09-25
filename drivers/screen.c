#include"../include/screen.h"
#include"../include/port.h"
#include"../include/memory.h"
#include"../include/type.h"
#include"../include/string.h"

int getCursorOffset();
void setCursorOffset(int offset);
void printChar(char c, int col, int row, char attr);
int getOffset(int col, int row);
int getOffsetRow(int offset);
int getOffsetCol(int offset);
int screenScrolling(int curOffset);
void printBackspace();

static int stop = 0;

void STOPROLL()
{
    stop = 1;
}

void printBackspace()
{
    unsigned char* screen = (unsigned char*)VIDEO_ADDRESS;
    int offset = getCursorOffset();
    offset -= 2;
    screen[offset] = ' ';
    screen[offset + 1] = WHITE_ON_BLACK;
    setCursorOffset(offset);
}

void putChar(char c)
{
    printChar(c,-1,-1,0);
}

void printChar(char character, int col, int row, char attr)
{
    if(stop)
        return;
    unsigned char* screen = (unsigned char*)VIDEO_ADDRESS;
    if(!attr)attr = WHITE_ON_BLACK;
    if(col >= MAX_COLS || row >= MAX_ROWS){
        int errPos = MAX_COLS * MAX_ROWS * 2;
        screen[errPos - 2] = 'E';
        screen[errPos - 1] = RED_ON_WHITE;
        return;
    }

    int offset;
    if(col < 0 && row < 0){
        offset = getCursorOffset();
    }
    else{
        offset = getOffset(col,row);
    }

    if(character == '\n'){
        row = getOffsetRow(offset);
        offset = getOffset(0,row + 1);
    }
    else{
        screen[offset] = character;
        screen[offset + 1] = attr;
        offset += 2;
    }

    if(offset >= MAX_COLS * MAX_ROWS * 2){
        offset = screenScrolling(offset);
    }

    setCursorOffset(offset);
}

void clearScreen()
{
    int screenSize = MAX_COLS * MAX_ROWS;
    unsigned char* mem = (unsigned char*)VIDEO_ADDRESS;
    for(int i = 0;i < screenSize;i++){
        mem[i * 2] = ' ';
        mem[i * 2 + 1] = WHITE_ON_BLACK;
    }
    setCursorOffset(getOffset(0,0));
}

int screenScrolling(int curOffset)
{
    memoryCopy(
        (char*)(VIDEO_ADDRESS + getOffset(0,1)),
        (char*)(VIDEO_ADDRESS),
        MAX_COLS * (MAX_ROWS - 1) * 2
    );
    char *pos = (char*)(getOffset(0,MAX_ROWS - 1) + VIDEO_ADDRESS);
    for(int i = 0;i < MAX_COLS;i++){
        pos[i * 2] = ' ';
        pos[i * 2 + 1] = WHITE_ON_BLACK;
    }
    curOffset -= MAX_COLS * 2;
    return curOffset;
}

int getOffset(int col, int row)
{
    return (row * MAX_COLS + col) * 2;
}

int getOffsetRow(int offset)
{
    return offset / (2 * MAX_COLS);
}

int getOffsetCol(int offset)
{
    return (offset - getOffsetRow(offset) * 2 * MAX_COLS) / 2;
}

int getCursorOffset()
{
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void setCursorOffset(int offset)
{
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}