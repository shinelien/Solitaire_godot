
#ifndef SpacecatSolitaireGame_ShopViewHD_H
#define SpacecatSolitaireGame_ShopViewHD_H

#include "BaseLayer.h"
#include "Factory.hpp"
#include <unordered_map>

class ShopNode;
class ShopViewHD : public BaseLayer, public Factory<ShopViewHD> {
public:
    enum class Tab {
        None,
        POKER_BACK,
        POKER_FORE,
        BACKGROUND
    };

    virtual ~ShopViewHD();
    ShopViewHD(bool isLobby = false);

    void onEnter() override;
    void onExit() override;
    void setTab(Tab tab);
    Tab getTab();
    void refush(bool isRefushAll);
    int getTotalCNT(Tab tab);
    void showSelect(int shopType, int shopIndex, const string name);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    void updateUI();

    vector<ShopNode*> _items;
    unordered_map<int, int> nowUseIndex;

    Tab _currentTab;
    vector<Button*> _tabBtnVec;
    bool _isLobby;
};

#endif //SpacecatSolitaireGame_ShopViewHD_H
