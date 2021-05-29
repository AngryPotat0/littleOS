#ifndef PMM__
#define PMM__

#define PAGE_COUNT 20
#define PAGE_SIZE 0x1000
#define PAGE_START 0x0A000000//FIXME:

void pmmInit(uint32_t kernelStart, uint32_t kernelEnd);
uint32_t pmmAlloc();
void pmmFree(uint32_t addr);

#endif