//
//  BagCardFaceItem.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/22.
//

#ifndef BagCardFaceItem_h
#define BagCardFaceItem_h
#include "BaseLayer.h"
#include "Factory.hpp"
class BagView;
class BagCardFaceItem : public BaseLayer, public Factory<BagCardFaceItem>
{
public:
    BagCardFaceItem(BagView* bagView);
    ~BagCardFaceItem();
    void updateUI();
    
    static BagCardFaceItem * createBagNode(int shopType, int index,int id, BagView* bagView);
    void setShopNodeState(int shopType, int index,int id);
    bool setUse(bool isUse, bool isInit = false);
    void setNew(bool is);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    Layout * panel_item;

    Sprite *img_card,*img_card2;
    ImageView *Sprite_used_bg;
    ImageView *Image_new_bg;
    bool isBuyed;
    bool isUsing;
    int shopType;
    int index,id;
    bool isNew;
    BagView* _bagView;
};

#endif /* BagCardFaceItem_h */
