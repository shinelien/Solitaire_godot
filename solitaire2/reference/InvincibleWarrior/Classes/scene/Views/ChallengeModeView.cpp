//
//  ChallengeModeView.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/10/24.
//

#include <stdio.h>
#include "ChallengeModeView.h"
#include "FishManager.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
#include "FishGuideManager.h"
#include "GameBackground.h"
#include "PlayerManager.h"
#include "ScoreManager.h"

ChallengeModeView::ChallengeModeView(Type type)
:BaseLayer("2021Challenge.csb"),
_type(type)
{
    fishId = GETINTEGER(StringUtils::format("ChallengeFishId").c_str(),-1);
    _oldNum = GETINTEGER("Challenge_oldNum",0);
    _num = GETINTEGER("Challenge_num",0);
    isBar = false;
}
ChallengeModeView::~ChallengeModeView()
{
    
}

void ChallengeModeView::initUI()
{
    BaseLayer::initUI();
    loadingBar_percent = getNode<LoadingBar*>("LoadingBar_1");
    Node_fish = getNode("Node_fish");
    if(fishId == -1)
    {
        auto min = 20;
        auto max = 35;
        auto lv = PlayerManager::getInstance()->getLevel();
        auto fishIdx = FishManager::getInstance()->getMaxFishIdx(lv);
        auto rand = (float)random(min, max)/100.f;
        auto idx = std::round(fishIdx * rand);
        fishId = 16;
        SETINTEGER(StringUtils::format("ChallengeFishId").c_str(),fishId);
    }
    
    _skeletonNode = FISH_M->getFishSpine(fishId);
    Node_fish->addChild(_skeletonNode);
    string aniName = "Run";
    
    _skeletonNode->setAnimation(0, aniName, true);
    if(fishId == 14)
    {
        _skeletonNode->setPositionX(466.55f * 0.1f);
        _skeletonNode->setScale(0.85f);
    }
    auto num = DATA_M->getChallengeNum();
    if(num > 30) num = 30;
    _oldNum = _num;
    _num = num;
    SETINTEGER("Challenge_oldNum",_oldNum);
    SETINTEGER("Challenge_num",_num);
    
    percent1 = (float)_num / (float)challengeMax * 100.f;
    percent2 = (float)_oldNum / (float)challengeMax * 100.f;
    auto maxPercent = percent1 - percent2;
    //速度
    //0.3s完成 s
    percentDx = maxPercent/0.2f;//m/s
    percentDx *= 0.017;
    
    loadingBar_percent->setPercent(percent2);
    _isComplete = num >= challengeMax;
    
    playAni("Start0",false,[this](){
        isBar = true;
    });
    
    text_StarHour = getNode<TextBMFont*>("BitmapFontLabel_StarHour");
    text_StarNumMin = getNode<TextBMFont*>("BitmapFontLabel_StarNumMin");
    getNode<TextBMFont*>("BitmapFontLabel_StarNum")->setString(StringUtils::toString(num));
    getNode<TextBMFont*>("BitmapFontLabel_StarNumMax")->setString(StringUtils::toString(challengeMax));
    auto text = getNode<Text*>("Text_level_up_lv");
    text->setString(Lang("100399"));
    text->setFontSize(getTextSize());
    
    getNode<Text*>("Text_miaoshu")->setString(_isComplete?Lang("100401"):StringUtils::format(Lang("100400").c_str(),challengeMax));
    getNode<Text*>("Text_ok")->setString(Lang("100162"));
    getNode<Text*>("Text_get")->setString(Lang("100186"));
    
    auto timeCB = [this](float dt){
        if(DATA_M->getIsChallenge())
        {
            auto time = DATA_M->getNextFreeCoinTime5();
            
            auto num = DATA_M->getChallengeNum();
            
            if(time > 0)
            {
                int h = (int)(time / 3600);
                int m = (int)((int)time % 3600);
                m = (int)((int)m / 60);
                text_StarHour->setString(StringUtils::format("%02d", h));
                text_StarNumMin->setString(StringUtils::format("%02d", m));
            }
            else if(num < challengeMax)
            {//48小时过了并且没完成，下一轮了
               
            }
        }
    };
    schedule(timeCB,1, "view_challenge");
    timeCB(0);
    
    //经验
    schedule([this](float dt){
        if(isBar)
        {
            percent2 += percentDx/0.03f * dt;
            if(percent2 >= percent1)
            {
                percent2 = percent1;
                isBar = false;
                if(_isComplete)
                {//解锁啦
                    playAni("lock",false);
                }
                else
                {
                    //显示按钮
                    playAni("out0",false);
                }
            }
            loadingBar_percent->setPercent(percent2);
        }
        
    },0.03f, "scheduler_update_bar");
}
void ChallengeModeView::initData()
{
    BaseLayer::initData();
    setName("ChallengeModeView");
}
void ChallengeModeView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;

    auto btnName = btn->getName();
    
    if(btnName == "Button_get")
    {//
        auto fishNum = DATA_M->getFishNum();
        if(fishNum >= FISH_MAX_NUM)
        {
            FishGuideManager::getInstance()->fishMaxGuide();
        }
        else
        {
            auto fashTank = SCENE_M->getGameBackground();
            fashTank->addFish(fishId);

            //领奖励了
            SETINTEGER(StringUtils::format("ChallengeFishId").c_str(),-1);
//            DATA_M->setFreeCoinTime5(DATA_M->getContentSec());
            DATA_M->setIsChallenge(false);
            //累积清零
            DATA_M->addChallengeNum(true);
            //隐藏入口
            auto lobby = SCENE_M->getLobby();
            auto game = SCENE_M->getGameView();
            if(lobby)
            {
                lobby->updateBtnChallenge();
            }
            if(game)
            {
                game->updateBtnChallenge();
            }
            SCENE_M->removeLayer(this);
        }
        UIUtils::FIRFirestoreAddOP("challenge_limit", "get");
        UIUtils::FIRAnalyticsEvent("challenge_limit", {
                {"click", Value("get")},
        });
    }
    else if(btnName == "Button_ok"||btnName == "Button_close")
    {
        auto winNum = ScoreManager::getInstance()->getWinTotalCNT(true);
        auto num = ScoreManager::getInstance()->getWinTotalCNT();
        if(!GUIDE_M->isEnd(FishGuideManager::GuideType::Three)&&winNum == 1&&num == 4)
        {
            auto gameView = SCENE_M->getGameView();
            auto poi = gameView->getPauseWorldPoi();
            auto scale = gameView->getNode("FileNode_2020Menu")->getScale();
            GUIDE_M->startGuide(FishGuideManager::GuideType::Three,gameView,poi,scale);
        }
        SCENE_M->removeLayer(this);
        UIUtils::FIRFirestoreAddOP("challenge_limit", "close");
        UIUtils::FIRAnalyticsEvent("challenge_limit", {
                {"click", Value("close")},
        });
    }
}

void ChallengeModeView::onEnter()
{
    BaseLayer::onEnter();
}
void ChallengeModeView::onExit()
{
    BaseLayer::onExit();
}

void ChallengeModeView::fishMove()
{
    auto gameView = SCENE_M->getGameView();
    auto lobby = SCENE_M->getLobby();
    auto poi = Node_fish->getPosition();
    poi = Node_fish->getParent()->convertToWorldSpace(poi);
    if(_type == Type::Game)
    {
        gameView->unlockFishMove(fishId,poi,[this,gameView](){
            //刷新GameView
            gameView->updateFishNewTips();
            
        });
    }
    else if(_type == Type::Lobby)
    {
        lobby->unlockFishMove(fishId,poi,[this,lobby](){
            lobby->updateFishNewTips();
            
        });
    }
}

int ChallengeModeView::getTextSize()
{
    //需要判断全部语言
    auto languageCode = DATA_M->getAllDyyStr();
    
    if(languageCode == "fr")
    {
        return 65;
    }
    else if(languageCode == "de")
    {
        return 55;
    }
    else if(languageCode == "tr")
    {
        return 55;
    }
    else if(languageCode == "ru")
    {
        return 55;
    }
    
    return 70;
}
