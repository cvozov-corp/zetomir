#include "console.h"
#include "../drivers/framebuffer.h"
#include "../drivers/serial.h"
static int cursor_x=24, cursor_y=100;
static const int scale=2;
#define WHITE 0x00E6EDF3u
#define GREEN 0x0057D6A0u
static void newline(void) { cursor_x=24; cursor_y += 20; }
void console_init(void) {
    cursor_x=24; cursor_y=100;
}
void console_putc(char c) {
    char tmp[2]={c,0};
    serial_putc(c);
    if (!fb_ready()) return;
    if (c=='\r') return;
    if (c=='\n') { newline(); return; }
    fb_text(cursor_x,cursor_y,tmp,WHITE,scale);
    cursor_x += 12;
    if (cursor_x > 1100) newline();
    if (cursor_y > 700) cursor_y=100;
}
void console_write(const char *s) {
    while (*s) console_putc(*s++);
}
