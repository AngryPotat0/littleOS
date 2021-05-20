#ifndef VMM__
#define VMM__
void vmmInit();
void loadPageDirectory(uint32_t* pd);
void vmmEnable();
#endif