# Zetomir OS на Arch Linux

Эта инструкция описывает сборку и запуск **проекта Zetomir OS из Arch Linux**. Она не означает, что Zetomir уже устанавливается поверх Arch или является Arch-пакетом: сейчас это отдельное freestanding-ядро, запускаемое в QEMU.

## 1. Установка инструментов

Обновите систему и установите базовые инструменты:

```bash
sudo pacman -Syu
sudo pacman -S --needed base-devel git python qemu-system-x86 xorriso nasm gdb
```

`base-devel` предоставляет GCC, GNU binutils и make; QEMU для x86 устанавливается пакетом `qemu-system-x86`. Состав пакетов со временем может меняться — сверяйтесь с ArchWiki и официальным каталогом пакетов.

Проверьте доступность команд:

```bash
gcc --version
ld --version
make --version
python --version
qemu-system-x86_64 --version
xorriso -version
```

## 2. Получение исходников

Перейдите в каталог проекта (или клонируйте ваш Git-репозиторий, если он опубликован):

```bash
cd zetomir-os
```

## 3. Быстрая проверка ядра на Arch

Сборка host-toolchain нужна для быстрой проверки исходников на x86_64:

```bash
make clean
make CROSS= -j"$(nproc)"
file build/kernel.elf
readelf -h build/kernel.elf
```

Ожидается ELF64 для AMD x86-64. Эта проверка компилирует и линкует ядро, но сама по себе не создаёт загрузочный ISO.

## 4. Кросс-компилятор для ISO

Для воспроизводимой freestanding-сборки рекомендуется `x86_64-elf-gcc` и `x86_64-elf-ld`. Проверьте наличие:

```bash
x86_64-elf-gcc --version
x86_64-elf-ld --version
```

Если их нет, установите подходящий кросс-компилятор из доверенного источника или соберите по руководству OSDev GCC Cross Compiler. Не подменяйте его случайным бинарником из непроверенного AUR-пакета.

Затем выполните:

```bash
make clean
make -j"$(nproc)"
make iso
```

Цель `iso` скачивает и собирает Limine `v9.x-binary` при отсутствии каталога `limine/`, поэтому для первого запуска нужен доступ к GitHub. После загрузки исходников Limine зафиксируйте конкретный commit для повторяемых сборок.

## 5. Запуск в QEMU

```bash
make run
```

Для отладки:

```bash
make debug
# В другом терминале:
gdb build/kernel.elf
(gdb) target remote :1234
(gdb) continue
```

Если QEMU не открывает графическое окно, проверьте доступность графического backend или используйте конфигурацию QEMU с подходящим display backend. Serial вывод ядра идёт в терминал.

## 6. Тесты и приложения-хост утилиты

```bash
make test
make zeto-check
make game
make fetch
make browse URL=https://example.com
```

`fetch` и `browse` — программы, которые пока запускаются **в Arch Linux как host utilities**, а не внутри ядра Zetomir. Им нужен Python 3; сторонние Python-пакеты не требуются.

Можно запускать напрямую:

```bash
./tools/zetofetch
./tools/zetobrowse https://example.com
./tools/zetobrowse
```

## Устранение неполадок

- `xorriso: command not found`: установите `xorriso` через pacman.
- `qemu-system-x86_64: command not found`: установите `qemu-system-x86`.
- `x86_64-elf-gcc: command not found`: установите/соберите кросс-компилятор; `make CROSS=` годится для host smoke build, но не заменяет целевой toolchain в документированной ISO-сборке.
- Ошибка клонирования Limine: проверьте сеть и доступ к GitHub либо заранее поместите исходники Limine в `limine/`.
- ISO и загрузка в QEMU должны считаться непроверенными, пока вы лично не выполнили `make iso` и `make run` в своей среде.

## Полезные ссылки

- [ArchWiki: Installation guide](https://wiki.archlinux.org/title/Installation_guide)
- [ArchWiki: GNU toolchain](https://wiki.archlinux.org/title/GNU)
- [Arch Linux: base-devel](https://archlinux.org/packages/core/any/base-devel/)
- [Arch Linux: qemu-system-x86](https://archlinux.org/packages/extra/x86_64/qemu-system-x86/)
- [OSDev: GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler)
