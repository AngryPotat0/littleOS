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

#define NIDT 256

#define GATE_TASK 0x5
#define GATE_INTERRUPT 0xe
#define GATE_TRAP 0xf

void idtInit();
void idtInstall(int n,uint32_t offset, uint16_t selector, uint8_t typeAttr);

void tssReset();
void tssSet(uint16_t ss0, uint32_t esp0);

#endif