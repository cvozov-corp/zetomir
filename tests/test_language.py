import importlib.util, pathlib, unittest
ROOT=pathlib.Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('zeto',ROOT/'language/zeto.py')
zeto=importlib.util.module_from_spec(spec); spec.loader.exec_module(zeto)
class LanguageTests(unittest.TestCase):
    def test_keywords(self):
        out=zeto.compile_source('let x = 3\nsay x\nwhen x > 1:\n    say "yes"\notherwise:\n    say "no"')
        self.assertIn('x = 3',out); self.assertIn('print(x)',out); self.assertIn('if x > 1:',out); self.assertIn('else:',out)
    def test_game_translates(self):
        src=(ROOT/'games/murino/game.zeto').read_text()
        py=zeto.compile_source(src)
        compile(py,'game.zeto','exec')
if __name__=='__main__': unittest.main()
