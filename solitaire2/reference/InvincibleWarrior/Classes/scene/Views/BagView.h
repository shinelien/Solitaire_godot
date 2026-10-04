//
//  BagView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/29.
//

#ifndef BagView_h
#define BagView_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include "TeachInterface.h"

class BagNode;
class BagCardBg;
class BagCardFace;
class BagGameBg;
class BagMusic;
class BagMagic;
class MainLobby;
class BagView : public BaseLayer, public Factory<BagView>, public TeachInterface
{
public:
    enum class Tab {
        None,
        BACKGROUND,
        POKER_FORE,
        POKER_BACK,
        POKER,
        MUSIC,
        PROPS,
        FASHTANK,
        FISH = 8,
    };
    
    enum class BagType
    {
        FISH,
        CARD,
    };
    
    BagView(BagType bagType);
    ~BagView();
    void onEnter() override;
    void onExit() override;
    
    void setTab(Tab tab);
    Tab getTab();
    //void refush(bool isRefushAll);
    int getTotalCNT(Tab tab);
    void showSelect(int shopType, int shopIndex, const string name);
    void updateUI();
    void updateMagic();
    void updateCoin(bool isDelay = false);
    void updateDiamond(bool isDelay = false);
    Node* getTeachItem(const std::string &name, int idx) override;
    
    Layout* getPanelView(Tab tab);
    int getSPLIT(Tab tab);
    void updateBagItem1(int index);
    void updateUI2();
    void updateCardBgNew();
    void updateCardFaceNew();
    void updateGameBgNew();
    void updateMusicNew();
    
    void updateMagicNum();
    
    Vec2 getGoldWorldPoi();
    Vec2 getdiamondWorldPoi();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    vector<BagNode*> _items;
    vector<BagGameBg*> _gameBgitems;
    vector<BagCardBg*> _cardBgitems;
    vector<BagCardFace*> _cardFaceitems;
    vector<BagMusic*> _musicitems;
    vector<BagMagic*> _magicitems;
    unordered_map<int, int> nowUseIndex;
    int startIDX;
    Tab _currentTab = Tab::None;
    vector<Button*> _tabBtnVec;
    
    Node* FileNode_BagItem1;
    
    int _coinNum;
    int _diamondNum;
    BagType _bagType;
};

#endif /* BagView_h */
