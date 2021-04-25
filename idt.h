#ifndef IDT__
#define IDT__
#include"type.h"

struct idtEntry{
    uint16_t offsetLow;
    uint16_t selector;
    uint8_t zero;
    uint8_t typeAttr;
    uint16_t offsetHigh;
}__attribute__ ((packed));

struct idtr{
    uint16_t limit;
    uint32_t base;
}__attribute__ ((packed));

#define NIDT 256;

#define TASK_GATE 0x5;
#define INTERRUPT_GATE 0xe;
#define TRAP_GATE 0xf;

void idtInit();
void idtInstall(int n,uint32_t offset, uint16_t selector, uint8_t type, uint8_t attr);

#endif