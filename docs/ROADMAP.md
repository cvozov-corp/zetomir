# Дорожная карта ZETOMIR OS 1.0

Галочка ставится только после реализации и проверки. Наличие каталога, заглушки или записи в Makefile не считается готовой функцией.

## Текущая база
- [x] Freestanding x86_64 ELF kernel и `_start`.
- [x] BIOS-конфигурация Limine.
- [x] Базовый framebuffer и статическая отрисовка.
- [x] COM1 serial diagnostics.
- [x] Чтение карты памяти Limine.
- [x] Python host-bootstrap языка ZETOMIR.
- [x] Host-прототипы ZetoBrowse и ZetoFetch.
- [x] Игра Murino и базовые host tests.

## 0.2 — CPU и прерывания
- [ ] GDT и TSS.
- [ ] IDT и обработчики CPU exceptions.
- [ ] PIC/APIC и IRQ dispatcher.
- [ ] PIT/system timer.
- [ ] Panic diagnostics с причиной и регистрами.

## 0.3 — клавиатура, мышь и терминал
- [ ] PS/2 keyboard controller и scancode parser.
- [ ] Раскладка, Shift/Ctrl/Alt/Caps Lock.
- [ ] Очередь событий ввода.
- [ ] Интерактивная консоль с редактированием строки.
- [ ] PS/2 mouse: движение, кнопки, колесо.
- [ ] Единый input API.
- [ ] Позже USB HID keyboard/mouse.

## 0.4 — память
- [ ] PMM.
- [ ] VMM и управление address spaces.
- [ ] Kernel heap.
- [ ] Тесты выделения, освобождения и выравнивания.

## 0.5 — накопители и файлы
- [ ] Блочные устройства.
- [ ] GPT/MBR parser.
- [ ] VFS.
- [ ] ZetoFS: создание, чтение, запись, каталоги.
- [ ] Initrd.

## 0.6 — приложения и многозадачность
- [ ] ELF loader.
- [ ] Scheduler.
- [ ] Processes and threads.
- [ ] Ring 3 и системные вызовы.
- [ ] ZetoShell.
- [ ] Защита адресных пространств.

## 0.7 — ZETOMIR runtime
- [ ] Lexer/parser и спецификация языка.
- [ ] Bytecode format.
- [ ] ZVM.
- [ ] Standard library.
- [ ] Нативный запуск `.zeto` без Python.

## 0.8 — графическая среда
- [ ] Графический backend и курсор.
- [ ] Оконный менеджер.
- [ ] Рабочий стол, панель задач, launcher.
- [ ] Файловый менеджер и настройки.
- [ ] Мышь и клавиатурная навигация во всех приложениях.

## 0.9 — устройства и системные службы
- [ ] USB xHCI/HID.
- [ ] Ethernet и сетевой драйвер.
- [ ] TCP/IP, DNS, DHCP.
- [ ] TLS/HTTPS.
- [ ] Базовый звук.
- [ ] ZetoPackage.
- [ ] Live ISO и установщик.
- [ ] Обновление и восстановление.

## 1.0 — стабильный релиз
- [ ] BIOS boot проверен.
- [ ] UEFI boot реализован и проверен.
- [ ] QEMU и VirtualBox test matrix.
- [ ] Список проверенного реального оборудования.
- [ ] Рабочие клавиатура и мышь.
- [ ] Интерактивный терминал и GUI.
- [ ] Файлы и нативные приложения.
- [ ] ZVM и системные приложения.
- [ ] Базовая сеть.
- [ ] Установщик, Live-режим и руководство.
- [ ] Автоматические тесты и воспроизводимая сборка.
