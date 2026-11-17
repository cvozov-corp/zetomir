# Приложения Zetomir

Приведённые ниже приложения — host-прототипы. Они запускаются в Linux с Python 3 и пока не исполняются внутри ядра Zetomir OS.

## ZetoBrowse

Минимальный текстовый просмотрщик HTTP/HTTPS:

```bash
./tools/zetobrowse https://example.com
./tools/zetobrowse
make browse URL=https://example.com
```

Текущие возможности:
- получает HTTP/HTTPS-страницы;
- отображает текст HTML и `text/plain`;
- пропускает содержимое `script`, `style`, `noscript` и SVG;
- извлекает ссылки и преобразует относительные URL в абсолютные;
- ограничивает размер ответа 1 000 000 байт;
- использует timeout 12 секунд.

Ограничения: нет JavaScript, CSS layout, изображений, вкладок, cookies, истории, загрузок и полноценной HTML-совместимости. Ссылки перечисляются, но переход по номеру ссылки не реализован. Не используйте прототип для авторизации, платежей или конфиденциальных данных.

## ZetoFetch

```bash
./tools/zetofetch
make fetch
```

Показывает ОС, hostname, ядро Linux, архитектуру, CPU, использование памяти, uptime, shell, Python и терминал. Использует `/etc/os-release` и `/proc`; это информация о Linux-хосте, не о ядре Zetomir.

## Murino

```bash
./tools/zeto games/murino/game.zeto
make game
```

Текстовая игра на `.zeto`, исполняемая текущим Python bootstrap.

## Дальнейшая интеграция

Для нативных версий нужны системные вызовы, VFS, сетевой стек, TLS, ZVM, графическая библиотека и ABI приложений. До реализации этих подсистем приложения остаются host tools.
