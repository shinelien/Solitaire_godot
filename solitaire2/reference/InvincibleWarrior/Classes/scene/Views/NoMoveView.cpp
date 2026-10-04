//
//  NoMoveView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/4.
//

#include <stdio.h>
#include "NoMoveView.h"
#include "GameViewHD.hpp"
#include "SceneManager.h"

NoMoveView::~NoMoveView()
{
    
}
NoMoveView::NoMoveView()
:BaseLayer("nomove.csb")
,isClose(false)
{
    
}

void NoMoveView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    _actionManager->play("Start0", false);
    _actionManager->setLastFrameCallFunc([this](){
        isClose = true;
    });
    getNode<Text*>("Text_title")->setString(Lang("100177"));
    auto text_guankan_0 = getNode<Text*>("text_guankan_0");
    text_guankan_0->setString(Lang("100180"));
    UIUtils::textAdaptiveSize(text_guankan_0,330);
    auto text_guankan = getNode<Text*>("text_guankan");
    text_guankan->setString(Lang("yihuode"));
    UIUtils::textAdaptiveSize(text_guankan,200);
}
void NoMoveView::initData()
{
    BaseLayer::initData();
    
}
void NoMoveView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto name = btn->getName();
    if(name == "Panel_close")
    {//关闭
        if(isClose)
        {
            auto game = SCENE_M->getGameView();
            //关闭窗口开始累计计时
            game->setIsOpenTipsTime(true);
            game->setIsShowTips(false);
            SCENE_M->removeLayer(this);
            UIUtils::FIRAnalyticsEvent("game_tips_close", {});
            UIUtils::FIRFirestoreAdd("operator", {
                    {"key", Value("noMoveView")},
                    {"value", Value("close")}
            });
        }
    }
    else if("Button_close" == name)
    {
        auto game = SCENE_M->getGameView();
        //关闭窗口开始累计计时
        game->setIsOpenTipsTime(true);
        game->setIsShowTips(false);
        SCENE_M->removeLayer(this);
        UIUtils::FIRAnalyticsEvent("game_tips_close", {});
        UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("noMoveView")},
                {"value", Value("close")}
        });
    }
    else if(name == "btn_use")
    {//使用道具
        auto game = SCENE_M->getGameView();
        game->useMagic();
        //关闭窗口开始累计计时
        game->setIsOpenTipsTime(true);
        game->setIsShowTips(false);
        SCENE_M->removeLayer(this);
        UIUtils::FIRAnalyticsEvent("game_tips_useMagic", {});
        UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("noMoveView")},
                {"value", Value("magic")}
        });
    }
    else if(name == "btn_agian")
    {//重开
        auto game = SCENE_M->getGameView();
        game->agianGame();
        //关闭窗口开始累计计时
        game->setIsOpenTipsTime(true);
        game->setIsShowTips(false);
        SCENE_M->removeLayer(this);
        UIUtils::FIRAnalyticsEvent("game_tips_agian", {});
        UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("noMoveView")},
                {"value", Value("again")}
        });
    }
}
