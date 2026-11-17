#include "memory.h"
#include "../drivers/serial.h"
#define LIMINE_MEMMAP_REQUEST_ID { 0x67cf3d9d378a806f, 0xe304acdfc50c3c62 }
struct limine_memmap_entry { u64 base; u64 length; u64 type; };
struct limine_memmap_response { u64 revision; u64 entry_count; struct limine_memmap_entry **entries; };
struct limine_memmap_request {
    u64 id[2]; u64 revision; struct limine_memmap_response *response;
};
__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request memmap_request = {
    LIMINE_MEMMAP_REQUEST_ID, 0, 0
};
static u64 total;
void memory_init(void) {
    struct limine_memmap_response *r = memmap_request.response;
    total=0;
    if (!r) { serial_write("MM: memory map unavailable\r\n"); return; }
    for (u64 i=0; i<r->entry_count; ++i) {
        struct limine_memmap_entry *e=r->entries[i];
        if (e->type == 0) total += e->length;
    }
    serial_write("MM: usable memory map parsed\r\n");
}
u64 memory_total_bytes(void) { return total; }
