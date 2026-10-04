//
//  Currency.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/22.
//

#include <stdio.h>
#include "Currency.h"

using namespace std;
Currency::Currency()
{
    
}
Currency::~Currency()
{
    
}
bool Currency::init()
{
    CacheNode<Currency>::init();
    
    rootNode = CSLoader::createNode("Animation/Node_currency.csb");
    
    
    
    this->addChild(rootNode);
    return true;
}

void Currency::cacheInit()
{
    actionManager = cocostudio::timeline::ActionTimelineCache::createAction("Animation/Node_currency.csb");
    rootNode->runAction(actionManager);
    actionManager->setTag(10086);
    rootNode->setTag(10086);
}

void Currency::onEnter()
{
    CacheNode<Currency>::onEnter();
}

void Currency::onExit()
{
    CacheNode<Currency>::onExit();
    if(this->getParent())
    {
        CCLOG("E");
    }
    //放入缓冲池
    //Currency::getCache()->deleteOnExit(this);
}

void Currency::playAni(std::string name,bool isLoop,std::function<void()> cb)
{
    if (name != "")
    {
        if (cb)
            actionManager->setLastFrameCallFunc(cb);
        actionManager->play(name, isLoop);
    }
}
