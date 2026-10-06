class_name NewHDTasks
extends Node
var game: NewHDGame
var dialog: NewHDScene

func configure(owner_game: NewHDGame, view: NewHDScene) -> void:
	game = owner_game
	dialog = view
	game.profile.refresh_tasks()
	for name in ["Panel_7", "Button_getGold", "Button_getDiamond", "Particle_crownlight_Box1", "Particle_crownlight_Box2", "Particle_crownlight_Box3"]:
		game.hide_node(dialog, name)
	refresh()

func refresh() -> void:
	var active: Array = game.profile.task_data.active.duplicate()
	for slot in 3:
		var item := dialog.find_child("FileNode_task%d" % (slot + 1), true, false) as NewHDScene
		item.visible = slot < active.size()
		if not item.visible:
			continue
		var id := int(active[slot])
		var count := int(game.profile.task_data.counts.get(str(id), 0))
		var maximum := game.profile.task_max(id)
		game.text(item, "Text_miaoshu", game.localize(str(100223 + id - 100 if id >= 100 else 100208 + id)))
		game.text(item, "Text_TaskNum1", "领取" if count >= maximum else "%d/%d" % [count, maximum])
		game.text(item, "Text_5", "")
		(item.find_child("LoadingBar_task1", true, false) as TextureProgressBar).value = 100.0 * count / maximum
		var button := item.find_child("Button_Task1", true, false) as TextureButton
		button.set_meta("local_action", func(): activate(id, item))
	var bar := dialog.find_child("LoadingBar_task", true, false) as TextureProgressBar
	bar.value = int(game.profile.task_data.rewards) % 3 * 100.0 / 3

func activate(id: int, item: NewHDScene) -> void:
	var result := game.profile.claim_task(id)
	if result.ok:
		var duration := item.play_clip("Start0")
		game.message("任务奖励：金币 +%d · 钻石 +%d" % [result.coins, result.diamonds])
		await get_tree().create_timer(duration).timeout
		if is_inside_tree():
			refresh()
		return
	game.close_dialog()
	if id in [0, 5, 6, 7]:
		game.wardrobe()
	elif id in [3, 10, 104, 105]:
		game.store()
	elif id in [2, 9, 102, 103, 106, 107] or id in range(11, 15):
		game.daily_selector()
	elif id == 8:
		game.level_selector()
	else:
		game.new_game()
