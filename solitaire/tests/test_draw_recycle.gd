extends BaseTest

## Draw-1 / Draw-3 order, last partial packet, and unlimited recycle
## semantics through both the raw executor and the controller.

func _card(id: int, face_up: bool = false) -> CardData:
	var c := CardData.from_id(id)
	c.face_up = face_up
	return c

func test_draw_order_through_full_cycle() -> void:
	# Legacy: stock = draw-order tail R[28..51]; top of stock is the LAST
	# element; draws pop the top; recycle reverses the waste back onto stock.
	var ids := LegacyDealDecoder.decode("GZ[>6bcTS_KMDBXVR:<\\^0@C7IQFEO?Ja4WAP8]U`1=HL5YN92;3")
	var built := LegacyDealBuilder.build(ids)
	var st := GameState.new()
	st.draw_mode = GameConfig.DRAW1
	st.tableau = built["tableau"]
	st.stock = built["stock"]
	var expected_stock: Array = []
	for k in range(28, 52):
		expected_stock.push_back(ids[k])
	check_eq(st.stock.size(), 24, "stock size")
	for i in 24:
		check_eq(st.stock[i].id, expected_stock[i], "stock order %d" % i)
	# Full draw sequence: waste must receive ids R[51], R[50], ..., R[28].
	var drawn: Array[int] = []
	var guard := 0
	while not st.stock.is_empty() and guard < 64:
		check_true(MoveExecutor.apply(st, Move.draw()).ok, "draw")
		drawn.push_back(st.waste[st.waste.size() - 1].id)
		guard += 1
	check_eq(drawn.size(), 24, "24 draws")
	for i in 24:
		check_eq(drawn[i], ids[51 - i], "draw order %d" % i)
	check_true(st.stock.is_empty(), "stock exhausted")
	# Recycle: legacy resetWaitCard appends waste top-first, so the next draw
	# order is the reversed waste (the oldest waste card first).
	check_true(MoveExecutor.apply(st, Move.recycle()).ok, "recycle")
	check_true(st.waste.is_empty(), "waste emptied")
	for i in 24:
		check_eq(st.stock[i].id, drawn[drawn.size() - 1 - i], "recycled stock order %d" % i)
	# Recycle again after exhausting: unlimited.
	while not st.stock.is_empty():
		check_true(MoveExecutor.apply(st, Move.draw()).ok, "draw cycle 2")
	check_true(MoveExecutor.apply(st, Move.recycle()).ok, "recycle cycle 2")
	check_eq(st.stock.size(), 24, "recycled again")

func test_draw3_last_partial_packet() -> void:
	var st := GameState.new()
	st.draw_mode = GameConfig.DRAW3
	st.stock = typed_col([_card(0), _card(1), _card(2), _card(3), _card(4)])
	check_true(MoveExecutor.apply(st, Move.draw()).ok, "first draw3")
	check_eq(st.waste.size(), 3, "drew 3")
	check_eq(st.stock.size(), 2, "left 2")
	check_true(MoveExecutor.apply(st, Move.draw()).ok, "second draw3")
	check_eq(st.waste.size(), 5, "partial packet of 2")
	check_true(st.stock.is_empty(), "stock empty")
	check_false(MoveExecutor.apply(st, Move.draw()).ok, "draw on empty stock rejected")

func test_controller_draw_and_recycle() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	# After the initial draw the waste has 1 card (legacy auto-draw).
	check_eq(ctrl.state.waste.size(), 1, "initial draw produced waste")
	check_eq(ctrl.state.stock.size(), 23, "stock after initial draw")
	var before := ctrl.state.deep_copy()
	check_true(ctrl.request_draw(), "draw command")
	check_eq(ctrl.state.waste.size(), 2, "waste grew")
	check_eq(ctrl.state.draw_count, 2, "draw counter counts both initial+manual")
	check_false(before.equals(ctrl.state), "state changed")
	# Illegal draw on empty stock is a no-op.
	var st := GameState.new()
	st.draw_mode = GameConfig.DRAW1
	ctrl.state = st
	check_false(ctrl.request_draw(), "draw on empty stock rejected")
	check_false(ctrl.request_recycle(), "recycle on empty waste rejected")
	check_true(ctrl.state.equals(st), "no-op state unchanged")

func test_controller_initial_draw_matches_legacy() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW3, 0, ""), "new deal draw3")
	check_eq(ctrl.state.waste.size(), 3, "draw3 initial waste")
	check_eq(ctrl.state.stock.size(), 21, "draw3 initial stock")
	check_true(ctrl.state.waste[2].face_up, "waste cards face-up")
