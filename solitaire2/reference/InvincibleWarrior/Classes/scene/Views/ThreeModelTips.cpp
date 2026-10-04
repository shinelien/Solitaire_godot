//
//  ThreeModelTips.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/22.
//

#include <stdio.h>
#include "ThreeModelTips.h"
#include "GameViewHD.hpp"

ThreeModelTips::ThreeModelTips(BaseLayer* layer)
:BaseLayer("2021ThreeModel.csb")
{
    _layer = layer;
}

ThreeModelTips::~ThreeModelTips()
{
    
}

void ThreeModelTips::updateUI()
{
    
    
}

void ThreeModelTips::initUI()
{
    BaseLayer::initUI();
    doLayout();
    playAni("start", false);
    getNode<Text*>("Text_no")->setString(Lang("100344"));
    auto Text_yes = getNode<Text*>("Text_yes");
    Text_yes->setString(Lang("100343"));
    
    UIUtils::textAdaptiveSize(Text_yes, 230);
    getNode<Text*>("Text_title")->setString(Lang("100346"));
}

void ThreeModelTips::initData()
{
    BaseLayer::initData();
    
}

void ThreeModelTips::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;

    auto btnName = btn->getName();
    if(btnName == "Button_yes")
    {//开始新的对局，

        auto _gameView = SCENE_M->getGameView();
        SOUND_M->playBtnClickAudio();
        _gameView->gamePause(false);
        _gameView->restartGame(false,DataManager::GameType::Huo);
        
        if(_layer)
        {
            SCENE_M->removeLayer(_layer);
        }
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_no")
    {//继续游戏
        if(_layer)
        {
            _layer->setVisible(true);
            _layer->playAni("Start", false);
        }
        SOUND_M->playBtnClickAudio();
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_close")
    {//继续游戏
        if(_layer)
        {
            _layer->setVisible(true);
            _layer->playAni("Start", false);
        }
        SOUND_M->playBtnClickAudio();
        SCENE_M->removeLayer(this);
    }
}
