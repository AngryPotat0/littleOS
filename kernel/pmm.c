#include"../include/type.h"
#include"../include/pmm.h"
#include"../include/memory.h"
#include"../include/bootStruct.h"

extern multiboot_t *mutiboot_addr32;
static uint32_t pageFrame[PAGE_COUNT];
static uint32_t pageSp = 0;

static uint32_t getMaxAddr(){
	uint32_t maxAddr=0;
	for(pm_entry_t * pm_entry_cur = mutiboot_addr32->mmap_addr;pm_entry_cur<mutiboot_addr32->mmap_addr+mutiboot_addr32->mmap_length;pm_entry_cur++){
		if(pm_entry_cur->type==1 && maxAddr < pm_entry_cur->base_addr_low+pm_entry_cur->length_low)
			maxAddr=pm_entry_cur->base_addr_low+pm_entry_cur->length_low;		
	}
	return maxAddr;
}

void pmmInit(uint32_t kernelStart, uint32_t kernelEnd)
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