#include<stdio.h>
void printInt(int num)
{
    int k = 0;
    while(num != 0)
    {
        k = k * 10 + num % 10;
        num = num / 10;
    }
    char c;
    while (k != 0)
    {
        c = k % 10 + '0';
        k = k / 10;
        printf("%c",c);
    }
    printf("\n");
    
}
int main()
{
    printInt(123);
    return 0;
}