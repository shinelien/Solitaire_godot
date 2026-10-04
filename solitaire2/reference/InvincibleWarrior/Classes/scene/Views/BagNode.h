//
//  BagNode.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/29.
//

#ifndef BagNode_h
#define BagNode_h
#include "BaseLayer.h"
#include "Factory.hpp"

class BagNode : public BaseLayer, public Factory<BagNode>
{
public:
    BagNode();
    ~BagNode();
    void updateUI();
    
    static BagNode * createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback);
    void setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback);
    bool setUse(bool isUse, bool isInit = false);
    void playLightAction();
    void selected(bool flag);
    void setMusicUse(bool flag);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    Layout * panel_item,*panel_item_0,*panel_zhengmian,*panel_Changjing,*panel_Music,*panel_Magic;
    
    ImageView *img_suo;
    Sprite *img_card,*img_card2;
    ImageView *Sprite_used_bg,*Sprite_used_face,*Sprite_used_gameBg,*Sprite_used_music;
    ImageView *Image_new_bg,*Image_new_face,*Image_new_gameBg,*Image_new_music;
    bool isBuyed;
    bool isUsing;
    int shopType;
    int index;
    bool isTouchMove;
    Vec2 img_card_poi;
};

#endif /* BagNode_h */
