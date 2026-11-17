#ifndef ZETOMIR_CPU_H
#define ZETOMIR_CPU_H
#include "../../types.h"
static inline void cpu_halt(void) { __asm__ volatile ("hlt"); }
static inline void cpu_cli(void) { __asm__ volatile ("cli" ::: "memory"); }
static inline void cpu_sti(void) { __asm__ volatile ("sti" ::: "memory"); }
static inline u8 inb(u16 port) {
    u8 value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}
static inline void outb(u16 port, u8 value) {
    __asm__ volatile ("outb %0, %1" :: "a"(value), "Nd"(port));
}
void cpu_init(void);
#endif
