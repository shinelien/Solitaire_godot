class_name LegacyDealBuilder
extends RefCounted

## Builds the initial dealt board from the decoder's draw-order ids,
## replicating legacy SpriteManager::initKCardAfter / initWaitCard:
##   - tableau columns 1..7, dealt column-first from the reversed sequence;
##   - last card of each column face-up;
##   - the remaining 24 ids become the stock, in order.

static func build(ids: Array[int]) -> Dictionary:
	var tableau: Array = []
	tableau.resize(PileType.TABLEAU_COUNT)
	for i in PileType.TABLEAU_COUNT:
		var col_arr: Array[CardData] = []
		tableau[i] = col_arr
	var stock: Array[CardData] = []
	var idx := 0
	for col in PileType.TABLEAU_COUNT:
		var col_cards: Array[CardData] = tableau[col]
		for row in range(col + 1):
			var c := CardData.from_id(ids[idx])
			c.face_up = (row == col)
			col_cards.push_back(c)
			idx += 1
	while idx < ids.size():
		stock.push_back(CardData.from_id(ids[idx]))
		idx += 1
	return {"tableau": tableau, "stock": stock}
