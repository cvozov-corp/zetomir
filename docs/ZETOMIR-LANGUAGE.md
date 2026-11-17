# Язык ZETOMIR 0.1

ZETOMIR — Python-подобный экспериментальный язык проекта с собственными ключевыми словами. Сейчас существует host-bootstrap: `language/zeto.py` преобразует `.zeto` в Python-код и исполняет его на Linux/другой системе с Python 3.

**Это не нативный компилятор и не ZVM.** Программы пока не исполняются ядром Zetomir OS.

## Синтаксис

```zeto
let health = 10
say "Здоровье: " + str(health)
ask "Сколько аптечек? " as kits
when int(kits) > 0:
    health = health + 3
otherwise:
    health = health - 1

fn alive(value):
    when value > 0:
        finish True
    otherwise:
        finish False
```

| Конструкция | Значение в текущем bootstrap |
|---|---|
| `let name = expr` | Присваивание |
| `say expr` | Вывод через Python `print` |
| `ask prompt as name` | Ввод строки через Python `input` |
| `when condition:` | Условие |
| `otherwise:` | Ветка `else` |
| `loop condition:` | Цикл `while` |
| `fn name(args):` | Функция |
| `finish value` | Возврат из функции |

Отступы значимы и должны сохранять вложенность Python-подобных блоков. Выражения пока используют ограничения Python-подобного синтаксиса.

## Запуск

```bash
./tools/zeto games/murino/game.zeto
python3 language/zeto.py games/murino/game.zeto
python3 language/zeto.py games/murino/game.zeto --emit-python
make zeto-check
```

## Ограничения и безопасность

Bootstrap использует Python `exec` с ограниченным набором builtins. Это не полноценная песочница. Не запускайте неизвестные `.zeto` файлы, считая их безопасными.

## Цель для 1.0

- спецификация грамматики и типов;
- отдельные lexer и parser;
- проверка ошибок и диагностические сообщения;
- bytecode format;
- виртуальная машина ZVM;
- стандартная библиотека;
- системный API для файлов, ввода и графики;
- нативный запуск программ без Python.
