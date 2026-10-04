//
//  RankFashTank.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/12.
//

#include <stdio.h>
#include "RankFashTank.h"

#include "../../Fish/Fish0.h"
#include "../../Fish/ShadowsFish.h"
#include "DataManager.h"
#include "MainLobby.h"
#include "GameViewHD.hpp"
#include "RankItem.h"
#include "PlayerManager.h"
#include "ShopManager.h"
#include "RankView.h"
#include "FishManager.h"

RankFashTank::~RankFashTank()
{
    
}

RankFashTank::RankFashTank()
:BaseLayer("2021FashTank_0.csb")
{
    
}

void RankFashTank::initRankFashTank(RankItem* rankItem,RankView* rankView)
{
    _rankItem = rankItem;
    _rankView = rankView;
    auto key = _rankItem?_rankItem->getUserKey():_rankView->getUserKey();
    //机器人key开头时rob
    auto str = key.substr(0,3);
    if(str == "rob")
    {
        _isJiQiRen = true;
    }
    else
    {
        _isJiQiRen = false;
    }
    
    Node_Fish = getNode("Node_Fish");
    Node_Start = getNode("Node_fishStartPoi");
    Node_Shadows = getNode("Node_Shadows");
    
    _currentFashTankIdx = _rankItem?_rankItem->getFashTankId():_rankView->getFashTankId();
    gameBg = Sprite::create();
    createBg();
    auto size = Director::getInstance()->getWinSize();
    gameBg->setContentSize(size);
    
    if (UIUtils::IsPad()) {
        gameBg->setPosition(Vec2(vSize.width/2, vSize.height/2));
    }
    else {
        gameBg->setAnchorPoint(Vec2::ZERO);
    }
    getNode("Node_bg")->addChild(gameBg, -1);
    clearFish();
    createFish();
    
    
    ceshiId = 0;
    
    
    
    
    getNode<Text*>("Text_lv_num")->setString(StringUtils::format("%d",_rankItem?_rankItem->getLevel():_rankView->getLevel()));
    auto Text_name = getNode<Text*>("Text_name");
    Text_name->setString(toString(_rankItem?_rankItem->getScore():_rankView->getScore()));
    UIUtils::textAdaptiveSize(Text_name,250);
    
    //多语言
    auto Text_lv_str = getNode<Text*>("Text_lv_str");
    Text_lv_str->setString(Lang("100200"));
    UIUtils::textAdaptiveSize(Text_lv_str,150);
    //getNode<Text*>("Text_name")->setString(Lang("100328"));
    auto Text_back = getNode<Text*>("Text_back");
    Text_back->setString(Lang("100337"));
    UIUtils::textAdaptiveSize(Text_back,250);
    auto Text_fishNum = getNode<Text*>("Text_fishNum");
    Text_fishNum->setString(StringUtils::format("%d/25",(int)_fishVec.size()));
    UIUtils::textAdaptiveSize(Text_fishNum,175);
    auto Text_country = getNode<Text*>("Text_country");
    Text_country->setString(StringUtils::format(Lang("100351").c_str(), _rankItem?_rankItem->getCy().c_str():
                                                _rankView->getCy().c_str()));
    UIUtils::textAdaptiveSize(Text_country,180);

#if (COCOS2D_DEBUG>0)
    auto uuidText = Text::create();
    uuidText->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    uuidText->setFontSize(40);
    uuidText->setPosition(Vec2(20, 100));
    this->addChild(uuidText);
    uuidText->setString(key);
#endif
}

void RankFashTank::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    
    //设置一些参数
    _listener = EventListenerTouchOneByOne::create();
    _listener->onTouchBegan = CC_CALLBACK_2(RankFashTank::myTouchBegan,this);
    _listener->onTouchMoved = CC_CALLBACK_2(RankFashTank::myTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(RankFashTank::myTouchEnded, this);
    _listener->onTouchCancelled = CC_CALLBACK_2(RankFashTank::myTouchEnded, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, -127);
    
    schedule(CC_CALLBACK_1(RankFashTank::Update, this),"update");
    
    
}

void RankFashTank::initData()
{
    BaseLayer::initData();
    setName("GameBackground");
}

void RankFashTank::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
    if(btnName == "Button_back")
    {
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_yes")
    {
        
    }
}

void RankFashTank::updateUI()
{
    
}

void RankFashTank::updateDYY()
{
    
}

void RankFashTank::onEnter()
{
    BaseLayer::onEnter();
}

void RankFashTank::onExit()
{
    BaseLayer::onExit();
    _eventDispatcher->removeEventListener(_listener);
}

bool RankFashTank::myTouchBegan(Touch * touch, Event * e)
{
    auto touchPoi = touch->getLocation();
    auto gameView = SCENE_M->getGameView();
    
    if(gameView->isVisible())
    {//在游戏中 判断一下点没点到牌

        SCENE_M->clickEff(touchPoi);
    }
    else
    {
        SCENE_M->clickEff(touchPoi);
    }
    
    
    
//    auto lobby = SCENE_M->getLobby();
//    if(!lobby->isVisible()) return true;
    auto fishArr = Node_Fish->getChildren();
    
    Vector<Fish0*> fishVec;
    for(int i = 0;i < fishArr.size();++i)
    {
        auto item = dynamic_cast<Fish0*>(fishArr.at(i));
        if(!item)continue;
        if(item->getIsStart())continue;
        if(!item->getIsTouch())continue;
        auto rect = item->getWorldRect();
        if(rect.containsPoint(touchPoi))
        {
            fishVec.pushBack(item);
        }
    }
    Fish0* fish = NULL;
    for(int i = 0;i < fishVec.size();++i)
    {
        auto item = fishVec.at(i);
        if(fish == NULL)
        {
            fish = item;
        }
        else
        {
            auto ZOrder0 = item->getLocalZOrder();
            auto ZOrder1 = fish->getLocalZOrder();
            if(ZOrder0 > ZOrder1)
            {//item还要在上边
                fish =item;
            }
        }
    }
    
    if(fish != NULL)
    {
        fish->jiaSu();
    }
    
    return true;
}

void RankFashTank::myTouchMoved(Touch * touch, Event * e)
{
    
}

void RankFashTank::myTouchEnded(Touch * touch, Event * e)
{
    
}

void RankFashTank::myTouchCancelled(Touch * t, Event * e)
{
    
}

void RankFashTank::weishi()
{
    auto size = Director::getInstance()->getWinSize();
    Vec2 poi = size/2;
    poi.x = random(poi.x - 200, poi.x + 200);
    poi.y = random(poi.y - 200, poi.y + 200);

    auto fishArr = Node_Fish->getChildren();
    Vector<Fish0*> weiShiVec;
    for(int i = 0;i < fishArr.size();++i)
    {
        auto item = dynamic_cast<Fish0*>(fishArr.at(i));
        //恢复30点血
        if(!item)continue;
        //满血的就别吃了
        if(!item->getIsWeiShi())continue;
        weiShiVec.pushBack(item);
        //item->restoreHp(30);
        //item->weiShi(poi);
    }
    
    std::random_shuffle(weiShiVec.begin(), weiShiVec.end(), UIUtils::myrandom);
    for(int i = 0;i < weiShiVec.size();++i)
    {
        auto item = weiShiVec.at(i);
        if(i == 0)
        {
            item->weiShi(poi,false,Lang("100350"));
        }
        else if(i == weiShiVec.size() - 1)
        {
            item->weiShi(poi,true);
        }
        else
        {
            item->weiShi(poi,false);
        }
    }
    
}

bool RankFashTank::isFishY(Vec2 poi,bool isLeft)
{//让鱼更分散
    int num = 0;
    for(int i = 0;i < _fishVec.size();++i)
    {
        auto item = _fishVec.at(i);
        auto itemPoi = item->getPosition();
        auto itemIsLeft = item->getIsLeft();
        if(itemIsLeft == isLeft&&(itemPoi-poi).length() < 500&&fabsf(poi.y-itemPoi.y) < 100)
        {//离得有点进了 在看看y
            num++;
        }
    }
    
    return num < 3;
}

void RankFashTank::createBg()
{
    _tempSelfPos = DEFAULTPOS;
    FileNode_fitting2_7 = NULL;
    
    auto lv = _rankItem?_rankItem->getLevel():_rankView->getLevel();
    vector<bool> isFashTankUnlockVec;
    if(_isJiQiRen)
    {//机器人的话 根据等级 选择最高解锁的鱼缸
        _currentFashTankIdx = ShopManager::getInstance()->getMaxFashTankIdx(lv);
        isFashTankUnlockVec = updateJiQiFashTankUnlock();
    }
    else
    {
        isFashTankUnlockVec = _rankItem?_rankItem->getIsFashTankUnlockVec():_rankView->getIsFashTankUnlockVec();
    }
    
    gameBg->removeAllChildren();
    auto node = UIUtils::createCSBNode(StringUtils::format("desktop/scene%d",_currentFashTankIdx) + (UIUtils::IsPad()?"_pad.csb":".csb"), "loop", true);
    gameBg->addChild(node);
    auto safeArea = Director::getInstance()->getSafeAreaRect();
    //设置为屏幕大小
    node->setContentSize(safeArea.size);
    node->setPosition(Vec2::ZERO);
    cocos2d::ui::Helper::doLayout(node);
    auto Panel_top = node->getChildByName("Panel_top");
    if(Panel_top)
    {
        Panel_top->setVisible(false);
    }
    
    auto fishTypeVec = _rankItem?_rankItem->getFishVec():_rankView->getFishVec();
    //计算
    auto fishStr = ShopManager::getInstance()->getFashTankFishNum(_currentFashTankIdx);
    auto fishVec = UIUtils::split(fishStr,",");
    string aniName = "loop";
    for(int i = 1;i < isFashTankUnlockVec.size();++i)
    {
        bool isUnlock = isFashTankUnlockVec.at(i-1);
        auto fitting = FIND_NODE(Node *,node,StringUtils::toString(i));
        auto FileNode_fitting = FIND_NODE(Node *,node,StringUtils::format("FileNode_%d",i));
        if(isUnlock&&i != 0)
        {
            aniName = StringUtils::format("idle%d",i - 1);
        }
        if(fitting)
        {
            fitting->setVisible(isUnlock);
            if(_currentFashTankIdx == 3&&i == 9)
            {
                auto parent = fitting->getParent();
                auto scaleX = parent->getScaleX();
                auto scaleY = parent->getScaleY();
                auto worldPos = fitting->getPosition();
                worldPos = parent->convertToWorldSpace(worldPos);
                fitting->removeFromParentAndCleanup(false);
                Node_Fish->addChild(fitting, -1);
                worldPos = Node_Fish->convertToNodeSpace(worldPos);
                fitting->setPosition(worldPos);
                fitting->setScale(scaleX, scaleY);
            }
            
        }
        else if(FileNode_fitting)
        {
            FileNode_fitting->setVisible(isUnlock);
            UIUtils::playInnerAction(FileNode_fitting,"loop",true);
            
            if(_currentFashTankIdx == 2&&i == 7)
            {
                FileNode_fitting2_7 = FileNode_fitting;
                fishZXMove();
            }
        }
    }
    
    UIUtils::playInnerAction(node,aniName,false);
}

void RankFashTank::clearFish()
{
    for(int i = 0;i < _fishVec.size();++i)
    {
        auto fish = _fishVec.at(i);
        fish->removeFromParent();
    }
    for(int i = 0;i < _fishSVec.size();++i)
    {
        auto fishS = _fishSVec.at(i);
        fishS->removeFromParent();
    }
    _fishVec.clear();
    _fishSVec.clear();
}

void RankFashTank::createFish()
{
    auto fishTypeVec = _rankItem?_rankItem->getFishVec():_rankView->getFishVec();
    auto isDailyVec = _rankItem?_rankItem->getIsDailyVec():_rankView->getIsDailyVec();
    //_fishVec = Vector<Fish0>();
    _fishVec.clear();
    _fishSVec.clear();
    
    //离线时间
    auto offlineTime = DATA_M->getOfflineTime();
    Vector<Fish0*> tempVec;
    for(int i = 0;i < fishTypeVec.size();++i)
    {
        auto type = fishTypeVec.at(i);
        auto isDaily = i < isDailyVec.size()?isDailyVec.at(i):false;
        auto fish = Fish0::createFish(NULL,this,i,(DataManager::FishType) type,offlineTime);//
        fish->setIsDaily(isDaily,true);
        auto shadows = ShadowsFish::createLayerN(fish);
        Node_Shadows->addChild(shadows);
        Node_Fish->addChild(fish);
        fish->setShadows(shadows);
        
        
        tempVec.pushBack(fish);
        _fishVec.pushBack(fish);
        _fishSVec.pushBack(shadows);
    }
    
    
    auto rand = 10;
    std::random_shuffle(tempVec.begin(), tempVec.end(), UIUtils::myrandom);
    //随便选一个翻白的
    bool isDuiHua = true;
    if(_fishVec.size() >= rand)
    {//随机选几个在中间
        for(int i = 0;i < tempVec.size();++i)
        {
            auto item = tempVec.at(i);
            if(isDuiHua)
            {
                isDuiHua = false;
                
            }
            if(i < rand)
            {
                item->fishZXMove();
            }
            else
            {
                item->fishMove();
            }
        }
    }
    else
    {//都在中间吧
        for(int i = 0;i < tempVec.size();++i)
        {
            auto item = tempVec.at(i);
            if(isDuiHua)
            {
                isDuiHua = false;
                
            }
            item->fishZXMove();
        }
    }
}

void RankFashTank::fishMove()
{
    _isAngle = true;
    auto moveSpeed = random(30.0f,100.0f);
    auto vec = getRoute();
    int PointCount = 10;//
    auto bezvec = ComputeBezier(vec[0],vec[1],vec[2] ,vec[3],PointCount);
    //求出长度
    int bezierLen = (int)BezierLenth(bezvec, PointCount+1);
    
    auto _time = bezierLen / moveSpeed;
    //阴影高度
    auto y = vec[0].y;
    auto a = y/1920.f;
    y = a * 1920.f / 3.f;
    FileNode_fitting2_7->setPosition(vec[0]);
    ccBezierConfig config;
    config.controlPoint_1 = vec[1];
    config.controlPoint_2 = vec[2];
    config.endPosition = vec[3];
    auto bez = BezierTo::create(_time, config);
    
    
    auto fishNum = DATA_M->getFishNum();

    auto randTime = random(1.0f, 3.0f);
    auto deTime = DelayTime::create(randTime);
    auto func = CallFunc::create([this](){
        fishMove();
    });
    
    auto seq = Sequence::create(deTime,bez,func, NULL);
    auto _fishActionSpeed = Speed::create(seq,1);
    
    FileNode_fitting2_7->runAction(_fishActionSpeed);
}

void RankFashTank::fishZXMove()
{
    _isAngle = true;
    auto moveSpeed = random(30.0f,100.0f);
    
    //计算起点
    auto vec = getRoute();
    auto randModel = random(0, 1);
    //判定 是否向左移动
    bool isLeft = vec[1].x > vec[2].x;
    
    Vec2 p0,p1,p2,p3;
    if(randModel == 0)
    {//只有一个控制点
        float randX = 0;
        if(isLeft)
        {
            randX = random(vec[2].x + 80,vec[1].x);
        }
        else
        {
            randX = random(vec[1].x,vec[2].x - 80);
        }
        auto y = random(vec[2].y-50, vec[2].y + 50);
        
        p0 = Vec2(randX,y);
        p1 = vec[2];
        p2 = vec[2];
        p3 = vec[3];
    }
    else
    {//有两个控制点
        float randX = 0;
        if(isLeft)
        {
            randX = random(vec[1].x + 80,1000.0f);
        }
        else
        {
            randX = random(80.0f,vec[1].x - 80);
        }
        auto y = random(vec[1].y-50, vec[1].y + 50);
        p0 = Vec2(randX,y);
        p1 = vec[1];
        p2 = vec[2];
        p3 = vec[3];
    }
    
    FileNode_fitting2_7->setPosition(p0);
    
    int PointCount = 10;//
    auto bezvec = ComputeBezier(p0,p1,p2 ,p3,PointCount);
    //求出长度
    int bezierLen = (int)BezierLenth(bezvec, PointCount+1);
    
    auto _time = bezierLen / moveSpeed;
    //阴影高度
    auto y = p0.y;
    auto a = y/1920.f;
    y = a * 1920.f / 3.f;
    FileNode_fitting2_7->setPosition(p0);
    
    ccBezierConfig config;
    config.controlPoint_1 = p1;
    config.controlPoint_2 = p2;
    config.endPosition = p3;
    auto bez = BezierTo::create(_time, config);
    auto randTime = 0;
    
    auto deTime = DelayTime::create(randTime);
    auto func = CallFunc::create([this](){
        fishMove();
    });
    
    auto seq = Sequence::create(deTime,bez,func, NULL);
    auto _fishActionSpeed = Speed::create(seq,1);
    
    FileNode_fitting2_7->runAction(_fishActionSpeed);
}


vector<Vec2> RankFashTank::getRoute()
{
    vector<Vec2> vecs = vector<Vec2>();
    
    if(!_isLeft)
    {
        scaleY = -1;
    }
    else
    {
        scaleY = 1;
    }
    FileNode_fitting2_7->setScaleY(scaleY);
    auto rect = FileNode_fitting2_7->getChildByName("qianting0_1")->getBoundingBox();
    auto x0 = -rect.size.width - 100;
    auto x1 = random(333-150, 333 + 150);
    auto x2 = random(766-150, 766 + 150);
    auto x3 = 1080 + rect.size.width + 100;
    
    auto tempY = 0;
    auto y0 = 0;
    auto y1 = 0;
    auto y2 = 0;
    auto y3 = 0;
    
    auto min = 450.f;
    auto max = 650.f;
    if(UIUtils::IsPad())
    {
        auto scaleMin = min/1920.f;
        auto scaleMax = max/1920.f;
        min = scaleMin * 1440.f;
        max = scaleMax * 1440.f;
    }
    tempY = random(min,max);//1625;
    
    auto dy = UIUtils::IsPad()?70:100;
    y0 = random(tempY-dy, tempY + dy);
    y1 = random(tempY-dy, tempY + dy);
    y2 = random(tempY-dy, tempY + dy);
    y3 = random(tempY-dy, tempY + dy);
    Vec2 poi0;
    if(!_isLeft)
    {//左到右
        poi0 = Vec2(x0,y0);
    }
    else
    {//右到左
        poi0 = Vec2(x3,y3);
    }
    
    if(!_isLeft)
    {//左到右
        vecs.push_back(Vec2(x0,y0));
        vecs.push_back(Vec2(x1,y1));
        vecs.push_back(Vec2(x2,y2));
        vecs.push_back(Vec2(x3,y3));
    }
    else
    {//右到左
        vecs.push_back(Vec2(x3,y3));
        vecs.push_back(Vec2(x2,y2));
        vecs.push_back(Vec2(x1,y1));
        vecs.push_back(Vec2(x0,y0));
    }
    _isLeft = !_isLeft;
    return vecs;
}

Vec2 RankFashTank::PointOnCubicBezier(Vec2* cp, float t)
{
    float ax, bx, cx; float ay, by, cy;
    float tSquared, tCubed; Vec2 result;
    /* 计算多项式系数 */
    cx = 3.0 * (cp[1].x - cp[0].x);
    bx = 3.0 * (cp[2].x - cp[1].x) - cx;
    ax = cp[3].x - cp[0].x - cx - bx;
    cy = 3.0 * (cp[1].y - cp[0].y);
    by = 3.0 * (cp[2].y - cp[1].y) - cy;
    ay = cp[3].y - cp[0].y - cy - by;
    /* 计算t位置的点值 */
    tSquared = t * t;
    tCubed = tSquared * t;
    result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + cp[0].x;
    result.y = (ay * tCubed) + (by * tSquared) + (cy * t) + cp[0].y;
    return result;
}
 
 
std::vector<Vec2> RankFashTank::ComputeBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments)
{
    std::vector<Vec2> vertices;

    float t = 0;
    for (unsigned int i = 0; i < segments; i++)
    {
        vertices.push_back(Vec2(powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x, powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y));
//        vertices[i].x = powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
//        vertices[i].y = powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y;
        t += 1.0f / segments;
    }
    vertices.push_back(Vec2(destination.x, destination.y));
//    vertices[segments].x = destination.x;
//    vertices[segments].y = destination.y;
    return vertices;
}

float RankFashTank::BezierLenth(const std::vector<Vec2> &points, int points_count)
{
    float len = 0;
    for (int i = 0; i<points_count; i++) {
 
        Vec2 nowP = points[i];
        Vec2 preP;
        if (i != 0) {
            preP = points[i - 1];
 
            Vec2 dis = nowP - preP;
            //distance就是两点距离
            float distance = sqrt(pow(dis.x, 2) + pow(dis.y, 2));
 
            len += distance;
        }
        else {
            preP = Point(0,0);
        }
    }
 
    return len;
}

void RankFashTank::Update(float dt)
{
    if(FileNode_fitting2_7)
    {
        auto selfPos = FileNode_fitting2_7->getPosition();
        auto length = (_tempSelfPos-selfPos).length();
        //角度
        Vec2 a(590,1060);
        auto angle = UIUtils::getAngle(_tempSelfPos,selfPos);
        FileNode_fitting2_7->setRotation(angle + 90);

        _tempSelfPos = selfPos;
    }
    
}

std::vector<bool> RankFashTank::updateJiQiFashTankUnlock()
{
    auto shopManager = ShopManager::getInstance();
    auto fishManager = FishManager::getInstance();
    
    auto fishTypeVec = _rankItem?_rankItem->getFishVec():_rankView->getFishVec();
    
    float num = 0.f;
    for(int i = 0;i < fishTypeVec.size();++i)
    {
        auto fishId = fishTypeVec.at(i);
        auto lv = fishManager->getUnlockLv(fishId);
        float f = (float)lv/NPC_NUM;
        auto str = UIUtils::getFloatStr(f,1);
        f = std::stof(str);
        num = num + f;
    }
    auto fishStr = shopManager->getFashTankFishNum(_currentFashTankIdx);
    auto fishVec = UIUtils::split(fishStr,",");
    
    vector<bool> unlockVec;
    unlockVec.push_back(true);
    for(int i = 1;i < fishVec.size();++i)
    {
        auto str = fishVec.at(i);
        if(str == "")continue;
        auto fishNum = std::stof(str);
        bool isUnlock = num >= fishNum;
        
        unlockVec.push_back(isUnlock);
    }
    return unlockVec;
}
