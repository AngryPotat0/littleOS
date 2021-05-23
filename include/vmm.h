#ifndef VMM__
#define VMM__
void vmmInit();
void loadPageDirectory(uint32_t* pd);
void vmmEnable();
void mapPage(uint32_t* pd,uint32_t physAddr,uint32_t virtualAddr, uint32_t flags);
#endif