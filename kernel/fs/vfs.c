#include "vfs.h"
#include "../types.h"

typedef struct { const char *name; const char *data; } vfs_file_t;
static vfs_file_t files[] = {
    { "readme.txt", "Zetomir OS in-memory VFS\n" },
    { "version", "0.2-dev\n" },
};
static int nfiles = 2;

void vfs_init(void) {}

int vfs_ls(char *out, int max) {
    int pos = 0;
    for (int i = 0; i < nfiles && pos < max - 1; i++) {
        const char *n = files[i].name;
        while (*n && pos < max - 1) out[pos++] = *n++;
        out[pos++] = '\n';
    }
    out[pos] = 0;
    return pos;
}
