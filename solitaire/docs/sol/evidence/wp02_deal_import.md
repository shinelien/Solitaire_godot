# WP-02 旧牌库导入与 Golden 取证

- 阶段: S1-GODOT-CORE-LOOP
- 执行者: DeepSeek v4 Worker
- 环境: Godot 4.6.2.stable.custom_build.001aa128b (headless), macOS darwin
- 时间: 2026-09-02T03:09+0800
- 基线: origin/InvincibleWarrior@12b33cbed606952e4f90c88d987961a6ef8f50fc（严格只读）

## 权威 blob（固定 commit，git cat-file/git show 只读）

| 牌库 | 源 blob (git rev-parse) | 大小(bytes) | 记录数 |
|---|---|---|---|
| Resources/data/bureau1.d | c43a8957bf7e13e0965fa9ae6ddbc8a2aa82c690 | 1,700,452 | 32,084 |
| Resources/data/bureau3.d | a04650d67840dee32b4171db9230b2e4c40b8f75 | 264,947 | 4,999 |

验证命令：`git -C <legacy> cat-file -p 12b33cb...:Resources/data/bureau1.d > data/legacy/bureau1.d`（逐字节复制，未使用工作树版本）。

## 导入副本（data/legacy/）

| 文件 | SHA-256 | 字节 | 行数 |
|---|---|---|---|
| bureau1.d | 36414bfcd91c916caa77c8b908dc51000732bfc8ba2b8113798d6a2a48d2ccf5 | 1,700,452 | 32,084 |
| bureau3.d | 0bf9409ac5a5954a02460274fc50e8cd1ca79693be4dd90e70cc6ebcac81ca43 | 264,947 | 4,999 |

- 命令：`shasum -a 256`, `wc -c`, `wc -l`，退出码 0。
- Draw-1 SHA-256 与施工合同 §2 完全一致；Draw-3 哈希与固定源 blob 一致。

## Golden 静态期望（data/legacy/golden/golden_draw1.json）

- 样本：bureau1.d 前 50 条记录。
- 生成方法：独立 Python 实现（tests/golden/generate_golden.py）实现 ADR-004 语义：
  - id = byte − ASCII '0'；倒序得到 draw order；列优先三角发牌（1..7，末张明牌）；剩余 24 张入 stock。
  - 每条记录校验 52 字符、id ∈ [0,51]、52 个 id 唯一。
- 期望文件在测试运行期间绝不由被测 GDScript decoder 生成（test_source_boundaries 校验运行时代码不引用 golden 文件）。
- 交叉验证：Python 独立生成的 golden 与 GDScript LegacyDealDecoder+LegacyDealBuilder 输出逐一比对，50/50 通过，每副 tableau+stock 覆盖 52/52 唯一 id。

## 解码语义（定点于 SpriteManager.cpp，见 wp01_forensics.md）

- initCardIds: `for i in 0..51: cardIds.push(record[51-i]-'0')`；SIMPLE_CHECK_SUM=1326。
- getCardId: 从前端取（保持倒序顺序）。
- initKCardAfter: 列优先 col0..6，行 0..col；末张(col==row)明牌。
- initWaitCard: 剩余 24 张入 Stock，栈顶=最后元素；初始发牌后自动抽一组（Draw-1 抽 1，Draw-3 抽 3）。
- 错误语义：解码失败严格返回失败，禁止随机回退。
