# WP-05 证据包：CORE-001 Legacy Deal + Core Model + Golden Tests

- 合同：`docs/sol/施工合同.md`（S2 v1.0，§5/§6 WP-05、§8 验收矩阵）；worker-order `docs/sol/worker-order-s2-classic-2d.md`；WP-05 开工令（负责人发布）
- 规则基线：SOL 4.5.2 + 通用执行者连续执行合同 3.2 + 每 WP 证据确认门
- 阶段：`S2-CLASSIC-2D-CORE-LOOP`；状态：**WP-05 施工完成、待证据确认**；WP-06..WP-08 保持依赖锁定（各依赖前一 WP 的 TD“证据确认”，非阶段裁决）
- 执行者运行时身份：DeepSeek（deepseek-v4-flash）
- 环境：macOS Darwin 25.5.0 arm64；Godot `4.6.2-stable (custom_build) 001aa128b`；Godot AI MCP 插件/服务器 `3.2.4`；时间 2026-09-03T00:43+0800；补证修订（WP-05 acceptance 返工）2026-09-03

## 1. 会话与工程路径（MCP）

- MCP 会话 `s1@b900`（初轮）与 `s1@58c7`（修复后全新编辑器干净终轮）：project_path = `/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1/`（精确目标路径）；Godot `4.6.2-stable (custom_build)`；插件/服务器 `3.2.4`；project_name “新建游戏项目”；play_state stopped（全程未运行游戏）；readiness ready；current_scene `res://mcp_verify.tscn`（基础设施夹具原样）。
- 干净终轮：全新编辑器重启 → MCP `filesystem_manage(scan)` settled → MCP `test_run` 全绿 → MCP editor log = 0 行错误。
- **补证修订（WP-05 返工，2026-09-03）**：Sol 复核指出证据 §6 声称“文件布局”负路径，但测试仅正向校验两个真实 pool，`LegacyDealDecoder.validate_pool_bytes` 的空池/非 53 倍数/坏 LF/内嵌非法记录分支无直接测试；且 14 个 `.gd.uid` 被笼统归为“可再生”而缺失精确记账。本修订：在 `tests/test_legacy_decode.gd` 直接新增 7 项 `validate_pool_bytes` 测试（6 负 + 1 良性多记录基线），全量 McpTestSuite 复跑 **passed=46 / failed=0 / skipped=0**（原 39 + 7），MCP editor log = 0 行错误；测试揭示 decoder **无缺陷**，产品代码零改动；§3 改为对 14 个 `.gd.uid` 逐一精确记账并与 `.godot/**` 可再生缓存区分。复跑在既有干净会话 `s1@58c7` 的同一编辑器进程内执行（本轮未再次重启编辑器），play_state 全程 stopped、未运行游戏——如实披露。

## 2. 固定源导入（只读 Git 对象，无 checkout/网络）

固定对象 `WTF-Solitaire@InvincibleWarrior@74f51802c8a5356223c84d8aff81c3300f190a43`（仅 `git show <object>:<path>` 重定向导出）：

| 固定对象内路径 | blob（git rev-parse） | 导出目标 | 字节 | 记录数 | 内容 SHA-256 |
|---|---|---|---|---|---|
| Resources/data/bureau1.d | c43a8957bf7e13e0965fa9ae6ddbc8a2aa82c690 | data/legacy/bureau1.d | 1,700,452 | 32,084 | 36414bfcd91c916caa77c8b908dc51000732bfc8ba2b8113798d6a2a48d2ccf5 |
| Resources/data/bureau3.d | a04650d67840dee32b4171db9230b2e4c40b8f75 | data/legacy/bureau3.d | 264,947 | 4,999 | 0bf9409ac5a5954a02460274fc50e8cd1ca79693be4dd90e70cc6ebcac81ca43 |

记录 0 行级 SHA-256：52B 无 LF = `7a0e10fddf…`，53B 含 LF = `6c839523ee…`（与 TD 预调查一致）；记录 0 消费/tableau/stock 规范 hash = `935879b0483480ea8f936cdc2c2b236d532d2b9531f800b19173f8dd50d620e3`，由 GDScript `LegacyDealDigest` 实测复现（见 §5）。bureau 数据无需 `image_decrypt` 预处理（固定 blob 直接 ASCII 明文，已实证）。

## 3. 目录骨架与改动文件（精确清单）

新增仅限以下路径（无 scene、无 project.godot/addon/夹具改动；无 presentation/application/rules/moves 目录）：

- `solitaire/core/card_data.gd`、`card_pile.gd`、`game_state.gd`——CardData/CardPile/GameState（全部 `extends RefCounted`，纯数据，深拷贝）。
- `solitaire/deal/legacy_deal_decoder.gd`、`legacy_deal_repository.gd`、`legacy_deal_digest.gd`、`legacy_deal_dealer.gd`、`legacy_deal_result.gd`——确定性解码器/仓库/规范摘要/发牌器/类型化结果。
- `tests/golden_loader.gd`、`tests/test_core_model.gd`、`tests/test_legacy_decode.gd`、`tests/test_legacy_dealer.gd`、`tests/test_golden_deal.gd`、`tests/test_library_integrity.gd`——McpTestSuite 测试 + 测试专用读取器。
- `data/legacy/bureau1.d`、`bureau3.d`；`data/legacy/golden/golden_bureau1.json`（100 fixtures，索引 0..99）、`golden_bureau3.json`（25 spread fixtures：0,1,2,3,4,9,49,99,199,499,999,1499,1999,2499,2999,3499,3999,4499,4700,4800,4900,4949,4970,4990,4998）。
- `deal_tools/importer/generate_fixtures.py`、`verify_fixtures.py`、`README.md`——独立 golden 生成器与独立抽检脚本。
- 治理/证据：`docs/sol/当前任务.md`、`项目状态.md`、`阶段结果.md`、`证据索引.md`、`evidence/wp05_core001.md`（本文件）。
- **改动清单精确记账（补证修订）**：WP-05 新增的 changed source-control artifacts = 上述 §3 各路径 **+ 14 个 `.gd.uid`**（Godot 4.4+ 为每个 `.gd` 生成的 UID 侧车单行文件，单行内容 `uid://…`；本项目 `.gitignore` 未排除 `.gd.uid`，故与 `.gd` 一并入版本库、属精确清单）。与 `.godot/**` 不同：`.godot/` 在 `.gitignore` 内、为编辑器可再生缓存，运行随变、不入版本库，不计入改动清单。以下为完整 subordinate manifest（路径 = `uid://…` 逐行）：

```
solitaire/core/card_data.gd.uid            uid://ds8pn22r2xsfs
solitaire/core/card_pile.gd.uid            uid://diaogwt0piqp6
solitaire/core/game_state.gd.uid           uid://bowpwq4fms0d3
solitaire/deal/legacy_deal_decoder.gd.uid  uid://cfm8lb8bjidlr
solitaire/deal/legacy_deal_digest.gd.uid   uid://druinf5i0iww2
solitaire/deal/legacy_deal_dealer.gd.uid   uid://bp3yluxq0hqyy
solitaire/deal/legacy_deal_repository.gd.uid  uid://b08561ed765dn
solitaire/deal/legacy_deal_result.gd.uid   uid://bcuu43n4dqm7a
tests/golden_loader.gd.uid                 uid://cxjtiasy4w0cx
tests/test_core_model.gd.uid               uid://68f314j8dhh3
tests/test_golden_deal.gd.uid              uid://dg1amoa3ewj7s
tests/test_legacy_dealer.gd.uid            uid://dnb2837titno0
tests/test_legacy_decode.gd.uid            uid://uuowkb3454bc
tests/test_library_integrity.gd.uid        uid://dmibcqgo6yg1s
```

  数据/夹具 `data/legacy/**` 为固定对象只读导出（见 §2），非编辑器生成；`.godot/**` 可再生缓存不计源。

产品文件 SHA-256（8 core/deal + 6 tests + 3 importer + 2 fixtures，raw 数据见 §2）：

```
solitaire/core/card_data.gd                c5e6236b4fa889ca64978ce88502c933db324020c2edb06f6991cee83262cdd9
solitaire/core/card_pile.gd                5d8dd3985ce093cf4d03f88c56007b850d2738642678383c29789b75ee2bfa11
solitaire/core/game_state.gd               282a85fdeefd014b7aea51430fb3c8019c552c3d0bb8fe1605b742cbe176c92e
solitaire/deal/legacy_deal_decoder.gd      7a0113bef726bff0ab5998d2a58044ded3088d5baf7186df086bc1fb215397ab
solitaire/deal/legacy_deal_repository.gd   38818d0c08cc04ab63564e2d293a9f291577d0b018bdb5c39423d5cb46736f2e
solitaire/deal/legacy_deal_digest.gd       c5ca9d0f89c08bab04d8c64fc1a7105386c568ca62f7d264bcb91519fb9cd35e
solitaire/deal/legacy_deal_dealer.gd       16b9773faab69fdbefcbc1768b367baa51aaf1abbc07ea756f8126b52338ea29
solitaire/deal/legacy_deal_result.gd       944ed71aad71f6b4ac8dcb006a78452bf99d69686620fbaaa672f119bf5f4e30
tests/golden_loader.gd                     87d4189820aa41dd6005e0c28716c80af7963e282551e704ebfa3ad3c5747923
tests/test_core_model.gd                   1955cfa88b3c3cc65d97e0f4f25426bd6df71139b99d71ca3ef70058d570e4f0
tests/test_legacy_decode.gd                63af43ee5edf903bc31cb351e922fac56cac009dab6fa6311c6f96017f8ca9b9
tests/test_legacy_dealer.gd                87aa2d45e9de9f253d0b96e8ac1a34fecb2052355a66f407d05c082224afd860
tests/test_golden_deal.gd                  76ffccda2836ea7daaadd0011b5f5cb6fa9a5853ba71b4837c97fe5ff3a40c0c
tests/test_library_integrity.gd            739897310ff28bf860fc4bccd635f1a8f2b8a513b8b3522961bfdd1dc8bb2fa6
deal_tools/importer/generate_fixtures.py   c3faa0659a744145d907d91d88ce68b9cef798de9aea38b9a667960d8bf943e8
deal_tools/importer/verify_fixtures.py     6dc44d2e4530d89ba0cfcd1ad50af58651b2d0404c2141109e9f9979d60a73d6
deal_tools/importer/README.md              28213ed69dd3590ae34c56d9dd78df04bf67221e02d66aa0a9f78357686be5e2
data/legacy/golden/golden_bureau1.json     a4c221bab675b4b04e423bb901c8b3a0739ee6515642bd4fcef37d5d9fe4ebf6
data/legacy/golden/golden_bureau3.json     f39c449c12cd5981701b3688328b4b93dea340a202434ac1f06f4ee986b62062
```

## 4. 公开接口/架构要点

- 分层：core（CardData/CardPile/GameState）→ deal（decoder/repository/digest/dealer/result）；无 Presentation 依赖；Core 无 Node/Node2D/Node3D/Control/Texture/CanvasItem 引用（实测 grep 仅注释）。
- `CardData`(RefCounted)：id/rank(=id%13+1)/suit(=id/13,0♠1♥2♣3♦)/face_up；clone()。
- `CardPile`(RefCounted)：数组序 0=底、末=顶；from_ids/ids/clone(深)/content_equals/top/bottom/pop。
- `GameState`(RefCounted)：唯一事实来源；stock/waste/tableau[7]/foundation[4]（`Array[CardPile]`，规避嵌套类型数组）、draw_count/stock_passes/move_count/score/game_status、deal_pool/deal_index/deal_source/deal_key()；`clone()` 全深拷贝无共享可变对象；`all_card_ids()`/`total_card_count()`。
- `LegacyDealDecoder`：52 字节 48..99、id=byte−48、consumption=`reverse(record)`；拒绝长度/非法字节/重复（含缺失补集）确定性返回 typed code；`validate_pool_bytes` 整池布局校验：53 字节记录（52 字符+LF），空池/非 53 倍数/坏 LF/内嵌非法记录分别确定性返回 `file_layout` 或记录级 typed code，带 `record_count`/`first_error_index`；无随机回退。
- `LegacyDealRepository`：按 pool+index 读 data/legacy 原始文件；越界/未知 pool 显式错误；整库布局校验。
- `LegacyDealDigest`：`sha256(列逗号串'|'连接+'#'+stock逗号串)`。
- `LegacyDealer`：`deal_dealt`/`deal_ready`（及 from_record 变体）产出 dealt（28 tableau + 24 stock，waste 空）或 ready（自动翻 1/3：从 stock 顶弹入 waste，waste 顶=最后弹出=可玩端）；typed `LegacyDealResult`（ok/error_code/state）。

## 5. Golden fixtures 与独立性

- 每 fixture 存：source/pool/index/raw_deal/consumption（52 消费序）/dealt_canonical_sha256/dealt{tableau[含每卡 id+face_up],stock,waste}/ready_draw1{stock,waste}/ready_draw3{stock,waste}。
- **独立性**：fixture 预期由 `deal_tools/importer/generate_fixtures.py`（独立 Python 实现 legacy 规范）直接读原始记录计算；生成与抽检全程不调用生产 GDScript decoder/dealer（文件头与 JSON meta 均记录该口径）；GDScript 测试消费静态 JSON。
- 记录 0 规范 digest = `935879b0483480ea8f936cdc2c2b236d532d2b9531f800b19173f8dd50d620e3`（fixture meta 与测试双重固定）。

## 6. MCP 测试结果与诊断

- McpTestSuite 全量：干净终轮（全新编辑器会话 s1@58c7）`test_run` → **passed=39 / failed=0 / skipped=0**；**补证修订复跑（同会话 s1@58c7 编辑器进程，2026-09-03）`test_run` → passed=46 / failed=0 / skipped=0**（suite：core_model、golden_deal、legacy_dealer、legacy_decode、library_integrity；实测断言 511 = core 322 + golden 15 + dealer 56 + decode 77 + library 41，含 100+25 全 fixture 逐项）。
- 覆盖：rank/suit 全 52 映射；CardPile 序；GameState 深拷贝隔离（改 clone 卡/堆/标量源不变）；52/52 守恒与 0..51 全排列；record 0 规范 hash（Draw1/Draw3 双态）；bureau1/bureau3 全库布局校验（32084/4999 条全部严格解码，bytes/sha 与固定对象一致）；每一 fixture 的 dealt 与 ready Draw-1/Draw-3 逐项；索引越界/未知 pool/非法 draw_count/非法长度/非法字节/重复缺失等负路径；**整池畸形布局直接负测试（补证新增，tests/test_legacy_decode.gd）**：空池 `file_layout`、字节数非 53 倍数 `file_layout`（1/52/54/158 字节）、记录终止符非 LF（CR）→ `file_layout`+`first_error_index`（record 0 与 record 1 两态）+`record_count`、结构合法首记录后跟非法记录 → `invalid_byte`+`record_count`+`first_error_index`=1、良性多记录基线 `ok`/`record_count`=2/`first_error_index`=-1、同一畸形缓冲重复校验结果逐字段全等（确定性、无随机、无越界崩溃）；确定性（重复解码/两次发牌 content_equals）；输入不变性。
- 诊断：修复迭代中生产类零错误；测试脚本类型/命名问题在迭代中修复（parse error 已清零）；干净终轮与补证复跑 **MCP editor log = 0 行**（`logs_read(source=editor)` 返回空）；plugin log 无 error/warning；无 game log（全程未运行游戏）。

## 7. 独立抽检（CLI 只读，不调生产代码）

`python3 deal_tools/importer/verify_fixtures.py` 退出 0：从固定对象原始记录独立重算 bureau1 索引 0,1,2,9,99 与 bureau3 全部 25 spread 索引的 consumption/tableau/face_up/stock/dealt digest/ready Draw1/Draw3，与持久 fixture 逐项一致。

## 8. 验收结果（§8 相关矩阵）

1. CardData/CardPile 为 RefCounted 纯数据；GameState 唯一事实来源且深拷贝隔离实证 ✓
2. rank/suit 全 52 映射与容器/堆序明确且测试 ✓
3. bureau1/bureau3 固定对象精确导入（blob+内容 sha）；畸形输入确定性拒绝、无随机；**整池畸形布局（空池/非 53 倍数/坏 LF/内嵌非法记录/确定性）7 项直接负测试全绿** ✓
4. 逆序/FIFO、三角列主序 tableau、翻开位、stock 序、dealt/ready Draw-1/Draw-3 与独立 fixtures 全一致 ✓
5. bureau1 100 + bureau3 25 fixtures；记录 0 = 935879b0…；每个 dealt 态 52/52 ✓
6. MCP McpTestSuite 46/46 通过（补证复跑，原 39/39）、复跑零诊断；CLI 未冒充 Godot 验证 ✓
7. project.godot SHA-256 `ef9dfc63…` 字节不变、无 main scene/display/input；无新建 scene；游戏未运行 ✓
8. 旧 Cocos（WTF master@515710ad）与旧 Godot 工程 pre/post 零变化（git status diff 空）；目标路径仅 §3 清单 ✓
9. 本证据包含环境/模型/时间/改动/哈希/MCP 测试/诊断/pre-post/限制/停止 ✓
10. WP-05 止于“待证据确认”；未启动 WP-06 ✓

## 9. 旧工程 pre/post 与边界

- `WTF-Solitaire`（HEAD 515710ad…）：pre/post `git status --porcelain` diff 为空（仅既有未跟踪 proj.ios_mac/* 未变）；未 checkout/写入。
- 旧 Godot `/Volumes/Mac studio pro/solitaire/godot/solitaire`：无任何变化（父仓库 diff 仅含 solitaire2/S1 授权新增目录）。
- `mcp_verify.tscn` SHA-256 `56a31e49…` = S1 固定夹具值，未改。
- 全程无 commit/push/下载/凭证/破坏性动作；未改动 addons/godot_ai、project.godot、夹具、.godot（仅编辑器可再生缓存随运行变动，已披露）。

## 10. 未验证项/限制

- WP-06 起的规则/移动/撤销/回收/计分/胜负与 WP-07/08 全部未实施（依赖锁定）。
- fixture 由 TD 独立抽检；`image_decrypt` 已实证为无需（固定对象为明文）。
- 改动清单已精确记账：14 个 `.gd.uid` 属 changed source-control artifacts（§3 清单），`.godot/**` 为可再生缓存不计源（见 §3 区分）。
- 测试在编辑器 @tool 上下文经 MCP 运行；未运行游戏进程；补证复跑未再次重启编辑器（与干净终轮同会话同进程，如实披露）。

## 11. 依赖与停止

- WP-06（Rules + MoveExecutor + Snapshot Undo + Draw1/Draw3）依赖本证据包获得 TD“证据确认”；**WP-06 保持依赖锁定**，执行者在收到证据确认前不启动 WP-06。
- 停止项：WP-05 CORE-001 已完成并提交证据；执行者停止，等待技术总监证据确认。
