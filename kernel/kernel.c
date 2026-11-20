#include "types.h"
#include "arch/x86_64/cpu.h"
#include "arch/x86_64/gdt.h"
#include "arch/x86_64/idt.h"
#include "drivers/serial.h"
#include "drivers/framebuffer.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"
#include "drivers/mouse.h"
#include "desktop/wm.h"
#include "desktop/desktop.h"
#include "runtime/zvm.h"
#include "games/murino.h"
#include "console/console.h"
#include "mm/memory.h"
#include "mm/pmm.h"
#include "fs/vfs.h"
#include "process/sched.h"
#include "loader/elf.h"

#define LIMINE_BASE_REVISION(N) { 0xf9562b2d5c95a6c8, 0x6a7b384944536bdc, (N) }
#define LIMINE_FRAMEBUFFER_REQUEST_ID { 0x9d5827dcd881dd75, 0xa3148604f6fab11b }

struct limine_framebuffer {
    void *address; u64 width; u64 height; u64 pitch; u16 bpp; u8 memory_model;
    u8 red_mask_size; u8 red_mask_shift; u8 green_mask_size; u8 green_mask_shift;
    u8 blue_mask_size; u8 blue_mask_shift; u8 unused[7]; u64 edid_size; void *edid;
    u64 mode_count; void *modes;
};
struct limine_framebuffer_response {
    u64 revision; u64 framebuffer_count; struct limine_framebuffer **framebuffers;
};
struct limine_framebuffer_request {
    u64 id[2]; u64 revision; struct limine_framebuffer_response *response;
};
__attribute__((used, section(".limine_requests_start")))
static volatile u64 req_start[2] = {0xf6b8f4b39de7d1ae,0xfab91a6940fcb9cf};
__attribute__((used, section(".limine_requests")))
static volatile u64 base_revision[3] = LIMINE_BASE_REVISION(3);
__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request fb_request = {
    LIMINE_FRAMEBUFFER_REQUEST_ID, 0, 0
};
__attribute__((used, section(".limine_requests_end")))
static volatile u64 req_end[2] = {0xadc0e0531bb10d03,0x9572709f31764c62};

static void gui_draw(void) {
    fb_clear(0x00101620u);
    fb_rect(0,0,1280,54,0x00192330u);
    fb_rect(18,72,220,620,0x00192330u);
    fb_rect(254,72,1008,620,0x00192330u);
    fb_rect(18,72,220,4,0x0057D6A0u);
    fb_rect(254,72,1008,4,0x0057D6A0u);
    fb_text(28,19,"ZETOMIR OS",0x0057D6A0u,3);
    fb_text(1070,22,"KERNEL 0.1",0x00E6EDF3u,1);
    fb_text(38,100,"SYSTEM",0x0057D6A0u,2);
    fb_text(38,140,"OVERVIEW",0x00E6EDF3u,1);
    fb_text(38,176,"CONSOLE",0x00E6EDF3u,1);
    fb_text(38,212,"MEMORY",0x00E6EDF3u,1);
    fb_text(38,248,"DRIVERS",0x00E6EDF3u,1);
    fb_text(278,92,"ZETOMIR TERMINAL",0x0057D6A0u,2);
    fb_text(278,660,"BIOS BOOT  |  X86_64",0x00899AA8u,1);
}
static void print_memory(void) {
    u64 mb=memory_total_bytes()/(1024*1024);
    char buf[24]; int n=0;
    if (!mb) { console_write("Memory map: unavailable\n"); return; }
    do { buf[n++]=(char)('0'+(mb%10)); mb/=10; } while(mb && n<20);
    console_write("Usable memory: ");
    while(n) console_putc(buf[--n]);
    console_write(" MB\n");
}
static int starts_with(const char *a, const char *b) {
    while (*b) { if (*a++ != *b++) return 0; }
    return 1;
}
static int streq(const char *a, const char *b) {
    while (*a && *b && *a == *b) { a++; b++; }
    return *a == *b;
}
void _start(void) {
    serial_init();
    serial_write("\r\nZetomir OS booting...\r\n");
    struct limine_framebuffer_response *r=fb_request.response;
    if (r && r->framebuffer_count) {
        struct limine_framebuffer *f=r->framebuffers[0];
        fb_init(f->address,f->width,f->height,f->pitch,f->bpp);
    }
    if (fb_ready()) gui_draw();
    console_init();
    gdt_init();
    idt_init();
    cpu_init();
    memory_init();
    pmm_init(memory_total_bytes());
    keyboard_init();
    timer_init(100);
    mouse_init();
    vfs_init();
    sched_init();
    wm_init();
    desktop_init();
    zvm_init();
    murino_init();
    console_write("Zetomir OS kernel 0.1\n");
    console_write("64-bit x86_64 BIOS boot\n");
    console_write("Framebuffer: ");
    console_write(fb_ready() ? "available\n" : "unavailable (serial console active)\n");
    print_memory();
    console_write("\nSystem initialization complete.\n");
    console_write("This is the first bootable development milestone.\n");
    console_write("Keyboard input and storage drivers are scheduled next.\n");
    console_write("\nroot@zetomir:/$ ");
    char buf[128]; int bi = 0;
    static int cx = 640, cy = 360;
    for (;;) {
        char c = keyboard_read();
        if (c) {
            if (c == '\\n') {
                buf[bi] = 0;
                if (!streq(buf, "help")) console_write("Commands: help ls mem clear\n");
                else if (!streq(buf, "ls")) { char out[256]; vfs_ls(out, 256); console_write(out); }
                else if (!streq(buf, "mem")) print_memory();
                else if (!streq(buf, "clear")) { gui_draw(); desktop_paint(); }
                else if (starts_with(buf, "cat ")) { char out[256]; vfs_read(buf+4, out, 256); console_write(out); }
                else if (streq(buf, "zfetch")) {
                    console_write("Zetomir OS 0.2-dev\n");
                    console_write("Kernel: x86_64 freestanding\n");
                    console_write("Boot: Limine BIOS\n");
                    console_write("Shell: zetoshell\n");
                }
                else if (bi) console_write("unknown command\n");
                bi = 0;
                console_write("root@zetomir:/$ ");
            } else if (c == 8 && bi > 0) {
                bi--; console_write("\\b \\b");
            } else if (bi < 127 && c >= 32) {
                buf[bi++] = c; console_putc(c);
            }
        }
        int dx,dy,btn;
        if (mouse_read(&dx,&dy,&btn)) { cx += dx; cy -= dy; wm_move_cursor(cx,cy); }
        wm_paint();
        cpu_halt();
    }
}
