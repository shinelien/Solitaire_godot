#!/usr/bin/env python3
"""Independent spot-check of WP-05 golden fixtures.

Recomputes the expected deal data directly from the raw fixed-object records
and compares against the persisted fixture JSONs — WITHOUT touching any
production GDScript decoder/dealer. Covers bureau1 indices 0,1,2,9,99 and
all 25 spread bureau3 indices (the same set the MCP McpTestSuite asserts).

Mirrors generate_fixtures.py's independent spec implementation so the check
cannot accidentally share a bug with res://solitaire/** production code.
"""

import hashlib
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DATA = os.path.join(ROOT, "data", "legacy")

POOLS = {
    "bureau1": {
        "file": os.path.join(DATA, "bureau1.d"),
        "indices": [0, 1, 2, 9, 99],
        "golden": os.path.join(DATA, "golden", "golden_bureau1.json"),
    },
    "bureau3": {
        "file": os.path.join(DATA, "bureau3.d"),
        "indices": [0, 1, 2, 3, 4, 9, 49, 99, 199, 499, 999, 1499, 1999, 2499,
                    2999, 3499, 3999, 4499, 4700, 4800, 4900, 4949, 4970, 4990, 4998],
        "golden": os.path.join(DATA, "golden", "golden_bureau3.json"),
    },
}


def canonical_digest(tableau, stock):
    cols = [",".join(str(c["id"]) for c in column) for column in tableau]
    text = "|".join(cols) + "#" + ",".join(str(x) for x in stock)
    return hashlib.sha256(text.encode("ascii")).hexdigest()


def main() -> int:
    failures = []
    for pool, info in POOLS.items():
        raw = open(info["file"], "rb").read()
        lines = raw[:-1].split(b"\n")
        if len(lines) != len(raw) // 53:
            raise SystemExit("layout unexpected %s" % pool)
        golden = json.load(open(info["golden"]))
        store = {int(f["index"]): f for f in golden["fixtures"]}
        for index in info["indices"]:
            rec = lines[index].decode("ascii")
            fixture = store[index]
            if rec != fixture["raw_deal"]:
                failures.append("%s#%d raw mismatch" % (pool, index))
            ids = [ord(rec[51 - i]) - 48 for i in range(52)]
            if ids != fixture["consumption"]:
                failures.append("%s#%d consumption mismatch" % (pool, index))
            tableau, stock = [], []
            cursor = 0
            for col in range(7):
                column = []
                for row in range(col + 1):
                    column.append({"id": ids[cursor], "face_up": row == col})
                    cursor += 1
                tableau.append(column)
            stock = ids[28:]
            if stock != fixture["dealt"]["stock"]:
                failures.append("%s#%d dealt stock mismatch" % (pool, index))
            got_cols = [[c["id"] for c in col] for col in tableau]
            exp_cols = [[c["id"] for c in col] for col in fixture["dealt"]["tableau"]]
            if got_cols != exp_cols:
                failures.append("%s#%d dealt tableau ids mismatch" % (pool, index))
            got_face = [[c["face_up"] for c in col] for col in tableau]
            exp_face = [[c["face_up"] for c in col] for col in fixture["dealt"]["tableau"]]
            if got_face != exp_face:
                failures.append("%s#%d dealt face_up mismatch" % (pool, index))
            if canonical_digest(tableau, stock) != fixture["dealt_canonical_sha256"]:
                failures.append("%s#%d digest mismatch" % (pool, index))
            for mode in ("ready_draw1", "ready_draw3"):
                draw = 1 if mode == "ready_draw1" else 3
                rest = list(stock)
                drawn = []
                for _ in range(draw):
                    if rest:
                        drawn.append(rest.pop())
                if rest != fixture[mode]["stock"]:
                    failures.append("%s#%d %s stock mismatch" % (pool, index, mode))
                if drawn != fixture[mode]["waste"]:
                    failures.append("%s#%d %s waste mismatch" % (pool, index, mode))
    if failures:
        for f in failures:
            print("MISMATCH:", f)
        return 1
    print("independent spot-check OK: all sampled fixtures match raw fixed-object records")
    return 0


if __name__ == "__main__":
    sys.exit(main())
