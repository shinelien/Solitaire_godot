//
//  FashTankUp.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/31.
//

#ifndef FashTankUp_h
#define FashTankUp_h
#include "BaseLayer.h"
#include "Factory.hpp"

class FashTankUp : public BaseLayer, public Factory<FashTankUp>
{
public:
    FashTankUp();
    ~FashTankUp();
    void onEnter() override;
    void onExit() override;
    void peiShiMove();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    Sprite* Sprite_reward,*Sprite_complete,*Sprite_BG;
    vector<vector<string>> peiShiFrameVec;
    int _fashTankIdx,_unlockIdx;
    Sprite *Sprite_peiShi;
    Vec2 startPoi;
    Node*FileNode_man;
    int effectIdx;
    
    bool isTouch;
};
#endif /* FashTankUp_h */
