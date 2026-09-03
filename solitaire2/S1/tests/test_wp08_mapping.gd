@tool
extends McpTestSuite


func suite_name() -> String:
	return "wp08_mapping"


func test_face_mapper_region_names_are_stable() -> void:
	assert_eq(LegacyFaceMapper.base_region(), "card_fronts", "shared face base region")
	assert_eq(LegacyFaceMapper.back_region(), "card_bg_5", "documented card back region")
	assert_eq(LegacyFaceMapper.rank_region(1), "card_01", "ace rank region")
	assert_eq(LegacyFaceMapper.rank_region(10), "card_010", "ten rank region")
	assert_eq(LegacyFaceMapper.rank_region(11), "card_011", "jack rank region")
	assert_eq(LegacyFaceMapper.rank_region(13), "card_013", "king rank region")
	assert_eq(LegacyFaceMapper.suit_region(1, 0), "card_0_A", "suit A rank<=10")
	assert_eq(LegacyFaceMapper.suit_region(10, 1), "card_0_B", "suit B rank<=10")
	assert_eq(LegacyFaceMapper.suit_region(11, 2), "card_0_C11", "suit C court")
	assert_eq(LegacyFaceMapper.suit_region(13, 3), "card_0_D13", "suit D court")


func test_face_mapper_red_parity() -> void:
	assert_true(LegacyFaceMapper.is_red_suit(1), "hearts red")
	assert_true(LegacyFaceMapper.is_red_suit(3), "diamonds red")
	assert_false(LegacyFaceMapper.is_red_suit(0), "spades black")
	assert_false(LegacyFaceMapper.is_red_suit(2), "clubs black")


func test_face_parts_dictionary_shape() -> void:
	var parts := LegacyFaceMapper.face_parts(13, 1)
	assert_eq(parts.base, "card_fronts", "base part")
	assert_eq(parts.rank, "card_013", "rank part")
	assert_eq(parts.suit, "card_0_B13", "suit part")
	assert_true(parts.red, "king of hearts red")


func test_every_face_region_exists_in_exported_sheets() -> void:
	for id in 52:
		var card := CardData.new(id, true)
		var parts := LegacyFaceMapper.face_parts(card.rank, card.suit)
		assert_true(
			LegacyAtlas.known_region(LegacyFaceMapper.ATLAS_FACES_IMAGE, LegacyFaceMapper.ATLAS_FACES_FILE, parts.base),
			"base region exists for id %d" % id
		)
		assert_true(
			LegacyAtlas.known_region(LegacyFaceMapper.ATLAS_FACES_IMAGE, LegacyFaceMapper.ATLAS_FACES_FILE, parts.rank),
			"rank region %s exists for id %d" % [parts.rank, id]
		)
		assert_true(
			LegacyAtlas.known_region(LegacyFaceMapper.ATLAS_FACES_IMAGE, LegacyFaceMapper.ATLAS_FACES_FILE, parts.suit),
			"suit region %s exists for id %d" % [parts.suit, id]
		)
	assert_true(
		LegacyAtlas.known_region(LegacyFaceMapper.ATLAS_BACK_IMAGE, LegacyFaceMapper.ATLAS_BACK_FILE, LegacyFaceMapper.back_region()),
		"back region exists"
	)


func test_face_textures_non_null_for_every_card() -> void:
	for id in 52:
		var textures := LegacyAtlas.face_textures(id)
		assert_true(textures.base != null, "base texture id %d" % id)
		assert_true(textures.suit != null, "suit texture id %d" % id)
		assert_true(textures.rank != null, "rank texture id %d" % id)
		assert_true(textures.back != null, "back texture id %d" % id)
		var card := CardData.new(id, true)
		assert_eq(bool(textures.red), LegacyFaceMapper.is_red_suit(card.suit), "red parity id %d" % id)


func test_card_rank_layout_constants_match_legacy_face() -> void:
	assert_eq(CardView.RANK_CELL, 56, "rank glyph native cell is 56x56 (legacy Sprite_num)")
	assert_eq(CardView.RANK_CELL_CENTER_X, 28, "legacy Sprite_num anchor center x = 28")
	assert_eq(CardView.DOUBLE_TAP_MS >= 350 and CardView.DOUBLE_TAP_MS <= 500, true, "double threshold in conventional 350..500ms range")
	assert_eq(CardView.DOUBLE_TAP_MS, 450, "production double-click threshold 450ms")


func test_every_rank_region_native_size_is_56x56() -> void:
	for rank in range(1, 14):
		var region := LegacyAtlas.region(
			LegacyFaceMapper.ATLAS_FACES_IMAGE,
			LegacyFaceMapper.ATLAS_FACES_FILE,
			LegacyFaceMapper.rank_region(rank)
		)
		assert_true(region.ok, "rank region card_0%02d exists" % rank)
		var tex: AtlasTexture = region.texture
		var native := tex.get_size()
		assert_eq(native, Vector2(CardView.RANK_CELL, CardView.RANK_CELL), "rank region %s is 56x56 native" % LegacyFaceMapper.rank_region(rank))


func test_card_rank_layer_displayed_at_native_56x56_top_left() -> void:
	for id in 52:
		var card := CardData.new(id, true)
		var view := CardView.new()
		view.set_size(Vector2(BoardGeometry.CARD_W, BoardGeometry.CARD_H))
		view.configure(id, true, LegacyAtlas.face_textures(id), {})
		assert_eq(view.rank_display_size(), Vector2(CardView.RANK_CELL, CardView.RANK_CELL), "rank layer display size native for id %d" % id)
		assert_eq(view.rank_rect(), Rect2(0, 0, CardView.RANK_CELL, CardView.RANK_CELL), "rank layer anchored card top-left for id %d" % id)
		var rank_texture: AtlasTexture = LegacyAtlas.face_textures(id).rank
		assert_eq(view.rank_display_size(), rank_texture.get_size(), "no scaling: display size == texture native size for id %d" % id)


func test_face_down_card_has_no_rank_layer_visible() -> void:
	var view := CardView.new()
	view.set_size(Vector2(BoardGeometry.CARD_W, BoardGeometry.CARD_H))
	view.configure(7, false, LegacyAtlas.face_textures(7), {})
	assert_eq(view.rank_display_size(), Vector2.ZERO, "face-down card hides the rank layer")
	assert_eq(view.rank_rect(), Rect2(), "face-down rank rect is empty")
