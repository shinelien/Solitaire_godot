//
//  GameViewHD.cpp
//  SpacecatSolitaireGame
//
//  Created by Cyutao on 2018/8/27.
//
#include "GameViewHD.hpp"
#include "SpriteManager.h"
#include "CardSprite.h"
#include "GameTime.hpp"
#include "SettingViewHD.h"
#include "GamePauseHD.h"
#include "GameViewResetHD.h"
#include "ShopViewHD.h"
#include "TipsNode.h"
#include "LevelManager.h"
#include "WinLayerLevelHD.h"
#include "WinLayerDailyHD.h"
#include "WinLayer.h"
#include "FreeCoinLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#include "VungleManager.h"
#endif

#include "EventObserver.h"
#include "WinHD.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "DailyView.h"
#include "DailyNotice.h"
//道具
#include "ShuffleView.h"
#include "ScoreManager.h"
#include "SceneManager.h"
#include "NoMoveView.h"
#include "RewardManager.h"
#include "RewardRouletteView.h"
#include "MainLobby.h"
//任务
#include "DailytaskView.h"
#include "TaskManager.h"
//经验
#include "PlayerManager.h"
#include "ShopManager.h"
//
#include "GameRewardsView.h"
//翻牌
#include "FanPaiAD.h"
// 教学
#include "WinLayerTeach.h"
//
#include "GrowupNode.h"
#include "RankManager.hpp"
//事件
#include "EventObserver.h"

#include "LevelUpView.h"
#include "FashTankShop.h"
#include "BagView.h"
#include "TeachManager.h"
#include "WinLayerTeachUnlock.h"
#include "RankView.h"
#include "FishManager.h"
#include "GameBackground.h"
#include "GoldShop.h"
#include "ChallengeModeView.h"
#if TestAutoPlay
#include "BureauTestManager.h"
#endif
#include "FishGuideManager.h"
using namespace spine;

#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
const bool NO_AD = false;
#else
const bool NO_AD = false;
#endif

static const int MOVE_DELAY = 18;
// ai 事件上传
static const std::unordered_map<int, string> GameTypeDefine{
        {(int)DataManager::GameType::Huo, "1"},
        {(int)DataManager::GameType::Random, "1"},
        {(int)DataManager::GameType::Daily, "2"},
        {(int)DataManager::GameType::Level, "3"},
};
static const std::unordered_map<int, string> GameTypeDefineName{
        {(int)DataManager::GameType::Huo, "classiccountall"},
        {(int)DataManager::GameType::Random, "classiccountall"},
        {(int)DataManager::GameType::Daily, "dailycountall"},
        {(int)DataManager::GameType::Level, "missioncountall"},
};
bool _isGameStart = false;
void GameViewHD::sendStartGameEvent(DataManager::GameType gameType)
{
    _isGameStart = true;
    string model = GameTypeDefine.at((int)gameType);
    string modelName = GameTypeDefineName.at((int)gameType);
    auto countall = GETINTEGER("ai_p_countall", 0);
    SETINTEGER("ai_p_countall", ++countall);
    string key = "ai_p_count_" + model;
    auto count1 = GETINTEGER(key.c_str(), 0);
    SETINTEGER(key.c_str(), ++count1);
    ValueMap params {
            {"model", Value(model)},
            {"countall", Value(countall)},
            {"countmodel", Value(count1)},
    };
    UIUtils::FIRAnalyticsEvent("startGame", params);
    if (count1 == 5 || count1 == 15 || count1 == 20 || count1 == 30) {
        UIUtils::FIRAnalyticsEvent(StringUtils::format("new_play_%s_%d", modelName.c_str(), count1), params);
    }
    if (countall == 5 || countall == 15 || countall == 20 || countall == 45 || countall == 60) {
        UIUtils::FIRAnalyticsEvent(StringUtils::format("new_play_countall_%d", countall), params);
    }
    UIUtils::FIRFirestoreAddOP("startGame", model, toString(countall), toString(count1));
}

//参数值：1（新游戏）、2（重新开始）、3（返回大厅）、4（解开本局）
void GameViewHD::sendEndGameEvent(DataManager::GameType gameType, string endEvent)
{
    _isGameStart = false;
    string model = GameTypeDefine.find((int)gameType) != GameTypeDefine.end() ? GameTypeDefine.at((int)gameType) : GameTypeDefine.at((int)DataManager::GameType::Huo);
    auto countall = GETINTEGER("ai_p_countall", 0);
    string key = "ai_p_count_" + model;
    auto count1 = GETINTEGER(key.c_str(), 0);
    ValueMap params {
            {"model", Value(model)},
            {"countall", Value(countall)},
            {"countmodel", Value(count1)},
            {"endevent", Value(endEvent)},
    };
    UIUtils::FIRAnalyticsEvent("endGame", params);
    UIUtils::FIRFirestoreAddOP("endGame", model, toString(countall), toString(count1), endEvent);
}

bool isFirstBureau() { return GETINTEGER("ai_p_countall", 0)<=1; }

// moves1 总移动步数 moves2 有效移动 moves3 无效移动
void sendFirstBureauEvent(int moves1, int moves2, int moves3)
{
//    auto count1 = GETINTEGER("ai_p_countall", 0);
    if (isFirstBureau()) {
        ValueMap params;
        UIUtils::FIRAnalyticsEvent(StringUtils::format("new_play_moves_%d", moves1), params);
        UIUtils::FIRAnalyticsEvent(StringUtils::format("new_play_correct_%d", moves2), params);
        UIUtils::FIRAnalyticsEvent(StringUtils::format("new_play_wrong_%d", moves3), params);
    }
}

GameViewHD::GameViewHD()
:BaseLayer("GameLayerHD.csb")
,score(0)
,timeDelay(0)
,moveNum(0)
,_isLeftModel(false)
,isOver(true)
,isAuto(true)
,_gameRewardsView(nullptr)
,LevelUpView(nullptr)
,isParse(false)
,_faildNum(0)
{
    EventObserver::getInstance()->addListener("msg_event_game_redpoint_update", [this](ValueMap params, void *obj){
        updateRedPoint((DataManager::GameType)params["gameType"].asInt());
    }, this);
    
    isLunPanTime = true;
    _excludeRecord = true; // 不要记录进入
}

GameViewHD::~GameViewHD()
{
    EventObserver::getInstance()->removeListener("msg_event_game_redpoint_update", this);
}


void GameViewHD::nodedoLayout(Node* node)
{
    auto safeArea = Director::getInstance()->getSafeAreaRect();
    node->setPosition(safeArea.origin);
    node->setContentSize(safeArea.size);
    setContentSize(node->getContentSize());
    ui::Helper::doLayout(node);
}

void GameViewHD::initData()
{
    setName("GameLayer");
    EVENT_M->addListener("msg_game_tips_end",[this](ValueMap valueMap, void *obj){
        //关闭提示
        SPRITE_M->cancleTips();
        isShowTips = false;
        isCanTouch = true;
        panel_tips->setVisible(false);
    },this);
//    addEvent("msg_game_tips_end", [this](EventCustom*) {
//        
//    });
    // 监听插屏结束
    EVENT_M->addListener("msg_game_showwin",[this](ValueMap valueMap, void *obj){
        if (InterstitialCB) {
            InterstitialCB();
            InterstitialCB = nullptr;
        }
        
        DATA_M->setPlayAds(false);
        //重置限制插屏的cd
        DATA_M->setInterstitialTime();
        DATA_M->setIsVideoAdsTime(true);
        DATA_M->setVideoAdsTime(0,true);//重置激励视频对插屏的限制cd
        DATA_M->setIsShowAds(false);
    },this);
//    addEvent("msg_game_showwin", [this](EventCustom*) {
//        
//    });
    // 监听广告
    scaleFactor = Director::getInstance()->getOpenGLView()->getFrameSize().height/Director::getInstance()->getWinSize().height;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    scaleFactor = AdsManager::getFrameScaleFactor()/scaleFactor;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto density = UIUtils::getDensity();
    scaleFactor = density/scaleFactor;
#endif
//    // 添加下一关事件
//    addEvent("msg_game_level_next", [this](EventCustom* eventCustom) {
//        if (!DATA_M->isLevelMode()) return;
//        
//        bool noAds = false;
//        auto userDataBool = static_cast<__Bool*>(eventCustom->getUserData());
//        if (userDataBool)
//            noAds = userDataBool->getValue();
//        auto group = (*_levelData)["group"].GetInt()-1, sub = (*_levelData)["sub"].GetInt()-1;
//        auto groupData = LevelManager::getInstance()->getLevelData(group);
//        const auto &array = (*groupData)["data"].GetArray();
//        int totalCNT = array.Size();
//        if (sub < (totalCNT-1)) {
//            LevelManager::getInstance()->getLevelData(group, sub);
//            startLevelRank(LevelManager::getInstance()->getLevelData(group, sub+1), noAds);
//        }
//        else if (LevelManager::getInstance()->hasLevelGroup(group+1)) {
//            startLevelRank(LevelManager::getInstance()->getLevelData(group+1, 0), noAds);
//        }
//    });
    EVENT_M->addListener("event_game_level_relive", [this](ValueMap valueMap, void *obj){
        if (!DATA_M->isLevelMode()) return;
        levelRelive();
    },this);
    EVENT_M->addListener("reward_item_update", [this](ValueMap valueMap, void *obj){
        updateShuffle();
    },this);
    EVENT_M->addListener("event_game_scene_change", [this](ValueMap valueMap, void *obj){
        playEffect();
    },this);
//    addEvent("event_game_level_relive", [this](EventCustom *eventCustom){
//        if (!DATA_M->isLevelMode()) return;
//        levelRelive();
//    });
//    addEvent("event_game_scene_change", [this](EventCustom *eventCustom){
//        playEffect();
////        playMusic();
//    });
//    addEvent("reward_item_update", [this](EventCustom *eventCustom){
//        updateShuffle();
//    });
    addEvent("jni_event_custom_callcppwithstring", [this](EventCustom *eventCustom){
        CCLOG("jni_event_custom_callcppwithstring call c++:(%f)", scaleFactor);
        auto params = (__String*)eventCustom->getUserData();
        rapidjson::Document d;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        params->release();
#endif
        std::string load_str(params->getCString(), params->length());
        d.Parse<0>(load_str.c_str());
        if (d.HasParseError())
        {
            return;
        }
        if (d.IsObject()) {
            if (d.HasMember("msg")) {
                string msg(d["msg"].GetString());
                if (msg == "msg_banner_show") {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                    moveOffsetY = d["height"].GetDouble()*scaleFactor;
#else
                    moveOffsetY = 54*scaleFactor;
#endif
                    this->updateUI();
                }
                else if (msg == "msg_banner_hide") {
                    moveOffsetY = 0;
                    this->updateUI();
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
                else if (msg == "msg_rank_list") {
//                    _randConfig.Parse<0>(params->getCString());
                    RankManager::getInstance()->setRankList(load_str);

                    CCLOG("DBManager2c++: %s, length: %d", load_str.c_str(), load_str.length());
//                    if (_randConfig.HasParseError())
//                    {
//                        isParse = false;
//                        return;
//                    }
//                    isParse = true;
                    if(params->length() != 0)
                    {
                        Director::getInstance()->getScheduler()->performFunctionInCocosThread([this] {
                            EVENT_M->sendEvent("msg_rank_update");
                        });
                    }
                    
                }
                else if (msg == "msg_rank_list_cancel") {
                    Director::getInstance()->getScheduler()->performFunctionInCocosThread([this] {
                        EVENT_M->sendEvent("msg_rank_update_cancel");
                    });
                }
                else if (msg == "mag_log_adimpression") {
                    UIUtils::FIRFirestoreAddOP("is_ad_show", d["network"].GetString(), d["adunit"].GetString(), d["value"].GetString(), d["type"].GetString());
                }
                else if (msg == "game_purchase_sub") {  // 应用订阅
                    if (d.HasMember("productId")) {
                        string productId = d["productId"].GetString();
                        if (productId == "sub_noads_week" || productId == "sub_noads_month" || productId == "sub_noads_halfyear") {
                            DATA_M->setVipNoAds(true);
                            EVENT_M->sendEvent("game_purchase_sub_update"); // 更新按钮
                            UIUtils::FIRFirestoreAddOP("purchase_sub", productId);
                            UIUtils::FIRAnalyticsEvent("purchase_sub", {
                                    {"id", Value(productId)},
                            });
                        }
                    }
                }
                else if (msg == "game_purchase_sub_cancel") { // 订阅取消了
                    DATA_M->setVipNoAds(false);
                    EVENT_M->sendEvent("game_purchase_sub_update"); // 更新按钮
                }
                else if (msg == "game_purchase") { // 应用内购
//                    {"orderId":"GPA.3363-0565-2774-55761","packageName":"com.cn.spacecate.solitaire2k","productId":"gold_0","purchaseTime":1622189494132,"purchaseState":0,"purchaseToken":"gmlppegnelimbgghilbjnglj.AO-J1OyhKExzbkE2DkcHZBlJS-3i5AB8DLMjun4zPxOvMkeA7Z98UHF2g2VdUxUqPdZa3oEWAWbEv8uGGJ1DQDuz2BDcA2Qx36u1GP6XOD63Sd3j9KXzUIY","acknowledged":false,"msg":"game_purchase"}
                    if (d.HasMember("productId")) {
                        string productId = d["productId"].GetString();
                        if (productId.find("sub_") != string::npos) { // 订阅直接提示+上报就可以了 在上面game_purchase_sub处理
                            Director::getInstance()->getScheduler()->performFunctionInCocosThread([this] {
                                SCENE_M->showTips(Lang("100391"));
                            });
                            UIUtils::FIRFirestoreAddOP("gold_iap", productId);
                            return;
                        }

                        int goldNum = 0;
                        bool isHotBuy = productId.find(HOT_KEY)!=string::npos;
                        if(isHotBuy)
                        {//限购一次
                            DATA_M->setPurchaseLimit(true);
                        }
                        auto product = RankManager::getInstance()->getProduct(productId);
                        if (product) {
                            goldNum = isHotBuy?product->getHotPrice():product->getPrice();
                            if(isHotBuy) product->setIsHotBuy(); // 购买完成要标记
                        }
                        Director::getInstance()->getScheduler()->performFunctionInCocosThread([this, goldNum,productId] {
                            if (goldNum > 0) {
                                DATA_M->setCoinNum(goldNum, false, 110);
                                SOUND_M->playEffectMusic(EffectCoin);
                                SCENE_M->showTips(
                                        CCString::createWithFormat(Lang("huodejinbi").c_str(),
                                                                   goldNum)->getCString());
                                //更新有金币显示
                                EVENT_M->sendEvent("event_game_update_coin");
                            }
                            else {
                                if (productId == "gold_0") { // 去广告
                                    DATA_M->setVipNoAds(true);
                                    this->updateBanner();
                                }
                                SCENE_M->showTips(Lang("goumaichengg"));
                            }
                            RankManager::getInstance()->updateProducts(); // 刷新列表
                            getEventDispatcher()->dispatchCustomEvent("msg_purchase_update");
                        });
                        UIUtils::FIRFirestoreAddOP("gold_iap", productId, toString(goldNum));
                        UIUtils::FIRAnalyticsEvent("gold_iap", {
                            {"id", Value(productId)},
                            {"goldNum", Value(goldNum)},
                        });
                    }
                }
            }
            
        }
    });
    
    
    EVENT_M->addListener("event_game_update_rank", [this](ValueMap valueMap, void *obj){
        if(!valueMap.empty())
        {
            auto msg = valueMap["msg"].asString();
            if(msg == "msg_rank_list")
            {
                
                auto valueVec = valueMap["list"].asValueVector();
                string str = "";
                
                RankManager::getInstance()->setRankList(valueVec);
                Director::getInstance()->getScheduler()->performFunctionInCocosThread([this] {
                    EVENT_M->sendEvent("msg_rank_update");
                });
            }
            else if(msg == "msg_rank_list_cancel")
            {
                Director::getInstance()->getScheduler()->performFunctionInCocosThread([this] {
                    EVENT_M->sendEvent("msg_rank_update_cancel");
                });
            }
        }
        else
        {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([this] {
                EVENT_M->sendEvent("msg_rank_update_cancel");
            });
        }
    }, this);
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
                else if (msg == "msg_banner_hide") {
                    updateBanner();
                }
            }
        }
    }, this);
    addEvent("event_updatebanner", [this](EventCustom* eventCustom) {
        updateBanner();
    });
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
        
        this->updateDiamond();
    },this);
//    addEvent("event_game_update_coin", [this](EventCustom *e){
//        this->updateCoin();
//    });
//    addEvent("event_game_update_diamond", [this](EventCustom *e){
//        this->updateDiamond();
//    });
    EVENT_M->addListener("msg_game_lingqu_game", [this](ValueMap valueMap, void *obj){
        //领取金币
        if(!this->isVisible())return;
        gamePause(false);//窗口关闭取消暂停游戏
        auto lobby = SCENE_M->getLobby();
        auto poi = getGoldWorldPoi();
        lobby->goldAni(DATA_M->getRewardCoin1(),this,Vec2(2000,2000),[this](){
            
            DATA_M->setCoinNum(DATA_M->getRewardCoin1(), true, 111);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            //updateCoin();
        }
        ,[this](){
            //SOUND_M->playEffectMusic(EffectGetCoin);
        },[this](){
            //SOUND_M->playEffectMusic(EffectGetCoin);
        },poi);
        this->updateCoin();
    },this);
//    addEvent("msg_game_lingqu_game", [this](EventCustom*) {
//        
//    });
//    addEvent("event_game_update_gameBg_game", [this](EventCustom*) {
//        playEffect();
//        playMusic();
//    });
    
    EVENT_M->addListener("msg_game_pause", [this](ValueMap valueMap, void *obj){
        if(!this->isVisible())return;
        this->gamePause(false);
    },this);
    
    addEvent("msg_game_scoreani", [this](EventCustom* eventCustom) {
        auto card = static_cast<CardSprite*>(eventCustom->getUserData());
        if (card == nullptr) return;

        auto value = dynamic_cast<__Integer*>(card->getUserObject());
        if (value) {
            card->setUserObject(nullptr);
            int score = value->getValue();
            Node* scoreNode = nullptr;
            scoreNode = UIUtils::createCSBNode("card/Score.csb", score>0?"start0":"start1", false, [scoreNode](){
                if (scoreNode) scoreNode->removeFromParent();
            });
            scoreNode->getChildByName(score>0?"Node_Addpoints":"Node_Minuspoints")->getChildByName<TextBMFont*>(score>0?"Text_add":"Text_minus")->setString(StringUtils::toString(score));
            panel_game->addChild(scoreNode, 60);
            scoreNode->setPosition(card->getPosition());
//        scoreNode->setPosition(Vec2::ZERO);
        }
    }, true);
}



void GameViewHD::initUI()
{
    BaseLayer::initUI();
    //隐藏
    this->setVisible(false);
    doLayout();
    if (_isLeftModel != DATA_M->getIsLeftModel()) {
        _isLeftModel = DATA_M->getIsLeftModel();
        changePos();
    }
    
//    auto btn = getNode("Button_winceshi");
//    btn->setVisible(true);
//    btn->setPosition(Vec2(-540,720));
    //星星宝箱按钮
    getNode("Button_Collect")->setVisible(false);
    
    //暂停
    isPause = true;
    auto node_59 = getNode("Node_59");
    Button_pause = node_59->getChildByName<Button*>("Button_pause");
    //辅助色块
//    sprite_fuZhu_on = getNode<Sprite*>("Sprite_fuZhu_on");
//    sprite_fuZhu_off = getNode<Sprite*>("Sprite_fuZhu_off");
    //top
    getNode("Button_getGold")->setVisible(false);
    getNode("Button_getDiamond")->setVisible(false);
    
    //
    FileNode_2020Menu = getNode("FileNode_2020Menu");
    //FileNode_pause = getNode("FileNode_pause");
    FileNode_pause2 = getNode("FileNode_pause2");
    menu_fish_tips = getNode("menu_fish_tips");
    menu_fish_tips->setVisible(false);
    panel_bottom = getNode<Node*>("Panel_bottom");
    panel_game = getNode<Node*>("Node_bg");
    for (int i=0;i<4;i++) {
        auto tipsNode = TipsNode::createLayerN();
        tipsNode->setName(StringUtils::format("TipsNode_%d", i));
        panel_game->addChild(tipsNode, 101);
        tipsNode->setPosition(getNode(StringUtils::format("Sprite_aPoker%d", i))->getPosition());
    }
    refushSprite = getNode<Sprite*>("Sprite_wait");
    showAutoFinishBtn(false);
    SPRITE_M->setGamePanel(panel_game);
    // 初始化 背景
//    gameBg = SPRITE_M->initGameBg();
//
//    if (UIUtils::IsPad()) {
//        gameBg->setPosition(Vec2(vSize.width/2, vSize.height/2));
//    }
//    else {
//        gameBg->setAnchorPoint(Vec2::ZERO);
//    }
//    this->addChild(gameBg, -1);
    SPRITE_M->initCard();
    //
    //SPRITE_M->resetGame();
    //SPRITE_M->endAniShouPai();
    //ceshi
    ceshi();
    //SPRITE_M->pokerStartAni1();
    
    
    auto tipsLayer = panel_game->getChildByName<Layer*>("TipsLayer");
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](Touch*, Event*) -> bool {
        if (isShowTips&&panel_tips->isVisible())
        {
//            SPRITE_M->showNextTips();
            SPRITE_M->cancleTips();
            panel_tips->setVisible(false);
            isShowTips = false;
            isCanTouch = true;
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, tipsLayer);
    
    initLimitTimeHintLayer();
    auto listener2 = EventListenerTouchOneByOne::create();
    listener2->setSwallowTouches(true);
    listener2->onTouchBegan = [this](Touch*, Event*) -> bool {
        if (LimitTimeHintLayer->isVisible())
        {
            LimitTimeHintLayer->setVisible(false);
            node_levelhint->removeFromParent();
            node_levelhint = nullptr;
            isCanTouch = true;
            openLimitTimeHintTime = 0;
            _tipsTime = 0;
            if(hintCard)hintCard->setLocalZOrder(hintCard->getCLocalZOrder());
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, LimitTimeHintLayer);
    loadingBar_percent = getNode<LoadingBar*>("LoadingBar_level");
    loadingBar_menu_percent = getNode<LoadingBar*>("LoadingBar_menu_level");
    FileNode_top = getNode("FileNode_top");
    Text_lv = FIND_NODE(TextBMFont *, FileNode_top, "BitmapFontLabel_level");
    Text_MenuLv = FIND_NODE(Text *, FileNode_2020Menu, "Text_level");
    lv = PlayerManager::getInstance()->getLevel();
    Text_MenuLv->setString(StringUtils::format("%d",lv));
    //经验
    schedule([this](float dt){
        if(isBar)
        {
            //定时器
            if(lv == oldLv)
            {//lv == oldLv从percent2涨到percent1
                percent2+=percentDx/0.03 * dt;
                if(percent2 >= percent1)
                {
                    percent2 = percent1;
                    isBar = false;
                }
                loadingBar_percent->setPercent(percent2);
                loadingBar_menu_percent->setPercent(percent2);
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
                    
                    Text_MenuLv->setString(StringUtils::format("%d",dLv + oldLv));
                    Text_lv->setString(StringUtils::format("%d",dLv + oldLv));
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
                
                loadingBar_percent->setPercent(percent2);
                loadingBar_menu_percent->setPercent(percent2);
            }
            if(!isBar&&winCB)
            {//进度条涨完了
                winCB();
            }
        }
        else
        {
            dLv = 0;
        }
    }, 0.03, "scheduler_update_bar");
    
    //目标
    Image_Bar = getNode("Image_Bar");
    img_icon_gold = getNode("img_icon_top_gold");
    
    // 添加时间
//    gameTimeView = GameTime::createLayerN();
//    gameTimeView->setTime(0);
//    getNode<Node*>("Node_time")->removeAllChildren();
//    getNode<Node*>("Node_time")->addChild(gameTimeView);
//    gameTimeView->setPosition(Vec2::ZERO);
    
    // 结算页面
    _gameWinLayer = WinLayer::createLayer();
    _gameWinLayer->setVisible(false);
    addChild(_gameWinLayer, 101);
//    _gameWinLayerLevel = WinLayerLevelHD::createLayerN();
//    _gameWinLayerLevel->setVisible(false);
//    addChild(_gameWinLayerLevel, 101);
//    _gameWinLayerDaily = WinLayerDailyHD::createLayer();
//    _gameWinLayerDaily->setVisible(false);
//    addChild(_gameWinLayerDaily, 101);
    
    if (TEACH_M->isDailyLevelUnlock()) {
        //创建结算特效显示
        _gameRewardsView = GameRewardsView::createLayerN();
        _gameRewardsView->setVisible(false);
        addChild(_gameRewardsView, 1);
        _gameRewardsView->setPosition(panel_game->getPosition());
        
        LevelUpView = LevelUpView::createLayerN();
        LevelUpView->setType(LevelUpView::Type::Game);
        this->addChild(LevelUpView, 2);
        LevelUpView->setVisible(false);
        Text_level_up = LevelUpView->getNode<Text*>("Text_level_up");
    }
    
    
    
    
    
    // 胜利动画
    _winHD = WinHD::create();
    _winHD->setVisible(false);
    addChild(_winHD, 100);
    
    
    auto panel_daily = getNode("Panel_daliy");
    if (panel_daily)
        getNode("Panel_daliy")->setVisible(false);

    updateRedPoint();
    // 分数和时间
    //resetGameData();
    this->scheduleUpdate();

    // 初始化ui
    //getNode("FileNode_task")->setVisible(false);
    //getNode("FileNode_mode")->setVisible(false);
    //getNode("FileNode_relive")->setVisible(false);
    // 点击动画
    _actionManager->play("idle", true);

    //奖励
    panel_gift = getNode("panel_gift");
    panel_gift->setVisible(false);  // 广告延迟30s显示 DATA_M->getHaveVideo()
    FileNode_lunPan = getNode("FileNode_lunPan");
    FileNode_lunPan->setVisible(false);
    btn_gift_lingqu = getNode<Button*>("btn_gift_lingqu");
    Button_fanPai = getNode("Button_fanPai");
    Button_fanPai->setVisible(false);
//    schedule([this](float){
//        if(!isVisible()||isOver)return;
//        refushGift();
//        //updateRedPoint();
//    }, 10, "scheduler_update_gift");
    //刷新排行榜奖励
    updateRandReward();
    schedule([this](float){
        updateRandReward();
    }, 10, "scheduler_update_rank");
    
    lunPanTime = 20 * 60;//倒计时毫秒
    Text_Se = getNode<Text*>("Text_Se");
    Text_Mill = getNode<Text*>("Text_Mill");
    //轮盘禁用
//    schedule([this](float dt){
//
//        if(isLunPan&&isVisible())
//        {
//            lunPanTime-=1;
//
//            auto sec = (int)lunPanTime/60;//sec
//            auto mill = (int)lunPanTime%60;//毫秒
//            if(lunPanTime <= 0)
//            {
//                Text_Se->setString(StringUtils::format("%02d.",0));
//                Text_Mill->setString(StringUtils::format("%02d",0));
//                FileNode_lunPan->setVisible(false);
//                isLunPan = false;
//                lunPanShowNum = 0;
//
//                DATA_M->setFreeCoinTime2(DATA_M->getContentSec());
//            }
//            else
//            {
//                if(lunPanTime <= 10*60)
//                {
//                    Text_Se->setColor(Color3B::RED);
//                    Text_Mill->setColor(Color3B::RED);
//                }
//                Text_Se->setString(StringUtils::format("%02d.",sec));
//                Text_Mill->setString(StringUtils::format("%02d",mill));
//            }
//
//        }
//        else
//        {
//            lunPanTime = 20*60;
//        }
//    }, "scheduler_update_lunPan");
    
    
    BitmapFontLabel_challenge = getNode<TextBMFont*>("BitmapFontLabel_challenge");
    auto time = DATA_M->getNextFreeCoinTime5();
    
    auto num = DATA_M->getChallengeNum();
    int h = (int)(time / 3600);
    int m = (int)((int)time % 3600);
    m = (int)((int)m / 60);
    BitmapFontLabel_challenge->setString(StringUtils::format("%02d:%02d", h, m));
    
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
                BitmapFontLabel_challenge->setString(StringUtils::format("%02d:%02d", h, m));
            }
            else if(num < challengeMax)
            {//48小时过了并且没完成，隐藏
                DATA_M->setIsChallenge(false);
                getNode("btn_challenge")->setVisible(false);
//                DATA_M->setFreeCoinTime5(DATA_M->getContentSec());
//                //累积清零
                DATA_M->addChallengeNum(true);
            }
        }
    },1, "game_reward_Text_Sign_AD");
    
    FileNode_getMagic = getNode("FileNode_getMagic");
    
    FileNode_MyBag = getNode("FileNode_Bag");
    
    FileNode_StarBox = getNode("FileNode_StarBox");
    FileNode_StarBox2 = getNode("FileNode_StarBox2");
    
    //是第二天增加一次
    updateyday();
    
    //提示文本
    panel_tips = getNode("Panel_tips");
    
    //每日挑战提示
//    auto isNotifyOpen = DailyManager::getInstance()->isNotifyOpen();
//    if(isNotifyOpen)
//    {//每次登陆时提醒一次
//       addChild(DailyNotice::createLayerN());
//    }
    
    //getNode("Panel_top")->setVisible(false);
    //playAni("top0",false);
    //playAni("top1",false);//退出记分板
    getLevelWorldPoi();
    updateDYY();
    getNode<Text*>("Text_ShuffleNum_0")->setString(StringUtils::toString(RewardManager::getInstance()->getCNT(RewardManager::RewardType::Magic)));
//    getNode<Text*>("Text_ShuffleNum_1")->setString(StringUtils::toString(RewardManager::getInstance()->getCNT(RewardManager::RewardType::Magic)));
    auto Text_StarNum_ = FIND_NODE(Text*, FileNode_StarBox,"Text_StarNum_");
    Text_StarNum_->setString("/");
    //修正宝箱文本位置
    auto starSize = Text_StarNum_->getBoundingBox().size;
    Text_StarNum_->getChildByName("BitmapFontLabel_StarNum")->setPosition(Vec2(starSize.width*-0.4f,starSize.height*0.5));
    Text_StarNum_->getChildByName("BitmapFontLabel_StarNumMax")->setPosition(Vec2(starSize.width*1.5f,starSize.height*0.5));
    updateBanner();
}

void GameViewHD::updateBanner()
{
    auto loaded = true; //UIUtils::bannerLoaded();
    CCLOG("WTF loaded???%d", loaded?1:0);
    if (loaded) {
        moveOffsetY = DATA_M->isVipNoAds()?0:54*scaleFactor;
        this->updateUI();
    }
}

void GameViewHD::hideLunPan()
{
    isLunPan = false;
    FileNode_lunPan->setVisible(false);
    panel_gift->setVisible(false);
}

void GameViewHD::refushGift()
{//DATA_M->getHaveVideo()
    //游戏内奖励停用
    return;
    if(!TEACH_M->isTaskUnlock()||TEACH_M->isTeaching("firstBureau"))
    {//教学模式不显示
        panel_gift->setVisible(false);
        return;
    }
    if(!isVisible()||isOver||!isRefushGift)return;
    if(isAuto)return;//游戏结束了
    if(DATA_M->getHaveVideo()&&!isOver)
    {
        panel_gift->setVisible(true);
        //视频停用
        //判定经典模式前十局多倍奖励 是否启用视频
//        auto num = ScoreManager::getInstance()->getWinTotalCNT();
//        auto isAds = num > GAMENOADSCNT;
//        if(isAds&&!FileNode_lunPan->isVisible())
//        {
//            btn_gift_lingqu->setVisible(true);
//        }
//        else
//        {
//            btn_gift_lingqu->setVisible(false);
//        }
//        if (isAds&&DATA_M->getNextFreeCoinTime() <= 0&&DATA_M->getHaveVideo()&&!isOver&&!FileNode_lunPan->isVisible())
//        {
//            //免费的
//            btn_gift_lingqu->setVisible(true);
//
//            btn_gift_lingqu->setEnabled(true);
//        }
//        else
//        {
//            //lunPanTime = 20 * 60;//倒计时毫秒
//            btn_gift_lingqu->setVisible(false);
//        }
        //轮盘禁用
//        if(DATA_M->getNextFreeCoinTime3() <= 0&&!FileNode_lunPan->isVisible()&&lunPanShowNum == 1)
//        {//轮盘60s
//            FileNode_lunPan->setVisible(true);
//            if(isLunPanTime)
//            {
//                UIUtils::playInnerAction(FileNode_lunPan, "Start1", false);
//                Text_Se->setString(StringUtils::format("%02d.",20));
//                Text_Mill->setString(StringUtils::format("%02d",0));
//                Text_Se->setColor(Color3B::WHITE);
//                Text_Mill->setColor(Color3B::WHITE);
//                isLunPan = true;
//            }
//            else
//            {//复位
//                FileNode_lunPan->setPositionX(btn_gift_lingqu->getPositionX());
//                UIUtils::playInnerAction(FileNode_lunPan, "Start0", true);
//            }
//            lunPanShowNum = 0;
//            isLunPanTime = false;
//            btn_gift_lingqu->setVisible(false);
//        }
//        else if(lunPanTime <= 0&&isLunPanTime)
//        {
//            FileNode_lunPan->setVisible(false);
//            //btn_gift_lingqu->setVisible(true);
//            lunPanTime = 20 * 60;//倒计时毫秒
//            //isLunPan = false;
//        }
        //翻牌禁用
//        getNode<Text*>("Text_fanPaiNum")->setString(StringUtils::toString(GETINTEGER("fanPaiNum",3)));
//        if(isAds&&DATA_M->getNextFreeCoinTime4() <= 0&&fanPaiShowNum == 1&&!getNode("Button_teach")->isVisible()&&GETINTEGER("fanPaiNum") > 0&&DATA_M->getHaveInterstitials())
//        {//翻牌
//            Button_fanPai->setVisible(true);
//        }
//        else
//        {
//            Button_fanPai->setVisible(false);
//        }
    }
    else
    {
        panel_gift->setVisible(false);
    }
    
}

void GameViewHD::startGame()
{
    if(!GUIDE_M->isEnd(FishGuideManager::GuideType::StartOne))
    {
        GUIDE_M->startGuide(FishGuideManager::GuideType::StartOne);
    }
    auto winningsnt = ScoreManager::getInstance()->getScore(!DATA_M->getIsThreeModel()?1:0, ScoreManager::Type::WINNINGSNT);
    if(winningsnt == 0)
    {//重开或新开弹出限时挑战
        showChallenge();
    }
    
    isCanTouch = true;
    setGameState(State::Play);
    //发牌结束 显示奖励
    if(!isRefushGift)
    {
        isRefushGift = true;
    }
    //在此加入引导，第二局开始后， 引导使用魔法棒
    //只需要一个位置
    
//    TEACH_M->startTeach("game_magic");
//    TEACH_M->nextTeachStep(this);
//    img_waitnum->setVisible(true);
}

void GameViewHD::gamePause(bool isPause)
{
    this->isPause = isPause;
}

void GameViewHD::setGameOverState()
{
    isOver = true;
    isPause = true;
    isRefushGift = false;//游戏结束了不刷新显示奖励
}

bool GameViewHD::getGameOver()
{
    return isOver;
}

bool GameViewHD::getIsAuto()
{//是否进入自动收牌 或经验结算
    return isAuto;
}

void GameViewHD::showStartTips()
{
    _winHD->setVisible(false);
    _actionManager->play("touch", true);
}


void GameViewHD::gameOver(bool isWin)
{
    if (isOver) // 结束了就不要在调用了
        return;
    if (_gameRewardsView == nullptr) {
        _gameRewardsView = GameRewardsView::createLayerN();
        _gameRewardsView->setVisible(false);
        addChild(_gameRewardsView, 1);
        _gameRewardsView->setPosition(panel_game->getPosition());
    }
    if (LevelUpView == nullptr) {
        LevelUpView = LevelUpView::createLayerN();
        this->addChild(LevelUpView, 2);
        LevelUpView->setVisible(false);
        
        Text_level_up = LevelUpView->getNode<Text*>("Text_level_up");
        auto Text_level_up_lv = LevelUpView->getNode<Text*>("Text_level_up_lv");
        Text_level_up_lv->setString(Lang("100200"));
    }
    SCENE_M->removeLayerByName("BagView"); // 关闭背包
    SCENE_M->removeLayerByName("FreeCoinLayer"); // 关闭金币页面
    setGameOverState();
    //UIUtils::showDialog(panel_pause, "img_end");
    int level = DATA_M->isDailyMode()?dailyType:0;
    if (isWin)
    {
//#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
//        AdsManager::showInterstitial();
//#endif
        /*if (DATA_M->isDailyMode()) {
            _winHD->setVisible(true);
//            DailyManager::getInstance()->complete();
            _winHD->show([this](cocos2d::Ref*) {
                _winHD->setVisible(false);
                _actionManager->play("touch", true);
                SCENE_M->addDialog(DailyView::createLayerN()->showComplete(), true);
            });
            return;
        }*/
        if(DATA_M->getIsChallenge())
        {
            DATA_M->addChallengeNum();
        }
        
        
        if (TEACH_M->isTeaching("firstBureau")) { //新手教学关卡 不应该有什么奖励存在
            auto teach_cn = [this](Ref*){
                this->addChild(WinLayerTeach::createLayerN());
            };
            if (DATA_M->isWinHDEnable()) {
                _winHD->setVisible(true);
                _winHD->show(teach_cn);
            }
            else {
                teach_cn(nullptr);
            }
            return;
        }
        
        if(DATA_M->isDailyMode())
        {
            sendEndGameEvent(DataManager::GameType::Daily, "4");
            auto dailyManager = DailyManager::getInstance();
            auto date = dailyManager->getCurrentDate();
            auto mode = dailyManager->getCurrentMode();
            auto completed = dailyManager->isDailyCompleted(date, mode);
            
            //累计挑战对局3次 新手ADSORDAILY
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::ADSORDAILY);
            //累计挑战对局 新手
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::DAILY);
            //累计挑战1局对局 每日
            TASK_M->addTaskNum((int)TaskManager::DayTaskType::ONEDAILY + 100);
            //累计挑战3局对局 每日
            TASK_M->addTaskNum((int)TaskManager::DayTaskType::THREEDAILY + 100);
            if(mode == "2")
            {//中等
                //累计挑战中等对局 每日
                TASK_M->addTaskNum((int)TaskManager::DayTaskType::DAILYMIDDLE + 100);
            }
            else if(mode == "4")
            {
                //累计挑战专家对局 每日
                TASK_M->addTaskNum((int)TaskManager::DayTaskType::DAILYEXPERT + 100);
            }
            
            DATA_M->setStarBoxNum(1);
        }
        else if(!DATA_M->isLevelMode())
        {
            sendEndGameEvent(DATA_M->getGameType(), "4");
            if(DATA_M->getGameType() == DataManager::GameType::Random)
            {
                if(isThreeModel)
                {//是三张 困难
                    //累计经典3张对局 每日
                    TASK_M->addTaskNum((int)TaskManager::DayTaskType::THREEHARD + 100);
                }
                //累计经典5局困难对局 每日
                TASK_M->addTaskNum((int)TaskManager::DayTaskType::FIVEHARD + 100);
                
            }
            else
            {
                if(isThreeModel)
                {//是三张 活局
                    //累计经典3张对局 每日
                    TASK_M->addTaskNum((int)TaskManager::DayTaskType::THREEHUO + 100);
                }
                //累计经典1局对局 新手
                TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::CLASSIC);
                //累计经典1局对局 每日
                TASK_M->addTaskNum((int)TaskManager::DayTaskType::ONECLASSIC + 100);
                //累计经典3局对局 每日
                TASK_M->addTaskNum((int)TaskManager::DayTaskType::THREECLASSIC + 100);
            }
            
            DATA_M->setStarBoxNum(1);
        }
        
        
        if (DATA_M->isLevelMode()) {
            //isOver 应为false
            isOver = false;
            levelComplete(true);
        }
        else {
            // 教学记录win的次数
            TEACH_M->addWinTimes();
            //弹出结算前
            playAni("top1",false);
            //退出记分板 播放动画。动画结束,显示top0  获得经验
            isAuto = true;
            //隐藏按钮
            menuMove(true);
//            FileNode_2020Menu->setVisible(false);
            //隐藏信封与轮盘
            panel_gift->setVisible(false);
            FileNode_lunPan->setVisible(false);
//            Image_LunPan->setVisible(false);
            getNode("Panel_daliy")->setVisible(false);
            getNode("Panel_level")->setVisible(false);
            getNode("Button_auto")->setVisible(false);
            
            //搞个步数
            auto extraScore = int(NBSCORE/timeDelay);
            if(extraScore > 20000)
            {
                CCLOG("eree");
            }
            auto star = getStar();
            
            if(isCeShiWin)
            {
                star = 3;
                extraScore = 1000;
            }

            
            this->runAction(Sequence::create(DelayTime::create(0.2), CallFunc::create([this, extraScore,level, star]{
                //得到连败场数
                _faildNum = ScoreManager::getInstance()->getScore(!DATA_M->getIsThreeModel()?1:0, ScoreManager::Type::FAILDNINGSNT);
                DATA_M->settlementGameOnWin(SPRITE_M->isThreeModel ? 2 : 1, isUseBack, score, (int)timeDelay, moveNum, extraScore, star);
                auto num = ScoreManager::getInstance()->getWinTotalCNT(false);
                if(num >= 4&&DATA_M->getIsChallengeOpen())
                {
                    DATA_M->setIsChallenge(true);
                }
                ScoreManager::getInstance()->setDataCNT(SPRITE_M->isThreeModel ? 2 : 1, _magicCNT,_tipsCNT,_useBackCNT,score,(int)timeDelay);//洗牌数 提示数 回退数 分数 时间
                setGameState(State::End);
                if (DATA_M->isWinHDEnable()&&!isCeShiWin) {
                    //出现动画 隐藏牌区
                    
                    SPRITE_M->showPaiQu(false);
                    _winHD->setVisible(true);
                    _winHD->show([this, extraScore,level, star](cocos2d::Ref*){
                        
                        
                        _winHD->setVisible(false);
                        //隐藏场景内容
                        SPRITE_M->clearAllData();
                        //panel_game->setVisible(false);
                        // j新手
                        //2020Gamerewards
                        _gameRewardsView->setVisible(true);
                        //（210000/(时间+步数+得分)）+（基础经验值80）
                        
                        auto exp = int((NBEXP/timeDelay + moveNum + score) / 100 + 80);
                        if(isCeShiWin)
                        {
                            exp = 100;
                        }
                        _winExp = exp;
                        //进度条跑完后调用winCB //动画播放完毕播放
                        static bool winCB_once = true;
                        winCB_once = true; // 好像回调用两次
                        winCB = [this, extraScore,level, star](){
                            //结束插屏
                            if (!winCB_once) {
                                return;
                            }
                            winCB_once = false;
                            auto cb = [this, extraScore,level, star](){
                                _gameRewardsView->setVisible(false);
                                auto taskCb = [this, extraScore,level, star](){
                                    if (_winEffectID) {
                                        SOUND_M->stopEffectMusic(_winEffectID);
                                        _winEffectID = 0;
                                    }
                                    if (false&&DATA_M->isDailyMode()) {
//                                        this->_gameWinLayerDaily->setVisible(true);
//                                        this->_gameWinLayerDaily->showAction(score, timeDelay, moveNum, extraScore, star);
                                    }
                                    else {
                                        this->_gameWinLayer->setVisible(true);
                                        this->_gameWinLayer->showAction(score, timeDelay, moveNum, extraScore, star);
                                    }
                                };
                                
                                

                                    taskCb();
                            };
                            
                            {
                                cb();
                            }
                        };
                        
                        //获得经验
                        auto player = PlayerManager::getInstance();
                        Text_MenuLv->setString(StringUtils::format("%d",player->getLevel()));
                        Text_lv->setString(StringUtils::format("%d",player->getLevel()));
                        auto percent22 = player->getPercent();
                        loadingBar_percent->setPercent(percent22);
                        loadingBar_menu_percent->setPercent(percent22);
                         //PlayerManager::getInstance()->getExp()+1;
                        if(DATA_M->isDailyMode())
                        {
                            auto dailyManager = DailyManager::getInstance();
                            auto date = dailyManager->getCurrentDate();
                            auto mode = dailyManager->getCurrentMode();
                            auto completed = dailyManager->isDailyCompleted(date, mode);
                            if(!completed)
                            {
                                auto levelUp = player->addExp(exp);
                            }
                            else
                            {
                                exp = exp/2;
                                _winExp = exp;
                                auto levelUp = player->addExp(exp);
                            }
                        }
                        else if(DATA_M->isLevelMode())
                        {
                            
                        }
                        else
                        {
                            auto levelUp = player->addExp(exp);
                        }
                        _extraScore = (score+extraScore) / 10;
                        //经验条
                        lv = player->getLevel();
                        oldLv = player->getOldLevel();
                        percent1 = player->getPercent();
                        percent2 = player->getPercent(true);
                        //没有升级时在此添加出现结算窗口回调
                        _gameRewardsView->updateUI(_extraScore,exp,winCB);//是否显示 显示什么
                        _gameRewardsView->setScore(isThreeModel?0:1, true, _extraScore);//更新数据
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

//                        playAni("top0",false);
//                        //创建5个经验节点 飞上去 经验条增长，增长完毕弹出结算
//                        auto poi = getLevelWorldPoi();
//                        //poi = _rootNode->convertToNodeSpace(poi);
//                        std::vector<Vec2> itemVec1;
//                        int expNum = exp==5?5:exp*0.7;
//                        DATA_M->randVec(expNum,&itemVec1,320);
//
//                        REWARD_M->rewardItemAction(expNum,poi,this->getContentSize()*0.5,itemVec1,[this](){
//
//                            if(lv == oldLv)
//                            {
//                                maxPercent = percent1 - percent2;
//                            }
//                            else
//                            {
//                                auto a = (lv-oldLv)*100 - percent2;
//                                auto b = percent1;
//                                maxPercent = a + b;
//                            }
//                            //速度
//                            //0.5s完成 s
//                            percentDx = maxPercent/0.5;//m/s
//                            percentDx *= 0.017;
//                            isBar = true;
//                        },"Exp",this,[this](){
//                            //SOUND_M->playEffectMusic(EffectGetGem);
//                            auto FileNode_level = getNode("FileNode_level");
//                            FileNode_level->setVisible(true);
//                            auto LevelBG_1 = getNode("LevelBG_1");
//                            LevelBG_1->setVisible(false);
//                            UIUtils::playInnerAction(FileNode_level,"Exp",false);
//                        },[this](){
//                            //SOUND_M->playEffectMusic(EffectGetGem);
//                            auto FileNode_level = getNode("FileNode_level");
//                            FileNode_level->setVisible(false);
//                            auto LevelBG_1 = getNode("LevelBG_1");
//                            LevelBG_1->setVisible(true);
//                        });
                        
//                        SCENE_M->addDialog(WinLayer::createLayer(score, timeDelay, moveNum, extraScore, star));
                        
                    });
                }
                else {
                    //隐藏场景内容
                                            //panel_game->setVisible(false);
                    SPRITE_M->clearAllData();
                    // j新手
                    //2020Gamerewards
                    _gameRewardsView->setVisible(true);
                    //（210000/(时间+步数+得分)）+（基础经验值80）
                    auto exp = int((NBEXP/timeDelay + moveNum + score) / 100 + 80);
                    if(isCeShiWin)
                    {
                        exp = 100;
                    }
                    _winExp = exp;
                    //进度条跑完后调用winCB //动画播放完毕播放
                    static bool winCB_once = true;
                    winCB_once = true; // 好像回调用两次
                    winCB = [this, extraScore,level, star](){
                        //结束插屏
                        if (!winCB_once) {
                            return;
                        }
                        winCB_once = false;
                        auto cb = [this, extraScore,level, star](){
                            _gameRewardsView->setVisible(false);
                            
                            auto taskCb = [this, extraScore,level, star](){
                                if (_winEffectID) {
                                    SOUND_M->stopEffectMusic(_winEffectID);
                                    _winEffectID = 0;
                                }
                                if (false&&DATA_M->isDailyMode()) {
//                                    this->_gameWinLayerDaily->setVisible(true);
//                                    this->_gameWinLayerDaily->showAction(score, timeDelay, moveNum, extraScore, star);
                                }
                                else {
                                    this->_gameWinLayer->setVisible(true);
                                    this->_gameWinLayer->showAction(score, timeDelay, moveNum, extraScore, star);
                                }
                            };
                                taskCb();
                        };
                        

                        {
                            cb();
                        }
                    };
                    
                    //获得经验
                    auto player = PlayerManager::getInstance();
                    Text_MenuLv->setString(StringUtils::format("%d",player->getLevel()));
                    Text_lv->setString(StringUtils::format("%d",player->getLevel()));
                    auto percent22 = player->getPercent();
                    loadingBar_percent->setPercent(percent22);
                    loadingBar_menu_percent->setPercent(percent22);
                     //PlayerManager::getInstance()->getExp()+1;
                    if(DATA_M->isDailyMode())
                    {
                        auto dailyManager = DailyManager::getInstance();
                        auto date = dailyManager->getCurrentDate();
                        auto mode = dailyManager->getCurrentMode();
                        auto completed = dailyManager->isDailyCompleted(date, mode);
                        if(!completed)
                        {
                            auto levelUp = player->addExp(exp);
                        }
                        else
                        {
                            exp = exp/2;
                            _winExp = exp;
                            player->addExp(exp);
                        }
                    }
                    else if(DATA_M->isLevelMode())
                    {
                        
                    }
                    else
                    {
                        auto levelUp = player->addExp(exp);
                    }
                    _extraScore = (score+extraScore) / 10;
                    //经验条
                    lv = player->getLevel();
                    oldLv = player->getOldLevel();
                    percent1 = player->getPercent();
                    percent2 = player->getPercent(true);
                    _gameRewardsView->updateUI(_extraScore,exp,winCB);//是否显示 显示什么
                    _gameRewardsView->setScore(isThreeModel?0:1, true, _extraScore);//更新数据
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
                    //playAni("top0",false);
//                    //创建5个经验节点 飞上去 经验条增长，增长完毕弹出结算
//                    auto poi = getLevelWorldPoi();
//                    //poi = _rootNode->convertToNodeSpace(poi);
//                    std::vector<Vec2> itemVec1;
//                    int expNum = exp==5?5:exp*0.7;
//                    DATA_M->randVec(expNum,&itemVec1,320);
                                            
//                                            REWARD_M->rewardItemAction(expNum,poi,this->getContentSize()*0.5,itemVec1,[this](){
//
//                                                if(lv == oldLv)
//                                                {
//                                                    maxPercent = percent1 - percent2;
//                                                }
//                                                else
//                                                {
//                                                    auto a = (lv-oldLv)*100 - percent2;
//                                                    auto b = percent1;
//                                                    maxPercent = a + b;
//                                                }
//                                                //速度
//                                                //0.5s完成 s
//                                                percentDx = maxPercent/0.5;//m/s
//                                                percentDx *= 0.017;
//                                                isBar = true;
//                                            },"Exp",this,[this](){
//                                                //SOUND_M->playEffectMusic(EffectGetGem);
//                                                auto FileNode_level = getNode("FileNode_level");
//                                                FileNode_level->setVisible(true);
//                                                auto LevelBG_1 = getNode("LevelBG_1");
//                                                LevelBG_1->setVisible(false);
//                                                UIUtils::playInnerAction(FileNode_level,"Exp",false);
//                                            },[this](){
//                                                //SOUND_M->playEffectMusic(EffectGetGem);
//                                                auto FileNode_level = getNode("FileNode_level");
//                                                FileNode_level->setVisible(false);
//                                                auto LevelBG_1 = getNode("LevelBG_1");
//                                                LevelBG_1->setVisible(true);
//                                            });
//                    if (_winEffectID) {
//                        SOUND_M->stopEffectMusic(_winEffectID);
//                        _winEffectID = 0;
//                    }
//                    if (DATA_M->isDailyMode()) {
//                        this->_gameWinLayerDaily->setVisible(true);
//                        this->_gameWinLayerDaily->showAction(score, timeDelay, moveNum, extraScore, star);
//                    }
//                    else {
//                        this->_gameWinLayer->setVisible(true);
//                        this->_gameWinLayer->showAction(score, timeDelay, moveNum, extraScore, star);
//                    }
                }
            }), NULL));
            ValueMap bureauParams {
                    {"bu", Value(SPRITE_M->getCurrentBureau())},
                    {"win", Value(true)},
                    {"bt", Value((int)DATA_M->getGameType())},
                    {"pt", Value(SPRITE_M->isThreeModel ? 3 : 1)},
                    {"playtime", Value((int)timeDelay)},
                    {"moves", Value(moveNum)},
                    {"score", Value(score+extraScore)},
                    {"backmoves", Value(useBackCNT)},
                    {"star", Value(star)},
                    {"tips", Value(_tipsCNT)},
                    {"noTips", Value(noMoveTipsNum)},
                    {"level", Value(level)},
                    {"shuffle", Value(_magicCNT)},

                    {"daily", Value(DailyManager::getInstance()->getCurrentDate().name())},
                    {"hard", Value(DailyManager::getInstance()->getCurrentMode())},
                    {"openEffe", Value(SPRITE_M->getIsOpenEffective())},//是否开启辅助 2.步数限定
                    {"openEffeNum", Value(SPRITE_M->getFanPaiNum())},
            };
            UIUtils::FIRFirestoreAdd("bureau", bureauParams);
            UIUtils::FIRAnalyticsEvent("game_bureau_win", bureauParams);
//            sendFirstBureauEvent(moveNum, moveNum - noMoveTipsNum, noMoveTipsNum);
        }
    }
    else
    {
        if(timeDelay != 0)
        {//没有开启对局重开不记录局数
            //中断连胜；
            //_gameRewardsView->initDayWin();
            DATA_M->settlementGameOnFail(SPRITE_M->isThreeModel ? 2 : 1, (int)timeDelay, score);
            auto num = ScoreManager::getInstance()->getWinTotalCNT(false);
            if(num >= 4&&DATA_M->getIsChallengeOpen())
            {
                DATA_M->setIsChallenge(true);
            }
            onFaild(level);
        }
    }
    //
}

void GameViewHD::resetGameData()
{
    //补充魔法棒
//    auto num = RewardManager::getInstance()->getCNT(RewardManager::RewardType::Magic);
//    if(num < 2)
//    {
//        int n = 2;
//        n = n - num;
//        RewardManager::getInstance()->getReward(RewardManager::RewardType::Magic,n,true);
//    }
    
    updateBtnChallenge();
    auto totalWinCNT = ScoreManager::getInstance()->getScore(DATA_M->getIsThreeModel()?2:1, ScoreManager::Type::WINCNT);
    auto winRate = ScoreManager::getInstance()->getScore(DATA_M->getIsThreeModel()?2:1, ScoreManager::Type::WINRATE);
    //得到连败场数
    auto faildNum = ScoreManager::getInstance()->getScore(!DATA_M->getIsThreeModel()?1:0, ScoreManager::Type::FAILDNINGSNT);
    //失败两次了 就换简单的
    bool isFaild = faildNum >= 1;
    auto isNan = totalWinCNT > 1 && winRate>45 && !isFaild;
    getNode<Text*>("Text_winceshi")->setString(isNan?"难":"易");
    
    
    //游戏直接胜利
    isCeShiWin = false;
    
    //发牌期间不显示奖励
    isRefushGift = false;
    //每局轮盘出现的次数1次
    lunPanShowNum = 1;
    fanPaiShowNum = 1;
    isLunPan = false;
    //显示防错，每局开始都刷新一下道具数
    updateShuffle();
    
    FileNode_2020Menu->setVisible(true);
    panel_game->setVisible(true);
    isBar = false;
    isQieHuan = false;
    isAuto = false;
    ceshi();
    isAutoShouPai = false;
    LimitTimeHintNum = 0;
    isOpenLimitTimeHint = false;
    isOpenTipsTime = true;
    noMoveTipsNum = 0;
    noMoveTipsNum2 = 0;
    _tipsTime = 0;
    openLimitTimeHintTime = 0;
    isPause = true;//提前暂停，在视频播放前暂停
    isOver = false;
    isUseBack = false;
    isMoveCard = false;
    isCanTouch = false;
    isTouchRefush = false;
    isShowTips = false;
    
    selectCard = NULL;
    
    isThreeModel = DATA_M->getIsThreeModel();

    
    //显示分数
    score = 0;
    
    
    timeDelay = 0;
    moveNum = -1;
    useBackCNT = 0;
//    noTipsCNT = 0; // 无有效 移动
//    _shuffleCNT = 0;
    completeCNT = 0;
    _winEffectID = 0;
    _reliveCNT = 0;
    autoTipsTime = 0;
    extraCDTime = SPRITE_M->isThreeModel?3*ThreeFlopSpaceTime:0;
    addMoveNum();
//    gameTimeView->setTime(0);
    updateScore(0);
    updateTime(0);
    _magicCNT = 0;
    _tipsCNT = 0;
    _useBackCNT = 0;
//    img_waitnum->setVisible(false);
    showAutoFinishBtn(false);
    _winHD->setVisible(false);
    // 界面引导按钮
    getNode("Button_teach")->setVisible(false);//TEACH_M->isTeachBureauOpen());
    if(TEACH_M->isTeachBureauOpen())
    {
        auto FileNode_teach = getNode("FileNode_teach");
        UIUtils::playInnerAction(FileNode_teach, "KingLoop", true);
    }
    //;
}

void GameViewHD::resetGame(const string pokers)
{
//#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
//    AdsManager::showInterstitial();
//#endif
    setGameOverState();
    
//    panel_reset->setVisible(false);
    resetGameData();
    //重置游戏
    SPRITE_M->showPaiQu(true);
    SPRITE_M->resetGame(pokers);
    setFuZhuTipsColor(SPRITE_M->getIsOpenEffective());
    panel_gift->setVisible(false);
    bool levelMode = DATA_M->isLevelMode();
    auto panel_sub = getNode("Panel_sub");
    if (panel_sub)
        panel_sub->setVisible(!levelMode);
    
    //--新增
    getNode("text_mainmove")->setVisible(!levelMode);
    getNode("text_maintime")->setVisible(!levelMode);
    getNode("Score")->setVisible(!levelMode);
    
    //---
    getNode("Node_time")->setVisible(!levelMode);
    getNode("text_mainscore")->setVisible(!levelMode);
    getNode("Panel_times")->setVisible(!levelMode);
    getNode("game_score1_game")->setVisible(!levelMode);
    //getNode("FileNode_mode")->setVisible(levelMode);
    //getNode("FileNode_relive")->setVisible(false);
    auto panel_level = getNode("Panel_level");
    panel_level->setVisible(levelMode);
    if (levelMode) {
        auto Image_moveBg = getNode("Image_moveBg");
        auto rect = Image_moveBg->getBoundingBox();
        rect.origin = Image_moveBg->getParent()->convertToWorldSpace(rect.origin);
        rect.origin = panel_level->getParent()->convertToNodeSpace(rect.origin);
        panel_level->setPositionY(rect.origin.y);
        panel_level->setOpacity(0);
        panel_level->runAction(FadeIn::create(LEVEL_SHOW_TIME));
    }

    /*if (levelMode && string((*_levelData)["type"].GetString()) == "LimitScore") {
        addEvent("msg_game_scoreani", [this](EventCustom* eventCustom) {
            auto card = static_cast<CardSprite*>(eventCustom->getUserData());
            if (card == nullptr) return;

            auto value = dynamic_cast<__Integer*>(card->getUserObject());
            if (value) {
                card->setUserObject(nullptr);
                int score = value->getValue();
                Node* scoreNode = nullptr;
                scoreNode = UIUtils::createCSBNode("card/Score.csb", score>0?"start0":"start1", false, [scoreNode](){
                    if (scoreNode) scoreNode->removeFromParent();
                });
                scoreNode->getChildByName(score>0?"Node_Addpoints":"Node_Minuspoints")->getChildByName<TextBMFont*>(score>0?"Text_add":"Text_minus")->setString(StringUtils::toString(score));
                panel_game->addChild(scoreNode, 60);
                scoreNode->setPosition(card->getPosition());
//        scoreNode->setPosition(Vec2::ZERO);
            }
        }, true);
    }
    else {
        removeEvent("msg_game_scoreani");
    }*/
    
    _winHD->setVisible(false);
#if HasDaily
    getNode("Panel_daliy")->setVisible(false);
#endif
    _actionManager->play("idle", true);
    //menuMove(false); // 出现吧
}

void GameViewHD::refush()
{
}

void GameViewHD::updateWaitCardNum(int num)
{
    
}

void GameViewHD::updateScore(int delay)
{
    score += delay;
    if (score < 0)
    {
        score = 0;
    }

    
//    gameTimeView->setTime(score);

//    atlasLabel_score->setString(toString(score));
    getNode<TextBMFont*>("BitmapFontLabel_score")->setString(StringUtils::format("%d", score));
    
    if (DATA_M->isLevelMode() && (*_levelData)["type"] == "LimitScore") {
        auto bannerScore = getNode("Node_score")->getChildByName<GameTime*>("BannerScore");
        auto lastScore = MAX(0, (*_levelData)["score"].GetInt()-score);
        if (bannerScore) {
            bannerScore->setTime(score);
        }
        if (lastScore==0) {
            levelComplete(true);
        }
    }
}

void GameViewHD::addMoveNum()
{
    moveNum++;
    getNode<TextBMFont*>("Text_moveNum")->setString(StringUtils::toString(moveNum));
    if (DATA_M->isLevelMode() && ((*_levelData)["type"] == "CollectPoker" || (*_levelData)["type"] == "LimitScore" || (*_levelData)["type"] == "TargetPoker")) {
        if (_levelData->HasMember("moves")) {
            auto laseMoves = (*_levelData)["moves"].GetInt()-moveNum;
            getNode<TextBMFont*>("Text_bannerTargetMoveNum")->setString(StringUtils::toString(laseMoves));
            if (laseMoves<=10)
            {
                //UIUtils::playInnerAction(getNode("FileNode_mode"), "start", true);
            }
            if (laseMoves<=0)
                levelComplete(false);
        }
        else {
            getNode<TextBMFont*>("Text_bannerTargetMoveNum")->setString(StringUtils::toString(moveNum));
        }
    }
}

void GameViewHD::showAutoFinishBtn(bool isShow)
{
    if (TEACH_M->isTeaching() && isShow) {
        return;
    }
    
    isAutoShouPai = isShow;
    if (isShow && DATA_M->isLevelMode()) {
        const auto &type = string((*_levelData)["type"].GetString());
        if (type == "OnePoker" || type == "ThreePoker") {
            levelComplete(true);
        }
        else if(type == "LimitTime")
        {//限时 都翻开之后 手指出现
            //limitTimeHint();//记录多少局限时
            auto num = DATA_M->getLimitTimeNum();
            DATA_M->setLimitTimeNum(num+1);
            if(num >= LIMITTIMENUM)
            {//3局后不再提示
                return;
            }
            isOpenLimitTimeHint = true;
            openLimitTimeHintTime = 9.8f;//0.2后提示
        }
        return;
    }
    
    getNode("Button_auto")->setVisible(isShow);
    auto autoNode = FIND_NODE(Node*, this, "FileNode_auto");
    if (isShow && autoNode->isVisible() != isShow)
    {
        UIUtils::playInnerAction(autoNode, "Start", false);
        for (int i = 1; i <= 3; ++i) {
            auto particle = autoNode->getChildByName<ParticleSystemQuad*>(StringUtils::format("Particle_%d", i));
            if (particle) {
                particle->resetSystem();
            }
        }
        SOUND_M->playEffectMusic(EffectAuto);
    }
    autoNode->setVisible(isShow);
}

bool GameViewHD::onTouchBegan(Touch * touch, Event * e)
{
    Point touchP = touch->getLocation();//触摸点
    _tipsTime = 0;
    openLimitTimeHintTime = 0;
	//检查是否发生提示结束后 仍然没有解除操作限制 并解除提示对操作的限制
	tipsFangCuo();
    if (!isCanTouch || isOver || isShowTips)
    {//新增||isShowTips。提示中禁止按钮操作并且禁止牌操作
        SCENE_M->clickEff(touchP);
        return false;
    }
    
    autoTipsTime = 0;
    touchMoveDelay = 0;
    if (false&&timeDelay == 0) {       // 点一下才会开始(禁用
        isPause = false;
        if(gameBg)
        {
            ShopManager::getInstance()->changeColor(gameBg);//开始后场景变色
        }
    }
    isMoveCard = false;
    
    
    if (selectCard == NULL)
    {
        auto gameTouchP = panel_game->convertToNodeSpace(touchP);
        selectCard = SPRITE_M->getCardSpriteByTouchPos(gameTouchP);
        if (selectCard)
        {
            if (timeDelay == 0) {       // 点一下牌才会开始
                isPause = false;
            }
            auto is = SPRITE_M->isWaitCardEnd(selectCard);
            auto isFanPai = getIsFanPai();
            auto noMove = SPRITE_M->isNoMoveTips(isFanPai);
            if(noMove)
            {//有路可走
                noMoveTipsNum2 = 0;
            }
            if(is&&!noMove&&!isShowTips)
            {
                noMoveTipsNum2++;
                //当进行第二轮翻牌时在提示
                if(noMoveTipsNum2 > 1)
                {
                    noMoveTipsNum2 = 0;
                    noMoveTipsNum++;
                    //打开窗口禁止累计提示计时
                    isShowTips = true;
                    isOpenTipsTime = false;
                    if(!GUIDE_M->isEnd(FishGuideManager::GuideType::NoMove))
                    {
                        auto node = FIND_NODE(Node*, FileNode_2020Menu, "Button_Shuffle");
                        auto rect = node->getBoundingBox();
                        rect.origin = node->getParent()->convertToWorldSpace(rect.origin);
                        auto poi = Vec2(rect.getMidX(),rect.getMidY());
                        auto scale = FileNode_2020Menu->getScale();
                        GUIDE_M->startGuide(FishGuideManager::GuideType::NoMove,this,poi,scale);
                    }
                    SCENE_M->showTips(Lang("100134"),false);
                }
            }
            SPRITE_M->setCardSelected(selectCard, true);
//            selectCard->setSelected(true);
            SPRITE_M->setKCardLocalZOrder(selectCard);
            isCanTouch = false;
        }
        else
        {
            //判断是否刷新
            if (refushSprite->getBoundingBox().containsPoint(gameTouchP) && SPRITE_M->waitShowNoCard())
            {
                //接触了
                isTouchRefush = true;
            }
            else
            {
                SCENE_M->clickEff(touchP);
            }
        }
    }
    return true;
}

void GameViewHD::onTouchMoved(Touch * touch, Event * e)
{
    Point touchP = touch->getLocation();
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    auto delta = touch->getDelta();
    log("移动距离： %f",delta.length());
    if(delta.length() > 200)
    {
        isCeShiWin = true;
        gameOver(true);
    }
#endif


    auto gameTouchP = panel_game->convertToNodeSpace(touchP);
    if (selectCard == NULL)
    {
        if (isTouchRefush && !refushSprite->getBoundingBox().containsPoint(gameTouchP))
        {
            //移开了
            isTouchRefush = false;
        }
        return;
    }

    if (!selectCard->getIsOpen() && !selectCard->getBoundingBox().containsPoint(gameTouchP))
    {
        //结束触摸时是否还是这个位置 是的话就翻牌
        selectCard = NULL;
        return;
    }

    if (selectCard->getIsOpen())
    {
        Point moveDelay = touch->getDelta();
        touchMoveDelay+=moveDelay.distance(Point::ZERO);
        if ((!isMoveCard && touchMoveDelay > MOVE_DELAY) || isMoveCard)
        {
            isMoveCard = true;
            SPRITE_M->setCardSpritePos(selectCard, moveDelay,moveOffsetY);
        }

        //selectCard->setPosition(selectCard->getPosition() + moveDelay);
    }
}

void GameViewHD::onTouchEnded(Touch * touch, Event * e)
{
    autoTipsTime = 0;
    auto cdTime = TOUCH_DELAY_CD;
    if (selectCard)
    {
        auto posId = selectCard->getPosId();
        if (!selectCard->getHasFlop()) {
            selectCard->setHasFlop(true);
            cdTime = 0.0001f;
        }
        else {
            cdTime = (posId==CARD_POS_WAIT||posId==CARD_POS_WAIT_SHOW)?(SPRITE_M->isThreeModel?TOP_TOUCH_DELAY_CD+2*ThreeFlopSpaceTime:TOP_TOUCH_DELAY_CD):cdTime;
        }
        bool flag = false;
        SPRITE_M->setCardSelected(selectCard, false);
//        selectCard->setSelected(false, flag?0:1);

        flag = SPRITE_M->checkCardPos(selectCard, isMoveCard);
        selectCard = NULL;
        isCanTouch = false;
    }
    else
    {
        if (isTouchRefush)
        {
            isTouchRefush = false;
            //等候的牌重置
            SPRITE_M->resetWaitCard();
            cdTime += SPRITE_M->getTotalWaitCardCNT()*WaitCardRestTime+OpenCardTime+extraCDTime;



                   // 重置牌区等待时间
            isCanTouch = false;
        }
    }
    CCLOG("CDTime(%f)", cdTime);
    if (!isCanTouch) {
        this->runAction(Sequence::create(DelayTime::create(cdTime), CallFunc::create([this]{
            isCanTouch = true;
        }), NULL));
    }
}


bool GameViewHD::getIsFanPai()
{
    bool is = true;
    
    
    return is;
}

bool GameViewHD::getIsFanPai2()
{//翻牌前的判断
    bool is = true;
   
    
    return is;
}

bool GameViewHD::vegasFaPaiTips()
{
    bool is = false;
//    //显示禁止图片。
//    if(isThreeModel)
//    {//三张情况下 允许 三轮
//        if(weiJiaSiJiShu < 2)
//        {
//            //等候的牌重置
//            SPRITE_M->resetWaitCard();
//            is = true;
//        }
//        else
//        {//弹出提示窗口
//            SCENE_M->addDialog(WeiJiaSiFaPaiTips::createLayerN());
//        }
//    }
//    else
//    {//单张情况下 允许一轮
//        if(weiJiaSiJiShu < 0)
//        {
//            //等候的牌重置
//            SPRITE_M->resetWaitCard();
//            is = true;
//        }
//        else
//        {//弹出提示窗口
//            SCENE_M->addDialog(WeiJiaSiFaPaiTips::createLayerN());
//        }
//    }
//    weiJiaSiJiShu++;
    return is;
}

void GameViewHD::showTips()
{
    if (TEACH_M->isTeaching()) return;
    
    SPRITE_M->cancleTips();
    float tipsActionTime = SPRITE_M->getTips();
    //用户没有操作 超过时间自动提示
    _tipsTime-=tipsActionTime;
    ++_tipsCNT;
    if (tipsActionTime > 0 && !isShowTips)
    {
        isShowTips = true;
        isCanTouch = false;
        this->stopActionByTag(10010110);
        auto action = Sequence::create(DelayTime::create(tipsActionTime), CallFunc::create([this]{
            isShowTips = false;
            isCanTouch = true;
        }), NULL);
        this->runAction(action);
        action->setTag(10010110);
    }
    else if(tipsActionTime == 0&&!isShowTips&&!GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::NoMove))
    {//没有有效移动
        //打开窗口禁止累计提示计时
        isShowTips = true;
        isOpenTipsTime = false;
        SCENE_M->showTips(Lang("100134"),false);
        noMoveTipsNum++;
        //在前5局并且有魔法棒并且第二次点击点击提示 提示nomove 就播hint
        auto num = ScoreManager::getInstance()->getWinTotalCNT(false);
        auto magicNum = RewardManager::getInstance()->getCNT(RewardManager::RewardType::Magic);
        
        if(!GUIDE_M->isEnd(FishGuideManager::GuideType::NoMove))
        {
            auto node = FIND_NODE(Node*, FileNode_2020Menu, "Button_Shuffle");
            auto rect = node->getBoundingBox();
            rect.origin = node->getParent()->convertToWorldSpace(rect.origin);
            auto poi = Vec2(rect.getMidX(),rect.getMidY());
            auto scale = FileNode_2020Menu->getScale();
            GUIDE_M->startGuide(FishGuideManager::GuideType::NoMove,this,poi,scale);
        }
        else if(num <= 4&&magicNum > 0&&noMoveTipsNum == 2)
        {
            UIUtils::playInnerAction(FileNode_2020Menu,"hint",false,[this](){
                    
            });
            
        }
        //SCENE_M->addDialog(NoMoveView::createLayerN());
    }
}

void GameViewHD::onTouchCancelled(Touch * t, Event * e) {
    isCanTouch = true;
}

void GameViewHD::dealButtonClick(Ref * pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    
    //有点击操作归零
    _tipsTime = 0;
    openLimitTimeHintTime = 0;
    if (btn == nullptr) {
        return;
    }
    autoTipsTime = 0;
//    UIUtils::testCrashlytics();       // 崩溃
    auto btnName = btn->getName();
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    if(btnName == "Button_effff")
    {
        auto is = SPRITE_M->getIsOpenEffective();
        SPRITE_M->setIsOpenEffective(!is);
        ceshi();
        SPRITE_M->pokerEndAni6();
        _winHD->show(nullptr);
    }
    else if(btnName == "Button_effff_0")
    {
        SPRITE_M->endAniFuWei();
    }
    else if(btnName == "Button_winceshi")//||btnName == "Button_reduction"
    {//游戏胜利
        isCeShiWin = true;
        gameOver(true);
    }
#endif
	//检查是否发生提示结束后 仍然没有解除操作限制 并解除提示对操作的限制
	tipsFangCuo();
    if(isShowTips)return;//提示中禁止按钮操作并且禁止牌操作
    ValueMap valueMap; // 上报参数
    if (btnName == "Button_game") {
//        _actionManager->play("idle", true);
        //打开窗口禁止累计提示计时
        isOpenTipsTime = false;
#if TestAutoPlay
        _bureauData = BureauTestManager::getInstance()->getBureauData(0/*>步数*/, 1000/*概率=n/1000*/);
//        _bureauData = BureauTestManager::getInstance()->getBureauData("1NaT`[A_I\\7<VcEM@bHC>0JXZFQ3Y;P=U?RG5]SW:K8^LDO2B694");
        DATA_M->setGameType(DataManager::GameType::Daily);
        resetGame(_bureauData["data"].asString());
#else
        SCENE_M->addDialog(GameViewResetHD::createLayerN(this));
#endif
    }
    
    if (!isCanTouch||isOver) return;   // 还在 cd中
    if (btnName == "Button_pause") {
        setButtonPauseEnabled(false);
#if TestAutoPlay
        SPRITE_M->autoPlay(_bureauData["move_steps"].asString());
#else
        auto gamePause = SCENE_M->getGamePause();
        if(!gamePause)
        {
            if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::Three)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::Three))
            {
                GUIDE_M->endGuide();
            }
            else if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::unlockFashTank)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::unlockFashTank,0))
            {
                GUIDE_M->endGuide(FishGuideManager::GuideType::None,NULL,0);
            }
            SOUND_M->playEffectMusic(EffectButtonStart);
            //按钮变化
            menuPausePlayAni("Start0",false);
            SCENE_M->addDialog(GamePauseHD::createLayerN(this), false);
        }
       
#endif
        UIUtils::FIRAnalyticsEvent("event_game_pause", valueMap);
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
//        SCENE_M->addLayer(MainLobby::createLayer());
//        gameOver(true);

//        if (_levelData)//没有此键报错
//            SPRITE_M->autoPlay((*_levelData)["autoData"].GetString());
//        _winHD->setVisible(true);
//        _winHD->show(nullptr);
#endif
    }
    else if(btnName == "Button_beibao")
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
        UIUtils::playInnerAction(FileNode_MyBag,"Start",false);
        SCENE_M->addDialog(BagView::createLayerN(BagView::BagType::CARD));
        gamePause(true);//窗口打开暂停游戏
    }
    else if(btnName == "Button_fish")
    {//返回大厅
        auto lobby = SCENE_M->getLobby();
        if(lobby)
        {
            //暂停音效
            //SOUND_M->pauseDTEffect();
            hideLunPan();
            showLobby();
            gamePause(true);
            setIsRefushGift(false);//返回大厅禁止刷新奖励
        }
        SOUND_M->playBtnClickAudio();
        menuPausePlayAni("Start1",false);
    }
    else if (btnName == "Button_auto") {
        if (btn->getScaleX()>=0.9)
        {
            isAuto = true;
            hideLunPan();//隐藏奖励
            isAutoShouPai = false;
            isCanTouch = false;
            //游戏即将结束禁止累计提示计时
            isOpenTipsTime = false;
            showAutoFinishBtn(false);
            _winEffectID = SOUND_M->playEffectMusic(EffectAutoplay);
        }
        SPRITE_M->autoFinshGame();
    }
    else if (btnName == "Button_setting") {
        SOUND_M->playEffectMusic(EffectButtonStart);
        SCENE_M->addDialog(SettingViewHD::createLayerN(SettingViewHD::ViewType::Game));
        gamePause(true);//窗口打开暂停游戏
        SCENE_M->getLobby()->updateNewVersion(false);
    }
    else if (btnName == "btn_gift_lingqu") {
        //直接给金币
        DATA_M->playVideoAds(13);
        gamePause(true);//窗口打开暂停游戏
    }
    else if(btnName == "Button_lunPan"||btnName == "Panel_lunPan")
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
        lunPanShowNum = 0;
        FileNode_lunPan->setVisible(false);
        SCENE_M->addDialog(RewardRouletteView::createLayerN(RewardRouletteView::Type::Game));
        
        gamePause(true);//窗口打开暂停游戏
    }
    else if(btnName == "Button_fanPai")
    {//翻牌
        SOUND_M->playEffectMusic(EffectButtonStart);
        fanPaiShowNum = 0;
        SCENE_M->addDialog(FanPaiAD::createLayerN(FanPaiAD::Type::Game));
        Button_fanPai->setVisible(false);
        gamePause(true);//窗口打开暂停游戏
    }
    else if (btnName == "Button_again" || btnName == "Button_liveReplay") {
        if (DATA_M->isLevelMode() && _levelData)
        levelCompleteEnd(false, true);
        restartGame(true);
        valueMap["Button"] = "Button_liveReplay";
        UIUtils::FIRAnalyticsEvent("event_newGame_replay", valueMap);
    }
    else if (btnName == "Button_reliveClose") {
        agianGame();
    }
    else if (btnName == "Button_relive") {
        DATA_M->playVideoAds(4);
        btn->setEnabled(DATA_M->getHaveVideo());
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("LevelRelive")},
            {"value", Value("ad")}
        });
    }
    else if (btnName == "Button_teach") {
        SOUND_M->playEffectMusic(EffectButtonStart);
        startTeachBureau();
        UIUtils::FIRAnalyticsEventWithPrefix("startTeachBureau", "teach");
    }
    else if(btnName == "Button_rank")
    {//排行
        SCENE_M->addDialog(RankView::createLayerN(RankView::RankType::GameView));
        gamePause(true);//窗口打开暂停游戏
    }
    else if(btnName == "Button_Level")
    {//升级窗口
        //SCENE_M->addDialog(FashTankShop::createLayerN());
        gamePause(true);//窗口打开暂停游戏
        LevelUpView->setVisible(true);
        LevelUpView->updateUI();
        LevelUpView->playAni("Start0",false,[this](){
            LevelUpView->playAni("out0",false);
        });
        UIUtils::FIRFirestoreAddOP("");
    }
    else if(btnName == "btn_challenge")
    {//
        SCENE_M->addDialog(ChallengeModeView::createLayerN(ChallengeModeView::Type::Game));
        gamePause(true);//窗口打开暂停游戏
    }
    else if (!isOver)
    {
        if (btnName == "Button_tips") {
            SOUND_M->playEffectMusic(EffectButtonStart);
            showTips();
            if (!TEACH_M->isDailyLevelUnlock()) {
                UIUtils::FIRFirestoreAdd("operator", {
                    {"key", Value("click")},
                    {"value", Value("tips")}
                });
            }
//            isCeShiWin = true;
//            gameOver(true);
        }
        else if (btnName == "Button_Shuffle") {
            SOUND_M->playEffectMusic(EffectButtonStart);
            if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::NoMove)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::NoMove))
            {
                GUIDE_M->endGuide();
            }
            useMagic();
        }
        else if (btnName == "Button_reduction") {
            SOUND_M->playEffectMusic(EffectButtonStart);
            auto moveType = SPRITE_M->backMove();
            if (moveType != MType_None)
            {
                ++_useBackCNT;
                isUseBack = true;
                SOUND_M->playEffectMusic(EffectUndo);
                auto cdTime = TOUCH_DELAY_CD;
                if (moveType == MType_Reset) {
                    cdTime += SPRITE_M->getTotalWaitCardCNT()*WaitCardRestTime+OpenCardTime+extraCDTime;        // 重置牌区等待时间
                }
                CCLOG("CDTime(%f)", cdTime);
                isCanTouch = false;
                this->runAction(Sequence::create(DelayTime::create(cdTime), CallFunc::create([this]{
                    isCanTouch = true;
                }), NULL));
            }
        }
        if (isFirstBureau()) {
            UIUtils::FIRFirestoreAddOP("game_click", btnName);
        }
    }
    
    if (btnName == "Button_liveReplay" || btnName == "Button_reliveClose") {
        //getNode("FileNode_relive")->setVisible(false);
        if (btnName == "Button_reliveClose") {
            levelCompleteEnd(false);
        }
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("LevelRelive")},
            {"value", Value("no")},
            {"v1", Value(DATA_M->getHaveVideo())}
        });
    }
}

void GameViewHD::onFaild(int level)
{
    ValueMap bureauParams {
        {"bu", Value(SPRITE_M->getCurrentBureau())},
        {"win", Value(false)},
        {"bt", Value((int)DATA_M->getGameType())},
        {"pt", Value(SPRITE_M->isThreeModel ? 3 : 1)},
        {"playtime", Value((int)timeDelay)},
        {"moves", Value(moveNum)},
        {"score", Value(score)},
        {"backmoves", Value(useBackCNT)},
        {"star", Value(0)},
        {"tips", Value(_tipsCNT)},
        {"noTips", Value(noMoveTipsNum)},
        {"level", Value(level)},
        {"shuffle", Value(_magicCNT)},

        {"daily", Value(DailyManager::getInstance()->getCurrentDate().name())},
        {"hard", Value(DailyManager::getInstance()->getCurrentMode())},
        {"openEffe", Value(SPRITE_M->getIsOpenEffective())},//是否开启辅助 2.步数限定
        {"openEffeNum", Value(SPRITE_M->getFanPaiNum())},
    };
    UIUtils::FIRFirestoreAdd("bureau", bureauParams);
//    sendFirstBureauEvent(moveNum, moveNum - noMoveTipsNum, noMoveTipsNum);
    UIUtils::FIRAnalyticsEvent("game_bureau_faild", bureauParams);
}

//倒计时
void GameViewHD::updateTime(float dt)
{
    //观看广告时不累计 自动收取按钮弹出 不累计
    if(!DATA_M->getPlayAds()&&isOpenTipsTime&&!isAutoShouPai)
    {
        _tipsTime+=dt;
    }
    else if(DATA_M->getPlayAds())
    {
        _tipsTime = 0;
        openLimitTimeHintTime = 0;
    }
    if(!DATA_M->getIsAutoTips())
    {
        _tipsTime = 0;
        openLimitTimeHintTime = 0;
    }
    
    if(!TEACH_M->isTeaching()&&_tipsTime > 12&&DATA_M->getIsAutoTips())
    {
        _tipsTime = 0;
        showTips();
    }
    timeDelay += dt;
//    gameTimeView->setTime(timeDelay);
    int fen = (int)(timeDelay / 60);
    int miao = (int)((int)timeDelay % 60);
    getNode<TextBMFont*>("Text_new_time")->setString(StringUtils::format("%02d:%02d", fen, miao));

    if (DATA_M->isLevelMode() && (*_levelData)["type"] == "LimitTime") {
        auto limitTime = (*_levelData)["times"].GetInt();
        limitTime = (float)limitTime*2.5f;
        limitTime = limitTime - limitTime%10;
        if (timeDelay>=limitTime) {
            levelComplete(false);
        }
        auto bannerTime = getNode("Node_bannerTime")->getChildByName<GameTime*>("BannerTime");
        if (bannerTime) {
            bannerTime->setTime(MAX(0, int(limitTime-timeDelay)));
        }
    }
}

void GameViewHD::update(float delta) {
    //游戏期间 判断是否是第二天了
    if (isPause || isOver) // || VungleManager::isAdPlaying)
    {
        //有点击操作归零 或暂停或结束 重置
        _tipsTime = 0;
        openLimitTimeHintTime = 0;
        return;
    }
    
    autoTipsTime += delta;
    if (autoTipsTime>AutoTipsWaitTime&&0) {
        autoTipsTime = 0;
        showTips();
    }
    
    updateTime(delta);
    updateLimitTimeHintTime(delta);
}

void GameViewHD::updateLimitTimeHintTime(float dt)
{
    //3局提示后不再进行提示；
    if(!isOpenLimitTimeHint||LimitTimeHintLayer->isVisible())
    {
        openLimitTimeHintTime = 0;
        return;
    }
    openLimitTimeHintTime+=dt;
    if(openLimitTimeHintTime > 10)
    {
        _tipsTime = 0;
        openLimitTimeHintTime = 0;
        limitTimeHint();
    }
    
}

void GameViewHD::changePos() {
    auto panel_times = getNode("Panel_times");
    auto parentSize = panel_times->getParent()->getContentSize();
    //panel_times->setPositionX(abs(panel_times->getPositionX()-parentSize.width));
    //auto button_pause = getNode("Button_pause");
    //button_pause->setPositionX(abs(button_pause->getPositionX()-parentSize.width));
//    auto Button_beibao = getNode("Button_beibao");
//    Button_beibao->setPositionX(abs(Button_beibao->getPositionX()-parentSize.width));
//    auto Node_bannerScore = getNode("Node_bannerScore");
//    Node_bannerScore->setPositionX(abs(Node_bannerScore->getPositionX()-parentSize.width));
    
    auto node_bg = getNode("Node_bg");
    for (auto child:node_bg->getChildren()) {
        child->setPositionX(-child->getPositionX());
    }
//    auto panel_bottom = getNode("Panel_bottom");
//    for (auto child:panel_bottom->getChildren()) {
//        child->setPositionX(abs(child->getPositionX()-parentSize.width));
//    }
}

void GameViewHD::showInterstitialDelay()
{
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([this] {
        showInterstitial();
    });
}

bool GameViewHD::showInterstitial()
{
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    if (NO_AD) {
        return false;
    }
#endif
    //是否允许插屏
    auto isPlayAds = DATA_M->getLimit();
    auto faildNum = ScoreManager::getInstance()->getScore(!DATA_M->getIsThreeModel()?1:0, ScoreManager::Type::FAILDNINGSNT);
    //失败第一次不给插屏
    bool isFaild = faildNum != 0;
    return isPlayAds && isFaild && DATA_M->showNativeAds(2, "GameViewHD");
}

void GameViewHD::restartGame(bool isReplay, DataManager::GameType gameType, bool noAds)
{
    if (_winEffectID) {
        SOUND_M->stopEffectMusic(_winEffectID);
        _winEffectID = 0;
    }
    
    if (gameType != DataManager::GameType::None) {
        DATA_M->setGameType(gameType);
    }
    else {
        gameType = DATA_M->getGameType();
    }
    
    if (isReplay) {
        isPause = true;
        
        int level = dailyType;
        if (DATA_M->getGameType() == DataManager::GameType::Level) {
            startLevelRank(_levelData);
            level = (*_levelData)["subShow"].GetInt();
        }
        else {
            if(timeDelay != 0)
            {
                //所有对局重开次数累计，不清零
                DATA_M->addchongKaiNum();
                //同一局重开累计次数，有新开就清零
                DATA_M->addSameChongKaiNum();
            }
            
            auto cb = [this](){
                _levelData = nullptr;
                gameOver(false);
                resetGameData();
                //重玩本局
                SPRITE_M->replayGame();
                //刷新banner显示
                DATA_M->setBannerVisible(true);
            };
            onFaild(level);  //重开失败
//            if (gameType == DataManager::GameType::Daily && !noAds) showInterstitial();
            //没有开始对局 不给插屏
            //单局重开次数第一次不给插屏
            //全部重开次数大于15次给插屏
            auto isDaily = timeDelay == 0||DATA_M->getSameChongKaiNum() < 2;
            if(isDaily)
            {//第一轮判读没插屏 判断全部重开次数大于15次没
                isDaily = DATA_M->getchongKaiNum() <= 15;
            }
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            if (!isDaily&&!noAds && showInterstitial()) {
                //暂停背景音乐
                //SoundManager::getInstance()->pauseGameBgMusic();
                DATA_M->addchongKaiNum(true);
                AdsManager::waitWinAction = true;
                InterstitialCB = cb;
            }
            else
            {
                cb();
            }
#else
            if (!isDaily&&!noAds) showInterstitial();
            cb();
#endif
        }
        
    }
    else {
        //同一局重开累计次数，有新开就清零
        DATA_M->addSameChongKaiNum(true);
        isPause = true;
        auto cb = [this](){
            if (!isOver && timeDelay>0) { // 记录失败局数
                DATA_M->settlementGameOnFail(SPRITE_M->isThreeModel ? 2 : 1, (int)timeDelay, score);
                auto num = ScoreManager::getInstance()->getWinTotalCNT(false);
                if(num >= 4&&DATA_M->getIsChallengeOpen())
                {
                    DATA_M->setIsChallenge(true);
                }
                int level = dailyType;
                if (DATA_M->isLevelMode())
                {
                    level = (*_levelData)["subShow"].GetInt();
                }
                onFaild(level); // 新牌局失败
            }
            //刷新banner显示
            DATA_M->setBannerVisible(true);
            resetGame();
        };
        
        //是挑战模式&&没有开始对局 不给插屏
        auto isDaily = DATA_M->getGameType() == DataManager::GameType::Daily&&timeDelay == 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if (!isDaily&&!noAds && showInterstitial()) {
            //暂停背景音乐
            //SoundManager::getInstance()->pauseGameBgMusic();
            AdsManager::waitWinAction = true;
            InterstitialCB = cb;
        }
        else
        {
            cb();
        }
#else
        if (!isDaily&&!noAds) showInterstitial();
        cb();
#endif
    }
    string eventName{(isReplay?"gameReStart_":"gameStart_") + toString(int(DATA_M->getGameType()))};
    if (!TEACH_M->isDailyLevelUnlock()) {
        UIUtils::FIRAnalyticsEventWithPrefix(eventName + "_" + TEACH_M->getCurrentTeachKey(), "teach");
    }
    else
        UIUtils::FIRAnalyticsEventWithPrefix(eventName);


    if (_isGameStart) { // 新游戏了 应该调用游戏结束
        sendEndGameEvent(gameType, isReplay?"2":"1");
    }

    sendStartGameEvent(gameType);
}

const vector<string> TaskNode {"Node_LimitScore", "Node_CollectPoker", "Node_TargetPoker", "Node_LimitTime"};
// 开启关卡模式 保存leveldata的json 处理数据 初始化UI
void GameViewHD::startLevelRank(std::shared_ptr<rapidjson::Document> levelData, bool noAds) {
    bool needShowAd = false;
    if (_levelData != levelData) {
        needShowAd = true && !noAds;
        _levelData = levelData;
    }
    
    DATA_M->setGameType(DataManager::GameType::Level);
    isPause = true;//提前暂停游戏
    auto cb = [this, levelData](){
//        DataManager::getInstance()->setIsThreeModel(string("One") != (*levelData)["pokerMode"].GetString());
        SPRITE_M->isThreeModel = (string("One") != (*levelData)["pokerMode"].GetString());
        auto taskStr = LevelManager::getInstance()->getShowString(levelData);
        getNode<Text*>("Text_levelContent")->setString(taskStr);
        getNode<Text*>("Text_taskTips")->setString(taskStr);
        //getNode("FileNode_task")->setVisible(true);
        //UIUtils::playInnerAction(getNode("FileNode_task"), "start", false);         // 关卡开始动画 提示当前任务
        //UIUtils::playInnerAction(getNode("FileNode_mode"), "idle", false);          // 重置 提示心跳

        auto Node_bannerScore = getNode("Node_bannerScore");
        Node_bannerScore->setVisible(false);
        auto Text_bannerTargetMoveNum = getNode<TextBMFont*>("Text_bannerTargetMoveNum");
        const auto &type = string((*levelData)["type"].GetString());                // 获取关卡类型
        if (type == "LimitScore" || type == "CollectPoker" || type == "LimitTime" || type == "TargetPoker") {
            getNode("Image_banner")->setVisible(true);
            for (auto &key:TaskNode) {
                getNode(key)->setVisible(key.find(type) != string::npos);
            }
            if (type == "LimitScore") {
                auto Node_score = getNode("Node_score");
                auto levelComplete = Node_score->getChildByName("LevelComplete");
                if (levelComplete)
                    levelComplete->setVisible(false);
                if (!Node_score->getChildByName("BannerScore")) {
                    auto bannerScore = GameTime::createLayerN();
                    Node_score->addChild(bannerScore);
                    bannerScore->setName("BannerScore");
                    bannerScore->setTime((*levelData)["score"].GetInt());
                }
            }
            else if (type == "CollectPoker") {
    //            auto Node_CollectPoker = getNode("Node_CollectPoker");
                _levelPoker.clear();
                const auto &array = (*levelData)["poker"].GetArray();
                completeCNT = array.Size();
                for (int i=0;i<4;i++) {
    //            for (auto &str:array) {
                    string str;
                    auto cardIdx = i+1;
                    if (i<completeCNT) {
                        str = array[i].GetString();
                        _levelPoker[str] = cardIdx;
                    }
                    auto cardSP = getNode<Sprite*>(StringUtils::format("Sprite_card%d", cardIdx));
                    if (cardSP) {
                        cardSP->setVisible(!str.empty());
                        if (!str.empty()) {
                            if (type == "CollectPoker") {
                                cardSP->setSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(str));
                            }
                            else {
                                cardSP->setSpriteFrame(SPRITE_M->getSpecialCardSpriteFrame(str));
                            }
                        }
                        if (cardSP->getChildByName("LevelComplete"))
                            cardSP->removeChildByName("LevelComplete");
                    }
                    auto cardLB = getNode<TextBMFont*>(StringUtils::format("Text_card%d", cardIdx));
                    if (cardLB) {
                        cardLB->setVisible(false);
                    }
                }
            }
            else if (type == "TargetPoker") {
                //            auto Node_CollectPoker = getNode("Node_CollectPoker");
                _specialPoker.clear();
                const auto &array = (*levelData)["poker"].GetArray();
                for (auto &str:array) {
                    string newStr{str.GetString()};
                    _specialPoker[newStr] = 1;
                }
                auto cardSP = getNode<Sprite*>("Sprite_cardTarget1");
                cardSP->setSpriteFrame(SPRITE_M->getSpecialCardSpriteFrame(""));
                if (cardSP->getChildByName("LevelComplete"))
                    cardSP->removeChildByName("LevelComplete");
                getNode<TextBMFont*>("Text_cardTarget1")->setString(StringUtils::toString(_specialPoker.size()));
            }
            else if (type == "LimitTime") {
                auto Node_bannerTime = getNode("Node_bannerTime");
                auto levelComplete = Node_bannerTime->getChildByName("LevelComplete");
                if (levelComplete)
                    levelComplete->setVisible(false);
                if (!Node_bannerTime->getChildByName("BannerTime")) {
                    auto bannerTime = GameTime::createLayerN();
                    Node_bannerTime->addChild(bannerTime);
                    bannerTime->setName("BannerTime");
                    bannerTime->setTime((*_levelData)["times"].GetInt());
                }
            }
            
            if (_levelData->HasMember("moves")) { // 限制步数
                Text_bannerTargetMoveNum->setString(StringUtils::toString((*_levelData)["moves"].GetInt()));
                Node_bannerScore->setVisible(true);
            }
        }
        else {
            getNode("Image_banner")->setVisible(false);
        }

        resetGame((*levelData)["bureau"].GetString());
        
        ValueMap valueMap;
        valueMap["level"] = Value(StringUtils::format("group%d_level%d", (*_levelData)["group"].GetInt(), (*_levelData)["sub"].GetInt()));
        UIUtils::FIRAnalyticsEvent("event_gameview_startlevel", valueMap);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("LevelStart")},
            {"value", Value((*_levelData)["subShow"].GetInt())}
        }); // 记录关卡开始
    };
    cb();
    //取消开始插屏 改在结算出现插屏
    return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (needShowAd && showInterstitial()) {
        //暂停背景音乐
        //SoundManager::getInstance()->pauseGameBgMusic();
        AdsManager::waitWinAction = true;
        InterstitialCB = cb;
    }
    else
    {
        cb();
    }
#else
    showInterstitial();
    cb();
#endif
}

void GameViewHD::collectACard(int number, int colorType) {
    if (DATA_M->isLevelMode() && ((*_levelData)["type"] == "CollectPoker")) {
        auto str = StringUtils::format("%d_%d", number, colorType);
        auto it = _levelPoker.find(str);
        if (it != _levelPoker.end()) {      // 收集了卡背飞天动画
            auto cardSP = getNode(StringUtils::format("Sprite_card%d", it->second));
            if (cardSP) {
                auto node = UIUtils::createCSBNode("Animation/collectCard.csb", "show");
                node->setName("LevelComplete");
                node->setPosition(cardSP->getContentSize()/2);
                cardSP->addChild(node);
            }
            _levelPoker.erase(it);
        }
            
        if (_levelPoker.size() == 0) {
            levelComplete(true);
        }
    }
}

void GameViewHD::collectSpecialCard(int pos) {
    if (DATA_M->isLevelMode() && ((*_levelData)["type"] == "TargetPoker")) {
        auto vec2 = SPRITE_M->getXYByPos(pos);
        auto str = StringUtils::format("%d_%d", (int)vec2.x, (int)vec2.y);
        auto it = _specialPoker.find(str);
        if (it != _specialPoker.end()) {
            _specialPoker.erase(it);
            auto startPos = SPRITE_M->getKCardPosByIndex((int)vec2.x, (int)vec2.y);
            auto cardMove = UIUtils::createCSBNode("card/move.csb", "start0", false);
            cardMove->setPosition(startPos);
            panel_game->addChild(cardMove, 53);
            auto destPos = panel_game->convertToNodeSpace(getNode("Node_Target1")->convertToWorldSpaceAR(Vec2::ZERO));
            auto lastPokerSize = _specialPoker.size();
            cardMove->runAction(Sequence::create(MoveTo::create(0.7, destPos), CallFunc::create([this, lastPokerSize]() {
                getNode<TextBMFont*>("Text_cardTarget1")->setString(StringUtils::toString(lastPokerSize));
                if (lastPokerSize == 0 ) {
                    auto cardSP = getNode("Sprite_cardTarget1");
                    if (cardSP) {
                        auto node = UIUtils::createCSBNode("Animation/collectCard.csb", "show");
                        node->setName("LevelComplete");
                        node->setPosition(cardSP->getContentSize()/2);
                        cardSP->addChild(node);
                    }
                }
            }), RemoveSelf::create(), nullptr));
        }

        if (_specialPoker.size() == 0) {
            levelComplete(true);
        }
    }
}

// 任务完成
void GameViewHD::levelComplete(bool isWin) {
    unschedule(AutoFinishKey);
    if (isOver)
    {
        return;
    }
    
    //setGameOverState();//有错误
        
    if (isWin) {
        sendEndGameEvent(DataManager::GameType::Level, "4");
        auto isComplete = LevelManager::getInstance()->isLevelComplete(_levelData);
        bool isFirst = LevelManager::getInstance()->setLevelComplete(_levelData, getStar());  // 比正常关卡-1
        const auto &type = string((*_levelData)["type"].GetString());
        Node *rootNode = nullptr;
        if (type == "LimitScore") {
            rootNode = getNode("Node_score");
        }
        else if (type == "LimitTime") {
            rootNode = getNode("Node_bannerTime");
        }
        if (rootNode) {
            auto levelComplete = rootNode->getChildByName("LevelComplete");
            if (!levelComplete) {
                auto node = UIUtils::createCSBNode("Animation/limitTime.csb", "show");
                node->setName("LevelComplete");
                rootNode->addChild(node);
            }
            else {
                levelComplete->setVisible(true);
                auto anctionManager = dynamic_cast<cocostudio::timeline::ActionTimeline *>(levelComplete->getActionByTag(10086));
                if (anctionManager && !anctionManager->isPlaying()) {
                    anctionManager->play("show", false);
                }
            }
        }
        //累积星星
        if(isFirst)
        {
            DATA_M->setStarBoxNum(1);
        }
        //累计完成关卡任务数 新手
        //TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::LEVEL);
        
        SOUND_M->playEffectMusic(EffectAuto);
        scheduleOnce([this, isWin, isFirst,isComplete](float) {
//            SCENE_M->addDialog(WinLayerLevelHD::createLayerN(isWin, _levelData, isFirst, getStar()));
            //弹出结算前
            playAni("top1",false);
            menuMove(true);
            auto extraScore = int(NBSCORE/timeDelay);
            //隐藏信封与轮盘
            panel_gift->setVisible(false);
            FileNode_lunPan->setVisible(false);
            //加入结算提示
            SPRITE_M->levelAutoShouPai([this,extraScore,isFirst,isWin,isComplete](){
                //隐藏场景内容
                //panel_game->setVisible(false);
                SCENE_M->removeLayerByName("BagView"); // 关闭背包
                SCENE_M->removeLayerByName("FreeCoinLayer"); // 关闭金币页面
                SPRITE_M->clearAllData();
                auto exp = 100;//(score+extraScore) / 100;
                _winExp = exp;
                
                winCB = [this,isWin,isFirst](){
                    auto cb = [this,isWin,isFirst](){
                        _gameRewardsView->setVisible(false);
                        
//                        _gameWinLayerLevel->setVisible(true);       // ccs actionmanager 容易引起崩溃
//                        _gameWinLayerLevel->showAction(isWin, _levelData, isFirst, getStar());
                    };
                    
//                    if (showInterstitial()) {
//                        //暂停背景音乐
//                        SoundManager::getInstance()->pauseGameBgMusic();
//                        AdsManager::waitWinAction = true;
//                        InterstitialCB = cb;
//                    }
//                    else
//                    {
                        cb();
                    //}
                };
                
                //获得经验
                auto player = PlayerManager::getInstance();
                Text_MenuLv->setString(StringUtils::format("%d",player->getLevel()));
                Text_lv->setString(StringUtils::format("%d",player->getLevel()));
                auto percent22 = player->getPercent();
                loadingBar_percent->setPercent(percent22);
                loadingBar_menu_percent->setPercent(percent22);
                if(DATA_M->isLevelMode())
                {
                    
                    if(!isComplete)
                    {
                        player->addExp(exp);
                    }
                    else
                    {
                        exp = 5;
                        player->addExp(exp);
                    }
                }
                _extraScore = 0;
                //经验条
                lv = player->getLevel();
                oldLv = player->getOldLevel();
                percent1 = player->getPercent();
                percent2 = player->getPercent(true);
                _gameRewardsView->setVisible(true);
                
                //升级时由升级动画控制是否显示结算窗口
                _gameRewardsView->updateUI(0,exp,winCB);//是否显示 显示什么
                _gameRewardsView->setScore(isThreeModel?0:1, true, 0);//更新数据  关卡分数不准，不记录分数
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
                //playAni("top0",false);
//                //创建5个经验节点 飞上去 经验条增长，增长完毕弹出结算
//                auto poi = getLevelWorldPoi();
//
//                std::vector<Vec2> itemVec1;
//                int expNum = exp==5?5:exp*0.7;
//                DATA_M->randVec(expNum,&itemVec1,320);
                
//                REWARD_M->rewardItemAction(expNum,poi,this->getContentSize()*0.5,itemVec1,[this](){
//
//                    if(lv == oldLv)
//                    {
//                        maxPercent = percent1 - percent2;
//                    }
//                    else
//                    {
//                        auto a = (lv-oldLv)*100 - percent2;
//                        auto b = percent1;
//                        maxPercent = a + b;
//                    }
//                    //速度
//                    //0.5s完成 s
//                    percentDx = maxPercent/0.5;//m/s
//                    percentDx *= 0.017;
//                    isBar = true;
//                },"Exp",this,[this](){
//                    auto FileNode_level = getNode("FileNode_level");
//                    FileNode_level->setVisible(true);
//                    auto LevelBG_1 = getNode("LevelBG_1");
//                    LevelBG_1->setVisible(false);
//                    UIUtils::playInnerAction(FileNode_level,"Exp",false);
//                },[this](){
//                    auto FileNode_level = getNode("FileNode_level");
//                    FileNode_level->setVisible(false);
//                    auto LevelBG_1 = getNode("LevelBG_1");
//                    LevelBG_1->setVisible(true);
//                });
            });
            
            
        }, 1.5, "schedule_windelay");
        SCENE_M->showTips(Lang(isWin?"100090":"100091"));
//        setGameOverState();
        levelCompleteEnd(true);
    }
    else if (_reliveCNT<2/* && DATA_M->getHaveVideo()*/){
        gamePause(true);
        getNode<Button*>("Button_relive")->setEnabled(DATA_M->getHaveVideo());
//        auto node = getNode("FileNode_relive");
//        node->setVisible(true);
        const auto &type = string((*_levelData)["type"].GetString());
        string title, tips, addCount;
        if (type == "LimitTime") {
            title = Lang("100092");
            tips = Lang("100093");
            addCount = toString(LevelAddTime);
        }
        else if (type == "LimitScore" || type == "TargetPoker" || type == "CollectPoker") {
            title = Lang("100094");
            tips = Lang("100095");
            addCount = toString(LevelAddMove);
        }
        getNode<Text*>("Text_title")->setString(title);
        getNode<Text*>("Text_tips")->setString(tips);
        getNode<TextBMFont*>("Text_addCNT")->setString(StringUtils::format("+%s", addCount.c_str()));
//        UIUtils::playInnerAction(node, "start", false);
    }
    else {
        sendEndGameEvent(DataManager::GameType::Level, "3");
        levelCompleteEnd(false);
    }
}

void GameViewHD::levelCompleteEnd(bool isWin, bool noShow)
{
    setGameOverState();
    if (!noShow)
    {
        SCENE_M->showTips(Lang(isWin?"100090":"100091"));
        if (!isWin)
        {
            //挑战失败跳回关卡界面
            showLobby();
            SCENE_M->showLevelComplete(isWin, _levelData);
        }
    }
    
    ValueMap valueMap;
    valueMap["level"] = Value(StringUtils::format("group%d_level%d", (*_levelData)["group"].GetInt(), (*_levelData)["sub"].GetInt()));
    valueMap["win"] = Value(isWin);
    UIUtils::FIRAnalyticsEvent("event_gameview_endlevel", valueMap);
    UIUtils::FIRFirestoreAdd("bureau", {
        {"bu", Value(SPRITE_M->getCurrentBureau())},
        {"win", Value(isWin)},
        {"bt", Value((int)DATA_M->getGameType())},
        {"pt", Value(SPRITE_M->isThreeModel ? 3 : 1)},
        {"playtime", Value((int)timeDelay)},
        {"moves", Value(moveNum)},
        {"score", Value(score)},
        {"backmoves", Value(useBackCNT)},
        {"star", Value(getStar())},
        {"tips", Value(_tipsCNT)},
        {"noTips", Value(noMoveTipsNum)},
        {"level", Value((*_levelData)["subShow"].GetInt())},
        {"relive", Value(_reliveCNT)},
        {"shuffle", Value(_magicCNT)},
        {"openEffe", Value(SPRITE_M->getIsOpenEffective())},//是否开启辅助 2.步数限定
        {"openEffeNum", Value(SPRITE_M->getFanPaiNum())},
    });
}

bool GameViewHD::isLevelCard(int number, int colorType) {
    if (DATA_M->isLevelMode() && ((*_levelData)["type"] == "CollectPoker")) {
        auto str = StringUtils::format("%d_%d", number, colorType);
        return _levelPoker.find(str) !=  _levelPoker.end();
    }
    return false;
}

bool GameViewHD::isLevelCard(int pos) {
    if (DATA_M->isLevelMode() && ((*_levelData)["type"] == "TargetPoker")) {
        auto vec2 = SPRITE_M->getXYByPos(pos);
        auto str = StringUtils::format("%d_%d", (int)vec2.x, (int)vec2.y);
        return _specialPoker.find(str) !=  _specialPoker.end();
    }
    return false;
}

void GameViewHD::updateUI() {
    CCLOG("updateUI0000 %f", moveOffsetY);
    static auto pos = getNode("Panel_bottom")->convertToWorldSpaceAR(Vec2::ZERO);
    static auto originalY = panel_bottom->getPositionY();
//    static auto originalY1 = panel_gift->getPositionY();
    float offsetY = moveOffsetY - pos.y;
    if (moveOffsetY == 0) {
        CCLOG("updateUI0000");
        offsetY = 0;
    }
    
    auto endani4Node = panel_game->getChildByName("Node_endAni4");
    if (endani4Node) {
        static auto endani4PoiY = endani4Node->getPositionY();
        endani4Node->setPositionY(endani4PoiY + offsetY);
    }
    getNode("Panel_bottom")->setPositionY(originalY + offsetY);
//    panel_gift->setPositionY(originalY1+moveOffsetY-pos.y);
}

const shared_ptr<rapidjson::Document> &GameViewHD::getLevelData() const {
    return _levelData;
}

void GameViewHD::levelRelive() {
    ++_reliveCNT;
    gamePause(false);
    const auto &type = string((*_levelData)["type"].GetString());
    //getNode("FileNode_relive")->setVisible(false);
    string show{Lang("100087")};
    if (type == "LimitTime") {
        timeDelay-=LevelAddTime+1;
        updateTime(0);
        show+=Lang_1("100088", LevelAddTime);
    }
    else if (type == "LimitScore" || type == "TargetPoker" || type == "CollectPoker") {
        //UIUtils::playInnerAction(getNode("FileNode_mode"), "idle", false);
        moveNum-=LevelAddMove+1;
        addMoveNum();
        show+=Lang_1("100089", LevelAddMove);
    }
    SCENE_M->showTips(show);
}

//auto vector<int> StarTime{270, 210, 150};
int GameViewHD::getStar() {
    if (DATA_M->getGameType() == DataManager::GameType::Level) {
        if (_reliveCNT != 0) {
            return 2;       //复活过 只能得2✨
        }
    }
    else if (DATA_M->getGameType() == DataManager::GameType::Random || SPRITE_M->isThreeModel) {
        return 3;       //随机或三张 能得3✨
    }
    //5分钟内3星 9分钟内2星
    
    if (timeDelay<= 300) {
        return 3;
    }
    else if(timeDelay<=540) {
        return 2;
    }
    else {
        return 1;
    }
}

const int ADSCDTIME = 24*60*60;
void GameViewHD::onEnter() {
    BaseLayer::onEnter();
    auto timeNow = std::time(0);
    static auto lastShowTime = timeNow;
    if (lastShowTime == timeNow) {
        lastShowTime = timeNow;
    }
    if ((timeNow - lastShowTime >= ADSCDTIME)) {
        this->scheduleOnce([this, timeNow](float){
            if (showInterstitial())
                lastShowTime = timeNow;
        }, 0.5, "delay_showinterstitial_key");
    }
    //    showADS(type, "show");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "showADS", 0, "init", "0"); // 初始化banner
#endif
//    UIUtils::updateRank(1);
}

void GameViewHD::onExit() {
    BaseLayer::onEnter();
    EVENT_M->removeListener("msg_game_tips_end",this);
    EVENT_M->removeListener("msg_game_showwin",this);
    EVENT_M->removeListener("event_game_level_relive",this);
    EVENT_M->removeListener("reward_item_update",this);
    EVENT_M->removeListener("event_game_scene_change",this);
    EVENT_M->removeListener("event_game_update_coin",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
    EVENT_M->removeListener("msg_game_lingqu_game",this);
}

void GameViewHD::setVisible(bool visible)
{
    BaseLayer::setVisible(visible);
    DATA_M->setBannerVisible(visible);
    auto fashTank = SCENE_M->getGameBackground();
    fashTank->showBuild(!visible);
    if (visible) {
        playEffect();
        updateStarBox();
        
        // 第一次 要看下动画
        isOut = true;
        playAni("in",false);
        menuMove(false);
        updateCoin();
        updateDiamond();
        updateLv();
//        playMusic();
        onRecordEnter();
        UIUtils::FIRAnalyticsTrackScreens("GameView");
    }
    else {
        auto lobby = SCENE_M->getLobby();
        if(lobby)
        {
            lobby->menuPlayAni("startloop",true);
        }
        
        if(-1 != SceneID) {
            SOUND_M->stopEffectMusic(SceneID);
            SceneID = -1;
        }
//        if(-1 != SceneMusicID) {
//            SOUND_M->stopEffectMusic(SceneMusicID);
//            SceneMusicID = -1;
//        }
        onRecordExit();
    }
}

void GameViewHD::updateRedPoint(DataManager::GameType gameType) {
#if HasDaily
    getNode("Sprite_tips")->setVisible((DATA_M->hasRedPoint(false) || DATA_M->hasRedPoint(false,DataManager::GameType::Daily)));
#else
    getNode("Sprite_tips")->setVisible((DATA_M->hasRedPoint(false))); // 不需要外边的红点
#endif
}

void GameViewHD::startDaily(const std::string &bureau, const std::string &type) {
    // 测试三张牌局 type 始终是4
    dailyType = atoi(type.c_str()); //4;
    string nbureau = bureau; // SPRITE_M->getBureau(3);
    CCLOG("WTF-%s", nbureau.c_str());
    //同一局重开累计次数，有新开就清零
    DATA_M->addSameChongKaiNum(true);

    DATA_M->setGameType(DataManager::GameType::Daily);
    sendStartGameEvent(DataManager::GameType::Daily);
    this->setVisible(true);
    auto cb = [this, nbureau, type]() {
        auto FileNode_dailytips = getNode("FileNode_dailytips");
        FileNode_dailytips->setVisible(true);
        UIUtils::playInnerAction(FileNode_dailytips, "start", false, [this, FileNode_dailytips](){
            FileNode_dailytips->setVisible(false);
            getNode("Panel_daliy")->setVisible(true);
        });
        auto curDate = DailyManager::getInstance()->getCurrentDate();
        getNode<Text*>("Text_dailyContent")->setString(Lang_1("100153", curDate.name().c_str()));
        //修正挑战提示图片位置
        auto Daily_Daily2_2 = getNode("Daily_Daily2_2");
        auto size = Daily_Daily2_2->getParent()->getBoundingBox().size;
        Daily_Daily2_2->setPosition(Vec2(-60,size.height*0.49));
        bool threeMode = dailyType==4 || dailyType==2; // 三张牌
        getNode<Text*>("Text_dailyMode")->setString(Lang(threeMode?"100107":"100156"));
        getNode<Text*>("Text_dailydate")->setString(curDate.name().c_str());
        getNode<ImageView*>("Image_dailyMode")->loadTexture(threeMode?"daily/Challenge_three.png":"daily/Challenge_one.png", TextureResType::PLIST);//无资源
//        DATA_M->setIsThreeModel(threeMode);
        SPRITE_M->isThreeModel = threeMode;
        resetGame(nbureau);
    };
    cb();//每日挑战插屏在游戏结束时显示
    return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (showInterstitial()) {
        //暂停背景音乐
        //SoundManager::getInstance()->pauseGameBgMusic();
        AdsManager::waitWinAction = true;
        InterstitialCB = cb;
    }
    else
    {
        cb();
    }
#else
    showInterstitial();
    cb();
#endif
}

void GameViewHD::showNode(const std::string &name, bool visible)
{
    auto node = getNode(name);
    if (node) {
        node->setVisible(visible);
    }
}

void GameViewHD::playEffect()
{
//    if(TEACH_M->isTeaching("firstBureau"))
//    {
//        SceneID = SOUND_M->playEffectMusic(ShopManager::getInstance()->getSceneEffect(18-12), true);
//        return;
//    }
//    int gameBgType = DATA_M->getCardPicType(1);
//    if(gameBgType > 13)
//    {
//        if(-1 != SceneID)
//            SOUND_M->stopEffectMusic(SceneID);
//        if(gameBgType<=16)
//        {
//            SceneID = SOUND_M->playEffectMusic(ShopManager::getInstance()->getSceneEffect(14-12), true);
//        }
//        else
//        {
//            SceneID = SOUND_M->playEffectMusic(ShopManager::getInstance()->getSceneEffect(gameBgType-12), true);
//        }
//
//    }
//    else
//    {
//        if(-1 != SceneID) {
//            SOUND_M->stopEffectMusic(SceneID);
//            SceneID = -1;
//        }
//        SOUND_M->stopDTEffect();
//    }
}

void GameViewHD::playMusic()
{
    // 不需要播放音乐
//    int gameBgType = DATA_M->getCardPicType(1);
//    if(gameBgType > 13&&this->isVisible())
//    {
//        auto musicName = ShopManager::getInstance()->getSceneMusic(gameBgType-12);
//        if(-1 != SceneMusicID) {
//            SOUND_M->stopEffectMusic(SceneMusicID);
//            SceneMusicID = -1;
//        }
//        if (!musicName.empty())
//            SceneMusicID = SOUND_M->playEffectMusic(musicName, true);
//    }
}

void GameViewHD::updateShuffle()
{
    auto text = getNode<Text*>("Text_ShuffleNum_0");
    auto str = text->getString();
    auto stri = UIUtils::stoii(str);
    auto num = RewardManager::getInstance()->getCNT(RewardManager::RewardType::Magic);
    auto grouwup = GrowupNode::create();
    text->addChild(grouwup);
    grouwup->startGrouwup(text, stri, num, 0.2, [this, grouwup](){
        //UIUtils::playInnerAction(FileNode_gold, "jump", false);
        grouwup->removeFromParent();
    });
    
//    auto text2 = getNode<Text*>("Text_ShuffleNum_1");
//    auto str2 = text->getString();
//    auto stri2 = UIUtils::stoii(str);
//    auto num2 = RewardManager::getInstance()->getCNT(RewardManager::RewardType::Magic);
//    auto grouwup2 = GrowupNode::create();
//    text2->addChild(grouwup2);
//    grouwup2->startGrouwup(text2, stri2, num2, 0.2, [this, grouwup2](){
//        //UIUtils::playInnerAction(FileNode_gold, "jump", false);
//        grouwup2->removeFromParent();
//    });
}

void GameViewHD::playGetMagic(bool isInterstitials)
{
    //设置位置
    auto poi = getMagicWorldPoi();
    FileNode_getMagic->setPosition(poi);
    UIUtils::playInnerAction(FileNode_getMagic,"Start0",false,[this, isInterstitials](){
        //更新道具显示
        updateShuffle();
    });
}

void GameViewHD::useMagic()
{
    //重置提示累计时间
    _tipsTime = 0;
    openLimitTimeHintTime = 0;
    auto num = RewardManager::getInstance()->getCNT(RewardManager::RewardType::Magic);
    if(num > 0)
    {
        //累计使用魔法棒任务数 新手
        TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::MAGIC);
        isCanTouch = false;
        auto is = SPRITE_M->isMagic();
        if(is)
        {
            _magicCNT++;
            
            if(isPause)
            {
                isPause = false;
            }//然后是分数步数
            //动画
            Node* node = Node::create();
            panel_game->addChild(node);
            auto poi = SPRITE_M->getMagicPoi();
            node->setPosition(poi);
            node->setLocalZOrder(200);
            //addFrameEndCallFunc
            auto magicNode = UIUtils::createCSBNode("Animation/Magic.csb", "Start0", false);
            node->addChild(magicNode);
            auto action = dynamic_cast<ActionTimeline*>(magicNode->getActionByTag(10086));
            
            action->setFrameEventCallFunc([this,num,node](Frame *e){
                auto event = dynamic_cast<EventFrame*>(e);
                if(event&&event->getEvent() == "magic")
                {
                    SPRITE_M->Shuffle();
                    SPRITE_M->clearMoveDatas();
                    RewardManager::getInstance()->useItem(RewardManager::RewardType::Magic);
                    //2021年4月1日 此版本关闭辅助
//                    //如果此局不是辅助局 则开启辅助  没有超过限制开启辅助的步数
//                    if(!SPRITE_M->getIsOpenEffective()&&(!SPRITE_M->getIsFanPaiNum()||(SPRITE_M->getIsFanPaiNum()&&SPRITE_M->getFanPaiNum() > moveNum)))
//                    {//开启辅助
//                        SPRITE_M->setIsDaoJuAI(true);
//                        //随机次数 2次或3次
//                        auto rand = random(0, 1);
//                        SPRITE_M->setDaoJuAINum(rand%2==0?2:3);
//                    }
                    updateShuffle();
                }
                
                
            });
            
            action->setLastFrameCallFunc([node](){
                node->removeFromParent();
            });
            action->play("Start0", false);
            SOUND_M->playEffectMusic(EffectMagic0);
            //action->gotoFrameAndPlay(0,113,0,false);
            
        }
        else
        {
//            isCanTouch = true;
//            showTips();
        }
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("click")},
            {"value", Value("magic")},
        });
        UIUtils::FIRAnalyticsEventWithPrefix("gameUseMagic");
    }
    else
    {
        //打开窗口禁止累计提示计时
        isOpenTipsTime = false;
        auto shuffleView = ShuffleView::createLayerN();
        SCENE_M->addDialog(shuffleView);
        gamePause(true);//窗口打开暂停游戏
    }
}

void GameViewHD::agianGame()
{
    ValueMap valueMap; // 上报参数
    restartGame(true);
    valueMap["Button"] = "Button_liveReplay";
    UIUtils::FIRAnalyticsEvent("event_newGame_replay", valueMap);
}

void GameViewHD::setFuZhuTipsColor(bool isOpenAI)
{
//    if(isOpenAI)
//    {
//        sprite_fuZhu_on->setVisible(true);
//        sprite_fuZhu_off->setVisible(false);
//    }
//    else
//    {
//        sprite_fuZhu_on->setVisible(false);
//        sprite_fuZhu_off->setVisible(true);
//    }
}

void GameViewHD::updateyday()
{//打开时 判断是不是第二天。
    auto is = DATA_M->isYday();
    auto isStartOne = DATA_M->getStartOne();
    if(is&&!isStartOne)
    {//是第二天
        //增加道具次数
        RewardManager::getInstance()->getReward(RewardManager::RewardType::Magic,1,true);
        //更新显示
        updateShuffle();
    }
}

void GameViewHD::ceshi()
{
    if(UIUtils::IsPad())
    {
        return;
    }
    auto is = SPRITE_M->getIsOpenEffective();
    if(is)
    {
        getNode<Text*>("Text_effff")->setString("已开启");
    }
    else
    {
        getNode<Text*>("Text_effff")->setString("已关闭");
    }
}

void GameViewHD::setIsShowTips(bool is)
{
    isShowTips = is;
}
bool GameViewHD::getIsShowTips()
{
    return isShowTips;
}

void GameViewHD::limitTimeHint()
{
    //提示10次；
    if(LimitTimeHintNum >= 10)
    {
        return;
    }
    LimitTimeHintNum++;
    //找到能收的牌的位置
    hintCard = SPRITE_M->findACardPoi();
    if(!hintCard)return;
    auto poi = hintCard->getPosition();
    if(!node_levelhint)
    {
        node_levelhint = UIUtils::createCSBNode("levelhint.csb","Start",false,[this](){
            node_levelhint->removeFromParent();
            node_levelhint = nullptr;
            isCanTouch = true;
            LimitTimeHintLayer->setVisible(false);
            openLimitTimeHintTime = 0;
            _tipsTime = 0;
            hintCard->setLocalZOrder(hintCard->getCLocalZOrder());
        });
        panel_game->addChild(node_levelhint);
        //auto poi2 = panel_game->convertToWorldSpace(poi);
        node_levelhint->setPosition(poi);
        LimitTimeHintLayer->setVisible(true);
        isCanTouch = false;
        hintCard->setLocalZOrder(100);
        node_levelhint->setLocalZOrder(100);
    }
}

void GameViewHD::initLimitTimeHintLayer()
{
    LimitTimeHintLayer = LayerColor::create(Color4B(0, 0, 0, 128));
    LimitTimeHintLayer->setLocalZOrder(100);
    //LimitTimeHintLayer->setAnchorPoint(Vec2(0.5,0.5));
    LimitTimeHintLayer->setIgnoreAnchorPointForPosition(false);
    LimitTimeHintLayer->setVisible(false);
    LimitTimeHintLayer->setName("LimitTimeHintLayer");
    auto size = Director::getInstance()->getWinSize()/panel_game->getScaleX();
    LimitTimeHintLayer->setContentSize(size);
    panel_game->addChild(LimitTimeHintLayer);
    auto poi = panel_game->convertToNodeSpace(Vec2::ZERO);
    LimitTimeHintLayer->setPosition(Vec2(poi.x + size.width*0.5,poi.y+size.height*0.5));
}

void GameViewHD::setGameState(State state)
{
    _gameState = state;
}

void GameViewHD::resetOne()
{
    auto type = DATA_M->getStartGameType();
    type = (type == DataManager::GameType::Huo || type == DataManager::GameType::Huo)?type:DataManager::GameType::Huo; // level和daily不能够
    DATA_M->setGameType(type);
    menuMove(false);
    restartGame(false, type, true); // 否展示插屏
    setVisible(true);
    string eventName{"gameStartOne_" + toString(int(type))};
    if (!TEACH_M->isDailyLevelUnlock()) {
        UIUtils::FIRAnalyticsEventWithPrefix(eventName + "_" + TEACH_M->getCurrentTeachKey(), "teach");
    }
    else
        UIUtils::FIRAnalyticsEventWithPrefix(eventName);
}

void GameViewHD::showLobby()
{
    //正在进入大厅中
    auto lobby = SCENE_M->getLobby();
    lobby->setIsGoGameView(false);
    menuMove(true); // 隐藏
    playAni("out",false,[this,lobby](){
        
        if (lobby) {
            lobby->setVisible(true);
//            if(DATA_M->getGameType() == DataManager::GameType::Level)
//            {
//                //lobby->setTab(MainLobby::Tab::Level);
//                lobby->resetLevelView();
//            }
//            else if(DATA_M->getGameType() == DataManager::GameType::Huo||DATA_M->getGameType() == DataManager::GameType::Random)
//            {//是经典模式
//                lobby->setTab(MainLobby::Tab::Home);
//            }
//            else if(DATA_M->getGameType() == DataManager::GameType::Daily)
//            {
//
//            }
            
            
            lobby->resetHome();
            this->setVisible(false);
    //        SPRITE_M->clearAllData();
        }
    });
    
}
void GameViewHD::showHome()
{
    auto lobby = SCENE_M->getLobby();
        if (lobby) {
            lobby->setVisible(true);
            if(DATA_M->getGameType() == DataManager::GameType::Level)
            {
                //lobby->setTab(MainLobby::Tab::Level);
                //lobby->resetLevelView();
            }
            lobby->setTab(MainLobby::Tab::Home);
            lobby->resetHome();
            this->setVisible(false);
    //        SPRITE_M->clearAllData();
        }
}

void GameViewHD::menuPlayAni(std::string name,bool isLoop,std::function<void()> cb)
{
    UIUtils::playInnerAction(FileNode_2020Menu,name,isLoop,cb);
}

void GameViewHD::menuPausePlayAni(std::string name,bool isLoop,std::function<void()> cb)
{
    //UIUtils::playInnerAction(FileNode_pause,name,isLoop,cb);
    UIUtils::playInnerAction(FileNode_pause2,name,isLoop,cb);
}


void GameViewHD::updateCoin(bool isDelay)
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
        auto coinNum = UIUtils::stoii(str);
        auto num = DATA_M->getCoinNum();
        auto tempNum = num - coinNum;
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
        grouwup->startGrouwup(text, coinNum, num, time, "",[this, grouwup](){
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

void GameViewHD::updateDiamond()
{
//    int diamondNum = DATA_M->getDiamond();
//    getNode<TextBMFont*>("BitmapFontLabel_diamond")->setString(StringUtils::toString(diamondNum));
}

void GameViewHD::updateLv()
{
    auto player = PlayerManager::getInstance();
    auto percent = player->getPercent();
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(player->getLevel()));
    loadingBar_percent->setPercent(percent);
    loadingBar_menu_percent->setPercent(percent);
}

void GameViewHD::showGoldAni()
{
//    //结算界面显示结束 创建金币节点img_icon_gold
//    auto poi = img_icon_gold->getPosition();
//    poi = img_icon_gold->getParent()->convertToWorldSpace(poi);
//    REWARD_M->rewardItemAction(5,poi,this->getContentSize()*0.5,itemVec1,[this](){
//        //刷新金币
//        updateCoin();
//    },"Gold");
}

void GameViewHD::updateDYY()
{
    
    #if HasDaily
        // 每日
        getNode<Text*>("Text_dailytips")->setString(Lang("100154"));
        getNode<Text*>("Text_dailyTitle")->setString(Lang("100155"));
    #endif
    //getNode<Text*>("Text_startagain")->setString(Lang("100128"));
    auto Text_Free = getNode<Text*>("Text_Free");
    Text_Free->setString(Lang("100279"));
    UIUtils::textAdaptiveSize(Text_Free,180);
    auto text_mainmove = getNode<Text*>("text_mainmove");
    text_mainmove->setString(Lang("100061"));
    UIUtils::textAdaptiveSize(text_mainmove,220);
    getNode<Text*>("text_maintime")->setString(Lang("100060"));
    
    
    auto Text_btntips = getNode<Text*>("Text_btntips");
    Text_btntips->setString(Lang("100131"));
    UIUtils::textAdaptiveSize(Text_btntips,150);
    
    auto Text_newgame2 = getNode<Text*>("Text_newgame2");
    Text_newgame2->setString(Lang("100072"));
    UIUtils::textAdaptiveSize(Text_newgame2,150);
//    auto Text_redution = getNode<Text*>("Text_redution");
//    Text_redution->setString(Lang("100130"));
//    UIUtils::textAdaptiveSize(Text_redution,150);
    auto Text_redution2 = getNode<Text*>("Text_redution2");
    Text_redution2->setString(Lang("100130"));
    UIUtils::textAdaptiveSize(Text_redution2,150);
    getNode<Text*>("text_mainscore")->setString(Lang("100059"));
    getNode<Text*>("Text_autoComplete")->setString(Lang("100069"));
    auto Text_btnMagic = getNode<Text*>("Text_btnMagic");
    Text_btnMagic->setString(Lang("100179"));
    UIUtils::textAdaptiveSize(Text_btnMagic,150);
    auto Text_btnMagic2 = getNode<Text*>("Text_btnMagic2");
    Text_btnMagic2->setString(Lang("100179"));
    UIUtils::textAdaptiveSize(Text_btnMagic2,150);
    
    auto Text_teach = getNode<Text*>("Text_teach");
    Text_teach->setString(Lang("100321"));
    UIUtils::textAdaptiveSize(Text_teach,130);
    FIND_NODE(Text*, FileNode_2020Menu, "Text_currentLv")->setString(Lang("100200"));
    
    FIND_NODE(Text*, FileNode_top, "Text_currentLv")->setString(Lang("100200"));
    
    
    getNode<Text*>("Text_StarBox")->setString(Lang("100234"));
    getNode<Text*>("Text_StarBox_open")->setVisible(false);
    getNode<Text*>("Text_StarBox_open")->setString(Lang("100285"));
    
    
    getNode<Text*>("Text_rankReward")->setString(Lang("100062"));

    
    if (LevelUpView) {
        auto Text_level_up_lv = LevelUpView->getNode<Text*>("Text_level_up_lv");
        Text_level_up_lv->setString("升级");
    }
    if(DATA_M->isDailyMode())
    {
        auto curDate = DailyManager::getInstance()->getCurrentDate();
        getNode<Text*>("Text_dailyContent")->setString(Lang_1("100153", curDate.name().c_str()));
    }
    else if(DATA_M->isLevelMode()&&_levelData)
    {
        auto taskStr = LevelManager::getInstance()->getShowString(_levelData);
        getNode<Text*>("Text_levelContent")->setString(taskStr);
        getNode<Text*>("Text_taskTips")->setString(taskStr);
    }
    
    _gameWinLayer->updateDYY();
    //_gameWinLayerDaily->updateDYY();
    //_gameWinLayerLevel->updateDYY();
    LevelUpView->updateDYY();
}

void GameViewHD::updateRandReward()
{
    auto rank = getMyRank();
    DATA_M->setRank(rank);
    long startTs = UIUtils::getDailyTS(); // + OneDaySec;
    DATA_M->setRankDailyTS(startTs);
    
    
    auto isReward = DATA_M->getIsRankReward();
    auto oldRank = DATA_M->getOldRank();
    //第一个排行榜 99名，结束后第二个排行榜 301名 没有领99名的奖励，
    if(isReward&&oldRank > 100)
    {//第二个排行榜了 并且排行没进前百
        DATA_M->resetRank();
    }
    getNode("Text_rankReward")->setVisible(isReward&&oldRank <= 100&&oldRank != -1);
}

void GameViewHD::updateNewVersion(bool isShow)
{
    auto isNew = DATA_M->isNewVer();
    getNode("img_new_Ver")->setVisible(isNew&&isShow);
}

Vec2 GameViewHD::getMagicWorldPoi()
{
    Node *Node_magic_poi;
    if(isHardDaily)
    {
        Node_magic_poi = getNode("Text_btnMagic");
    }
    else
    {
        Node_magic_poi = getNode("Text_btnMagic2");
    }
    
    
    auto poi = Node_magic_poi->getPosition();
    poi = Node_magic_poi->getParent()->convertToWorldSpace(poi);
    poi = FileNode_getMagic->getParent()->convertToNodeSpace(poi);
    return poi;
}

Vec2 GameViewHD::getGoldWorldPoi()
{
    auto img_icon_top_gold = getNode("Node_Gold");
    auto poi = img_icon_top_gold->getPosition();
    poi = img_icon_top_gold->getParent()->convertToWorldSpace(poi);
    //poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}
Vec2 GameViewHD::getdiamondWorldPoi()
{
    auto img_icon_top_diamond = getNode("img_icon_top_diamond");
    auto poi = img_icon_top_diamond->getPosition();
    poi = img_icon_top_diamond->getParent()->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}

Vec2 GameViewHD::getLevelWorldPoi()
{//
    auto img_icon_top_diamond = getNode("Node_Exp");
    auto poi = img_icon_top_diamond->getPosition();
    poi = img_icon_top_diamond->getParent()->convertToWorldSpace(poi);
    //poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}

Vec2 GameViewHD::getBtnFishWorldPoi()
{
    auto Node_59 = FileNode_2020Menu->getChildByName("Node_59");
    
    auto Button_fish = Node_59->getChildByName("Button_pause");
    auto poi = Button_fish->getPosition();
    poi = Node_59->convertToWorldSpace(poi);
    //poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}

Vec2 GameViewHD::getPauseWorldPoi()
{
    auto poi = FileNode_pause2->getPosition();
    poi = FileNode_pause2->getParent()->convertToWorldSpace(poi);
    return poi;
}

Vec2 GameViewHD::getBagWorldPoi()
{
    auto poi = FileNode_MyBag->getPosition();
    poi = FileNode_MyBag->getParent()->convertToWorldSpace(poi);
    
//    auto sp = Sprite::createWithSpriteFrameName("main_tips1.png");
//    addChild(sp);
//    sp->setPosition(poi);
    return poi;
}

float GameViewHD::getFishScale(float fishWidth)
{
    auto Button_fish = getNode("Button_fish");
    auto size = Button_fish->getBoundingBox().size;
    auto width = size.width/3;
    
    auto scale = width / fishWidth;
    
    
    return scale;
}

void GameViewHD::updataBagNew()
{
    auto Ui_Previewicon2_4 = FileNode_MyBag->getChildByName("Ui_Previewicon2_4");
    auto isPropNew = DATA_M->getIsPropNew();
    auto img_new_Bag = Ui_Previewicon2_4->getChildByName("img_new_Bag");
    img_new_Bag->setVisible(isPropNew);
}

void GameViewHD::updateFishNewTips()
{
    auto isFishNew = DATA_M->getIsFishNuw();
    auto isFashTank = DATA_M->getIsFashTankNuw();
    menu_fish_tips->setVisible(isFishNew||isFashTank);
}

void GameViewHD::menuMove(bool out)
{
    auto type = DATA_M->getGameType();
    isHardDaily = (type==DataManager::GameType::Daily&&dailyType==4);
    if (out) {
        if (!isOut) {
            isOut = true;
            menuPlayAni("Start1", false);
        }
    }
    else {
        if (isOut) {
            isOut = false;
            menuPlayAni("Start0", false,[this](){
                
            });
        }
    }
}

void GameViewHD::startTeachBureau() {
    //恢复音效
    //SOUND_M->resumeDTEffect();
    //隐藏奖励
    panel_gift->setVisible(false);
    //指定模式
    DATA_M->setGameType(DataManager::GameType::Huo);
    DATA_M->setIsThreeModel(false);
    bool levelMode = DATA_M->isLevelMode();
    auto panel_sub = getNode("Panel_sub");
    if (panel_sub)
        panel_sub->setVisible(!levelMode);
    
    getNode("text_mainmove")->setVisible(!levelMode);
    getNode("text_maintime")->setVisible(!levelMode);
    getNode("Score")->setVisible(!levelMode);
    
    getNode("Node_time")->setVisible(!levelMode);
    getNode("text_mainscore")->setVisible(!levelMode);
    getNode("Panel_times")->setVisible(!levelMode);
    getNode("game_score1_game")->setVisible(!levelMode);
    //getNode("FileNode_mode")->setVisible(levelMode);
    getNode("Panel_daliy")->setVisible(false);
    getNode("Panel_level")->setVisible(false);
    //============================================
    panel_gift->setVisible(false);
    TEACH_M->startTeach("firstBureau");
    resetGameData();
    SPRITE_M->setTeachBureau();
    menuMove(true);
}

void GameViewHD::setIsRefushGift(bool isShow)
{
    isRefushGift = isShow;
}

void GameViewHD::playBagAni()
{
    UIUtils::playInnerAction(FileNode_MyBag,"Start",false);
}


bool GameViewHD::winLayerIsShow()
{
    auto layerVisible = _gameWinLayer->isVisible();
//    auto dailyVisible = _gameWinLayerDaily->isVisible();
//    auto levelVisible = _gameWinLayerLevel->isVisible();
    
    return layerVisible;
}

void GameViewHD::tipsFangCuo()
{//针对 游戏中 被提示限制操作的问题 
	if (isShowTips&&!panel_tips->isVisible()&&isOpenTipsTime)
	{// 防错 如果panel_tips已经隐藏了 但是isShowTips仍然为true; 将其变为false
		isShowTips = false;
	}
}

void GameViewHD::winAnimation(int goldNum)
{
    
    LevelUpView->setData(lv,oldLv, percent1,percent2,percentDx,winCB);
    //播放
    playAni("top0",false,[this,goldNum](){
        
        winCB = [this](){
            auto isUnlock = LevelUpView->getIsUnlock();
            if(isUnlock)
            {
//                playAni("in",false);
//                menuMove(false); // 出现吧
                this->runAction(Sequence::create(DelayTime::create(3),CallFunc::create([this](){
                    playAni("in",false);
                    menuMove(false); // 出现吧
                }),NULL));
            }
            else
            {
                this->runAction(Sequence::create(DelayTime::create(3),CallFunc::create([this](){
                    playAni("in",false);
                    menuMove(false); // 出现吧
                }),NULL));
            }
        };
        
        //经验
        //创建5个经验节点 飞上去 经验条增长，增长完毕弹出结算
        auto poi = getLevelWorldPoi();
        //poi = _rootNode->convertToNodeSpace(poi);
        std::vector<Vec2> itemVec1;
        int expNum = _winExp==5?5:_winExp*0.5;
        DATA_M->randVec(expNum,&itemVec1,320);
        
        REWARD_M->rewardItemAction(expNum,poi,this->getContentSize()*0.5,itemVec1,[this](){

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
        
        
        
        //星星
        auto lobby = SCENE_M->getLobby();
        auto starNum = 1;
        lobby->starAni(starNum,"start1",getStarBoxWorldPoi(),[this](){
            updateStarBox(true);
        });
        
        //金币
        auto goldPoi = getGoldWorldPoi();
        poi = getContentSize()*0.5;
        lobby->goldAni(goldNum,nullptr,poi,[this,lobby,goldNum](){
            DATA_M->setCoinNum(goldNum, true, 112);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            //SCENE_M->getLobby()->updateCoin(true);

        },[lobby,this](){
            //home
            //SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni(1,true);
        },[lobby,this](){
            
            lobby->playGoldAni(1,false);
        },goldPoi);
    });
}

Vec2 GameViewHD::getStarBoxWorldPoi()
{
    auto Button_StarBox = FileNode_StarBox->getChildByName("Button_StarBox");
    auto Star_target = Button_StarBox->getChildByName("Star_target");
    auto poi = Star_target->getPosition();
    poi = Button_StarBox->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}

void GameViewHD::updateStarBox(bool isDelay)
{
    auto num1 = DATA_M->getStarBoxNum();
    auto num2 = DATA_M->getStarBoxNumMax();
    if(num1 == num2)
    {
        
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
        auto nam = Text_StarNum->getString();
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
                //UIUtils::playInnerAction(FileNode_gold, "jump", false);
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
                //UIUtils::playInnerAction(FileNode_gold, "jump", false);
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

int GameViewHD::getMyRank()
{
    //排名
    auto &rankArr = RankManager::getInstance()->getRankList();
    string uuid = "";
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    uuid = UIUtils::getAD();
#endif
    int rank = MAX_RANK;
    
    for (int i = 0; i < rankArr.size(); i++) {
        if (uuid == rankArr.at(i).getKey()) {
            rank = i + 1;
            break;
        }
    }
    
    return rank;
}

void GameViewHD::unlockFishMove(int idx,Vec2 startPoi,std::function<void()> cb)
{
    auto skeletonNode = FISH_M->getFishSpine(idx);
    this->addChild(skeletonNode);
    skeletonNode->setPosition(startPoi);
    auto size = skeletonNode->getBoundingBox().size;
    auto gameView = SCENE_M->getGameView();
    auto poi = gameView->getBtnFishWorldPoi();
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

void GameViewHD::unlockFashTankMove(int idx,string frameName,Vec2 startPoi,std::function<void()> cb)
{
    auto sprite = Sprite::createWithSpriteFrameName(frameName);
    this->addChild(sprite);
    sprite->setPosition(startPoi);
    auto fashTank = SCENE_M->getGameBackground();
    auto endPoi = fashTank->getPeiShiWorldPoi(idx);
    auto moTo = MoveTo::create(0.5f, endPoi);
    
    auto remo = RemoveSelf::create();
    auto seq = Sequence::create(moTo, remo,CallFunc::create(cb),NULL);
    sprite->runAction(seq);
}

void GameViewHD::setButtonPauseEnabled(bool isEnabled)
{
    Button_pause->setEnabled(isEnabled);
}

void GameViewHD::updateRank()
{
    if(_gameWinLayer)
    {
        _gameWinLayer->updateRank();
    }
}

void GameViewHD::updateBtnChallenge()
{
    auto isChallenge = DATA_M->getIsChallenge();
    getNode("btn_challenge")->setVisible(isChallenge);//更新
}

void GameViewHD::showChallenge()
{//在总局数大于等于4局时弹窗一次 在新开 重开 与关闭升级弹窗时触发
    auto isChallenge = DATA_M->getIsChallenge();
    if(DATA_M->getIsChallengeOpenOne()&&isChallenge)
    {
        SCENE_M->addDialog(ChallengeModeView::createLayerN(ChallengeModeView::Type::Game));
        gamePause(true);//窗口打开暂停游戏
        DATA_M->setIsChallengeOpenOne(false);
    }
    
}
