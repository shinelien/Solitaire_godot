
#ifndef SpacecatSolitaireGame_ShopItemHD_H
#define SpacecatSolitaireGame_ShopItemHD_H

#include "BaseLayer.h"
#include "Factory.hpp"

class ShopItemHD : public BaseLayer, public Factory<ShopItemHD> {
public:
    virtual ~ShopItemHD();
    ShopItemHD();

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;


};

#endif //SpacecatSolitaireGame_ShopItemHD_H
