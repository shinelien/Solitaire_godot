//
// Created by Cyutao on 2018/10/13.
//

#include "GamePauseHD.h"
#include "GameViewHD.hpp"
#include "SpriteManager.h"
#include "MainLobby.h"
#include "WinHD.h"
#include "ScoreManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#endif
#include "TeachManager.h"
#include "DailyMoreView.h"
#include "FishGuideManager.h"
void GamePauseHD::initUI() {
    BaseLayer::initUI();
    doLayout();
    
//    if(DATA_M->isDailyMode())
//    {
//        getNode("Button_DailyBack")->setVisible(true);
//        getNode("Button_NewGame")->setVisible(false);
//    }
//    else if(DATA_M->isLevelMode())
//    {
//        getNode("Button_DailyBack")->setVisible(false);
//        getNode("Button_NewGame")->setVisible(false);
//    }
//    else
    {
        getNode("Button_DailyBack")->setVisible(false);
        getNode("Button_NewGame")->setVisible(true);
    }
    
    auto num = ScoreManager::getInstance()->getWinTotalCNT(true);
    getNode("Button_Lobby")->setVisible(num >= 1);
    getNode("Button_game_daily")->setVisible(num >= 3);
    
    pause_fish_tips = getNode("pause_fish_tips");
    auto isFishNew = DATA_M->getIsFishNuw();
    auto isFashTank = DATA_M->getIsFashTankNuw();
    pause_fish_tips->setVisible(isFishNew||isFashTank);
    
    auto node = _rootNode;
    //INIT_BTN(node,"Button_Lobby", CC_CALLBACK_1(GamePauseHD::dealButtonClick, this));
    isTouch = false;
    //getNode<Text*>("Text_continue")->setString(Lang("100113"));100206
    getNode<Text*>("Text_pauseTitle1")->setString(Lang("100072"));
    getNode<Text*>("Text_NewGame")->setString(Lang("100291"));
    getNode<Text*>("Text_Again")->setString(Lang("100128"));
    getNode<Text*>("Text_Lobby")->setString(Lang("100205"));
    getNode<Text*>("Text_DailyBack")->setString(Lang("100291"));
    getNode<Text*>("Text_game_daily")->setString(Lang("100204"));
    _gameView->gamePause(true);
    playAni("Start0", false);
    _actionManager->setFrameEventCallFunc([this](Frame*frame){
        auto event = dynamic_cast<EventFrame*>(frame);
        auto name = event->getEvent();
        if(name == "game_pause_0")
        {
            if(!GUIDE_M->isEnd(FishGuideManager::GuideType::LobbyOne)&&GUIDE_M->isEnd(FishGuideManager::GuideType::Three))
            {//搭配Three使用
                auto btn = getNode("Button_Lobby");
                
                auto poi = btn->getPosition();
                auto parent = btn->getParent();
                poi = parent->convertToWorldSpace(poi);
                auto scale = parent->getScale();
                GUIDE_M->startGuide(FishGuideManager::GuideType::LobbyOne,this,poi,scale);
            }
            else if(!GUIDE_M->isEnd(FishGuideManager::GuideType::gotoLobby,0)&&GUIDE_M->isEnd(FishGuideManager::GuideType::unlockFashTank,0))
            {//搭配Three使用
                auto btn = getNode("Button_Lobby");
                
                auto poi = btn->getPosition();
                auto parent = btn->getParent();
                poi = parent->convertToWorldSpace(poi);
                auto scale = parent->getScale();
                GUIDE_M->startGuide(FishGuideManager::GuideType::gotoLobby,this,poi,scale,0);
            }
             isTouch = true;//动画结束才能相应按钮
        }
        else if(name == "game_pause_1")
        {
             SCENE_M->removeLayer(this);
        }
    });
    
    _actionManager->setLastFrameCallFunc([this](){
       
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        DATA_M->showNativeAds(0);
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        DATA_M->showNativeAds(4);
//#endif
    });
    
    auto unlock = TEACH_M->isDailyLevelUnlock();
    getNode<Button*>("Button_Lobby")->setEnabled(unlock);
}

void GamePauseHD::initData() {
    BaseLayer::initData();
    setName("GamePauseHD");
}

void GamePauseHD::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr||!isTouch) {
        return;
    }
    auto btnName = btn->getName();
    if (btnName == "Panel_close"||btnName == "Panel_close0"||btnName == "Button_close") {
        isTouch = false;
        playAni("Start1",false);
        SOUND_M->playBtnClickAudio();
        
        _gameView->gamePause(false);
        _gameView->menuPausePlayAni("Start1",false);
        _gameView->setButtonPauseEnabled(true);
        // puim acg12.us
    }
    else if(btnName == "Button_NewGame"||btnName == "Button_DailyBack") {
        isTouch = false;
        playAni("Start1",false);
        SOUND_M->playBtnClickAudio();
        
        _gameView->gamePause(false);
        
        _gameView->restartGame(false,DataManager::GameType::Huo);
        _gameView->hideLunPan();
        _gameView->menuPausePlayAni("Start1",false);
        _gameView->setButtonPauseEnabled(true);
        //SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_Again") {
        isTouch = false;
        playAni("Start1",false);
        SOUND_M->playBtnClickAudio();
        
        _gameView->gamePause(false);
        
        if (DATA_M->isLevelMode()&& _gameView->getLevelDate())
        _gameView->levelCompleteEnd(false, true);
        _gameView->restartGame(true);
        _gameView->hideLunPan();
        _gameView->menuPausePlayAni("Start1",false);
        _gameView->setButtonPauseEnabled(true);
        //SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_Lobby") {
        
        auto lobby = SCENE_M->getLobby();
        if(lobby)
        {
            //暂停音效
            //SOUND_M->pauseDTEffect();
            _gameView->hideLunPan();
            _gameView->showLobby();
            _gameView->gamePause(true);
            _gameView->setIsRefushGift(false);//返回大厅禁止刷新奖励
        }
        _gameView->menuPausePlayAni("Start1",false);
        _gameView->setButtonPauseEnabled(true);
        SOUND_M->playBtnClickAudio();
        if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::LobbyOne)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::LobbyOne))
        {
            GUIDE_M->endGuide();
        }
        else if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::gotoLobby)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::gotoLobby,0))
        {
            GUIDE_M->endGuide(FishGuideManager::GuideType::None,NULL,0);
        }
        SCENE_M->removeLayer(this);
    }
    else if(false)
    {//返回大厅并移动至每日挑战

        if(DATA_M->isDailyMode())
        {//弹出难度选择
            auto lobby = SCENE_M->getLobby();
            if(lobby)
            {
                lobby->showDailyStart();
            }
        }
        else
        {
            auto lobby = SCENE_M->getLobby();
            if(lobby)
            {
                //暂停音效
                //SOUND_M->pauseDTEffect();
                _gameView->hideLunPan();
                _gameView->showLobby();
                _gameView->gamePause(true);
            }
            SOUND_M->playBtnClickAudio();
        }
        _gameView->setButtonPauseEnabled(true);
        
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_game_daily")
    {//打开每日挑战
        
        auto currentDate = DailyManager::getInstance()->getCurrentDate();
        auto _today = DailyManager::getInstance()->today();
        auto _current = currentDate==NoneDate?_today:currentDate;
        
        auto Panel_more = DailyMoreView::createLayerN(_current);
        SCENE_M->addDialog(Panel_more,false,2);
        //SCENE_M->addDialog(DailyView::createLayerN());
        _gameView->menuPausePlayAni("Start1",false);
        _gameView->setButtonPauseEnabled(true);
        SCENE_M->removeLayer(this);
    }
}

void GamePauseHD::setIsPlay(bool isPlay)
{
    _isPlay = isPlay;
}

GamePauseHD::GamePauseHD(GameViewHD *gameView,bool isPlay)
:BaseLayer("2020Pause.csb")
,_gameView(gameView)
,_isPlay(isPlay)
{
}
//16.5  11.5 2 24 11.5 27 5.6 24 5.5 20 24.5 143 100 99.9 39 98 49.95 20
GamePauseHD::~GamePauseHD() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    DATA_M->hideNativeAds(0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    DATA_M->hideNativeAds(4);
#endif
}

void GamePauseHD::testWinAction() {
    auto pos = getNode<Widget*>("panel_pause")->getTouchBeganPosition();
    auto winSize = Director::getInstance()->getWinSize();
    auto cardSprite = Sprite::createWithSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(13, 0));
    cardSprite->setName("CardSprite");
    
    auto curPos = Vec2(0, winSize.height*3/4);
    cardSprite->setPosition(curPos);
    _renderTex->addChild(cardSprite);
    
    auto dir = 1;
    auto offsetX = dir*winSize.width/6;
    vector<Vec2> destOffset {Vec2(offsetX, winSize.height/4), Vec2(offsetX-20, winSize.height*3/4), Vec2(offsetX, winSize.height/2), Vec2(offsetX, winSize.height/4)};
    Vector<FiniteTimeAction*> actions;
    auto totalCNT = 8;
    for (auto i=0; i<totalCNT; i++) {
        auto destPos = Vec2(curPos.x+offsetX, 0);
        float offsetY = ( i==0 ? (1.0/totalCNT) : ((1.0*totalCNT-i)/totalCNT) )*winSize.height;
        auto distance = (curPos.y+2*offsetY);
        actions.pushBack(BezierTo::create(distance/2500, {destPos, Vec2(curPos.x, curPos.y+offsetY), Vec2(destPos.x, curPos.y+offsetY)}));
        curPos = destPos;
    }
    actions.pushBack(RemoveSelf::create());
    cardSprite->runAction(Sequence::create(actions));

//    cardSprite->runAction(MoveTo::create(1, Vec2(winSize.width, 0)));
}

void GamePauseHD::onEnter() {
    BaseLayer::onEnter();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    if (AdsManager::nativeInit)
//        AdsManager::setBannerVisible(false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    DATA_M->showNativeAds(4);
#endif
}

void GamePauseHD::onExit() {
    BaseLayer::onExit();
    
    //_gameView->menuPausePlayAni("Start1",false);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    AdsManager::setBannerVisible(true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    DATA_M->hideNativeAds(4);
#endif
}
