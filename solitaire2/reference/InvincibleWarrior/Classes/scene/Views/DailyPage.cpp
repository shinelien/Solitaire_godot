//
// Created by  on 2020/3/16.
//

#include "DailyPage.h"

void DailyPage::initUI() {
    BaseLayer::initUIByRemove(true);
    
    for (int i=0; i<4; ++i) {
        auto root = getNode(StringUtils::format("Image_root_%d", i));
        root->getChildByName<TextBMFont*>("Text_day_0")->setString(StringUtils::toString(_idx*4+i));
    }
}

void DailyPage::initData() {
    BaseLayer::initData();
    setName("DailyPage");
}

void DailyPage::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
}

DailyPage::DailyPage(int idx)
:BaseLayer("DailyPage.csb"),
_idx(idx)
{
}

DailyPage::~DailyPage() {
    
}
