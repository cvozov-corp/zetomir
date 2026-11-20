#include "usb.h"
#include "../../types.h"
#include "../../arch/x86_64/cpu.h"

static inline void outl(u16 p, u32 v){ __asm__ volatile("outl %0,%1"::"a"(v),"Nd"(p)); }
static inline u32 inl(u16 p){ u32 v; __asm__ volatile("inl %1,%0":"=a"(v):"Nd"(p)); return v; }

u32 pci_config_read(u8 bus, u8 slot, u8 func, u8 off) {
    u32 addr = (1u<<31) | ((u32)bus<<16) | ((u32)slot<<11) | ((u32)func<<8) | (off & 0xFC);
    outl(0xCF8, addr);
    return inl(0xCFC);
}

void usb_init(void) {
    for (u16 bus = 0; bus < 256; bus++)
        for (u8 slot = 0; slot < 32; slot++) {
            u32 v = pci_config_read(bus, slot, 0, 0);
            if (v == 0xFFFFFFFF) continue;
            u32 reg = pci_config_read(bus, slot, 0, 0x08);
            u32 cls = reg >> 24;
            u32 sub = (reg >> 16) & 0xFF;
            u32 prog = (reg >> 8) & 0xFF;
            if (cls == 0x0C && sub == 0x03 && prog == 0x30) {
                /* xHCI found */
            }
        }
}
EOF