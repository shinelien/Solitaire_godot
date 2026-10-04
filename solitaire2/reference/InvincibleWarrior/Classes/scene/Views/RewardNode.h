//
//  RewardNode.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/19.
//

#ifndef RewardNode_h
#define RewardNode_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include "GameBackground.h"
class GameBackground;
class RewardNode : public BaseLayer, public Factory<RewardNode>
{
public:
    RewardNode(GameBackground::RewardType rewardType,int rewardNum);
    ~RewardNode();
    void updateUI();
    void showReward();
    void hideReward();
    Rect getWorldRect();
    Rect getRewardRect();
    bool getIsTouch() { return isTouch; }
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    GameBackground::RewardType _rewardType;
    int _rewardNum;
    bool isTouch;
};

#endif /* RewardNode_h */
