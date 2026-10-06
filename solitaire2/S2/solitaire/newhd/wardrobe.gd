class_name NewHDWardrobe
extends Node
var game: NewHDGame
var dialog: NewHDScene
var current_tab := "back"
var preview: AudioStreamPlayer


func configure(owner_game: NewHDGame, view: NewHDScene) -> void:
	game = owner_game
	dialog = view
	preview = AudioStreamPlayer.new()
	add_child(preview)
	for name in ["Panel_view_bg", "Panel_view_Changjing", "Panel_view_zhengmian", "Panel_view_magic", "Panel_view_music", "Panel_teach", "Panel_confirm", "FileNode_BagItem1"]:
		game.hide_node(dialog, name)
	for pair in [["Button_tab2_0", "face"], ["Button_tab1", "background"], ["Button_tab3", "back"], ["Button_tab2", "face"], ["Button_tab4", "magic"], ["Button_tab5", "music"]]:
		var button := dialog.find_child(pair[0], true, false) as TextureButton
		button.set_meta("local_action", func(): show_tab(pair[1]))
	show_tab("back")

func show_tab(tab: String) -> void:
	current_tab = tab
	preview.stop()
	for pair in [["Button_tab1", "background"], ["Button_tab3", "back"], ["Button_tab2", "face"], ["Button_tab4", "magic"], ["Button_tab5", "music"]]:
		(dialog.find_child(pair[0], true, false) as TextureButton).disabled = tab == pair[1]
	var scroller := dialog.find_child("ListView_bg", true, false) as ScrollContainer
	scroller.scroll_vertical = 0
	var content := scroller.get_node("Content") as Control
	for child in content.get_children():
		content.remove_child(child)
		child.queue_free()
	var count := 26 if tab == "background" else 35 if tab == "back" else 6 if tab == "face" else 20 if tab == "music" else 1
	var columns := 3 if tab in ["back", "background"] else 2 if tab == "face" else 1
	var height := 450 if tab == "background" else 400 if tab == "back" else 450 if tab == "face" else 210 if tab == "music" else 660
	content.custom_minimum_size = Vector2(scroller.size.x, ceilf(float(count) / columns) * height)
	for index in count:
		var item := game.scene("2020BagItem_gameBg" if tab == "background" else "2020BagItem_cardBg" if tab == "back" else "2020BagItem_cardFace" if tab == "face" else "2020BagItem_music" if tab == "music" else "2020BagItem_magic")
		content.add_child(item)
		item.position = Vector2((index % columns + .5) * scroller.size.x / columns, (index / columns + .5) * height)
		if tab == "background":
			background_item(item, index)
		elif tab == "back":
			back_item(item, index)
		elif tab == "face":
			face_item(item, index)
		elif tab == "music":
			music_item(item, index)
		else:
			(item.find_child("panel_Magic", true, false) as CanvasItem).show()
			game.text(item, "Text_MagicNum", "x%d" % game.profile.magic)
			(item.find_child("Button_magic", true, false) as TextureButton).pressed.connect(magic_shop)

func show_node(view: Node, name: String, value: bool) -> void:
	var node := view.find_child(name, true, false) as CanvasItem
	if node != null:
		node.visible = value

func back_item(item: NewHDScene, index: int) -> void:
	show_node(item, "panel_item", true)
	show_node(item, "img_new_bg", false)
	var image := item.find_child("img_card_bg", true, false) as TextureRect
	var center := image.position + image.size / 2
	image.texture = NewHDAtlas.texture("card_bg_%d.png" % index)
	image.size = image.texture.get_size()
	image.position = center - image.size / 2
	image.pivot_offset = image.size / 2
	var owned: bool = index in game.profile.skin_owned.back
	var unlocked := game.profile.level >= game.profile.unlock_level("back", index)
	show_node(item, "Button_buy", false)
	show_node(item, "Button_card_bg", int(game.profile.settings.back) != index)
	show_node(item, "Sprite_used_bg", int(game.profile.settings.back) == index)
	show_node(item, "ui_Lock0_Changjing", not owned)
	show_node(item, "Text_buy", not unlocked)
	show_node(item, "BitmapFontLabel_1", unlocked)
	game.text(item, "Text_card_bg", "使用" if owned else "尚未获得")
	game.text(item, "BitmapFontLabel_1", "")
	game.text(item, "Text_buy", "%d级解锁" % game.profile.unlock_level("back", index))
	for name in ["Button_card_bg", "Button_card_bgA"]:
		(item.find_child(name, true, false) as TextureButton).pressed.connect(func():
			if index in game.profile.skin_owned.back:
				game.profile.advance_task(5)
				game.profile.settings.back = index
				game.profile.save()
				game.board.set_skins(game.profile)
				show_tab("back"))

func purchase(kind: String, index: int) -> void:
	var result := game.profile.buy_skin(kind, index)
	game.message("已获得" if result.ok else str(result.reason))
	show_tab(kind)

func face_item(item: NewHDScene, index: int) -> void:
	show_node(item, "panel_zhengmian", true)
	show_node(item, "img_new_face", false)
	show_node(item, "Image_used_face", int(game.profile.settings.face) == index)
	var count := game.profile.face_count(index)
	game.text(item, "Text_faceNum", "%d/52" % count)
	(item.find_child("LoadingBar_face", true, false) as TextureProgressBar).value = count * 100.0 / 52
	for pair in [["img_card_face1", 11], ["img_card_face2", 12]]:
		var placeholder := item.find_child(pair[0], true, false) as Control
		placeholder.self_modulate.a = 0
		var card := NewHDCard.new()
		placeholder.add_child(card)
		card.position = placeholder.size / 2
		card.configure(pair[1], index, 0)
		card.show_face(true, false)
	(item.find_child("Button_zhengmian", true, false) as TextureButton).pressed.connect(func(): face_details(index))

func face_details(style: int) -> void:
	var detail := game.open_dialog("2020BagItem_1", "Start")
	detail.position = Vector2(540, 960)
	game.hide_node(detail, "Panel_card")
	game.hide_node(detail, "Button_3")
	var scroller := detail.find_child("ListView_card", true, false) as ScrollContainer
	var content := scroller.get_node("Content") as Control
	content.custom_minimum_size = Vector2(scroller.size.x, 13 * 320)
	game.text(detail, "Text_cardNum", "%d/52" % game.profile.face_count(style))
	(detail.find_child("LoadingBar_card", true, false) as TextureProgressBar).value = game.profile.face_count(style) * 100.0 / 52
	var use_all := detail.find_child("Button_card_item1_get", true, false) as TextureButton
	game.text(detail, "Text_card_item1_get", "使用已获得的牌")
	use_all.disabled = game.profile.face_count(style) == 0
	use_all.set_meta("local_action", func():
		game.profile.advance_task(6)
		game.profile.settings.face = style
		for id in 52:
			if game.profile.owns_face(style, id):
				game.profile.face_choices[str(id)] = style
		game.profile.save()
		game.board.set_skins(game.profile)
		game.close_dialog()
		show_tab("face"))
	content.custom_minimum_size = Vector2(scroller.size.x, 11 * 300)
	for id in 52:
		var card := NewHDCard.new()
		content.add_child(card)
		card.position = Vector2((id % 5 + .5) * scroller.size.x / 5, (id / 5 + .5) * 300)
		card.configure(id, style, 0)
		card.show_face(true, false)
		card.modulate.a = 1.0 if game.profile.owns_face(style, id) else .2

func music_item(item: NewHDScene, index: int) -> void:
	game.text(item, "Text_music", "音乐 %02d" % (index + 1))
	game.text(item, "Text_use", "使用" if index in game.profile.skin_owned.music else "尚未获得")
	var owned: bool = index in game.profile.skin_owned.music
	var unlocked := game.profile.level >= game.profile.unlock_level("music", index)
	show_node(item, "Button_buy", false)
	show_node(item, "Button_music", true)
	show_node(item, "ui_Lock0_music", not owned)
	show_node(item, "Sprite_used_music", int(game.profile.settings.music_track) == index)
	show_node(item, "Image_new_music", false)
	game.text(item, "BitmapFontLabel_1", "")
	game.text(item, "Text_buy", "%d级解锁" % game.profile.unlock_level("music", index) if not unlocked else "")
	(item.find_child("Button_music_on", true, false) as TextureButton).pressed.connect(func():
		game.audio.stop()
		preview.stream = load("res://assets/newhd/music/bgm%d.mp3" % index)
		preview.play())
	(item.find_child("Button_music", true, false) as TextureButton).disabled = not owned
	(item.find_child("Button_music", true, false) as TextureButton).pressed.connect(func():
		game.profile.advance_task(7)
		game.profile.settings.music_track = index
		game.profile.save()
		show_tab("music")
		game.play_music())

func magic_shop() -> void:
	game.magic_shop(func(): show_tab("magic"))

func background_item(item: NewHDScene, index: int) -> void:
	show_node(item, "panel_Changjing", true)
	show_node(item, "img_new_gameBg", false)
	var image := item.find_child("Sprite_Changjing", true, false) as TextureRect
	var center := image.position + image.size / 2
	var icon := "game_bg_%d" % index if index <= 13 else "Map_%d" % (2 if index <= 16 else index - 14)
	image.texture = NewHDAtlas.texture("" + icon + ".png")
	image.size = Vector2(270, 260)
	image.position = center - image.size / 2
	image.pivot_offset = image.size / 2
	var owned: bool = index in game.profile.skin_owned.background
	var used := index == int(game.profile.settings.background)
	show_node(item, "Image_used_gameBg", used)
	show_node(item, "ui_Lock0_Changjing", not owned)
	image.modulate.a = 1 if owned else .2
	game.text(item, "Text_gameBg", "使用" if owned else "尚未获得")
	var button := item.find_child("Button_gameBg", true, false) as TextureButton
	button.disabled = not owned
	button.visible = not used
	button.pressed.connect(func():
		game.profile.advance_task(0)
		game.profile.settings.background = index
		game.profile.save()
		game.background.configure(game.profile)
		game.play_music()
		show_tab("background"))
	(item.find_child("Button_gameBgA", true, false) as TextureButton).disabled = true

func _exit_tree() -> void:
	if is_instance_valid(game) and is_instance_valid(game.audio):
		game.play_music()
