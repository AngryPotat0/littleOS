#include"../include/type.h"
#include"../include/pmm.h"
#include"../include/memory.h"
#include"../include/bootStruct.h"

// #include"../include/screen.h"

extern multiboot_t *mutiboot_addr32;
extern uint32_t kernel_start_addr;
extern uint32_t kernel_end_addr;

static uint32_t pageFrame[PAGE_MAX_SIZE];
static uint32_t pageSp = 0;

static uint32_t getMaxAddr(){
	uint32_t maxAddr=0;
	for(pm_entry_t * pm_entry_cur = mutiboot_addr32->mmap_addr;pm_entry_cur<mutiboot_addr32->mmap_addr+mutiboot_addr32->mmap_length;pm_entry_cur++){
		if(pm_entry_cur->type==1 && maxAddr < pm_entry_cur->base_addr_low+pm_entry_cur->length_low)
			maxAddr=pm_entry_cur->base_addr_low+pm_entry_cur->length_low;		
	}
	return maxAddr;
}

void pmmInit()
{
    uint32_t pageStart = (kernel_start_addr + PAGE_SIZE) & 0xFFFFF000;
    uint32_t pageEnd = (getMaxAddr()) & 0xFFFFF000;
    uint32_t pageCount = (pageEnd - pageStart) / PAGE_SIZE;
    // int count = 0;
    for(int i = 0;i < pageCount && i < PAGE_MAX_SIZE;i++)
    {
        pageFrame[pageSp++] = PAGE_SIZE * i + pageStart;
        // count += 1;
    }
    // printString("Page count:");
    // printInt(count);
    // printString("\n");
    // printString("Page Start:");
    // printInt(pageStart);
    // printString("\n");
    // printString("Page End:");
    // printInt(pageEnd);
    // printString("\n");
    
    
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