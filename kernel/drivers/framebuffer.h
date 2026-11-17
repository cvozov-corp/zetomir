#ifndef ZETOMIR_FRAMEBUFFER_H
#define ZETOMIR_FRAMEBUFFER_H
#include "../types.h"
void fb_init(void *address, u64 width, u64 height, u64 pitch, u16 bpp);
void fb_clear(u32 color);
void fb_rect(i32 x, i32 y, i32 w, i32 h, u32 color);
void fb_text(i32 x, i32 y, const char *s, u32 color, i32 scale);
int fb_ready(void);
#endif
