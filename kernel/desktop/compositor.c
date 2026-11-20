#include "compositor.h"
#include "../../types.h"
#include "../../drivers/framebuffer.h"

typedef struct window {
    int x, y, w, h;
    u32 bg;
    int visible;
} window_t;

static window_t windows[16];
static int nwin = 0;

void compositor_init(void) { nwin = 0; }

int compositor_create_window(int x, int y, int w, int h, u32 bg) {
    if (nwin >= 16) return -1;
    windows[nwin].x=x; windows[nwin].y=y; windows[nwin].w=w; windows[nwin].h=h; windows[nwin].bg=bg; windows[nwin].visible=1;
    return nwin++;
}

void compositor_paint(void) {
    fb_clear(0x000B1220u);
    for (int i = 0; i < nwin; i++) {
        if (!windows[i].visible) continue;
        fb_rect(windows[i].x, windows[i].y, windows[i].w, windows[i].h, windows[i].bg);
    }
}

void compositor_move(int id, int x, int y) {
    if (id < 0 || id >= nwin) return;
    windows[id].x = x; windows[id].y = y;
}
EOF