#include "smp.h"
#include "../../types.h"
#include "../../arch/x86_64/cpu.h"

void smp_init(void) {
    /* INIT IPI to APs (stubbed sequence) */
    outb(0x20, 0x20); /* EOI */
}
EOF