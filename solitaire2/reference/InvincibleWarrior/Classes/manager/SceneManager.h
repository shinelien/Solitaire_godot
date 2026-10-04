/*
	场景管理器
	author:codehua
	time:2016年9月2日00:33:52
*/

# ifndef __SCENE_MANAGER__
# define __SCENE_MANAGER__

# include "cocos2d.h"
# include "UIUtils.h"
# include "DataManager.h"
# include "BaseLayer.h"
# include "MainScene.h"
#include "Dialog.h"

# define SCENE_M SceneManager::getInstance()

USING_NS_CC;
class GameBackground;
class GamePauseHD;
class GameViewHD;
class MainLobby;
class BackstagePause;
class FreeCoinLayer;
class BagView;
class FanPaiRewardView;
class LoadingView;
class SevenDayView;
static const int TeachOrder = 5;
static const int TeachTag = 100086111;

class SceneManager : public Ref
{
public:
	static SceneManager * getInstance();

	void addLayer(BaseLayer * baseLayer);//Layer是移除原有界面，添加这个界面
    void removeLayerByName(const char *layerName);
	void removeLayerByName(const string &layerName, BaseLayer *excludeLayer);
	void removeLayer(Node * baseLayer);
    void removeLayer();//移除出大厅与游戏窗口外的弹窗
	void addDialog(Node * baseLayer, bool once = false, int zOrder = 0, int tag = 0);	//dialog是添加在原有界面上的
	void addTeachDialog(Node * baseLayer, int zOrder = TeachOrder, int tag = TeachTag);	//dialog是添加在原有界面上的
    void refushShopScene(bool isRefushAll = false);//刷新界面 isRefushAll = true 刷新整个界面 false刷新金币
	void showLevelComplete(bool isWin = false, std::shared_ptr<rapidjson::Document> levelData = nullptr);// 星星

	void recoveryGame();//恢复游戏
	void showAutoFinishBtn(bool isShow);
	void gameOver(bool isWin);
	void resetGame(const string pokers = "", bool noAds = false);
	GameViewHD *getGameView();
    GamePauseHD* getGamePause();
    BackstagePause* getBackstagePause();
    MainLobby* getLobby();
    FreeCoinLayer* getFreeCoinLayer();
    LoadingView* getLoadingView();
    SevenDayView* getSevenDayView();
    Node* getRewardNode();
    Node* getStarNode();
    Node* getWinLayerNode();
    BagView* getBagView();
    GameBackground* getGameBackground();
    FanPaiRewardView* getFanPaiRewardView();
	void gameStart();

	void showTips(string tips,bool isNoTips = false,std::function<void()> cb = nullptr);
    Dialog* showDialog(Dialog::Type type, CBFunc ok, CBFunc no);

    void lockScreen(std::function<void(Ref*)> cb = nullptr);
    void unlockScreen();
    
    void showLoading();
    void removeLoading();

	void updateWaitCardNum(int waitCardNum);
	void addMoveNum();

	void refushGift();
	void updateScore(int delay);
    
    void clickEff(Vec2 poi);
private:
	SceneManager();
	static SceneManager * sceneManager;

	bool isPlayBg;
};

# endif
