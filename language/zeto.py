#!/usr/bin/env python3
"""ZETOMIR bootstrap interpreter/compiler (host-side tool, Python stdlib only)."""
from __future__ import annotations
import argparse, pathlib, re, sys

KEYWORDS = [(r'^(\s*)let\s+', r'\1'),
            (r'^(\s*)say\s+', r'\1print('),
            (r'^(\s*)ask\s+(.+?)\s+as\s+([A-Za-z_]\w*)\s*$', r'\1\3 = input(\2)'),
            (r'^(\s*)when\s+(.+?)\s*:\s*$', r'\1if \2:'),
            (r'^(\s*)otherwise\s*:\s*$', r'\1else:'),
            (r'^(\s*)loop\s+(.+?)\s*:\s*$', r'\1while \2:'),
            (r'^(\s*)fn\s+', r'\1def '),
            (r'^(\s*)finish(?:\s+(.*))?$', r'\1return \2')]

def compile_source(source: str) -> str:
    out=[]
    for number,line in enumerate(source.splitlines(),1):
        stripped=line.strip()
        if not stripped or stripped.startswith('#'):
            out.append(line); continue
        converted=line
        is_say = bool(re.match(r'^\s*say\s+', line))
        for pattern,replacement in KEYWORDS:
            converted=re.sub(pattern,replacement,converted)
        # say is a statement, so close the print call on the line.
        if is_say:
            converted=converted.rstrip()+')'
        if re.match(r'^\s*return\s*$',converted): converted=re.sub(r'return\s*$','return None',converted)
        out.append(converted)
    return '\n'.join(out)+'\n'

def run_file(path: pathlib.Path, argv: list[str]) -> int:
    source=path.read_text(encoding='utf-8')
    python_source=compile_source(source)
    scope={'__name__':'__main__','ZETOMIR_VERSION':'0.1'}
    # Bootstrap stage only. A restricted builtins table avoids exposing file/process APIs.
    safe={'print':print,'input':input,'int':int,'str':str,'len':len,'range':range,
          'min':min,'max':max,'abs':abs,'bool':bool,'True':True,'False':False,'None':None}
    scope['__builtins__']=safe
    exec(compile(python_source,str(path),'exec'),scope,scope)
    return 0

def main():
    p=argparse.ArgumentParser(prog='zeto',description='ZETOMIR language bootstrap tool')
    p.add_argument('file',type=pathlib.Path)
    p.add_argument('--emit-python',action='store_true',help='print translated bootstrap source')
    args=p.parse_args()
    try:
        source=args.file.read_text(encoding='utf-8')
        translated=compile_source(source)
        if args.emit_python: print(translated,end=''); return 0
        scope={'__name__':'__main__'}
        safe={'print':print,'input':input,'int':int,'str':str,'len':len,'range':range,
              'min':min,'max':max,'abs':abs,'bool':bool,'True':True,'False':False,'None':None}
        scope['__builtins__']=safe
        exec(compile(translated,str(args.file),'exec'),scope,scope)
        return 0
    except (OSError, SyntaxError, NameError, TypeError, ValueError) as e:
        print(f'ZETOMIR error: {e}',file=sys.stderr); return 1
if __name__=='__main__': raise SystemExit(main())
