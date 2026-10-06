class_name CardData
extends RefCounted

## 纸牌数据（纯数据，WP-05 CORE-001）。不依赖 Node/Control/Texture。
## 身份约定：id 范围 0..51；rank = id % 13 + 1；suit = id / 13
## （0=黑桃, 1=红心, 2=梅花, 3=方块）。

const MIN_ID := 0
const MAX_ID := 51
const SUIT_COUNT := 4
const RANK_COUNT := 13

var id: int = 0
var rank: int = 1
var suit: int = 0
var face_up: bool = false


## 构造牌：由 id 推导点数与花色，可选设置初始翻面状态。
func _init(p_id: int = 0, p_face_up: bool = false) -> void:
	id = p_id
	rank = p_id % RANK_COUNT + 1
	suit = p_id / RANK_COUNT
	face_up = p_face_up


## 深拷贝：返回一张身份完全相同的新牌（作为深拷贝的基础构件）。
func clone() -> CardData:
	return CardData.new(id, face_up)


## 校验：id 位于 [0,51] 且点数/花色与身份约定一致时返回 true。
func is_valid() -> bool:
	return id >= MIN_ID and id <= MAX_ID and rank == id % RANK_COUNT + 1 and suit == id / RANK_COUNT


## 相等判断：仅当两张牌的 id 与翻面状态都相同时视为相等。
func equals(other: CardData) -> bool:
	if other == null:
		return false
	return id == other.id and face_up == other.face_up


## 人类可读字符串，如 "S1U"（黑桃 A、翻开）/ "D13D"（方块 K、盖牌）。
func _to_string() -> String:
	var color := "D"
	if suit == 0:
		color = "S"
	elif suit == 1:
		color = "H"
	elif suit == 2:
		color = "C"
	return "%s%d%s" % [color, rank, "U" if face_up else "D"]
