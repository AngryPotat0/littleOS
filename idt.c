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