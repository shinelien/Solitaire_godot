
#include "PrivacyViewHD.h"
#include "SceneManager.h"

void PrivacyViewHD::initUI() {
    BaseLayer::initUI();

    getNode<Text*>("Text_title")->setString(Lang("100108"));
    getNode<Text*>("text_rule")->setString(Lang("100109"));
}

void PrivacyViewHD::initData() {
    BaseLayer::initData();
    setName("PrivacyViewHD");
}

void PrivacyViewHD::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
    if (btnName == "Button_close") {
        this->removeFromParent();
    }
}

PrivacyViewHD::PrivacyViewHD()
:BaseLayer("privacy.csb")
{
}

PrivacyViewHD::~PrivacyViewHD() {

}
