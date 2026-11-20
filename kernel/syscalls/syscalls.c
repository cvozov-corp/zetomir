#include "syscalls.h"
#include "../../types.h"
#include "../../arch/x86_64/cpu.h"

static u64 syscall_handler(u64 num, u64 a1, u64 a2, u64 a3) {
    switch (num) {
        case 0: /* write */ {
            const char *s = (const char*)a2;
            for (u64 i = 0; i < a3; i++) {
                /* serial output */
            }
            UNUSED(s);
            return a3;
        }
        case 1: /* exit */
            for (;;) cpu_halt();
        default: return (u64)-1;
    }
}

void syscalls_init(void) {
    /* set up LSTAR MSR */
    u64 handler = (u64)syscall_entry;
    __asm__ volatile ("wrmsr" :: "c"(0xC0000082), "a"(handler & 0xFFFFFFFF), "d"(handler >> 32));
    /* enable syscall */
    u32 lo, hi;
    __asm__ volatile ("rdmsr" : "=a"(lo), "=d"(hi) : "c"(0xC0000080));
    lo |= (1 << 0);
    __asm__ volatile ("wrmsr" :: "c"(0xC0000080), "a"(lo), "d"(hi));
}

/* naked entry */
__attribute__((naked)) void syscall_entry(void) {
    __asm__ volatile (
        "swapgs\n\t"
        "mov %rsp, %gs:0\n\t"
        "mov %gs:8, %rsp\n\t"
        "push %rcx\n\t"
        "push %r11\n\t"
        "call syscall_dispatch\n\t"
        "pop %r11\n\t"
        "pop %rcx\n\t"
        "swapgs\n\t"
        "sysretq\n\t"
    );
}

u64 syscall_dispatch(u64 num, u64 a1, u64 a2, u64 a3) {
    return syscall_handler(num, a1, a2, a3);
}
EOF