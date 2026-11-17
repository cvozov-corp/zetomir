# Сборка и запуск

## Среда

Рекомендуется x86_64 Linux. Нужны:
- GNU Make;
- Python 3;
- GCC и GNU binutils для host smoke build;
- рекомендуемый `x86_64-elf-gcc` и `x86_64-elf-ld` для freestanding cross build;
- xorriso и Limine для ISO;
- QEMU `qemu-system-x86_64` для виртуального запуска;
- GDB для отладки.

## Arch Linux

```bash
sudo pacman -Syu
sudo pacman -S --needed base-devel git python qemu-system-x86 xorriso nasm gdb
```

Инструкция по cross-compiler приведена в `platforms/ARCH-LINUX.md`.

## Проверка компиляции ядра host toolchain

```bash
make clean
make CROSS= -j"$(nproc)"
file build/kernel.elf
readelf -h build/kernel.elf
```

Это smoke build на x86_64 Linux. Он не заменяет проверку сборки целевым cross-compiler и не доказывает загрузку ISO.

## Целевая сборка

По умолчанию Makefile использует префикс `x86_64-elf-`:

```bash
x86_64-elf-gcc --version
x86_64-elf-ld --version
make clean
make -j"$(nproc)"
```

Ожидаемый результат: `build/kernel.elf`.

## Тесты

```bash
make test
make zeto-check
```

Текущие тесты проверяют host-код языка и ZetoBrowse. Это не kernel unit tests.

## Host applications

```bash
make game
make fetch
make browse URL=https://example.com
```

Или:

```bash
./tools/zeto games/murino/game.zeto
./tools/zetofetch
./tools/zetobrowse https://example.com
```

## ISO и QEMU

```bash
make iso
make run
```

Makefile клонирует Limine `v9.x-binary`, если каталога `limine/` нет, затем использует BIOS assets и `limine bios-install`. Для первого запуска требуется сеть и доступ к GitHub. Текущая цель не является доказательством UEFI поддержки.

Отладка:

```bash
make debug
```

Во втором терминале:

```bash
gdb build/kernel.elf
(gdb) target remote :1234
(gdb) continue
```

## VirtualBox

Сначала создайте ISO через `make iso`. Создайте виртуальную машину типа Linux/Other 64-bit, выделите разумный объём RAM, подключите ISO как оптический диск и начните с BIOS firmware. UEFI следует проверять отдельно после появления соответствующей конфигурации и тестов. Параметры виртуального графического адаптера могут влиять на доступность framebuffer.

## Реальное оборудование

Текущая версия не готова к установке на основной компьютер. До тестов на физическом устройстве:
- используйте отдельный тестовый диск/USB;
- сохраняйте резервную копию важных данных;
- не запускайте экспериментальные команды записи диска на рабочей системе;
- проверяйте загрузку с отключёнными важными данными;
- записывайте точную модель устройства и результат.

## Android / Termux

Termux на Android ARM64 подходит для редактирования, Git и публикации исходников. Для сборки x86_64 ядра используйте x86_64 Linux, VM или специально настроенный cross-toolchain/CI.
