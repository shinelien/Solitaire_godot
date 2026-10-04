//
//  ShadowsFish.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by 宋 on 2021/4/19.
//

#include <stdio.h>

#include "ShadowsFish.h"
#include "Fish0.h"

ShadowsFish* ShadowsFish::createShadows(Fish0* fish)
{
    auto shadowsFish = new ShadowsFish(fish);
    if(shadowsFish)
    {
        shadowsFish->shadowsInit();
        return shadowsFish;
    }
    return NULL;
}

ShadowsFish::ShadowsFish(Fish0* fish)
:BaseLayer("fish/Shadows.csb")
{
    _fish0 = fish;
}

ShadowsFish::~ShadowsFish()
{
    
}

void ShadowsFish::initUI()
{
    BaseLayer::initUI();
    shadowsIcon = getNode<Sprite*>("Sprite_shadows");
    this->setPositionX(-500);
    //shadowsIcon->setVisible(false);
    schedule(CC_CALLBACK_1(ShadowsFish::Update, this),"ShadowsFishUpate");
}
void ShadowsFish::initData()
{
    BaseLayer::initData();
}

void ShadowsFish::shadowsInit()
{
    
}

void ShadowsFish::Update(float dt)
{
    if(_fish0)
    {//x轴跟随
        auto x = _fish0->getPositionX();
        this->setPositionX(x);
    }
}

void ShadowsFish::deSelf()
{
    ceshi++;
    this->removeFromParent();
}
