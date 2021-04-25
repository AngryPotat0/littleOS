#include"idt.h"
#include"type.h"
#include"util.h"

struct idtEntry idt[NIDT];
struct idtr idtp;

extern struct tssEntry tss;
extern void idtLoad() // entry.s

void idtInit()
{
    idtp.limit = (sizeof(struct idtEntry) * NIDT) - 1;
    idtp.base = (uint32_t)&(idtp);
    memset(&idt, 0, sizeof(struct idtEntry) * NIDT);

    idtLoad();
}

void idtInstall(int n,uint32_t offset, uint16_t selector, uint8_t type, uint8_t attr)
{
    idt[n].offsetLow = (offset & 0xffff);
    idt[n].offsetHigh = (offset >> 16) & 0xffff;
    idt[n].selector = selector;
    idt[n].zero = 0;
    //TODO type and attr
}