#include"irq.h"
#include"asm.h"

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

void irq0_handler(void)
{
    outb(0x20, 0x20); //EOI
}
 
void irq1_handler(void)
{
    outb(0x20, 0x20); //EOI
}
 
void irq2_handler(void)
{
    outb(0x20, 0x20); //EOI
}
 
void irq3_handler(void)
{
    outb(0x20, 0x20); //EOI
}
 
void irq4_handler(void)
{
    outb(0x20, 0x20); //EOI
}
 
void irq5_handler(void)
{
    outb(0x20, 0x20); //EOI
}
 
void irq6_handler(void)
{
    outb(0x20, 0x20); //EOI
}
 
void irq7_handler(void)
{
    outb(0x20, 0x20); //EOI
}
 
void irq8_handler(void)
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI          
}
 
void irq9_handler(void)
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq10_handler(void)
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq11_handler(void)
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq12_handler(void)
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq13_handler(void)
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq14_handler(void)
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq15_handler(void)
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}