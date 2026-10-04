//
//  GoldShop.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/25.
//

#ifndef GoldShop_h
#define GoldShop_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include "TeachInterface.h"
class Product;
class GoldShop : public BaseLayer, public Factory<GoldShop>
{
public:
    enum class Tab {
        None,
        Gold,
    };
    
    enum class GoldShopType {
        None,
        Lobby,
    };
    
    GoldShop(GoldShopType type = GoldShopType::None,BaseLayer* layer = NULL);
    ~GoldShop();
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
    void updateMainUI(); // 更新第一页热销
    
    void updateMagicNum();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    int startIDX;
    Tab _currentTab = Tab::None;
    int _coinNum;
    int _diamondNum;
    ListView* scrollViewBG;
    GoldShopType _type = GoldShopType::None;
    Node*Node_Gold;
    vector<int> _shangPinId;
    vector<std::shared_ptr<Product>> _productVec;
    BaseLayer* _layer;
};

#endif /* GoldShop_h */
