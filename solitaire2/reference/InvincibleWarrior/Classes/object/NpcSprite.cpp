//
//  NPCNpcSprite.cpp
//  SolitaireClassicGame-mobile
//
//  Created by lien on 2019/8/3.
//

#include <stdio.h>
#include "NpcSprite.h"
#include "UIUtils.h"

NpcSprite::NpcSprite()
:targetPoi(0,0)
,startPoi(0,0)
,xiaBiao(0)
,isUp(false)
,isDown(false)
,isLeft(false)
,isRight(false)
,actionManager(NULL)
{
    speed = 1;
    isStart = false;
}
NpcSprite::~NpcSprite()
{
    
}

bool NpcSprite::init()
{
    CacheNode<NpcSprite>::init();
    
    Node_Npc = UIUtils::createCSBNode("Animation/Node_Npc.csb");
    this->addChild(Node_Npc);
    Node_Npc->setTag(10086);
    Node_Npc->setScale(1.0f);
    Sprite_1 = Node_Npc->getChildByName<Sprite*>("Sprite_1");
    //actionManager = UIUtils::playInnerAction(Node_Npc, "", false);
    //得到目标点
    speed = random(25,40);
    _npcId = random(0,5);
    return true;
}

void NpcSprite::cacheInit()
{//重新初始化信息
    xiaBiao = 0;
    isStart = false;
    this->setPosition(Vec2(0,0));
    actionManager = ActionTimelineCache::createAction("Animation/Node_Npc.csb");
    Node_Npc->stopAllActions();
    Node_Npc->runAction(actionManager);
    actionManager->setTag(10086);
    actionManager->setTimeSpeed(1.0f);
    vector<string> strVec {
        "Human/gif/A",
        "Human/gif/B",
        "Human/gif/C",
        "Human/gif/D",
        "Human/gif/E",
        "Human/gif/F",
    };
    actionManager->setFrameEventCallFunc([this,strVec](Frame* frame){
         auto event = dynamic_cast<EventFrame*>(frame);
         auto msg = event->getEvent();
         if(msg.find('_') != string::npos)
         {
             auto frameName = StringUtils::format("%s%s.png",strVec.at(_npcId).c_str(),msg.c_str());
             Sprite_1->setSpriteFrame(frameName);
         }
    });
}

Vec2 NpcSprite::getWorldPoi()
{
    Vec2 poi = this->getPosition();
    poi = this->getParent()->convertToWorldSpace(poi);
    return poi;
}

Vec2 NpcSprite::getNodePoi(Vec2 pos)
{
    pos = this->getParent()->convertToNodeSpace(pos);
    return pos;
}
Rect NpcSprite::getWorldRect()
{
    auto rect = this->getBoundingBox();
    rect.origin = this->getParent()->convertToWorldSpace(rect.origin);
    return rect;
}

void NpcSprite::playUpAni()
{
    if(!isUp)
    {
        this->setScaleX(-1);
        //auto aniName = StringUtils::format("Npc_up",_npcId);
        actionManager->play("Npc_up", true);
        //UIUtils::playInnerAction(Node_Npc, aniName, true);
        isUp = true;
        isDown = false;
        isLeft = false;
        isRight = false;
    }
}
void NpcSprite::playDownAni()
{
    if(!isDown)
    {
        this->setScaleX(1);
        //auto aniName = StringUtils::format("Npc_down",_npcId);
        actionManager->play("Npc_down", true);
        //UIUtils::playInnerAction(Node_Npc, aniName, true);
        isUp = false;
        isDown = true;
        isLeft = false;
        isRight = false;
    }
}
void NpcSprite::playLeftAni()
{
    if(!isLeft)
    {
        this->setScaleX(1);
        //auto aniName = StringUtils::format("Npc_up",_npcId);
        actionManager->play("Npc_up", true);
        //UIUtils::playInnerAction(Node_Npc, aniName, true);
        isUp = false;
        isDown = false;
        isLeft = true;
        isRight = false;
    }
}
void NpcSprite::playRightAni()
{
    if(!isRight)
    {
        this->setScaleX(-1);
        //auto aniName = StringUtils::format("Npc_down",_npcId);
        actionManager->play("Npc_down", true);
        //UIUtils::playInnerAction(Node_Npc, aniName, true);
        isUp = false;
        isDown = false;
        isLeft = false;
        isRight = true;
    }
}

void NpcSprite::onEnter()
{
    CacheNode<NpcSprite>::onEnter();
    schedule(CC_CALLBACK_1(NpcSprite::myUpdate, this),"npc");
    
}

void NpcSprite::onExit()
{
    CacheNode<NpcSprite>::onExit();
    unschedule("npc");
}

void NpcSprite::myUpdate(float dt)
{
    if(!isStart || _isStop) return;
    
    //移动过程中要判断障碍
    Vec2 poi = this->getPosition();
    //变换层次
    if(targetPoi == poi)
    {//是否到了目标点
        
//        if(poi == startPoi)
//        {
//            this->removeFromParent();
//            return;
//        }
        //切换目标点
        auto node = _pathVec.at(xiaBiao);
        auto poi = node->getPosition();
        if(_pathIdx == 1&&_isHide)
        {
            if(xiaBiao == 0||xiaBiao == 2)
            {
                _randHide = 1;//random(0, 1) == 0?2:0;
                this->setVisible(!this->isVisible());
            }
        }
        
        if(_pathIdx == 0)
        {
            if(xiaBiao%2 == 0)
            {
                this->setVisible(true);
            }
            else
            {//隐藏了
                _isStop = true;
                auto time = random(0.1f, 0.5f);
                auto delay = DelayTime::create(time);
                auto func = CallFunc::create([this](){
                    _isStop = false;
                });
                auto seq = Sequence::create(delay,func, NULL);
                this->stopAllActions();
                this->runAction(seq);
                this->setVisible(false);
            }
            xiaBiao++;
        }
        else if(_pathIdx == 1)
        {
            if(isFront)
            {
                xiaBiao++;
            }
            else
            {
                xiaBiao--;
            }
        }
        
        
        if(xiaBiao >= _pathVec.size()) xiaBiao = 0;
        if(xiaBiao < 0) xiaBiao = (int)_pathVec.size() - 1;
        if(xiaBiao == 0)
        {
            isFront = true;
        }
        else if(xiaBiao == _pathVec.size()-1)
        {
            isFront = false;
        }
        
        
        
        
        auto node2 = _pathVec.at(xiaBiao);
        targetPoi = node2->getPosition();
        _normalized = (targetPoi-poi).getNormalized();
    }
    else
    {
        //0-800
        this->setLocalZOrder(400 - poi.y);
        
        auto length = (targetPoi - poi).length();
        if(targetPoi.y > poi.y&&targetPoi.x > poi.x)
        {//向上移动
            playUpAni();
        }
        else if(targetPoi.y < poi.y&&targetPoi.x > poi.x)
        {//s向右移动
            playRightAni();
        }
        else if(targetPoi.y > poi.y&&targetPoi.x < poi.x)
        {//向左移动
            playLeftAni();
        }
        else
        {//向下移动
            playDownAni();
        }
        auto dl = dt * speed;
        if(length < dl)//dt/0.016f * speed)
        {//少于一步的距离
            poi = targetPoi;
        }
        else
        {
            poi += dl * _normalized;
        }
        this->setPosition(poi);
    }
}

void NpcSprite::setPath(Vector<Node*> pathVec,int pathIdx,bool isHide)
{
    _isStop = false;
    _isHide = isHide;
    _randHide = 0;//random(0, 2);
    isStart = true;
    _pathIdx = pathIdx;
    _pathVec = pathVec;
    xiaBiao = random(0,(int)_pathVec.size()-1);
    auto node = _pathVec.at(xiaBiao);
    auto poi = node->getPosition();
    isFront = random(0,1) == 0;
    if(xiaBiao == 0)
    {
        isFront = true;
    }
    else if(xiaBiao == _pathVec.size()-1)
    {
        isFront = false;
    }
    if(_pathIdx == 0)
    {
        if(xiaBiao%2 == 0)
        {
            this->setVisible(true);
        }
        else
        {
            this->setVisible(false);
        }
        xiaBiao++;
    }
    else if(_pathIdx == 1)
    {
        auto hide = random(0,1) == 0;
        if(isHide)
        {
            this->setVisible(hide);
        }
        
        if(isFront)
        {
            xiaBiao++;
        }
        else
        {
            xiaBiao--;
        }
    }
    
    if(xiaBiao >= _pathVec.size()) xiaBiao = 0;
    if(xiaBiao < 0) xiaBiao = (int)_pathVec.size() - 1;
    if(xiaBiao == 0)
    {
        isFront = true;
    }
    else if(xiaBiao == _pathVec.size()-1)
    {
        isFront = false;
    }
    
    
    
    
    auto node2 = _pathVec.at(xiaBiao);
    targetPoi = node2->getPosition();
    _normalized = (targetPoi-poi).getNormalized();
    
    
    
    //计算初始位置
    auto length = (targetPoi-poi).length();
    
    auto randLength = random(0.0f, length-3);
    
    poi += randLength * _normalized;
    
    this->setPosition(poi);
    
}
