
#include "DailyNotice.h"
#include "DailyView.h"
#include "SpriteManager.h"

void DailyNotice::initUI() {
    BaseLayer::initUI();
    doLayout();
    
    playAni("start",false);
    
    getNode<Text*>("Text_title")->setString(Lang("100155"));
    getNode<Text*>("Text_content")->setString(Lang("100161"));
    getNode("Button_go")->getChildByName<Text*>("Text_Name")->setString(Lang("100163"));
    getNode("Button_ok")->getChildByName<Text*>("Text_Name")->setString(Lang("100162"));
}

void DailyNotice::initData() {
    BaseLayer::initData();
    setName("DailyNotice");
}

void DailyNotice::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();

    if (btnName == "Button_close") {
        //SCENE_M->removeLayer(this);
        this->removeFromParent();
    }
    else if (btnName == "Button_ok") {
        //SCENE_M->removeLayer(this);
        this->removeFromParent();
    }
    else if (btnName == "Button_go") {
        SCENE_M->addDialog(DailyView::createLayerN(), true);
        //SCENE_M->removeLayer(this);
        this->removeFromParent();
    }
}

DailyNotice::DailyNotice()
:BaseLayer("notice.csb")
{
}

DailyNotice::~DailyNotice()
{
}
