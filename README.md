# ZETOMIR OS - отечественная житомирская операционная система 

**ZETOMIR OS** — проект самостоятельной 64-битной операционной системы для компьютеров x86_64. Цель — собственное ядро, графическая среда, командная оболочка, файловая система, сеть, системные приложения и язык программирования ZETOMIR.

> **Текущий статус: ранний development-прототип.** В исходниках есть freestanding x86_64 ELF-ядро, загрузочная конфигурация Limine для BIOS, базовый framebuffer, COM1 serial, чтение карты памяти Limine и host-инструменты на Python. Это ещё не полноценная операционная система. Клавиатура, мышь, диски, файловая система, сеть, процессы и интерактивный GUI пока не реализованы.

## Цели проекта

- x86_64-ядро на C и Assembly.
- BIOS и UEFI через Limine (каждый режим должен быть отдельно проверен).
- Запуск в QEMU и VirtualBox, затем на реальном совместимом оборудовании.
- Клавиатура, мышь, таймеры, прерывания и управление памятью.
- Накопители, разделы, VFS и собственная файловая система ZetoFS.
- Процессы, потоки, системные вызовы и пользовательские приложения.
- Графический рабочий стол и интерактивный ZetoShell.
- Язык ZETOMIR, байткод и виртуальная машина ZVM.
- Сеть, браузер, системные утилиты, установщик и Live ISO.

Функция считается готовой только после реализации и проверки. Упоминание в целях или дорожной карте не означает, что она уже работает.

## Текущее состояние исходников

| Компонент | Что есть сейчас | Чего пока нет |
|---|---|---|
| x86_64 kernel | Freestanding ELF, `_start`, базовая инициализация | Полноценные CPU tables, scheduler, syscalls |
| Boot | Конфигурация Limine BIOS | Проверенная UEFI-конфигурация и матрица загрузки |
| Framebuffer | Базовая инициализация, очистка, прямоугольники, bitmap-текст | Полноценный графический backend и оконный менеджер |
| Serial | COM1 diagnostic output | Более развитая система логирования |
| Memory | Чтение карты памяти Limine и подсчёт usable memory | PMM, VMM, heap и освобождение памяти |
| Console | Вывод символов в framebuffer/serial | Ввод с клавиатуры, редактирование строки, история команд |
| Panic | Базовый panic output и остановка CPU | Полный dump регистров и диагностическая трассировка |
| ZETOMIR | Python host-bootstrap для `.zeto` | Собственные lexer/parser, bytecode и ZVM |
| ZetoBrowse | Текстовый HTTP/HTTPS host-прототип | Нативный браузер внутри ОС, JS/CSS и GUI |
| ZetoFetch | Linux host-утилита в стиле fastfetch | Нативная информация о Zetomir kernel |
| Murino | Текстовая игра `.zeto` | Нативный запуск внутри Zetomir OS |
| Tests | Python unit tests для языка и host-приложений | Kernel tests, boot tests и hardware test suite |

### Важные ограничения

- ZetoBrowse, ZetoFetch и `language/zeto.py` сейчас запускаются на Linux-хосте с Python 3, а не внутри ядра Zetomir.
- Панель, нарисованная ядром, является статической графикой. Кнопки и меню не интерактивны.
- Надпись `root@zetomir:/$` — приглашение, выведенное как текст, а не работающая оболочка.
- Функция `memory_init()` читает карту памяти и суммирует доступные области; она ещё не выделяет и не освобождает страницы.
- В текущем дереве нет драйверов клавиатуры и мыши.
- Наличие цели `make iso` не является доказательством, что ISO успешно собран или загрузился. Проверяйте сборку в своей среде.

## Архитектура проекта

```text
zetomir-os/
├── apps/                    # host-прототипы ZetoBrowse и ZetoFetch
├── boot/                    # конфигурация Limine
├── docs/                    # документация проекта
│   └── platforms/           # инструкции для дистрибутивов Linux
├── games/murino/            # игра на языке ZETOMIR
├── kernel/
│   ├── arch/x86_64/         # начальный CPU-код
│   ├── console/             # вывод kernel-консоли
│   ├── drivers/             # framebuffer и serial
│   ├── mm/                  # чтение карты памяти
│   ├── kernel.c             # точка входа и ранняя инициализация
│   ├── panic.c              # аварийная остановка
│   └── types.h              # базовые типы
├── language/                # host-bootstrap языка ZETOMIR
├── tests/                   # unit tests host-инструментов
├── tools/                   # shell-обёртки CLI
├── linker.ld                # linker script
├── Makefile
├── VERSION
└── README.md
```

Подробнее: [архитектура](docs/ARCHITECTURE.md), [поддержка оборудования](docs/HARDWARE-SUPPORT.md), [дорожная карта](docs/ROADMAP.md).

## Быстрый старт

Рекомендуемая среда разработки — 64-битный Linux на x86_64. Для работы нужны GCC/binutils или рекомендуемый `x86_64-elf` cross-toolchain, GNU Make, Python 3. Для ISO/QEMU дополнительно нужны Limine, xorriso и QEMU.

### Установка инструментов на Arch Linux

```bash
sudo pacman -Syu
sudo pacman -S --needed base-devel git python qemu-system-x86 xorriso nasm gdb
```

Сборка с host toolchain для первичной проверки:

```bash
make clean
make CROSS= -j"$(nproc)"
file build/kernel.elf
readelf -h build/kernel.elf
```

Для целевой freestanding-сборки рекомендуется `x86_64-elf-gcc` и `x86_64-elf-ld`:

```bash
make clean
make -j"$(nproc)"
```

### Тесты

```bash
make test
make zeto-check
```

### Host-приложения

```bash
make fetch
make browse URL=https://example.com
make game
```

Или напрямую:

```bash
./tools/zetofetch
./tools/zetobrowse https://example.com
./tools/zeto games/murino/game.zeto
```

### ISO и QEMU

```bash
make iso
make run
```

Для GDB:

```bash
make debug
# В другом терминале:
gdb build/kernel.elf
(gdb) target remote :1234
(gdb) continue
```

Текущая ISO-цель в Makefile использует BIOS-файлы Limine. UEFI boot пока не следует считать поддержанным только на основании общей цели сборки. Подробная инструкция: [сборка и запуск](docs/BUILDING.md).

## Язык программирования ZETOMIR

Текущий bootstrap преобразует конструкции `.zeto` в Python и запускает результат через Python 3. Это промежуточный инструмент разработки, а не нативная виртуальная машина.

Пример:

```zeto
let health = 10
say "Health: " + str(health)

ask "Use a medkit? " as answer
when answer == "yes":
    health = health + 3
otherwise:
    health = health - 1

say "Current health: " + str(health)
```

Поддерживаемые конструкции и ограничения описаны в [документации языка](docs/ZETOMIR-LANGUAGE.md).

Цель для 1.0: собственный lexer/parser, спецификация языка, байткод, ZVM, стандартная библиотека и нативный запуск `.zeto` приложений без Python.

## Приложения

- **ZetoBrowse** — текстовый HTTP/HTTPS просмотрщик для Linux host. Не поддерживает JavaScript, CSS layout, вкладки, cookies и безопасные сценарии авторизации/платежей.
- **ZetoFetch** — Linux host-утилита, использующая `/proc`, `/etc/os-release` и системные интерфейсы Linux.
- **Murino** — текстовая игра на ZETOMIR, сейчас запускается через Python bootstrap.

Подробности: [документация приложений](docs/APPS.md).

## План до версии 1.0

1. **CPU и прерывания:** GDT/TSS, IDT, исключения, PIC/APIC, IRQ, таймер.
2. **Ввод:** PS/2 keyboard, очередь событий, интерактивная консоль, PS/2 mouse; затем USB HID.
3. **Память:** PMM, VMM, kernel heap.
4. **Хранение:** блочные устройства, GPT/MBR, VFS, ZetoFS, initrd.
5. **Выполнение:** ELF loader, процессы, потоки, планировщик, Ring 3, syscalls, ZetoShell.
6. **ZETOMIR runtime:** lexer/parser, bytecode, ZVM, стандартная библиотека.
7. **GUI:** input API, курсор, оконный менеджер, рабочий стол, панель, файловый менеджер и настройки.
8. **Устройства и сеть:** USB, Ethernet, TCP/IP, DNS, DHCP, TLS, звук.
9. **Дистрибутив:** менеджер пакетов, установщик, Live ISO, обновление и восстановление.
10. **Релиз 1.0:** тесты QEMU/VirtualBox, проверка на реальном оборудовании, документация и воспроизводимая сборка.

Полный чек-лист: [ROADMAP.md](docs/ROADMAP.md).

## Цели совместимости 1.0

.


