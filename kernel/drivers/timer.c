#include "timer.h"
#include "../types.h"
#include "../../arch/x86_64/cpu.h"

static volatile u64 ticks = 0;
void timer_init(u32 hz) {
    u32 divisor = 1193180 / hz;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}
u64 timer_ticks(void) { return ticks; }
