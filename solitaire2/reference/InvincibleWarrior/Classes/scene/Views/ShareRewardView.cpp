//
//  ShareRewardView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/26.
//

#include <stdio.h>
#include "ShareRewardView.h"
#include "MainLobby.h"
#include "HomeView.h"
#include "DailyView.h"
#include "EventObserver.h"
#include "TaskManager.h"
#include "SceneManager.h"
#include "DataManager.h"

ShareRewardView::ShareRewardView(ShareRewardView::Type type)
:BaseLayer("2020Share.csb")
,_type(type)
{
    auto is = TASK_M->getIsYday();
    if(is)
    {//是第二天
        SETINTEGER("rewardNum",1);
    }
    //领取次数
    rewardNum = GETINTEGER("rewardNum",1);
}
ShareRewardView::~ShareRewardView()
{
    
}

void ShareRewardView::updateUI()
{
    
}
    
void ShareRewardView::initUI()
{
    BaseLayer::initUI();
    
    
    
    if(rewardNum == 1)
    {
        goldNum = 50;
    }
    else
    {
        goldNum = 0;
    }
    
    
    
    doLayout();
    playAni("Start0",false);
    
    if(goldNum > 0)
    {
        getNode<TextBMFont*>("BitmapFontLabel_goldNum")->setVisible(true);
        getNode<TextBMFont*>("BitmapFontLabel_goldNum")->setString(StringUtils::format("+%d",goldNum));
    }
    else
    {
        getNode<TextBMFont*>("BitmapFontLabel_goldNum")->setVisible(false);
    }
    getNode<Text*>("Text_miaoshu")->setString(StringUtils::format(Lang("100249").c_str(),goldNum));
    getNode<Text*>("Text_top")->setString(Lang("100248"));
    getNode<Text*>("Text_share")->setString(Lang("100119"));
}

void ShareRewardView::initData()
{
    BaseLayer::initData();
    
    setName("ShareRewardView");
    EVENT_M->addListener("event_game_share", [this](ValueMap valueMap, void *obj){
        //分享成功50金币
        auto num = goldNum;//DATA_M->getRewardCoin1();
        if(_type == ShareRewardView::Type::Home)
        {
            
        }
        else if(_type == ShareRewardView::Type::Daily)
        {
            
        }
        if(num == 0)
        {//
            SCENE_M->removeLayer(this);
            return;
        }
        rewardNum--;
        SETINTEGER("rewardNum",rewardNum);
        
        
        auto lobby = SCENE_M->getLobby();
        lobby->goldAni(num,nullptr,Vec2(2000,2000),[lobby,this,num](){
            DATA_M->setCoinNum(num, true, 116);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            //lobby->updateCoin(true);
        },[lobby,this](){
        //home
            //SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni((int)_type,true);
        },[lobby,this](){
            //home
            //SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni((int)_type,false);
            SCENE_M->removeLayer(this);
        });
        this->setVisible(false);
    },this);
//    addEvent("event_game_share", [this](EventCustom *eventCustom){
//        
//        //更新有金币显示
//
//        //SCENE_M->removeLayer(this);
//    });
}

void ShareRewardView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    auto name = btn->getName();
    if(name == "Button_close")
    {
        SCENE_M->removeLayer(this);
    }
    else if(name == "Button_share")
    {
        UIUtils::shareApp();
    }
}

void ShareRewardView::onEnter()
{
    BaseLayer::onEnter();
}
void ShareRewardView::onExit()
{
    BaseLayer::onExit();
    EVENT_M->removeListener("event_game_share",this);
}
