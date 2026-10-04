//
//  FishGuideManager.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/30.
//

#include <stdio.h>
#include "FishGuideManager.h"
#include "FishGuideView.h"
#include "SceneManager.h"
#include "PlayerManager.h"
#include "MainLobby.h"
#include "ScoreManager.h"

FishGuideManager* FishGuideManager::_instance = nullptr;


FishGuideManager* FishGuideManager::getInstance()
{
    if(!_instance)
    {
        _instance = new FishGuideManager();
    }
    return _instance;
}

FishGuideManager::FishGuideManager()
{
    _layer = NULL;
    
    for(int i = 0; i < (int)GuideType::None;++i)
    {
        isStartGuideVec.push_back(false);
    }
}
FishGuideManager::~FishGuideManager()
{
    
}

const int layerZOrder = 20210101;
bool FishGuideManager::startGuide(GuideType type,Node* node,Vec2 shouPoi,float btnScale,int idx)
{
    auto isGuide = false;
    if(idx != -1)
    {
        isGuide = GETBOOL(StringUtils::format("isGuide_%d_%d",type,idx).c_str(),false);
    }
    else
    {
        isGuide = GETBOOL(StringUtils::format("isGuide_%d",type).c_str(),false);
    }
    if(isGuide||_guideType != GuideType::None) return false;
    _guideType = type;
    
    isStartGuideVec[(int)_guideType] = true;
    _layer = FishGuideView::createLayerN();
    
    SCENE_M->addDialog(_layer);
    
    
    _layer->setGuideType((int)type);
    _layer->setShowPoi(shouPoi);
    _layer->setTargetNode(node);
    _layer->setBtnScale(btnScale);
    _layer->setIdx(idx);
    _layer->startGuide();
    
    return true;
}

void FishGuideManager::nextGuide(GuideType type)
{
    auto isGuide = GETBOOL(StringUtils::format("isGuide_%d",type).c_str(),false);
    if(isGuide)return;
    endGuide();
    startGuide(type);
}

void FishGuideManager::endGuide(GuideType type,FishGuideView* layer,int idx)
{
    auto tempType = type == GuideType::None?_guideType:type;
    
    if(idx != -1)
    {
        SETBOOL(StringUtils::format("isGuide_%d_%d",tempType,idx).c_str(),true);
    }
    else
    {
        SETBOOL(StringUtils::format("isGuide_%d",tempType).c_str(),true);
    }
    
    isStartGuideVec[(int)tempType] = false;
    
    _guideType = GuideType::None;
    if(_layer)
    {
        _layer->hide();
        _layer = NULL;
    }
    else if(layer)
    {
        layer->hide();
    }
}

bool FishGuideManager::isEnd(GuideType type,int idx)
{
    bool isGuide = false;
    if(idx != -1)
    {
        isGuide = GETBOOL(StringUtils::format("isGuide_%d_%d",type,idx).c_str(),false);
    }
    else
    {
        isGuide = GETBOOL(StringUtils::format("isGuide_%d",type).c_str(),false);
    }
    
    auto isPlay = isStartGuideLv(type);
    
    return isGuide||!isPlay;
}

bool FishGuideManager::getIsStartGuide(GuideType type)
{
    auto isStart = isStartGuideVec[(int)type];
    return isStart;
}

bool FishGuideManager::isStartGuideLv(GuideType type)
{
    auto winNum = ScoreManager::getInstance()->getWinTotalCNT(true);
    
    //等级小于五级并且胜利局数小与5次
    bool isPlay = false;
    switch (type) {
        case GuideType::StartOne:
        {// 胜利五局以内
            isPlay = winNum <= 5;
        }
            break;
        case GuideType::WinOne:
        {//胜利五局以内
            isPlay = winNum <= 5;
        }
            break;
        case GuideType::NoMove:
        {//胜利五局以内
            isPlay = winNum <= 5;
        }
            break;
        case GuideType::Three:
        {//胜利五局以内
            isPlay = winNum <= 5;
        }
            break;
        case GuideType::LobbyOne:
        {//胜利五局以内
            isPlay = winNum <= 5;
        }
            break;
        case GuideType::ClickFishShop:
        {//打开鱼商店引导 任意等级
            isPlay = true;
        }
            break;
        case GuideType::FishShopOne:
        {//买鱼引导任意等级
            isPlay = true;
        }
            break;
        case GuideType::GetFishOne:
        {//获得第一条鱼提示任意等级
            isPlay = true;
        }
            break;
        case GuideType::unlockTipsOne:
        {//胜利五局以内
            isPlay = winNum <= 5;
        }
            break;
        case GuideType::getSuiPian:
        {//胜利五局以内
            isPlay = winNum <= 5;
        }
            break;
        case GuideType::unlockOne:
        {//胜利五局以内
            isPlay = winNum <= 5;
        }
            break;
        case GuideType::unlockFashTank:
        {//
            isPlay = true;
        }
            break;
        case GuideType::gotoLobby:
        {//
            isPlay = true;
        }
            break;
        case GuideType::ClickFashTank:
        {//
            isPlay = true;
        }
            break;
        case GuideType::UseFashTank:
        {//
            isPlay = true;
        }
            break;
        case GuideType::UseFashTankTipsOne:
        {//
            isPlay = true;
        }
            break;
        default:
            break;
    }
    
    return isPlay;
}

//鱼缸满了提示
void FishGuideManager::fishMaxGuide()
{
    _layer = FishGuideView::createLayerN();
    
    SCENE_M->addDialog(_layer,false,3);
    _layer->setGuideType((int)FishGuideManager::GuideType::None);
    _layer->setShowPoi(DEFAULTPOS);
    _layer->setTargetNode(NULL);
    _layer->setBtnScale(1);
    _layer->setIdx(-1);
    _layer->startGuide(Lang("100364"));
}
