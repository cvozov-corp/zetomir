#include "sched.h"
#include "../types.h"
static u64 current = 0;
void sched_init(void) { current = 0; }
void sched_tick(void) { current++; }
