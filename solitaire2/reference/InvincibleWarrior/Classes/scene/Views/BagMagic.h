//
//  BagMagic.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/13.
//

#ifndef BagMagic_h
#define BagMagic_h
#include "BaseLayer.h"
#include "Factory.hpp"

class BagMagic : public BaseLayer, public Factory<BagMagic>
{
public:
    BagMagic();
    ~BagMagic();
    void updateUI();
    
    static BagMagic * createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback);
    void setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback);
    //bool setUse(bool isUse, bool isInit = false);
    //void playLightAction();
    void selected(bool flag);
    void setMusicUse(bool flag);
    
    void updateMagicNum();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    Layout *panel_Magic;
    
    
    bool isBuyed;
    bool isUsing;
    int shopType;
    int index;
    bool isTouchMove;
    Vec2 img_card_poi;
};

#endif /* BagMagic_h */
