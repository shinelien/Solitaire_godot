//
// Created by Cyutao on 2018/11/25.
//

#include "WinHD.h"
#include "SpriteManager.h"
#include "TeachManager.h"
#include "AtlasManager.h"
USING_NS_CC;

// Bezier cubic formula:
//    ((1 - t) + t)3 = 1
// Expands to ...
//   (1 - t)3 + 3t(1-t)2 + 3t2(1 - t) + t3 = 1
static inline float bezierat( float a, float b, float c, float d, float t )
{
    return (powf(1-t,3) * a +
            3*t*(powf(1-t,2))*b +
            3*powf(t,2)*(1-t)*c +
            powf(t,3)*d );
}

bool WinHD::init() {
    setName("WinHD");
    // 初始化 rendertexture
    auto winSize = Director::getInstance()->getWinSize();
    setPosition(winSize/2);
    setContentSize(winSize);
    scheduleOnce([winSize, this](float){
        auto renderTex = RenderTexture::create(winSize.width, winSize.height);
        renderTex->setPosition(winSize/2);
        this->addChild(renderTex);
        _renderTex = renderTex;
    }, 0.0001f, "winhd_scheduleonce_key");
    auto bgSprite = Sprite::create();
    this->addChild(bgSprite);
    bgSprite->schedule([this, bgSprite](float t){
        if (_renderTex==nullptr || !this->isVisible()) return;
        
        _renderTex->begin();
        for (auto node:_renderTex->getChildren()) {
            if (node->getName() == "CardSprite")
                node->visit();
        }
        _renderTex->end();
        bgSprite->setTexture(_renderTex->getSprite()->getTexture());
    }, 0, "card_update");

    return Widget::init();
}

void WinHD::showWinAction(const Vec2 &pos, int num, int suit, float delay) {
    auto winSize = Size(pos.x, pos.y);
    auto cardSprite = UIUtils::createCSBNode("card/CardFace.csb");
    cardSprite->setName("card");
    auto _sprite1 = cardSprite->getChildByName<Sprite*>("Sprite_face");
    auto _sprite2 = _sprite1->getChildByName<Sprite*>("Sprite_num");
    auto _sprite3 = _sprite1->getChildByName<Sprite*>("Sprite_color");
    _sprite1->setSpriteFrame(AtlasManager::getInstance()->getSF(2, num, suit, 0));
    _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5, num, suit, 0));
    _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6, num, suit, 0));
    _sprite2->setColor(UIUtils::getCardColor(suit));
    auto size2 = _sprite2->getContentSize();
    _sprite2->setPositionX(size2.width*0.5f);
    
    //auto cardSprite = Sprite::createWithSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(num, suit));
    if (UIUtils::IsPad()) {
        cardSprite->setScale(0.90, 0.90);
    }
    cardSprite->setName("CardSprite");
    
    auto curPos = pos;
    cardSprite->setPosition(curPos);
    _renderTex->addChild(cardSprite);

    auto dir = DATA_M->getIsLeftModel()?-1:1;
    auto offsetX = dir*Director::getInstance()->getWinSize().width/6;
    auto totalCNT = 8;

    int i=0;
    float offsetY = ( i==0 ? (1.0/totalCNT) : ((1.0*totalCNT-i)/totalCNT) )*winSize.height;
    Vec2 destPos(offsetX, 0-pos.y);
    Vec2 p1(0, offsetY);
    Vec2 p2(offsetX, offsetY);
    float totalT = 0, dy = 1./60;
    cardSprite->schedule([cardSprite, curPos, p1, p2, destPos, totalT, winSize, totalCNT, i, offsetX, offsetY, dy](float t) mutable {
        totalT+=dy;
        float x = curPos.x+bezierat(0, p1.x, p2.x, destPos.x, totalT);
        float y = curPos.y+bezierat(0, p1.y, p2.y, destPos.y, totalT);
//        CCLOG("wtf bezierat %.2f-%.2f", x, y);
        cardSprite->setPosition(x, y);
        if (y<=0) {
            ++i;
            if (i>=totalCNT) {
//                cardSprite->removeFromParent();
                cardSprite->unschedule("cardSprite_update");
                return;
            }
            dy *= 1.1;
            totalT = 0;
            offsetY = ( i==0 ? (1.0/totalCNT) : ((1+1.*totalCNT-i)/totalCNT) )*winSize.height;
            curPos = cardSprite->getPosition();
            destPos = Vec2(offsetX, 0);
            p1 = Vec2(0, offsetY);
            p2 = Vec2(offsetX, offsetY);
        }
    }, delay, "cardSprite_update");
//    cardSprite->runAction(MoveTo::create(1, Vec2(winSize.width, 0)));
}

void WinHD::show(std::function<void(cocos2d::Ref*)> cb) {
    auto rand = 1;
    auto isAll = DATA_M->getIsEndAniAll();
    if(!isAll)
    {
        rand = DATA_M->getEndAniIdx();
    }//random(3, 8);
    else
    {
        rand = random(1, 7);
    }
    if(TEACH_M->isTeaching("firstBureau"))
    {
        rand = 5;//random(2, 7);
    }
    _renderTex->clear(0, 0, 0, 0);
    _renderTex->removeAllChildren();
    if(rand == 1)//<= 2)
    {
        for (int i = 3; i >=0; --i) {
            auto pos = SPRITE_M->aSprite[i]->convertToWorldSpaceAR(Vec2::ZERO);
            if (!SPRITE_M->aCardVector[i].empty()) {
                auto card = SPRITE_M->aCardVector[i].back();
                showWinAction(pos, card->getNumber(), card->getColNum(), 0);
            }
            else {
                showWinAction(Vec2(100+i*100, 1600), 13, 1, 0);
            }
        }
    }
    else if(rand == 2)
    {
        SPRITE_M->pokerEndAni1();
    }
    else if(rand == 3)
    {
        SPRITE_M->pokerEndAni2();
    }
    else if(rand == 4)
    {
        SPRITE_M->pokerEndAni3();
    }
    else if(rand == 5)
    {
        SPRITE_M->pokerEndAni4();
    }
    else if(rand == 6)
    {
        SPRITE_M->pokerEndAni5();
    }
    else if(rand == 7)
    {
        SPRITE_M->pokerEndAni6();
    }
    

    setTouchEnabled(true);
    addClickEventListener([this, cb](Ref* ref){
        this->unschedule("scheduleonce_key_end");
        setTouchEnabled(false);
        if (cb) cb(ref);
    });
    scheduleOnce([this, cb](float){
        setTouchEnabled(false);
        if (cb) cb(nullptr);
    }, 5, "scheduleonce_key_end");
}
