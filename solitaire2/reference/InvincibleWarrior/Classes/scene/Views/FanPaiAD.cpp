//
//  FanPaiAD.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/8.
//

#include <stdio.h>
#include "FanPaiAD.h"
#include "MainLobby.h"
#include "PlayerManager.h"
#include "AtlasManager.h"
#include "ShopManager.h"
#include "HomeView.h"
#include "DailyView.h"
#include "StoreView.h"
#include "DrawPropsView.h"
#include "RewardManager.h"
#include "GameViewHD.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#endif
#include "GrowupNode.h"
#include "EventObserver.h"
#include "SpriteManager.h"
#include "DataManager.h"

const int goldNumArr[] = {2,3,4,10};
const string CARDITEM = "cardItem";

FanPaiAD::FanPaiAD(FanPaiAD::Type type)
:BaseLayer("2021DrawAD1.csb")
,_type(type)
{
    isOne = GETBOOL("FanPaiOne",isOne);
    
    for(int i = 0;i<6;++i)
    {
        _goldNum[i] = -1;//如果金币钻石 记录数目
        _idx[i] = -1;//如果牌 背景 音乐，记录id
        _randNum[i] = -1;//如果是牌面，记录num
        shopType[i] = -1;//记录对应奖励类型
    }
    fanPaiNum = GETINTEGER("fanPaiNum",3);
}

FanPaiAD::~FanPaiAD()
{
    
}

void FanPaiAD::initUI()
{
    BaseLayer::initUI();
    doLayout();
    //top
    getNode("Button_getGold")->setVisible(false);
    getNode("Button_getDiamond")->setVisible(false);

    getNode("Button_get")->setVisible(false);
    getNode("Button_close")->setVisible(false);
    auto spFrame = SPRITE_M->getCardBgSpriteFrame(0);
    int j = random(1,5);
    for(int i = 1;i<6;++i)
    {
        auto node = getNode(StringUtils::format("FileNode_%d",i));
        auto sp = node->getChildByName<Sprite*>("card_bg_0_1");
        
        auto panel = sp->getChildByName<Layout*>("Panel_get");
        panel->setEnabled(false);
    }
    FileNode_reward = getNode("FileNode_1");
    isTouch = false;
    
    _rewardNum = 5;
        playAni("Start2",false,[this](){
            //允许点击
            isTouch = true;
            for(int i = 1;i<6;++i)
            {
                auto node = getNode(StringUtils::format("FileNode_%d",i));
                
                UIUtils::playInnerAction(node,"Loop",true);
            }
            getNode("Button_close")->setVisible(true);
        });
    
    reward1 = 0;//100金币
    reward2 = 0;//50钻石
    while (1) {
        
        auto tag = random(1, 5);
        if(reward1 == 0)
        {
            reward1 = tag;
        }
        else if(reward1 != tag)
        {
            reward2 = tag;
            break;
        }
    }
    randReward();
    
    _actionManager->setFrameEventCallFunc([this](Frame* frame){
         auto event = dynamic_cast<EventFrame*>(frame);
         auto msg = event->getEvent();
         if(msg.find(CARDITEM) != string::npos)
         {
//             auto idstr = msg[8];
//             auto node = getNode(StringUtils::format("FileNode_%c",idstr));
//             UIUtils::playInnerAction(node,"Loop",true);
         }
         else if(msg == "panel_29Show")
         {
             for(int i = 1;i<6;++i)
             {
                 auto node = getNode(StringUtils::format("FileNode_%d",i));
                 
                 auto Panel_69 = node->getChildByName("Panel_69");

                 Panel_69->setVisible(false);
                 
             }
         }
    });
    tempFangCuo = 0;
    float time = 240 * 0.017;
    //防错
    schedule([this,time](float dt){
        
        tempFangCuo+=dt;
        if(tempFangCuo >= time)
        {
            //允许点击
            isTouch = true;
            unschedule("FanPaifangCuo");
        }
    },"FanPaifangCuo");
    
    updateUI();
    
    
    getNode<Text*>("Text_13")->setString(Lang("100001"));
    getNode<Text*>("Text_10")->setString("Lucky Coin!");
}
void FanPaiAD::initData()
{
    BaseLayer::initData();
    setName("FanPaiAD");
    EVENT_M->addListener("event_game_update_coin", [this](ValueMap valueMap, void *obj){
        if(!valueMap.empty())
        {
            auto isTime = valueMap["isTime"].asBool();
            this->updateCoin(isTime);
        }
        else
        {
            this->updateCoin();
        }
    },this);
    EVENT_M->addListener("event_game_update_diamond", [this](ValueMap valueMap, void *obj){
        if(!valueMap.empty())
        {
            auto isTime = valueMap["isTime"].asBool();
            this->updateDiamond(isTime);
        }
        else
        {
            this->updateDiamond();
        }
    },this);
//    addEvent("event_game_update_coin", [this](EventCustom *e){
//        auto isTime = (bool)e->getUserData();
//        this->updateCoin(isTime);
//    });
//    addEvent("event_game_update_diamond", [this](EventCustom *e){
//        auto isTime = (bool)e->getUserData();
//        this->updateDiamond(isTime);
//    });
    
    EVENT_M->addListener("msg_game_showwin",[this](ValueMap valueMap, void *obj){
        if (_InterstitialCB) {
            _InterstitialCB();
            _InterstitialCB = nullptr;
        }
//        DATA_M->setPlayAds(false);
//        //重置限制插屏的cd
//        auto timeNow = std::time(0);
//        DATA_M->setInterstitialTime(timeNow);
//        DATA_M->setIsVideoAdsTime(true);
//        DATA_M->setVideoAdsTime(0,true);//重置激励视频对插屏的限制cd
//        DATA_M->setIsShowAds(false);
    },this);
//    addEvent("msg_game_showwin", [this](EventCustom*) {//。插屏
//
//    });
    
    
//    EVENT_M->addListener("event_game_update_fanPai", [this](ValueMap valueMap, void *obj){
//        //翻牌
//        if(FanPaiAD::RewardType::BigGold == _RewardType[_tag]||FanPaiAD::RewardType::SmallGold == _RewardType[_tag])
//        {
//            //获得奖励gold
//            Vec2 poi(2000,2000);
//            GameViewHD* gameview = nullptr;
//            if(FanPaiAD::Type::Game == _type)
//            {
//                gameview = SCENE_M->getGameView();
//                poi = gameview->getGoldWorldPoi();
//            }
//             //出现金币
//            auto lobby = SCENE_M->getLobby();
//            lobby->goldAni(_goldNum[_tag],gameview,Vec2(2000,2000),[lobby,this](){
//                if(_type == FanPaiAD::Type::Game)
//                {
//                    auto gameview = SCENE_M->getGameView();
//                    gameview->updateCoin();
//                    gameview->updateDiamond();
//                }
//                else
//                {
//                    lobby->updateCoin(true);
//                }
//
//            },[lobby,this](){
//            //home
//                //SOUND_M->playEffectMusic(EffectGetCoin);
//                lobby->playGoldAni((int)_type,true);
//            },[lobby,this](){
//                //home
//                //SOUND_M->playEffectMusic(EffectGetCoin);
//                lobby->playGoldAni((int)_type,false);
//                SCENE_M->removeLayer(this);
//            },poi);
//        }
//        else if(FanPaiAD::RewardType::BigDiamond == _RewardType[_tag]||FanPaiAD::RewardType::SmallDiamond == _RewardType[_tag])
//        {
//            Vec2 poi(2000,2000);
//            GameViewHD* gameview = nullptr;
//            if(FanPaiAD::Type::Game == _type)
//            {
//                gameview = SCENE_M->getGameView();
//                poi = gameview->getdiamondWorldPoi();
//            }
//            //获得奖励Dia
//            auto lobby = SCENE_M->getLobby();
//            lobby->diamondAni(_goldNum[_tag],gameview,Vec2(2000,2000),[lobby,this](){
//
//                if(_type == FanPaiAD::Type::Game)
//                {
//                    auto gameview = SCENE_M->getGameView();
//                    gameview->updateCoin();
//                    gameview->updateDiamond();
//                }
//                else
//                {
//                    lobby->updateDiamond(true);
//                }
//            },[lobby,this](){
//                //home
//                //SOUND_M->playEffectMusic(EffectGetGem);
//                lobby->playDiamondAni(1,true);
//            },[lobby,this](){
//                //home
//                //SOUND_M->playEffectMusic(EffectGetGem);
//                lobby->playDiamondAni(1,false);
//                SCENE_M->removeLayer(this);
//            },poi);
//        }
//        fanPaiNum--;
//        SETINTEGER("fanPaiNum",fanPaiNum);
//
//        if(_type == FanPaiAD::Type::Game)
//        {
//            auto gameview = SCENE_M->getGameView();
//            gameview->gamePause(false);//解除暂停
//        }
//
//        this->setVisible(false);
//    },this);
//    addEvent("event_game_update_fanPai", [this](EventCustom *){
//        
//    });
}

void FanPaiAD::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn||!isTouch)return;
    auto name = btn->getName();
    if(name == "Button_close")
    {//guanbi
        if(_type == FanPaiAD::Type::Game)
        {
            auto gameview = SCENE_M->getGameView();
            gameview->gamePause(false);//解除暂停
        }
        fangCuo = -1;
        SCENE_M->removeLayer(this);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("FanPaiAD")},
            {"value", Value("no")},
            {"v1", Value((int)_type)},
            {"v2", Value(DATA_M->getHaveVideo())}
        });
    }
    else if(name == "Button_get")
    {

        fangCuo = -1;
        SCENE_M->removeLayer(this);
    }
    else if(name.find("Button_reward") != string::npos)
    {//开启二段动画
        //选中的牌移动到中心，
        //其余四张牌隐藏
        getNode("Button_close")->setVisible(false);
        auto tag = btn->getTag();
        _tag = tag;
        for(int i = 1;i<6;++i)
        {
            auto btn = getNode<Button*>(StringUtils::format("Button_reward%d",i));
            btn->setEnabled(i==tag);
            btn->setVisible(i==tag);
        }
        auto node = getNode(StringUtils::format("Button_reward%d",tag));
        auto Panel_7 = getNode("Panel_7");
        auto poi = Panel_7->getContentSize() * 0.5f;
        auto Panel_9 = getNode("Panel_9");
        poi = Panel_9->convertToNodeSpace(poi);
        float time = 0.2;
        auto to = MoveTo::create(time, poi);
        auto rota = RotateTo::create(time,0);
        auto swa = Spawn::create(to,rota, NULL);
        auto func = CallFunc::create([this](){
            //randReward(tag,true);
            //找到对应的奖励
            
            int tag = randRewardTag();
            
            if(FanPaiAD::RewardType::BigGold == _RewardType[tag]||FanPaiAD::RewardType::SmallGold == _RewardType[tag])
            {
                            //获得奖励gold
                openGold(tag, true);
            }
            else if(FanPaiAD::RewardType::BigDiamond == _RewardType[tag]||FanPaiAD::RewardType::SmallDiamond == _RewardType[tag])
            {
                //获得奖励Dia
                openDiamond(tag, true);
            }
            if(FanPaiAD::RewardType::GameBg == _RewardType[tag])
            {
               //获得奖励
                //DATA_M->unLockShopItemStatus(1,_idx[_tag]);
                openGameBg(tag, true);
            }
            else if(FanPaiAD::RewardType::CardBg == _RewardType[tag])
            {
                //获得奖励
                openCardBg(tag, true);
            }
            else if(FanPaiAD::RewardType::CardFace == _RewardType[tag])
            {
                //获得奖励
                openCardFace(tag, true);
            }
            else if(FanPaiAD::RewardType::Music == _RewardType[tag])
            {//音乐Ui_music.png
                //获得奖励
                openMusic(tag, true);
            }
            else if(FanPaiAD::RewardType::Magic == _RewardType[tag])
            {//
                //获得奖励
                //增加一次
                openMagic(tag, true);
            }
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("FanPaiAD")},
                {"value", Value("ad")},
                {"v1", Value((int)_type)}
            });
        });
        auto seq = Sequence::create(swa,func, NULL);
        //isTouch = false;
        node->runAction(seq);
        btn->setEnabled(false);
    }
}

int FanPaiAD::randGoldNum()
{
    auto rand = random(0,100);
    int id = 0;
    
    if(rand < 25)
    {//100
        id = 3;
    }
    else if(rand < 50)
    {//75
        id = 2;
    }
    else if(rand < 75)
    {//50
        id = 1;
    }
    else if(rand <= 100)
    {//25
        id = 0;
    }

    return goldNumArr[id];
}

void FanPaiAD::openGold(int tag,bool isAni)
{
    //_tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",_tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    auto sp = node;
    if(!isAni)
    {
        shopType[tag] = 1;//1是金币
        
        
        
        bool is = _goldNum[tag]>10;
        updateItemUI(tag,sp,_RewardType[tag]);
    }
    else
    {
        
        SOUND_M->playEffectMusic(EffectCrown);
        auto animanager = UIUtils::playInnerAction(node,"Start1",false,[this,poi,tag](){
                isTouch = true;
            getNode("Button_close")->setVisible(true);
                _rewardNum--;
                auto cb = [this](){
                    
                    
                    if(_type == FanPaiAD::Type::Game)
                    {
                        auto gameview = SCENE_M->getGameView();
                        gameview->gamePause(false);//解除暂停
                    }
                    
                    
                    Vec2 poi(2000,2000);
                    GameViewHD* gameview = nullptr;
                    if(FanPaiAD::Type::Game == _type)
                    {
                        gameview = SCENE_M->getGameView();
                        poi = gameview->getGoldWorldPoi();
                    }
                     //出现金币
                    auto lobby = SCENE_M->getLobby();
                    auto coin = _goldNum[_tag];
                    lobby->goldAni(_goldNum[_tag],gameview,Vec2(2000,2000),[lobby,this,coin](){
                        DATA_M->setCoinNum(coin, true, 122);
                        ValueMap valueMap{
                            {"isTime",Value{true}}
                        };
                        //更新有金币显示
                        EVENT_M->sendEvent("event_game_update_coin",valueMap);
                    
                    },[lobby,this](){
                    //home
                        //SOUND_M->playEffectMusic(EffectGetCoin);
                        if(fangCuo == 10)
                        {
                            lobby->playGoldAni(1,true);
                        }
                        else
                        {
                            lobby->playGoldAni((int)_type,true);
                        }
                        
                    },[lobby,this](){
                        //home
                        //SOUND_M->playEffectMusic(EffectGetCoin);
                        if(fangCuo == 10)
                        {
                            lobby->playGoldAni(1,true);
                        }
                        else
                        {
                            lobby->playGoldAni((int)_type,true);
                        }
                        //SCENE_M->removeLayer(this);
                    },poi);
                    
                    fanPaiNum--;
                    SETINTEGER("fanPaiNum",fanPaiNum);
                    //翻牌时间重置
                    DATA_M->setFreeCoinTime4(DATA_M->getContentSec());
                    //通知游戏界面删除礼包z
                    SCENE_M->refushGift();
                    
                    getNode("Button_get")->setVisible(true);
                    if(_type == FanPaiAD::Type::Game)
                    {
                        SCENE_M->removeLayer(this);
                    }
                };
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                if(DATA_M->showNativeAds(2, "FanPaiAD"))
                {
                    AdsManager::waitWinAction = true;
                    _InterstitialCB = cb;
                }
                else
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            DATA_M->showNativeAds(2, "FanPaiAD");
#endif
                {
                    cb();
                }
                
        //        if(_rewardNum == 0)
        //        {//出现按钮
        //        }
        //        //出现金币
        //        auto lobby = SCENE_M->getLobby();
        //        lobby->goldAni(_goldNum[tag],this,poi,[lobby,this](){
        //
        
        //        },[lobby,this](){
        //            //home
        //            lobby->playGoldAni(this,true);
        //        },[lobby,this](){
        //            //home
        //            lobby->playGoldAni(this,false);
        //        });
                
            });
            animanager->setFrameEventCallFunc([this,sp,tag](Frame* frame){
                auto event = dynamic_cast<EventFrame*>(frame);
                auto msg = event->getEvent();
                if(msg == "game_Front")
                {
                    //auto frame = SPRITE_M->getCardSpriteFrameByNumAndColor(1,0,0);

                    bool is = _goldNum[tag]>10;
                    updateItemUI(tag,sp,_RewardType[tag]);
                    //is?FanPaiAD::RewardType::BigGold:FanPaiAD::RewardType::SmallGold);
                }
            });
    }
}

void FanPaiAD::openDiamond(int tag,bool isAni)
{
    openGold(tag,isAni);
}

void FanPaiAD::updateUI()
{
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    
    updateCoin();
    updateDiamond();
}

void FanPaiAD::updateCoin(bool isDelay)
{
    auto text = getNode<TextBMFont*>("BitmapFontLabel_gold");
    auto vec = text->getChildren();
    for(auto child:vec)
    {
        auto grouwup = dynamic_cast<GrowupNode*>(child);
        if(grouwup)
        {
            grouwup->unTextSchedule();
        }
    }
    if(isDelay)
    {//2.45
        //auto text = getNode<TextBMFont*>("BitmapFontLabel_gold");
        auto str = text->getString();
        _coinNum = UIUtils::stoii(str);
        auto num = DATA_M->getCoinNum();
        auto tempNum = num - _coinNum;
        if(tempNum <= 0)
        {
            text->setString(StringUtils::toString(num));
            return;
        }
        float time = 0;
        if(tempNum >= 15)
        {
            time = 0.75/FLYSPEED;
        }
        else
        {
            time = 0.05/FLYSPEED * tempNum;
        }
        auto grouwup = GrowupNode::create();
        text->addChild(grouwup);
        grouwup->startGrouwup(text, _coinNum, num, time, "",[this, grouwup](){
            //UIUtils::playInnerAction(FileNode_gold, "jump", false);
            grouwup->removeFromParent();
        });
    }
    else
    {
        int coinNum = DATA_M->getCoinNum();
        text->setString(StringUtils::toString(coinNum));
    }
}

void FanPaiAD::updateDiamond(bool isDelay)
{
//    auto text = getNode<TextBMFont*>("BitmapFontLabel_diamond");
//    auto vec = text->getChildren();
//    for(auto child:vec)
//    {
//        auto grouwup = dynamic_cast<GrowupNode*>(child);
//        if(grouwup)
//        {
//            grouwup->unTextSchedule();
//        }
//    }
//    if(isDelay)
//    {
//        //auto text = getNode<TextBMFont*>("BitmapFontLabel_diamond");
//        auto str = text->getString();
//        _diamondNum = UIUtils::stoii(str);
//        auto num = DATA_M->getDiamond();
//        auto tempNum = num - _diamondNum;
//        if(tempNum <= 0)
//        {
//            text->setString(StringUtils::toString(num));
//            return;
//        }
//        float time = 0;
//        if(tempNum >= 15)
//        {
//            time = 0.75/FLYSPEED;
//        }
//        else
//        {
//            time = 0.05/FLYSPEED * tempNum;
//        }
//        auto grouwup = GrowupNode::create();
//        text->addChild(grouwup);
//        grouwup->startGrouwup(text, _diamondNum, num, time, [this, grouwup](){
//            //UIUtils::playInnerAction(FileNode_gold, "jump", false);
//            grouwup->removeFromParent();
//        });
//    }
//    else
//    {
//        int diamondNum = DATA_M->getDiamond();
//        text->setString(StringUtils::toString(diamondNum));
//    }
}

void FanPaiAD::openCardBg(int tag,bool isAni)
{
    //_tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",_tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    auto sp = node;
    if(!isAni)
    {
        shopType[tag] = 3;//3是牌背
        _idx[tag] = random(0, CARD_BG_NUM-1);
        auto isBuy = DATA_M->getShopItemStatus(3,_idx[tag]);
        
        
        //sp->setVisible(!isBuy);
        if(isBuy)
        {//金币50
            _goldNum[tag] = 50;
            updateItemUI(tag,sp,FanPaiAD::RewardType::BigGold);
        }
        else
        {
            updateItemUI(tag,sp,FanPaiAD::RewardType::CardBg,_idx[tag]);
        }
    }
    else
    {
        auto isBuy = DATA_M->getShopItemStatus(3,_idx[tag]);
        auto index = 3*100000 + _idx[tag]*1000;
        if(!isBuy)
        {
            idxVec.push_back(index);
        }
        auto animanager = UIUtils::playInnerAction(node,isBuy?"Start":"Start1",false,[this,poi,isBuy,node,tag](){
                isTouch = true;
                
                    getNode("Button_get")->setVisible(true);
        //        _rewardNum--;
        //        if(_rewardNum == 0)
        //        {//出现按钮
        //        }
                if(1)
                {
        
                }
                else
                {//卡牌飞出
                    
                }
            });
            animanager->setFrameEventCallFunc([this,node,tag,sp,isBuy](Frame* frame){
                auto event = dynamic_cast<EventFrame*>(frame);
                auto msg = event->getEvent();
                if(msg == "game_Front")
                {
                    if(isBuy)
                    {//金币50
                        _goldNum[tag] = 50;
                        updateItemUI(tag,sp,FanPaiAD::RewardType::BigGold);
                    }
                    else
                    {
                        updateItemUI(tag,sp,FanPaiAD::RewardType::CardBg,_idx[tag]);
                    }
                }
            });
    }
    
    
    
    
    
}

void FanPaiAD::openGameBg(int tag,bool isAni)
{
    
    //_tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",_tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);

    auto sp = node;
    if(!isAni)
    {
        shopType[tag] = 1;//1是背景
        
        _idx[tag] = random(0, GAME_BG_NUM-1);
        auto isBuy = DATA_M->getShopItemStatus(1,_idx[tag]);
        
        if(isBuy)
        {//金币50
            _goldNum[tag] = 50;
            updateItemUI(tag,sp,FanPaiAD::RewardType::BigGold);
        }
        else
        {
            updateItemUI(tag,sp,FanPaiAD::RewardType::GameBg,_idx[tag]);
        }
    }
    else
    {
        auto isBuy = DATA_M->getShopItemStatus(1,_idx[tag]);
        auto index = 1*100000 + _idx[tag]*1000;
        if(!isBuy)
        {
            idxVec.push_back(index);
        }
        auto animanager = UIUtils::playInnerAction(node,isBuy?"Start":"Start1",false,[this,poi,isBuy,node,tag](){
                isTouch = true;
                 _rewardNum--;
               
                     getNode("Button_get")->setVisible(true);
        //        if(_rewardNum == 0)
        //        {//出现按钮
        //        }
                if(isBuy)
                {
        
                     
                }
                else
                {//卡牌飞出
                     
                }
            });
            animanager->setFrameEventCallFunc([this,node,isBuy,tag,sp](Frame* frame){
                 auto event = dynamic_cast<EventFrame*>(frame);
                 auto msg = event->getEvent();
                 if(msg == "game_Front")
                 {
                     if(isBuy)
                     {//金币50
                         _goldNum[tag] = 50;
                         updateItemUI(tag,sp,FanPaiAD::RewardType::BigGold);
                     }
                     else
                     {
                         updateItemUI(tag,sp,FanPaiAD::RewardType::GameBg,_idx[tag]);
                     }
                 }
            });
    }
    
    
    
    
    
//
    
     
    
}

void FanPaiAD::openCardFace(int tag,bool isAni)
{
    //_tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",_tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    auto sp = node;
    if(!isAni)
    {
        shopType[tag] = 2;//2是牌面
        _idx[tag] = DATA_M->getCardFace();
        _randNum[tag] = random(0, 51);
        auto isBuy = DATA_M->getCardFaceStatus(2,_idx[tag],_randNum[tag]);
        
        if(isBuy)
        {//金币50
           _goldNum[tag] = 50;
           updateItemUI(tag,sp,FanPaiAD::RewardType::BigGold);
        }
        else
        {
            
            updateItemUI(tag,sp,FanPaiAD::RewardType::CardFace,_idx[tag],_randNum[tag]);
        }
        
    }
    else
    {
        auto num = _randNum[tag] % 13 + 1;
        auto col = (int)(_randNum[tag] / 13);
           
          
        auto isBuy = DATA_M->getCardFaceStatus(2,_idx[tag],_randNum[tag]);
           
        auto index = 2*100000 + _idx[tag]*1000 + _randNum[tag];
        if(!isBuy)
        {
            idxVec.push_back(index);
        }
        auto animanager = UIUtils::playInnerAction(node,isBuy?"Start":"Start1",false,[this,poi,isBuy,node,tag](){
                isTouch = true;
                 _rewardNum--;
                
                     getNode("Button_get")->setVisible(true);
        //        if(_rewardNum == 0)
        //        {//出现按钮
        //        }
                if(isBuy)
                {
        
                }
                else
                {//卡牌飞出
                     
                }
            });
            animanager->setFrameEventCallFunc([this,num,col,node,isBuy,tag,sp](Frame* frame){
                 auto event = dynamic_cast<EventFrame*>(frame);
                 auto msg = event->getEvent();
                 if(msg == "game_Front")
                 {
                     if(isBuy)
                     {//金币50
                        _goldNum[tag] = 50;
                        updateItemUI(tag,sp,FanPaiAD::RewardType::BigGold);
                     }
                     else
                     {
                         
                         updateItemUI(tag,sp,FanPaiAD::RewardType::CardFace,_idx[tag],_randNum[tag]);
                     }
                 }
            });
    }
    
    
    
   
     
    
}

void FanPaiAD::openMusic(int tag,bool isAni)
{//音乐
    //_tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",_tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    auto sp = node;
    if(!isAni)
    {
        shopType[tag] = 5;//音乐5
        
        _idx[tag] = random(0, LobbyMusicTotalCNT-1);
        
        auto isBuy = DATA_M->getShopItemStatus(5,_idx[tag]);
        
        
        if(isBuy)
        {//金币50
           _goldNum[tag] = 50;
           updateItemUI(tag,sp,FanPaiAD::RewardType::BigGold);
        }
        else
        {
            updateItemUI(tag,sp,FanPaiAD::RewardType::Music,_idx[tag]);
        }
    }
    else
    {
        auto isBuy = DATA_M->getShopItemStatus(5,_idx[tag]);
        auto index = 5*100000 + _idx[tag]*1000;
        if(!isBuy)
        {
            idxVec.push_back(index);
        }
        auto animanager = UIUtils::playInnerAction(node,isBuy?"Start":"Start1",false,[this,poi,isBuy,node,tag](){
                isTouch = true;
                 _rewardNum--;
                
                     getNode("Button_get")->setVisible(true);
        //        if(_rewardNum == 0)
        //        {//出现按钮
        //        }
                if(isBuy)
                {
        
                }
            });
            animanager->setFrameEventCallFunc([this,node,isBuy,tag,sp](Frame* frame){
                 auto event = dynamic_cast<EventFrame*>(frame);
                 auto msg = event->getEvent();
                 if(msg == "game_Front")
                 {
                     if(isBuy)
                     {//金币50
                        _goldNum[tag] = 50;
                        updateItemUI(tag,sp,FanPaiAD::RewardType::BigGold);
                     }
                     else
                     {
                         updateItemUI(tag,sp,FanPaiAD::RewardType::Music,_idx[tag]);
                     }
                 }
            });
    }
    
    
    
    
    

    
    
}

void FanPaiAD::openMagic(int tag,bool isAni)
{//魔法棒
    //_tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",_tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    auto sp = node;
    if(!isAni)
    {
        shopType[tag] = 4;//魔法棒4
        _idx[tag] = 1000;

        updateItemUI(tag,sp,FanPaiAD::RewardType::Magic);
    }
    else
    {
        auto index = 6*100000;
        idxVec.push_back(index);

        auto animanager = UIUtils::playInnerAction(node,"Start1",false,[this,poi,node,tag](){
                isTouch = true;
                 _rewardNum--;
                
                     getNode("Button_get")->setVisible(true);
        //        if(_rewardNum == 0)
        //        {//出现按钮
        //        }
            });
            animanager->setFrameEventCallFunc([this,node,tag,sp](Frame* frame){
                 auto event = dynamic_cast<EventFrame*>(frame);
                 auto msg = event->getEvent();
                 if(msg == "game_Front")
                 {
                     updateItemUI(tag,sp,FanPaiAD::RewardType::Magic);
                 }
            });
    }
}

/*。20
 金币 / 钻石 30
 
 牌面。25
 
 牌背 / 背景。20
 
 音乐。15
 
 魔法棒。10
 
 */


void FanPaiAD::randReward(int tag,bool isAni)
{
    _tag = tag;
    
//    if(rand <= 8)
//    {
//        _RewardType[tag] = FanPaiAD::RewardType::Magic;
//        openMagic(tag,isAni);
//    }
    //分配奖励
    
    if(tag == 1)
    {//110 - 125 金币
        _RewardType[tag] = FanPaiAD::RewardType::SmallGold;
        _goldNum[tag] = random(18, 28);
        openGold(tag,isAni);
    }
    else if(tag == 2)
    {//100金币
        _RewardType[tag] = FanPaiAD::RewardType::SmallGold;
        _goldNum[tag] = random(1, 5);
        openGold(tag,isAni);
    }
    else if(tag == 3)
    {//50-75金币
        _RewardType[tag] = FanPaiAD::RewardType::SmallGold;
        _goldNum[tag] = random(8, 18);
        openGold(tag,isAni);
    }
    else if(tag == 4)
    {//100-125钻石
        _RewardType[tag] = FanPaiAD::RewardType::BigGold;
        _goldNum[tag] = random(28, 56);
        openDiamond(tag, isAni);
    }
    else if(tag == 5)
    {//75-100钻石
        _RewardType[tag] = FanPaiAD::RewardType::BigGold;
        _goldNum[tag] = random(56, 70);
        openDiamond(tag, isAni);
    }
}


void FanPaiAD::updateItemUI(int tag,Node* item,FanPaiAD::RewardType type,int index,int randNum)
{
    _tag = tag;
    _RewardType[tag] = type;
    auto Panel_69 = item->getChildByName("Panel_69");
    auto text = Panel_69->getChildByName<TextBMFont*>("BitmapFontLabel_num");
    auto Text_29 = Panel_69->getChildByName<Text*>("Text_29");
    //auto Image_75 = Panel_69->getChildByName("Image_75");
    auto gold1 = Panel_69->getChildByName("Gold1");
    auto gold0 = Panel_69->getChildByName("Gold0");
    auto Baoshi1 = Panel_69->getChildByName("Baoshi1");
    auto Baoshi0 = Panel_69->getChildByName("Baoshi0");
    gold0->setVisible(false);
    gold1->setVisible(false);
    Baoshi0->setVisible(false);
    Baoshi1->setVisible(false);
    //->setVisible(false);
    if(FanPaiAD::RewardType::BigGold == type)
    {
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->setVisible(false);
        Text_29->setString(Lang("100286"));
        
        gold1->setVisible(true);
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",_goldNum[tag]));
    }
    else if(FanPaiAD::RewardType::SmallGold == type)
    {
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->setVisible(false);
        Text_29->setString(Lang("100286"));
        
        
        gold0->setVisible(true);
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",_goldNum[tag]));
    }
    else if(FanPaiAD::RewardType::BigDiamond == type)
    {
//        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
//        card_item->setVisible(false);
//        Text_29->setString(Lang("100287"));
//
//        Baoshi1->setVisible(true);
//        text->setVisible(true);
//        text->setString(StringUtils::format("x%d",_goldNum[tag]));
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->setVisible(false);
        Text_29->setString(Lang("100286"));
        
        gold1->setVisible(true);
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",_goldNum[tag]));
    }
    else if(FanPaiAD::RewardType::SmallDiamond == type)
    {
//        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
//        card_item->setVisible(false);
//        Text_29->setString(Lang("100287"));
//
//        Baoshi0->setVisible(true);
//        text->setVisible(true);
//        text->setString(StringUtils::format("x%d",_goldNum[tag]));
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->setVisible(false);
        Text_29->setString(Lang("100286"));
        
        
        gold0->setVisible(true);
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",_goldNum[tag]));
    }
    else if(FanPaiAD::RewardType::GameBg == type)
    {
        
        SpriteFrame* frameA = nullptr;
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        if(index > 13)
        {//动态
//            auto Panel_0 = Image_75->getChildByName("Panel_0");
//            auto node = Panel_0->getChildByName(StringUtils::format("FileNode_Changjing%d",index-12));
//            node->setVisible(true);
//            ShopManager::getInstance()->changeGameBG(node,index-12);
//            Image_75->setVisible(true);
            frameA = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", index-12),"car_new_0_1.atlas");
            card_item->setVisible(false);
        }
        else
        {
            frameA = AtlasManager::getInstance()->getSF(1, 0, 0, index);
            card_item->setVisible(true);
        }
        gold0->setVisible(false);
        gold1->setVisible(false);
        Baoshi0->setVisible(false);
        Baoshi1->setVisible(false);
        
        card_item->setSpriteFrame(frameA);
        Text_29->setString("背景");
        text->setVisible(false);
    }
    else if(FanPaiAD::RewardType::CardBg == type)
    {
        auto frame = SPRITE_M->getCardBgSpriteFrame(index);
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->setVisible(true);
        card_item->setSpriteFrame(frame);
        Text_29->setString("卡背");
        text->setVisible(false);
        gold0->setVisible(false);
        gold1->setVisible(false);
        Baoshi0->setVisible(false);
        Baoshi1->setVisible(false);
    }
    else if(FanPaiAD::RewardType::CardFace == type)
    {
        auto num = randNum % 13 + 1;
        auto col = (int)(randNum / 13);
        auto frameA = SPRITE_M->getCardSpriteFrameByNumAndColor(num,col,index);
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->setVisible(true);
        card_item->setSpriteFrame(frameA);
        Text_29->setString("卡面");
        text->setVisible(false);
        gold0->setVisible(false);
        gold1->setVisible(false);
        Baoshi0->setVisible(false);
        Baoshi1->setVisible(false);
    }
    else if(FanPaiAD::RewardType::Music == type)
    {//音乐Ui_music.png
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->setSpriteFrame("Ui_music.png");
        card_item->setVisible(true);
        Text_29->setString("音乐");
        text->setVisible(false);
        gold0->setVisible(false);
        gold1->setVisible(false);
        Baoshi0->setVisible(false);
        Baoshi1->setVisible(false);
    }
    else if(FanPaiAD::RewardType::Magic == type)
    {//
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->setSpriteFrame("Magic_0.png");
        card_item->setVisible(true);
        Text_29->setString("魔法棒");
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",1));
        gold0->setVisible(false);
        gold1->setVisible(false);
        Baoshi0->setVisible(false);
        Baoshi1->setVisible(false);
    }
    
}

void FanPaiAD::setConsumptionType(FanPaiAD::ConsumptionType type)
{
    _consumptionType = type;
}

void FanPaiAD::randReward()
{//分配五个奖励
    
    vector<int> tagVec{1,2,3,4,5};
    int i = 1;
    while(i < 6)
    {
        randReward(tagVec[i-1],false);
        i++;
    }

}

void FanPaiAD::onEnter()
{
    BaseLayer::onEnter();
    UIUtils::FIRAnalyticsEventWithPrefix("LuckCoinView");
}
void FanPaiAD::onExit()
{
    BaseLayer::onExit();
    auto lobby = SCENE_M->getLobby();
    if(lobby)
    {
        lobby->openReward(false);
        lobby->isShowTop(true);
    }
    EVENT_M->removeListener("event_game_update_coin",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
    EVENT_M->removeListener("msg_game_showwin",this);
    EVENT_M->removeListener("event_game_update_fanPai",this);
}

int FanPaiAD::randRewardTag()
{
    auto rand = random(1, 1000);
    int tag = 0;
    if(rand <= 200)
    {
        tag = 1;
    }
    else if(rand <= 230)
    {
        tag = 2;
    }
    else if(rand <= 860)
    {
        tag = 3;
    }
    else if(rand <= 940)
    {
        tag = 4;
    }
    else if(rand <= 1000)
    {
        tag = 5;
    }
    return tag;
}
