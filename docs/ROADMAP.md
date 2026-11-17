# План разработки Zetomir OS

- [x] Этап 1: x86_64 ELF kernel, Limine BIOS entry, framebuffer, serial log, memory-map readout.
- [x] Этап 2a: ZETOMIR 0.1 host bootstrap, `.zeto` game script, automated syntax tests.
- [ ] Этап 2b: GDT/TSS, IDT, CPU exceptions, PIC/IRQ, PIT.
- [ ] Этап 3: PS/2 keyboard, input queue, interactive kernel terminal.
- [ ] Этап 4: physical/virtual memory allocators and kernel heap.
- [ ] Этап 5: block device driver and ZetoFS.
- [ ] Этап 6: VFS, process model, scheduler, ring 3, syscalls.
- [ ] Этап 7: native ZVM bytecode runtime + compiler in C.
- [ ] Этап 8: ZetoShell and app launcher; Murino runs as a ZETOMIR application.
- [ ] Этап 9: graphical desktop, window manager, input stack, audio.
- [ ] Этап 10: package manager, installer, reproducible distribution ISO.

A checked item means source exists and its stated tests pass; it does not imply the whole OS is feature-complete.
