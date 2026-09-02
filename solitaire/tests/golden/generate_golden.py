#!/usr/bin/env python3
"""One-time generator for the static Draw-1 golden fixtures.

Implements the documented legacy semantics (ADR-004) independently of the
GDScript decoder so the fixtures are a genuine cross-check:

  - each record is 52 ASCII bytes; id = byte - ord('0')
  - draw order = reversed record:  ids[i] = byte[51 - i] - ord('0')
  - deal column-first: col 0..6, rows 0..col (sizes 1..7); last card of each
    column face-up; the remaining 24 ids become the stock in draw order.

Output is written to data/legacy/golden/golden_draw1.json and is a static,
independent expectation consumed by tests/test_golden.gd at test-run time.
"""

import hashlib
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = os.path.join(ROOT, "data", "legacy", "bureau1.d")
OUT = os.path.join(ROOT, "data", "legacy", "golden", "golden_draw1.json")
SAMPLE_COUNT = 50


def decode(record: str) -> list:
    if len(record) != 52:
        raise ValueError("record length %d" % len(record))
    ids = []
    for i in range(51, -1, -1):
        b = ord(record[i])
        if b < 0x30 or b > 0x30 + 51:
            raise ValueError("byte out of range at %d" % i)
        ids.append(b - 0x30)
    if len(set(ids)) != 52 or min(ids) != 0 or max(ids) != 51:
        raise ValueError("ids not a permutation")
    return ids


def deal(ids: list) -> tuple:
    tableau = []
    idx = 0
    for col in range(7):
        column = []
        for row in range(col + 1):
            column.append({"id": ids[idx], "face_up": bool(row == col)})
            idx += 1
        tableau.append(column)
    stock = ids[idx:idx + 24]
    if len(stock) != 24:
        raise ValueError("stock != 24")
    return tableau, stock


def main() -> None:
    with open(SRC, "r", encoding="ascii") as fh:
        lines = fh.read().splitlines()
    if len(lines) != 32084:
        raise SystemExit("unexpected record count %d" % len(lines))
    digest = hashlib.sha256(open(SRC, "rb").read()).hexdigest()
    fixtures = []
    for i in range(SAMPLE_COUNT):
        rec = lines[i]
        ids = decode(rec)
        tableau, stock = deal(ids)
        fixtures.append({
            "index": i,
            "encoded": rec,
            "tableau": tableau,
            "stock": stock,
        })
    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(fixtures, fh, indent=1, ensure_ascii=True)
    print("wrote %s" % OUT)
    print("fixtures=%d source_records=%d sha256=%s" % (len(fixtures), len(lines), digest))


if __name__ == "__main__":
    main()
