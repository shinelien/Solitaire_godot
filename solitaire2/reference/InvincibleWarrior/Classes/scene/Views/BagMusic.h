//
//  BagMusic.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/13.
//

#ifndef BagMusic_h
#define BagMusic_h
#include "BaseLayer.h"
#include "Factory.hpp"
class BagView;
class BagMusic : public BaseLayer, public Factory<BagMusic>
{
public:
    BagMusic(BagView* bagView);
    ~BagMusic();
    void updateUI();
    
    static BagMusic * createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback,BagView* bagView);
    void setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback);
    bool setUse(bool isUse, bool isInit = false);
    void playLightAction();
    void selected(bool flag);
    void setMusicUse(bool flag);
    void setNew(bool is);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    Layout*panel_Music;
    
    ImageView *img_suo;
    Sprite *img_card,*img_card2;
    ImageView *Sprite_used_music;
    ImageView *Image_new_music;
    Node* FileNode_music;
    bool isBuyed;
    bool isUsing;
    int shopType;
    int index;
    bool isTouchMove;
    Vec2 img_card_poi;
    bool isNew;
    cocostudio::timeline::ActionTimeline* aniManager;
    BagView* _bagView;
    int _price;
};

#endif /* BagMusic_h */
