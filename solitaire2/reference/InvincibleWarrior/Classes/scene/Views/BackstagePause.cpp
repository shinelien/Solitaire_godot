
//
//  BackstagePause.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/7.
//

#include <stdio.h>
#include "BackstagePause.h"
#include "GameViewHD.hpp"
BackstagePause::BackstagePause(GameViewHD *gameView,bool isPlay)
:BaseLayer("UI_Pause.csb")
{
    
}
BackstagePause::~BackstagePause()
{
    
}
    
void BackstagePause::setIsPlay(bool isPlay)
{
    isPlay = isPlay;
}

void BackstagePause::initUI()
{
    BaseLayer::initUI();
    doLayout();
    auto game = SCENE_M->getGameView();
    isPause = game->getGamePause();
    btn_music_on = getNode<Button*>("btn_MusicTips");
    btn_effTips = getNode<Button*>("btn_effTips");
    setEffMusic(DATA_M->getIsEffect());
    setMusic(DATA_M->getIsMusic());
    
    
    
    if(!isPause)
    {//在游戏中。暂停游戏
        game->gamePause(true);
    }
    
    
    getNode<Text*>("text_music")->setString(Lang("100240"));
    getNode<Text*>("text_effTips")->setString(Lang("100048"));
    getNode<Text*>("Text_pauseTitle1")->setString(Lang("100072"));
    auto Text_continue = getNode<Text*>("Text_continue");
    Text_continue->setString(Lang("100113"));
    UIUtils::textAdaptiveSize(Text_continue, 300);
    
}

void BackstagePause::initData()
{
    BaseLayer::initData();
    setName("BackstagePause");
}
void BackstagePause::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto btnName = btn->getName();
    if(btnName == "btn_pause_continue")
    {
        if(!isPause)
        {
            SCENE_M->getGameView()->gamePause(isPause);
        }
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_eff"||btnName == "btn_effTips")
    {//yinn xiao音效  btn_effTips
        setEffMusic(!DATA_M->getIsEffect());
    }
    else if ("Button_music" == btnName||btnName == "btn_MusicTips")
    {
        //音乐开关
        setMusic(!DATA_M->getIsMusic());
    }
}

void BackstagePause::onEnter()
{
    BaseLayer::onEnter();
}

void BackstagePause::onExit()
{
    BaseLayer::onExit();
}

void BackstagePause::setMusic(bool isMusic)
{
    DATA_M->setIsMusic(isMusic);
    if (isMusic)
    {
        btn_music_on->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_music_on->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "animation0", false);
    }
    else
    {
        btn_music_on->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_music_on->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "Start", false);
    }
}

void BackstagePause::setEffMusic(bool isMusic)
{
    DATA_M->setIsEffect(isMusic);
    if (isMusic)
    {
        btn_effTips->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_effTips->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "animation0", false);
    }
    else
    {
        btn_effTips->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_effTips->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "Start", false);
    }
}
