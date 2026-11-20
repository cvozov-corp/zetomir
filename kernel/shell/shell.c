#include "shell.h"
#include "../types.h"
#include "../console/console.h"
#include "../fs/vfs.h"
#include "../drivers/keyboard.h"
#include "../apps/reboot.h"

static int starts_with(const char *a, const char *b) {
    while (*b) { if (*a++ != *b++) return 0; }
    return 1;
}
static int streq(const char *a, const char *b) {
    while (*a && *b && *a == *b) { a++; b++; }
    return *a == *b;
}

static void print_mem(void) {
    /* informational */
}

void shell_run(void) {
    char buf[128]; int bi = 0;
    console_write("root@zetomir:/$ ");
    for (;;) {
        char c = keyboard_read();
        if (c) {
            if (c == '\n') {
                buf[bi] = 0;
                if (streq(buf, "help")) console_write("Commands: help ls cat mem clear zfetch reboot shutdown\n");
                else if (streq(buf, "ls")) { char out[256]; vfs_ls(out, 256); console_write(out); }
                else if (streq(buf, "mem")) print_mem();
                else if (streq(buf, "clear")) { }
                else if (streq(buf, "zfetch")) {
                    console_write("Zetomir OS 0.2-dev\n");
                    console_write("Kernel: x86_64 freestanding\n");
                    console_write("Boot: Limine BIOS\n");
                }
                else if (starts_with(buf, "cat ")) { char out[256]; vfs_read(buf+4, out, 256); console_write(out); }
                else if (streq(buf, "reboot")) reboot();
                else if (streq(buf, "shutdown")) shutdown();
                else if (bi) console_write("unknown command\n");
                bi = 0;
                console_write("root@zetomir:/$ ");
            } else if (c == 8 && bi > 0) {
                bi--; console_write("\b \b");
            } else if (bi < 127 && c >= 32) {
                buf[bi++] = c; console_putc(c);
            }
        }
        cpu_halt();
    }
}
EOF