class_name GameState
extends RefCounted

## 一局进行中牌局的唯一事实来源（纯数据，无 Node 依赖）。
## 持有 stock/waste/tableau[7]/foundation[4]、各计数器及牌局身份。
## tableau/foundation 使用 Array[CardPile]，
## 因为 GDScript 不支持嵌套类型数组（如 Array[Array[int]]）。

const DRAW1 := 1
const DRAW3 := 3
const TABLEAU_COUNT := 7
const FOUNDATION_COUNT := 4


enum GameStatus {
	IN_PROGRESS = 0,
	## 胜利状态由 WP-06 规则引擎判定：四座基础牌堆全部收满。
	## 设计上不存在 LOST 状态（经典 Klondike 在最后一步前都仍有胜机；
	## 自行猜测 LOST 属于解算器决策，而非游戏状态）。
	WON = 1,
}

## 发牌堆：翻牌时从中取牌（盖牌）。
var stock: CardPile = CardPile.new()
## 弃牌堆：翻 1/翻 3 后明牌所在处。
var waste: CardPile = CardPile.new()
## 七列工作区，列号 0..6。
var tableau: Array[CardPile] = []
## 四座基础牌堆，槽位 0..3。
var foundation: Array[CardPile] = []
## 翻牌张数：1（翻 1）或 3（翻 3）。
var draw_count: int = DRAW1
## 发牌堆完整重翻（recycle）的次数。
var stock_passes: int = 0
## 已执行的有效移动次数。
var move_count: int = 0
## 当前得分。
var score: int = 0
## 当前牌局状态（进行中/胜利）。
var game_status: GameStatus = GameStatus.IN_PROGRESS

## 牌局身份（WP-05）：来源牌池文件、从 0 开始的序号、固定对象路径。
var deal_pool: String = ""
var deal_index: int = -1
var deal_source: String = ""


## 初始化：清空并创建 7 列表格区与 4 座基础堆。
func _init() -> void:
	tableau.clear()
	for i in TABLEAU_COUNT:
		tableau.append(CardPile.new())
	foundation.clear()
	for i in FOUNDATION_COUNT:
		foundation.append(CardPile.new())


## 按列号（0..6）取表格区牌堆；列号越界返回 null。
func tableau_pile(col: int) -> CardPile:
	if col < 0 or col >= TABLEAU_COUNT:
		return null
	return tableau[col]


## 按槽位（0..3）取基础牌堆。槽位是动态的：槽位不与特定花色绑定，
## 当前正在收牌的花色由槽内牌决定。
func foundation_pile(slot: int) -> CardPile:
	if slot < 0 or slot >= FOUNDATION_COUNT:
		return null
	return foundation[slot]


## 稳定的牌局标识，如 "bureau1#0"。
func deal_key() -> String:
	return "%s#%d" % [deal_pool, deal_index]


## 真正的深拷贝：每个牌堆与每张 CardData 都是全新实例，
## 源状态与克隆之间不存在任何共享可变对象。
func clone() -> GameState:
	var out := GameState.new()
	out.stock = stock.clone()
	out.waste = waste.clone()
	for i in TABLEAU_COUNT:
		out.tableau[i] = tableau[i].clone()
	for i in FOUNDATION_COUNT:
		out.foundation[i] = foundation[i].clone()
	out.draw_count = draw_count
	out.stock_passes = stock_passes
	out.move_count = move_count
	out.score = score
	out.game_status = game_status
	out.deal_pool = deal_pool
	out.deal_index = deal_index
	out.deal_source = deal_source
	return out


## 当前牌局容器中持有的总牌数。
func total_card_count() -> int:
	var n := stock.size() + waste.size()
	for pile in tableau:
		n += pile.size()
	for pile in foundation:
		n += pile.size()
	return n


## 返回牌局内全部牌的 id，顺序按容器排列：
## stock（底→顶）、waste（底→顶）、各 tableau 列（底→顶）、各 foundation。
func all_card_ids() -> Array[int]:
	var out: Array[int] = []
	out.append_array(stock.ids())
	out.append_array(waste.ids())
	for pile in tableau:
		out.append_array(pile.ids())
	for pile in foundation:
		out.append_array(pile.ids())
	return out


## 确定性结构相等判断（比较各堆 id、翻面状态及全部标量字段）。
func content_equals(other: GameState) -> bool:
	if other == null:
		return false
	if not stock.content_equals(other.stock) or not waste.content_equals(other.waste):
		return false
	for i in TABLEAU_COUNT:
		if not tableau[i].content_equals(other.tableau[i]):
			return false
	for i in FOUNDATION_COUNT:
		if not foundation[i].content_equals(other.foundation[i]):
			return false
	return (
		draw_count == other.draw_count
		and stock_passes == other.stock_passes
		and move_count == other.move_count
		and score == other.score
		and game_status == other.game_status
		and deal_pool == other.deal_pool
		and deal_index == other.deal_index
		and deal_source == other.deal_source
	)
