//
//  FanPaiRewardView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/29.
//

#include <stdio.h>
#include "FanPaiRewardView.h"
#include "MainLobby.h"
#include "PlayerManager.h"
#include "AtlasManager.h"
#include "ShopManager.h"
#include "HomeView.h"
#include "DailyView.h"
#include "StoreView.h"
#include "DrawPropsView.h"
#include "RewardManager.h"
#include "GrowupNode.h"
#include "TaskManager.h"
#include "TeachManager.h"
//事件
#include "EventObserver.h"
#include "BoxDataManager.h"
#include "DataManager.h"
#include "SpriteManager.h"

const int goldNumArr[] = {2,3,4,10};
const string CARDITEM = "cardItem";
const string BOX = "box";
int myrandomFP (int i) { return std::rand()%i;}
const int TeachReardBGIndex = 14;

FanPaiRewardView::FanPaiRewardView(int rewardNum,FanPaiRewardView::Type type)
:BaseLayer("2020Draw.csb")
,_rewardNum(rewardNum)
,_type(type)
,isPorp(false)
,isChongFu(true)
,randFiveTagNum(-1)
{
    
    fivePumpNum = GETINTEGER("fivePumpNum",0);
    isThreeReward  = GETBOOL("isThreeReward",true);
    teachBGGetCNT = GETINTEGER("teachBGGetCNT", DATA_M->getShopItemStatus(1, TeachReardBGIndex)?1:0);
}

FanPaiRewardView::~FanPaiRewardView()
{
    
}

void FanPaiRewardView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    FileNode_reward = getNode("FileNode_1");
    
    updateUI();
}
void FanPaiRewardView::initData()
{
    BaseLayer::initData();
    setName("FanPaiRewardView");
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
    
    _rewardFuncMap = {
        {(int)RewardType::BigGold, CC_CALLBACK_1(FanPaiRewardView::openGold, this)},
        {(int)RewardType::SmallGold, CC_CALLBACK_1(FanPaiRewardView::openGold, this)},
        {(int)RewardType::BigDiamond, CC_CALLBACK_1(FanPaiRewardView::openDiamond, this)},
        {(int)RewardType::SmallDiamond, CC_CALLBACK_1(FanPaiRewardView::openDiamond, this)},
        {(int)RewardType::CardBg, CC_CALLBACK_1(FanPaiRewardView::openCardBgAni, this)},
        {(int)RewardType::CardFace, CC_CALLBACK_1(FanPaiRewardView::openCardFaceAni, this)},
        {(int)RewardType::Music, CC_CALLBACK_1(FanPaiRewardView::openMusicAni, this)},
        {(int)RewardType::Magic, CC_CALLBACK_1(FanPaiRewardView::openMagic, this)},
        {(int)RewardType::GameBg, CC_CALLBACK_1(FanPaiRewardView::openGameBgAni, this)},
    };
}

void FanPaiRewardView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn||!isTouch)return;
    auto name = btn->getName();
    if(name == "Button_get")
    {
        bool isProp = false;
        auto lobby = SCENE_M->getLobby();
        if(!idxVec.empty())
        {
            isProp = true;
            auto type = (int)_type;
            SCENE_M->addDialog(DrawPropsView::createLayerN(idxVec,(DrawPropsView::ViewType)type));
        }
        else
        {
            lobby->showGuide();
        }
        
        vector<int> vec;
        for(auto id:idxVec)
        {
            auto is = (id/10000000) == 1;
            if(!is)
            {//true是已拥有
                vec.push_back(id);
            }
        }
        
        DATA_M->setPropNew(vec);
        
        lobby->updataBagNew();
        TEACH_M->nextTeachStep(lobby);
        fangCuo = -1;
        //SCENE_M->removeLayer(this);
        if(lobby)
        {
            lobby->isShowTop(true);
            lobby->openReward(false);
        }
        this->setVisible(false);
    }
    else if(name == "Panel_get")
    {//开启二段动画
        //isTouch = true;
        _openNum--;
        auto tag = btn->getTag();
        
        randReward(tag);
        //openCardFace(tag);
        //openGameBg(tag);
        //openCardBg(tag);
        //openMusic(tag);
        //openMagic(tag);
        btn->setEnabled(false);
    }
    else if(name == "Button_open")
    {//从前到后依次翻开
        float time = 0;
        vector<int>::iterator it = _openIdVec.begin();
        while(it != _openIdVec.end())
        {
            auto id = *it;
            auto node = getNode(StringUtils::format("FileNode_%d",id));
            auto sp = node->getChildByName<Sprite*>("card_bg_0_1");
            auto button = sp->getChildByTag<Button*>(id);
            if(button->isEnabled())
            {
                auto node = Node::create();
                this->addChild(node);
                auto func = CallFunc::create([this,id](){
                    randReward(id);
                    //openCardFace(id);
                });
                auto delay = DelayTime::create(time);
                auto removeS = RemoveSelf::create();
                auto seq = Sequence::create(delay,func,removeS, NULL);
                node->runAction(seq);
                button->setEnabled(false);
                it = _openIdVec.erase(it);
                time += 0.05;
            }
            else
            {
                it++;
            }
            
        }
        hideOpenBtn();
    }
}

int FanPaiRewardView::randGoldNum()
{
    auto rand = random(0,100);
    int id = 0;
    if(rand < 25)
    {
        id = 3;
    }
    else if(rand < 50)
    {
        id = 2;
    }
    else if(rand < 75)
    {
        id = 1;
    }
    else if(rand < 100)
    {
        id = 0;
    }
    
    if(id != -1)
    {
        return goldNumArr[id];
    }
    
}

void FanPaiRewardView::showCompletedBtn()
{
    getNode("Button_get")->setVisible(true);
    getNode<Button*>("Button_get")->setEnabled(true);
    getNode("Button_open")->setVisible(false);//防错如果没有隐藏就隐藏
    TEACH_M->nextTeachStep(this);
}

void FanPaiRewardView::hideOpenBtn()
{//翻到最后一张牌时隐藏一键翻开按钮
    getNode("Button_open")->setVisible(false);
}

void FanPaiRewardView::openGold(int tag)
{
    _tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    
    if(_rewardType[tag] == FanPaiRewardView::RewardType::BigGold)
    {
        SOUND_M->playEffectMusic(EffectCrown);
    }
    
    auto animanager = UIUtils::playAction(node,_rewardType[tag] == FanPaiRewardView::RewardType::BigGold?"Start1":"Start",false,[this,tag,poi](){
        isTouch = true;
        _rewardNum--;
        if(_rewardNum == 0)
        {//出现按钮
            showCompletedBtn();
        }
        auto coinNum = _goldNum[tag];
        //出现金币
        auto lobby = SCENE_M->getLobby();
        lobby->goldAni(_goldNum[tag],this,poi,[lobby,this,coinNum](){
            DATA_M->setCoinNum(coinNum,true, 117);
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
                auto img_icon_gold = this->getNode("img_icon_top_gold");
                auto FileNode_gold = this->getNode("FileNode_gold");
                img_icon_gold->setVisible(false);//(!isPlay);
                FileNode_gold->setVisible(true);
                UIUtils::playInnerAction(FileNode_gold,"Gold",false);
            }
            else
            {
                lobby->playGoldAni(1, true);
            }
            
        },[lobby,this](){
            //home
            //SOUND_M->playEffectMusic(EffectGetCoin);
            if(fangCuo == 10)
            {
                auto img_icon_gold = this->getNode("img_icon_top_gold");
                auto FileNode_gold = this->getNode("FileNode_gold");
                img_icon_gold->setVisible(true);//(!isPlay);
                FileNode_gold->setVisible(false);
            }
            else
            {
                lobby->playGoldAni(1, false);
            }
            
        });
    });
    
    animanager->setFrameEventCallFunc([this,node,tag](Frame* frame){
        auto event = dynamic_cast<EventFrame*>(frame);
        auto msg = event->getEvent();
        if(msg == "game_Front")
        {
            //auto frame = SPRITE_M->getCardSpriteFrameByNumAndColor(1,0,0);
            auto sp = node->getChildByName<Sprite*>("card_bg_0_1");
            
            if(_type == FanPaiRewardView::Type::Home)
            {
                
            }
            else if(_type == FanPaiRewardView::Type::Daily)
            {
                
            }
            else
            {
               
            }
            
            updateItemUI(tag,sp,_rewardType[tag]);
        }
    });
    
}

void FanPaiRewardView::openDiamond(int tag)
{
    openGold(tag);
    
//    _tag = tag;
//    auto node = getNode(StringUtils::format("FileNode_%d",tag));
//    auto poi = node->getPosition();
//    poi = node->getParent()->convertToWorldSpace(poi);
//
//    if(_rewardType[tag] == FanPaiRewardView::RewardType::BigDiamond)
//    {
//        SOUND_M->playEffectMusic(EffectCrown);
//    }
//
//
//    auto animanager = UIUtils::playAction(node,_rewardType[tag] == FanPaiRewardView::RewardType::BigDiamond?"Start1":"Start",false,[this,tag,poi](){
//        isTouch = true;
//        _rewardNum--;
//        if(_rewardNum == 0)
//        {//出现按钮
//            showCompletedBtn();
//        }
//        //出现金币
//        auto diamondNum = _goldNum[tag];
//        auto lobby = SCENE_M->getLobby();
//        lobby->diamondAni(_goldNum[tag],this,poi,[lobby,this,diamondNum](){
//            DATA_M->setDiamond(diamondNum,true);
//            ValueMap valueMap{
//                {"isTime",Value{true}}
//            };
//            //更新有金币显示
//            EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//        },[lobby,this](){
//            //home
//            //SOUND_M->playEffectMusic(EffectGetGem);
//            if(fangCuo == 10)
//            {
//                auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                auto FileNode_diamond = this->getNode("FileNode_diamond");
//                img_icon_diamond->setVisible(false);//(!isPlay);
//                FileNode_diamond->setVisible(true);
//
//                UIUtils::playInnerAction(FileNode_diamond,"Baoshi",false);
//            }
//            else
//            {
//                SCENE_M->getLobby()->playDiamondAni(1, true);
//            }
//        },[lobby,this](){
//            //home
//            //SOUND_M->playEffectMusic(EffectGetGem);
//            if(fangCuo == 10)
//            {
//                auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                auto FileNode_diamond = this->getNode("FileNode_diamond");
//                img_icon_diamond->setVisible(true);//(!isPlay);
//                FileNode_diamond->setVisible(false);
//            }
//            else
//            {
//                SCENE_M->getLobby()->playDiamondAni(1, false);
//            }
//        });
//    });
//
//
//    animanager->setFrameEventCallFunc([this,node,tag](Frame* frame){
//        auto event = dynamic_cast<EventFrame*>(frame);
//        auto msg = event->getEvent();
//        if(msg == "game_Front")
//        {
//            //auto frame = SPRITE_M->getCardSpriteFrameByNumAndColor(1,0,0);
//            auto sp = node->getChildByName<Sprite*>("card_bg_0_1");
//            if(_type == FanPaiRewardView::Type::Home)
//            {
//                //randHome(tag);
//            }
//            else if(_type == FanPaiRewardView::Type::Daily)
//            {
//                //randDaily(tag);
//            }
//            else
//            {
//
//            }
//            updateItemUI(tag,sp,_rewardType[tag]);
//        }
//    });
}

void FanPaiRewardView::updateUI()
{
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<Text*>("Text_13")->setString(Lang("100064"));
    auto Text_open = getNode<Text*>("Text_open");
    Text_open->setString(Lang("100323"));
    UIUtils::textAdaptiveSize(Text_open,420);
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    
    updateCoin();
    updateDiamond();
}

void FanPaiRewardView::updateCoin(bool isDelay)
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
        text->addChild(grouwup,0,88);
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

void FanPaiRewardView::updateDiamond(bool isDelay)
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
//
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
//        text->addChild(grouwup,0,88);
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

void FanPaiRewardView::openCardBg(int tag)
{
    _tag = tag;
   
    int idx = 0;
    
    auto rand = random(1, 100);
    
    auto randCF2 = 0;
    if(_consumptionType == ConsumptionType::Gold)
    {//金币箱子。
        auto num = DATA_M->getCoinNum();
        if(num <= 10000)
        {
            randCF2 = 25;
        }
        else
        {
            randCF2 = 30;
        }
    }
    else if(_consumptionType == ConsumptionType::Diamond)
    {//钻石箱子。
//        auto num = DATA_M->getDiamond();
//        if(num <= 10000)
//        {
//            if(_rewardTempNum == 1)
//            {
//                randCF2 = 20;
//            }
//            else if(_rewardTempNum == 5)
//            {
//                randCF2 = 25;
//            }
//        }
//        else
//        {
//            if(_rewardTempNum == 1)
//            {
//                randCF2 = 25;
//            }
//            else if(_rewardTempNum == 5)
//            {
//                randCF2 = 30;
//            }
//        }
        
    }
    
    if(rand <= randCF2&&isChongFu)
    {
        isChongFu = false;
        idx = 0;
    }
    else
    {
        isChongFu = true;
        vector<int> randVec;
        
        for(int i = 0;i<CARD_BG_NUM;++i)
        {
            randVec.push_back(i);
        }
        std::random_shuffle(randVec.begin(), randVec.end(), myrandomFP);
        int i = 0;
        while (i<CARD_BG_NUM) {
            
            idx = randVec.at(i);
            auto isBuy = DATA_M->getShopItemStatus(3,idx);
            if(!isBuy)
            {
                break;
            }
            i++;
        }
    }
    
    
    if(fivePumpNum == -1)
    {//给一个牌背。idx=3
        fivePumpNum = -2;
        idx = 3;
    }
    
    _itemIdx[tag] = idx;
    openCardBgAni(tag);
}

void FanPaiRewardView::openCardBgAni(int tag)
{
    _tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    int idx = _itemIdx[tag];
    auto frameA = SPRITE_M->getCardBgSpriteFrame(idx);
        auto sp = Sprite::createWithSpriteFrame(frameA);
        sp->setVisible(false);
        this->addChild(sp);
        sp->setPosition(poi);
        sp->setRotation(node->getRotation());
        sp->setScale(node->getScale());
        auto isBuy = DATA_M->getShopItemStatus(3,idx);
        DATA_M->unLockShopItemStatus(3,idx);
    //金币是1000000。钻石是2000000
    auto index = 3*100000 + idx*1000 + (_consumptionType == ConsumptionType::Gold?1000000:2000000) + (isBuy?10000000:20000000);
        if(!isBuy||1)
        {//重复也发送弹窗
            idxVec.push_back(index);
            SOUND_M->playEffectMusic(EffectCrown);
        }
        
        
        
    auto animanager = UIUtils::playAction(node,"Start1",false,[this,poi,isBuy,sp,node,tag](){
        isTouch = true;
        _rewardNum--;
        if(_rewardNum == 0)
        {//出现按钮
            showCompletedBtn();
        }
        if(isBuy&&0)
        {
            auto lobby = SCENE_M->getLobby();
            //出现金币
            if(_consumptionType == ConsumptionType::Gold)
            {
                auto coinNum = _goldNum[tag];
                lobby->goldAni(_goldNum[tag],this,poi,[lobby,this,coinNum](){
                    DATA_M->setCoinNum(coinNum, true, 118);
                    ValueMap valueMap{
                        {"isTime",Value{true}}
                    };
                    //更新有金币显示
                    EVENT_M->sendEvent("event_game_update_coin",valueMap);
                },[lobby,this](){
                    //home
                    if(fangCuo == 10)
                    {
                        lobby->playGoldAni(1,true);
                    }
                    else
                    {
                        lobby->playGoldAni(1,true);
                    }
                    //SOUND_M->playEffectMusic(EffectGetCoin);
                    
                },[lobby,this](){
                    //home
                    //SOUND_M->playEffectMusic(EffectGetCoin);
                    if(fangCuo == 10)
                    {
                        lobby->playGoldAni(1,false);
                    }
                    else
                    {
                        lobby->playGoldAni(1,false);
                    }
                    
                });
            }
//            else if(_consumptionType == ConsumptionType::Diamond)
//            {
//                auto diamondNum = _goldNum[tag];
//                lobby->diamondAni(_goldNum[tag],this,poi,[lobby,this,diamondNum](){
//                    DATA_M->setDiamond(diamondNum);
//                    ValueMap valueMap{
//                        {"isTime",Value{true}}
//                    };
//                    //更新有金币显示
//                    EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//                },[lobby,this](){
//                    //home
//                    if(fangCuo == 10)
//                    {
//                        auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                        auto FileNode_diamond = this->getNode("FileNode_diamond");
//                        img_icon_diamond->setVisible(false);//(!isPlay);
//                        FileNode_diamond->setVisible(true);
//                        UIUtils::playInnerAction(FileNode_diamond,"Baoshi",false);
//                    }
//                    else
//                    {
//                        lobby->playDiamondAni(1,true);
//                    }
//                    //SOUND_M->playEffectMusic(EffectGetGem);
//
//                },[lobby,this](){
//                    //home
//                    //SOUND_M->playEffectMusic(EffectGetGem);
//                    if(fangCuo == 10)
//                    {
//                        auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                        auto FileNode_diamond = this->getNode("FileNode_diamond");
//                        img_icon_diamond->setVisible(true);//(!isPlay);
//                        FileNode_diamond->setVisible(false);
//                    }
//                    else
//                    {
//                        lobby->playDiamondAni(1,false);
//                    }
//                });
//            }
        }
        else
        {//卡牌飞出
            
        }
    });
    
    
    animanager->setFrameEventCallFunc([this,sp,idx,node,isBuy,tag](Frame* frame){
        auto event = dynamic_cast<EventFrame*>(frame);
        auto msg = event->getEvent();
        if(msg == "game_Front")
        {
            auto card_bg_0_1 = node->getChildByName<Sprite*>("card_bg_0_1");
            //sp->setVisible(!isBuy);
            if(isBuy&&0)
            {//金币70
                _goldNum[tag] = 70;
                if(_consumptionType == ConsumptionType::Gold)
                {//金币箱子。
                    updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::BigGold);
                }
                else if(_consumptionType == ConsumptionType::Diamond)
                {//钻石箱子。
                    updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::BigDiamond);
                }
            }
            else
            {
                updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::CardBg,idx);
            }
        }
    });
}

void FanPaiRewardView::openGameBg(int tag, int teachUnlockIdx)
{
    _tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    
    auto rand = random(1, 100);
    auto randCF2 = 0;
    if(_consumptionType == ConsumptionType::Gold)
    {//金币箱子。
        //randCF2 = 20;
    }
    else if(_consumptionType == ConsumptionType::Diamond)
    {//钻石箱子。
        
//        auto num = DATA_M->getDiamond();
//        if(num <= 10000)
//        {
//            if(_rewardTempNum == 1)
//            {
//                randCF2 = 20;
//            }
//            else if(_rewardTempNum == 5)
//            {
//                randCF2 = 25;
//            }
//        }
//        else
//        {
//            if(_rewardTempNum == 1)
//            {
//                randCF2 = 25;
//            }
//            else if(_rewardTempNum == 5)
//            {
//                randCF2 = 30;
//            }
//        }
        
    }
    
    int idx = 0;
    if(rand < randCF2&&isChongFu)
    {//重复
        isChongFu = false;
        idx = 0;
    }
    else
    {
        isChongFu = true;
        vector<int> randVec;
        
        for(int i = 0;i<GAME_BG_NUM;++i)
        {
            randVec.push_back(i);
        }
        if (teachUnlockIdx == -1)
            std::random_shuffle(randVec.begin(), randVec.end(), myrandomFP);
        int i = teachUnlockIdx==-1?0:teachUnlockIdx;
        while (i<GAME_BG_NUM) {
            idx = randVec.at(i);
            auto isBuy = DATA_M->getShopItemStatus(1,idx);
            if(!isBuy)
            {
                break;
            }
            i++;
        }
    }
    _itemIdx[tag] = idx;
    openGameBgAni(tag);
}

void FanPaiRewardView::openGameBgAni(int tag)
{
    _tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    
    int idx = _itemIdx[tag]; // 道具idx
    SpriteFrame* frameA = nullptr;
        if(idx > 13)
        {//动态
            if(idx<=16)
            {
                frameA = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", 14-12),"car_new_0_1.atlas");
            }
            else
            {
                frameA = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", idx-14),"car_new_0_1.atlas");
            }
            //frameA = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", idx-12),"car_new_0_1.atlas");
        }
        else
        {
            frameA = AtlasManager::getInstance()->getSF(1, 0, 0, idx);
        }
        auto sp = Sprite::createWithSpriteFrame(frameA);
        sp->setVisible(false);
        this->addChild(sp);
        sp->setPosition(poi);
        sp->setRotation(node->getRotation());
        sp->setScale(node->getScale());
        auto isBuy = DATA_M->getShopItemStatus(1,idx);
        DATA_M->unLockShopItemStatus(1,idx);
        auto index = 1*100000 + idx*1000 + (_consumptionType == ConsumptionType::Gold?1000000:2000000) + (isBuy?10000000:20000000);;
        if(!isBuy||1)
        {
            idxVec.push_back(index);
            SOUND_M->playEffectMusic(EffectCrown);
        }
         
    auto animanager = UIUtils::playAction(node,"Start1",false,[this,poi,isBuy,sp,node,tag](){
        isTouch = true;
         _rewardNum--;
        if(_rewardNum == 0)
        {//出现按钮
            showCompletedBtn();
        }
        if(isBuy&&0)
        {
             auto lobby = SCENE_M->getLobby();
             //出现金币
             if(_consumptionType == ConsumptionType::Gold)
             {
                 auto coinNum = _goldNum[tag];
                 lobby->goldAni(_goldNum[tag],this,poi,[lobby,this,coinNum](){
                     DATA_M->setCoinNum(coinNum, true, 119);
                     ValueMap valueMap{
                         {"isTime",Value{true}}
                     };
                     //更新有金币显示
                     EVENT_M->sendEvent("event_game_update_coin",valueMap);
                 },[lobby,this](){
                     //home
                     if(fangCuo == 10)
                     {
                         lobby->playGoldAni(1,true);
                     }
                     else
                     {
                         lobby->playGoldAni(1,true);
                     }
                     //SOUND_M->playEffectMusic(EffectGetCoin);
                     
                 },[lobby,this](){
                     //home
                     //SOUND_M->playEffectMusic(EffectGetCoin);
                     if(fangCuo == 10)
                     {
                         lobby->playGoldAni(1,false);
                     }
                     else
                     {
                         lobby->playGoldAni(1,false);
                     }
                     
                 });
             }
//             else if(_consumptionType == ConsumptionType::Diamond)
//             {
//                 auto diamondNum = _goldNum[tag];
//                 lobby->diamondAni(_goldNum[tag],this,poi,[lobby,this,diamondNum](){
//                     DATA_M->setDiamond(diamondNum);
//                     ValueMap valueMap{
//                         {"isTime",Value{true}}
//                     };
//                     //更新有金币显示
//                     EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//                 },[lobby,this](){
//                     //home
//                     if(fangCuo == 10)
//                     {
//                         auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                         auto FileNode_diamond = this->getNode("FileNode_diamond");
//                         img_icon_diamond->setVisible(false);//(!isPlay);
//                         FileNode_diamond->setVisible(true);
//                         UIUtils::playInnerAction(FileNode_diamond,"Baoshi",false);
//                     }
//                     else
//                     {
//                         lobby->playDiamondAni(1,true);
//                     }
//                     //SOUND_M->playEffectMusic(EffectGetGem);
//
//                 },[lobby,this](){
//                     //home
//                     //SOUND_M->playEffectMusic(EffectGetGem);
//                     if(fangCuo == 10)
//                     {
//                         auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                         auto FileNode_diamond = this->getNode("FileNode_diamond");
//                         img_icon_diamond->setVisible(true);//(!isPlay);
//                         FileNode_diamond->setVisible(false);
//                     }
//                     else
//                     {
//                         lobby->playDiamondAni(1,false);
//                     }
//                 });
//             }
        }
        else
        {//卡牌飞出
             
        }
    });
    
    
    animanager->setFrameEventCallFunc([this,sp,idx,node,isBuy,tag](Frame* frame){
         auto event = dynamic_cast<EventFrame*>(frame);
         auto msg = event->getEvent();
         if(msg == "game_Front")
         {
             auto card_bg_0_1 = node->getChildByName<Sprite*>("card_bg_0_1");
             if(isBuy&&0)
             {//金币50
                 _goldNum[tag] = 70;
                 if(_consumptionType == ConsumptionType::Gold)
                 {//金币箱子。
                     updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::BigGold);
                 }
                 else if(_consumptionType == ConsumptionType::Diamond)
                 {//钻石箱子。
                     updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::BigDiamond);
                 }
             }
             else
             {
                 updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::GameBg,idx);
             }
         }
    });
    if(_rewardNum == 1)
    {//翻到了最后一个隐藏open按钮
        hideOpenBtn();
    }
}

void FanPaiRewardView::openCardFace(int tag)
{
    _tag = tag;
    auto idx1 = DATA_M->getCardFace();
    auto randCF = random(1, 100);
    auto idx = 0;
    auto randNum = 0;
    
    auto randCF2 = 0;
    if(_consumptionType == ConsumptionType::Gold)
    {//金币箱子。
        auto num = DATA_M->getCoinNum();
        if(num <= 10000)
        {
            randCF2 = 15;
        }
        else
        {
            if(_rewardTempNum == 5)
            {
                randCF2 = 20;
            }
            else
            {
                randCF2 = 25;
            }
        }
        
    }
    else if(_consumptionType == ConsumptionType::Diamond)
    {//钻石箱子。
//        auto num = DATA_M->getDiamond();
//
//        if(num <= 10000)
//        {
//            if(_rewardTempNum == 1)
//            {
//                randCF2 = 15;
//            }
//            else if(_rewardTempNum == 5)
//            {
//                randCF2 = 15;
//            }
//        }
//        else
//        {
//            if(_rewardTempNum == 1)
//            {
//                randCF2 = 20;
//            }
//            else if(_rewardTempNum == 5)
//            {
//                randCF2 = 20;
//            }
//        }
        
    }
    
    if(randCF <= randCF2&&isChongFu)
    {//重复
        isChongFu = false;
        idx = 0;
        randNum = 0;
    }
    else
    {//不重复
        isChongFu = true;
        vector<int> randVec;
        for(auto i = 0;i<52;++i)
        {
            randVec.push_back(i);
        }
        std::random_shuffle(randVec.begin(), randVec.end(), myrandomFP);
        if(idx1 == CARD_FACE_NUM-1)
        {//到最后一个了，
            
        }
        int i = 0;
        while (i<52) {
            idx = random(idx1, CARD_FACE_NUM-1);
            randNum = randVec.at(i);
            auto isBuy = DATA_M->getCardFaceStatus(2,idx,randNum);
            if(!isBuy)
            {
                break;
            }
            i++;
        }
    }
    _itemIdx[tag] = idx;
    _goldNum[tag] = randNum; // 暂时借用下数量 保存某张牌的idx

    openCardFaceAni(tag);
}

void FanPaiRewardView::openCardFaceAni(int tag)
{
    _tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    
    int idx = _itemIdx[tag];
    int randNum = _goldNum[tag];
    auto num = randNum % 13 + 1;
    auto col = (int)(randNum / 13);
    
    SpriteFrame* frameA = SPRITE_M->getCardSpriteFrameByNumAndColor(num,col,idx);
    
    auto sp = Sprite::createWithSpriteFrame(frameA);
    sp->setVisible(false);
    this->addChild(sp);
    sp->setPosition(poi);
    sp->setRotation(node->getRotation());
    sp->setScale(node->getScale());
    auto isBuy = DATA_M->getCardFaceStatus(2,idx,randNum);
    DATA_M->unLockShopItemStatus(2,idx,randNum);
    auto index = 2*100000 + idx*1000 + randNum + (_consumptionType == ConsumptionType::Gold?1000000:2000000) + (isBuy?10000000:20000000);;
    if(!isBuy||1)
    {
        idxVec.push_back(index);
        SOUND_M->playEffectMusic(EffectCrown);
    }
     
    auto animanager = UIUtils::playAction(node,"Start1",false,[this,poi,isBuy,sp,node,tag](){
        isTouch = true;
         _rewardNum--;
        if(_rewardNum == 0)
        {//出现按钮
            showCompletedBtn();
        }
        if(isBuy&&0)
        {
             auto lobby = SCENE_M->getLobby();
             //出现金币
             if(_consumptionType == ConsumptionType::Gold)
             {
                 auto coinNum = _goldNum[tag];
                 lobby->goldAni(_goldNum[tag],this,poi,[lobby,this,coinNum](){
                     DATA_M->setCoinNum(coinNum, true, 120);
                     ValueMap valueMap{
                         {"isTime",Value{true}}
                     };
                     //更新有金币显示
                     EVENT_M->sendEvent("event_game_update_coin",valueMap);
                     
                 },[lobby,this](){
                     //home
                     if(fangCuo == 10)
                     {
                         lobby->playGoldAni(1,true);
                     }
                     else
                     {
                         lobby->playGoldAni(1,true);
                     }
                     //SOUND_M->playEffectMusic(EffectGetCoin);
                     
                 },[lobby,this](){
                     //home
                     //SOUND_M->playEffectMusic(EffectGetCoin);
                     if(fangCuo == 10)
                     {
                         lobby->playGoldAni(1,false);
                     }
                     else
                     {
                         lobby->playGoldAni(1,false);
                     }
                     
                 });
             }
//             else if(_consumptionType == ConsumptionType::Diamond)
//             {
//                 auto diamondNum = _goldNum[tag];
//                 lobby->diamondAni(_goldNum[tag],this,poi,[lobby,this,diamondNum](){
//                     DATA_M->setDiamond(diamondNum);
//                     ValueMap valueMap{
//                         {"isTime",Value{true}}
//                     };
//                     //更新有金币显示
//                     EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//                 },[lobby,this](){
//                     //home
//                     if(fangCuo == 10)
//                     {
//                         auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                         auto FileNode_diamond = this->getNode("FileNode_diamond");
//                         img_icon_diamond->setVisible(false);//(!isPlay);
//                         FileNode_diamond->setVisible(true);
//                         UIUtils::playInnerAction(FileNode_diamond,"Baoshi",false);
//                     }
//                     else
//                     {
//                         lobby->playDiamondAni(1,true);
//                     }
//                     //SOUND_M->playEffectMusic(EffectGetGem);
//
//                 },[lobby,this](){
//                     //home
//                     //SOUND_M->playEffectMusic(EffectGetGem);
//                     if(fangCuo == 10)
//                     {
//                         auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                         auto FileNode_diamond = this->getNode("FileNode_diamond");
//                         img_icon_diamond->setVisible(true);//(!isPlay);
//                         FileNode_diamond->setVisible(false);
//                     }
//                     else
//                     {
//                         lobby->playDiamondAni(1,false);
//                     }
//                 });
//             }
        }
        else
        {//卡牌飞出
             
        }
    });
    
    
    animanager->setFrameEventCallFunc([this,sp,idx,num,col,node,isBuy,randNum,tag](Frame* frame){
         auto event = dynamic_cast<EventFrame*>(frame);
         auto msg = event->getEvent();
         if(msg == "game_Front")
         {
             auto card_bg_0_1 = node->getChildByName<Sprite*>("card_bg_0_1");
             if(isBuy&&0)
             {//金币50
                _goldNum[tag] = 70;
                if(_consumptionType == ConsumptionType::Gold)
                {//金币箱子。
                    updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::BigGold);
                }
                else if(_consumptionType == ConsumptionType::Diamond)
                {//钻石箱子。
                    updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::BigDiamond);
                }
             }
             else
             {
                 
                 updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::CardFace,idx,randNum);
             }
         }
    });
}

void FanPaiRewardView::openMusic(int tag)
{//音乐
    _tag = tag;
    
    
    auto rand = random(1, 100);
    auto randCF2 = 0;
    if(_consumptionType == ConsumptionType::Gold)
    {//金币箱子。
        //randCF2 = 20;
    }
    else if(_consumptionType == ConsumptionType::Diamond)
    {//钻石箱子。
        
//        auto num = DATA_M->getDiamond();
//        if(num <= 10000)
//        {
//            if(_rewardTempNum == 1)
//            {
//                randCF2 = 20;
//            }
//            else if(_rewardTempNum == 5)
//            {
//                randCF2 = 25;
//            }
//        }
//        else
//        {
//            if(_rewardTempNum == 1)
//            {
//                randCF2 = 25;
//            }
//            else if(_rewardTempNum == 5)
//            {
//                randCF2 = 30;
//            }
//        }
        
    }
    
    auto randId = 0;
    if(rand < randCF2&&isChongFu)
    {//重复
        isChongFu = false;
        randId = 0;
    }
    else
    {//不重复
        isChongFu = true;
        vector<int> randVec;
        
        for(int i = 0;i<LobbyMusicTotalCNT;++i)
        {
            randVec.push_back(i);
        }
        std::random_shuffle(randVec.begin(), randVec.end(), myrandomFP);
        int i = 0;
        while (i<LobbyMusicTotalCNT) {
            randId = randVec.at(i);
            auto isBuy = DATA_M->getShopItemStatus(5,randId);
            if(!isBuy)
            {
                break;
            }
            i++;
        }
    }
    
    if(fivePumpNum == -5)
    {
        fivePumpNum = -4;
        randId = 0;
    }
    
    _itemIdx[tag] = randId;
    openMusicAni(tag);
}

void FanPaiRewardView::openMusicAni(int tag)
{
    _tag = tag;
    int randId = _itemIdx[tag];
    auto node = getNode(StringUtils::format("FileNode_%d",tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    auto isBuy = DATA_M->getShopItemStatus(5,randId);
    DATA_M->unLockShopItemStatus(5,randId);
    auto index = 5*100000 + randId*1000 + (_consumptionType == ConsumptionType::Gold?1000000:2000000) + (isBuy?10000000:20000000);
    if(!isBuy||1)
    {
        idxVec.push_back(index);
        SOUND_M->playEffectMusic(EffectCrown);
    }

    
    auto animanager = UIUtils::playAction(node,"Start1",false,[this,poi,isBuy,node,tag](){
        isTouch = true;
         _rewardNum--;
        if(_rewardNum == 0)
        {//出现按钮
            showCompletedBtn();
        }
        if(isBuy&&0)
        {
             auto lobby = SCENE_M->getLobby();
             //出现金币
             if(_consumptionType == ConsumptionType::Gold)
             {
                 auto coinNum = _goldNum[tag];
                 lobby->goldAni(_goldNum[tag],this,poi,[lobby,this,coinNum](){
                     DATA_M->setCoinNum(coinNum, true, 121);
                     ValueMap valueMap{
                         {"isTime",Value{true}}
                     };
                     //更新有金币显示
                     EVENT_M->sendEvent("event_game_update_coin",valueMap);
                 },[lobby,this](){
                     //home
                     if(fangCuo == 10)
                     {
                         lobby->playGoldAni(1,true);
                     }
                     else
                     {
                         lobby->playGoldAni(1,true);
                     }
                     //SOUND_M->playEffectMusic(EffectGetCoin);
                     
                 },[lobby,this](){
                     //home
                     //SOUND_M->playEffectMusic(EffectGetCoin);
                     if(fangCuo == 10)
                     {
                         lobby->playGoldAni(1,false);
                     }
                     else
                     {
                         lobby->playGoldAni(1,false);
                     }
                     
                 });
             }
//             else if(_consumptionType == ConsumptionType::Diamond)
//             {
//                 auto diamondNum = _goldNum[tag];
//                 lobby->diamondAni(_goldNum[tag],this,poi,[lobby,this,diamondNum](){
//                     DATA_M->setDiamond(diamondNum);
//                     ValueMap valueMap{
//                         {"isTime",Value{true}}
//                     };
//                     //更新有金币显示
//                     EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//                 },[lobby,this](){
//                     //home
//                     if(fangCuo == 10)
//                     {
//                         auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                         auto FileNode_diamond = this->getNode("FileNode_diamond");
//                         img_icon_diamond->setVisible(false);//(!isPlay);
//                         FileNode_diamond->setVisible(true);
//                         UIUtils::playInnerAction(FileNode_diamond,"Baoshi",false);
//                     }
//                     else
//                     {
//                         lobby->playDiamondAni(1,true);
//                     }
//                     //SOUND_M->playEffectMusic(EffectGetGem);
//                     
//                 },[lobby,this](){
//                     //home
//                     //SOUND_M->playEffectMusic(EffectGetGem);
//                     if(fangCuo == 10)
//                     {
//                         auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                         auto FileNode_diamond = this->getNode("FileNode_diamond");
//                         img_icon_diamond->setVisible(true);//(!isPlay);
//                         FileNode_diamond->setVisible(false);
//                     }
//                     else
//                     {
//                         lobby->playDiamondAni(1,false);
//                     }
//                 });
//             }
        }
    });
    
    animanager->setFrameEventCallFunc([this,node,isBuy,tag,randId](Frame* frame){
         auto event = dynamic_cast<EventFrame*>(frame);
         auto msg = event->getEvent();
         if(msg == "game_Front")
         {
             auto card_bg_0_1 = node->getChildByName<Sprite*>("card_bg_0_1");
             if(isBuy&&0)
             {//金币50
                _goldNum[tag] = 70;
                if(_consumptionType == ConsumptionType::Gold)
                {//金币箱子。
                    updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::BigGold);
                }
                else if(_consumptionType == ConsumptionType::Diamond)
                {//钻石箱子。
                    updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::BigDiamond);
                }
             }
             else
             {
                 updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::Music,randId);
             }
         }
    });
}

void FanPaiRewardView::openMagic(int tag)
{//魔法棒
    _tag = tag;
    auto node = getNode(StringUtils::format("FileNode_%d",tag));
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
 

    //增加一次
    REWARD_M->getReward(RewardManager::RewardType::Magic, 1);//_goldNum[tag]);
    
    auto index = 6*100000;
    index += 1;//_goldNum[tag];
    idxVec.push_back(index);
    SOUND_M->playEffectMusic(EffectCrown);

    auto animanager = UIUtils::playAction(node,"Start1",false,[this,poi,node,tag](){
        isTouch = true;
         _rewardNum--;
        if(_rewardNum == 0)
        {//出现按钮
            showCompletedBtn();
        }
    });
    
    animanager->setFrameEventCallFunc([this,node,tag](Frame* frame){
         auto event = dynamic_cast<EventFrame*>(frame);
         auto msg = event->getEvent();
         if(msg == "game_Front")
         {
             auto card_bg_0_1 = node->getChildByName<Sprite*>("card_bg_0_1");
             
             updateItemUI(tag,card_bg_0_1,FanPaiRewardView::RewardType::Magic);
         }
    });
}

void FanPaiRewardView::openMagicAni(int tag)
{
    
}

/*。20
 金币 / 钻石 30
 
 牌面。25
 
 牌背 / 背景。20
 
 音乐。15
 
 魔法棒。10
 
 */

void FanPaiRewardView::randDaily(int tag)
{//
    
    int idx = 0;
    if(tag == 4)
    {
        idx = 0;
    }
    else if(tag == 1)
    {
        idx = 1;
    }
    else if(tag == 5)
    {
        idx = 2;
    }
    
    if(crownMax == 20)
    {
        if(_randBoxVec[idx] == 4)
        {//800金币。
            _goldNum[tag] = 800;
            _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
            openGold(tag);
        }
        else if(_randBoxVec[idx] == 1)
        {//800钻石。
            _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
            _goldNum[tag] = 800;
            openDiamond(tag);
        }
        else if(_randBoxVec[idx] == 5)
        {//第三张
            _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
            _goldNum[tag] = 2;
            openMagic(tag);
        }
    }
    else if(crownMax < 6)
    {
        if(_randBoxVec[idx] == 4)
        {//2-10金币。
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randBoxVec[idx] == 1)
        {//2-10钻石。
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(2, 10);
            openDiamond(tag);
        }
        else if(_randBoxVec[idx] == 5)
        {
            auto rand = random(1, 100);
            if(rand <= 50)
            {//50-75金币
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                _goldNum[tag] = random(50, 75);
                openGold(tag);
            }
            else if(rand <= 100)
            {//50-75钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(50, 75);
                openDiamond(tag);
            }
        }
        
    }
    else if(crownMax < 20)
    {
        if(_randBoxVec[idx] == 4)
        {//2-10金币。
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randBoxVec[idx] == 1)
        {//2-10钻石。
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(2, 10);
            openDiamond(tag);
        }
        else if(_randBoxVec[idx] == 5)
        {
            auto rand = random(1, 100);
            if(rand <= 50)
            {//75-120金币
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                _goldNum[tag] = random(75, 120);
                openGold(tag);
            }
            else if(rand <= 100)
            {//75-120钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(75, 120);
                openDiamond(tag);
            }
        }
    }
    
}
void FanPaiRewardView::randHome(int tag)
{//
    
    int idx = 0;
    if(tag == 4)
    {
        idx = 0;
    }
    else if(tag == 1)
    {
        idx = 1;
    }
    else if(tag == 5)
    {
        idx = 2;
    }
    
    if(starMax < 18)
    {
        if(_randBoxVec[idx] == 4)
        {//2-10金币。
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randBoxVec[idx] == 1)
        {//2-10钻石。
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(2, 10);
            openDiamond(tag);
        }
        else if(_randBoxVec[idx] == 5)
        {
            auto rand = random(1, 100);
            if(rand <= 50)
            {//50-75金币
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                _goldNum[tag] = random(50, 75);
                openGold(tag);
            }
            else if(rand <= 100)
            {//50-75钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(50, 75);
                openDiamond(tag);
            }
        }
    }
    else if(starMax < 22)
    {
        if(_randBoxVec[idx] == 4)
        {//2-10金币。
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randBoxVec[idx] == 1)
        {//2-10钻石。
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(2, 10);
            openDiamond(tag);
        }
        else if(_randBoxVec[idx] == 5)
        {
            auto rand = random(1, 100);
            if(rand <= 50)
            {//75-120金币
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                _goldNum[tag] = random(75, 120);
                openGold(tag);
            }
            else if(rand <= 100)
            {//75-120钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(75, 120);
                openDiamond(tag);
            }
        }
    }
}

void FanPaiRewardView::randReward(int tag)
{
    if(_openNum == 0)
    {//翻到了最后一个隐藏open按钮
        hideOpenBtn();
    }
//    if ((TEACH_M->isTeaching("win_times1")||teachBGGetCNT==0) && tag==5) { // 新手引导给一个游戏背景
//        _rewardType[tag] = FanPaiRewardView::RewardType::GameBg;
//        openGameBg(tag, TeachReardBGIndex);
//        SETINTEGER("teachBGGetCNT", ++teachBGGetCNT);
//        return;
//    }
    
    if(randFiveTagNum == tag&&randFiveTagNum != -1)
    {//
//        if(fivePumpNum == 1)
//        {//第一次五连抽 // 给一个背景 idx = 3
//            //仅进来一次
//            fivePumpNum = -1;
//            openCardBg(tag);
//
//            return;
//        }
//        if(fivePumpNum >= 3)
//        {//第3次五连抽 // 给一个音乐 idx = 0
//            //仅进来一次
//            fivePumpNum = -5;
//            openMusic(tag);
//            
//            return;
//        }
    }
    
    
    /*if(_type == FanPaiRewardView::Type::Home)
    {
        randHome(tag);
    }
    else if(_type == FanPaiRewardView::Type::Daily)
    {
        randDaily(tag);
    }
    else */if(_type == FanPaiRewardView::Type::SevenGold)
    {
        int idx = 0;
        if(tag == 4)
        {
            idx = 0;
        }
        else if(tag == 1)
        {
            idx = 1;
        }
        else if(tag == 5)
        {
            idx = 2;
        }
        if(_randBoxVec[idx] == 4)
        {//100金币
            _goldNum[tag] = 30;
            _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
            openGold(tag);
        }
        else if(_randBoxVec[idx] == 1)
        {//2-20金币
            _goldNum[tag] = random(1, 5);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randBoxVec[idx] == 5)
        {//2-20钻石
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            _goldNum[tag] = random(5, 9);
            openDiamond(tag);
        }
    }
    else if(_type == FanPaiRewardView::Type::SevenDiamond)
    {
        int idx = 0;
        if(tag == 4)
        {
            idx = 0;
        }
        else if(tag == 1)
        {
            idx = 1;
        }
        else if(tag == 5)
        {
            idx = 2;
        }
        if(_randBoxVec[idx] == 4)
        {//150金币
            _goldNum[tag] = 100;
            _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
            openGold(tag);
        }
        else if(_randBoxVec[idx] == 1)
        {//2-20金币
            _goldNum[tag] = random(1, 5);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randBoxVec[idx] == 5)
        {//100-120钻石
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            _goldNum[tag] = random(5, 10);
            openDiamond(tag);
        }
    }
    else
    {
        // 使用boxData.json 来控制抽奖概率
        auto &reward = _rewardVec.back().asValueMap();
        auto type2 = (FanPaiRewardView::RewardType)reward.at("type2").asInt();
        if (_rewardFuncMap.find((int)type2) != _rewardFuncMap.end()) {
            _rewardType[tag] = type2;                                           // 奖励类型
            _itemIdx[tag] = reward.at("idx").asInt();                           // 奖励 idx
            _goldNum[tag] = type2==FanPaiRewardView::RewardType::CardFace?reward.at("randNum").asInt():reward.at("count").asInt();
            _rewardFuncMap.at((int)type2)(tag);
        }
        _rewardVec.pop_back();
    }
}

void FanPaiRewardView::randGold1(int tag)
{
    if(_rewardTempNum == 1)
    {
        auto rand = random(1, 100);
        if(rand <= 50)
        {//2-10金币
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(rand <= 95)
        {//2-10钻石
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            openDiamond(tag);
        }
        else if(rand <= 98)
        {//道具
            auto randProp = random(1, 100);
            if(randProp <= 65)
            {//扑克正面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                openCardFace(tag);
            }
            else if(randProp <= 90)
            {//o扑克背面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                openCardBg(tag);
            }
            else
            {//魔法棒
                _goldNum[tag] = 1;
                _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                openMagic(tag);
            }
        }
        else if(rand <= 100)
        {//大额金币 100-200
            _goldNum[tag] = random(100, 200);
            _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
            openGold(tag);
        }
    }
    else if(_rewardTempNum == 5)
    {
        
        if(_randVec[tag-1] == 1)
        {//金币 2-10
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 2)
        {//2-10 金币
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 3)
        {//1-10 钻石
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(1, 10);
            openDiamond(tag);
        }
        else if(_randVec[tag-1] == 4)
        {
            auto rand = random(1, 100);
            if(rand <= 2)
            {//大额 100-260 金币
                _goldNum[tag] = random(100, 260);
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                openGold(tag);
            }
            else if(rand <= 3)
            {//大额 100-260 钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(100, 260);
                openDiamond(tag);
            }
            else if(rand <= 52)
            {//小额金币 15-30
                _goldNum[tag] = random(15, 30);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石 15-30
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(15, 30);
                openDiamond(tag);
            }
        }
        else if(_randVec[tag-1] == 5)
        {
            auto rand = random(1, 100);
            
            if(rand <= 30)
            {//道具
                auto randProp = random(1, 100);
                if(randProp <= 65)
                {//正面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                    openCardFace(tag);
                }
                else if(randProp <= 90)
                {//背面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                    openCardBg(tag);
                }
                else
                {//魔法棒
                    _goldNum[tag] = 1;
                    _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                    openMagic(tag);
                }
            }
            else if(rand <= 65)
            {//小额金币1 -8
                _goldNum[tag] = random(1, 8);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石1 -8
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(1, 8);
                openDiamond(tag);
            }
        }
    }
}
void FanPaiRewardView::randGold2(int tag)
{
    if(_rewardTempNum == 1)
    {
        auto rand = random(1, 100);
        if(rand <= 50)
        {//2-10金币
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(rand <= 96)
        {//2-10钻石
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            openDiamond(tag);
        }
        else if(rand <= 98)
        {//道具
            auto randProp = random(1, 100);
            if(randProp <= 65)
            {//扑克正面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                openCardFace(tag);
            }
            else if(randProp <= 90)
            {//o扑克背面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                openCardBg(tag);
            }
            else
            {//魔法棒
                _goldNum[tag] = 1;
                _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                openMagic(tag);
            }
        }
        else if(rand <= 100)
        {//大额金币 100-200
            _goldNum[tag] = random(100, 200);
            _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
            openGold(tag);
        }
    }
    else if(_rewardTempNum == 5)
    {
        
        if(_randVec[tag-1] == 1)
        {//金币 2-10
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 2)
        {//2-10 金币
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 3)
        {//1-10 钻石
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(1, 10);
            openDiamond(tag);
        }
        else if(_randVec[tag-1] == 4)
        {
            auto rand = random(1, 100);
            if(rand <= 2)
            {//大额 100-260 金币
                _goldNum[tag] = random(100, 260);
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                openGold(tag);
            }
            else if(rand <= 3)
            {//大额 100-200 钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(100, 260);
                openDiamond(tag);
            }
            else if(rand <= 52)
            {//小额金币 15-30
                _goldNum[tag] = random(15, 30);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石 15-30
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(15, 30);
                openDiamond(tag);
            }
        }
        else if(_randVec[tag-1] == 5)
        {
            auto rand = random(1, 100);
            
            if(rand <= 25)
            {//道具
                auto randProp = random(1, 100);
                if(randProp <= 65)
                {//正面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                    openCardFace(tag);
                }
                else if(randProp <= 90)
                {//背面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                    openCardBg(tag);
                }
                else
                {//魔法棒
                    _goldNum[tag] = 1;
                    _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                    openMagic(tag);
                }
            }
            else if(rand <= 65)
            {//小额金币1 -8
                _goldNum[tag] = random(1, 8);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石1 -8
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(1, 8);
                openDiamond(tag);
            }
        }
    }
}
void FanPaiRewardView::randGold3(int tag)
{
    if(_rewardTempNum == 1)
    {
        auto rand = random(1, 100);
        if(rand <= 50)
        {//2-10金币
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(rand <= 98)
        {//2-10钻石
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            openDiamond(tag);
        }
        else if(rand <= 99)
        {//道具
            auto randProp = random(1, 100);
            if(randProp <= 65)
            {//扑克正面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                openCardFace(tag);
            }
            else if(randProp <= 90)
            {//o扑克背面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                openCardBg(tag);
            }
            else
            {//魔法棒
                _goldNum[tag] = 1;
                _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                openMagic(tag);
            }
        }
        else if(rand <= 100)
        {//大额金币 100-200
            _goldNum[tag] = random(100, 200);
            _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
            openGold(tag);
        }
    }
    else if(_rewardTempNum == 5)
    {
        
        if(_randVec[tag-1] == 1)
        {//金币 2-10
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 2)
        {//2-10 金币
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 3)
        {//1-10 钻石
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(1, 10);
            openDiamond(tag);
        }
        else if(_randVec[tag-1] == 4)
        {
            auto rand = random(1, 100);
            if(rand <= 2)
            {//大额 100-260 金币
                _goldNum[tag] = random(100, 260);
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                openGold(tag);
            }
            else if(rand <= 3)
            {//大额 100-260 钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(100, 260);
                openDiamond(tag);
            }
            else if(rand <= 52)
            {//小额金币 15-30
                _goldNum[tag] = random(15, 30);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石 15-30
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(15, 30);
                openDiamond(tag);
            }
        }
        else if(_randVec[tag-1] == 5)
        {
            auto rand = random(1, 100);
            
            if(rand <= 10)
            {//道具
                auto randProp = random(1, 100);
                if(randProp <= 65)
                {//正面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                    openCardFace(tag);
                }
                else if(randProp <= 90)
                {//背面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                    openCardBg(tag);
                }
                else
                {//魔法棒
                    _goldNum[tag] = 1;
                    _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                    openMagic(tag);
                }
            }
            else if(rand <= 60)
            {//小额金币1 -8
                _goldNum[tag] = random(1, 8);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石1 -8
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(1, 8);
                openDiamond(tag);
            }
        }
    }
}
void FanPaiRewardView::randDiamond1(int tag)
{
    if(_rewardTempNum == 1)
    {
        auto rand = random(1, 100);
        if(rand <= 45)
        {//小额金币 2-10
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(rand <= 95)
        {//小额钻石 2-10
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(2, 10);
            openDiamond(tag);
        }
        else if(rand <= 98)
        {//道具
            auto randProp = random(1, 100);
            if(randProp <= 35)
            {//正面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                openCardFace(tag);
            }
            else if(randProp <= 55)
            {//背面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                openCardBg(tag);
            }
            else if(randProp <= 60)
            {//魔法棒
                _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                _goldNum[tag] = 1;
                openMagic(tag);
            }
            else if(randProp <= 80)
            {//背景
                _rewardType[tag] = FanPaiRewardView::RewardType::GameBg;
                openGameBg(tag);
            }
            else if(randProp <= 100)
            {//音乐
                _rewardType[tag] = FanPaiRewardView::RewardType::Music;
                openMusic(tag);
            }
        }
        else if(rand <= 100)
        {//大额金币100-200
            _goldNum[tag] = random(100, 200);
            _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
            openDiamond(tag);
        }
        
    }
    else if(_rewardTempNum == 5)
    {
        
        if(_randVec[tag-1] == 1)
        {//金币 2-10
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 2)
        {//2-10 金币
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 3)
        {//1-10 钻石
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(1, 10);
            openDiamond(tag);
        }
        else if(_randVec[tag-1] == 4)
        {
            auto rand = random(1, 100);
            if(rand <= 2)
            {//大额 200-600 金币
                _goldNum[tag] = random(200, 600);
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                openGold(tag);
            }
            else if(rand <= 3)
            {//大额 200-600 钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(200, 600);
                openDiamond(tag);
            }
            else if(rand <= 52)
            {//小额金币 100-150
                _goldNum[tag] = random(100, 150);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石 100-150
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(100, 150);
                openDiamond(tag);
            }
        }
        else if(_randVec[tag-1] == 5)
        {
            auto rand = random(1, 100);
            
            if(rand <= 35)
            {//道具
                auto randProp = random(1, 100);
                if(randProp <= 35)
                {//正面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                    openCardFace(tag);
                }
                else if(randProp <= 55)
                {//背面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                    openCardBg(tag);
                }
                else if(randProp <= 60)
                {//魔法棒
                    _goldNum[tag] = 1;
                    _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                    openMagic(tag);
                }
                else if(randProp <= 80)
                {//背景
                    _rewardType[tag] = FanPaiRewardView::RewardType::GameBg;
                    openGameBg(tag);
                }
                else if(randProp <= 100)
                {//音乐
                    _rewardType[tag] = FanPaiRewardView::RewardType::Music;
                    openMusic(tag);
                }
            }
            else if(rand <= 70)
            {//小额金币1-8
                _goldNum[tag] = random(1, 8);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石1-8
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(1, 8);
                openDiamond(tag);
            }
        }
    }
}
void FanPaiRewardView::randDiamond2(int tag)
{
    if(_rewardTempNum == 1)
    {
        auto rand = random(1, 100);
        if(rand <= 46)
        {//小额金币 2-10
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(rand <= 50)
        {//小额钻石 2-10
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(2, 10);
            openDiamond(tag);
        }
        else if(rand <= 98)
        {//道具
            auto randProp = random(1, 100);
            if(randProp <= 35)
            {//正面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                openCardFace(tag);
            }
            else if(randProp <= 55)
            {//背面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                openCardBg(tag);
            }
            else if(randProp <= 60)
            {//魔法棒
                _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                _goldNum[tag] = 1;
                openMagic(tag);
            }
            else if(randProp <= 80)
            {//背景
                _rewardType[tag] = FanPaiRewardView::RewardType::GameBg;
                openGameBg(tag);
            }
            else if(randProp <= 100)
            {//音乐
                _rewardType[tag] = FanPaiRewardView::RewardType::Music;
                openMusic(tag);
            }
        }
        else if(rand <= 100)
        {//大额金币100-200
            _goldNum[tag] = random(100, 200);
            _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
            openDiamond(tag);
        }
        
    }
    else if(_rewardTempNum == 5)
    {
        
        if(_randVec[tag-1] == 1)
        {//金币 2-10
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 2)
        {//2-10 金币
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 3)
        {//1-10 钻石
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(1, 10);
            openDiamond(tag);
        }
        else if(_randVec[tag-1] == 4)
        {
            auto rand = random(1, 100);
            if(rand <= 3)
            {//大额 200-600 金币
                _goldNum[tag] = random(200, 600);
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                openGold(tag);
            }
            else if(rand <= 6)
            {//大额 200-600 钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(200, 600);
                openDiamond(tag);
            }
            else if(rand <= 53)
            {//小额金币 100-150
                _goldNum[tag] = random(100, 150);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石 100-150
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(100, 150);
                openDiamond(tag);
            }
        }
        else if(_randVec[tag-1] == 5)
        {
            auto rand = random(1, 100);
            
            if(rand <= 30)
            {//道具
                auto randProp = random(1, 100);
                if(randProp <= 35)
                {//正面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                    openCardFace(tag);
                }
                else if(randProp <= 55)
                {//背面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                    openCardBg(tag);
                }
                else if(randProp <= 60)
                {//魔法棒
                    _goldNum[tag] = 1;
                    _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                    openMagic(tag);
                }
                else if(randProp <= 80)
                {//背景
                    _rewardType[tag] = FanPaiRewardView::RewardType::GameBg;
                    openGameBg(tag);
                }
                else if(randProp <= 100)
                {//音乐
                    _rewardType[tag] = FanPaiRewardView::RewardType::Music;
                    openMusic(tag);
                }
            }
            else if(rand <= 65)
            {//小额金币1-8
                _goldNum[tag] = random(1, 8);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石1-8
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(1, 8);
                openDiamond(tag);
            }
        }
    }
}
void FanPaiRewardView::randDiamond3(int tag)
{
    if(_rewardTempNum == 1)
    {
        auto rand = random(1, 100);
        if(rand <= 46)
        {//小额金币 2-10
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(rand <= 50)
        {//小额钻石 2-10
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(2, 10);
            openDiamond(tag);
        }
        else if(rand <= 98)
        {//道具
            auto randProp = random(1, 100);
            if(randProp <= 35)
            {//正面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                openCardFace(tag);
            }
            else if(randProp <= 55)
            {//背面
                _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                openCardBg(tag);
            }
            else if(randProp <= 60)
            {//魔法棒
                _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                _goldNum[tag] = 1;
                openMagic(tag);
            }
            else if(randProp <= 80)
            {//背景
                _rewardType[tag] = FanPaiRewardView::RewardType::GameBg;
                openGameBg(tag);
            }
            else if(randProp <= 100)
            {//音乐
                _rewardType[tag] = FanPaiRewardView::RewardType::Music;
                openMusic(tag);
            }
        }
        else if(rand <= 100)
        {//大额金币100-200
            _goldNum[tag] = random(100, 200);
            _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
            openDiamond(tag);
        }
        
    }
    else if(_rewardTempNum == 5)
    {
        
        if(_randVec[tag-1] == 1)
        {//金币 2-10
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 2)
        {//2-10 金币
            _goldNum[tag] = random(2, 10);
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
            openGold(tag);
        }
        else if(_randVec[tag-1] == 3)
        {//1-10 钻石
            _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
            _goldNum[tag] = random(1, 10);
            openDiamond(tag);
        }
        else if(_randVec[tag-1] == 4)
        {
            auto rand = random(1, 100);
            if(rand <= 3)
            {//大额 200-600 金币
                _goldNum[tag] = random(200, 600);
                _rewardType[tag] = FanPaiRewardView::RewardType::BigGold;
                openGold(tag);
            }
            else if(rand <= 6)
            {//大额 200-600 钻石
                _rewardType[tag] = FanPaiRewardView::RewardType::BigDiamond;
                _goldNum[tag] = random(200, 600);
                openDiamond(tag);
            }
            else if(rand <= 53)
            {//小额金币 100-150
                _goldNum[tag] = random(100, 150);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石 100-150
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(100, 150);
                openDiamond(tag);
            }
        }
        else if(_randVec[tag-1] == 5)
        {
            auto rand = random(1, 100);
            
            if(rand <= 15)
            {//道具
                auto randProp = random(1, 100);
                if(randProp <= 35)
                {//正面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardFace;
                    openCardFace(tag);
                }
                else if(randProp <= 55)
                {//背面
                    _rewardType[tag] = FanPaiRewardView::RewardType::CardBg;
                    openCardBg(tag);
                }
                else if(randProp <= 60)
                {//魔法棒
                    _goldNum[tag] = 1;
                    _rewardType[tag] = FanPaiRewardView::RewardType::Magic;
                    openMagic(tag);
                }
                else if(randProp <= 80)
                {//背景
                    _rewardType[tag] = FanPaiRewardView::RewardType::GameBg;
                    openGameBg(tag);
                }
                else if(randProp <= 100)
                {//音乐
                    _rewardType[tag] = FanPaiRewardView::RewardType::Music;
                    openMusic(tag);
                }
            }
            else if(rand <= 60)
            {//小额金币1-8
                _goldNum[tag] = random(1, 8);
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallGold;
                openGold(tag);
            }
            else if(rand <= 100)
            {//小额钻石1-8
                _rewardType[tag] = FanPaiRewardView::RewardType::SmallDiamond;
                _goldNum[tag] = random(1, 8);
                openDiamond(tag);
            }
        }
    }
}


void FanPaiRewardView::updateItemUI(int tag,Node* item,FanPaiRewardView::RewardType type,int index,int randNum)
{
    auto Panel_69 = item->getChildByName("Panel_69");
    auto text = Panel_69->getChildByName<TextBMFont*>("BitmapFontLabel_num");
    auto Text_29 = Panel_69->getChildByName<Text*>("Text_29");
    Text_29->setVisible(true);
//    auto Image_75 = Panel_69->getChildByName("Image_75");
//    Image_75->setVisible(false);
    if(FanPaiRewardView::RewardType::BigGold == type)
    {
        Text_29->setString(Lang("100286"));
        auto gold1 = Panel_69->getChildByName("Gold1");
        gold1->setVisible(true);
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",_goldNum[tag]));
    }
    else if(FanPaiRewardView::RewardType::SmallGold == type)
    {
        Text_29->setString(Lang("100286"));
        
        auto gold0 = Panel_69->getChildByName("Gold0");
        gold0->setVisible(true);
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",_goldNum[tag]));
    }
    else if(FanPaiRewardView::RewardType::BigDiamond == type)
    {
//        Text_29->setString(Lang("100287"));
//        auto Baoshi1 = Panel_69->getChildByName("Baoshi1");
//        Baoshi1->setVisible(true);
//        text->setVisible(true);
//        text->setString(StringUtils::format("x%d",_goldNum[tag]));
        Text_29->setString(Lang("100286"));
        auto gold1 = Panel_69->getChildByName("Gold1");
        gold1->setVisible(true);
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",_goldNum[tag]));
    }
    else if(FanPaiRewardView::RewardType::SmallDiamond == type)
    {
//        Text_29->setString(Lang("100287"));
//        auto Baoshi0 = Panel_69->getChildByName("Baoshi0");
//        Baoshi0->setVisible(true);
//        text->setVisible(true);
//        text->setString(StringUtils::format("x%d",_goldNum[tag]));
        Text_29->setString(Lang("100286"));
        
        auto gold0 = Panel_69->getChildByName("Gold0");
        gold0->setVisible(true);
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",_goldNum[tag]));
    }
    else if(FanPaiRewardView::RewardType::GameBg == type)
    {
        
        SpriteFrame* frameA = nullptr;
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->removeChildByName("card");
        if(index > 13)
        {//动态
//            auto Panel_0 = Image_75->getChildByName("Panel_0");
//            auto node = Panel_0->getChildByName(StringUtils::format("FileNode_Changjing%d",index-12));
//            node->setVisible(true);
//            ShopManager::getInstance()->changeGameBG(node,index-12);
//            Image_75->setVisible(true);
            if(index <=16)
            {
                frameA = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", 14-12),"car_new_0_1.atlas");
            }
            else
            {
                frameA = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", index-14),"car_new_0_1.atlas");
            }
            
            card_item->setVisible(true);
        }
        else
        {
            frameA = AtlasManager::getInstance()->getSF(1, 0, 0, index);
            card_item->setVisible(true);
        }
        
        
        card_item->setSpriteFrame(frameA);
        Text_29->setString(Lang("100123"));
        text->setVisible(false);
    }
    else if(FanPaiRewardView::RewardType::CardBg == type)
    {
        auto frame = SPRITE_M->getCardBgSpriteFrame(index);
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->removeChildByName("card");
        card_item->setVisible(true);
        card_item->setSpriteFrame(frame);
        Text_29->setString(Lang("100125"));
        text->setVisible(false);
    }
    else if(FanPaiRewardView::RewardType::CardFace == type)
    {
        auto num = randNum % 13 + 1;
        auto col = (int)(randNum / 13);
        auto frameA = SPRITE_M->getCardSpriteFrameByNumAndColor(num,col,index);
        auto card = UIUtils::createCSBNode("card/CardFace.csb");
        card->setName("card");
        
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->setVisible(true);
        card_item->setSpriteFrame(frameA);
        card_item->removeChildByName("card");
        card_item->addChild(card);
        
        auto _sprite1 = card->getChildByName<Sprite*>("Sprite_face");
        auto _sprite2 = _sprite1->getChildByName<Sprite*>("Sprite_num");
        auto _sprite3 = _sprite1->getChildByName<Sprite*>("Sprite_color");
        _sprite1->setSpriteFrame(AtlasManager::getInstance()->getSF(2, num, col, index));
        _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5, num, col, index));
        _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6, num, col, index));
        _sprite2->setColor(UIUtils::getCardColor(col));
        card->setPosition(card_item->getContentSize()*0.5f);
        auto size2 = _sprite2->getContentSize();
        _sprite2->setPositionX(size2.width*0.5f);
        
        Text_29->setString(Lang("100124"));
        text->setVisible(false);
    }
    else if(FanPaiRewardView::RewardType::Music == type)
    {//音乐Ui_music.png
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->removeChildByName("card");
        card_item->setSpriteFrame("Ui_music.png");
        card_item->setVisible(true);
        Text_29->setString(Lang("100240"));
        text->setVisible(false);
    }
    else if(FanPaiRewardView::RewardType::Magic == type)
    {//
        auto card_item = Panel_69->getChildByName<Sprite*>("card_item");
        card_item->removeChildByName("card");
        card_item->setSpriteFrame("Magic_0.png");
        card_item->setVisible(true);
        Text_29->setString(Lang("100179"));
        text->setVisible(true);
        text->setString(StringUtils::format("x%d",_goldNum[tag]));
    }
    UIUtils::textAdaptiveSize(Text_29,180);
    
}

void FanPaiRewardView::setConsumptionType(ConsumptionType type)
{
    _consumptionType = type;
    
    
}
void FanPaiRewardView::setType(FanPaiRewardView::Type type)
{
    _type = type;
}

void FanPaiRewardView::setRewardNum(int num)
{
    _rewardNum = num;
    _rewardTempNum = _rewardNum;
}

void FanPaiRewardView::onEnter()
{
    BaseLayer::onEnter();
}
void FanPaiRewardView::onExit()
{
    BaseLayer::onExit();
    EVENT_M->removeListener("event_game_update_coin",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
}

Node* FanPaiRewardView::getTeachItem(const std::string &name, int idx)
{
    return FileNode_reward;
}

void FanPaiRewardView::startFanPai()
{
    idxVec.clear();
    isPorp = false;
    isPorp2 = false;
    prop = 0;
    isGold = false;
    isDiamond = false;
    _randVec.clear();
    _randBoxVec.clear();
    _openIdVec.clear();
    fangCuo = 10;
    isPorp = false;
    isChongFu = true;
    
    
    
    this->setVisible(true);
    
    //_actionManager->gotoFrameAndPause(0);
    auto FileNode_6 = getNode("FileNode_6");
    UIUtils::playInnerAction(FileNode_6, "Start0", false);//宝箱跳出动画
    //getNode("FileNode_6")->setPositionY(187.20);
    //top
    getNode("Button_getGold")->setVisible(false);
    getNode("Button_getDiamond")->setVisible(false);
    for(int i = 0;i<6;++i)
    {
        _goldNum[i] = 0;
    }

    getNode("Button_get")->setVisible(false);
    getNode<Button*>("Button_get")->setEnabled(false);
    getNode("Button_close")->setVisible(false);
    //auto spFrame = SPRITE_M->getCardBgSpriteFrame(0);
    for(int i = 1;i<6;++i)
    {
        auto node = getNode(StringUtils::format("FileNode_%d",i));
        UIUtils::playInnerAction(node,"idle",false);
        auto sp = node->getChildByName<Sprite*>("card_bg_0_1");
        auto node_AD = node->getChildByName<Sprite*>("Node_AD");
        node_AD->setVisible(false);
        sp->setVisible(true);
        auto Panel_69 = sp->getChildByName("Panel_69");
        auto vec = Panel_69->getChildren();
        for(auto child:vec)
        {
            child->setVisible(false);
        }
        auto text = Panel_69->getChildByName<TextBMFont*>("BitmapFontLabel_num");
        text->setVisible(false);
        //sp->setSpriteFrame(spFrame);
        auto panel = sp->getChildByName<Layout*>("Panel_get");
        panel->setEnabled(true);
        panel->setTag(i);
    }
    
    isTouch = false;
    if(_type == FanPaiRewardView::Type::None)
    {
        auto Sprite_Box = getNode<Sprite*>("Sprite_Box");
        if(_type == FanPaiRewardView::Type::Home)
        {
            auto max = DATA_M->getStarBoxNumMax();
            string name = "";
            //1-7
            //2/4/6/7
            if(max <= 2)
            {
                name = "Box_0.png";
            }
            else if(max <= 4)
            {
                name = "Box2_0.png";
            }
            else if(max <= 6)
            {
                name = "Box3_0.png";
            }
            else if(max <= 8)
            {
                name = "Box4_0.png";
            }
            Sprite_Box->setSpriteFrame(name);
        }
        else if(_type == FanPaiRewardView::Type::Daily)
        {
            auto max = DATA_M->getDailyStarBoxNumMax();
            _rewardNum = 3;
            string name = "";
            if(max <= 3)
            {
                name = "Box_0.png";
            }
            else if(max <= 5)
            {
                name = "Box2_0.png";
            }
            else if(max <= 19)
            {
                name = "Box3_0.png";
            }
            else if(max == 20)
            {
                name = "Box6_0.png";
            }
            Sprite_Box->setSpriteFrame(name);
        }
        else
        {
            
            bool isGold = _consumptionType == ConsumptionType::Gold;
            // 获取抽奖结果
            _rewardVec = BOX_M->startLottery(isGold?BoxDataManager::LotteryType::Gold:BoxDataManager::LotteryType::Gem, _rewardTempNum==1?BoxDataManager::LotteryTimes::One:BoxDataManager::LotteryTimes::Five, isGold?DATA_M->getCoinNum():0);//DATA_M->getDiamond());

            if(ConsumptionType::Gold == _consumptionType)
            {//Box3_%s
                //累计黄金宝箱任务数 新手
                TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::GOLDBOX);
                //累计黄金宝箱任务数 每日
                TASK_M->addTaskNum((int)TaskManager::DayTaskType::GOLDBOX + 100);
                Sprite_Box->setSpriteFrame("Box3_0.png");
                
                
            }
            else if(ConsumptionType::Diamond == _consumptionType)
            {//Box5_%s
                //累计钻石宝箱任务数 新手
                TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::DIAMONDBOX);
                //累计钻石宝箱任务数 每日
                TASK_M->addTaskNum((int)TaskManager::DayTaskType::DIAMONDBOX + 100);
                Sprite_Box->setSpriteFrame("Box5_0.png");
                
               
            }
        }
        
        playAni(_rewardNum==1?"Start0":"Start2",false,[this](){
            //允许点击
            isTouch = true;
            TEACH_M->nextTeachStep(this);
        });
        
        if(_rewardNum == 1)
        {//一张
            _openIdVec.push_back(1);
        }
        else
        {//五张 3 2 1 4 5
            vector<int> vec{3,2,1,4,5};
            for(auto id:vec)
            {
                _openIdVec.push_back(id);
            }
        }
    }
    else if(_type == FanPaiRewardView::Type::Home || _type == FanPaiRewardView::Type::Daily)
    {
        auto Sprite_Box = getNode<Sprite*>("Sprite_Box");
        if(_type == FanPaiRewardView::Type::Home)
        {
            auto max = DATA_M->getStarBoxNumMax();
            starMax = max;
            _rewardNum = 3;
            // 获取抽奖结果
            _rewardVec = BOX_M->startLottery(BoxDataManager::LotteryType::Star, BoxDataManager::LotteryTimes::Star, starMax);
            
            if(_rewardVec.empty())
            {
                CCLOG("E");
            }
            
            string name = "";
            if(max <= 2)
            {
                name = "Box_0.png";
            }
            else if(max <= 4)
            {
                name = "Box2_0.png";
            }
            else if(max <= 6)
            {
                name = "Box3_0.png";
            }
            else if(max <= 8)
            {
                name = "Box4_0.png";
            }
            Sprite_Box->setSpriteFrame(name);
        }
        else if(_type == FanPaiRewardView::Type::Daily)
        {
            auto max = DATA_M->getDailyStarBoxNumMax();
            crownMax = max;
            _rewardNum = 3;
            // 获取抽奖结果
            _rewardVec = BOX_M->startLottery(BoxDataManager::LotteryType::Daily, BoxDataManager::LotteryTimes::Daily, crownMax);
            if(_rewardVec.empty())
            {
                CCLOG("E");
            }
            string name = "";
            if(max <= 3)
            {
                name = "Box_0.png";
            }
            else if(max <= 5)
            {
                name = "Box2_0.png";
            }
            else if(max <= 19)
            {
                name = "Box3_0.png";
            }
            else if(max == 20)
            {
                name = "Box6_0.png";
            }
            Sprite_Box->setSpriteFrame(name);
        }
        playAni(_rewardNum == 3?"Start1":"Start0",false,[this](){
            //允许点击
            isTouch = true;
            TEACH_M->nextTeachStep(this);
        });
        
        if(_rewardNum == 1)
        {//一张
            _openIdVec.push_back(1);
        }
        else
        {//三张 4 1 5
            vector<int> vec{4,1,5};
            for(auto id:vec)
            {
                _openIdVec.push_back(id);
            }
        }
        
    }
    else if(_type == FanPaiRewardView::Type::SevenGold||_type == FanPaiRewardView::Type::SevenDiamond)
    {
        auto Sprite_Box = getNode<Sprite*>("Sprite_Box");
        if(_type == FanPaiRewardView::Type::SevenGold)
        {
            Sprite_Box->setSpriteFrame("Box2_0.png");
        }
        else if(_type == FanPaiRewardView::Type::SevenDiamond)
        {
            Sprite_Box->setSpriteFrame("Box3_0.png");
        }
        
        playAni(_rewardNum == 3?"Start1":"Start0",false,[this](){
            //允许点击
            isTouch = true;
        });
        
        if(_rewardNum == 1)
        {//一张
            _openIdVec.push_back(1);
        }
        else
        {//三张 4 1 5
            vector<int> vec{4,1,5};
            for(auto id:vec)
            {
                _openIdVec.push_back(id);
            }
        }
    }
    
    
    
    
    
    if(_type == FanPaiRewardView::Type::Home)
    {
        //starMax = DATA_M->getStarBoxNumMax();
        DATA_M->setStarBoxNumMax();
        DATA_M->setStarBoxNum(0,true);
        SCENE_M->getLobby()->updateStarBox();
    }
    else if(_type == FanPaiRewardView::Type::Daily)
    {
        //crownMax = DATA_M->getDailyStarBoxNumMax();
        DATA_M->setDailyStarBoxNumMax();
        DATA_M->setDailyStarBoxNum(0,true);
        SCENE_M->getLobby()->updateCrownnBox();
    }
    
    
    _actionManager->setFrameEventCallFunc([this](Frame* frame){
         auto event = dynamic_cast<EventFrame*>(frame);
         auto msg = event->getEvent();
         if(msg.find(CARDITEM) != string::npos)
         {
             auto idstr = msg[8];
             auto node = getNode(StringUtils::format("FileNode_%c",idstr));
             UIUtils::playInnerAction(node,"Loop",true);
         }
         else if(msg.find(BOX) != string::npos)
         {
             auto idstr = msg[3];
             if(idstr == '1')
             {
                 SOUND_M->playEffectMusic(EffectBoxOpen);
             }
             auto Sprite_Box = getNode<Sprite*>("Sprite_Box");
             if(_type == FanPaiRewardView::Type::Home)
             {
                 auto max = starMax;//DATA_M->getStarBoxNumMax();
                 string name = "";
                 if(max <= 2)
                 {
                     name = "Box_%c.png";
                 }
                 else if(max <= 4)
                 {
                     name = "Box2_%c.png";
                 }
                 else if(max <= 6)
                 {
                     name = "Box3_%c.png";
                 }
                 else if(max <= 8)
                 {
                     name = "Box4_%c.png";
                 }
                 Sprite_Box->setSpriteFrame(StringUtils::format(name.c_str(),idstr));
             }
             else if(_type == FanPaiRewardView::Type::Daily)
             {
                 auto max = crownMax;//DATA_M->getDailyStarBoxNumMax();
                 string name = "";
                 if(max <= 3)
                 {
                     name = "Box_%c.png";
                 }
                 else if(max <= 5)
                 {
                     name = "Box2_%c.png";
                 }
                 else if(max <= 19)
                 {
                     name = "Box3_%c.png";
                 }
                 else if(max == 20)
                 {
                     name = "Box6_%c.png";
                 }
                 Sprite_Box->setSpriteFrame(StringUtils::format(name.c_str(),idstr));
             }
             else if(_type == FanPaiRewardView::Type::SevenGold)
             {
                 Sprite_Box->setSpriteFrame(StringUtils::format("Box2_%c.png",idstr));
             }
             else if(_type == FanPaiRewardView::Type::SevenDiamond)
             {
                 Sprite_Box->setSpriteFrame(StringUtils::format("Box3_%c.png",idstr));
             }
             else
             {
                 if(ConsumptionType::Gold == _consumptionType)
                 {//Box3_%s
                     Sprite_Box->setSpriteFrame(StringUtils::format("Box3_%c.png",idstr));
                 }
                 else if(ConsumptionType::Diamond == _consumptionType)
                 {//Box5_%s
                     Sprite_Box->setSpriteFrame(StringUtils::format("Box5_%c.png",idstr));
                 }
             }
         }
    });
    //47 50 53 56 59 62
    
    tempFangCuo = 0;
    float time = 0;
    if(_rewardNum == 1)
    {//120
        time = 120 * 0.017;
    }
    else if(_rewardNum == 3)
    {//140
        time = 140 * 0.017;
    }
    else
    {//155
        time = 155 * 0.017;
    }
    //防错
    unschedule("FanPaifangCuo");
    schedule([this,time](float dt){
        
        tempFangCuo+=dt;
        if(tempFangCuo >= time)
        {
            //允许点击
            isTouch = true;
            unschedule("FanPaifangCuo");
        }
    },"FanPaifangCuo");
    
   
    _rewardTempNum = _rewardNum;
    _openNum = _rewardNum;
    for(int i = 1;i<6;++i)
    {
        _randVec.push_back(i);
        CCLOG("RandVec--------%d",i);
    }
    
    _randBoxVec.push_back(4);
    _randBoxVec.push_back(1);
    _randBoxVec.push_back(5);
    
    std::random_shuffle(_randBoxVec.begin(), _randBoxVec.end(), myrandomFP);
    std::random_shuffle(_randVec.begin(), _randVec.end(), myrandomFP);
    std::random_shuffle(_rewardVec.begin(), _rewardVec.end(), myrandomFP);
    
    
    
    TEACH_M->nextTeachStep();
    
    randFiveTagNum = -1;
    fivePumpNum = GETINTEGER("fivePumpNum",0);
    isThreeReward = GETBOOL("isThreeReward",true);
    
    if(!TEACH_M->isTeaching())
    {
        if(ConsumptionType::Gold == _consumptionType)
        {//Box3_%s
            
            //引导进来时不叠加
            SETINTEGER("fivePumpNum",++fivePumpNum);
            if(fivePumpNum == 1)
            {//第一次必中。金币箱子
                if(_rewardNum == 5)
                {
                    randFiveTagNum = random(1, 5);
                }
                else
                {
                    randFiveTagNum = 1;
                }
            }
            
        }
        else if(ConsumptionType::Diamond == _consumptionType)
        {//Box5_%s
            SETINTEGER("fivePumpNum",++fivePumpNum);
            if(fivePumpNum == 1)
            {//第一次必中 钻石箱子
                if(_rewardNum == 5)
                {
                    randFiveTagNum = random(1, 5);
                }
                else
                {
                    randFiveTagNum = 1;
                }
            }
            else if(fivePumpNum >= 3&&isThreeReward)
            {//进来一次
                isThreeReward = false;
                SETBOOL("isThreeReward",false);
                if(_rewardNum == 5)
                {
                    randFiveTagNum = random(1, 5);
                }
                else
                {
                    randFiveTagNum = 1;
                }
            }
        }
        
        UIUtils::FIRAnalyticsEventWithPrefix("openStarBox_" + toString(int(_type)) + "_" +  toString(int(_consumptionType)));
    }
    else { // 在引导
        UIUtils::FIRAnalyticsEventWithPrefix("openStarBox", "teach");
    }
    
    if(randFiveTagNum != -1)
    {
        ValueVector::iterator it = _rewardVec.begin();
        while(it != _rewardVec.end())
        {
            auto item = *it;
            auto &reward = item.asValueMap();
            auto type2 = reward.at("type2").asInt();
            if(type2>4)
            {//1 2 3 4是金币钻石。5开始是道具
                //是道具  移除奖励中的道具
                _rewardVec.erase(it);
                break;
            }
            else
            {//一直没有道具则不用管
                it++;
            }
        }
    }
    
    updateUI();
}

void FanPaiRewardView::addIdxVec(int idx)
{
    idxVec.push_back(idx);
}
