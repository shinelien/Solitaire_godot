//
// Created by  on 2019-06-03.
//

#include "HomeSetting.h"
#include "GameKitHelper.h"
#include "SettingViewHD.h"
#include "ScoreManager.h"
#include "CountLayer.h"
//fankui
#include "FeedBackView.h"
#include "ShareRewardView.h"
#include "LikemeView.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "GamePayment.h"
#endif
#include "SubscriptionView.h"
#include "RankView.h"
#include "FishGuideManager.h"

void HomeSetting::initUI() {
    BaseLayer::initUI();
    doLayout();
    playAni("Start", false);
    //UIUtils::playInnerAction(getNode("FileNode_setting"), "loop", true);
    img_new_lobby_share = getNode("img_new_lobby_share");
    auto isNew = DATA_M->isNewVer();
    getNode("img_new_Ver")->setVisible(isNew);
  
    //只提示一次
    if(setNewNum == 1)
    {
        SETINTEGER("setNewNum",0);
    }
    
    img_new_lobby_share->setVisible(setNewNum == 1);//每天第一次分享有叹号
    // 多语言
    getNode<Text*>("Text_info")->setString(Lang("100006"));//统计
    getNode<Text*>("Text_rank")->setString(Lang("100121"));//排行
    getNode<Text*>("Text_setting")->setString(Lang("100122"));//设置
    getNode<Text*>("Text_one")->setString(Lang("100119"));//分享
    getNode<Text*>("Text_fanKui")->setString(Lang("100274"));//反馈
    getNode<Text*>("Text_jiaoxue")->setString(Lang("100275"));//1 card
    getNode<Text*>("Text_dingyue")->setString(Lang("100324"));//订阅
    
}

void HomeSetting::initData() {
    BaseLayer::initData();
    setName("HomeSetting");
}

void HomeSetting::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    
    auto btnName = btn->getName();

    if (btnName == "Button_jiaoxue") {
        auto lobby = SCENE_M->getLobby();
        if(lobby)
        {
            
            lobby->hideLobby([lobby](){
                lobby->setVisible(false);
                auto gameView = SCENE_M->getGameView();
                if(gameView)
                {
                    gameView->setVisible(true);
                    gameView->startTeachBureau();
                }
            });
            
        }
        
    }
    else if (btnName == "btn_set_close" || btnName == "Panel_out") {
        
    }
    else if (btnName == "Button_info") {
        //显示统计界面
        SCENE_M->addDialog(CountLayer::createLayer());
    }
    else if (btnName == "Button_rank") {
        //GameKitHelper::showLeaderBoard();
        SCENE_M->addDialog(RankView::createLayerN(RankView::RankType::Lobby));
    }
    else if (btnName == "Button_setting") {
        SCENE_M->addDialog(SettingViewHD::createLayerN(SettingViewHD::ViewType::Home));
    }
    else if (btnName == "Button_fanKui") {
        SCENE_M->addDialog(FeedBackView::createLayerN());
    }
    else if (btnName == "Button_pingJia") {
        //SCENE_M->addDialog(LikemeView::createLayerN());
    }
    else if (btnName == "Button_one") {
//        img_new_lobby_share->setVisible(false);//触发按钮！隐藏
        //分享不给金币了，禁止弹窗直接分享
        UIUtils::shareApp();
    }
    else if (btnName == "Button_dingyue") {
        // 测试内购
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        string nodAdId = NoAdKey;
        GamePayment::getInstance()->req_iap(nodAdId);
        SCENE_M->addDialog(SubscriptionView::createLayerN());
#endif
    }
    
    this->removeFromParent();
}

HomeSetting::HomeSetting()
:BaseLayer("UI_homeset.csb")
{
    setNewNum = GETINTEGER("setNewNum",0);
}

HomeSetting::~HomeSetting() {

}

void HomeSetting::onEnter() {
    BaseLayer::onEnter();
}
