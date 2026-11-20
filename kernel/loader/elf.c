#include "elf.h"
#include "../../types.h"
#include "../../mm/vmm/vmm.h"

typedef struct {
    unsigned char e_ident[16];
    u16 e_type, e_machine;
    u32 e_version;
    u64 e_entry, e_phoff, e_shoff;
    u32 e_flags;
    u16 e_ehsize, e_phentsize, e_phnum, e_shentsize, e_shnum, e_shstrndx;
} elf64_ehdr_t;

typedef struct {
    u32 p_type, p_flags;
    u64 p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_align;
} elf64_phdr_t;

#define PT_LOAD 1

int elf_load(const void *image, u64 size) {
    const elf64_ehdr_t *eh = (const elf64_ehdr_t*)image;
    if (eh->e_ident[0] != 0x7F || eh->e_ident[1] != 'E' || eh->e_ident[2] != 'L' || eh->e_ident[3] != 'F') return -1;
    if (eh->e_machine != 0x3E) return -1; /* x86-64 */
    const elf64_phdr_t *ph = (const elf64_phdr_t*)((const u8*)image + eh->e_phoff);
    for (int i = 0; i < eh->e_phnum; i++) {
        if (ph[i].p_type == PT_LOAD) {
            const u8 *src = (const u8*)image + ph[i].p_offset;
            u8 *dst = (u8*)ph[i].p_vaddr;
            for (u64 j = 0; j < ph[i].p_filesz; j++) dst[j] = src[j];
            for (u64 j = ph[i].p_filesz; j < ph[i].p_memsz; j++) dst[j] = 0;
        }
    }
    UNUSED(size);
    return 0;
}
EOF