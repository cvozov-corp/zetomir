#include "acpi.h"
#include "../../types.h"

static int memcheck(const void *p, const char *sig, int len) {
    const char *s = (const char*)p;
    for (int i = 0; i < len; i++) if (s[i] != sig[i]) return 0;
    return 1;
}

u64 acpi_find_rsdp(void) {
    /* search EBDA and BIOS area */
    for (u64 addr = 0x80000; addr < 0x100000; addr += 16) {
        if (memcheck((void*)addr, "RSD PTR ", 8)) return addr;
    }
    return 0;
}
EOF