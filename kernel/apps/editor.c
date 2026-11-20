#include "editor.h"
#include "../../types.h"
#include "../../console/console.h"
#include "../../fs/vfs.h"

static char editbuf[512];
static int editpos = 0;

void editor_init(void) { editpos = 0; editbuf[0] = 0; }

void editor_open(const char *name) {
    char tmp[256];
    vfs_read(name, tmp, 256);
    int i = 0;
    while (tmp[i] && i < 511) { editbuf[i] = tmp[i]; i++; }
    editbuf[i] = 0;
    editpos = i;
}

void editor_insert(char c) {
    if (editpos < 511 && c >= 32 && c < 127) {
        editbuf[editpos++] = c;
        editbuf[editpos] = 0;
        console_putc(c);
    }
}

void editor_save(const char *name) {
    vfs_write(name, editbuf, editpos);
    console_write("saved: ");
    console_write(name);
    console_write("\n");
}
EOF