//
//  FashTankShop.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/18.
//

#ifndef FashTankShop_h
#define FashTankShop_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include "TeachInterface.h"

class BagGameBg;
class MainLobby;
class FashTankShop : public BaseLayer, public Factory<FashTankShop>
{
public:
    enum class Tab {
        None,
        
        FISH = 8,
        FASHTANK,
    };
    
    
    FashTankShop();
    ~FashTankShop();
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
    
    void setFashTankIdx(int idx);
    void toFish(int guanLiIdx);
    void toFashTank();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    int startIDX,_fashTankIdx,_guanLifashTankIdx;
    Tab _currentTab = Tab::None;
    Node* Image_top;
    Node* FileNode_BagItem1;
    Button* Button_guanLi,*Button_back;
    Text* Text_guanLi;
    int _coinNum;
    int _diamondNum;
    ListView* scrollViewBG;
    TextBMFont* BitmapFontLabel_lvNum;
    Text* Text_lvStr;
    BaseLayer* guideNode;
};

#endif /* FashTankShop_h */
