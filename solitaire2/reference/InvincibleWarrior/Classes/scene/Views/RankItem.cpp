//
//  RankItem.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/11.
//

#include <stdio.h>
#include "RankItem.h"
#include "RewardManager.h"
#include "MainLobby.h"
#include "DataManager.h"
#include "GameViewHD.hpp"
#include "RankFashTank.h"
#include "ScoreManager.h"
#include "RankManager.hpp"
#include "RankView.h"

RankItem::RankItem(RankView* rankView)
:BaseLayer("2021RankItem.csb")
,_rankView(rankView)
{
    
}
RankItem::~RankItem()
{
    
}
    
RankItem * RankItem::createBagNode(int idx,RankView* rankView)
{
    auto bagNode = RankItem::createLayerN(rankView);
    bagNode->setShopNodeState(idx);
    return bagNode;
}
void RankItem::setShopNodeState(int idx)
{
    const auto list = RankManager::getInstance()->getRankList();
    auto gameView = SCENE_M->getGameView();
    _rankArr = gameView->getRankArr();
//    int cnt = _rankArr.IsNull()||_rankArr.Size() == 0?1:_rankArr.Size();
    int cnt = list.size();
    if(cnt > 100) cnt = 100;
    vector<int> vec;
    vec.push_back(0);
    auto str = DATA_M->getMyName() == ""?"ME":DATA_M->getMyName();
    string name = cnt == 1?str:StringUtils::format("name_%d",idx + 1);
    int fashTankIdx = 0;
    int lv = 1;
    int score = cnt == 1?ScoreManager::getInstance()->getScore(1, ScoreManager::Type::TOTALSCORE):1000;
    string cy;
    string key;
    if(list.size() > 0)
    {
        auto tm = DATA_M->getContentTime();
        
        auto &rankItem = list.at(idx);
        lv = rankItem.getLv();
        name = rankItem.getName();
        score = rankItem.getP1();
        fashTankIdx = rankItem.getFishTankIdx();
        _fishVec = rankItem.getFishVec();
        _isDailyVec = rankItem.getIsDailyVec();
        _isFashTankUnlockVec = rankItem.getIsFashTankUnlockVec();
        cy = rankItem.getCy();
        key = rankItem.getKey();
//        lv = rankItem.getP2();
    }
    else
    {
        _fishVec = vec;
        _isDailyVec.clear();
        _isDailyVec.push_back(true);
        _isFashTankUnlockVec.clear();
        _isFashTankUnlockVec.push_back(true);
    }
    _key = key;
    _cy = cy;
    _idx = idx;
    _name = name;
    _fashTankId = fashTankIdx;
    _score = score;
    _lv = lv;
    auto rank = gameView->getMyRank();
    auto rankType = _rankView->getRankType();
    
    getNode("Button_look")->setVisible(rank != idx+1&&rankType != RankView::RankType::WinLayer);
    auto Text_rank = getNode<TextBMFont*>("BitmapFontLabel_rank");
    auto Text_name = getNode<Text*>("Text_name");
    auto Text_look = getNode<Text*>("Text_look");
    auto Text_score = getNode<Text*>("Text_score");
    Text_rank->setString(StringUtils::format("%d",idx+1));
    Text_name->setString(name);
    UIUtils::textAdaptiveSize(Text_name,225);
    Text_look->setString(Lang("100326"));
    Text_score->setString(StringUtils::format("%d",score));
    UIUtils::textAdaptiveSize(Text_score,150);
    Sprite_JiangBei->setVisible(idx < 3);
    if(idx < 3)
    {
        Sprite_JiangBei->setSpriteFrame(StringUtils::format("JiangBei_%d.png",102-idx));
    }
    
    updateUI();
}

void RankItem::initUI()
{
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    Sprite_JiangBei = getNode<Sprite*>("Sprite_JiangBei");
    
}
void RankItem::initData()
{
    BaseLayer::initData();
    
}

void RankItem::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;

    auto btnName = btn->getName();
    
    if(btnName == "Button_look")
    {//
        auto node = RankFashTank::createLayerN();
        SCENE_M->addDialog(node);
        node->initRankFashTank(this,NULL);
    }
}

void RankItem::updateUI()
{
    
}

void RankItem::updateName()
{
    auto Text_name = getNode<Text*>("Text_name");
    auto name = DATA_M->getMyName() == ""?"ME":DATA_M->getMyName();
    Text_name->setString(name);
}
