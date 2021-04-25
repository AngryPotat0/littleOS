#include"gdt.h"
#include"tss.h"
void tssInit() {
    gdtInstall(SEL_TSS, (uint32_t)&tss, sizeof(tss), AC_PR|AC_AC|AC_EX, GDT_GR); 
    /* for tss, access_reverse bit is 1 */
    gdt[SEL_TSS].access &= ~AC_RE;
}