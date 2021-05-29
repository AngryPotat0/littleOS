#ifndef PMM__
#define PMM__

#define PAGE_SIZE 0x1000

#define PMM_MAX_SIZE 0x04000000 // 64M
#define PAGE_MAX_SIZE (PMM_MAX_SIZE/PAGE_SIZE)

void pmmInit();
uint32_t pmmAlloc();
void pmmFree(uint32_t addr);

#endif