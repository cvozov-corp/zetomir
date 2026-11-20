#include "wm.h"
#include "../types.h"
#include "../drivers/framebuffer.h"
static int cx = 640, cy = 360;
void wm_init(void) {}
void wm_move_cursor(int x, int y) { cx = x; cy = y; }
void wm_paint(void) {
    fb_rect(cx, cy, 8, 8, 0x00FFFFFFu);
}
