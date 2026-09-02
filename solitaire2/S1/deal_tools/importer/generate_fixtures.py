#!/usr/bin/env python3
"""WP-05 golden fixture generator (INDEPENDENT of the production GDScript decoder/dealer).

Implements the documented legacy semantics directly from the raw fixed-object
records so the fixtures are a genuine cross-check:

  - each record is 52 ASCII bytes (48..99); id = byte - ord('0')
  - consumption order = reversed record: ids[i] = byte[51 - i] - ord('0')
  - gameplay consumes ids FIFO
  - tableau triangular deal, column-major cols 0..6 with sizes 1..7:
    for col in 0..6: for row in 0..col: place next consumed id at
    pile[bottom..top]; the last dealt card of each column (pile tail) is
    face-up.
  - the remaining 24 consumed ids form the stock, bottom-to-top with the
    stock top at the array end.
  - dealt snapshot has an empty waste. Ready snapshots then auto-draw
    draw_count cards (1 or 3) from the stock top (array end) and push each,
    in pop order, onto the waste tail (top = last drawn = playable).

The production GDScript LegacyDealDecoder / LegacyDealer under
res://solitaire/** is NEVER called here; expectations are computed by this
standalone Python implementation of the same spec. Output JSON fixtures are
static files consumed by res://tests/ at MCP test-run time.

Canonical dealt-digest (pins legacy record 0 to the TD-fixed hash):
  sha256( columns joined ',' per column and '|' between columns + '#' +
          stock ids joined ',' )  == 935879b0...  for record 0.
"""

import hashlib
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DATA = os.path.join(ROOT, "data", "legacy")
OUT = os.path.join(DATA, "golden")

POOLS = {
    "bureau1": {
        "file": os.path.join(DATA, "bureau1.d"),
        "source": "Resources/data/bureau1.d",
        "records": 32084,
    },
    "bureau3": {
        "file": os.path.join(DATA, "bureau3.d"),
        "source": "Resources/data/bureau3.d",
        "records": 4999,
    },
}

BUREAU1_INDICES = list(range(100))

BUREAU3_INDICES = [
    0, 1, 2, 3, 4, 9, 49, 99, 199, 499, 999, 1499, 1999,
    2499, 2999, 3499, 3999, 4499, 4700, 4800, 4900, 4949,
    4970, 4990, 4998,
]


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def load_records(pool: str) -> list:
    info = POOLS[pool]
    raw = open(info["file"], "rb").read()
    expect_bytes = info["records"] * 53
    if len(raw) != expect_bytes:
        raise SystemExit("pool %s: byte count %d != expected %d" % (pool, len(raw), expect_bytes))
    body = raw
    if not body.endswith(b"\n"):
        raise SystemExit("pool %s: file does not end with LF" % pool)
    lines = body.split(b"\n")
    if len(lines) - 1 != info["records"]:
        raise SystemExit("pool %s: record count %d != %d" % (pool, len(lines) - 1, info["records"]))
    if any(len(ln) != 52 for ln in lines[:-1]):
        bad = [i for i, ln in enumerate(lines[:-1]) if len(ln) != 52]
        raise SystemExit("pool %s: bad lengths at %s" % (pool, bad[:10]))
    return [ln.decode("ascii") for ln in lines[:-1]]


def decode(record: str) -> list:
    if len(record) != 52:
        raise ValueError("record length %d" % len(record))
    ids = []
    for i in range(51, -1, -1):
        b = ord(record[i])
        if b < 0x30 or b > 0x30 + 51:
            raise ValueError("byte out of range at %d: %d" % (i, b))
        ids.append(b - 0x30)
    if len(set(ids)) != 52 or min(ids) != 0 or max(ids) != 51:
        raise ValueError("ids not a complete 0..51 permutation")
    return ids


def deal(ids: list):
    tableau = []
    idx = 0
    for col in range(7):
        column = []
        for row in range(col + 1):
            face_up = row == col
            column.append({"id": ids[idx], "face_up": face_up})
            idx += 1
        tableau.append(column)
    stock = ids[idx:idx + 24]
    if len(stock) != 24:
        raise ValueError("stock length != 24")
    return tableau, stock


def draw(stock: list, draw_count: int):
    """Pop up to draw_count cards from the stock top; returns (rest, drawn)."""
    rest = list(stock)
    drawn = []
    for _ in range(draw_count):
        if not rest:
            break
        drawn.append(rest.pop())
    return rest, drawn


def canonical_dealt_digest(tableau: list, stock: list) -> str:
    cols = [",".join(str(c["id"]) for c in column) for column in tableau]
    text = "|".join(cols) + "#" + ",".join(str(x) for x in stock)
    return hashlib.sha256(text.encode("ascii")).hexdigest()


def build_fixture(record: str, index: int, pool: str, source: str) -> dict:
    ids = decode(record)
    tableau, stock = deal(ids)
    digest = canonical_dealt_digest(tableau, stock)
    stock1, drawn1 = draw(stock, 1)
    stock3, drawn3 = draw(stock, 3)
    return {
        "source": source,
        "pool": pool,
        "index": index,
        "raw_deal": record,
        "consumption": ids,
        "dealt_canonical_sha256": digest,
        "dealt": {
            "tableau": tableau,
            "stock": stock,
            "waste": [],
        },
        "ready_draw1": {
            "stock": stock1,
            "waste": drawn1,
        },
        "ready_draw3": {
            "stock": stock3,
            "waste": drawn3,
        },
    }


def main() -> None:
    meta = {
        "generator": "deal_tools/importer/generate_fixtures.py",
        "independence": (
            "Expectations are computed by an independent Python implementation "
            "of the documented legacy spec, reading only the raw fixed-object "
            "records exported under data/legacy/. The production GDScript "
            "LegacyDealDecoder/LegacyDealer are never invoked here."
        ),
        "canonical_digest_format": (
            "sha256(columns ','-joined and '|'-joined + '#' + stock ids ','-joined); "
            "record 0 must equal 935879b0483480ea8f936cdc2c2b236d532d2b9531f800b19173f8dd50d620e3"
        ),
        "pools": {},
    }
    counts = {}
    for pool, info in POOLS.items():
        raw = open(info["file"], "rb").read()
        meta["pools"][pool] = {
            "source": info["source"],
            "records": info["records"],
            "bytes": len(raw),
            "sha256": sha256_bytes(raw),
        }
        counts[pool] = info["records"]

    b1 = load_records("bureau1")
    fixtures_b1 = [build_fixture(b1[i], i, "bureau1", POOLS["bureau1"]["source"]) for i in BUREAU1_INDICES]

    b3 = load_records("bureau3")
    fixtures_b3 = [build_fixture(b3[i], i, "bureau3", POOLS["bureau3"]["source"]) for i in BUREAU3_INDICES]

    record0_sha = sha256_bytes(b1[0].encode("ascii") + b"\n")
    record0_sha_nolf = sha256_bytes(b1[0].encode("ascii"))
    meta["record0"] = {
        "pool": "bureau1",
        "index": 0,
        "sha256_52b_no_lf": record0_sha_nolf,
        "sha256_53b_with_lf": record0_sha,
        "canonical_dealt_sha256": fixtures_b1[0]["dealt_canonical_sha256"],
        "expected_canonical_dealt_sha256": "935879b0483480ea8f936cdc2c2b236d532d2b9531f800b19173f8dd50d620e3",
    }

    for pool_name, fixtures, indices in (
        ("bureau1", fixtures_b1, BUREAU1_INDICES),
        ("bureau3", fixtures_b3, BUREAU3_INDICES),
    ):
        out_path = os.path.join(OUT, "golden_%s.json" % pool_name)
        payload = {"meta": meta, "fixtures": fixtures}
        with open(out_path, "w", encoding="utf-8") as fh:
            json.dump(payload, fh, indent=1, ensure_ascii=True)
            fh.write("\n")
        print("wrote %s fixtures=%d sha256=%s" % (out_path, len(fixtures), sha256_bytes(open(out_path, "rb").read())))

    ok = fixtures_b1[0]["dealt_canonical_sha256"] == meta["record0"]["expected_canonical_dealt_sha256"]
    print("record0 canonical digest match:", ok)
    if not ok:
        sys.exit(1)


if __name__ == "__main__":
    main()
