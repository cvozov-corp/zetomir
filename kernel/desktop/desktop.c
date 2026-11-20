#include "desktop.h"
#include "../types.h"
#include "../drivers/framebuffer.h"
void desktop_init(void) {}
void desktop_paint(void) {
    fb_clear(0x000B1220u);
    fb_rect(0,0,1280,48,0x00141E30u);
    fb_text(20,14,"ZETOMIR OS",0x0057D6A0u,2);
    fb_rect(0,680,1280,40,0x00141E30u);
    fb_text(20,692,"Taskbar",0x00E6EDF3u,1);
}
