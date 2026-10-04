#include "DataManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#else
#include "AdsManager.h"
#include "VungleManager.h"
#include "GameKitHelper.h"
#endif
#include "ScoreManager.h"
#include "EventObserver.h"
#include "SpriteManager.h"
#include "TaskManager.h"
#include "EventObserver.h"
#include "GamePayment.h"
#include "DailyManager.h"
#include "ShopManager.h"
#include "GameBackground.h"
#include "Fish0.h"

long DataManager::GAME_START_TS = 0;
DataManager * DataManager::dataManager = nullptr;
const auto TEX_MIN0 = 2*60 + 30;
const auto TEX_MIN1 = 1*60 + 30;//
const auto TEX_MIN2 = 20*60;//
const auto TEX_MIN3 = 60;
const auto TEX_MIN4 = 60;
const auto TEX_MIN5 = 50;
const auto TEX_MIN6 = 60 * 60 * 3;//3个小时
const auto TEX_MIN7 = 60 * 60 * 48;//48个小时
static bool s_isWinHDEnable;
static const int DaySec = 24*60*60;

DataManager::DataManager()
{
    _isNewVer = false;
    _isCeShiUnLock = false;
    _currentFashTankIdx = GETINTEGER("_currentFashTankIdx",0);
    auto shopManager = ShopManager::getInstance();
    for(int i = 0;i < FASH_TANK_NUM;++i)
    {
        if(i == 0)
        {
            _fishNumVec.push_back(GETINTEGER(StringUtils::format("fishNum_%d", i).c_str(),1));
        }
        else
        {
            _fishNumVec.push_back(GETINTEGER(StringUtils::format("fishNum_%d", i).c_str(),0));
        }
        
        vector<int> vec;
        vector<int> dieVec;
        for(int j = 0;j < _fishNumVec.at(i);++j)
        {
         
            
            vec.push_back(GETINTEGER(StringUtils::format("fishType_%d_%d", i,j).c_str(), i));
            
            
            dieVec.push_back(GETINTEGER(StringUtils::format("fishDie_%d_%d",i , j).c_str(), 0));
            
        }
        _fishTypeVec.push_back(vec);
        _fishDieVec.push_back(dieVec);
        
        //记录鱼缸解锁阶段 _fashTankUnlockVec
        vector<int> unlockVec;
        auto num = shopManager->getFashTankUnlockNum(i);
        for(int j = 0;j < num;++j)
        {
            unlockVec.push_back(GETINTEGER(StringUtils::format("fashTankUnlockVec_%d_%d", i,j).c_str(), 0));
        }
        _fashTankUnlockVec.push_back(unlockVec);
    }
    
    for(int i = 0;i < 2;++i)
    {
        isSevenOneVec.push_back(GETBOOL(StringUtils::format("isSevenOneVec_%d", i).c_str(),false));
    }
    //是第二天
    d_yday = GETINTEGER("GameYDay",0);
    seven_yday = GETINTEGER("SevenYDay",0);
    newVer_yday = GETINTEGER("NewVerYDay",0);
    dayOfflineTime = 0;
    
    auto isDay = sevenDayIsYday();
    if(isDay)
    {
        isGetSevenReward = false;
        SETBOOL("isGetSevenReward",false);
    }
    else
    {
        isGetSevenReward = GETBOOL("isGetSevenReward",false);
    }
    
    challengeNum = GETINTEGER("challengeNum",0);
    isChallenge = GETBOOL("isChallenge",false);
    challengeOpenNum = GETINTEGER("challengeOpenNum",0);
    isChallengeOpenOne = GETBOOL("isChallengeOpenOne",true);
    
    
    _myName = GETSTR("fish_myName","");;
    _oldDailyTime = GETINTEGER("_oldDailyTime",-1);
    _dailyTime = GETINTEGER("_dailyTime",-1);
    _myOldRank = GETINTEGER("_myOldRank",-1);
    _myRank = GETINTEGER("_myRank",-1);
    _chongKaiNum = GETINTEGER("_chongKaiNum",0);
    _samechongKaiNum = GETINTEGER("_samechongKaiNum",0);
    //开始动画
    startAni = GETINTEGER("startAni",0);
    //广告模式
    isGuangGao = GETBOOL("isGuangGao",false);
    starBoxLimit = GETINTEGER("starBoxLimit",1);
    starBoxNumMax = GETINTEGER("fish_starBoxNumMax",1);
    starBoxNum = GETINTEGER("fish_starBoxNum",0);
    dailyStarBoxNumMax = GETINTEGER("dailyStarBoxNumMax",2);
    dailyStarBoxNum = GETINTEGER("dailyStarBoxNum",0);
    limitTimeNum = GETINTEGER("limitTimeNum",0);
    //指定结束动画
    endAniIdx = GETINTEGER("endAniIdx",1);//1-7
    //开启随机动画
    isEndAniAll = GETBOOL("isEndAniAll",true);
    //dyy
    dyyNum = GETINTEGER("dyyNum",-1);
    //初始开启
    isAutoTips = GETBOOL("isAutoTips", true);
    //是否是第一次切后台
    isInitialHouTai = true;
    //第一次启动时大厅显示的模式
    _startGameType = (GameType)GETINTEGER("startGameType",(int)GameType::Huo);
    //是否是第一次登陆
    isStartOne = GETBOOL("isStartOne",true);
    
    isWeiJiaSi = GETBOOL("isWeiJiaSi",false);//是否是 维加斯模式
    isWeiJiaSiJiFen = GETBOOL("isWeiJiaSiJiFen",false);//是否 累计维加斯计分
    
	isMusic = GETBOOL("isMusic",true);
    isEffect = GETBOOL("isEffect",true);
    
	isThreeModel = GETBOOL("isThreeModel", false);
	isLeftModel = GETBOOL("isLeftModel",false);
    
    if(!isThreeModel)
    {
        weiJiaSiJiFen = GETINTEGER("weiJiaSiJiFen",-52);//维加斯模式初始积分 -52
    }
    else
    {
        weiJiaSiJiFen = GETINTEGER("weiJiaSiJiFenThree", -52);
    }

    for(int i = 0;i < 52; ++i)
    {
        auto type =  GETINTEGER(StringUtils::format("cardPicType_%d",i).c_str(), 0);//牌面类型
        if (type>=CARD_FACE_NUM) {     // 容错
            type = 0;
        }
        cardPicType[i] = type;
    }
	
    
    
	cardBgType = GETINTEGER("cardBgType", 0);//牌背类型
    if (cardBgType>=CARD_BG_NUM) {
        cardBgType = 0;
    }
	gameBgType = GETINTEGER("gameBgType", 0);//游戏背景
    if (gameBgType>=GAME_BG_NUM) {
        gameBgType = 0;
    }
    musicType = GETINTEGER("musicType", -1);//音乐
    if (musicType>=LobbyMusicTotalCNT) {
        musicType = 0;
    }
    
    gameHard = GETINTEGER("gameHard", 100);

	adsTime = GETINTEGER("adsTime", 0);
    rouletteTime = GETINTEGER("rouletteTime", 0);
	freeCoinTime = GETINTEGER("freeCoinTime", 0);
    freeCoinTime1 = GETINTEGER("freeCoinTime1", 0);
    freeCoinTime2 = GETINTEGER("freeCoinTime2", 0);
    freeCoinTime3 = GETINTEGER("freeCoinTime3", 0);
    freeCoinTime4 = GETINTEGER("freeCoinTime4", 0);
    freeCoinTime5 = GETINTEGER("freeCoinTime5", 0);
    _offlineTime = GETINTEGER("offlineTime", 0);
    _clickFishTime = GETINTEGER("clickFishTime", 0);
    InterstitialTime = 0;//插屏cd
    isHaveAds = false;
    isHaveInterstitials = false;
    
    gameBgPrices = UIUtils::getGameBgPrices();
    cardFacePrices = UIUtils::getCardFacePrices();
    cardBgPrices = UIUtils::getCardBgPrices();
	//数据统计
	for (int i = 1; i <= CarDataCNT; i++)
	{
        
		oneCardDatas[i - 1] = GETINTEGER(StringUtils::format("oneCardData_%d",i).c_str(), 0);
		threeCardDatas[i - 1] = GETINTEGER(StringUtils::format("threeCardData_%d", i).c_str(), 0);
	}

    ValueVector data;
	for (int i = 0; i < GAME_BG_NUM; i++)
	{
		if ( i == 0 || i == 18 )
		{
			gameBgStatus[i] = GETINTEGER(StringUtils::format("gameBgStatus_%d",i).c_str(), true);
		}
		else
		{
            gameBgStatus[i] = GETINTEGER(StringUtils::format("gameBgStatus_%d", i).c_str(),false);
            //gameBgStatus[i] = GETINTEGER(StringUtils::format("gameBgStatus_%d", i).c_str(), getShopItemPrice(1, i)==0?true:false);
		}
        ValueMap item;
        item["i"] = i;
        item["t1"] = "shop";
        item["t2"] = "bg";
        item["st"] = gameBgType==i?2:(int)gameBgStatus[i];
        data.push_back(Value(item));
	}

	for (int i = 0; i < CARD_FACE_NUM; i++)
	{
		if (i == 0)
		{
			cardFaceStatus[i] = GETINTEGER(StringUtils::format("cardFaceStatus_%d", i).c_str(), true);
		}
		else
		{
            cardFaceStatus[i] = GETINTEGER(StringUtils::format("cardFaceStatus_%d", i).c_str(), false);
			//cardFaceStatus[i] = GETINTEGER(CCString::createWithFormat("cardFaceStatus_%d", i)->getCString(), false);
		}
//        ValueMap item;
//        item["i"] = i;
//        item["t1"] = "shop";
//        item["t2"] = "face";
//        item["st"] = cardPicType==i?2:(int)cardFaceStatus[i];
//        data.push_back(Value(item));
	}
    
    for (int i = 0; i < CARD_FACE_NUM; i++)
    {
        for(int j = 0;j < 52;++j)
        {
            if (i == 0)
            {
                cardFaceStatus52[i][j] = GETINTEGER(StringUtils::format("cardFaceStatus_%d_%d", i, j).c_str(), true);
            }
            else
            {
                cardFaceStatus52[i][j] = GETINTEGER(StringUtils::format("cardFaceStatus_%d_%d", i, j).c_str(), cardFaceStatus[i]);  // 老用户获得了就直接有
                //cardFaceStatus[i] = GETINTEGER(CCString::createWithFormat("cardFaceStatus_%d", i)->getCString(), false);
            }
        }
    }
    
    
	for (int i = 0; i < CARD_BG_NUM; i++)
	{
		if (i == 0)
		{
			cardBgStatus[i] = GETINTEGER(StringUtils::format("cardBgStatus_%d", i).c_str(), true);
		}
		else
		{
            cardBgStatus[i] = GETINTEGER(StringUtils::format("cardBgStatus_%d", i).c_str(), false);
			//cardBgStatus[i] = GETINTEGER(CCString::createWithFormat("cardBgStatus_%d", i)->getCString(), false);
		}
        ValueMap item;
        item["i"] = i;
        item["t1"] = "shop";
        item["t2"] = "back";
        item["st"] = cardBgType==i?2:(int)cardBgStatus[i];
        data.push_back(Value(item));
	}
    
    //音乐
    for(int i = 0;i < LobbyMusicTotalCNT;++i)
    {
        if(i == 0)
        {
            musicStatus[i] = GETINTEGER(StringUtils::format("musicStatus_%d", i).c_str(), false);
        }
        else
        {
            musicStatus[i] = GETINTEGER(StringUtils::format("musicStatus_%d", i).c_str(), false);
        }
        ValueMap item;
        item["i"] = i;
        item["t1"] = "shop";
        item["t2"] = "music";
        item["st"] = musicType==i?2:(int)musicStatus[i];
        data.push_back(Value(item));
    }
    
    UIUtils::FIRFirestoreAdd("userInfo", {
        {"data", Value(data)}
    });
    //BagNEW
    propNewClear();
    fishNewClear();
    fashTankNewClear();
    

	keepDay = GETINTEGER("keepDay", 0);
    coinNum = GETINTEGER("fish_coinNum", 0);
    //diamondNum = GETINTEGER("fish_diamondNum", 0);
    _vipNoAds = GETBOOL("key_vip_noads", false); // vip免广告订阅
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    _vipNoAds = _vipNoAds && checkVipValid(); // 检查时限
#endif
    _isPurchaseLimit = GETBOOL("isPurchaseLimit", false);
    
    
    setBannerVisible(!_vipNoAds);
    
    //_shulleNum = GETINTEGER("shulleNum", 2);
    isBuying = false;

    _gameType = UIUtils::getNetworkState() == 0?DataManager::GameType::Random:DataManager::GameType::Huo;
    s_isWinHDEnable = UserDefault::getInstance()->getBoolForKey("config_winend_ani", true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	_netReachable = true;
#endif
    
    // 记录安装时间
    auto tm = getContentTime();
    auto yyear = GETINTEGER("key_firstopen_yyear", 0);
    auto yday = GETINTEGER("key_firstopen_yday", 0);
    ValueMap valueMap1;
    if (yyear == 0 || yday == 0) { // 第一次打开
        SETINTEGER("key_firstopen_yyear", tm->tm_year);
        SETINTEGER("key_firstopen_yday", tm->tm_yday);
        UIUtils::FIRAnalyticsEvent("event_game_firstopen",
                                   valueMap1);
    }
    else { // 回访
        bool isNextDay = false;
        if (yyear == tm->tm_year) { // 同一年
            if (yday == tm->tm_yday-1) { // 次日
                isNextDay = true;
            }
        }
        else if (yyear == tm->tm_year - 1) { // 不同年
            auto isLeay = DailyManager::isLeayYear(yyear);
            if (yyear == (isLeay?365:364) && tm->tm_yday == 0)
            {
                isNextDay = true;
            }
        }
        if (isNextDay) {
            UIUtils::FIRAnalyticsEvent("2d_retention",
                                       valueMap1);
        }
    }

    firstOpenTimeSec = stol(GETSTR("key_firstopen_timesec", "0").c_str());
    auto timeNowSec = getContentSec();
    if (firstOpenTimeSec == 0) {
        firstOpenTimeSec = timeNowSec;
        SETSTR("key_firstopen_timesec", toString(firstOpenTimeSec));
    }
    needRecordLayerData = timeNowSec-firstOpenTimeSec<=DaySec;
    
    //判定是否时登陆后的第一局 计算牌局难度用
    _isStartOneGame = true;
    
    
    initCiKu();
}

bool DataManager::thizGameTypeFirstStart()
{
    bool flag = false;
    if (_lastGameType == GameType::None || _lastGameType != _gameType) {
        flag = true;
        _lastGameType = _gameType;
    }
    return flag;
}

void DataManager::setGameType(GameType gameType)
{
    if (_gameType != gameType) {
        _lastGameType = _gameType;
        _gameType = gameType;
        SETINTEGER("startGameType",(int)gameType);
        SPRITE_M->setShufflingFirst(SpriteManager::ShuffingType::Box);
    }
    else if (_lastGameType == GameType::None)
    {
        _lastGameType = _gameType;
    }
    else if(_gameType == GameType::Huo||_gameType == GameType::Random)
    {
        _lastGameType = _gameType;
    }
}

DataManager * DataManager::getInstance()
{
	if (dataManager == nullptr)
	{
		dataManager = new DataManager();
	}

	return dataManager;
}

bool DataManager::getIsMusic()
{
	return isMusic;
}

void DataManager::setIsMusic(bool isMusic)
{
	this->isMusic = isMusic;
	SETBOOL("isMusic",isMusic);

	if (isMusic == true)
	{
		SOUND_M->resumeGameBgMusic();
	}
	else
	{
		SOUND_M->pauseGameBgMusic();
	}
}

bool DataManager::getIsEffect() {
    return isEffect;
}

void DataManager::setIsEffect(bool isEffect) {
    SETBOOL("isEffect", isEffect);
    if (this->isEffect != isEffect) {
        this->isEffect = isEffect;
    }
    if (isEffect == true)
    {
        SOUND_M->setEffectVolume(1);
    }
    else
    {
        SOUND_M->setEffectVolume(0);
    }
}
 
int DataManager::getCardPicType(int shopType,int faceId)
{
	if (shopType == 1)
	{
		return gameBgType;
	}
	else if (shopType == 2)
	{
        return cardPicType[faceId];
	}
	else if (shopType == 3)
	{
		return cardBgType;
	}
    else if(shopType == 5)
    {
        return musicType;
    }
}

void DataManager::setCardPicType(int shopType, int picIndex,int faceId)
{
    ValueVector data;
    ValueMap preitem;
    ValueMap item;
    item["i"] = picIndex;
	if (shopType == 1)
	{
        preitem["t2"] = "bg";
        item["t2"] = "bg";
        preitem["i"] = gameBgType;
		gameBgType = picIndex;
		SETINTEGER("gameBgType", picIndex);
	}
	else if (shopType == 2)
	{
        preitem["t2"] = "face";
        item["t2"] = "face";
        preitem["i"] = cardPicType;
        cardPicType[faceId] = picIndex;
        SETINTEGER(StringUtils::format("cardPicType_%d",faceId).c_str(), picIndex);
	}
	else if (shopType == 3)
	{
        preitem["t2"] = "back";
        item["t2"] = "back";
        preitem["i"] = cardBgType;
		cardBgType = picIndex;
		SETINTEGER("cardBgType", picIndex);
	}
    else if(shopType == 5)
    {
        preitem["t2"] = "music";
        item["t2"] = "music";
        preitem["i"] = musicType;
        musicType = picIndex;
        SETINTEGER("musicType", picIndex);
    }
    FLUSH();
    
    item["t1"] = "shop";
    item["st"] = 2;
    data.push_back(Value(item));
    preitem["t1"] = "shop";
    preitem["st"] = 1;
    data.push_back(Value(preitem));
    
    UIUtils::FIRFirestoreAdd("userInfo", {
        {"data", Value(data)}
    });
}

int DataManager::getShopItemTotalCount(int shopType)
{
    if (shopType == 1)
    {
        return GAME_BG_NUM;
    }
    else if (shopType == 2)
    {
        return CARD_FACE_NUM;
    }
    else if (shopType == 3)
    {
        return CARD_BG_NUM;
    }
    else if(shopType == 5)
    {
        return LobbyMusicTotalCNT;
    }
    return 0;
}

bool DataManager::getShopItemStatus(int shopType, int index)
{
	if (shopType == 1)
	{
		return gameBgStatus[index];
	}
	else if (shopType == 2)
	{
		return cardFaceStatus[index];
	}
	else if (shopType == 3)
	{
		return cardBgStatus[index];
	}
    else if(shopType == 5)
    {
        return musicStatus[index];
    }

    return false;
}

bool DataManager::getCardFaceStatus(int shopType,int index,int num)
{
    if (shopType == 2)
    {
        return cardFaceStatus52[index][num];
    }
}

int DataManager::getShopItemPrice(int shopType, int index)
{
	if (shopType == 1)
	{
		return gameBgPrices[index];
	}
	else if (shopType == 2)
	{
		return cardFacePrices[index];
	}
	else if (shopType == 3)
	{
		return cardBgPrices[index];
	}
}

void DataManager::unLockShopItemStatus(int shopType, int index,int num)
{
    if (shopType == 2)
    {
        cardFaceStatus52[index][num] = true;
        SETINTEGER(StringUtils::format("cardFaceStatus_%d_%d", index,num).c_str(), true);
        int temp = 0;
        for(int i = 0;i<52;++i)
        {
            auto is = cardFaceStatus52[index][i];
            if(is)
            {
                temp++;
            }
        }
        if(temp == 52)
        {
            cardFaceStatus[index] = true;
            SETINTEGER(StringUtils::format("cardFaceStatus_%d", index).c_str(), true);
        }
    }
}

int DataManager::getCardFace()
{//返回 抽奖时 应该抽的牌组类型。由0-CARD_FACE_NUM-1
    int temp = -1;
    for(int i = 0;i < CARD_FACE_NUM;++i)
    {
        auto is = cardFaceStatus[i];
        if(!is)
        {
            temp = i;
            break;
        }
    }
    return temp;
}

int DataManager::getCardFaceNum(int index)
{
    int temp = 0;
    for(int i = 0;i<52;++i)
    {
        auto is = cardFaceStatus52[index][i];
        if(is)
        {
            temp++;
        }
    }
    return temp;
}

void DataManager::unLockShopItemStatus(int shopType, int index)
{
    ValueVector data;
    ValueMap item;
    item["i"] = index;
	if (shopType == 1)
	{
        item["t2"] = "bg";
        gameBgStatus[index] = true;
		SETINTEGER(StringUtils::format("gameBgStatus_%d", index).c_str(), true);
	}
	else if (shopType == 2)
	{
        item["t2"] = "face";
        cardFaceStatus[index] = true;
		SETINTEGER(StringUtils::format("cardFaceStatus_%d", index).c_str(), true);
	}
	else if (shopType == 3)
	{
        item["t2"] = "back";
        cardBgStatus[index] = true;
        SETINTEGER(StringUtils::format("cardBgStatus_%d", index).c_str(), true);
	}
    else if(shopType == 5)
    {
        musicStatus[index] = true;
        SETINTEGER(StringUtils::format("musicStatus_%d", index).c_str(), true);
    }
    FLUSH();
    
    //以往的反馈
    item["t1"] = "shop";
    item["st"] = 1;
    data.push_back(Value(item));
    
    UIUtils::FIRFirestoreAdd("userInfo", {
        {"data", Value(data)}
    });
}

//返回金币数
int DataManager::getCoinNum()
{
	return coinNum;
}

void DataManager::setCoinNum(int delayNum,bool isTime,int type)
{
	coinNum += delayNum;
	if (coinNum < 0)
	{
		coinNum = 0;
	}
    else if(coinNum >= 9999999)
    {
        coinNum = 9999999;
    }
	SETINTEGER("fish_coinNum",coinNum);
    UIUtils::FIRAnalyticsUserProperty("gold", toString(coinNum));
    UIUtils::FIRFirestoreAdd("set", {
        {"table", Value("info")},
        {"kkey", Value("gold")},
        {"value", Value(coinNum)},
    });
    UIUtils::FIRFirestoreAddOP("gold", toString(coinNum), toString(delayNum), toString(type));
}

//int DataManager::getDiamond()
//{
//    return diamondNum;
//}
//void DataManager::setDiamond(int num,bool isTime)
//{
//    diamondNum+=num;
//    if (diamondNum < 0)
//    {
//        diamondNum = 0;
//    }
//    else if(diamondNum >= 9999999)
//    {
//        diamondNum = 9999999;
//    }
//    SETINTEGER("diamondNum",diamondNum);
//    UIUtils::FIRAnalyticsUserProperty("diamond", toString(diamondNum));
//    UIUtils::FIRFirestoreAdd("set", {
//        {"table", Value("info")},
//        {"kkey", Value("diamond")},
//        {"value", Value(diamondNum)},
//    });
//}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
	//方法名与java类中的包名+方法名，以下划线连接 org.cocos2dx.cpp
	void Java_org_cocos2dx_cpp_PayTool_paySuccess(JNIEnv*  env, jobject thiz, jint a)
	{
		//DATA_M->buySuccess(a);
	}
}
#endif

int DataManager::getKeepDay()
{
	return keepDay;
}

void DataManager::setKeepDay(int keepDay)
{
	this->keepDay = keepDay;
	SETINTEGER("keepDay", keepDay);
}

bool DataManager::checkNowDay()
{
	//判断是否领取过
	struct tm *tm;
	time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	time(&timep);
#else  
	struct  timeval  now;
	gettimeofday(&now, NULL);
	timep = now.tv_sec;
#endif  

	tm = localtime(&timep);
	int contentDay = tm->tm_yday;

	int keepDay = DATA_M->getKeepDay();
	if (contentDay != keepDay)
	{
		//这代表是新的一天--
		//DATA_M->setGift_YWJX_Status(false);
		DATA_M->setKeepDay(contentDay);
		return true;
	}
	return false;
	//return DATA_M->getGift_YWJX_Status();
}


bool DataManager::getIsThreeModel()
{
	return isThreeModel;
}

void DataManager::setIsThreeModel(bool isThreeModel)
{
	this->isThreeModel = isThreeModel;
	SETBOOL("isThreeModel", isThreeModel);
    FLUSH();
    
    if(isThreeModel)
    {//切换维加斯模式计分
        weiJiaSiJiFen = GETINTEGER("weiJiaSiJiFenThree",-52);//维加斯模式初始积分 -52
    }
    else
    {
        weiJiaSiJiFen = GETINTEGER("weiJiaSiJiFen", -52);
    }
}

//bool DataManager::getIsLeftModel()
//{
//    return isLeftModel;
//}

void DataManager::setIsLeftModel(bool isLeftModel)
{
	this->isLeftModel = isLeftModel;
	SETBOOL("isLeftModel", isLeftModel);
	FLUSH();
}

struct tm* DataManager::getContentTime(){

	time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	time(&timep);
#else  
	struct timeval now;
	gettimeofday(&now, NULL);
	timep = now.tv_sec;
#endif  
	return localtime(&timep);
}

long DataManager::getContentSec(int day, int hour, int min, int sec){

	return ((day * 24 + hour) * 60 + min) * 60 + sec;
}

long DataManager::getContentSec(){

	struct tm* tm = getContentTime();
	return getContentSec(tm->tm_yday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void DataManager::setRouletteTime(long time)
{
    rouletteTime = time;
    SETINTEGER("rouletteTime", time);
}

void DataManager::setAdsTime(long adsTime)
{
	this->adsTime = adsTime;
	SETINTEGER("adsTime", adsTime);
}

void DataManager::setFreeCoinTime(long freeCoinTime)
{
	this->freeCoinTime = freeCoinTime + TEX_MIN0 - 1; //免费金币是2分30一次;
	SETINTEGER("freeCoinTime", this->freeCoinTime);
}

void DataManager::setFreeCoinTime1(long freeCoinTime)
{
    this->freeCoinTime1 = freeCoinTime + TEX_MIN1 - 1; //免费金币是1分钟30一次;
    SETINTEGER("freeCoinTime1", this->freeCoinTime1);
}

void DataManager::setFreeCoinTime2(long freeCoinTime)
{
    this->freeCoinTime2 = freeCoinTime + TEX_MIN2 - 1; //免费金币是20分钟一次;
    SETINTEGER("freeCoinTime2", this->freeCoinTime2);
}

void DataManager::setFreeCoinTime3(long freeCoinTime)
{
    this->freeCoinTime3 = freeCoinTime + TEX_MIN3 - 1; //轮盘60s
    SETINTEGER("freeCoinTime3", this->freeCoinTime3);
}
void DataManager::setFreeCoinTime4(long freeCoinTime)
{
    this->freeCoinTime4 = freeCoinTime + TEX_MIN4 - 1; //翻牌60s;
    SETINTEGER("freeCoinTime4", this->freeCoinTime4);
}

void DataManager::setFreeCoinTime5(long freeCoinTime)
{
    this->freeCoinTime5 = freeCoinTime + TEX_MIN7 - 1;
    SETINTEGER("freeCoinTime5", this->freeCoinTime5);
}

long DataManager::getNextRouletteTime(bool isAD)
{
    time_t contentTime = getContentSec();
    
    time_t nextTime = rouletteTime + 60 * 20 + 4; //轮盘 20分钟玩一次
    
    if (nextTime - contentTime < 0){
        if(isAD)
        {
            setRouletteTime(contentTime);
            CCLOG("%d",contentTime);
        }
        
        //重新加载广告
        //AdsManager::createVideoAds();
        return 0;
    }
    
    return nextTime - contentTime;
}

long DataManager::getNextAdsTime()
{
	time_t contentTime = getContentSec();

	time_t nextTime = adsTime + 60 * 1 + 30 - 1; //广告是1分钟30才能看一次

	if (nextTime - contentTime < 0){
		setAdsTime(nextTime);
        //重新加载广告
        //AdsManager::createVideoAds();
		return 0;
	}

	return nextTime - contentTime;
}

long DataManager::getNextFreeCoinTime()
{//场景奖励出现时间
	time_t contentTime = getContentSec();

    if (contentTime > freeCoinTime) {
        return 0;
    }
    return freeCoinTime-contentTime;
}

long DataManager::getNextFreeCoinTime1()
{//freecoin
    time_t contentTime = getContentSec();
    
    if (contentTime > freeCoinTime1) {
        return 0;
    }
    return freeCoinTime1-contentTime;
}

long DataManager::getNextFreeCoinTime2()
{//已禁用
    time_t contentTime = getContentSec();
    
    if (contentTime > freeCoinTime2) {
        return 0;
    }
    return freeCoinTime2-contentTime;
}

long DataManager::getNextFreeCoinTime3()
{//轮盘 60
    time_t contentTime = getContentSec();
    
    if (contentTime > freeCoinTime3) {
        return 0;
    }
    return freeCoinTime3-contentTime;
}

long DataManager::getNextFreeCoinTime4()
{//翻牌 60
    time_t contentTime = getContentSec();
    
    if (contentTime > freeCoinTime4) {
        return 0;
    }
    return freeCoinTime4-contentTime;
}

long DataManager::getNextFreeCoinTime5()
{//
    time_t contentTime = getContentSec();
    
    if (contentTime > freeCoinTime5) {
        return 0;
    }
    return freeCoinTime5-contentTime;
}

void DataManager::lingqujinbi(int coinNum)
{
    //观看视频任务增加计数
    TASK_M->addTaskADS();
    if(isLingQuFangCuo)
    {//出现了先关闭后完成的视频
        playLingQUActionFangCuo();
    }
    
	if (lingquType == 4) { // 复活
        EVENT_M->sendEvent("event_game_level_relive");
		//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_level_relive");
		return;
	}
    

    setCoinNum(lingquCoinNum,false, lingquType);
    if (lingquType == 3) {
        //setFreeCoinTime1(getContentSec());
    }
    else if (lingquType == 0){
        //setFreeCoinTime(getContentSec());
        //通知游戏界面删除礼包z
        SCENE_M->refushGift();
    }
    SCENE_M->refushShopScene();
    isLingQu = true;
    
    UIUtils::FIRFirestoreAddOP("gold_lingqu", toString(coinNum), toString(lingquType));
}

void DataManager::playLingQUAction()
{
    //广告结束了
    if(!isPlayAds)
    {//有两次进入
        return;
    }
    isPlayAds = false;
    if(!isLingQu)
    {//有广告播完后 先走的这里，关闭后才走完成回调
        //提前关闭视频的话 取消游戏内暂停
        EVENT_M->sendEvent("msg_game_pause");
        isLingQuFangCuo = true;
        return;
    }
    
    isLingQu = true;
    ValueMap params = {
            {"key", Value("videolingqu")},
            {"value", Value(lingquType)}
    };
    UIUtils::FIRFirestoreAdd("operator", params);
    UIUtils::FIRAnalyticsEventWithPrefix("AD_SHOW_VIDEO_" + toString(lingquType));
    UIUtils::FIRAnalyticsEvent("ads_video_lingqu", params);

    // 防止跳过
    if(lingquType == 5)
    {//背包中播放获取道具动画 并更新次数
        EVENT_M->sendEvent("event_game_bag_Shuffle");
        return;
    }
    else if(lingquType == 6)
    {//
        EVENT_M->sendEvent("event_game_roulette");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_roulette");
        //通知游戏界面删除礼包z
        //轮盘第五次开始 5分钟cd
        auto num = GETINTEGER("lunPanNum",4);
        int dx = 0;
        if(num == 0) dx = 60 * 4;
        DATA_M->setFreeCoinTime3(DATA_M->getContentSec() + dx);
        SCENE_M->refushGift();
        return;
    }
    else if(lingquType == 7)
    {//增加道具次数
        EVENT_M->sendEvent("event_game_multiple_gold");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_multiple_gold");
        isLingQu = true;
        return;
    }
    else if(lingquType == 8)
    {//经典结算
        EVENT_M->sendEvent("event_game_winLayer");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_winLayer");
        isLingQu = true;
        return;
    }
    else if(lingquType == 9)
    {//每日结算
        EVENT_M->sendEvent("event_game_winLayer");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_winDailyLayer");
        isLingQu = true;
        return;
    }
    else if(lingquType == 10)
    {//
        EVENT_M->sendEvent("msg_game_lingqu");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_lingqu");
        isLingQu = true;
        setFreeCoinTime(getContentSec());
        //通知游戏界面删除礼包z
        SCENE_M->refushGift();
        return;
    }
    else if(lingquType == 11)
    {//
        EVENT_M->sendEvent("event_game_update_fanPai");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_update_fanPai");
        isLingQu = true;
        //翻牌时间重置
        setFreeCoinTime4(getContentSec());
        //通知游戏界面删除礼包z
        SCENE_M->refushGift();
        return;
    }
    else if(lingquType == 12)
    {//关卡结算
        EVENT_M->sendEvent("event_game_winLevelLayer");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_winLevelLayer");
        isLingQu = true;
        return;
    }
    else if(lingquType == 13)
    {//游戏中领取金币
        EVENT_M->sendEvent("msg_game_lingqu_game");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_lingqu_game");
        isLingQu = true;
        setFreeCoinTime(getContentSec());
        //通知游戏界面删除礼包z
        SCENE_M->refushGift();
        return;
    }
    else if(lingquType == 14)
    {//签到
        EVENT_M->sendEvent("event_lobby_seven");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_lobby_seven");
        isLingQu = true;
        return;
    }
    else if(lingquType == 15 || lingquType == 16)
    {//领取金币
        EVENT_M->sendEvent("event_lobby_freeCoin");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_lobby_freeCoin");
        isLingQu = true;
        return;
    }
    else if(lingquType == 17)
    {//游戏内播放获取道具动画 并更新次数
        EVENT_M->sendEvent("event_game_game_Shuffle");
        return;
    }
//    SOUND_M->playEffectMusic(EffectCoin);
//    string huodejinbi = UIUtils::getStringByName("huodejinbi");
//    SCENE_M->showTips(CCString::createWithFormat(huodejinbi.c_str(), lingquCoinNum)->getCString());
}

void DataManager::playLingQUActionFangCuo()
{
    if(!isPlayAds)
    {//有两次进入
        return;
    }
    //广告结束了
    isPlayAds = false;
    //观看视频任务增加计数
    TASK_M->addTaskADS();
    ValueMap params = {
            {"key", Value("videolingqu")},
            {"value", Value(lingquType)}
    };
    UIUtils::FIRFirestoreAdd("operator", params);
    UIUtils::FIRAnalyticsEventWithPrefix("AD_SHOW_VIDEO_" + toString(lingquType));
    UIUtils::FIRAnalyticsEvent("ads_video_lingqu", params);

    isLingQu = true;
    // 防止跳过
    if(lingquType == 5)
    {//播放获取道具动画 并更新次数
        EVENT_M->sendEvent("event_game_bag_Shuffle");
        return;
    }
    else if(lingquType == 6)
    {//
        EVENT_M->sendEvent("event_game_roulette");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_roulette");
        //通知游戏界面删除礼包z
        //轮盘第五次开始 5分钟cd
        auto num = GETINTEGER("lunPanNum",4);
        int dx = 0;
        if(num == 0) dx = 60 * 4;
        DATA_M->setFreeCoinTime3(DATA_M->getContentSec() + dx);
        SCENE_M->refushGift();
        return;
    }
    else if(lingquType == 7)
    {//增加道具次数
        EVENT_M->sendEvent("event_game_multiple_gold");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_multiple_gold");
        isLingQu = true;
        return;
    }
    else if(lingquType == 8)
    {//经典结算
        EVENT_M->sendEvent("event_game_winLayer");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_winLayer");
        isLingQu = true;
        return;
    }
    else if(lingquType == 9)
    {//每日结算
        EVENT_M->sendEvent("event_game_winLayer");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_winDailyLayer");
        isLingQu = true;
        return;
    }
    else if(lingquType == 10)
    {//
        EVENT_M->sendEvent("msg_game_lingqu");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_lingqu");
        isLingQu = true;
        setFreeCoinTime(getContentSec());
        //通知游戏界面删除礼包z
        SCENE_M->refushGift();
        return;
    }
    else if(lingquType == 11)
    {//
        EVENT_M->sendEvent("event_game_update_fanPai");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_update_fanPai");
        isLingQu = true;
        //翻牌时间重置
        setFreeCoinTime4(getContentSec());
        //通知游戏界面删除礼包z
        SCENE_M->refushGift();
        return;
    }
    else if(lingquType == 12)
    {//关卡结算
        EVENT_M->sendEvent("event_game_winLevelLayer");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_winLevelLayer");
        isLingQu = true;
        return;
    }
    else if(lingquType == 13)
    {//游戏中领取金币
        EVENT_M->sendEvent("msg_game_lingqu_game");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_lingqu_game");
        isLingQu = true;
        setFreeCoinTime(getContentSec());
        //通知游戏界面删除礼包z
        SCENE_M->refushGift();
        return;
    }
    else if(lingquType == 14)
    {//签到
        EVENT_M->sendEvent("event_lobby_seven");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_lobby_seven");
        isLingQu = true;
        return;
    }
    else if(lingquType == 15 || lingquType == 16)
    {//领取金币
        EVENT_M->sendEvent("event_lobby_freeCoin");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_lobby_freeCoin");
        isLingQu = true;
        return;
    }
    else if(lingquType == 17)
    {//游戏内播放获取道具动画 并更新次数
        EVENT_M->sendEvent("event_game_game_Shuffle");
        return;
    }
//    SOUND_M->playEffectMusic(EffectCoin);
//    string huodejinbi = UIUtils::getStringByName("huodejinbi");
//    SCENE_M->showTips(CCString::createWithFormat(huodejinbi.c_str(), lingquCoinNum)->getCString());
}

void DataManager::playVideoAds(int type, int gold)
{
    if(!getHaveVideo())
    {
        return;
    }
    //开启广告了
    isPlayAds = true;
//    //暂停背景音乐
//    SoundManager::getInstance()->pauseGameBgMusic();
    
    setAdsTime(getContentSec());
    isLingQu = false;
    isLingQuFangCuo = false;
    lingquType = type;
    if (type == 1)
    {
        lingquCoinNum = getRewardCoin();
    }
    else if(type == 0)
    {
        //调用视频播放
//        lingquCoinNum = 2 * ((int)(CCRANDOM_0_1() * 700) + 500);
        lingquCoinNum = getRewardCoin() * 2;
    }
    else if (type == 3)
    {
        lingquCoinNum = gold;
    }
    else if (type == 4)
    // 复活
	{
		lingquCoinNum = 0;
	}
    else if(type == 5)
    // 背包领魔法棒
    {
        lingquCoinNum = 0;
    }
    else if(type == 6)
    // 轮盘
    {
        lingquCoinNum = 0;
    }
    else if(type == 7)
    {//多倍奖励
        lingquCoinNum = gold;
    }
    else if(type == 8)
    {//经典结算
        lingquCoinNum = 0;
    }
    else if(type == 9)
    {//每日结算
        lingquCoinNum = 0;
    }
    else if(type == 10)
    {//大厅中领取金币
        lingquCoinNum = 0;
    }
    else if(type == 11)
    {//翻牌
        lingquCoinNum = 0;
    }
    else if(type == 12)
    {//关卡结算
        lingquCoinNum = 0;
    }
    else if(type == 13)
    {//大厅中领取金币
        lingquCoinNum = 0;
    }
    else if(type == 14)
    {//签到再次领取
        lingquCoinNum = 0;
    }
    else if(type == 15 || type == 16)
    {//领取金币
        lingquCoinNum = 0;
    }
    else if(type == 17)
    // 游戏内领魔法棒
    {
        lingquCoinNum = 0;
    }
    else
    {
        lingquCoinNum = 100;
    }
    
    //调用视频播放
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    showNativeAds(3, StringUtils::format("%d", 100 + type));
#else
    AdsManager::showVideoAds();
#endif
    ValueMap params = {
            {"key", Value("clickvideo")},
            {"value", Value(type)}
    };
    UIUtils::FIRFirestoreAdd("operator", params);
    UIUtils::FIRAnalyticsEventWithPrefix("AD_SHOW_VIDEO_" + toString(type));
    UIUtils::FIRAnalyticsEvent("ads_video", params);
}

void DataManager::initAds()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // 没啥用了 都在adsmanager中
#endif
}

void DataManager::setBannerVisible(bool isVisible)
{
    auto num = ScoreManager::getInstance()->getWinTotalCNT();
    if(num < 8)
    {
        isVisible = false;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    AdsManager::bannerVisible = isVisible;
    AdsManager::setBannerVisible(isVisible && AdsManager::bannerVisible);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (_vipNoAds) isVisible = false;
    string str = isVisible?"show":"hide";
    JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "showADS", 0, str, "");
#endif
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_updatebanner");
}

const int LimitInterAdsTyp2Time = 20;
static unordered_map<string, int> InterMap {
        {"FanPaiAD", 5},
        {"GameViewHD", 1},
        {"WinLayerDailyHD", 3},
        {"WinLayerLevelHD", 4},
        {"WinLayer", 2},
        {"MainLobby", 6},
        {"ShuffleView", 7},
};
bool DataManager::showNativeAds(int type, const std::string &stype)
{
    if (DATA_M->isVipNoAds() && stype != "FanPaiAD") return false; // vip 免插屏
    string interType = stype;
    // 插屏广告限制
    if(type == 2)
    {
        // 前15局就不显示插屏
        auto num = ScoreManager::getInstance()->getWinTotalCNT();
        auto noAds = num <= GAMENOADSCNT;
        if (noAds && stype != "FanPaiAD" && stype != "ShuffleView") {
            cocos2d::log("IronAds:no inter(%s)!!!", stype.c_str());
            return false;
        }
        cocos2d::log("IronAds:show inter(%s)!!!", stype.c_str());

        UIUtils::FIRAnalyticsEventWithPrefix("AD_SHOW_INTERSTITIAL");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        ValueMap valueMap;
        valueMap["scene"] = Value(stype);
        auto hasInterstitial = UIUtils::hasInterstitial();
        valueMap["hasInterstitial"] = Value(hasInterstitial);

        UIUtils::FIRAnalyticsEvent("event_ad_show_interstitial", valueMap);
        UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("ad_show_interstitial")},
                {"value", Value(stype)},
                {"v1", Value(hasInterstitial)}
        });
#endif
        
        interType = toString(InterMap.find(stype)!=InterMap.end()?InterMap.at(stype):0);
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	showADS(type, "show");
    //重置限制插屏的cd   50s不给插屏
    setInterstitialTime();
	JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "showADS", type, "show", toString(interType));
#else
    if (type == 2)
    {
        return AdsManager::showInterstitial();
    }
    else
        AdsManager::showNativeExpressAds(type);
#endif
    return false;
}
void DataManager::hideNativeAds(int type)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    showADS(type, "hide");
	JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "showADS", type, "hide", toString(type));
#else
    AdsManager::hiedNativeExpressAds(type);
#endif
}

void DataManager::getFreeCoin()
{
	string huodejinbi = UIUtils::getStringByName("huodejinbi");
//    int randomCoinNum = (int)(CCRANDOM_0_1() * 700) + 500;
    int randomCoinNum = getRewardCoin();

	setFreeCoinTime2(getContentSec());
	setCoinNum(randomCoinNum,false,103);
	SOUND_M->playEffectMusic(EffectCoin);
	SCENE_M->showTips(CCString::createWithFormat(huodejinbi.c_str(), randomCoinNum)->getCString());
	//通知游戏界面删除礼包
	SCENE_M->refushGift();
	SCENE_M->refushShopScene();
}

time_t *  DataManager::getOneCardDatas()
{
	return oneCardDatas;
}

time_t *  DataManager::getThreeCardDatas()
{
	return threeCardDatas;
}

void DataManager::setGameData(int gameType, int index, int data)
{
	if (gameType == 1)
	{
		oneCardDatas[index - 1] = data;
		SETINTEGER(CCString::createWithFormat("oneCardData_%d", index)->getCString(), data);
	}
	else
	{
		threeCardDatas[index - 1] = data;
		SETINTEGER(CCString::createWithFormat("threeCardData_%d", index)->getCString(), data);
	}
}

//胜利结算
void DataManager::settlementGameOnWin(int gameType, bool isUseBack, int score, int useTime, int moveNum, int extraScore, int star)
{
    int totalScore = extraScore+score;
    totalScore = totalScore/10;
//    ValueMap valueMap({"", Value(1)});
    ValueVector valueVector{
        Value({{"type", Value((int)ScoreManager::Type::WINCNT)}, {"score", Value(1)}, {"op", Value("+")},}),
        Value({{"type", Value((int)ScoreManager::Type::WINRATE)}, {"score", Value(0)}, {"op", Value("!")},}),
        Value({{"type", Value((int)ScoreManager::Type::BESTWINTIME)}, {"score", Value(useTime)}, {"op", Value("<")}, {"new", Value(1)},}),
        Value({{"type", Value((int)ScoreManager::Type::LONEGESTTIME)}, {"score", Value(useTime)}, {"op", Value(">")},}),
        Value({{"type", Value((int)ScoreManager::Type::WINMINMOVES)}, {"score", Value(moveNum)}, {"op", Value("<")}, {"new", Value(1)},}),
        Value({{"type", Value((int)ScoreManager::Type::WINMAXMOVES)}, {"score", Value(moveNum)}, {"op", Value(">")},}),
        Value({{"type", Value((int)ScoreManager::Type::WINNOMOVES)}, {"score", Value(isUseBack?0:1)}, {"op", Value("+")}}),
        Value({{"type", Value((int)ScoreManager::Type::BESTSCORE)}, {"score", Value(score)}, {"op", Value(">")},}),
        Value({{"type", Value((int)ScoreManager::Type::WINNINGSNT)}, {"score", Value(1)}, {"op", Value("+")},}),
        Value({{"type", Value((int)ScoreManager::Type::FAILDNINGSNT)}, {"score", Value(0)}, {"op", Value("=")},}),
//        Value({{"type", Value((int)ScoreManager::Type::LONGESTWINNINGSCNT)}, {"score", Value(1)}, {"op", Value("+")},}),
        Value({{"type", Value((int)ScoreManager::Type::TOTALTIME)}, {"score", Value(useTime)}, {"op", Value("+")},}),
        Value({{"type", Value((int)ScoreManager::Type::EXTRASCORE)}, {"score", Value(extraScore)}, {"op", Value(">")},}),
        Value({{"type", Value((int)ScoreManager::Type::TOTALSCORE)}, {"score", Value(totalScore)}, {"op", Value(">")}, {"new", Value(1)},}),
        Value({{"type", Value((int)ScoreManager::Type::TOTALSTAR)}, {"score", Value(star)}, {"op", Value("+")},}),
    };
    if (DATA_M->getGameType() == DataManager::GameType::Random) {
        valueVector.push_back(Value({{"type", Value((int)ScoreManager::Type::RANDBESTSCORE)}, {"score", Value(totalScore)}, {"op", Value(">")}, {"new", Value(2)}}));
    }
    else if (DATA_M->getGameType() == DataManager::GameType::Huo) {
        valueVector.push_back(Value({{"type", Value((int)ScoreManager::Type::LIVEBESTSCORE)}, {"score", Value(totalScore)}, {"op", Value(">")}, {"new", Value(2)}}));
    }
    
    ScoreManager::getInstance()->setScore(gameType, valueVector);
    
}

//失败结算
void DataManager::settlementGameOnFail(int gameType, int useTime, int score)
{
    ValueVector valueVector{
        Value({{"type", Value((int)ScoreManager::Type::FAILDCNT)}, {"score", Value(1)}, {"op", Value("+")},}),
        Value({{"type", Value((int)ScoreManager::Type::TOTALTIME)}, {"score", Value(useTime)}, {"op", Value("+")},}),
        Value({{"type", Value((int)ScoreManager::Type::WINNINGSNT)}, {"score", Value(0)}, {"op", Value("=")},}),
        Value({{"type", Value((int)ScoreManager::Type::FAILDNINGSNT)}, {"score", Value(1)}, {"op", Value("+")},}),
        
    };
    if(isWeiJiaSiJiFen)
    {//维加斯模式 记录累计得分
        valueVector.push_back(Value({{"type", Value((int)ScoreManager::Type::HighestWeiJiaSiScore)}, {"score", Value(score)}, {"op", Value("!")},}));
    }
    ScoreManager::getInstance()->setScore(gameType, valueVector);
    
}

time_t * DataManager::getCardDatas(int gameType)
{
	if (gameType == 1)
	{
		return oneCardDatas;
	}
	else
	{
		return threeCardDatas;
	}
}

int DataManager::getYDay()
{
    auto tm = getContentTime();
    return tm->tm_yday;
}

void DataManager::setFrameSize(float w,float h)
{
    frameSizeWidth = w;
    frameSizeHeight = h;
    
}

bool DataManager::getHaveVideo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return AdsManager::haveRewardVides();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool ret = false;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "isVideoPlayable", "()Z")) {
		ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);

	}
	return ret;
#else
    return isHaveAds;
#endif
}
void DataManager::setIsHaveInterstitials(bool isHave)
{
    isHaveInterstitials = isHave;
}
bool DataManager::getHaveInterstitials()
{//新填充完毕 || 还有有填充
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return AdsManager::haveInterstitials();//isHaveInterstitials || 无网络下也会填充 不用此条件判断
#else
    return UIUtils::hasInterstitial();
#endif
}

long DataManager::getRewardCoin()
{
//    auto currentSec = getContentSec();
//    return MAX(1, MIN(6, ceil((currentSec-freeCoinTime)*1.0/TEX_MIN))) * 100;
    return FREE_COIN_REWARD;     // 不累积
}
// 商店里的奖励
long DataManager::getRewardCoin1()
{
    return FREE_VIDEO_COIN_REWARD;
}

int DataManager::getAppStartCNT() const {
	return _appStartCNT;
}

void DataManager::setAppStartCNT(int _appStartCNT) {
	DataManager::_appStartCNT = _appStartCNT;
}

bool DataManager::isLevelMode() {
	return getGameType() == GameType::Level;
}

bool DataManager::isDailyMode() {
    return getGameType() == GameType::Daily;
}

bool DataManager::hasRedPoint(bool reset, DataManager::GameType type) {
    auto tm = getContentTime();
    auto todayStr = StringUtils::format("%d_%d_%d", tm->tm_year, tm->tm_mon, tm->tm_mday);
    auto key = StringUtils::format("game_redpoint_%d", int(type));
    auto dayStr = UserDefault::getInstance()->getStringForKey(key.c_str(), "");
    if (reset) {
        UserDefault::getInstance()->setStringForKey(key.c_str(), todayStr);
        ValueMap params {{"gameType", Value(int(type))}};
        EventObserver::getInstance()->sendEvent("msg_event_game_redpoint_update", params);
    }
    return dayStr != todayStr;
}

void DataManager::setWinHDEnable(bool flag) {
    s_isWinHDEnable = flag;
	UserDefault::getInstance()->setBoolForKey("config_winend_ani", flag);
    FLUSH();
}

bool DataManager::isWinHDEnable() {
    return s_isWinHDEnable;
}

int DataManager::userLevel()
{
    //无辅助活局局数完成一局后开始评分
    auto huoTotalCNT = ScoreManager::getInstance()->getComTotalCNT((int)getIsThreeModel(),0);
    if(huoTotalCNT < 1)return -1;
    float toRate = 0;//辅助分
    float toWinRate = 0;//胜率分
    float toStarRate = 0;//星星分
    float toScoreRate = 0;//得分分
//    float toShuffleRate = 0;//洗牌分
//    float toTipsRate = 0;//提示分

    //被辅助局数占比 10 - 比例。占比约低 低分越高 8分

    auto huoEffTotalCNT = ScoreManager::getInstance()->getEffComTotalCNT((int)getIsThreeModel(),0);
    if(huoEffTotalCNT + huoTotalCNT != 0)
    {
        auto huoEffRate = (float)huoEffTotalCNT / (float)(huoEffTotalCNT + huoTotalCNT);
        toRate = 100 - huoEffRate * 100;
        _toRate = toRate;
    }

    //胜率 记录非辅助胜率5分 与 辅助胜率5分   60  30
    auto huoWinRate = ScoreManager::getInstance()->getComRate((int)getIsThreeModel(), 0);
    auto huoEffWinRate = ScoreManager::getInstance()->getEffComRate((int)getIsThreeModel(), 0);
    if((huoWinRate == 0&&huoEffWinRate == -1)||(huoWinRate == -1&&huoEffWinRate == 0))
    {
        toWinRate = 0;
    }
    else if(huoWinRate == -1&&huoEffWinRate != -1)
    {
        toWinRate = huoEffWinRate;
    }
    else if(huoWinRate != -1&&huoEffWinRate == -1)
    {
        toWinRate = huoWinRate;
    }
    else
    {
        toWinRate = (float)(huoWinRate + huoEffWinRate)/2;
    }
    _toWinRate = toWinRate;

    //星星数 123 3 10分  2 6分  1 3分 8分
    auto starCNT = ScoreManager::getInstance()->getStarCNT((int)getIsThreeModel());
    if(starCNT != -1)
    {
        auto starRate = starCNT/3;
        toStarRate = starRate * 100;
        _toStarRate = toStarRate;
    }

    //1.得分占比 理想总分为：745 理想不扣分最低总得分：595 8分 基本最低得分625
    //2.只记录最低得分
    auto minScore = ScoreManager::getInstance()->getMinScore((int)getIsThreeModel());
    if(minScore >= 625)
    {
        toScoreRate = 100;
    }
    else if(minScore > 595)
    {
        toScoreRate = 100 - (625 - minScore)/(625 - 595) * 100;
    }
    else
    {
        toScoreRate = 0;
    }
    _toScoreRate = toScoreRate;

    //场均魔法棒数  上限为10；
    auto magicCNT = ScoreManager::getInstance()->getMagicCNT((int)getIsThreeModel());

    auto magicRate = 100 - magicCNT/10 * 100;
//    auto tsRate = toShuffleRate + toTipsRate;
    //A B C 都会玩区分道具与辅助
    //D级 胜率可能会偏高 但是道具分偏低
    if(toWinRate > 90&&toRate == 100&&magicRate == 100&&toStarRate == 100&&toScoreRate == 100)
    {//A级
        _userlevel = "A";
        return 1;
    }
    else if(toWinRate > 80&&toRate > 90&&magicRate > 90&&toStarRate >= 90&&toScoreRate == 100)
    {//B级
        _userlevel = "B";
        return 2;
    }
    else if(((toWinRate > 80&&toRate > 60)||(huoEffWinRate >= 80&&((huoWinRate < 50&&huoTotalCNT < 3)||huoWinRate >= 50)))&&magicRate > 70&&toStarRate >= 66&&toScoreRate >= 90)
    {//C级
        //((（胜率分>80并且辅助分大于60）或者（辅助胜率 >= 80并且（(非辅助胜率小于50并且非辅助局数<3）或者 非辅助胜率>=50）)）并且道具分>80并且星星分>=66并且得分分>90
        _userlevel = "C";
        return 3;
    }
    else if(toWinRate > 60&&toRate > 60&&magicRate > 60&&toStarRate > 66&&toScoreRate >= 60)
    {//D级
        _userlevel = "D";
        return 4;
    }
    else if(toWinRate > 50&&toRate > 40&&magicRate > 50&&toStarRate > 33&&toScoreRate >= 60)
    {//E级
        _userlevel = "E";
        return 5;
    }
    else if(toWinRate <= 50&&toRate >= 0&&magicRate >= 0&&toStarRate >= 0&&toScoreRate >= 0)
    {//F级
        _userlevel = "F";
        return 6;
    }
    else if(toWinRate > 50&&toRate >= 0&&magicRate >= 0&&toStarRate > 33&&toScoreRate >= 0)
    {//F级
        _userlevel = "F";
        return 6;
    }
    return -1;
}

////洗牌次数
//void DataManager::setShulleNum(int num)
//{
//    _shulleNum = num < 0?0:num;
//    SETINTEGER("shulleNum", _shulleNum);
//}
//
//int DataManager::getShulleNum()
//{
//    return _shulleNum;
//}

bool DataManager::isYday()
{
    auto yDay = getYDay();
    if(d_yday != yDay)
    {//不同天数
        SETINTEGER("GameYDay",yDay);
        d_yday = yDay;
        return true;
    }
    //同一天
    return false;
}

bool DataManager::sevenDayIsYday()
{//改为判断今天奖励领没领
    auto yDay = getYDay();
    if(seven_yday != yDay)
    {//不同天数
        SETINTEGER("SevenYDay",yDay);
        seven_yday = yDay;
        //第二天
        return true;
    }
    //同一天
    return false;
}

void DataManager::updatenewVerIsYday()
{
    auto yDay = getYDay();
    SETINTEGER("NewVerYDay",yDay);
    newVer_yday = yDay;
}

bool DataManager::newVerIsYday()
{
    auto yDay = getYDay();
    if(newVer_yday != yDay)
    {//不同天数
        return true;
    }
    //同一天
    return false;
}

bool DataManager::getLimit()
{
    auto t = DATA_M->getInterstitialTime();//记录插屏cd
//    auto t2 = DATA_M->getVideoAdsTime();//记录激励cd
//    auto is = DATA_M->getIsShowAds();//对局开始时为true 没开始时为false 没开始时重开没有插屏
    if(t <= 0)
    {//可以播插屏
        //DATA_M->setIsInterstitial(false);
        return true;
    }
    
    return false;
}

void DataManager::setIsAutoTips(bool is)
{
    isAutoTips = is;
    SETBOOL("isAutoTips", is);
    FLUSH();
}
bool DataManager::getIsAutoTips()
{
    return isAutoTips;
}


//dyy
std::string DataManager::getDyyStr()
{
    std::string str = "1";
    if(dyyNum == 1)
    {
        str = "zh";
    }
    else if(dyyNum == 2)
    {
        str = "tw";
    }
    else if(dyyNum == 3)
    {
        str = "en";
    }
    else if(dyyNum == 4)
    {
        str = "ja";
    }
    else if(dyyNum == 5)
    {
        str = "ko";
    }
    else if(dyyNum == 6)
    {
        str = "fr";
    }
    else if(dyyNum == 7)
    {
        str = "de";
    }
    else if(dyyNum == 8)
    {
        str = "tr";
    }
    else if(dyyNum == 9)
    {
        str = "ru";
    }
    return str;
}

int DataManager::getDyyNum()
{
    return dyyNum;
}

void DataManager::setDyyNum(int num)
{//设置窗口修改多语言用
    if (dyyNum != num) {
        dyyNum = num;
        if(dyyNum > 9)
        {
            dyyNum = 1;
        }
        SETINTEGER("dyyNum",dyyNum);
        FLUSH();
        
        //刷新语言配置
        UIUtils::updateString();
    }
}

void DataManager::setDyyNum(const char* name)
{//设备第一次登陆判断当前设备哦语言， 匹配语言配置文件，没有对应配置文件的改为英文
    int num = -1;
    if(std::strcmp(name, "zh") == 0)
    {
        num = 1;
    }
    else if(std::strcmp(name, "tw") == 0)
    {
        num = 2;
    }
    else if(std::strcmp(name, "en") == 0)
    {
        num = 3;
    }
    else if(std::strcmp(name, "ja") == 0)
    {
        num = 4;
    }
    else if(std::strcmp(name, "ko") == 0)
    {
        num = 5;
    }
    else if(std::strcmp(name, "fr") == 0)
    {
        num = 6;
    }
    else if(std::strcmp(name, "de") == 0)
    {
        num = 7;
    }
    else if(std::strcmp(name, "tr") == 0)
    {
        num = 8;
    }
    else if(std::strcmp(name, "ru") == 0)
    {
        num = 9;
    }
    else if(num == -1)
    {//其余语言 改为英语。语言设定结束，
        num = 3;
    }
    
    
    dyyNum = num;
    SETINTEGER("dyyNum",dyyNum);
    FLUSH();
}

std::string DataManager::getSectionDyyStr()
{//返回部分语言 德语法语改为英语文本
    const char* languageCode;
    auto fileN = DATA_M->getDyyStr();//
    //其他语言 返回en
    languageCode = fileN.c_str();
    
    //判断当前语言 如果是第一次
    
    auto st =  StringUtils::format("%s",languageCode);
    if(st == "de"||st == "fr"||st == "tr"||st == "ru")
    {
        languageCode = "en";
    }
    
    return languageCode;
}

std::string DataManager::getAllDyyStr()
{//返回全部语言
    const char* languageCode;
    auto fileN = DATA_M->getDyyStr();//
    //其他语言 返回en
    languageCode = fileN.c_str();
    
    return languageCode;
}

void DataManager::setEndAniIdx(int idx)
{
    if(idx > 7)endAniIdx = 7;
    if(idx <= 0)endAniIdx = 1;
    endAniIdx = idx;
    SETINTEGER("endAniIdx",endAniIdx);
    FLUSH();
}
int DataManager::getEndAniIdx()
{
    return endAniIdx;
}

void DataManager::setIsEndAniAll(bool is)
{
    isEndAniAll = is;
    SETBOOL("isEndAniAll",is);
}
bool DataManager::getIsEndAniAll()
{
    return isEndAniAll;
}

void DataManager::setLimitTimeNum(int num)
{
    limitTimeNum = num;
    SETINTEGER("limitTimeNum",limitTimeNum);
    FLUSH();
}
int DataManager::getLimitTimeNum()
{
    return limitTimeNum;
}

void DataManager::setIsWeiJiaSi(bool weiJiaSi)
{
    isWeiJiaSi = weiJiaSi;
    SETBOOL("isWeiJiaSi", weiJiaSi);
    FLUSH();
}

void DataManager::setIsWeiJiaSiJiFen(bool isLeiJi)
{
    isWeiJiaSiJiFen = isLeiJi;
    SETBOOL("isWeiJiaSiJiFen", isLeiJi);
    FLUSH();
}

void DataManager::setWeiJiaSiJiFen(int jiFen, bool isThree/*false*/)
{
    weiJiaSiJiFen = jiFen;
    if(isThree)
    {
        SETINTEGER("weiJiaSiJiFenThree", weiJiaSiJiFen);
    }
    else if(isThreeModel)
    {//三张
        SETINTEGER("weiJiaSiJiFenThree", weiJiaSiJiFen);
    }
    else
    {//单张
        SETINTEGER("weiJiaSiJiFen", weiJiaSiJiFen);
    }
    FLUSH();
}
//void DataManager::setWeiJiaSiJiFen()
//{
//    weiJiaSiJiFen -= 52;
//    if(isThreeModel)
//    {//三张
//        SETINTEGER("weiJiaSiJiFenThree", weiJiaSiJiFen);
//    }
//    else
//    {//单张
//        SETINTEGER("weiJiaSiJiFen", weiJiaSiJiFen);
//    }
//    FLUSH();
//}

int DataManager::getWeiJiaSiJiFen()
{
    return GETINTEGER("weiJiaSiJiFen");
}
int DataManager::getWeiJiaSiJiFenThree()
{
    return GETINTEGER("weiJiaSiJiFenThree");
}

void DataManager::setStarBoxNumMax()
{
    //抑制增长
//    auto num = MIN(starBoxNumMax/3,5);
//    if(starBoxLimit >= num)
//    {
//        starBoxNumMax+=3;
//        starBoxLimit = 1;
//    }
//    else
//    {
//        starBoxLimit++;
//    }
    starBoxNumMax++;
    //SETINTEGER("starBoxLimit",starBoxLimit);
    starBoxNumMax = MIN(starBoxNumMax,8);
    SETINTEGER("fish_starBoxNumMax",starBoxNumMax);
    FLUSH();
}
int DataManager::getStarBoxNumMax()
{
    return starBoxNumMax;
}
void DataManager::setStarBoxNum(int num, bool isZero)
{
    if(isZero)
    {
        starBoxNum = 0;
    }
    else
    {
        starBoxNum += num;
    }
    
    starBoxNum = MIN(starBoxNum,starBoxNumMax);
    SETINTEGER("fish_starBoxNum",starBoxNum);
    FLUSH();
}
int DataManager::getStarBoxNum()
{
    return starBoxNum;
}

void DataManager::setDailyStarBoxNumMax()
{
    if(dailyStarBoxNumMax >=20)
    {
        dailyStarBoxNumMax = 1;
    }
    dailyStarBoxNumMax++;
    if(dailyStarBoxNumMax >= 11)
    {//玩到10/10。进来后变成0/20
        dailyStarBoxNumMax = 20;
    }
    SETINTEGER("dailyStarBoxNumMax",dailyStarBoxNumMax);
    FLUSH();
}
int DataManager::getDailyStarBoxNumMax()
{
    return dailyStarBoxNumMax;
}
void DataManager::setDailyStarBoxNum(int num ,bool isZero)
{
    if(isZero)
    {
        dailyStarBoxNum = 0;
    }
    else
    {
        dailyStarBoxNum+=num;
    }
    
    dailyStarBoxNum = MIN(dailyStarBoxNum,dailyStarBoxNumMax);
    SETINTEGER("dailyStarBoxNum",dailyStarBoxNum);
    FLUSH();
}
int DataManager::getDailyStarBoxNum()
{
    return dailyStarBoxNum;
}

void DataManager::shareYES()
{
    EVENT_M->sendEvent("event_game_share");
    //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_share");
}

void DataManager::showCoinTips(int coin)
{
    string huodejinbi = UIUtils::getStringByName("huodejinbi");
    SOUND_M->playEffectMusic(EffectCoin);
    SCENE_M->showTips(StringUtils::format(huodejinbi.c_str(), coin));
}

const float PI = 3.14159265358979323846;
float DataManager::getSinValue(float angle)
{
    return std::sin(angle*PI/180);
}

float DataManager::getCosValue(float angle)
{
    return std::cos(angle*PI/180);
}

float DataManager::getSpeedX(float speed,float moveAngle)
{
    speed = std::fabsf(speed);
    if(moveAngle == 0)
    {
        return 0;
    }
    if(moveAngle == 90)
    {
        return moveAngle;
    }
    if(moveAngle == 180)
    {
        return 0;
    }
    if(moveAngle == 270)
    {
        return -moveAngle;
    }
    
    return getSinValue(moveAngle*speed);
}

float DataManager::getSpeedY(float speed,float moveAngle)
{
    speed = std::fabsf(speed);
    if(moveAngle == 0)
    {
        return speed;
    }
    if(moveAngle == 90)
    {
        return 0;
    }
    if(moveAngle == 180)
    {
        return -speed;
    }
    
    if(moveAngle == 270)
    {
        return 0;
    }
    
    return getCosValue(moveAngle*speed);
}

float DataManager::getAngleByVector(float x,float y)
{
    if(y == 0)
    {
        if(x < 0)
        {
            return 270;
        }
        else if(x > 0)
        {
            return 90;
        }
    }
    
    if(x == 0)
    {
        if(y >= 0)
        {
            return 0;
        }
        else if(y < 0)
        {
            return 180;
        }
    }
    
    float tan_yx = std::fabsf(y)/std::fabsf(x);
    float angle = 0;
    if(y > 0&&x < 0)
    {
        angle = 270 + std::atan(tan_yx)*180/PI;
    }
    else if(y > 0&&x > 0)
    {
        angle = 90 - std::atan(tan_yx)*180/PI;
    }
    else if(y < 0&&x < 0)
    {
        angle = 270 - std::atan(tan_yx)*180/PI;
    }
    else if(y < 0&&x > 0)
    {
        angle = std::atan(tan_yx)*180/PI + 90;
    }
    
    return angle;
}

Vec2 DataManager::getVectorByAngle(float angle)
{
    if(angle == 0)
    {
        return Vec2(0,0);
    }
    else if(angle == 90)
    {
        return Vec2(1,0);
    }
    else if(angle == 180)
    {
        return Vec2(0,-1);
    }
    else if(angle == 270)
    {
        return Vec2(-1,0);
    }
    
    float x = getSpeedX(1, angle);
    float y = getSpeedY(1, angle);
    return Vec2(x,y);
}

int myrandom2 (int i) { return std::rand()%i;}
void DataManager::randVec(int num , std::vector<Vec2> *itemVec,float length)
{
    //分角度
    auto angle = 360/(float)num;//每次都加自身
    int id = 0;
    float tempAngle = angle+0.05;
    tempAngle += random(0.f, 20.f);
    while(id < num)
    {
        auto ve = DATA_M->getVectorByAngle(tempAngle);
        float R = random(20.f, length);
        Vec2 Position(0,0);
        float varX = Position.x +R * ve.x;
        float varY = Position.y + R * ve.y;
        
        itemVec->push_back(Vec2(varX,varY));
        tempAngle += angle;
        id++;
        if(tempAngle >= 360)
        {
            tempAngle = tempAngle - 360;
        }
    }
    std::random_shuffle(itemVec->begin(), itemVec->end(), myrandom2);
}

void DataManager::setPropNew(std::vector<int> idxVec)
{
    propNewClear();
    
    for(int i = 0;i<idxVec.size();++i)
    {
        setIsPropNew(true);
        
        auto tag = idxVec.at(i);
        auto shoptype = tag /100000;
        shoptype = shoptype%10;
        auto index = tag / 1000;
        index = index%100;
        
        if(shoptype == 1)
        {
            gameBgNew[index] = index;
        }
        else if(shoptype == 2)
        {
            cardFaceNew[index] = tag;
        }
        else if(shoptype == 3)
        {
            cardBgNew[index] = index;
        }
        else if(shoptype == 5)
        {
            musicNew[index] = index;
        }
    }
}

void DataManager::propNewClear(int shopType)
{
    if(shopType == -1)
    {
        setIsPropNew(false);
        for(int i = 0;i<GAME_BG_NUM;++i)
        {
            gameBgNew[i] = -1;
        }
        for(int i = 0;i<CARD_BG_NUM;++i)
        {
            cardBgNew[i] = -1;
        }
        for(int i = 0;i<CARD_FACE_NUM;++i)
        {
            cardFaceNew[i] = -1;
        }
        for(int i = 0;i<LobbyMusicTotalCNT;++i)
        {
            musicNew[i] = -1;
        }
    }
    
    if(shopType == 1)
    {
        for(int i = 0;i<GAME_BG_NUM;++i)
        {
            gameBgNew[i] = -1;
        }
    }
    else if(shopType == 2)
    {
        for(int i = 0;i<CARD_FACE_NUM;++i)
        {
            cardFaceNew[i] = -1;
        }
    }
    else if(shopType == 3)
    {
        for(int i = 0;i<CARD_BG_NUM;++i)
        {
            cardBgNew[i] = -1;
        }
    }
    else if(shopType == 5)
    {
        for(int i = 0;i<LobbyMusicTotalCNT;++i)
        {
            musicNew[i] = -1;
        }
    }
}

void DataManager::setPropNew(int shopType,int index,int num)
{
    if(num != -1)
    {
        setIsPropNew(true);
    }
    if(shopType == 1)
    {
        gameBgNew[index] = num;
    }
    else if(shopType == 2)
    {
        cardFaceNew[index] = num;
    }
    else if(shopType == 3)
    {
        cardBgNew[index] = num;
    }
    else if(shopType == 5)
    {
        musicNew[index] = num;
    }
    
}

int DataManager::getPropNew(int shopType,int index)
{
    if(shopType == 1)
    {
        return gameBgNew[index];
    }
    else if(shopType == 2)
    {
        return cardFaceNew[index];
    }
    else if(shopType == 3)
    {
        return cardBgNew[index];
    }
    else if(shopType == 5)
    {
        return musicNew[index];
    }
    return -1;
}

void DataManager::setIsPropNew(bool isNew)
{
    isPropNew = isNew;
}
bool DataManager::getIsPropNew()
{
    return isPropNew;
}

bool DataManager::getIsPropNew(int showType)
{
    if(showType == 1)
    {
        for(int i = 0;i<GAME_BG_NUM;++i)
        {
            auto is = gameBgNew[i] != -1;
            if(is)
            {
                return true;
            }
        }
    }
    else if(showType == 2)
    {
        for(int i = 0;i<CARD_FACE_NUM;++i)
        {
            auto is = cardFaceNew[i] != -1;
            if(is)
            {
                return true;
            }
        }
    }
    else if(showType == 3)
    {
        for(int i = 0;i<CARD_BG_NUM;++i)
        {
            auto is = cardBgNew[i] != -1;
            if(is)
            {
                return true;
            }
        }
    }
    else if(showType == 5)
    {
        for(int i = 0;i<LobbyMusicTotalCNT;++i)
        {
            auto is = musicNew[i] != -1;
            if(is)
            {
                return true;
            }
        }
    }
    
    
    return false;
}

//记录新解锁的鱼
void DataManager::setFishNew(int index,int num)
{
    fishNew[index] = num;
}

bool DataManager::getFishNew(int index)
{
    return fishNew[index] != -1;
}

void DataManager::fishNewClear()
{
    for(int i = 0;i < FISH_NUM;++i)
    {
        fishNew[i] = -1;
    }
}

bool DataManager::getIsFishNuw()
{
    bool isNew = false;
    for(int i = 0;i < FISH_NUM;++i)
    {
        isNew = fishNew[i] != -1;
        if(isNew)
        {
            break;
        }
    }
    return isNew;
}

//记录新解锁的鱼缸
void DataManager::setFashTankNew(int index,int num)
{
    fashTankNew[index] = num;
}

bool DataManager::getFashTankNew(int index)
{
    return fashTankNew[index] != -1;
}

void DataManager::fashTankNewClear()
{
    for(int i = 0;i < FASH_TANK_NUM;++i)
    {
        fashTankNew[i] = -1;
    }
}

bool DataManager::getIsFashTankNuw()
{
    bool isNew = false;
    for(int i = 0;i < FASH_TANK_NUM;++i)
    {
        isNew = fashTankNew[i] != -1;
        if(isNew)
        {
            break;
        }
    }
    return isNew;
}

void DataManager::setStartAni(int id)
{
    startAni = id;
    SETINTEGER("startAni",id);
    FLUSH();
}
int DataManager::getStartAni()
{
    return startAni;
}

void DataManager::setGuangGao(bool is)
{
    isGuangGao = is;
    jieSuoProp(is);
    SETBOOL("isGuangGao",is);
    FLUSH();
}

bool DataManager::getGuangGao()
{
    return isGuangGao;
}

void DataManager::jieSuoProp(bool isJieSuo)
{
    if(isJieSuo)
    {
        for (int i = 0; i < GAME_BG_NUM; i++)
        {
            if ( i == 0)
            {
                SETINTEGER(StringUtils::format("gameBgStatus_%d",i).c_str(), true);
                gameBgStatus[i] = true;
            }
            else
            {
                 SETINTEGER(StringUtils::format("gameBgStatus_%d", i).c_str(),true);
                gameBgStatus[i] = true;
                //gameBgStatus[i] = GETINTEGER(StringUtils::format("gameBgStatus_%d", i).c_str(), getShopItemPrice(1, i)==0?true:false);
            }
        }

        for (int i = 0; i < CARD_FACE_NUM; i++)
        {
            if (i == 0)
            {
                SETINTEGER(StringUtils::format("cardFaceStatus_%d", i).c_str(), true);
                cardFaceStatus[i] = true;
            }
            else
            {
                SETINTEGER(StringUtils::format("cardFaceStatus_%d", i).c_str(), true);
                cardFaceStatus[i] = true;
                //cardFaceStatus[i] = GETINTEGER(CCString::createWithFormat("cardFaceStatus_%d", i)->getCString(), false);
            }
        }
        
        for (int i = 0; i < CARD_FACE_NUM; i++)
        {
            for(int j = 0;j < 52;++j)
            {
                if (i == 0)
                {
                    SETINTEGER(StringUtils::format("cardFaceStatus_%d_%d", i, j).c_str(), true);
                    cardFaceStatus52[i][j] = true;
                }
                else
                {
                    SETINTEGER(StringUtils::format("cardFaceStatus_%d_%d", i, j).c_str(), true);
                    cardFaceStatus52[i][j] = true;
                    //cardFaceStatus[i] = GETINTEGER(CCString::createWithFormat("cardFaceStatus_%d", i)->getCString(), false);
                }
            }
        }
        
        for (int i = 0; i < CARD_BG_NUM; i++)
        {
            if (i == 0)
            {
                SETINTEGER(StringUtils::format("cardBgStatus_%d", i).c_str(), true);
                cardBgStatus[i] = true;
            }
            else
            {
                SETINTEGER(StringUtils::format("cardBgStatus_%d", i).c_str(), true);
                cardBgStatus[i] = true;
                //cardBgStatus[i] = GETINTEGER(CCString::createWithFormat("cardBgStatus_%d", i)->getCString(), false);
            }
        }
        
        //音乐
        for(int i = 0;i < LobbyMusicTotalCNT;++i)
        {
            if(i == 0)
            {
                SETINTEGER(StringUtils::format("musicStatus_%d", i).c_str(), true);
                musicStatus[i] = true;
            }
            else
            {
                SETINTEGER(StringUtils::format("musicStatus_%d", i).c_str(), true);
                musicStatus[i] = true;
            }
        }
    }
    else
    {
        for (int i = 0; i < GAME_BG_NUM; i++)
        {
            if ( i == 0)
            {
                SETINTEGER(StringUtils::format("gameBgStatus_%d",i).c_str(), true);
                gameBgStatus[i] = true;
            }
            else
            {
                 SETINTEGER(StringUtils::format("gameBgStatus_%d", i).c_str(),false);
                gameBgStatus[i] = false;
                //gameBgStatus[i] = GETINTEGER(StringUtils::format("gameBgStatus_%d", i).c_str(), getShopItemPrice(1, i)==0?true:false);
            }
        }

        for (int i = 0; i < CARD_FACE_NUM; i++)
        {
            if (i == 0)
            {
                SETINTEGER(StringUtils::format("cardFaceStatus_%d", i).c_str(), true);
                cardFaceStatus[i] = true;
            }
            else
            {
                SETINTEGER(StringUtils::format("cardFaceStatus_%d", i).c_str(), false);
                cardFaceStatus[i] = false;
                //cardFaceStatus[i] = GETINTEGER(CCString::createWithFormat("cardFaceStatus_%d", i)->getCString(), false);
            }
        }
        
        for (int i = 0; i < CARD_FACE_NUM; i++)
        {
            for(int j = 0;j < 52;++j)
            {
                if (i == 0)
                {
                    SETINTEGER(StringUtils::format("cardFaceStatus_%d_%d", i, j).c_str(), true);
                    cardFaceStatus52[i][j] = true;
                }
                else
                {
                    SETINTEGER(StringUtils::format("cardFaceStatus_%d_%d", i, j).c_str(), false);
                    cardFaceStatus52[i][j] = false;
                    //cardFaceStatus[i] = GETINTEGER(CCString::createWithFormat("cardFaceStatus_%d", i)->getCString(), false);
                }
            }
        }
        
        for (int i = 0; i < CARD_BG_NUM; i++)
        {
            if (i == 0)
            {
                SETINTEGER(StringUtils::format("cardBgStatus_%d", i).c_str(), true);
                cardBgStatus[i] = true;
            }
            else
            {
                SETINTEGER(StringUtils::format("cardBgStatus_%d", i).c_str(), false);
                cardBgStatus[i] = false;
                //cardBgStatus[i] = GETINTEGER(CCString::createWithFormat("cardBgStatus_%d", i)->getCString(), false);
            }
        }
        
        //音乐
        for(int i = 0;i < LobbyMusicTotalCNT;++i)
        {
            if(i == 0)
            {
                SETINTEGER(StringUtils::format("musicStatus_%d", i).c_str(), true);
                musicStatus[i] = true;
            }
            else
            {
                SETINTEGER(StringUtils::format("musicStatus_%d", i).c_str(), false);
                musicStatus[i] = false;
            }
        }
    }
}

void DataManager::delayPlayBtn(std::function<void()> cb)
{//结算场景防错
    auto node = SCENE_M->getWinLayerNode();
    
    auto func = CallFunc::create([cb](){
        cb();
    });
    auto delay = DelayTime::create(3);//防错判断时机3s
    auto seq = Sequence::create(delay,func, NULL);
    seq->setTag(88);
    node->runAction(seq);
    
}

void DataManager::stopDelayPlayBtn()
{//插屏顺利播放取消防错
    auto node = SCENE_M->getWinLayerNode();
    auto action = node->getActionByTag(88);
    if(action)
    {
        node->stopAction(action);
    }
}

void DataManager::setVipNoAds(bool flag, time_t startTime, time_t endTime, int payid)
{
    if (_vipNoAds != flag)
    {
        _vipNoAds = flag;
        SETBOOL("key_vip_noads", flag);
        SETSTR("key_vip_noads_start", toString(startTime));
        SETSTR("key_vip_noads_end", toString(endTime));
        SETSTR("key_vip_trans_id", toString(startTime));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        AdsManager::setBannerVisible(!_vipNoAds);
#endif
        setBannerVisible(false);
    }
}

void DataManager::setPurchaseLimit(bool isLimit)
{
    _isPurchaseLimit = isLimit;
    SETBOOL("isPurchaseLimit", isLimit);
}

bool DataManager::checkVipValid()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    GamePayment::getInstance()->checkVipStatus(); // 连接服务器检测订阅状态
    time_t nowTs = utils::getTimeInMilliseconds(); // ms
    time_t startTime = atoll(GETSTR("key_vip_noads_start", "0").c_str());
    time_t endTime = atoll(GETSTR("key_vip_noads_end", "0").c_str());
    bool valid = nowTs>=startTime && nowTs<=endTime;
    if (valid) {
        SETSTR("key_vip_noads_start", toString(nowTs-10000)); // 少存10s
    }
    return valid;
#endif
    return true;
}

int DataManager::getElo()
{
    //活局局数完成一局后开始计算
    auto huoTotalCNT = ScoreManager::getInstance()->getComTotalCNT((int)getIsThreeModel(),0);
    auto huoWinRate = ScoreManager::getInstance()->getComRate((int)getIsThreeModel(), 0);
    if(huoTotalCNT < 1)
    {
        _isStartOneGame = false;
        return 100;
    }
    
    //得到上一次对局的信息
    //胜负
    auto oldWin = ScoreManager::getInstance()->getOldWin((int)getIsThreeModel());
    //得分
    auto oldScore = ScoreManager::getInstance()->getOldScore((int)getIsThreeModel());
    //时间
    auto oldTime = ScoreManager::getInstance()->getOldTime((int)getIsThreeModel());
    //魔法棒使用情况
    auto oldMagic = ScoreManager::getInstance()->getOldMagicNum((int)getIsThreeModel());
    //当前难度
    auto gameHard = DATA_M->getGameHard(); // 活局难度
    
    //得分
    auto toScoreRate = 0;
    if(oldScore >= 625)
    {
        toScoreRate = 100;
    }
    else if(oldScore > 595)
    {
        toScoreRate = 100 - (625 - oldScore)/(625 - 595) * 100;
    }
    else
    {
        toScoreRate = 0;
    }
    
    auto toTimeRate = 0;
    //时间
    if (oldTime<=360) {
        toTimeRate = 100;
    }
    else if(oldTime<=450) {
        toTimeRate = 50;
    }
    else {
        toTimeRate = 0;
    }

    
    //如果没有新开重开 直接退了
    if(_isStartOneGame)
    {
        _isStartOneGame = false;
        return gameHard;
    }
    //
    if(oldWin&&oldMagic == 0)
    {//上一局胜利了并且没有用魔法棒 增加难度 数值减少
        
        if(gameHard >= 90)
        {//胜利了 从60开始减
            gameHard = 60;
        }
        else if(gameHard == 20)
        {
            gameHard = 20;
        }
        else
        {//计算
            auto score = toScoreRate * 5 / 100;
            auto time = toTimeRate * 5 / 100;
            
            gameHard -= (int)(score + time);
            if(gameHard < 20) gameHard = 20;
        }

    }
    else
    {//上一局失败了 降低难度 数值增加
        //失败了
        if(gameHard <= 60)
        {
            gameHard = 70;
        }
        else if(gameHard == 100)
        {
            gameHard = 100;
        }
        else
        {
            gameHard += 20;
            if(gameHard > 100) gameHard = 100;
        }
    }
    
    //记录当前难度
    DATA_M->setGameHard(gameHard);
    SETINTEGER("gameHard", gameHard);
    FLUSH();
    
    return gameHard;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include  <android/log.h>

extern "C"
{
    JNIEXPORT jboolean JNICALL Java_org_cocos2dx_cpp_AppActivity_getIsPlayAds(JNIEnv *env, jobject thiz)
    {
        auto num = ScoreManager::getInstance()->getWinTotalCNT();
        auto isAds = num > GAMENOADSCNT;
        return isAds;
    }

    JNIEXPORT jintArray JNICALL Java_org_cocos2dx_cpp_AppActivity_getFishArray(JNIEnv *env, jobject thiz)
    {
        auto idx = DATA_M->getCurrentFashTankIdx();
        auto vec = DATA_M->getFishTypeVec(idx);
        auto length = vec.size();
        int arr[length];
        for(int i = 0;i < length;++i)
        {
            arr[i] = vec.at(i);
        }
        
        jintArray array = env->NewIntArray(length);
        env->SetIntArrayRegion(array,0,length,arr);
        return array;
    }

    JNIEXPORT jintArray JNICALL Java_org_cocos2dx_cpp_AppActivity_getIsDailyArray(JNIEnv *env, jobject thiz)
    {
        auto idx = DATA_M->getCurrentFashTankIdx();
        auto fashTank = SCENE_M->getGameBackground();
        auto vec = fashTank->getFishIsDaily();
        auto length = vec.size();
        int arr[length];
        for(int i = 0;i < length;++i)
        {
            arr[i] = vec.at(i);
        }

        jintArray array = env->NewIntArray(length);
        env->SetIntArrayRegion(array,0,length,arr);
        return array;
    }

    JNIEXPORT jintArray JNICALL Java_org_cocos2dx_cpp_AppActivity_getIsFashTankUnlockArray(JNIEnv *env, jobject thiz)
    {
        auto idx = DATA_M->getCurrentFashTankIdx();
        auto vec = DATA_M->getFashTankUnlockVec(idx);
        auto length = vec.size();
        int arr[length];
        for(int i = 0;i < length;++i)
        {
           arr[i] = vec.at(i);
        }

        jintArray array = env->NewIntArray(length);
        env->SetIntArrayRegion(array,0,length,arr);
        return array;
    }

    JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_AppActivity_getWinNum(JNIEnv *env, jobject thiz)
    {
        auto num = ScoreManager::getInstance()->getWinTotalCNT(true);
        return num;
    }
};
#endif


//---------------鱼
void DataManager::setFishNum(int fishNum,int fashtankIdx)
{
    _fishNumVec.at(fashtankIdx) = fishNum;
    //_fishNum = fishNum;
    
    SETINTEGER(StringUtils::format("fishNum_%d", fashtankIdx).c_str(),fishNum);
    
}
int DataManager::getFishNum()
{
    return _fishNumVec.at(_currentFashTankIdx);
}

int DataManager::getFishNum(int idx)
{
    return _fishNumVec.at(idx);
}

vector<int> DataManager::getFishTypeVec(int fashtankIdx)
{
    return _fishTypeVec.at(fashtankIdx);
}

void DataManager::deleteFishTypeData(int deleteId,int fashtankIdx)
{
    auto &vec = _fishTypeVec.at(fashtankIdx);
    vector<int>::iterator it = vec.begin();
    int id = 0;
    while(it != vec.end())
    {
        auto type = *it;
        if(id == deleteId)
        {//找到对应的id。移除他
            DELETEKEY(StringUtils::format("fishType_%d_%d",fashtankIdx, deleteId).c_str());
            it = vec.erase(it);
            id++;
        }
        else
        {
            if(id > deleteId)
            {//后面的数据前移
                DELETEKEY(StringUtils::format("fishType_%d_%d",fashtankIdx, id).c_str());
                SETINTEGER(StringUtils::format("fishType_%d_%d",fashtankIdx, id - 1).c_str(), type);
            }
            id++;
            it++;
        }
    }
    auto &dieVec = _fishDieVec.at(fashtankIdx);
    it = dieVec.begin();
    id = 0;
    while(it != dieVec.end())
    {
        auto type = *it;
        if(id == deleteId)
        {//找到对应的id。移除他
            DELETEKEY(StringUtils::format("fishDie_%d_%d",fashtankIdx, deleteId).c_str());
            it = dieVec.erase(it);
            id++;
        }
        else
        {
            if(id > deleteId)
            {//后面的数据前移
                DELETEKEY(StringUtils::format("fishDie_%d_%d",fashtankIdx, id).c_str());
                SETINTEGER(StringUtils::format("fishDie_%d_%d",fashtankIdx, id - 1).c_str(), type);
            }
            id++;
            it++;
        }
    }
    
    FLUSH();
    UIUtils::FIRFirestoreAddOP("fish_del", toString(deleteId), to_string(fashtankIdx));
    updateFishVec();
}

void DataManager::addFishTypeData(int id,int type)
{
    _fishTypeVec.at(_currentFashTankIdx).push_back(type);
    SETINTEGER(StringUtils::format("fishType_%d_%d",_currentFashTankIdx, id).c_str(), type);
    //活着的
    _fishDieVec.at(_currentFashTankIdx).push_back(0);
    SETINTEGER(StringUtils::format("fishDie_%d_%d",_currentFashTankIdx,  id).c_str(), 0);
    FLUSH();
    UIUtils::FIRFirestoreAddOP("fish_buy", toString(id), toString(type), to_string(_currentFashTankIdx));
    updateFishVec();
}

void DataManager::updateFishVec()
{
    ValueVector data;
    for (auto i=0; i<_fishTypeVec.size(); i++) {
        auto vec = _fishTypeVec.at(i);
        for (auto j=0; j<vec.size(); j++) {
            ValueMap item;
            item["i"] = j;
            item["t1"] = "shop";
            item["t2"] = StringUtils::format("fish_%d", i);
            item["st"] = _currentFashTankIdx==i?2:1;
            data.push_back(Value(item));
        }
    }
    UIUtils::FIRFirestoreAdd("userInfo", {
        {"data", Value(data)}
    });
}

void DataManager::setIsFishDie(int id,bool isDie)
{
    auto &vec = _fishDieVec.at(_currentFashTankIdx);
    
    vec[id] = isDie;
    SETINTEGER(StringUtils::format("fishDie_%d_%d", _currentFashTankIdx,id).c_str(), isDie?1:0);
    FLUSH();
}

bool DataManager::isFishDie(int id)
{// 为1 就没了
    return _fishDieVec.at(_currentFashTankIdx).at(id) == 1;
}

//换鱼缸了
void DataManager::setCurrentFashTankIdx(int fashTankidx)
{
    _currentFashTankIdx = fashTankidx;
    SETINTEGER("_currentFashTankIdx",fashTankidx);
}

int DataManager::getCurrentFashTankIdx()
{
    return _currentFashTankIdx;
}

void DataManager::updateOfflineTime()
{
    //记录当前时间。为了计算离线时间
    _offlineTime = getContentSec();
    SETINTEGER("offlineTime",(int)_offlineTime);
    FLUSH();
}

int DataManager::getOfflineTime()
{
    //算出离线时间
    auto time = (int)_offlineTime;
    time = time == 0?0:(int)getContentSec() - time;
    if(time < 0) time = 0;
    return time;
}

int DataManager::getFishTypeNum(int fishType,int fashTank)
{
    auto vec = _fishTypeVec.at(fashTank);
    int num = 0;
    for(int i = 0;i < vec.size();++i)
    {
        auto id = vec.at(i);
        if(id == fishType)
        {
            num++;
        }
    }
    
    return num;
}

void DataManager::setClickFishTime(long time)
{
    _clickFishTime = getContentSec() + time;
    SETINTEGER("clickFishTime", (int)_clickFishTime);
}

int DataManager::getClickFishTime()
{
    time_t contentTime = getContentSec();
    
    if (contentTime > _clickFishTime) {
        return 0;
    }
    auto time = int(_clickFishTime-contentTime);
    return time;
}

void DataManager::setInterstitialTime()
{
    InterstitialTime = getContentSec() + TEX_MIN5;
}
int DataManager::getInterstitialTime()
{
    time_t contentTime = getContentSec();
    
    if (contentTime > InterstitialTime) {
        return 0;
    }
    auto time = int(InterstitialTime-contentTime);
    return time;
}

void DataManager::setFashTankUnlock(int idx,int unlockIdx)
{
    auto &vec = _fashTankUnlockVec.at(idx);
    vec[unlockIdx] = 1;
    SETINTEGER(StringUtils::format("fashTankUnlockVec_%d_%d", idx,unlockIdx).c_str(), 1);
    UIUtils::FIRFirestoreAddOP("fish_tank_unlock", toString(idx), toString(unlockIdx));
    UIUtils::FIRAnalyticsEvent("fish_tank_unlock", {
        {"i", Value(idx)},
        {"unlock", Value(unlockIdx)},
    });
}

bool DataManager::getFashTankUnlock(int idx,int unlockIdx)
{
    auto vec = _fashTankUnlockVec.at(idx);
    bool isUnlock = vec.at(unlockIdx) == 1;
    return isUnlock;
}


vector<int> DataManager::getFashTankUnlockVec(int idx)
{
    auto vec = _fashTankUnlockVec.at(idx);
    return vec;
}

void DataManager::setMyName(string name)
{
    _myName = name;
    SETSTR("fish_myName",name);
}

//记录当前排行榜
void DataManager::setRankDailyTS(long time)
{
    log("updateRandReward  time : %d, ",time);
    //time 会有错误的参数传进来 1340762112  1624924860
    auto str = StringUtils::toString(time);
    
    if(time < 1624924860)
    {
        log("_dailyTime : 0");
        return;
    }
    
    if(_dailyTime != time&&_dailyTime != -1&&_oldDailyTime == -1)
    {//如果当前排行榜变化了 就记录一下之前那个排行榜
        _oldDailyTime = _dailyTime;
        SETINTEGER("_oldDailyTime",_oldDailyTime);
    }
    _dailyTime = time;
    SETINTEGER("_dailyTime",_dailyTime);
    
    log("updateRandReward  _dailyTime : %d, _oldDailyTime : %d, _myRank : %d, _myOldRank : %d",_dailyTime,_oldDailyTime,_myRank,_myOldRank);
    
}
//记录名次
void DataManager::setRank(int rank)
{
    if(_oldDailyTime == -1)
    {
        _myOldRank = _myRank;
        SETINTEGER("_myOldRank",_myOldRank);
    }
    _myRank = rank;
    SETINTEGER("_myRank",_myRank);
}

//判断是不是该领奖励了
bool DataManager::getIsRankReward()
{
    if(_oldDailyTime != -1)
    {
        return true;
    }
    return false;
}

//领完了，或者没奖励可以领
void DataManager::resetRank()
{
    _dailyTime = -1;
    SETINTEGER("_dailyTime",_dailyTime);
    _oldDailyTime = -1;
    SETINTEGER("_oldDailyTime",_oldDailyTime);
    _myRank = -1;
    SETINTEGER("_myRank",_myRank);
    _myOldRank = -1;
    SETINTEGER("_myOldRank",_myOldRank);
}

void DataManager::initCiKu()
{
//    auto load_str = FileUtils::getInstance()->getStringFromFile("ciku.json");
//    _ciKuConfig.Parse(load_str.c_str());
//    if (_ciKuConfig.HasParseError())
//    {
//        //解析出错
//        CCASSERT(true, "解析出现错误");
//        return;
//    }
}

bool DataManager::isJinYongCi(string str)
{
//    auto array = _ciKuConfig["ciku"].GetArray();
//
//    for(int i = 0;i < array.Size();++i)
//    {
//        auto temp = array[i]["text"].GetString();
//        if(str.find(temp) != string::npos)
//        {
//            return true;
//        }
//    }
    return false;
}

void DataManager::setPlayerVer(string data)
{
    _isNewVer = false;
    rapidjson::Document d;
    //        std::string load_str(params, strlen(params));
    d.Parse<0>(data.c_str());
    if (d.HasParseError())
    {
        return;
    }
    //auto pn = d["pn"].GetString();
    auto verCode = d["verCode"].GetString();
    auto verName = d["ver"].GetString();
    //auto country = d["country"].GetString();
    auto currentVer = UIUtils::getVersion();
    auto currentVerName = UIUtils::getVersionName();
    
    if(verName != currentVerName||verCode != currentVer)
    {
        _isNewVer = true;
    }

}

bool DataManager::isNewVer()
{
    return _isNewVer;
}

void DataManager::addchongKaiNum(bool zero)
{
    if(zero)
    {
        _chongKaiNum = 0;
    }
    else
    {
        _chongKaiNum++;
    }
    
    SETINTEGER("_chongKaiNum",_chongKaiNum);
}

void DataManager::addSameChongKaiNum(bool zero)
{
    if(zero)
    {
        _samechongKaiNum = 0;
    }
    else
    {
        _samechongKaiNum++;
    }
    
    SETINTEGER("_samechongKaiNum",_samechongKaiNum);
}

void DataManager::setSevenOneVec(int idx,bool isOne)
{//idx = 0,1
    isSevenOneVec[idx] = isOne;
    SETBOOL(StringUtils::format("isSevenOneVec_%d", idx).c_str(),isOne);
}

bool DataManager::getSevenOneVec(int idx)
{
    return isSevenOneVec[idx];
}

void DataManager::setIsGetSevenReward(bool isReward)
{
    isGetSevenReward = isReward;
    SETBOOL("isGetSevenReward",isReward);
}

bool DataManager::getIsGetSevenReward()
{
    return isGetSevenReward;
}

void DataManager::setDayOfflineTime()
{
    dayOfflineTime = getContentSec() + TEX_MIN6;
}

long DataManager::getDayOfflineTime()
{
    if(dayOfflineTime == 0)
    {
        return -1;
    }
    auto time = getContentSec();
    auto t = dayOfflineTime - time;
    if(t < 0)
    {
        t = 0;
    }
    return t;
}

void DataManager::addChallengeNum(bool isZero)
{
    if(isZero)
    {
        challengeNum = 0;
    }
    else
    {
        challengeNum++;
    }
    SETINTEGER("challengeNum",challengeNum);
}

int DataManager::getChallengeNum()
{
    return challengeNum;
}

void DataManager::setIsChallenge(bool isOpen)
{
    if(isOpen)
    {
        if(challengeOpenNum == 0)
        {
            setFreeCoinTime5(getContentSec());
            isChallenge = true;
        }
        else
        {
            isChallenge = false;
        }
        challengeOpenNum++;
        SETINTEGER("challengeOpenNum",challengeOpenNum);
    }
    else
    {
        isChallenge = false;
    }
    
    SETBOOL("isChallenge",isChallenge);
}

bool DataManager::getIsChallenge()
{
    return isChallenge;
}
bool DataManager::getIsChallengeOpen()
{
    return challengeOpenNum == 0;
}
void DataManager::setIsChallengeOpenOne(bool isOne)
{
    isChallengeOpenOne = isOne;
    SETBOOL("isChallengeOpenOne",isChallengeOpenOne);
}

bool DataManager::getIsChallengeOpenOne()
{
    return isChallengeOpenOne;
}
