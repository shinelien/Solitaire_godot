from pathlib import Path
import subprocess
P = Path(__file__).resolve().parents[1]
R = P.parent / "reference/NewHD-runtime/cocos2d/cocos/editor-support/spine"
subprocess.run(["clang", "-O2", "-I" + str(R.parent), str(P / "tools/spine_sampler.c"), *map(str, sorted(R.glob("*.c"))), "-lm", "-o", str(P / "tools/spine_sampler")], check=True)
