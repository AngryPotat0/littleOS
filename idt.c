#include"idt.h"
#include"type.h"
#include"util.h"
#include"screen.h"

static struct idtEntry idt[NIDT];
struct idtr idtp;

extern struct tssEntry tss;
extern void idtLoad() // loader.s

void idtInit()
{
    idtp.limit = (sizeof(struct idtEntry) * NIDT) - 1;
    idtp.base = (uint32_t)&(idtp);
    memset(&idt, 0, sizeof(struct idtEntry) * NIDT);

    

    // debugIdtInstall();
    idtLoad();
}

void idtInstall(int n,uint32_t offset, uint16_t selector, uint8_t typeAttr)
{
    idt[n].offsetLow = (offset & 0xffff);
    idt[n].offsetHigh = (offset >> 16) & 0xffff;
    idt[n].selector = selector;
    idt[n].zero = 0;
    //TODO type and attr
    idt[n].typeAttr = typeAttr;
}

// 设置TSS
void tssSet(uint16_t ss0, uint32_t esp0)
{
    // 清空TSS
    memset((void *)&tss, 0, sizeof(tss));
    tss.ss0 = ss0;
    tss.esp0 = esp0;
    tss.iopb_off = sizeof(tss);
}

// 重置当前进程的TSS
void tssReset()
{
    // TSS用于当切换到ring0时设置堆栈
    // 每个进程有一个内核堆栈
    tssSet(SEL_KDATA << 3, (uint32_t)proc->stack + PAGE_SIZE);
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