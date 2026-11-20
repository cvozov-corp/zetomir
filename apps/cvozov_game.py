import random, sys, time

BROWN, GRAY, RED, GOLD, CYAN, RESET = "\033[33m", "\033[90m", "\033[91m", "\033[93m", "\033[96m", "\033[0m"

hp, max_hp = 100, 100
checkpoint = 0
trophies = set()
morale = 50
fog = 40

TIPS = [
    "Подсказка: туман — твой друг. Дрон — нет.",
    "Подсказка: прячься в укрытие, и здоровье восстановится само.",
    "Подсказка: Илья Мораль всегда прав. Особенно когда молчит.",
    "Подсказка: Aphex Twin лучше слушать в наушниках. Radiohead — тоже.",
    "Подсказка: Мельстрой не продаёт квартиры, он продаёт ожидание.",
    "Подсказка: если игра кажется мрачной, вы играете правильно.",
]

def p(text="", color=BROWN, delay=0.0):
    print(f"{color}{text}{RESET}")
    if delay: time.sleep(delay)

def loading(name):
    p(f"\n  Загрузка: {name}...", GRAY, 0.4)
    p("  [" + "█" * 10 + "]", GRAY, 0.3)
    p("  " + random.choice(TIPS), GRAY, 0.6)

def trophy(name, desc, kind="🥉"):
    if name not in trophies:
        trophies.add(name)
        p(f"\n  {GOLD}{kind} ДОСТИЖЕНИЕ РАЗБЛОКИРОВАНО: {name} — {desc}", GOLD, 0.4)

def hud():
    bar = "█" * (hp // 10) + "·" * ((max_hp - hp) // 10)
    p(f"\n  HP [{bar}] {hp}  |  Мораль {morale}  |  Туман {fog}%", BROWN)
    if hp < 40:
        p("  >>> ЭКРАН КРАСНЕЕТ. ПРЯЧЬСЯ В УКРЫТИЕ. <<<", RED)

def choose(options):
    for i, o in enumerate(options, 1):
        p(f"   [{i}] {o}", BROWN)
    while True:
        a = input(f"{CYAN}   > {RESET}").strip()
        if a.isdigit() and 1 <= int(a) <= len(options):
            return int(a)

def cover():
    global hp
    p("  Ты прячешься за бетонной плитой. Музыка стихает до низкого гула.", GRAY, 0.5)
    hp = min(max_hp, hp + 40)
    p("  Здоровье восстанавливается.", GRAY)

def qte(button="X", seconds=2.0):
    p(f"\n  !!! БЫСТРО НАЖМИ [{button}] + ENTER !!!", RED)
    t = time.time()
    a = input("  > ").strip().lower()
    return a == button.lower() and time.time() - t < seconds

def game_over():
    p("\n  ВЫ ПОГИБЛИ", RED, 1)
    p("  Загрузка с последнего контрольного пункта...", GRAY, 1)
    return checkpoint

def ch0_title():
    p("\n" + "=" * 52, GRAY)
    p("      М У Р И Н О :   Т У М А Н Н А Я   В О Й Н А", GOLD)
    p("            (Фильтр: серо-коричневый, 2007)", GRAY)
    p("=" * 52, GRAY)
    input("\n          НАЖМИТЕ START (Enter)\n")

def ch1_murino():
    global morale, fog
    loading("Глава 1: Мурино")
    p("\n  ГЛАВА 1: МУРИНО. Ты — Дима. Тебе 27. Ты ждёшь ключи от квартиры.", BROWN, 0.5)
    p("  Мельстрой переносит сдачу дома уже пятый раз.", BROWN, 0.5)
    c = choose(["Поговорить с Геной", "Позвонить в Мельстрой", "Сделать мелкую пакость"])
    if c == 1:
        p("  Гена: «Дима, иногда лучше просто постоять в тумане».", GRAY)
        morale += 10
    elif c == 2:
        p("  Автоответчик: «Ваш звонок очень важен для нас. Ожидайте».", RED)
        fog += 10
    else:
        p("  Ты отключил лифт на пять минут. Пакость засчитана.", GOLD)
        trophy("Мелкая пакость", "Первая шалость в Мурино", "🥉")
    trophy("Добро пожаловать в Мурино", "Начать игру", "🥉")
    return 1

def main():
    global checkpoint, hp
    ch0_title()
    chapters = [ch1_murino]
    while checkpoint < len(chapters):
        hp = max_hp
        res = chapters[checkpoint]()
        if res is not None and res > checkpoint:
            checkpoint = res
            p("\n  [КОНТРОЛЬНЫЙ ПУНКТ СОХРАНЁН]", GRAY, 0.4)
        else:
            checkpoint = res if res is not None else checkpoint
    p("\n" + "=" * 52, GRAY)
    p("                  К О Н Е Ц   И Г Р Ы", GOLD)
    p(f"      Достижений: {len(trophies)}", BROWN)
    p("=" * 52, GRAY)

if __name__ == "__main__":
    try:
        main()
    except (KeyboardInterrupt, EOFError):
        print("\nВыход. Туман остаётся.")
        sys.exit(0)
EOF
echo done