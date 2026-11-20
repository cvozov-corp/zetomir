#include "net.h"
#include "../../types.h"
#include "../../arch/x86_64/cpu.h"

static u8 mac[6] = {0x52,0x54,0x00,0x12,0x34,0x56};
static u32 ip = 0x0A000002;

typedef struct {
    u8 dst[6]; u8 src[6]; u16 ethertype;
} eth_hdr_t;

typedef struct {
    u16 hwtype, proto; u8 hwlen, protolen; u16 op;
    u8 sha[6]; u32 spa; u8 tha[6]; u32 tpa;
} arp_pkt_t;

void net_init(void) {}

int net_send(const void *buf, usize len) {
    UNUSED(buf); UNUSED(len);
    return (int)len;
}

void net_poll(void) {
    /* poll NIC (stub) */
}

/* ARP reply handler */
void net_handle_arp(const u8 *pkt) {
    const arp_pkt_t *a = (const arp_pkt_t*)pkt;
    if (a->op == 0x0100) { /* request */
        /* build reply (stub) */
    }
}
EOF