# include "WinLayerDailyHD.h"
#include "ScoreManager.h"
#include "GrowupNode.h"
#include "SpriteManager.h"
#include "DailyView.h"
#include "GameViewHD.hpp"
#include "DailyManager.h"
#include "MainLobby.h"
#include "PlayerManager.h"
#include "MultipleRewardView.h"
#include "RewardManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#endif
#include "EventObserver.h"
#include "FeedBackView.h"
#include "ShareRewardView.h"
#include "GameKitHelper.h"

Scene * WinLayerDailyHD::createScene()
{
	return UIUtils::createScene(WinLayerDailyHD::create());
}

WinLayerDailyHD * WinLayerDailyHD::createLayer()
{
    auto winLayer = WinLayerDailyHD::create();
    winLayer->setName("WinLayer");
    return winLayer;
}

WinLayerDailyHD * WinLayerDailyHD::createLayer(int score, float time, int moveNum, int extraScore, int totalStar)
{
	auto winLayer = WinLayerDailyHD::create();
	winLayer->setName("WinLayerDailyHD");
	winLayer->showAction(score,time,moveNum,extraScore,totalStar);
	return winLayer;
}

bool WinLayerDailyHD::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	return true;
}

void WinLayerDailyHD::initData()
{
    BaseLayer::initData();
    EVENT_M->addListener("event_game_winDailyLayer", [this](ValueMap valueMap, void *obj){
        auto lobby = SCENE_M->getLobby();
        lobby->setVisible(true);
        lobby->setTab(MainLobby::Tab::Daily);
        lobby->dailyShowComplete();
        lobby->updateExp();
        auto poi = getContentSize()*0.5;
        auto num = _coinNum*multipleNum;
        lobby->goldAni(_coinNum*multipleNum,nullptr,poi,[this,lobby,num](){
            //更新有金币显示
            DATA_M->setCoinNum(num, true);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            //SCENE_M->getLobby()->updateCoin(true);
            
        },[lobby](){
            //daily
            //SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni(2,true);
        },[lobby,this](){
            //daily
            if(isShowStar)
            {
                isShowStar = false;
                
            }
            //SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni(2,false);
        });
//        poi.width+=160;
//        auto diamond = _diamondNum*multipleNum;
//        lobby->diamondAni(_diamondNum*multipleNum,nullptr,poi,[this,lobby,diamond](){
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
//            //daily
//            //SOUND_M->playEffectMusic(EffectGetGem);
//            lobby->playDiamondAni(2,true);
//        },[lobby](){
//            //home
//            //SOUND_M->playEffectMusic(EffectGetGem);
//            lobby->playDiamondAni(2,false);
//        });
        if (!completed)
        {
            lobby->starAni(1,"start1");
        }
        SCENE_M->getGameView()->setVisible(false);
        this->setVisible(false);
        tempMultipleNum = multipleNum;
        
        // 记录app启动次数
        auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
        cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
        DATA_M->setAppStartCNT(startCNT);
        UIUtils::requestReview();
    },this);
//    addEvent("event_game_winDailyLayer", [this](EventCustom *eventCustom){
//
//        });
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

void WinLayerDailyHD::initUI()
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


    loadingBar_percent = getNode<LoadingBar*>("LoadingBar_percent");
    Text_lv = getNode<Text*>("Text_lv");
//    schedule([this](float dt){
//        if(isBar&&!completed&&0)
//        {
//            //定时器
//            if(lv == oldLv)
//            {//lv == oldLv从percent2涨到percent1
//                percent2+=percentDx;
//                if(percent2 > percent1)
//                {
//                    percent2 = percent1;
//                    isBar = false;
//                }
//                loadingBar_percent->setPercent(percent2);
//            }
//            else if(lv > oldLv)
//            {// lv > oldLv 从percent2涨到100;再从0涨到percent1
//                percent2+=percentDx;
//                
//                if(percent2 > 100)
//                {
//                    percent2 = 0;
//                    isQieHuan = true;
//                    auto player = PlayerManager::getInstance();
//                    Text_lv->setString(StringUtils::format("Lv %d",player->getLevel()));
//                }
//                else if(percent2 > percent1&&isQieHuan)
//                {
//                    percent2 = percent1;
//                    isBar = false;
//                    isQieHuan = false;
//                }
//                loadingBar_percent->setPercent(percent2);
//            }
//        }
//    }, 0.05, "scheduler_update_bar");


	INIT_BTN(node,"btn_next", CC_CALLBACK_1(WinLayerDailyHD::dealButtonClick, this));
    INIT_BTN(node,"Button_doubleWin", CC_CALLBACK_1(WinLayerDailyHD::dealButtonClick, this));
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
//    FileNode_zuanShi = UIUtils::createCSBNode("Animation/Node_currency.csb","Baoshi",false);
//    getNode("Node_zuanShi")->addChild(FileNode_zuanShi);
    FIND_NODE(Node*, node, "Node_gold")->addChild(FileNode_gold);
//    atlasLabel_you_score = FIND_NODE(TextBMFont *, node, "atlasLabel_you_score");
//    atlasLabel_best_score = FIND_NODE(TextBMFont *, node, "atlasLabel_best_score");
	atlasLabel_you_time = FIND_NODE(TextBMFont *, node, "atlasLabel_you_time");
	atlasLabel_best_time = FIND_NODE(TextBMFont *, node, "atlasLabel_best_time");
	atlasLabel_you_movetime = FIND_NODE(TextBMFont *, node, "atlasLabel_you_movetime");
	atlasLabel_best_movetime = FIND_NODE(TextBMFont *, node, "atlasLabel_best_movetime");
	atlasLabel_coinnum = FIND_NODE(TextBMFont *, node, "atlasLabel_coinnum");
    atlasLabel_zuanShiNum = getNode<TextBMFont*>("atlasLabel_zuanShiNum");
    atlasLabel_zuanShiNum->setVisible(false);
//    FileNode_gold = FIND_NODE(Node *, node, "FileNode_gold");
    Text_modeformat = FIND_NODE(Text *, node, "Text_modeformat");
    Text_percent = FIND_NODE(Text *, node, "Text_percent");
    BitmapFontLabel_doubleCoin = getNode<TextBMFont*>("BitmapFontLabel_doubleCoin");

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

void WinLayerDailyHD::updateDYY()
{
    auto node = _rootNode;
    FIND_NODE(Text *,node,"text_ni")->setString(UIUtils::getStringByName("100057"));

//    FIND_NODE(Text *,node,"text_zuijia")->setString(UIUtils::getStringByName("100058"));
    FIND_NODE(Text *,node,"text_totalscore")->setString(UIUtils::getStringByName("100042"));
    FIND_NODE(Text *,node,"text_time")->setString(UIUtils::getStringByName("100060"));
    auto text_movetime = FIND_NODE(Text *,node,"text_movetime");
    text_movetime->setString(UIUtils::getStringByName("100061"));
    UIUtils::textAdaptiveSize(text_movetime,290);
    FIND_NODE(Text *,node,"text_get")->setString(UIUtils::getStringByName("100062"));
    auto text_new = FIND_NODE(Text *,node,"text_next");
    text_new->setString(UIUtils::getStringByName("100063"));
    UIUtils::textAdaptiveSize(text_new,360);
    FIND_NODE(Text *,node,"Text_congratulations")->setString(UIUtils::getStringByName("100111"));
//FIND_NODE(Text *,node,"text_guankan")->setString(UIUtils::getStringByName("100135"));
    getNode<Text*>("Text_share")->setString(Lang("100119"));
    getNode<Text*>("Text_PingJia")->setString(Lang("100273"));
    getNode<Text*>("Text_rank")->setString(Lang("100121"));
}

void WinLayerDailyHD::showAction(int score, float time, int moveNum, int extraScore, int totalStar)
{
    //判定经典模式前十局多倍奖励 是否启用视频
    auto num = ScoreManager::getInstance()->getWinTotalCNT();
    isAds = num > GAMENOADSCNT;
    
    isShowStar = true;
    starNum = totalStar;
    //进度条不动
    isBar = false;
    isButton = false;
    isBtnAni = false;//每次只播放一次btnAni
    fangCuoTime = 0;
    //动画防错，动画回调改为动作回调 获取动画运行多少帧getEndFrame()//起始帧为0
    playAni("Start", false);
    auto startFrame = _actionManager->getStartFrame();
    auto endFrame = _actionManager->getEndFrame();
    //所需时间
    float actionTime = 1.0f/60.0f * (endFrame-startFrame);
    auto delay = DelayTime::create(actionTime);
    auto func = CallFunc::create([this](){
        if(!isButton)
        {
            isButton = true;
            auto cb = [this](){
                if(!isBtnAni)
                {
                    isBtnAni = true;
                    playAni("Btn", false);
                    //触发防错时
                    _InterstitialCB = nullptr;
                }
            };
            DATA_M->delayPlayBtn(cb);//防错延时动作 3s 后 没有成功播放插屏 主动播放btn帧动画
            //是否允许插屏
            auto isPlayAds = DATA_M->getLimit();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            if(isPlayAds && DATA_M->showNativeAds(2, "WinLayerDailyHD"))
            {
                AdsManager::waitWinAction = true;
                _InterstitialCB = cb;
            }
            else
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            if(isPlayAds)
            {
                DATA_M->showNativeAds(2, "WinLayerDailyHD");
            }
#endif
            {
                DATA_M->stopDelayPlayBtn();
                cb();
            }
        }
    });
    auto seq = Sequence::createWithTwoActions(delay,func);
    this->runAction(seq);
    
    
    SOUND_M->playEffectMusic(EffectVictory);
//    for (int i=1; i<=3; ++i) {
//        auto node = FIND_NODE(Node*, this, StringUtils::format("FileNode_star%d", i));
//        if (node)
//            node->setVisible(i<=totalStar);
//    }
    
    //随机生成奖励倍数
    auto rand = random(1, 1000);
    if(rand <= 450)
    {
        multipleNum = 2;
    }
    else if(rand <= 830)
    {
        multipleNum = 3;
    }
    else if(rand <= 950)
    {
        multipleNum = 5;
    }
    else if(rand <= 1000)
    {
        multipleNum = 7;
    }

    auto gameType = SPRITE_M->isThreeModel?2:1;
	
	long nextTime = time;
	int min = nextTime / 60;
	int sec = nextTime % 60;
    atlasLabel_you_time->setString(CCString::createWithFormat("%02d:%02d", min, sec)->getCString());
	atlasLabel_you_movetime->setString(toString(moveNum));

	int totalScore = score+extraScore;
	text_you_TotalScore->setString(StringUtils::toString(totalScore));
    
    //经验条
    auto player = PlayerManager::getInstance();
    //Text_lv->setString(StringUtils::format("Lv %d",player->getLevel()));
    
    
    
    BitmapFontLabel_doubleCoin->setString(StringUtils::format("x%d",multipleNum));//multipleNum==0||isMultiple?7:5));

    auto dailyManager = DailyManager::getInstance();
    auto date = dailyManager->getCurrentDate();
    auto mode = dailyManager->getCurrentMode();
    completed = dailyManager->isDailyCompleted(date, mode);
    auto completeCNT = dailyManager->getCompleteCNT(date);
    
    //isAds 前十局无视频
    FIND_NODE(Node*, this, "ui_Videoplayer_1")->setVisible(isAds);
    FIND_NODE(Button*, this, "Button_doubleWin")->setEnabled(!isAds || DATA_M->getHaveVideo());//!completed &&
    if (!completed) {
        //经验条
        //auto exp = (score+extraScore) / 100; //PlayerManager::getInstance()->getExp()+1;
        //auto levelUp = player->addExp(exp);//已经获得过经验了
        int coinNum = WINLAYER_COIN;//(int)(100000 / 2 / time);
        _coinNum = coinNum;
        _diamondNum = WINLAYER_DIAMOND;
        //DATA_M->setCoinNum(coinNum);
        SCENE_M->refushShopScene();
        completeCNT = MIN(completeCNT+1, 3);
    }
    else {
        _coinNum = WINLAYER_COIN2;
        _diamondNum = WINLAYER_DIAMOND2;
    }
    
    for (int i=1; i<=3; i++) {
        if (i==1) {
            getNode(StringUtils::format("Node_crownGem%d", i))->setVisible(completeCNT>1);
        }
        else {
            getNode(StringUtils::format("Node_crownGem%d", i))->setVisible(completeCNT>=3);
        }
    }
    
    atlasLabel_coinnum->setString("0");
    atlasLabel_coinnum->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([this](){
        auto grouwup = GrowupNode::create();
        atlasLabel_coinnum->addChild(grouwup);
        grouwup->startGrouwup(atlasLabel_coinnum, 0, _coinNum, 2.5, "",[this, grouwup](){
            UIUtils::playInnerAction(FileNode_gold, "jump", false);
            grouwup->removeFromParent();
        });
        UIUtils::playInnerAction(FileNode_gold, "loop", true);
    }), NULL));
    
//    atlasLabel_zuanShiNum->setString("0");
//    atlasLabel_zuanShiNum->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([this](){
//        auto grouwup = GrowupNode::create();
//        atlasLabel_zuanShiNum->addChild(grouwup);
//        grouwup->startGrouwup(atlasLabel_zuanShiNum, 0, _diamondNum, 2.5, [this, grouwup](){
//            //UIUtils::playInnerAction(FileNode_gold, "jump", false);
//            grouwup->removeFromParent();
//        });
//        //UIUtils::playInnerAction(FileNode_gold, "loop", true);
//    }), NULL));
    
    UIUtils::FIRAnalyticsEventWithPrefix("gameWinDaily");
}

void WinLayerDailyHD::dealButtonClick(Ref * pSender)
{
	auto dealBtn = dynamic_cast<Widget *>(pSender);
	auto btnName = dealBtn->getName();

    if (dynamic_cast<Button*>(pSender))
        SOUND_M->playBtnClickAudio();

	if ("btn_next" == btnName)
	{
        auto opaciity = getNode("btn_next")->getOpacity();
        if(opaciity > 200)
        {
            auto cb = [this](){
                
                auto lobby = SCENE_M->getLobby();
                lobby->setVisible(true);
                lobby->setTab(MainLobby::Tab::Daily);
                lobby->updateExp();
                
                lobby->dailyShowComplete();
                if(!completed||1)
                {
                    auto poi = getContentSize()*0.5;
                    lobby->goldAni(_coinNum,nullptr,poi,[this,lobby](){
                        //更新有金币显示
                        DATA_M->setCoinNum(_coinNum, true);
                        ValueMap valueMap{
                            {"isTime",Value{true}}
                        };
                        //更新有金币显示
                        EVENT_M->sendEvent("event_game_update_coin",valueMap);
                        //SCENE_M->getLobby()->updateCoin(true);
                    },[lobby](){
                        //home
                        //SOUND_M->playEffectMusic(EffectGetCoin);
                        lobby->playGoldAni(2,true);
                    },[lobby,this](){
                        //daily
                        if(isShowStar)
                        {
                            isShowStar = false;
                            
                        }
                        //SOUND_M->playEffectMusic(EffectGetCoin);
                        lobby->playGoldAni(2,false);
                    });
//                    poi.width+=160;
//                    lobby->diamondAni(_diamondNum,nullptr,poi,[this,lobby](){
//                        //更新有金币显示
//                        DATA_M->setDiamond(_diamondNum);
//                        ValueMap valueMap{
//                            {"isTime",Value{true}}
//                        };
//                        //更新有金币显示
//                        EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//                        //SCENE_M->getLobby()->updateDiamond(2);
//
//                    },[lobby](){
//                        //daily
//                        //SOUND_M->playEffectMusic(EffectGetGem);
//                        lobby->playDiamondAni(2,true);
//                    },[lobby](){
//                        //daily
//
//                        //SOUND_M->playEffectMusic(EffectGetGem);
//                        lobby->playDiamondAni(2,false);
//                    });
                    if (!completed)
                    {
                        lobby->starAni(1,"start1");
                    }
                    
                }
            
                SCENE_M->getGameView()->setVisible(false);
                
                // 记录app启动次数
                auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
                cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
                DATA_M->setAppStartCNT(startCNT);
                UIUtils::requestReview();
            };
            
//            auto cb2 = [this](){
//                auto lobby = SCENE_M->getLobby();
//                lobby->setVisible(true);
//                lobby->setTab(MainLobby::Tab::Daily);
//                lobby->updateExp();
//                lobby->dailyShowComplete();
//                SCENE_M->getGameView()->setVisible(false);
//                if (!completed)
//                {
//                    lobby->starAni(1,"Crown");
//                }
//                // 记录app启动次数
//                auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
//                cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
//                DATA_M->setAppStartCNT(startCNT);
//                UIUtils::requestReview();
//            };
            //2021年4月1日 此版本关闭7倍奖励弹窗
//            auto rand = random(1, 100);
//            if(multipleNum == 2&&DATA_M->getHaveVideo()&&!completed&&rand <= 10)
//            {
//                tempMultipleNum = 0;
//                SCENE_M->addDialog(MultipleRewardView::createLayerN(cb,cb2));
//            }
//            else
//            {
                cb();
//            }
            tempMultipleNum = multipleNum;
            setVisible(false);
            
            //SCENE_M->addDialog(DailyView::createLayerN()->showComplete(), true);
            //SCENE_M->getGameView()->showStartTips();
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("WinLayerDaily")},
                {"value", Value("no")},
                {"v1", Value(DATA_M->getHaveVideo())}
            });
        }
        
	}
    else if ("Button_doubleWin" == btnName)
    {
        if(isAds)
        {
            auto multiple = multipleNum==0||isMultiple?7:5;
            DATA_M->playVideoAds(9, _coinNum*multiple);
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("WinLayerDaily")},
                {"value", Value("ad")}
            });
        }
        else
        {//前十次无视频
            EVENT_M->sendEvent("event_game_winDailyLayer");
        }
        
        FIND_NODE(Button*, this, "Button_doubleWin")->setEnabled(false);
    }
    else if ("Button_share" == btnName)
    {//分享
        //分享不给金币了，禁止弹窗直接分享
        UIUtils::shareApp();
    }
    else if ("Button_rank" == btnName)
    {//排行榜
        GameKitHelper::showLeaderBoard();
    }
    else if ("Button_PingJia" == btnName)
    {//评价
        SCENE_M->addDialog(FeedBackView::createLayerN());
    }
}

WinLayerDailyHD::WinLayerDailyHD()
:BaseLayer("WinLayer_Challenge.csb")
{
    _excludeRecord = true; // 不要记录进入
}


void WinLayerDailyHD::onEnter()
{
    BaseLayer::onEnter();
}
void WinLayerDailyHD::onExit()
{
    BaseLayer::onExit();
    EVENT_M->removeListener("event_game_winDailyLayer",this);
    EVENT_M->removeListener("msg_game_showwin",this);
}
