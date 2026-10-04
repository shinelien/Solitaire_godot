//
//  StoreView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/25.
//

#ifndef StoreView_h
#define StoreView_h
#include "BaseLayer.h"
#include "Factory.hpp"
class ShopNode;
class MainLobby;
class StoreView : public BaseLayer, public Factory<StoreView>
{
public:
    StoreView(MainLobby* mainLobby);
    ~StoreView();
    void onEnter() override;
    void onExit() override;
    
    void updateUI();
    void updateCoin();
    void updateDiamond();
    void playBagAni();
    Vec2 getBagWorldPoi();
    void updateDYY();
    void updateBtnGold();
    void updateBtnDiamond();
    void updataBagNew();
    //切换模式时隐藏奖品描述
    void showMiaoShu(bool isShow);
    void updateMiaoShu();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    MainLobby* _mainLobby;
    int goldBS;
    int diamondBS;
    bool isGold,isDiamond;
    Node* FileNode_MyBag,*Node_dyy,*FileNode_Gold_btn,*FileNode_Diamond_btn,*FileNode_MiaoShu;
    TextBMFont* Text_btnGold,*Text_btnDiamond;
    
    //描述
    Sprite* card_gold_fronts,*card_gold_bg,*card_diamond_front,*card_diamond_bg,*scene_diamond_bg;
    Text* Text_gold_front,*Text_gold_bg,*Text_gold_magic,*Text_gold_bigwin,*Text_diamond_front,*Text_diamond_bg,*Text_diamond_magic,*Text_diamond_bigwin,*Text_diamonnd_scene,*Text_diamond_music;
    Node* card_1,*card_2;
};
#endif /* StoreView_h */
