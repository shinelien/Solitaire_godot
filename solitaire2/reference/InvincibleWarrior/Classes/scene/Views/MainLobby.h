
#ifndef NewSpaceCatSolitaire_MainLoby_H
#define NewSpaceCatSolitaire_MainLoby_H

#include "BaseLayer.h"
#include "Factory.hpp"
#include <external/json/document.h>
#include "TeachInterface.h"

class GameViewHD;
class BagView;
class LevelUpView;
class MainLobby : public BaseLayer, public Factory<MainLobby>, public TeachInterface {
public:
    enum class Tab {
        Home = 0,
        Level,
        Daily,
        Store,
        None
    };
    
    virtual ~MainLobby();
    MainLobby();
    void resetLevelView();
    void resetHome();
    void updateBanner();
    void updateUI();
    void updatePage(int page = 0);
    Node* setTab(Tab tab);
    void startGame();
    void startGame(bool isNew);
    void startDaily(const std::string &deck, const std::string &num);
    void startDaily();
    void startLevel(std::shared_ptr<rapidjson::Document> levelData);
    void startLevel();
    void showSetting();

    void setVisible(bool visible) override;
    void setView();
    void setViewShow();
    void dailyShowComplete();
    void starAni(int starNum,std::string aniName,Vec2 poi = Vec2(0,0),std::function<void()> cb = nullptr);//星星增加动画
    void goldAni(int goldNum,Node* parent = nullptr,Vec2 startPoi = Vec2(2000,2000),std::function<void()> cb = nullptr,std::function<void()> endCB = nullptr,std::function<void()> endCB2 = nullptr,Vec2 endPoi = Vec2(2000,2000));
    void diamondAni(int zuanShiNum,Node* parent = nullptr,Vec2 startPoi = Vec2(2000,2000),std::function<void()> cb = nullptr,std::function<void()> endCB = nullptr,std::function<void()> endCB2 = nullptr,Vec2 endPoi = Vec2(2000,2000));
    void magicAni(int zuanShiNum,Node* parent = nullptr,Vec2 startPoi = Vec2(2000,2000),std::function<void()> cb = nullptr,std::function<void()> endCB = nullptr,std::function<void()> endCB2 = nullptr,Vec2 endPoi = Vec2(2000,2000));
    void spriteAni(Node* node,int type,std::function<void()> cb);
    void stroeBoxAni(Node*node, int type,std::function<void()> cb);
    Vec2 getBagWorldPoi(int type);
    Vec2 getStarBoxWorldPoi();
    Vec2 getGoldWorldPoi();
    Vec2 getdiamondWorldPoi();
    Vec2 getBagWorldPoi();
    Vec2 getLevelWorldPoi();
    
    void playGoldAni(int type,bool isPlay);
    void playDiamondAni(int type,bool isPlay);
    void playGoldAni(BaseLayer* node, bool isPlay);
    void playDiamondAni(BaseLayer* node,bool isPlay);
    void playBagAni();
    void updateDYY();
    
    void isShowBag(bool isShow);
    void isShowTop(bool isShow);
    void updateCoin(int type);
    void updateDiamond(int type);
    
    //
    void playEffect();
    void playMusic();
    
    void updateCoin(bool isDelay = false);
    void updateDiamond(bool isDelay = false);
    void updateExp();
    void updateStarBox(bool isDelay = false);
    void updateCrownnBox(bool isDelay = false);
    void updateStar();
    void updateNewVersion(bool isShow = true);
    
    void setInterstitialCB(std::function<void()> cb);
    
    void refushGift();
    
    void showBag(int type);
    //-------------NEW
    void updataBagNew();
    void updateStoreNew();
    void updateTaskNew();
    void updateSevenNew();
    void showDailyStart();
    void showTaskNew();
    void showSetNew(bool isShow);
    void updateLockState();
    //fishNew
    void updateFishNewTips();
    void updateFashTankNewTips();
    // node
    Node* getTeachItem(const std::string &name, int idx) override;
    
    void effCeShi();
    void effCeShi0();
    void effCeShi1();
    
    //ceshi fish
    void updateFishNum();
    
    void setIsStart(bool is);
    bool getIsStart();
    bool getIsNewGame();
    
    void hideLobby(std::function<void()> cb);
    void rewardExp(int rewardNum,Vec2 startPoi);
    void rewardGold(int rewardNum,Vec2 startPoi);
    void rewardMagic(int rewardNum,Vec2 startPoi);
    void unlockFishMove(int idx,Vec2 startPoi,std::function<void()> cb);
    void unlockFashTankMove(int idx,SpriteFrame* frame,Vec2 startPoi,std::function<void()> cb);
    Vec2 getBtnFishWorldPoi();
    
    bool myTouchBegan(Touch * t, Event * e);
    void myTouchMoved(Touch * t, Event * e);
    void myTouchEnded(Touch * t, Event * e);
    
    void openReward(bool isOpen);
    void menuPlayAni(string aniName,bool isLoop);
    void setIsGoGameView(bool isGo) { isGoGameView = isGo; }
    bool getIsGoGameView() { return isGoGameView; }
    void showGetGoldBtn(bool isShow);
    void showWeiShiBtn(bool isShow);
    void clickFishShop();
    void showGuide();
    void updateBtnChallenge();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    bool isOne = true;
public:
    void onEnter() override;
    void onExit() override;

private:
    
    float moveOffsetY = 0;
    cocos2d::Node *Image_bottom;
    Tab _currentTab = Tab::None;
    Vector<Node*> _rootLayers;
    Node *panel_root,*Node_rewardAni,*FileNode_top;
    GameViewHD *gameView;
    BagView* _bagView;
    Node* Panel_home,*FileNode_MyBag,*FileNode_StarBox,*FileNode_StarBox2,*FileNode_CrownBox2,*FileNode_LunPan,*Image_Sign_AD,*FileNode_StoreBox;
    Node* FileNode_gold;
    Button*Button_LunPan,*Button_Sign_AD,*Button_fanPai,*Button_share,*Button_Collect;
    Node* main_tips1_Task,*lobby_fashTank_tips,*lobby_fish_tips;
    float percent;
    int _diamondNum,_coinNum;
    std::function<void()> InterstitialCB = nullptr;
    Text* Text_Sign_AD;
    
    //翻牌与轮盘轮换
    bool isShowFanPai = true;
    int storeNewNum;
    int taskNewNum;
    int sevenNewNum;
    bool isNewGame;
    int setNewNum;
    //当前选择的模式 方便再次打开游戏时转到对应模式
    int _oldTab;
    
    float scaleFactor;
    bool isStart;
    
    //开启进度条变化
    int lv = 0,oldLv = 0,dLv = 0;
    float percent1 = 0,percent2 = 0;
    bool isBar = false;
    bool isQieHuan = false;
    float maxPercent;
    float percentDx;
    LoadingBar* _LoadingBar_level;
    Text*Text_level_up;
    TextBMFont*_Text_level,*Text_challenge_time;
    LevelUpView* LevelUpView;
    Node* FileNode_fish,* FileNode_fashTank,* FileNode_play;
    bool isGoGameView;
    bool isTouch;
    Vec2 BtnStartPoi;
    bool isAppStart;
};

#endif //NewSpaceCatSolitaire_MainLoby_H
