#include "gdt.h"
#include "../../types.h"

typedef struct {
    u16 limit_low;
    u16 base_low;
    u8  base_mid;
    u8  access;
    u8  granularity;
    u8  base_high;
} PACKED gdt_entry_t;

typedef struct {
    u16 limit;
    u64 base;
} PACKED gdt_ptr_t;

static gdt_entry_t gdt[5];
static gdt_ptr_t gdt_ptr;

static void gdt_set(int i, u32 base, u32 limit, u8 access, u8 gran) {
    gdt[i].base_low = base & 0xFFFF;
    gdt[i].base_mid = (base >> 16) & 0xFF;
    gdt[i].base_high = (base >> 24) & 0xFF;
    gdt[i].limit_low = limit & 0xFFFF;
    gdt[i].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[i].access = access;
}

void gdt_init(void) {
    gdt_ptr.limit = sizeof(gdt) - 1;
    gdt_ptr.base = (u64)&gdt;
    gdt_set(0, 0, 0, 0, 0);
    gdt_set(1, 0, 0xFFFFFFFF, 0x9A, 0xAF); /* kernel code */
    gdt_set(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* kernel data */
    gdt_set(3, 0, 0xFFFFFFFF, 0xFA, 0xAF); /* user code */
    gdt_set(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* user data */
    __asm__ volatile ("lgdt %0" :: "m"(gdt_ptr) : "memory");
    __asm__ volatile (
        "pushq $0x08\n\t"
        "lea 1f(%%rip), %%rax\n\t"
        "pushq %%rax\n\t"
        "lretq\n\t"
        "1:\n\t"
        "mov $0x10, %%ax\n\t"
        "mov %%ax, %%ds\n\t"
        "mov %%ax, %%es\n\t"
        "mov %%ax, %%ss\n\t"
        ::: "rax", "memory"
    );
}
