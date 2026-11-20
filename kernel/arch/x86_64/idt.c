#include "idt.h"
#include "../../types.h"
#include "../../drivers/serial.h"

typedef struct {
    u16 offset_low;
    u16 selector;
    u8  ist;
    u8  type_attr;
    u16 offset_mid;
    u32 offset_high;
    u32 zero;
} PACKED idt_entry_t;

typedef struct {
    u16 limit;
    u64 base;
} PACKED idt_ptr_t;

static idt_entry_t idt[256];
static idt_ptr_t idt_ptr;

extern void isr0(void);
static void idt_set(int i, u64 handler) {
    idt[i].offset_low = handler & 0xFFFF;
    idt[i].selector = 0x08;
    idt[i].ist = 0;
    idt[i].type_attr = 0x8E;
    idt[i].offset_mid = (handler >> 16) & 0xFFFF;
    idt[i].offset_high = (handler >> 32) & 0xFFFFFFFF;
    idt[i].zero = 0;
}

__attribute__((naked)) void isr0(void) {
    __asm__ volatile (
        "pushq $0\n\t"
        "pushq $0\n\t"
        "jmp common_handler\n\t"
    );
}

__attribute__((naked)) static void common_handler(void) {
    __asm__ volatile (
        "pushq %rax\n\t"
        "pushq %rcx\n\t"
        "pushq %rdx\n\t"
        "movb $'!', %al\n\t"
        "outb %al, $0x3F8\n\t"
        "popq %rdx\n\t"
        "popq %rcx\n\t"
        "popq %rax\n\t"
        "iretq\n\t"
    );
}

void idt_init(void) {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (u64)&idt;
    for (int i = 0; i < 256; i++) idt_set(i, (u64)isr0);
    __asm__ volatile ("lidt %0" :: "m"(idt_ptr) : "memory");
}
