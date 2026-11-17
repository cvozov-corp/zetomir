#!/usr/bin/env python3
"""ZetoFetch: compact system summary inspired by fastfetch."""
from __future__ import annotations
import os
import platform
import re
import shutil

LOGO = ["     _______", "    / ____  /", "   / /___/ /", "  /_____  /", "       /_/ "]


def read_os() -> str:
    try:
        with open("/etc/os-release", encoding="utf-8") as f:
            for line in f:
                if line.startswith("PRETTY_NAME="):
                    return line.split("=", 1)[1].strip().strip('"')
    except OSError:
        pass
    return platform.system()


def cpu_name() -> str:
    try:
        with open("/proc/cpuinfo", encoding="utf-8", errors="replace") as f:
            for line in f:
                if line.lower().startswith(("model name", "hardware")):
                    return line.split(":", 1)[-1].strip()
    except OSError:
        pass
    return platform.processor() or "не определён"


def memory() -> str:
    try:
        values = {}
        with open("/proc/meminfo", encoding="utf-8") as f:
            for line in f:
                match = re.match(r"(MemTotal|MemAvailable):\s+(\d+)", line)
                if match:
                    values[match.group(1)] = int(match.group(2))
        total = values.get("MemTotal")
        if total:
            used = total - values.get("MemAvailable", total)
            return f"{used / 1048576:.1f} GiB / {total / 1048576:.1f} GiB"
    except OSError:
        pass
    return "недоступно"


def uptime() -> str:
    try:
        with open("/proc/uptime", encoding="ascii") as f:
            seconds = int(float(f.read().split()[0]))
        days, seconds = divmod(seconds, 86400)
        hours, seconds = divmod(seconds, 3600)
        minutes = seconds // 60
        return f"{days}д {hours}ч {minutes}м" if days else f"{hours}ч {minutes}м"
    except (OSError, ValueError, IndexError):
        return "недоступно"


def main() -> None:
    user = os.environ.get("USER") or os.environ.get("USERNAME") or "unknown"
    host = platform.node() or "unknown"
    shell = os.path.basename(os.environ.get("SHELL", "неизвестно"))
    rows = [
        ("OS", read_os()),
        ("Host", host),
        ("Kernel", platform.release()),
        ("Architecture", platform.machine()),
        ("CPU", cpu_name()),
        ("Memory", memory()),
        ("Uptime", uptime()),
        ("Shell", shell),
        ("Python", platform.python_version()),
        ("Terminal", os.environ.get("TERM", "неизвестно")),
    ]
    width = max(len(k) for k, _ in rows)
    print("\033[36m" + "\n".join(LOGO) + "\033[0m  \033[1mZetomir OS tools\033[0m")
    print(f"  {user}@{host}")
    print("  " + "─" * 42)
    for key, value in rows:
        print(f"  \033[36m{key:<{width}}\033[0m  {value}")


if __name__ == "__main__":
    main()
