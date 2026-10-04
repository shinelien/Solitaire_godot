//
//  GoldShop.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/25.
//

#include <stdio.h>
#include "GoldShop.h"
#include "GoldItem.h"
#include "MainLobby.h"
#include "PlayerManager.h"
#include "FreeCoinLayer.h"
#include "GameViewHD.hpp"
#include "EventObserver.h"
#include "GrowupNode.h"
#include "FashTankItem.h"
#include "GameBackground.h"
#include "ShopManager.h"
#include "AppConstant.h"
#include "RankManager.hpp"

const string TAB_PRFIX = "Button_tab";
const string NEW = "img_new_bg_%d";

GoldShop::GoldShop(GoldShopType type,BaseLayer* layer)
:BaseLayer("2021GoldShop.csb")
,_type(type)
,_layer(layer)
{
    
}
GoldShop::~GoldShop()
{
    
}

void GoldShop::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    scrollViewBG = getNode<ListView*>("ListView_bg");
    Node_Gold = getNode("Panel_Gold");
    scrollViewBG->setVisible(false);
    Node_Gold->setVisible(true);
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    
    getNode("Button_getGold")->setVisible(false);
    playAni("Start0",false);
    
    
    
    updateMainUI();
    //描述
    getNode<Text*>("Text_store")->setString(Lang("100038"));
//    getNode<Text*>("Text_gold0")->setString(Lang("100358"));
//    getNode<Text*>("Text_gold1")->setString(Lang("100356"));
//    getNode<Text*>("Text_gold2")->setString(Lang("100356"));
    getNode<Text*>("Text_eWai")->setString(Lang("100359"));
    getNode<Text*>("Text_More")->setString(Lang("100360"));
//    //奖励数值
//    getNode<TextBMFont*>("BitmapFontLabel_gold0")->setString(toString(_productVec[0]->getPrice()));
//    getNode<TextBMFont*>("BitmapFontLabel_gold1")->setString(toString(_productVec[1]->getPrice()));
//    getNode<TextBMFont*>("BitmapFontLabel_gold2")->setString(toString(_productVec[2]->getPrice()));
//    //消费数值
//    getNode<TextBMFont*>("BitmapFontLabel_buy0")->setString(_productVec[0]->getShowStr());
//    getNode<TextBMFont*>("BitmapFontLabel_buy1")->setString(_productVec[1]->getShowStr());
//    getNode<TextBMFont*>("BitmapFontLabel_buy2")->setString(_productVec[2]->getShowStr());
//    //符号
//    getNode<Text*>("Text_fuHao0")->setString("$");
//    getNode<Text*>("Text_fuHao1")->setString(Lang("$"));
//    getNode<Text*>("Text_fuHao2")->setString(Lang("$"));
    
    updateCoin();
    updateDiamond();
}
void GoldShop::initData()
{
    BaseLayer::initData();
    setName("GoldShop");
    
    EVENT_M->addListener("event_game_update_coin", [this](ValueMap valueMap, void *obj){
        if(!valueMap.empty())
        {
            auto isTime = valueMap["isTime"].asBool();
            this->updateCoin(isTime);
        }
        else
        {
            this->updateCoin();
        }
    },this);
    EVENT_M->addListener("event_game_update_diamond", [this](ValueMap valueMap, void *obj){
        if(!valueMap.empty())
        {
            auto isTime = valueMap["isTime"].asBool();
            this->updateDiamond(isTime);
        }
        else
        {
            this->updateDiamond();
        }
    },this);
    addEvent("msg_purchase_update", [this](EventCustom *){
        if(scrollViewBG->isVisible())
        {
            this->updateUI();
        }
        
        this->updateMainUI();
    });
}
void GoldShop::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto btnName = btn->getName();
    if(btnName == "Button_close"||btnName == "Panel_top_0")
    {
        SCENE_M->removeLayer(this);
    }
    else if (btnName.find("Button_buy") != string::npos)
    {
        
        auto tag = btn->getTag();
        auto isHotBuy = _productVec[tag]->isHot() && !_productVec[tag]->isHotBuy();
        UIUtils::calIAP(isHotBuy?_productVec[tag]->getHotID():_productVec[tag]->getID());
    }
    else if(btnName == "Button_More")
    {
        scrollViewBG->setVisible(true);
        Node_Gold->setVisible(false);
        setTab(Tab::Gold);
    }
}


void GoldShop::onEnter()
{
    BaseLayer::onEnter();
    
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("OpenGoldShop")},
    });
    
    
}

void GoldShop::onExit()
{
    BaseLayer::onExit();
    //窗口关闭
    auto lobby = SCENE_M->getLobby();
    auto gameview = SCENE_M->getGameView();
    if(lobby&&_type == GoldShopType::Lobby)
    {
        lobby->openReward(false);
        lobby->isShowTop(true);
    }
    if(_layer)
    {
        _layer->setVisible(true);
        _layer->playAni("Start0",false);
    }
    
    EVENT_M->removeListener("event_game_update_coin",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
    
//    SCENE_M->getGameView()->showNode("Panel_top", true);
}

void GoldShop::setTab(GoldShop::Tab tab) {
    
    //if((int)tab == 5)return;
    auto panel_confirm = getNode("Panel_confirm");
    if (panel_confirm)
        panel_confirm->setVisible(false);
    _currentTab = tab;
    updateUI();
}

GoldShop::Tab GoldShop::getTab() {
    return _currentTab;
}

const int SPLIT_GOLD = 1;
void GoldShop::updateUI() {
    scrollViewBG->setScrollBarEnabled(false);
    scrollViewBG->removeAllChildren();
    scrollViewBG->jumpToTop();
    
    const auto& products = RankManager::getInstance()->getProducts();
    auto size = scrollViewBG->getContentSize();
//    auto noAds = DATA_M->isVipNoAds();
    int totalCNT = products.size(); // getTotalCNT(_currentTab);

    int SPLIT = getSPLIT(_currentTab);
    startIDX = 0;
    this->unschedule("create_tab");
    auto func = [this, totalCNT,SPLIT](float t){
        int i = 0;
        
        while (startIDX < ceil(totalCNT*1./SPLIT))
        {
            auto panel = getPanelView(_currentTab)->clone();
            auto panelSize = panel->getContentSize();
            if(_currentTab == GoldShop::Tab::Gold)
            {
                for (int j=0;j<SPLIT;j++)
                {
                    auto idx = startIDX*SPLIT+j;
                    if (idx>=totalCNT) break;
                    auto node = GoldItem::createBagNode(idx,this);
                    node->setCascadeOpacityEnabled(true);
                    auto splitSize = panelSize/SPLIT;
                    node->setPosition(Vec2(j*splitSize.width+splitSize.width/2,panelSize.height/2));
                    panel->addChild(node);
                    //_gameBgitems.push_back(node);
                }
                scrollViewBG->pushBackCustomItem(panel);
            }
            
            ++startIDX;
            if (++i>=5) {
                //refush(false);
                return;
            }
        }
        //refush(false);
        this->unschedule("create_tab");
    };
    schedule(func, 0, "create_tab");
    func(0);
    
//    if((int)_currentTab == 2||(int)_currentTab == 3||(int)_currentTab == 4)
//    {
//        getNode("Button_tab2")->setVisible(true);
//        getNode("Button_tab3")->setVisible(true);
//    }
//    else
//    {
//        getNode("Button_tab2")->setVisible(false);
//        getNode("Button_tab3")->setVisible(false);
//    }
    updateCoin();
    updateDiamond();
}

void GoldShop::updateMainUI()
{
    auto sprite50 = getNode("pay_hot1_6");
    auto isPurchaseLimit = DATA_M->getPurchaseLimit();
    auto noAds = false; //DATA_M->isVipNoAds();
    
    sprite50->setVisible(!isPurchaseLimit);
    _shangPinId.clear();
    _productVec.clear();
    if(isPurchaseLimit)
    {
        if(noAds)
        {
            _shangPinId.push_back(0);
            _shangPinId.push_back(1);
            _shangPinId.push_back(2);
        }
        else
        {
            _shangPinId.push_back(1);
            _shangPinId.push_back(2);
            _shangPinId.push_back(3);
        }
        
    }
    else
    {
        _shangPinId.push_back(noAds?1:2);
        _shangPinId.push_back(1);
        _shangPinId.push_back(2);
    }
    
    
    const auto& products = RankManager::getInstance()->getProducts();
    for(int i = 0;i < _shangPinId.size();++i)
    {
        auto idx = _shangPinId.at(i);
        auto product = products.at(idx)->clone();
        if (i == 0) product->setHot(!isPurchaseLimit && !product->isHotBuy()); // 第一个是热门 有加成哦
        _productVec.push_back(product); // 复印一个新的
    }
    
    for (int i = 0; i<3; i++) {
        auto node = getNode(StringUtils::format("gold%d",i));
        getNode<Text*>(StringUtils::format("Text_gold%d", i))->setString(!isPurchaseLimit&&i == 0?Lang("100358"):Lang("100356"));
        //奖励数值
        getNode<TextBMFont*>(StringUtils::format("BitmapFontLabel_gold%d", i))->setString(toString(!isPurchaseLimit&&i == 0?_productVec[i]->getHotPrice():_productVec[i]->getPrice()));
        //消费数值
        getNode<TextBMFont*>(StringUtils::format("BitmapFontLabel_buy%d", i))->setString(!isPurchaseLimit&&i == 0?_productVec[i]->getHotShowStr():_productVec[i]->getShowStr());
        //符号
        getNode<Text*>(StringUtils::format("Text_fuHao%d", i))->setString(_productVec[i]->getCurrencyCode());
        
        //图片
        node->getChildByName("Node_new0")->setVisible(!isPurchaseLimit);
        node->getChildByName("Node_new1")->setVisible(isPurchaseLimit);
    }
    
    
}

void GoldShop::updateUI2()
{
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    
    updateCoin();
    updateDiamond();
}

Layout* GoldShop::getPanelView(Tab tab)
{
    Layout* panelView = 0;
    switch (_currentTab) {
        case Tab::Gold:
            panelView = getNode<Layout*>("Panel_view_gold");
            break;
    }
    return panelView;
}

int GoldShop::getSPLIT(Tab tab)
{
    int SPLIT = 0;
    switch (_currentTab) {
        case Tab::Gold:
            SPLIT = SPLIT_GOLD;
            break;
    }
    return SPLIT;
}

int GoldShop::getTotalCNT(Tab tab) {
    int totalCNT = 0;
    switch (_currentTab) {
        case Tab::Gold:
            totalCNT = ProductPrice.size();
            break;
    }
    return totalCNT;
}

void GoldShop::updateCoin(bool isDelay)
{
    auto text = getNode<TextBMFont*>("BitmapFontLabel_gold");
    auto vec = text->getChildren();
    for(auto child:vec)
    {
        auto grouwup = dynamic_cast<GrowupNode*>(child);
        if(grouwup)
        {
            grouwup->unTextSchedule();
        }
    }
    if(isDelay)
    {//2.45
        //auto text = getNode<TextBMFont*>("BitmapFontLabel_gold");
        auto str = text->getString();
        _coinNum = UIUtils::stoii(str);
        auto num = DATA_M->getCoinNum();
        auto tempNum = num - _coinNum;
        if(tempNum <= 0)
        {
            text->setString(StringUtils::toString(num));
            return;
        }
        float time = 0;
        if(tempNum >= 15)
        {
            time = 0.75/FLYSPEED;
        }
        else
        {
            time = 0.05/FLYSPEED * tempNum;
        }
        auto grouwup = GrowupNode::create();
        text->addChild(grouwup,0,88);
        grouwup->startGrouwup(text, _coinNum, num, time, "",[this, grouwup](){
            //UIUtils::playInnerAction(FileNode_gold, "jump", false);
            grouwup->removeFromParent();
        });
    }
    else
    {
        int coinNum = DATA_M->getCoinNum();
        text->setString(StringUtils::toString(coinNum));
    }
//    int coinNum = DATA_M->getCoinNum();
//    getNode<TextBMFont*>("BitmapFontLabel_gold")->setString(StringUtils::toString(coinNum));
}

void GoldShop::updateDiamond(bool isDelay)
{
//    auto text = getNode<TextBMFont*>("BitmapFontLabel_diamond");
//    auto vec = text->getChildren();
//    for(auto child:vec)
//    {
//        auto grouwup = dynamic_cast<GrowupNode*>(child);
//        if(grouwup)
//        {
//            grouwup->unTextSchedule();
//        }
//
//    }
//    if(isDelay)
//    {
//        //auto text = getNode<TextBMFont*>("BitmapFontLabel_diamond");
//        auto str = text->getString();
//        _diamondNum = UIUtils::stoii(str);
//        auto num = DATA_M->getDiamond();
//        auto tempNum = num - _diamondNum;
//        if(tempNum <= 0)
//        {
//            text->setString(StringUtils::toString(num));
//            return;
//        }
//        float time = 0;
//        if(tempNum >= 15)
//        {
//            time = 0.75/FLYSPEED;
//        }
//        else
//        {
//            time = 0.05/FLYSPEED * tempNum;
//        }
//        auto grouwup = GrowupNode::create();
//        text->addChild(grouwup,0,88);
//        grouwup->startGrouwup(text, _diamondNum, num, time, [this, grouwup](){
//            //UIUtils::playInnerAction(FileNode_gold, "jump", false);
//            grouwup->removeFromParent();
//        });
//    }
//    else
//    {
//        int diamondNum = DATA_M->getDiamond();
//        text->setString(StringUtils::toString(diamondNum));
//    }
}
