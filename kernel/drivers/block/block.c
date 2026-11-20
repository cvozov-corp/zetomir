#include "block.h"
#include "../../types.h"
#include "../../mm/heap.h"

#define BLOCK_SIZE 512
#define NUM_BLOCKS 1024
static u8 disk[NUM_BLOCKS * BLOCK_SIZE];

void block_init(void) {
    for (usize i = 0; i < NUM_BLOCKS * BLOCK_SIZE; i++) disk[i] = 0;
}

int block_read(u32 lba, u8 *buf) {
    if (lba >= NUM_BLOCKS) return -1;
    for (int i = 0; i < BLOCK_SIZE; i++) buf[i] = disk[lba*BLOCK_SIZE + i];
    return 0;
}

int block_write(u32 lba, const u8 *buf) {
    if (lba >= NUM_BLOCKS) return -1;
    for (int i = 0; i < BLOCK_SIZE; i++) disk[lba*BLOCK_SIZE + i] = buf[i];
    return 0;
}
EOF