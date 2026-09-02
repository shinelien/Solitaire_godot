# WP-01 基线与取证（Legacy Behavior Forensics）

- 阶段: S1-GODOT-CORE-LOOP
- 执行者: implementation Executor (worker-order-s1.md)
- 时间: 2026-09-02 (session)
- 环境: Godot 4.6.2-stable custom build; Godot AI MCP 3.2.4 (session solitaire@bbcb, project path /Volumes/Mac studio pro/solitaire/godot/solitaire/)

## 权威基线验证

- 固定 commit: origin/InvincibleWarrior = 12b33cbed606952e4f90c88d987961a6ef8f50fc (2021-11-30 17:34:57 +0800, Merge branch 'InvincibleWarrior')
- git rev-parse origin/InvincibleWarrior 输出与固定 commit 一致。
- bureau1.d blob (git rev-parse): c43a8957bf7e13e0965fa9ae6ddbc8a2aa82c690, 对象大小 1700452 bytes = 32084 × 53
- bureau3.d blob: a04650d67840dee32b4171db9230b2e4c40b8f75, 对象大小 264947 bytes = 4999 × 53

## 解码语义取证（只读 git show 12b33cb...）

### SpriteManager::initCardIds (Classes/manager/SpriteManager.cpp)
- reloadFile(): 读取 data/bureau1.d 与 data/bureau3.d，调用 cocos2d::utils::image_decrypt。
- image_decrypt (cocos2d/cocos/base/ccUtils.cpp): 若文件头不匹配 XXTEA_HM_SIGN 则原样返回 —— 对这两份牌库是 no-op，文件即纯 ASCII。
- getBureau(t): 每记录 53 bytes，currentIDX*53 起取 52 bytes。
- 解码循环: for i in 0..51: value = *(it+51-i) - '0' → cardIds[i] = record[51-i] - ASCII '0'（即整条 52 字节反转后逐字节减 '0'）。
- sum 校验: SIMPLE_CHECK_SUM = SUM(51) = 0+1+...+51 = 1326；若不符旧代码会随机重排 —— 本合同要求改为严格失败，不回退随机（见施工合同 §10.5）。

### getCardId() (line 505)
- 从 cardIds 前端 (index 0) 取出并 erase → 按反转后顺序逐个发牌。

### initKCardAfter() (line 1023) —— 发牌布局
- for col 0..6, for row 0..col: cardId = getCardId(); kCardVector[col].pushBack(cardSprite)
- 每列 1..7 张，列优先填充（col0 取 cardIds[0]，col1 取 cardIds[1..2]，...，col6 取 cardIds[21..27]）。
- createCardSprite(cardId, ..., col==row) 第三个参数为明牌标志 → 每列最后一张（col==row 时）为 face-up。
- 共 28 张入 Tableau；剩余 cardIds[28..51] 24 张。

### initWaitCard() (line 1084) —— Stock 顺序
- for num 0..23: cardId = getCardId() → waitCardVector.pushBack(cardSprite)
- Stock 数组 = [cardIds[28], cardIds[29], ..., cardIds[51]]，栈顶 = 最后一个元素（cardIds[51]）。

### openWaitCard() / openOneWaitCard() (line 1298/1270) —— 抽牌
- 取 waitCardVector.at(size-1)（栈顶）→ waitShowCardVector.pushBack（Waste 顶 = 最后元素）。
- Draw-1: openOneWaitCard(2) 只抽 1 张。
- Draw-3: startIdx = 3 - MIN(3, waitCNT)；循环 i=startIdx..2 → 抽 MIN(3, 剩余) 张；尾组不足 3 张时抽尽剩余。

### resetWaitCard() (line 1340) —— 回收（无限循环）
- 反复取 Waste 顶 (size-1) → waitCardVector.pushBack 到 Stock 末尾，直到 Waste 空。
- 回收后 Stock = [旧Stock..., 原Waste顶,...,原Waste底]；新栈顶 = 原第一批抽出的第一张 → 保持原抽牌顺序，可无限回收。

### 纸牌映射 CardSprite::setCardDataByCardId (Classes/object/CardSprite.cpp line 262)
- number = cardId % 13 + 1（rank 1..13）
- colorType = cardId / 13（suit 0=♠,1=♥,2=♣,3=♦）

### 规则（同文件）
- checkKPos (line 685): number - 1 == target.number（降序 1）且花色交替（黑{0,2}↔红{1,3}）。
- checkAPos (line 676): number + 1 == target.number 且 colorType 相同（同花色升序）。
- checkKCardPos (line 1801): 空列仅接受 number == 13（K）。
- checkACardPos (line 1769): 空基础堆仅接受 number == 1（A）。
- 胜利 (line ~2000): 4 个 aCardVector 均 size() == 13。

## 本阶段语义定义（与合同一致）

- 每条记录: 52 ASCII 字节 + 1 换行；Card ID = byte - ASCII '0'；先整体反转 52 字节得到 cardIds（列优先发牌顺序）。
- 发牌: col0..6 各取 1..7 张（列优先），每列最后一张 face-up；剩余 24 张入 Stock（顺序 = cardIds[28..51]，栈顶 = 最后元素）。
- 严格校验: 长度必须 52/53；每字节 ∈ ['0','0'+51]；52 个 ID 必须互不重复（等价于不缺牌）；失败即报错，不回退随机。

## 关键命令（只读，Cocos 工作树零改动）

- git -C /Volumes/Mac studio pro/solitaire/WTF-Solitaire rev-parse origin/InvincibleWarrior
- git -C ... show 12b33cbed606952e4f90c88d987961a6ef8f50fc:Classes/manager/SpriteManager.cpp
- git -C ... show 12b33cbed606952e4f90c88d987961a6ef8f50fc:Classes/object/CardSprite.cpp
- git -C ... show 12b33cbed606952e4f90c88d987961a6ef8f50fc:cocos2d/cocos/base/ccUtils.cpp
- git -C ... show 12b33cbed606952e4f90c88d987961a6ef8f50fc:Resources/data/bureau1.d > data/legacy/bureau1.d
- git -C ... show 12b33cbed606952e4f90c88d987961a6ef8f50fc:Resources/data/bureau3.d > data/legacy/bureau3.d

## 产物与结果

- data/legacy/bureau1.d: 1,700,452 bytes, SHA-256 36414bfcd91c916caa77c8b908dc51000732bfc8ba2b8113798d6a2a48d2ccf5 (与合同一致), 32,084 条
- data/legacy/bureau3.d: 264,947 bytes, SHA-256 0bf9409ac5a5954a02460274fc50e8cd1ca79693be4dd90e70cc6ebcac81ca43, 4,999 条
- data/legacy/golden/bureau1_draw1_first50.json: 50 个静态 Golden Case（encoded + ids + tableau + face_up + stock），由独立 Python 参考实现生成，与运行时 decoder 分离。
- 限制: 未修改 Cocos 工作树（仅 git show / git rev-parse / git cat-file）；未 checkout/switch/reset/clean/stash/format。
