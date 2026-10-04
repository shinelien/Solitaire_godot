
#include "ShopItemHD.h"

void ShopItemHD::initUI() {
    BaseLayer::initUI();
}

void ShopItemHD::initData() {
    BaseLayer::initData();
    setName("ShopItemHD");
}

void ShopItemHD::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
}

ShopItemHD::ShopItemHD()
:BaseLayer("ShopItemHD.csb")
{
}

ShopItemHD::~ShopItemHD() {

}
