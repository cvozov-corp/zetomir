#ifndef ZETOMIR_TIMER_H
#define ZETOMIR_TIMER_H
#include "../types.h"
void timer_init(u32 hz);
u64 timer_ticks(void);
#endif
