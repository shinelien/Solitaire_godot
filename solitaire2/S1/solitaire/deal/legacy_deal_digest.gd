class_name LegacyDealDigest
extends RefCounted

## 已发牌状态的规范摘要（纯数据）。固定旧版牌局身份：
##   sha256( 各列 id 以 ',' 连接、七列间以 '|' 连接
##            + '#' + stock id 以 ',' 连接 )
## 旧版记录 0 必须得到 935879b0...（TD 裁定规范哈希）。

const CANONICAL_RECORD0_SHA256 := "935879b0483480ea8f936cdc2c2b236d532d2b9531f800b19173f8dd50d620e3"


## 生成已发牌状态的规范文本：
## "列0|列1|...|列6#stock_ids"（列内与 stock 内 id 以逗号连接）。
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


## 计算 dealt_text 的 SHA-256（十六进制），用于确定性校验/身份固定。
static func dealt_sha256(state: GameState) -> String:
	var ctx := HashingContext.new()
	ctx.start(HashingContext.HASH_SHA256)
	ctx.update(dealt_text(state).to_utf8_buffer())
	return ctx.finish().hex_encode()
