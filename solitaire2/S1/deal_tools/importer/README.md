# WP-05 golden fixture generator

`generate_fixtures.py` precomputes the static Golden Deal fixtures consumed by
the MCP `McpTestSuite` under `res://tests/`.

## Independence

The generator is a standalone Python implementation of the documented legacy
spec. It reads only the raw records exported under `data/legacy/` and never
loads, preloads, or invokes the production GDScript `LegacyDealDecoder` /
`LegacyDealer`. Expectations therefore cannot silently inherit a bug shared
with the production decoder — the fixtures are a genuine cross-check.

Spec encoded here (mirrors legacy `SpriteManager.initCardIds`/`getCardId`):
record = 52 ASCII bytes 48..99; `id = byte - ord('0')`; consumption order =
`reverse(record)` consumed FIFO; tableau triangular column-major cols 0..6
with sizes 1..7 (each column's last dealt card face-up); remaining 24 ids form
the stock bottom-to-top with the top at the array end; dealt snapshot has an
empty waste; ready Draw-1 / Draw-3 snapshots pop `draw_count` cards off the
stock top (array end) and push them onto the waste in pop order (waste top =
last drawn).

## Output

- `data/legacy/golden/golden_bureau1.json` — 100 fixtures (indices 0..99).
- `data/legacy/golden/golden_bureau3.json` — 25 spread fixtures (indices
  0,1,2,3,4,9,49,99,199,499,999,1499,1999,2499,2999,3499,3999,4499,4700,
  4800,4900,4949,4970,4990,4998).

Each fixture stores source/pool/index, the raw deal, the 52-id consumption
order, the canonical dealt digest, the dealt tableau/stock/waste, and the
ready Draw-1 and Draw-3 stock+waste snapshots. `meta` also records the pool
record/byte counts, source SHA-256s and the record-0 canonical digest pinned
to `935879b0…`.

## Regenerate

    python3 deal_tools/importer/generate_fixtures.py

Deterministic: outputs are reproducible from the fixed raw records.
