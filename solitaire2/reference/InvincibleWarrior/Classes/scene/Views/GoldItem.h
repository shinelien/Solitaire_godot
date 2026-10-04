//
//  GoldItem.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/25.
//

#ifndef GoldItem_h
#define GoldItem_h
#include "BaseLayer.h"
#include "Factory.hpp"

class Product;
class GoldShop;
class GoldItem : public BaseLayer, public Factory<GoldItem>
{
public:
    GoldItem(GoldShop* goldShop);
    ~GoldItem();
    void updateUI();
    static GoldItem * createBagNode(int idx,GoldShop* goldShop);
    
    void setShopNodeState(int idx);
    void selected(bool flag);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    GoldShop* _goldShop;
    int _idx;
    std::shared_ptr<Product> _product;
    
    Node* Image_Gold;
    Sprite* Sprite_HOT;
    Vector<Node*> _nodeVec;
};


#endif /* GoldItem_h */
