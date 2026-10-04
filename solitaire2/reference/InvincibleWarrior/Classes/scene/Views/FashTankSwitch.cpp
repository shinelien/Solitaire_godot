//
//  FashTankSwith.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/29.
//

#include <stdio.h>
#include "FashTankSwitch.h"
#include "SceneManager.h"
#include "DataManager.h"
#include "FishGuideManager.h"

FashTankSwitch::FashTankSwitch(int fashTankIdx)
:BaseLayer("scence_switch.csb")
,_fashTankIdx(fashTankIdx)
{
    
}

FashTankSwitch::~FashTankSwitch()
{
    
}

void FashTankSwitch::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    
    playAni("in",false,[this](){
        
        if(!GUIDE_M->isEnd(FishGuideManager::GuideType::UseFashTankTipsOne)&&GUIDE_M->isEnd(FishGuideManager::GuideType::UseFashTank,0))
        {//点击商店引导结束后才能进行买鱼引导
            GUIDE_M->startGuide(FishGuideManager::GuideType::UseFashTankTipsOne);
        }
        
        SCENE_M->removeLayer(this);
    });
    
    auto num = DATA_M->getFishNum(_fashTankIdx);
    getNode<TextBMFont*>("BitmapFontLabel_min")->setString(StringUtils::toString(num));
    getNode<TextBMFont*>("BitmapFontLabel_max")->setString(StringUtils::toString(FISH_MAX_NUM));
    vector<string> frameNameVec{
        "Logo0_1.png",
        "Logo0_2.png",
        "Logo0_3.png",
        "Logo0_4.png",
    };
    getNode<Sprite*>("fish_Aquarium0_1_2")->setSpriteFrame(frameNameVec.at(_fashTankIdx));
    //dyy
    vector<string> strVec{
        "100367",
        "100368",
        "100369",
        "100370",
    };
    getNode<Text*>("Text_Aquarium")->setString(Lang("100353"));
}

void FashTankSwitch::initData()
{
    BaseLayer::initData();
    
}

void FashTankSwitch::dealButtonClick(Ref *pSender)
{
    
}

void FashTankSwitch::onEnter()
{
    BaseLayer::onEnter();
}

void FashTankSwitch::onExit()
{
    BaseLayer::onExit();
}
