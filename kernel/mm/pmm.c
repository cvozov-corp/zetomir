#include "pmm.h"
#include "../types.h"

#define PMM_MAX_PAGES (1<<16)
static u8 bitmap[PMM_MAX_PAGES/8];
static u64 total_pages = 0;

void pmm_init(u64 total_bytes) {
    total_pages = total_bytes / 4096;
    if (total_pages > PMM_MAX_PAGES) total_pages = PMM_MAX_PAGES;
    for (u64 i = 0; i < sizeof(bitmap); i++) bitmap[i] = 0;
}

void *pmm_alloc_page(void) {
    for (u64 i = 0; i < total_pages; i++) {
        if (!(bitmap[i/8] & (1 << (i%8)))) {
            bitmap[i/8] |= (1 << (i%8));
            return (void*)(i * 4096 + 0x100000);
        }
    }
    return NULL;
}

void pmm_free_page(void *p) {
    u64 idx = ((u64)p - 0x100000) / 4096;
    if (idx < total_pages) bitmap[idx/8] &= ~(1 << (idx%8));
}
