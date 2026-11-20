# ZETOMIR OS

Собственная 64-битная ОС для x86_64. Ядро freestanding ELF, загрузка через Limine, framebuffer, serial, карта памяти, GDT/IDT, PMM, таймер, клавиатура, мышь, VFS, планировщик, ELF loader, рабочий стол, ZVM, движок Murino.

## Сборка

```bash
make all
make iso
make run
```

## Тесты

```bash
make test
make zeto-check
```

## Структура

- `kernel/` — ядро (arch, drivers, console, mm, fs, process, loader, desktop, runtime, games)
- `apps/` — host-утилиты (ZetoBrowse, ZetoFetch)
- `language/` — ZETOMIR (host bootstrap)
- `games/` — Murino
- `docs/` — документация
- `tests/` — тесты

## Статус

Ранний прототип. Многие подсистемы — заглушки, требующие реализации и проверки.
