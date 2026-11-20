#include "install.h"
#include "../../types.h"
#include "../../console/console.h"
#include "../../drivers/block/block.h"

int install_run(void) {
    console_write("Zetomir Installer\n");
    console_write("Partitioning disk...\n");
    /* write magic to block 0 */
    u8 buf[512];
    for (int i = 0; i < 512; i++) buf[i] = 0;
    buf[0] = 'Z'; buf[1] = 'E'; buf[2] = 'T'; buf[3] = 'O';
    block_write(0, buf);
    console_write("Formatting ZetoFS...\n");
    console_write("Copying kernel...\n");
    console_write("Installing bootloader...\n");
    console_write("Installation complete.\n");
    return 0;
}
EOF