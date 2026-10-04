//
//  BagGameBg.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/13.
//

#ifndef BagGameBg_h
#define BagGameBg_h
#include "BaseLayer.h"
#include "Factory.hpp"
class FishShop;
class FashTankShop;
class BagGameBg : public BaseLayer, public Factory<BagGameBg>
{
public:
    BagGameBg(FishShop* fishShop,FashTankShop* fashTankShop);
    ~BagGameBg();
    void updateUI();
    
    static BagGameBg * createBagNode(int shopType, int index,int type,int fashTankIdx, std::function<void(Ref *)> clickCallback,FishShop* fishShop,FashTankShop* fashTankShop);
    void setShopNodeState(int shopType, int index,int type,int fashTankIdx, std::function<void(Ref *)> clickCallback);
    bool setUse(bool isUse, bool isInit = false);
    void playLightAction();
    void selected(bool flag);
    void setNew(bool is);
    FashTankShop* getFashTankShop() { return _fashTankShop; }
    void updateGuide();
    void setIsTouch(bool touch) { isTouch = touch; };
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    Layout *panel_Changjing;
    
    ImageView *img_suo;
    Sprite *img_card,*img_card2;
    //ImageView *Sprite_used_gameBg;
    ImageView *Image_new_gameBg;
    bool isBuyed;
    bool isUsing;
    int shopType;
    int index,_fashTankIdx,_type;
    bool isTouchMove;
    Vec2 img_card_poi;
    bool isNew;
    FishShop* _fishShop;
    FashTankShop* _fashTankShop;
    int _price,_sellPrice;
    int _fishNum;
    bool isTouch;
};

#endif /* BagGameBg_h */
