//
//  FishShop.h
//  NewSpaceCatSolitaire-mobile
//
//  Created by 宋 on 2021/4/30.
//

#ifndef FishShop_h
#define FishShop_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include "TeachInterface.h"

class BagGameBg;
class MainLobby;
class FishShop : public BaseLayer, public Factory<FishShop>
{
public:
    enum class Tab {
        None,
        
        FISH = 8,
        FASHTANK,
    };
    
    
    FishShop();
    ~FishShop();
    void onEnter() override;
    void onExit() override;
    
    void setTab(Tab tab);
    Tab getTab();
    //void refush(bool isRefushAll);
    int getTotalCNT(Tab tab);
    void showSelect(int shopType, int shopIndex, const string name);
    void updateUI();
    void updateCoin(bool isDelay = false);
    void updateDiamond(bool isDelay = false);
    
    Layout* getPanelView(Tab tab);
    int getSPLIT(Tab tab);
    void updateUI2();
    
    void updateMagicNum();
    
    Vec2 getGoldWorldPoi();
    Vec2 getdiamondWorldPoi();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    int startIDX,_fashTankIdx;
    Tab _currentTab = Tab::None;
    
    Node* FileNode_BagItem1;
    
    int _coinNum;
    int _diamondNum;
    BagGameBg* guideNode;
    Vec2 guidePoi;
};


#endif /* FishShop_h */
