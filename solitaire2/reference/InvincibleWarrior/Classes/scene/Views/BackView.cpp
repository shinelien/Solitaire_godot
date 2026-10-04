//
// Created by  on 2019-06-03.
//

#include "BackView.h"
#include "MainLobby.h"
#include "SoundManager.h"
#include "SceneManager.h"

void BackView::initUI() {
    BaseLayer::initUI();
    playAni("Start", false);

    getNode<Text*>("Text_title")->setString(_title);
    getNode<Text*>("Text_yes")->setString(_yes);
    getNode<Text*>("Text_no")->setString(_no);
}

void BackView::initData() {
    BaseLayer::initData();
    setName("BackView");
}

void BackView::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    
    if(dynamic_cast<Button*>(btn))
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
    }
    
    auto btnName = btn->getName();
    if (btnName == "Button_yes") {
        if (_yesCB != nullptr) {
            _yesCB();
        }
        removeFromParent();
    }
    else if (btnName == "Button_no") {
        if (_noCB != nullptr) {
            _noCB();
        }
        removeFromParent();
    }
    else if(btnName == "Button_close"||btnName == "Panel_out")
    {//
        auto lobby = SCENE_M->getLobby();
        if(lobby)
        {
            lobby->resetHome();
        }
        
        SCENE_M->removeLayer(this);
    }
}

BackView::BackView(BackCB yesCB, BackCB noCB, const std::string title, const std::string yes, const std::string no)
:BaseLayer("UI_Back.csb"),
_yesCB(yesCB),
_noCB(noCB),
_title(title),
_yes(yes),
_no(no)
{
}

BackView::~BackView() {

}
