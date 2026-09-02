# WP-01 证据包：新目标基线只读复核

- 合同：`docs/sol/施工合同.md` v1.0（§6 WP-01）；worker-order `docs/sol/worker-order-s1-clean.md`（WP-01 只读复核，不做 bootstrap）
- 规则基线：SOL 4.5.2 + 通用执行者连续执行合同 3.2
- 阶段：`S1-CLEAN-GODOT-BASELINE`
- 执行者运行时身份：DeepSeek（deepseek-v4-flash，DSH harness）
- 环境：macOS Darwin 25.5.0 arm64（LiandeMacBook-Pro.local）；git 2.50.1（Apple Git-155）；Godot.app 位于 /Applications（版本待 WP-03 经编辑器/MCP 确认）；复核时间 2026-09-02T12:35:15+0800
- 性质：全程只读；未写入/修改任何目标文件、旧工程或仓库；未做任何 bootstrap

## 1. 目标路径与顶层内容

- 路径：`/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1` 存在。
- 顶层条目：`.editorconfig`、`.gitattributes`、`.gitignore`、`.godot/`、`docs/`、`icon.svg`、`icon.svg.import`、`project.godot`。
- 无旧 Solitaire 顶层目录（无 core/data/deal/application/presentation/scenes/tests/assets）。

## 2. 6 个默认源文件（排除 .godot/** 与 docs/**）

| 文件 | SHA-256 |
|---|---|
| .editorconfig | 3b2c749c8a940905a08f727d8be9017c9568a12421c0aee7e37e9543b3751b1b |
| .gitattributes | 21b01a606c9f85f18bb9230245f00ab104df7409cbb2fe9423f6751ca72ba754 |
| .gitignore | d6194b1a176268740a0b7f153bd4926908b4a0955a9a311181c0200b4329bc94 |
| icon.svg | 6c80384360a5b269d1054bfb27241258154e2cc8167c522016fdc1820e84e0f8 |
| icon.svg.import | 80e27a2c8c55abff9a41ba160d1785c8b692aba0ff425653b32e7ae1c426b8ed |
| project.godot | 3f041c32bcc2eb76c96347f839ace629aa8a06df327420e4163ab66bb3a83819 |

- 聚合 SHA-256（按排序后 sha256sum 输出行整体再哈希）：`b18db22eb06e1a27c1777ee1e198c5887b3b7543ce5d1be6357b74d26057bf0a` —— 与合同 §2 一致（该口径与合同 §2 基线吻合，可作为后续 WP 聚合口径）。
- `project.godot` SHA-256 `3f041c32bcc2eb76c96347f839ace629aa8a06df327420e4163ab66bb3a83819` —— 与合同 §2 一致。
- `project.godot` 内容核对：无 main scene、无 autoload、无 editor plugin、无 [display]/[input]；项目名“新建游戏项目”；feature 4.6 + GL Compatibility —— 与合同 §2 一致。

## 3. .godot 缓存与符号链接

- `.godot/**` 文件数：11（.gdignore、editor/ 下 6 项、global_script_class_cache.cfg、imported/icon.svg 的 .ctex/.md5、uid_cache.bin 等）—— 与合同 §2 一致。
- 符号链接：0 —— 与合同 §2 一致。

## 4. 父 Git 与状态

- 仓库：`/Volumes/Mac studio pro/solitaire/godot`；HEAD `6d5eaf3c6ae6f602044f5519e62f0700dae14fd1`（main）—— 与合同 §2 一致。
- `git status --porcelain` 全文（10 行，均为旧工程既有状态，未触碰）：
  - ` M solitaire/project.godot`
  - `?? solitaire/application/` `?? solitaire/core/` `?? solitaire/data/` `?? solitaire/deal/` `?? solitaire/docs/` `?? solitaire/presentation/` `?? solitaire/scenes/` `?? solitaire/tests/`
  - `?? solitaire2/`（目标工程整体未跟踪）
- 目标 `solitaire2/**` 未跟踪 —— 与合同 §2 一致。

## 5. MCP 复用源（固定提交只读核验）

- `solitaire/addons/godot_ai/**`：跟踪文件 **267** 个（`ls-tree -r` 与 `ls-files` 双口径一致；全部 mode 100644；无 gitlink/子模块；含 132 个 .uid 文件）。
- `solitaire/mcp_verify.tscn`：固定提交中存在（1 个）。
- `plugin.cfg`：name="Godot AI"，version="3.2.4"，script="plugin.gd" —— 与 MCP-SOURCE-001 一致。
- **差异待裁定**：合同 §6 WP-02 / worker-order / TD 预调查记“269 个跟踪文件”。实测 267；267 + mcp_verify.tscn + project.godot = 269，疑似原计数含此两文件。执行者不自行取舍：WP-02 的导出与逐项一致性验证以固定提交实际文件（267）为准，请 TD 裁定权威计数并据实修订合同指标。

## 6. 旧工程状态（pre 记录，未写入）

- 旧 Godot `/Volumes/Mac studio pro/solitaire/godot/solitaire`：父仓库子路径；pre-status 9 行（1 modified + 8 untracked，见 §4）。
- 旧 Cocos `/Volumes/Mac studio pro/solitaire/WTF-Solitaire`：独立仓库；pre-status 5 行（proj.ios_mac 下 5 个未跟踪项）。
- 本 WP 全程未对这些路径做任何写入；post = pre（WP-04 将再次核对）。

## 7. 其他基线记录（§3.3）

- 凭证/密钥存在性扫描（目标 maxdepth 4，模式 .env*/*.pem/*.key/id_rsa*/*.p12/*.pfx）：无命中。仅检查存在性，未读取值。
- 运行环境：Godot.app 存在（/Applications）；godot 不在 PATH（WP-03 经 MCP 操作，不受影响）。

## 8. 结果

- WP-01 验收指标逐项：路径精确且无旧顶层目录 ✓；6 源文件 hash 一致（含聚合与 project.godot）✓；11 缓存 ✓；0 符号链接 ✓；父 Git commit + 完整 status 一致 ✓；旧工程 pre 状态已记录且零写入 ✓。
- 唯一待裁定项：addon 跟踪文件数 267 vs 文档 269（§5）。
- 未验证/限制：未做任何 bootstrap（属 WP-02）；Godot 编辑器打开、插件连接、MCP 空场验证属 WP-03。

## 9. 依赖

- WP-02（MCP 最小 Bootstrap）依赖本证据包被技术总监确认，并需 TD 对 addon 文件数（267/269）作出裁定后再启动。
