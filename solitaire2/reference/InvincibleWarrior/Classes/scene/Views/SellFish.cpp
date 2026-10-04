//
//  SellFish.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/18.
//

#include <stdio.h>
#include "SellFish.h"
#include "FishManager.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "GameBackground.h"
#include "MainLobby.h"
#include "EventObserver.h"
#include "BagGameBg.h"
#include "SceneManager.h"
#include "FashTankShop.h"

SellFish::SellFish(BagGameBg* bagGameBg,int fashTankIdx,int fishType,int index,int price,std::function<void()> cb)
:BaseLayer("2021SellFish.csb")
{
    _bagGameBg = bagGameBg;
    _fashTankIdx = fashTankIdx;
    _fishType = fishType;
    _index = index;
    _price = price;
    _cb = cb;
}
SellFish::~SellFish()
{
    
}

void SellFish::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    auto Node_Fish = getNode("Node_Fish");
    
    auto fishSpine = FishManager::getInstance()->getFishSpine(_fishType);
    Node_Fish->addChild(fishSpine);
    if(_fishType == 14)
    {
        
        fishSpine->setPositionX(682.27f/4);
    }
    fishSpine->setAnimation(0, "Run", true);
    getNode<Text*>("Text_jiaGe")->setString(StringUtils::format(Lang("100342").c_str(),_price));
    getNode<Text*>("Text_miaoShu")->setString(Lang("100341"));

    getNode<Text*>("Text_NameNo")->setString(Lang("100344"));
    auto Text_NameYes = getNode<Text*>("Text_NameYes");
    Text_NameYes->setString(Lang("100343"));
}

void SellFish::initData()
{
    BaseLayer::initData();
    setName("SellFish");
}

void SellFish::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;

    auto btnName = btn->getName();
    
    if(btnName == "Button_close"||btnName == "Panel_out"||btnName == "Button_no")
    {//关闭
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_yes")
    {//出售
        
        SCENE_M->getGameBackground()->deleteFish(_index,_fashTankIdx);
        nodeAni();
        //_bagGameBg->updateUI();
        auto shop = _bagGameBg->getFashTankShop();
        
        shop->setTab(FashTankShop::Tab::FISH);
        if(_cb)_cb();
        
        SCENE_M->removeLayer(this);
        UIUtils::FIRFirestoreAddOP("fish_sell", toString(_fishType));
        UIUtils::FIRAnalyticsEvent("fish_sell", {});
    }
}

void SellFish::onEnter()
{
    BaseLayer::onEnter();
    
}
void SellFish::onExit()
{
    BaseLayer::onExit();
}

void SellFish::updateUI()
{
    
}

void SellFish::nodeAni()
{
    auto lobby = SCENE_M->getLobby();
    //出现金币
    if(true)
    {
        auto coinNum = _price;
        lobby->goldAni(100,nullptr,Vec2(2000,2000),[lobby,this,coinNum](){
            DATA_M->setCoinNum(coinNum, true, 124);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            
        },[lobby,this](){
            //home
           
            lobby->playGoldAni(1,true);
            
            
        },[lobby,this](){
            //home
            
            lobby->playGoldAni(1,false);
            
        });
    }
//    else
//    {
//        auto diamondNum = 70;
//        lobby->diamondAni(70,nullptr,Vec2(2000,2000),[lobby,this,diamondNum](){
//            DATA_M->setDiamond(diamondNum);
//            ValueMap valueMap{
//                {"isTime",Value{true}}
//            };
//            //更新有金币显示
//            EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//
//        },[lobby,this](){
//            //home
//
//            lobby->playDiamondAni(1,true);
//
//            //SOUND_M->playEffectMusic(EffectGetGem);
//
//        },[lobby,this](){
//
//
//            lobby->playDiamondAni(1,false);
//
//        });
//    }
}
