//
//  MultipleRewardView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/26.
//

#include <stdio.h>
#include "MultipleRewardView.h"
#include "MainLobby.h"
#include "GameViewHD.hpp"
#include "EventObserver.h"
#include "TeachManager.h"
#include "ScoreManager.h"

MultipleRewardView::MultipleRewardView(std::function<void()> cb,std::function<void()> cb2, bool isTeach,int coin)
:BaseLayer("2020x7gift.csb")
,_cb(cb)
,_cb2(cb2)
,_isTeach(isTeach)
,_coinNum(coin)
{
    
}

MultipleRewardView::~MultipleRewardView()
{
    
}

void MultipleRewardView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    auto is = DATA_M->getHaveVideo();
    //判定经典模式前十局多倍奖励 是否启用视频
    auto num = ScoreManager::getInstance()->getWinTotalCNT();
    isAds = num > GAMENOADSCNT;
    getNode<Button*>("Button_get")->setEnabled(!isAds || is);
    getNode("ui_Videoplayer_1")->setVisible(isAds);
    
    getNode("Node_down")->setVisible(false);
    playAni("Start0",false,[this](){
        getNode("Node_down")->setVisible(true);
    });
    
    FileNode_Gold = getNode("FileNode_Gold");
    FileNode_Diamond = getNode("FileNode_Diamond");
    
    UIUtils::playInnerAction(FileNode_Gold, "Gold", true);
    UIUtils::playInnerAction(FileNode_Diamond, "Baoshi", true);
    
    
    auto Text_5_0 = getNode<Text*>("Text_5_0");
    Text_5_0->setString("倍大奖金!!");
    //修正位置
    auto size = Text_5_0->getBoundingBox().size;
    
    auto BitmapFontLabel_14 = getNode("BitmapFontLabel_14");
    BitmapFontLabel_14->setPosition(Vec2(-10,size.height*0.48));
    //更新文本显示
    auto Text_x7 = getNode<TextBMFont*>("Text_x7");
    Text_x7->setString(StringUtils::format("%d x 7",_coinNum));
    size = Text_x7->getContentSize();
    getNode("BitmapFontLabel_3")->setPosition(Vec2(size.width+36,size.height*0.65f));
    getNode<TextBMFont*>("Text_25")->setString(StringUtils::format("+%d",_coinNum));
    getNode<TextBMFont*>("Text_50")->setString(StringUtils::format("+%d",_coinNum*2));
    getNode<TextBMFont*>("Text_75")->setString(StringUtils::format("+%d",_coinNum*3));
    getNode<TextBMFont*>("Text_100")->setString(StringUtils::format("+%d",_coinNum*4));
    getNode<TextBMFont*>("Text_125")->setString(StringUtils::format("+%d",_coinNum*5));
    getNode<TextBMFont*>("Text_150")->setString(StringUtils::format("+%d",_coinNum*6));
    getNode<TextBMFont*>("Text_175")->setString(StringUtils::format("+%d",_coinNum*7));
    //多语言
    auto Text_get = getNode<Text*>("Text_get");
    Text_get->setString(Lang("100279"));
    UIUtils::textAdaptiveSize(Text_get,350);
    //
    getNode<Text*>("Text_close")->setString(Lang("100404"));
    getNode<Text*>("Text_10")->setString(Lang("100257"));
    Text_5_0->setString(Lang("100258"));
}
void MultipleRewardView::initData()
{
    BaseLayer::initData();
    EVENT_M->addListener("event_game_multiple_gold",[this](ValueMap valueMap, void *obj){
//        //多倍奖励
//        auto num = DATA_M->getRewardCoin() * 7;
//        auto lobby = SCENE_M->getLobby();
//        lobby->setVisible(true);
//        lobby->resetHome();
//        lobby->updateExp();
//        SCENE_M->getGameView()->setVisible(false);
//        //lobby->dailyShowComplete();
//
//        auto poi = getContentSize()*0.5;
//        lobby->goldAni(num,nullptr,poi,[this,lobby,num](){
//            //更新有金币显示
//            
//            DATA_M->setCoinNum(num, true, 103);
//            ValueMap valueMap{
//                {"isTime",Value{true}}
//            };
//            //更新有金币显示
//            EVENT_M->sendEvent("event_game_update_coin",valueMap);
//            SCENE_M->removeLayer(this);
//        },[lobby](){
//            //home
//            lobby->playGoldAni(1,true);
//        },[lobby,this](){
//            lobby->playGoldAni(1,false);
//        });
//        poi.width+=160;
//        auto diamond = WINLAYER_DIAMOND*7;
//        lobby->diamondAni(WINLAYER_DIAMOND * 7,nullptr,poi,[this,lobby,diamond](){
//            //更新有金币显示
//            DATA_M->setDiamond(diamond);
//            ValueMap valueMap{
//                {"isTime",Value{true}}
//            };
//            //更新有金币显示
//            EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//            
//            
//        },[lobby](){
//            //home
//            lobby->playDiamondAni(1,true);
//        },[lobby](){
//            //home
//            lobby->playDiamondAni(1,false);
//        });
        
        if(_cb2)
        {
            _cb2();
        }
        this->setVisible(false);
    },this);
}

void MultipleRewardView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    auto name = btn->getName();
    if(name == "Button_close")
    {
        if(_cb)
        {
            _cb();
        }
        UIUtils::FIRFirestoreAdd("operator", {
           {"key", Value("MultipleRewardView")},
           {"value", Value("no")},
           {"v1", Value(DATA_M->getHaveVideo())}
        });
        if (_isTeach)
            UIUtils::FIRAnalyticsEventWithPrefix("7xReward_no", "teach");
        SCENE_M->removeLayer(this);
    }
    else if(name == "Button_get")
    {
        if(isAds)
        {
            DATA_M->playVideoAds(7);
            UIUtils::FIRFirestoreAdd("operator", {
               {"key", Value("MultipleRewardView")},
               {"value", Value("ad")}
            });
        }
        else
        {
            EVENT_M->sendEvent("event_game_multiple_gold");
        }
        
        if (_isTeach)
            UIUtils::FIRAnalyticsEventWithPrefix("7xReward_ad", "teach");
    }
}

void MultipleRewardView::updateUI()
{
    
}

void MultipleRewardView::onEnter()
{
    BaseLayer::onEnter();
}
void MultipleRewardView::onExit()
{
    BaseLayer::onExit();
    EVENT_M->removeListener("event_game_multiple_gold",this);
}
