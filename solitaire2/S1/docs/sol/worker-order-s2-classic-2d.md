OWNER-PUBLISHED TASK: 本任务只有在项目负责人亲自发送给你后才生效。Sol 负责架构、合同、证据确认和最终验收，没有启动或指挥你的施工会话。

ROLE: 你是 DeepSeek 执行者，负责 `S2-CLASSIC-2D-CORE-LOOP`（WP-05..WP-08）的实现与验证。不得改变合同、阶段、权限或验收标准，不得自行宣布通过。**本 worker order 交付时 WP-05 处于“就绪、未启动”**；你不得在收到独立开工指令前执行任何 WP-05 施工。

PROJECT: `/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1`

OBJECTIVE: 在已关闭的 S1 干净 Godot 基线上，建立经典 Klondike 纯 2D 核心循环（翻 1/翻 3），覆盖 WP-05 Legacy Deal + Core Model + Golden Tests、WP-06 Rules + MoveExecutor + Snapshot Undo + Draw1/Draw3、WP-07 Hint + AutoComplete + Application Session、WP-08 Pure 2D Playable Loop。

MANDATORY READING:

1. `docs/sol/施工合同.md`（S2 v1.0，唯一阶段合同）
2. `docs/sol/项目状态.md`（唯一进度看板）
3. `docs/sol/当前任务.md`
4. `docs/sol/决策记录.md`（ADR-007..010 架构决定）
5. `docs/sol/证据索引.md`
6. `docs/sol/阶段结果.md`
7. `docs/sol/evidence/s2_td_preinvestigation.md`
8. `docs/sol/contracts/S1-CLEAN-GODOT-BASELINE-v1.2.md`（S1 已归档合同，只读事实源）

BASELINE:

- S1 已通过并关闭（关闭时间 2026-09-02T23:20:00+0800；TD 正式裁决 THROUGH/PASS；独立验收第 1 轮工程 PASS）。S1 最终 manifest sha256 `dee4dec745dd99fd25487644843e9eab7033eba27e81df423bc6fd8822b27f4f`；project.godot 权威字节基线 `ef9dfc63fdcbe8273eb9edceff9216f7e592bcdcd95f011603b494c2fcf9e4c9`（无 main scene/display/input，WP-08 前不得改）。
- 父 Git：`/Volumes/Mac studio pro/solitaire/godot`；旧 Godot（只读）：`/Volumes/Mac studio pro/solitaire/godot/solitaire`；旧 Cocos（只读）：`/Volumes/Mac studio pro/solitaire/WTF-Solitaire`。
- **产品参考固定对象**：`InvincibleWarrior@74f51802c8a5356223c84d8aff81c3300f190a43`（含 SpriteManager.cpp 6486 行与全部命名 data/managers；关键 blob = `InvincibleWarrior-ios@967384cc…`）。禁止 checkout/写入；资产/数据只从该对象 blob 确定性导出。
- MCP 唯一来源与 Godot 动作口径沿用 S1：Godot editor/scene/settings/run/test 必须经 Godot AI MCP（插件 3.2.4、Godot 4.6.2）；CLI 仅做常规源码编辑、固定 Git 对象二进制/数据提取、hash、Git status。

ORDERED WORK:

- 严格按 `施工合同.md` §6 施工：WP-05 →（TD“证据确认”）→ WP-06 →（TD“证据确认”）→ WP-07 →（TD“证据确认”）→ WP-08。
- 每个 WP 完成后更新 `项目状态.md` 为“待证据确认”，提交 WP 证据包，然后停止依赖工作。
- 证据包包含：合同/基线、运行时身份（DeepSeek/deepseek-v4-flash）、环境与时间、固定指标实际值、精确改动文件、Godot AI MCP 测试/诊断/日志/截图、pre/post 旧仓库状态、未验证项与依赖、停止项。
- WP-05 测试用已装 MCP `McpTestSuite` runner；不设 main scene、不碰规则/UI/资产/主场景。
- WP-08 才允许经 MCP 应用 display/input/main-scene；正式场景不得含 Node3D；`mcp_verify.tscn` 保留为基础设施夹具。

ACCEPTANCE（详见合同 §8 十二项矩阵）:

- 52/52 精确、dealt 与 ready（自动翻 1/3）快照正确；非法输入拒绝、无回退随机化。
- Core 无 Node/Control/Texture/Firebase/广告/SEO/服务器；Scene Tree 不是 GameState；CardData/CardPile 为 RefCounted 纯数据；GameState 唯一事实来源且可深拷贝；tableau/foundation 用 `Array[CardPile]`。
- 一切状态改变走 Move/MoveBatch + RulesEngine + MoveExecutor（返回新状态+显式移动，源不变，非法移动类型化拒绝）；撤销快照按用户动作、容量 ≥100、精确恢复；Hint/AutoComplete/Replay 确定性、零变异、无隐藏辅助。
- Golden ≥100 bureau1 + 代表性 bureau3；记录 0 规范 hash `935879b0483480ea8f936cdc2c2b236d532d2b9531f800b19173f8dd50d620e3`；TD 独立抽检 fixtures。
- 资产只来自 `74f51802…`；无 Spine；不烘焙 52 张新图；CardView 用 Control/TextureRect + AtlasTexture region；1080×1920 + canvas_items + keep_width。
- WP-08 实际游戏运行通过 MCP 验证（拖拽/双击/翻1/翻3/撤销/hint/autocomplete/replay/win）并截图；阶段终局报告 ≤40 行后停工等独立验收与 TD 最终裁决。

STOP CONDITIONS:

- 错误旧引用/路径；旧仓库被写；golden 映射畸形或非精确；Core 依赖 Node/UI；规则绕过 Move；正式产品场景含 Node3D；隐藏换牌/辅助；MCP 错工程/断连；测试/诊断失败；资产非固定 blob；main scene 早于 WP-08；引入未批准系统。任一发生即架构/状态完整性停止并提交最小报告。
- 普通问题在当前 WP 内修复，不扩大范围，不用 CLI-only 冒充 MCP 3 级验证。

FINAL DELIVERABLE: WP-08 完成后提交一份不超过 40 行的阶段终局报告（状态、验收级别、变更区域、WP 证据链、MCP/验证结果、最终文件/hash、未验证项、风险、阻塞、依赖），随后严格停工等待独立验收与技术总监最终裁决。不得进入 S2 之外的 Solitaire 扩展工作。
