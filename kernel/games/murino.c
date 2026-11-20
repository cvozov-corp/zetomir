#include "murino.h"
#include "../types.h"
#include "../console/console.h"
#include "../drivers/keyboard.h"

static int px = 5, py = 5;
static int running = 1;

void murino_init(void) {
    console_write("Murino engine initialized\n");
    console_write("Controls: w/a/s/d move, q quit\n");
}

void murino_tick(void) {
    char c = keyboard_read();
    if (!c) return;
    if (c == 'q') { running = 0; console_write("Murino: quit\n"); return; }
    if (c == 'w') py--;
    if (c == 's') py++;
    if (c == 'a') px--;
    if (c == 'd') px++;
    /* redraw minimal */
    console_write("Murino player: ");
    /* print coords */
    char buf[16]; int i=0, v=px;
    if (v<0) { console_putc('-'); v=-v; }
    do { buf[i++]='0'+(v%10); v/=10; } while(v && i<15);
    while(i) console_putc(buf[--i]);
    console_write(",");
    i=0; v=py;
    if (v<0) { console_putc('-'); v=-v; }
    do { buf[i++]='0'+(v%10); v/=10; } while(v && i<15);
    while(i) console_putc(buf[--i]);
    console_write("\n");
}
EOF