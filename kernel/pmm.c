#include"../include/type.h"
#include"../include/pmm.h"
#include"../include/memory.h"

static uint32_t pageFrame[PAGE_COUNT];
static uint32_t pageSp = 0;

void pmmInit()
{
    for(int i = 0;i < PAGE_COUNT;i++)
    {
        pageFrame[pageSp++] = PAGE_SIZE * i + PAGE_START;
    }
}

uint32_t pmmAlloc()
{
    uint32_t addr = pageFrame[--pageSp];
    memset(addr,0,PAGE_SIZE);
    return addr;
}

void pmmFree(uint32_t addr)
{
    pageFrame[pageSp++] = addr;
}