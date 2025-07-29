#include "gdt.h"

#define GDT_ENTRIES 3
struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gdtp;

extern void gdt_flush(uint32_t); // From assembly

static void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low    = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = limit & 0xFFFF;
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access       = access;
}

void gdt_install(void) {
    gdtp.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
    gdtp.base  = (uint32_t)&gdt;

    gdt_set_entry(0, 0, 0, 0, 0);                // Null segment
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment

    gdt_flush((uint32_t)&gdtp);
}

