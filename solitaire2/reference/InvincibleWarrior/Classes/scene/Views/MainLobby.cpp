
#include "MainLobby.h"
#include "HomeSetting.h"
#include "BackView.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#endif

#include "GameViewHD.hpp"
//#include "PlayerManager.h"
#include "HomeView.h"
#include "LevelViewHD.h"
#include "MissionView.h"
#include "DailyView.h"
#include "DailyNode.h"
#include "DailyMoreView.h"
#include "ShopViewHD.h"
#include "UIUtils.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
//shangdian
#include "StoreView.h"
#include "RewardManager.h"
//背包
#include "BagView.h"
#include "ShopManager.h"
#include "GrowupNode.h"
#include "FanPaiAD.h"
#include "FanPaiRewardView.h"
#include "StarBoxView.h"
#include "DailytaskView.h"
#include "SevenDayView.h"
#include "ShareRewardView.h"
#include "FreeCoinLayer.h"
#include "RewardRouletteView.h"
#include "PlayerManager.h"
#include "TaskManager.h"
#include "TeachManager.h"

#include "EventObserver.h"
#include "Currency.h"
#include "StarNode.h"
#include "ScoreManager.h"
#include "GameBackground.h"
#include "FishShop.h"
#include "FashTankShop.h"
#include "LevelUpView.h"
#include "FishManager.h"
#include "GoldShop.h"
#include "FishGuideManager.h"
#include "SubscriptionView.h"
#include "ChallengeModeView.h"

const string LOBBYNEW = "img_new_lobby_%d";

using namespace spine;
vector<Color3B> LobbyColors {Color3B(39, 161, 255), Color3B(39, 161, 255),};

MainLobby::MainLobby()
:BaseLayer("2020Dating_0.csb")
{
    taskNewNum = GETINTEGER("taskNewNum",1);
    sevenNewNum = GETINTEGER("sevenNewNum",1);
    storeNewNum = GETINTEGER("storeNewNum",1);
    setNewNum = GETINTEGER("setNewNum",0);
    
    _oldTab = GETINTEGER("_oldTab",0);
    _excludeRecord = true; // 不要记录进入
    isStart = false;
    isGoGameView = false;
    isAppStart = true;
}

MainLobby::~MainLobby() {

}

void MainLobby::initUI() {
    BaseLayer::initUI();
    doLayout();
    getNode<Button*>("Button_100exp")->setTitleText("110经验");
    getNode<Button*>("Button_unLock")->setTitleText("解锁");
    getNode("Button_Dailytasks")->setVisible(false);
    // 为了记录数据
    onRecordEnter();
    UIUtils::FIRAnalyticsTrackScreens("MainLobby");
    
//    TaskManager::getInstance();
    gameView = SCENE_M->getGameView();
    //gameView->setVisible(false);
    
    auto is = DATA_M->getStartOne();
    auto isDailyLevelUnlock = TEACH_M->isDailyLevelUnlock();
    auto num = ScoreManager::getInstance()->getWinTotalCNT(true);
//    auto isTaskUnlock = TEACH_M->isTaskUnlock();
    if(true)//is || !isDailyLevelUnlock || num < 2)
    {
        SETBOOL("isStartOne",false);
        gameView->resetOne();
        this->setVisible(false);
    }
    else
    {
        if(TEACH_M->isTaskAllEnd())
        {//大厅任务结束
            //每日首次登陆显示签到
            auto isDay = DATA_M->sevenDayIsYday();
            if(isDay)
            {
                isShowTop(false);
                auto sevenDayView = SevenDayView::createLayerN();
                this->addChild(sevenDayView);
            }
        }
        //gameView->setVisible(false);
    }
    //gameView->setVisible(true);
    //this->setVisible(false);
    FileNode_fish = getNode("FileNode_fish");
    FileNode_fashTank = getNode("FileNode_fashTank");
    FileNode_play = getNode("FileNode_play");
    UIUtils::playInnerAction(FileNode_fish, "fishIdle", false);
    UIUtils::playInnerAction(FileNode_fashTank, "tankIdle", false);
    
    main_tips1_Task = getNode("main_tips1_Task");
    main_tips1_Task->setVisible(is);
    lobby_fashTank_tips = getNode("lobby_fashTank_tips");
    lobby_fish_tips = getNode("lobby_fish_tips");
    lobby_fashTank_tips->setVisible(false);
    lobby_fish_tips->setVisible(false);
    
    FileNode_gold = getNode("FileNode_gold");
    auto LevelBG_1 = FileNode_gold->getChildByName("LevelBG_1");
    LevelBG_1->setOpacity(0);
    auto coinNum = DATA_M->getCoinNum();
    main_tips1_Task->setVisible(taskNewNum == 1);
    getNode("main_tips1_1")->setVisible(sevenNewNum == 1);
    Panel_home = getNode("Panel_home");
    
    auto gameNum = ScoreManager::getInstance()->getWinTotalCNT(true);

    getNode("Button_daily")->setVisible(gameNum >= 3);

//    _rootLayers.pushBack(HomeView::createLayerN(this));
    //_rootLayers.pushBack(VegasView::createLayer(false,this));
//    _rootLayers.pushBack(MissionView::createLayerN(this));
//    _rootLayers.pushBack(DailyView::createLayerN(this));
//    _rootLayers.pushBack(StoreView::createLayerN(this));
//    auto daily = dynamic_cast<DailyView*>(_rootLayers.at((int)Tab::Daily));

    //判断当天的每日完成度
    auto date = DailyManager::getInstance()->today();//daily->getSelectedNode();
    auto completeCNT = DailyManager::getInstance()->getCompleteCNT(date);
    
    
    panel_root = getNode("Panel_root");
    panel_root->setPosition(panel_root->convertToNodeSpace(Vec2::ZERO));
    
    // kongjin
    Image_bottom = getNode("Panel_bottom");
    updatePage(1);
    
//    string spineFile = "res/Scenes";
//    auto skeNode = SkeletonAnimation::createWithJsonFile(spineFile+".json", spineFile+".atlas", 1.f);
//    skeNode->setAnimation(0, "home", true);
//    getNode("Node_leaf")->addChild(skeNode);
    FileNode_top = getNode("FileNode_top");
    FileNode_MyBag = getNode("FileNode_MyBag");
    FileNode_StarBox = getNode("FileNode_StarBox");
    FileNode_StarBox2 = getNode("FileNode_StarBox2");
    FileNode_CrownBox2 = getNode("FileNode_CrownBox2");
    Node_rewardAni = getNode("Node_rewardAni");
    FileNode_LunPan = getNode("FileNode_LunPan");
    //商店按钮宝箱
    FileNode_StoreBox = getNode("FileNode_StoreBox");
    
    Button_LunPan = getNode<Button*>("Button_LunPan");
    Button_Sign_AD = getNode<Button*>("Button_Sign_AD");
    Button_fanPai = getNode<Button*>("Button_fanPai");
    Button_share = getNode<Button*>("Button_share");
    Button_share->setVisible(false);
    Button_Collect = getNode<Button*>("Button_Collect");
    
//    auto isPlayAds = DATA_M->getLimit();
//    if(isPlayAds&&!DATA_M->showNativeAds(2, "MainLobby"))
//    {
//        Button_LunPan->setVisible(false);
//        Button_Sign_AD->setVisible(false);
//        Button_fanPai->setVisible(false);
//    }
    
    
    schedule([this](float dt){
        refushGift();
    }, 10, "mainlobby_reward_refushGift");
    
    //更新离线时间
    DATA_M->updateOfflineTime();
    schedule([this](float dt){
        DATA_M->updateOfflineTime();
    }, 2, "mainlobby_updateOfflineTime");
    
    //视频奖励冷却时间
    Text_Sign_AD = getNode<Text*>("Text_Sign_AD");
    Image_Sign_AD = getNode("Image_Sign_AD");
    schedule([this](float dt){
        auto time = DATA_M->getNextFreeCoinTime();
        if(time > 0)
        {
            Image_Sign_AD->setVisible(true);
            int fen = (int)(time / 60);
            int miao = (int)((int)time % 60);
            Text_Sign_AD->setString(StringUtils::format("%02d:%02d", fen, miao));
        }
        else
        {
            Image_Sign_AD->setVisible(false);
            Button_Sign_AD->setEnabled(true);
        }
    }, "mainlobby_reward_Text_Sign_AD");
    
    Text_challenge_time = getNode<TextBMFont*>("BitmapFontLabel_challenge");
    auto time = DATA_M->getNextFreeCoinTime5();
    int h = (int)(time / 3600);
    int m = (int)((int)time % 3600);
    m = (int)((int)m / 60);
    Text_challenge_time->setString(StringUtils::format("%02d:%02d", h, m));
    
    schedule([this](float dt){
        if(DATA_M->getIsChallenge())
        {
            auto time = DATA_M->getNextFreeCoinTime5();
            
            auto num = DATA_M->getChallengeNum();
            
            if(time > 0)
            {
                int h = (int)(time / 3600);
                int m = (int)((int)time % 3600);
                m = (int)((int)m / 60);
                Text_challenge_time->setString(StringUtils::format("%02d:%02d", h, m));
            }
            else if(num < challengeMax)
            {//48小时过了并且没完成，下一轮了
                DATA_M->setIsChallenge(false);
                getNode("btn_challenge")->setVisible(false);
                //ATA_M->setFreeCoinTime5(DATA_M->getContentSec());
                //累积清零
                DATA_M->addChallengeNum(true);
            }
        }
    },1, "lobby_challenge");
    
    //升级窗口
    LevelUpView = LevelUpView::createLayerN();
    LevelUpView->setType(LevelUpView::Type::Lobby);
    this->addChild(LevelUpView, 2);
    LevelUpView->setVisible(false);
    Text_level_up = LevelUpView->getNode<Text*>("Text_level_up");
    //经验
    _Text_level = getNode<TextBMFont*>("BitmapFontLabel_level");
    _LoadingBar_level = getNode<LoadingBar*>("LoadingBar_level");
    schedule([this](float dt){
        if(isBar)
        {
            //定时器
            if(lv == oldLv)
            {//lv == oldLv从percent2涨到percent1
                percent2+=percentDx/0.03 * dt;
                if(percent2 > percent1)
                {
                    percent2 = percent1;
                    isBar = false;
                }
                _LoadingBar_level->setPercent(percent2);
            }
            else if(lv > oldLv)
            {// lv > oldLv 从percent2涨到100;再从0涨到percent1
                percent2+=percentDx/0.03 * dt;
                if(percent2 > percent1&&dLv == lv-oldLv)
                {
                    percent2 = percent1;
                }
                
                if(percent2 > 100)
                {
                    dLv++;
                    percent2 = 0;
                    isQieHuan = true;
                    
                    _Text_level->setString(StringUtils::format("%d",dLv + oldLv));
                }
                else if(percent2 >= percent1&&isQieHuan&&dLv == lv-oldLv)
                {
                    percent2 = percent1;
                    isBar = false;
                    isQieHuan = false;
                    //升级动画
                    SOUND_M->playEffectMusic(EffectLevelup);
                    Text_level_up->setString(StringUtils::toString(lv));

                    LevelUpView->setVisible(true);

                    LevelUpView->playUpAni();
                }
                
                _LoadingBar_level->setPercent(percent2);
            }
        }
        else
        {
            dLv = 0;
        }
    }, 0.03, "scheduler_update_bar");

    auto btn = getNode("Button_start");
    auto poi = btn->getPosition();
    BtnStartPoi = btn->getParent()->convertToWorldSpace(poi);
    
    UIUtils::playInnerAction(FileNode_LunPan, "Start0", true);
    auto bt = getNode<Button*>("Button_addFish");
    bt->setTitleFontSize(28);
    updateFishNum();
    auto isYDay = DATA_M->newVerIsYday();
    
    if(isYDay)
    {//每天只显示一次
        updateNewVersion();
    }
    else
    {
        updateNewVersion(false);
    }
    
    //更新喂食按钮显示
    auto fashTank = SCENE_M->getGameBackground();
    showWeiShiBtn(!fashTank->getIsMaxHp());
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainLobby::myTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(MainLobby::myTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainLobby::myTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MainLobby::myTouchEnded, this);
    _eventDispatcher->addEventListenerWithFixedPriority(listener, -129);
    
    // 多语言
    updateDYY();
    auto Text_StarNum_ = FIND_NODE(Text*, FileNode_StarBox,"Text_StarNum_");
    auto Text_CrownNum_ = FIND_NODE(Text*, FileNode_StarBox,"Text_CrownNum_");
    Text_StarNum_->setString("/");
    Text_CrownNum_->setString("/");
    //修正宝箱文本位置
    auto starSize = Text_StarNum_->getBoundingBox().size;
    auto crownSize = Text_CrownNum_->getBoundingBox().size;
    Text_StarNum_->getChildByName("BitmapFontLabel_StarNum")->setPosition(Vec2(starSize.width*-0.4f,starSize.height*0.5));
    Text_StarNum_->getChildByName("BitmapFontLabel_StarNumMax")->setPosition(Vec2(starSize.width*1.5f,starSize.height*0.5));
    Text_CrownNum_->getChildByName("BitmapFontLabel_CrownNum")->setPosition(Vec2(crownSize.width*-0.4f,crownSize.height*0.5));
    Text_CrownNum_->getChildByName("BitmapFontLabel_CrownNumMax")->setPosition(Vec2(crownSize.width*1.5f,crownSize.height*0.5));
    
    
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (AdsManager::bannerInit) {
//cuo        moveOffsetY = LobbyBannerHeight;
        //updateUI();
    }
#endif
    _currentTab = Tab::Home;
    //setTab((Tab)Tab::Home);
    
//    TEACH_M->startTeach("lobby_test");
//    TEACH_M->nextTeachStep(this);
    if (!TEACH_M->isTeaching()) { // 大厅触发的教学
        TEACH_M->triggerTeach("lobby_times2", this);
    }
}

void MainLobby::setViewShow()
{
    for (int i=0;i<_rootLayers.size();++i) {
        _rootLayers.at(i)->setVisible(i == int(_currentTab));
        if(i == int(_currentTab)&&Tab::Daily == _currentTab)
        {
            auto daily = dynamic_cast<DailyView*>(_rootLayers.at(i));
//cuo            daily->playAni();
        }
    }
}
Node* MainLobby::setTab(Tab tab)
{
    //记录当前选择的模式 退出游戏后 再次打开显示退出前所在的模式
    if(_oldTab != (int)tab)
    {
        if(tab == Tab::Store)
        {
            _oldTab = (int)Tab::Home;
        }
        else
        {
            _oldTab = (int)tab;
        }
        SETINTEGER("_oldTab",_oldTab);
    }
    
    if(tab != Tab::Store)
    {//隐藏奖品描述
//        auto store = StoreView::createLayerN(this);//dynamic_cast<StoreView*>(_rootLayers.at((int)Tab::Store));
//        store->showMiaoShu(false);
    }
    if (tab == Tab::Store&&0) {
        //SCENE_M->addDialog(ShopViewHD::createLayerN(this));
//        for (int i=0;i<_rootLayers.size();++i) {
//            _rootLayers.at(i)->setVisible(i == int(tab));
//            if(i == 2)
//            {
//                auto daily = dynamic_cast<DailyView*>(_rootLayers.at(i));
////cuo                daily->stopAni();
//            }
            //getNode<Button*>(StringUtils::format("Button_tab%d", i))->setEnabled(i!=int(tab));
//        }StoreView
        SCENE_M->addDialog(StoreView::createLayerN(this));
        this->setVisible(false);
        return nullptr;
    }
    else if (_currentTab != tab) {
        
        Panel_home->setVisible(tab != Tab::Store);
        auto newColor = LobbyColors.at(cocos2d::random(1, (int)LobbyColors.size()-1));
        //getNode<ImageView*>("Sprite_bg")->runAction(TintTo::create(0.5, newColor.r, newColor.g, newColor.b));
        _currentTab = tab;
        panel_root->removeAllChildren();
        BaseLayer* childLayer = nullptr;
        switch (tab) {
            case Tab::Home:
                childLayer = HomeView::createLayerN(this);
                childLayer->setName("HomeView");
                break;
//            case Tab::Daily:
//                childLayer = DailyView::createLayerN(this);
//                childLayer->setName("DailyView");
//                break;
//            case Tab::Level:
//                childLayer = MissionView::createLayerN(this);
//                childLayer->setName("MissionView");
//                break;
//            case Tab::Store:
//                childLayer = StoreView::createLayerN(this);
//                childLayer->setName("StoreView");
//                break;
            default:
                break;
        }
//        auto childLayer = _rootLayers.at((int)tab);
        panel_root->addChild(childLayer);
//        auto id = (int)tab;
//        for (int i=0;i<_rootLayers.size();++i) {
//            _rootLayers.at(i)->setVisible(i == id);
        for (int i=0;i<(int)Tab::None;++i) {
            auto str = StringUtils::format("Button_tab%d", i);
            getNode<Button*>(str)->setEnabled(i!=int(tab));
        }
        updateUI();
        TEACH_M->nextTeachStep(this);
        if (TEACH_M->isTeaching())
            UIUtils::FIRAnalyticsEventWithPrefix(string("setTab_") + toString(int(_currentTab)) + "_" + TEACH_M->getCurrentTeachKey(), "teach");
        return childLayer;
    }
    
//    return _rootLayers.at((int)tab);
    return panel_root->getChildren().at(0);
}

void MainLobby::initData() {
    BaseLayer::initData();
    setName("MainLobby");

    // 监听广告
    scaleFactor = Director::getInstance()->getOpenGLView()->getFrameSize().height/Director::getInstance()->getWinSize().height;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    scaleFactor = AdsManager::getFrameScaleFactor()/scaleFactor;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto density = UIUtils::getDensity();
    scaleFactor = density/scaleFactor;
#endif
    
    addEvent("jni_event_custom_callcppwithstring", [this](EventCustom *eventCustom){
        CCLOG("jni_event_custom_callcppwithstring call c++:(%f)", scaleFactor);
        auto params = (__String*)eventCustom->getUserData();
        rapidjson::Document d;
        //        std::string load_str(params, strlen(params));
        d.Parse<0>(params->getCString());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        params->release();
#endif
        if (d.HasParseError())
        {
            return;
        }
        if (d.IsObject()) {
            if (d.HasMember("msg")) {
                string msg(d["msg"].GetString());
                if (msg == "msg_banner_show") {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//                    moveOffsetY = d["height"].GetDouble()*scaleFactor;
//#else
//                    moveOffsetY = 54*scaleFactor;
//#endif
//                    this->updateUI();
                }
                else if (msg == "msg_banner_hide") {
//                    moveOffsetY = 0;
//                    this->updateUI();
                }
                else if (msg == "msg_video_ready") {
//                    DATA_M->isHaveAds = true;
                    refushGift();
                }
                else if (msg == "mag_reward_getcoin") {
//                    DATA_M->isHaveAds = false;
                    //获得金币
                    Director::getInstance()->getScheduler()->performFunctionInCocosThread( [=]() {
                        DATA_M->lingqujinbi(0);
                        DATA_M->playLingQUAction();
                    });
                }
                else if (msg == "mag_reward_seemore") {
                    
                }
                else if (msg == "mag_interstitial_close") {

                }
            }
            
        }
    });

    EVENT_M->addListener("jni_event_new_callcpp", [this](ValueMap valueMap, void *obj){
        CCLOG("new_jni_event_custom_callcppwithstring call c++:(%f)", scaleFactor);
        auto params = valueMap["value"].asString();
        rapidjson::Document d;
        //        std::string load_str(params, strlen(params));
        d.Parse<0>(params.c_str());
        if (d.HasParseError())
        {
            return;
        }
        if (d.IsObject()) {
            if (d.HasMember("msg")) {
                string msg(d["msg"].GetString());
                if (msg == "msg_banner_show") {
                    updateBanner();
                }
            }
        }
    }, this);

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
    EVENT_M->addListener("msg_game_lingqu",[this](ValueMap valueMap, void *obj){
        //领取金币
        auto lobby = SCENE_M->getLobby();
        lobby->goldAni(DATA_M->getRewardCoin1(),nullptr,Vec2(2000,2000),[this](){
            DATA_M->setCoinNum(DATA_M->getRewardCoin1(),true,105);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            //updateCoin(true);
        },[lobby,this](){
        //home
           // SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni(1,true);
        },[lobby,this](){
            //home
            //SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni(1,false);
            //SCENE_M->removeLayer(this);
        });
    },this);
//    addEvent("msg_game_lingqu", [this](EventCustom*) {
//        
//    });
    EVENT_M->addListener("msg_game_showwin",[this](ValueMap valueMap, void *obj){
        if (InterstitialCB) {
            InterstitialCB();
            InterstitialCB = nullptr;
        }
        
//        //重置限制插屏的cd
//        auto timeNow = std::time(0);
//        DATA_M->setInterstitialTime();
//        DATA_M->setIsVideoAdsTime(true);
//        DATA_M->setVideoAdsTime(0,true);//重置激励视频对插屏的限制cd
//        DATA_M->setIsShowAds(false);
    },this);
}

void MainLobby::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr||!isTouch) {
        return;
    }
    auto btnName = btn->getName();
    if(dynamic_cast<Button*>(btn))
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
//        updateStar();
    }
    
    
    if (btnName.find("Button_tab") != string::npos) {
        isShowFanPai = false;//翻牌不显示，改为轮盘
        //refushGift();//更新
        auto tag = btn->getTag();
        if(tag != 0)
        {
            auto newTips = getNode(StringUtils::format(LOBBYNEW.c_str(),tag));
            if(tag == 3&&newTips->isVisible())
            {//商店
                
                storeNewNum = 0;
                SETINTEGER("storeNewNum",0);
            }
            newTips->setVisible(false);
        }
        if(_currentTab == Tab::Daily&&(Tab)tag != Tab::Daily)
        {
//            auto daily = dynamic_cast<DailyView*>(_rootLayers.at((int)Tab::Daily));
//            daily->hideStart();
        }

        if(TEACH_M->isTaskAllEnd())
        {//任务完成后打开 用在新手引导完成时自动弹出签到窗口
//            auto isDay = DATA_M->sevenDayIsYday();
//            if(isDay)
//            {
//                isShowTop(false);
//                auto sevenDayView = SevenDayView::createLayerN();
//                this->addChild(sevenDayView);
//            }
        }
        setTab((Tab)tag);
    }
    else if (btnName == "Button_CrownBox")
    {//starBox
        isShowFanPai = false;//翻牌不显示，改为轮盘
        //refushGift();//更新
        auto num1 = DATA_M->getDailyStarBoxNum();
        auto num2 = DATA_M->getDailyStarBoxNumMax();
        if(num1 >= num2)
        {
            openReward(true);
            auto fanpai = SCENE_M->getFanPaiRewardView();
            if(!fanpai)
            {
                fanpai = FanPaiRewardView::createLayerN(1,FanPaiRewardView::Type::Daily);
                SCENE_M->addDialog(fanpai);
            }
            fanpai->setRewardNum(1);
            fanpai->setConsumptionType(FanPaiRewardView::ConsumptionType::None);
            fanpai->setType(FanPaiRewardView::Type::Daily);
            fanpai->startFanPai();
        }
        else
        {
            SCENE_M->addDialog(StarBoxView::createLayerN(StarBoxView::Type::Daily));
        }
    }
    else if (btnName == "Button_Set") {  // 设置
        
        showSetting();
        updateNewVersion(false);
        isShowFanPai = false;//翻牌不显示，改为轮盘
        //refushGift();//更新
    }
    else if (btnName == "Button_StarBox"|| btnName == "Button_Collect")
    {//starBox
        
        isShowFanPai = false;//翻牌不显示，改为轮盘
        //refushGift();//更新
        auto num1 = DATA_M->getStarBoxNum();
        auto num2 = DATA_M->getStarBoxNumMax();
        if(num1 >= num2)
        {
            openReward(true);
            isShowTop(false);
            auto fanpai = SCENE_M->getFanPaiRewardView();
            if(!fanpai)
            {
                fanpai = FanPaiRewardView::createLayerN(1,FanPaiRewardView::Type::Home);
                SCENE_M->addDialog(fanpai);
            }
            fanpai->setRewardNum(1);
            fanpai->setConsumptionType(FanPaiRewardView::ConsumptionType::None);
            fanpai->setType(FanPaiRewardView::Type::Home);
            fanpai->startFanPai();
            
        }
        else
        {
            if(_currentTab == MainLobby::Tab::Home)
            {
                SCENE_M->addDialog(StarBoxView::createLayerN(StarBoxView::Type::Home));
            }
            else if(_currentTab == MainLobby::Tab::Level)
            {
                SCENE_M->addDialog(StarBoxView::createLayerN(StarBoxView::Type::Level));
            }
        }
    }
    else if (btnName == "Button_Dailytasks")
    {//任务
        main_tips1_Task->setVisible(false);
        isShowFanPai = false;//翻牌不显示，改为轮盘
        //refushGift();//更新
        SCENE_M->addDialog(DailytaskView::createLayerN());
    }
    else if (btnName == "Button_Mybag")
    {//背包
        
        isShowFanPai = false;//翻牌不显示，改为轮盘
        //refushGift();//更新
        UIUtils::playInnerAction(FileNode_MyBag,"Start",false);
        SCENE_M->addDialog(BagView::createLayerN(BagView::BagType::CARD));
        isShowTop(false);
        //_lobby->isShowBag(true);
    }
    else if (btnName == "Button_Sign")
    {//七日签到
        
        isShowFanPai = false;//翻牌不显示，改为轮盘
        //refushGift();//更新
        isShowTop(false);
        SCENE_M->addDialog(SevenDayView::createLayerN(SevenDayView::Type::Home));
    }
    else if (btnName == "Button_sub")   // 订阅按钮
    {
        SCENE_M->addDialog(SubscriptionView::createLayerN());
    }
    else if(btnName == "Button_share")
    {//分享
        isShowFanPai = false;//翻牌不显示，改为轮盘
        //refushGift();//更新
        //分享不给金币了，禁止弹窗直接分享
        UIUtils::shareApp();
    }
    else if(btnName == "Button_getGold")
    {//领取金币
//        isShowFanPai = false;//翻牌不显示，改为轮盘
//        SCENE_M->addDialog(FreeCoinLayer::createLayerN(FreeCoinLayer::Type::Gold));
        
        openReward(true);
        isShowFanPai = false;//翻牌不显示，改为轮盘
        isShowTop(false);
        SCENE_M->addDialog(GoldShop::createLayerN(GoldShop::GoldShopType::Lobby));
    }
    else if(btnName == "Button_getDiamond")
    {//领取钻石
        isShowFanPai = false;//翻牌不显示，改为轮盘
        //refushGift();//更新
        SCENE_M->addDialog(FreeCoinLayer::createLayerN(FreeCoinLayer::Type::Diamond));
    }
    else if(btnName == "Button_LunPan"||btnName == "Panel_lunPan")
    {//轮盘
        
        openReward(true);
        //isShowTop(false);
        showGetGoldBtn(false);
        isShowFanPai = true;//翻牌不显示，改为轮盘
        //refushGift();//更新
        SCENE_M->addDialog(RewardRouletteView::createLayerN(RewardRouletteView::Type::Home));
    }
    else if(btnName == "Button_fanPai")
    {
        
        openReward(true);
        isShowTop(false);
        isShowFanPai = false;//翻牌不显示，改为轮盘
        Button_fanPai->setVisible(false);
        SCENE_M->addDialog(FanPaiAD::createLayerN(FanPaiAD::Type::Home));
    }
    else if(btnName == "Button_Sign_AD")
    {
        
        //直接给金币
//        DATA_M->playVideoAds(10);
//        UIUtils::FIRAnalyticsEventWithPrefix("openLobbyVideos");
        isShowFanPai = false;//翻牌不显示，改为轮盘
        
        SCENE_M->addDialog(FreeCoinLayer::createLayerN(FreeCoinLayer::Type::Gold));
    }
    else if(btnName == "Button_renwu")
    {
        TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::BRONZEREWARD);
        //累计银奖杯任务数 新手
        TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::SILVERAWARD);
         
        //累计金奖杯任务数 新手
        TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::GOLDAWARD);
        
        //累计钻石奖杯任务数 新手
        TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::DIAMONDAWARD);
         
    }
    else if(btnName == "Button_weishi")
    {//所有鱼回血30
        auto gameBackground = SCENE_M->getGameBackground();
        gameBackground->weishi();
        UIUtils::FIRFirestoreAddOP("fish_wei");
        UIUtils::FIRAnalyticsEvent("fish_wei", {});
    }
    else if(btnName == "Button_addFish")
    {//加入一条鱼
        auto gameBackground = SCENE_M->getGameBackground();
        gameBackground->addFish();
    }
    else if(btnName == "Button_deFish")
    {//移除一条鱼
        auto gameBackground = SCENE_M->getGameBackground();
        gameBackground->delateFish();
        updateFishNum();
    }
    else if(btnName == "Button_jiasu")
    {//jiasu
        auto gameBackground = SCENE_M->getGameBackground();
        gameBackground->jiasu();
    }
    else if(btnName == "Button_jiansu")
    {//减速
        auto gameBackground = SCENE_M->getGameBackground();
        gameBackground->jiansu();
    }
    else if(btnName == "Button_stop")
    {//停止
        auto gameBackground = SCENE_M->getGameBackground();
        gameBackground->stop();
    }
    else if(btnName == "Button_start")
    {//进入游戏
        menuPlayAni("start",false);
        startGame();
    }
    else if(btnName == "Button_shopping")
    {//
        
        if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::ClickFishShop)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFishShop))
        {
            GUIDE_M->endGuide();
        }
        clickFishShop();
        isShowFanPai = false;//翻牌不显示，改为轮盘
        SCENE_M->addDialog(FishShop::createLayerN());
        isShowTop(false);
    }
    else if(btnName == "Button_shopping_fish")
    {//鱼缸
        if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::ClickFashTank)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFashTank,0))
        {
            GUIDE_M->endGuide(FishGuideManager::GuideType::None,NULL,0);
        }
        UIUtils::playInnerAction(FileNode_fashTank, "tank", false);
        SCENE_M->addDialog(FashTankShop::createLayerN());
        isShowTop(false);
    }
    else if(btnName == "Button_unLock")
    {//解锁
        DATA_M->setIsCeShiUnLock(true);
    }
    else if(btnName == "Button_100exp")
    {//解锁
        //SCENE_M->showLoading();
        //SCENE_M->addDialog(GoldShop::createLayerN());
//        rewardExp(110,getContentSize()/2);
//        SCENE_M->addDialog(GoldViewHD::createLayerN());
    }
    else if(btnName == "Button_daily")
    {//每日
        
        openReward(true);
        auto currentDate = DailyManager::getInstance()->getCurrentDate();
        auto _today = DailyManager::getInstance()->today();
        auto _current = currentDate==NoneDate?_today:currentDate;
        
        auto Panel_more = DailyMoreView::createLayerN(_current);
        SCENE_M->addDialog(Panel_more,false,2);
    }
    else if(btnName == "Button_goShop")
    {//商店
        isShowFanPai = false;//翻牌不显示，改为轮盘
        isShowTop(false);
        SCENE_M->addDialog(GoldShop::createLayerN());
    }
    else if(btnName == "Button_10000")
    {//
        DATA_M->setCoinNum(1000, true);
        ValueMap valueMap{
            {"isTime",Value{true}}
        };
        //更新有金币显示
        EVENT_M->sendEvent("event_game_update_coin",valueMap);
    }
    else if(btnName == "Button_lock")
    {//
        
        LevelUpView->setVisible(true);
        LevelUpView->updateUI();
        LevelUpView->playAni("Start0",false,[this](){
            LevelUpView->playAni("out0",false);
        });
    }
    else if(btnName == "btn_challenge")
    {//
        SCENE_M->addDialog(ChallengeModeView::createLayerN(ChallengeModeView::Type::Lobby));
        
    }
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    if (btnName == "Button_teach")
    {
        this->setVisible(false);
        gameView->setVisible(true);
        gameView->startTeachBureau();
    }
    else if(btnName == "Button_effCeShi")
    {
        effCeShi();
    }
    else if(btnName == "Button_effCeShi_0")
    {
        effCeShi1();
    }
    else if(btnName == "Button_effCeShi_1")
    {
        effCeShi0();
    }
    
#endif
}

void MainLobby::updateBanner()
{
    auto loaded = true; //UIUtils::bannerLoaded();
    CCLOG("WTF loaded???%d", loaded?1:0);
    if (loaded) {
//        moveOffsetY = 0; // DATA_M->isVipNoAds()?0:54*scaleFactor; // 没有banner
//        this->updateUI();
    }
}

void MainLobby::updateUI()
{
    CCLOG("0000 %f", moveOffsetY);
    
    static auto pos = Image_bottom->convertToWorldSpaceAR(Vec2::ZERO);
    static auto originalY = Image_bottom->getPositionY();
    if (moveOffsetY == 0) {
        CCLOG("0000");
    }
    Image_bottom->setPositionY(originalY+moveOffsetY-pos.y);

    updateStar();
    updataBagNew();
    updateFishNewTips();
    
    updateFashTankNewTips();
    updateExp();
    updateCoin();
    updateDiamond();
    
    updateLockState();
}

void MainLobby::updateStar()
{
    SCENE_M->getStarNode()->removeAllChildren();
    if(_currentTab == Tab::Home||_currentTab == Tab::Level)
    {
        UIUtils::playInnerAction(FileNode_StarBox, "Start0", true);
        
        FileNode_StarBox->setVisible(true);
        updateStarBox();
    }
    else if(_currentTab == Tab::Daily)
    {
        UIUtils::playInnerAction(FileNode_StarBox, "Start1", true);
        FileNode_StarBox->setVisible(true);
        updateCrownnBox();
    }
}


void MainLobby::updateLockState()
{
    // 新手引导解锁 每日 关卡任务 等等
    auto unlock = TEACH_M->isDailyLevelUnlock();
    getNode("Node_tabLock1")->setVisible(!unlock);
    getNode("Node_tabLock2")->setVisible(!unlock);
    
    unlock = TEACH_M->isTaskUnlock();
    //getNode("Button_Dailytasks")->setVisible(unlock);
    //商店蒙层 第一局结束后解除
    getNode("Node_tabLock3")->setVisible(!unlock);
}

void MainLobby::updateExp()
{
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
}

void MainLobby::updateNewVersion(bool isShow)
{
    auto isNew = DATA_M->isNewVer();
    getNode("img_new_Ver")->setVisible(isNew&&isShow);
    gameView->updateNewVersion(isShow);
    if(!isShow)
    {
        DATA_M->updatenewVerIsYday();
    }
}

//经验值公式就   ( 700000/时间(取整) ) /100
/*
 lv1 100
 lv2 200
 lv3 300
 以此类推.我在调等级
 
 经验值 动画加一个 Circ_EaseOut的过程
 */
void MainLobby::updatePage(int page)
{
    switch (page) {
        case 1:
        {
            break;
        }
        default:
            break;
    }
}

void MainLobby::showSetting()
{
    SCENE_M->addDialog(HomeSetting::createLayerN());
}

void MainLobby::startGame()
{
    if(getIsStart())
    {//防止持续点击进入
        //正在进入游戏中
        setIsGoGameView(true);
        //防止动画没播放结束跳转界面时没有刷新星星数目
        if (TEACH_M->isTeaching())
            UIUtils::FIRAnalyticsEventWithPrefix(string("lobbyStart_") + TEACH_M->getCurrentTeachKey(), "teach");
        else
            UIUtils::FIRAnalyticsEventWithPrefix("gameStartNormal_" + toString(0));
        TEACH_M->nextTeachStep(); // 新手
        
        setIsStart(false);
        
        //auto type = DataManager::GameType::Huo;
        
        //auto isThree = false;
        bool is = false;//getIsNewGame();
        //DATA_M->setGameType(type);
        //DATA_M->setIsThreeModel(isThree);
        startGame(is);
    }
}

void MainLobby::startGame(bool isNew)
{//指定为新开
    isNewGame = false;
    auto go = [this](bool newGame){ // newGame true 新开 false 继续
        
        hideLobby([this,newGame](){
            gameView->setVisible(true);
            //播放音效
            //恢复音效
            //SOUND_M->resumeDTEffect();
//                gameView->playMusic();
//                gameView->playEffect();
            this->setVisible(false);
            DATA_M->setIsWeiJiaSi(false);
            SCENE_M->getRewardNode()->setVisible(false);
            
            if (newGame)
            {
                if(isOne)
                {
                    isOne = false;
                }
                else
                {
                    
                }
                gameView->restartGame(false, DataManager::GameType::None, !isNewGame); // isNewGame 决定是否展示插屏
            }
            else
            {//重置显示UI
                gameView->setIsRefushGift(true);//返回游戏开始刷新奖励
                gameView->updateShuffle();
                gameView->gamePause(false);
            }
            
            updateStar();//预防星星在场景中显示
        });
    };

    // 只有随机和活局5提示
    if (true)//(DATA_M->getLastGameType()== DataManager::GameType::Huo || DATA_M->getLastGameType()== DataManager::GameType::Random) && gameView->gameState() == GameViewHD::State::Play&&!isNew)
    {//进入经典之后才能进入
        isNewGame = true;
        
        go(false);
//        SCENE_M->addDialog(BackView::createLayerN([this, go](){
//            go(false);
//        }, [this, go](){
//            go(true);
//        }, Lang("100197"), Lang("100198"), Lang("100199")));
    }
    else {
        go(true);
    }
}

void MainLobby::startDaily(const std::string &deck, const std::string &num)
{
    playAni("out", false, [this, deck, num](){
        gameView->setVisible(true);
        //恢复音效
        //SOUND_M->resumeDTEffect();
        //播放音效
//        gameView->playMusic();
//        gameView->playEffect();
        this->setVisible(false);
        gameView->startDaily(deck, num);
        //gameView->playNavigate0("Go2", false);
        UIUtils::FIRAnalyticsEventWithPrefix("gameStartDaily");
    });
}

void MainLobby::startDaily()
{
    auto childLayer = panel_root->getChildByName<DailyView*>("DailyView");//dynamic_cast<DailyView*>(_rootLayers.at((int)Tab::Daily));
    if (childLayer) {
        childLayer->filterSimpleDate();
        childLayer->showStart();
    }
}

void MainLobby::startLevel(std::shared_ptr<rapidjson::Document> levelData)
{
    playAni("out", false, [this, levelData](){
        gameView->setVisible(true);
        //恢复音效
        //SOUND_M->resumeDTEffect();
        //播放音效
//        gameView->playMusic();
//        gameView->playEffect();
        this->setVisible(false);
        gameView->startLevelRank(levelData);
        //gameView->playNavigate0("Go2", false);
        playAni("idle", false);
        UIUtils::FIRAnalyticsEventWithPrefix("gameStartLevel");
        gameView->sendStartGameEvent(DataManager::GameType::Level);
    });
}

void MainLobby::startLevel()
{
    auto levelView = panel_root->getChildByName<MissionView*>("MissionView");//dynamic_cast<MissionView*>(_rootLayers.at((int)Tab::Level));
    if (levelView)
        levelView->startLevel();
    playAni("idle", false);
}
void MainLobby::menuPlayAni(string aniName,bool isLoop)
{
    UIUtils::playInnerAction(FileNode_play, aniName, isLoop);
}
void MainLobby::onEnter() {
    BaseLayer::onEnter();
    playAni("idle", false);
    menuPlayAni("startloop",true);
    updateUI();
    SOUND_M->playGameBgMusic(StringUtils::format(BGM.c_str(), DATA_M->getCardPicType(5)));
    //playEffect();
    //playMusic();
}

void MainLobby::onExit() {
    BaseLayer::onExit();
    EVENT_M->removeListener("event_game_update_coin",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
    EVENT_M->removeListener("msg_game_lingqu",this);
    EVENT_M->removeListener("msg_game_showwin",this);
    EVENT_M->removeListener("msg_interstitialDidLoad",this);
    
}

void MainLobby::playEffect()
{
//    int gameBgType = DATA_M->getCardPicType(1);
//    if(gameBgType > 13)
//    {
//        SOUND_M->playEffectMusic(ShopManager::getInstance()->getSceneEffect(gameBgType-12), true);
//    }
}
void MainLobby::playMusic()
{
//    int gameBgType = DATA_M->getCardPicType(1);
//    if(gameBgType > 13)
//    {
//        auto musicName = ShopManager::getInstance()->getSceneMusic(gameBgType-12);
//        if (!musicName.empty())
//            SOUND_M->playEffectMusic(musicName, true);
//    }
}

void MainLobby::setVisible(bool visible) {
    Node::setVisible(visible);
    if (visible) {
        playAni("idle", false);
        EVENT_M->sendEvent("event_home_updateui");
        //getEventDispatcher()->dispatchCustomEvent("event_home_updateui");
        
        updateLockState(); // 更新tab 锁定
        if (TEACH_M->isTeaching("win_times1") || TEACH_M->isTeaching("win_times2")) {
            TEACH_M->nextTeachStep(this); // 引导点击box 点击商店
            UIUtils::FIRAnalyticsEventWithPrefix("12Lobby_" + TEACH_M->getCurrentTeachKey(), "teach");
        }
        else {
            TEACH_M->triggerTeach("lobby_times2", this);
            if (TEACH_M->isTeaching())
                UIUtils::FIRAnalyticsEventWithPrefix("2Lobby_" + TEACH_M->getCurrentTeachKey(), "teach");
            else
                UIUtils::FIRAnalyticsEventWithPrefix("Lobby");
        }
        //
        onRecordEnter();
        UIUtils::FIRAnalyticsTrackScreens("MainLobby");
    }
    else {
//        SOUND_M->stopGameBgMusic();
        onRecordExit();
    }
}


void MainLobby::setView()
{
    auto type = DATA_M->getStartGameType();
    if(type == DataManager::GameType::Level)
    {
        setTab(Tab::Level);
    }
    else if(type == DataManager::GameType::Daily)
    {
        setTab(Tab::Daily);
    }
    else
    {
        setTab(Tab::Home);
    }
}

void MainLobby::resetLevelView()
{
    isShowFanPai = true;//翻牌显示，
    updateStoreNew();//更新商店newtips
    refushGift();//更新
    auto levelView = panel_root->getChildByName<MissionView*>("MissionView");//dynamic_cast<MissionView*>(_rootLayers.at((int)Tab::Level));
    if (levelView)
        levelView->updateUI();
    //levelView->setIsStart(true);//恢复关卡选择
    //levelView->resetView();//恢复
}

void MainLobby::showGuide()
{
    //来个等级判断 大于0
    auto lv = PlayerManager::getInstance()->getLevel();
    
    if(lv > 0&&!GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFishShop)&&GUIDE_M->isEnd(FishGuideManager::GuideType::LobbyOne))
    {//在引导到大厅结束后才进行点击买鱼引导
        auto btn = getNode("Button_shopping");
        auto poi = btn->getPosition();
        poi = btn->getParent()->convertToWorldSpace(poi);
        GUIDE_M->startGuide(FishGuideManager::GuideType::ClickFishShop,this,poi);
    }
    if(!GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFashTank,0)&&GUIDE_M->isEnd(FishGuideManager::GuideType::gotoLobby,0))
    {//在引导到大厅结束后才进行点击买鱼引导
        auto btn = getNode("Button_shopping_fish");
        auto poi = btn->getPosition();
        poi = btn->getParent()->convertToWorldSpace(poi);
        GUIDE_M->startGuide(FishGuideManager::GuideType::ClickFashTank,this,poi,1,0);
    }
    
}

void MainLobby::resetHome()
{
    isTouch = false;
    UIUtils::playInnerAction(FileNode_top,"in",false,[this](){
        //弹出签到
        //每日签到奖励未领取 程序打开后isAppStart = ture; 或者 后台3小时回来
        auto isReward = DATA_M->getIsGetSevenReward();
        auto time = DATA_M->getDayOfflineTime();
        if(!isReward&&(isAppStart || time == 0))
        {
            isAppStart = false;
            isShowTop(false);
            auto seven = SevenDayView::createLayerN(SevenDayView::Type::Home);
            SCENE_M->addDialog(seven);
            //seven->oneOpen();
        }
        else
        {
            showGuide();
        }
        
        auto fashTank = SCENE_M->getGameBackground();
        fashTank->showGuide();
        isTouch = true;
    });
    playAni("in", false);
    //刷新每日显示
    auto gameNum = ScoreManager::getInstance()->getWinTotalCNT(true);
    getNode("Button_daily")->setVisible(gameNum >= 3);
    isShowFanPai = true;//翻牌显示，
    updateStoreNew();//更新商店newtips
    updateFishNewTips();
    updateFashTankNewTips();
    refushGift();//更新
    updateBtnChallenge();
    setIsStart(true);
    //刷新订阅显示
    auto num = ScoreManager::getInstance()->getWinTotalCNT();
    auto isAds = num > GAMENOADSCNT;
    getNode("Button_sub")->setVisible(isAds);
//    auto home = panel_root->getChildByName<HomeView*>("HomeView"); //dynamic_cast<HomeView*>(_rootLayers.at((int)Tab::Home));
//    if (home)
//        home->setIsStart(true);
//    if(DATA_M->isLevelMode())
//    {//恢复关卡模式界面
////        auto levelView = dynamic_cast<LevelViewHD*>(_rootLayers.at((int)Tab::Level));
////        levelView->showLevel(0);
//    }
}

void MainLobby::dailyShowComplete()
{
//    isShowFanPai = true;//翻牌显示，
//    updateStoreNew();//更新商店newtips
//    refushGift();//更新
//    auto childLayer = panel_root->getChildByName<DailyView*>("DailyView");//dynamic_cast<DailyView*>(_rootLayers.at((int)Tab::Daily));
//    if (childLayer)
//        childLayer->showComplete();
    if(DATA_M->isDailyMode())
    {
        bool firstComplete = DailyManager::getInstance()->complete();
    }
    
}

void MainLobby::starAni(int starNum,std::string aniName,Vec2 poi,std::function<void()> cb)
{
    
    float time = 0;
    std::vector<Vec2> itemVec1;
    DATA_M->randVec(starNum,&itemVec1,200);

//    auto daily = dynamic_cast<DailyView*>(_rootLayers.at((int)Tab::Daily));
    poi = poi == Vec2(0,0)?getStarBoxWorldPoi():poi;
    float moByTime = 0.4f,moToTime = 1.5f;
    for(int i = 0;i<starNum;++i)
    {
        time += 0.05;
        //UIUtils::createCSBNode("Animation/Node_currency.csb",aniName,true);
        auto expNode = StarNode::getCache()->createCacheNode(SCENE_M->getStarNode());

        expNode->setVisible(false);
        expNode->setPosition(this->getContentSize()*0.5);//目前在屏幕中心
        auto show = Show::create();
        auto delay = DelayTime::create(time+0.7);//停留0.2s飞上去
        auto moBy = MoveBy::create(moByTime, itemVec1[i]);
        auto cubicOut = EaseCubicActionOut::create(moBy);
        auto moTo = MoveTo::create(moToTime, poi);
        auto quarticIn = EaseQuarticActionIn::create(moTo);
        //auto out = FadeOut::create(0.5);
        auto remo = RemoveSelf::create();
        auto func = CallFunc::create(cb = nullptr?[this](){
            //刷新星星数目
            if(DATA_M->isDailyMode())
            {
                updateCrownnBox(true);
            }
            else if(DATA_M->isLevelMode())
            {
                updateStarBox(true);
            }
            else
            {
                updateStarBox(true);
            }
            
        }:cb);
        auto func2 = CallFunc::create([expNode,aniName,moByTime,moToTime](){
            //expNode->setVisible(true);
            expNode->playAni(aniName, false,(moByTime + moToTime)/STARFLYSPEED);
            
        });
        auto effFunc = CallFunc::create([this](){
            //
            SOUND_M->playEffectMusic(EffectGetStar);
        });
        if(i == 0)
        {
            auto seq = Sequence::create(delay,func2,show,cubicOut, quarticIn,effFunc,func,remo, NULL);
            auto speed = Speed::create(seq, STARFLYSPEED);
            expNode->runAction(speed);
        }
        else
        {
            auto seq = Sequence::create(delay,func2,show,cubicOut, quarticIn,effFunc,remo, NULL);
            auto speed = Speed::create(seq, STARFLYSPEED);
            expNode->runAction(speed);
        }
    }
}

void MainLobby::goldAni(int goldNum,Node* parent,Vec2 startPoi,std::function<void()> cb,std::function<void()> endCB,std::function<void()> endCB2,Vec2 endPoi)
{
    int num = 0;
    if(goldNum > 10)
    {
        num=goldNum/2;
        if(num > 50)
        {
            num = 50;
        }
    }
    else
    {
        num = goldNum;
        
    }
    SCENE_M->getRewardNode()->setVisible(true);
    std::vector<Vec2> itemVec1;
    DATA_M->randVec(num,&itemVec1,200);
    auto goldPoi = getGoldWorldPoi();
    REWARD_M->rewardItemAction(num,endPoi==Vec2(2000,2000)?goldPoi:endPoi,startPoi==Vec2(2000,2000)?this->getContentSize()*0.5:startPoi,itemVec1,cb,"Gold",SCENE_M->getRewardNode(),endCB,endCB2);
}

void MainLobby::diamondAni(int diamondNum,Node* parent,Vec2 startPoi,std::function<void()> cb,std::function<void()> endCB,std::function<void()> endCB2,Vec2 endPoi)
{
    int num = 0;
    if(diamondNum > 10)
    {
        num=diamondNum/2;
        if(num > 50)
        {
            num = 50;
        }
    }
    else
    {
        num = diamondNum;
        
    }
    
    SCENE_M->getRewardNode()->setVisible(true);
    std::vector<Vec2> itemVec1;
    DATA_M->randVec(num,&itemVec1,200);
    auto goldPoi = getdiamondWorldPoi();
    REWARD_M->rewardItemAction(num,endPoi==Vec2(2000,2000)?goldPoi:endPoi,startPoi==Vec2(2000,2000)?this->getContentSize()*0.5:startPoi,itemVec1,!cb?[this,diamondNum](){
        //更新有金币显示
        
    }:cb,"Baoshi",SCENE_M->getRewardNode(),endCB,endCB2);
}

void MainLobby::magicAni(int magicNum,Node* parent,Vec2 startPoi,std::function<void()> cb,std::function<void()> endCB,std::function<void()> endCB2,Vec2 endPoi)
{
    REWARD_M->getReward(RewardManager::RewardType::Magic,magicNum,true);
    //游戏里也刷新
    gameView->updateShuffle();
    std::vector<Vec2> itemVec1;
    DATA_M->randVec(magicNum,&itemVec1,200);
    auto goldPoi = getBagWorldPoi();
    REWARD_M->rewardItemAction(magicNum,endPoi==Vec2(2000,2000)?goldPoi:endPoi,startPoi==Vec2(2000,2000)?this->getContentSize()*0.5:startPoi,itemVec1,
                               !cb?[this,magicNum](){
        
    }:cb,"Magic",!parent?Node_rewardAni:parent,endCB,endCB2);
}

void MainLobby::spriteAni(Node*node, int type,std::function<void()> cb)
{

    auto poi = getBagWorldPoi(type);
    
    auto moto = MoveTo::create(0.8, poi);
    auto scale = ScaleTo::create(0.5, 1);
    //auto out = FadeOut::create(0.7);
    auto swq = Spawn::create(moto,scale, NULL);
    auto delay = DelayTime::create(0);
    auto func = CallFunc::create([this,cb](){
        if(this->isVisible())
        {
            playBagAni();
        }
        else
        {
            gameView->playBagAni();
        }
        
        cb();
    });
    auto re = RemoveSelf::create();
    auto seq = Sequence::create(delay,swq,func,re, NULL);
    node->runAction(seq);
}

void MainLobby::stroeBoxAni(Node*node, int type,std::function<void()> cb)
{
    auto store = panel_root->getChildByName<StoreView*>("StoreView");
    if (store == nullptr) return;
    
    auto poi = store->getBagWorldPoi();
    auto moto = MoveTo::create(0.8, poi);
    auto scale = ScaleTo::create(0.5, 1);
    //auto out = FadeOut::create(0.7);
    auto swq = Spawn::create(moto,scale, NULL);
    auto delay = DelayTime::create(0);
    auto func = CallFunc::create([this,cb](){
        playBagAni();
        cb();
    });
    auto re = RemoveSelf::create();
    auto seq = Sequence::create(delay,swq,func,re, NULL);
    node->runAction(seq);
}

Vec2 MainLobby::getBagWorldPoi(int type)
{
    return getBagWorldPoi();
}

void MainLobby::playGoldAni(int type,bool isPlay)
{
    playGoldAni(this,isPlay);
}
void MainLobby::playDiamondAni(int type,bool isPlay)
{
    playDiamondAni(this,isPlay);
}

void MainLobby::playGoldAni(BaseLayer* node, bool isPlay)
{
    FileNode_gold->setVisible(isPlay);
    if(isPlay)
    {
        UIUtils::playInnerAction(FileNode_gold,"Gold",false);
    }
   
}
void MainLobby::playDiamondAni(BaseLayer* node,bool isPlay)
{
    auto img_icon_diamond = this->getNode("img_icon_top_diamond");
    auto FileNode_diamond = this->getNode("FileNode_diamond");
    img_icon_diamond->setVisible(!isPlay);//(!isPlay);
    FileNode_diamond->setVisible(isPlay);
    if(isPlay)
    {
        UIUtils::playInnerAction(FileNode_diamond,"Baoshi",false);
    }
}

void MainLobby::playBagAni()
{
    UIUtils::playInnerAction(FileNode_MyBag,"Start",false);
}

void MainLobby::updateDYY()
{
    getNode<Text*>("Text_play")->setString(Lang("100113"));
    getNode<Text*>("Text_btn0")->setString(Lang("100116"));
    getNode<Text*>("Text_btn1")->setString(Lang("100118"));
    getNode<Text*>("Text_btn2")->setString(Lang("100204"));
    getNode<Text*>("Text_btn3")->setString(Lang("100068"));

    //适配大小  目前各个语言文本大小没有超出范围的 
    for(int i = 0;i<4;++i)
    {
        auto textStr = StringUtils::format("Text_btn%d", i);
        auto text = getNode<Text*>(textStr);
        UIUtils::textAdaptiveSize(text,260);
    }
    
    
    auto Text_LunPan = getNode<Text*>("Text_LunPan");
    Text_LunPan->setString(Lang("100281"));
    UIUtils::textAdaptiveSize(Text_LunPan,150);
    getNode<Text*>("Text_Task")->setString(Lang("100280"));
    getNode<Text*>("Text_Sign")->setString(Lang("100282"));
    getNode<Text*>("Text_Lucky")->setString(Lang("100283"));
    getNode<Text*>("Text_MyBag")->setString(Lang("100284"));
    getNode<Text*>("Text_StarBox")->setString(Lang("100234"));
    getNode<Text*>("Text_StarBox")->setVisible(false);
    getNode<Text*>("Text_StarBox_0")->setVisible(false);
    getNode<Text*>("Text_StarBox_open")->setVisible(false);
    getNode<Text*>("Text_StarBox_open")->setString(Lang("100285"));
    getNode<Text*>("Text_CrownBox")->setString(Lang("100235"));
    getNode<Text*>("Text_CrownBox_open")->setString(Lang("100285"));
    getNode<Text*>("Text_setting")->setString(Lang("100122"));
    getNode<Text*>("Text_Collect")->setString(Lang("100389"));
    
    FIND_NODE(Text*, FileNode_fish, "Text_new")->setString(Lang("100374"));
    FIND_NODE(Text*, FileNode_fashTank, "Text_new")->setString(Lang("100374"));
    //修复 多语言
    auto home = panel_root->getChildByName<HomeView*>("HomeView");
    if(home)
    {
        home->updateDYY();
    }
    auto daily = panel_root->getChildByName<DailyView*>("DailyView");
    if(daily)
    {
        daily->updateDYY();
    }
    auto store = panel_root->getChildByName<HomeView*>("StoreView");
    if(store)
    {
        store->updateDYY();
    }
    auto level = panel_root->getChildByName<MissionView*>("MissionView");
    if(level)
    {
        level->updateDYY();
    }
    auto fashTank = SCENE_M->getGameBackground();
    if(fashTank)
    {
        fashTank->updateDYY();
    }
//    auto daily = dynamic_cast<DailyView*>(_rootLayers.at((int)Tab::Daily));
//    daily->updateDYY();
//    auto store = dynamic_cast<StoreView*>(_rootLayers.at((int)Tab::Store));
//    store->updateDYY();
//    auto level = dynamic_cast<MissionView*>(_rootLayers.at((int)Tab::Level));
//    level->updateDYY();
    
    updateExp();
}

void MainLobby::isShowBag(bool isShow)
{
    isShowTop(!isShow);
}
void MainLobby::isShowTop(bool isShow)
{
    getNode("FileNode_top")->setVisible(isShow);
}

void MainLobby::updateCoin(int type)
{
    updateCoin(true);
}

void MainLobby::updateDiamond(int type)
{
    updateDiamond(true);
}

Vec2 MainLobby::getStarBoxWorldPoi()
{
    auto Button_StarBox = FileNode_StarBox->getChildByName("Button_StarBox");
    auto Star_target = Button_StarBox->getChildByName("Star_target");
    auto poi = Star_target->getPosition();
    poi = Button_StarBox->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}
Vec2 MainLobby::getGoldWorldPoi()
{
    auto goldNode = getNode("img_icon_top_gold");
    auto poi = goldNode->getPosition();
    poi = goldNode->getParent()->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}
Vec2 MainLobby::getdiamondWorldPoi()
{
    auto diamondNode = getNode("img_icon_top_diamond");
    auto poi = diamondNode->getPosition();
    poi = diamondNode->getParent()->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}

Vec2 MainLobby::getBagWorldPoi()
{
    Vec2 poi;
    if(isVisible())
    {//在大厅
        poi = FileNode_MyBag->getPosition();
        poi = FileNode_MyBag->getParent()->convertToWorldSpace(poi);
    }
    else
    {//在游戏中
        poi = gameView->getBagWorldPoi();
    }
    
    //poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}

Vec2 MainLobby::getLevelWorldPoi()
{//
    auto Button_lock =  FIND_NODE(Node*, FileNode_top, "Button_lock");
    auto poi = Button_lock->getPosition();
    poi = Button_lock->getParent()->convertToWorldSpace(poi);
    //poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}

void MainLobby::updateCoin(bool isDelay)
{
    //移除还没有结束的定时器
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
    {
        auto str = text->getString();
        _coinNum = UIUtils::stoii(str);
        auto num = DATA_M->getCoinNum();
        auto tempNum = num - _coinNum;
        if(tempNum <= 0)
        {
            text->setString(StringUtils::toString(num));
            return;
        }
        //auto time = 0.75/(float)tempNum;
        float time = 0;
        if(tempNum >= 15)
        {
            time = 0.75 / FLYSPEED;
        }
        else
        {
            time = 0.05/FLYSPEED * tempNum;
        }
        auto grouwup = GrowupNode::create();
        text->addChild(grouwup,0,88);
        grouwup->startGrouwup(text, _coinNum, num, time, "",[this, grouwup](){
            grouwup->removeFromParent();
        });
    }
    else
    {
        int coinNum = DATA_M->getCoinNum();
        text->setString(StringUtils::toString(coinNum));
    }
}

void MainLobby::updateDiamond(bool isDelay)
{
    //移除还没有结束的定时器
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
//            grouwup->removeFromParent();
//        });
//    }
//    else
//    {
//        int diamondNum = DATA_M->getDiamond();
//        text->setString(StringUtils::toString(diamondNum));
//    }
//    int coinNum = DATA_M->getCoinNum();
//    int diamondNum = DATA_M->getDiamond();
//    if(coinNum >= 500||diamondNum>=500)
//    {
//        FileNode_StoreBox->setVisible(true);
//        UIUtils::playInnerAction(FileNode_StoreBox, "Start3", true);
//    }
//    else
//    {
//        FileNode_StoreBox->setVisible(false);
//    }
}

void MainLobby::updateStarBox(bool isDelay)
{
    auto num1 = DATA_M->getStarBoxNum();
    auto num2 = DATA_M->getStarBoxNumMax();
    if(num1 == num2)
    {
        Button_Collect->setVisible(true);
        auto animanager = UIUtils::playInnerAction(FileNode_StarBox2,"Start3",true);

        string name = "";
        if(num2 <= 2)
        {
            name = "Box_2.png";
        }
        else if(num2 <= 4)
        {
            name = "Box2_2.png";
        }
        else if(num2 <= 6)
        {
            name = "Box3_2.png";
        }
        else if(num2 <= 8)
        {
            name = "Box4_2.png";
        }
        auto Sprite_Box = FileNode_StarBox2->getChildByName<Sprite*>("Sprite_Box");
        Sprite_Box->setSpriteFrame(name);
        getNode("Node_StarBox")->setVisible(false);
        //getNode<Text*>("Text_StarBox_open")->setVisible(true);
        auto Text_StarNum = getNode<TextBMFont*>("BitmapFontLabel_StarNum");
        auto Text_StarNumMax = getNode<TextBMFont*>("BitmapFontLabel_StarNumMax");
        //auto nam = Text_StarNum->getString();
        Text_StarNumMax->setString(StringUtils::toString(num2));
        auto minStr = Text_StarNum->getString();
        auto min = UIUtils::stoii(minStr);
        if(num1 == 0||num1 - min > 3||!isDelay)
        {
            Text_StarNum->setString(StringUtils::toString(num1));
        }
        else
        {
            auto grouwup = GrowupNode::create();
            Text_StarNum->addChild(grouwup);
            grouwup->startGrouwup(Text_StarNum, min, num1, 0.2, "",[this, grouwup](){
                grouwup->removeFromParent();
            });
        }

        auto LoadingBar_StarBox = getNode<LoadingBar*>("LoadingBar_StarBox");
        percent = LoadingBar_StarBox->getPercent();
        auto percent2 = (float)num1/(float)num2 * 100;

        if(percent >= percent2||!isDelay)
        {
            LoadingBar_StarBox->setPercent(percent2);
        }
        if(isDelay)
        {
            schedule([percent2,this,LoadingBar_StarBox,Text_StarNum,Text_StarNumMax,num1,num2](float dt){
                if(percent < percent2)
                {
                    auto num1 = DATA_M->getStarBoxNum();
                    if(num1 == 0)
                    {
                        LoadingBar_StarBox->setPercent(0);
                        unschedule("schedule_starBox");
                    }
                    else
                    {
                        //问题 星星归零了定时器还在走
                        percent += 96.66*dt;
                        if(percent > percent2)
                        {
                            percent = percent2;
                        }
                        LoadingBar_StarBox->setPercent(percent);
                    }
                }
                else
                {
                    unschedule("schedule_starBox");
                }
            },"schedule_starBox");
        }
        
    }
    else
    {
        Button_Collect->setVisible(false);
        UIUtils::playInnerAction(FileNode_StarBox2,"Loop",false);
        string name = "";
        if(num2 <= 2)
        {
            name = "Box_0.png";
        }
        else if(num2 <= 4)
        {
            name = "Box2_0.png";
        }
        else if(num2 <= 6)
        {
            name = "Box3_0.png";
        }
        else if(num2 <= 8)
        {
            name = "Box4_0.png";
        }
        auto Sprite_Box = FileNode_StarBox2->getChildByName<Sprite*>("Sprite_Box");
        Sprite_Box->setSpriteFrame(name);

        getNode("Node_StarBox")->setVisible(false);
        getNode<Text*>("Text_StarBox_open")->setVisible(false);

        auto Text_StarNum = getNode<TextBMFont*>("BitmapFontLabel_StarNum");
        auto Text_StarNumMax = getNode<TextBMFont*>("BitmapFontLabel_StarNumMax");
        Text_StarNumMax->setString(StringUtils::toString(num2));
        auto minStr = Text_StarNum->getString();
        auto min = UIUtils::stoii(minStr);
        if(num1 == 0||num1 - min > 3||!isDelay)
        {
            Text_StarNum->setString(StringUtils::toString(num1));
        }
        else
        {
            auto grouwup = GrowupNode::create();
            Text_StarNum->addChild(grouwup);
            grouwup->startGrouwup(Text_StarNum, min, num1, 0.2, "",[this, grouwup](){
                grouwup->removeFromParent();
            });
        }


        //Text_StarNum->setString(StringUtils::format("%d/%d",num1,num2));
        
        auto LoadingBar_StarBox = getNode<LoadingBar*>("LoadingBar_StarBox");
        percent = LoadingBar_StarBox->getPercent();
        auto percent2 = (float)num1/(float)num2 * 100;
        if(min == num1||percent >= percent2||!isDelay)
        {
            LoadingBar_StarBox->setPercent(percent2);
        }
        if(isDelay)
        {
            schedule([percent2,this,LoadingBar_StarBox,Text_StarNum,Text_StarNumMax,num1,num2](float dt){
                if(percent < percent2)
                {
                    percent += 96.66*dt;
                    if(percent > percent2)
                    {
                        percent = percent2;
                    }
                    LoadingBar_StarBox->setPercent(percent);
                }
                else
                {
                    unschedule("schedule_starBox");
                }
            },"schedule_starBox");
        }
    }
}


void MainLobby::updateCrownnBox(bool isDelay)
{
    auto num1 = DATA_M->getDailyStarBoxNum();
    auto num2 = DATA_M->getDailyStarBoxNumMax();
    if(num1 == num2)
    {
        
        auto animanager = UIUtils::playInnerAction(FileNode_CrownBox2,"Start3",true);
//        animanager->setFrameEventCallFunc([this,num2](Frame* f){
//            auto e = dynamic_cast<EventFrame*>(f);
//            auto msg = e->getEvent();
//            if(msg == "Box2")
//            {
//
//            }
//        });
        string name = "";
        if(num2 <= 3)
        {
            name = "Box_2.png";
        }
        else if(num2 <= 5)
        {
            name = "Box2_2.png";
        }
        else if(num2 <= 19)
        {
            name = "Box3_2.png";
        }
        else if(num2 == 20)
        {
            name = "Box6_2.png";
        }
        auto Sprite_Box = FileNode_CrownBox2->getChildByName<Sprite*>("Sprite_Box");
        Sprite_Box->setSpriteFrame(name);
        getNode("Node_CrownBox")->setVisible(false);
        getNode<Text*>("Text_CrownBox_open")->setVisible(true);
        auto Text_CrownNum = getNode<TextBMFont*>("BitmapFontLabel_CrownNum");
        auto Text_CrownNumMax = getNode<TextBMFont*>("BitmapFontLabel_CrownNumMax");
        Text_CrownNumMax->setString(StringUtils::toString(num2));
        auto minStr = Text_CrownNum->getString();
        auto min = UIUtils::stoii(minStr);
        if(num1 == 0||num1 - min > 3||!isDelay)
        {
            Text_CrownNum->setString(StringUtils::toString(num1));
        }
        else
        {
            auto grouwup = GrowupNode::create();
            Text_CrownNum->addChild(grouwup);
            grouwup->startGrouwup(Text_CrownNum, min, num1, 0.2, "",[this, grouwup](){
                grouwup->removeFromParent();
            });
        }
        auto LoadingBar_CrownBox = getNode<LoadingBar*>("LoadingBar_CrownBox");
        percent = LoadingBar_CrownBox->getPercent();
        auto percent2 = (float)num1/(float)num2 * 100;
        if(percent >= percent2||!isDelay)
        {
            LoadingBar_CrownBox->setPercent(percent2);
        }
        if(isDelay)
        {
            schedule([percent2,this,LoadingBar_CrownBox,Text_CrownNum,Text_CrownNumMax,num1,num2](float dt){
                if(percent < percent2)
                {
                    auto num1 = DATA_M->getDailyStarBoxNum();
                    if(num1 == 0)
                    {
                        LoadingBar_CrownBox->setPercent(0);
                        unschedule("schedule_starBox");
                    }
                    else
                    {
                        percent += 96.66*dt;
                        if(percent > percent2)
                        {
                            percent = percent2;
                        }
                        LoadingBar_CrownBox->setPercent(percent);
                    }
                    
                }
                else
                {
                    Text_CrownNum->setString(StringUtils::toString(num1));
                    Text_CrownNumMax->setString(StringUtils::toString(num2));
                    unschedule("schedule_starBox");
                }
            },"schedule_starBox");
        }
        
    }
    else
    {
        
        UIUtils::playInnerAction(FileNode_CrownBox2,"Loop",false);
        string name = "";
        if(num2 <= 3)
        {
            name = "Box_0.png";
        }
        else if(num2 <= 5)
        {
            name = "Box2_0.png";
        }
        else if(num2 <= 19)
        {
            name = "Box3_0.png";
        }
        else if(num2 == 20)
        {
            name = "Box6_0.png";
        }
        else {
            name = "Box6_0.png";
        }
        auto Sprite_Box = FileNode_CrownBox2->getChildByName<Sprite*>("Sprite_Box");
        Sprite_Box->setSpriteFrame(name);
        getNode("Node_CrownBox")->setVisible(true);
        getNode<Text*>("Text_CrownBox_open")->setVisible(false);
        auto Text_CrownNum = getNode<TextBMFont*>("BitmapFontLabel_CrownNum");
        auto Text_CrownNumMax = getNode<TextBMFont*>("BitmapFontLabel_CrownNumMax");
        Text_CrownNumMax->setString(StringUtils::toString(num2));
        auto minStr = Text_CrownNum->getString();
        auto min = UIUtils::stoii(minStr);
        if(num1 == 0||num1 - min >= 3||!isDelay)
        {
            Text_CrownNum->setString(StringUtils::toString(num1));
        }
        else
        {
            auto grouwup = GrowupNode::create();
            Text_CrownNum->addChild(grouwup);
            grouwup->startGrouwup(Text_CrownNum, min, num1, 0.2, "",[this, grouwup](){
                grouwup->removeFromParent();
            });
        }
        
        if(num1 == min)
        {
            Text_CrownNum->setString(StringUtils::toString(num1));
            Text_CrownNumMax->setString(StringUtils::toString(num2));
        }
        //Text_StarNum->setString(StringUtils::format("%d/%d",num1,num2));
        
        auto LoadingBar_CrownBox = getNode<LoadingBar*>("LoadingBar_CrownBox");
        percent = LoadingBar_CrownBox->getPercent();
        auto percent2 = (float)num1/(float)num2 * 100;
        if(min == num1||percent > percent2||!isDelay)
        {
            LoadingBar_CrownBox->setPercent(percent2);
        }
        
        if(isDelay)
        {
            schedule([percent2,this,LoadingBar_CrownBox,Text_CrownNum,Text_CrownNumMax,num1,num2](float dt){
                if(percent < percent2)
                {
                    percent += 96.66*dt;
                    if(percent > percent2)
                    {
                        percent = percent2;
                    }
                    LoadingBar_CrownBox->setPercent(percent);
                }
                else
                {
                    Text_CrownNum->setString(StringUtils::toString(num1));
                    Text_CrownNumMax->setString(StringUtils::toString(num2));
                    unschedule("schedule_starBox");
                }
            },"schedule_starBox");
        }
    }
}

void MainLobby::setInterstitialCB(std::function<void()> cb)
{
    InterstitialCB = cb;
}

void MainLobby::refushGift()
{//DATA_M->getHaveVideo()
    auto isVideo = DATA_M->getHaveVideo();
    if(isVideo)
    {
        Button_Sign_AD->setVisible(true);
    }
    else
    {
        Button_Sign_AD->setVisible(false);
    }
    if (DATA_M->getNextFreeCoinTime() <= 0&&isVideo)
    {
        //免费的
        Button_Sign_AD->setEnabled(true);
    }
    else
    {
        Button_Sign_AD->setEnabled(false);
    }
    
    if(GETINTEGER("fanPaiNum") <= 0)
    {
        isShowFanPai = false;
    }
    //轮盘大于4次之后 5分钟冷却
    if(DATA_M->getNextFreeCoinTime3() <= 0&&isVideo&&!isShowFanPai)
    {//轮盘60s
        auto gameNum = ScoreManager::getInstance()->getWinTotalCNT(true);
        Button_LunPan->setVisible(gameNum >= 3);
    }
    else
    {//
        Button_LunPan->setVisible(false);
    }
    
    getNode<Text*>("Text_fanPaiNum")->setString(StringUtils::toString(GETINTEGER("fanPaiNum",3)));
    if(DATA_M->getNextFreeCoinTime4() <= 0&&GETINTEGER("fanPaiNum") > 0&&isShowFanPai&&DATA_M->getHaveInterstitials())
    {
        auto gameNum = ScoreManager::getInstance()->getWinTotalCNT(true);
        Button_fanPai->setVisible(gameNum >= 3);
    }
    else
    {
        Button_fanPai->setVisible(false);
    }
    //Button_share->setVisible(true);
}

void MainLobby::updataBagNew()
{
    auto isPropNew = DATA_M->getIsPropNew();
    getNode("lobby_new_Bag")->setVisible(isPropNew);
    auto store = panel_root->getChildByName<StoreView*>("StoreView");
    if (store)
        store->updataBagNew();
    
    gameView->updataBagNew();
}

void MainLobby::updateStoreNew()
{
}

void MainLobby::updateTaskNew()
{
    taskNewNum--;
    SETINTEGER("taskNewNum",0);
    main_tips1_Task->setVisible(taskNewNum == 1);
}

void MainLobby::updateSevenNew()
{
    sevenNewNum--;
    SETINTEGER("sevenNewNum",0);
    getNode("main_tips1_1")->setVisible(sevenNewNum == 1);
}

void MainLobby::updateFishNewTips()
{
    auto isFishNew = DATA_M->getIsFishNuw();
    lobby_fish_tips->setVisible(isFishNew);
    if(isFishNew)
    {
        UIUtils::playInnerAction(FileNode_fish, "startloop2", true);
    }
    gameView->updateFishNewTips();
}

void MainLobby::updateFashTankNewTips()
{
    auto isFishNew = DATA_M->getIsFashTankNuw();
    if(isFishNew)
    {
        UIUtils::playInnerAction(FileNode_fashTank, "startloop3", true);
    }
    lobby_fashTank_tips->setVisible(isFishNew);
    gameView->updateFishNewTips();
}

void MainLobby::showDailyStart()
{
//    auto daily = panel_root->getChildByName<DailyView*>("DailyView");//dynamic_cast<DailyView*>(_rootLayers.at((int)Tab::Daily));
//    if (daily)
//        daily->showStart();
    SCENE_M->addDialog(DailyView::createLayerN());
}

void MainLobby::showBag(int type)
{
    isShowFanPai = false;//翻牌不显示，改为轮盘
    if(type == 7)
    {
        SCENE_M->addDialog(FashTankShop::createLayerN());
    }
    else
    {
        UIUtils::playInnerAction(FileNode_MyBag,"Start",false);
        auto bag = BagView::createLayerN(BagView::BagType::CARD);
        SCENE_M->addDialog(bag);
        bag->setTab((BagView::Tab)type);
    }
    
    isShowTop(false);
}

void MainLobby::showTaskNew()
{
    main_tips1_Task->setVisible(true);
}

void MainLobby::showSetNew(bool isShow)
{
    
}

Node* MainLobby::getTeachItem(const std::string &name, int idx)
{
    if (name == "Button_start")
        return panel_root->getChildByName<HomeView*>(name); //dynamic_cast<HomeView*>(_rootLayers.at((int)Tab::Home))->getNode(name);
    else if (name == "Button_gold")
        return panel_root->getChildByName<StoreView*>(name);  //dynamic_cast<StoreView*>(_rootLayers.at((int)Tab::Store))->getNode(name);
    return nullptr;
}

void MainLobby::effCeShi()
{
    auto poi = getContentSize()*0.5;
    goldAni(200,nullptr,poi,[this](){
        //更新有金币显示
        DATA_M->setCoinNum(200, true, 106);
        ValueMap valueMap{
            {"isTime",Value{true}}
        };
        //更新有金币显示
        EVENT_M->sendEvent("event_game_update_coin",valueMap);
        //SCENE_M->getLobby()->updateCoin(true);
    },[this](){
        //home
        //SOUND_M->playEffectMusic(EffectGetCoin);
        playGoldAni(2,true);
    },[this](){
       
        //SOUND_M->playEffectMusic(EffectGetCoin);
        playGoldAni(2,false);
    });
//    poi.width+=160;
//    diamondAni(120,nullptr,poi,[this](){
//        //更新有金币显示
//        DATA_M->setDiamond(120);
//        ValueMap valueMap{
//            {"isTime",Value{true}}
//        };
//        //更新有金币显示
//        EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//        //SCENE_M->getLobby()->updateDiamond(2);
//
//    },[this](){
//        //daily
//        //SOUND_M->playEffectMusic(EffectGetGem);
//        playDiamondAni(2,true);
//    },[this](){
//        //daily
//
//        //SOUND_M->playEffectMusic(EffectGetGem);
//        playDiamondAni(2,false);
//    });
}

void MainLobby::effCeShi0()
{
    auto poi = getContentSize()*0.5;
    //poi.width-=80;
    goldAni(200,nullptr,poi,[this](){
        //更新有金币显示
        DATA_M->setCoinNum(200, true, 107);
        ValueMap valueMap{
            {"isTime",Value{true}}
        };
        //更新有金币显示
        EVENT_M->sendEvent("event_game_update_coin",valueMap);
        //SCENE_M->getLobby()->updateCoin(true);
    },[this](){
        //home
        //SOUND_M->playEffectMusic(EffectGetCoin);
        playGoldAni(2,true);
    },[this](){
       
        //SOUND_M->playEffectMusic(EffectGetCoin);
        playGoldAni(2,false);
    });
}
void MainLobby::effCeShi1()
{
//    auto poi = getContentSize()*0.5;
//    diamondAni(120,nullptr,poi,[this](){
//        //更新有金币显示
//        DATA_M->setDiamond(120);
//        ValueMap valueMap{
//            {"isTime",Value{true}}
//        };
//        //更新有金币显示
//        EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//        //SCENE_M->getLobby()->updateDiamond(2);
//        
//    },[this](){
//        //daily
//        //SOUND_M->playEffectMusic(EffectGetGem);
//        playDiamondAni(2,true);
//    },[this](){
//        //daily
//        
//        //SOUND_M->playEffectMusic(EffectGetGem);
//        playDiamondAni(2,false);
//    });
}

void MainLobby::updateFishNum()
{
    auto bt = getNode<Button*>("Button_addFish");
    auto num = DATA_M->getFishNum();
    bt->setTitleText(StringUtils::format("添加%d/25", num).c_str());
}

bool MainLobby::getIsNewGame()
{
    bool isGameModel = false;
    bool isThreeModel = false;
    auto type = DataManager::GameType::Huo;
    if(type == DATA_M->getGameType())
    {//模式相同
        isGameModel = false;
    }
    else
    {//模式不同 必定新开
        isGameModel = true;
    }
    auto isThree = SCENE_M->getGameView()->getIsThreeModel();
    int i = -1;
    int j = -1;
    if(isThree)
    {
        i = 1;
    }
    else
    {
        i = 0;
    }
    if (DATA_M->getIsThreeModel())
    {
        j = 1;
    }
    else
    {
        j = 0;
    }
    if(i == j)
    {//翻牌次数相同
        isThreeModel = false;
    }
    else
    {//模式不同 必定新开
        isThreeModel = true;
    }
    return isThreeModel || isGameModel;
}

void MainLobby::setIsStart(bool is)
{
    isStart = is;
}
bool MainLobby::getIsStart()
{
    return isStart;
}

void MainLobby::hideLobby(std::function<void()> cb)
{
    UIUtils::playInnerAction(FileNode_top,"out",false);
    playAni("out", false,cb);
}

void MainLobby::rewardExp(int rewardNum,Vec2 startPoi)
{
    //经验
    auto player = PlayerManager::getInstance();
    player->addExp(rewardNum);
    lv = player->getLevel();
    oldLv = player->getOldLevel();
    percent1 = player->getPercent();
    percent2 = player->getPercent(true);
    
    if(lv == oldLv)
    {
        maxPercent = percent1 - percent2;
    }
    else
    {
        auto a = (lv-oldLv)*100 - percent2;
        auto b = percent1;
        maxPercent = a + b;
    }
    //速度
    //0.5s完成 s
    percentDx = maxPercent/0.5;//m/s
    percentDx *= 0.017;
    
    LevelUpView->setData(lv,oldLv, percent1,percent2,percentDx,nullptr);
    //创建5个经验节点 飞上去 经验条增长，增长完毕弹出结算
    auto poi = getLevelWorldPoi();
    //poi = _rootNode->convertToNodeSpace(poi);
    std::vector<Vec2> itemVec1;
    int expNum = rewardNum;
    DATA_M->randVec(expNum,&itemVec1,320);
    
    REWARD_M->rewardItemAction(expNum,poi,startPoi,itemVec1,[this](){

        if(lv == oldLv)
        {
            maxPercent = percent1 - percent2;
        }
        else
        {
            //LevelUpView->setIsBar(true);
            auto a = (lv-oldLv)*100 - percent2;
            auto b = percent1;
            maxPercent = a + b;
        }
        //速度
        //0.5s完成 s
        percentDx = maxPercent/0.5;//m/s
        percentDx *= 0.017;
        isBar = true;
    },"Exp",this,[this](){
        //SOUND_M->playEffectMusic(EffectGetGem);
        auto FileNode_level = getNode("FileNode_level");
        FileNode_level->setVisible(true);
        auto LevelBG_1 = getNode("LevelBG_1");
        LevelBG_1->setVisible(false);
        UIUtils::playInnerAction(FileNode_level,"Exp",false);
    },[this](){
        //SOUND_M->playEffectMusic(EffectGetGem);
        auto FileNode_level = getNode("FileNode_level");
        FileNode_level->setVisible(false);
        auto LevelBG_1 = getNode("LevelBG_1");
        LevelBG_1->setVisible(true);
    });
}


void MainLobby::rewardGold(int rewardNum,Vec2 startPoi)
{
    goldAni(rewardNum,nullptr,startPoi,[this,rewardNum](){
        //更新有金币显示
        DATA_M->setCoinNum(rewardNum, true, 108);
        ValueMap valueMap{
            {"isTime",Value{true}}
        };
        //更新有金币显示
        EVENT_M->sendEvent("event_game_update_coin",valueMap);
        //SCENE_M->getLobby()->updateCoin(1);
        
    },[this](){
        //home
        //SOUND_M->playEffectMusic(EffectGetCoin);
        playGoldAni(1,true);
    },[this](){
        
        playGoldAni(1,false);
    });
}

void MainLobby::rewardMagic(int rewardNum,Vec2 startPoi)
{
    magicAni(rewardNum,nullptr,startPoi,[this](){
        UIUtils::playInnerAction(FileNode_MyBag,"Start",false);
        
    });
}

void MainLobby::unlockFishMove(int idx,Vec2 startPoi,std::function<void()> cb)
{
    auto skeletonNode = FISH_M->getFishSpine(idx);
    this->addChild(skeletonNode);
    skeletonNode->setPosition(startPoi);
    auto size = skeletonNode->getBoundingBox().size;
    
    auto poi = getBtnFishWorldPoi();
    auto scale = gameView->getFishScale(size.width);
    auto time = 1.0f;
    auto moTo = MoveTo::create(time, poi);
    auto cubic = EaseCubicActionIn::create(moTo);
    auto scaleTo = ScaleTo::create(time, scale);
    auto spawn = Spawn::createWithTwoActions(cubic, scaleTo);
    auto remo = RemoveSelf::create();
    auto seq = Sequence::create(spawn, remo,CallFunc::create(cb),NULL);
    skeletonNode->runAction(seq);
    
}

void MainLobby::unlockFashTankMove(int idx,SpriteFrame* frame,Vec2 startPoi,std::function<void()> cb)
{
    auto sprite = Sprite::createWithSpriteFrame(frame);
    this->addChild(sprite);
    sprite->setPosition(startPoi);
    auto fashTank = SCENE_M->getGameBackground();
    fashTank->hideBuild();
    auto endPoi = fashTank->getPeiShiWorldPoi(idx+1);
    auto moTo = MoveTo::create(0.5f, endPoi);
    
    auto remo = RemoveSelf::create();
    auto seq = Sequence::create(moTo, remo,CallFunc::create(cb),NULL);
    sprite->runAction(seq);
}

Vec2 MainLobby::getBtnFishWorldPoi()
{
    auto node = getNode("Button_shopping");
    auto poi = node->getPosition();
    poi = node->getParent()->convertToWorldSpace(poi);
    return poi;
}

bool MainLobby::myTouchBegan(Touch * touch, Event * e)
{
    auto touchPoi = touch->getLocation();
    auto gameView = SCENE_M->getGameView();
    
    if(gameView->isVisible())
    {//在游戏中 判断一下点没点到牌

        SCENE_M->clickEff(touchPoi);
    }
    else
    {
        SCENE_M->clickEff(touchPoi);
    }
    return true;
}

void MainLobby::myTouchMoved(Touch * touch, Event * e)
{
    
}

void MainLobby::myTouchEnded(Touch * touch, Event * e)
{
    
}

void MainLobby::openReward(bool isOpen)
{
    auto aniName = isOpen?"out":"in";
    auto fashTank = SCENE_M->getGameBackground();
    fashTank->showBuild(!isOpen);
    
    playAni(aniName,false);
}

void MainLobby::showGetGoldBtn(bool isShow)
{
    getNode("Button_getGold")->setVisible(isShow);
}

void MainLobby::showWeiShiBtn(bool isShow)
{
    getNode("Button_weishi")->setVisible(isShow);
}

void MainLobby::clickFishShop()
{
    UIUtils::playInnerAction(FileNode_fish, "fish", false);
}

void MainLobby::updateBtnChallenge()
{
    auto isChallenge = DATA_M->getIsChallenge();
    getNode("btn_challenge")->setVisible(isChallenge);//更新
}
