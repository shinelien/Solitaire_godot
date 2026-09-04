class_name CardPile
extends RefCounted

## 有序牌堆（纯数据）。约定（与旧版及测试夹具一致）：
## 索引 0 = 牌堆底部，最后一个元素 = 牌堆顶部（可操作端）。
## 发牌后的 tableau 列与 stock 中：先发的牌位于索引 0，
## 翻开的牌/牌堆顶部牌位于数组末尾。

var _cards: Array[CardData] = []


## 当前牌堆中的牌数。
func size() -> int:
	return _cards.size()


## 牌堆是否为空。
func is_empty() -> bool:
	return _cards.is_empty()


## 顶牌（最后一个元素）；空堆返回 null。
func top() -> CardData:
	if _cards.is_empty():
		return null
	return _cards[_cards.size() - 1]


## 底牌（第一个元素）；空堆返回 null。
func bottom() -> CardData:
	if _cards.is_empty():
		return null
	return _cards[0]


## 取指定位置的牌；下标越界返回 null。
func card_at(index: int) -> CardData:
	if index < 0 or index >= _cards.size():
		return null
	return _cards[index]


## 压入顶牌：追加到数组末尾。
func add_top(card: CardData) -> void:
	if card != null:
		_cards.append(card)


## 压入底牌：插入到数组开头。
func add_bottom(card: CardData) -> void:
	if card != null:
		_cards.insert(0, card)


## 移除并返回顶牌；空堆返回 null。
func pop_top() -> CardData:
	if _cards.is_empty():
		return null
	return _cards.pop_back()


## 从顶部移除并返回 count 张牌，结果保持被移除区段的牌堆顺序
## （底→顶，即第一张是必须满足目标点数/颜色规则的那张）。
## count <= 0 时返回空；count 超过牌堆长度时整堆移除。
func pop_top_n(count: int) -> Array[CardData]:
	var taken: Array[CardData] = []
	if count <= 0:
		return taken
	var n := mini(count, _cards.size())
	for i in n:
		taken.push_front(_cards.pop_back())
	return taken


## 移除并返回底牌；空堆返回 null。
func pop_bottom() -> CardData:
	if _cards.is_empty():
		return null
	return _cards.pop_front()


## 容器浅拷贝（CardData 引用被共享，不新建对象）。
func cards_snapshot() -> Array[CardData]:
	var out: Array[CardData] = []
	for card in _cards:
		out.append(card)
	return out


## 按牌堆顺序（底→顶）返回全部牌的 id。
func ids() -> Array[int]:
	var out: Array[int] = []
	for card in _cards:
		out.append(card.id)
	return out


## 深拷贝：新建牌堆，所有 CardData 均为克隆（无共享可变对象）。
func clone() -> CardPile:
	var out := CardPile.new()
	for card in _cards:
		out.add_top(card.clone())
	return out


## 从 id 列表按底→顶建堆；默认所有牌使用 `face_up` 翻面状态。
## 若提供了足够长的 `face_up_flags`，则按牌堆位置逐张覆盖翻面状态。
static func from_ids(ids: Array, face_up: bool = false, face_up_flags: Array = []) -> CardPile:
	var pile := CardPile.new()
	for i in ids.size():
		var flag := face_up
		if face_up_flags.size() > i:
			flag = face_up_flags[i]
		pile.add_top(CardData.new(int(ids[i]), flag))
	return pile


## 确定性内容相等判断：逐张比较 id 与翻面状态，且顺序一致。
func content_equals(other: CardPile) -> bool:
	if other == null or other.size() != size():
		return false
	for i in _cards.size():
		if not _cards[i].equals(other.card_at(i)):
			return false
	return true
