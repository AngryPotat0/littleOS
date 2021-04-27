#include"idt.h"
#include"type.h"
#include"util.h"
#include"screen.h"
#include"asm.h"
#include"gdt.h"
#include"tss.h"

static struct idtEntry idt[NIDT];
struct idtr idtp;

struct tssEntry tss;
extern void idtLoad(); // loader.s

void idtInit()
{   
    extern int irq0();
    extern int irq1();
    extern int irq2();
    extern int irq3();
    extern int irq4();
    extern int irq5();
    extern int irq6();
    extern int irq7();
    extern int irq8();
    extern int irq9();
    extern int irq10();
    extern int irq11();
    extern int irq12();
    extern int irq13();
    extern int irq14();
    extern int irq15();
 
	unsigned long irq0Address;
    unsigned long irq1Address;
    unsigned long irq2Address;
    unsigned long irq3Address;          
    unsigned long irq4Address; 
    unsigned long irq5Address;
    unsigned long irq6Address;
    unsigned long irq7Address;
    unsigned long irq8Address;
    unsigned long irq9Address;          
    unsigned long irq10Address;
    unsigned long irq11Address;
    unsigned long irq12Address;
    unsigned long irq13Address;
    unsigned long irq14Address;          
    unsigned long irq15Address;
 
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 40);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    irq0Address = (unsigned long)irq0; 
    idtInstall(32, irq0Address,0x08,0x8e);//0x08:KERNEL_CODE_SEGMENT_OFFSET 0x8e:INTERRUPT_GATE
    irq1Address = (unsigned long)irq1;
    idtInstall(33, irq1Address,0x08,0x8e);
    irq2Address = (unsigned long)irq2;
    idtInstall(34, irq2Address,0x08,0x8e);
    irq3Address = (unsigned long)irq3;
    idtInstall(35, irq3Address,0x08,0x8e);
    irq4Address = (unsigned long)irq4;
    idtInstall(36, irq4Address,0x08,0x8e);
    irq5Address = (unsigned long)irq5;
    idtInstall(37, irq5Address,0x08,0x8e);
    irq6Address = (unsigned long)irq6;
    idtInstall(38, irq6Address,0x08,0x8e);
    irq7Address = (unsigned long)irq7;
    idtInstall(39, irq7Address,0x08,0x8e);
    irq8Address = (unsigned long)irq8;
    idtInstall(40, irq8Address,0x08,0x8e);
    irq9Address = (unsigned long)irq9;
    idtInstall(41, irq9Address,0x08,0x8e);
    irq10Address = (unsigned long)irq10;
    idtInstall(42, irq10Address,0x08,0x8e);
    irq11Address = (unsigned long)irq11;
    idtInstall(43, irq11Address,0x08,0x8e);
    irq12Address = (unsigned long)irq12;
    idtInstall(44, irq12Address,0x08,0x8e);
    irq13Address = (unsigned long)irq13;
    idtInstall(45, irq13Address,0x08,0x8e);
    irq14Address = (unsigned long)irq14;
    idtInstall(46, irq14Address,0x08,0x8e);
    irq15Address = (unsigned long)irq15;
    idtInstall(47, irq15Address,0x08,0x8e);

    idtp.limit = (sizeof(struct idtEntry) * NIDT) - 1;
    idtp.base = (uint32_t)&(idtp);

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
    tss.iopbOff = sizeof(tss);
}

// 重置当前进程的TSS
// void tssReset()
// {
//     // TSS用于当切换到ring0时设置堆栈
//     // 每个进程有一个内核堆栈
//     tssSet(SEL_KDATA << 3, (uint32_t)proc->stack + PAGE_SIZE);
// }

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