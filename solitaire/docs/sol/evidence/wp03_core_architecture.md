# WP-03 Core 架构与源码边界

- 阶段: S1-GODOT-CORE-LOOP
- 执行者: DeepSeek v4 Worker
- 时间: 2026-09-02
- 环境: Godot 4.6.2 custom build (headless)

## 模块结构（typed GDScript，Godot 4.6 兼容）

- core/model/: CardData, Location, PileType —— 纯逻辑，不继承 Node。
- core/state/: GameStatus, GameState（SSOT，深拷贝 snapshot，不变量检查，equals）。
- core/rules/: KlondikeRules —— 纯规则静态函数，不改变状态。
- core/moves/: Move, MoveCommand（事务）, MoveResult, MoveExecutor（原子执行）。
- deal/repository/: LegacyDealDecoder（严格 52 字节解码）, LegacyDealBuilder, LegacyDealRepository。
- deal/selector/: DealSelector —— 中立均匀随机，无 DDA。
- application/: GameConfig, GameController（命令/Undo/Hint/Auto Complete/Replay/New Deal/Draw 切换）。
- presentation/board|cards|input/: BoardView, CardView, InputHandler —— 只读渲染 + 意图，禁止改状态。
- scenes/main.tscn + main.gd：装配 HUD 按钮与状态反馈。

## 核心语义

- GameState 是唯一游戏真相；UI 只渲染 GameState 并调用 controller 意图方法。
- 所有玩家/Hint/Auto Complete/Replay 操作统一经 MoveCommand + MoveExecutor；非法命令原子失败（工作副本丢弃，GameState/history/undo 零变化）。
- 自动暴露的 Tableau 翻牌是同一事务内的显式 FlipTableau Move。
- Undo 用命令边界的深拷贝 snapshot 恢复 draw_mode/stock/waste/tableau/foundation/status/计数/history/session。
- Draw-1/Draw-3、尾组不足 3 张、无限回收：按 legacy 语义（栈顶=最后元素）。
- Hint 只读返回合法 Move；Auto Complete 仅执行当前合法 foundation Move，停滞安全停止；Replay 恢复同一 encoded 与 draw_mode。
- 胜利由 4×13 Foundation 判定（GameStatus.WON）。

## 源码边界证据（自动化测试 test_source_boundaries + 外部 grep）

- `rg "extends Node|extends Control|extends CanvasItem" core/**/*.gd` → 0 处。
- 运行期检查：核心类实例 `is Node` 全部为 false，全部 `is RefCounted`。
- `rg "push_back|pop_back|.resize(|face_up =|controller.state =" presentation/**/*.gd` → 仅 1 处为只读判空 `controller.state == null`（正则排除后为 0）。
- presentation 不包含 `state.stock.*/state.waste.*` 写操作、不出现 `state.tableau/state.foundations` 直改。

## 解析备注

- 本引擎对 `Array[T]()` 构造器解析失败 → 统一改为 `var x: Array[T] = []`（见 wp08 迭代记录）。
- GameState 与 KlondikeRules 不形成 class_name 依赖环（invariant 内联本地规则副本），确保 headless 全量分析通过。
