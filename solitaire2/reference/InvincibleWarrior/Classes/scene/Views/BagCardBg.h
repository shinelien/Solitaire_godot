//
//  BagCardBg.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/13.
//

#ifndef BagCardBg_h
#define BagCardBg_h
#include "BaseLayer.h"
#include "Factory.hpp"
class BagView;
class BagCardBg : public BaseLayer, public Factory<BagCardBg>
{
public:
    BagCardBg(BagView* bagView);
    ~BagCardBg();
    void updateUI();
    
    static BagCardBg * createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback,BagView* bagView);
    void setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback);
    bool setUse(bool isUse, bool isInit = false);
    void playLightAction();
    void selected(bool flag);
    void setNew(bool is);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    Layout * panel_item;
    
    ImageView *img_suo;
    Sprite *img_card,*img_card2;
    ImageView *Sprite_used_bg;
    ImageView *Image_new_bg;
    bool isBuyed;
    bool isUsing;
    int shopType;
    int index;
    bool isTouchMove;
    Vec2 img_card_poi;
    bool isNew;
    BagView* _bagView;
    int _price;
};

#endif /* BagCardBg_h */
