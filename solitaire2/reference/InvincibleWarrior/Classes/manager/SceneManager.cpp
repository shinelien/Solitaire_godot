# include "SceneManager.h"
#include "GameViewHD.hpp"
#include "SceneManager.h"
#include "LevelViewHD.h"
#include "ShopViewHD.h"
#include "BackstagePause.h"
#include "MainLobby.h"
#include "GamePauseHD.h"
#include "FreeCoinLayer.h"
#include "BagView.h"
#include "FanPaiRewardView.h"
#include "LoadingView.h"
#include "GameBackground.h"
#include "RankLoading.h"
#include "SevenDayView.h"

SceneManager * SceneManager::sceneManager = nullptr;

SceneManager::SceneManager()
{
}

SceneManager * SceneManager::getInstance()
{
	if (sceneManager == nullptr)
	{
		sceneManager = new SceneManager();
	}

	return sceneManager;
}

void SceneManager::addLayer(BaseLayer * baseLayer)
{
	MainScene::g_mainScene->removeAllLayer();
	MainScene::g_mainScene->addLayer(baseLayer);
}

//dialog是添加在原有界面上的
void SceneManager::addDialog(Node * baseLayer, bool once, int zOrder, int tag)
{
    if (once) {
        auto dialog = MainScene::g_mainScene->getChildByName(baseLayer->getName());
        if (dialog) {
            dialog->setVisible(true);
            return;
        }
    }
	MainScene::g_mainScene->addLayer(baseLayer);
	baseLayer->setLocalZOrder(zOrder);
	baseLayer->setTag(tag);
}

void SceneManager::removeLayerByName(const char * layerName)
{
    MainScene::g_mainScene->removeLayerByName(layerName);
}

void SceneManager::removeLayer(Node * baseLayer)
{
	MainScene::g_mainScene->removeLayer(baseLayer);
}

void SceneManager::removeLayer()
{
    MainScene::g_mainScene->removeLayer();
}

//刷新界面
void SceneManager::refushShopScene(bool isRefushAll)
{
	auto shopView = dynamic_cast<ShopViewHD *>(MainScene::g_mainScene->getChildByName("ShopViewHD"));
	if (shopView)
	{
		shopView->refush(isRefushAll);
	}
}

void SceneManager::gameOver(bool isWin)
{
	auto gameLayer = (GameViewHD *)MainScene::g_mainScene->getChildByName("GameLayer");
	if (gameLayer)
	{
		gameLayer->gameOver(isWin);
	}
}

void SceneManager::resetGame(const string pokers, bool noAds)
{
	auto gameLayer = (GameViewHD *)MainScene::g_mainScene->getChildByName("GameLayer");
	if (gameLayer)
	{
//        gameLayer->resetGame(pokers);
        gameLayer->restartGame(false, DATA_M->getNetReachable() == 0?DataManager::GameType::Random:DataManager::GameType::None, noAds);
	}
}

//恢复游戏
void SceneManager::recoveryGame()
{
	//判断，如果是在游戏界面关闭的话，就开启游戏
	auto gameLayer = (GameViewHD *)MainScene::g_mainScene->getChildByName("GameLayer");
	if (gameLayer)
	{
		gameLayer->gamePause(false);
		gameLayer->refush();
	}
}

void SceneManager::updateWaitCardNum(int waitCardNum)
{
	auto gameLayer = (GameViewHD *)MainScene::g_mainScene->getChildByName("GameLayer");
	if (gameLayer)
	{
		gameLayer->updateWaitCardNum(waitCardNum);
	}
}

void SceneManager::refushGift()
{
	auto gameLayer = (GameViewHD *)MainScene::g_mainScene->getChildByName("GameLayer");
	if (gameLayer)
	{
        gameLayer->refushGift();
	}
    auto lobby = static_cast<MainLobby*>(MainScene::g_mainScene->getChildByName("MainLobby"));
    
    if (lobby)
    {
        lobby->refushGift();
    }
}

void SceneManager::updateScore(int delay)
{
	auto gameLayer = (GameViewHD *)MainScene::g_mainScene->getChildByName("GameLayer");
	if (gameLayer)
	{
		gameLayer->updateScore(delay);
	}
}

void SceneManager::addMoveNum()
{
	auto gameLayer = (GameViewHD *)MainScene::g_mainScene->getChildByName("GameLayer");
	if (gameLayer)
	{
		gameLayer->addMoveNum();
	}
}

void SceneManager::gameStart()
{
	auto gameLayer = (GameViewHD *)MainScene::g_mainScene->getChildByName("GameLayer");
	if (gameLayer)
	{
		gameLayer->startGame();
	}
}

void SceneManager::showAutoFinishBtn(bool isShow)
{
	auto gameLayer = (GameViewHD *)MainScene::g_mainScene->getChildByName("GameLayer");
	if (gameLayer)
	{
		gameLayer->showAutoFinishBtn(isShow);
	}
}
void SceneManager::showTips(string tips,bool isNoTips,std::function<void()> cb)
{
	MainScene::g_mainScene->showTips(tips,isNoTips,cb);
}

GameViewHD *SceneManager::getGameView() {
	return static_cast<GameViewHD*>(MainScene::g_mainScene->getChildByName("GameLayer"));
}

GamePauseHD* SceneManager::getGamePause()
{
    return static_cast<GamePauseHD*>(MainScene::g_mainScene->getChildByName("GamePauseHD"));
}

BackstagePause* SceneManager::getBackstagePause()
{
    return static_cast<BackstagePause*>(MainScene::g_mainScene->getChildByName("BackstagePause"));
}

MainLobby* SceneManager::getLobby()
{
    return static_cast<MainLobby*>(MainScene::g_mainScene->getChildByName("MainLobby"));
}

FreeCoinLayer* SceneManager::getFreeCoinLayer()
{
    return static_cast<FreeCoinLayer*>(MainScene::g_mainScene->getChildByName("FreeCoinLayer"));
}

Node* SceneManager::getRewardNode()
{
    return MainScene::g_mainScene->getRewardNode();
}

Node* SceneManager::getStarNode()
{
    return MainScene::g_mainScene->getStarNode();
}

Node* SceneManager::getWinLayerNode()
{
    return MainScene::g_mainScene->getWinLayerNode();
}

BagView* SceneManager::getBagView()
{
    return static_cast<BagView*>(MainScene::g_mainScene->getChildByName("BagView"));
}

FanPaiRewardView* SceneManager::getFanPaiRewardView()
{
    return static_cast<FanPaiRewardView*>(MainScene::g_mainScene->getChildByName("FanPaiRewardView"));
}

LoadingView* SceneManager::getLoadingView()
{
    return static_cast<LoadingView*>(MainScene::g_mainScene->getChildByName("LoadingView"));
}

GameBackground* SceneManager::getGameBackground()
{
    return static_cast<GameBackground*>(MainScene::g_mainScene->getChildByName("GameBackground"));
}

SevenDayView* SceneManager::getSevenDayView()
{
    return static_cast<SevenDayView*>(MainScene::g_mainScene->getChildByName("SevenDayView"));
}

void SceneManager::showLevelComplete(bool isWin, std::shared_ptr<rapidjson::Document> levelData) {
	auto levelView = dynamic_cast<LevelViewHD*>(MainScene::g_mainScene->getChildByName("LevelViewHD"));
	if (levelView) {
		levelView->complete(isWin, levelData);
	}
}

void SceneManager::removeLayerByName(const string &layerName, BaseLayer *excludeLayer) {
	MainScene::g_mainScene->enumerateChildren("[[:alnum:]]+.LevelViewHD", [excludeLayer](Node *node)->bool{
		if (excludeLayer != node) {
			node->removeFromParent();
		}
        return false;
	});
}

Dialog* SceneManager::showDialog(Dialog::Type type, CBFunc ok, CBFunc no) {
	auto dialog = Dialog::createLayerN(type, ok, no);
	addDialog(dialog, true);
	return dialog;
}

void SceneManager::lockScreen(function<void(Ref*)> cb) {
	auto layout = ui::Layout::create();
	MainScene::g_mainScene->addChild(layout, 999, 10010110);
	layout->setContentSize(Director::getInstance()->getWinSize());
    layout->setTouchEnabled(true);
    if (cb) {
        layout->addClickEventListener(cb);
    }
}

void SceneManager::unlockScreen() {
    if (MainScene::g_mainScene->getChildByTag(10010110)) {
        MainScene::g_mainScene->removeLayerByTag(10010110);
    }
}

void SceneManager::addTeachDialog(Node *baseLayer, int zOrder, int tag) {
	addDialog(baseLayer, false, zOrder, tag);
}


void SceneManager::showLoading()
{
    if (!MainScene::g_mainScene->getChildByTag(10010111)) {
        auto view = RankLoading::createLayerN();
        MainScene::g_mainScene->addChild(view, 999, 10010111);
    }
}

void SceneManager::removeLoading()
{
    if (MainScene::g_mainScene->getChildByTag(10010111)) {
        MainScene::g_mainScene->removeChildByTag(10010111);
    }
}

void SceneManager::clickEff(Vec2 poi)
{
    MainScene::g_mainScene->clickEff(poi);
}
