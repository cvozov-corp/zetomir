# Архитектура ZETOMIR OS

## Принципы

Zetomir OS разрабатывается как freestanding x86_64 система. Ядро не использует стандартную библиотеку хостовой ОС и получает начальные сведения о платформе через загрузчик Limine. Пользовательские программы в целевой архитектуре должны запускаться через системный ABI Zetomir, а не через Python или Linux.

## Фактическая ранняя последовательность запуска

1. Limine загружает `build/kernel.elf` по конфигурации `boot/limine.conf`.
2. Точка входа `_start` инициализирует COM1 и пишет диагностическое сообщение.
3. Ядро проверяет ответ Limine на framebuffer request.
4. При наличии совместимого 32-bpp framebuffer запускается простая статическая отрисовка.
5. Инициализируется консольный вывод.
6. Вызывается `cpu_init()` — сейчас это диагностическое сообщение, а не полная настройка CPU tables.
7. `memory_init()` читает карту памяти Limine и суммирует записи типа usable.
8. Ядро выводит сведения и переходит в цикл `hlt`.

## Существующие модули

- `kernel/kernel.c` — запросы Limine, ранняя инициализация, статическая графика, вывод сведений о памяти.
- `kernel/arch/x86_64/cpu.c` и `cpu.h` — базовые x86 инструкции и ранняя CPU-функция.
- `kernel/drivers/serial.*` — COM1.
- `kernel/drivers/framebuffer.*` — простая отрисовка пикселей, прямоугольников и ограниченного ASCII bitmap font.
- `kernel/console/console.*` — отправка символов в serial и framebuffer.
- `kernel/mm/memory.*` — чтение карты памяти, без аллокатора.
- `kernel/panic.c` — остановка CPU и краткое сообщение об ошибке.

## Целевая архитектура

Планируемые подсистемы:
- `arch/x86_64`: GDT, TSS, IDT, interrupt stubs, context switching, SMP groundwork.
- `interrupts`: exception handling, PIC/APIC, IRQ dispatch, timer.
- `mm`: PMM, VMM, kernel heap, address-space management.
- `drivers`: keyboard, mouse, block, USB, network, audio, display.
- `fs`: VFS, partition parser, ZetoFS, initrd.
- `process`: scheduler, process/thread lifecycle, syscall boundary, user mode.
- `runtime`: ELF loader, ZVM and native program ABI.
- `desktop`: compositor/window manager, input routing, shell and applications.

Эти пункты являются проектированием, а не существующим кодом.
