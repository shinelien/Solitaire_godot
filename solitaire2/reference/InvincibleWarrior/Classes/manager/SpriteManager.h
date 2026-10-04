# ifndef __SPRITE_MANAGER__
# define __SPRITE_MANAGER__

# include "cocos2d.h"
# include "UIUtils.h"
# include "DataManager.h"
# include "CardSprite.h"
# include "MoveData.h"
# include "base/CCData.h"
#include "WinHD.h"
#include "TeachTalkView.h"

# define SPRITE_M SpriteManager::getInstance()
static const char *const BgFormat = "background-%d.jpg";
USING_NS_CC;

namespace spine {
    class SkeletonAnimation;
}
class GameScene;
class CardSprite;
class MoveData;
class SpriteManager : public Ref
{
public:
    enum class ShuffingType {
        None,
        Box,
        Shuffing
    };
    
    
    enum class ShuffleType
    {
        None,
        Box,
        Shuffing
    };
    
	friend class WinHD;
    friend class TeachTalkView;
	static SpriteManager * getInstance();
	
	void initCardIds(const string &pokers = "");
	string getBureau(int t = 1);
	int getCardId();
	vector<cocos2d::Point> getCardInitPositions();
    vector<cocos2d::Point> getCardInitPositions2();

	void initData();
	void clearAllData();//清理所有的数据


	void initCard();

	void initKCard();
    void initKCardAfter();
    void initKCardAfter2();
	void initWaitCard();

	void openKCard();//打开K位置的尾牌
	CardSprite* openKCardByCol(int col,CardSprite* card = nullptr);
	int openWaitCard();//打开等待位置的尾牌
	void openOneWaitCard(int i = 0, float delay = 0.f);
	void resetWaitCard();//重置等待的牌

	void setGamePanel(Node * panel_game);
	SpriteFrame * getCardBgSpriteFrame(int pos=0);
	SpriteFrame * getCardSpriteFrameByNumAndColor(int number,int color,int picType=-1);
	SpriteFrame * getCardSpriteFrameByNumAndColor(const string cardStr);
    SpriteFrame * getSpecialCardSpriteFrame(const string cardStr, bool isLittle = true);

	CardSprite * getCardSpriteByTouchPos(cocos2d::Point touchPos);
	void setCardSpritePos(CardSprite * card,cocos2d::Point delayPos, float moveOffsetY);
	void setKCardLocalZOrder(CardSprite * card);
	bool checkCardPos(CardSprite * card,bool isMoved);//寻找牌的位置 置换到新的位置或者归位
	void autoFindCardPos(CardSprite * card);//自动寻找牌的新位置

	int checkACardPos(CardSprite * card);
	int checkKCardPos(CardSprite * card);

	void addjustWaitShowCard(int offset = 0);
	void moveCardToNowPos(CardSprite * card,int endPosId,int colNum,float delayTime=.0f);

	void checkWaitShowCard();

	void noticeGameStart();

	//牌的位置获取 初始位置
	cocos2d::Point getACardPosByIndex(int index);
	cocos2d::Point getKCardPosByIndex(int index, int row = 0);
	cocos2d::Point getKCardPosByIndexAndCardVector(int index, int row = 0);
	
	cocos2d::Point getWaitCardPos(int index=0);
	cocos2d::Point getWaitShowCardPosByIndex(int index);

	void pushMoveData(MoveData * moveData);
    void clearMoveDatas();
	MOVE_TYPE backMove(); //回退
	void moveCardByMoveData(MoveData * moveData);

	cocos2d::Rect getEmptyCardRect(int posId,int col);

	//
	float getTips();//获得提示
	void showTipsByMoveData(MoveData * moveData);
	void cancleTips();//取消提示

	Sprite * initGameBg();

	void changeCardSkin(int changeType, bool isTeach = false);
    void changeGameBG(int gameBgType);

	void playACardAction(int col, int colorType);
    
    
    void resetGame(const string pokers = ""); //开启新的一局
	void replayGame();//重新玩这局

	void setLeftModel();

	void playWinAction();

	void autoFinshGame();//自动完成游戏
	void autoFindOneCardToA();
	bool checkIsAllOpen();
    void reloadFile();

	bool isThreeModel;

	void setShaderStatus(int posId,int col);
    void initNBBureau();
    bool waitShowNoCard() { return waitCardVector.size()==0; }
	const size_t getWaitShowCardCNT() const { return waitShowCardVector.size(); }
	const size_t getWaitCardCNT() const { return waitCardVector.size(); }
	const size_t getTotalWaitCardCNT() const { return waitCardVector.size()+waitShowCardVector.size(); }
    void clearTipsData();
    void showNextTips();
    void resetTipsCard();
    // 积分模式
    void updateScore(CardSprite *card, int score);
    Vec2 getXYByPos(int pos);
    // 选中了牌
    void setCardSelected(CardSprite *card, bool select);
    // 第一次洗牌逻辑
    void setShufflingFirst(ShuffingType type);
    ShuffingType getShufflingFirst();
    
    void autoPlay(const std::string& autoData);
    //---------shuffle
    bool Shuffle();
    
    bool shuffle(Vector<CardSprite*> upVec,Vector<CardSprite*> downVec);
    //单独筛选上方牌组
    void shuffle(Vector<CardSprite*> vec);
    //筛选明牌收牌
    void shuffleUp();
    
    //判断是否可以执行道具效果
    bool isMagic();
    //判断下放牌组 之后的牌组是否还有牌
    bool isCardVec(int idx);
    //o判断是否还有有效牌
    bool isCardVec();
    //给抽出牌的牌组重新排列位置
    void updateEffVecPoi(Vector<CardSprite*>* vec,Sprite* kSprite);
    //发牌区显示的位置
    Vec2 getWaitShowPoi()
    {
        return Node_waitOpenThree->getPosition();
    }
    //发牌区等待的位置
    Vec2 getWaitPoi()
    {
        return waitSprite->getPosition();
    }
    //道具应该放置的位置
    Vec2 getMagicPoi();
    //------------------ai
    //筛选
    void upCard(Vector<CardSprite*> vec,Vector<CardSprite*> &tempVec);
    void downCard(Vector<CardSprite*> vec,Vector<CardSprite*> &tempVec);
    
    // 每翻开一张牌时 被翻开的牌始终为有效牌
    void shuffleEffect(Vector<CardSprite*> upVec,Vector<CardSprite*> downVec,CardSprite* moveCard,CardSprite* card);
    void effectiveCard(CardSprite* moveCard,CardSprite* card,int col);
    void effectiveCardOne();
    //记录牌分布
    void updateAgainVec();
    void updateAgainVec(CardSprite* moveCard,CardSprite* card,int col);
    void updateIsOpenVec(CardSprite* card);
    void updateIsMagicOpenVec(CardSprite* card);
    //重开后 提换
    CC_SYNTHESIZE(int, againMoveNum, AgainMoveNum);
    void tiHuanCard();
    CardSprite* tiHuanShaiXuan(int num,int color,int id);
    //判定开启翻牌有效条件
    void openEffective();
    
    
    void setIsOpenEffective(bool is)
    {
        isOpenEffective = is;
    }
    bool getIsOpenEffective()
    {
        return isOpenEffective;
    }
    bool getIsFanPaiNum()
    {
        return isFanPaiNum;
    }
    int getFanPaiNum()
    {
        return fanPaiNum;
    }
    //---------------------------
    //-----------------结束动画
    void endAniShouPai();
    void endAniFuWei();
    void pokerEndAni1();
    void pokerEndAni2();
    void pokerEndAni3();
    void pokerEndAni4();
    void pokerEndAni5();
    void pokerEndAni6();
    
    //-----------------发牌动画
    void pokerStartAni1();
    void pokerStartAni2();
    //-----------------
    //给外部使用A音效
    void playEffA();
    //判读是否时发牌牌组的最后一张牌
    bool isWaitCardEnd(CardSprite* card);
    //判断死局
    bool isNoMoveTips(bool isFanPai = true);//维加斯模式是否剩余翻牌次数
    //找到可以收取的牌的位置
    CardSprite* findACardPoi();
    //
    void stopShuffle();
    
    //关卡模式结算收牌
    void levelAutoShouPai(std::function<void()> cb);
    
    //教学模式
    void setTeachBureau();
    
    //返回容器下表
    int getAVecCol(CardSprite* card);
    //魔法棒使用后 判断是否胜利
    void magicIsWin();
    
    //判断收牌状态
    bool getIsAutoFinshGame()
    {
        return isAutoFinshGame;
    }
    void showPaiQu(bool isShow);
private:
    void resetCombo(bool flag = false);
    void addNoCombo();
	SpriteManager();
	static SpriteManager * spriteManager;
	
	vector<int> cardIds;//牌的ID集合
	vector<int> saveCardIds;//保存牌的序列 如果是新开始游戏的话
	vector<int> saveCardIdsFILPX;
	bool isFilpX;

	Vector<CardSprite *> kCardVector[7]; //K位置的牌集合
	Vector<CardSprite *> aCardVector[4]; //A位置的牌集合
	Vector<CardSprite *> waitCardVector; //等待位置的牌集合
	Vector<CardSprite *> waitShowCardVector; //等待位置显示出来的牌集合
	Vector<MoveData *> moveDatas;//操作集合

	Vector<MoveData *> tipsMoveDatas;//提示操作集合
	int _currentTipsIDX = 0;
public:
	int getCurrentTipsIDX() const;

	void setCurrentTipsIDX(int currentTipsIDX);

private:
    void printPokers(const std::string &tips = "");
	Sprite * gameBg;

	Sprite * aSprite[4];
	Sprite * kSprite[7];
    Sprite * waitSprite;
	Node * panel_game, *Node_waitOpen, *Node_waitOpenThree, *startNode;
	LayerColor * tipsLayer;
    Label* tipeLabel;
    bool isTipsFanPai;
    spine::SkeletonAnimation *_skeletonNode, *_skeletonShuffleNode;
	bool isReplay;
    ShuffingType shufflingFirst = ShuffingType::Box; // 1 是牌盒 2 是洗牌
	int initCardNum, noMoreMoveMark, currentMusicLevel = 1, noCombo = 0;

    vector<Node*> magicBG;
    std::string bureauData, bureau3Data, bureauTeachData, hardData;
    std::string currentBureau;
    bool isAutoFinshGame;
    
    //-----------------ai
    //有效牌集合
    Vector<CardSprite*> effectiveVec;
    //记录选中的牌 翻牌有效判定用
    CardSprite* tempMoveCard = nullptr;
    //翻开有效开关isOpenEffective
    bool isOpenEffective = true;
    //是否是重开
    bool isChongKai = false;
    //开启指定步数开启翻牌有效
    bool isFanPaiNum;
    //设定步数
    int fanPaiNum = -1;
    //开启道具辅助
    CC_SYNTHESIZE(bool ,isDaoJuAI,IsDaoJuAI);
    //可辅助次数
    CC_SYNTHESIZE(int ,daoJuAINum,DaoJuAINum);
    //记录本局牌局 大小 花色。id 移动次数
    std::vector<int> kAgainCardNumVec[7];
    std::vector<int> kAgainCardColVec[7];
    std::vector<int> kAgainCardIdVec[7];
    std::vector<int> kAgainCardJiaoHuanVec[7];
    //随机生成翻出主动有效牌次数
    int randEffective = -1;
    //困难模式限定步数
    int randomMoveNum = -1;
    int randomTempMoveNum = 0;
    //每局开始选择出优先花色
    int hongColor;
    int heiColor;
    //---------------------
    //-----------shuffle
    bool isShuffle;
    Vector<CardSprite*> tempLastVec;
    Vector<CardSprite*> tempLastBDVec;
    Vector<CardSprite*> tempLastUpVec;
    //记录有效牌
    CardSprite* _effCard = nullptr;
    //-----------
    //结束动画
    //结束动画1 位置
    Vec2 endAni1_1Poi,endAni1_2Poi,endAni1_3Poi;
    //结束动画2
    vector<Vec2> endAni2Vec;
    //结束动画3
    vector<Vec2> endAni3Vec;
    //结束动画4
    vector<Vec2> endAni4Vec;
    //结束动画5
    vector<Vec2> endAni5Vec;
    //结束动画6
    vector<Vec2> endAni6Vec;
    //洗牌动画冲突，同时只能执行一个t动画
    ShuffleType _shuffleType;
public:
    const string &getCurrentBureau() const {
        return currentBureau;
    }
};

# endif
