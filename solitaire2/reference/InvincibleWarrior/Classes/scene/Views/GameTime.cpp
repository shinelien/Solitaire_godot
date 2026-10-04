//
//  GameTime.cpp
//  SpacecatSolitaireGame-mobile
//
//  Created by Cyutao on 2018/8/27.
//

#include "GameTime.hpp"

GameTime::GameTime()
:BaseLayer("GameTime.csb")
,_time(-1){
    for (int i = 0; i < TimeType::End; ++i) {
        _timeVec.push_back(-1);
    }
    _excludeRecord = true; // 不要记录进入
}

void GameTime::setTime(time_t time)
{
    if (_time != time) {
        _time = time;
//        int fen = (int)(_time / 60);
//        int fen1 = fen/10;
//        int fen2 = fen%10;
//        int miao = ((int)_time % 60);
//        int miao1 = miao/10;
//        int miao2 = miao%10;
        int hour1 = int(time/10000);
        int fen1 = int(time/1000%100);
        int fen2 = int(time/100%10);
        int miao1 = int(time/10%10);
        int miao2 = int(time%10);
        setTimeAni(hour1, TimeType::Hour1);
        setTimeAni(fen1, TimeType::Fen1);
        setTimeAni(fen2, TimeType::Fen2);
        setTimeAni(miao1, TimeType::Miao1);
        setTimeAni(miao2, TimeType::Miao2);
    }
}

void GameTime::setTimeAni(int value, TimeType t) {
    if (_timeVec[t] != value) {
        auto currentValue = MAX(0, _timeVec[t]);
        auto child = _nodeVec[t];
        auto root = child->getChildByName("Sprite_root");
        auto actionManager = dynamic_cast<cocostudio::timeline::ActionTimeline *>(child->getActionByTag(child->getTag()));
        if (actionManager) {
            if (actionManager->getCurrentFrame() == actionManager->getEndFrame()
                || actionManager->getCurrentFrame() == 0) { // 如果刚播放完第二段动画
    //            ui::Helper::seekWidgetByName(child, "Sprite_0_0")
                root->getChildByName<Sprite*>("Sprite_0_0")->setSpriteFrame(StringUtils::format("time0_%d_0.png", currentValue));
                root->getChildByName<Sprite*>("Sprite_0_1")->setSpriteFrame(StringUtils::format("time0_%d_1.png", currentValue));
                root->getChildByName<Sprite*>("Sprite_1_0")->setSpriteFrame(StringUtils::format("time0_%d_0.png", value));
                root->getChildByName<Sprite*>("Sprite_1_1")->setSpriteFrame(StringUtils::format("time0_%d_1.png", value));
                actionManager->play("start0", false);
            }
            else {
                root->getChildByName<Sprite*>("Sprite_1_0")->setSpriteFrame(StringUtils::format("time0_%d_0.png", currentValue));
                root->getChildByName<Sprite*>("Sprite_1_1")->setSpriteFrame(StringUtils::format("time0_%d_1.png", currentValue));
                root->getChildByName<Sprite*>("Sprite_2_0")->setSpriteFrame(StringUtils::format("time0_%d_0.png", value));
                root->getChildByName<Sprite*>("Sprite_2_1")->setSpriteFrame(StringUtils::format("time0_%d_1.png", value));
                actionManager->play("start1", false);
            }
        }
        _timeVec[t] = value;
    }
}

void GameTime::initData()
{
    setName("GameTime");
}

/***
 * 0 1   2 3 <-[idx]
 * 0 0 : 0 0
 */
void GameTime::initUI()
{
    BaseLayer::initUI();
    _nodeVec.resize(TimeType::End);
    // 跑起来actionManager
    static vector<string> nodeNames{"FileNode_hour1", "FileNode_min1", "FileNode_min0", "FileNode_sec1", "FileNode_sec0"};
    for (int i = TimeType::Hour1; i<=TimeType::Miao2; i++) {
        auto actionManager = ActionTimelineCache::createAction("card/Timer.csb");
        auto node = getNode<Node*>(nodeNames[i]);
        _nodeVec[i] = node;
        node->runAction(actionManager);
        actionManager->setTag(node->getTag());
    }
}
