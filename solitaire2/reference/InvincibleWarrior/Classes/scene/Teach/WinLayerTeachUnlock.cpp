//
// Created by  on 2020/3/28.
//

#include "WinLayerTeachUnlock.h"
#include "TeachManager.h"

void WinLayerTeachUnlock::initUI() {
    BaseLayer::initUI();
    doLayout();
    auto btn = dynamic_cast<Button*>(UIUtils::seekNodeByName(this, "btn_pause_continue"));
    btn->addClickEventListener([this](Ref*){
        if (_cb) _cb();
        TEACH_M->nextTeachStep();
        this->removeFromParent();
    });
    auto txt_unlocktips = dynamic_cast<Text*>(UIUtils::seekNodeByName(this, "Text_unlockTips"));
    txt_unlocktips->setString(Lang("100250"));
    auto txt_unlockContent = dynamic_cast<Text*>(UIUtils::seekNodeByName(this, "Text_unlockContent"));
    auto isTeaching1 = TEACH_M->isTeaching("win_times1");
    txt_unlockContent->setString(Lang(isTeaching1?"100251":"100252"));

    UIUtils::seekNodeByName(this, "no_1")->setVisible(isTeaching1);
    UIUtils::seekNodeByName(this, "no_2")->setVisible(!isTeaching1);
    getNode<Text*>("Text_continue")->setString(Lang("100113"));
    
    _actionManager->setFrameEventCallFunc([this](Frame* frame){
        auto event = dynamic_cast<EventFrame*>(frame);
        auto msg = event->getEvent();
        if(msg == "event_btn_show") {
            TEACH_M->nextTeachStep(this);
        }
    });
    playAni("Start1", false);
}

void WinLayerTeachUnlock::initData() {
    BaseLayer::initData();
    setName("WinLayerTeachUnlock");
}

void WinLayerTeachUnlock::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
}

WinLayerTeachUnlock::WinLayerTeachUnlock(std::function<void()> cb)
:BaseLayer("WinLayer_Unlock.csb")
,_cb(cb)
{
}

WinLayerTeachUnlock::~WinLayerTeachUnlock() {

}
