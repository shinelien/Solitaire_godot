//
//  SubscriptionView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by 宋 on 2020/7/17.
//

#include <stdio.h>
#include "SubscriptionView.h"
#include "SceneManager.h"
#include "EventObserver.h"
#include "RankManager.hpp"

SubscriptionView::SubscriptionView()
:BaseLayer("2020Subscription.csb")
{
    
}
SubscriptionView::~SubscriptionView()
{
    
}

void SubscriptionView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    //描述
    getNode<Text*>("Text_title")->setString("VIP");
    //无广告
    getNode<Text*>("Text_noAds");
    //解锁挑战
    getNode<Text*>("Text_daily");
    //专属主题
    getNode<Text*>("Sprite_theme");
    
    getNode<Text*>("Text_94")->setString(Lang("100392"));
    getNode<Text*>("Text_fanPaiNum")->setString("50%");
    getNode<Text*>("Text_fanPaiNum_0")->setString(Lang("100398"));
    
    //周
    auto subWeek = RankManager::getInstance()->getSubProduct("sub_noads_week");
    getNode<Text*>("text_week")->setString(Lang("100395"));
    getNode<Text*>("text_week_num")->setString(subWeek!=nullptr?StringUtils::format("%s%s", subWeek->getCurrencyCode().c_str(), subWeek->getShowStr().c_str()):"$1.99");
    
    //月
    auto subMonth = RankManager::getInstance()->getSubProduct("sub_noads_month");
    getNode<Text*>("text_month")->setString(Lang("100396"));
    getNode<Text*>("text_month_num")->setString(subMonth!=nullptr?StringUtils::format("%s%s", subMonth->getCurrencyCode().c_str(), subMonth->getShowStr().c_str()):"$5.99");
    //年
    auto subHalfyear = RankManager::getInstance()->getSubProduct("sub_noads_halfyear");
    getNode<Text*>("text_year")->setString(Lang("100397"));
    getNode<Text*>("text_year_num")->setString(subHalfyear!=nullptr?StringUtils::format("%s%s", subHalfyear->getCurrencyCode().c_str(), subHalfyear->getShowStr().c_str()):"$17.99");
    
    //协议
    getNode<Text*>("Text_yinsi")->setString(Lang("100108"));
    getNode<Text*>("Text_dingyue")->setString(Lang("100394"));

    updateUI();
}
void SubscriptionView::initData()
{
    BaseLayer::initData();
    setName("SubscriptionView");
}
void SubscriptionView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
    if(btnName == "btn_close"||btnName == "Panel_root")
    {//
        SCENE_M->removeLayer(this);
    }
    else if (btnName == "btn_week")
    {
        UIUtils::calIAP("sub_noads_week", true);
    }
    else if (btnName == "btn_month")
    {
        UIUtils::calIAP("sub_noads_month", true);
    }
    else if (btnName == "btn_year")
    {
        UIUtils::calIAP("sub_noads_halfyear", true);
    }
    else if (btnName == "Text_fuwu")
    {
        
    }
    else if (btnName == "Text_yinsi")
    {
        Application::getInstance()->openURL("https://sites.google.com/view/space-cat-studio/%E9%A6%96%E9%A1%B5");
    }
    else if (btnName == "Text_dingyue")
    {
        Application::getInstance()->openURL("https://play.google.com/store/apps/details?id=com.cn.spacecate.solitaire2k");
    }
}

void SubscriptionView::updateUI() {
    auto isVip = DATA_M->isVipNoAds();
    getNode<Button*>("btn_week")->setEnabled(!isVip);
    getNode<Button*>("btn_month")->setEnabled(!isVip);
    getNode<Button*>("btn_year")->setEnabled(!isVip);

    //描述
//    getNode<Text*>("Text_title")->setString("VIP");
}

void SubscriptionView::onEnter() {
    BaseLayer::onEnter();
    EVENT_M->addListener("game_purchase_sub_update", [this] (ValueMap params, void *) {
        this->updateUI();
    }, this);
}

void SubscriptionView::onExit() {
    BaseLayer::onExit();
    EVENT_M->removeListener("game_purchase_sub_update", this);
}
