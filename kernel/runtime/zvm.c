#include "zvm.h"
#include "../types.h"
#include "../console/console.h"
void zvm_init(void) {}
int zvm_run(const char *src) {
    console_write("ZVM: running script (host bootstrap parity pending)\n");
    console_write(src);
    console_write("\n");
    return 0;
}
