#include "mouse.h"
#include "../types.h"
#include "../../arch/x86_64/cpu.h"
void mouse_init(void) {
    outb(0x64, 0xA8);
    outb(0x64, 0xD4);
    outb(0x60, 0xF4);
}
int mouse_read(int *dx, int *dy, int *buttons) {
    if (!(inb(0x64) & 0x01)) return 0;
    *buttons = inb(0x60);
    *dx = (signed char)inb(0x60);
    *dy = (signed char)inb(0x60);
    return 1;
}
