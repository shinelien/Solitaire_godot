//
//  FashTankItem.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/18.
//

#ifndef FashTankItem_h
#define FashTankItem_h
#include "BaseLayer.h"
#include "Factory.hpp"
class FashTankShop;
class FashTankItem : public BaseLayer, public Factory<FashTankItem>
{
public:
    FashTankItem(FashTankShop* fishShop);
    ~FashTankItem();
    void updateUI();
    static FashTankItem * createBagNode(int idx,FashTankShop* fishShop);
    
    void setShopNodeState(int idx);
    void selected(bool flag);
    void setIsTouch(bool isTouch);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    FashTankShop* _fishShop;
    int _idx;
    Node* Sprite_used_bg,*Panel_unlock;
    bool isUnlock,_isTouch;
    
};

#endif /* FashTankItem_h */
