//
//  BagCardFace.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/13.
//

#ifndef BagCardFace_h
#define BagCardFace_h
#include "BaseLayer.h"
#include "Factory.hpp"
class BagView;
class BagCardFace : public BaseLayer, public Factory<BagCardFace>
{
public:
    BagCardFace(BagView* bagView);
    ~BagCardFace();
    void updateUI();
    
    static BagCardFace * createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback,BagView* bagView);
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
    Layout *panel_zhengmian;
    
    ImageView *img_suo;
    Sprite *img_card,*img_card2;
    ImageView *Sprite_used_face;
    ImageView *Image_new_face;
    bool isBuyed;
    bool isUsing;
    int shopType;
    int index;
    bool isTouchMove;
    Vec2 img_card_poi;
    bool isNew;
    BagView* _bagView;
};

#endif /* BagCardFace_h */
