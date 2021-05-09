#include"interrupt.h"
#include"type.h"
#include"util.h"
#include"screen.h"
#include"asm.h"
#include"gdt.h"
#include"tss.h"

serverFunc serverFuncList[256];

struct idtEntry idt[NIDT];
struct idtr idtp;

struct tssEntry tss;
extern void idtLoad(); // loader.s

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
extern void isr31();
extern void isr32();

void timerServer(void *args)
{
    printString("T\n");
}

void registeInterrupt(int idx,serverFunc target_func){
    // printString("run!\n");
    // target_func(NULL);
	serverFuncList[idx] = target_func;
}

void funcRoute(int int_no,void * args){
	serverFuncList[int_no](args);
}

// 时钟中断 初始化 8253 PIT

static void timerInit(uint32_t frequency){
    // Intel 8253/8254 PIT芯片 I/O端口地址范围是40h~43h
    // 输入频率为 1193180，frequency 即每秒中断次数
    uint32_t divisor = 1193180 / frequency;
    // D7 D6 D5 D4 D3 D2 D1 D0
    // 0  0  1  1  0  1  1  0
    // 即就是 36 H
    // 设置 8253/8254 芯片工作在模式 3 下
    outb(0x43, 0x36);

    // 拆分低字节和高字节
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t hign = (uint8_t)((divisor >> 8) & 0xFF);
    
    // 分别写入低字节和高字节
    outb(0x40, low);
    outb(0x40, hign);
}

void idtInit()
{
    // outb(0x20, 0x11);
    // outb(0xA0, 0x11);
    // outb(0x21, 0x20);
    // outb(0xA1, 40);
    // outb(0x21, 0x04);
    // outb(0xA1, 0x02);
    // outb(0x21, 0x01);
    // outb(0xA1, 0x01);
    // outb(0x21, 0x0);
    // outb(0xA1, 0x0);

    #define PIC_M_CTRL 0x20 //主片控制端口
    #define PIC_M_DATA 0x21 //主片数据端口
    #define PIC_S_CTRL 0xa0 //从片控制端口
    #define PIC_S_DATA 0xa1 //从片数据端口

     /*初始化主片 */
outb (PIC_M_CTRL, 0x11); // ICW1: 边沿触发,级联8259, 需要ICW4
outb (PIC_M_DATA, 0x20); // ICW2: 起始中断向量号为0x20, 也就是IR[0-7] 为 0x20 ～ 0x27
outb (PIC_M_DATA, 0x04); // ICW3: IR2 接从片
outb (PIC_M_DATA, 0x01); // ICW4: 8086 模式, 正常EOI

/*初始化从片 */
outb (PIC_S_CTRL, 0x11); // ICW1: 边沿触发,级联8259, 需要ICW4
outb (PIC_S_DATA, 0x28); // ICW2: 起始中断向量号为0x28, 也就是IR[8-15]为0x28 ～ 0x2F
outb (PIC_S_DATA, 0x02); // ICW3: 设置从片连接到主片的IR2 引脚
outb (PIC_S_DATA, 0x01); // ICW4: 8086 模式, 正常EOI

/*打开主片上IR0,也就是目前只接受时钟产生的中断 */
outb (PIC_M_DATA, 0xfe);
outb (PIC_S_DATA, 0xff);


    idtInstall(0, (unsigned long)isr0,0x08,0x8e);//0x08:KERNEL_CODE_SEGMENT_OFFSET 0x8e:INTERRUPT_GATE
    idtInstall(1, (unsigned long)isr1,0x08,0x8e);
    idtInstall(2, (unsigned long)isr2,0x08,0x8e);
    idtInstall(3, (unsigned long)isr3,0x08,0x8e);
    idtInstall(4, (unsigned long)isr4,0x08,0x8e);
    idtInstall(5, (unsigned long)isr5,0x08,0x8e);
    idtInstall(6, (unsigned long)isr6,0x08,0x8e);
    idtInstall(7, (unsigned long)isr7,0x08,0x8e);
    idtInstall(8, (unsigned long)isr8,0x08,0x8e);
    idtInstall(9, (unsigned long)isr9,0x08,0x8e);
    idtInstall(10, (unsigned long)isr10,0x08,0x8e);
    idtInstall(11, (unsigned long)isr11,0x08,0x8e);
    idtInstall(12, (unsigned long)isr12,0x08,0x8e);
    idtInstall(13, (unsigned long)isr13,0x08,0x8e);
    idtInstall(14, (unsigned long)isr14,0x08,0x8e);
    idtInstall(15, (unsigned long)isr15,0x08,0x8e);
    idtInstall(16, (unsigned long)isr16,0x08,0x8e);
    idtInstall(17, (unsigned long)isr17,0x08,0x8e);
    idtInstall(18, (unsigned long)isr18,0x08,0x8e);
    idtInstall(19, (unsigned long)isr19,0x08,0x8e);
    idtInstall(20, (unsigned long)isr20,0x08,0x8e);
    idtInstall(21, (unsigned long)isr21,0x08,0x8e);
    idtInstall(22, (unsigned long)isr22,0x08,0x8e);
    idtInstall(23, (unsigned long)isr23,0x08,0x8e);
    idtInstall(24, (unsigned long)isr24,0x08,0x8e);
    idtInstall(25, (unsigned long)isr25,0x08,0x8e);
    idtInstall(26, (unsigned long)isr26,0x08,0x8e);
    idtInstall(27, (unsigned long)isr27,0x08,0x8e);
    idtInstall(28, (unsigned long)isr28,0x08,0x8e);
    idtInstall(29, (unsigned long)isr29,0x08,0x8e);
    idtInstall(30, (unsigned long)isr30,0x08,0x8e);
    idtInstall(31, (unsigned long)isr31,0x08,0x8e);
    idtInstall(32, (unsigned long)isr32,0x08,0x8e);

    registeInterrupt(32,timerServer);

    idtp.limit = (sizeof(struct idtEntry) * NIDT) - 1;
    idtp.base = (uint32_t)&(idt);//这里是怎么写成idtp的
    timerInit(1000);

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