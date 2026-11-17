#!/usr/bin/env python3
"""ZetoBrowse: a deliberately small, text-only HTTP/HTTPS browser."""
from __future__ import annotations

import sys
import urllib.error
import urllib.parse
import urllib.request
from html.parser import HTMLParser

MAX_BYTES = 1_000_000
TIMEOUT = 12


class PageParser(HTMLParser):
    BLOCKS = {"p", "div", "br", "hr", "h1", "h2", "h3", "h4", "li", "tr", "section", "article"}

    def __init__(self, base_url: str):
        super().__init__(convert_charrefs=True)
        self.base_url = base_url
        self.parts: list[str] = []
        self.links: list[tuple[str, str]] = []
        self.skip_depth = 0

    def handle_starttag(self, tag, attrs):
        attrs = dict(attrs)
        if tag in ("script", "style", "noscript", "svg"):
            self.skip_depth += 1
            return
        if self.skip_depth:
            return
        if tag in self.BLOCKS:
            self.parts.append("\n")
        if tag == "a" and attrs.get("href"):
            href = urllib.parse.urljoin(self.base_url, attrs["href"])
            if urllib.parse.urlsplit(href).scheme in ("http", "https"):
                self.links.append((href, ""))
                self.parts.append(f" [{len(self.links)}] ")

    def handle_endtag(self, tag):
        if tag in ("script", "style", "noscript", "svg") and self.skip_depth:
            self.skip_depth -= 1
        elif not self.skip_depth and tag in self.BLOCKS:
            self.parts.append("\n")

    def handle_data(self, data):
        if not self.skip_depth:
            text = " ".join(data.split())
            if text:
                self.parts.append(text + " ")

    def text(self) -> str:
        lines = [" ".join(line.split()) for line in "".join(self.parts).splitlines()]
        return "\n".join(line for line in lines if line)


def normalize_url(value: str) -> str:
    value = value.strip()
    if not urllib.parse.urlsplit(value).scheme:
        value = "https://" + value
    parsed = urllib.parse.urlsplit(value)
    if parsed.scheme not in ("http", "https") or not parsed.hostname:
        raise ValueError("Разрешены только корректные адреса http:// и https://")
    return value


def fetch(url: str) -> tuple[str, str, PageParser]:
    request = urllib.request.Request(url, headers={"User-Agent": "ZetoBrowse/0.1 (text browser)"})
    with urllib.request.urlopen(request, timeout=TIMEOUT) as response:
        final_url = response.geturl()
        if urllib.parse.urlsplit(final_url).scheme not in ("http", "https"):
            raise ValueError("Перенаправление на не-HTTP(S) адрес запрещено")
        content_type = response.headers.get_content_type()
        data = response.read(MAX_BYTES + 1)
        if len(data) > MAX_BYTES:
            raise ValueError(f"Страница больше лимита {MAX_BYTES // 1000} КБ")
        charset = response.headers.get_content_charset() or "utf-8"
    if content_type not in ("text/html", "application/xhtml+xml", "text/plain"):
        raise ValueError(f"Этот прототип показывает HTML и текст, не {content_type}")
    decoded = data.decode(charset, errors="replace")
    parser = PageParser(final_url)
    if content_type == "text/plain":
        parser.parts.append(decoded)
    else:
        parser.feed(decoded)
    return final_url, content_type, parser


def show(url: str) -> None:
    try:
        final_url, content_type, page = fetch(normalize_url(url))
        print(f"\nZetoBrowse 0.1 | {final_url}\n{'-' * 72}")
        print(page.text() or "[На странице нет отображаемого текста]")
        if page.links:
            print("\nСсылки:")
            for number, (href, _label) in enumerate(page.links, 1):
                print(f"  [{number}] {href}")
        print(f"\n[тип: {content_type}; ссылок: {len(page.links)}]")
    except (ValueError, urllib.error.URLError, TimeoutError, OSError) as exc:
        print(f"ZetoBrowse: ошибка: {exc}", file=sys.stderr)


def main() -> int:
    if len(sys.argv) > 1:
        show(" ".join(sys.argv[1:]))
        return 0
    print("ZetoBrowse 0.1 — текстовый браузер Zetomir\nВведите URL или q для выхода.")
    while True:
        try:
            value = input("zeto-web> ").strip()
        except (EOFError, KeyboardInterrupt):
            print()
            break
        if value.lower() in ("q", "quit", "exit"):
            break
        if value:
            show(value)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
