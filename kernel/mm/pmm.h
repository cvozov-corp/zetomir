#ifndef ZETOMIR_PMM_H
#define ZETOMIR_PMM_H
#include "../types.h"
void pmm_init(u64 total_bytes);
void *pmm_alloc_page(void);
void pmm_free_page(void *p);
#endif
