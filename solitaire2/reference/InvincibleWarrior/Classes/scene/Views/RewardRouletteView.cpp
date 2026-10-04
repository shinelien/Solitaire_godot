//
// Created by  on 2019-07-13.
//

#include "RewardRouletteView.h"
#include "RewardManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#endif
#include "MainLobby.h"
#include "HomeView.h"
#include "DailyView.h"
#include "GameViewHD.hpp"
#include "PlayerManager.h"
#include "GrowupNode.h"
#include "DrawPropsView.h"
#include "EventObserver.h"
#include "FishManager.h"
const int TotalRewardCNT = 8;
const float TotalRotationTime = 10;
const float RepeatRoteTime = 15;
const float RepeatRotation = -360*3;
using namespace std;
vector<RewardManager::RewardType> rewards {
    RewardManager::RewardType::Gold,
    RewardManager::RewardType::Magic,
    RewardManager::RewardType::Gold,
    RewardManager::RewardType::Magic,
    RewardManager::RewardType::CARDFACE,
    RewardManager::RewardType::Gold,
    
    RewardManager::RewardType::Magic,
    
    RewardManager::RewardType::Gold,
};
vector<int> rewardsJiLv{
    10,//1
    160,//15
    190,//3
    230,//4
    430,//20
    510,//8
    660,//15
    1000,//34
};

vector<int> rewardsCount{
    500,
    1,
    100,
    5,
    1,
    42,
    1,
    28,
};
vector<string> iconNames{
    "7Daily_icon6.png",
    "7Daily_icon0.png",
    "7Daily_icon0.png",
    "7Daily_icon0.png",
    "Magic_0.png",
    "Magic_0.png",
    "Magic_0.png",
    "7Daily_icon0.png",
};

void RewardRouletteView::initUI() {
    BaseLayer::initUI();
    doLayout();
    auto Node_zhuan = getNode("Node_zhuan");
    auto Roby = RotateBy::create(RepeatRoteTime, RepeatRotation);
    auto re = RepeatForever::create(Roby);
    re->setTag(88);
    Node_zhuan->runAction(re);
    
    
    Text_time = getNode<TextBMFont*>("Text_time");
    Text_time->setVisible(false);
    getNode("Panel_Get")->setVisible(false);
    Button_get = getNode<Button*>("Button_get");
    Button_adget = getNode<Button*>("Button_adget");
    Button_adget->setEnabled(DATA_M->getHaveVideo());
    
    Button_get->setVisible(false);
    Button_adget->setVisible(true);
    //getNode("panel_SDKGift")->setVisible(false);
    auto updatTime = [this](float t){
        
        auto time = DATA_M->getNextRouletteTime(isAD);
        _freeGet = time<=0;
        if(1)
        {
            if(_freeGet)
            {
                setIsAD(false);
            }
            
            //Text_time->setVisible(!_freeGet);
//            Button_adget->setVisible(!_freeGet);
//            Button_adget->setEnabled(DATA_M->getHaveVideo());
//            Button_get->setVisible(_freeGet);
            if (!_freeGet) {
//                int fen = (int)(time / 60);
//                int miao = (int)((int)time % 60);
//                Text_time->setString(StringUtils::format("%02d:%02d", fen, miao));
            }
            else {
                
            }
        }
    };
    schedule(updatTime, 0.1, "schedule_roulette_update");
    updatTime(0);
    for (int i=0;i<rewardsCount.size();i++) {
        auto label = getNode<TextBMFont*>(StringUtils::format("Text_reward%d", i));
        if (label) {
            label->setString(StringUtils::format("+%d", rewardsCount.at(i)));
        }
    }
    
    
    //点击广告了
    isClickAds = false;
    
    //多语言
    auto Text_lingqu = getNode<Text*>("Text_lingqu");
    Text_lingqu->setString(Lang("100295"));
    
    getNode<Text*>("Text_dayReward")->setString(Lang("100184"));
    
    auto Text_playAgain = getNode<Text*>("Text_playAgain");
    Text_playAgain->setString(Lang("100295"));
    
    UIUtils::textAdaptiveSize(Text_playAgain,360);
    playAni("Start");
}

void RewardRouletteView::initData() {
    BaseLayer::initData();
    setName("RewardRouletteView");
    EVENT_M->addListener("event_game_roulette", [this](ValueMap valueMap, void *obj){
        //广告结束了
        isClickAds = false;
        lunPanNum--;
        SETINTEGER("lunPanNum",lunPanNum);
        startRoulette(false);
    },this);
//    addEvent("event_game_roulette", [this](EventCustom*) {
//        lunPanNum--;
//        SETINTEGER("lunPanNum",lunPanNum);
//        startRoulette(false);
//    });
}

void RewardRouletteView::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();

    if (btnName == "Button_get") {
        startRoulette();
    }
    else if (btnName == "Button_adget") {
//        startRoulette();
        isClickAds = true;
        this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.5f), CallFunc::create([this](){
            isClickAds = false;
        })));
        DATA_M->playVideoAds(6);
        UIUtils::FIRFirestoreAdd("operator", {
           {"key", Value("RewardRouletteView")},
           {"value", Value("ad")}
        });
        UIUtils::FIRAnalyticsEventWithPrefix("roulette_" + toString((int)_type));
    }
    else if (btnName == "Button_getreward") {
        //getNode("panel_SDKGift")->setVisible(false);
        EVENT_M->sendEvent("reward_item_update");
    }
    else if (btnName == "btn_close") {
        if(!isClickAds)
        {
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("RewardRouletteView")},
                {"value", Value("no")},
                {"v1", Value(DATA_M->getHaveVideo())}
            });
            if(_type == RewardRouletteView::Type::Game)
            {
                auto gameview = SCENE_M->getGameView();
                gameview->gamePause(false);//解除暂停
            }
            auto lobby = SCENE_M->getLobby();
            if(lobby)
            {
                lobby->showGetGoldBtn(true);
                lobby->openReward(false);
            }
            
            removeFromParent();
        }
    }
}

float expoEaseOut(float time)
{
    // modify by ct + 0.001 的偏移 因为 pow(2, -10) 不为0
    return time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1 + 0.0008f);
}

void RewardRouletteView::startRoulette(bool free) {
    if (free)
        DATA_M->setRouletteTime(DATA_M->getContentSec());
    _rotating = true;
    getNode("Node_bottom")->setVisible(false);
    getNode("btn_close")->setVisible(false);
    int idx = 0;
    auto value = random(1, 1000);
//    if (value <= 2) {
//        vector<int> items{1, 4, 6};
//        idx = items.at(random(0, int(items.size()-1)));
//    }
//    else if (value <= 22) {
//        vector<int> items{2,7};
//        idx = items.at(random(0, int(items.size()-1)));
//    }
//    else {
//        vector<int> items{0,  3, 5};
//        idx = items.at(random(0, int(items.size()-1)));
//    }


    if (value <= rewardsJiLv.at(0))
    {
        idx = 0;
    }
    else if (value <= rewardsJiLv.at(1))
    {
        idx = 1;
    }
    else if (value <= rewardsJiLv.at(2))
    {
        idx = 2;
    }
    else if (value <= rewardsJiLv.at(3))
    {
        idx = 3;
    }
    else if (value <= rewardsJiLv.at(4))
    {
        idx = 4;
    }
    else if (value <= rewardsJiLv.at(5))
    {
        idx = 5;
    }
    else if (value <= rewardsJiLv.at(6))
    {
        idx = 6;
    }
    else if (value <= rewardsJiLv.at(7))
    {
        idx = 7;
    }
    CCLOG("roulette idx:%d num:%d", idx, rewardsCount.at(idx));
    auto onePice = 360/TotalRewardCNT;
    auto Node_zhuan = getNode("Node_zhuan");
    auto action = Node_zhuan->getActionByTag(88);
    if(action)
    {
//        Node_zhuan->stopAction(action);
        Node_zhuan->runAction(Sequence::create(DelayTime::create(0), CallFunc::create([Node_zhuan](){
            Node_zhuan->stopActionByTag(88);
        }), NULL));
    }
//    float dx = MIN(10, abs(RepeatRotation/RepeatRoteTime)*Director::getInstance()->getDeltaTime()); // 补偿 这里并没有根据实际帧时间来计算 极端 情况可能产生bug
    auto offset = (idx*onePice + random(10.f, (float)onePice - 10.f/* - dx*/));
    float curRotating = Node_zhuan->getRotationX();
    float lastOffset = fmod(curRotating, 360.f);
//    Node_zhuan->setRotation(lastOffset);
    auto totalRotation = -(360*20 + offset + (lastOffset));
    CCLOG("roulette:%d curRotating:%f offset:%f totalrotate:%f", idx, curRotating, lastOffset, totalRotation);
//    Node_zhuan->runAction(Sequence::create(EaseExponentialOut::create(RotateBy::create(1, totalRotation)), /*ScaleTo::create(0.25, 1.1) , ScaleTo::create(0.25, 1)*/DelayTime::create(0.5f), CallFunc::create([this, idx](){
//        _rotating = false;
//        getNode("Node_bottom")->setVisible(true);
//        getNode("btn_close")->setVisible(true);
//        setIsAD(true);
////        showReward(idx);
//    }), NULL));
    
    totalRotetime = TotalRotationTime;
    auto targetRotation = curRotating + totalRotation;
    schedule([this, idx, curRotating, Node_zhuan, totalRotation, targetRotation](float t){
        totalRotetime-=t;
        float tt = (1-totalRotetime/TotalRotationTime);
        auto offsett = expoEaseOut(tt);
        if (totalRotetime<0)
        {
            offsett = 1;
            this->unschedule("key_roulette_schedule_update");
            runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([this, idx](){
                _rotating = false;
                getNode("Node_bottom")->setVisible(true);
                getNode("btn_close")->setVisible(true);
                setIsAD(true);
                showReward(idx);
            }), NULL));
        }
        auto roteX = curRotating + offsett * totalRotation;
        Node_zhuan->setRotation(roteX);
    }, "key_roulette_schedule_update");
}

void RewardRouletteView::update(float t)
{
    
}

void RewardRouletteView::showReward(int idx)
{
    auto lobby = SCENE_M->getLobby();
    if(lobby)
    {
        lobby->showGetGoldBtn(true);
        lobby->openReward(false);
    }
    
    if(_type == RewardRouletteView::Type::Game)
    {
        auto gameview = SCENE_M->getGameView();
        gameview->gamePause(false);//解除暂停
    }
    if(RewardRouletteView::Type::Game == _type)
    {
        _gameView = SCENE_M->getGameView();
    }
    else
    {
        _gameView = nullptr;
    }
    if(rewards.at(idx) == RewardManager::RewardType::ZuanShi)
    {
//        Vec2 poi(2000,2000);
//        if(_gameView)
//        {
//            poi = _gameView->getdiamondWorldPoi();
//        }
//        auto lobby = SCENE_M->getLobby();
//        auto num = rewardsCount.at(idx);
//        lobby->diamondAni(rewardsCount.at(idx),_gameView?_gameView:nullptr,Vec2(2000,2000),[lobby,this,num](){
//            DATA_M->setDiamond(num);
//            ValueMap valueMap{
//                {"isTime",Value{true}}
//            };
//            //更新有金币显示
//            EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//        },[lobby,this](){
//            //home
//            
//            //SOUND_M->playEffectMusic(EffectGetGem);
//            lobby->playDiamondAni((int)_type,true);
//        },[lobby,this](){
//            //home
//            //SOUND_M->playEffectMusic(EffectGetGem);
//            lobby->playDiamondAni((int)_type,false);
//            SCENE_M->removeLayer(this);
//        },poi);
    }
    else if(rewards.at(idx) == RewardManager::RewardType::Gold)
    {
        //播放奖励
        Vec2 poi(2000,2000);
        if(_gameView)
        {
            poi = _gameView->getGoldWorldPoi();
        }
        auto lobby = SCENE_M->getLobby();
        auto coin = rewardsCount.at(idx);
        lobby->goldAni(rewardsCount.at(idx),_gameView?_gameView:nullptr,Vec2(2000,2000),[lobby,this,coin](){
            DATA_M->setCoinNum(coin, true, 109);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
//            if(_type == RewardRouletteView::Type::Game)
//            {//DailyView
//                auto game = SCENE_M->getGameView();
//                game->updateCoin();
//            }
//            else
//            {
//                lobby->updateCoin(true);
//            }
        },[lobby,this](){
        //home
            //SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni((int)_type,true);
        },[lobby,this](){
            //home
            //SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni((int)_type,false);
            SCENE_M->removeLayer(this);
        },poi);
    }
    else if(rewards.at(idx) == RewardManager::RewardType::Magic)
    {
        auto index = 6*100000;
        index+=rewardsCount.at(idx);
        idxVec.push_back(index);
        
        REWARD_M->getReward(RewardManager::RewardType::Magic,rewardsCount.at(idx),true);
        if(!idxVec.empty())
        {
            SCENE_M->addDialog(DrawPropsView::createLayerN(idxVec,DrawPropsView::ViewType::Home));
        }
        SCENE_M->removeLayer(this);
        return;
    }
    else if(rewards.at(idx) == RewardManager::RewardType::CARDBG)
    {
        
        auto id = random(0,CARD_BG_NUM-1);
        //index+=rewardsCount.at(idx);
        auto isBuy = DATA_M->getShopItemStatus(3,id);
        DATA_M->unLockShopItemStatus(3,id);
        auto index = 3*100000 + id*1000 + (true?1000000:2000000) + (isBuy?10000000:20000000);
        idxVec.push_back(index);
        
        if(!idxVec.empty())
        {
            SCENE_M->addDialog(DrawPropsView::createLayerN(idxVec,DrawPropsView::ViewType::Home));
        }
        SCENE_M->removeLayer(this);
        return;
    }
    else if(rewards.at(idx) == RewardManager::RewardType::CARDFACE)
    {
        auto id = random(1, CARD_FACE_NUM-1);
        auto randNum = random(0, 51);
        //index+=rewardsCount.at(idx);
        auto isBuy = DATA_M->getCardFaceStatus(2,id,randNum);
        DATA_M->unLockShopItemStatus(2,id,randNum);
        auto index = 2*100000 + id*1000 + randNum + (true?1000000:2000000) + (isBuy?10000000:20000000);;
        idxVec.push_back(index);
        DATA_M->setPropNew(idxVec);
        auto lobby = SCENE_M->getLobby();
        lobby->updataBagNew();
        if(!idxVec.empty())
        {
            SCENE_M->addDialog(DrawPropsView::createLayerN(idxVec,DrawPropsView::ViewType::Home));
        }
        SCENE_M->removeLayer(this);
        return;
    }
    
    //getNode<Sprite*>("Sprite_reward")->setSpriteFrame(iconNames.at(idx));
    //auto cnt = rewardsCount.at(idx);
//    RewardManager::getInstance()->getReward(rewards.at(idx), cnt);
    //getNode("panel_SDKGift")->setVisible(true);
//    playAni("Start1", false,[this,idx](){
//
//    });
    
    
    this->setVisible(false);
//
    //getNode<TextBMFont*>("Text_addNum")->setString(StringUtils::format("+%d", cnt));
}

void RewardRouletteView::setIsAD(bool is)
{
    isAD = is;
    SETBOOL("isAD",is);
}

RewardRouletteView::RewardRouletteView(RewardRouletteView::Type type)
:BaseLayer("RewardRoulette.csb")
,_type(type)
{
    isAD = GETBOOL("isAD",false);
    
    lunPanNum = GETINTEGER("lunPanNum",4);
}

RewardRouletteView::~RewardRouletteView() {

}

void RewardRouletteView::onEnter()
{
    BaseLayer::onEnter();
    UIUtils::FIRAnalyticsEventWithPrefix("RewardRouletteView");
}
void RewardRouletteView::onExit()
{
    BaseLayer::onExit();
    EVENT_M->removeListener("event_game_roulette",this);
}
