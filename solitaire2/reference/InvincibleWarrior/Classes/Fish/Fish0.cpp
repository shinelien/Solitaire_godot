//
//  Fish0.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by 宋 on 2021/4/17.
//

#include <stdio.h>
#include "Fish0.h"
#include "GameBackground.h"
#include "UIUtils.h"
#include "ShadowsFish.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "FishManager.h"
#include "RankFashTank.h"

Fish0* Fish0::createFish(GameBackground* fishTank,RankFashTank* rankFashTank,int id,DataManager::FishType type,int offlineTime)
{
    Fish0* fish = new Fish0(fishTank,rankFashTank,id,type,offlineTime);
    if(fish&&fish->init())
    {
        return fish;
    }
    return NULL;
}

Fish0::Fish0(GameBackground* fishTank,RankFashTank* rankFashTank,int id,DataManager::FishType type,int offlineTime)//
:BaseLayer("fish/fish.csb")
{
    ceshiId = 0;
    _duiHuaIndex = 0;
    _isPlayText = false;
    _fishTank = fishTank;
    _rankFashTank = rankFashTank;
    _fishId = id;
    _fishLv = 1;
    _type = type;
    _fashTankIdx = DATA_M->getCurrentFashTankIdx();
    _fishMaxHp = 60;
    _fishHp = 60;
    _dieTime = 0;
    _isDie = false;
    _isDaily = false;
    if(_fishTank)
    {
        _fishHp = GETINTEGER(StringUtils::format("fish_hp_%d_%d", _fashTankIdx,_fishId).c_str(),60);
        _dieTime = GETINTEGER(StringUtils::format("fish_dieTime_%d_%d", _fashTankIdx,_fishId).c_str(),0);
        _isDie = false;//DATA_M->isFishDie(id);
        _isDaily = GETBOOL(StringUtils::format("fish_isDaily_%d_%d", _fashTankIdx,_fishId).c_str(),false);
    }
    if(offlineTime != 0)
    {
        //看看离线这会儿扣了多少吖
        auto hp = _fishHp;
        auto num = offlineTime/60;
        _fishHp -= num;
        if(_fishHp < 0) _fishHp = 0;
        if(hp > 0&&_fishHp <= 0)
        {//血没了 记录倒计时
            _dieTime = (int)(DATA_M->getContentSec() + 24 * 60 * 60);//24小时
            SETINTEGER(StringUtils::format("fish_dieTime_%d_%d",_fashTankIdx, _fishId).c_str(),_dieTime);
        }
    }
    _fishTime = DATA_M->getContentSec() + 60;
    _tempSelfPos = DEFAULTPOS;
    _isTempDie = _isDie;
    tempSpeed = 2;//0.016
    isStop = false;
    isStopJiaSu = false;
    _isTouch = false;
    _fishMoveType = FishMoveType::None;
    _spTrackEntry = NULL;
    _isLeft = random(0, 1) == 0;
    _oldIsLeft = _isLeft;
    _isJinShi = false;
    _isAngle = true;
    isBar = false;
}

Fish0::~Fish0()
{
    
}

void Fish0::initUI()
{
    BaseLayer::initUI();
    
    this->setVisible(false);
    isDaYu = false;
    if(_type == DataManager::FishType::Fish14)
    {
        isDaYu = true;
    }
    _skeletonNode = FISH_M->getFishSpine((int)_type);
    _skeletonNode->setCompleteListener([this](spTrackEntry* entry) {
        auto endtime = entry->animationEnd;
        auto a = entry->animationLast;
        
        auto c = entry->nextAnimationLast;
        
        auto trackTime = entry->trackTime;
        
        endtime = entry->animationEnd;
        
        endtime = _spTrackEntry->animationEnd;
        a = _spTrackEntry->animationLast;
        
        c = _spTrackEntry->nextAnimationLast;
        
        trackTime = _spTrackEntry->trackTime;
        
        endtime = _spTrackEntry->animationEnd;
        
        if(_fishMoveType == FishMoveType::RUN&&_fishAniType != FishAniType::RUN)
        {
            fishPlayAni("Run",true);
            _fishMoveType = FishMoveType::None;
        }
        else if(_fishMoveType == FishMoveType::UP&&_fishAniType != FishAniType::UP)
        {
            fishPlayAni("Up",true);
            _fishMoveType = FishMoveType::None;
        }
        else if(_fishMoveType == FishMoveType::LOOP&&_fishAniType != FishAniType::LOOP)
        {
            
            fishPlayAni("Loop",true);
            isStopJiaSu = true;
            setFishMoveType(FishMoveType::RUN);
        }
        else if(_fishMoveType == FishMoveType::HAPPY&&_fishAniType != FishAniType::HAPPY)
        {
            fishPlayAni("happy",true);
            _fishMoveType = FishMoveType::None;
        }
        else if(_fishMoveType == FishMoveType::Stay)
        {
            fishPlayAni("Run",true);
            tempSpeed = 2;
            _isJiaSu = true;
            _jiaSuTime = 2;
            _fishActionSpeed->setSpeed(0.3f);
            _fishMoveType = FishMoveType::None;
        }
        else if(_fishMoveType == FishMoveType::Rush)
        {//自身加速
            fishPlayAni("Up",true);
            tempSpeed = 2;
            _isJiaSu = true;
            _jiaSuTime = 1.5f;
            _fishActionSpeed->setSpeed(2.5f);
            setFishMoveType(FishMoveType::RUN);
        }
        else if(_fishMoveType == FishMoveType::Admission)
        {
            _fishMoveType = FishMoveType::Admission2;
            fishPlayAni("happy",false);
            _fishMoveType = FishMoveType::None;
        }
        else if(_fishMoveType == FishMoveType::Admission2)
        {
            isStart = false;
            _isTouch = true;
            fishPlayAni("Run",true);
            auto move2 = MoveTo::create(move2Time, move2Vec);
            auto func = CallFunc::create([this](){
                fishMove();
            });
            auto seq = Sequence::create(move2,func, NULL);
            _fishActionSpeed = Speed::create(seq,1);
            runAction(_fishActionSpeed);
            _fishMoveType = FishMoveType::None;
        }
        else if(_fishMoveType == FishMoveType::WeiShi)
        {
            
            fishPlayAni("Run",true);
            _fishMoveType = FishMoveType::None;
        }
        else if(_fishMoveType == FishMoveType::Stop)
        {
            if(!isStopJiaSu)
            {
                isStopJiaSu = true;
                fishPlayAni("Run",true);
            }
            _fishMoveType = FishMoveType::None;
        }
        else if(_fishMoveType == FishMoveType::Die)
        {
            _isDie = true;
            _isTempDie = _isDie;
            dieAction();
            fishPlayAni("Loop",true);
            _fishMoveType = FishMoveType::None;
        }
        else
        {
            _fishMoveType = FishMoveType::None;
        }
    });
    //_skeletonNode->setScale(0.3f);
    auto Node_spine = getNode("Node_spine");
    Node_spine->addChild(_skeletonNode);
    //Loop  Run  Up  happy
    fishPlayAni("Run",true);
    //"Loop" "Run" "Up" "happy"
    _skeletonNode->setMix("Run", "happy", 0.8);
    _skeletonNode->setMix("Up", "happy", 0.8);
    _skeletonNode->setMix("Loop", "happy", 0.8);
    _skeletonNode->setMix("Run", "Loop", 0.9);
    _skeletonNode->setMix("Up", "Run", 0.5);
    //_skeletonNode->setMix("Loop", "Run", 0.8);
    auto rect = _skeletonNode->getBoundingBox();
    
    
    
    
    
    
    rect = _skeletonNode->getBoundingBox();
    _loadingBar = getNode<LoadingBar*>("LoadingBar");
    auto Node_1 = getNode("Node_1");
    Node_loadingBar = getNode("Node_2");
    auto height = _skeletonNode->getBoundingBox().size.height;
    auto height2 = _loadingBar->getBoundingBox().size.height;
    Node_1->setPosition(Vec2(0,height*0.65f + height2/2));
    Node_loadingBar->setVisible(false);
    
    //对话
    FileNode_DuiHua = getNode("FileNode_DuiHua");
    FileNode_DuiHua->setVisible(false);
    _duiHua = getNode<Text*>("Text_duihua");
    Sprite_DuiHua = getNode<Sprite*>("Sprite_DuiHua");
    Sprite_emoji = getNode<Sprite*>("Sprite_emoji");
    Image_DuiHua = getNode<ImageView*>("Image_1");
    
    Text_rare = getNode<Text*>("Text_rare");
    Text_rare->setVisible(_isDaily);
    thinkTime = random(40.0f,60.0f);
    thinkTempTime = 0;
    _time = 20;
    _isJiaSu = false;
    _jiaSuTime = 0;
    isStart = true;
    isAngle = true;
    
    updateHp();
    
    schedule(CC_CALLBACK_1(Fish0::Update, this),"update");
    schedule(CC_CALLBACK_1(Fish0::updateSec, this),1,"updateSec");
    schedule(CC_CALLBACK_1(Fish0::updateText, this),0.1f,"updateText");
    
    //血条
    schedule([this](float dt){
        if(isBar)
        {
            _percent2+=percentDx * dt;
            if(_percent2 >= _percent)
            {
                isBar = false;
                _percent2 = _percent;
                //隐藏雪条
                Node_loadingBar->setVisible(false);
            }
            _loadingBar->setPercent(_percent2);
        }
    }, 0.017, "scheduler_update_bar");
    
    
    
    updateDYY();
}
void Fish0::initData()
{
    BaseLayer::initData();
}

Vec2 Fish0::PointOnCubicBezier(Vec2* cp, float t)
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
 
 
std::vector<Vec2> Fish0::ComputeBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments)
{
//    Vec2* vertices = new (std::nothrow) Vec2[segments + 1];
    std::vector<Vec2> vertices;
    float t = 0;
    for (unsigned int i = 0; i < segments; i++)
    {
        vertices.push_back(Vec2(powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x, powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y));
        t += 1.0f / segments;
    }
    vertices.push_back(Vec2(destination.x, destination.y));
    return vertices;
}

float Fish0::BezierLenth(const std::vector<Vec2> &points, int points_count)
{
    float len = 0;
    for (int i = 0; i<points_count; i++) {
 
        Vec2 nowP = points.at(i);
        Vec2 preP;
        if (i != 0) {
            preP = points.at(i - 1);
 
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

void Fish0::fishMove()
{
//    if(_isDie)
//    {
//        dieStart();
//        return;
//    }
    _isAngle = true;
    _isTouch = true;
    _fishMoveType = FishMoveType::None;
    moveSpeed = random(30.0f,100.0f);
    fishPlayAni("Run",true);
    auto vec = getRoute();
    int PointCount = 10;//
    auto bezvec = ComputeBezier(vec[0],vec[1],vec[2] ,vec[3],PointCount);
    //求出长度
    int bezierLen = (int)BezierLenth(bezvec, PointCount+1);
    
    _time = bezierLen / moveSpeed;
    //阴影高度
    auto y = vec[0].y;
    auto num = UIUtils::IsPad()?1440.f:1920.f;
    auto a = y/num;
    y = a * num/ 3.f;
    _shadows->setPositionY(y);
    this->setPosition(vec[0]);
    ccBezierConfig config;
    config.controlPoint_1 = vec[1];
    config.controlPoint_2 = vec[2];
    config.endPosition = vec[3];
    auto bez = BezierTo::create(_time, config);
    auto randTime = random(1.0f, 15.0f);
    
    
    auto fishNum = DATA_M->getFishNum();
    if(isStart)
    {
        isStart = false;
        auto maxTime = fishNum > 10 ? 15.0f:6.0f;
        randTime = random(1.0f, maxTime);
    }
    else
    {
        randTime = random(1.0f, 3.0f);
    }
    auto deTime = DelayTime::create(randTime);
    auto func = CallFunc::create([this](){
        fishMove();
    });
    
    auto seq = Sequence::create(deTime,bez,func, NULL);
    _fishActionSpeed = Speed::create(seq,1);
    
    this->runAction(_fishActionSpeed);
}

void Fish0::fishZXMove()
{
//    if(_isDie)
//    {
//        dieStart();
//        return;
//    }
    _isAngle = true;
    _isTouch = true;
    _fishMoveType = FishMoveType::None;
    moveSpeed = random(30.0f,100.0f);
    fishPlayAni("Run",true);
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
    
    this->setPosition(p0);
    
    int PointCount = 10;//
    auto bezvec = ComputeBezier(p0,p1,p2 ,p3,PointCount);
    //求出长度
    int bezierLen = (int)BezierLenth(bezvec, PointCount+1);
    
    _time = bezierLen / moveSpeed;
    //阴影高度
    auto y = p0.y;
    auto num = UIUtils::IsPad()?1440.f:1920.f;
    auto a = y/num;
    y = a * num / 3.f;
    _shadows->setPositionY(y);
    this->setPosition(p0);
    
    ccBezierConfig config;
    config.controlPoint_1 = p1;
    config.controlPoint_2 = p2;
    config.endPosition = p3;
    auto bez = BezierTo::create(_time, config);
    auto randTime = 0;
    
    isStart = false;
    
    auto deTime = DelayTime::create(randTime);
    auto func = CallFunc::create([this](){
        fishMove();
    });
    
    auto seq = Sequence::create(deTime,bez,func, NULL);
    _fishActionSpeed = Speed::create(seq,1);
    
    this->runAction(_fishActionSpeed);
}

// Update is called once per frame
void Fish0::Update(float dt)
{
    if(isStart)
    {
        return;
    }
    auto selfPos = this->getPosition();
    auto speed = _fishActionSpeed->getSpeed();
    
    if(_tempSelfPos == DEFAULTPOS)
    {
        
    }
    else if(speed != 0)
    {
        auto length = (_tempSelfPos-selfPos).length();
        //角度
        Vec2 a(590,1060);
        auto angle = UIUtils::getAngle(_tempSelfPos,selfPos);
        if(_type == DataManager::FishType::Fish14&&!_isAngle)
        {
            log("shayu");
        }
        if(angle != 0&&length > 0.0005f&&_isAngle)
        {
            _skeletonNode->setRotation(angle + 90);
        }
        if(!this->isVisible())
        {
            this->setVisible(true);
        }
    }
    _tempSelfPos = selfPos;
    if(speed == 0)
    {
        _tempSelfPos = DEFAULTPOS;
        stopMaxTempTime -= dt;
        if(stopMaxTempTime < -3&&!isStopJiaSu&&!_isJinShi)
        {//停留时间超时
            log("停留时间超时,恢复Run");
            isStopJiaSu = true;
            fishPlayAni("Run",true);
        }
    }
    
    
    
    if(_isJiaSu&&!isStop)
    {
        _jiaSuTime-=dt;
        if(_jiaSuTime < 0)
        {
            if(speed > 1)
            {//缓慢减速
                speed -= dt * tempSpeed;
                if(speed < 1)
                {
                    speed = 1;
                    _isJiaSu = false;
                    //fishPlayAni("Run",true);
                }
                _fishActionSpeed->setSpeed(speed);
            }
            else
            {//缓慢加速
                speed += dt * tempSpeed;
                if(speed > 1)
                {
                    speed = 1;
                    _isJiaSu = false;
                }
                _fishActionSpeed->setSpeed(speed);
            }
        }
    }
    else if(isStop)
    {
        if(speed != 0)
        {
            stopTempTime-=dt;
            if(stopTempTime <= 0)stopTempTime = 0;
            speed = stopTempTime/stopTime;
            
            if(speed == 0){
                isStop = false;
                fishPlayAni("Loop",true);
                setFishMoveType(FishMoveType::Stop);
            }
            _fishActionSpeed->setSpeed(speed);
        }
        else
        {
            isStop = false;
            fishPlayAni("Loop",true);
            setFishMoveType(FishMoveType::Stop);
        }
    }
    else if(isStopJiaSu)
    {
        if(speed < 1)
        {
            speed += dt * tempSpeed;
            if(speed >= 1)
            {
                speed = 1;
                isStopJiaSu = false;
            }
            _fishActionSpeed->setSpeed(speed);
        }
    }
    
    
    //考虑加速或者减速
    if(!_isJinShi)
    {//吃东西时停止了思考 翻白了 停止思考
        thinkTempTime+=dt;
        if(thinkTempTime > thinkTime)
        {
            thinkTempTime = 0;
            thinkTime = random(40.0f,60.0f);
            if(speed != 1) return;
            auto rand = random(0,99);
            //特殊运动的鱼太多了 减少一些
            if(rand < 8)
            {//减速
                fishStay();
            }
            else if(rand < 48)
            {//加速
                fishRush();
            }
            else if(rand < 88)
            {
                fishStop();
            }
        }
    }
    
}

void Fish0::updateSec(float dt)
{
    if(!_fishTank)
    {//别人的鱼
        return;
    }
    if(_isDie) return;
    //获取时间 扣血
    auto time = getTime();
    if(time <= 0&&_fishHp > 0)
    {//时间到了 重置时间并 扣血
        _fishTime = DATA_M->getContentSec() + 60;
        setFishHp(_fishHp - 1);
        
        if(_fishHp <= 0)
        {//血没了 记录倒计时
            _fishHp = 0;
            _dieTime = (int)(DATA_M->getContentSec() + 24 * 60 * 60);//24小时
            SETINTEGER(StringUtils::format("fish_dieTime_%d_%d",_fashTankIdx, _fishId).c_str(),_dieTime);
        }
    }
    
    //更新时间 累积超过24小时 消失
    if(_dieTime != 0&&_fishHp <= 0&&!_isTempDie)
    {
        auto dieTime = getDieTime();
        if(dieTime <= 0)
        {//翻白。停留不动
            //setFishMoveType(FishMoveType::Die);
            //_isTempDie = true;
            //_isDie = true;
            DATA_M->setIsFishDie(_fishId, true);
        }
    }
}

void Fish0::updateText(float dt)
{
    if(!_isPlayText) return;
    char c = _duiHuaVec.at(_duiHuaIndex);
    _duiHuaIndex++;
    if(_duiHuaIndex >= _duiHuaVec.size())
    {
        _isPlayText = false;
    }
    
    
    //音效
    SOUND_M->playTextEffect(c);
}

vector<Vec2> Fish0::getRoute()
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
    auto rect = _skeletonNode->getBoundingBox();
    auto x0 = -rect.size.width - 100;
    auto x1 = random(333-150, 333 + 150);
    auto x2 = random(766-150, 766 + 150);
    auto x3 = 1080 + rect.size.width + 100;
    if(_type == DataManager::FishType::Fish14)
    {
        x0 = -700 - 100;
        x3 = 1080 + 700 + 100;
    }
    
    auto randY = random(0, 99);//三个区域的鱼
    
    
    
    auto tempY = 0;
    auto y0 = 0;
    auto y1 = 0;
    auto y2 = 0;
    auto y3 = 0;
    if(randY < 12&&!isDaYu)
    {//上1460  1790  1625   165
        //tempY = random(1260,1790);//1625;
        this->setLocalZOrder(-4);
        _skeletonNode->setScaleY(scaleY);
        _shadows->setScale(0.7f);
        _shadows->setLocalZOrder(-2 - 100);
        _skeletonNode->setColor(Color3B(110,110,110));
    }
    else if(randY < 28&&!isDaYu)
    {//中950  1460  1205  255
        //tempY = random(850,1560);

        this->setLocalZOrder(-3);
        _skeletonNode->setScaleY(scaleY);
        _shadows->setScale(0.8f);
        _shadows->setLocalZOrder(-1 - 100);
        _skeletonNode->setColor(Color3B(180,180,180));
    }
    else
    {//260 950  605  345
        //tempY = random(450,1200);
        auto zorder = random(0, 1) == 0?0:-2;
        this->setLocalZOrder(zorder);
        _skeletonNode->setScaleY(scaleY);
        _shadows->setScale(1);
        _shadows->setLocalZOrder(0 - 100);
        _skeletonNode->setColor(Color3B(255,255,255));
    }
    while (true) {
        if(isDaYu)
        {
            
            auto min = 600.f;
            auto max = 1000.f;
            if(UIUtils::IsPad())
            {
                auto scaleMin = min/1920.f;
                auto scaleMax = max/1920.f;
                min = scaleMin * 1440.f;
                max = scaleMax * 1440.f;
            }
            
            tempY = random(min,max);
        }
        else
        {
            if(randY < 12)
            {//上1460  1790  1625   165
                auto min = 1260.f;
                auto max = 1790.f;
                if(UIUtils::IsPad())
                {
                    auto scaleMin = min/1920.f;
                    auto scaleMax = max/1920.f;
                    min = scaleMin * 1440.f;
                    max = scaleMax * 1440.f;
                }
                tempY = random(min,max);//1625;
            }
            else if(randY < 28)
            {//中950  1460  1205  255
                auto min = 850.f;
                auto max = 1460.f;
                if(UIUtils::IsPad())
                {
                    auto scaleMin = min/1920.f;
                    auto scaleMax = max/1920.f;
                    min = scaleMin * 1440.f;
                    max = scaleMax * 1440.f;
                }
                tempY = random(min,max);
            }
            else
            {//260 950  605  345
                auto min = 450.f;
                auto max = 1100.f;
                if(UIUtils::IsPad())
                {
                    auto scaleMin = min/1920.f;
                    auto scaleMax = max/1920.f;
                    min = scaleMin * 1440.f;
                    max = scaleMax * 1440.f;
                }
                tempY = random(min,max);
            }
        }
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
        
        
        if(_fishTank&&_fishTank->isFishY(poi0,_isLeft))
        {//可以了
            break;
        }
        else if(_rankFashTank&&_rankFashTank->isFishY(poi0,_isLeft))
        {//可以了
            break;
        }
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
    _oldIsLeft = _isLeft;
    _isLeft = !_isLeft;
    return vecs;
}


Rect Fish0::getWorldRect()
{
    auto rect = _skeletonNode->getBoundingBox();
    rect.origin = _skeletonNode->getParent()->convertToWorldSpace(rect.origin);
    
    return rect;
}

long Fish0::getTime()
{
    auto time = _fishTime - DATA_M->getContentSec();
    if(time < 0)time = 0;
    return time;
}

long Fish0::getDieTime()
{
    auto time = _dieTime - DATA_M->getContentSec();
    if(time < 0)time = 0;
    return time;
}

void Fish0::updateHp()
{
    if(isBar)
    {
        return;
    }
    auto p = ((float)_fishHp / (float)_fishMaxHp) * 100;
    _loadingBar->setPercent(p);
}

void Fish0::setFishHp(int hp)
{
    if(hp < 0) hp = 0;
    if(hp > _fishMaxHp) hp = _fishMaxHp;
    if(hp < _fishHp)
    {//在扣血
        auto p = ((float)hp / (float)_fishMaxHp) * 100;
        auto p2 = ((float)_fishHp / (float)_fishMaxHp) * 100;
        auto fishManager = FishManager::getInstance();
        auto isEle = fishManager->getIsEle();
        if(((p <= 30.01f&&p2 > 30.01f)||(p == 0&&p2 > 0))
           &&!isEle)
        {//当血变道30或者30以下时 或者血变为0时选择一个鱼触发
            fishManager->setIsEle(true);
            showDuiHua("",Fish0::EmojiType::ele);
        }
    }
    
    _fishHp = hp;
    updateHp();
    SETINTEGER(StringUtils::format("fish_hp_%d_%d", _fashTankIdx,_fishId).c_str(),hp);
}

int Fish0::getFishHp()
{
    return _fishHp;
}

void Fish0::restoreHp(int hp)
{
    auto speed = random(1.5f, 2.0f);
    fishPlayAni("happy", false,speed);
    
    setFishMoveType(FishMoveType::WeiShi);
    if(_fishHp == 0&&hp > 0)
    {//回血了
        _dieTime = 0;
        SETINTEGER(StringUtils::format("fish_dieTime_%d_%d", _fashTankIdx,_fishId).c_str(),0);
    }
    //复活啦
    DATA_M->setIsFishDie(_fishId, false);
    _isDie = false;
    _isTempDie = _isDie;
    _percent2 = (float)_fishHp/(float)_fishMaxHp * 100;
    auto maxHp = _fishHp + hp;
    if(maxHp > _fishMaxHp) maxHp = _fishMaxHp;
    _percent = (float)maxHp / (float)_fishMaxHp * 100;
    auto maxPercent = _percent - _percent2;
    percentDx = maxPercent/0.2;//m/s
    
    //恢复了hp
    setFishHp(_fishHp + hp);
    
    isBar = true;
    
    //重置计时
    _fishTime = DATA_M->getContentSec() + 60;
}

int Fish0::getFishId()
{
    return _fishId;
}

void Fish0::setFishId(int id)
{
    //移除
    DELETEKEY(StringUtils::format("fish_hp_%d_%d", _fashTankIdx,_fishId).c_str());
    DELETEKEY(StringUtils::format("fish_dieTime_%d_%d",_fashTankIdx, _fishId).c_str());
    DELETEKEY(StringUtils::format("fish_isDaily_%d_%d", _fashTankIdx,_fishId).c_str());
    _fishId = id;
    //更换
    SETINTEGER(StringUtils::format("fish_hp_%d_%d", _fashTankIdx,_fishId).c_str(),_fishHp);
    SETINTEGER(StringUtils::format("fish_dieTime_%d_%d",_fashTankIdx, _fishId).c_str(),_dieTime);
    SETBOOL(StringUtils::format("fish_isDaily_%d_%d", _fashTankIdx,_fishId).c_str(),_isDaily);
}

void Fish0::deleteSelf()
{
    //移除
    DELETEKEY(StringUtils::format("fish_hp_%d_%d",_fashTankIdx, _fishId).c_str());
    DELETEKEY(StringUtils::format("fish_dieTime_%d_%d", _fashTankIdx,_fishId).c_str());
    DELETEKEY(StringUtils::format("fish_isDaily_%d_%d", _fashTankIdx,_fishId).c_str());
    
    _shadows->deSelf();
    this->removeFromParent();
}

void Fish0::jiaSu()
{
    fishPlayAni("Up",false);
    setFishMoveType(FishMoveType::RUN);
    tempSpeed = 8;
    _isJiaSu = true;
    isStopJiaSu = false;
    isStop = false;
    _jiaSuTime = 0.2f;
    _fishActionSpeed->setSpeed(10);
}

void Fish0::fishStay()
{
    setFishMoveType(FishMoveType::Stay);
}

void Fish0::fishRush()
{
    setFishMoveType(FishMoveType::Rush);
}

void Fish0::fishStop()
{//原地停留
    //已经停下了
    if(isStop && _fishMoveType == FishMoveType::Stop)return;
    //动画总时长
    auto endtime = _spTrackEntry->animationEnd;
    stopMaxTime = endtime;
    stopMaxTempTime = endtime;
    //动画播了多长时间
    auto trackTime = _spTrackEntry->trackTime;
    
    //还有多长时间这个动画结束
    auto time = fabsf(endtime - trackTime);
    stopTime = fabsf(time) < 0.02f?endtime:time;
    stopTempTime = fabsf(time) < 0.02f?endtime:time;
    //在time时间内 速度减为0
    isStop = true;
    isStopJiaSu = false;
    tempSpeed = 0.5f;
    _jiaSuTime = 2;

}

void Fish0::fishAdmission()
{
    this->setVisible(true);
//    if(isDaYu)
//    {//鲨鱼
//        _isTouch = true;
//        fishMove();
//        return;
//    }
    _oldIsLeft = true;
    _isLeft = false;
    //动画总时长
    auto endtime = _spTrackEntry->animationEnd;
    //动画播了多长时间
    auto trackTime = _spTrackEntry->trackTime;
    //还有多长时间这个动画结束
    auto time = fabsf(endtime - trackTime);
    
    
    
    moveSpeed = random(30.0f,100.0f);
    auto size = Director::getInstance()->getWinSize();
    auto moveTime = time * 2.0f / 4.5f;
    
    auto x = random(size.width/2-150,size.width/2+150);
    auto y = random(size.height/2-150,size.height/2+150);
    auto moveVec = Vec2(x,y);
    auto move = MoveTo::create(moveTime, moveVec);
    auto sine = EaseSineOut::create(move);
    //角度
    auto selfPos = this->getPosition();
    auto angle = UIUtils::getAngle(selfPos,moveVec);
    _skeletonNode->setRotation(angle + 90);
    auto rotate = RotateTo::create(moveTime/2, 0);
    auto seqRoate = Sequence::create(DelayTime::create(moveTime/2), rotate, NULL);
    auto tar = TargetedAction::create(_skeletonNode, seqRoate);
    auto spawn = Spawn::create(sine,tar, NULL);
    
    
    moveTime = time * 0.5f / 4.5f;
    auto move1Vec = Vec2(moveVec.x,moveVec.y + 10);
    auto move1 = MoveTo::create(moveTime, move1Vec);
    auto sine1 = EaseSineOut::create(move1);
    
    auto rect = _skeletonNode->getBoundingBox();
    auto x0 = -rect.size.width - 200;
    
    move2Vec = Vec2(x0,move1Vec.y);
    auto length = (move1Vec - move2Vec).length();
    move2Time = length / moveSpeed;
    
    
    
    
    auto seq = Sequence::create(spawn,sine1,CallFunc::create([this](){
        setFishMoveType(FishMoveType::Admission2);
        fishPlayAni("happy",false);
    }), NULL);
    _fishActionSpeed = Speed::create(seq,1);
    runAction(_fishActionSpeed);
    
    //阴影高度
    y = move1Vec.y;
    auto a = y/1920.f;
    y = a * 1920.f / 3.f;
    _shadows->setPositionY(y);
    
}

void Fish0::fishPlayAni(string aniName,bool loop,float speed)
{
    
    if(aniName == "Loop")
    {//停下
        _fishAniType = FishAniType::LOOP;
    }
    else if(aniName == "Run")
    {//行动
        _fishAniType = FishAniType::RUN;
    }
    else if(aniName == "Up")
    {//加速
        _fishAniType = FishAniType::UP;
    }
    if(aniName == "happy")
    {//开心
        _fishAniType = FishAniType::HAPPY;
    }
    
//    if(_isDie)
//    {
//        aniName = "Loop";
//    }
    
    _spTrackEntry = _skeletonNode->setAnimation(0, aniName, loop);
    _spTrackEntry->timeScale = speed;
    
    
}

bool Fish0::getIsWeiShi()
{
    return _fishHp != _fishMaxHp && !_isJinShi;
}

bool Fish0::getIsMaxHp()
{
    return _fishHp == _fishMaxHp;
}

void Fish0::weiShi(Vec2 poi,bool isEnd,string str)
{
    if(isStart) return;
    if(_fishHp == _fishMaxHp)return;//满血就别吃了
    if(_isJinShi) return;
//    if(_isDie)
//    {
//        //变化左右
//        if(!_isLeft)
//        {
//            scaleY = 1;
//        }
//        else
//        {
//            scaleY = -1;
//        }
//        _skeletonNode->setScaleY(scaleY);
//    }
    
    //显示雪条
    Node_loadingBar->setVisible(true);
    //鱼向着 poi 移动
    _isJiaSu = false;
    isStop = false;
    isStopJiaSu = false;
    _isJinShi = true;
    _fishMoveType = FishMoveType::None;
    _isTouch = false;//禁止点击
    auto selfPoi = this->getPosition();
    weiShiTempSelfPos = selfPoi;
    
    float time = 1;
    float speed = 800;
    int PointCount = 10;//
    //得到鱼的宽度
    auto width = _skeletonNode->getBoundingBox().size.width;
    float min = width/2 + 20;
    float max = width/2 + 150;
    auto n = random(min, max);
    poi.x = random(poi.x-50,poi.x+50);
    poi.y = random(poi.y-50,poi.y+50);
    auto p = poi-selfPoi;
    auto normalized = p.getNormalized();
    auto length = fabsf(poi.x-selfPoi.x);//p.length();
    auto func = CallFunc::create([this,isEnd,str](){
        //吃完了 回血 播放happy
        if(str != "")
        {
            //掉落
            auto poi = this->getPosition();
            poi = this->getParent()->convertToWorldSpace(poi);
            _fishTank->clickFishReward(poi,this);
            showDuiHua(str,Fish0::EmojiType::happy);
        }
        restoreHp(30);
        
        auto fashTank = SCENE_M->getGameBackground();
        fashTank->updateWeiShi();
    });
    
    //然后恢复游动
    float delayTime = 0.3f;
    auto delay = DelayTime::create(delayTime);
    auto resumeFunc = CallFunc::create([this](){
        //吃完就走吧
        resumeMove();
    });
    auto resumeSeq = Sequence::createWithTwoActions(delay, resumeFunc);
    
    if(_oldIsLeft)
    {//向左移动中
        if(poi.x < selfPoi.x&&length > n + 300)
        {//直接移动
            this->stopAllActions();
            //计算目的地
            //n = n > length?length/2:n;
            auto p2 = selfPoi - poi;
            auto normalized2 = p2.getNormalized();
            Vec2 endPoi = poi + (normalized2 * n);
            if(_type == DataManager::FishType::Fish14)
            {
                log("shayu");
            }
            time = (poi - selfPoi).length()/speed;
            auto moTo = MoveTo::create(time, endPoi);
            
            
            auto tar = chiFanAction(normalized);
            
            auto seq = Sequence::create(moTo,tar,func,resumeSeq, NULL);
            _fishActionSpeed = Speed::create(seq,1);
            this->runAction(_fishActionSpeed);
        }
        else
        {//加速向前 移动出屏幕 在移动到poi
            this->stopAllActions();
            bool isXia = selfPoi.y < poi.y;
            auto rect = _skeletonNode->getBoundingBox();
            auto x0 = -rect.size.width/2 - 100;
            Vec2 endPoi = Vec2(x0,selfPoi.y);
            //移动到屏幕外
            Vec2 p0 = selfPoi;
            auto xlength = fabsf(selfPoi.x) + fabsf(x0);
            float y = isXia?-100:100;
            Vec2 p1 = Vec2(selfPoi.x - xlength/3,selfPoi.y + y);
            Vec2 p2 = Vec2(selfPoi.x - xlength * 2/3,selfPoi.y + y);
            Vec2 p3 = Vec2(x0,selfPoi.y);
            ccBezierConfig config;
            config.controlPoint_1 = p1;
            config.controlPoint_2 = p2;
            config.endPosition = p3;


            auto bezvec = ComputeBezier(p0,p1,p2,p3,PointCount);
            //求出长度
            int bezierLen = (int)BezierLenth(bezvec, PointCount+1);
            time = bezierLen/speed;
            //移动出屏幕
            auto bez = BezierTo::create(time, config);

            //进入屏幕到食物位置
            //随机个y
            float inY = random(500.0f,1500.0f);
            p0 = Vec2(x0,inY);
            auto p = p0 - poi;
            auto normalized = p.getNormalized();
            p3 = poi + (normalized * n);
            
            auto length = (p0-p3).length();
            //根据p0 与 p3 计算 p1 与 p2
            //在p0与p3直线上 垂直的两个点 随机在那一侧
            p = p0-p3;
            normalized = p.getNormalized();
            auto isleft = random(0, 1) == 0;
            if(isleft)
            {// 左侧
                // -y,x
                Vec2 left(-normalized.y,normalized.x);
                auto p11 = p3 + normalized * length * 2/3;
                auto p22 = p3 + normalized * length * 1/3;
                
                
                p1 = p11 + (left * 20);
                p2 = p22 + (left * 20);
            }
            else
            {//右侧
                Vec2 right(normalized.y,-normalized.x);
                auto p11 = p3 + normalized * length * 2/3;
                auto p22 = p3 + normalized * length * 1/3;
                
                
                p1 = p11 + (right * 20);
                p2 = p22 + (right * 20);
            }
            
            
            ccBezierConfig configIn;
            configIn.controlPoint_1 = p1;
            configIn.controlPoint_2 = p2;
            configIn.endPosition = p3;


            auto bezvecIn = ComputeBezier(p0,p1,p2,p3,PointCount);
            //求出长度
            int bezierLenIn = (int)BezierLenth(bezvecIn, PointCount+1);
            time = bezierLenIn/speed;
            //设置到指定位置
            auto place = Place::create(p0);
            //进入屏幕
            auto bezIn = BezierTo::create(time, configIn);
            normalized = (bezvecIn.at(PointCount) - bezvecIn.at(PointCount - 1)).getNormalized();
            auto tar = chiFanAction(normalized);
            
            auto seq = Sequence::create(bez,place,CallFunc::create([this](){
                //变化左右
                if(!_isLeft)
                {
                    scaleY = -1;
                }
                else
                {
                    scaleY = 1;
                }
                _skeletonNode->setScaleY(scaleY);
                _oldIsLeft = _isLeft;
                _isLeft = !_isLeft;

            }),bezIn,tar,func,resumeSeq, NULL);
            
            _fishActionSpeed = Speed::create(seq,1);
            this->runAction(_fishActionSpeed);
        }
    }
    else
    {//向右移动中
        if(poi.x > selfPoi.x&&length > n + 300)
        {//直接移动
            this->stopAllActions();

            //计算目的地
            //n = n > length?length/2:n;
            auto p2 = selfPoi - poi;
            auto normalized2 = p2.getNormalized();
            Vec2 endPoi = poi + (normalized2 * n);
            if(_type == DataManager::FishType::Fish14)
            {
                log("shayu");
            }
            time = (poi - selfPoi).length()/speed;
            auto moTo = MoveTo::create(time, endPoi);
            
            
            
            auto tar = chiFanAction(normalized);
            
            auto seq = Sequence::create(moTo,tar,func,resumeSeq, NULL);
            _fishActionSpeed = Speed::create(seq,1);
            this->runAction(_fishActionSpeed);
        }
        else
        {
            this->stopAllActions();
            bool isXia = selfPoi.y < poi.y;
            auto rect = _skeletonNode->getBoundingBox();
            auto x0 = 1080 + rect.size.width/2 + 100;
            
            Vec2 endPoi = Vec2(x0,selfPoi.y);
            //移动到屏幕外
            Vec2 p0 = selfPoi;
            auto xlength = fabsf(selfPoi.x) + fabsf(x0);
            float y = isXia?-100:100;
            Vec2 p1 = Vec2(selfPoi.x + xlength/3,selfPoi.y + y);
            Vec2 p2 = Vec2(selfPoi.x + xlength * 2/3,selfPoi.y + y);
            Vec2 p3 = Vec2(x0,selfPoi.y);
            ccBezierConfig config;
            config.controlPoint_1 = p1;
            config.controlPoint_2 = p2;
            config.endPosition = p3;


            auto bezvec = ComputeBezier(p0,p1,p2,p3,PointCount);
            //求出长度
            int bezierLen = (int)BezierLenth(bezvec, PointCount+1);
            time = bezierLen/speed;
            //移动出屏幕
            auto bez = BezierTo::create(time, config);

            //进入屏幕到食物位置
            //随机个y
            float inY = random(500.0f,1500.0f);
            
            p0 = Vec2(x0,inY);
            auto p = p0 - poi;
            auto normalized = p.getNormalized();
            p3 = poi + (normalized * n);
            
            auto length = (p0-p3).length();
            //根据p0 与 p3 计算 p1 与 p2
            //在p0与p3直线上 垂直的两个点 随机在那一侧
            p = p0-p3;
            normalized = p.getNormalized();
            auto isleft = random(0, 1) == 0;
            if(isleft)
            {// 左侧
                // -y,x
                Vec2 left(-normalized.y,normalized.x);
                auto p11 = p3 + normalized * length * 2/3;
                auto p22 = p3 + normalized * length * 1/3;
                
                
                p1 = p11 + (left * 20);
                p2 = p22 + (left * 20);
            }
            else
            {//右侧
                Vec2 right(normalized.y,-normalized.x);
                auto p11 = p3 + normalized * length * 2/3;
                auto p22 = p3 + normalized * length * 1/3;
                
                
                p1 = p11 + (right * 20);
                p2 = p22 + (right * 20);
            }
            
            
            ccBezierConfig configIn;
            configIn.controlPoint_1 = p1;
            configIn.controlPoint_2 = p2;
            configIn.endPosition = p3;


            auto bezvecIn = ComputeBezier(p0,p1,p2,p3,PointCount);
            //求出长度
            int bezierLenIn = (int)BezierLenth(bezvecIn, PointCount+1);
            time = bezierLenIn/speed;
            //设置到指定位置
            auto place = Place::create(p0);
            //进入屏幕
            auto bezIn = BezierTo::create(time, configIn);

            normalized = (bezvecIn.at(PointCount) - bezvecIn.at(PointCount - 1)).getNormalized();
            auto tar = chiFanAction(normalized);
            
            auto seq = Sequence::create(bez,place,CallFunc::create([this](){
                //变化左右
                if(!_isLeft)
                {
                    scaleY = -1;
                }
                else
                {
                    scaleY = 1;
                }
                _skeletonNode->setScaleY(scaleY);
                _oldIsLeft = _isLeft;
                _isLeft = !_isLeft;

            }),bezIn,tar,func,resumeSeq, NULL);
            
            _fishActionSpeed = Speed::create(seq,1);
            this->runAction(_fishActionSpeed);
        }
    }
    
}

void Fish0::resumeMove()
{//吃完鱼食。恢复运动
    //根据自身位置和移动方向 重新生成路线
    
    //恢复角度计算
    _isAngle = true;
    //可以点了
    _isTouch = true;
    auto selfPoi = this->getPosition();
    auto rect = _skeletonNode->getBoundingBox();
    auto x0 = -rect.size.width - 200;
    if(_oldIsLeft)
    {
        x0 = -rect.size.width - 200;
    }
    else
    {
        x0 = 1080 + rect.size.width + 200;
    }

    //判断向上还是向下
    bool isXia = weiShiTempSelfPos.y > selfPoi.y;
    
    
    //向量
    auto normalized = _jinShiNormalized;
    
    //贝塞尔
    Vec2 p0 = selfPoi;
    Vec2 p3 = Vec2(x0,random(selfPoi.y - 50,selfPoi.y + 50));
    //p1 当前朝向 延伸 200-300;
    float n = random(10.0f,50.0f);
    
    
    Vec2 p1 = selfPoi + normalized * n;
    
    // p1-p3响亮
    auto p = p3 - p1;
    normalized = p.getNormalized();
    
    //p1-p3中心点
    auto vp = p1 + normalized * p.length()/2;
    auto isleft = random(0, 1) == 0;
    Vec2 p2;
    if(isleft)
    {
        //左侧向量
        Vec2 left(-normalized.y,normalized.x);
        p2 = vp + left * random(100, 200);
    }
    else
    {
        //右侧响亮
        Vec2 right(normalized.y,-normalized.x);
        p2 = vp + right * random(100, 200);
    }
    
    int PointCount = 10;//
    auto bezvec = ComputeBezier(p0,p1,p2,p3,PointCount);
    
    
    
    //求出长度
    int bezierLen = (int)BezierLenth(bezvec, PointCount+1);
    float speed = 300;
    auto beztime = bezierLen / speed;
    ccBezierConfig config;
    config.controlPoint_1 = p1;
    config.controlPoint_2 = p2;
    config.endPosition = p3;
    auto bez = BezierTo::create(beztime, config);
    
    //auto moTo = MoveTo::create(time, endPoi);
//    auto seq = Sequence::create(bez,CallFunc::create([this](){
//        //可以点了
//        _isTouch = true;
//    }),moTo,CallFunc::create([this](){
//        fishMove();
//    }), NULL);
    auto seq = Sequence::create(bez,CallFunc::create([this](){
        _isJinShi = false;
        fishMove();
    }), NULL);
    _fishActionSpeed = Speed::create(seq,1);
    this->runAction(_fishActionSpeed);
    log("恢复行动啦------");
}

TargetedAction* Fish0::chiFanAction(Vec2 normalized)
{
    _jinShiNormalized = normalized;
    float time1 = 0.1f;
    float time2 = 0.4f;
    auto endP = normalized * 50;

    
    Vector<FiniteTimeAction*> finite;
    
    
    int num = random(0,2);
    if(isDaYu)
    {//鲨鱼
        num = 0;
    }
    for(int i = 0;i < num;++i)
    {
        auto moBy0 = MoveTo::create(time1, endP);
        auto moBy1 = MoveTo::create(time1, Vec2(0,0));
        finite.pushBack(moBy0);
        finite.pushBack(moBy1);
    }
    auto moBy2 = MoveTo::create(time1, endP);
    auto moBy3 = MoveTo::create(time2, Vec2(0,0));
    auto sine = EaseSineOut::create(moBy3);
    finite.pushBack(moBy2);
    finite.pushBack(sine);
    auto seq = Sequence::create(finite);
    
    auto iconSeq = Sequence::create(CallFunc::create([this](){
        _isAngle = false;
    }),seq, NULL);
    auto tar = TargetedAction::create(_skeletonNode, iconSeq);
    return tar;
}

void Fish0::dieStart()
{//死亡时 初始化位置 与其他属性
    isStart = false;
    
    //外观与y轴设置完毕
    auto vec = getRoute();
    auto fishSize = _skeletonNode->getBoundingBox().size;
    auto size = Director::getInstance()->getSafeAreaRect().size;
    
    float x = random(fishSize.width/2,size.width - fishSize.width/2);
    float y = random(450,1100);
    Vec2 startPoi(x,y);
    Vec2 angleVec;
    if(!_isLeft)
    {//右到左
        angleVec = Vec2(startPoi.x - 50,startPoi.y);
    }
    else
    {//左到右
        angleVec = Vec2(startPoi.x + 50,startPoi.y);
    }
    
    //算下角度
    auto angle = UIUtils::getAngle(startPoi,angleVec);
    _skeletonNode->setRotation(angle + 90);
    
    this->setPosition(startPoi);
    dieAction();
}

void Fish0::dieAction()
{
    if(!_isDie) return;
    //停止所有动作
    this->stopAllActions();
    
    if(!_isLeft)
    {
        scaleY = -1;
    }
    else
    {
        scaleY = 1;
    }
    //肚子朝上
    _skeletonNode->setScaleY(scaleY);
    //发表情
    showDuiHua("",Fish0::EmojiType::ele);
}


void Fish0::resurrection()
{
    
}

void Fish0::setFishMoveType(FishMoveType type)
{
    if(_fishMoveType == FishMoveType::Die&&!_isJinShi)
    {//在死亡过程 而且没有进食
        return;
    }
    _fishMoveType = type;
}

void Fish0::showDuiHua(string str,EmojiType type)
{
    //有显示了
    if(FileNode_DuiHua->isVisible())return;
    
    string frameName = "";
    if(type == EmojiType::happy)
    {
        auto id = random(0, 3);
        frameName = StringUtils::format("emoji/happy%d.png",id);
    }
    else if(type == EmojiType::money)
    {
        frameName = "emoji/money.png";
    }
    else if(type == EmojiType::ele || type == EmojiType::fanu)
    {
        bool isEle = random(0, 1) == 0;
        frameName = isEle?"emoji/ele.png":"emoji/fanu.png";
    }
    
    
    FileNode_DuiHua->setVisible(true);
    string aniName = "";
    //happy0-3  money fanu ele
    
    if(str != "")
    {//基础70 算上文本长度s
        auto languageCode = DATA_M->getAllDyyStr();
        string enStr = "That's delicious!";
        
        _duiHua->setString(str);
        auto width = _duiHua->getBoundingBox().size.width;
        auto size = Image_DuiHua->getContentSize();
        size.width = 70 + width;
        Image_DuiHua->setContentSize(size);
        _duiHuaVec.clear();
        
        _duiHuaIndex = 0;
        for(int i = 0;i < enStr.length();++i)
        {
            _duiHuaVec.push_back(enStr[i]);
        }
        _isPlayText = true;
        
        Sprite_DuiHua->setSpriteFrame(frameName);
        aniName = "start0";
    }
    else
    {
        Sprite_emoji->setSpriteFrame(frameName);
        aniName = "start1";
    }
    
    UIUtils::playInnerAction(FileNode_DuiHua,aniName,false,[this,type](){
        if(type == EmojiType::ele || type == EmojiType::fanu)
        {
            FishManager::getInstance()->setIsEle(false);
        }
        FileNode_DuiHua->setVisible(false);
    });
    
}

void Fish0::setIsDaily(bool isDaily,bool isRank)
{
    _isDaily = isDaily;
    if(isDaily)
    {
        Text_rare->setVisible(true);
        if(!isRank)
        {//不是排行榜 才储存
            SETBOOL(StringUtils::format("fish_isDaily_%d_%d", _fashTankIdx,_fishId).c_str(),true);
        }
    }
}

void Fish0::updateDYY()
{
    Text_rare->setString(Lang("100373"));
}
