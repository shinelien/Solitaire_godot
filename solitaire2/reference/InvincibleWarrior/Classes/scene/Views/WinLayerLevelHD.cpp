
#include "WinLayerLevelHD.h"
#include "LevelManager.h"
#include "DataManager.h"
#include "GrowupNode.h"
#include "UIUtils.h"
#include "MultipleRewardView.h"
#include "RewardManager.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#endif
#include "EventObserver.h"
#include "FeedBackView.h"
#include "ShareRewardView.h"
#include "GameKitHelper.h"

void WinLayerLevelHD::initUI() {
    BaseLayer::initUI();
    doLayout();
    BitmapFontLabel_doubleCoin = getNode<TextBMFont*>("BitmapFontLabel_doubleCoin");
    atlasLabel_coinnum = getNode<TextBMFont*>("atlasLabel_coinnum");
    atlasLabel_zuanShiNum = getNode<TextBMFont*>("atlasLabel_zuanShiNum");
    atlasLabel_zuanShiNum->setVisible(false);
    FileNode_gold = UIUtils::createCSBNode("Animation/Node_gold.csb");
//    FileNode_zuanShi = UIUtils::createCSBNode("Animation/Node_currency.csb","Baoshi",false);
//    getNode("Node_zuanShi")->addChild(FileNode_zuanShi);
    getNode("Node_gold")->addChild(FileNode_gold);
    
    vector<string> strArr = {"C","O","N","G","R","A","T","U","L","A","T","I","O","N","S","!"};
    //文本
    for(int i = 0;i < strArr.size();++i)
    {
        auto text = getNode<Text*>(StringUtils::format("Text_14_%d",i));
        text->setString(strArr.at(i));
    }
    
    
    updateDYY();
}

void WinLayerLevelHD::initData() {
    BaseLayer::initData();
    setName("WinLayerLevelHD");
    EVENT_M->addListener("event_game_winLevelLayer", [this](ValueMap valueMap, void *obj){
        auto gameview = SCENE_M->getGameView();
        gameview->showLobby();
        
        auto lobby = SCENE_M->getLobby();
        lobby->updateExp();
        
        if(_isFirst||1)
        {
            lobby->goldAni(_coinNum *multipleNum, nullptr,Vec2(2000,2000),[this,lobby](){
                //更新金币显示
                DATA_M->setCoinNum(_coinNum *multipleNum, true);
                ValueMap valueMap{
                    {"isTime",Value{true}}
                };
                //更新有金币显示
                EVENT_M->sendEvent("event_game_update_coin",valueMap);
                //lobby->updateCoin(true);
            },[this,lobby](){
                //星星闪烁
                //SOUND_M->playEffectMusic(EffectGetCoin);
                lobby->playGoldAni(2,true);
            },[this,lobby](){
                //隐藏特效
                if(isShowStar)
                {
                    isShowStar = false;
                    
                }
                //SOUND_M->playEffectMusic(EffectGetCoin);
                lobby->playGoldAni(2,false);
            });
            
//            lobby->diamondAni(_diamondNum*multipleNum,nullptr,Vec2(2000,2000),[lobby,this](){
//                //更新金币显示
//                DATA_M->setDiamond(_diamondNum*multipleNum);
//                ValueMap valueMap{
//                    {"isTime",Value{true}}
//                };
//                //更新有金币显示
//                EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//                //lobby->updateDiamond(2);
//            },[this,lobby](){
//                //SOUND_M->playEffectMusic(EffectGetGem);
//                lobby->playDiamondAni(2,true);
//            },[this,lobby](){
//                //SOUND_M->playEffectMusic(EffectGetGem);
//                lobby->playDiamondAni(2,false);
//            });
            tempMultipleNum = multipleNum;
            if(_isFirst)
            {
                lobby->starAni(_star,"start1");
            }
            
            setVisible(false);
        }
        
        // 记录app启动次数
        auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
        cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
        DATA_M->setAppStartCNT(startCNT);
        UIUtils::requestReview();
    },this);
    
    EVENT_M->addListener("msg_game_showwin",[this](ValueMap valueMap, void *obj){
            if (_InterstitialCB) {
                _InterstitialCB();
                _InterstitialCB = nullptr;
            }
        },this);
//    addEvent("event_game_winLevelLayer", [this](EventCustom *eventCustom){
//        
//        
//    });
}

void WinLayerLevelHD::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
    if (btnName == "btn_next") {
        auto opaciity = getNode("btn_next")->getOpacity();
        if(opaciity > 200)
        {
            auto cb = [this](){
                auto gameview = SCENE_M->getGameView();
                gameview->showLobby();
                auto lobby = SCENE_M->getLobby();
                lobby->updateExp();
                if(_isFirst||1)
                {
                    lobby->goldAni(_coinNum , nullptr,Vec2(2000,2000),[this,lobby](){
                        //更新金币显示
                        DATA_M->setCoinNum(_coinNum, true);
                        ValueMap valueMap{
                            {"isTime",Value{true}}
                        };
                        //更新有金币显示
                        EVENT_M->sendEvent("event_game_update_coin",valueMap);
                        //lobby->updateCoin(true);
                    },[this,lobby](){
                        //星星闪烁
                        lobby->playGoldAni(2,true);
                    },[this,lobby](){
                        //隐藏特效
                        if(isShowStar)
                        {
                            isShowStar = false;
                            
                        }
                        lobby->playGoldAni(2,false);
                    });
                    
//                    lobby->diamondAni(_diamondNum,nullptr,Vec2(2000,2000),[lobby,this](){
//                        //更新金币显示
//                        DATA_M->setDiamond(_diamondNum);
//                        ValueMap valueMap{
//                            {"isTime",Value{true}}
//                        };
//                        //更新有金币显示
//                        EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//                        //lobby->updateDiamond(2);
//                    },[this,lobby](){
//                        //SOUND_M->playEffectMusic(EffectGetGem);
//                        lobby->playDiamondAni(2,true);
//                    },[this,lobby](){
//                        //SOUND_M->playEffectMusic(EffectGetGem);
//                        lobby->playDiamondAni(2,false);
//                    });
                }
                if(_isFirst)
                {
                    lobby->starAni(_star,"start1");
                }
                
                // 记录app启动次数
                auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
                cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
                DATA_M->setAppStartCNT(startCNT);
                UIUtils::requestReview();
       
            };
            auto cb2 = [this](){
                
                auto gameview = SCENE_M->getGameView();
                gameview->showLobby();
                auto lobby = SCENE_M->getLobby();
                lobby->updateExp();
                if(_isFirst)
                {
                    lobby->starAni(_star,"start1");
                }
                
                // 记录app启动次数
                auto startCNT = cocos2d::UserDefault::getInstance()->getIntegerForKey("app_start_cnt", 0);
                cocos2d::UserDefault::getInstance()->setIntegerForKey("app_start_cnt", ++startCNT);
                DATA_M->setAppStartCNT(startCNT);
                UIUtils::requestReview();
            };
            //2021年4月1日 此版本关闭7倍奖励弹窗
//            auto rand = random(1, 100);
//            if(multipleNum == 2&&DATA_M->getHaveVideo()&&_isFirst&&rand <= 10)
//            {
//                SCENE_M->addDialog(MultipleRewardView::createLayerN(cb,cb2));
//            }
//            else
//            {
                cb();
//            }
            tempMultipleNum = multipleNum;
            setVisible(false);
            UIUtils::FIRFirestoreAdd("operator", {
               {"key", Value("WinLayerLevel")},
               {"value", Value("no")},
               {"v1", Value(DATA_M->getHaveVideo())}
            });
        }
        
    }
    else if (btnName == "Button_back") {
        SCENE_M->showLevelComplete(_isWin, _levelData);
//        this->removeFromParent();
        setVisible(false);
        UIUtils::FIRFirestoreAdd("operator", {
           {"key", Value("WinLayerLevel")},
           {"value", Value("no")},
           {"v1", Value(DATA_M->getHaveVideo())}
        });
    }
    else if (btnName == "Button_doubleWin") {
        auto multiple = multipleNum==0||isMultiple?7:5;
        DATA_M->playVideoAds(12, /*(*_levelData)["reward"].GetInt()*/25 * multiple);
        btn->setEnabled(false);
        
        ValueMap valueMap;
        valueMap["getType"] = Value("video");
        UIUtils::FIRAnalyticsEvent("event_winlevellayer_video", valueMap);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("WinLayerLevel")},
            {"value", Value("ad")}
        });
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

WinLayerLevelHD::WinLayerLevelHD(bool isWin, std::shared_ptr<rapidjson::Document> levelData, bool isFirst, int star)
:BaseLayer("WinLayer_level.csb")
,_isWin(isWin)
,_levelData(levelData)
,_isFirst(isFirst)
,_star(star)
{
}

WinLayerLevelHD::~WinLayerLevelHD() {

}

WinLayerLevelHD::WinLayerLevelHD()
:BaseLayer("WinLayer_level.csb")
{
    _excludeRecord = true; // 不要记录进入
}

void WinLayerLevelHD::showAction(bool isWin, std::shared_ptr<rapidjson::Document> levelData, bool isFirst, int star) {
    
    isShowStar = true;
    _star = 3;
    _isFirst = isFirst;
    
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
    BitmapFontLabel_doubleCoin->setString(StringUtils::format("x%d",multipleNum));//multipleNum==0||isMultiple?7:5));
    
    _levelData = levelData;
    auto str = Lang_1("100112", (*levelData)["subShow"].GetInt());
    getNode<Text*>("Text_level")->setString(str);
    //auto rewardGold = 25;//(*levelData)["reward"].GetInt();
    atlasLabel_coinnum->setString("0");
    //atlasLabel_zuanShiNum->setString("0");
    
    
    
    
    if (isFirst) {
        //DATA_M->setCoinNum(rewardGold,false);
        //更新有金币显示
        _coinNum = WINLAYER_COIN;
        _diamondNum = WINLAYER_DIAMOND;
    }
    else
    {
        _coinNum = WINLAYER_COIN2;
        _diamondNum = WINLAYER_DIAMOND2;
    }
    
    atlasLabel_coinnum->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([this](){
        auto grouwup = GrowupNode::create();
        atlasLabel_coinnum->addChild(grouwup);
        grouwup->startGrouwup(atlasLabel_coinnum, 0, _coinNum, 2.5, "",[this,grouwup](){
            UIUtils::playInnerAction(FileNode_gold, "jump", false);
            grouwup->removeFromParent();
        });
        UIUtils::playInnerAction(FileNode_gold, "loop", true);
    }), NULL));
    
//    atlasLabel_zuanShiNum->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([this](){
//        auto grouwup = GrowupNode::create();
//        atlasLabel_zuanShiNum->addChild(grouwup);
//        grouwup->startGrouwup(atlasLabel_zuanShiNum, 0, _diamondNum, 2.5, [this,grouwup](){
//            //UIUtils::playInnerAction(FileNode_gold, "jump", false);
//            grouwup->removeFromParent();
//        });
//        //UIUtils::playInnerAction(FileNode_gold, "loop", true);
//    }), NULL));
    
    
    for (auto i=1;i<=3;i++) {
        getNode(StringUtils::format("FileNode_star%d", i))->setVisible(i<=star);
    }
    getNode<Button*>("Button_doubleWin")->setEnabled(DATA_M->getHaveVideo());//isFirst && 
    isButton = false;
    isBtnAni = false;//每次只播放一次btnAni
    //动画防错，动画回调改为动作回调 获取动画运行多少帧getEndFrame()//起始帧为0
    playAni("Start", false);
    auto startFrame = _actionManager->getStartFrame();
    auto endFrame = _actionManager->getEndFrame();
    //所需时间
    float actionTime = 1.0f/60.0f * (endFrame-startFrame);
    auto delay = DelayTime::create(actionTime);
//    auto func = CallFunc::create([this](){
//        if(!isButton)
//        {
//            isButton = true;
//            playAni("Btn", false);
//        }
//    });
    
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
            if(isPlayAds&&DATA_M->showNativeAds(2, "WinLayerLevelHD"))
            {
                AdsManager::waitWinAction = true;
                _InterstitialCB = cb;
            }
            else
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            if(isPlayAds)
            {
                DATA_M->showNativeAds(2, "WinLayerLevelHD");
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
    
    // 设置没领取过
    DATA_M->setLingQu(false);
    UIUtils::FIRAnalyticsEventWithPrefix("gameWinLevel");
}

void WinLayerLevelHD::updateDYY()
{
    getNode<Text*>("Text_congratulations")->setString(UIUtils::getStringByName("100111"));
    getNode<Text*>("text_get")->setString(UIUtils::getStringByName("100062"));
    //getNode<Text*>("text_guankan")->setString(UIUtils::getStringByName("100135"));
    auto text_next = getNode<Text*>("text_next");;
    text_next->setString(UIUtils::getStringByName("100136"));
    UIUtils::textAdaptiveSize(text_next,355);
    getNode<Text*>("Text_share")->setString(Lang("100119"));
    getNode<Text*>("Text_PingJia")->setString(Lang("100273"));
    getNode<Text*>("Text_rank")->setString(Lang("100121"));
}

void WinLayerLevelHD::onEnter()
{
    BaseLayer::onEnter();
}
void WinLayerLevelHD::onExit()
{
    BaseLayer::onExit();
    EVENT_M->removeListener("event_game_winLevelLayer",this);
}
