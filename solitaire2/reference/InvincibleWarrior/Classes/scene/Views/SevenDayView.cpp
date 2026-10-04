//
//  SevenDayView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/26.
//

#include <stdio.h>
#include "SevenDayView.h"
#include "MainLobby.h"
#include "RewardManager.h"
#include "FanPaiRewardView.h"
#include "HomeView.h"
#include "DailyView.h"
#include "PlayerManager.h"
#include "GrowupNode.h"
#include "DrawPropsView.h"
#include "EventObserver.h"
#include "DataManager.h"
#include "FishManager.h"
#include "GameBackground.h"
#include "FishGuideManager.h"

#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"

vector<int> rewardVec{14,20,28,1,50,70,1};
vector<int> magicNum{
    0,
    1,
    1,
    1,
    1,
    2,
    2,
};

SevenDayView::SevenDayView(SevenDayView::Type type)
:BaseLayer("20207DaySgin.csb")
,_type(type)
{
    auto tm = DATA_M->getContentTime();
    auto yday = tm->tm_yday;
    int year = tm->tm_year+1900;
    if(yday == 1)
    {
        bool isRunNian = false;
        if(year%100 == 0)
        {//世纪年
            isRunNian = year%400 == 0;
        }
        else
        {//普通年
            isRunNian = year%4 == 0;
        }
        yday = isRunNian?366:365;
    }
    else
    {
        yday -= 1;
    }
    //SETINTEGER("lastYDay",1);
    //记录天数 第一次登陆 记录的天数是前一天的天数
    lastYDay = GETINTEGER("lastYDay",yday);
    
    //记录年份
    lastYear = GETINTEGER("lastYear",year);
    
    for(int i = 0;i < 7;++i)
    {
        isGetReward.push_back(GETBOOL(StringUtils::format("isGetReward%d",i).c_str(),false));
        isGetRewardAD.push_back(GETBOOL(StringUtils::format("isGetRewardAD%d",i).c_str(),false));
    }
    //SETINTEGER("RewardDays",4);
    RewardDays = GETINTEGER("RewardDays",1);//每领取一遍奖励 累计+1
    bool isGetR = isGetReward[RewardDays-1];
    //第一次登陆 第二次登陆
    if(/*true ||*/tm->tm_yday != lastYDay&&isGetR)
    {
        if(true ||lianXu())
        {//今天的没领
            RewardDays++;
            //SETINTEGER("RewardDays",RewardDays);
            SETINTEGER("RewardDays",RewardDays);//每领取一遍奖励 累计+1
            if (RewardDays == 1 || RewardDays == 3 || RewardDays == 7) {
                ValueMap valueMap1;
                UIUtils::FIRAnalyticsEvent(StringUtils::format("event_game_seven_%d", RewardDays), valueMap1);
            }
        }
        else
        {
            initDay();
        }
        lastYDay = tm->tm_yday;
        SETINTEGER("lastYDay",lastYDay);
    }
    
    if(RewardDays == 8)
    {
       initDay();
    }
     
}
SevenDayView::~SevenDayView()
{
    
}
    
void SevenDayView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    getNode<Button*>("Button_getAD")->setEnabled(DATA_M->getHaveVideo());
    
    getNode("Button_getGold")->setVisible(false);
    getNode("Button_getDiamond")->setVisible(false);
    Text_time = getNode<Text*>("Text_time");
    auto tm = DATA_M->getContentTime();
    Text_time->setString(StringUtils::format(Lang("100256").c_str(),23 - tm->tm_hour,59-tm->tm_min));
    schedule([this](float dt){
        auto tm = DATA_M->getContentTime();
        Text_time->setString(StringUtils::format(Lang("100256").c_str(),23 - tm->tm_hour,59-tm->tm_min));
    }, 1,"sevenDay_time");
    
    for(int i = 1;i<8;++i)
    {
        auto node = getNode(StringUtils::format("FileNode_%d",i));
        for(int j = 1;j < 8;++j)
        {
            node->getChildByName(StringUtils::format("Panel_reward%d",j))->setVisible(i == j);
        }
        auto reward = node->getChildByName(StringUtils::format("Panel_reward%d",i));
        auto btn = reward->getChildByName<Button*>("Button_1");
        auto Ui_7day1_0 = reward->getChildByName("Ui_7day1_0");
        btn->setEnabled(i <= RewardDays);
        reward->setVisible(true);
        reward->getChildByName<Text*>("Text_28")->setString(Lang("100292"));
        auto BitmapFontLabel_1 = FIND_NODE(TextBMFont*, reward, "BitmapFontLabel_1");
        auto BitmapFontLabel_magic = FIND_NODE(TextBMFont*, reward, "BitmapFontLabel_magic");
        
        if(i == 1)
        {
            BitmapFontLabel_1->setString(StringUtils::format("+%d",rewardVec.at(i-1)));
        }
        else if(i == 2||i == 4||i == 5||i == 6)
        {
            BitmapFontLabel_1->setString(StringUtils::format("+%d",rewardVec.at(i-1)));
            BitmapFontLabel_magic->setString(StringUtils::format("x%d",magicNum.at(i-1)));
        }
        else if(i == 3||i==7)
        {
            auto isOne = DATA_M->getSevenOneVec(i==3?0:1);
            auto Node_fish = FIND_NODE(Node*, reward, "Node_fish");
            auto Node_icon = FIND_NODE(Node*, reward, "Node_icon");
            auto Node_icon_fish = FIND_NODE(Node*, reward, "Node_icon_fish");
            Node_fish->removeAllChildren();
            
            //Node_fish->setVisible(sevenNum == 0);
            Node_icon->setVisible(isOne);
            Node_icon_fish->setVisible(!isOne);
            if(!isOne)
            {
                auto BitmapFontLabel_fish_1 = FIND_NODE(TextBMFont*, reward, "BitmapFontLabel_fish_1");
                auto BitmapFontLabel_fish_magic = FIND_NODE(TextBMFont*, reward, "BitmapFontLabel_fish_magic");
                BitmapFontLabel_fish_1->setString(StringUtils::format("x%d",rewardVec.at(i-1)));
                BitmapFontLabel_fish_magic->setString(StringUtils::format("x%d",magicNum.at(i-1)));
                auto fish = FISH_M->getFishSpine(i==3?0:1);
                Node_fish->addChild(fish);
                fish->setAnimation(0, "Run", true);
            }
            else
            {
                BitmapFontLabel_1->setString(StringUtils::format("+%d",rewardVec.at(i-1)));
                BitmapFontLabel_magic->setString(StringUtils::format("x%d",magicNum.at(i-1)));
            }
        }
        
        if(i == 7)
        {
            auto isOne = DATA_M->getSevenOneVec(1);
            auto FileNode_box = FIND_NODE(Node*, reward, "FileNode_box");
            auto FileNode_fish_box = FIND_NODE(Node*, reward, "FileNode_fish_box");
           
            if(!isOne)
            {
                auto Sprite_Box = FileNode_fish_box->getChildByName<Sprite*>("Sprite_Box");
                Sprite_Box->setSpriteFrame("Box3_0.png");
                UIUtils::playInnerAction(FileNode_fish_box, "Loop", true);
            }
            else
            {
                auto Sprite_Box = FileNode_box->getChildByName<Sprite*>("Sprite_Box");
                Sprite_Box->setSpriteFrame("Box3_0.png");
                UIUtils::playInnerAction(FileNode_box, "Loop", true);
            }
            //
            auto Text_28_0_0 = reward->getChildByName<Text*>("Text_28_0_0");
            Text_28_0_0->setString(Lang("100254"));
        }
        if(i <= RewardDays)
        {//已经或即将签到的
            auto opacity = isGetReward[i - 1]?255:0;
            Ui_7day1_0->setOpacity(opacity);
        }
        else
        {
            Ui_7day1_0->setOpacity(0);
        }
//        if(i == RewardDays&&!isGetReward[RewardDays - 1])
//        {
//            UIUtils::playInnerAction(node, "Flop1", false);
//        }
    }
    auto node4 = getNode(StringUtils::format("FileNode_%d",4));
    auto Sprite_Box4 = FIND_NODE(Sprite*, node4, "Box3_0_44");
    Sprite_Box4->setSpriteFrame("Box2_0.png");
    
    
    //RewardDays = 4;
    
    getNode<Button*>("Button_get")->setVisible(true);
    
    isAniEnd = false;
    playAni("Start0",false,[this](){
        
//        if(!isGetReward.at(RewardDays-1))
//        {//false 可以发放奖励
//            updateDay();
//            getReward();
//            _isGetClicked = true;
//            UIUtils::FIRFirestoreAdd("operator", {
//                {"key", Value("WinLayer")},
//                {"value", Value("free")}
//            });
//        }
        //动画结束
        isAniEnd = true;
    });
    
    
    
    updateUI();
    
    //多语言
    getNode<Text*>("Text_get")->setString(Lang("100170"));
    getNode<Text*>("Text_10")->setString(Lang("100253"));
    auto Text_5_0 = getNode<Text*>("Text_5_0");
    Text_5_0->setString(Lang("100255"));
    UIUtils::textAdaptiveSize(Text_5_0,400);
    getNode<Text*>("Text_getx2")->setString(Lang("100375"));
    //getNode<Text*>("Text_time")->setString(Lang("100256"));
}
void SevenDayView::initData()
{
    BaseLayer::initData();
    //
    
    setName("SevenDayView");
    EVENT_M->addListener("event_lobby_seven", [this](ValueMap valueMap, void *obj){
        updateAD();
        getReward(1);
        
    },this);
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
//    addEvent("event_lobby_seven", [this](EventCustom *e){
//        updateAD();
//        getReward(2);
//    });
}
void SevenDayView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn||!isAniEnd)return;//窗口弹出动画还未结束
    auto name = btn->getName();
    if(name == "Button_close"||name == "Panel_bg_0")
    {
        SCENE_M->getLobby()->isShowTop(true);
        fangCuo = -1;
        if (!_isGetClicked) {
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("SevenDayView")},
                {"value", Value("no")},
                {"v1", Value(DATA_M->getHaveVideo())}
            });
        }
        auto lobby = SCENE_M->getLobby();
        lobby->showGuide();
        lobby->updateSevenNew();
        this->removeFromParent();
        auto fishBg = SCENE_M->getGameBackground();
        fishBg->updateBuildComplete();
    }
    else if(name == "Button_getAD")
    {
        auto fishNum = DATA_M->getFishNum();
        auto isThreeOne = DATA_M->getSevenOneVec(0);
        auto isSevenOne = DATA_M->getSevenOneVec(1);
        if(((RewardDays == 3&&!isThreeOne)||(RewardDays == 7&&!isSevenOne))&&fishNum >= FISH_MAX_NUM)
        {
            //SCENE_M->showTips(Lang("100364"));
            FishGuideManager::getInstance()->fishMaxGuide();
        }
        else
        {
            DATA_M->playVideoAds(14);
            _isGetClicked = true;
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("SevenDayView")},
                {"value", Value("ad")},
            });
        }
        
    }
    else if(name == "Button_get")
    {
        oneOpen();
    }
}

void SevenDayView::updateUI()
{
    //当前应该领取的奖励
    
    if(isGetReward.at(RewardDays-1))
    {//true 已经领了
        getNode<Button*>("Button_get")->setEnabled(false);
    }
    if(isGetRewardAD.at(RewardDays-1))
    {
        getNode<Button*>("Button_getAD")->setVisible(false);
    }
    
    
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    updateCoin();
    updateDiamond();
}


void SevenDayView::getReward(int num)
{
    //今天奖励领过了
    DATA_M->setIsGetSevenReward(true);
    idxVec.clear();
    if(RewardDays == 1||RewardDays == 2||RewardDays == 5||RewardDays == 6)
    {//gold
        
        //魔法棒
        if(RewardDays > 0&&magicNum[RewardDays-1] > 0)
        {
            auto num = magicNum[RewardDays-1];
            REWARD_M->getReward(RewardManager::RewardType::Magic, num);//_goldNum[tag]);
            auto index = 6*100000;
            index += num;//_goldNum[tag];
            idxVec.push_back(index);
            SCENE_M->addDialog(DrawPropsView::createLayerN(idxVec,DrawPropsView::ViewType::Home));
        }
        
        auto FileNode = getNode(StringUtils::format("FileNode_%d",RewardDays));
        UIUtils::playInnerAction(FileNode, "Day1", false);
        auto poi = FileNode->getPosition();
        poi = FileNode->getParent()->convertToWorldSpace(poi);
        
        auto goldNum = rewardVec.at(RewardDays-1);
        if(!isGetReward.at(RewardDays-1))
        {
            goldNum = num*goldNum;
        }
        
        //DATA_M->setCoinNum(goldNum,true);
        SCENE_M->getLobby()->goldAni(goldNum,this,poi,[goldNum,this](){
            //updateDay();
            DATA_M->setCoinNum(goldNum, true, 113);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            
        },[this](){
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
                SCENE_M->getLobby()->playGoldAni(1, true);
            }
        },[this](){
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
                SCENE_M->getLobby()->playGoldAni(1, false);
            }
            
        });
        //RewardDays+=1;
        
    }
    else if(false)
    {//钻石改金币啦
//        auto FileNode = getNode(StringUtils::format("FileNode_%d",RewardDays));
//        auto poi = FileNode->getPosition();
//        poi = FileNode->getParent()->convertToWorldSpace(poi);
//        auto dimNum = rewardVec.at(RewardDays-1);
//        if(!isGetReward.at(RewardDays-1))
//        {
//            dimNum = num*dimNum;
//        }
//        //DATA_M->setDiamond(dimNum,true);
//        SCENE_M->getLobby()->diamondAni(dimNum,this,poi,[dimNum,this](){
//            //updateDay();
//            DATA_M->setDiamond(dimNum);
//            ValueMap valueMap{
//                {"isTime",Value{true}}
//            };
//            //更新有金币显示
//            EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//        },[this](){
//            //daily
//            if(fangCuo == 10)
//            {
//                //SOUND_M->playEffectMusic(EffectGetGem);
//                auto img_icon_diamond = this->getNode("img_icon_top_diamond");
//                auto FileNode_diamond = this->getNode("FileNode_diamond");
//                img_icon_diamond->setVisible(false);//(!isPlay);
//                FileNode_diamond->setVisible(true);
//                UIUtils::playInnerAction(FileNode_diamond,"Baoshi",false);
//            }
//            else
//            {
//                SCENE_M->getLobby()->playDiamondAni(1, true);
//            }
//
//        },[this](){
//            //daily
//            if(fangCuo == 10)
//            {
//                //SOUND_M->playEffectMusic(EffectGetGem);
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
        auto FileNode = getNode(StringUtils::format("FileNode_%d",RewardDays));
        UIUtils::playInnerAction(FileNode, "Day1", false);
        auto poi = FileNode->getPosition();
        poi = FileNode->getParent()->convertToWorldSpace(poi);
        
        auto goldNum = rewardVec.at(RewardDays-1);
        if(!isGetReward.at(RewardDays-1))
        {
            goldNum = num*goldNum;
        }
        
        //DATA_M->setCoinNum(goldNum,true);
        SCENE_M->getLobby()->goldAni(goldNum,this,poi,[goldNum,this](){
            //updateDay();
            DATA_M->setCoinNum(goldNum, true, 114);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            
        },[this](){
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
                SCENE_M->getLobby()->playGoldAni(1, true);
            }
        },[this](){
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
                SCENE_M->getLobby()->playGoldAni(1, false);
            }
            
        });
        
    }
    else if(RewardDays == 3)
    {//鱼
        //魔法棒
        if(RewardDays > 0&&magicNum[RewardDays-1] > 0)
        {
            auto num = magicNum[RewardDays-1];
            REWARD_M->getReward(RewardManager::RewardType::Magic, num);//_goldNum[tag]);
            auto index = 6*100000;
            index += num;//_goldNum[tag];
            idxVec.push_back(index);
            
            auto type = (int)_type;
            SCENE_M->addDialog(DrawPropsView::createLayerN(idxVec,DrawPropsView::ViewType::Home));
        }
        auto isOne = DATA_M->getSevenOneVec(0);
        if(!isOne)
        {//还能领鱼
            isOne = true;
            DATA_M->setSevenOneVec(0,true);
            //给鱼
            auto fishNum = DATA_M->getFishNum();
            if(fishNum >= FISH_MAX_NUM)
            {
                
            }
            else
            {
                auto fashTank = SCENE_M->getGameBackground();
                fashTank->addFish(0);
            }
            //更新显示
            auto node = getNode(StringUtils::format("FileNode_%d",3));
            auto reward = node->getChildByName(StringUtils::format("Panel_reward%d",3));
            
            auto BitmapFontLabel_1 = FIND_NODE(TextBMFont*, reward, "BitmapFontLabel_1");
            auto BitmapFontLabel_magic = FIND_NODE(TextBMFont*, reward, "BitmapFontLabel_magic");
            auto Node_icon = FIND_NODE(Node*, reward, "Node_icon");
            auto Node_icon_fish = FIND_NODE(Node*, reward, "Node_icon_fish");
            Node_icon->setVisible(isOne);
            Node_icon_fish->setVisible(!isOne);
            BitmapFontLabel_1->setString(StringUtils::format("+%d",rewardVec.at(3-1)));
            BitmapFontLabel_magic->setString(StringUtils::format("x%d",magicNum.at(3-1)));
        }
        auto FileNode = getNode(StringUtils::format("FileNode_%d",RewardDays));
        UIUtils::playInnerAction(FileNode, "Day1", false);
        auto poi = FileNode->getPosition();
        poi = FileNode->getParent()->convertToWorldSpace(poi);
        
        auto goldNum = rewardVec.at(RewardDays-1);
        if(!isGetReward.at(RewardDays-1))
        {
            goldNum = num*goldNum;
        }
        
        //DATA_M->setCoinNum(goldNum,true);
        SCENE_M->getLobby()->goldAni(goldNum,this,poi,[goldNum,this](){
            //updateDay();
            DATA_M->setCoinNum(goldNum, true, 115);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            
        },[this](){
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
                SCENE_M->getLobby()->playGoldAni(1, true);
            }
        },[this](){
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
                SCENE_M->getLobby()->playGoldAni(1, false);
            }
            
        });
    }
    else if(RewardDays == 4)
    {//抽奖 关闭本窗口
        //魔法棒
        int index = -1;
        if(RewardDays > 0&&magicNum[RewardDays-1] > 0)
        {
            auto num = magicNum[RewardDays-1];
            REWARD_M->getReward(RewardManager::RewardType::Magic, num);//_goldNum[tag]);
            index = 6*100000;
            index += num;//_goldNum[tag];
        }
        if(!isGetReward.at(RewardDays-1))
        {//普通奖励没有领
            if(num == 2)
            {
                getNode<Button*>("Button_get")->setEnabled(true);
            }
            else
            {

            }
        }
        auto FileNode = getNode(StringUtils::format("FileNode_%d",RewardDays));
        UIUtils::playInnerAction(FileNode, "Day1", false);
        auto fanpai = SCENE_M->getFanPaiRewardView();
        if(!fanpai)
        {
            fanpai = FanPaiRewardView::createLayerN(3,FanPaiRewardView::Type::SevenGold);
            SCENE_M->addDialog(fanpai);
        }
        fanpai->setRewardNum(3);
        fanpai->setType(FanPaiRewardView::Type::SevenGold);
        fanpai->setConsumptionType(FanPaiRewardView::ConsumptionType::Gold);
        fanpai->startFanPai();
        if(index != -1)
        {
            fanpai->addIdxVec(index);
        }
        
        //RewardDays++;
        //updateDay();
        
        SCENE_M->removeLayer(this);
        
        auto lobby = SCENE_M->getLobby();
        lobby->openReward(true);
        lobby->isShowTop(false);
        return;
    }
    else if(RewardDays == 7)
    {//抽奖
        //魔法棒
        int index = -1;
        if(RewardDays > 0&&magicNum[RewardDays-1] > 0)
        {
            auto num = magicNum[RewardDays-1];
            REWARD_M->getReward(RewardManager::RewardType::Magic, num);//_goldNum[tag]);
            index = 6*100000;
            index += num;//_goldNum[tag];
        }
        if(!isGetReward.at(RewardDays-1))
        {//普通奖励没有领
            if(num == 2)
            {
                getNode<Button*>("Button_get")->setEnabled(true);
            }
            else
            {

            }
        }
        
        auto FileNode = getNode(StringUtils::format("FileNode_%d",RewardDays));
        UIUtils::playInnerAction(FileNode, "Day1", false);
        auto fanpai = SCENE_M->getFanPaiRewardView();
        if(!fanpai)
        {
            fanpai = FanPaiRewardView::createLayerN(3,FanPaiRewardView::Type::SevenDiamond);
            SCENE_M->addDialog(fanpai);
        }
        fanpai->setRewardNum(3);
        fanpai->setType(FanPaiRewardView::Type::SevenDiamond);
        fanpai->setConsumptionType(FanPaiRewardView::ConsumptionType::Diamond);
        fanpai->startFanPai();
        if(index != -1)
        {
            fanpai->addIdxVec(index);
        }
        
        auto isOne = DATA_M->getSevenOneVec(1);
        if(!isOne)
        {//还能领鱼
            DATA_M->setSevenOneVec(1,true);
            //给鱼
            auto fishNum = DATA_M->getFishNum();
            if(fishNum >= FISH_MAX_NUM)
            {
                
            }
            else
            {
                auto fashTank = SCENE_M->getGameBackground();
                fashTank->addFish(1);
            }
            //更新显示
            auto node = getNode(StringUtils::format("FileNode_%d",7));
            auto reward = node->getChildByName(StringUtils::format("Panel_reward%d",7));
            
            auto BitmapFontLabel_1 = FIND_NODE(TextBMFont*, reward, "BitmapFontLabel_1");
            auto BitmapFontLabel_magic = FIND_NODE(TextBMFont*, reward, "BitmapFontLabel_magic");
            auto Node_icon = FIND_NODE(Node*, reward, "Node_icon");
            auto Node_icon_fish = FIND_NODE(Node*, reward, "Node_icon_fish");
            Node_icon->setVisible(isOne);
            Node_icon_fish->setVisible(!isOne);
            BitmapFontLabel_1->setString(StringUtils::format("+%d",rewardVec.at(7-1)));
            BitmapFontLabel_magic->setString(StringUtils::format("x%d",magicNum.at(7-1)));
        }
        
        //RewardDays++;
        //updateDay();
        
        
        SCENE_M->removeLayer(this);
        auto lobby = SCENE_M->getLobby();
        lobby->openReward(true);
        lobby->isShowTop(false);
        return;
    }
    //this->setVisible(false);
}

void SevenDayView::updateDay()
{
    auto tm = DATA_M->getContentTime();
    //记录年份
    lastYear = tm->tm_year+1900;
    GETINTEGER("lastYear",lastYear);
    lastYDay = tm->tm_yday;
    SETINTEGER("lastYDay",lastYDay);
    SETBOOL(StringUtils::format("isGetReward%d",RewardDays-1).c_str(),true);
    auto &vec = isGetReward;
    vec.at(RewardDays-1) = true;
    getNode<Button*>("Button_get")->setEnabled(false);
}

void SevenDayView::updateAD()
{
    if(RewardDays == 4||RewardDays == 7)
    {
        
    }
    else
    {
        //updateDay();
    }
    auto tm = DATA_M->getContentTime();
    //记录年份
    lastYear = tm->tm_year+1900;
    GETINTEGER("lastYear",lastYear);
    lastYDay = tm->tm_yday;
    SETINTEGER("lastYDay",lastYDay);
    
    SETBOOL(StringUtils::format("isGetRewardAD%d",RewardDays-1).c_str(),true);
    auto &vec = isGetRewardAD;
    vec.at(RewardDays-1) = true;
    getNode<Button*>("Button_getAD")->setEnabled(false);
}

void SevenDayView::initDay()
{
    SETINTEGER("RewardDays",1);//每领取一遍奖励 累计+1
    RewardDays = 1;
    isGetReward.clear();
    isGetRewardAD.clear();
    for(int i = 0;i < 7;++i)
    {
        SETBOOL(StringUtils::format("isGetReward%d",i).c_str(),false);
        SETBOOL(StringUtils::format("isGetRewardAD%d",i).c_str(),false);
        isGetReward.push_back(false);
        isGetRewardAD.push_back(false);
    }
}


void SevenDayView::updateCoin(bool isDelay)
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

void SevenDayView::updateDiamond(bool isDelay)
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

void SevenDayView::onEnter()
{
    BaseLayer::onEnter();
    UIUtils::FIRAnalyticsEventWithPrefix("SevenDayView");
}
void SevenDayView::onExit()
{
    BaseLayer::onExit();
    SCENE_M->getLobby()->isShowTop(true);
    EVENT_M->removeListener("event_lobby_seven",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
    EVENT_M->removeListener("event_game_update_coin",this);
}

bool SevenDayView::lianXu()
{
    auto tm = DATA_M->getContentTime();
    auto year = tm->tm_year+1900;
    bool isRunNian = false;
    if(year%100 == 0)
    {//世纪年
        isRunNian = year%400 == 0;
    }
    else
    {//普通年
        isRunNian = year%4 == 0;
    }
    int dayMax = isRunNian?366:365;
    auto yday = DATA_M->getYDay();
    bool isLianXu = false;
    if(yday - lastYDay == 1&&year == lastYear)
    {//连续天数 可以连续领取奖励
        isLianXu = true;
    }
    else if(yday == 1&&lastYDay==dayMax&&year - lastYear == 1)
    {//是连续天数
        isLianXu = true;
    }
    else if(year - lastYear > 1)
    {//不连续
        isLianXu = false;
    }
    else if(yday - lastYDay > 1&&year == lastYear)
    {//不连续
        isLianXu = false;
    }
    else
    {//不连续
        isLianXu = false;
    }
    
    //不是同一天 返回true 并且签到天数变为1
    auto isOne = tm->tm_wday == 1&&RewardDays != 0;
    
    //是连续的并且不是周一
    return isLianXu&&!isOne;
}

void SevenDayView::oneOpen()
{
    auto fishNum = DATA_M->getFishNum();
    auto isThreeOne = DATA_M->getSevenOneVec(0);
    auto isSevenOne = DATA_M->getSevenOneVec(1);
    if(((RewardDays == 3&&!isThreeOne)||(RewardDays == 7&&!isSevenOne))&&fishNum >= FISH_MAX_NUM)
    {
        //SCENE_M->showTips(Lang("100364"));
        FishGuideManager::getInstance()->fishMaxGuide();
    }
    else
    {
        updateDay();
        getReward();
        _isGetClicked = true;
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("SevenDayView")},
            {"value", Value("free")}
        });
    }
}
