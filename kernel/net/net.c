#include "net.h"
#include "../../types.h"
#include "../../arch/x86_64/cpu.h"

static u8 mac[6] = {0x52,0x54,0x00,0x12,0x34,0x56};
static u32 ip = 0x0A000002; /* 10.0.0.2 */

void net_init(void) {
    /* reset NIC (e1000 stub) */
}

int net_send(const void *buf, usize len) {
    UNUSED(buf); UNUSED(len);
    return 0;
}

void net_poll(void) {
    /* poll for packets (stub) */
}
EOF