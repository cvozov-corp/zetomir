# ZETOMIR OS — отечественная житомирская операционная система

**ZETOMIR OS** — самостоятельная 64-битная операционная система для компьютеров x86_64. Цель проекта — собственное ядро, графическая среда, командная оболочка, файловая система, сеть, системные приложения и язык программирования ZETOMIR.

> Статус: ранний development-прототип. Многие подсистемы реализованы как заглушки и требуют доработки и проверки.

## Возможности (текущие)

- Freestanding x86_64 ELF-ядро, точка входа `_start`.
- Загрузка через Limine (BIOS).
- Framebuffer: очистка, прямоугольники, bitmap-текст.
- COM1 serial-диагностика.
- Чтение карты памяти Limine.
- GDT/IDT, PMM, таймер PIT.
- Клавиатура PS/2 и мышь.
- VFS (in-memory) и команды shell: help, ls, cat, mem, clear, zfetch.
- Планировщик (заглушка), ELF loader (заглушка).
- Рабочий стол и оконный менеджер (базовые).
- ZVM — интерпретатор языка ZETOMIR (let, say).
- Движок Murino и игра CvoZov.
- Host-утилиты: ZetoBrowse, ZetoFetch.
- Язык ZETOMIR (host bootstrap).

## Сборка и запуск

```bash
make all        # сборка ядра
make iso        # сборка ISO
make run        # запуск в QEMU
make test       # Python-тесты
make zeto-check # проверка языка
```

Требования: `x86_64-elf-gcc`, `nasm`, `qemu-system-x86_64`, `xorriso`, `limine`.

## Структура проекта

```
zetomir-os/
├── kernel/          # ядро
│   ├── arch/x86_64/ # GDT, IDT, CPU
│   ├── console/     # консоль
│   ├── drivers/     # serial, framebuffer, keyboard, mouse, timer, block
│   ├── mm/          # память, PMM
│   ├── fs/          # VFS
│   ├── process/     # планировщик
│   ├── loader/      # ELF loader
│   ├── desktop/     # рабочий стол, WM
│   ├── runtime/     # ZVM
│   ├── games/       # Murino engine
│   ├── net/ audio/  # заглушки
│   └── installer/   # заглушка
├── apps/            # host-утилиты
├── boot/            # конфиг Limine
├── docs/            # документация
├── games/           # игры (.zeto)
├── language/        # ZETOMIR
├── tests/           # тесты
└── tools/           # инструменты
```

## Цели проекта

- x86_64-ядро на C и Assembly.
- BIOS и UEFI через Limine.
- Запуск в QEMU и VirtualBox, затем на реальном оборудовании.
- Клавиатура, мышь, таймеры, прерывания, управление памятью.
- Накопители, разделы, VFS и собственная файловая система ZetoFS.
- Процессы, потоки, системные вызовы, пользовательские приложения.
- Графический рабочий стол и интерактивный ZetoShell.
- Язык ZETOMIR, байткод и ZVM.
- Сеть, браузер, системные утилиты, установщик, Live ISO.

## Ограничения

- ZetoBrowse, ZetoFetch и `language/zeto.py` работают на Linux-хосте, а не в ядре.
- Панель ядра — статическая графика, кнопки не интерактивны.
- `memory_init()` читает карту памяти, но не выделяет страницы (PMM — отдельный модуль).
- Нет драйверов дисков, ФС, сети, процессов в полном виде.
- Наличие `make iso` не гарантирует успешную загрузку.

## Документация

См. `docs/INDEX.md`.
