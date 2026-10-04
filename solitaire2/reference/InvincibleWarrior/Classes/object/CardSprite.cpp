#include "CardSprite.h"
#include "TipsNode.h"
#include "cocostudio/CCComExtensionData.h"
#include "GameViewHD.hpp"
#include "SpriteManager.h"
#include "AtlasManager.h"
#include "UIUtils.h"
#include "EventObserver.h"

#define USE_SPINE_EF 1
const float PI = 3.14159265358979323846;
using namespace spine;
static std::unordered_map<std::string, spAtlas*>  AtlasCache;
static std::vector<std::string> AtlasNames{"car_0_1.altas","car_2_3.altas","car_4_5.altas","car_6_7.altas"};
static const float EPLOSE = 0.01;

static spAtlasRegion* getAtlasCache(const std::string &key, const std::string &region) {
    auto it = AtlasCache.find(key);
    if (it!=AtlasCache.end()) {
        return spAtlas_findRegion(it->second, region.c_str());
    }
    else {
        auto atlas = spAtlas_createFromFile(key.c_str(), 0);
        AtlasCache[key] = atlas;
        return spAtlas_findRegion(atlas, region.c_str());
    }
}

static spAtlasRegion* getAtlasCache(int shopType, int number = 0, int color = 0) {
    spAtlas *atlas = nullptr;
    string key;
    int picType = DATA_M->getCardPicType(shopType);
    if (shopType == 1) {
        atlas = AtlasManager::getInstance()->load("car_new_0_1.atlas");
        key = StringUtils::format("card_bg_%d", picType);
//        return getAtlasCache("cardBg.atlas", StringUtils::format("card_bg_%d", picType));
    }
    else {
        atlas = AtlasManager::getInstance()->load(AtlasNames[picType/2]);
        key = StringUtils::format("card_%d_%d_%d", picType, number, color);
//        return getAtlasCache(AtlasNames[picType/2], StringUtils::format("card_%d_%d_%d", picType, number, color));
    }
    if (atlas) {
        return spAtlas_findRegion(atlas, key.c_str());
    }
    return nullptr;
}

int CardSprite::actionTag = -1;
CardSprite::CardSprite():
_hasFlop(true)
{
    isFaPaiAni = false;
    _isJiaoHuan = false;
	isOpen = false;
    isTempOpen = false;
	cardScale = 1;
	colNum = 0;
	c_localZOrder = 0;
    isDrag = false;
    isLobby = false;
}
CardSprite::~CardSprite()
{
}
CardSprite * CardSprite::createCardSprite(CardColor colorType, int number)
{
	auto cs = new CardSprite();
    
	cs->setScale(cs->cardScale);
	cs->setColorType(colorType);
	cs->setNumber(number);
	cs->setCardId((int)colorType * 13 + number - 1);
	cs->init();
	return cs;
}

CardSprite * CardSprite::createCardSprite(int cardId, int pos, bool isLast)
{
	auto cs = new CardSprite();
    
	cs->_pos = pos;
    cs->_isLast = isLast;
	cs->setCardDataByCardId(cardId);
	cs->setScale(cs->cardScale);
    cs->init();
	return cs;
}

void CardSprite::setSkeletonSoltVisible(const std::string &slotName, bool visible)
{
    if (_skeletonNode == nullptr) return;
    spSlot* slotPoker0 = _skeletonNode->findSlot(slotName);
    if (slotPoker0) spColor_setFromFloats(&slotPoker0->color, slotPoker0->color.r, slotPoker0->color.g, slotPoker0->color.b, visible?1:0);
}

void CardSprite::setCarBG()
{
    auto isLevelCard = !_isLast&&SCENE_M->getGameView()->isLevelCard(_pos);     // 特殊处理最后一张牌 与上一张pos x y相同
#if USE_SPINE_EF
//    auto imgStr = StringUtils::format("card_bg_%d", DATA_M->getCardPicType(1));
//    _skeletonNode->replaceAttachmentImage("card_bg_5", "card_bg_5", isLevelCard?SPRITE_M->getSpecialCardSpriteFrame("", false):SPRITE_M->getCardBgSpriteFrame(_pos));
    _skeletonNode->replaceAttachmentByRegion("card_bg_5", "card_bg_5", AtlasManager::getInstance()->getRegion(isLevelCard?4:3));
    _size = POKER_SIZE; //_skeletonNode->getBoundingBox().size;
    setContentSize(_size);
    _skeletonNode->setPosition(_size/2);
    
    setSkeletonSoltVisible("poker0", false);
    setSkeletonSoltVisible("poker2", false);
    setSkeletonSoltVisible("poker3", false);
#else
    shaderS->initWithSpriteFrame(isLevelCard?SPRITE_M->getSpecialCardSpriteFrame("", false):SPRITE_M->getCardBgSpriteFrame(_pos));
    auto size = shaderS->getContentSize();
    _size = size;
    setContentSize(size);
    centerNode->setPosition(size/2);
#endif
    
    if (0) { // 调试信息
        if (isLevelCard) {
            auto layer = LayerColor::create(Color4B::RED, 10, 10);
            this->addChild(layer);
            layer->setPositionY(100);
        }
        auto vec2 = SPRITE_M->getXYByPos(_pos);
        auto lb = Label::create();
        lb->setPosition(Vec2(_contentSize)-Vec2(70, -30));
        lb->setSystemFontSize(30);
        lb->setColor(Color3B::BLUE);
        lb->setString(StringUtils::format("%d_or(%d)", colorType, number));
//        lb->setString(StringUtils::format("%d_or(%d)", _localZOrder, c_localZOrder));
//        this->scheduleOnce([this, lb](float){
//            lb->setString(StringUtils::format("%d_or(%d)", _localZOrder, c_localZOrder));
//        }, 1/30, "xxxxx_debuglb_update");
        addChild(lb);
    }
}

void CardSprite::setLobbyCardBg()
{
    if(isLobby)
    {
        return;
    }
    _skeletonNode->replaceAttachmentByRegion("card_bg_5", "card_bg_5", AtlasManager::getInstance()->getRegion(3));
    _size = POKER_SIZE; //_skeletonNode->getBoundingBox().size;
    setContentSize(_size);
    _skeletonNode->setPosition(_size/2);
    
    setSkeletonSoltVisible("poker0", false);
    setSkeletonSoltVisible("poker2", false);
    setSkeletonSoltVisible("poker3", false);
}

void CardSprite::loadShader()
{
//    shaderS = Sprite::create("img_card_shader.png");
//    shaderS->setScale(2.05);
//    shaderS->setLocalZOrder(-1);
//    shaderS->setPosition(Point(this->getContentSize()/2)+Point(0,-9));
//    this->addChild(shaderS);
    
    // 加载动画 复制动画
//    if (actionTag == -1) {
//        auto node = CSLoader::createNode("card/FlopOne.csb");
//        auto sp = node->getChildByName("Sprite_card");
//        actionTag = dynamic_cast<ComExtensionData*>(sp->getComponent("ComExtensionData"))->getActionTag();
//        shaderS->setAnchorPoint(sp->getAnchorPoint());
//    }
//    auto newCom = ComExtensionData::create();
//    newCom->setActionTag(actionTag);
//    shaderS->addComponent(newCom);
//    _actionManager = ActionTimelineCache::createAction("card/FlopOne.csb");
//    shaderS->runAction(_actionManager);
//    _actionManager->setFrameEventCallFunc([this](Frame *frame){
//        auto eventName = static_cast<EventFrame*>(frame)->getEvent();
//        if (eventName == "flop" || eventName == "flop1") {
//            openCard();
//        }
//    });
#if USE_SPINE_EF
    _skeletonNode->setEventListener( [this] (spTrackEntry* entry, spEvent* event) {
        if (isWaitCard&&!isDaoJuEff) { // 上边牌区翻转
            this->setCardLocalZOrder((int)SPRITE_M->getTotalWaitCardCNT()-c_localZOrder);
        }
        if (strcmp(event->data->name, "unflop") == 0) {
            initCardNum();
        }
        else if(isDaoJuEff)
        {
            SOUND_M->playEffectMusic(EffectMovePoker);
            //this->setCardLocalZOrder(1);
            isDaoJuEff = false;
            //moveShowWiat();
            isOpen = true;
            isTempOpen = true;
            updateSkin();
        }
        else {
            _skeletonNode->setColor(Color3B::WHITE);
            openCard(_delay>=EPLOSE);
        }
    });
//    _skeletonNode->setCompleteListener([this](spTrackEntry* entry) {
//        _skeletonNode->clearTrack();
//    });
#endif
}

void CardSprite::setShaderVisible(bool isVisible)
{
//    shaderS->setVisible(isVisible);
    if (posId == CARD_POS_WAIT) {
        if (isVisible) {
            _skeletonNode->setColor(Color3B::WHITE);
        }
//        else {
//            _skeletonNode->setColor(WaitPokerColor[UIUtils::clamp(c_localZOrder, 0, 8)]);
//        }
    }
}

void CardSprite::initCardNum()
{
	if (isOpen)
	{
        if (!_isLast&&DATA_M->isLevelMode()) {
            SCENE_M->getGameView()->collectSpecialCard(_pos);
        }
#if USE_SPINE_EF == 0
		shaderS->setSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(number,colorType));
#else
//        auto imgStr = StringUtils::format("card_%d_%d_%d", DATA_M->getCardPicType(2), number, colorType);
//        _skeletonNode->replaceAttachmentImage("card_bg_5", "card_bg_5", SPRITE_M->getCardSpriteFrameByNumAndColor(number,colorType));
        updateSkin();
#endif
	}
	else
	{
		this->setCarBG();
	}
    
    EventCustom event("msg_game_scoreani");
    event.setUserData(this);
    getEventDispatcher()->dispatchEvent(&event);
}

void CardSprite::initCardNum(int type)
{
    isOpen = true;
    isTempOpen = true;
    _skeletonNode->replaceAttachmentByRegion("card_bg_5", "card_bg_5", AtlasManager::getInstance()->getRegion(2, number, colorType,type));
    _skeletonNode->replaceAttachmentByRegion("poker0", "poker0", AtlasManager::getInstance()->getRegion(6, number, colorType,type));
    _skeletonNode->replaceAttachmentByRegion("poker2", "poker2", AtlasManager::getInstance()->getRegion(5, number, colorType,type));
    _skeletonNode->replaceAttachmentByRegion("poker3", "poker3", AtlasManager::getInstance()->getRegion(5, number, colorType,type));
    bool isBlack = (int)colorType%2==0;
    setSkeletonSoltVisible("poker0", true);
    setSkeletonSoltVisible("poker2", isBlack);
    setSkeletonSoltVisible("poker3", !isBlack);
}

void CardSprite::setCardDataByCardId(int cardId)
{
	this->cardId = cardId;
	this->number = cardId % 13 + 1;
	this->colorType = (CardColor)(int)(cardId / 13);

	this->setName("Poker_" + toString(cardId));
	//CCLOG("NUMBER = %d , COLOR = %d", number, colorType);
}

//Kλ�õ����ƿ�
void CardSprite::openCardWithAction(float delay)        // 开牌
{
    isTempOpen = true;
#if USE_SPINE_EF == 0
    static float openTm = POKER_ACTION_MOVE/2;    // 开牌时间
    _isLeftMode = DATA_M->getIsLeftModel();
    auto dd = _isLeftMode?-1:1;
	if (posId==CARD_POS_WAIT) { // 上边牌区翻转
        if (_isLeftMode)
            this->setCardLocalZOrder((int)SPRITE_M->getWaitCardCNT());
//        setLocalZOrder((int)SPRITE_M->getWaitCardCNT());
        shaderS->runAction(Sequence::create(DelayTime::create(delay)
                                            ,CallFunc::create([this, dd]{
                                                shaderS->setAnchorPoint(_isLeftMode?Vec2::ANCHOR_MIDDLE_RIGHT:Vec2::ANCHOR_MIDDLE_LEFT);          // 设置锚点在左边中间
                                                shaderS->setPositionX(-_size.width/2*dd);                      // 由于锚点变换纠正位置
                                            })
                                            ,Spawn::createWithTwoActions(RotateTo::create(openTm, Vec3(0, -100*dd, 0)/*沿着y轴翻转-90°*/), MoveTo::create(openTm, Vec2(0, 40+shaderS->getPositionY()))/*移动牌x的位置 并想上移动*/)
                                            , CallFunc::create([this, delay]{
                                                shaderS->setFlippedX(true);     // 开牌 需要翻转一下
                                                shaderS->setColor(Color3B::WHITE);
                                                openCard(delay>0);
                                                this->setCardLocalZOrder((int)SPRITE_M->getTotalWaitCardCNT()-c_localZOrder);
                                            })
                                            , Spawn::createWithTwoActions(RotateTo::create(openTm, Vec3(0, 180*dd, 0))/*沿着y轴翻转180°*/, MoveTo::create(openTm, Vec2(_size.width/2*dd, 0)))
                                            , CallFunc::create([this](){
                                                // 翻转结束还原纸牌坐标
                                                shaderS->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
                                                shaderS->setPosition(Vec2::ZERO);
                                                shaderS->setFlippedX(false);
                                                shaderS->setRotation3D(Vec3::ZERO);
                                            })
			, NULL));
	}
	else {  // 原地翻转
		shaderS->runAction(Sequence::create(DelayTime::create(delay)
                                            , Spawn::createWithTwoActions(RotateTo::create(openTm, Vec3(0, -100*dd, 0)), MoveTo::create(openTm, Vec2(0, 20)))
                                            , CallFunc::create([this]{
                                                shaderS->setFlippedX(true);
                                                openCard();
                                            })
                                            , Spawn::createWithTwoActions(RotateTo::create(openTm, Vec3(0, 180*dd, 0)), MoveTo::create(openTm, Vec2(0, 0)))
                                            , CallFunc::create([this](){
                                                shaderS->setFlippedX(false);
                                                shaderS->setRotation3D(Vec3::ZERO);
                                            })
                                            , NULL));
	}
//    if (_actionManager)
//        _actionManager->play(posId==CARD_POS_WAIT?"flop1":"flop", false);
#else
    isWaitCard = posId==CARD_POS_WAIT;
    string aniName = "Flip0";
    if (isWaitCard) {
        aniName = DATA_M->getIsLeftModel()?"Flip_L1":"Flip1";
    }
    
    _delay = delay;
    if (delay>EPLOSE) {
        _skeletonNode->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create([this, aniName](){
            _skeletonNode->setAnimation(0, aniName, false);
        }), NULL));
    }
    else {
        _skeletonNode->setAnimation(0, aniName, false);
    }
#endif
}

void CardSprite::closeCardWithAction(float delay, std::function<void()> cb)     // 扣牌
{
    isOpen = false;
    isTempOpen = false;
#if USE_SPINE_EF == 0
	static float openTm = POKER_ACTION_MOVE/2;
    auto dd = DATA_M->getIsLeftModel()?-1:1;
	if (posId==CARD_POS_WAIT_SHOW) {
//        if (_isLeftMode)
//            this->setCardLocalZOrder((int)SPRITE_M->getTotalWaitCardCNT()-c_localZOrder);
		shaderS->runAction(Sequence::create(DelayTime::create(delay)
                                            ,CallFunc::create([this, dd]{
                                                shaderS->setAnchorPoint(_isLeftMode?Vec2::ANCHOR_MIDDLE_LEFT:Vec2::ANCHOR_MIDDLE_RIGHT);
                                                shaderS->setPositionX(_size.width/2*dd);
                                            })
                                            ,Spawn::createWithTwoActions(RotateTo::create(openTm, Vec3(0, 80*dd, 0)), MoveTo::create(openTm, Vec2(0, 40+shaderS->getPositionY())))
                                            , CallFunc::create([this]{
                                                initCardNum();
                                                shaderS->setAnchorPoint(_isLeftMode?Vec2::ANCHOR_MIDDLE_LEFT:Vec2::ANCHOR_MIDDLE_RIGHT);
                                                shaderS->setColor(Color3B::WHITE);
                                                shaderS->setFlippedX(true);
                                                this->setCardLocalZOrder((int)SPRITE_M->getTotalWaitCardCNT()-c_localZOrder);
                                            })
                                            , Spawn::createWithTwoActions(RotateTo::create(openTm, Vec3(0, 180*dd, 0)), MoveTo::create(openTm, Vec2(-_size.width/2*dd, 0)))
                                            , CallFunc::create([this, cb](){
                                                shaderS->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
                                                shaderS->setPosition(Vec2::ZERO);
                                                shaderS->setFlippedX(false);
                                                shaderS->setRotation3D(Vec3::ZERO);
                                            })
                                            , NULL));
	}
	else {
		shaderS->runAction(Sequence::create(DelayTime::create(delay)
                                            ,Spawn::createWithTwoActions(RotateTo::create(openTm, Vec3(0, 80*dd, 0)), MoveTo::create(openTm, Vec2(0, 20)))
                                            , CallFunc::create([this, dd]{
                                                initCardNum();
                                                shaderS->setFlippedX(true);
                                            })
                                            , Spawn::createWithTwoActions(RotateTo::create(openTm, Vec3(0, -180*dd, 0)), MoveTo::create(openTm, Vec2(0, 0)))
                                            , CallFunc::create([this, cb](){
                                                shaderS->setFlippedX(false);
                                                shaderS->setRotation3D(Vec3::ZERO);
                                            })
                                            , NULL));
	}
#else
    isWaitCard = posId==CARD_POS_WAIT_SHOW;
    string aniName = "Flip3";
    if (isWaitCard) {
        aniName = DATA_M->getIsLeftModel()?"Flip_L2":"Flip2";
    }
    _delay = delay;
    if (delay>EPLOSE) {
        _skeletonNode->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create([this, aniName](){
            _skeletonNode->setAnimation(0, aniName, false);
        }), NULL));
    }
    else {
        _skeletonNode->setAnimation(0, aniName, false);
    }
    _skeletonNode->setCompleteListener([this, cb](spTrackEntry* entry) {
        if (cb) {
            cb();
        }
        _skeletonNode->setCompleteListener(nullptr);
    });
#endif
}

void CardSprite::openCardToPos(Point pos, float delay)
{
//    isOpen = true;
//    initCardNum();
    openCardWithAction(delay);
	moveToPos(pos, delay);
}

void CardSprite::closeCardToPos(Point pos, float delay)
{
//    isOpen = false;
//    initCardNum();
    closeCardWithAction(delay);
    moveToPos(pos, delay);
}

void CardSprite::closeCard()
{
	isOpen = false;
    isTempOpen = false;
	initCardNum();
}

void CardSprite::removeLevelTips() {
    auto tipsNode = getChildByName("LevelTipsNode");
    if (tipsNode) {
        tipsNode->setVisible(false);
    }
}

//�ȴ�λ�õ����ƿ�
void CardSprite::openCard(bool isFlop)
{
	isOpen = true;
    isTempOpen = true;
	initCardNum();
    if (!isFlop) {
        SOUND_M->playEffectMusic(EffectMovePoker);
        // 如果是任务卡牌
        if (SCENE_M->getGameView()->isLevelCard(number, (int)colorType)) {
            addTipsNodeOnce("LevelTipsNode")->setVisible(true);
        }
    }
}

void CardSprite::moveToPos(Point p, float delayTime, bool isReback/*是否是没找到回来的*/)
{
    //不再是拖动
    setIsDrag(false);
	this->stopActionByTag(999);
    auto isGuangGao = DATA_M->getGuangGao();
    if(isGuangGao)
    {
        if(posId == CARD_POS_A)
        {//收牌移动
            //计算贝塞尔曲线控制点
            //已知起始点与目标点
            //控制点y坐标高于起始点y坐标
            //控制点x坐标先取 起始点x +- 100；
            
            
            //目标点-起始点 /2。= 中心点。
            auto poi = getPosition();
            auto zhongxinPoi = p + poi;
            //计算两点直接线段角度
            //算xy 两个直角边  100,100,  -100 100;  -200
            auto x = p.x - poi.x;
            auto y = p.y - poi.y;
            auto length = zhongxinPoi.length();//斜边
            //sin。对边比斜边 tan 对边比邻边
            auto angle = atan(fabsf(y/x)) * 180/PI;
            //计算垂直角度
            int i = 0;
            int j = 0;
            auto rand = random(0, 1);
            if(rand == 0)
            {
                i = -45;
                j = -90;
            }
            else if(rand == 1)
            {
                i = 135;
                j = 90;
            }
            
            auto rand2 = random(0, 1);
            int k = 0;
            if(rand2 == 0)
            {
                k = 1;
            }
            else if(rand2 == 1)
            {
                k = -1;
            }
            
            angle+=i;
            //算出向量
            auto xlPoi = DATA_M->getVectorByAngle(angle);
            Vec2 config1 = xlPoi*300*k + zhongxinPoi/2;
            xlPoi = DATA_M->getVectorByAngle(angle+j);
            Vec2 config2 = xlPoi*300*k + zhongxinPoi/2;
            
            auto startPoi = getPosition();
            
            ccBezierConfig c;
            c.controlPoint_1 = config1;
            c.controlPoint_2 = config2;
            c.endPosition = p;
            setVisible(true);
            auto bez = BezierTo::create(0.5, c);
            auto ease = EaseCircleActionOut::create(bez);
            
            //旋转
            auto rota = RotateBy::create(0.5, 360*k);
            auto spa = Spawn::create(bez,rota, NULL);
            
            auto del = DelayTime::create(delayTime);
            auto func = CallFunc::create([this]{
                if(getIsDrag())
                {
                    
                }
                else
                {
                    setCardLocalZOrder(this->c_localZOrder);
                }
                
                
                if (posId == CARD_POS_A) {
                    removeLevelTips();
                    SCENE_M->getGameView()->collectACard(number, colorType);
                }
                
                EventCustom event("msg_game_scoreani");
                event.setUserData(this);
                getEventDispatcher()->dispatchEvent(&event);
            });
            int num = 0.5/0.04;
            //0.15s
            schedule([this](float dt){
                //可以走七次
                auto picType = DATA_M->getCardPicType(2);
                auto is = DATA_M->getCardFaceStatus(2,picType,cardId);
                picType = is?picType:0;
                auto card_1 = UIUtils::createCSBNode("card/CardFace.csb");
                auto _sprite1 = card_1->getChildByName<Sprite*>("Sprite_face");
                auto _sprite2 = _sprite1->getChildByName<Sprite*>("Sprite_num");
                auto _sprite3 = _sprite1->getChildByName<Sprite*>("Sprite_color");
                _sprite1->setSpriteFrame(AtlasManager::getInstance()->getSF(2,number,(int)colorType,picType));
                _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5,number,(int)colorType,picType));
                _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6,number,(int)colorType,picType));
                _sprite2->setColor(UIUtils::getCardColor((int)colorType));
                getParent()->addChild(card_1);
                card_1->setPosition(getPosition());
                card_1->setRotation(getRotation());
                card_1->setLocalZOrder(getLocalZOrder()-1);
                auto size2 = _sprite2->getContentSize();
                _sprite2->setPositionX(size2.width*0.5f);
                //auto sp = Sprite::createWithSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(number,(int)colorType,picType));
                
                
                auto delay = DelayTime::create(0.2);
                auto fa = FadeOut::create(0.3);
                auto re = RemoveSelf::create();
                auto seq = Sequence::create(fa,re, NULL);
                card_1->runAction(seq);
                
            },0.04,num,0,StringUtils::format("move%d",cardId));
            
            auto runSeq = Sequence::create(del,spa,func, NULL);
            auto speed = Speed::create(runSeq, 1);
            speed->setTag(999);
            this->runAction(speed);
        }
        else
        {
            auto move = MoveTo::create(POKER_ACTION_MOVE, p);
            ActionInterval *moveAction = (posId==(int)CARD_POS_WAIT||posId==(int)CARD_POS_WAIT_SHOW)?(ActionInterval*)move:(ActionInterval*)EaseCircleActionOut::create(move);
            auto runSeq = Sequence::create(DelayTime::create(delayTime), moveAction, CallFunc::create([this]{
                if(getIsDrag())
                {
                    
                }
                else
                {
                    setCardLocalZOrder(this->c_localZOrder);
                }
                
                
                if (posId == CARD_POS_A) {
                    removeLevelTips();
                    SCENE_M->getGameView()->collectACard(number, colorType);
                }
                
                EventCustom event("msg_game_scoreani");
                event.setUserData(this);
                getEventDispatcher()->dispatchEvent(&event);
            }), NULL);
            runSeq->setTag(999);
            this->runAction(runSeq);
        }
    }
    else
    {
        auto isAuto = SPRITE_M->getIsAutoFinshGame();
        auto move = MoveTo::create(isAuto?POKER_ACTION_MOVE/2:POKER_ACTION_MOVE, p);
        ActionInterval *moveAction = (posId==(int)CARD_POS_WAIT||posId==(int)CARD_POS_WAIT_SHOW)?(ActionInterval*)move:(ActionInterval*)EaseCircleActionOut::create(move);
        auto runSeq = Sequence::create(DelayTime::create(delayTime), moveAction, CallFunc::create([this, isReback]{
            if(getIsDrag())
            {
                
            }
            else
            {
                setCardLocalZOrder(this->c_localZOrder);
            }
            
            
            if (posId == CARD_POS_A) {
                removeLevelTips();
                SCENE_M->getGameView()->collectACard(number, colorType);
            }
            
            EventCustom event("msg_game_scoreani");
            event.setUserData(this);
            getEventDispatcher()->dispatchEvent(&event);
            if (!isReback) {
                ValueMap valueMap {
                    {"name", Value(this->getName())}
                };
                EventObserver::getInstance()->sendEvent("msg_teach_next", valueMap);
            }
        }), NULL);
        runSeq->setTag(999);
        this->runAction(runSeq);
    }
    
    
}

//�Ƴ�����
void CardSprite::remove()
{
	auto scale = ScaleTo::create(0.1,0);
	this->runAction(Sequence::create(scale,
		CallFunc::create(
		[&]{
			this->removeFromParentAndCleanup(true);
		})
		,NULL));
}

void CardSprite::setCardLocalZOrder(int localZOrder)
{
	this->c_localZOrder = localZOrder;
    this->setLocalZOrder(localZOrder+teach_lZOrder);
}

int CardSprite::getCLocalZOrder()
{
	return c_localZOrder;
}

bool CardSprite::checkAPos(CardSprite * targetC)
{
	if (number + 1 == targetC->getNumber() && colorType == targetC->getColorType())
	{
		return true;
	}
	return false;
}

bool CardSprite::checkKPos(CardSprite * targetC)
{
	if (number - 1 == targetC->getNumber())
	{
		if (colorType == CARD_BLACK && (targetC->getColorType() == CARD_RED || targetC->getColorType() == CARD_SQUARE))
		{
			return true;
		}
		if (colorType == CARD_RED && (targetC->getColorType() == CARD_BLACK || targetC->getColorType() == CARD_FLOWER))
		{
			return true;
		}
		if (colorType == CARD_FLOWER && (targetC->getColorType() == CARD_RED || targetC->getColorType() == CARD_SQUARE))
		{
			return true;
		}
		if (colorType == CARD_SQUARE && (targetC->getColorType() == CARD_BLACK || targetC->getColorType() == CARD_FLOWER))
		{
			return true;
		}
	}
	return false;
}

Rect CardSprite::getHeadBox()
{
	Rect boxRect = this->getBoundingBox();
	return Rect(boxRect.getMinX() - 5, boxRect.getMaxY() - OffsetOpen, boxRect.size.width + 10, OffsetOpen);
}

Rect CardSprite::getCenterBox()
{
	Rect boxRect = this->getBoundingBox();
	Point centerP = this->getPosition();
	return boxRect;
	//return Rect((centerP.x + boxRect.getMinX()) / 2, (centerP.y - boxRect.getMinY()) / 4 + boxRect.getMinY(), boxRect.size.width / 2, boxRect.size.height * 3 / 4);
}

Rect CardSprite::getCheckBox()
{
	Rect boxRect = this->getBoundingBox();
	return Rect(boxRect.getMinX() , boxRect.getMinY() - 20, boxRect.size.width, boxRect.size.height + 15);;
}

void CardSprite::playUnDealAction()
{
    centerNode->stopActionByTag(999);
	float delay = 0.05;
	auto rotate_1 = MoveTo::create(delay, Vec2(-10, 0));    //RotateTo::create(delay, 20);
	auto rotate_2 = MoveTo::create(delay*2, Vec2(20, 0));   //RotateTo::create(delay * 2, -20);
    auto rotate_3 = MoveTo::create(delay, Vec2(-15, 0));      //RotateTo::create(delay ,0);
	auto rotate_4 = MoveTo::create(delay, Vec2(10, 0));    //RotateTo::create(delay, 10);
	auto rotate_5 = MoveTo::create(delay*2, Vec2(-5, 0));   //RotateTo::create(delay * 2, -10);
	auto rotate_6 = MoveTo::create(delay, Vec2(0, 0));      //RotateTo::create(delay, 0);
    auto action = Sequence::create(rotate_1, rotate_2, rotate_3, rotate_4, rotate_5, rotate_6, NULL);
    action->setTag(999);
	centerNode->runAction(action);
}

void CardSprite::stopCarTipsAction(bool reorder,bool isZOrder) {
    this->stopActionByTag(999);
    if (reorder) {
        if(isZOrder)
        {
            setCardLocalZOrder(c_localZOrder);
        }
        
        if (this->getChildByName("TipsNode"))
            this->removeChildByName("TipsNode");
    }
}

void CardSprite::playTipsAction(Point endPos, int idx)
{
    stopCarTipsAction(false);
	Point nowPos = this->getPosition();
//    float dis = nowPos.distance(endPos);
	auto runSeq = Sequence::create(MoveTo::create(TIPS_ACTION_MOVE1, endPos), DelayTime::create(TIPS_ACTION_DELAY1), MoveTo::create(TIPS_ACTION_MOVE2, nowPos), DelayTime::create(TIPS_ACTION_DELAY2), CallFunc::create([this]{
        stopCarTipsAction();
	}), NULL);
	runSeq->setTag(999);
	this->runAction(runSeq);
	// 添加提示
    if (idx==0) {
        addTipsNodeOnce("TipsNode");
    }
}

Node* CardSprite::addTipsNodeOnce(const std::string &name) {
    auto tipsNode = this->getChildByName<TipsNode*>(name);
    if (tipsNode == nullptr) {
        tipsNode = TipsNode::createLayerN();
        this->addChild(tipsNode);
        tipsNode->setPosition(getContentSize()/2);
        tipsNode->playAni("start1", true);
        tipsNode->setName(name);
    }
    return tipsNode;
}

bool CardSprite::init()
{
    centerNode = Node::create();
    addChild(centerNode);
#if USE_SPINE_EF
    _skeletonNode = SkeletonAnimation::createFromCache(StringUtils::format("Card%d", cardId));
//    AtlasManager::getInstance()->getSkeletonNode(StringUtils::format("Card%d", cardId), "res/skeleton.json", "res/skeleton.atlas");
    
//    _skeletonNode = SkeletonAnimation::createWithJsonFile("res/skeleton.json", "res/skeleton.atlas", 1.f);
//    _skeletonNode = SkeletonAnimation::createWithBinaryFile("res/skeleton.skel", "res/skeleton.atlas", 1.f);
//    auto imgStr = StringUtils::format("card_bg_%d", DATA_M->getCardPicType(1));
    
    //_skeletonNode = spine::SkeletonAnimation::createWithJsonFile("res/pk/skeleton.json", "res/pk/skeleton.atlas", 1.f);
    _skeletonNode->replaceAttachmentByRegion("card_bg_5", "card_bg_5", AtlasManager::getInstance()->getRegion(3));
	centerNode->addChild(_skeletonNode);
#else
    shaderS = Sprite::create();
    centerNode->addChild(shaderS);
#endif
	_isLeftMode = DATA_M->getIsLeftModel();

    setCarBG();
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    loadShader();
    autorelease();
    return Node::init();
}

Node *CardSprite::getShaderS() const {
#if USE_SPINE_EF
	return _skeletonNode;
#else
    return shaderS;
#endif
}

const std::string StateName[]{"test", "touch1"};
void CardSprite::setSelected(bool flag, int state)
{
    _selected = flag;
#if USE_SPINE_EF
    auto currentEntry = _skeletonNode->getCurrent();
    if (currentEntry)
        CCLOG("wtf state %s %d", currentEntry->animation->name, _skeletonNode->getState());
    if (posId==CARD_POS_WAIT)
        return;
    
    _skeletonNode->unschedule("schedule_skeleton_ani");
    if (flag) {
//        _skeletonNode->scheduleOnce([this](float){
        
            //_skeletonNode->setAnimation(0, "touch0", false);移除悬浮效果
//        }, 0.0001, "schedule_skeleton_ani");
    }
    else
    {
//        _skeletonNode->scheduleOnce([this](float){
            _skeletonNode->setAnimation(0, "touch1", false);
//        }, 0.0001, "schedule_skeleton_ani");
    }
#endif
}


void CardSprite::updateSkin()
{
    auto picType = DATA_M->getCardPicType(2,cardId);
//    auto is = DATA_M->getCardFaceStatus(2,picType,cardId);
//    picType = is?picType:0;
    _skeletonNode->replaceAttachmentByRegion("card_bg_5", "card_bg_5", AtlasManager::getInstance()->getRegion(2, number, colorType,picType));
    
    _skeletonNode->replaceAttachmentByRegion("poker0", "poker0", AtlasManager::getInstance()->getRegion(6, number, colorType,picType));
    bool isBlack = (int)colorType%2==0;
    if (isBlack)
        _skeletonNode->replaceAttachmentByRegion("poker2", "poker2", AtlasManager::getInstance()->getRegion(5, number, colorType,picType));
    else
        _skeletonNode->replaceAttachmentByRegion("poker3", "poker3", AtlasManager::getInstance()->getRegion(5, number, colorType,picType));
    
    setSkeletonSoltVisible("poker0", true);
    setSkeletonSoltVisible("poker2", isBlack);
    setSkeletonSoltVisible("poker3", !isBlack);
}

void CardSprite::playDaoJuEff(Vec2 movePoi,Vector<CardSprite*>* vec,int posid,Vec2 poi)
{//播放道具动画
    _movePoi = movePoi;
    selfVec = vec;
    beforePosId = posid;
    selfVecPoi = poi;
    isDaoJuEff = true;
    _skeletonNode->setAnimation(0, "Magic", false);
    //层级+100；
    this->setLocalZOrder(this->getLocalZOrder() + 100);
    this->getShaderS()->setColor(WaitPokerColor[8]);
    //--------------------关卡模式收集卡背
    if (!_isLast&&DATA_M->isLevelMode()) {
        SCENE_M->getGameView()->collectSpecialCard(_pos);
    }
    
    // 如果是任务卡牌
    if (SCENE_M->getGameView()->isLevelCard(number, (int)colorType)) {
        addTipsNodeOnce("LevelTipsNode")->setVisible(false);
    }
    //-----------------------------------
    moveShowWiat();
}
//第一次延时
float time_0 = 0.4;
//移动到中间的时间
float time_1 = 0.27;
//中间等待的时间
float time_2 = 1.25;
float time_3 = 0.26;
//其余牌向上移动的时间
float time_4 = 0.2;
//其余向上移动的时间递增
float time_5 = 0.1;

void CardSprite::moveShowWiat()
{//59帧最大。 时长70帧
    auto movePoi = SPRITE_M->getWaitShowCardPosByIndex(2);
    auto delay0 = DelayTime::create(time_0);
    auto move = MoveTo::create(time_1, Vec2(0,0));
    auto func0 = CallFunc::create([this](){
        //将容器中元素重新设置位置
        updateEffVecPoi();
    });
    auto delay = DelayTime::create(time_2);
    auto move2 = MoveTo::create(time_3, _movePoi);
    auto func = CallFunc::create([this](){
        
        //恢复层次
        auto z = this->getLocalZOrder();
        if(z > 100)
        {
            this->setLocalZOrder(z - 100);
        }
        //增加步数
        SCENE_M->getGameView()->addMoveNum();
        //分数
        if (posId == CARD_POS_A) {
            SPRITE_M->updateScore(this, 10);
            SPRITE_M->playEffA();
            //播放特效
            auto col = SPRITE_M->getAVecCol(this);
            if(col != -1)
            SPRITE_M->playACardAction(col, getColorType());
            
            SPRITE_M->magicIsWin();
        }
        else
        {
            //移动生效
            SOUND_M->playEffectMusic(EffectMovePoker0);
            SPRITE_M->updateScore(this, 5);
        }
        
        //关卡模式
        //-------------------------收集卡牌
        // 如果是任务卡牌
        if (SCENE_M->getGameView()->isLevelCard(number, (int)colorType)) {
            addTipsNodeOnce("LevelTipsNode")->setVisible(true);
        }
        if (posId == CARD_POS_A) {
            removeLevelTips();
            SCENE_M->getGameView()->collectACard(number, colorType);
        }
        //----------------------------------
        //---------------------------收集卡背
        
        //----------------------------------
        //-------------------------限定分数
        if(1)
        {
            EventCustom event("msg_game_scoreani");
            event.setUserData(this);
            getEventDispatcher()->dispatchEvent(&event);
        }
        //----------------------------------
        
        //----------普通模式挑战模式，关卡模式中牌局模式 判定输赢
        if (SPRITE_M->checkIsAllOpen())
        {
            SCENE_M->showAutoFinishBtn(true);
        }
        //---------------------------------------------
        //恢复触摸
        SCENE_M->gameStart();
        //
        //SCENE_M->getGameView()->useMagic();
        
    });
    auto seq = Sequence::create(delay0,move,func0,delay,move2,func, NULL);
    this->runAction(seq);
    //SPRITE_M->addjustWaitShowCard(1);
}


void CardSprite::updateEffVecPoi()
{
    float tempTiem = 0;
    int localZ = 0;
    if(beforePosId==(int)CardPos::CARD_POS_A)
    {
        localZ = 0;
    }
    else if(beforePosId==(int)CardPos::CARD_POS_K)
    {
        localZ = 25;
    }
    else if(beforePosId==(int)CardPos::CARD_POS_WAIT)
    {
        localZ = 0;
    }
    else if(beforePosId==(int)CardPos::CARD_POS_WAIT_SHOW)
    {
        localZ = 1;
    }
    CardSprite*oneCard=nullptr;
    if(!selfVec->empty())
    {
        oneCard = selfVec->at(0);
        oneCard->setCardLocalZOrder(localZ);
    }
    
    if(beforePosId==(int)CardPos::CARD_POS_K)
    {
        if(oneCard&&(oneCard->getPosition() - selfVecPoi).length() < 10)
        {//第一张牌在。
            //true 时后面的牌统一移动
            bool is = false;
            for(int i = 1;i< selfVec->size();++i)
            {
                auto card = selfVec->at(i);
                if(card!=this)
                {
                    card->setCardLocalZOrder(localZ+i);
                }
                
                //前一张位置和现在这张位置 差值 都是翻开时 差66 其他差30
                auto tempPoi = oneCard->getPosition();
                auto cardPoi = card->getPosition();
                float dy = oneCard->getIsOpen()&&card->getIsOpen()?68:32;
                if(tempPoi.y - cardPoi.y <= dy)
                {//是相邻
                    
                }
                else
                {//当前牌及其之后的牌都移动
                    is = true;
                }
                oneCard = card;
                if(is)
                {//前一张牌位置- dy
                    auto move = MoveBy::create(time_4, Vec2(0,30));
                    auto delay = DelayTime::create(tempTiem);
                    auto seq = Sequence::create(move,delay, NULL);
                    card->runAction(seq);
                    tempTiem+=time_5;
                }
            }
        }
        else
        {//第一张牌没有了；整体向上移动
            for(int i = 0;i< selfVec->size();++i)
            {
                auto card = selfVec->at(i);
                if(card!=this)
                {
                    card->setCardLocalZOrder(localZ+i);
                }
                auto move = MoveBy::create(time_4, Vec2(0,30));
                auto delay = DelayTime::create(tempTiem);
                auto seq = Sequence::create(move,delay, NULL);
                card->runAction(seq);
                tempTiem+=time_5;
            }
        }
        if(!selfVec->empty())
        {
            auto card = selfVec->at(selfVec->size()-1);
            if(!card->getIsOpen())
            {
                card->openCardWithAction();
            }
        }
        
        //
    }
    else if(beforePosId==(int)CardPos::CARD_POS_WAIT_SHOW)
    {//需要移动
        auto waitShowPoi = SPRITE_M->getWaitShowPoi();
        int dx = 0;
        for(int i = selfVec->size()-1;i>=0 ;--i)
        {
            auto card = selfVec->at(i);
            card->setCardLocalZOrder(localZ+i);
            if(i >= selfVec->size()-2)
            {
                waitShowPoi.x -= dx*OffsetWait;
                dx++;
                if((waitShowPoi-card->getPosition()).length() < 20)
                {//在指定位置
                    
                }
                else
                {//不在指定位置 前移
                    auto move = MoveBy::create(0.2, Vec2(OffsetWait,0));
                    card->runAction(move);
                }
            }
            else
            {
                
            }
            
        }
    }
    else if(beforePosId==(int)CardPos::CARD_POS_WAIT)
    {//收牌区 和发牌等待区 只改变层次就好了
        auto waitPoi = SPRITE_M->getWaitPoi();
        auto x = selfVec->size()-9;
        int j = x>=0?0:9-selfVec->size();
        for(int i = 0;i< selfVec->size();++i)
        {
            auto card = selfVec->at(i);
            card->setCardLocalZOrder(localZ+i);
            card->getShaderS()->setColor(WaitPokerColor[(selfVec->size()-1==i)?8:UIUtils::clamp(i, 0, 8)]);
//            card->getShaderS()->setColor(WaitPokerColor[j]);//0-8
//            if(x >= 0&&i>=x)
//            {
//                j++;
//            }
//            else if(x<0)
//            {
//                j++;
//            }
            Vec2 endPos = SPRITE_M->getWaitCardPos(i);
            card->setPosition(endPos);
            
        }
    }
    else if(beforePosId==(int)CardPos::CARD_POS_A)
    {//收牌区 和发牌等待区 只改变层次就好了
        auto waitPoi = SPRITE_M->getWaitPoi();
        for(int i = 0;i< selfVec->size();++i)
        {
            auto card = selfVec->at(i);
            card->setCardLocalZOrder(localZ+i);
        }
    }
}

void CardSprite::playFaPai(int idx)
{
    auto trackEntry = _skeletonNode->setAnimation(0, StringUtils::format("flight%d",idx), false);
    _skeletonNode->setTrackEndListener(trackEntry,[this](spTrackEntry* entry){
        if(isFaPaiAni)
        {
            isFaPaiAni = false;
            _skeletonNode->setScaleX(1);
        }
    });
    if(DATA_M->getIsLeftModel())
    {//左手模式开启翻转
        isFaPaiAni = true;
        _skeletonNode->setScaleX(-1);
    }
    
}

int CardSprite::getPos() const {
    return _pos;
}

int CardSprite::getTeachLZOrder() const {
    return teach_lZOrder;
}

void CardSprite::setTeachLZOrder(int teachLZOrder) {
    teach_lZOrder = teachLZOrder;
    this->setCardLocalZOrder(this->c_localZOrder);
}
