#include "vmm.h"
#include "../../types.h"
#include "../../arch/x86_64/cpu.h"

#define PTE_PRESENT (1ULL<<0)
#define PTE_WRITABLE (1ULL<<1)
#define PTE_HUGE (1ULL<<7)

static u64 pml4[512] __attribute__((aligned(4096)));
static u64 pdpt[512] __attribute__((aligned(4096)));
static u64 pd[512] __attribute__((aligned(4096)));

void vmm_init(void) {
    for (int i = 0; i < 512; i++) { pml4[i]=0; pdpt[i]=0; pd[i]=0; }
    /* identity map first 1GB with 2MB pages */
    pml4[0] = (u64)pdpt | PTE_PRESENT | PTE_WRITABLE;
    pdpt[0] = (u64)pd | PTE_PRESENT | PTE_WRITABLE;
    for (int i = 0; i < 512; i++) {
        pd[i] = (i * 0x200000ULL) | PTE_PRESENT | PTE_WRITABLE | PTE_HUGE;
    }
    __asm__ volatile ("mov %0, %%cr3" :: "r"((u64)pml4) : "memory");
}
EOF