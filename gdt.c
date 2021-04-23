#include"gdt.h"
// #include"idt.h"
#include"util.h"
#include"type.h"

// extern struct tssEntry tss;

static struct gdtEntry gdt[NGDT]; // 256 gdt entry
struct gdtPtr gp; // entry.s中使用

extern void gdtFlush(); // 在loader.asm中实现 extern func in loader.asm

void gdtInstall(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    gdt[num].baseLow = base & 0xffff;
    gdt[num].baseMiddle = (base >> 16) & 0xff;
    gdt[num].baseHigh = (base >> 24) & 0xff;

    gdt[num].limitLow = limit & 0xffff;
    gdt[num].limitHigh = (limit >> 16) & 0x0f;

    gdt[num].flags = flags;
    access |= AC_RE;
    gdt[num].access = access;
}

// void tssInit() {
//     gdtInstall(SEL_TSS, (uint32_t)&tss, sizeof(tss), AC_PR|AC_AC|AC_EX, GDT_GR); 
//     /* for tss, access_reverse bit is 1 */
//     gdt[SEL_TSS].access &= ~AC_RE;
// }

void gdtInit() {
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct gdtEntry) * NGDT) - 1;
    gp.base = (uint32_t)&gdt;

    // 注意：启用分页GDT_GR后，limit的单位是4KB，故0xfffff*4KB=4GB

    /* null descriptor */
    gdtInstall(0, 0, 0, 0, 0);
    /* kernel code segment type: code addr: 0 limit: 4G gran: 4KB sz: 32bit */
    gdtInstall(SEL_KCODE, 0, 0xfffff, AC_RW|AC_EX|AC_DPL_KERN|AC_PR, GDT_GR|GDT_SZ);
    /* kernel data segment type: data addr: 0 limit: 4G gran: 4KB sz: bit 32bit */
    gdtInstall(SEL_KDATA, 0, 0xfffff, AC_RW|AC_DPL_KERN|AC_PR, GDT_GR|GDT_SZ);
    /* user code segment type: code addr: 0 limit: 4G gran: 4KB sz: 32bit */
    gdtInstall(SEL_UCODE, 0, 0xfffff, AC_RW|AC_EX|AC_DPL_USER|AC_PR, GDT_GR|GDT_SZ);
    /* user code segment type: data addr: 0 limit: 4G gran: 4KB sz: 32bit */
    gdtInstall(SEL_UDATA, 0, 0xfffff, AC_RW|AC_DPL_USER|AC_PR, GDT_GR|GDT_SZ);
    /* systask code segment type: code addr: 0 limit: 4G gran: 4KB sz: 32bit */
    gdtInstall(SEL_SCODE, 0, 0xfffff, AC_RW|AC_EX|AC_DPL_SYST|AC_PR, GDT_GR|GDT_SZ);
    /* systask code segment type: data addr: 0 limit: 4G gran: 4KB sz: 32bit */
    gdtInstall(SEL_SDATA, 0, 0xfffff, AC_RW|AC_DPL_SYST|AC_PR, GDT_GR|GDT_SZ);

    // tssInit();
    gdtFlush();
    // tssInstall();
}