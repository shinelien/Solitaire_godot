//
//  FishShop.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by 宋 on 2021/4/30.
//

#include <stdio.h>
#include "FishShop.h"
#include "BagGameBg.h"
#include "MainLobby.h"
#include "PlayerManager.h"
#include "FreeCoinLayer.h"
#include "GameViewHD.hpp"
#include "EventObserver.h"
#include "GrowupNode.h"
#include "FashTankItem.h"
#include "GoldShop.h"
#include "FishGuideManager.h"
const string TAB_PRFIX = "Button_tab";
const string NEW = "img_new_bg_%d";

FishShop::FishShop()
:BaseLayer("2021FishShop.csb")
{
    
}
FishShop::~FishShop()
{
    
}

void FishShop::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    auto panelView = getNode<Layout*>("Panel_view_fish");
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    
    FileNode_BagItem1 = getNode("FileNode_BagItem1");
    playAni("Start0",false,[this](){
        
        if(!GUIDE_M->isEnd(FishGuideManager::GuideType::FishShopOne)&&GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFishShop))
        {//点击商店引导结束后才能进行买鱼引导
            auto btn = guideNode->getNode("Button_gameBg");
            auto poi = btn->getPosition();
            poi = btn->getParent()->convertToWorldSpace(poi);
            auto scale = getNode("Node_6")->getScale();
            GUIDE_M->startGuide(FishGuideManager::GuideType::FishShopOne,guideNode,poi,scale);
            
            //更新价格
            guideNode->updateGuide();
        }
    });
}
void FishShop::initData()
{
    BaseLayer::initData();
    setName("FishShop");
    
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
}
void FishShop::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto btnName = btn->getName();
    if(btnName == "Button_close"||btnName == "Panel_top_0")
    {
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "")
    {
        
    }
    else if(btnName == "Button_getGold")
    {//领取金币
        SCENE_M->addDialog(GoldShop::createLayerN(GoldShop::GoldShopType::None,this));
        this->setVisible(false);
    }
    else if(btnName == "Button_getDiamond")
    {//领取钻石
        SCENE_M->addDialog(FreeCoinLayer::createLayerN(FreeCoinLayer::Type::Diamond,this));
    }
}


void FishShop::onEnter()
{
    BaseLayer::onEnter();
    
    //getNode<Text*>("text_title")->setString(Lang("100038"));
    setTab(Tab::FISH);
    
//    SCENE_M->getGameView()->showNode("Panel_top", false);
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("OpenFishShop")},
    });
}

void FishShop::onExit()
{
    BaseLayer::onExit();
    //窗口关闭
    DATA_M->fishNewClear();
    auto lobby = SCENE_M->getLobby();
    auto gameview = SCENE_M->getGameView();
    if(gameview->isVisible())
    {//恢复游戏 取消暂停
        gameview->gamePause(false);
    }
    else if(lobby)
    {
        lobby->isShowTop(true);
    }
    if(lobby)
    {
        lobby->updateFishNewTips();
    }
    
    EVENT_M->removeListener("event_game_update_coin",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
    
//    SCENE_M->getGameView()->showNode("Panel_top", true);
}

void FishShop::setTab(FishShop::Tab tab) {
    
    //if((int)tab == 5)return;
    if (_currentTab != tab) {
        
        auto panel_confirm = getNode("Panel_confirm");
        if (panel_confirm)
            panel_confirm->setVisible(false);
        _currentTab = tab;
        updateUI();
    }
}

FishShop::Tab FishShop::getTab() {
    return _currentTab;
}

const int SPLIT_FISH = 3;
const int SPLIT_FASHTANK = 1;
void FishShop::updateUI() {
    auto scrollViewBG = getNode<ListView*>("ListView_bg");
    scrollViewBG->setScrollBarEnabled(false);
    scrollViewBG->removeAllChildren();
    scrollViewBG->jumpToTop();
    
    auto size = scrollViewBG->getContentSize();

    int totalCNT = getTotalCNT(_currentTab);
    
    
    int SPLIT = getSPLIT(_currentTab);
    startIDX = 0;
    this->unschedule("create_tab");
    auto func = [this, totalCNT, scrollViewBG,SPLIT](float t){
        int i = 0;
        
        while (startIDX < ceil(totalCNT*1./SPLIT))
        {
            auto panel = getPanelView(_currentTab)->clone();
            auto panelSize = panel->getContentSize();
            if(_currentTab == FishShop::Tab::FISH)
            {
                for (int j=0;j<SPLIT;j++)
                {
                    auto idx = startIDX*SPLIT+j;
                    if (idx>=totalCNT) break;
                    auto fishId = newShopIdx[idx];
                    auto node = BagGameBg::createBagNode((int)_currentTab, idx,fishId,_fashTankIdx, CC_CALLBACK_1(FishShop::dealButtonClick, this),this,NULL);
                    node->setCascadeOpacityEnabled(true);
                    auto splitSize = panelSize/SPLIT;
                    auto p = Vec2(j*splitSize.width+splitSize.width/2,panelSize.height/2);
                    node->setPosition(p);
                    
                    if(idx == 0)
                    {
                        if(!GUIDE_M->isEnd(FishGuideManager::GuideType::FishShopOne))
                        {
                            guideNode = node;
                        }
                    }
                    panel->addChild(node);
                    //_gameBgitems.push_back(node);
                }
                scrollViewBG->pushBackCustomItem(panel);
            }
            
            ++startIDX;
            if (++i>=3) {
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

void FishShop::updateUI2()
{
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    updateCoin();
    updateDiamond();
}

Layout* FishShop::getPanelView(Tab tab)
{
    Layout* panelView = 0;
    switch (_currentTab) {
        case Tab::FISH:
            panelView = getNode<Layout*>("Panel_view_Changjing");
            break;
        case Tab::FASHTANK:
            panelView = getNode<Layout*>("Panel_view_Changjing");
            break;
    }
    return panelView;
}

int FishShop::getSPLIT(Tab tab)
{
    int SPLIT = 0;
    switch (_currentTab) {
        case Tab::FISH:
            SPLIT = SPLIT_FISH;
            break;
        case Tab::FASHTANK:
            SPLIT = SPLIT_FASHTANK;
            break;
    }
    return SPLIT;
}

int FishShop::getTotalCNT(Tab tab) {
    int totalCNT = 0;
    switch (_currentTab) {
        case Tab::FISH:
            totalCNT = FISH_NUM;
            break;
        case Tab::FASHTANK:
            totalCNT = FASH_TANK_NUM;
            break;
    }
    return totalCNT;
}

void FishShop::updateCoin(bool isDelay)
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

void FishShop::updateDiamond(bool isDelay)
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

Vec2 FishShop::getGoldWorldPoi()
{
    auto goldNode = getNode("img_icon_top_gold");
    auto poi = goldNode->getPosition();
    poi = goldNode->getParent()->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}
Vec2 FishShop::getdiamondWorldPoi()
{
    auto diamondNode = getNode("img_icon_top_diamond");
    auto poi = diamondNode->getPosition();
    poi = diamondNode->getParent()->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}
