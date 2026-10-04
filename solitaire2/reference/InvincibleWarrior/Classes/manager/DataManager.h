/*
	数据管理器
	author:codehua
	time:2016年9月2日00:34:11
*/
# ifndef __DATA_MANAGER__
# define __DATA_MANAGER__

# include "cocos2d.h"
# include "UIUtils.h"
# include "SceneManager.h"
#include <external/json/document.h>

# define DATA_M DataManager::getInstance()
# define IS_MUSIC DATA_M->getIsMusic()
# define IS_SOUND DATA_M->getIsEffect()
# define GAME_TYPE DataManager::GameType

# define SET_IS_MUSIC(isMusic) DATA_M->setIsMusic(isMusic)

USING_NS_CC;


class DataManager : public Ref
{
public:
    enum class GameType {
    	None,
        Huo,        // 活局
        Random,    // 随机
        Level,    // 任务
        Daily,
    };

	static DataManager * getInstance();

	bool getIsMusic();
	void setIsMusic(bool isMusic);
    
    bool getIsEffect();
    void setIsEffect(bool isEffect);

    CC_SYNTHESIZE(bool, isBuying, IsBuying);//是否在购买中
    CC_SYNTHESIZE(int, gameHard, GameHard);//是否在购买中

	bool checkNowDay();
	int getKeepDay();
	void setKeepDay(int keepDay);
    //金币
	int getCoinNum();
	void setCoinNum(int delayNum,bool isTime,int type = 0);
    //钻石
    //int getDiamond();
    //void setDiamond(int num,bool isTime = false);
	//
	int getCardPicType(int shopType,int faceId = 0);
	void setCardPicType(int shopType,int picIndex,int faceId = 0);

    int getShopItemTotalCount(int shopType);
	bool getShopItemStatus(int shopType,int index);
	void unLockShopItemStatus(int shopType, int index);
    void unLockShopItemStatus(int shopType, int index,int num);
	int getShopItemPrice(int shopType, int index);
    int getCardFace();//返回 抽奖时 应该抽的牌组类型。由0-CARD_FACE_NUM-1
    bool getCardFaceStatus(int shopType,int index,int num);//返回此牌面是否获得
    int getCardFaceNum(int index);//返回目前拥有数
    
	bool getIsThreeModel();
	void setIsThreeModel(bool isThreeModel);
    inline bool getIsLeftModel() {
        return isLeftModel;
    }
	void setIsLeftModel(bool isLeftModel);

	static struct tm* getContentTime();
	static long getContentSec(int day, int hour, int min, int sec);
	static long getContentSec();
	void setAdsTime(long adsTime);
    void setRouletteTime(long time);
	void setFreeCoinTime(long freeCoinTime);
    void setFreeCoinTime1(long freeCoinTime);
    void setFreeCoinTime2(long freeCoinTime);
    void setFreeCoinTime3(long freeCoinTime);//轮盘
    void setFreeCoinTime4(long freeCoinTime);//翻牌
    void setFreeCoinTime5(long freeCoinTime);//限时挑战
	long getNextAdsTime();
	long getNextFreeCoinTime();
    long getNextFreeCoinTime1();
    long getNextFreeCoinTime2();
    long getNextFreeCoinTime3();
    long getNextFreeCoinTime4();
    long getNextFreeCoinTime5();
    long getNextRouletteTime(bool isAD);
    void updateFishVec();

	void playVideoAds(int type, int gold = 0);//播放视频广告
	void getFreeCoin();
    void setBannerVisible(bool isVisible);
	//---------------------游戏统计的数据----------------------

	time_t * getOneCardDatas();
	time_t * getThreeCardDatas();

	time_t * getCardDatas(int gameType);
    //获取天数
    int getYDay();
	void setGameData(int gameType,int index,int data);

	//胜利结算
	void settlementGameOnWin(int gameType, bool isUseBack, int score, int useTime, int moveNum, int extraScore, int star);
	//失败结算
	void settlementGameOnFail(int gameType, int useTime, int score);

    void lingqujinbi(int coinNum);
    void playLingQUAction();
    void playLingQUActionFangCuo();//领奖防错
    int lingquCoinNum = 0;
    int lingquType = 0;
//    bool isLingQu;
    void initAds();
    bool showNativeAds(int type = 1, const std::string &stype = "");
    void hideNativeAds(int type = 1);
    CC_SYNTHESIZE(bool, isLingQu, LingQu);
    CC_SYNTHESIZE(bool, isLingQuFangCuo, LingQuFangCuo);
    
    float frameSizeWidth = 100;
    float frameSizeHeight = 100;
    void setFrameSize(float w,float h);
    bool isLevelMode();
    bool isDailyMode();
    
    bool isHaveAds;//是否加载到广告
    bool getHaveVideo();
    void setIsHaveInterstitials(bool isHave);
    bool getHaveInterstitials();
    void setNetReachable(int netReachable) { _netReachable = netReachable;}
    int getNetReachable() { return _netReachable; }
    long getRewardCoin();
    long getRewardCoin1();
    
    bool hasRedPoint(bool reset, GameType type = GameType::Level); // 检测红点

    void setWinHDEnable(bool flag);
	bool isWinHDEnable();
//    CC_SYNTHESIZE(GameType, _gameType, GameType);
    GameType getGameType() { return _gameType; }
    bool thizGameTypeFirstStart();
    void setGameType(GameType gameType);
    
    //预判用户水平
    int userLevel();
    //洗牌次数
//    void setShulleNum(int num);
//    int getShulleNum();
    //是否在进行广告
    bool getPlayAds()
    {
        return isPlayAds;
    }
    void setPlayAds(bool is)
    {
        isPlayAds = is;
    }
    //判断是否时同一天
    bool isYday();
    //签到用
    bool sevenDayIsYday();
    //版本更新用
    void updatenewVerIsYday();
    bool newVerIsYday();
    //30s广告限制
    void setVideoAdsTime(float time,bool isChongZhi = false)
    {
        if(isChongZhi)
        {
            VideoAdsTime = 0;
        }
        else
        {
            VideoAdsTime += time;
        }
    }
    float getVideoAdsTime()
    {
        return VideoAdsTime;
    }
    
    void setIsVideoAdsTime(bool is)
    {
        isVideoAdsTime = is;
    }
    bool getIsVideoAdsTime()
    {
        return isVideoAdsTime;
    }
    
    void setInterstitialTime();
    int getInterstitialTime();
    
    void setIsInterstitial(bool is)
    {
        isInterstitial = is;
    }
    bool getIsInterstitial()
    {
        return isInterstitial;
    }
    
    void setIsShowAds(bool is)
    {
        isShowAds = is;
    }
    bool getIsShowAds()
    {
        return isShowAds;
    }
    
    //返回ns限制是否开启
    bool getLimit();
    //12s提示是否开启
    void setIsAutoTips(bool is);
    bool getIsAutoTips();
    
    //记录玩了几局限时关卡
    void setLimitTimeNum(int num);
    int getLimitTimeNum();
    //是否满足继续游戏
    GameType getLastGameType()
    {
        return _lastGameType;
    }
    //第一次开启游戏大厅显示的模式
    GameType getStartGameType()
    {
        return _startGameType;
    }
    bool getStartOne()
    {
        return isStartOne;
    }
    //---vegas-----
    void setIsWeiJiaSi(bool weiJiaSi);
    bool getIsWeiJiaSi()
    {
        return isWeiJiaSi;
    }
    void setIsWeiJiaSiJiFen(bool isLeiJi);
    bool getIsWeiJiaSiJiFen()
    {
        return isWeiJiaSiJiFen;
    }
    
    void setWeiJiaSiJiFen();
    void setWeiJiaSiJiFen(int jiFen, bool isThree = false);
    int getWeiJiaSiJiFen();
    
    int getWeiJiaSiJiFenThree();
    
    //星星宝箱
    void setStarBoxNumMax();
    int getStarBoxNumMax();
    void setStarBoxNum(int num,bool isZero = false);
    int getStarBoxNum();
    void setDailyStarBoxNumMax();
    int getDailyStarBoxNumMax();
    void setDailyStarBoxNum(int num,bool isZero = false);
    int getDailyStarBoxNum();
    //分享成功
    void shareYES();
    //获取金币提示
    void showCoinTips(int coin);
    
    //计算向量角度
    float getSinValue(float angle);
    float getCosValue(float angle);
    float getSpeedX(float speed,float moveAngle);
    float getSpeedY(float speed,float moveAngle);
    float getAngleByVector(float x,float y);
    Vec2 getVectorByAngle(float angle);
    //随机生成坐标
    void randVec(int num , std::vector<Vec2> *itemVec,float length);
    
    //记录新获得的道具
    void setPropNew(std::vector<int> idxVec);
    void setPropNew(int shopType,int index,int num = -1);
    int getPropNew(int shopType,int index);
    void propNewClear(int shopType = -1);
    void setIsPropNew(bool isNew);
    bool getIsPropNew();
    bool getIsPropNew(int showType);
    //记录新解锁的鱼
    void setFishNew(int index,int num = -1);
    bool getFishNew(int index);
    void fishNewClear();
    bool getIsFishNuw();
    //记录新解锁的鱼缸
    void setFashTankNew(int index,int num = -1);
    bool getFashTankNew(int index);
    void fashTankNewClear();
    bool getIsFashTankNuw();
    //结算场景防错
    void delayPlayBtn(std::function<void()> cb);
    //插屏顺利播放取消防错
    void stopDelayPlayBtn();
    long getFirstOpenTimeSec() { return firstOpenTimeSec; }
    inline bool recordLayerData() { return needRecordLayerData; }
    
    void addchongKaiNum(bool zero = false);
    void addSameChongKaiNum(bool zero = false);
    
    int getchongKaiNum() { return _chongKaiNum; }
    int getSameChongKaiNum() { return _samechongKaiNum; }
private:
	DataManager();
	static DataManager * dataManager;

	//背景跟牌面状态
	bool gameBgStatus[GAME_BG_NUM];
	bool cardFaceStatus[CARD_FACE_NUM];
	bool cardBgStatus[CARD_BG_NUM];
    //音乐
    bool musicStatus[LobbyMusicTotalCNT];
    //单张
    bool cardFaceStatus52[CARD_FACE_NUM][52];
	/////////////////////数据统计
	//胜利局数
	//失败局数
	//胜率
	//最快胜利时间
	//最长胜利时间
	//胜利最少步数
	//胜利最多步数
	//无返回胜利数
	//最高分数
	//当前连胜局数
	//最高连胜局数
	//总游戏时间
    //额外得分
    //总得分

	time_t oneCardDatas[CarDataCNT];
	time_t threeCardDatas[CarDataCNT];

	vector<int> gameBgPrices;
	vector<int> cardFacePrices;
	vector<int> cardBgPrices;

    int cardPicType[52];//牌面类型
	int cardBgType;//牌背类型
	int gameBgType;//游戏背景
    int musicType;//音乐

	bool isMusic; //音乐
    bool isEffect; //音效

	int coinNum;
    //int diamondNum;
	int keepDay;
    long firstOpenTimeSec; // 第一次打开应用的时间
    bool needRecordLayerData;

	bool isThreeModel;//翻三张
	bool isLeftModel;//左手模式
	long adsTime;
    long rouletteTime;
	long freeCoinTime;
    long freeCoinTime1 = 0;
    long freeCoinTime2 = 0;
    long freeCoinTime3 = 0;
    long freeCoinTime4 = 0;
    long freeCoinTime5 = 0;
    int _netReachable = 0;
    int _appStartCNT;
    GameType _gameType = GameType::None, _lastGameType = GameType::None,_startGameType = GameType::None;
    
    //用户评分
    float _toRate = -1;//辅助分
    float _toWinRate = -1;//胜率分
    float _toStarRate = -1;//星星分
    float _toScoreRate = -1;//得分分
    float _toShuffleRate =-1;//洗牌分
    float _toTipsRate = -1;//提示分
    string _userlevel="";
    //洗牌次数
//    int _shulleNum;
    //记录是否正在播放广告
    bool isPlayAds = false;
    //记录当前天数
    int d_yday;
    int seven_yday,newVer_yday;
    //30s广告限制
    float VideoAdsTime = 100;
    bool isVideoAdsTime = false;
    time_t InterstitialTime = 0;
    bool isInterstitial = true;
    bool isShowAds = true;
    //后台插屏 是否是第一次切后台
    CC_SYNTHESIZE(bool, isInitialHouTai, IsInitialHouTai);
    //是否开启自动提示
    bool isAutoTips;
    //记录玩了几局限时关卡
    int limitTimeNum;
    //是否第一次登陆
    bool isStartOne;
    //星星宝箱 限制增长
    int starBoxLimit;
    //星星宝箱 星星累计最大数目
    int starBoxNumMax;
    //星星宝箱 当前星星累计数目
    int starBoxNum;
    //星星宝箱 星星累计最大数目
    int dailyStarBoxNumMax;
    //星星宝箱 当前星星累计数目
    int dailyStarBoxNum;
    
    //记录新获得的道具类型1 2 3 5
    int gameBgNew[GAME_BG_NUM];
    int cardBgNew[CARD_BG_NUM];
    int cardFaceNew[CARD_FACE_NUM];
    int musicNew[LobbyMusicTotalCNT];
    int fishNew[FISH_NUM];
    int fashTankNew[FASH_TANK_NUM];
    
    bool isPropNew = false;
    
    //dyy
    int dyyNum;
    std::string dyyStr;
    
    //通知h插屏填充
    bool isHaveInterstitials;
    //vip免banner 插屏
    bool _vipNoAds;
    bool _isPurchaseLimit;
    //判定是否时登陆后的第一局
    bool _isStartOneGame;
    //累积重开次数
    int _chongKaiNum,_samechongKaiNum;
public:
	int getAppStartCNT() const;

	void setAppStartCNT(int _appStartCNT);
    //用户评级
    float getRate1()
    {
        return _toRate;
    }
    float getRate2()
    {
        return _toWinRate;
    }
    float getRate3()
    {
        return _toShuffleRate + _toTipsRate;
    }
    float getRate4()
    {
        return _toStarRate;
    }
    float getRate5()
    {
        return _toScoreRate;
    }
    string getRate6()
    {
        return _userlevel;
    }
    
    void setDyyNum(int num);
    void setDyyNum(const char* name);
    int getDyyNum();
    std::string getDyyStr();
    //返回部分语言
    std::string getSectionDyyStr();
    //返回全部语言
    std::string getAllDyyStr();
    
    //指定动画
    int endAniIdx;
    void setEndAniIdx(int idx);
    int getEndAniIdx();
    void setIsEndAniAll(bool is);
    bool getIsEndAniAll();
    bool isEndAniAll = true;
    //----vegas----
    bool isWeiJiaSi;//维加斯模式
    bool isWeiJiaSiJiFen;//维加斯累计积分
    int weiJiaSiJiFen;//维加斯积分
    
    
    //发牌动画
    void setStartAni(int id);
    int getStartAni();
    int startAni;
    
    //广告模式
    void setGuangGao(bool is);
    bool getGuangGao();
    bool isGuangGao;
    //解锁道具
    void jieSuoProp(bool isJieSuo);
    //vip免banner 插屏
    bool checkVipValid();
    void setVipNoAds(bool flag, time_t startTime = 0, time_t endTime = 0, int payid = 0);
    bool isVipNoAds() { return _vipNoAds; }
    void setPurchaseLimit(bool isLimit);
    bool getPurchaseLimit() { return _isPurchaseLimit; }
    
    //控制牌局难易度elo 用上局牌局信息判断
    int getElo();
    
    void setSevenOneVec(int idx,bool isOne);
    bool getSevenOneVec(int idx);
    void setIsGetSevenReward(bool isReward);
    bool getIsGetSevenReward();
public:
    enum class FishType
    {
        Fish0, //0  0
        Fish1, //1  1
        Fish2, //2  2
        Fish3, //3  3
        Fish4, //4  5
        Fish5, //5  6
        Fish6, //6  7
        Fish7, //7  10
        Fish8, //8  8
        Fish9, //9  12
        Fish10, //10    20
        Fish11, //11    13
        Fish12, //12    19
        Fish13, //13    17
        Fish14, //14    14
        
        Fish15, //15    21
        Fish16, //16    16
        Fish17, //17    15
        Fish18, //18    18
        Fish19, //19    9
        Fish20, //20    23
        Fish21, //21    4
        Fish22, //22    11
        Fish23, //23    22
        Fish24, //24    24
    };
    //记录已拥有的鱼id 与种类
    //方案1
    /*
     //记录鱼总数
     int fishCNT;
     //0-fishCNT 这些字段所记录的鱼的种类 同时也是鱼的id 字段从0开始 中间有鱼移除了将后面的数据字段前移
     */
    void setFishNum(int fishNum,int fashtankIdx);
    int getFishNum();
    int getFishNum(int idx);
    vector<int> getFishTypeVec(int fashtankIdx);
    void deleteFishTypeData(int deleteId,int fashtankIdx);
    void addFishTypeData(int id,int type);
    void setIsFishDie(int id,bool isDie);
    bool isFishDie(int id);
    void setCurrentFashTankIdx(int fashTankidx);
    int getCurrentFashTankIdx();
    void updateOfflineTime();
    int getOfflineTime();
    int getFishTypeNum(int fishType,int fashTank);
    //记录鱼掉落奖励时间
    void setClickFishTime(long time);
    int getClickFishTime();
    void setIsCeShiUnLock(bool isUnLock) { _isCeShiUnLock = isUnLock; }
    bool getIsCeShiUnLock() { return _isCeShiUnLock; }
    //给鱼缸解锁
    void setFashTankUnlock(int idx,int unlockIdx);
    bool getFashTankUnlock(int idx,int unlockIdx);
    vector<int> getFashTankUnlockVec(int idx);
    // 计算时间
    static long GAME_START_TS;
    //玩家名字
    void setMyName(string name);
    string getMyName() { return _myName; }
    //-------------排行榜奖励用
    //记录当前排行榜
    void setRankDailyTS(long time);
    long getRankDailyTS() { return _dailyTime; }
    //记录名次
    void setRank(int rank);
    int getOldRank() { return _myOldRank; }
    //判断是不是该领奖励了
    bool getIsRankReward();
    //领完了，或者没奖励可以领
    void resetRank();
    //初始化词库
    void initCiKu();
    bool isJinYongCi(string str);
    void setPlayerVer(string data);
    bool isNewVer();
    void setDayOfflineTime();
    long getDayOfflineTime();
    void addChallengeNum(bool isZero = false);
    int getChallengeNum();
    void setIsChallenge(bool isOpen);
    bool getIsChallenge();
    bool getIsChallengeOpen();
    void setIsChallengeOpenOne(bool isOne);
    bool getIsChallengeOpenOne();//首次弹出
private:
    vector<int> _fishNumVec;
    //用来储存鱼的id remove
    //vector<int> _fishTypeVec;
    vector<vector<int>> _fishTypeVec;
    //看看鱼饿死了没
    vector<vector<int>> _fishDieVec;
    //当前使用的场景idx
    int _currentFashTankIdx;
    //鱼缸解锁阶段
    vector<vector<int>> _fashTankUnlockVec;
    //记录离线时间
    long _offlineTime;
    //记录鱼掉落奖励时间
    long _clickFishTime;
    bool _isCeShiUnLock;
    string _myName;
    
    //-------------排行榜奖励用
    long _dailyTime,_oldDailyTime;
    int _myRank,_myOldRank;
    //词库
    rapidjson::Document _ciKuConfig;
    bool _isNewVer;
    //记录第三天与第七天首次奖励
    vector<bool> isSevenOneVec;
    //判断签到奖励领没领
    bool isGetSevenReward;
    //当天离线时间
    long dayOfflineTime;
    //限时挑战
    int challengeNum;
    bool isChallenge;
    int challengeOpenNum;
    bool isChallengeOpenOne;
};

# endif
