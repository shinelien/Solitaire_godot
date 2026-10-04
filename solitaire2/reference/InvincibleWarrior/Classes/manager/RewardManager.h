//
// Created by Cyutao on 2019-07-12.
//

#ifndef SOLITAIRECLASSICGAME_REWARDMANAGER_H
#define SOLITAIRECLASSICGAME_REWARDMANAGER_H

#include "SqlCommon.h"
#include "SqlTable.h"
#include "SqlDatabase.h"
#include "cocos2d.h"

#define REWARD_M RewardManager::getInstance()

using namespace cocos2d;
class RewardManager {
public:
    enum class RewardType {
        Gold,
        Magic,
        PokerFace,
        ZuanShi,
        CARDBG,
        CARDFACE,
        None,
    };
    
    ~RewardManager();
    
    static RewardManager *getInstance();
    void getReward(RewardType type, int count, bool notify = false);
    int getCNT(RewardType type);
    int useItem(RewardType type, int count=1);
    
    void updateMultipleNum();
    int getMultipleNum();
    bool getis7Multiple();
    
    
    //奖励显示动画
    void rewardItemAction(int num,Vec2 targetPoi,Vec2 startPoi,std::vector<Vec2> itemVec,std::function<void()> itemCB,std::string aniName,Node* parent,std::function<void()> itemEndCB,std::function<void()> itemEnd2);
private:
    RewardManager();
    void init();
    std::string getKey(RewardType type);
    static RewardManager *s_instance;
    int multipleNum;//5倍奖励次数
    bool isLianXu;//连续7倍
    
    
    unsigned int effDId;
    unsigned int effGId;
};


#endif //SOLITAIRECLASSICGAME_REWARDMANAGER_H
