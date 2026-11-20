#include "install.h"
#include "../../types.h"
#include "../../console/console.h"
#include "../../drivers/block/block.h"

void install_init(void) {}
int install_run(void) {
    console_write("Zetomir Installer\n");
    console_write("1. Partition disk\n");
    console_write("2. Format ZetoFS\n");
    console_write("3. Copy kernel\n");
    console_write("4. Install bootloader\n");
    console_write("Installation complete (simulated).\n");
    return 0;
}
EOF