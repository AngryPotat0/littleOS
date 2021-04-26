#include"idt.h"
#include"type.h"
#include"util.h"
#include"screen.h"

struct idtEntry idt[NIDT];
struct idtr idtp;

extern struct tssEntry tss;
extern void idtLoad() // entry.s

void idtInit()
{
    idtp.limit = (sizeof(struct idtEntry) * NIDT) - 1;
    idtp.base = (uint32_t)&(idtp);
    memset(&idt, 0, sizeof(struct idtEntry) * NIDT);

    // debugIdtInstall();
    idtLoad();
}

void idtInstall(int n,uint32_t offset, uint16_t selector, uint8_t p, uint8_t dpl, uint8_t s, uint8_t gate)
{
    idt[n].offsetLow = (offset & 0xffff);
    idt[n].offsetHigh = (offset >> 16) & 0xffff;
    idt[n].selector = selector;
    idt[n].zero = 0;
    //TODO type and attr
    idt[n].typeAttr = 0;// if we have idtInit, then why we need this?
    idt[n].typeAttr = idt[n].typeAttr | gate | (s << 4) | (dpl << 5) | (p << 7); 
}

// void debugIdtInstall()
// {
//     for(int i = 0;i < 15;i++)
//     {
//         idtInstall(i,1835008 + i,i,i % 2,i % 4,(i + 1) % 2,(i + 10) % 16);
//     }
//     for(int n = 0;n < 15;n++)
//     {
//         printBin(idt[n].offsetLow,2);
//         printBin(idt[n].selector,2);
//         printBin(idt[n].zero,1);
//         printBin(idt[n].typeAttr,1);
//         printBin(idt[n].offsetHigh,2);
//     }
// }