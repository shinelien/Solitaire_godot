//
//  RankItem.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/11.
//

#ifndef RankItem_h
#define RankItem_h
#include "BaseLayer.h"
#include "Factory.hpp"
class RankView;
class RankItem : public BaseLayer, public Factory<RankItem>
{
public:
    RankItem(RankView* rankView);
    ~RankItem();
    void updateUI();
    void updateName();
    //需要 排名 idx  名字 name 鱼缸id  鱼缸里的鱼vector<int> fishVec
    static RankItem * createBagNode(int idx,RankView* rankView);
    
    void setShopNodeState(int idx);
    
    vector<int> getFishVec() { return _fishVec; }
    vector<bool> getIsDailyVec() { return _isDailyVec; }
    std::vector<bool> getIsFashTankUnlockVec() const { return _isFashTankUnlockVec; }
    int getLevel() { return _lv; }
    int getScore() { return _score; }
    string getUserName() { return _name; }
    string getCy() { return _cy; }
    string getUserKey() { return _key; }
    int getFashTankId() { return _fashTankId; }
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    RankView* _rankView;
    int _idx, _fashTankId, _lv, _score;
    Sprite* Sprite_JiangBei;
    string _name, _cy, _key;
    vector<int> _fishVec;
    vector<bool> _isDailyVec;
    vector<bool> _isFashTankUnlockVec;
    rapidjson::Value _rankArr;
};

#endif /* RankItem_h */
