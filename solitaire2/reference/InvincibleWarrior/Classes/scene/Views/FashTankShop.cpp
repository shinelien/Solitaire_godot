//  FishShop.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by 宋 on 2021/4/30.
//

#include <stdio.h>
#include "FashTankShop.h"
#include "BagGameBg.h"
#include "MainLobby.h"
#include "PlayerManager.h"
#include "FreeCoinLayer.h"
#include "GameViewHD.hpp"
#include "EventObserver.h"
#include "GrowupNode.h"
#include "FashTankItem.h"
#include "GameBackground.h"
#include "ShopManager.h"
#include "FishGuideManager.h"
const string TAB_PRFIX = "Button_tab";
const string NEW = "img_new_bg_%d";

FashTankShop::FashTankShop()
:BaseLayer("2021FishShop_0.csb")
{
    
}
FashTankShop::~FashTankShop()
{
    
}

void FashTankShop::initUI()
{
    BaseLayer::initUI();
    doLayout();
    getNode("Button_getGold")->setVisible(false);
    scrollViewBG = getNode<ListView*>("ListView_bg");
    
    _fashTankIdx = DATA_M->getCurrentFashTankIdx();
    _guanLifashTankIdx = _fashTankIdx;
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    
    FileNode_BagItem1 = getNode("FileNode_BagItem1");
    Image_top = getNode("Image_top");
    //Image_top->setVisible(false);
    
    //Button_guanLi = getNode<Button*>("Button_guanLi");
    Text_guanLi = getNode<Text*>("Text_guanLi");
    //Button_back = getNode<Button*>("Button_back");
    playAni("Start0",false,[this](){
        
        if(!GUIDE_M->isEnd(FishGuideManager::GuideType::UseFashTank,0)&&GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFashTank,0))
        {//点击商店引导结束后才能进行买鱼引导
            auto btn = guideNode->getNode("Button_goFashTank");
            auto poi = btn->getPosition();
            poi = btn->getParent()->convertToWorldSpace(poi);
            auto scale = getNode("Node_6")->getScale();
            GUIDE_M->startGuide(FishGuideManager::GuideType::UseFashTank,guideNode,poi,scale,0);
        }
    });
    BitmapFontLabel_lvNum = getNode<TextBMFont*>("BitmapFontLabel_lvNum");
    Text_lvStr = getNode<Text*>("Text_lvStr");
    //多语言
    getNode<Text*>("Text_fishNum")->setString(Lang("100349"));
}
void FashTankShop::initData()
{
    BaseLayer::initData();
    setName("FashTankShop");
    
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
void FashTankShop::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto btnName = btn->getName();
    if(btnName == "Button_close"||btnName == "Panel_top_0")
    {
        if(_currentTab == Tab::FISH)
        {
            toFashTank();
        }
        else
        {
            SCENE_M->removeLayer(this);
        }
        
    }
    else if(btnName == "Button_guanLi")
    {
        toFish(_fashTankIdx);
    }
    else if(btnName == "Button_back")
    {
        toFashTank();
    }
}


void FashTankShop::onEnter()
{
    BaseLayer::onEnter();
    
    //getNode<Text*>("text_title")->setString(Lang("100038"));
    toFashTank();
    
//    SCENE_M->getGameView()->showNode("Panel_top", false);
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("OpenFashTankShop")},
    });
}

void FashTankShop::onExit()
{
    BaseLayer::onExit();
    //窗口关闭
    DATA_M->fashTankNewClear();
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
        lobby->updateFashTankNewTips();
    }
    
    EVENT_M->removeListener("event_game_update_coin",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
    
//    SCENE_M->getGameView()->showNode("Panel_top", true);
}

void FashTankShop::setTab(FashTankShop::Tab tab) {
    
    //if((int)tab == 5)return;
    auto panel_confirm = getNode("Panel_confirm");
    if (panel_confirm)
        panel_confirm->setVisible(false);
    _currentTab = tab;
    updateUI();
}

FashTankShop::Tab FashTankShop::getTab() {
    return _currentTab;
}

const int SPLIT_FISH = 3;
const int SPLIT_FASHTANK = 1;
void FashTankShop::updateUI() {
    updateCoin();
    updateDiamond();
    
    
    scrollViewBG->setScrollBarEnabled(false);
    scrollViewBG->removeAllChildren();
    
    auto size = scrollViewBG->getContentSize();

    auto vec = DATA_M->getFishTypeVec(_guanLifashTankIdx);
    int totalCNT = getTotalCNT(_currentTab);
    if(_currentTab == FashTankShop::Tab::FISH)
    {
        totalCNT = (int)vec.size();
    }
    auto fashTankIdx = DATA_M->getCurrentFashTankIdx();
    int SPLIT = getSPLIT(_currentTab);
    startIDX = 0;
    this->unschedule("create_tab");
    auto func = [this, totalCNT,SPLIT,vec,fashTankIdx](float t){
        int i = 0;
        
        while (startIDX < ceil(totalCNT*1./SPLIT))
        {
            auto panel = getPanelView(_currentTab)->clone();
            auto panelSize = panel->getContentSize();
            if(_currentTab == FashTankShop::Tab::FISH)
            {
                for (int j=0;j<SPLIT;j++)
                {
                    auto idx = startIDX*SPLIT+j;
                    if (idx>=totalCNT) break;
                    auto type = vec.at(idx);
                    
                    auto node = BagGameBg::createBagNode((int)_currentTab,idx, type,_guanLifashTankIdx, CC_CALLBACK_1(FashTankShop::dealButtonClick, this),NULL,this);
                    node->setCascadeOpacityEnabled(true);
                    auto splitSize = panelSize/SPLIT;
                    node->setPosition(Vec2(j*splitSize.width+splitSize.width/2,panelSize.height/2));
                    panel->addChild(node);
                    //_gameBgitems.push_back(node);
                }
                scrollViewBG->pushBackCustomItem(panel);
            }
            else if(_currentTab == FashTankShop::Tab::FASHTANK)
            {
                for (int j=0;j<SPLIT;j++)
                {
                    auto idx = startIDX*SPLIT+j;
                    if (idx>=totalCNT) break;
                    
                    auto node = FashTankItem::createBagNode(idx,this);
                    node->setCascadeOpacityEnabled(true);
                    auto splitSize = panelSize/SPLIT;
                    node->setPosition(Vec2(j*splitSize.width+splitSize.width/2,panelSize.height*0.45f));
                    panel->addChild(node);
                    if(idx == 1)
                    {
                        if(!GUIDE_M->isEnd(FishGuideManager::GuideType::UseFashTank,0))
                        {
                            guideNode = node;
                        }
                    }
                    //_gameBgitems.push_back(node);
                }
                scrollViewBG->pushBackCustomItem(panel);
            }
            
            ++startIDX;
            if (++i>=4) {
                //refush(false);
                return;
            }
        }
        if(_currentTab == FashTankShop::Tab::FISH)
        {
            scrollViewBG->jumpToTop();
        }
        else if(_currentTab == FashTankShop::Tab::FASHTANK)
        {
            if(!GUIDE_M->isEnd(FishGuideManager::GuideType::UseFashTank,0)&&GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFashTank,0))
            {//点击商店引导结束后才能进行买鱼引导
                scrollViewBG->jumpToItem(1, Vec2(0,1), Vec2(0,1));
            }
            else if(fashTankIdx == FASH_TANK_NUM-1)
            {
                scrollViewBG->jumpToBottom();
            }
            else if(fashTankIdx > 0)
            {
                scrollViewBG->jumpToItem(fashTankIdx, Vec2(0,1), Vec2(0,1));
            }
            else
            {
                scrollViewBG->jumpToTop();
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
}

void FashTankShop::updateUI2()
{
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    
    updateCoin();
    updateDiamond();
}

Layout* FashTankShop::getPanelView(Tab tab)
{
    Layout* panelView = 0;
    switch (_currentTab) {
        case Tab::FISH:
            panelView = getNode<Layout*>("Panel_view_fish");
            break;
        case Tab::FASHTANK:
            panelView = getNode<Layout*>("Panel_view_Changjing");
            break;
    }
    return panelView;
}

int FashTankShop::getSPLIT(Tab tab)
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

int FashTankShop::getTotalCNT(Tab tab) {
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

void FashTankShop::updateCoin(bool isDelay)
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

void FashTankShop::updateDiamond(bool isDelay)
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

Vec2 FashTankShop::getGoldWorldPoi()
{
    auto goldNode = getNode("img_icon_top_gold");
    auto poi = goldNode->getPosition();
    poi = goldNode->getParent()->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}
Vec2 FashTankShop::getdiamondWorldPoi()
{
    auto diamondNode = getNode("img_icon_top_diamond");
    auto poi = diamondNode->getPosition();
    poi = diamondNode->getParent()->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}

void FashTankShop::setFashTankIdx(int idx)
{
    if(_fashTankIdx != idx)
    {
        _fashTankIdx = idx;
        DATA_M->setCurrentFashTankIdx(idx);
        SCENE_M->getGameBackground()->updateBg();
        updateUI2();
    }
    SCENE_M->removeLayer(this);
}

void FashTankShop::toFish(int guanLiIdx)
{
    auto lv = PlayerManager::getInstance()->getLevel();
    auto unLockLv = ShopManager::getInstance()->getFashTankUnlockLv(guanLiIdx);
    bool isUnlock = lv >= unLockLv;
    scrollViewBG->setVisible(isUnlock);
    if(!isUnlock)
    {
        
        BitmapFontLabel_lvNum->setString(StringUtils::toString(unLockLv));
        Text_lvStr->setString(StringUtils::format(Lang("100348").c_str(),unLockLv));
    }
    else
    {
        _guanLifashTankIdx = guanLiIdx;
        setTab(Tab::FISH);
        //Button_guanLi->setVisible(false);
        //Button_back->setVisible(true);
        //Image_top->setVisible(true);
    }
}

void FashTankShop::toFashTank()
{
    scrollViewBG->setVisible(true);
    setTab(Tab::FASHTANK);
    //Button_guanLi->setVisible(true);
    //Button_back->setVisible(false);
    //Image_top->setVisible(false);
}

