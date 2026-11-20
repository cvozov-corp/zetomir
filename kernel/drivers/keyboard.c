#include "keyboard.h"
#include "../types.h"
#include "../../arch/x86_64/cpu.h"

void keyboard_init(void) {
    while (inb(0x64) & 0x02) {}
    outb(0x64, 0xAE);
}

char keyboard_read(void) {
    if (!(inb(0x64) & 0x01)) return 0;
    u8 sc = inb(0x60);
    if (sc & 0x80) return 0;
    static const char map[128] = {
        0,27,'1','2','3','4','5','6','7','8','9','0','-','=',8,
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
        'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\',
        'z','x','c','v','b','n','m',',','.','/',0,'*',0,' '
    };
    if (sc < 128) return map[sc];
    return 0;
}
