class_name LegacyDealDigest
extends RefCounted

## Canonical dealt-state digest (pure data). Pins the legacy deal identity:
##   sha256( columns ','-joined per column and '|'-joined across columns 0..6
##           + '#' + stock ids ','-joined )
## Legacy record 0 must yield 935879b0... (TD-fixed canonical hash).

const CANONICAL_RECORD0_SHA256 := "935879b0483480ea8f936cdc2c2b236d532d2b9531f800b19173f8dd50d620e3"


static func dealt_text(state: GameState) -> String:
	if state == null:
		return ""
	var columns: PackedStringArray = []
	for col in state.tableau:
		var ids := col.ids()
		var joined: Array[String] = []
		for cid in ids:
			joined.append(str(cid))
		columns.append(",".join(joined))
	var head := "|".join(columns)
	var stock_ids := state.stock.ids()
	var stock_parts: Array[String] = []
	for sid in stock_ids:
		stock_parts.append(str(sid))
	return head + "#" + ",".join(stock_parts)


static func dealt_sha256(state: GameState) -> String:
	var ctx := HashingContext.new()
	ctx.start(HashingContext.HASH_SHA256)
	ctx.update(dealt_text(state).to_utf8_buffer())
	return ctx.finish().hex_encode()
