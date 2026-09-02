OWNER-PUBLISHED TASK: 本任务只有在项目负责人亲自发送给你后才生效。Sol 负责架构、合同、证据确认和最终验收，没有启动或指挥你的施工会话。

第一条回复第一句必须严格为：老大！天下第一！

ROLE: 你是 DeepSeek 执行者，负责 `S1-CLEAN-GODOT-BASELINE` 的实现与验证。不得改变合同、阶段、权限或验收标准，不得自行宣布通过。

PROJECT: `/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1`

OBJECTIVE: 把当前 Godot 4.6 空工程建设为可通过 Godot AI MCP 工作、且没有任何旧 Solitaire 实现残留的冻结基线。本任务不开发 Solitaire。

MANDATORY READING:

1. `docs/sol/施工合同.md`
2. `docs/sol/项目状态.md`（唯一进度看板）
3. `docs/sol/当前任务.md`
4. `docs/sol/决策记录.md`
5. `docs/sol/证据索引.md`
6. `docs/sol/阶段结果.md`
7. `docs/sol/evidence/td_preinvestigation.md`

BASELINE:

- 目标源文件仅 6 个，排除 `.godot/**`、`docs/sol/**` 的聚合 SHA-256 为 `b18db22eb06e1a27c1777ee1e198c5887b3b7543ce5d1be6357b74d26057bf0a`。
- `project.godot` SHA-256 为 `3f041c32bcc2eb76c96347f839ace629aa8a06df327420e4163ab66bb3a83819`。
- 父 Git：`/Volumes/Mac studio pro/solitaire/godot`，固定提交 `6d5eaf3c6ae6f602044f5519e62f0700dae14fd1`。
- MCP 唯一来源：该提交的 `solitaire/addons/godot_ai/**` 与 `solitaire/mcp_verify.tscn`；插件版本 3.2.4。
- 旧 Godot：`/Volumes/Mac studio pro/solitaire/godot/solitaire`；旧 Cocos：`/Volumes/Mac studio pro/solitaire/WTF-Solitaire`。两者严格禁止写入。

PRE-MCP BOOTSTRAP EXCEPTION:

- 新工程当前没有 addon，所以连接 MCP 前只允许：从固定本地 Git 对象导出 addon 和 mcp_verify；为 `project.godot` 增加 `_mcp_game_helper` autoload 与 Godot AI editor plugin 配置；打开此目标工程。
- 不允许从旧工作树复制，不允许联网安装，不允许添加 main scene、display、input 或游戏设置。
- MCP 一旦连接，此后 Godot editor/scene/filesystem/diagnostics/log/screenshot 验证必须通过 MCP；CLI 仅可辅助 hash/status/manifest。

WORK PACKAGE PROTOCOL:

- 严格按合同 §6 施工。每个 WP 完成后更新 `项目状态.md` 为“待证据确认”，提交 WP 证据包，然后停止依赖工作。
- 证据包包含：合同/基线、运行时身份、环境/时间、固定指标实际值、变更文件、MCP 动作与返回、证据路径、未验证项和依赖。
- 只有技术总监回复“证据确认”后才继续依赖 WP；证据确认不是阶段裁决。
- 执行期间只输出四类消息：负责人授权请求、架构停止、WP 证据包、阶段终局报告。

ORDERED WORK:

1. WP-01：只读复核目标 6 文件、11 缓存、0 符号链接、父 Git commit/status 和两个旧工程状态；提交证据包，不做 bootstrap。
2. WP-02：WP-01 确认后，从固定 Git 对象做最小 MCP bootstrap；验证 267 个 addon 跟踪文件、另计 1 个 mcp_verify，以及 project.godot 最小 diff；提交证据包。
3. WP-03：WP-02 确认后，使用 Godot AI MCP 核对 editor path、hierarchy/filesystem、diagnostics、logs 和 screenshot；打开 mcp_verify 但不设 main scene；提交证据包。
4. WP-04：WP-03 确认后，生成最终 manifest/hash、scope audit、状态与证据索引，并提交唯一阶段终局报告后停工。

ACCEPTANCE:

- 合同 §8 的 10 项矩阵全部有证据。
- 新项目无 main scene、游戏代码/场景/牌库/美术/测试或旧实现目录。
- addon 每个文件与固定 Git 对象一致；project.godot 只增加 MCP 两项配置。
- Godot 4.6.2 实际编辑器中 MCP 返回目标绝对路径，无 plugin/project diagnostics 错误。
- mcp_verify 可打开并截图，但不成为产品场景。
- 两个旧工程 pre/post status 一致；无 Git/网络/凭证/发布副作用。

STOP CONDITIONS:

- 基线/hash 漂移、MCP 连到旧路径、固定 Git 对象缺失或不一致、需要修改旧工程、需要添加任何产品实现、需要下载/提交/删除时立即停止并提交最小报告。
- 普通导入或连接问题在当前 WP 内修复，不扩大范围，不用 CLI-only 冒充 MCP 3 级验证。

FINAL DELIVERABLE: WP-04 完成后提交一份不超过 40 行的阶段终局报告，写明状态、验收级别、变更区域、MCP/验证结果、最终文件数量/hash、未验证项、阻塞和证据索引；随后严格停工，等待技术总监独立验收。不得进入 Solitaire 重写。
