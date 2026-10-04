//
//  MissionView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/11.
//

#include <stdio.h>
#include "MissionView.h"
#include "LevelViewHD.h"
#include "LevelManager.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"

MissionView::MissionView(MainLobby* lobby)
:BaseLayer("2020HomeView_Mission.csb")
,_lobby(lobby)
{
    
}
MissionView::~MissionView()
{
    
}

void MissionView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    _gameView = SCENE_M->getGameView();
    
    Text_level = getNode<TextBMFont*>("Text_level");
    Text_Mission = getNode<Text*>("Text_Mission");
    Text_start = getNode<Text*>("Text_start");
    Sprite_level_icon = getNode<Sprite*>("Sprite_level_icon");
    
    
    
    
    updateUI();
    updateDYY();
}

void MissionView::initData()
{
    BaseLayer::initData();
    setName("MissionView");
}
void MissionView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    if(dynamic_cast<Button*>(btn))
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
    }
    auto btnName = btn->getName();
    if(btnName == "Button_start")
    {//开始关卡
        startLevel();
    }
    else if(btnName == "Button_level")
    {//选择关卡
        SCENE_M->addDialog(LevelViewHD::createLayerN(false));
    }
}

void MissionView::startLevel()
{
    SCENE_M->getRewardNode()->setVisible(false);
    //恢复音效
    //SOUND_M->resumeDTEffect();
    _gameView->playMusic();
    _gameView->playEffect();
    _lobby->setVisible(false);
    _lobby->updateStar();//预防星星在场景中显示
    _gameView->setVisible(true);
    _gameView->startLevelRank(_LevelData);
    UIUtils::FIRAnalyticsEventWithPrefix("gameStartLevel");
    _gameView->sendStartGameEvent(DataManager::GameType::Level);
}

void MissionView::onEnter()
{
    BaseLayer::onEnter();
    playAni("In", false);
    updateUI();
    UIUtils::FIRAnalyticsEventWithPrefix("MissionView");
}

void MissionView::onExit()
{
    BaseLayer::onExit();
    playAni("Out", false);
}

void MissionView::updateUI()
{
    _sub = LevelManager::getInstance()->getCurrentSub();
    _group = LevelManager::getInstance()->getCurrentGroup();
    
    auto unLock = LevelManager::getInstance()->isLevelUnLock(_group,_sub);
    auto completed = LevelManager::getInstance()->isLevelComplete(_group,_sub);
    if(completed)
    {//已经完成了
        _sub += 1;
    }
    
    //防止越界
    if(_group == 5&&_sub == 70)
    {//玩家玩到300关时 固定在300关
        _group = 5;
        _sub = 69;
    }
    else if(_group > 5)
    {//有的玩家在更新前就通关了,在此处添加限制。限制到300关 _group只有<=5才不会越界
        _group = 5;
        _sub = 69;
    }
    
    auto groupData = LevelManager::getInstance()->getLevelData(_group);
    const auto &array = (*groupData)["data"].GetArray();
    int totalCNT = array.Size();
    if (_sub < (totalCNT)) {
        _LevelData = LevelManager::getInstance()->getLevelData(_group, _sub);
    }
    else if (LevelManager::getInstance()->hasLevelGroup(_group+1)) {
       _LevelData = LevelManager::getInstance()->getLevelData(_group+1, 0);
    }
    if (_LevelData != nullptr) {
        Text_level->setString(StringUtils::toString((*_LevelData)["subShow"].GetInt()));
        Sprite_level_icon->setSpriteFrame((*_LevelData)["icon"].GetString());
        Text_Mission->setString(StringUtils::format(Lang("100263").c_str(),(*_LevelData)["group"].GetInt(),(*_LevelData)["subShow"].GetInt()));
    }
}


void MissionView::updateDYY()
{
    getNode<Text*>("Text_Mission")->setString(Lang("100263"));
    getNode<Text*>("Text_1")->setString(Lang("100262"));
    getNode<Text*>("Text_start")->setString(Lang("100150"));
   if(_LevelData)
   {
       Text_Mission->setString(StringUtils::format(Lang("100263").c_str(),(*_LevelData)["group"].GetInt(),(*_LevelData)["subShow"].GetInt()));
   }
}
