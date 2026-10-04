
#include "Dialog.h"

void Dialog::initUI() {
    BaseLayer::initUI();
    doLayout();
}

void Dialog::initData() {
    BaseLayer::initData();
    setName("Dialog");
}

void Dialog::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
    if (btnName == "Button_yes") {
        if (_cbOk) _cbOk();
    }
    else if (btnName == "Button_no") {
        if (_cbNo) _cbNo();
    }
    removeFromParent();
}

Dialog::~Dialog() {

}

void Dialog::setText(const std::string &title, const std::string &content, const std::string &yes, const std::string &no) {
    if(!no.empty())
        getNode("Button_no")->getChildByName<Text*>("Text_Name")->setString(no);
    if(!yes.empty())
        getNode("Button_yes")->getChildByName<Text*>("Text_Name")->setString(yes);
    getNode<Text*>("Text_title")->setString(title);
    getNode<Text*>("Text_content")->setString(content);
}

Dialog::Dialog(Dialog::Type type, CBFunc ok, CBFunc no):BaseLayer("Dialog.csb"),
_type(type),
_cbOk(ok),
_cbNo(no)
{

}
