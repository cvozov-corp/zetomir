import importlib.util
import pathlib
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]


def load(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


browse = load("zetobrowse", "apps/zetobrowse.py")


class BrowserTests(unittest.TestCase):
    def test_url_normalization(self):
        self.assertEqual(browse.normalize_url("example.com"), "https://example.com")

    def test_rejects_non_http_scheme(self):
        with self.assertRaises(ValueError):
            browse.normalize_url("file:///etc/passwd")

    def test_html_text_and_links(self):
        parser = browse.PageParser("https://example.com/path/")
        parser.feed('<h1>Hello</h1><script>secret()</script><a href="/next">Next</a>')
        self.assertIn("Hello", parser.text())
        self.assertNotIn("secret", parser.text())
        self.assertEqual(parser.links[0][0], "https://example.com/next")


if __name__ == "__main__":
    unittest.main()
