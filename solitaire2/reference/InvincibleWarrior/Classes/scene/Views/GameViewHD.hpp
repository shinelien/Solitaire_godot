//
//  GameViewHD.hpp
//  SpacecatSolitaireGame
//
//  Created by Cyutao on 2018/8/27.
//

#ifndef GameViewHD_hpp
#define GameViewHD_hpp

#include <stdio.h>
#include "BaseLayer.h"
#include "Factory.hpp"
#include "DataManager.h"
#include <spine/AnimationState.h>
namespace spine {
    class SkeletonAnimation;
}

namespace spine {
    class SkeletonAnimation;
}
class LevelUpView;
class CardSprite;
class GameTime;
class WinLayer;
class WinLayerLevelHD;
class WinLayerDailyHD;
class WinHD;
class GameRewardsView;
class GameViewHD : public BaseLayer, public Factory<GameViewHD>
{
public:
    enum class State {
        Shuffle,
        Ready,
        Play,
        End,
        
        None,
    };
    
    
    GameViewHD();
    ~GameViewHD();
    
    void initData() override;
    void initUI() override;
    
    // 实现老的接口
    void startGame();
    void gameOver(bool isWin);
    void resetGame(const string pokers = "");
    void resetGameData();
    void gamePause(bool isPause);
    bool getGamePause()
    {
        return isPause;
    }
    void refush() override;
    void updateWaitCardNum(int num);
    void updateScore(int delay);
    void addMoveNum();
    void showAutoFinishBtn(bool isShow);
    void changePos();
    void restartGame(bool isReplay, DataManager::GameType gameType = DataManager::GameType::None, bool noAds = false);
    void startLevelRank(std::shared_ptr<rapidjson::Document> levelData, bool noAds = false);
    void startDaily(const std::string &bureau, const std::string &type);
    void collectACard(int number, int colorType);
    void collectSpecialCard(int pos);
    void refushGift();
    void updateUI();
    // 挑战
    void levelComplete(bool isWin);
    bool isLevelCard(int number, int colorType);
    bool isLevelCard(int pos);
    void levelRelive();
    void levelCompleteEnd(bool isWin, bool noShow = false);
    // 每日
    void showStartTips();
    void showNode(const std::string &name, bool visible);
    // 统计事件
    void onFaild(int level);

    void onEnter() override;
    void onExit() override;
    void setVisible(bool visible) override;
    // 星星评级
    int getStar();
    void setGameOverState();
    void updateRedPoint(DataManager::GameType gameType = DataManager::GameType::Level);

    void update(float delta) override;

    void updateTime(float t);
    void showTips();
    // 触屏事件
    virtual bool onTouchBegan(Touch * t, Event * e) override;
    virtual void onTouchMoved(Touch * t, Event * e) override;
    virtual void onTouchEnded(Touch * t, Event * e) override;
    virtual void onTouchCancelled(Touch * t, Event * e) override;
    void dealButtonClick(Ref * pSender) override;// , ui::TouchEventType teType);
    
    CC_SYNTHESIZE(int, score, Score);//分数
    CC_SYNTHESIZE(bool, _isLeftModel, LeftModel);//分数
    //---------------ai翻开有效 重开步数
    int getMoveNum()
    {
        return moveNum;
    }
    //更新音乐
    void playEffect();
    void playMusic();
    //更新道具数量
    void updateShuffle();
    //获取道具动画
    void playGetMagic(bool isInterstitials = false);
    //使用道具
    void useMagic();
    //重开本局
    void agianGame();
    CC_SYNTHESIZE(bool, isOpenTipsTime, IsOpenTipsTime);
    //重置无操作提示时间
    void setTipsTime(int time)
    {
        _tipsTime = time;
    }
    void setFuZhuTipsColor(bool isOpenAI);
    void updateyday();
    Node* getTipsTextNode()
    {
        return panel_tips;
    }
    
    void setIsShowTips(bool is);
    bool getIsShowTips();
    
    void ceshi();
    //关卡限时提示
    void updateLimitTimeHintTime(float dt);
    void limitTimeHint();
    void initLimitTimeHintLayer();
    //对局状态
    void setGameState(State state);
    State gameState() {
        return _gameState;
    }
    //第一次安装开启游戏
    void resetOne();
    //返回大厅
    void showLobby();
    void showHome();
    //vegas
    bool vegasFaPaiTips();
    //
    bool getIsFanPai();
    bool getIsFanPai2();
    //底部按钮
    void menuPausePlayAni(std::string name,bool isLoop,std::function<void()> cb = nullptr);
    void menuMove(bool in);
    
    //暂停界面要用
    std::shared_ptr<rapidjson::Document> getLevelDate()
    {
        return _levelData;
    }
    void showGoldAni();
    //更新财产
    void updateCoin(bool isDelay = false);
    void updateDiamond();
    void updateLv();
    void updateDYY();
    void updateRandReward();
    void updateNewVersion(bool isShow = true);
    
    Vec2 getMagicWorldPoi();
    Vec2 getGoldWorldPoi();
    Vec2 getdiamondWorldPoi();
    Vec2 getBagWorldPoi();
    Vec2 getLevelWorldPoi();
    Vec2 getBtnFishWorldPoi();
    Vec2 getPauseWorldPoi();
    //返回 鱼图片缩小倍数
    float getFishScale(float fishWidth);
    //提前退出时隐藏轮盘
    void hideLunPan();
    //BagNew
    void updataBagNew();
    //fishNew
    void updateFishNewTips();
    // 开启教学关卡
    void startTeachBureau();
    
    //适配
    void nodedoLayout(Node* node);
    //返回 游戏是否结束
    bool getGameOver();

    bool getIsAuto();
    //设置是否刷新奖励
    void setIsRefushGift(bool isShow);

    void playBagAni();
    //判断结算窗口是否出现 后台切换暂停用
    bool winLayerIsShow();
    void updateBanner();
    // ai 事件打点
    void sendStartGameEvent(DataManager::GameType gameType);
    void sendEndGameEvent(DataManager::GameType gameType, string endEvent);
    
    void winAnimation(int goldNum);
    Vec2 getStarBoxWorldPoi();
    void updateStarBox(bool isDelay = false);
    bool getClickCard(Vec2 touchPoi);
    void unlockFishMove(int idx,Vec2 startPoi,std::function<void()> cb);
    void unlockFashTankMove(int idx,string frameName,Vec2 startPoi,std::function<void()> cb);
    void setButtonPauseEnabled(bool isEnabled);
    int getFaildNum() { return _faildNum; }
    bool getIsThreeModel() { return isThreeModel; }
    void updateTextChallenge();
    void updateBtnChallenge();
    void showChallenge();
private:
    void showInterstitialDelay();
    bool showInterstitial();
    //底部按钮
    void menuPlayAni(std::string name,bool isLoop,std::function<void()> cb = nullptr);
    
    Sprite* gameBg;
    
    float moveOffsetY = 0, touchMoveDelay = 0;
    int moveNum = 0, completeCNT = 0, useBackCNT = 0, dailyType = 0;
    std::unordered_map<std::string, int> _levelPoker;
    std::unordered_map<std::string, int> _specialPoker;
    float timeDelay, extraCDTime, autoTipsTime;
    bool isOver, isPause, isUseBack, isCanTouch, isShowTips, isMoveCard, isTouchRefush;
    CardSprite * selectCard;
    Node *panel_game, *panel_gift, *panel_bottom,*FileNode_getMagic;
    Sprite * refushSprite;
    GameTime *gameTimeView = nullptr;
    std::shared_ptr<rapidjson::Document> _levelData;
    unsigned int _winEffectID = 0, _reliveCNT = 0;
    WinLayer *_gameWinLayer;
    WinLayerLevelHD *_gameWinLayerLevel;
    WinLayerDailyHD *_gameWinLayerDaily;
    GameRewardsView* _gameRewardsView;
    WinHD *_winHD;
    std::function<void()> InterstitialCB = nullptr;
    std::function<void()> winCB = nullptr;
    int _magicCNT,_tipsCNT,_useBackCNT;
    float _tipsTime, scaleFactor;
    bool isChuMo;
    //限制noMove弹窗次数
    int noMoveTipsNum;
    //控制不要每次翻牌都弹出 目前是一轮后下一轮翻完弹出
    int noMoveTipsNum2;
    Sprite* sprite_fuZhu_on,*sprite_fuZhu_off;
    Node* panel_tips;
    //手指
    Node* node_levelhint = nullptr;
    //选中的牌
    CardSprite* hintCard = nullptr;
    //LimitTime 是否解开提示限制
    bool isOpenLimitTimeHint;
    //10s提示一次
    float openLimitTimeHintTime;
    Layer* LimitTimeHintLayer;
    //每局提示次数
    int LimitTimeHintNum;
    ValueMap _bureauData;
    //轮盘
    ImageView* Image_LunPan;
    //游戏状态
    State _gameState = State::None;
    //vegas
    bool _isWeiJiaSi;
    bool _isWeiJiaSiJiFen;
    int weiJiaSiJiShu;
    bool isThreeModel;
    //自动收牌是否开启
    bool isAutoShouPai;
    //按钮Node
    Node* FileNode_2020Menu,*FileNode_pause,*FileNode_pause2,*FileNode_StarBox,*FileNode_StarBox2,*FileNode_top;
    //开启进度条变化
    int lv = 0,oldLv = 0,dLv = 0;
    float percent1 = 0,percent2 = 0;
    bool isBar = false;
    bool isQieHuan = false;
    float maxPercent;
    float percentDx;
    LoadingBar* loadingBar_percent,*loadingBar_menu_percent;
    Text*Text_level_up,*Text_MenuLv;
    TextBMFont*Text_lv,*BitmapFontLabel_challenge;
    bool isAuto = false, isOut = true;
    //经验条背景
    Node* Image_Bar,*img_icon_gold;
    LevelUpView* LevelUpView;
    //记录音乐
    int SceneID = -1, SceneMusicID = -1;
    //奖励
    Node* FileNode_lunPan,*Button_fanPai;
    Button*btn_gift_lingqu,*Button_pause;
    bool isLunPan = false;
    float lunPanTime;
    Text* Text_Se;
    Text* Text_Mill,*text_lingqu,*Text_Sign_AD;
    
    //背包
    Node*FileNode_MyBag;
    //每局轮盘出现的次数1次
    int lunPanShowNum = 0;
    int fanPaiShowNum = 0;
    //轮盘动画交换
    bool isLunPanTime;
    //发牌结束后可以显示轮盘
    bool isShowLunPan;
    
    //是否刷新奖励
    bool isRefushGift = false;
    //按钮类型
    bool isHardDaily = false;
    bool isCeShiWin = false;

    //记录获得的经验
    int _winExp;
    int _extraScore;
    //星星宝箱用
    float percent;
    //连败场数
    int _faildNum;
    //鱼提示图片
    Node*menu_fish_tips;
    spine::SkeletonAnimation *_fishWinSkeletonNode;
    
public:
    bool getIsCeShiWin() { return isCeShiWin; }
    const shared_ptr<rapidjson::Document> &getLevelData() const;
    
    rapidjson::Value getRankArr()
    {
        if (!isParse)
        {
            rapidjson::Value arr;
            return arr;
        }
        
        return _randConfig["list"].GetArray();
    }
    
    int getMyRank();
    void updateRank();
private:
    rapidjson::Document _randConfig;
    bool isParse;
	void tipsFangCuo();
};

#endif /* GameViewHD_hpp */
