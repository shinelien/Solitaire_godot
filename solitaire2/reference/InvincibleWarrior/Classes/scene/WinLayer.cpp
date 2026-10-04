# include "WinLayer.h"
#include "ScoreManager.h"
#include "GrowupNode.h"
#include "SpriteManager.h"
#include "PlayerManager.h"
#include "MultipleRewardView.h"
#include "RewardManager.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#endif
#include "TeachManager.h"
#include "EventObserver.h"
#include "FeedBackView.h"
#include "ShareRewardView.h"
#include "GameKitHelper.h"
#include "RankView.h"
#include "DailyManager.h"
#include "FishGuideManager.h"

Scene * WinLayer::createScene()
{
	return UIUtils::createScene(WinLayer::create());
}

WinLayer * WinLayer::createLayer()
{
    auto winLayer = WinLayer::create();
    winLayer->setName("WinLayer");
    return winLayer;
}

WinLayer * WinLayer::createLayer(int score, float time, int moveNum, int extraScore, int totalStar)
{
	auto winLayer = WinLayer::create();
	winLayer->setName("WinLayer");
	winLayer->showAction(score,time,moveNum,extraScore,totalStar);
	return winLayer;
}

bool WinLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	return true;
}

void WinLayer::initData()
{
    EVENT_M->addListener("event_game_winLayer",[this](ValueMap valueMap, void *obj){
//        auto lobby = SCENE_M->getLobby();
//        lobby->setVisible(true);
//        lobby->resetHome();
//        //lobby->dailyShowComplete();
//        lobby->updateExp();
//        auto poi = getContentSize()*0.5;
//        auto multiple = multipleNum==0||isMultiple?7:5;
//        auto num = WINLAYER_COIN*multipleNum;
//        lobby->goldAni(WINLAYER_COIN*multipleNum,nullptr,poi,[this,lobby,num](){
//            DATA_M->setCoinNum(num, true);
//            ValueMap valueMap{
//                {"isTime",Value{true}}
//            };
//            //更新有金币显示
//            EVENT_M->sendEvent("event_game_update_coin",valueMap);
//            //SCENE_M->getLobby()->updateCoin(true);
//
//        },[lobby](){
//            //home
//            //SOUND_M->playEffectMusic(EffectGetCoin);
//            lobby->playGoldAni(1,true);
//        },[lobby,this](){
//            if(isShowStar)
//            {
//                isShowStar = false;
//
//            }
//            //SOUND_M->playEffectMusic(EffectGetCoin);
//            lobby->playGoldAni(1,false);
//        });
//        poi.width+=160;
//        auto diamond = WINLAYER_DIAMOND*multipleNum;
//        lobby->diamondAni(WINLAYER_DIAMOND*multipleNum,nullptr,poi,[this,lobby,diamond](){
//            //更新有金币显示
//            DATA_M->setDiamond(diamond);
//            ValueMap valueMap{
//                {"isTime",Value{true}}
//            };
//            //更新有金币显示
//            EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//            //SCENE_M->getLobby()->updateDiamond(true);
//
//        },[lobby](){
//            //home
//            //SOUND_M->playEffectMusic(EffectGetGem);
//            lobby->playDiamondAni(1,true);
//        },[lobby](){
//            //home
//            //SOUND_M->playEffectMusic(EffectGetGem);
//            lobby->playDiamondAni(1,false);
//        });
//        lobby->starAni(starNum,"Star");
//        tempMultipleNum = multipleNum;
//        SCENE_M->getGameView()->setVisible(false);
//        this->setVisible(false);
        
        auto gameView = SCENE_M->getGameView();
        
        auto lobby = SCENE_M->getLobby();
        lobby->dailyShowComplete();
        lobby->updateUI();//虽然没有回大厅，但是也刷新一下
        
        gameView->restartGame(false, DataManager::GameType::Huo, true);
        gameView->winAnimation(_coinNum * multipleNum);
        this->setVisible(false);
        // 记录app启动次数
        auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
        cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
        DATA_M->setAppStartCNT(startCNT);
        UIUtils::requestReview();
    },this);
    //addEvent("event_game_winLayer", CC_CALLBACK_1(WinLayer::getVideoReward, this));
    
    EVENT_M->addListener("msg_game_showwin",[this](ValueMap valueMap, void *obj){
        if (_InterstitialCB) {
            _InterstitialCB();
            _InterstitialCB = nullptr;
        }
        
//        //重置限制插屏的cd
//        auto timeNow = std::time(0);
//        DATA_M->setInterstitialTime();
//        DATA_M->setIsVideoAdsTime(true);
//        DATA_M->setVideoAdsTime(0,true);//重置激励视频对插屏的限制cd
//        DATA_M->setIsShowAds(false);
    },this);
//    addEvent("msg_game_showwin", [this](EventCustom*) {
//
//    });
}

void WinLayer::initUI()
{
    BaseLayer::initUI();
    doLayout();
    auto node = _rootNode;
    _actionManager->setLastFrameCallFunc([this]() {
        _actionManager->play("Loop", true);
        _actionManager->setLastFrameCallFunc(nullptr);
//        this->showPokersAction();
        
        // 记录app启动次数
        auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
        cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
        DATA_M->setAppStartCNT(startCNT);
        UIUtils::requestReview();
    });
    
    _actionManager->setFrameEventCallFunc([this](Frame*frame){
        
        auto event = dynamic_cast<EventFrame*>(frame);
        auto name = event->getEvent();
        if(name=="ChaPing")
        {
            
        }
    });
    
	INIT_BTN(node,"btn_new", CC_CALLBACK_1(WinLayer::dealButtonClick, this));
    INIT_BTN(node,"Button_doubleWin", CC_CALLBACK_1(WinLayer::dealButtonClick, this));
    INIT_BTN(node,"btn_new", CC_CALLBACK_1(WinLayer::dealButtonClick, this));
//	for (int i = 0; i < 7;i++)
//	{
//		panel[i] = FIND_NODE(Node *, node, CCString::createWithFormat("panel_%d",i)->getCString());
//		panel[i]->setVisible(false);
//	}
//    text_you_ExtraScore = FIND_NODE(TextBMFont *, node, "text_you_ExtraScore");
//    text_best_ExtraScore = FIND_NODE(TextBMFont *, node, "text_best_ExtraScore");
    text_you_TotalScore = FIND_NODE(TextBMFont *, node, "text_you_TotalScore");
    text_best_TotalScore = FIND_NODE(TextBMFont *, node, "text_best_TotalScore");
    
    FileNode_gold = UIUtils::createCSBNode("Animation/Node_gold.csb");
    //FileNode_zuanShi = UIUtils::createCSBNode("Animation/Node_currency.csb","Baoshi",false);
    //getNode("Node_zuanShi")->addChild(FileNode_zuanShi);
    FIND_NODE(Node*, node, "Node_gold")->addChild(FileNode_gold);
//    atlasLabel_you_score = FIND_NODE(TextBMFont *, node, "atlasLabel_you_score");
//    atlasLabel_best_score = FIND_NODE(TextBMFont *, node, "atlasLabel_best_score");
	atlasLabel_you_time = FIND_NODE(TextBMFont *, node, "atlasLabel_you_time");
	atlasLabel_best_time = FIND_NODE(TextBMFont *, node, "atlasLabel_best_time");
	atlasLabel_you_movetime = FIND_NODE(TextBMFont *, node, "atlasLabel_you_movetime");
	atlasLabel_best_movetime = FIND_NODE(TextBMFont *, node, "atlasLabel_best_movetime");
	atlasLabel_coinnum = FIND_NODE(TextBMFont *, node, "atlasLabel_coinnum");
    atlasLabel_coinnum_0 = FIND_NODE(TextBMFont *, node, "atlasLabel_coinnum_0");
    atlasLabel_coinnum_0_0 = FIND_NODE(TextBMFont *, node, "atlasLabel_coinnum_0_0");
    atlasLabel_zuanShiNum = getNode<TextBMFont*>("atlasLabel_zuanShiNum");
    atlasLabel_zuanShiNum->setVisible(false);
//    FileNode_gold = FIND_NODE(Node *, node, "FileNode_gold");
    Text_modeformat = FIND_NODE(Text *, node, "Text_modeformat");
    Text_percent = FIND_NODE(Text *, node, "Text_percent");
    
    loadingBar_percent = getNode<LoadingBar*>("LoadingBar_percent");
    Text_lv = getNode<Text*>("Text_lv");
    //金币倍数
    BitmapFontLabel_doubleCoin = getNode<TextBMFont*>("BitmapFontLabel_doubleCoin");
    Text_look = getNode<Text*>("text_look");
    Text_rank = getNode<Text*>("text_rank");
    atlasLabel_rank = getNode<TextBMFont*>("atlasLabel_rank");
    vector<string> strArr = {"C","O","N","G","R","A","T","U","L","A","T","I","O","N","S","!"};
    //文本
    for(int i = 0;i < strArr.size();++i)
    {
        auto text = getNode<Text*>(StringUtils::format("Text_14_%d",i));
        text->setString(strArr.at(i));
    }
    
    
    // 处理多语言
    updateDYY();
}
void WinLayer::updateDYY()
{
    auto node = _rootNode;
    FIND_NODE(Text *,node,"text_ni")->setString(UIUtils::getStringByName("100057"));

    FIND_NODE(Text *,node,"text_zuijia")->setString(UIUtils::getStringByName("100058"));
    FIND_NODE(Text *,node,"text_totalscore")->setString(UIUtils::getStringByName("100059"));
    FIND_NODE(Text *,node,"text_time")->setString(UIUtils::getStringByName("100060"));
    auto text_movetime = FIND_NODE(Text *,node,"text_movetime");
    text_movetime->setString(UIUtils::getStringByName("100061"));
    UIUtils::textAdaptiveSize(text_movetime,290);
    FIND_NODE(Text *,node,"text_get")->setString(UIUtils::getStringByName("100062"));
    FIND_NODE(Text *,node,"Text_congratulations")->setString(UIUtils::getStringByName("100111"));
    //FIND_NODE(Text *,node,"text_guankan")->setString(UIUtils::getStringByName("100135"));
    getNode<Text*>("Text_share")->setString(Lang("100119"));
    getNode<Text*>("Text_PingJia")->setString(Lang("100273"));
    getNode<Text*>("text_rank")->setString(Lang("100121"));
    getNode<Text*>("text_look")->setString(Lang("100326"));
    auto text_new = FIND_NODE(Text *,node,"text_new"); // 大厅
    text_new->setString(UIUtils::getStringByName("100205"));
    UIUtils::textAdaptiveSize(text_new,360);

    auto text_lobby = FIND_NODE(Text *,node,"text_lobby");
    text_lobby->setString(UIUtils::getStringByName("100199")); // 新游戏
    UIUtils::textAdaptiveSize(text_new,720);
    //                                            Technologiepreise Ek ödüller
    auto Text_jishu = getNode<Text*>("Text_jishu");
    Text_jishu->setString(Lang("100334"));
    UIUtils::textAdaptiveSize(Text_jishu,190);
    getNode<Text*>("Text_jiben")->setString(Lang("100333"));
}
void WinLayer::showAction(int score, float time, int moveNum, int extraScore, int totalStar)
{
    //判定经典模式前十局多倍奖励 是否启用视频
    auto num = ScoreManager::getInstance()->getWinTotalCNT();
    isAds = true;//num > GAMENOADSCNT;
    //胜利的前两局大厅与奖励按钮隐藏
    auto winNum = ScoreManager::getInstance()->getWinTotalCNT(true);
    //getNode("btn_new")->setVisible(winNum > 2);
    //getNode("Button_doubleWin")->setVisible(winNum > 2);
    auto gameView = SCENE_M->getGameView();
    
    //没有引导
    isGuide = false;
    //进度条不动
    isBar = false;
    starNum = 1;
    isShowStar = true;
    
    string percent{"75%"};
    switch (totalStar) {
        case 2:
            percent = StringUtils::format("%d%%", random(80, 90));
            break;
        case 3:
            if (time<90)
                percent = StringUtils::format("%d%%", 99);
            else
                percent = StringUtils::format("%d%%", random(90, 98));
            break;
        default:
            break;
    }
    Text_modeformat->setString(Lang_1("100110", percent.c_str()));
//    Text_percent->setString(percent);
    
    //随机生成奖励倍数
    auto rand = random(1, 100);
    if(rand <= 35)
    {
        multipleNum = 2;
    }
    else if(rand <= 70)
    {
        multipleNum = 3;
    }
    else if(rand <= 90)
    {
        multipleNum = 4;
    }
    else if(rand <= 100)
    {
        multipleNum = 5;
    }
    
    if(TEACH_M->isTeaching("win_times1") || TEACH_M->isTeaching("win_times2"))
    {
        multipleNum = 2;
    }
    
    //经验条
    auto player = PlayerManager::getInstance();
    //Text_lv->setString(StringUtils::format("Lv %d",player->getLevel()));
    auto percent22 = player->getPercent();
    loadingBar_percent->setPercent(percent22);
    
    //isAds 前十局无视频
    auto button = FIND_NODE(Button*, this, "Button_doubleWin");
    
    auto sprite = FIND_NODE(Node*, button, "ui_Videoplayer_1");
    button->setEnabled(!isAds || TEACH_M->isTeaching("win_times1") || DATA_M->getHaveVideo());
    isButton = false;
    isBtnAni = false;//每次只播放一次btnAni
    fangCuoTime = 0;
    isTouch = true;
    if(!GUIDE_M->isEnd(FishGuideManager::GuideType::WinOne))
    {
        isTouch = false;
    }
    //动画防错，动画回调改为动作回调 获取动画运行多少帧getEndFrame()//起始帧为0
    playAni("Start", false);
    auto startFrame = _actionManager->getStartFrame();
    auto endFrame = _actionManager->getEndFrame();
    //所需时间
    float actionTime = 1.0f/60.0f * (endFrame-startFrame);
    auto delay = DelayTime::create(actionTime);
    auto func = CallFunc::create([this,sprite,gameView,button,winNum](){
        if(!isButton)
        {
            isButton = true;
            auto cb = [this,sprite,button,winNum](){
                if(!isBtnAni)
                {
                    isBtnAni =  true;
                    
                    if(!GUIDE_M->isEnd(FishGuideManager::GuideType::WinOne))
                    {
                        
                        auto buttonPoi = button->getPosition();
                        auto scale = getNode("panel_win")->getScale();
                        buttonPoi = button->getParent()->convertToWorldSpace(buttonPoi);
                        GUIDE_M->startGuide(FishGuideManager::GuideType::WinOne,this,buttonPoi,scale);
                        isTouch = true;
                        
                        button->setVisible(true);
                        button->setEnabled(true);
                        isGuide = true;
                        multipleNum = 4;
                        sprite->setVisible(false);
                        BitmapFontLabel_doubleCoin->setString(StringUtils::format("x%d",multipleNum));
                    }
                    else if(winNum == 2)
                    {
                        isGuide = true;
                        multipleNum = 2;
                        button->setEnabled(true);
                        sprite->setVisible(false);
                        BitmapFontLabel_doubleCoin->setString(StringUtils::format("x%d",multipleNum));
                    }
                    else
                    {
                        sprite->setVisible(isAds);
                    }
                    playAni("Btn", false);
                    
                    
                    
                    // teach 教学
                    if (TEACH_M->isTeaching("win_times1")) {
                        TEACH_M->nextTeachStep(this); // 引导点击双倍
                        this->getNode("ui_Videoplayer_1")->setVisible(false);
                    }
                    else if(!isGuide){
                        this->getNode("ui_Videoplayer_1")->setVisible(true);
                    }
                    //触发防错时
                    _InterstitialCB = nullptr;
                }
            };
            DATA_M->delayPlayBtn(cb);//防错延时动作 3s 后 没有成功播放插屏 主动播放btn帧动画
            //是否允许插屏
            auto isPlayAds = DATA_M->getLimit();
            auto faildNum = gameView->getFaildNum();
            //失败第一次不给插屏
            bool isFaild = faildNum != 1;
            auto adKey = DATA_M->isDailyMode()?"WinLayerDailyHD":"WinLayer";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            if(!TEACH_M->isTeaching("win_times1") && isPlayAds && isFaild && DATA_M->showNativeAds(2, adKey))
            {
                AdsManager::waitWinAction = true;
                _InterstitialCB = cb;
                if (!TEACH_M->isDailyLevelUnlock())
                    UIUtils::FIRAnalyticsEventWithPrefix("showInterstitial_ad_" +  TEACH_M->getCurrentTeachKey(), "teach");
            }
            else
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            bool flagTeach = !TEACH_M->isTeaching("win_times1");
            if (flagTeach && isPlayAds && isFaild) {
                DATA_M->showNativeAds(2, adKey);
            }
            // 添加打点记录
            int limitTime = DATA_M->getInterstitialTime();
            bool isVip = DATA_M->isVipNoAds();
            UIUtils::FIRFirestoreAddOP("winlayer_show", toString(flagTeach), toString(isPlayAds), toString(limitTime), toString(isFaild), toString(faildNum), toString(isVip));
            UIUtils::FIRAnalyticsEvent("winlayer_show", {
                    {"teach", Value(flagTeach)},
                    {"limit", Value(limitTime)},
                    {"faild", Value(faildNum)},
                    {"isVip", Value(isVip)},
            });
#endif
            {
                DATA_M->stopDelayPlayBtn();
                cb();
                if (!TEACH_M->isDailyLevelUnlock())
                    UIUtils::FIRAnalyticsEventWithPrefix("showInterstitial_no_" + TEACH_M->getCurrentTeachKey(), "teach");
            }
        }
    });
    auto seq = Sequence::createWithTwoActions(delay,func);
    this->runAction(seq);
    
    
    
    
    
    BitmapFontLabel_doubleCoin->setString(StringUtils::format("x%d",multipleNum));//multipleNum==0||isMultiple?7:5));
    SOUND_M->playEffectMusic(EffectVictory);
    for (int i=1; i<=3; ++i) {
        auto node = FIND_NODE(Node*, this, StringUtils::format("FileNode_star%d", i));
        if (node)
            node->setVisible(i==1);//node->setVisible(i<=totalStar);
    }

    auto showNew = [this](int gameType, ScoreManager::Type type, int idx) {
        auto panel = FIND_NODE(Node*, this, StringUtils::format("panel_%d", idx));
        if (panel) {
            if (panel->getChildByName("GradeNew"))
            {
                panel->removeChildByName("GradeNew");
            }
            if (ScoreManager::getInstance()->isNewRecordAndMinus(gameType, type)) {
                
                auto grade = UIUtils::createCSBNode("Grade.csb", "Loop", true);
                grade->setName("GradeNew");
                grade->getChildByName<Text*>("N")->setString("N");
                grade->getChildByName<Text*>("E")->setString("E");
                grade->getChildByName<Text*>("W")->setString("W");
                panel->addChild(grade);
                auto size = panel->getContentSize();
                grade->setPosition(size.width, size.height/2);
            }
        }
    };

    auto gameType = SPRITE_M->isThreeModel?2:1;
    auto scoreManager = ScoreManager::getInstance();
	
	long nextTime = time;
	int min = nextTime / 60;
	int sec = nextTime % 60;
    atlasLabel_you_time->setString(CCString::createWithFormat("%02d:%02d", min, sec)->getCString());
	atlasLabel_you_movetime->setString(toString(moveNum));


	int totalScore = score+extraScore;
    totalScore = totalScore / 10;
	text_you_TotalScore->setString(StringUtils::toString(totalScore));
	text_best_TotalScore->setString(StringUtils::toString(scoreManager->getScore(gameType, ScoreManager::Type::TOTALSCORE)));
	showNew(gameType, ScoreManager::Type::TOTALSCORE, 6);

    //额外金币（（120000/时间+步数+得分）/100 小数点四舍五入取整）
    
    _extraCoinNum = std::round((400000/time + moveNum + score)/1000);
    if(gameView->getIsCeShiWin())
    {
        _extraCoinNum = 100;
    }
    auto coinNum1 = WINLAYER_COIN;
    auto coinNum2 = _extraCoinNum;
    if(DATA_M->isDailyMode())
    {
        auto dailyManager = DailyManager::getInstance();
        auto date = dailyManager->getCurrentDate();
        auto mode = dailyManager->getCurrentMode();
        auto completed = dailyManager->isDailyCompleted(date, mode);
        if(!completed)
        {
            
        }
        else
        {
            coinNum1 /= 2;
            coinNum2 /= 2;
            if(coinNum2 < 1) coinNum2 = 1;
        }
    }
    _coinNum = coinNum1 + coinNum2;
    
	//DATA_M->setCoinNum(coinNum);
	SCENE_M->refushShopScene();
    atlasLabel_coinnum->setString("0");
    atlasLabel_coinnum->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([this](){
        auto grouwup = GrowupNode::create();
        atlasLabel_coinnum->addChild(grouwup);
        grouwup->startGrouwup(atlasLabel_coinnum, 0, _coinNum, 2.5, "",[this, grouwup](){
            UIUtils::playInnerAction(FileNode_gold, "jump", false);
            grouwup->removeFromParent();
        });
        UIUtils::playInnerAction(FileNode_gold, "loop", true);
    }), NULL));
    
    atlasLabel_coinnum_0->setString("+" + StringUtils::toString(coinNum2));
    atlasLabel_coinnum_0_0->setString("+" + StringUtils::toString(coinNum1));
//    atlasLabel_coinnum_0->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([this](){
//        auto grouwup = GrowupNode::create();
//        atlasLabel_coinnum_0->addChild(grouwup);
//        grouwup->startGrouwup(atlasLabel_coinnum_0, 0, _extraCoinNum, 2.5, "+",[this, grouwup](){
//            grouwup->removeFromParent();
//        });
//    }), NULL));
//    atlasLabel_zuanShiNum->setString("0");
//    atlasLabel_zuanShiNum->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([this](){
//        auto grouwup = GrowupNode::create();
//        atlasLabel_zuanShiNum->addChild(grouwup);
//        grouwup->startGrouwup(atlasLabel_zuanShiNum, 0, WINLAYER_DIAMOND, 2.5, [this, grouwup](){
//            //UIUtils::playInnerAction(FileNode_gold, "jump", false);
//            grouwup->removeFromParent();
//        });
//        //UIUtils::playInnerAction(FileNode_gold, "loop", true);
//    }), NULL));

//    atlasLabel_you_score->setString(toString(score));
//    atlasLabel_best_score->setString(toString(scoreManager->getScore(gameType, ScoreManager::Type::BESTSCORE)));

	int bestTime = scoreManager->getScore(gameType, ScoreManager::Type::BESTWINTIME);
	min = bestTime / 60;
	sec = bestTime % 60;
    atlasLabel_best_time->setString(CCString::createWithFormat("%02d:%02d", min, sec)->getCString());
	atlasLabel_best_movetime->setString(toString(scoreManager->getScore(gameType, ScoreManager::Type::WINMINMOVES)));
	showNew(gameType, ScoreManager::Type::BESTWINTIME, 3);
	showNew(gameType, ScoreManager::Type::WINMINMOVES, 4);
    
    // 设置没领取过
    DATA_M->setLingQu(false);
    
    //排名
    updateRank();
    
    string eventName{"gameWin"};
    if (!TEACH_M->isDailyLevelUnlock())
        UIUtils::FIRAnalyticsEventWithPrefix(eventName + "_" + TEACH_M->getCurrentTeachKey(), "teach");
    else
        UIUtils::FIRAnalyticsEventWithPrefix(eventName);
}

void WinLayer::dealButtonClick(Ref * pSender)
{
    if(!isTouch)
    {
        return;
    }
	auto dealBtn = dynamic_cast<Widget *>(pSender);
	auto btnName = dealBtn->getName();

    if (dynamic_cast<Button*>(pSender))
        SOUND_M->playBtnClickAudio();

	if ("btn_new" == btnName)
	{
        auto opaciity = getNode("btn_new")->getOpacity();
        if(opaciity > 200)
        {
            bool isTeaching = TEACH_M->isTeaching();
            TEACH_M->nextTeachStep(); // 新手
            //回到大厅
            auto cb = [this](){
                auto lobby = SCENE_M->getLobby();
                lobby->setVisible(true);
                lobby->resetHome();
                lobby->updateExp();
                
                SCENE_M->getGameView()->setVisible(false);
                //lobby->dailyShowComplete();
                auto poi = getContentSize()*0.5;
                lobby->goldAni(_coinNum,nullptr,poi,[this,lobby](){
                    //更新有金币显示
                    DATA_M->setCoinNum(_coinNum, true, 101);
                    ValueMap valueMap{
                        {"isTime",Value{true}}
                    };
                    //更新有金币显示
                    EVENT_M->sendEvent("event_game_update_coin",valueMap);
                    //SCENE_M->getLobby()->updateCoin(1);
                    
                },[lobby](){
                    //home
                    //SOUND_M->playEffectMusic(EffectGetCoin);
                    lobby->playGoldAni(1,true);
                },[lobby,this](){
                    if(isShowStar)
                    {
                        isShowStar = false;
                        
                    }
                    //SOUND_M->playEffectMusic(EffectGetCoin);
                    lobby->playGoldAni(1,false);
                });
//                poi.width+=160;
//                lobby->diamondAni(WINLAYER_DIAMOND,nullptr,poi,[this,lobby](){
//                    //更新有金币显示
//                    DATA_M->setDiamond(WINLAYER_DIAMOND);
//                    ValueMap valueMap{
//                        {"isTime",Value{true}}
//                    };
//                    //更新有金币显示
//                    EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//                    //SCENE_M->getLobby()->updateDiamond(1);
//
//                },[lobby](){
//                    //home
//                    //SOUND_M->playEffectMusic(EffectGetGem);
//                    lobby->playDiamondAni(1,true);
//                },[lobby](){
//                    //home
//                    //SOUND_M->playEffectMusic(EffectGetGem);
//                    lobby->playDiamondAni(1,false);
//                });
                //同时生成但延时出现
                lobby->starAni(starNum,"start1");
                
                // 记录app启动次数
                auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
                cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
                DATA_M->setAppStartCNT(startCNT);
                UIUtils::requestReview();
                
            };
            auto cb2 = [this](){
                //如果触发七倍并领取 则用这个
                auto lobby = SCENE_M->getLobby();
                lobby->setVisible(true);
                lobby->resetHome();
                lobby->updateExp();
                SCENE_M->getGameView()->setVisible(false);
                //同时生成但延时出现
                lobby->starAni(starNum,"start1");
                
                // 记录app启动次数
                auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
                cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
                DATA_M->setAppStartCNT(startCNT);
                UIUtils::requestReview();
            };
            //2021年4月1日 此版本关闭7倍奖励弹窗
//            auto rand = random(1, 100);
//            if((isTeaching&&DATA_M->getHaveVideo()) || // 教学必须有这个//必须有视频填充
//               (multipleNum == 2&&DATA_M->getHaveVideo()&&rand <= 10))
//            {
//                tempMultipleNum = 0;
//                SCENE_M->addDialog(MultipleRewardView::createLayerN(cb,cb2,isTeaching));
//                if (isTeaching)
//                    UIUtils::FIRAnalyticsEventWithPrefix("7xReward", "teach");
//            }
//            else
//            {
                cb();
//            }
            tempMultipleNum = multipleNum;
            setVisible(false);
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("WinLayer")},
                {"value", Value("no")},
                {"v1", Value(DATA_M->getHaveVideo())}
            });
            UIUtils::FIRAnalyticsEvent("win_btn_lobby", {});
        }
//        SCENE_M->removeLayer(this);
        
	}
    else if ("Button_doubleWin" == btnName)
    {
        if (TEACH_M->isTeaching("win_times1")||isGuide) {
            //DATA_M->lingqujinbi(_coinNum*=5);
            getVideoReward(nullptr);
            UIUtils::FIRAnalyticsEventWithPrefix("clickDouble", "teach");
        }
        else {
            TEACH_M->nextTeachStep(); // 新手
            if(isAds)
            {
                DATA_M->playVideoAds(DATA_M->isDailyMode()?9:8, 0);
                UIUtils::FIRFirestoreAdd("operator", {
                    {"key", Value("WinLayer")},
                    {"value", Value("ad")},
                    {"v1", Value(multipleNum)},
                });
            }
            else
            {//前十次无视频
                EVENT_M->sendEvent("event_game_winLayer");
            }
            
            FIND_NODE(Button*, this, "Button_doubleWin")->setEnabled(false);
        }
        UIUtils::FIRAnalyticsEvent("win_btn_double", {});
    }
    else if ("btn_lobby" == btnName) // 返回大厅
    {
        auto opaciity = getNode("btn_lobby")->getOpacity();
        if(opaciity > 200)
        {
            auto cb = [this](){
                auto gameView = SCENE_M->getGameView();
                auto lobby = SCENE_M->getLobby();
                lobby->dailyShowComplete();
                lobby->updateUI();//虽然没有回大厅，但是也刷新一下
                
                gameView->restartGame(false, DataManager::GameType::Huo, true);
                gameView->winAnimation(_coinNum);

                
            };
            auto cb2 = [this](){
                auto gameView = SCENE_M->getGameView();
                auto lobby = SCENE_M->getLobby();
                lobby->dailyShowComplete();
                lobby->updateUI();//虽然没有回大厅，但是也刷新一下
                
                gameView->restartGame(false, DataManager::GameType::Huo, true);
                gameView->winAnimation(_coinNum * 7);
            };
            auto rand = random(1, 100);
            if((multipleNum == 2&&DATA_M->getHaveVideo()&&rand <= 10))
            {
                //tempMultipleNum = 0;
                SCENE_M->addDialog(MultipleRewardView::createLayerN(cb,cb2,false,_coinNum));
                if (false)
                    UIUtils::FIRAnalyticsEventWithPrefix("7xReward", "teach");
            }
            else
            {
                cb();
            }
            this->setVisible(false);
            UIUtils::FIRAnalyticsEvent("win_btn_new", {});
        }
    }
    else if ("Button_share" == btnName)
    {//分享
        //分享不给金币了，禁止弹窗直接分享
        UIUtils::shareApp();
    }
    else if ("Button_look" == btnName)
    {//排行榜
//        GameKitHelper::showLeaderBoard();
        SCENE_M->addDialog(RankView::createLayerN(RankView::RankType::WinLayer));
    }
    else if ("Button_PingJia" == btnName)
    {//评价
        SCENE_M->addDialog(FeedBackView::createLayerN());
    }
}

void WinLayer::showPokersAction()
{
    for (int i=0;i<4;i++) {
        auto winSize = Director::getInstance()->getWinSize();
        auto cardSprite = Sprite::createWithSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(13, 0));
        cardSprite->schedule([cardSprite](float){
            auto newCard = Sprite::createWithSpriteFrame(cardSprite->getSpriteFrame());
            cardSprite->getParent()->addChild(newCard, 0);
            newCard->setPosition(cardSprite->getPosition());
            newCard->setOpacity(200);
            newCard->runAction(Sequence::create(FadeOut::create(1), RemoveSelf::create(), NULL));
        }, 1/10, "card_update");
        cardSprite->setName("CardSprite");
        cardSprite->setVisible(false);
        auto randx = cocos2d::random(0.f, winSize.width), randy = winSize.height-50;
        cardSprite->setPosition(randx, randy);
        this->addChild(cardSprite, 1);
        auto dir = randx>winSize.width/2?1:-1;
        Vec2 destPos(randx+dir*winSize.width/4, winSize.height/2);
        Vec2 destPos1(destPos.x+dir*winSize.width/4, 0);
        cardSprite->runAction(Sequence::create(DelayTime::create(cocos2d::random(0.f, 1.f)), Show::create()
                                               , BezierTo::create(2, {destPos, Vec2(destPos.x, randy*1.5), Vec2(destPos.x, randy*1.5)})
                                               , BezierTo::create(2, {destPos1, Vec2(destPos1.x, winSize.height), Vec2(destPos1.x, winSize.height)}), RemoveSelf::create(), NULL));
    }
}

WinLayer::WinLayer()
:BaseLayer("WinLayer.csb")
{
    isOneTeach = GETBOOL("isOneTeach",true);
    _excludeRecord = true; // 不要记录进入
    isMultiple = false;
}

void WinLayer::getVideoReward(EventCustom *eventCustom) {
//        SCENE_M->resetGame();
//        setVisible(false);
    auto gameView = SCENE_M->getGameView();
    
    auto lobby = SCENE_M->getLobby();
    lobby->dailyShowComplete();
    lobby->updateUI();//虽然没有回大厅，但是也刷新一下
    
    gameView->restartGame(false, DataManager::GameType::Huo, true);
    gameView->winAnimation(_coinNum * multipleNum);
    
    
    if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::WinOne)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::WinOne))
    {
        GUIDE_M->endGuide();
    }
    this->setVisible(false);
}

void WinLayer::onEnter()
{
    BaseLayer::onEnter();
}
void WinLayer::onExit()
{
    BaseLayer::onExit();
    EVENT_M->removeListener("event_game_winLayer",this);
    EVENT_M->removeListener("msg_game_showwin",this);
}

void WinLayer::updateRank()
{
    //排名
    auto gameView = SCENE_M->getGameView();
    int rank = gameView->getMyRank();
    atlasLabel_rank->setString(StringUtils::format("%d",rank));
}
