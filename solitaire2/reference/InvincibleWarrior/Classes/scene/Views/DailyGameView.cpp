//
//  DailyGameView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/12.
//

#include <stdio.h>
#include "DailyGameView.h"
#include "DailyNode.h"
#include "DailyMoreView.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
#include "FishGuideManager.h"

DailyGameView::DailyGameView(DailyNode*selectedNode,DailyMoreView* dailyView)
:BaseLayer("2020Daily_gameNode.csb")
,_selectedNode(selectedNode)
,_dailyView(dailyView)
{
    
}
DailyGameView::~DailyGameView()
{
    
}

void DailyGameView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    setLocalZOrder(3);
    setPosition(getContentSize()*0.5f);
    setVisible(false);
    updateUI();
    updateDYY();
}

void DailyGameView::initData()
{
    BaseLayer::initData();
    setName("DailyGameView");
    
}
void DailyGameView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    if(dynamic_cast<Button*>(btn))
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
    }
    auto btnName = btn->getName();
    if (btnName.find("Button_start") != string::npos) {
        
        SCENE_M->getRewardNode()->setVisible(false);
        
        auto date = _selectedNode->getDate();
        int dayofyear = date.DayOfYear();
        string num{btnName.back()};
        auto deck = DailyManager::getInstance()->getDeckByDay(dayofyear, num);
        DailyManager::getInstance()->setCurrentDaily(date, num);
        SCENE_M->getGameView()->startDaily(deck, num);
        UIUtils::FIRAnalyticsEventWithPrefix("gameStartDaily");
        //
        //getNode("FileNode_start")->setVisible(false);
        
        SCENE_M->getLobby()->setVisible(false);
        //恢复音效
        //SOUND_M->resumeDTEffect();
        SCENE_M->getGameView()->playMusic();
        SCENE_M->getGameView()->playEffect();
        this->removeFromParent();
        
        SCENE_M->removeLayer(_dailyView);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("daily_start")},
            {"value", Value(date.name())}
        });
    }
    else if (btnName == "Button_get") {
        getNode("panel_dailyget")->setVisible(false);
        getNode("Panel_1")->setVisible(false);
       // _dailyView->showCompleteAni();
        
        //SCENE_M->removeLayer(this);
    }
    else if(btnName == "btn_dailyclose"||btnName == "Panel_out")
    {
        _dailyView->setVisible(true);
        _dailyView->playAni("Start0", false);
        
        _dailyView->setFileNodeStart(NULL);
        this->removeFromParent();
    }
}

void DailyGameView::updateUI()
{
    if(_selectedNode)
    {
        auto date = _selectedNode->getDate();
                for (int i=1; i<=4; ++i) {
                    bool complete = DailyManager::getInstance()->isDailyCompleted(date, toString(i));
                    string btnImgName0 = complete?"btn_blue0.png":"btn_gre0.png";
                    string btnImgName1 = complete?"btn_blue1.png":"btn_gre1.png";
        //            getNode(StringUtils::format("Sprite_cown%d", i))->setVisible(complete);
        //            getNode<Button*>(StringUtils::format("Button_start%d", i))->setEnabled(!complete);
                    auto btnStart = getNode<Button*>(StringUtils::format("Button_start%d", i));
                    btnStart->loadTextures(btnImgName0, btnImgName1, btnImgName0, Widget::TextureResType::PLIST);
                    auto Text_Name = btnStart->getChildByName<Text*>("Text_Name");
                    Text_Name->setString(complete?Lang("100149"):Lang("100150"));
                    UIUtils::textAdaptiveSize(Text_Name, 230);
                    if (i!=4) {
                        getNode<Text*>(StringUtils::format("Text_rewardTitle%d", i))->setString(Lang(complete?"100151":"100152"));
                    }
                    getNode(StringUtils::format("Level_win%d", i))->setVisible(complete);
                }
                auto cnt = DailyManager::getInstance()->getCompleteCNT(date);
                getNode<LoadingBar*>("LoadingBar_rewardPercent")->setPercent(cnt/3.0f * 100);
    }
    
}
void DailyGameView::updateDYY()
{
    for (int i=1; i<=4; ++i) {
        if (i == 4 || i == 2) {
            auto text = getNode<Text*>(StringUtils::format("text_modeContext%d", i));
            text->setString(Lang("100168"));
            UIUtils::textAdaptiveSize(text,370);
        }
        else {
            getNode<Text*>(StringUtils::format("text_modeContext%d", i))->setString(Lang("100167"));
        }
        getNode<Text*>(StringUtils::format("text_mode%d", i))->setString(Lang(toString(100096+i)));
    }
    getNode<Text*>("Text_dailyDialogTitle")->setString(Lang("100165"));
    getNode<Text*>("Text_getReward")->setString(Lang("100176"));
    getNode<Text*>("Text_rewardTitle")->setString(Lang("100152"));
}


void DailyGameView::setDailyNode(DailyNode* node)
{
    _selectedNode = node;
}

void DailyGameView::onEnter()
{
    BaseLayer::onEnter();
}

void DailyGameView::onExit()
{
    BaseLayer::onExit();
}
