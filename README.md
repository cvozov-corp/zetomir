# Zetomir OS 0.1

Первый загрузочный фундамент Zetomir: 64-битное freestanding-ядро,
BIOS-загрузка через Limine, framebuffer UI и serial-консоль.

> Это первый собираемый этап, а не законченная ОС. На этом этапе ещё нет
> IDT/IRQ, драйвера клавиатуры, дискового драйвера, планировщика и ZetoFS.

## Документация по платформам

- [Arch Linux](docs/platforms/ARCH-LINUX.md) — установка инструментов, сборка и запуск.
- [Приложения](docs/APPS.md) — ZetoBrowse и ZetoFetch, их возможности и ограничения.
- [Язык ZETOMIR](docs/ZETOMIR-LANGUAGE.md).
- [Дорожная карта](docs/ROADMAP.md).

## Требования (Debian/Ubuntu)

```sh
sudo apt update
sudo apt install build-essential git xorriso qemu-system-x86
```

Нужен кросс-компилятор `x86_64-elf-gcc` и `x86_64-elf-ld`.
Его можно собрать по руководству OSDev GCC Cross Compiler:
https://wiki.osdev.org/GCC_Cross-Compiler

Проверка:

```sh
x86_64-elf-gcc --version
x86_64-elf-ld --version
qemu-system-x86_64 --version
```

## Сборка

В корне проекта:

```sh
make
make iso
```

Цель `iso` автоматически клонирует и собирает Limine ветки `v9.x-binary`,
если каталога `limine/` ещё нет. Для повторяемой сборки в дальнейшем
зафиксируйте конкретный commit Limine.

## Запуск

```sh
make run
```

Ожидаемый результат:
- QEMU стартует с BIOS-прошивкой по умолчанию.
- Limine загружает `kernel.elf`.
- При наличии совместимого 32-bpp framebuffer рисуется графическая панель.
- В окне терминала, откуда запущен QEMU, отображается serial-консоль.

Для отладки:

```sh
make debug
```

QEMU ждёт GDB на TCP-порту 1234. В другом терминале:

```sh
gdb build/kernel.elf
(gdb) target remote :1234
(gdb) continue
```

## Проверки

```sh
file build/kernel.elf
readelf -h build/kernel.elf
grub-file --is-x86-multiboot2 build/kernel.elf
```

Последняя команда не является проверкой Limine: это ядро использует
протокол Limine, а не Multiboot2. Проверяйте ELF через `readelf`.

## Текущие ограничения

- Серийная консоль COM1 и графический framebuffer.
- Вывод текста использует встроенный минимальный bitmap-шрифт.
- Нет обработки клавиатуры и мыши.
- Нет IDT/исключений/IRQ и PIT.
- Парсится карта памяти Limine; физический аллокатор пока не выделяет страницы.
- Нет paging manager, heap, процессов, syscall и файловой системы.
- Текстовый терминал на этом этапе выводит сообщения, но ещё не принимает команды.

## План следующих этапов

1. GDT/TSS, IDT, исключения, PIC/APIC, PIT и PS/2 keyboard.
2. PMM, VMM, heap и защита памяти.
3. ATA/AHCI и собственная файловая система ZetoFS.
4. VFS, initrd, каталоги, файлы и права.
5. Планировщик, потоки, ring 3 и системные вызовы.
6. ELF loader, libc и ZetoShell.
7. Графическая подсистема, ввод мыши и оконный менеджер.
8. Установщик, менеджер пакетов и дистрибутив Zetomir.
