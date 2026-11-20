#ifndef ZETOMIR_BLOCK_H
#define ZETOMIR_BLOCK_H
#include "../../types.h"
void block_init(void);
int block_read(u32 lba, u8 *buf);
int block_write(u32 lba, const u8 *buf);
#endif
EOF