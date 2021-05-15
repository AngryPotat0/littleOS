#include"../include/interrupt.h"
#include"../include/type.h"
#include"../include/util.h"
#include"../include/screen.h"
#include"../include/port.h"
#include"../include/asm.h"
#include"../include/gdt.h"
#include"../include/tss.h"

serverFunc serverFuncList[256];

struct idtEntry idt[NIDT];
struct idtr idtp;

struct tssEntry tss;
extern void idtLoad(); // loader.s

static char *faultMsg[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();//isr0-31 is used to service exceptions
extern void isr32();
extern void isr33();

void falutHandler(void* args)
{
    printString((char*)args);
}

void registeInterrupt(int idx,serverFunc target_func){
	serverFuncList[idx] = target_func;
}

void funcRoute(int int_no,void * args){
    if(int_no >= 40)
        port_byte_out(0x20,0x20);//slave
    port_byte_out(0x20,0x20);//master

    if(int_no < 32)
    {
        serverFuncList[int_no]((void*)faultMsg[int_no]);
    }
    else
    {
        serverFuncList[int_no](args);
    }
}

void idtInit()
{
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

    idtInstall(0, (uint32_t)isr0,0x08,0x8e);//0x08:KERNEL_CODE_SEGMENT_OFFSET 0x8e:INTERRUPT_GATE
    idtInstall(1, (uint32_t)isr1,0x08,0x8e);
    idtInstall(2, (uint32_t)isr2,0x08,0x8e);
    idtInstall(3, (uint32_t)isr3,0x08,0x8e);
    idtInstall(4, (uint32_t)isr4,0x08,0x8e);
    idtInstall(5, (uint32_t)isr5,0x08,0x8e);
    idtInstall(6, (uint32_t)isr6,0x08,0x8e);
    idtInstall(7, (uint32_t)isr7,0x08,0x8e);
    idtInstall(8, (uint32_t)isr8,0x08,0x8e);
    idtInstall(9, (uint32_t)isr9,0x08,0x8e);
    idtInstall(10, (uint32_t)isr10,0x08,0x8e);
    idtInstall(11, (uint32_t)isr11,0x08,0x8e);
    idtInstall(12, (uint32_t)isr12,0x08,0x8e);
    idtInstall(13, (uint32_t)isr13,0x08,0x8e);
    idtInstall(14, (uint32_t)isr14,0x08,0x8e);
    idtInstall(15, (uint32_t)isr15,0x08,0x8e);
    idtInstall(16, (uint32_t)isr16,0x08,0x8e);
    idtInstall(17, (uint32_t)isr17,0x08,0x8e);
    idtInstall(18, (uint32_t)isr18,0x08,0x8e);
    idtInstall(19, (uint32_t)isr19,0x08,0x8e);
    idtInstall(20, (uint32_t)isr20,0x08,0x8e);
    idtInstall(21, (uint32_t)isr21,0x08,0x8e);
    idtInstall(22, (uint32_t)isr22,0x08,0x8e);
    idtInstall(23, (uint32_t)isr23,0x08,0x8e);
    idtInstall(24, (uint32_t)isr24,0x08,0x8e);
    idtInstall(25, (uint32_t)isr25,0x08,0x8e);
    idtInstall(26, (uint32_t)isr26,0x08,0x8e);
    idtInstall(27, (uint32_t)isr27,0x08,0x8e);
    idtInstall(28, (uint32_t)isr28,0x08,0x8e);
    idtInstall(29, (uint32_t)isr29,0x08,0x8e);
    idtInstall(30, (uint32_t)isr30,0x08,0x8e);
    idtInstall(31, (uint32_t)isr31,0x08,0x8e);

    idtInstall(32, (uint32_t)isr32,0x08,0x8e);
    idtInstall(33, (uint32_t)isr33,0x08,0x8e);

    for(int i = 0;i < 32;i++)
    {
        registeInterrupt(i,falutHandler);
    }

    idtp.limit = (sizeof(struct idtEntry) * NIDT) - 1;
    idtp.base = (uint32_t)&(idt);//这里是怎么写成idtp的

    // debugIdtInstall();
    idtLoad();
}

void idtInstall(int n,uint32_t offset, uint16_t selector, uint8_t typeAttr)
{
    idt[n].offsetLow = (offset & 0xffff);
    idt[n].offsetHigh = (offset >> 16) & 0xffff;
    idt[n].selector = selector;
    idt[n].zero = 0;
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