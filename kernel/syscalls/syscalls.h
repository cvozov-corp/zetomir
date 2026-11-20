#ifndef ZETOMIR_SYSCALLS_H
#define ZETOMIR_SYSCALLS_H
#include "../../types.h"
void syscalls_init(void);
u64 syscall_dispatch(u64 num, u64 a1, u64 a2, u64 a3);
void syscall_entry(void);
#endif
EOF