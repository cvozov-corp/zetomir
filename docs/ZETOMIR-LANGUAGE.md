# Язык ZETOMIR 0.1

ZETOMIR — Python-подобный язык с собственными ключевыми словами. В этой версии есть bootstrap-компилятор, который переводит исходники `.zeto` в Python-подобное промежуточное представление и запускает его на машине разработчика. Это инструмент разработки, а НЕ ещё нативная реализация внутри ядра.

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

| ZETOMIR | Значение |
|---|---|
| `let name = expr` | объявление/присваивание переменной |
| `say expr` | вывод |
| `ask "prompt" as name` | ввод строки |
| `when condition:` | условие |
| `otherwise:` | ветка иначе |
| `loop condition:` | цикл |
| `fn name(args):` | функция |
| `finish value` | возврат из функции |

Отступы — 4 пробела. Имена переменных и выражения пока следуют ограничениям Python-подобной грамматики. Следующий этап — собственный lexer/parser, байткод ZVM и нативный runtime на C для Zetomir OS.

## Запуск

```sh
python3 language/zeto.py games/murino/game.zeto
python3 language/zeto.py games/murino/game.zeto --emit-python
```

Bootstrap-компилятор использует только стандартную библиотеку Python. Никаких сторонних пакетов не требуется.
