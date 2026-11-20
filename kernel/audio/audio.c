#include "audio.h"
#include "../../types.h"
#include "../../arch/x86_64/cpu.h"

void audio_init(void) {}
void audio_beep(u32 freq, u32 ms) {
    u32 div = 1193180 / freq;
    outb(0x43, 0xB6);
    outb(0x42, div & 0xFF);
    outb(0x42, (div >> 8) & 0xFF);
    u8 tmp = inb(0x61);
    outb(0x61, tmp | 3);
    /* busy wait approx */
    for (volatile u32 i = 0; i < ms * 1000; i++) {}
    outb(0x61, tmp & ~3);
}
EOF