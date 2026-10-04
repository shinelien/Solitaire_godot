#include "SpriteManager.h"
#include <zlib.h>
#include "TipsNode.h"
#include "GameViewHD.hpp"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "AtlasManager.h"
#include "DailyManager.h"
#include "ShopManager.h"
#include "BureauTestManager.h"
#include "TeachManager.h"
#include "TaskManager.h"
#include "EventObserver.h"
#include "TeachManager.h"
#include "ScoreManager.h"
#include "SceneManager.h"
#include "LevelManager.h"
#include <stdlib.h>
#include <stdio.h>
#define TEST_OTHER_BUREAU 0
#define DEBUG_BACKMOVE 0
using namespace spine;
const auto DestBufferSize = 1024*1024*7;

static vector<string> ColorStr{
    "♠️", "♥️", "♣️", "♦️"
};
static vector<string> PosStr{
"CARD_POS_A",                //A
"CARD_POS_K",                //K
"CARD_POS_WAIT",             //�ȴ�����
"CARD_POS_WAIT_SHOW"         //�ȴ���ʾ����
};
SpriteManager * SpriteManager::spriteManager = nullptr;
SpriteManager::SpriteManager()
{
	initData();
	//initCardIds();
}

SpriteManager * SpriteManager::getInstance()
{
	if (spriteManager == nullptr)
	{
		spriteManager = new SpriteManager();
	}
	return spriteManager;
}

void SpriteManager::initData()
{
	initCardNum = 0;
	isFilpX = true;
	isReplay = false;
	for (int i = 0; i < 4;i++)
	{
		aCardVector[i] = Vector<CardSprite *>();
	}

	for (int i = 0; i < 7; i++)
	{
		kCardVector[i] = Vector<CardSprite *>();
	}

	waitCardVector = Vector<CardSprite *>();
	waitShowCardVector = Vector<CardSprite *>();

	isThreeModel = DATA_M->getIsThreeModel();
}

bool donotNeedEasyBureau()
{
    auto totalWinCNT = ScoreManager::getInstance()->getScore(DATA_M->getIsThreeModel()?2:1, ScoreManager::Type::WINCNT);
    auto winRate = ScoreManager::getInstance()->getScore(DATA_M->getIsThreeModel()?2:1, ScoreManager::Type::WINRATE);
    return totalWinCNT<3 || winRate<45;
}

bool userOtherBureau()
{
    auto totalWinCNT = ScoreManager::getInstance()->getScore(DATA_M->getIsThreeModel()?2:1, ScoreManager::Type::WINCNT);
    auto winRate = ScoreManager::getInstance()->getScore(DATA_M->getIsThreeModel()?2:1, ScoreManager::Type::WINRATE);
    //得到连败场数
    auto faildNum = ScoreManager::getInstance()->getScore(!DATA_M->getIsThreeModel()?1:0, ScoreManager::Type::FAILDNINGSNT);
    //失败两次了 就换简单的
    bool isFaild = faildNum >= 1;
    return totalWinCNT > 1 && winRate>45 && !isFaild;
}

// random generator function:
int myrandom (int i) { return std::rand()%i;}
constexpr int SUM(int total)
{
    return total==0?0:total+SUM(total-1);
}
constexpr int SIMPLE_CHECK_SUM = SUM(51);
static int EASY_BUREAU_CNT = 2300;   // 单张牌局 前1000把 比较简答
static int OTHER_BUREAU_CNT = 10000;   // 单张牌局 别人的 可能比较难...
static int HARD_BUREAU_MOVES1 = 0, HARD_BUREAU_MOVES2 = 100, HARD_BUREAU_PERCENT1 = 800, HARD_BUREAU_PERCENT2 = 900;
void SpriteManager::reloadFile()
{

#if TEST_OTHER_BUREAU
    auto data = FileUtils::getInstance()->getDataFromFile("data/bureau_new.data");
#else
    auto data = FileUtils::getInstance()->getDataFromFile("data/bureau1.d");
#endif
    cocos2d::utils::image_decrypt(&data);
    bureauData = std::string((char*)data.getBytes(), data.getSize());

#if TEST_OTHER_BUREAU
    auto data3 = FileUtils::getInstance()->getDataFromFile("data/bureau_daily3.txt");
#else
    auto data3 = FileUtils::getInstance()->getDataFromFile("data/bureau3.d");
#endif

    cocos2d::utils::image_decrypt(&data3);
    bureau3Data = std::string((char*)data3.getBytes(), data3.getSize());
    
    auto dataTeach = data;
    cocos2d::utils::image_decrypt(&dataTeach);
    bureauTeachData = std::string((char*)dataTeach.getBytes(), dataTeach.getSize());
    
    auto dataHard = FileUtils::getInstance()->getDataFromFile("data/bureau1.d");
    cocos2d::utils::image_decrypt(&dataHard);
    hardData = std::string((char*)dataHard.getBytes(), dataHard.getSize());
    
    EASY_BUREAU_CNT = UIUtils::getJsonIntData("easy_bureau.json", "EASY_BUREAU_CNT", EASY_BUREAU_CNT);
    HARD_BUREAU_MOVES1 = UIUtils::getJsonIntData("easy_bureau.json", "moves1", HARD_BUREAU_MOVES1);
    HARD_BUREAU_MOVES2 = UIUtils::getJsonIntData("easy_bureau.json", "moves2", HARD_BUREAU_MOVES2);
    HARD_BUREAU_PERCENT1 = UIUtils::getJsonIntData("easy_bureau.json", "percent1", HARD_BUREAU_PERCENT1);
    HARD_BUREAU_PERCENT2 = UIUtils::getJsonIntData("easy_bureau.json", "percent2", HARD_BUREAU_PERCENT2);
//    auto data100 = FileUtils::getInstance()->getDataFromFile("data/bureau100.d");
//    cocos2d::utils::image_decrypt(&data100);
//    bureau100Data = std::string((char*)data100.getBytes(), data100.getSize());
}

string SpriteManager::getBureau(int t) {
    const string *bureauDataP = nullptr;
    if (t == 1) bureauDataP = &bureauData;
    else bureauDataP = &bureau3Data;
    // 测试别人牌局
    size_t length = bureauDataP->size();
    int totalCNT = MAX(1, floor(length/53));
    long currentIDX = rand() % totalCNT;
    auto it = bureauDataP->begin()+currentIDX*53;
    return string(it, it + 52);
}

void SpriteManager::initCardIds(const string &pokers)
{
    static auto inited = false;
    bool notfirstInit = inited;
    if (!inited) {
        srand((unsigned)time(0));
        
//        std::function<void(void*)> mainThread = [this](void* param)
//        {
        // 牌局难度为 0->100 100是解开概率越大越简单
        reloadFile();
//            bureauData = new string((char*)data.getBytes(), data.getSize());
//        };
//        AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO, mainThread, nullptr, []()
//                                              {
//                                              });
        inited = true;
    }
    auto sum = 0;
    auto playedCNT = GETINTEGER("newplay_cnt", 0); // 前十把都是活局
    SETINTEGER("newplay_cnt", ++playedCNT);
    auto isNewPlayer = playedCNT<10;
    //auto gameHard = DATA_M->getGameHard(); // 活局难度
    auto gameHard = DATA_M->getElo();
    if (isNewPlayer) {
        //gameHard = DATA_M->getGameType() == DataManager::GameType::Huo?100:20;
    }
    bool isTeachBureau = false; //ScoreManager::getInstance()->getWinTotalCNT(true) == 0;
    if (isNewPlayer || DATA_M->getGameType() == DataManager::GameType::Huo || DATA_M->getGameType() == DataManager::GameType::Level || DATA_M->getGameType() == DataManager::GameType::Daily) {  // 如果是活局或者关卡特殊处理
        const string *bureauDataP = nullptr;
        int totalCNT, currentIDX = 0;
        if (DATA_M->getGameType() == DataManager::GameType::Level || DATA_M->getGameType() == DataManager::GameType::Daily)
        {
            bureauDataP = &pokers;
        }
        else {
            if (isTeachBureau && !bureauTeachData.empty() && !isThreeModel) {
                bureauDataP = &bureauTeachData;
            }
            else if (!bureauData.empty() && !isThreeModel) {
                bureauDataP = &bureauData;
            }
            else if (!bureau3Data.empty() && isThreeModel) {
                bureauDataP = &bureau3Data;
            }
        }
        if (bureauDataP) {  // 活局逻辑
            if (*bureauDataP != pokers)  // 指定了牌局的 不处理
            {
                size_t length = bureauDataP->size();
                if (isThreeModel)
                {
                    totalCNT = MAX(1, floor(length/53));
                    currentIDX = rand() % totalCNT;
                }
                else
                {
                    if (isTeachBureau) {
                        currentIDX = TEACH_M->getTeachBureauIdx(*bureauDataP);
                    }
                    else {
#if TEST_OTHER_BUREAU
                        // 测试别人牌局
                        totalCNT = MAX(1, floor(length/53));
                        currentIDX = rand() % totalCNT;
#else
                        // HARD_BUREAU_MOVES1 最小步数 HARD_BUREAU_MOVES2 最大步数 胜率1000是最大 HARD_BUREAU_PERCENT1 最小胜率 HARD_BUREAU_PERCENT2 最大胜率
                        //计算最大与最小值
                        HARD_BUREAU_PERCENT1 = (gameHard-1) * 10;
                        /*
                        HARD_BUREAU_PERCENT2 = (gameHard+1) * 10;
                        if(HARD_BUREAU_PERCENT1 < 190) HARD_BUREAU_PERCENT1 = 190;
                        if(HARD_BUREAU_PERCENT2 > 1000) HARD_BUREAU_PERCENT2 = 1000;
                        totalCNT = MIN(floor(length/53), MAX(1, floor(length/53)));
                        currentIDX = BureauTestManager::getInstance()->getHardBureauData(HARD_BUREAU_PERCENT1, HARD_BUREAU_PERCENT2);
                        if (currentIDX < 0 || currentIDX > totalCNT) { // 牌局读取又问题 就找一局
                            currentIDX = rand() % totalCNT;
                        }*/
                        // 胜率45 以上就难的
                        bool otherBureau = userOtherBureau();
                        totalCNT = MAX(1, floor(length/53));
                        totalCNT = MIN(totalCNT, MAX(1, otherBureau?OTHER_BUREAU_CNT:(totalCNT-OTHER_BUREAU_CNT)));
//                        totalCNT = MIN(floor(length/53), MAX(1, otherBureau?OTHER_BUREAU_CNT:floor(length/53)));
                        currentIDX = rand() % totalCNT + (otherBureau?0:(OTHER_BUREAU_CNT-1));
                        CCLOG("WTF newIndex: %d(%d, %d)", currentIDX, HARD_BUREAU_PERCENT1, HARD_BUREAU_PERCENT2);
#endif
                    }


//                    bool isEasyBureau = !donotNeedEasyBureau();
//                    totalCNT = MIN(floor(length/53), MAX(1, isEasyBureau?EASY_BUREAU_CNT:floor(length/53)));
//                    currentIDX = rand() % totalCNT;

//                    if (notfirstInit && !TEACH_M->isDailyLevelUnlock()) {
//                        currentIDX = TEACH_M->getTeachBureauIdx(*bureauDataP);
//                    }
//                    else {
//                        bool isEasyBureau = !donotNeedEasyBureau();
//                        totalCNT = MIN(floor(length/53), MAX(1, isEasyBureau?EASY_BUREAU_CNT:floor(length/53)));
//                        currentIDX = rand() % totalCNT;
//                        if (gameHard > 0) {
//                            auto onePice = totalCNT/100;
//                            currentIDX = cocos2d::random(onePice * (gameHard-1), onePice * gameHard);
//                        }
//                    }

                }

            }
            if (sum == 0) { // 如果没有找到 就找一局
                auto it = bureauDataP->begin()+currentIDX*53;
                for (int i = 0; i < 52; i++)
                {
                    auto value = *(it+51-i)-'0';
                    cardIds.push_back(value);
                    sum+=value;
                }
            }
        }
    }
    else if (!hardData.empty()) { // 困难
        const string *bureauDataP = isThreeModel?&bureau3Data:&hardData;
        size_t length = bureauDataP->size();
        int totalCNT = MAX(1, floor(length/53));
        int currentIDX = rand() % totalCNT;
        auto it = bureauDataP->begin()+currentIDX*53;
        for (int i = 0; i < 52; i++)
        {
            auto value = *(it+51-i)-'0';
            cardIds.push_back(value);
            sum+=value;
        }
    }
    if (sum != SIMPLE_CHECK_SUM) {
        cardIds.clear();
        for (int i = 0; i < 52; i++)
        {
            cardIds.push_back(i);
        }
        std::random_shuffle(cardIds.begin(), cardIds.end(), myrandom);
    }
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    if (0) {
        cardIds.clear();
        sum = 1;
//        string testBureau = "0215439876>=<;:DCBA@?KJIHGFELMNOPQRSTUVWXYZ[\\]^_`abc";
//        reverse(testBureau.begin(), testBureau.end());
//        HX73C;c_@>N:P6`0AUFY5<WO=[BbGS\94D^IV1JT8ELRM2Q]ZK?a // bug 连续点击 牌没翻过来
        string testBureau = "FVcRKX]P=WDH1NZ68^LICAB50UY>EMG[7b4T:J\\_9Q@;<?SO`3a2";
        for (auto c=testBureau.rbegin();c!=testBureau.rend();c++){
//        for (auto c:testBureau) {
            auto value = *c-'0';
            sum+=value;
            cardIds.push_back(value);
        }
    }
    CCLOG("%d-sum(%d)", cardIds.size(), sum);
#endif
    
    if (!cardIds.empty())
    {
        currentBureau = "";
        for (auto it = cardIds.begin(); it!=cardIds.end(); it++) {
            currentBureau += (*it+'0');
        }
    }
    reverse(currentBureau.begin(), currentBureau.end());
    CCLOG("WTF:%s", currentBureau.c_str());
}

Sprite * SpriteManager::initGameBg()
{
	int gameBgType = DATA_M->getCardPicType(1);

    auto maxi = LiveGameBGCNT-1;
	auto flag = gameBgType < maxi;
    if(gameBgType>13)
    {
        gameBg = Sprite::create(/*StringUtils::format(BgFormat, flag ? 0 : 1)*/);
        auto size = Director::getInstance()->getWinSize();
        gameBg->setContentSize(size);
        auto scale = Director::getInstance()->getWinSize().width/gameBg->getContentSize().width;
        //gameBg->setScale(scale, scale);
        ShopManager::getInstance()->changeGameBG(gameBg, panel_game, gameBgType-12);
    }
    else
    {
        
        gameBg = Sprite::create(StringUtils::format(BgFormat, flag ? 0 : gameBgType-maxi));
        auto size = Director::getInstance()->getWinSize();
        gameBg->setContentSize(size);
        auto scale = Director::getInstance()->getWinSize().width/gameBg->getContentSize().width;
        gameBg->setScale(scale, scale);
    }
	
    
    // 动态背景
    for (int i=0; i<maxi; i++) {
        auto node = UIUtils::createCSBNode(StringUtils::format("game_bg%d.csb", i), "loop", true);
        magicBG.push_back(node);
        gameBg->addChild(node);
        node->setVisible(gameBgType==i);
    }

//    if (gameBgType == 0)
//    {
//        gameBg->setColor(Color3B(29,121,62));
//    }
//    else if (gameBgType == 1)
//    {
//        gameBg->setColor(Color3B(147, 41, 41));
//    }
//    else if (gameBgType == 2)
//    {
//        gameBg->setColor(Color3B(0, 101, 151));
//    }
	return gameBg;
}

void SpriteManager::setGamePanel(Node * panel_game)
{
	this->panel_game = panel_game;
	tipsLayer = LayerColor::create(Color4B(0, 0, 0, 128));
	tipsLayer->setLocalZOrder(100);
	tipsLayer->setVisible(false);
    tipsLayer->setName("TipsLayer");
    tipsLayer->setContentSize(Director::getInstance()->getWinSize()/panel_game->getScaleX());
	panel_game->addChild(tipsLayer);
    tipsLayer->setPosition(panel_game->convertToNodeSpace(Vec2::ZERO));
}

void SpriteManager::changeGameBG(int gameBgType)
{
    return;
    if(gameBgType>13)
    {//动态
        //换游戏背景
        auto maxi = LiveGameBGCNT-1;
        auto flag = gameBgType < maxi;
        gameBg->setSpriteFrame(Sprite::create(StringUtils::format(BgFormat, flag ? 0 : 1))->getSpriteFrame());
        auto scale = Director::getInstance()->getWinSize().width/gameBg->getContentSize().width;
        gameBg->setScale(1, 1);
        auto size = Director::getInstance()->getWinSize();
        gameBg->setContentSize(size);
        ShopManager::getInstance()->changeGameBG(gameBg, panel_game, gameBgType-12);
        
    }
    else
    {
        ShopManager::getInstance()->removeBG(gameBg, panel_game);
        //换游戏背景
        auto maxi = LiveGameBGCNT-1;
        auto flag = gameBgType < maxi;
        gameBg->setSpriteFrame(Sprite::create(StringUtils::format(BgFormat, flag ? 0 : gameBgType-maxi))->getSpriteFrame());
        auto scale = Director::getInstance()->getWinSize().width/gameBg->getContentSize().width;
        gameBg->setScale(scale, scale);
        for (int i=0; i<maxi; i++) {
            magicBG[i]->setVisible(gameBgType==i);
        }
        //刷新背景音效
        EVENT_M->sendEvent("event_game_scene_change");
    }
}

void SpriteManager::changeCardSkin(int changeType, bool isTeach/* = false*/)
{
	if (changeType == 1)
	{
        //完成替换背景
        if(!isTeach)
        {
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::GAMEBG);
            SCENE_M->showTips(UIUtils::getStringByName("changegamebg"));
        }
        
		
		int gameBgType = DATA_M->getCardPicType(1);
        changeGameBG(gameBgType);
		
//        if (gameBgType == 0)
//        {
//            gameBg->setColor(Color3B(29, 121, 62));
//        }
//        else if (gameBgType == 1)
//        {
//            gameBg->setColor(Color3B(147, 41, 41));
//        }
//        else if (gameBgType == 2)
//        {
//            gameBg->setColor(Color3B(0, 101, 151));
//        }
//        else
//        {
//            gameBg->setColor(Color3B::WHITE);
//        }
	}
	else if (changeType == 2 || changeType == 3)
	{
		if (changeType == 2)
		{
            //累计牌面任务
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::CARDFACE);
			SCENE_M->showTips(UIUtils::getStringByName("changecardface"));
		}
		else
		{
            //累计牌背任务
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::CARDBG);
			SCENE_M->showTips(UIUtils::getStringByName("changecardbg"));
		}
		//换牌
		for (int col = 0; col < 7; col++)
		{
			for (int row = 0; row < kCardVector[col].size();row++)
			{
				auto card = kCardVector[col].at(row);
				if (card)
				{
					card->initCardNum();
				}
			}
		}

		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < aCardVector[col].size(); row++)
			{
				auto card = aCardVector[col].at(row);
				if (card)
				{
					card->initCardNum();
				}
			}
		}

		for (int row = 0; row < waitCardVector.size(); row++)
		{
			auto card = waitCardVector.at(row);
			if (card)
			{
				card->initCardNum();
			}
		}

		for (int row = 0; row < waitShowCardVector.size(); row++)
		{
			auto card = waitShowCardVector.at(row);
			if (card)
			{
				card->initCardNum();
			}
		}
	}
}

int SpriteManager::getCardId()
{
	if (isReplay)
	{
		if (isFilpX)
		{
			if (saveCardIdsFILPX.size() > 0)
			{
				int cardId = saveCardIdsFILPX.at(0);
				saveCardIdsFILPX.erase(saveCardIdsFILPX.begin());
				saveCardIds.push_back(cardId);
				return cardId;
			}
		}
		else
		{
			if (saveCardIds.size() > 0)
			{
				int cardId = saveCardIds.at(0);
				saveCardIds.erase(saveCardIds.begin());
				saveCardIdsFILPX.push_back(cardId);
				return cardId;
			}
		}
	}
	if (cardIds.size() <= 0)
	{
		return -1;
	}
    int index = 0;      //rand() % cardIds.size();
	int cardId = cardIds[index];
	cardIds.erase(cardIds.begin() + index);

	saveCardIds.push_back(cardId);
	return cardId;
}

vector<Point> SpriteManager::getCardInitPositions()
{
	vector<Point> initPos;
	int rowNum = 7, colNum = 7;
	for (int col = 0; col < 7; col++)
	{
		for (int row = 0; row < 7; row++)
		{
			if (col >= row)
			{
				initPos.push_back(getKCardPosByIndex(col,row));
			}
		}
	}
	return initPos;
}

vector<Point> SpriteManager::getCardInitPositions2()
{
    vector<Point> initPos;
    for (int col = 6; col >= 0; col--)
    {
        for (int row = 6; row >= 0; row--)
        {
            if (col == row)
            {
                initPos.push_back(getKCardPosByIndex(col,row));
            }
        }
    }
    return initPos;
}

//清理所有的数据
void SpriteManager::clearAllData()
{
	for (int col = 0; col < 4; col++)
	{
		for (int i = 0; i< aCardVector[col].size(); i++)
		{
			auto card = aCardVector[col].at(i);
			if (card)
			{
				card->removeFromParentAndCleanup(true);
			}
		}
		aCardVector[col].clear();
	}

	for (int col = 0; col < 7; col++)
	{
		for (int i = 0;i< kCardVector[col].size(); i++)
		{
			auto card = kCardVector[col].at(i);
			if (card)
			{
				card->removeFromParentAndCleanup(true);
			}
		}
		kCardVector[col].clear();
	}

	for (int i = 0; i< waitCardVector.size(); i++)
	{
		auto card = waitCardVector.at(i);
		if (card)
		{
			card->removeFromParentAndCleanup(true);
		}
	}
	for (int i = 0; i< waitShowCardVector.size(); i++)
	{
		auto card = waitShowCardVector.at(i);
		if (card)
		{
			card->removeFromParentAndCleanup(true);
		}
	}

	waitCardVector.clear();
	waitShowCardVector.clear();
	moveDatas.clear();
	clearTipsData();
	initCardNum = 0;
    currentMusicLevel = 1;      // 当前声音idx
    noCombo = 0;                // 当前连击数
    // 停止逻辑
    tipsLayer->stopAllActions();
    panel_game->stopActionByTag(10086111);
}

void SpriteManager::resetGame(const string pokers)
{
    auto gameType = DATA_M->getGameType();
    //初始化 洗牌方式类型
    _shuffleType = ShuffleType::None;
    isThreeModel = (gameType==DataManager::GameType::Daily||gameType==DataManager::GameType::Level)?isThreeModel:DATA_M->getIsThreeModel();
	noMoreMoveMark = -1;
	isReplay = false;
	isFilpX = true;
    //-------新开 开启 翻开有效
    //againMoveNum = 0;
    //根据胜率判断是否开启翻牌有效
    isFanPaiNum = false;
    fanPaiNum = -1;
    isChongKai = false;
    //初始道具ai
    isDaoJuAI = false;
    daoJuAINum = -1;
    //困难模式限定步数
    randomTempMoveNum = 0;
    randomMoveNum = 0;
    //判断是否开启ai
    openEffective();
    hongColor = random(0, 1) == 0?1:3;//1 3
    heiColor = random(0, 1) == 0?0:2;//0 2
    isAutoFinshGame = false;
//    isOpenEffective = true;
//    isFanPaiNum = false;
//    fanPaiNum = -1;
    //-----------
    stopShuffle();
	clearAllData();
	saveCardIds.clear();
    cardIds.clear();
	saveCardIdsFILPX.clear();
	initCardIds(pokers);//重新生成牌序列

	initKCard();
}

void SpriteManager::replayGame()
{
//    isThreeModel = DATA_M->getIsThreeModel();
    //初始化 洗牌方式类型
    _shuffleType = ShuffleType::None;
	isReplay = true;
	isFilpX = !isFilpX;
    
    //重开 取消 翻开有效
    //againMoveNum = 0;
    //根据胜率判断是否开启翻牌有效 重开时不判断是否开启 沿用上一把的判断条件
    isFanPaiNum = false;
    fanPaiNum = -1;
    isChongKai = true;
    //初始道具ai
    isDaoJuAI = false;
    daoJuAINum = -1;
    //困难模式限定步数
    randomMoveNum = 0;
    randomTempMoveNum = 0;
    openEffective();
    hongColor = random(0, 1) == 0?1:3;//1 3
    heiColor = random(0, 1) == 0?0:2;//0 2
    isAutoFinshGame = false;
//    isOpenEffective = true;
//    isFanPaiNum = false;
//    fanPaiNum = -1;
    //-------------------
    stopShuffle();
	clearAllData();

	initKCard();
}

SpriteFrame * SpriteManager::getCardBgSpriteFrame(int pos)
{
	/*auto cardBgType = DATA_M->getCardPicType(3);
    if (cardBgType == QINGLONG_TYPE) {
        auto pngName = StringUtils::format("vipbg0_%d.png", MIN(21, pos));
//        CCLOG(pngName.c_str());
        return SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName);
	}
	else {
        return SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("card_bg_%d.png", DATA_M->getCardPicType(3)));
    }*/
    return AtlasManager::getInstance()->getSF(3, 0, 0, pos);
}

SpriteFrame * SpriteManager::getCardSpriteFrameByNumAndColor(int number, int color, int picType)
{
//    auto imgStr = StringUtils::format("card_%d_%d_%d.png", DATA_M->getCardPicType(2), number, color);
//    CCLOG("Get card(%s)", imgStr.c_str());
//    return SpriteFrameCache::getInstance()->getSpriteFrameByName(imgStr);
    return AtlasManager::getInstance()->getSF(2, number, color, picType);
}

SpriteFrame * SpriteManager::getCardSpriteFrameByNumAndColor(const string cardStr)
{
    auto imgStr = StringUtils::format("task/task_card_0_%s.png", cardStr.c_str());
    CCLOG("Get card(%s)", imgStr.c_str());
	return SpriteFrameCache::getInstance()->getSpriteFrameByName(imgStr);
}

SpriteFrame * SpriteManager::getSpecialCardSpriteFrame(const string cardStr, bool isLittle)
{
    return SpriteFrameCache::getInstance()->getSpriteFrameByName(isLittle?"Level_card0.png":"Level_card1.png");
}

void SpriteManager::initCard()
{
	//初始化A的位置
	for (int i = 0; i < 4; i++)
	{
//        aSprite[i] = Sprite::create("img_card_a.png");
//        aSprite[i]->setScale(0.9);
//        aSprite[i]->setPosition(SPRITE_M->getACardPosByIndex(i));
//        panel_game->addChild(aSprite[i]);
        aSprite[i] = panel_game->getChildByName<Sprite*>(StringUtils::format("Sprite_aPoker%d", i));
	}

	//初始化K的位置
	for (int i = 0; i < 7; i++)
	{
//        kSprite[i] = Sprite::create("img_card_k.png");
//        kSprite[i]->setScale(0.9);
//        kSprite[i]->setPosition(SPRITE_M->getKCardPosByIndex(i));
//        panel_game->addChild(kSprite[i]);
        kSprite[i] = panel_game->getChildByName<Sprite*>(StringUtils::format("Sprite_pokerStack%d", i));
	}
    
    //结束动画1
    auto endani1Node = panel_game->getChildByName("Node_endAni1");
    endAni1_1Poi = endani1Node->getChildByName("Node_end1_1")->getPosition();
    endAni1_2Poi = endani1Node->getChildByName("Node_end1_2")->getPosition();
    endAni1_3Poi = endani1Node->getChildByName("Node_end1_3")->getPosition();
    //结束动画2
    auto endani2Node = panel_game->getChildByName("Node_endAni2");
    endAni2Vec.clear();
    for(int i = 1;i < 9;++i)
    {
        endAni2Vec.push_back(endani2Node->getChildByName(StringUtils::format("Node_end2_%d",i))->getPosition());
    }
    //结束动画3
    auto endani3Node = panel_game->getChildByName("Node_endAni3");
    endAni3Vec.clear();
    for(int i = 1;i < 5;++i)
    {
        endAni3Vec.push_back(endani3Node->getChildByName(StringUtils::format("Node_end3_%d",i))->getPosition());
    }
    //结束动画4
    auto endani4Node = panel_game->getChildByName("Node_endAni4");
    endAni4Vec.clear();
    for(int i = 1;i < 5;++i)
    {
        endAni4Vec.push_back(endani4Node->getChildByName(StringUtils::format("Node_end4_%d",i))->getPosition());
    }
    //结束动画5
    auto endani5Node = panel_game->getChildByName("Node_endAni5");
    endAni5Vec.clear();
    for(int i = 1;i < 5;++i)
    {
        endAni5Vec.push_back(endani5Node->getChildByName(StringUtils::format("Node_end5_%d",i))->getPosition());
    }
    //结束动画6
    auto endani6Node = panel_game->getChildByName("Node_endAni6");
    endAni6Vec.clear();
    for(int i = 1;i < 5;++i)
    {
        endAni6Vec.push_back(endani6Node->getChildByName(StringUtils::format("Node_end6_%d",i))->getPosition());
    }
    
    waitSprite = panel_game->getChildByName<Sprite*>("Sprite_wait");
    Node_waitOpen = panel_game->getChildByName("Node_waitOpen");
    Node_waitOpenThree = panel_game->getChildByName("Node_waitOpenThree");
    startNode = panel_game->getChildByName("Node_start");
    startNode->setLocalZOrder(102); // 置顶
    _skeletonNode = SkeletonAnimation::createWithJsonFile("res/poker.json", "res/poker.atlas", 1.f);
    _skeletonNode->setVisible(false);
    _skeletonShuffleNode = SkeletonAnimation::createWithJsonFile("res/Shuffle.json", "res/Shuffle.atlas", 1.f);
    _skeletonShuffleNode->setVisible(false);
    _skeletonNode->setCompleteListener([this](spTrackEntry* entry) {
        if(_shuffleType == ShuffleType::Box)
        {
            auto isGuangGao = DATA_M->getGuangGao();
            if(isGuangGao)
            {
                auto id = DATA_M->getStartAni();
                if(id == 0)
                {
                    initKCardAfter();
                }
                else if(id == 1)
                {
                    pokerStartAni1();
                }
                else if(id == 2)
                {
                    pokerStartAni2();
                }
            }
            else
            {
                initKCardAfter();
            }
            
            //
        }
    });
    _skeletonShuffleNode->setCompleteListener([this](spTrackEntry* entry) {
        if(_shuffleType == ShuffleType::Shuffing)
        {
            _skeletonShuffleNode->setVisible(false);
            
            auto isGuangGao = DATA_M->getGuangGao();
            if(isGuangGao)
            {
                auto id = DATA_M->getStartAni();
                if(id == 0)
                {
                    initKCardAfter();
                }
                else if(id == 1)
                {
                    pokerStartAni1();
                }
                else if(id == 2)
                {
                    pokerStartAni2();
                }
            }
            else
            {
                initKCardAfter();
            }
        }
    });
    
    startNode->addChild(_skeletonNode);
    startNode->addChild(_skeletonShuffleNode);
    _skeletonNode->setPositionY(-100);
	//initKCard();
}

void SpriteManager::stopShuffle()
{
    if(_skeletonNode->isVisible())
    {
        _skeletonNode->stopAllActions();
        _skeletonNode->setVisible(false);
    }
    if(_skeletonShuffleNode->isVisible())
    {//已经隐藏了
        _skeletonShuffleNode->stopAllActions();
        _skeletonShuffleNode->setVisible(false);
    }
}

void SpriteManager::initKCard()
{
    auto gameView = SCENE_M->getGameView();
    if (gameView)
        gameView->unschedule(AutoFinishKey);
	SOUND_M->playEffectMusic(EffectShuffle);
    auto shufflingFirst_ = getShufflingFirst();
    if (shufflingFirst_ == ShuffingType::Box) {
        _skeletonNode->setVisible(true);
        _skeletonNode->setAnimation(0, "animation", false);
        _shuffleType = ShuffleType::Box;
    }
    else/* if (shufflingFirst_ == ShuffingType::Shuffing)*/ {
        _skeletonShuffleNode->replaceAttachmentsByRegion("card_bg_0", "card_bg_0", AtlasManager::getInstance()->getRegion(3));  // 更换卡背先
        isShuffle = false;
        _skeletonShuffleNode->setVisible(true);
        _skeletonShuffleNode->setAnimation(0, cocos2d::random(0, 1) == 0?"Shuffle0":"Shuffle1", false);
        _shuffleType = ShuffleType::Shuffing;
    }
    /*else {
        initKCardAfter();
    }*/
}
/*
 递增加5
 1, 2, 3, 4, 5, 6, 7
   13,14,15,16,17,18
      24,25,26,27,28
         34,35,36,37
            43,44,45
               51,52
                  58
 0 1 2 3 4 5 6
   1 2 3 4 5 6
     2 3 4 5 6
       3 4 5 6
         4 5 6
           5 6
             6
 0 1 1 2 2 2 3 3 3 3 4 4 4 4 4 5 5 5 5 5 5 6 6 6 6 6 6 6
 0 1 2 3 4 5 6
0,0
0,1
1,1
0,2
1,2
2,2
 
 1  2  3  4  5  6  7
   10  9  8  7  6  5
    8  9 10 11 12 13
      15 14 13 12 11
         13 14 15 16
            16 15 14
               14 15
                  13
 for(int i = 0;i< 7;++i)
 {
    for(int j = 0;j<7;++j)
    {
        if(i == j)
        {//0,0 0,1
            a[i][j]
        }
    }
 }
 */
/*
 1,2,8,3,9,14,4,10,15,19,5,11,16,20,23,6,12,17,21,24,26,7,13,18,22,25,27,28
 1,2,13,3,14,24,4,15,25,34,5,16,26,35,,43,6,17,27,36,44,51,7,18,28,37,45,52,58
 */

void xnumber(vector<float> &dxVec)
{
    //-----
    float dx = 0;
    float a[7][7];
    memset(a, 0, sizeof(a));
    for(int i = 6;i >= 0;--i)
    {
        for(int j = 0;j<7;++j)
        {
            if(i >= j)
            {//
                dx++;
                
                //dxVec.push_back(dx);
                auto x = i%2 == 0?j:i-j;
                if(i==6||i == 4)
                {//第一排和第三排加速
                    a[6-i][x] = dx - 0.5;
                }
                else if(i == 1)
                {//倒数第二排慢一些
                    a[6-i][x] = dx + 1;
                }
                else if(i == 0)
                {//倒数第一排在慢一些
                    a[6-i][x] = dx + 2;
                }
                else
                {
                    a[6-i][x] = dx;
                }
                //仅增加一次
                if(i == j&&i!= 1&&(i == 6||i == 4))
                {
                    dx -= faPaiJiaSu;
                }
            }
        }
    }
    for(int i = 0;i< 7;++i)
    {
       for(int j = 0;j<7;++j)
       {
           if(i >= j)
           {
                dx = a[j][i - j];
                dxVec.push_back(dx);
           }
        }
    }
    //dxVec.clear();
}

//int DX[] = {1,2,13,3,14,24,4,15,25,34,5,16,26,35,43,6,17,27,36,44,51,7,18,28,37,45,52,58};
int flight[] = {0, 1, 2, 3, 3, 4, 4};
int tempIdxArr[] = {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6};
//{0, 1, 5, 2, 4, 0, 3, 3, 1, 3, 4, 2, 2, 2, 0, 5, 1, 3, 1, 1, 1, 6, 0, 4, 0, 2, 0, 0};
//{0, 1, 4, 2, 3, 0, 3, 3, 1, 3, 3, 2, 2, 2, 0, 4, 1, 3, 1, 1, 1, 4, 0, 3, 0, 2, 0, 0};
//                 {0, 1, 0, 2, 1, 0, 3, 2, 1, 0, 3, 3, 2, 1, 0, 4, 3, 3, 2, 1, 0, 4, 4, 3, 3, 2, 1, 0};

void SpriteManager::initKCardAfter()
{
    vector<float> dxVec;
    xnumber(dxVec);
    
    Vec2 beginPos = startNode->getPosition();               //panel_game->convertToNodeSpace(Vec2(winSize.width/2, -200));
    vector<Vec2> endPosions = getCardInitPositions();
    int endPosIndex = 0;
    int idx = 1;
    for (int col = 0; col < 7; col++)
    {
        for (int row = 0; row < 7; row++)
        {
            if (col >= row)
            {
                int cardId = SPRITE_M->getCardId();
                if (cardId < 0)
                {
                    continue;
                }
                auto cardSprite = CardSprite::createCardSprite(cardId, col==row?idx-1:idx++, col==row);
                cardSprite->setPosId(CARD_POS_K);
                cardSprite->setPosition(beginPos);
                cardSprite->setCardLocalZOrder((int)kCardVector[col].size() + 1 + TotalWatiCardNum);
                cardSprite->setVisible(false);
                
                cardSprite->setColNum(col);
                panel_game->addChild(cardSprite);
                kCardVector[col].pushBack(cardSprite);
                
                Point endPos = endPosions[endPosIndex ++ ];
                float mvDt = 0.4f;
                float delayOff = faPaiDelayTime;//float delayOff = 0.04f;
                auto *mvBy = MoveBy::create(0.02, Vec2(0, 100));
                MoveTo *mvTo = MoveTo::create(mvDt, endPos);
                DelayTime *delay = DelayTime::create(dxVec[endPosIndex - 1] * delayOff + 0.2);//DelayTime::create(endPosIndex * delayOff + 0.2);(col + row)
                auto show = Show::create();
                
                auto callFunc1 = col==6&&3==row?CallFunc::create([this, col]() {//auto callFunc1 = col==row?CallFunc::create([this, col]() {
                    //openKCardByCol(col);//都发完牌后依此翻开

                    initWaitCard();
                }):nullptr;
                auto callFunc2 = endPosIndex == endPosions.size()?CallFunc::create([this, col]() {
                    
                }):nullptr;
                auto func = CallFunc::create([this,endPosIndex,cardSprite](){
                    cardSprite->playFaPai(tempIdxArr[endPosIndex - 1]);
                });
                auto speed = Speed::create(Sequence::create(delay, mvBy,show, func, mvTo, callFunc1, callFunc2, NULL), 0.735);
                
                cardSprite->runAction(speed);
            }
        }
    }
    if(!isChongKai)
    {//是新开
        updateAgainVec();
    }
}

void SpriteManager::initWaitCard()
{
    auto width = waitSprite->getContentSize().width + UIUtils::IsPad()?280:60;
    float mvDt = MVDT;
    //每张牌的延时
    float delayTime = 0.1;
    //延时递增数值
    float dt = DT_0;
    //初始角度
    float angle = DATA_M->getIsLeftModel()?-ANGLE:ANGLE;
    //翻牌延时
    //float fanPaiDt = 0.1;
//    int endPosIndex = 0;
	for (int num = 0; num < TotalWatiCardNum; num++)
	{
        Point endPos = getWaitCardPos(num);
        Point beginPos = endPos+Point(DATA_M->getIsLeftModel()?-width:width, 00);
		int cardId = SPRITE_M->getCardId();
		if (cardId < 0)
		{
			continue;
		}
		auto cardSprite = CardSprite::createCardSprite(cardId);
        cardSprite->setRotation(WaitPokerOffset[UIUtils::clamp(num, 0, 7)].z);
        auto s = UIUtils::clamp(num, 0, 8);
        cardSprite->getShaderS()->setColor(WaitPokerColor[s]);
		cardSprite->setPosition(beginPos);
		cardSprite->setPosId(CARD_POS_WAIT);
		cardSprite->setCardLocalZOrder(num);
        cardSprite->setRotation(angle);
		panel_game->addChild(cardSprite);
		waitCardVector.pushBack(cardSprite);
		
		MoveTo *mvTo = MoveTo::create(mvDt, endPos);
        RotateTo* rota = RotateTo::create(mvDt,0);
        auto spawn = Spawn::create(mvTo,rota, NULL);
		DelayTime *delay = DelayTime::create(delayTime);
        delayTime += dt;
		if (num == 23)
		{
            auto delay2 = DelayTime::create(0);
			cardSprite->runAction(Sequence::create(delay, spawn,delay2, CallFunc::create([this]{
//                openKCard();
                //翻下方的牌
                float dt3 = 0;
                for(int i = 0;i<7;++i)
                {
                    auto node = Node::create();
                    panel_game->addChild(node);
                    auto delay3 = DelayTime::create(dt3);
                    auto delay4 = DelayTime::create(fanPaiJianGe*2);
                    auto func3 = CallFunc::create([this,i](){
                        openKCardByCol(i);
                    });
                    auto re3 = RemoveSelf::create();
                    
                    auto func = CallFunc::create([this](){
                        //发牌区翻牌
                        //_skeletonNode->setVisible(false);
                        checkWaitShowCard();
                    });
                    float time = 0;
                    if (isThreeModel)
                    {
                        time = 2*ThreeFlopSpaceTime;
                    }
                    auto delay5 = DelayTime::create(time);
                    auto func2 = CallFunc::create([this](){
                        //通知游戏界面可以开始
                        noticeGameStart();
                    });
                    auto seq3 = Sequence::create(delay3,func3,re3, NULL);
                    auto seq4 = Sequence::create(delay3,func3,delay4,func,delay5,func2,re3, NULL);
                    if(i == 6)
                    {
                        node->runAction(seq4);
                    }
                    else
                    {
                        node->runAction(seq3);
                    }
                    
                    dt3 += fanPaiJianGe;
                }
                
                _skeletonNode->setVisible(false);
//				checkWaitShowCard();
//				//通知游戏界面可以开始
//				noticeGameStart();
			}), NULL));
		}
		else
		{
            cardSprite->runAction(Sequence::create(delay,CallFunc::create([](){
                for(int i = 0;i<2;++i)
                {
                    i;
                }
            }), spawn, NULL));
		}
	}
    //是重开  提换和锁定上局翻开的牌
    if(isChongKai)
    {
        tiHuanCard();
    }
#if DEBUG_BACKMOVE
    printPokers(StringUtils::format("INIT:%s", currentBureau.c_str()));
#endif
}

void SpriteManager::noticeGameStart()
{
	SCENE_M->gameStart();
}

void SpriteManager::openKCard()
{
	for (int col = 0; col < 7; col++)
	{
		openKCardByCol(col);
	}
}

CardSprite* SpriteManager::openKCardByCol(int col,CardSprite* card)
{
	if (kCardVector[col].size() <= 0)
	{
		return nullptr;
	}
	auto cardSprite = kCardVector[col].at(kCardVector[col].size() - 1);
	if (cardSprite && !cardSprite->getIsOpen())
	{
        
#if TestAutoPlay
        if(0)//DATA_M->getGameType() == DataManager::GameType::Huo)
#else
        if(TEACH_M->isTaskUnlock()&&!TEACH_M->isTeaching())//DATA_M->getGameType() == DataManager::GameType::Huo) // 新手引导不开启
#endif
        {
            //        //判断移动步数 步数符合则开启翻牌有效
            if(!isOpenEffective&&isFanPaiNum&&fanPaiNum != -1&&fanPaiNum <= SCENE_M->getGameView()->getMoveNum())
            {// 限制步数。到指定步数时 开启辅助
                isOpenEffective = true;
                //更新辅助提示色块颜色
                SCENE_M->getGameView()->setFuZhuTipsColor(isOpenEffective);
                if(isOpenEffective)
                {
                    randEffective = random(1, 4);
                }
            }
            if(isOpenEffective||(isDaoJuAI&&daoJuAINum > 0))
            {
                effectiveCard(card,cardSprite,col);
            }
            else if(card)
            {//没有开启翻牌有效 防止重开后开启翻开有效 先锁定翻开的牌
                cardSprite->setIsJiaoHuan(true);
                updateIsOpenVec(cardSprite);
            }
        }
		cardSprite->openCardWithAction();
	}
	
	//0.2,秒后检测
    panel_game->stopActionByTag(10086111);
    auto action = Sequence::create(DelayTime::create(0.8), CallFunc::create([this]{
        if (checkIsAllOpen())
        {
            SCENE_M->showAutoFinishBtn(true);
        }
        
    }), NULL);
    action->setTag(10086111);
    panel_game->runAction(action);
    return cardSprite;
}

void SpriteManager::checkWaitShowCard()
{
	if (waitShowCardVector.size() == 0)
	{
		openWaitCard();
	}
}

void SpriteManager::openOneWaitCard(int i, float delay)
{
	if (waitCardVector.size() <= 0)
	{
		return;
	}
	auto cardSprite = waitCardVector.at(waitCardVector.size() - 1);
	if (!cardSprite){
		return;
	}

//    auto indexPos = waitShowCardVector.size();
//    cardSprite->setCardLocalZOrder(waitShowCardVector.size() + 1);
//    cardSprite->openCardWithAction(delay);
    cardSprite->openCardToPos(getWaitShowCardPosByIndex(i), delay);

//    cardSprite->setLocalZOrder(100);//将它置顶
	cardSprite->setPosId(CARD_POS_WAIT_SHOW);

	waitCardVector.eraseObject(cardSprite);
	waitShowCardVector.pushBack(cardSprite);
	
//	if (checkIsAllOpen())
//	{
//		SCENE_M->showAutoFinishBtn(true);
//	}
}

int SpriteManager::openWaitCard()
{

    auto waitCNT = waitCardVector.size();
    auto wsCNT = (int)waitShowCardVector.size();
	if (isThreeModel)
	{
        auto startIdx = 3-MIN(3, waitCNT);
		for (int i = startIdx; i < 3;i++)
		{
			openOneWaitCard(i, i*ThreeFlopSpaceTime);
		}
	}
	else
	{
		openOneWaitCard(2);
	}

	setShaderStatus(CARD_POS_WAIT,0);
	setShaderStatus(CARD_POS_WAIT_SHOW, 0);
//    SOUND_M->playEffectMusic(EffectMovePoker);
    int offset = int(waitCNT-waitCardVector.size());
	addjustWaitShowCard(offset);
	SCENE_M->updateWaitCardNum((int)waitCardVector.size());
#if DEBUG_BACKMOVE
    printPokers("OPEN");
#endif
    return wsCNT;
}

void SpriteManager::addjustWaitShowCard(int offset)
{//前面的牌后移
    auto waitShowCNT = waitShowCardVector.size();
    int indexPos = 3-offset;
    for (auto i=waitShowCNT-offset; i>0; --i) {
        auto card = waitShowCardVector.at(i-1);
        indexPos--;
        card->moveToPos(getWaitShowCardPosByIndex(MAX(indexPos, 0)));
        card->removeLevelTips();
    }
}

void SpriteManager::resetWaitCard()
{
	int waitShowNum = waitShowCardVector.size();
	for (int i = 0; i < waitShowNum ; i++)
	{
		auto cardSprite = waitShowCardVector.at(waitShowCardVector.size() - 1);
		cardSprite->closeCardToPos(getWaitCardPos(i), i*WaitCardRestTime);
        cardSprite->getShaderS()->setColor(WaitPokerColor[(waitShowNum-1==i)?8:UIUtils::clamp(i, 0, 8)]);

//        cardSprite->setCardLocalZOrder(waitCardVector.size() + 1);
//        cardSprite->setLocalZOrder(100);//将它置顶
		cardSprite->setPosId(CARD_POS_WAIT);
		waitCardVector.pushBack(cardSprite);
		waitShowCardVector.eraseObject(cardSprite);
	}

    auto totalWaitCardCNT = getTotalWaitCardCNT();
    if (totalWaitCardCNT>8) {
        SOUND_M->playEffectMusic(EffectCover);
    }
    else if (totalWaitCardCNT>3) {
        SOUND_M->playEffectMusic(EffectCover1);
    }
    else if (getTotalWaitCardCNT()>0) {
        SOUND_M->playEffectMusic(EffectCover2);
    }
	SCENE_M->updateWaitCardNum(waitCardVector.size());
	pushMoveData(MoveData::createMoveDataByReset());

//    if (isThreeModel)
//    {
//        SCENE_M->updateScore(-100);
//    }
//    else
//    {
//        SCENE_M->updateScore(-20);
//    }
}

CardSprite * SpriteManager::getCardSpriteByTouchPos(Point touchPos)
{

	for (int i = 0; i < 4; i++)
	{
		if (aCardVector[i].size() > 0)
		{
			auto card = aCardVector[i].at(aCardVector[i].size() - 1);
			if (card && card->getCheckBox().containsPoint(touchPos))
			{
				return card;
			}
		}
	}

	for (int i = 0; i < 7; i++)
	{
		//判断是否点击非第一张牌 K位置
		for (int row = 0; row < kCardVector[i].size();row++)
		{
			auto card = kCardVector[i].at(row);
			Rect checkRect;
			if (kCardVector[i].size() - 1 == row)
			{
				checkRect = card->getCheckBox();
			}
			else
			{
				checkRect = card->getHeadBox();
			}
			if (card && checkRect.containsPoint(touchPos) && card->getIsOpen())
			{
				return card;
			}
		}
	}
	
	if (waitShowCardVector.size() > 0)
	{
		auto card = waitShowCardVector.at(waitShowCardVector.size() - 1);
		if (card && card->getCheckBox().containsPoint(touchPos))
		{
			return card;
		}
	}
	
	//判断是否点击等待区域 是的话就发牌或者重置等待区域
	if (waitCardVector.size() > 0)
	{
		auto card = waitCardVector.at(waitCardVector.size() - 1);
		if (card && card->getCheckBox().containsPoint(touchPos))
		{
			return card;
		}
	}

	return NULL;
}

void SpriteManager::setCardSpritePos(CardSprite * card, Point delayPos, float moveOffsetY)
{//限制最下面的牌 不能低于横幅

    Vec2 offset(0,moveOffsetY);
    //转局部
    offset = card->getParent()->convertToNodeSpace(offset);
	if (card->getPosId() == CARD_POS_K)
	{
		//移动整个序列
        auto length = kCardVector[card->getColNum()].size();
		for (int i = card->getCLocalZOrder() - 1 - TotalWatiCardNum; i < kCardVector[card->getColNum()].size(); i++)
		{//有一列牌时  最后一张牌的rect.origin.y > 横幅高度
			auto dealCard = kCardVector[card->getColNum()].at(i);
            dealCard->setIsDrag(true);
            //取最下面的牌
            auto endCard = kCardVector[card->getColNum()].at(kCardVector[card->getColNum()].size()-1);
            auto rect = endCard->getBoundingBox();
            auto origin = rect.origin + delayPos;//移动的量
            Vec2 pos;//更新位置
            if(origin.y < offset.y)
            {//最后一张牌位置
                pos = dealCard->getPosition() + delayPos;
                //pos.y = moveOffsetY + 牌高度/2; 每张牌的间隔 OffsetOpen
                pos.y = offset.y + rect.size.height/2 + (length - i - 1) * OffsetOpen;
            }
            else
            {
                pos = dealCard->getPosition() + delayPos;
            }
			dealCard->setPosition(pos);
		}
	}
	else
	{//只有一张牌时，牌的rect.origin.y > 横幅高度
        auto rect = card->getBoundingBox();
        auto origin = rect.origin + delayPos;//移动的量
        Vec2 pos;
        if(origin.y < offset.y)
        {
            pos = card->getPosition() + delayPos;
            //pos.y = moveOffsetY + 牌高度/2;
            pos.y = offset.y + rect.size.height/2;
        }
        else
        {
            pos = card->getPosition() + delayPos;
        }
        
		card->setPosition(pos);
	}
	
}

//寻找牌的位置 置换到新的位置或者归位
bool SpriteManager::checkCardPos(CardSprite * card, bool isMoved)
{
    //记录选中牌
    tempMoveCard = card;
    if (noMoreMoveMark >= 0)
        ++noMoreMoveMark;  // 统计移动步骤
	int cardPosId = card->getPosId();
	int cardCol = card->getColNum();
	if (cardPosId == CARD_POS_WAIT)
	{
		int offset = openWaitCard();//发牌
		pushMoveData(MoveData::createMoveDataByShuffle(offset));
		SCENE_M->addMoveNum();
		return true;
	}

	if (isMoved)
	{
//        Point cardP = card->getPosition();
        auto srcCardRect = card->getBoundingBox();
        auto newWidth = srcCardRect.size.width*CardBoxScale;
        auto newHeight = srcCardRect.size.height*CardBoxScale;
        // 放大 box
        auto subx = (newWidth-srcCardRect.size.width) / 2.f;
        auto suby = (newHeight-srcCardRect.size.height) / 2.f;
        srcCardRect.origin.x -= subx;
        srcCardRect.origin.y -= suby;
        srcCardRect.size.width = newWidth;
        srcCardRect.size.height = newHeight;
        
        // 绘制debugnode
//        auto debugNode = Director::getInstance()->getRunningScene()->getChildByTag(100000010);
//        if (debugNode == nullptr) {
//            auto colorLayer = LayerColor::create(Color4B::RED, srcCardRect.size.width, srcCardRect.size.height);
//            Director::getInstance()->getRunningScene()->addChild(colorLayer, 100, 100000010);
//            debugNode = (Node*)colorLayer;
//        }
//        auto worldPos = card->getParent()->convertToWorldSpace(srcCardRect.origin);
//        debugNode->setPosition(worldPos);
		//判断当前位置是否为新的位置
		for (int col = 0; col < 4; col++)
		{
			Rect cardRect;
			auto cardNum = aCardVector[col].size();
			
			if (cardNum > 0)
			{
				auto lastCard = aCardVector[col].at(cardNum - 1);
				if (lastCard->checkAPos(card))
				{
					cardRect = lastCard->getCenterBox();
				}
				else
				{
					continue;
				}
			}
			else
			{
				if (card->getNumber() == 1)
				{
					//找到位置
					cardRect = getEmptyCardRect(CARD_POS_A, col);
				}
				else
				{
					continue;
				}

			}

			if (cardRect.intersectsRect(srcCardRect))
			{
                if (cardPosId == CARD_POS_WAIT_SHOW) {// 如果是开牌区
                    cardCol = waitShowCardVector.size()-1;
                }
				//归到这个位置
				pushMoveData(MoveData::createMoveDataByMove(cardPosId, CARD_POS_A, cardCol, col));
				moveCardToNowPos(card, CARD_POS_A, col);
				SCENE_M->addMoveNum();
				if (cardPosId != CARD_POS_A)
				{
                    updateScore(card, 10);
				}
				return true;
			}
			
		}

		for (int col = 0; col < 7; col++)
		{
			Rect cardRect;
			int cardNum = kCardVector[col].size();
			if (cardNum > 0)
			{
				auto lastCard = kCardVector[col].at(cardNum - 1);
				if (lastCard->checkKPos(card))
				{
					cardRect = lastCard->getCenterBox();
				}
				else
				{
					continue;
				}
			}
			else
			{
				if (card->getNumber() == 13)
				{
					//找到位置
					cardRect = getEmptyCardRect(CARD_POS_K, col);
				}
				else
				{
					continue;
				}

			}

			if (cardRect.intersectsRect(srcCardRect))
			{
				//归到这个位置
				if (cardPosId == CARD_POS_K)
				{
					int cardIndex = card->getCLocalZOrder() - 1 - TotalWatiCardNum;
					int num = kCardVector[cardCol].size() - cardIndex;
					pushMoveData(MoveData::createMoveDataByMove(cardPosId, CARD_POS_K, cardCol, col, num));
					for (int i = 0; i < num; i++)
					{
						auto dealCard = kCardVector[cardCol].at(cardIndex);
						//找到K位置
						moveCardToNowPos(dealCard, CARD_POS_K, col);
					}
				}
				else
				{
					pushMoveData(MoveData::createMoveDataByMove(cardPosId, CARD_POS_K, cardCol, col));
					moveCardToNowPos(card, CARD_POS_K, col);
				}

				if (cardPosId == CARD_POS_WAIT_SHOW)
				{
					updateScore(card, 5);
				}
				else if (cardPosId == CARD_POS_A)
				{
					updateScore(card, -10);
				}

				SCENE_M->addMoveNum();
				return true;
			}
		}

		//归位
		if (cardPosId == CARD_POS_A)
		{
			card->moveToPos(getACardPosByIndex(card->getColNum()), 0, true);
		}
		else if (cardPosId == CARD_POS_K)
		{
			//card->moveToPos(getKCardPosByIndexAndCardVector(card->getColNum(), kCardVector[card->getColNum()].size() - 1));
			//移动整个序列
			for (int i = card->getCLocalZOrder() - 1 - TotalWatiCardNum; i < kCardVector[card->getColNum()].size(); i++)
			{
				auto dealCard = kCardVector[card->getColNum()].at(i);
				dealCard->moveToPos(getKCardPosByIndexAndCardVector(card->getColNum(), i), 0, true);
			}
		}
		else if (cardPosId == CARD_POS_WAIT_SHOW)
		{
//            auto indexPos = (int)waitShowCardVector.size();
//            if (indexPos >= 3)
//            {
//                indexPos = 3;
//            }
            card->moveToPos(getWaitShowCardPosByIndex(2), 0, true);
		}

        SOUND_M->playEffectMusic(EffectMovePoker0);
	}
	else
	{
		//自动寻找合适的位置置换
		autoFindCardPos(card);
	}
    return false;
}

void SpriteManager::autoFindCardPos(CardSprite * card)
{
    //翻牌有效用 记录选中牌
    tempMoveCard = card;
	//寻找顺序 A[0.1.2.3] -> K[0.1.2.3.4.5.6]
	int cardPosId = card->getPosId();
	int cardCol = card->getColNum();
	//K位置的只有最后一张才要检测是否进入到A
	if (cardPosId == CARD_POS_A || cardPosId == CARD_POS_WAIT_SHOW || (cardPosId == CARD_POS_K && kCardVector[cardCol].back() == card))
	{
		int aCardCol = checkACardPos(card);
		if (aCardCol != -1)
		{//收牌
            if (cardPosId == CARD_POS_WAIT_SHOW) {// 如果是开牌区
                cardCol = waitShowCardVector.size()-1;
            }
			pushMoveData(MoveData::createMoveDataByMove(cardPosId, CARD_POS_A, cardCol, aCardCol));
			//找到A位置
			moveCardToNowPos(card, CARD_POS_A, aCardCol);
			SCENE_M->addMoveNum();
			if (cardPosId != CARD_POS_A)
			{
				updateScore(card, 10);
			}
            CCLOG("socre id %s", StringUtils::format(EffectScore.c_str(), currentMusicLevel).c_str());
            //SOUND_M->playEffectMusic(StringUtils::format(EffectScore.c_str(), currentMusicLevel).c_str());
            SOUND_M->playEffectMusic(EffectMovePoker0);
            ++currentMusicLevel;
            currentMusicLevel = MIN(currentMusicLevel, 10);
            resetCombo();
			return;
		}
	}

	int kCardCol = checkKCardPos(card);
	if (kCardCol != -1)
	{
		if (cardPosId == CARD_POS_K)
		{
			int cardIndex = card->getCLocalZOrder() - 1 - TotalWatiCardNum;
			int num = kCardVector[cardCol].size() - cardIndex;
			pushMoveData(MoveData::createMoveDataByMove(cardPosId, CARD_POS_K, cardCol, kCardCol, num));
			for (int i = 0; i < num;i++)
			{
				auto dealCard = kCardVector[cardCol].at(cardIndex);
				//找到K位置
				moveCardToNowPos(dealCard, CARD_POS_K, kCardCol,i*DRIFT_DELAY_TIME);
				//dealCard->setCardLocalZOrder(dealCard->getCLocalZOrder());
			}
		}
		else
		{
			pushMoveData(MoveData::createMoveDataByMove(cardPosId, CARD_POS_K, cardCol, kCardCol));
			moveCardToNowPos(card, CARD_POS_K, kCardCol);
			//card->setCardLocalZOrder(card->getCLocalZOrder());
		}

		if (cardPosId == CARD_POS_WAIT_SHOW)
		{
			updateScore(card, 5);
		}
		else if (cardPosId == CARD_POS_A)
		{
			updateScore(card, -10);
		}
		SOUND_M->playEffectMusic(EffectMovePoker0);
		SCENE_M->addMoveNum();
	}
	else
	{
		if (cardPosId == CARD_POS_K)
		{
			for (int i = 0; i < kCardVector[cardCol].size(); i++)
			{
				auto dealCard = kCardVector[cardCol].at(i);
				dealCard->setCardLocalZOrder(dealCard->getCLocalZOrder());
			}
		}

		//找不到匹配的操作
		card->playUnDealAction();
		card->setCardLocalZOrder(card->getCLocalZOrder());
		SOUND_M->playEffectMusic(EffectNoMoreMove);
        addNoCombo();
	}
	
}

int SpriteManager::checkACardPos(CardSprite * card)
{
	int indexA = 4;
	if (card->getPosId() == CARD_POS_A)
	{
		indexA = card->getColNum() + 1;
	}
	for (int i = 0; i < indexA; i++)
	{
		if (aCardVector[i].size() == 0)
		{
			//找到位置
			if (card->getNumber() == 1)
			{
				return i;
			}
		}
		else
		{
			auto lastCard = aCardVector[i].back();
			if (lastCard && lastCard->checkAPos(card))
			{
				//可以归到这个位置
				return i;
			}
		}

	}

	return -1;
}

int SpriteManager::checkKCardPos(CardSprite * card)
{
	for (int i = 0; i < 7; i++)
	{
		if (kCardVector[i].size() == 0)
		{
			//找到位置
			if (card->getNumber() == 13)
			{
				return i;
			}
		}
		else
		{
			auto lastCard = kCardVector[i].back();
			if (lastCard && lastCard->checkKPos(card))
			{
				//可以归到这个位置
				return i;
			}
		}
	}

	return -1;
}

enum class MoveT {
    Top = 1,
    Stack = 2,
    Collector = 3,
    Producer = 4
};

static int AutoPlayIDX = 0;
static rapidjson::Document doc;
void SpriteManager::autoPlay(const std::string& autoData)
{
    CCLOG("AutoPlay: %s", autoData.c_str());
    doc.Parse(autoData.c_str());
    if (doc.HasParseError()) {
        //解析出错
        CCASSERT(true, "解析出现错误");
        return;
    }
    
    if (doc.HasMember("moves") && doc["moves"].IsArray()) {
        AutoPlayIDX = 0;
        std::function<void(float)> goNext;
        goNext = [this, &goNext](float) {
            if (AutoPlayIDX<doc["moves"].GetArray().Size()) {
                const auto &step = doc["moves"].GetArray()[AutoPlayIDX].GetObject();
                auto fromType = MoveT(step["ft"].GetInt());
                auto toType = MoveT(step["tt"].GetInt());
                if (step.HasMember("poker")){
                    string cardInfo = step["poker"].GetString();
                    CCLOG("cardInfo:%s",cardInfo.c_str());
                }
                vector<string> elements;
                UIUtils::split(step["fi"].GetString(), '_', elements);
                vector<string> elements1;
                UIUtils::split(step["ti"].GetString(), '_', elements1);
                switch (fromType) {
                    case MoveT::Stack: {
                        auto idx = UIUtils::stoii(elements[1]), idx1 = UIUtils::stoii(elements[0])-1;
                        auto sliceSize = kCardVector[idx1].size();
                        Vector<CardSprite *> needMove;
                        for (auto i=idx;i<sliceSize;++i) {
                            needMove.pushBack(kCardVector[idx1].at(i));
                        }
                        for (auto cardSprite: needMove) {
                            cardSprite->openCard();
                            moveCardToNowPos(cardSprite, toType==MoveT::Stack?CARD_POS_K:CARD_POS_A, UIUtils::stoii(elements1[0])-1);
                        }
                        
                        break;
                    }
                    case MoveT::Collector:{
                        auto idx = UIUtils::stoii(elements[1]);
                        CardSprite *cardSprite = nullptr;
                        if (idx == 1 && waitShowCardVector.size()>0) {
                            cardSprite = waitShowCardVector.front();
                        }
                        else {
                            cardSprite = waitCardVector.at(waitCardVector.size()-idx+waitShowCardVector.size());
                        }
                        cardSprite->openCard();
                        moveCardToNowPos(cardSprite, toType==MoveT::Stack?CARD_POS_K:CARD_POS_A, UIUtils::stoii(elements1[0])-1);
                        break;
                    }
                    default:
                        break;
                }
            };
            ++AutoPlayIDX;
        };
        SCENE_M->getGameView()->schedule(goNext, 0.5, AutoFinishKey);
    }
}

void SpriteManager::moveCardToNowPos(CardSprite * cardSprite, int endPosId, int colNum,float delayTime)
{
	int posId = cardSprite->getPosId();
	int cardColNum = cardSprite->getColNum();
	if (posId == endPosId && cardColNum == colNum)
	{
		return;
	}

	Point targetPos;
	int localZOrder = 0;
	bool isMove = true;
	switch (endPosId)
	{
	case CARD_POS_A:
		localZOrder = aCardVector[colNum].size() + 1;

		aCardVector[colNum].pushBack(cardSprite);
		//播放特效
		playACardAction(colNum, cardSprite->getColorType());
		targetPos = getACardPosByIndex(colNum);
		break;
	case CARD_POS_K:
		localZOrder = kCardVector[colNum].size() + 1 + TotalWatiCardNum;
		kCardVector[colNum].pushBack(cardSprite);
		targetPos = getKCardPosByIndexAndCardVector(colNum, kCardVector[colNum].size() - 1);
		break;
	case CARD_POS_WAIT_SHOW:
        localZOrder = (int)waitShowCardVector.size()+1; //TotalWatiCardNum-(int)waitCardVector.size();
		waitShowCardVector.pushBack(cardSprite);
		isMove = false;
        cardSprite->setPosId(endPosId);//改动
		addjustWaitShowCard();
		break;
	case CARD_POS_WAIT:
		localZOrder = (int)waitCardVector.size();
		waitCardVector.pushBack(cardSprite);
		SCENE_M->updateWaitCardNum(waitCardVector.size());
		targetPos = getWaitCardPos(localZOrder);
		break;
	default:
		break;
	}

	setShaderStatus(posId, cardColNum);
	setShaderStatus(endPosId, colNum);

	if (posId == CARD_POS_A)
	{
		//移动到新的位置
		aCardVector[cardColNum].eraseObject(cardSprite);
		
	}
	else if (posId == CARD_POS_K)
	{
		//移动到新的位置
		kCardVector[cardColNum].eraseObject(cardSprite);

		if (kCardVector[cardColNum].size() > 0 && !kCardVector[cardColNum].at(kCardVector[cardColNum].size() - 1)->getIsOpen())
		{
            cardSprite->setHasFlop(false);
			//如果这张牌的上一张没开
			auto card = openKCardByCol(cardColNum,cardSprite);
			updateScore(card, 5);
			pushMoveData(MoveData::createMoveDataByOpen(cardColNum));
		}
	}
	else if (posId == CARD_POS_WAIT_SHOW)
	{
		waitShowCardVector.eraseObject(cardSprite);
		addjustWaitShowCard();
    }
    else if (posId == CARD_POS_WAIT)
    {
        if(!cardSprite->getIsOpen())
        {
            cardSprite->openCard();
        }
        waitCardVector.eraseObject(cardSprite);
        addjustWaitShowCard();
    }
    
    if (endPosId != CARD_POS_WAIT) {
        cardSprite->setCardLocalZOrder(localZOrder);
//    if (endPosId == CARD_POS_A || endPosId == CARD_POS_K)
        cardSprite->setLocalZOrder(MaxTopOrder);//将它置顶
    }
	cardSprite->setColNum(colNum);
	cardSprite->setPosId(endPosId);
	if (isMove)
	{
		cardSprite->moveToPos(targetPos,delayTime);
	}

	if (endPosId == CARD_POS_A)
	{
		//检测游戏是否成功
		bool isWin = true;
		for (int col = 0; col < 4; col++)
		{
			if (aCardVector[col].size() < 13)
			{
				isWin = false;
				break;
			}
		}
		if (isWin)
		{
			//先播放动画
            auto is = DATA_M->getGuangGao();
            if(is)
            {
                auto de = DelayTime::create(0.5);
                auto func = CallFunc::create([this](){
                    SCENE_M->gameOver(true);
                });
                auto re = RemoveSelf::create();
                auto seq = Sequence::create(de,func,re, NULL);
                auto node = Node::create();
                panel_game->addChild(node);
                node->runAction(seq);
            }
            else
            {
                SCENE_M->gameOver(true);
            }
			
		}
	}

	auto cardFirstMove = GETBOOL("game_ai_cardmove", false);
	if (!cardFirstMove) {
        SETBOOL("game_ai_cardmove", true);
        auto deltaSec = DataManager::getContentSec() - DataManager::GAME_START_TS;
        ValueMap valueMap{
            {"ts", Value(toString(deltaSec))}
        };
        UIUtils::FIRAnalyticsEvent("cardFirstMove", valueMap);
        UIUtils::FIRFirestoreAddOP("cardFirstMove", toString(deltaSec));
	}
#if DEBUG_BACKMOVE
    int c = cardSprite->getColorType();
    int num = cardSprite->getNumber();
    printPokers(StringUtils::format("MOVE poker(%s%d) src:%s-%d dst:%s-%d", ColorStr[c].c_str(), num, PosStr[posId].c_str(), cardColNum,  PosStr[endPosId].c_str(), colNum));
#endif
}

void SpriteManager::setKCardLocalZOrder(CardSprite * card)
{
	if (card->getPosId() == CARD_POS_K)
	{
		for (int i = card->getCLocalZOrder() - 1 - TotalWatiCardNum; i < kCardVector[card->getColNum()].size(); i++)
		{
			auto dealCard = kCardVector[card->getColNum()].at(i);
			//找到K位置
			dealCard->setLocalZOrder(MaxTopOrder + i);
		}
	}
	else
	{
		card->setLocalZOrder(MaxTopOrder);
	}
}


//牌的位置获取 初始位置
Point SpriteManager::getACardPosByIndex(int index)
{
	Point point = Point(57 + 77 * index, 880);
//    if (DATA_M->getIsLeftModel())
//    {
//        point.x = 576 - point.x;
//    }
	return aSprite[index]->getPosition();
}

Point SpriteManager::getKCardPosByIndex(int index,int row)
{
	Point point = Point(57 + 77 * index, 720 - row * 20);
//    if (DATA_M->getIsLeftModel())
//    {
//        point.x = 576 - point.x;
//    }
	return kSprite[index]->getPosition() - Vec2(0, row * OffsetNoOpen);
}

Point SpriteManager::getKCardPosByIndexAndCardVector(int index, int row)
{
	float delayY = 0;
	for (int i = 0; i < row;i++)
	{
		auto card = kCardVector[index].at(i);
		if (card)
		{
			if (card->getIsTempOpen())
			{
				delayY += OffsetOpen;
			}
			else
			{
				delayY += OffsetNoOpen;
			}
		}
	}

//    Point point = Point(57 + 77 * index, delayY);
//    if (DATA_M->getIsLeftModel())
//    {
//        point.x = 576 - point.x;
//    }

	return kSprite[index]->getPosition() - Vec2(0, delayY);
}

Point SpriteManager::getWaitCardPos(int index)
{
//    Point point = Point(57 + 77 * 6, 880); 
//    if (DATA_M->getIsLeftModel())
//    {
//        point.x = 576 - point.x;
//    }
    auto offset = WaitPokerOffset[UIUtils::clamp(index, 0, 7)];
	return waitSprite->getPosition() + Vec2(offset.x, offset.y);
}

Point SpriteManager::getWaitShowCardPosByIndex(int index)
{
//    Point point = Point(57 + 77 * 4 + 10 + index * 30, 880 - index * 0);
    if (DATA_M->getIsLeftModel()) {
        return Node_waitOpenThree->getPosition()+Vec2(index*OffsetWait, 0);
    }
    else {
        return Node_waitOpen->getPosition()+Vec2(index*OffsetWait, 0);
    }
}

void SpriteManager::pushMoveData(MoveData * moveData)
{
	moveDatas.pushBack(moveData);
}

MOVE_TYPE SpriteManager::backMove()
{
    resetCombo(true);
	if (moveDatas.size() <= 0)
	{
		return MType_None;
	}
	auto moveData = moveDatas.at(moveDatas.size() - 1);

	moveCardByMoveData(moveData);
	moveDatas.eraseObject(moveData);
	auto moveType = moveData->m_moveType;
	if (moveType == MType_Open)
	{
		backMove();
	}
	else
	{
		SCENE_M->addMoveNum();
		SCENE_M->updateScore(-2);
	}
	return moveType;
}

void SpriteManager::moveCardByMoveData(MoveData * moveData)
{
    if (isThreeModel && (moveData->m_moveType == MType_Move_W_A
        || moveData->m_moveType == MType_Move_W_K)) { // 回到wait
        auto beginCol = moveData->beginCol;
        auto wsCNT = waitShowCardVector.size();
        if (wsCNT < beginCol) {
            size_t lessCardCNT = beginCol - wsCNT;
            for (size_t i=0; i<lessCardCNT; i++) {
                auto lastCard = waitCardVector.back();
                if (lastCard) {
                    moveCardToNowPos(lastCard, CARD_POS_WAIT_SHOW, moveData->beginCol);
                }
            }
        }
    }
	if (moveData->m_moveType == MType_Open)
	{
		//开牌
		auto card = kCardVector[moveData->beginCol].at(kCardVector[moveData->beginCol].size() - 1);
		card->closeCardWithAction();
		SCENE_M->showAutoFinishBtn(false);
        updateScore(card, -5);

	}
	else if (moveData->m_moveType == MType_Move_A_A || moveData->m_moveType == MType_Move_K_A || moveData->m_moveType == MType_Move_W_A)
	{
		//A位置
		auto card = aCardVector[moveData->endCol].at(aCardVector[moveData->endCol].size() - 1);
		moveCardToNowPos(card, moveData->beginPosId, moveData->beginCol);

        updateScore(card, -10);
	}
	else if (moveData->m_moveType == MType_Move_A_K || moveData->m_moveType == MType_Move_K_K || moveData->m_moveType == MType_Move_W_K)
	{
		//K位置
		int cardIndex = kCardVector[moveData->endCol].size() - moveData->moveNum;
		auto card = kCardVector[moveData->endCol].at(cardIndex);
		for (int i = 0; i < moveData->moveNum; i++)
		{
			auto dealCard = kCardVector[moveData->endCol].at(cardIndex);
			//找到K位置
			moveCardToNowPos(dealCard, moveData->beginPosId, moveData->beginCol, i*DRIFT_DELAY_TIME);
		}

		if (moveData->m_moveType == MType_Move_A_K)
		{
			updateScore(card, 15);
		}
		else if (moveData->m_moveType == MType_Move_W_K)
		{
			updateScore(card, -5);
		}

	}
	else if (moveData->m_moveType == MType_Shuffle)
	{
		if (isThreeModel)
		{
            auto moveNum = moveData->moveNum;
            auto offset = waitShowCardVector.size()-moveNum;
            auto totalShowCNT = offset;
            if (totalShowCNT <= 0) {
                totalShowCNT = waitShowCardVector.size()%3;
                totalShowCNT = totalShowCNT==0?3:totalShowCNT;
            }
			for (int i = 0; i < MIN(3,totalShowCNT); i++)
			{
				auto card = waitShowCardVector.at(waitShowCardVector.size() - 1);
                if (card) {
                    card->closeCardWithAction(i*ThreeFlopSpaceTime);
                    moveCardToNowPos(card, CARD_POS_WAIT, moveData->beginCol, i*ThreeFlopSpaceTime);
                }
				SCENE_M->showAutoFinishBtn(false);
                card->removeLevelTips();
			}
		}
		else
		{
			auto card = waitShowCardVector.at(waitShowCardVector.size() - 1);
            card->closeCardWithAction(0, [this](){
                if (waitCardVector.size() > 1) {
                    auto i = int(waitCardVector.size() - 2);
                    auto cardDown = waitCardVector.at(i);
                    cardDown->getShaderS()->setColor(WaitPokerColor[UIUtils::clamp(i, 0, 8)]);
                }
            });
			moveCardToNowPos(card, CARD_POS_WAIT, moveData->beginCol);
			SCENE_M->showAutoFinishBtn(false);
            card->removeLevelTips();
		}
	
	}
	else if (moveData->m_moveType == MType_Reset)
	{
        
		int waitNum = waitCardVector.size();
        auto startIDX = waitNum-3;
		for (int i = 0; i < waitNum; i++)
		{
			auto cardSprite = waitCardVector.at(waitCardVector.size() - 1);
			cardSprite->openCardToPos(getWaitShowCardPosByIndex(MAX(0, i-startIDX)), i*WaitCardRestTime+0.01);

			cardSprite->setCardLocalZOrder(waitNum-i);
//            cardSprite->setLocalZOrder(100);//将它置顶
			cardSprite->setPosId(CARD_POS_WAIT_SHOW);
			waitShowCardVector.pushBack(cardSprite);
			waitCardVector.eraseObject(cardSprite);
		}
        auto totalWaitCardCNT = getTotalWaitCardCNT();
        if (totalWaitCardCNT>8) {
            SOUND_M->playEffectMusic(EffectCover);
        }
        else if (totalWaitCardCNT>3) {
            SOUND_M->playEffectMusic(EffectCover1);
        }
        else if (getTotalWaitCardCNT()>0) {
            SOUND_M->playEffectMusic(EffectCover2);
        }
		SCENE_M->updateWaitCardNum(waitCardVector.size());
//        addjustWaitShowCard();
	}
//    printPokers("BACK");
    CCLOG("PPOKERS ================[BACK]===============");
}

Rect SpriteManager::getEmptyCardRect(int posId, int col)
{
	Rect boxRect;
	Point centerP;
	if (posId == CARD_POS_A)
	{
		boxRect = aSprite[col]->getBoundingBox();
		centerP = aSprite[col]->getPosition();
	}
	else if (posId == CARD_POS_K)
	{
		boxRect = kSprite[col]->getBoundingBox();
		centerP = kSprite[col]->getPosition();
	}
	return boxRect;
	//return Rect((centerP.x + boxRect.getMinX()) / 2, (centerP.y - boxRect.getMinY()) / 4 + boxRect.getMinY(), boxRect.size.width / 2, boxRect.size.height * 3 / 4);
}

//提示的话 这一步操作要有效果 跑到A位置 或者下一步可以跑到A位置 K位置最后一张 掀牌 或者 等待区连到K位置 A->K下一步有一张牌可以接上去 
//提示的效果要产生正向的  K->K（开牌 置空 下一步收牌） W->A k->A收牌 W->K(连到K) A->K(下一步置空 开牌)
float SpriteManager::getTips()
{
	clearTipsData();
	for (int col = 0; col < 7; col++)
	{
        auto kCardSize = kCardVector[col].size();
        auto firstOpen = true;
		//K位置判断
		for (int i = 0; i < kCardSize;i++)
		{
			auto card = kCardVector[col].at(i);
			if (card->getIsOpen())
			{
				//直接判断是否能到A位置 能就直接结束
				if (i == kCardVector[col].size() - 1)
				{
					int aCardCol = checkACardPos(card);
					if (aCardCol != -1)
					{
						tipsMoveDatas.insert(0, MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_A, card->getColNum(), aCardCol));
						break;
					}
				}
				
                if (firstOpen) {
                    //判断是否可以接到其他K位置
                    int kCardCol = checkKCardPos(card);
                    if (kCardCol != -1)
                    {
                        if (kCardVector[kCardCol].size() == 0 && i == 0)
                        {
                            
                        }
                        else
                        {
                            //可以
                            tipsMoveDatas.pushBack(MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_K, card->getColNum(), kCardCol, kCardVector[col].size() - i));
                            break;
                        }
                    }
                }
                firstOpen = false;
			}
		}
	}
	
	if (waitShowCardVector.size() > 0)
	{
		auto card = waitShowCardVector.at(waitShowCardVector.size() - 1);
		int aCardCol = checkACardPos(card);
		if (aCardCol != -1)
		{
			tipsMoveDatas.insert(0, MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_A, card->getColNum(), aCardCol));
		}
		else
		{
			//判断是否可以接到其他K位置
			int kCardCol = checkKCardPos(card);
			if (kCardCol != -1)
			{
				tipsMoveDatas.pushBack(MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_K, card->getColNum(), kCardCol));
			}
		}
	}

	//K(最后一张牌) ->K
//	for (int col = 0; col < 7; col++)
//	{
//		int kCardNum = kCardVector[col].size();
//		//K位置判断
//		if (kCardNum >= 2)
//		{
//			auto card_1 = kCardVector[col].at(kCardNum - 1);
//			auto card_2 = kCardVector[col].at(kCardNum - 2);
//
//			if (card_2->getIsOpen())
//			{
//				int checkACol = checkACardPos(card_2);
//				int checkKCol = checkKCardPos(card_1);
//				if (checkACol != -1 && checkKCol != -1)
//				{
//					tipsMoveDatas.pushBack(MoveData::createMoveDataByMove(card_1->getPosId(), CARD_POS_K, card_1->getColNum(), checkKCol));
//				}
//			}
//		}
//	}
    for (int col = 0; col < 7; col++)
    {
        int kCardNum = (int)kCardVector[col].size();
        for(int i = 0;i < kCardNum;++i)
        {
            auto card_1 = kCardVector[col].at(i);
            //找到翻开的牌
            if (card_1->getIsOpen())
            {
                //看看这张牌能放到A区域不
                int checkACol = checkACardPos(card_1);
                
                
                if(checkACol != -1)
                {
                    if(i + 1 < kCardNum)
                    {
                        auto card_2 = kCardVector[col].at(i + 1);
                        //看看压在card_1上的牌能移动开不
                        auto checkKCol = checkKCardPos(card_2);
                        if(checkKCol != -1)
                        {
                            tipsMoveDatas.pushBack(MoveData::createMoveDataByMove(card_2->getPosId(), CARD_POS_K, card_2->getColNum(), checkKCol,kCardVector[col].size() - i - 1));
                        }
                    }
                }
            }
        }
    }

	for (int col = 0; col < 4; col++)
	{
		if (aCardVector[col].size() > 0)
		{
			auto card = aCardVector[col].at(aCardVector[col].size() - 1);
			int kCardCol = checkKCardPos(card);
			if (kCardCol != -1)
			{
				bool isCanMove = false;
				for (int colK = 0; colK < 7; colK++)
				{
					int kCardNum = kCardVector[colK].size();

					//K位置判断
					if (kCardNum > 0)
					{
						//置空
						auto kCard = kCardVector[colK].at(kCardNum - 1);
						if (card->checkKPos(kCard))
						{
							if (kCardNum > 1)
							{
								auto cardK = kCardVector[colK].at(kCardNum - 2);
								if (!cardK->getIsOpen())
								{
									//翻牌
									isCanMove = true;
									break;
								}
								else
								{
									break;
								}
							}
							isCanMove = true;
							break;
						}
						
					}
				}
				if (isCanMove)
				{
					tipsMoveDatas.pushBack(MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_K, card->getColNum(), kCardCol));
				}
			}
		}
	}
    
	if (tipsMoveDatas.size() == 0)
	{
		auto waitCardCanMoveFlag = false;
        if (isThreeModel)
        {   // 三张牌检测
            int i = 0;
            for (auto it = waitCardVector.rbegin(); it != waitCardVector.rend(); ++it) {
                if ((i+1)%3 == 0 || (i==waitCardVector.size()-1)) {
                    auto card = *it;
                    if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                        waitCardCanMoveFlag = true;
                        break;
                    }
                }
                ++i;
            }
            // 检测所有
            auto endIndex = 0;
            if (!waitCardCanMoveFlag) {
                for (int i=2; i<waitShowCardVector.size(); i+=3) {
                    auto card = waitShowCardVector.at(i);
                    if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                        waitCardCanMoveFlag = true;
                        break;
                    }
                    endIndex = i;
                }
            }
            if (!waitCardCanMoveFlag) {
                int start = (int)MAX(0, 3-waitShowCardVector.size()-endIndex);
                if (waitCardVector.size()>=start) {
                    int i = 0;
                    for (auto it = waitCardVector.rbegin()+start; it != waitCardVector.rend(); ++it) {
                        if ((i+1)%3 == 0 || (i==waitCardVector.size()-1)) {
                            auto card = *it;
                            if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                                waitCardCanMoveFlag = true;
                                break;
                            }
                        }
                        ++i;
                    }
                }
            }
        }
        else { //单张牌模式直接检测所有卡牌
            for (auto card:waitCardVector) {
                if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                    waitCardCanMoveFlag = true;
                    break;
                }
            }
            if (!waitCardCanMoveFlag) {
                for (auto card:waitShowCardVector) {
                    if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                        waitCardCanMoveFlag = true;
                        break;
                    }
                }
            }
        }
        //没有可以直接操作的步骤 就提示开牌或者重置 维加斯模式场上无牌可走并且翻牌次数用尽
        auto isFanPai = SCENE_M->getGameView()->getIsFanPai();
		// 无有效移动
		if (!waitCardCanMoveFlag||!isFanPai) {
            //SCENE_M->showTips(Lang("100134"));
            return 0;
		}

		if (waitCardVector.size() > 0)
		{
            isTipsFanPai = true;
			tipsMoveDatas.pushBack(MoveData::createMoveDataByShuffle());
		}
		else if (waitShowCardVector.size() > 0)
		{
            isTipsFanPai = true;
			tipsMoveDatas.pushBack(MoveData::createMoveDataByReset());
		}
	}
	else {
		noMoreMoveMark = -1;
        isTipsFanPai = false;
	}
    
	//执行动画
	int tipsNum = tipsMoveDatas.size();
	
	tipsNum = tipsNum > 3 ? 3 : tipsNum;
	if (tipsNum > 0)
	{
		tipsLayer->stopAllActions();
		tipsLayer->setVisible(true);
        auto tipsTextNode = SCENE_M->getGameView()->getTipsTextNode();
        if(tipsTextNode)tipsTextNode->setVisible(true);
	}
	showNextTips();
	return tipsNum * TIPS_ACTION_TOTALTIME + 0.1;
}

void SpriteManager::cancleTips()
{
	tipsLayer->stopAllActions();
	tipsLayer->setVisible(false);
    clearTipsData();

    resetTipsCard();
}

void SpriteManager::resetTipsCard() {
    //归位
    for (int col = 0; col < 4;col++)
    {
        int num = aCardVector[col].size();
        for (int i = 0; i < num;i++)
        {
            auto card = aCardVector[col].at(i);
            if (card)
            {
                card->setPosition(getACardPosByIndex(card->getColNum()));
                card->stopCarTipsAction();
            }
        }
    }
    
    for (int col = 0; col < 7; col++)
    {
        int num = kCardVector[col].size();
        for (int i = 0; i < num; i++)
        {
            auto card = kCardVector[col].at(i);
            if (card)
            {
                card->setPosition(getKCardPosByIndexAndCardVector(card->getColNum(), i));
                card->stopCarTipsAction();
            }
        }
    }
    
    for (int i = 0; i < waitCardVector.size(); i++)
    {
        auto card = waitCardVector.at(i);
        if (card)
        {
            card->setPosition(getWaitCardPos(i));
            card->stopCarTipsAction();
        }
    }
    
    for (int i = 0; i < waitShowCardVector.size(); i++)
    {
        auto card = waitShowCardVector.at(i);
        if (card)
        {
            card->stopCarTipsAction(true,false);
        }
    }
    addjustWaitShowCard();
}

void SpriteManager::showTipsByMoveData(MoveData * moveData)
{
	if (moveData->m_moveType == MType_Move_K_A)
	{
		//A位置
		if (kCardVector[moveData->beginCol].size() > 0)
		{
			auto card = kCardVector[moveData->beginCol].at(kCardVector[moveData->beginCol].size() - 1);
			card->setLocalZOrder(100);
			card->playTipsAction(getACardPosByIndex(moveData->endCol));
		}
	}
	else if (moveData->m_moveType == MType_Move_W_A)
	{
		if (waitShowCardVector.size() > 0)
		{
			auto card = waitShowCardVector.at(waitShowCardVector.size() - 1);
			card->setLocalZOrder(100);
			card->playTipsAction(getACardPosByIndex(moveData->endCol));
		}
	}
	else if (moveData->m_moveType == MType_Move_A_K)
	{
		if (aCardVector[moveData->beginCol].size() > 0)
		{
			auto card = aCardVector[moveData->beginCol].at(aCardVector[moveData->beginCol].size() - 1);
			card->setLocalZOrder(100);
			card->playTipsAction(getKCardPosByIndexAndCardVector(moveData->endCol, kCardVector[moveData->endCol].size()));
		}
	}
	else if (moveData->m_moveType == MType_Move_W_K)
	{
		if (waitShowCardVector.size() > 0)
		{
			auto card = waitShowCardVector.at(waitShowCardVector.size() - 1);
			card->setLocalZOrder(100);
			card->playTipsAction(getKCardPosByIndexAndCardVector(moveData->endCol, kCardVector[moveData->endCol].size()));
		}
	}
	else if(moveData->m_moveType == MType_Move_K_K)
	{
		//K位置
		int cardIndex = kCardVector[moveData->beginCol].size() - moveData->moveNum;
		for (int i = 0; i < moveData->moveNum; i++)
		{
			auto dealCard = kCardVector[moveData->beginCol].at(cardIndex + i);
			dealCard->setLocalZOrder(100);
			//找到K位置
			dealCard->playTipsAction(getKCardPosByIndexAndCardVector(moveData->endCol, kCardVector[moveData->endCol].size()) + Point(0,-OffsetOpen) * i, i);
		}

	}
	else if (moveData->m_moveType == MType_Shuffle)
	{
		if (isThreeModel)
		{
			for (int i = 0; i < 3; i++)
			{
				auto card = waitCardVector.at(waitCardVector.size() - 1);
				card->playTipsAction(getWaitShowCardPosByIndex(i), i);
				card->setLocalZOrder(100);
			}
		}
		else
		{
			auto card = waitCardVector.at(waitCardVector.size() - 1);
			card->playTipsAction(getWaitShowCardPosByIndex(2));
			card->setLocalZOrder(100);
		}

	}
	else if (moveData->m_moveType == MType_Reset)
	{
		int waitNum = waitShowCardVector.size();
		for (int i = 0; i < waitNum; i++)
		{
			auto cardSprite = waitShowCardVector.at(i);
			cardSprite->setLocalZOrder(100);
			cardSprite->playTipsAction(getWaitCardPos(0), i);
		}
	}
}

void SpriteManager::playACardAction(int col, int colorType)
{
	string picName = "";
	if (colorType == CARD_BLACK)
	{
		picName = "Card_Black.png";
	}
	else if (colorType == CARD_RED)
	{
		picName = "Card_Red.png";
	}
	else if (colorType == CARD_FLOWER)
	{
		picName = "Card_Flower.png";
	}
	else if (colorType == CARD_SQUARE)
	{
		picName = "Card_Square.png";
	}
    auto is = DATA_M->getGuangGao();
    float time = 0.1;
    if(is)
    {
        time = 0.45;
    }
    
	panel_game->runAction(Sequence::create(DelayTime::create(time), CallFunc::create([this, col, picName]{
		/*ParticleSystemQuad *particleSystem = ParticleSystemQuad::create(picName);
		particleSystem->setPosition(getACardPosByIndex(col));
		particleSystem->setAutoRemoveOnFinish(true);
		particleSystem->setLocalZOrder(101);
		panel_game->addChild(particleSystem, 100);*/

        auto tipsNode = panel_game->getChildByName<TipsNode*>(StringUtils::format("TipsNode_%d", col));
        if (tipsNode) {
            tipsNode->playAni("start0");
            if(DATA_M->getGuangGao())
            {
                auto Particle_2 = tipsNode->getNode<ParticleSystemQuad*>("Particle_2");
                Particle_2->setVisible(true);
                Particle_2->resetSystem();
            }
        }
        else
        {
            for (int i = 0; i < 10;i++)
            {
                auto sprite = Sprite::create(picName);
                sprite->setScale(POKER_ACTION_MOVE+0.1);
                sprite->setPosition(getACardPosByIndex(col));
                sprite->setLocalZOrder(101);
                panel_game->addChild(sprite, 100);
                float randomAngle = CCRANDOM_0_1() * M_PI * 2;
                sprite->runAction(Sequence::create(MoveBy::create(0.4, Point(cos(randomAngle), sin(randomAngle)) * 70), FadeOut::create(0.2), RemoveSelf::create(), NULL));
            }
        }
	}), NULL));
}

void SpriteManager::setLeftModel()
{
	for (int col = 0; col < 4; col++)
	{
		for (int i = 0; i< aCardVector[col].size(); i++)
		{
			auto card = aCardVector[col].at(i);
			if (card)
			{
				card->setPosition(getACardPosByIndex(col));
			}
		}
	}

	for (int col = 0; col < 7; col++)
	{
		for (int i = 0; i< kCardVector[col].size(); i++)
		{
			auto card = kCardVector[col].at(i);
			if (card)
			{
				card->setPosition(getKCardPosByIndexAndCardVector(col, card->getCLocalZOrder() - 1 - TotalWatiCardNum));
			}
		}
	}

	for (int i = 0; i< waitCardVector.size(); i++)
	{
		auto card = waitCardVector.at(i);
		if (card)
		{
			card->setPosition(getWaitCardPos(i));
		}
	}
	for (int i = 0; i< waitShowCardVector.size(); i++)
	{
		auto card = waitShowCardVector.at(i);
		if (card)
		{
			card->setPosition(getWaitShowCardPosByIndex(0));
		}
	}
	for (int i = 0; i < 4; i++)
	{
		aSprite[i]->setPosition(SPRITE_M->getACardPosByIndex(i));
	}

	for (int i = 0; i < 7; i++)
	{
		kSprite[i]->setPosition(SPRITE_M->getKCardPosByIndex(i));
	}

	addjustWaitShowCard();
}

void SpriteManager::playWinAction()
{
	
}

void SpriteManager::autoFinshGame()
{
	float delayTime = 0;
    isAutoFinshGame = true;
	auto num = waitShowCardVector.size();
    
    num += waitCardVector.size();
	for (int col = 0; col < 7; col++)
	{
		num += kCardVector[col].size();
	}

    
	for (int i = 0; i < num;i++)
	{
		tipsLayer->runAction(Sequence::create(DelayTime::create(delayTime), CallFunc::create([this, i, num]{
			autoFindOneCardToA();
			if (i == num-1) {
				CCLOG("Auto FinishDone!!");
			}
		}), NULL));
		delayTime += 0.07;
	}
}

void SpriteManager::autoFindOneCardToA()
{
	for (int col = 0; col < 7; col++)
	{
		if (kCardVector[col].size() > 0)
		{
			auto card = kCardVector[col].at(kCardVector[col].size() - 1);
			int aCardCol = checkACardPos(card);
			if (aCardCol != -1)
			{
				int cardPosId = card->getPosId();
                SCENE_M->addMoveNum();
				moveCardToNowPos(card, CARD_POS_A, aCardCol);
				if (cardPosId != CARD_POS_A)
				{
					updateScore(card, 10);
				}
				return;
			}
		}
	}
    
    for (int i = 0; i < waitCardVector.size(); i++)
    {

        auto card = waitCardVector.at(i);
        int aCardCol = checkACardPos(card);
        if (aCardCol != -1)
        {
            //找到A位置
            int cardPosId = card->getPosId();
            SCENE_M->addMoveNum();
            card->getShaderS()->setColor(Color3B::WHITE);
            moveCardToNowPos(card, CARD_POS_A, aCardCol);
            if (cardPosId != CARD_POS_A)
            {
                updateScore(card, 10);
            }
            SCENE_M->updateWaitCardNum(waitCardVector.size());
            return;
        }
    }

	for (int i = 0; i < waitShowCardVector.size(); i++)
	{

		auto card = waitShowCardVector.at(i);
		int aCardCol = checkACardPos(card);
		if (aCardCol != -1)
		{
			//找到A位置
			int cardPosId = card->getPosId();
            SCENE_M->addMoveNum();
			moveCardToNowPos(card, CARD_POS_A, aCardCol);
			if (cardPosId != CARD_POS_A)
			{
				updateScore(card, 10);
			}
			SCENE_M->updateWaitCardNum(waitShowCardVector.size());
			return;
		}
	}
}

bool SpriteManager::checkIsAllOpen()
{
//	for (int col = 0; col < 4; col++)
//	{
//		for (int i = 0; i< aCardVector[col].size(); i++)
//		{
//			auto card = aCardVector[col].at(i);
//			if (card && !card->getIsOpen())
//			{
//				return false;
//			}
//		}
//	}
    //只需要判断k区域是否都翻开
	for (int col = 0; col < 7; col++)
	{
		for (int i = 0; i< kCardVector[col].size(); i++)
		{
			auto card = kCardVector[col].at(i);
			if (card && !card->getIsOpen())
			{
				return false;
			}
		}
	}

    //只要其他地方是开的就可以
//	for (int i = 0; i< waitCardVector.size(); i++)
//	{
//		auto card = waitCardVector.at(i);
//		if (card && !card->getIsOpen())
//		{
//			return false;
//		}
//	}
//	for (int i = 0; i< waitShowCardVector.size(); i++)
//	{
//		auto card = waitShowCardVector.at(i);
//		if (card && !card->getIsOpen())
//		{
//			return false;
//		}
//	}

	return true;
}

void SpriteManager::setShaderStatus(int posId, int colNum)
{

	if (posId == CARD_POS_A)
	{
		//尾部两张显示
		int aCardNum = aCardVector[colNum].size();
		for (int i = 0; i<aCardNum;i++)
		{
			auto cardA = aCardVector[colNum].at(i);
			if (cardA){
				if (aCardNum - 1 == i || aCardNum - 2 == i)
				{
					cardA->setShaderVisible(true);
				}
				else
				{
					cardA->setShaderVisible(false);
				}
			}
		}
	}
	else if (posId == CARD_POS_WAIT)
	{
		int waitCardNum = waitCardVector.size();
		//尾部一张显示
		for (int i = 0; i<waitCardNum; i++)
		{
			auto cardA = waitCardVector.at(i);
			if (cardA){
				if (waitCardNum - 1 == i)
				{
					cardA->setShaderVisible(true);
				}
				else
				{
					cardA->setShaderVisible(false);
				}
			}
		}
		
	}
	else if (posId == CARD_POS_WAIT_SHOW)
	{
		//尾部四张显示
		int waitShowCardNum = waitShowCardVector.size();
		for (int i = 0; i<waitShowCardNum; i++)
		{
			auto cardA = waitShowCardVector.at(i);
			if (cardA){
				if (waitShowCardNum - 1 == i || waitShowCardNum - 2 == i || waitShowCardNum - 3 == i || waitShowCardNum -4 == i)
				{
					cardA->setShaderVisible(true);
				}
				else
				{
					cardA->setShaderVisible(false);
				}
			}
		}
	}
	
}

int SpriteManager::getCurrentTipsIDX() const {
	return _currentTipsIDX;
}

void SpriteManager::setCurrentTipsIDX(int currentTipsIDX) {
	_currentTipsIDX = currentTipsIDX;
}

void SpriteManager::clearTipsData() {
	tipsMoveDatas.clear();
    _currentTipsIDX = 0;
}
void SpriteManager::clearMoveDatas()
{
    moveDatas.clear();
}

void SpriteManager::showNextTips() {
    if (tipsMoveDatas.size()>0) {
        auto tipsEndFunc = [this]() {
            tipsLayer->runAction(Sequence::create(FadeOut::create(TIPS_ACTION_FADEOUT), CallFunc::create([this]{
                tipsLayer->setVisible(false);
                tipsLayer->setOpacity(128);
                EVENT_M->sendEvent("msg_game_tips_end");
                //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_tips_end");
            }), NULL));
        };
		//最多三个提示
        if (_currentTipsIDX>=MIN(3, tipsMoveDatas.size())) {
            return tipsEndFunc();
        }
        
        resetTipsCard();
        auto tipsData = tipsMoveDatas.at(_currentTipsIDX);
        ++_currentTipsIDX;
        auto max = MIN(3, tipsMoveDatas.size());
        auto tipsTextNode = SCENE_M->getGameView()->getTipsTextNode();
        if(tipsTextNode)
        {//Text_tipsNum
            auto textTips = tipsTextNode->getChildByName<Text*>("Text_tipsNum");
            textTips->setString(isTipsFanPai?Lang("100182"):StringUtils::format(Lang("100181").c_str(),_currentTipsIDX,max));
        }
        auto action = Sequence::create(CallFunc::create([this, tipsData]{
            showTipsByMoveData(tipsData);
        }), DelayTime::create(TIPS_ACTION_TOTALTIME), CallFunc::create([this, tipsEndFunc](){
            if (_currentTipsIDX>=tipsMoveDatas.size()) {
                tipsEndFunc();
            }
            else
                showNextTips();
        }), NULL);
        tipsLayer->runAction(action);
        action->setTag(10086);
    }
}

void SpriteManager::updateScore(CardSprite *card, int score)
{
//    if (DATA_M->isLevelMode())
        card->setUserObject(__Integer::create(score));
    SCENE_M->updateScore(score);
}


vector<int> ColSum = {0, 1, 3, 6, 10, 15, 21, 28};
vector<int> ColTotal = {1, 2, 3, 4, 5, 6, 7};
Vec2 SpriteManager::getXYByPos(int pos) {
    Vec2 vec(0, 0);
    auto i = ColSum.size()-1;
    for (auto it=ColSum.rbegin(); it!=ColSum.rend();it++) {
        if (pos > *it) {
            vec.x = i+1;
            vec.y = (pos-*it)-1;
            break;
        }
        --i;
    }
    return vec;
}

void SpriteManager::resetCombo(bool flag) {
    noCombo = 0; // 重置combo
    if (flag)
        currentMusicLevel = 1;
}

void SpriteManager::addNoCombo() {
    if (++noCombo>5) {
        currentMusicLevel = 1;
    }
}

void SpriteManager::setCardSelected(CardSprite *card, bool select) {
    if (card->getPosId() == CARD_POS_K) {
        int index = card->getIndex()-1;
        auto &kcards = kCardVector[card->getColNum()];
        for (int i=index; i<kcards.size(); i++) {
            kcards.at(i)->setSelected(select);
        }
    }
    else {
        card->setSelected(select);
    }
}

void SpriteManager::setShufflingFirst(ShuffingType type)
{
    if (shufflingFirst == ShuffingType::None)
        shufflingFirst = type;
}

SpriteManager::ShuffingType SpriteManager::getShufflingFirst()
{
    auto t = shufflingFirst;
    shufflingFirst = ShuffingType::None;
    return t;
}

//-----------------------ai
void SpriteManager::upCard(Vector<CardSprite*> vec,Vector<CardSprite*> &tempVec)
{
    if(!vec.empty())
    {
        for(auto card:vec)
        {
            card->setIsJie(false);
            tempVec.pushBack(card);
        }
    }
}
void SpriteManager::downCard(Vector<CardSprite*> vec,Vector<CardSprite*> &tempVec)
{
    if(!vec.empty())
    {
        for(auto card:vec)
        {
            auto is = card->getIsOpen();
            if(!is)
            {
                card->setIsJie(false);
                tempVec.pushBack(card);
            }
        }
    }
}

void lastCard(Vector<CardSprite*> vec,Vector<CardSprite*> &tempVec)
{
    if(!vec.empty())
    {
        auto card = vec.at(vec.size()-1);
        //取出最后一张牌
        if(card->getIsOpen())
        {
            tempVec.pushBack(card);
        }
    }
}

void lastBDCard(Vector<CardSprite*> vec,Vector<CardSprite*> &tempVec)
{
    if(!vec.empty())
    {
        auto card = vec.at(vec.size()-1);
        //如果只有一张打开的牌。取出最后一张牌
        if(vec.size()>1)
        {
            auto cardA = vec.at(vec.size()-2);
            if(!cardA->getIsOpen())
            {//上一张不是打开的 才取最后一张
                if(card->getIsOpen()&&card->getNumber() != 13)
                {
                    tempVec.pushBack(card);
                }
            }
            else
            {//上一张是打开的。取最上边的
                for(int i = 0;i<vec.size();++i)
                {
                    auto cardB = vec.at(i);
                    if(!cardB->getIsOpen())
                    {//至少有一个是盖住的 往下找第一个翻开的
                        if(i+1<vec.size())
                        {
                            auto cardC = vec.at(i+1);
                            if(cardC->getIsOpen()&&card->getNumber() != 13)
                            {//是打开的 放入容器。 跳出
                                tempVec.pushBack(cardC);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
void SpriteManager::shuffleEffect(Vector<CardSprite*> upVec,Vector<CardSprite*> downVec,CardSprite* moveCard,CardSprite* card)
{
    //筛选出可以移动到下方的牌
    //先选出下方各个牌组 中最下面的牌
    Vector<CardSprite*> lastVec;
    Vector<CardSprite*> lastBDVec;
    //是否筛选出k
    bool isK = false;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        if(vec.size() == 0)
        {
            isK = true;
        }
        else
        {
            lastCard(vec,lastVec);
            lastBDCard(vec,lastBDVec);
        }
        
    }
    Vector<CardSprite*> effectiveTempVec;
    Vector<CardSprite*> effectiveTempBDVec;
    effectiveVec.clear();
    int idx = -1;
    int id = -1;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        if(vec.getIndex(card) != -1)
        {
            idx = vec.getIndex(card);
            id = i;
        }
    }
    auto vec = kCardVector[id];
    auto size = vec.size();
    
    if(1)
    {
        //取出被动有效牌
        for(auto lastCard:lastBDVec)
        {
            auto lastNumber = lastCard->getNumber();
            //0,2黑    1,3红
            auto lastCol = (int)lastCard->getColorType();
            for(auto downCard:downVec)
            {//取出下方牌组中有效的牌
                if(downCard->getIsJiaoHuan())continue;//已经交换过的跳过
                auto downNumber = downCard->getNumber();
                auto downCol = (int)downCard->getColorType();
                //被动有效 比目标牌数值大1
                if(downNumber - lastNumber == 1&&lastCol%2 != downCol%2)
                {
                    if(effectiveTempBDVec.getIndex(downCard) == -1)
                    {//防止重复筛选
                        downCard->setIsJie(true);
                        effectiveTempBDVec.pushBack(downCard);
                    }
                }
            }
        }
//        //如果功能一样 就移出有效容器
//        for(auto lastCard:lastBDVec)
//        {
//            auto lastNumber = lastCard->getNumber();
//            //0,2黑    1,3红
//            auto lastCol = (int)lastCard->getColorType();
//            for(auto effCard:effectiveVec)
//            {
//                auto effNumber = effCard->getNumber();
//                //0,2黑    1,3红
//                auto effCol = (int)effCard->getColorType();
//                if(effNumber == lastNumber&&lastCol%2 == effCol%2)
//                {//大小一样 红黑一样
//                    effectiveVec.eraseObject(effCard);
//                    break;
//                }
//            }
//        }
    }
    
    
    if(1)
    {//寻找主动有效牌
        if(1)
        {
            for(auto lastCard:lastVec)
            {
                auto lastNumber = lastCard->getNumber();
                //0,2黑    1,3红
                auto lastCol = (int)lastCard->getColorType();
                //            for(auto upCard:upVec)
                //            {//取出发牌牌组中有效的牌
                //                if(upCard->getIsJiaoHuan())continue;//已经交换过的跳过
                //                auto upNumber = upCard->getNumber();
                //                auto upCol = (int)upCard->getColorType();
                //                if(lastNumber - upNumber == 1&&lastCol%2 != upCol%2)
                //                {
                //                    if(effectiveVec.getIndex(upCard) == -1)
                //                    {//防止重复筛选
                //                        upCard->setIsJie(true);
                //                        effectiveVec.pushBack(upCard);
                //                    }
                //                }
                //                else if(isK&&upNumber == 13)
                //                {
                //                    if(effectiveVec.getIndex(upCard) == -1)
                //                    {//防止重复筛选
                //                        upCard->setIsJie(true);
                //                        effectiveVec.pushBack(upCard);
                //                    }
                //                }
                //            }
                for(auto downCard:downVec)
                {//取出下方牌组中有效的牌
                    if(downCard->getIsJiaoHuan())continue;//已经交换过的跳过
                    auto downNumber = downCard->getNumber();
                    auto downCol = (int)downCard->getColorType();
                    if(lastNumber - downNumber == 1&&lastCol%2 != downCol%2)
                    {
                        if(effectiveTempVec.getIndex(downCard) == -1)
                        {//防止重复筛选
                            downCard->setIsJie(true);
                            effectiveTempVec.pushBack(downCard);
                        }
                    }
                    else if(isK&&downNumber == 13)
                    {
                        if(effectiveTempVec.getIndex(downCard) == -1)
                        {//防止重复筛选
                            downCard->setIsJie(true);
                            effectiveTempVec.pushBack(downCard);
                        }
                    }
                }
            }
        }
        
        if(1)
        {// 选出A-K
            //选出符合条件的牌  空地与k  大小差一花色不同。 与收牌
            Vector<CardSprite*> AVec;
            bool isNull = false;
            for(int i = 0;i<4;++i)
            {
                auto vec = aCardVector[i];
                if(vec.empty())
                {
                    isNull = true;
                }
                else
                {
                    lastCard(vec,AVec);
                }
            }
            
            if(isNull)
            {//空的
                //筛选出四个a
                //        for(auto upCard:upVec)
                //        {//取出发牌牌组中有效的牌
                //            if(upCard->getIsJiaoHuan())continue;//已经交换过的跳过
                //            auto upNumber = upCard->getNumber();
                //            auto upCol = (int)upCard->getColorType();
                //            if(upNumber == 1)
                //            {
                //                if(effectiveVec.getIndex(upCard) == -1)
                //                {//防止重复筛选
                //                    upCard->setIsJie(true);
                //                    effectiveVec.pushBack(upCard);
                //                }
                //            }
                //        }
                for(auto downCard:downVec)
                {//取出下方牌组中有效的牌
                    if(downCard->getIsJiaoHuan())continue;//已经交换过的跳过
                    auto downNumber = downCard->getNumber();
                    auto downCol = (int)downCard->getColorType();
                    if(downNumber== 1)
                    {
                        if(effectiveTempVec.getIndex(downCard) == -1)
                        {//防止重复筛选
                            downCard->setIsJie(true);
                            effectiveTempVec.pushBack(downCard);
                        }
                    }
                }
            }
            
            for(auto aCard:AVec)
            {
                auto aNumber = aCard->getNumber();
                //0,2黑    1,3红
                auto aCol = (int)aCard->getColorType();
                //        for(auto upCard:upVec)
                //        {//取出发牌牌组中有效的牌
                //            if(upCard->getIsJiaoHuan())continue;//已经交换过的跳过
                //            auto upNumber = upCard->getNumber();
                //            auto upCol = (int)upCard->getColorType();
                //            if(upNumber - aNumber == 1&&aCol == upCol)
                //            {
                //                if(effectiveVec.getIndex(upCard) == -1)
                //                {//防止重复筛选
                //                    upCard->setIsJie(true);
                //                    effectiveVec.pushBack(upCard);
                //                }
                //            }
                //        }
                for(auto downCard:downVec)
                {//取出下方牌组中有效的牌
                    if(downCard->getIsJiaoHuan())continue;//已经交换过的跳过
                    auto downNumber = downCard->getNumber();
                    auto downCol = (int)downCard->getColorType();
                    if(downNumber - aNumber == 1&&aCol == downCol)
                    {
                        if(effectiveTempVec.getIndex(downCard) == -1)
                        {//防止重复筛选
                            downCard->setIsJie(true);
                            effectiveTempVec.pushBack(downCard);
                        }
                    }
                }
            }
        }
    }
    //筛选有效容器
    if(!effectiveTempVec.empty())
    {
        Vector<CardSprite*> tempVecZD;
        for(auto effCard:effectiveTempVec)
        {
            auto effNum = effCard->getNumber();
            auto effCol = (int)effCard->getColorType();
            for(auto bdcard:lastBDVec)
            {
                auto bdNum = bdcard->getNumber();
                auto bdCol = (int)bdcard->getColorType();
                if(effNum == bdNum&&effCol%2 == bdCol%2&&effNum != 1&&effNum != 13)
                {//场上有相同效果的牌 移除有效容器
                    tempVecZD.pushBack(effCard);
                }
            }
        }
        for(auto card:tempVecZD)
        {
            effectiveTempVec.eraseObject(card);
        }
    }
    if(!effectiveTempBDVec.empty())
    {
        //筛选被动有效容器
        Vector<CardSprite*> tempVecBD;
        for(auto effCard:effectiveTempBDVec)
        {
            auto effNum = effCard->getNumber();
            auto effCol = (int)effCard->getColorType();
            for(auto card:lastVec)
            {
                auto Num = card->getNumber();
                auto Col = (int)card->getColorType();
                if(effNum == Num&&effCol%2 == Col%2)
                {//场上有相同效果的牌 移除有效容器
                    tempVecBD.pushBack(effCard);
                }
            }
        }
        for(auto card:tempVecBD)
        {
            effectiveTempBDVec.eraseObject(card);
        }
    }
    
    
    if(size != 1&&randEffective > 0)
    {//主动 最后一张牌时先选一下被动
        if(!effectiveTempVec.empty())
        {//主动不为空
            for(auto card:effectiveTempVec)
            {
                effectiveVec.pushBack(card);
            }
        }
        else
        {//主动空的
            if(!effectiveTempBDVec.empty())
            {//被动不为空
                for(auto card:effectiveTempBDVec)
                {
                    effectiveVec.pushBack(card);
                }
            }
        }
        randEffective--;
    }
    else if(size == 1||randEffective == 0)
    {//被动
        if(!effectiveTempBDVec.empty())
        {//被动不为空
            for(auto card:effectiveTempBDVec)
            {
                effectiveVec.pushBack(card);
            }
        }
        else
        {//被动空的
            if(!effectiveTempVec.empty())
            {//主动不为空
                for(auto card:effectiveTempVec)
                {
                    effectiveVec.pushBack(card);
                }
            }
        }
        if(size != 1)
        {//最后一张时不计算
            randEffective--;
        }
    }
    
    
    
    
    // 被动
    // 主动
    
    if(effectiveVec.empty())
    {//没有有效牌
        //筛选出最小的牌 并指定花色
        CardSprite* tCard = nullptr;
        CardSprite* tMinCard = nullptr;
        
        for(int i = 0;i<downVec.size();++i)
        {//排序最小的放在最前面
            auto card = downVec.at(i);
            if(card->getIsJiaoHuan())continue;//已经交换过的跳过
            auto num = card->getNumber();
            auto col = (int)card->getColorType();
            if(col == hongColor||col == heiColor)
            {
                if(tCard)
                {
                    auto tNum = tCard->getNumber();
                    if(tNum > num)
                    {
                        tCard = card;
                    }
                }
                else
                {
                    tCard = card;
                }
            }
        }
        if(!tCard)
        {
            for(int i = 0;i<downVec.size();++i)
            {//排序最小的放在最前面
                auto card = downVec.at(i);
                if(card->getIsJiaoHuan())continue;//已经交换过的跳过
                auto num = card->getNumber();
                auto col = (int)card->getColorType();
                if(1)//col == hongColor||col == heiColor)
                {
                    if(tCard)
                    {
                        auto tNum = tCard->getNumber();
                        if(tNum > num)
                        {
                            tCard = card;
                        }
                    }
                    else
                    {
                        tCard = card;
                    }
                }
            }
        }
        
        
        if(tCard)
        {
            effectiveVec.pushBack(tCard);
        }
    }
    
    if(randEffective < 0)
    {
        randEffective = random(1, 4);
    }
}

void SpriteManager::effectiveCardOne()
{
    hongColor;
    heiColor;
    Vector<CardSprite*> tVec;
    if(effectiveVec.size() > 1)
    {//查出有没有大小和红黑 相同的牌
        for(auto card1 : effectiveVec)
        {
            auto num1 = card1->getNumber();
            auto col1 = (int)card1->getColorType();
            for(auto card2 : effectiveVec)
            {
                if(card1 == card2)continue;
                auto num2 = card2->getNumber();
                auto col2 = (int)card2->getColorType();
                if(num1 == num2&&col1%2 == col2%2)
                {//大小相同
                    if(col1%2 == 1)
                    {//hong
                        if(hongColor == col1)
                        {
                            if(tVec.getIndex(card2) != -1)continue;
                            tVec.pushBack(card2);
                        }
                        else
                        {
                            if(tVec.getIndex(card1) != -1)continue;
                            tVec.pushBack(card1);
                        }
                    }
                    else
                    {//hei
                        if(heiColor == col1)
                        {
                            if(tVec.getIndex(card2) != -1)continue;
                            tVec.pushBack(card2);
                        }
                        else
                        {
                            if(tVec.getIndex(card1) != -1)continue;
                            tVec.pushBack(card1);
                        }
                    }
                }
            }
        }
        for(auto card:tVec)
        {//移除重复的牌 保留优先花色
            effectiveVec.eraseObject(card);
        }
        
    }
}

void SpriteManager::effectiveCard(CardSprite* moveCard,CardSprite* card,int col)
{
    if(card->getIsJiaoHuan()||!moveCard)return;
    //道具ai次数
    if(isDaoJuAI)
    {
        daoJuAINum--;
        //次数归零 取消道具效果
        isDaoJuAI = daoJuAINum > 0;
    }
    
    if(DATA_M->getGameType() == DataManager::GameType::Random)
    {//每走4步 开启一步辅助 当辅助生效时 再次走4步 开启一步辅助
        auto tempNum = SCENE_M->getGameView()->getMoveNum() + 1;
        randomMoveNum += tempNum - randomTempMoveNum;
        randomTempMoveNum = tempNum;
        if(randomMoveNum < 5)
        {
            //被翻开了 锁定这张牌
            card->setIsJiaoHuan(true);
            return;
        }
        else
        {
            randomMoveNum = 0;
        }
    }
    //此处翻牌  替换掉这张牌
    //更新有效牌组。
    //取出一张
    if(moveCard)
    {
        Vector<CardSprite*> tempUpVec;
        upCard(waitShowCardVector,tempUpVec);
        upCard(waitCardVector,tempUpVec);
        Vector<CardSprite*> tempDownVec;
        for(int i = 0;i<7;++i)
        {
            auto vec = kCardVector[i];
            downCard(vec,tempDownVec);
        }
        shuffleEffect(tempUpVec,tempDownVec,tempMoveCard,card);
        effectiveCardOne();
        //打乱排序
        std::random_shuffle(effectiveVec.begin(), effectiveVec.end(), myrandom);
        if(!effectiveVec.empty())
        {
            auto Num = tempMoveCard->getNumber();
            auto Col = (int)tempMoveCard->getColorType();
            auto cardNum = card->getNumber();
            auto cardCol = (int)card->getColorType();
            for(auto effCard:effectiveVec)
            {//这张有效牌不能与card 大小相同或者 颜色相同
                auto effNum = effCard->getNumber();
                auto effCol = (int)effCard->getColorType();
                if((effCard == card)||(cardNum == 1&&effNum == 1)||(cardNum == 13&&effNum == 13)||cardNum == 1)
                {//如果功能相同就不提换
                    //已经交换过了
                    card->setIsJiaoHuan(true);
                    break;
                }
                if(Num != effNum||Col%2 != effCol%2||effNum == 1)
                {//每张牌只交换一次  加入
                    //交换
                    auto upColor = effCard->getColorType();
                    auto downColor = card->getColorType();
                    effCard->setColorType(downColor);
                    card->setColorType(upColor);
                    //        CC_SYNTHESIZE(int ,number,Number);
                    //交换大小getIndex
                    auto upNumber = effCard->getNumber();
                    auto downNumber = card->getNumber();
                    effCard->setNumber(downNumber);
                    card->setNumber(upNumber);
                    //交换id
                    auto upId = effCard->getCardId();
                    auto downId = card->getCardId();
                    effCard->setCardId(downId);
                    card->setCardId(upId);
                    
                    //已经交换过了
                    card->setIsJiaoHuan(true);
                    //每次交换更新交换的位置。 仅限k牌组
                    updateAgainVec(effCard,card,col);
                    break;
                }
            }
        }
        else
        {//被翻开了。锁定这张牌
            card->setIsJiaoHuan(true);
        }
        //每次翻牌更新一次 被锁定的牌 kAgainCardJiaoHuanVec
        updateIsOpenVec(card);
    }
    tempMoveCard = nullptr;
}


//先记录一遍初始牌
void SpriteManager::updateAgainVec()
{
    //清空
    for(int i = 0;i<7;++i)
    {
        auto numVec = &kAgainCardNumVec[i];
        auto colVec = &kAgainCardColVec[i];
        auto idVec = &kAgainCardIdVec[i];
        auto isVec = &kAgainCardJiaoHuanVec[i];
        numVec->clear();
        colVec->clear();
        idVec->clear();
        isVec->clear();
    }
    
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        auto numVec = &kAgainCardNumVec[i];
        auto colVec = &kAgainCardColVec[i];
        auto idVec = &kAgainCardIdVec[i];
        auto isVec = &kAgainCardJiaoHuanVec[i];
        for(int j = 0;j < vec.size();++j)
        {
            auto card = vec.at(j);
            auto num = card->getNumber();
            auto col = (int)card->getColorType();
            auto id = card->getCardId();
            auto is = card->getIsJiaoHuan();
            numVec->push_back(num);
            colVec->push_back(col);
            idVec->push_back(id);
            isVec->push_back(is);
        }
    }
}
//只记录是否被固定

////记录换掉的牌  当翻开有效开启时记录 每次翻开记录
void SpriteManager::updateAgainVec(CardSprite* moveCard,CardSprite* card,int col)
{
    //得到所在的位置
    auto idx = kCardVector[col].size() - 1;
    int moveIdx = -1;
    int moveCol = -1;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        moveIdx = vec.getIndex(moveCard);
        if(moveIdx != -1)
        {
            moveCol = i;
            break;
        }
    }
    
    auto numVec = &kAgainCardNumVec[col];
    auto colVec = &kAgainCardColVec[col];
    auto idVec = &kAgainCardIdVec[col];
    
    auto &knum = numVec->at(idx);
    auto &kcol = colVec->at(idx);
    auto &kid = idVec->at(idx);
    
    auto num = card->getNumber();
    auto color = (int)card->getColorType();
    auto id = card->getCardId();
    
    knum = num;
    kcol = color;
    kid = id;
    //记录交换的牌
    if(moveIdx != -1)
    {
        auto movenumVec = &kAgainCardNumVec[moveCol];
        auto movecolVec = &kAgainCardColVec[moveCol];
        auto moveidVec = &kAgainCardIdVec[moveCol];
        auto &moveknum = movenumVec->at(moveIdx);
        auto &movekcol = movecolVec->at(moveIdx);
        auto &movekid = moveidVec->at(moveIdx);
        
        auto movenum = moveCard->getNumber();
        auto movecolor = (int)moveCard->getColorType();
        auto moveid = moveCard->getCardId();
        
        moveknum = movenum;
        movekcol = movecolor;
        movekid = moveid;
    }
}

void SpriteManager::tiHuanCard()
{
    for(int i = 0;i<7;++i)
    {
        auto numVec = kAgainCardNumVec[i];
        auto colVec = kAgainCardColVec[i];
        auto idVec = kAgainCardIdVec[i];
        auto isVec = kAgainCardJiaoHuanVec[i];
        auto vec = kCardVector[i];
        for(int j = 0;j<numVec.size();++j)
        {
            auto num = numVec.at(j);
            auto color = colVec.at(j);
            auto id = idVec.at(j);
            auto is = (bool)isVec.at(j);
            auto card = vec.at(j);
            card->setIsJiaoHuan(is);
            //找到符合提换的牌。两个牌交换
            auto tiHuanCard = tiHuanShaiXuan(num, color, id);
            if(tiHuanCard&&tiHuanCard != card)
            {//两个牌交换
                //交换
                auto upColor = tiHuanCard->getColorType();
                auto downColor = card->getColorType();
                tiHuanCard->setColorType(downColor);
                card->setColorType(upColor);
                //        CC_SYNTHESIZE(int ,number,Number);
                //交换大小getIndex
                auto upNumber = tiHuanCard->getNumber();
                auto downNumber = card->getNumber();
                tiHuanCard->setNumber(downNumber);
                card->setNumber(upNumber);
                //交换id
                auto upId = tiHuanCard->getCardId();
                auto downId = card->getCardId();
                tiHuanCard->setCardId(downId);
                card->setCardId(upId);
            }
        }
    }
}

CardSprite* SpriteManager::tiHuanShaiXuan(int num,int color,int id)
{
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        for(auto card:vec)
        {
            auto cardnum = card->getNumber();
            auto cardcolor = (int)card->getColorType();
            auto cardid = card->getCardId();
            if(cardnum == num&&cardcolor == color&&cardid == id)
            {
                return card;
            }
        }
    }
}

void SpriteManager::openEffective()
{
#if TestAutoPlay
    if (true)
    {
        isOpenEffective = false;
        return;
    }
#endif
    auto is = DATA_M->getGuangGao();
    if(is)
    {
        isOpenEffective = true;
        return;
    }
    if(DATA_M->getGameType() == DataManager::GameType::Daily)
    {
        /*
         挑战模式
         重开就开启
         */
        auto dailyStr = DailyManager::getInstance()->getCurrentMode();
        auto dailyNum = UIUtils::stoii(dailyStr);
        if(isChongKai)
        {
            if(dailyNum == 1)
            {//简单
                isOpenEffective = true;
                isFanPaiNum = false;
                fanPaiNum = -1;
            }
            else if(dailyNum == 2)
            {//中等
                isOpenEffective = false;
                isFanPaiNum = true;
                fanPaiNum = 30;
            }
            else if(dailyNum == 3)
            {//困难
                isOpenEffective = false;
                isFanPaiNum = true;
                fanPaiNum = 50;
            }
            else if(dailyNum == 4)
            {//专家
                isOpenEffective = false;
                isFanPaiNum = true;
                fanPaiNum = 50;
            }
        }
        else
        {
            if(dailyNum == 1)
            {//简单
                isOpenEffective = true;
            }
            else
            {
                isOpenEffective = false;
            }
        }
    }
    else if(DATA_M->getGameType() == DataManager::GameType::Huo)
    {
        /*
         经典模式  1 2 局开启 3局关闭，之后看评分
         */
        //无辅助活局总局数
        auto huoTotalCNT = ScoreManager::getInstance()->getComTotalCNT((int)DATA_M->getIsThreeModel(),0);
        //有辅助活局总局数
        auto huoEffTotalCNT = ScoreManager::getInstance()->getEffComTotalCNT((int)DATA_M->getIsThreeModel(),0);
        auto totalCNT = huoTotalCNT + huoEffTotalCNT;
        auto total = ScoreManager::getInstance()->getTotalCNT((int)DATA_M->getIsThreeModel() + 1);
        
        //2021年4月1日 改动 第一局关闭辅助，之后看评分
        if(total < 1)
        {//总局数小于2局 开启辅助
            totalCNT = 1;
        }
        else
        {
            totalCNT += 10;
        }
        if(totalCNT <= 1)
        {
            isOpenEffective = true;
            fanPaiNum = 0;
        }
        else if(totalCNT == 10)
        {
            isOpenEffective = false;
        }
        else if(totalCNT > 10)
        {
            auto level = DATA_M->userLevel();
            //评分
            if(level == 1||level == 2||level == 3)
            {//高手
                isOpenEffective = false;
            }
            else if(level == 4)
            {//一般
                isOpenEffective = false;
                isFanPaiNum = true;
                fanPaiNum = 50;
            }
            else if(level == 5)
            {//入门
                isOpenEffective = false;
                isFanPaiNum = true;
                fanPaiNum = 30;
            }
            else if(level == 6)
            {//菜鸟/新手
                isOpenEffective = true;
                fanPaiNum = 0;
            }
            else if(level == -1)
            {//没有满足评分条件
                isOpenEffective = false;
            }
        }
        
        if(isOpenEffective)
        {
            randEffective = random(1, 4);
        }
    }
    else if(DATA_M->getGameType() == DataManager::GameType::Random)
    {//困难模式没有开启
        isOpenEffective = false;
    }
    else if(DATA_M->getGameType() == DataManager::GameType::Level)
    {
        auto group = LevelManager::getInstance()->getCurrentGroup();
        auto sub = LevelManager::getInstance()->getCurrentSub();
        //100关后关闭  100关 group = 2； sub = 39
        if((group==2&&sub >= 39)||group > 2)
        {
            isOpenEffective = false;
        }
        else
        {
            isOpenEffective = false;
        }
    }
    
    //2021年6月17日 此版本只第一局开启辅助
    
    auto gameNum = ScoreManager::getInstance()->getWinTotalCNT(false);
    if(gameNum < 1)
    {
        isOpenEffective = true;
    }
    else
    {
        isOpenEffective = false;
    }
    
}

void SpriteManager::updateIsOpenVec(CardSprite* card)
{//记录被翻开锁定的牌
    //判断翻开的牌的位置
    auto idx = -1;
    auto col = -1;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        idx = vec.getIndex(card);
        if(idx != -1)
        {
            col = i;
            break;
        }
    }
    
    if(idx != -1)
    {
        auto isVec = &kAgainCardJiaoHuanVec[col];
        auto &is = isVec->at(idx);
        is = (int)card->getIsJiaoHuan();
    }
    
}

//-------------shuffle
bool SpriteManager::Shuffle()
{
    //setGameState(State::Shuffle);
    //选取上下牌堆的牌
    Vector<CardSprite*> tempUpVec;
    upCard(waitShowCardVector,tempUpVec);
    upCard(waitCardVector,tempUpVec);
    
    
    Vector<CardSprite*> tempDownVec;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        downCard(vec,tempDownVec);
    }
    
    return shuffle(tempUpVec,tempDownVec);
}

void SpriteManager::shuffle(Vector<CardSprite*> vec)
{
    //筛选出vec中的有效牌与被动有效牌
    
    //先选出下方各个牌组 中最下面的牌
    Vector<CardSprite*> lastVec;
    Vector<CardSprite*> lastBDVec;
    //是否筛选出k
    bool isK = false;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        if(vec.size() == 0)
        {
            isK = true;
        }
        else
        {
            lastCard(vec,lastVec);
            lastBDCard(vec,lastBDVec);
        }
    }
    
    //选出符合条件的牌  空地与k  大小差一花色不同。 与收牌
    Vector<CardSprite*> AVec;
    for(int i = 0;i<4;++i)
    {
        auto vec = aCardVector[i];
        lastCard(vec,AVec);
    }
    
    tempLastVec.clear();
    Vector<CardSprite*> tempBDCard5;
    
    for(auto lastCard:lastVec)
    {
        auto lastNumber = lastCard->getNumber();
        //0,2黑    1,3红
        auto lastCol = (int)lastCard->getColorType();
        for(auto downCard:vec)
        {//取出下方牌组中有效的牌
            auto downNumber = downCard->getNumber();
            auto downCol = (int)downCard->getColorType();
            if(lastNumber - downNumber == 1&&lastCol%2 != downCol%2)
            {
                if(tempBDCard5.getIndex(downCard) == -1)
                {//防止重复筛选
                    downCard->setIsJie(true);
                    tempBDCard5.pushBack(downCard);
                }
                if(tempLastVec.getIndex(downCard) == -1)
                {//防止重复筛选
                    downCard->setIsJie(true);
                    tempLastVec.pushBack(downCard);
                }
            }
            else if(isK&&downNumber == 13)
            {
                if(tempBDCard5.getIndex(downCard) == -1)
                {//防止重复筛选
                    downCard->setIsJie(true);
                    tempBDCard5.pushBack(downCard);
                }
                if(tempLastVec.getIndex(downCard) == -1)
                {//防止重复筛选
                    downCard->setIsJie(true);
                    tempLastVec.pushBack(downCard);
                }
            }
            if(downNumber == 1)
            {
                if(tempLastVec.getIndex(downCard) == -1)
                {//防止重复筛选
                    downCard->setIsJie(true);
                    tempLastVec.pushBack(downCard);
                }
            }
        }
    }
    
    
    if(!AVec.empty())
    {//选出最小的
        CardSprite* minCard = nullptr;
        for(auto aCard:AVec)
        {
            auto aNumber = aCard->getNumber();
            //0,2黑    1,3红
            auto aCol = (int)aCard->getColorType();
            for(auto downCard:vec)
            {//取出下方牌组中有效的牌
                auto downNumber = downCard->getNumber();
                auto downCol = (int)downCard->getColorType();
                if(downNumber - aNumber == 1&&aCol == downCol)
                {
                    if(!minCard)
                    {
                        minCard = downCard;
                    }
                    else
                    {
                        auto minNum = minCard->getNumber();
                        if(downNumber < minNum)
                        {//取出小的
                            minCard = downCard;
                        }
                    }
                }
            }
        }
        if(minCard)
        {
            if(tempLastVec.getIndex(minCard) == -1)
            {//防止重复筛选
                minCard->setIsJie(true);
                tempLastVec.pushBack(minCard);
            }
        }
    }
    else
    {
    }
    
    //进一步筛选被动有效牌
    tempLastBDVec.clear();
    //
    for(auto bdCard:lastBDVec)
    {
        auto bdnum = bdCard->getNumber();
        auto bdcolor = (int)bdCard->getColorType();
        for(auto tempCard:tempBDCard5)
        {
            auto tempNum = tempCard->getNumber();
            auto tempColor = (int)tempCard->getColorType();
            if(tempNum - bdnum == 1&&bdcolor%2 != tempColor%2)
            {
                tempLastBDVec.pushBack(tempCard);
            }
        }
    }
}

void SpriteManager::shuffleUp()
{
    //目标 选择可以收起来的牌
    tempLastUpVec.clear();
    //取下放所有的牌
    Vector<CardSprite*> tempDownVec;
    bool isNull = false;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        if(!vec.empty())
        {//取出最下面的牌
            auto card = vec.at(vec.size()-1);
            tempDownVec.pushBack(card);
        }
    }
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        if(!vec.empty())
        {//取出所有盖住的牌
            for(auto card:vec)
            {
                if(!card->getIsOpen())
                {//没有翻开的牌
                    tempDownVec.pushBack(card);
                }
            }
        }
    }
    
    for(auto card:waitCardVector)
    {//取所有发牌区的牌
        tempDownVec.pushBack(card);
    }
    for(auto card:waitShowCardVector)
    {//取所有发牌等待区的牌
        tempDownVec.pushBack(card);
    }

    Vector<CardSprite*> tempUpVec;
    for(int i = 0;i<4;++i)
    {
        auto vec = aCardVector[i];
        if(!vec.empty())
        {//取出收牌牌区最后一张 做判断
            isNull = true;
            auto card = vec.at(vec.size()-1);
            tempUpVec.pushBack(card);
        }
    }
    
    
    for(auto upCard:tempUpVec)
    {
        auto upNum = upCard->getNumber();
        auto upCol = (int)upCard->getColorType();
        
        for(auto downCard:tempDownVec)
        {
            auto downNum = downCard->getNumber();
            auto downCol = (int)downCard->getColorType();
            if(downNum - upNum == 1&&upCol == downCol)
            {
                if(tempLastUpVec.getIndex(downCard) == -1)
                {
                    tempLastUpVec.pushBack(downCard);
                }
                
            }
            else if(downNum == 1)
            {
                if(tempLastUpVec.getIndex(downCard) == -1)
                {
                    tempLastUpVec.pushBack(downCard);
                }
            }
        }
    }
}

bool SpriteManager::isMagic()
{
    Vector<CardSprite*> tempUpVec;
    upCard(waitShowCardVector,tempUpVec);
    upCard(waitCardVector,tempUpVec);
    
    
    Vector<CardSprite*> tempDownVec;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        downCard(vec,tempDownVec);
    }
    
    shuffle(tempDownVec);
    bool is = true;
    if(tempLastVec.empty()&&tempLastBDVec.empty())
    {
        shuffle(tempUpVec);
    }
    
    if(tempLastVec.empty()&&tempLastBDVec.empty())
    {
        shuffleUp();
        is = false;
    }
    
    _effCard=nullptr;
    //筛出有效牌。 替换下方牌组中 最下面的盖住的牌
    std::random_shuffle(tempLastBDVec.begin(), tempLastBDVec.end(), myrandom);
    std::random_shuffle(tempLastVec.begin(), tempLastVec.end(), myrandom);
    std::random_shuffle(tempLastUpVec.begin(), tempLastUpVec.end(), myrandom);
    if(is)
    {
        //被动不为空 用被动牌进行替换
        
        //禁用被动有效牌
        auto lastVec2 = tempLastVec;//!tempLastBDVec.empty()?tempLastBDVec:tempLastVec;
        //只替换一张牌
        if(!lastVec2.empty())
        {
            for(auto effCard: lastVec2)
            {
                _effCard = effCard;
                break;
            }
        }
    }
    else
    {
        //只替换一张牌
        if(!tempLastUpVec.empty())
        {
            for(auto effCard: tempLastUpVec)
            {
                _effCard = effCard;
                break;
            }
        }
    }
    
    is = true;
    for(int i = 0;i<4;++i)
    {
        auto vec = aCardVector[i];
        if(vec.size() == 13)
        {
            is = false;
        }
        else
        {
            return true;
        }
    }
    
    if(!is)
    {//牌都收起来
        
    }
    
    return is;
    return true;
}

bool SpriteManager::shuffle(Vector<CardSprite*> upVec,Vector<CardSprite*> downVec)
{
    
    //先选出下方各个牌组 中最下面的牌
    Vector<CardSprite*> lastVec;
    Vector<CardSprite*> lastBDVec;
    //是否筛选出k
    bool isK = false;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        if(vec.size() == 0)
        {
            isK = true;
        }
        else
        {
            lastCard(vec,lastVec);
            lastBDCard(vec,lastBDVec);
        }
    }
    
    
    //选出符合条件的牌  空地与k  大小差一花色不同。 与收牌
    Vector<CardSprite*> AVec;
    
    for(int i = 0;i<4;++i)
    {
        auto vec = aCardVector[i];
        lastCard(vec,AVec);
    }
    
    shuffle(downVec);
    
    if(tempLastVec.empty()&&tempLastBDVec.empty())
    {
        shuffle(upVec);
    }
    //找到对应的牌
    auto num = _effCard->getNumber();
    auto color = (int)_effCard->getColorType();
    CardSprite* tempCard = nullptr;
    CardSprite* tempUpCard = nullptr;
    
    
    if(!tempUpCard)
    {// 不能放到下面  检测上边
        for(auto aCard:AVec)
        {
            auto aNum = aCard->getNumber();
            auto aCol = (int)aCard->getColorType();
            if(num - aNum == 1&&aCol == color)
            {
                tempUpCard = aCard;
                break;
            }
        }
    }
    
    if(!tempCard)
    {
        for(auto lastCard:lastVec)
        {
            auto lastNum = lastCard->getNumber();
            auto lastCol = (int)lastCard->getColorType();
            if(lastNum - num == 1&&color%2!=lastCol%2)
            {
                tempCard = lastCard;
                break;
            }
        }
    }
    int effId = -1;
    Sprite* effSprite = nullptr;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        
        if(vec.getIndex(_effCard)!=-1)
        {
            effSprite = kSprite[i];
            effId = i;
        }
    }
    //有效牌的容器
    Vector<CardSprite*>* effVec = nullptr;
    if(effId != -1&&!_effCard->getIsOpen())
    {//必须是没有被翻开的牌
        effVec = &kCardVector[effId];
        updateIsOpenVec(_effCard);
    }
    else if(tempLastUpVec.getIndex(_effCard) != -1)
    {//选择所有牌。进行收牌
        effVec = &kCardVector[effId];
    }
    else
    {
        effVec = waitShowCardVector.getIndex(_effCard) != -1?&waitShowCardVector:&waitCardVector;
    }
    
    //移动与层次解决了，考虑抽出的牌组的排序
    if(tempUpCard)
    {
        for(int i = 0;i<4;++i)
        {
            auto vec = &aCardVector[i];
            if(vec->getIndex(tempUpCard) != -1)
            {//
                auto sp = aSprite[i];
                //交换容器
                effVec->eraseObject(_effCard);
                
                vec->pushBack(_effCard);
                //层级
                _effCard->setCardLocalZOrder(tempUpCard->getLocalZOrder() + 1);
                //翻开
                _effCard->setIsOpen(true);
                //容器id
                _effCard->setColNum(i);
                //容器位置
                auto posid = _effCard->getPosId();
                _effCard->setPosId(0);
                
                //移动
                if(effSprite)
                {
                    _effCard->playDaoJuEff(sp->getPosition(),effVec,posid,effSprite->getPosition());
                }
                else
                {
                    _effCard->playDaoJuEff(sp->getPosition(),effVec,posid,Vec2(0,0));
                }
                
                break;
            }
        }
    }
    else if(num == 1)
    {
        //找空地
        for(int i = 0;i<4;++i)
        {
            auto vec = &aCardVector[i];
            if(vec->empty())
            {
                auto sp = aSprite[i];
                //交换容器
                effVec->eraseObject(_effCard);
                
                vec->pushBack(_effCard);
                //层级
                _effCard->setCardLocalZOrder(1);
                //翻开
                _effCard->setIsOpen(true);
                //容器id
                _effCard->setColNum(i);
                //容器位置
                auto posid = _effCard->getPosId();
                _effCard->setPosId(0);
                
                //移动
                if(effSprite)
                {
                    _effCard->playDaoJuEff(sp->getPosition(),effVec,posid,effSprite->getPosition());
                }
                else
                {
                    _effCard->playDaoJuEff(sp->getPosition(),effVec,posid,Vec2(0,0));
                }
                break;
            }
        }
    }
    else if(tempCard)
    {
        //判断所在容器
        int id = -1;
        for(int i = 0;i<7;++i)
        {
            auto vec = kCardVector[i];
            if(vec.getIndex(tempCard)!=-1)
            {
                id = i;
            }
        }
        //目标牌的容器
        auto vec = &kCardVector[id];
        effVec->eraseObject(_effCard);
        vec->pushBack(_effCard);
        if(effVec == vec)
        {//同一个的话不需要加1
            _effCard->setCardLocalZOrder(tempCard->getLocalZOrder());
        }
        else
        {
            _effCard->setCardLocalZOrder(tempCard->getLocalZOrder() + 1);
        }
        
        _effCard->setIsOpen(true);
        //容器id
        _effCard->setColNum(id);
        //容器位置
        auto posid = _effCard->getPosId();
        _effCard->setPosId(1);
        //算一下有几张明牌
        int openNum = 0;
        for(int i = 0;i<vec->size();++i)
        {
            auto card = vec->at(i);
            if(card->getIsOpen())
            {
                openNum++;
            }
        }
        auto dy = effVec == vec?36:0;
        if(dy != 0)
        {
            
            dy+=0;
        }
        
        
        //移动
        if(effSprite)
        {
            _effCard->playDaoJuEff(tempCard->getPosition() - Vec2(0,OffsetOpen - dy),effVec,posid,effSprite->getPosition());
        }
        else
        {
            _effCard->playDaoJuEff(tempCard->getPosition() - Vec2(0,OffsetOpen - dy),effVec,posid,Vec2(0,0));
        }
        
    }
    else if(num == 13)
    {
        for(int i = 0;i<7;++i)
        {
            auto vec = &kCardVector[i];
            if(vec->empty())
            {
                auto sp = kSprite[i];
                //交换容器
                effVec->eraseObject(_effCard);
                
                vec->pushBack(_effCard);
                //层级
                _effCard->setCardLocalZOrder(25);
                //翻开
                _effCard->setIsOpen(true);
                //容器id
                _effCard->setColNum(i);
                //容器位置
                auto posid = _effCard->getPosId();
                _effCard->setPosId(1);
                
                //移动
                if(effSprite)
                {
                    _effCard->playDaoJuEff(sp->getPosition(),effVec,posid,effSprite->getPosition());
                }
                else
                {
                    _effCard->playDaoJuEff(sp->getPosition(),effVec,posid,Vec2(0,0));
                }
                break;
            }
        }
    }
    return true;
}

Vec2 SpriteManager::getMagicPoi()
{
    auto poi = _effCard->getPosition();
    auto rect = _effCard->getBoundingBox();
    
    poi.x -= rect.size.width;
    poi.y += rect.size.height*0.5f;
    
    return poi;
}


bool SpriteManager::isCardVec(int idx)
{
    bool is = false;
    int a = idx + 1;
    if(a == 7)
    {
        return false;
    }
    for(int i = a;i < 7;++i)
    {
        auto vec = kCardVector[i];
        if(!vec.empty())
        {//有牌
            is = true;
        }
    }
    
    return is;
}

bool SpriteManager::isCardVec()
{
    bool isK = false;
    bool isWait = false;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        if(!vec.empty())
        {
            for(auto card:vec)
            {//判断是否翻开
                auto isOpen = card->getIsOpen();
                if(!isOpen)
                {//有盖住的牌
                    isK = true;
                }
            }
        }
    }
    //发牌区也有牌
    if(!waitCardVector.empty())
    {
        isWait = true;
    }
    if(!waitShowCardVector.empty())
    {
        isWait = true;
    }
    return isK&&isWait;
}

void SpriteManager::endAniShouPai()
{
    vector<int> idxVec;
    for (int i = 0; i < 52; i++)
    {
        idxVec.push_back(i);
    }
    for(int i = 0,j = 0; i < 52; i++)
    {
        if(i%13==0&&i!=0)
        {
            j++;
        }
        auto cardId = idxVec[i];
        auto cardSprite = CardSprite::createCardSprite(cardId, i, true);
        cardSprite->setPosition(aSprite[j]->getPosition());
        cardSprite->openCardToPos(aSprite[j]->getPosition(),0);
        cardSprite->setColNum(j);
        panel_game->addChild(cardSprite);
        aCardVector[j].pushBack(cardSprite);
    }

}

void SpriteManager::endAniFuWei()
{
    for(int i =0;i<4;++i)
    {
        auto vec = aCardVector[i];
        int zo = 1;
        for(auto card:vec)
        {
            card->setCardLocalZOrder(zo);
            zo++;
            card->setPosition(aSprite[i]->getPosition());
        }
    }
}

//----------结束动画
const float moveTime = 0.4;
const float endTime = 0.15;
void SpriteManager::pokerEndAni1()
{//分三组；
    //52张牌分成3份
    Vector<CardSprite*> tempVec1;
    Vector<CardSprite*> tempVec2;
    Vector<CardSprite*> tempVec3;
    int a=0,b=0,c=0;
    for(int i = 0; i<4;++i)
    {
        auto vec = aCardVector[i];
        std::random_shuffle(vec.begin(), vec.end(), myrandom);
        for(auto card:vec)
        {
            a++;
            if(a < 18)
            {
                card->setLocalZOrder(a);
                tempVec1.pushBack(card);
            }
            else if(b < 17)
            {
                card->setLocalZOrder(b);
                b++;
                tempVec2.pushBack(card);
            }
            else if(c < 18)
            {
                card->setLocalZOrder(c);
                c++;
                tempVec3.pushBack(card);
            }
        }
    }
    float dt = 0;
    float dt1 = 0.05;
    float dt2 = 0.2;
    float detime = 0.05;
    float dedt = 0.01;
    float dedt1 = 0.02;
    //每两张 延时一次
    int deNum = 0;
    for(auto card : tempVec1)
    {
        auto to = MoveTo::create(0.2f, endAni1_1Poi);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to2 = MoveTo::create(moveTime, endAni1_2Poi);
        auto to3 = MoveTo::create(moveTime, endAni1_3Poi);
        auto to4 = MoveTo::create(moveTime, endAni1_1Poi);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(dt1);
        auto seq1 = Sequence::create(to2,delay1,to3,delay3,to4,delay2, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        
        if(deNum%3 == 0)
        {
            dt+=dedt;
            dt1 += dedt1;
        }
        deNum++;
        
        
    }
    dt = 0;
    dt1 = 0.05;
    deNum = 0;
    for(auto card : tempVec2)
    {
        auto to = MoveTo::create(0.2f, endAni1_2Poi);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to2 = MoveTo::create(moveTime, endAni1_3Poi);
        auto to3 = MoveTo::create(moveTime, endAni1_1Poi);
        auto to4 = MoveTo::create(moveTime, endAni1_2Poi);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(dt1);
        auto seq1 = Sequence::create(to2,delay1,to3,delay3,to4,delay2, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%3 == 0)
        {
            dt+=dedt;
            dt1 += dedt1;
        }
        deNum++;
    }
    dt = 0;
    dt1 = 0.05;
    deNum = 0;
    for(auto card : tempVec3)
    {
        auto to = MoveTo::create(0.2f, endAni1_3Poi);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to2 = MoveTo::create(moveTime, endAni1_1Poi);
        auto to3 = MoveTo::create(moveTime, endAni1_2Poi);
        auto to4 = MoveTo::create(moveTime, endAni1_3Poi);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(dt1);
        auto seq1 = Sequence::create(to2,delay1,to3,delay3,to4,delay2, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%3 == 0)
        {
            dt+=dedt;
            dt1 += dedt1;
        }
        deNum++;
        
    }
}
const float moveTime2 = 0.4;
void SpriteManager::pokerEndAni2()
{
    endAni2Vec;
    //52张牌分成6份
    Vector<CardSprite*> tempVec1;
    Vector<CardSprite*> tempVec2;
    Vector<CardSprite*> tempVec3;
    Vector<CardSprite*> tempVec4;
    Vector<CardSprite*> tempVec5;
    Vector<CardSprite*> tempVec6;
    Vector<CardSprite*> tempVec7;
    Vector<CardSprite*> tempVec8;
    int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;
    for(int i = 0; i<4;++i)
    {
        auto vec = aCardVector[i];
        std::random_shuffle(vec.begin(), vec.end(), myrandom);
        for(auto card:vec)
        {
            a++;
            if(a < 7)
            {
                card->setLocalZOrder(10 - a);
                tempVec1.pushBack(card);
            }
            else if(b < 6)
            {
                card->setLocalZOrder(10 - b);
                b++;
                tempVec2.pushBack(card);
            }
            else if(c < 6)
            {
                card->setLocalZOrder(10 - c);
                c++;
                tempVec3.pushBack(card);
            }
            else if(d < 6)
            {
                card->setLocalZOrder(10 - d);
                d++;
                tempVec4.pushBack(card);
            }
            else if(e < 6)
            {
                card->setLocalZOrder(10 - e);
                e++;
                tempVec5.pushBack(card);
            }
            else if(f < 6)
            {
                card->setLocalZOrder(10 - f);
                f++;
                tempVec6.pushBack(card);
            }
            else if(g < 8)
            {
                card->setLocalZOrder(10 - g);
                g++;
                tempVec7.pushBack(card);
            }
            else if(h < 8)
            {
                card->setLocalZOrder(10 - h);
                h++;
                tempVec8.pushBack(card);
            }
        }
    }
    float dt = 0;
    float dt2 = 0.2;
    float dt3 = 0.04;
    float detime = 0;
    for(auto card : tempVec8)
    {
        auto to = MoveTo::create(0.2f, endAni2Vec[7]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime2, endAni2Vec[2]);
        
        auto to2 = MoveTo::create(moveTime2, endAni2Vec[3]);
        auto to3 = MoveTo::create(moveTime2, endAni2Vec[4]);
        auto to4 = MoveTo::create(moveTime2, endAni2Vec[5]);
        auto to5 = MoveTo::create(moveTime2, endAni2Vec[0]);
        auto to6 = MoveTo::create(moveTime2, endAni2Vec[1]);
        auto to7 = MoveTo::create(moveTime2, endAni2Vec[2]);
        
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to2,delay1,to3,delay2,to4,delay3,to5,delay4,to6,delay5,to7,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,to1,rep, NULL);//
        card->runAction(seq);
        dt+=dt3;
    }
    dt = 0;
    for(auto card : tempVec7)
    {
        auto to = MoveTo::create(0.2f, endAni2Vec[6]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime2, endAni2Vec[3]);
        
        auto to2 = MoveTo::create(moveTime2, endAni2Vec[4]);
        auto to3 = MoveTo::create(moveTime2, endAni2Vec[5]);
        auto to4 = MoveTo::create(moveTime2, endAni2Vec[0]);
        auto to5 = MoveTo::create(moveTime2, endAni2Vec[1]);
        auto to6 = MoveTo::create(moveTime2, endAni2Vec[2]);
        auto to7 = MoveTo::create(moveTime2, endAni2Vec[3]);
        
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to2,delay1,to3,delay2,to4,delay3,to5,delay4,to6,delay5,to7,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,to1,rep, NULL);//
        card->runAction(seq);
        dt+=dt3;
    }
    dt = 0;
    for(auto card : tempVec1)
    {
        auto to = MoveTo::create(0.2f, endAni2Vec[0]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime2, endAni2Vec[1]);
        auto to2 = MoveTo::create(moveTime2, endAni2Vec[2]);
        auto to3 = MoveTo::create(moveTime2, endAni2Vec[3]);
        auto to4 = MoveTo::create(moveTime2, endAni2Vec[4]);
        auto to5 = MoveTo::create(moveTime2, endAni2Vec[5]);
        auto to6 = MoveTo::create(moveTime2, endAni2Vec[0]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        dt+=dt3;
    }
    dt = 0;
    for(auto card : tempVec2)
    {
        auto to = MoveTo::create(0.2f, endAni2Vec[1]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime2, endAni2Vec[2]);
        auto to2 = MoveTo::create(moveTime2, endAni2Vec[3]);
        auto to3 = MoveTo::create(moveTime2, endAni2Vec[4]);
        auto to4 = MoveTo::create(moveTime2, endAni2Vec[5]);
        auto to5 = MoveTo::create(moveTime2, endAni2Vec[0]);
        auto to6 = MoveTo::create(moveTime2, endAni2Vec[1]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        dt+=dt3;
    }
    dt = 0;
    for(auto card : tempVec3)
    {
        auto to = MoveTo::create(0.2f, endAni2Vec[2]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime2, endAni2Vec[3]);
        auto to2 = MoveTo::create(moveTime2, endAni2Vec[4]);
        auto to3 = MoveTo::create(moveTime2, endAni2Vec[5]);
        auto to4 = MoveTo::create(moveTime2, endAni2Vec[0]);
        auto to5 = MoveTo::create(moveTime2, endAni2Vec[1]);
        auto to6 = MoveTo::create(moveTime2, endAni2Vec[2]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        dt+=dt3;
    }
    dt = 0;
    for(auto card : tempVec4)
    {
        auto to = MoveTo::create(0.2f, endAni2Vec[3]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime2, endAni2Vec[4]);
        auto to2 = MoveTo::create(moveTime2, endAni2Vec[5]);
        auto to3 = MoveTo::create(moveTime2, endAni2Vec[0]);
        auto to4 = MoveTo::create(moveTime2, endAni2Vec[1]);
        auto to5 = MoveTo::create(moveTime2, endAni2Vec[2]);
        auto to6 = MoveTo::create(moveTime2, endAni2Vec[3]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        dt+=dt3;
    }
    dt = 0;
    for(auto card : tempVec5)
    {
        auto to = MoveTo::create(0.2f, endAni2Vec[4]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime2, endAni2Vec[5]);
        auto to2 = MoveTo::create(moveTime2, endAni2Vec[0]);
        auto to3 = MoveTo::create(moveTime2, endAni2Vec[1]);
        auto to4 = MoveTo::create(moveTime2, endAni2Vec[2]);
        auto to5 = MoveTo::create(moveTime2, endAni2Vec[3]);
        auto to6 = MoveTo::create(moveTime2, endAni2Vec[4]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        dt+=dt3;
    }
    dt = 0;
    for(auto card : tempVec6)
    {
        auto to = MoveTo::create(0.2f, endAni2Vec[5]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime2, endAni2Vec[0]);
        auto to2 = MoveTo::create(moveTime2, endAni2Vec[1]);
        auto to3 = MoveTo::create(moveTime2, endAni2Vec[2]);
        auto to4 = MoveTo::create(moveTime2, endAni2Vec[3]);
        auto to5 = MoveTo::create(moveTime2, endAni2Vec[4]);
        auto to6 = MoveTo::create(moveTime2, endAni2Vec[5]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        dt+=dt3;
    }
}
const float moveTime3 = 0.35;
void SpriteManager::pokerEndAni3()
{
    endAni3Vec;
    //52张牌分成4份
    Vector<CardSprite*> tempVec1;
    Vector<CardSprite*> tempVec2;
    Vector<CardSprite*> tempVec3;
    Vector<CardSprite*> tempVec4;
    int a=0,b=0,c=0,d=0;
    for(int i = 0; i<4;++i)
    {
        auto vec = aCardVector[i];
        std::random_shuffle(vec.begin(), vec.end(), myrandom);
        for(auto card:vec)
        {
            a++;
            if(a < 14)
            {
                card->setLocalZOrder(a);
                tempVec1.pushBack(card);
            }
            else if(b < 13)
            {
                card->setLocalZOrder(b);
                b++;
                tempVec2.pushBack(card);
            }
            else if(c < 13)
            {
                card->setLocalZOrder(c);
                c++;
                tempVec3.pushBack(card);
            }
            else if(d < 13)
            {
                card->setLocalZOrder(d);
                d++;
                tempVec4.pushBack(card);
            }
        }
    }
    
    float dt = 0;
    float dedt = 0.08;
    float dt2 = 0.3;
    float detime = 0.2;
    int deNum = 0;
    for(auto card : tempVec1)
    {
        auto to = MoveTo::create(0.2f, endAni3Vec[0]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        
        auto to1 = MoveTo::create(moveTime3, endAni3Vec[1]);
        auto to2 = MoveTo::create(moveTime3, endAni3Vec[2]);
        auto to3 = MoveTo::create(moveTime3, endAni3Vec[3]);
        auto to4 = MoveTo::create(moveTime3, endAni3Vec[2]);
        auto to5 = MoveTo::create(moveTime3, endAni3Vec[1]);
        auto to6 = MoveTo::create(moveTime3, endAni3Vec[0]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%2 == 0)
        {
            
        }
        dt+=dedt;
        deNum++;
    }
    dt=0;
    deNum = 0;
    for(auto card : tempVec2)
    {
        auto to = MoveTo::create(0.2f, endAni3Vec[1]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime3, endAni3Vec[2]);
        auto to2 = MoveTo::create(moveTime3, endAni3Vec[3]);
        auto to3 = MoveTo::create(moveTime3, endAni3Vec[2]);
        auto to4 = MoveTo::create(moveTime3, endAni3Vec[1]);
        auto to5 = MoveTo::create(moveTime3, endAni3Vec[0]);
        auto to6 = MoveTo::create(moveTime3, endAni3Vec[1]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%2 == 0)
        {
            
        }
        dt+=dedt;
        deNum++;
    }
    dt=0;
    deNum = 0;
    for(auto card : tempVec3)
    {
        auto to = MoveTo::create(0.2f, endAni3Vec[2]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime3, endAni3Vec[1]);
        auto to2 = MoveTo::create(moveTime3, endAni3Vec[0]);
        auto to3 = MoveTo::create(moveTime3, endAni3Vec[1]);
        auto to4 = MoveTo::create(moveTime3, endAni3Vec[2]);
        auto to5 = MoveTo::create(moveTime3, endAni3Vec[3]);
        auto to6 = MoveTo::create(moveTime3, endAni3Vec[2]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%2 == 0)
        {
            
        }
        dt+=dedt;
        deNum++;
    }
    dt=0;
    deNum = 0;
    for(auto card : tempVec4)
    {
        auto to = MoveTo::create(0.2f, endAni3Vec[3]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime3, endAni3Vec[2]);
        auto to2 = MoveTo::create(moveTime3, endAni3Vec[1]);
        auto to3 = MoveTo::create(moveTime3, endAni3Vec[0]);
        auto to4 = MoveTo::create(moveTime3, endAni3Vec[1]);
        auto to5 = MoveTo::create(moveTime3, endAni3Vec[2]);
        auto to6 = MoveTo::create(moveTime3, endAni3Vec[3]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        auto delay5 = DelayTime::create(detime);
        auto delay6 = DelayTime::create(detime);
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4,to5,delay5,to6,delay6, NULL);
        auto rep = Repeat::create(seq1,5);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%2 == 0)
        {
            
        }
        dt+=dedt;
        deNum++;
    }
}

void SpriteManager::pokerEndAni4()
{
    endAni4Vec;
    auto zhongxin = panel_game->getPosition();
    auto topY = aSprite[0]->getPosition().y;
    float dt = 0;
    float dt2 = 0;
    
    for(int i = 0; i<4;++i)
    {
        auto vec = aCardVector[i];
        
        dt = 0;
        for(int j = vec.size() - 1;j >= 0;--j)
        {
            auto card = vec.at(j);
            Vector<FiniteTimeAction*> actionVec;
            auto y = topY - endAni4Vec[0].y;
            auto y1 = 0 - endAni4Vec[0].y;
            float downtime = 1;
            float uptime = 0.5;
            //平移
            auto by = MoveBy::create(4.2, Vec2(DATA_M->getIsLeftModel()?-1200:1200,0));
            auto delay = DelayTime::create(dt + dt2);
            for(int j = 0;j<5;++j)
            {
                //下坠
                auto bydown = MoveBy::create(downtime,Vec2(0,-y));
                auto easeIn = EaseSineIn::create(bydown);
                //弹起
                auto byup = MoveBy::create(uptime,Vec2(0,y1));
                auto easeOut = EaseSineOut::create(byup);
                y = y1;
                y1/=1.5;
                downtime/=1.5;
                uptime/=1.5;
                actionVec.pushBack(easeIn);
                actionVec.pushBack(easeOut);
            }
            auto seq = Sequence::create(actionVec);
            auto spawn = Spawn::create(by,seq, NULL);
            auto seq1 = Sequence::create(delay,spawn, NULL);
            card->runAction(seq1);
            dt+=0.6f;
        }
        dt2 += 0.25f;
    }
}
const float moveTime5 = 0.4;
void SpriteManager::pokerEndAni5()
{
    //52张牌分成4份
    Vector<CardSprite*> tempVec1;
    Vector<CardSprite*> tempVec2;
    Vector<CardSprite*> tempVec3;
    Vector<CardSprite*> tempVec4;
    int a=0,b=0,c=0,d=0;
    for(int i = 0; i<4;++i)
    {
        auto vec = aCardVector[i];
        std::random_shuffle(vec.begin(), vec.end(), myrandom);
        for(auto card:vec)
        {
            a++;
            if(a < 14)
            {
                card->setLocalZOrder(a);
                tempVec1.pushBack(card);
            }
            else if(b < 13)
            {
                card->setLocalZOrder(b);
                b++;
                tempVec2.pushBack(card);
            }
            else if(c < 13)
            {
                card->setLocalZOrder(c);
                c++;
                tempVec3.pushBack(card);
            }
            else if(d < 13)
            {
                card->setLocalZOrder(d);
                d++;
                tempVec4.pushBack(card);
            }
        }
    }
    
    float dt=0;
    float dedt = 0.04;
    float dt2 = 0.2;
    float detime = 0.2;
    int deNum = 0;
    for(auto card : tempVec1)
    {
        auto to = MoveTo::create(0.2f, endAni5Vec[0]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime5, endAni5Vec[1]);
        auto to2 = MoveTo::create(moveTime5, endAni5Vec[2]);
        auto to3 = MoveTo::create(moveTime5, endAni5Vec[3]);
        auto to4 = MoveTo::create(moveTime5, endAni5Vec[0]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4, NULL);
        auto rep = Repeat::create(seq1,7);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%2 == 0)
        {
            dt+=dedt;
        }
        deNum++;
    }
    dt=0;
    deNum = 0;
    for(auto card : tempVec2)
    {
        auto to = MoveTo::create(0.2f, endAni5Vec[1]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime5, endAni5Vec[2]);
        auto to2 = MoveTo::create(moveTime5, endAni5Vec[3]);
        auto to3 = MoveTo::create(moveTime5, endAni5Vec[0]);
        auto to4 = MoveTo::create(moveTime5, endAni5Vec[1]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4, NULL);
        auto rep = Repeat::create(seq1,7);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%2 == 0)
        {
            dt+=dedt;
        }
        deNum++;
    }
    dt=0;
    deNum = 0;
    for(auto card : tempVec3)
    {
        auto to = MoveTo::create(0.2f, endAni5Vec[2]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime5, endAni5Vec[3]);
        auto to2 = MoveTo::create(moveTime5, endAni5Vec[0]);
        auto to3 = MoveTo::create(moveTime5, endAni5Vec[1]);
        auto to4 = MoveTo::create(moveTime5, endAni5Vec[2]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4, NULL);
        auto rep = Repeat::create(seq1,7);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%2 == 0)
        {
            dt+=dedt;
        }
        deNum++;
    }
    dt=0;
    deNum = 0;
    for(auto card : tempVec4)
    {
        auto to = MoveTo::create(0.2f, endAni5Vec[3]);
        auto delay = DelayTime::create(dt);
        auto delay0 = DelayTime::create(dt2);
        auto to1 = MoveTo::create(moveTime5, endAni5Vec[0]);
        auto to2 = MoveTo::create(moveTime5, endAni5Vec[1]);
        auto to3 = MoveTo::create(moveTime5, endAni5Vec[2]);
        auto to4 = MoveTo::create(moveTime5, endAni5Vec[3]);
        auto delay1 = DelayTime::create(detime);
        auto delay2 = DelayTime::create(detime);
        auto delay3 = DelayTime::create(detime);
        auto delay4 = DelayTime::create(detime);
        
        auto seq1 = Sequence::create(to1,delay1,to2,delay2,to3,delay3,to4,delay4, NULL);
        auto rep = Repeat::create(seq1,7);
        auto seq = Sequence::create(to,delay,delay0,rep, NULL);
        card->runAction(seq);
        if(deNum%2 == 0)
        {
            dt+=dedt;
        }
        deNum++;
    }
}

void SpriteManager::pokerEndAni6()
{
    endAni6Vec;
    auto zhongxin = panel_game->getPosition();
    auto topY = aSprite[0]->getPosition().y;
    float dt = 0;
    float dt2 = 0;
    float a1 = 1.5f;
    float a2 = 0.75f;
    auto a3 = 4.2f * a1;
    float a4 = 0.2f;
    for(int i = 0; i<4;++i)
    {
        auto vec = aCardVector[i];
        dt = 0;
        for(int j = vec.size() - 1;j >= 0;--j)
        {
            auto card = vec.at(j);
            card->setLocalZOrder(card->getLocalZOrder() + 100-i+j);
            Vector<FiniteTimeAction*> actionVec;
            auto y = topY - endAni6Vec[0].y;
            auto y1 = 50 - endAni6Vec[0].y;
            float downtime = a1;
            float uptime = a2;
            //平移
            auto by = MoveBy::create(a3 - a4*i, Vec2(DATA_M->getIsLeftModel()?-1200:1200,0));
            auto delay = DelayTime::create(dt + dt2);
            for(int j = 0;j<5;++j)
            {
                //下坠
                auto bydown = MoveBy::create(downtime,Vec2(0,-y));
                auto easeIn = EaseSineIn::create(bydown);
                //弹起
                auto byup = MoveBy::create(uptime,Vec2(0,y1));
                auto easeOut = EaseSineOut::create(byup);
                y = y1;
                y1/=1.5;
                downtime/=1.5;
                uptime/=1.5;
                actionVec.pushBack(easeIn);
                actionVec.pushBack(easeOut);
            }
            auto seq = Sequence::create(actionVec);
            auto spawn = Spawn::create(by,seq, NULL);
            auto seq1 = Sequence::create(delay,spawn, NULL);
            card->runAction(seq1);
            dt+=0.13f;
        }
        dt2 += 0.2f;
    }
}

void SpriteManager::playEffA()
{
    SOUND_M->playEffectMusic(StringUtils::format(EffectScore.c_str(), currentMusicLevel).c_str());
    ++currentMusicLevel;
}

bool SpriteManager::isWaitCardEnd(CardSprite* card)
{
    if(!waitCardVector.empty())
    {
        if(isThreeModel)
        {
            return waitCardVector.getIndex(card) <= 2&&waitCardVector.getIndex(card)!=-1;
        }
        else
        {
            return waitCardVector.getIndex(card) == 0;
        }
    }
    return false;
}

bool SpriteManager::isNoMoveTips(bool isFanPai)
{
    clearTipsData();
    auto waitCardCanMoveFlag = false;
    for (int col = 0; col < 7; col++)
    {
        auto kCardSize = kCardVector[col].size();
        auto firstOpen = true;
        //K位置判断
        for (int i = 0; i < kCardSize;i++)
        {
            auto card = kCardVector[col].at(i);
            if (card->getIsOpen())
            {
                //直接判断是否能到A位置 能就直接结束
                if (i == kCardVector[col].size() - 1)
                {
                    int aCardCol = checkACardPos(card);
                    if (aCardCol != -1)
                    {
                        tipsMoveDatas.insert(0, MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_A, card->getColNum(), aCardCol));
                        break;
                    }
                }
                
                if (firstOpen) {
                    //判断是否可以接到其他K位置
                    int kCardCol = checkKCardPos(card);
                    if (kCardCol != -1)
                    {
                        if (kCardVector[kCardCol].size() == 0 && i == 0)
                        {
                            
                        }
                        else
                        {
                            //可以
                            tipsMoveDatas.pushBack(MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_K, card->getColNum(), kCardCol, kCardVector[col].size() - i));
                            break;
                        }
                    }
                }
                firstOpen = false;
            }
        }
    }
    
    if (waitShowCardVector.size() > 0)
    {
        auto card = waitShowCardVector.at(waitShowCardVector.size() - 1);
        int aCardCol = checkACardPos(card);
        if (aCardCol != -1)
        {
            tipsMoveDatas.insert(0, MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_A, card->getColNum(), aCardCol));
        }
        else
        {
            //判断是否可以接到其他K位置
            int kCardCol = checkKCardPos(card);
            if (kCardCol != -1)
            {
                tipsMoveDatas.pushBack(MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_K, card->getColNum(), kCardCol));
            }
        }
    }
    
    //K(最后一张牌) ->K
    for (int col = 0; col < 7; col++)
    {
        int kCardNum = kCardVector[col].size();
        //K位置判断
        if (kCardNum >= 2)
        {
            auto card_1 = kCardVector[col].at(kCardNum - 1);
            auto card_2 = kCardVector[col].at(kCardNum - 2);
            
            if (card_2->getIsOpen())
            {
                int checkACol = checkACardPos(card_2);
                int checkKCol = checkKCardPos(card_1);
                if (checkACol != -1 && checkKCol != -1)
                {
                    tipsMoveDatas.pushBack(MoveData::createMoveDataByMove(card_1->getPosId(), CARD_POS_K, card_1->getColNum(), checkKCol));
                }
            }
        }
    }
    
    for (int col = 0; col < 4; col++)
    {
        if (aCardVector[col].size() > 0)
        {
            auto card = aCardVector[col].at(aCardVector[col].size() - 1);
            int kCardCol = checkKCardPos(card);
            if (kCardCol != -1)
            {
                bool isCanMove = false;
                for (int colK = 0; colK < 7; colK++)
                {
                    int kCardNum = kCardVector[colK].size();
                    
                    //K位置判断
                    if (kCardNum > 0)
                    {
                        //置空
                        auto kCard = kCardVector[colK].at(kCardNum - 1);
                        if (card->checkKPos(kCard))
                        {
                            if (kCardNum > 1)
                            {
                                auto cardK = kCardVector[colK].at(kCardNum - 2);
                                if (!cardK->getIsOpen())
                                {
                                    //翻牌
                                    isCanMove = true;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            isCanMove = true;
                            break;
                        }
                        
                    }
                }
                if (isCanMove)
                {
                    tipsMoveDatas.pushBack(MoveData::createMoveDataByMove(card->getPosId(), CARD_POS_K, card->getColNum(), kCardCol));
                }
            }
        }
    }
    //wei jia维加斯模式 翻牌次数用尽不进入
    if(tipsMoveDatas.size() == 0&&isFanPai)
    {
        if (isThreeModel)
        {   // 三张牌检测
            int i = 0;
            for (auto it = waitCardVector.rbegin(); it != waitCardVector.rend(); ++it) {
                if ((i+1)%3 == 0 || (i==waitCardVector.size()-1)) {
                    auto card = *it;
                    if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                        waitCardCanMoveFlag = true;
                        break;
                    }
                }
                ++i;
            }
            // 检测所有
            auto is2 = SCENE_M->getGameView()->getIsFanPai2();
            if(is2)
            {
                auto endIndex = 0;
                if (!waitCardCanMoveFlag) {
                    for (int i=2; i<waitShowCardVector.size(); i+=3) {
                        auto card = waitShowCardVector.at(i);
                        if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                            waitCardCanMoveFlag = true;
                            break;
                        }
                        endIndex = i;
                    }
                }
                
                if (!waitCardCanMoveFlag) {
                    int start = (int)MAX(0, 3-waitShowCardVector.size()-endIndex);
                    if (waitCardVector.size()>=start) {
                        int i = 0;
                        for (auto it = waitCardVector.rbegin()+start; it != waitCardVector.rend(); ++it) {
                            if ((i+1)%3 == 0 || (i==waitCardVector.size()-1)) {
                                auto card = *it;
                                if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                                    waitCardCanMoveFlag = true;
                                    break;
                                }
                            }
                            ++i;
                        }
                    }
                }
            }
        }
        else { //单张牌模式直接检测所有卡牌
            for (auto card:waitCardVector) {
                if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                    waitCardCanMoveFlag = true;
                    break;
                }
            }
            auto is2 = SCENE_M->getGameView()->getIsFanPai2();
            if (!waitCardCanMoveFlag&&is2) {
                for (auto card:waitShowCardVector) {
                    if (checkACardPos(card) != -1 || checkKCardPos(card) != -1) {
                        waitCardCanMoveFlag = true;
                        break;
                    }
                }
            }
        }
    }
    else if(tipsMoveDatas.size() != 0)
    {
        waitCardCanMoveFlag = true;
    }
    
    return waitCardCanMoveFlag;
}

CardSprite* SpriteManager::findACardPoi()
{
    Vector<CardSprite*> AVec;
    for(int i = 0;i<4;++i)
    {
        auto vec = aCardVector[i];
        if(!vec.empty())
        {
            auto card = vec.at(vec.size()-1);
            AVec.pushBack(card);
        }
    }
    
    Vector<CardSprite*> KVec;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        if(!vec.empty())
        {
            auto card = vec.at(vec.size()-1);
            KVec.pushBack(card);
        }
    }
    
    vector<Vec2> cardVec;
    Vector<CardSprite*> CardVec2;
    if(!AVec.empty())
    {//上面不为空时
        if(!KVec.empty())
        {//下面也不为空
            for(auto aCard:AVec)
            {
                auto acol = (int)aCard->getColorType();
                auto anum = aCard->getNumber();
                for(auto kCard:KVec)
                {
                    auto kcol = (int)kCard->getColorType();
                    auto knum = kCard->getNumber();
                    if(knum - anum == 1&&acol == kcol)
                    {
                        cardVec.push_back(kCard->getPosition());
                        CardVec2.pushBack(kCard);
                    }
                }
            }
        }
        if(!waitShowCardVector.empty()&&CardVec2.empty())
        {//下面牌组中没有能收起来的牌了 发牌显示区第一张能不能收起
            auto kCard = waitShowCardVector.at(waitShowCardVector.size()-1);
            auto kcol = (int)kCard->getColorType();
            auto knum = kCard->getNumber();
            for(auto aCard:AVec)
            {
                auto acol = (int)aCard->getColorType();
                auto anum = aCard->getNumber();
                if(knum - anum == 1&&acol == kcol)
                {
                    cardVec.push_back(kCard->getPosition());
                    CardVec2.pushBack(kCard);
                }
            }
        }
        if(!waitCardVector.empty()&&CardVec2.empty())
        {//下面牌组中没有能收起来的牌了 发牌显示区第一张也不能收起
            cardVec.push_back(waitSprite->getPosition());
            auto kCard = waitCardVector.at(waitCardVector.size()-1);
            CardVec2.pushBack(kCard);
        }
        
    }
    else
    {//上面为空 找A
        if(!KVec.empty())
        {//下面不为空 找A
            for(auto kCard:KVec)
            {
                auto kcol = (int)kCard->getColorType();
                auto knum = kCard->getNumber();
                if(knum == 1)
                {
                    cardVec.push_back(kCard->getPosition());
                    CardVec2.pushBack(kCard);
                }
            }
        }
        
        if(!waitShowCardVector.empty()&&CardVec2.empty())
        {//下面没找到a
            auto kCard = waitShowCardVector.at(waitShowCardVector.size()-1);
            auto kcol = (int)kCard->getColorType();
            auto knum = kCard->getNumber();
            if(knum == 1)
            {
                cardVec.push_back(kCard->getPosition());
                CardVec2.pushBack(kCard);
            }
        }
        if(!waitCardVector.empty()&&CardVec2.empty())
        {//场上明牌没有A
            cardVec.push_back(waitSprite->getPosition());
            auto kCard = waitCardVector.at(waitCardVector.size()-1);
            CardVec2.pushBack(kCard);
        }
    }
    if(!CardVec2.empty())
    {//有位置
        return CardVec2.at(0);//cardVec.at(0);
    }
    return nullptr;//Vec2::ZERO;
}

void SpriteManager::levelAutoShouPai(std::function<void()> cb)
{
    float time = 0.2;
    int max = -1;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        if(max <= vec.size()-1)
        {
            max = vec.size();
        }
    }
    int k = 0;
    bool is = false;
    for(int i = 0;i<7;++i)
    {
        auto vec = kCardVector[i];
        for(int j = vec.size()-1;j>=0;--j,++k)
        {
            auto card = vec.at(j);
            //card->setVisible(false);
            //渐隐
            auto fadeOut = FadeOut::create(time);
        
            //auto by = MoveBy::create(time, Vec2(0,100));
            if(k == max)
            {
                is = true;
                auto func = CallFunc::create(cb);
                auto seq = Sequence::create(fadeOut,func, NULL);
                card->getShaderS()->runAction(seq);
            }
            else
            {
                card->getShaderS()->runAction(fadeOut);
            }
            
            //time+= 0.01;
        }
    }
    time = 0.2;
    for(int i = 0;i<4;++i)
    {
        auto vec = aCardVector[i];
        for(auto card:vec)
        {
            //渐隐
            //card->setVisible(false);
            auto fadeOut = FadeOut::create(time);
            
            auto by = MoveBy::create(time, Vec2(0,100));
            if(max == 0)
            {
                max = 100;
                auto func = CallFunc::create(cb);
                auto seq = Sequence::create(fadeOut,func, NULL);
                card->getShaderS()->runAction(seq);
            }
            else
            {
                card->getShaderS()->runAction(fadeOut);
            }
            
        }
    }
    
    for(auto card:waitShowCardVector)
    {
        auto fadeOut = FadeOut::create(time);
        auto by = MoveBy::create(time, Vec2(0,100));
        //card->setVisible(false);
        card->getShaderS()->runAction(fadeOut);
    }
    
    for(auto card:waitCardVector)
    {
        auto by = MoveBy::create(time, Vec2(0,100));
        auto fadeOut = FadeOut::create(time);
        card->setVisible(false);
        card->getShaderS()->runAction(fadeOut);
    }
    
}

void SpriteManager::pokerStartAni1()
{
    auto startPoi = waitSprite->getPosition();
    
    Vec2 beginPos = startNode->getPosition();               //panel_game->convertToNodeSpace(Vec2(winSize.width/2, -200));
    vector<Vec2> endPosions = getCardInitPositions();
    vector<Vec2> endPosions2 = getCardInitPositions2();
    int endPosIndex = 0;
    int idx = 1;
    //延时
    float delayTime = 0.05;
    for (int col = 0; col < 7; col++)
    {
        Vec2 tempPoi = Vec2::ZERO;
        for (int row = 0; row < 7; row++)
        {
            if (col >= row)
            {
                int cardId = SPRITE_M->getCardId();
                if (cardId < 0)
                {
                    continue;
                }
                auto cardSprite = CardSprite::createCardSprite(cardId, col==row?idx-1:idx++, col==row);
                cardSprite->setPosId(CARD_POS_K);
                cardSprite->setPosition(beginPos);
                cardSprite->setCardLocalZOrder((int)kCardVector[col].size() + 1 + TotalWatiCardNum);
                cardSprite->setVisible(false);
                
                cardSprite->setColNum(col);
                panel_game->addChild(cardSprite);
                kCardVector[col].pushBack(cardSprite);
                
                Point endPos = endPosions[endPosIndex ++ ];
                auto endPos2 = endPosions2[6-col];
                if(tempPoi == Vec2::ZERO)
                {
                    tempPoi = endPos;
                }
                //测试 加个延时
                auto delay = DelayTime::create(0 + (6-col)*(0.3));
                auto delay2 = DelayTime::create(0.05*(6-row));
                //移动到指定位置，
                auto moveTo = MoveTo::create(0.3, endPos2);
                //旋转360度
                auto rota = RotateBy::create(0.3, 360);
                //同步
                auto spa = Spawn::create(moveTo,rota, NULL);
                
                auto show = Show::create();
                
                if(row != col)
                {//随后的牌顺序出现
                    auto moveTo2 = MoveTo::create(0.1, endPos);
                    
                        auto seq = Sequence::create(delay,delay2,show,spa,moveTo2, NULL);
                        cardSprite->runAction(seq);
                    
                }
                else
                {
                    if(col == 0&&row == 0)
                    {
                        auto func = CallFunc::create([this](){
                            initWaitCard();
                        });
                        auto seq = Sequence::create(delay,delay2,show,spa,func, NULL);
                        cardSprite->runAction(seq);
                    }
                    else
                    {
                        auto seq = Sequence::create(delay,delay2,show,spa, NULL);
                        cardSprite->runAction(seq);
                    }
                }
                
            }
        }
    }
    
    if(!isChongKai)
    {//是新开
        updateAgainVec();
    }
    
//    for (int num = 0; num < TotalWatiCardNum; num++)
//    {
//        Point endPos = getWaitCardPos(num);
//        //Point beginPos = endPos+Point(DATA_M->getIsLeftModel()?-width:width, 00);
//        int cardId = SPRITE_M->getCardId();
//        if (cardId < 0)
//        {
//            continue;
//        }
//        auto cardSprite = CardSprite::createCardSprite(cardId);
//        cardSprite->setRotation(WaitPokerOffset[UIUtils::clamp(num, 0, 7)].z);
//        auto s = UIUtils::clamp(num, 0, 8);
//        cardSprite->getShaderS()->setColor(WaitPokerColor[s]);
//        cardSprite->setPosition(startPoi);
//        cardSprite->setPosId(CARD_POS_WAIT);
//        cardSprite->setCardLocalZOrder(num);
//        //cardSprite->setRotation(angle);
//        panel_game->addChild(cardSprite);
//        waitCardVector.pushBack(cardSprite);
//    }
}

void SpriteManager::pokerStartAni2()
{
    auto startPoi = waitSprite->getPosition();
    
    Vec2 beginPos = startNode->getPosition();               //panel_game->convertToNodeSpace(Vec2(winSize.width/2, -200));
    vector<Vec2> endPosions = getCardInitPositions();
    vector<Vec2> endPosions2 = getCardInitPositions2();
    int endPosIndex = 0;
    int idx = 1;
    //延时
    float delayTime = 0.05;
    for (int col = 0; col < 7; col++)
    {
        Vec2 tempPoi = Vec2::ZERO;
        for (int row = 0; row < 7; row++)
        {
            if (col >= row)
            {
                int cardId = SPRITE_M->getCardId();
                if (cardId < 0)
                {
                    continue;
                }
                auto cardSprite = CardSprite::createCardSprite(cardId, col==row?idx-1:idx++, col==row);
                cardSprite->setPosId(CARD_POS_K);
                cardSprite->setPosition(beginPos);
                cardSprite->setCardLocalZOrder((int)kCardVector[col].size() + 1 + TotalWatiCardNum);
                cardSprite->setVisible(false);
                
                cardSprite->setColNum(col);
                panel_game->addChild(cardSprite);
                kCardVector[col].pushBack(cardSprite);
                
                Point endPos = endPosions[endPosIndex ++ ];
                auto endPos2 = endPosions2[6-col];
                if(tempPoi == Vec2::ZERO)
                {
                    tempPoi = endPos;
                }
                //测试 加个延时
                auto delay = DelayTime::create(0 + (col)*(0.3));
                auto delay2 = DelayTime::create(0.05*(6-row));
                //移动到指定位置，
                auto moveTo = MoveTo::create(0.3, endPos2);
                //旋转360度
                auto rota = RotateBy::create(0.3, 360);
                //同步
                auto spa = Spawn::create(moveTo,rota, NULL);
                
                auto show = Show::create();
                
                if(row != col)
                {//随后的牌顺序出现
                    auto moveTo2 = MoveTo::create(0.1, endPos);
                    if(col == 6&&row == 0)
                    {
                        auto func = CallFunc::create([this](){
                            initWaitCard();
                        });
                        auto seq = Sequence::create(delay,delay2,show,spa,moveTo2,func, NULL);
                        cardSprite->runAction(seq);
                    }
                    else
                    {
                        auto seq = Sequence::create(delay,delay2,show,spa,moveTo2, NULL);
                        cardSprite->runAction(seq);
                    }
                }
                else
                {
                    auto seq = Sequence::create(delay,delay2,show,spa, NULL);
                    cardSprite->runAction(seq);
                }
            }
        }
    }
    if(!isChongKai)
    {//是新开
        updateAgainVec();
    }
}

const float TeachMoveTime = 0.5f;
// 开启教学模式
void SpriteManager::setTeachBureau()
{
    
    //changeGameBG(18);
    isOpenEffective = false; // 不开启辅助
    isThreeModel = false;
    clearAllData();
    Vec2 beginPos = startNode->getPosition();               //panel_game->convertToNodeSpace(Vec2(winSize.width/2, -200));
    panel_game->runAction(Sequence::create(DelayTime::create(TeachMoveTime), CallFunc::create([this](){
        //通知游戏界面可以开始
        noticeGameStart();
    }), NULL));
    for (int i=0; i<4; i++) {
        auto pokerAData = TeachManager::getInstance()->getPokerData(StringUtils::format("pokerA%d", i));
        const auto& pokerArray = (*pokerAData).GetArray();
        for (int j=0; j<pokerArray.Size(); j++) {
            string data = pokerArray[j].GetString();
            vector<string> elems;
            UIUtils::split(data, '_', elems);
            bool isBack = elems.size()==3;
            int suit = UIUtils::stoii(elems[0]);
            int value = UIUtils::stoii(elems[1]);
            int num = suit*13+value;
            auto cardSprite = CardSprite::createCardSprite(num, j, false);
            cardSprite->setIsOpen(!isBack);
            cardSprite->setIsTempOpen(!isBack);
            cardSprite->setPosId(CARD_POS_A);
            cardSprite->setPosition(beginPos);
            cardSprite->setCardLocalZOrder((int)aCardVector[i].size());
//            cardSprite->setVisible(false);
            
            cardSprite->setColNum(i);
            panel_game->addChild(cardSprite);
            aCardVector[i].pushBack(cardSprite);
            cardSprite->initCardNum();
            auto endPos = getACardPosByIndex(i);
            cardSprite->runAction(MoveTo::create(TeachMoveTime, endPos));
        }
    }
    
    for (int i=0; i<7; i++) {
        auto pokerKData = TeachManager::getInstance()->getPokerData(StringUtils::format("pokerK%d", i));
        const auto& pokerArray = (*pokerKData).GetArray();
        for (int j=0; j<pokerArray.Size(); j++) {
            string data = pokerArray[j].GetString();
            vector<string> elems;
            UIUtils::split(data, '_', elems);
            bool isBack = elems.size()==3;
            int suit = UIUtils::stoii(elems[0]);
            int value = UIUtils::stoii(elems[1]);
            int num = suit*13+value;
            auto cardSprite = CardSprite::createCardSprite(num, j, false);
            cardSprite->setIsOpen(!isBack);
            cardSprite->setIsTempOpen(!isBack);
            cardSprite->setPosId(CARD_POS_K);
            cardSprite->setPosition(beginPos);
            cardSprite->setCardLocalZOrder((int)kCardVector[i].size() + 1 + TotalWatiCardNum);
//            cardSprite->setVisible(false);
            
            cardSprite->setColNum(i);
            panel_game->addChild(cardSprite);
            kCardVector[i].pushBack(cardSprite);
            cardSprite->initCardNum();
            auto endPos = getKCardPosByIndexAndCardVector(i,j);
            cardSprite->runAction(MoveTo::create(TeachMoveTime, endPos));
        }
    }
    
    auto pokerWData = TeachManager::getInstance()->getPokerData("pokerW");
    const auto& pokerArray = (*pokerWData).GetArray();
    for (int j=0; j<pokerArray.Size(); j++) {
        string data = pokerArray[j].GetString();
        vector<string> elems;
        UIUtils::split(data, '_', elems);
        bool isBack = elems.size()==3;
        int suit = UIUtils::stoii(elems[0]);
        int value = UIUtils::stoii(elems[1]);
        int num = suit*13+value;
        auto cardSprite = CardSprite::createCardSprite(num, j, false);
        cardSprite->setIsOpen(false);
        cardSprite->setIsTempOpen(false);
        cardSprite->setPosId(CARD_POS_WAIT);
        cardSprite->setPosition(beginPos);
        cardSprite->setCardLocalZOrder((int)waitCardVector.size() + 1);
//        cardSprite->setVisible(false);
        
        cardSprite->setColNum((int)waitCardVector.size());
        panel_game->addChild(cardSprite);
        waitCardVector.pushBack(cardSprite);
        cardSprite->initCardNum();
        auto endPos = getWaitCardPos(j);
        cardSprite->runAction(MoveTo::create(TeachMoveTime, endPos));
    }
    
    auto pokerWSData = TeachManager::getInstance()->getPokerData("pokerWS");
    const auto& pokerWSArray = (*pokerWSData).GetArray();
    for (int j=0; j<pokerWSArray.Size(); j++) {
        string data = pokerWSArray[j].GetString();
        vector<string> elems;
        UIUtils::split(data, '_', elems);
        bool isBack = elems.size()==3;
        int suit = UIUtils::stoii(elems[0]);
        int value = UIUtils::stoii(elems[1]);
        int num = suit*13+value;
        auto cardSprite = CardSprite::createCardSprite(num, j, false);
        cardSprite->setIsOpen(true);
        cardSprite->setPosId(CARD_POS_WAIT_SHOW);
        cardSprite->setPosition(beginPos);
        cardSprite->setCardLocalZOrder((int)waitCardVector.size() + 1);
//        cardSprite->setVisible(false);
        
        cardSprite->setColNum((int)waitCardVector.size());
        panel_game->addChild(cardSprite);
        waitCardVector.pushBack(cardSprite);
    }
    
    //updateAgainVec();
}

int SpriteManager::getAVecCol(CardSprite* card)
{
    for(int i = 0;i<4;++i)
    {
        auto vec = aCardVector[i];
        if(!vec.empty())
        {
            if(vec.getIndex(card)!=-1)
            {
                return i;
            }
        }
    }
    
    return -1;
}

void SpriteManager::magicIsWin()
{
    //检测游戏是否成功
    bool isWin = true;
    for (int col = 0; col < 4; col++)
    {
        if (aCardVector[col].size() < 13)
        {
            isWin = false;
            break;
        }
    }
    if (isWin)
    {
        //先播放动画
        auto is = DATA_M->getGuangGao();
        if(is)
        {
            auto de = DelayTime::create(0.5);
            auto func = CallFunc::create([this](){
                SCENE_M->gameOver(true);
            });
            auto re = RemoveSelf::create();
            auto seq = Sequence::create(de,func,re, NULL);
            auto node = Node::create();
            panel_game->addChild(node);
            node->runAction(seq);
        }
        else
        {
            SCENE_M->gameOver(true);
        }
    }
}

void SpriteManager::showPaiQu(bool isShow)
{
    for(int i = 0;i < 4;++i)
    {
        auto sprite = aSprite[i];
        if(sprite)
        {
            sprite->setVisible(isShow);
        }
    }
    for(int i = 0;i < 7;++i)
    {
        auto sprite = kSprite[i];
        if(sprite)
        {
            sprite->setVisible(isShow);
        }
    }

    waitSprite->setVisible(isShow);
}

void SpriteManager::printPokers(const std::string &tips)
{
    if (tips != "") CCLOG("PPOKERS ================[%s]===============", tips.c_str());
    string sws = "";
    for (int i=0; i<waitShowCardVector.size(); i++) {
        auto poker = waitShowCardVector.at(i);
        auto c = poker->getColorType();
        auto n = poker->getNumber();
        sws += StringUtils::format("%s%02d ", ColorStr[int(c)].c_str(), n);
    }
    CCLOG("PPOKERS WS[%s]", sws.c_str());
    sws = "";
    for (int i=0; i<waitCardVector.size(); i++) {
        auto poker = waitCardVector.at(i);
        auto c = poker->getColorType();
        auto n = poker->getNumber();
        sws += StringUtils::format("%s%02d ", ColorStr[int(c)].c_str(), n);
    }
    CCLOG("PPOKERS W[%s]", sws.c_str());
    for (int i=0; i<4; i++) {
        sws = "";
        auto apokers = aCardVector[i];
        for (int j=0; j<apokers.size(); j++) {
            auto poker = apokers.at(j);
            auto c = poker->getColorType();
            auto n = poker->getNumber();
            sws += StringUtils::format("%s%02d ", ColorStr[int(c)].c_str(), n);
        }
        CCLOG("PPOKERS A%d[%s]", i, sws.c_str());
    }
    for (int i=0; i<7; i++) {
        sws = "";
        auto kpokers = kCardVector[i];
        for (int j=0; j<kpokers.size(); j++) {
            auto poker = kpokers.at(j);
            auto c = poker->getColorType();
            auto n = poker->getNumber();
            sws += StringUtils::format("%s%02d ", ColorStr[int(c)].c_str(), n);
        }
        CCLOG("PPOKERS K%d[%s]", i, sws.c_str());
    }
}
