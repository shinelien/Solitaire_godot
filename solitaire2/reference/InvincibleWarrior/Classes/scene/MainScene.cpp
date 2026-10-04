#include "MainScene.h"
#include "GameViewHD.hpp"
#include "DailyManager.h"
#include "DailyNotice.h"
#include "AtlasManager.h"
#include "NoMoveView.h"
#include "MainLobby.h"
#include "cocos-ext.h"
#include "BoxDataManager.h"
#include "SpriteManager.h"
#include "LevelManager.h"
#include "TeachManager.h"
#include "LoadingView.h"
#include "RewardManager.h"
#include "PlayerManager.h"

using namespace extension;

MainScene * MainScene::g_mainScene = nullptr;

MainScene::MainScene()
{
    
}

MainScene::~MainScene()
{
    
}

Scene * MainScene::createScene()
{
	if (nullptr == g_mainScene)
	{
		g_mainScene = new MainScene();
		g_mainScene->init();
		g_mainScene->autorelease();
	}
	return g_mainScene;
}

static long LoadCNT = 0;
bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
    
    SCENE_M->addLayer(LoadingView::createLayerN());
	//第一次加载主界面
//    AtlasManager::getInstance();
//    auto gameView = GameViewHD::createLayerN();
//    SCENE_M->addLayer(gameView);
//    if (TEACH_M->isDailyLevelUnlock()) {
//        SCENE_M->addDialog(MainLobby::createLayerN());
//    }
//    else {
//        gameView->setVisible(true);
//        vector<string> ImageNames{"ui1", "Gamebox"};
//        LoadCNT = ImageNames.size();
//        for (auto name:ImageNames) {
//            Director::getInstance()->getTextureCache()->addImageAsync(name+".png", [name](Texture2D *texture2D){
//                if (texture2D != nullptr) {
//                    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name+".plist", texture2D);
//                }
//                if (--LoadCNT == 0) {
//                    Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
//                        SCENE_M->addDialog(MainLobby::createLayerN());
//                    });
//                }
//            });
//        }
//    }
    
#if HasDaily
    // 引导每日
    /*if (DailyManager::getInstance()->getCompleteCNT(DailyManager::getInstance()->today()) == 0) {
        //SCENE_M->addDialog(DailyNotice::createLayerN());
    }*/
#endif
    this->initData();
	this->initUI();
	//this->scheduleUpdate();
	return true;
}

void MainScene::initData()
{
    UIUtils::FIRFirestoreAdd("info", {
            {"lang", Value(Application::getInstance()->getCurrentLanguageCode())},
            {"info", Value(UIUtils::getDeviceModel())},
            {"zone", Value(UIUtils::IsPad()?"pad":"phone")}, //将时间字符串当utc处理，打印时根据本地时区自动打印 +8
            {"gold", Value(DATA_M->getCoinNum())},
            {"diamond", Value(PlayerManager::getInstance()->getLevel())}, // 暂时代替 lv
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            {"os", Value("ios")},
    #elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            {"os", Value("android")},
    #else
            {"os", Value("other")},
    #endif
        });
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("login")}
        });
    CCLOG("ad is %s", UIUtils::getAD().c_str());
    UIUtils::FIRAnalyticsUserProperty("gold", toString(DATA_M->getCoinNum()));
    //UIUtils::FIRAnalyticsUserProperty("diamond", toString(DATA_M->getDiamond()));
    schedule([](float t){
        CCLOG("log cloud!!!");
        AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, [](void*){
            CCLOG("log cloud1!!!");
            UIUtils::FIRFirestoreAddCloud();
        }, nullptr, []{});
    }, 10, CC_REPEAT_FOREVER, 0.5, "repeat_log_key");
    
    CCLOG("WriteablePath:%s", FileUtils::getInstance()->getWritablePath().c_str());
    auto _assets_manager_ex = AssetsManagerEx::create("res/project.manifest", FileUtils::getInstance()->getWritablePath() + "download/data");
    UserDefault::getInstance()->setStringForKey("bu_version", _assets_manager_ex->getLocalManifest()->getVersion());
    _assets_manager_ex->retain();
    if (!_assets_manager_ex->getLocalManifest()->isLoaded())
    {
        
    }
    else
    {
        auto _assets_manager_listener = cocos2d::extension::EventListenerAssetsManagerEx::create(_assets_manager_ex, [this](EventAssetsManagerEx * event){
            switch (event->getEventCode()) {
                case cocos2d::extension::EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
                case cocos2d::extension::EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
                case cocos2d::extension::EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
                case cocos2d::extension::EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
                case cocos2d::extension::EventAssetsManagerEx::EventCode::UPDATE_FAILED:
                {
                    
                    break;
                }


                case cocos2d::extension::EventAssetsManagerEx::EventCode::ERROR_UPDATING:
                {

                    break;
                }

                case cocos2d::extension::EventAssetsManagerEx::EventCode::ASSET_UPDATED:
                {

                    break;
                }

                case cocos2d::extension::EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
                {
                    CCLOG("已经是最新版本，直接进入主界面");
                    UserDefault::getInstance()->setStringForKey("bu_version", event->getAssetsManagerEx()->getLocalManifest()->getVersion());
                    break;
                }

                case cocos2d::extension::EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
                {
                    CCLOG("更新完成重新加载");
                    SpriteManager::getInstance()->reloadFile();
                    DailyManager::getInstance()->initConfig();
                    LevelManager::getInstance()->analysisJsonConfig();
                    BoxDataManager::getInstance()->analysisJsonConfig();
                    UserDefault::getInstance()->setStringForKey("bu_version", event->getAssetsManagerEx()->getLocalManifest()->getVersion());
                    break;
                }

                case cocos2d::extension::EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
                {
//                    this->onLoadPercent(event->getPercent());
                    CCLOG("Update percent:%.2f...", event->getPercent());
                    break;
                }

                case cocos2d::extension::EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND:
                {
                    CCLOG("发现新本版开始升级");
                    break;
                }

                default:
                    break;
            }
        });

        Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_assets_manager_listener, 1);
        _assets_manager_ex->update();
    }
}

void MainScene::initUI()
{

}

void MainScene::showTips(string tipStr,bool isNoTips,std::function<void()> cb)
{
	auto panel_tips = CSLoader::createNode("TipsNode.csb");
	panel_tips->setLocalZOrder(999);
	this->addChild(panel_tips);
	auto text_tips = FIND_NODE(Text *, panel_tips, "text_tips");

    auto size = Director::getInstance()->getWinSize();
    auto center = Vec2(size/2);
	panel_tips->setVisible(true);
	panel_tips->setPosition(Vec2(0, 400) + center);
	text_tips->setString(tipStr);
	panel_tips->setOpacity(0);
    if(cb)
    {
        
        panel_tips->runAction(Sequence::create(DelayTime::create(0.02f),FadeIn::create(0.1), DelayTime::create(0.5), Spawn::create(MoveTo::create(0.8, Vec2(0, 200)+center), FadeOut::create(0.8), NULL), CallFunc::create(cb),CallFunc::create([isNoTips,panel_tips]{
            
            panel_tips->removeFromParentAndCleanup(false);
        }), NULL));
    }
    else
    {
        auto num = RewardManager::getInstance()->getCNT(RewardManager::RewardType::Magic);
        panel_tips->runAction(Sequence::create(DelayTime::create(0.02f),FadeIn::create(0.1), DelayTime::create(0.5), Spawn::create(MoveTo::create(0.8, Vec2(0, 200)+center), FadeOut::create(0.8), NULL), CallFunc::create([isNoTips,panel_tips,num]{
            
            if(isNoTips&&num > 0)
            {
                SCENE_M->getGameView()->setIsOpenTipsTime(false);
                SCENE_M->addDialog(NoMoveView::createLayerN());
                UIUtils::FIRAnalyticsEvent("game_tips_view_nomove", {});
            }
            else
            {
                auto game = SCENE_M->getGameView();
                //关闭窗口开始累计计时
                game->setIsOpenTipsTime(true);
                game->setIsShowTips(false);
                UIUtils::FIRAnalyticsEvent("game_tips_view_tips", {});
            }
            panel_tips->removeFromParentAndCleanup(false);
        }), NULL));
    }
	
    // 多语言
    FIND_NODE(Text *,panel_tips,"text_tips")->setString(tipStr);
    
    UIUtils::textAdaptiveSize(text_tips,1000);
}

void MainScene::dealButtonClick(Ref * pSender)
{
	auto dealBtn = dynamic_cast<Button *>(pSender);
	auto btnName = dealBtn->getName();

	SOUND_M->playBtnClickAudio();
}

void MainScene::update(float dt)
{

}

bool MainScene::onTouchBegan(Touch * t, Event * e)
{
	auto position = t->getLocation();
	return true;
}

void MainScene::onTouchMoved(Touch * t, Event * e)
{
}

void MainScene::onTouchEnded(Touch * t, Event * e)
{
}

//添加界面
void MainScene::addLayer(Node * layer)
{
	layerNames.push_back(layer->getName());
	this->addChild(layer);
}

//移除界面
void MainScene::removeLayer(Node * layer)
{
	this->removeChild(layer);
}

void MainScene::removeLayerByName(const char * name)
{
	auto child = this->getChildByName(name);
	if (child)
	{
		this->removeChild(child);
	}
}

void MainScene::removeLayerByTag(int tag)
{
	auto child = this->getChildByTag(tag);
	if (child)
	{
		this->removeChild(child);
	}
}

//移除所有的界面
void MainScene::removeAllLayer()
{
	for (auto it = layerNames.begin(); it != layerNames.end(); it++)
	{
		auto name = (*it);
		this->removeLayerByName(name.c_str());
	}
	layerNames.clear();
}

//移除大厅与游戏c窗口除外的弹窗
void MainScene::removeLayer()
{
    vector<string> tempLayerNames;
    for(int i = 2;i<layerNames.size();++i)
    {
        auto name = layerNames.at(i);
        if(name == "DailyMoreView"||name == "DailyGameView"||name == "DrawPropsView"||name == "BagView"||name == "ShareRewardView"||name == "SevenDayView"||name == "StarBoxView"||name == "DailytaskView"||name == "ShuffleView"||name == "GuideView"||name == "DailyNotice"||name == "Dialog"||name == "SettingViewHD"||name == "LevelViewHD"||name == "FeedBackView"||name == "GamePauseHD"||name == "PrivacyViewHD"||name == "RewardRouletteView"||name == "HomeSetting"||name == "BackView"||name == "FreeCoinLayer"||name == "RuleLayer"||name == "CountLayer"||name == "CoinLayer")
        {
            auto child = this->getChildByName(name);
            if (child)
            {
                tempLayerNames.push_back(name);
                this->removeChild(child);
            }
        }
    }
    
}

bool MainScene::hasLayerByName(const string &name)
{
    for (auto it = layerNames.begin(); it != layerNames.end(); it++)
    {
        if (*it == name) {
            return true;
        }
    }
    return false;
}

Node* MainScene::getRewardNode()
{
    if(!rewardNode)
    {
        rewardNode = Node::create();
        this->addChild(rewardNode,100);
        auto safeArea = Director::getInstance()->getSafeAreaRect();
        rewardNode->setPosition(safeArea.origin);
    }
    return rewardNode;
}

Node* MainScene::getStarNode()
{
    if(!starNode)
    {
        starNode = Node::create();
        this->addChild(starNode,101);
        auto safeArea = Director::getInstance()->getSafeAreaRect();
        starNode->setPosition(safeArea.origin);
    }
    return starNode;
}

Node* MainScene::getWinLayerNode()
{
    if(!winLayerFCNode)
    {
        winLayerFCNode = Node::create();
        this->addChild(winLayerFCNode);
    }
    return winLayerFCNode;
}

void MainScene::clickEff(Vec2 poi)
{
    auto click = CSLoader::createNode("Animation/Node_click.csb");
    auto Paricle_1 = FIND_NODE(ParticleSystemQuad *, click, "Particle_1");
    Paricle_1->resetSystem();
    auto time = Paricle_1->getDuration();
    click->setLocalZOrder(999);
    this->addChild(click);
    click->setPosition(poi);
    click->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create([click]{
        click->removeFromParentAndCleanup(false);
    }), NULL));
}
