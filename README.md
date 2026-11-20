# ZETOMIR OS — отечественная житомирская операционная система

**ZETOMIR OS** — самостоятельная 64-битная ОС для x86_64. Ядро, графическая среда, оболочка, ФС, сеть, приложения, язык ZETOMIR.

## Реализовано

- Ядро: serial, framebuffer, console, память, GDT/IDT, PMM, VMM, heap.
- Драйверы: keyboard, mouse, timer, block (ramdisk), audio (PC speaker), ACPI RSDP search, SMP init.
- VFS + ZetoFS, shell (help, ls, cat, mem, clear, zfetch).
- ZVM (let, say), Murino engine, CvoZov game.
- Package manager, installer (запись magic).
- Syscall entry/dispatch.
- Host: ZetoBrowse, ZetoFetch.

## Сборка

```bash
make all && make iso && make run
```

## Структура

См. docs/INDEX.md.

## Ограничения

Многие подсистемы минимальны; требуется toolchain и QEMU для проверки.
