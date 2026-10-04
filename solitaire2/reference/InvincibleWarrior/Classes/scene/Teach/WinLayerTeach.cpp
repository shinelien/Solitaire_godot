//
// Created by  on 2020/3/24.
//

#include "WinLayerTeach.h"
#include "TeachManager.h"
#include "GameViewHD.hpp"

void WinLayerTeach::initUI() {
    BaseLayer::initUI();
    
    vector<string> strArr = {"C","O","N","G","R","A","T","U","L","A","T","I","O","N","S","!"};
    //文本
    for(int i = 0;i < strArr.size();++i)
    {
        auto text = getNode<Text*>(StringUtils::format("Text_14_%d",i));
        text->setString(strArr.at(i));
    }
    
    
    playAni("Start");
    auto text_new = FIND_NODE(Text *,this,"text_new");
    text_new->setString(UIUtils::getStringByName("100063"));
    UIUtils::textAdaptiveSize(text_new,360);
    FIND_NODE(Text *,this,"Text_congratulations")->setString(UIUtils::getStringByName("100111"));
}

void WinLayerTeach::initData() {
    BaseLayer::initData();
    setName("WinLayerTeach");
}

void WinLayerTeach::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
    if (btnName == "btn_new") {
        TEACH_M->nextTeachStep();
        auto game = SCENE_M->getGameView();
        game->resetGame();
        game->playAni("in",false);
        game->menuMove(false);
        this->removeFromParent();
    }
}

WinLayerTeach::WinLayerTeach()
:BaseLayer("WinLayer_teach.csb")
{
}

WinLayerTeach::~WinLayerTeach() {

}
