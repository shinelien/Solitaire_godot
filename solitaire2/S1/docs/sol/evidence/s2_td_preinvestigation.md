# TD 开工前调查：S2 经典纸牌纯 2D 核心循环（固定旧源定位与事实核对）

- 调查者：Sol 5.6（技术总监）
- 记录：2026-09-03（DeepSeek 按技术总监裁定材料记录为只读预调查证据；本文件不是执行者施工证据）
- 目标：`/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1`
- 性质：只读调查、固定引用与合同依据。全程未 checkout、未写入任何旧仓库/工程对象。
- 环境：macOS Darwin 25.5.0 arm64；Godot 4.6.2；Godot AI MCP 3.2.4；DeepSeek（deepseek-v4-flash）。

## 1. 固定旧源定位：master 不是产品参考

- 检出主分支 `master` 位于独立仓库 `/Volumes/Mac studio pro/solitaire/WTF-Solitaire`，HEAD `515710ad2ff06bb405f5ee539904f6c837cb2983`（2018-07-15 “提交 小的修改”）。其树不含 `Resources/data/bureau1.d`/`bureau3.d` 等本阶段所需数据/管理器，**不是产品参考**。
- **产品参考 = 不可变 Git 对象 `InvincibleWarrior@74f51802c8a5356223c84d8aff81c3300f190a43`**（`InvincibleWarrior` 分支合并提交，2021-10-25 17:36:37 +0800，作者 tt）。
- 固定对象核对命令（只读 git）：`git cat-file -t 74f51802…` → commit；`git ls-tree -r --name-only 74f51802…`、`git rev-parse <commit>:<path>`、`git show <commit>:<path> | wc -l`、`git grep`。本地实测值如下。

## 2. 关键文件与 blob（固定对象 74f51802… = InvincibleWarrior-ios@967384cc…，逐路径一致）

| 路径 | blob（sha）@74f51802 | blob（sha）@InvincibleWarrior-ios | 事实 |
|---|---|---|---|
| Classes/manager/SpriteManager.cpp | 075f4a0dc9a9cf6c2ebce3bdde0759a41849fdea | 同 | **6486 行**；`reloadFile()`（105-123 行）加载 `data/bureau1.d`、`data/bureau3.d`；`initCardIds()` 为解码/发牌实现 |
| Classes/object/CardSprite.cpp | 5ba6eefafdd0fceb3e383342379b11b6d1615b43 | 同 | atlas 卡面 region 组合 |
| Classes/object/MoveData.cpp | 73a60b8e7fe53e49d0cb4a24a3191bf03a1b59d5 | 同 | 移动数据 |
| Resources/data/bureau1.d | c43a8957bf7e13e0965fa9ae6ddbc8a2aa82c690 | 同 | **32084 条**，每条 53 字节（52 字符 + LF），总 1,700,452B |
| Resources/data/bureau3.d | a04650d67840dee32b4171db9230b2e4c40b8f75 | 同 | **4999 条** |
| Resources/game/car_new_0_1.png / .atlas | 1d080ad75c62867d04e2365defe5651059935853 / 1612f965c62f7a7924a4310ae2ecaef51cd53387 | 同 | Spine 文本 atlas 卡面图集 |
| Resources/game/car_new_0_6.png / .atlas | 34f2c737db508b7304899e9c4ad5d10c4a313118 / a2c0aabd12bec4b759921997d9f92ae17324468a | 同 | size 1858×1776 RGBA8888；108 region（148×220，如 `card_0_1A`/`card_0_A11`） |
| Resources/background-0.png | c47b1a646bea70b127d66cea37ce3139f60bcfbf | 同 | 背景 |
| Resources/music/{deal,shuffle,movecard,nomove,undo,autoplay,auto,victory}.mp3 | 28363a57…/28363a57…/789293db…/9ef2f5d4…/5fbfae62…/576ea7fa…/35a807fb…/03ca21b2… | 同 | 所需音效（deal 与 shuffle blob 相同） |

平台文件（proj.android/proj.ios_mac/proj.linux/proj.win32）为两分支唯一差异类。

## 3. 旧解码/发牌事实（从固定对象 SpriteManager.cpp `initCardIds()` 实测）

- 记录符号：ASCII 48..99（52 个字符集，record0 实测 52 个互异符号），**id = 符号字节 − 48** ∈ [0,51]。
- 消费：`it = begin + currentIDX*53`，对 `i=0..51` 取 `*(it+51-i)` → **整条 52 字符逆序**填入 `cardIds`（即 `cardIds = reverse(record)`，SpriteManager.cpp:260-263）；发牌 `getCardId()` 对 `cardIds` **前端 FIFO** 取牌（SpriteManager.cpp:505、534-536，恒取 `cardIds[0]` 并 `erase`），**实际出牌顺序 = `reverse(record)`（全程仅此一次反转）**。`currentBureau` 另行由 `cardIds` 顺序转串后整条反转（SpriteManager.cpp:311-316），等于**原记录正向序**，**仅用于日志与 `"bu"` 上报/序列化**（GameViewHD.cpp:1542/2393/3075）；对 `currentBureau` 的反转不改动 `cardIds`，也不是发牌顺序来源。
- 校验口径：`SIMPLE_CHECK_SUM = SUM(51)` 总校验；畸形时旧代码才回退随机，**本阶段确定性解码器禁止回退随机化**。
- bureau1 首条记录（52 字符，53B 含 LF）SHA-256（原始行）：`7a0e10fdd…`（52B 无 LF）/`6c839523e…`（53B）；**规范记录 0 消费/tableau/stock 的固定 hash = `935879b0483480ea8f936cdc2c2b236d532d2b9531f800b19173f8dd50d620e3`（TD 固定口径，WP-05 fixtures 依此校验）**。

## 4. 布局/分辨率事实（固定对象实测）

- `Classes/AppDelegate.cpp` 56 行 `designResolutionSize = Size(1080, 1920)`；114 行 `ResolutionPolicy::FIXED_WIDTH`。
- `Classes/AppConstant.h` 105 行 `POKER_SIZE = Size(148, 220)`；113/114 行 `OffsetNoOpen = 30`、`OffsetOpen = 66`（`CardSprite.cpp` 1024 行注释：翻开差 66、其他差 30）。
- 牌垫 pad 1080×1440；bureau 记录格式、stock 自底向上顶端在数组末尾、列主序 tableau 1..7、发牌后自动翻 1/3 的“玩家就绪”口径，沿用 TD 预调查裁定（详见 `施工合同.md` §3.2/§5）。

## 5. 官方 Godot 依据（stable，均已实测可访问）

- RefCounted：https://docs.godotengine.org/en/stable/classes/class_refcounted.html
- Control：https://docs.godotengine.org/en/stable/classes/class_control.html
- TextureRect：https://docs.godotengine.org/en/stable/classes/class_texturerect.html
- 静态类型 GDScript（含“嵌套类型数组不受支持”）：
  https://docs.godotengine.org/en/stable/tutorials/scripting/gdscript/static_typing.html
- 多分辨率（base size / canvas_items / Keep Width / 竖屏 1080×1920 建议）：
  https://docs.godotengine.org/en/stable/tutorials/rendering/multiple_resolutions.html

## 6. 结论与风险

- 结论：产品参考锁定 `InvincibleWarrior@74f51802c8a5356223c84d8aff81c3300f190a43`；关键代码/数据/图集/音频 blob 与该提交一致并与 `InvincibleWarrior-ios` 关键 blob 逐字节相同；S2 架构 = 纯 2D Control/TextureRect、纯 Core/State/Move、1080×1920 + canvas_items + keep_width、atlas region 组合（不移植 Spine、不烘焙新图）。合同 `docs/sol/施工合同.md`（S2 v1.0）、ADR-007..010、worker order 与 golden fixtures 口径依本文件落地。
- 风险：bureau 数据是否需 `image_decrypt` 预处理（旧 `reloadFile()` 调用 `cocos2d::utils::image_decrypt`）须在 WP-05 以记录 0 固定 hash `935879b0…` 实证校准；fixtures 由 TD 独立抽检；WP-08 前不得改 `project.godot` 字节基线。
