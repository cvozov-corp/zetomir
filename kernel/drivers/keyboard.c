#include "keyboard.h"
#include "../../types.h"
#include "../../arch/x86_64/cpu.h"
#include "../../drivers/serial.h"

#define KBD_BUF_SIZE 256
static u8 kbd_buf[KBD_BUF_SIZE];
static int kbd_head = 0, kbd_tail = 0;

static irq_handler_t kbd_irq1_handler;

void kbd_irq1(void) {
    u8 sc = inb(0x60);
    if (kbd_head < KBD_BUF_SIZE) {
        kbd_buf[kbd_head++ & (KBD_BUF_SIZE-1)] = sc;
    }
    outb(0x20, 0x20); /* EOI PIC */
}

void keyboard_init(void) {
    /* enable IRQ1 */
    outb(0x21, inb(0x21) & ~0x02);
    /* register IRQ1 handler (stub: just mark as registered) */
    kbd_irq1_handler = kbd_irq1;
    /* install via IDT (simplified) */
    /* in real code: set IDT entry for IRQ1 */
}

/* called from kernel interrupt stub */
void keyboard_poll(void) {
    while (kbd_tail != kbd_head) {
        u8 sc = kbd_buf[kbd_tail++ & (KBD_BUF_SIZE-1)];
        /* simple translate: 0x1C = Enter, 0x2A = Left Shift, etc. */
        /* for now just discard or echo via serial */
        serial_putc(sc);
    }
}
EOF