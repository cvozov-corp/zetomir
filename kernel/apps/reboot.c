#include "reboot.h"
#include "../../types.h"
#include "../../arch/x86_64/cpu.h"

typedef struct { u16 limit; u64 base; } PACKED idtr_t;

void reboot(void) {
    outb(0xCF9, 0x06);
    idtr_t idtr = {0, 0};
    __asm__ volatile ("lidt %0" :: "m"(idtr));
    __asm__ volatile ("int $0");
    for (;;) cpu_halt();
}

void shutdown(void) {
    /* ACPI shutdown (simplified) */
    outb(0xB004, 0x00);
    __asm__ volatile ("cli");
    for (;;) cpu_halt();
}
EOF