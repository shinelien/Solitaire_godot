# include "FreeCoinLayer.h"
#include "MainLobby.h"
#include "EventObserver.h"
#include "TaskManager.h"
#include "GameViewHD.hpp"
#include "RewardManager.h"
#include "BagView.h"
Scene * FreeCoinLayer::createScene()
{
    return nullptr;//UIUtils::createScene(FreeCoinLayer::create());
}

FreeCoinLayer * FreeCoinLayer::createLayer()
{
	auto freeCoinLayer = FreeCoinLayer::createLayerN(FreeCoinLayer::Type::Gold);
	freeCoinLayer->setName("FreeCoinLayer");
	return freeCoinLayer;
}

bool FreeCoinLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	UIUtils::showDialog(panel_freecoin, "img_freecoin");
	return true;
}

void FreeCoinLayer::initData()
{
    isCanSeeAds = true;
    setName("FreeCoinLayer");
    
    if (DATA_M->getNextFreeCoinTime1() <= 0)
    {
        isCanSeeAds = true;
    }
    else
    {
        isCanSeeAds = false;
    }
    //event_lobby_freeCoin
    EVENT_M->addListener("event_lobby_freeCoin", [this](ValueMap valueMap, void *obj){
        if(_layer)
        {
            _layer->getNode("Panel_top_0")->setVisible(true);
            _layer->playAni("Start0",false);
        }
        auto lobby = SCENE_M->getLobby();
        //刷新cd时间
        if(freeCoinNum >= 14)
        {
            DATA_M->setFreeCoinTime1(DATA_M->getContentSec());
        }
        freeCoinNum++;
        SETINTEGER("freeCoinNum",freeCoinNum);
       
        if(_type == FreeCoinLayer::Type::Gold)
        {
            Vec2 poi(2000,2000);
            GameViewHD* gameview = SCENE_M->getGameView();
            if(gameview&&gameview->isVisible())
            {
                //poi = gameview->getGoldWorldPoi();
            }
            else
            {
                gameview = nullptr;
            }
            int goldNum = (int)DATA_M->getRewardCoin1();
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
            Vec2 goldPoi;
            if(lobby)
            {
                goldPoi = lobby->getGoldWorldPoi();
            }
            else
            {
                auto bagView = SCENE_M->getBagView();
                goldPoi = bagView->getGoldWorldPoi();
            }
            
            REWARD_M->rewardItemAction(num,poi == Vec2(2000,2000)?goldPoi:poi,
                                       this->getContentSize()*0.5,
                                       itemVec1,[this,lobby](){
                                           DATA_M->setCoinNum((int)DATA_M->getRewardCoin1(), true, 126);
                                           ValueMap valueMap{
                                               {"isTime",Value{true}}
                                           };
                                           //更新有金币显示
                                           EVENT_M->sendEvent("event_game_update_coin",valueMap);
                                           //lobby->updateCoin(true);
                                       },"Gold",SCENE_M->getRewardNode(),[lobby,this](){
                                       //home
                                           if(lobby)
                                           {
                                               lobby->playGoldAni(1,true);
                                           }
                                           
                                       },[lobby,this](){
                                           //home
                                           if(lobby)
                                           {
                                               lobby->playGoldAni(1,false);
                                           }
                                       });
//            lobby->goldAni(DATA_M->getRewardCoin1()*2,gameview,Vec2(2000,2000),[this,lobby](){
//                DATA_M->setCoinNum(DATA_M->getRewardCoin1()*2, true);
//                ValueMap valueMap{
//                    {"isTime",Value{true}}
//                };
//                //更新有金币显示
//                EVENT_M->sendEvent("event_game_update_coin",valueMap);
//                //lobby->updateCoin(true);
//            },[lobby,this](){
//            //home
//                //SOUND_M->playEffectMusic(EffectGetCoin);
//                lobby->playGoldAni(1,true);
//            },[lobby,this](){
//                //home
//                //SOUND_M->playEffectMusic(EffectGetCoin);
//                lobby->playGoldAni(1,false);
//                //SCENE_M->removeLayer(this);
//            },poi);
        }
        else if(_type == FreeCoinLayer::Type::Diamond)
        {
//            Vec2 poi(2000,2000);
//            GameViewHD* gameview = SCENE_M->getGameView();
//            if(gameview&&gameview->isVisible())
//            {
//                //poi = gameview->getdiamondWorldPoi();
//            }
//            else
//            {
//                gameview = nullptr;
//            }
//            int goldNum = (int)DATA_M->getRewardCoin1()*2;
//            int num = 0;
//            if(goldNum > 10)
//            {
//                num=goldNum/2;
//                if(num > 50)
//                {
//                    num = 50;
//                }
//            }
//            else
//            {
//                num = goldNum;
//            }
//            SCENE_M->getRewardNode()->setVisible(true);
//            std::vector<Vec2> itemVec1;
//            DATA_M->randVec(num,&itemVec1,200);
//            Vec2 goldPoi;
//            if(lobby)
//            {
//                goldPoi = lobby->getdiamondWorldPoi();
//            }
//            else
//            {
//                auto bagView = SCENE_M->getBagView();
//                goldPoi = bagView->getdiamondWorldPoi();
//            }
//            REWARD_M->rewardItemAction(num,poi == Vec2(2000,2000)?goldPoi:poi,
//                                       this->getContentSize()*0.5,
//                                       itemVec1,[this,lobby](){
//                                                DATA_M->setDiamond((int)DATA_M->getRewardCoin1()*2, true);
//                                                ValueMap valueMap{
//                                                    {"isTime",Value{true}}
//                                                };
//                                                //更新有金币显示
//                                                EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//                                            },"Baoshi",SCENE_M->getRewardNode(),[lobby,this](){
//                                                //home
//                                                if(lobby)
//                                                {
//                                                    lobby->playDiamondAni(1,true);
//                                                }
//                                            },[lobby,this](){
//                                                //home
//                                                if(lobby)
//                                                {
//                                                    lobby->playDiamondAni(1,false);
//                                                }
//                                            });
        }
        
        SCENE_M->removeLayer(this);
    },this);
//     addEvent("event_lobby_freeCoin", [this](EventCustom *eventCustom){
//         
//     });
}

void FreeCoinLayer::initUI()
{
    BaseLayer::initUI();
    doLayout();
    _actionManager->play("loop", false);
    auto node = _rootNode;
	panel_freecoin = node->getChildByName("panel_freecoin");
	INIT_BTN(node,"btn_close", CC_CALLBACK_1(FreeCoinLayer::dealButtonClick, this));
	INIT_BTN(node, "btn_lingqu", CC_CALLBACK_1(FreeCoinLayer::dealButtonClick, this));

	btn_guankan = INIT_BTN(node, "btn_guankan", CC_CALLBACK_1(FreeCoinLayer::dealButtonClick, this));
	text_guankan = FIND_NODE(Text *, node, "text_guankan");
    
    FileNode_1 = getNode("FileNode_1");
    

	if (isCanSeeAds && DATA_M->getHaveVideo())
	{
		btn_guankan->setEnabled(true);
		text_guankan->setString(UIUtils::getStringByName("lingqu2"));
	}
	else
	{
		btn_guankan->setEnabled(false);
		text_guankan->setString(UIUtils::getStringByName("zanwuship"));
	}
    
    if(_type == FreeCoinLayer::Type::Gold)
    {
        UIUtils::playInnerAction(FileNode_1, "Gold", true);
        
        FIND_NODE(Text *,node,"Text_title")->setString(UIUtils::getStringByName("100036"));
        FIND_NODE(Text *,node,"Text_miaoshu")->setString(StringUtils::format(UIUtils::getStringByName("100033").c_str(), DATA_M->getRewardCoin1()));
        getNode<TextBMFont*>("BitmapFontLabel_goldNum")->setString(StringUtils::format("+%d",DATA_M->getRewardCoin1()));
    }
    else if(_type == FreeCoinLayer::Type::Diamond)
    {
        UIUtils::playInnerAction(FileNode_1, "Baoshi", true);
        FIND_NODE(Text *,node,"Text_title")->setString(Lang("100296"));
        FIND_NODE(Text *,node,"Text_miaoshu")->setString(StringUtils::format(UIUtils::getStringByName("100297").c_str(), DATA_M->getRewardCoin1()));
        getNode<TextBMFont*>("BitmapFontLabel_goldNum")->setString(StringUtils::format("+%d",DATA_M->getRewardCoin1()));
    }
    
    
    
    
    
    
	// 处理多语言
    
	
	FIND_NODE(Text *,node,"text_lingqu")->setString(UIUtils::getStringByName("100034"));
	FIND_NODE(Text *,node,"text_guankan")->setString(UIUtils::getStringByName("100035"));
	
    getNode<Text*>("text_game")->setString(Lang("100113"));
//    schedule([this](float){
//        FIND_NODE(Text *,this,"Text_miaoshu")->setString(StringUtils::format(UIUtils::getStringByName("100033").c_str(), DATA_M->getRewardCoin1()*2));
//    }, .5, "schedule_update_coin");
}

void FreeCoinLayer::dealButtonClick(Ref * pSender)
{
	auto dealBtn = dynamic_cast<Widget *>(pSender);
	auto btnName = dealBtn->getName();

    if (dynamic_cast<Button*>(pSender))
        SOUND_M->playBtnClickAudio();

    ValueMap valueMap;
	if ("btn_close" == btnName||"panel_freecoin" == btnName)
	{
        
        
		UIUtils::hideDialog(panel_freecoin, "img_freecoin");
		this->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([this]{
            if(_layer)
            {
                _layer->getNode("Panel_top_0")->setVisible(true);
                _layer->playAni("Start0",false);
            }
			SCENE_M->removeLayerByName("FreeCoinLayer");
		}), NULL));
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("FreeCoinLayer")},
            {"value", Value("no")},
            {"v1", Value(DATA_M->getHaveVideo())}
        });
	}
	else if ("btn_lingqu" == btnName)
	{
		DATA_M->getFreeCoin();
		SCENE_M->removeLayer(this);
        valueMap["getType"] = Value("free");
        UIUtils::FIRAnalyticsEvent("event_freecoin_lingqu", valueMap);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("FreeCoinLayer")},
            {"value", Value("no")},
            {"v1", Value(DATA_M->getHaveVideo())}
        });
	}
	else if ("btn_guankan" == btnName)
	{
        
        DATA_M->playVideoAds(_type == FreeCoinLayer::Type::Gold ? 15 : 16);
		
		//SCENE_M->removeLayer(this);
        this->setVisible(false);
        valueMap["getType"] = Value("video");
        UIUtils::FIRAnalyticsEvent("event_freecoin_lingqu", valueMap);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("FreeCoinLayer")},
            {"value", Value("ad")}
        });
	}
    else if ("btn_game" == btnName)
    {//转到游戏
        
        auto lobby = SCENE_M->getLobby();
        auto gameView = SCENE_M->getGameView();
        
        if(_layer)
        {
            SCENE_M->removeLayer(_layer);
        }
        if(!gameView->isVisible())
        {
            lobby->startGame();
        }
        
        SCENE_M->removeLayer(this);
    }
//    else if("Button_1000" == btnName)
//    {
//#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
//        DATA_M->setCoinNum(1000,false);
//        DATA_M->setDiamond(1000,false);
//        //更新有金币显示
//        SCENE_M->getLobby()->updateCoin();
//        SCENE_M->getLobby()->updateDiamond();
//#endif
//    }
}

void FreeCoinLayer::dealButtonTouch(Ref * pSender, Widget::TouchEventType touchType)
{
	auto btn = static_cast<Button *>(pSender);
	switch (touchType)
	{
	case Widget::TouchEventType::BEGAN:
		btn->setScale(1.1);
		break;
	case Widget::TouchEventType::ENDED:
		btn->setScale(1);
		break;
	case Widget::TouchEventType::CANCELED:
		btn->setScale(1);
		break;
	case Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}


bool FreeCoinLayer::onTouchBegan(Touch * t, Event * e)
{
	auto position = t->getLocation();
	return true;
}

void FreeCoinLayer::onTouchMoved(Touch * t, Event * e)
{
}

void FreeCoinLayer::onTouchEnded(Touch * t, Event * e)
{
}

FreeCoinLayer::FreeCoinLayer(FreeCoinLayer::Type type,BaseLayer* layer):
BaseLayer("FreeCoinLayer.csb")
,_type(type)
,_layer(layer)
{
    auto is = TASK_M->getIsYday();
    if(is)
    {
        SETINTEGER("freeCoinNum",0);
    }
    
    //功能  可以无cd领取15次，  freeCoinNum => 14时 加入1分半cd
    freeCoinNum = GETINTEGER("freeCoinNum",0);
}

void FreeCoinLayer::onEnter()
{
    BaseLayer::onEnter();
}
void FreeCoinLayer::onExit()
{
    BaseLayer::onExit();
    EVENT_M->removeListener("event_lobby_freeCoin",this);
}
