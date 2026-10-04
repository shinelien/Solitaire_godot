# ifndef __CARD_SPRITE__
# define __CARD_SPRITE__

# include "cocos2d.h"
# include "UIUtils.h"
# include "DataManager.h"

USING_NS_CC;
using namespace std;
namespace spine {
    class SkeletonAnimation;
}

enum CardColor
{
	CARD_BLACK,              //♠️
	CARD_RED,                //♥️
	CARD_FLOWER,             //♣️
	CARD_SQUARE              //♦️
};

enum CardPos
{
	CARD_POS_A,                //A
	CARD_POS_K,                //K
	CARD_POS_WAIT,             //�ȴ�����
	CARD_POS_WAIT_SHOW         //�ȴ���ʾ����
};

class CardSprite : public Node
{
public:
	CardSprite();
	~CardSprite();
	static CardSprite * createCardSprite(CardColor colorType, int number);
	static CardSprite * createCardSprite(int cardId, int pos = 0, bool isLast = false);
	CC_SYNTHESIZE(CardColor, colorType, ColorType);
	CC_SYNTHESIZE(int ,number,Number);
	CC_SYNTHESIZE(bool, isOpen, IsOpen);
    //判断k区域坐标专用
    CC_SYNTHESIZE(bool, isTempOpen, IsTempOpen);
    CC_SYNTHESIZE(bool, _isLast, IsLast);
    CC_SYNTHESIZE(bool, _hasFlop, HasFlop);
	CC_SYNTHESIZE(int, cardId, CardId);//�Ƶ�ID colorType * 13 + number - 1 0-51
	CC_SYNTHESIZE(int, posId, PosId);//�ƶѵ�λ�� 0 A 1 K 2 �ȴ����� 3 �ȴ���ʾ����
	CC_SYNTHESIZE(int, colNum, ColNum);//�����ƶѵ���λ��
    CC_SYNTHESIZE(bool, isDrag, IsDrag);
	void setCardDataByCardId(int cardId);
    void setCarBG();
    void setLobbyCardBg();

	void initCardNum();
    void initCardNum(int type);

	void openCardWithAction(float delay = 0.f);
    void closeCardWithAction(float delay = 0.f, std::function<void()> cb = nullptr);
	void closeCardToPos(cocos2d::Point pos, float delay = 0.f);
	void openCardToPos(cocos2d::Point pos, float delay = 0.f);
	void openCard(bool isFlop = false);
	void closeCard();
    void removeLevelTips();

	void moveToPos(cocos2d::Point p, float delayTime = .0f, bool isReback = false);
	//�Ƴ�����
	void remove();
	int getCLocalZOrder();
	void setCardLocalZOrder(int localZOrder);

	bool checkAPos(CardSprite * targetC);//����Ƿ���Ե���
	bool checkKPos(CardSprite * targetC);

	cocos2d::Rect getHeadBox();//����ͷ����(Kλ�õ�)
	cocos2d::Rect getCenterBox();//�õ��м䲿��
	cocos2d::Rect getCheckBox();
	void playUnDealAction();

    void stopCarTipsAction(bool reorder = true,bool isZOrder = true);
	void playTipsAction(cocos2d::Point endPos, int idx = 0);
    void setSelected(bool flag, int state = 0);
    
	void loadShader();
	void setShaderVisible(bool isVisible);
    Node* addTipsNodeOnce(const std::string &name);
    int getIndex() { return posId==CARD_POS_K?c_localZOrder-TotalWatiCardNum:c_localZOrder; }
    //ai
    CC_SYNTHESIZE(bool, _isJie, IsJie);
    void setIsJiaoHuan(bool is)
    {
        _isJiaoHuan = is;
    }
    bool getIsJiaoHuan()
    {
        return _isJiaoHuan;
    }
    //CC_SYNTHESIZE(bool, _isJiaoHuan, IsJiaoHuan);
    CC_SYNTHESIZE(bool, _isJiaoHuan2, IsJiaoHuan2);
    //shuffle
    void updateSkin();
    void setShufflePoi(Vec2 poi)
    {
        shufflePoi = poi;
    }
    Vec2 getShufflePoi()
    {
        return shufflePoi;
    }
    void setShuffleZOrder(int zor)
    {
        z_ZOrder = zor;
    }
    int getShufflrZOrder()
    {
        return z_ZOrder;
    }
    //道具动画
    void playDaoJuEff(Vec2 movePoi,Vector<CardSprite*>* vec,int posid,Vec2 poi);
    void moveShowWiat();
    void updateEffVecPoi();
    void setSkeletonSoltVisible(const std::string &slotName, bool visible);
    
    void playFaPai(int idx);
    //大厅展示牌用
    CC_SYNTHESIZE(bool, isLobby, IsLobby);
protected:
    bool init() override;
private:

	float cardScale, _delay = 0;
	int c_localZOrder, _pos, teach_lZOrder = 0;
public:
	int getTeachLZOrder() const;

	void setTeachLZOrder(int teachLZOrder);

public:
	int getPos() const;

private:
	Node *centerNode = nullptr;
	Sprite * shaderS = nullptr;
    bool isDaoJuEff = false;
public:
	Node *getShaderS() const;

private:
//    Label *debugLb = nullptr;
    cocos2d::Size _size;
    static int actionTag;
    ActionTimeline *_actionManager = nullptr;
    bool _isLeftMode, isWaitCard = false, _selected = false;
    spine::SkeletonAnimation* _skeletonNode;
    //------------shuffle
    Vec2 shufflePoi;
    //用道具后需要移动到的位置
    Vec2 _movePoi;
    int z_ZOrder;
    //使用道具时自身的容器
    Vector<CardSprite*>* selfVec;
    //前任容器位置
    int beforePosId;
    //所在容器的位置
    Vec2 selfVecPoi;
    
    bool _isJiaoHuan;
    bool isFaPaiAni;
};

# endif
