#include "settings.h"
#include "../../types.h"
#include "../../console/console.h"

static int brightness = 100;
static int volume = 50;

void settings_init(void) {}
void settings_set_brightness(int v) { if (v<0) v=0; if (v>100) v=100; brightness=v; }
void settings_set_volume(int v) { if (v<0) v=0; if (v>100) v=100; volume=v; }
void settings_show(void) {
    console_write("Brightness: "); /* print */
    console_write("\nVolume: ");
    console_write("\n");
}
EOF