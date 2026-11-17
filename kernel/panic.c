#include "types.h"
#include "arch/x86_64/cpu.h"
#include "drivers/serial.h"
#include "drivers/framebuffer.h"
void panic(const char *message) {
    cpu_cli();
    serial_write("\r\n*** ZETOMIR KERNEL PANIC ***\r\n");
    serial_write(message);
    serial_write("\r\nSystem halted.\r\n");
    if (fb_ready()) {
        fb_rect(0,0,1280,64,0x00800000u);
        fb_text(24,20,"KERNEL PANIC",0x00FFFFFFu,3);
    }
    for (;;) cpu_halt();
}
