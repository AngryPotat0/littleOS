#include"../include/screen.h"
#include"../include/stdarg.h"

static char digits[] = "0123456789ABCDEF";

void printInt(int num,int base)
{
    char lis[20];
    int i = 0;
    int sign = num > 0 ? 1 : -1;
    while (num != 0)
    {
        lis[i++] = digits[num % base];
        num /= base;
    }
    if(sign < 0)
        lis[i++] = '-';
    for(i = i - 1;i > 0;i--)putChar(lis[i]);
}

void printStrings(char *str)
{
    if(str == 0)
        str = "(null)";
    for(;*str != '\0';str++)
    {
        putChar(*str);
    }
}

void printf(char *fmt, ...)
{
    va_list va;
    va_start(va,fmt);
    char c,*s;
    for(int i = 0;(c = fmt[i]) != '\0';i++)
    {
        if(c != '%')
        {
            putChar(c);
            continue;
        }
        c = fmt[++i];
        switch (c)
        {
        case 'd':
            printInt(va_arg(va,int),10);
            break;
        case 'x':
            printInt(va_arg(va,int),16);
            break;
        case 's':
            printStrings(va_arg(va,char*));
            break;
        case '%':
            putChar('%');
            break;
        default:
            putChar('%');
            putChar(c);
            break;
        }
    }
}