# WP-06 证据包：CORE-002/003/004 Rules + MoveExecutor + Snapshot Undo + Draw1/Draw3

- 合同：`docs/sol/施工合同.md`（S2 v1.0，§4/§5/§6 WP-06、§8 验收矩阵）；worker-order `docs/sol/worker-order-s2-classic-2d.md`；WP-06 开工令（负责人发布，含“WP-05 证据已确认”）
- 规则基线：SOL 4.5.2 + 通用执行者连续执行合同 3.2 + 每 WP 证据确认门；计分/翻牌/回收事实以 WP-05 已验证的固定 SpriteManager.cpp 行为为准
- 阶段：`S2-CLASSIC-2D-CORE-LOOP`；状态：**WP-06 修正 2 施工完成、修正 3（残留命名收尾）完成、待证据确认**（WP-06 保持“待证据确认”，未获 TD 确认；WP-07/WP-08 保持依赖锁定）
- 执行者运行时身份：DeepSeek（deepseek-v4-flash）
- 环境：macOS Darwin arm64；Godot `4.6.2-stable (custom_build)`；Godot AI MCP 插件/服务器 `3.2.4`；时间 2026-09-03

## 0. 修正 2 摘要（Foundation 槽位语义：固定槽位=suit → 动态槽位；Sol 架构裁定）

Sol 复核固定产品对象 `WTF-Solitaire@74f51802c8a5356223c84d8aff81c3300f190a43` 的 `Classes/manager/SpriteManager.cpp`（blob `075f4a0dc9a9cf6c2ebce3bdde0759a41849fdea`，6486 行）`int SpriteManager::checkACardPos(CardSprite * card)`（第 1769~1796 行）后裁定：foundation[4] 是 **4 个动态槽**，不是预绑定花色。修正 1 的“槽位索引即花色”规则/API 口径产品不兼容，**不予验收**；修正 2 把该语义纠正为动态槽，同时**保留**修正 1 有效的 Move 形状门与跨容器隔离改进。

### 固定旧源证据摘记（legacy-reference note，只引证必要行为与出处）

固定对象内该函数逐行行为（仅引证必要范围）：

```
int SpriteManager::checkACardPos(CardSprite * card)
{
	int indexA = 4;
	if (card->getPosId() == CARD_POS_A) indexA = card->getColNum() + 1;
	for (int i = 0; i < indexA; i++) {
		if (aCardVector[i].size() == 0) {
			if (card->getNumber() == 1) return i;      // 空槽接受任意 Ace（不查花色）
		} else {
			auto lastCard = aCardVector[i].back();
			if (lastCard && lastCard->checkAPos(card)) return i;  // 非空槽由顶张的 checkAPos 决定
		}
	}
	return -1;
}
```

`CardSprite::checkAPos` 同对象内判据：`number + 1 == targetC->getNumber() && colorType == targetC->getColorType()`（与顶张**同花色且恰高 1 级**）。出处：固定对象 `74f51802…`，`Classes/manager/SpriteManager.cpp` 第 1769~1796 行；该函数扫描槽 i（默认 indexA=4），**从不把槽位索引与花色绑定**：空槽任何 Ace 可入、非空槽仅接受“与当前顶张同花色、rank 恰高 1”的牌。S2 合同口径“foundation 同花色递增；空槽仅 A”与之一致（不涉及槽=suit）。

### 修正内容（相对修正 1）

1. **RulesEngine foundation 目的地（T2F/W2F 共用 `_check_foundation_destination`）**：移除 `card.suit == 槽位索引` 前置门；空槽接受**任意花色、face-up 的 Ace**（非 A → `foundation_requires_ace`）；非空槽要求落子卡与**槽顶同花色且恰高 1 级**（花色不符 → `foundation_suit`，级差/同级/跳级 → `foundation_rank`）；槽顶 face-down/缺失 → 畸形态拒绝（`face_down_card`/`invalid_state`）。
2. **F2T 源（`_validate_foundation_to_tableau`）**：只按**源槽索引**取槽顶；移除“槽顶 suit 必须等于源槽位索引”门；槽顶 face-up 即可按经典 tableau 目的地规则落子（空列仅 K、非空列降 1 级且红黑交替）——槽由何种花色“拥有”不再影响其顶张可否回到 tableau。
3. **WinEvaluator**：改为**槽序无关**判胜——每槽必须恰持 13 张 face-up、物理身份恰为 `suit*13..suit*13+12`（位置 p 满足 `id==suit*13+p`、`rank==p+1`、`suit` 一致）A→K 升序的完整同花色 run；四槽花色互异（四槽完整 + 花色互异 ⇒ 花色集必为 {0,1,2,3}）。**整花色换槽可胜**；重复花色、混合、缺短、乱序、face-down、身份不符不判胜。
4. **公开命名/文档**：GameState/Move/Rules/tests 中 foundation 相关索引一律表述为 `slot`/`foundation_index`（“foundation slot”），移除“foundation suit / slot index is the suit / 槽位索引即花色”等误导措辞；MoveKind/Location 结构与形状门不变（见 §3）。
5. **保留（修正 1 有效项，不回归）**：坐标/形状门先于一切棋盘合法性 + `invalid_location`/`invalid_count`；`no_shared_state` 全容器/全位置交叉比较；`state_isolation` suite；执行器失败零变异零快照；生成翻牌显式原子。

修正 2 取代修正 1 **仅限 foundation 槽位绑定这一语义**；Move 形状门、隔离修复、计分、撤销、抽/回收均非本修正对象（未改）。

### 修正 3（残留命名收尾，2026-09-03，Sol 复核发现后追加）

Sol 独立复核本证据时发现修正 2 记“未改”的 `move_executor.gd` 内部仍残留 foundation **地址**参数命名 `suit`/`from_suit`（`_apply_tableau_to_foundation(state, from_col, suit)`、`_apply_waste_to_foundation(state, suit)`、`_apply_foundation_to_tableau(state, from_suit, to_col)`，内部对应 `foundation_pile(suit)`/`foundation_pile(from_suit)`），与本证据“公开命名统一为 slot/foundation_index、地址整数即动态槽索引”的表述不符。修正 3 **仅**把这三处 foundation 地址参数及局部用法改名为 `slot`/`from_slot`（调用点不变，仍按位置传 `source_index`/`target_index`），**零行为变化**、无测试改动。

全 `solitaire/**` 复核确认已无 `foundation_pile(suit)`、`from_suit`、`target_suit`、`to_suit` 或任何把“槽位索引”当作“花色”的地址命名。保留且属允许：稳定错误码 `foundation_suit`（语义 = 非空槽顶花色不符）、规则/判胜注释中“某槽当前拥有之花色”的表述、`_complete_run_suit` 返回的槽内容花色。修正 2 全部语义决定原样保留（动态槽目的地/源、槽序无关判胜、形状门与隔离改进不变）。

## 1. 会话与工程路径（MCP）

- 同一编辑器会话（project_path = `/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1/`，精确目标路径）；Godot `4.6.2-stable (custom_build)`；插件/服务器 `3.2.4`；play_state stopped（**全程未运行游戏**）；readiness ready；current_scene `res://mcp_verify.tscn`（基础设施夹具原样）。
- 修正流程：filesystem `scan` settled（global_class_count 71）→ MCP `test_run(verbose=true)` 全量 **passed=121 / failed=0 / skipped=0**（11 suites）→ MCP editor log = 0 行；无 parse/运行时错误，编辑器进程内零诊断。

## 2. 改动文件（精确清单，含 `.gd.uid`）

全部改动仅在目标工程内；无 scene/project.godot/addon/fixture/夹具改动。**修正 2 相对修正 1 改动 4 个产品 .gd + 3 个测试 .gd**（修正 2 后当前字节 SHA-256）：

```
solitaire/core/game_state.gd                f8305022881799c3f62c842ec31077d8cf48bc5815015a45fb850cc78c9f1389  (修正2: foundation_pile(slot) 命名/注释)
solitaire/core/moves/move.gd                fe144b8e402b11b22d5ac2a22a5f21b5e60b6ea5573679df9676ddd4f57d370b  (修正2: 工厂参数 slot + description/头注释)
solitaire/core/rules/rules_engine.gd        608abee47df318365ecb3600767077f64908d5ad44df2386ceec3fab9d410ce3  (修正2: 动态槽目的地/源)
solitaire/core/rules/win_evaluator.gd       50399425483921a026c2cc7644141a74e24982bba726d3f9eb5cd228d0038832  (修正2: 槽序无关唯一花色判胜)
tests/test_rules_engine.gd                  d679083d4e4b0ec8d384f52bf9cfc7d5c99e8d7f988386b01bd2548629b63c26  (修正2: 动态槽契约测试重写)
tests/test_score_win.gd                     5762b995564a467bb6ad10f72541cd14722f109fc583230d3667184e1205204f  (修正2: 换槽判胜/重复花色判负)
tests/test_move_executor.gd                 612293901304482b3b055c77c801fbd3f574c1fba415f36b5d2ffff5d3a844e8  (修正2: 动态槽端到端执行正负测试)
```

修正 3（2026-09-03，命名收尾；追加改动 1 个产品 .gd，当前字节 SHA-256）：

```
solitaire/core/moves/move_executor.gd        c2306da9360fcdeb3eabf33f079f5cbedf3bb7b8758eadd254ac191c6a6203de  (修正3: foundation 地址参数 suit→slot / from_suit→from_slot；行为零变化)
```

未改（修正 1 值保持，SHA-256 与修正 1 证据 §2 一致；该口径截至修正 2）：`card_pile.gd`、`move_batch.gd`、`move_execution_result.gd`、`legacy_score_policy.gd`、`move_validation_result.gd`（稳定码不变，`foundation_suit` 保留但仅表“非空槽顶花色不符”）、`snapshot_history.gd`、`card_state_testkit.gd`（`no_shared_state` 全容器交叉）、`test_move_model.gd`、`test_undo_history.gd`、`test_state_isolation.gd`。修正 2 中 `move_executor.gd` 未改；修正 3 起作为唯一改动文件（见上，其 `.gd.uid` 源伴随文件仍逐项在库、内容未重写），其余 product/test/数据/夹具字节未变。全部 16 个 WP-06 `.gd.uid` 源伴随文件逐项在库。

## 3. 公开接口/架构要点

- 分层延续：core（CardData/CardPile/GameState）→ moves/rules/state；**无 Presentation/Application 路径**（WP-07 未实现）。
- `GameState`：`foundation_pile(slot)`；文档明确槽为动态（`docs/sol/evidence` 与代码注释一致）；`FOUNDATION_COUNT=4` 不变。
- `Move`：`MoveKind`（8 玩法 + UNDO）+ 工厂 + `key()`。工厂参数 `tableau_to_foundation(from_col, slot)`、`waste_to_foundation(slot)`、`foundation_to_tableau(from_slot, to_col)`（参数名不再叫 suit；位置参数语义不变）。`description()` 用 “foundation slot %d”。Location 结构与形状门契约不变。
- `RulesEngine.validate`：形状门（**先于一切棋盘合法性**）→ 逐 kind 合法性（同修正 1 §3 所列每 kind 契约，未改）。稳定码集合不变（含 invalid_state/invalid_kind/invalid_index/invalid_location/self_move/empty_source/face_down_card/invalid_count/run_rank/run_color/dest_rank/dest_color/dest_requires_king/foundation_requires_ace/foundation_rank/foundation_suit/stock_empty/stock_not_empty/waste_empty/not_face_down/already_won/invalid_draw_count）。
- foundation 目的地（动态槽）：空槽任意花色 face-up Ace；非空槽同花色恰升 1 级；槽顶畸形（face-down/null）拒绝。F2T 源：槽顶 face-up 即按源槽索引取牌，经典 tableau 目的地规则。
- `WinEvaluator`：纯函数、槽序无关（§0.3）。
- `MoveExecutor.execute`/`execute_undo`/`SnapshotHistory`/`LegacyScorePolicy`/回收/翻牌语义与修正 1 一致（未改）；内部 foundation 地址参数修正 3 已统一为 `slot`/`from_slot`（命名收尾，调用点与语义零变化）；执行器在动态槽上端到端验证通过。

## 4. MCP 测试结果与诊断

- McpTestSuite 全量（修正 2 干净复跑，同一会话）：**passed=121 / failed=0 / skipped=0**，**11 suites**。
- McpTestSuite 全量（修正 3 干净复跑，同一会话）：**passed=121 / failed=0 / skipped=0**，**11 suites**，断言数与修正 2 完全一致（WP-06 888 / 全工程 1399）；命名修正零行为变化，测试文件零改动即全绿。
- 套件：core_model、golden_deal、legacy_dealer、legacy_decode、library_integrity（WP-05 保留 46/46 全绿）+ move_model、rules_engine、move_executor、snapshot_undo、score_win、state_isolation（WP-06 共 75 项测试）。
- 实测断言数（`test_run(verbose=true)` 逐项累计）：WP-05 = **511**（与 WP-05 证据一致，未变）；WP-06 = move_executor 371 + move_model 78 + rules_engine 221 + score_win 58 + snapshot_undo 149 + state_isolation 11 = **888**；**全量断言合计 1399**。相对修正 1（118 项测试/839 WP-06 断言）：净增 3 项测试、+49 条 WP-06 断言。
- 覆盖要点（修正 2 新增/改写，选列）：
  - **换槽判胜**：四整花色 run 以任意置换/旋转（每槽 suit≠槽位索引）分布 → `is_won` true 且 `update_status` 置 WON。
  - **任意花色 Ace → 空槽**：4 花色 × 4 空槽，T2F/W2F 共 32 项正断言全绿（suit≠slot 亦成）。
  - **非空槽错花色/错级**：异花色 2 上同色 A 槽 → `foundation_suit`（T2F/W2F 双源）；同级 A、跳级 3 → `foundation_rank`；同花 A 入槽后继续同花 2 合法（槽 0 拥有红心）。
  - **F2T 槽位而非花色**：槽 0 持红心 run（suit≠index）顶张 2 → 黑桃 3 合法；槽 0 持方块 K → 空 tableau 合法；face-down 槽顶 → `face_down_card`。
  - **重复整花色不判胜**：双黑桃+双红心、四黑桃 full runs → 不判胜且状态保持 IN_PROGRESS。
  - **face-down full pile / 混合 / 乱序 / 缺短 / 身份不符**不判胜（保留）。
  - 坐标/形状门、跨容器隔离、执行器零变异零快照等修正 1 改进全部保持绿色（回归证明）。
- 诊断：干净复跑 **MCP editor log = 0 行**；plugin log 无 error/warning；无 game log（全程未运行游戏）。修正全程无 parse/运行时错误。

## 5. 依赖/约束静态检查

- `rg "extends Node/Node2D/Node3D/Control|preload|ResourceLoader|\.tscn|Texture"` 于 `solitaire/core`、`solitaire/deal` 与测试 kit/isolation/golden_loader：仅命中注释（SpriteManager.cpp/checkACardPos 说明与 WP-05 头注释），无实际依赖。
- Core 无 hint/autocomplete/session/replay/UI/application 路径；WP-07 未实现、未启动。
- `project.godot` SHA-256 = `ef9dfc63fdcbe8273eb9edceff9216f7e592bcdcd95f011603b494c2fcf9e4c9`（权威字节基线，未改）；无 main scene/display/input。
- `mcp_verify.tscn` SHA-256 `56a31e49…`（夹具原样）；addon `268` 原始计数（267 固定对象 + 1 披露 `.DS_Store`）不变。

## 6. 旧工程 pre/post 与边界

- `WTF-Solitaire`：pre/post `git status --porcelain` 一致，零新增/零改动（固定对象只读，仅 `git show` 只读引证）；未 checkout/写入。
- 父仓库 diff 仅含 `solitaire2/S1` 授权目录（含本证据）；`solitaire/` 旧 Godot 工程零变化。
- 全程无 commit/push/下载/凭证/破坏性动作；未改动 addons、project.godot、fixtures、mcp_verify.tscn、`.godot`（仅编辑器可再生缓存随运行变动，已披露）。

## 7. 验收结果（§8 相关矩阵 / WP-06 十条 + Sol 架构裁定）

1. 成功状态改变均显式 Move/MoveBatch 且由 MoveExecutor 在克隆上执行；源 GameState 结构全等且与结果无共享可变牌/堆 ✓
2. 非法移动稳定 typed 拒绝且零变异；负例全覆盖 + WON 拒绝 + 畸形坐标/count 稳定 typed 拒绝且零变异零快照 ✓
3. 经典 foundation/tableau/waste/run/可达性正负测试全绿；**空 foundation 槽接受任意花色 face-up Ace（无槽=suit 绑定）；非空槽同花色升序且全 face-up；F2T 按源槽索引取顶并按经典 tableau 规则落子**；畸形 face-down 槽顶拒绝 ✓
4. Draw-1/Draw-3/partial 末次/废牌可见/回收序/face-down/stock_passes/重复回收/52 守恒正确 ✓
5. SnapshotHistory 默认容量 128>=100、确定性 FIFO、失败不记录、深拷贝精确恢复；flip/draw/recycle/move 撤销；空撤销 typed 失败；score=max(0,pre−2) 与 action 计数显式测试；畸形 Move 不入历史 ✓
6. 计分表与已验证基础表逐项一致且与合法性隔离；**判胜 = 四槽各持 13 张 face-up 的单一花色 A→K 完整 run（物理身份逐位置精确）+ 四槽花色互异（⇒ 花色集 {0,1,2,3}）；槽序无关（换槽可胜）；重复花色/混合/缺短/乱序/face-down/身份不符不判胜** ✓
7. WP-05 46 + WP-06 75 = 121/121 全绿、editor log 0 行；游戏未运行；无 scene/project 设置改动 ✓
8. Core 无 Node/Control/Texture/CanvasItem/场景/纹理依赖；无 hint/autocomplete/session/UI 路径 ✓
9. project.godot 权威字节基线不变；旧 Cocos/旧 Godot pre/post 不变；无意外文件；改动清单精确记账（含 16 个 `.gd.uid`）✓
10. 本证据如实报告公开 API、精确文件与 `.gd.uid`、测试/suite/断言数、MCP 会话/路径/版本/结果/日志、不可变测试、限制与停止；**修正 2 仅将 foundation 槽位绑定语义纠正为动态槽，保留修正 1 的形状门与隔离改进**；WP-06 止于“待证据确认”，未启动 WP-07 ✓

Sol 架构裁定逐项：固定 `checkACardPos`（74f51802… / SpriteManager.cpp:1769-1796）空槽任意 Ace、非空槽顶张同花色升序 → 已按动态槽落实并测试（任意花色 A→任意空槽、非空槽同花色升序、F2T 槽位而非花色）；修正 1 的槽=suit 断言与测试已移除/改写 ✓。

## 8. 未验证项/限制

- 规则/执行器/撤销经 @tool 上下文 MCP 测试；未运行游戏进程（WP-08 范围）。撤销采取“pop 快照且不入栈”线性模型：无 redo、undo 不可再被 undo（WP-07 会话层若需另行裁定）。
- “移动非顶张/埋藏 waste/foundation 卡”在类型化 API 中结构上不可寻址（waste/foundation 移动仅引用顶张、tableau 移动仅取顶 suffix），负例以“仅 waste 顶可玩、foundation 仅顶单张、face-down 不可移、self/invalid/坐标形状拒收”覆盖。
- 固定旧源仅作只读行为引证；WP-06 断言覆盖到 `checkACardPos`/`checkAPos` 的落子面，未移植旧代码结构。
- bureau1/bureau3 全库记录由 WP-05 fixtures 覆盖 dealt/ready；WP-06 回收/连续抽/守恒另以真实 dealt/ready 态 + 独立构造态覆盖。
- 计分 floor-at-zero 对普通移动亦生效，依据固定参考 `GameViewHD::updateScore` 实测 `if (score < 0) score = 0`。

## 9. 依赖与停止

- WP-07（Hint + AutoComplete + Application Session/Replay/New Deal）依赖本证据包获得 TD“证据确认”；**WP-07 保持依赖锁定**，执行者在收到证据确认前不启动 WP-07。
- 停止项：WP-06 修正 2（Foundation 动态槽语义纠正 + 回归）已完成并重提交证据；修正 3（move_executor.gd 残留 `suit`/`from_suit` 地址命名收尾，行为零变化）已完成并更新本证据；执行者停止，等待技术总监证据确认。
