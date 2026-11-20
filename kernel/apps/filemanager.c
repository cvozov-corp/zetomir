#include "filemanager.h"
#include "../../types.h"
#include "../../console/console.h"
#include "../../fs/vfs.h"

void filemanager_init(void) {}
void filemanager_list(void) {
    char out[256];
    vfs_ls(out, 256);
    console_write(out);
}
EOF