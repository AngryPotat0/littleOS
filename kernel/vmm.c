#include"../include/type.h"
#include"../include/vmm.h"

uint32_t pageDirectory[1024] __attribute__((aligned(4096)));
uint32_t firstPageTable[1024] __attribute__((aligned(4096)));
uint32_t table_768[1024] __attribute__((aligned(4096)));

extern void reMap();

inline void loadPageDirectory(uint32_t* pd)
{
    __asm__ volatile ("mov %0, %%cr3": :"r"(pd));
}

inline void vmmEnable()
{
    uint32_t cr0;
    __asm__ volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	__asm__ volatile ("mov %0, %%cr0" : : "r" (cr0));
}

void vmmInit()
{
    for(int i = 0;i < 1024;i++)
    {
        pageDirectory[i] = 0x00000002;
    }
    for(unsigned int i = 0;i < 1024;i++)
    {
        firstPageTable[i] = (i * 0x1000) | 3;
    }
    reMap();
    pageDirectory[0] = (uint32_t)firstPageTable | 3;
    pageDirectory[768] = (uint32_t)table_768 | 3;
    loadPageDirectory(pageDirectory);
    vmmEnable();
}