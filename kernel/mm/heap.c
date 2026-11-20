#include "heap.h"
#include "../types.h"
#define HEAP_SIZE (1024*1024)
static char heap[HEAP_SIZE];
static usize heap_pos = 0;
void *kmalloc(usize size) {
    if (heap_pos + size > HEAP_SIZE) return NULL;
    void *p = &heap[heap_pos];
    heap_pos = (heap_pos + size + 15) & ~15;
    return p;
}
void kfree(void *p) { UNUSED(p); }
EOF