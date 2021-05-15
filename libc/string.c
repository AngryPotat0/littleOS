#include"../include/string.h"

int strlen(char* str)
{
    int ret = 0;
    for(;*str != '\0';str++,++ret);
    return ret;
}

void reverse(char str[])
{
    char c;
    for(int i = 0,j = strlen(str) - 1;i < j;i += 1,j -= 1)
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

void intToStr(int n,char list[])
{
    int k = 0,sign;
    if(sign = n < 0)n = -n;
    while (n != 0)
    {
        list[k++] = n % 10 + '0';
        n /= 10;
    }
    if(sign < 0)
        list[k++] = '-';
    list[k] = '\0';
    reverse(list);   
}

int strcmp(char* str1,char* str2)
{
    int i;
    for(i = 0;str1[i] == str2[i];i++)
    {
        if(str1[i] == '\0') return 0;
    }
    return str1[i] - str2[i];
}