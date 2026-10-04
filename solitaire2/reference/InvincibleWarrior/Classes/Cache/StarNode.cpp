//
//  StarNode.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/7.
//
#include <stdio.h>
#include "StarNode.h"

using namespace std;
StarNode::StarNode()
{
    
}
StarNode::~StarNode()
{
    
}
bool StarNode::init()
{
    CacheNode<StarNode>::init();
    
    rootNode = CSLoader::createNode("Animation/win_star.csb");
    
    
    
    this->addChild(rootNode);
    return true;
}

void StarNode::cacheInit()
{
    actionManager = cocostudio::timeline::ActionTimelineCache::createAction("Animation/win_star.csb");
    rootNode->runAction(actionManager);
    actionManager->setTag(10086);
    rootNode->setTag(10086);
}

void StarNode::onEnter()
{
    CacheNode<StarNode>::onEnter();
}

void StarNode::onExit()
{
    CacheNode<StarNode>::onExit();
    if(this->getParent())
    {
        CCLOG("E");
    }
    //放入缓冲池
    //StarNode::getCache()->deleteOnExit(this);
}

void StarNode::playAni(std::string name,bool isLoop,float time,std::function<void()> cb)
{
    if (name != "")
    {
        if (cb)
            actionManager->setLastFrameCallFunc(cb);
        actionManager->play(name, isLoop);
        //计算倍数
        auto startFrame = actionManager->getStartFrame();
        auto endFrame = actionManager->getEndFrame();
        float actionTime = 1.0f/60.0f * (endFrame-startFrame);
        float speed = actionTime/time;
        
        actionManager->setTimeSpeed(speed);
        
    }
}
