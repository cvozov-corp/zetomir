#include "zvm.h"
#include "../types.h"
#include "../console/console.h"

static int starts(const char *s, const char *pref) {
    while (*pref) { if (*s++ != *pref++) return 0; }
    return 1;
}

static void run_line(const char *line) {
    if (starts(line, "say ")) {
        console_write(line + 4);
        console_write("\n");
    }
}

int zvm_run(const char *src) {
    console_write("ZVM: executing\n");
    const char *p = src;
    char line[256]; int li = 0;
    while (*p) {
        if (*p == '\n') {
            line[li] = 0; li = 0;
            run_line(line);
        } else if (li < 255) {
            line[li++] = *p;
        }
        p++;
    }
    if (li) { line[li]=0; run_line(line); }
    return 0;
}
EOF