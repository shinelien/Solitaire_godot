//
//  ShuffleView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/1.
//

#include <stdio.h>
#include "ShuffleView.h"
#include "DataManager.h"
#include "GameViewHD.hpp"
#include "RewardManager.h"
#include "MainLobby.h"
#include "BagView.h"
#include "EventObserver.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#endif
ShuffleView::~ShuffleView()
{
    
}
ShuffleView::ShuffleView(ShuffleView::Type type)
:BaseLayer("AD_magic.csb")
,_type(type)
{
    auto day = GETINTEGER("MagicYDay",0);
    auto yDay = DATA_M->getYDay();
    if(day != yDay)
    {//不同天数
        _getNum = 0;
        SETINTEGER("MagicGetNum",0);
        SETINTEGER("MagicYDay",yDay);
        _xianZhiNum = 0;
        SETINTEGER("xianZhiNum",0);
    }
    else
    {
        _getNum  = GETINTEGER("MagicGetNum",0);
        _xianZhiNum = GETINTEGER("xianZhiNum",0);
    }
    
}

void ShuffleView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    auto is = DATA_M->getHaveVideo();
    auto isChaPing = DATA_M->getHaveInterstitials();
    auto btn_guankan = getNode<Button*>("btn_guankan");
    auto btn_guankan0 = getNode<Button*>("btn_guankan0");
    
//    if(_xianZhiNum == 50)
//    {
//        getNode<Button*>("btn_guankan")->setEnabled(false);
//    }
    
    auto coinNum = DATA_M->getCoinNum();
    //auto diamond = DATA_M->getDiamond();
    _goldNum = 1000 + _getNum*500;
    if(false)//diamond < MAGIC_PRICE)
    {
        getNode<Button*>("btn_1000gold")->setEnabled(false);
        getNode<Button*>("btn_1000gold")->setVisible(false);
        getNode<Button*>("btn_guankan0")->setEnabled(false);
        getNode<Button*>("btn_guankan0")->setVisible(false);
        getNode<Button*>("btn_guankan")->setVisible(true);
    }
    else
    {
        getNode<Button*>("btn_1000gold")->setVisible(true);
        getNode<Button*>("btn_guankan")->setVisible(false);
        getNode<Button*>("btn_1000gold")->setEnabled(coinNum>=MAGIC_PRICE);
        getNode<Button*>("btn_guankan0")->setEnabled(true);
        getNode<Button*>("btn_guankan0")->setVisible(true);
    }
    
    auto text_guankan = getNode<Text*>("text_guankan");
    auto text_guankan0 = getNode<Text*>("text_guankan0");
    
    //区分视频与插屏
    if(true||ShuffleView::Type::Bag == _type)
    {//这里是视频
        btn_guankan->setEnabled(is);
        btn_guankan0->setEnabled(is);
    }
    else
    {//是插屏
        //ui_AD_0_20
        FIND_NODE(Node*, btn_guankan, "ui_AD_0_20")->setVisible(false);
        FIND_NODE(Node*, btn_guankan0, "ui_AD_0_20")->setVisible(false);
        auto width = btn_guankan0->getContentSize().width;
        text_guankan0->setPositionX(width/2);
        btn_guankan->setEnabled(isChaPing);
        btn_guankan0->setEnabled(isChaPing);
    }
    
    
    
    
    _actionManager->play("loop", true);
    getNode<Text*>("x2_0")->setString(StringUtils::format("x%d",1));
    auto num = RewardManager::getInstance()->getCNT(RewardManager::RewardType::Magic);
    getNode<Text*>("Text_xianZhi")->setString(StringUtils::format("%d/%d",num,50));
    getNode<Text*>("Text_xianZhi")->setVisible(true);
    getNode<Button*>("btn_1000gold")->setEnabled(num < 50&&coinNum>=MAGIC_PRICE);
    getNode<Button*>("btn_guankan")->setEnabled(num < 50&&is);
    getNode<Button*>("btn_guankan0")->setEnabled(num < 50&&is);
    getNode<Text*>("text_1000")->setString(StringUtils::toString(MAGIC_PRICE));
    
    //Text_xianZhi
    getNode<Text*>("Text_title")->setString(Lang("100177"));
    getNode<Text*>("Text_miaoshu")->setString(Lang("100178"));

    text_guankan->setString(Lang("100279"));
    UIUtils::textAdaptiveSize(text_guankan,270);
    text_guankan0->setString(Lang("100279"));
    UIUtils::textAdaptiveSize(text_guankan0,180);
    
}
void ShuffleView::initData()
{
    BaseLayer::initData();
    setName("ShuffleView");

    EVENT_M->addListener("event_game_bag_Shuffle", [this](ValueMap valueMap, void *obj){
        //背包
        addMagic();
        auto bagView = SCENE_M->getBagView();
        if(bagView)
        {
            bagView->getNode("Panel_top_0")->setVisible(true);
            bagView->playAni("Start0",false);
        }
    },this);
    
    EVENT_M->addListener("event_game_game_Shuffle", [this](ValueMap valueMap, void *obj){
        //游戏内
        addMagic();
    },this);
    
    EVENT_M->addListener("msg_game_showwin",[this](ValueMap valueMap, void *obj){
        if (_InterstitialCB) {
            _InterstitialCB();
            _InterstitialCB = nullptr;
        }
    },this);

}
void ShuffleView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto name = btn->getName();
    if(name == "btn_close"||"Panel_close" == name)
    {//关闭
        if(_cb)
        {
            _cb();
        }
        if(ShuffleView::Type::Bag == _type)
        {
            auto bagView = SCENE_M->getBagView();
            if(bagView)
            {
                bagView->getNode("Panel_top_0")->setVisible(true);
                bagView->playAni("Start0",false);
            }
        }
        auto game = SCENE_M->getGameView();
        //关闭窗口开始累计计时
        game->setIsOpenTipsTime(true);
        game->gamePause(false);//解除暂停
        SCENE_M->removeLayer(this);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("magic")},
            {"value", Value("no")},
            {"v1", Value((int)_type)},
            {"v2", Value(DATA_M->getHaveVideo())}
        });
    }
    else if(name == "btn_guankan"||name == "btn_guankan0")
    {//领取
        if(Type::Bag == _type)
        {//背包视频
            DATA_M->playVideoAds(5);
        }
        else
        {//游戏内视频
            DATA_M->playVideoAds(17);
        }
        
        btn->scheduleOnce([btn](float t){
            btn->setEnabled(DATA_M->getHaveVideo());
        }, 0.0001, "delay_key_btn");
     
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("magic")},
            {"value", Value("ad")},
            {"v1", Value((int)_type)}
        });
    }
    else if(name == "btn_1000gold")
    {
        auto coin = DATA_M->getCoinNum();
        if(coin >= MAGIC_PRICE)
        {
            if(ShuffleView::Type::Bag == _type)
            {
                auto bagView = SCENE_M->getBagView();
                if(bagView)
                {
                    bagView->getNode("Panel_top_0")->setVisible(true);
                    bagView->playAni("Start0",false);
                }
            }
            SETINTEGER("MagicGetNum",_getNum);
            DATA_M->setCoinNum(-MAGIC_PRICE,false, 202);//
            ValueMap valueMap{
                {"isTime",Value{false}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            //SCENE_M->getLobby()->updateDiamond();
            
            if(ShuffleView::Type::Bag == _type)
            {
                RewardManager::getInstance()->getReward(RewardManager::RewardType::Magic,1,true);
                SCENE_M->getBagView()->updateMagicNum();
            }
            else
            {
                RewardManager::getInstance()->getReward(RewardManager::RewardType::Magic,1,true);
                auto game = SCENE_M->getGameView();
                game->playGetMagic();
                game->updateDiamond();
                //关闭窗口开始累计计时
                game->setIsOpenTipsTime(true);
                game->gamePause(false);//解除暂停
            }
            SCENE_M->removeLayer(this);
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("magic")},
                {"value", Value("gold")},
            });
        }
    }
}

void ShuffleView::xianZhi()
{
    _xianZhiNum++;
    if(_xianZhiNum > 50)
    {
        _xianZhiNum = 50;
    }
    getNode<Text*>("Text_xianZhi")->setString(StringUtils::format("%d/%d",_xianZhiNum,50));
    SETINTEGER("xianZhiNum",_xianZhiNum);
}


void ShuffleView::onEnter()
{
    BaseLayer::onEnter();
    UIUtils::FIRAnalyticsEventWithPrefix("MagicView");
}
void ShuffleView::onExit()
{
    BaseLayer::onExit();
//    EVENT_M->removeListener("event_game_level_Shuffle_1",this);
    EVENT_M->removeListener("event_game_bag_Shuffle",this);
    EVENT_M->removeListener("event_game_game_Shuffle",this);
    EVENT_M->removeListener("msg_game_showwin",this);
}

void ShuffleView::addMagic()
{
    //增加道具次数
    RewardManager::getInstance()->getReward(RewardManager::RewardType::Magic,1,true);
    if(ShuffleView::Type::Bag == _type)
    {
        //RewardManager::getInstance()->getReward(RewardManager::RewardType::Magic,1,true);
        SCENE_M->getBagView()->updateMagicNum();
    }
    else
    {
        auto game = SCENE_M->getGameView();
        //播放获取道具动画
        game->playGetMagic(true);
        //关闭窗口开始累计计时
        game->setIsOpenTipsTime(true);
        game->gamePause(false);//解除暂停
    }
    
    
    scheduleOnce([this](float dt){
        SCENE_M->removeLayer(this);
    }, 0.02,"delayremove");
    this->setVisible(false);
}
