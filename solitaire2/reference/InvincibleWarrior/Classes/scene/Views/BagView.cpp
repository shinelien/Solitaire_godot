//
//  BagView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/29.
//

#include <stdio.h>
#include "BagView.h"
#include "BagNode.h"
#include "BagCardBg.h"
#include "BagCardFace.h"
#include "BagCardFaceItem.h"
#include "BagGameBg.h"
#include "BagMusic.h"
#include "BagMagic.h"
#include "MainLobby.h"
#include "PlayerManager.h"
#include "FreeCoinLayer.h"
#include "GameViewHD.hpp"
#include "TeachManager.h"
#include "ShuffleView.h"
#include "EventObserver.h"
#include "SpriteManager.h"
#include "GrowupNode.h"
#include "CardSprite.h"
#include "AtlasManager.h"
#include "GoldShop.h"
const string TAB_PRFIX = "Button_tab";
const string NEW = "img_new_bg_%d";

BagView::BagView(BagType bagType)
:BaseLayer("2020Bag.csb")
{
    _bagType = bagType;
}
BagView::~BagView()
{
    
}

void BagView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    if(_bagType == BagType::FISH)
    {
        getNode("Node_button")->setVisible(false);
    }
    else
    {
        getNode("Node_button")->setVisible(true);
    }
    
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    
    FileNode_BagItem1 = getNode("FileNode_BagItem1");
    playAni("Start0",false);
    //top
    
    getNode("img_new_bg_1")->setVisible(DATA_M->getIsPropNew(3));
    //getNode("img_new_bg_2")->setVisible(DATA_M->getIsPropNew(2));
    //getNode("img_new_bg_3")->setVisible(DATA_M->getIsPropNew(3));
    getNode("img_new_bg_23")->setVisible(DATA_M->getIsPropNew(2));
    getNode("img_new_bg_5")->setVisible(DATA_M->getIsPropNew(5));
    //getNode("img_new_bg_6")->setVisible(false);
    auto node = _rootNode;
    //INIT_BTN(node,"Button_tab1", CC_CALLBACK_1(BagView::dealButtonClick, this));
    //INIT_BTN(node,"Button_tab2_0", CC_CALLBACK_1(BagView::dealButtonClick, this));
    INIT_BTN(node,"Button_tab5", CC_CALLBACK_1(BagView::dealButtonClick, this));
    INIT_BTN(node,"Button_tab4", CC_CALLBACK_1(BagView::dealButtonClick, this));
    INIT_BTN(node,"Button_tab2", CC_CALLBACK_1(BagView::dealButtonClick, this));
    INIT_BTN(node,"Button_tab3", CC_CALLBACK_1(BagView::dealButtonClick, this));
    
    
    getNode<Text*>("text_title5")->setString(Lang("100240"));
    getNode<Text*>("text_title2_0")->setString(Lang("100245"));
    auto text_title4 = getNode<Text*>("text_title4");
    text_title4->setString(Lang("100179"));
    UIUtils::textAdaptiveSize(text_title4,170);
    
    auto Text_card_item1_get = getNode<Text*>("Text_card_item1_get");
    Text_card_item1_get->setString(Lang("yihuode"));
    UIUtils::textAdaptiveSize(Text_card_item1_get,320);
    getNode("Panel_teach")->setVisible(false); // 新手遮罩
}
void BagView::initData()
{
    BaseLayer::initData();
    setName("BagView");
    
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
void BagView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto btnName = btn->getName();
    if(btnName == "Button_close"||btnName == "Panel_top_0")
    {
        if(FileNode_BagItem1->isVisible())
        {
            FileNode_BagItem1->setVisible(false);
            getNode("Node_6")->setVisible(true);
            playAni("Start0",false);
        }
        else
        {
            TEACH_M->nextTeachStep(SCENE_M->getLobby());
            SCENE_M->removeLayer(this);
        }
        
        
    }
    else if(btnName == "")
    {
        
    }
    else if (btnName.find(TAB_PRFIX) != string::npos) {
        FileNode_BagItem1->setVisible(false);
        SOUND_M->playBtnClickAudio();
        DATA_M->propNewClear((int)_currentTab);//2 3 5
        int id = 1;
        if((int)_currentTab==3)
        {
            id = 1;
        }
        else if((int)_currentTab==2)
        {
            id = 23;
        }
        else if((int)_currentTab==5)
        {
            id = 5;
        }
        getNode(StringUtils::format(NEW.c_str(),id))->setVisible(false);
        auto tag = btn->getTag();
            
        
        if(tag == 7) tag = 2;
        
        setTab((BagView::Tab)tag);
    }
    else if (btnName == "select") {
        SOUND_M->playBtnClickAudio();
        int shopType = (int)(btn->getTag() / 1000);
        int selectIndex = btn->getTag() % 1000;
        if (shopType == 1){
            bool isUse = _gameBgitems[selectIndex]->setUse(true);
            if (isUse) {
                _gameBgitems[nowUseIndex[shopType - 1]]->setUse(false);
                nowUseIndex[shopType - 1] = selectIndex;
            }
        }
        else if(shopType == 3)
        {//_cardBgitems
            bool isUse = _cardBgitems[selectIndex]->setUse(true);
            if (isUse) {
                _cardBgitems[nowUseIndex[shopType - 1]]->setUse(false);
                nowUseIndex[shopType - 1] = selectIndex;
            }
            SPRITE_M->setShufflingFirst(SpriteManager::ShuffingType::Shuffing);
        }
        else if(shopType == 5)
        {//
            bool isUse = _musicitems[selectIndex]->setUse(true);
            if (isUse) {
                _musicitems[nowUseIndex[shopType - 1]]->setUse(false);
                nowUseIndex[shopType - 1] = selectIndex;
            }
        }
            
            
            UIUtils::FIRAnalyticsUserProperty(StringUtils::format("shop_gamebg_%d", shopType), StringUtils::format("shop_index_%d", selectIndex));
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("ShopSelect")},
                {"value", Value(StringUtils::format("%d_%d", _currentTab, selectIndex))}
            });
    }
    else if (btnName == "buy") {
//            SOUND_M->playBtnClickAudio();
//    //        int shopType = (int) (btn->getTag() / 1000);
//            int selectIndex = btn->getTag() % 1000;
//
//            bool isBuy = _items[selectIndex]->buy();
//            if (isBuy)
//            {
//                //购买成功--刷新所有的
//                refush(true);
//            }
//            else {
//                SCENE_M->showTips(Lang("100096"));
//            }
//            ValueMap valueMap;
//            valueMap["buy"] = Value(selectIndex);
//            UIUtils::FIRAnalyticsEvent("shop_buy", valueMap);
//            UIUtils::FIRFirestoreAdd("operator", {
//                {"key", Value("ShopBuy")},
//                {"value", Value(StringUtils::format("%d_%d", _currentTab, selectIndex))}
//            });
    }
    else if(btnName == "Button_zhengmian")
    {//弹出正面
        auto tag = btn->getTag();
        auto idx = tag%1000;

        
//        if(num > 0)
//        {//至少有一张牌
//            DATA_M->setPropNew(5,idx);
//            updateMusicNew();
//
//            bool isUse = _cardFaceitems[idx]->setUse(true);
//            if (isUse) {
//                if(nowUseIndex[2 - 1] != idx)
//                {
//                    _cardFaceitems[nowUseIndex[2 - 1]]->setUse(false);
//                    nowUseIndex[2 - 1] = idx;
//                }
//            }
//        }
        _cardFaceitems[idx]->setNew(false);
        updateBagItem1(idx);
    }
    else if(btnName == "Button_card_item1_close")
    {//正面
        FileNode_BagItem1->setVisible(false);
        getNode("Node_6")->setVisible(true);
        playAni("Start0",false);
    }
    else if(btnName == "Button_card_item1_get")
    {//正面
        auto index = btn->getTag();
        auto num = DATA_M->getCardFaceNum(index);
        auto id = DATA_M->getCardPicType(2);
        if(id == index&&0)
        {//是同一个  已经在使用中
            FileNode_BagItem1->setVisible(false);
        }
        else
        {
            if(num > 0)
            {//使用
                bool isUse = _cardFaceitems[index]->setUse(true);
                if (isUse) {
                    _cardFaceitems[nowUseIndex[2 - 1]]->setUse(false);
                    nowUseIndex[2 - 1] = index;
                }
                FileNode_BagItem1->setVisible(false);
                getNode("Node_6")->setVisible(true);
                playAni("Start0",false);
            }
            else
            {
                auto gameview = SCENE_M->getGameView();
                auto lobby = SCENE_M->getLobby();
                if(lobby&&!gameview->isVisible())
                {
                    //跳转商店
//                    lobby->isShowTop(true);
//                    lobby->setTab(MainLobby::Tab::Store);
                }
                
                SCENE_M->removeLayer(this);
            }
        }
        
        
    }
    else if("Button_Shop" == btnName)
    {//音乐
        auto gameview = SCENE_M->getGameView();
        auto lobby = SCENE_M->getLobby();
        if(lobby&&!gameview->isVisible())
        {
            //跳转商店
//            lobby->isShowTop(true);
//            lobby->setTab(MainLobby::Tab::Store);
        }
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_magic")
    {//魔发棒
        SCENE_M->addDialog(ShuffleView::createLayerN(ShuffleView::Type::Bag));
        getNode("Panel_top_0")->setVisible(false);
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


void BagView::onEnter()
{
    BaseLayer::onEnter();
    for (int i=2;i<=5;i++) {
        _tabBtnVec.push_back(getNode<Button*>(TAB_PRFIX + StringUtils::toString(i)));
        auto text = getNode<Text*>(StringUtils::format("text_title%d", i));
        text->setString(Lang(toString(100122+i)));
        if(i == 2||i == 3)
        {
            UIUtils::textAdaptiveSize(text,200);
        }
    }
    //getNode<Text*>("text_title")->setString(Lang("100038"));
    
    if(_bagType == BagType::FISH)
    {
        setTab(Tab::FISH);
    }
    else
    {
        setTab(Tab::POKER_BACK);
    }
    
//    SCENE_M->getGameView()->showNode("Panel_top", false);
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("OpenShop")},
    });
}

void BagView::onExit()
{
    BaseLayer::onExit();
    //窗口关闭
    DATA_M->propNewClear();
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
        lobby->updataBagNew();
    }
    
    EVENT_M->removeListener("event_game_update_coin",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
    
//    SCENE_M->getGameView()->showNode("Panel_top", true);
}


void BagView::showSelect(int shopType, int shopIndex, const string name) {
    if (name == "select") {
        bool isUse = _items[shopIndex]->setUse(true);
        if (isUse) {
            _items[nowUseIndex[shopType - 1]]->setUse(false);
            nowUseIndex[shopType - 1] = shopIndex;
        }
        UIUtils::FIRAnalyticsUserProperty(StringUtils::format("shop_gamebg_%d", shopType), StringUtils::format("shop_index_%d", shopIndex));
        UIUtils::FIRFirestoreAdd("ShopSelect", {
            {"key", Value("ShopBuy")},
            {"value", Value(StringUtils::format("%d_%d", shopType, shopIndex))}
        });
    }
    else if (name == "buy") {
//        bool isBuy = _items[shopIndex]->buy();
//        if (isBuy)
//        {
//            //购买成功--刷新所有的
//            refush(true);
//        }
//        else {
//            SCENE_M->showTips(Lang("100096"));
//        }
//        ValueMap valueMap;
//        valueMap["buy"] = Value(shopIndex);
//        UIUtils::FIRAnalyticsEvent("shop_buy", valueMap);
//        UIUtils::FIRFirestoreAdd("operator", {
//            {"key", Value("ShopBuy")},
//            {"value", Value(StringUtils::format("%d_%d", shopType, shopIndex))}
//        });
    }
}

void BagView::setTab(BagView::Tab tab) {
    
    //if((int)tab == 5)return;
    if (_currentTab != tab) {
        
        auto panel_confirm = getNode("Panel_confirm");
        if (panel_confirm)
            panel_confirm->setVisible(false);
        _currentTab = tab;
        for (auto btn:_tabBtnVec) {
            if(btn->getTag() == 7)
            {
                auto is = (int)tab != 2&&(int)tab != 3;
                btn->setEnabled(is);
            }
            else
            {
                btn->setEnabled((int)tab != btn->getTag());
            }
            
        }
        
        
        updateUI();
        
        TEACH_M->nextTeachStep(this);
        // 特殊处理 5s 后显示关闭
        scheduleOnce([this](float){
            TEACH_M->nextTeachStep(this);
        }, 5.f, "schedule_teach_finger_key");
        if (TEACH_M->isTeaching()) {
            UIUtils::FIRAnalyticsEventWithPrefix("openBagView", "teach");
        }
    }
}

BagView::Tab BagView::getTab() {
    return _currentTab;
}

const int SPLIT_BG = 3;
const int SPLIT_CHANGJING = 3;
const int SPLIT_ZHENGMIAN = 2;
const int SPLIT_FISH = 3;
void BagView::updateUI() {
    auto scrollViewBG = getNode<ListView*>("ListView_bg");
    scrollViewBG->setScrollBarEnabled(false);
    scrollViewBG->removeAllChildren();
    scrollViewBG->jumpToTop();
    _items.clear();
    auto size = scrollViewBG->getContentSize();

    int totalCNT = getTotalCNT(_currentTab);
    
    
    int SPLIT = getSPLIT(_currentTab);
    _cardBgitems.clear();
    _gameBgitems.clear();
    _cardFaceitems.clear();
    _musicitems.clear();
    _magicitems.clear();
    startIDX = 0;
    this->unschedule("create_tab");
    auto func = [this, totalCNT, scrollViewBG, SPLIT, size](float t){
        if (_currentTab == Tab::MUSIC) {
            int i = 0;
            
            while(startIDX < LobbyMusicTotalCNT)
            {
                auto panel = getPanelView(_currentTab)->clone();
                auto panelSize = panel->getContentSize();
                
                auto node = BagMusic::createBagNode((int)_currentTab, startIDX, CC_CALLBACK_1(BagView::dealButtonClick, this),this);
                node->setCascadeOpacityEnabled(true);
                panel->addChild(node);
                node->setPosition(Vec2(panelSize.width/2,panelSize.height*0.47f));
                if (startIDX == DATA_M->getCardPicType((int)_currentTab))
                {
                    //node->setMusicUse(true);
                }
                nowUseIndex[(int)_currentTab-1] = DATA_M->getCardPicType((int)_currentTab);
                scrollViewBG->pushBackCustomItem(panel);
               _musicitems.push_back(node);
                
                startIDX++;
                i++;
                
                if(i >= 6)
                {
                    return;
                }
            }
            this->unschedule("create_tab");
        }
        else{
            int i = 0;
            
            while (startIDX < ceil(totalCNT*1./SPLIT))
            {
                auto panel = getPanelView(_currentTab)->clone();
                auto panelSize = panel->getContentSize();
                if(_currentTab == BagView::Tab::POKER_BACK)
                {//
                    for (int j=0;j<SPLIT;j++)
                    {
                        auto idx = startIDX*SPLIT+j;
                        if (idx>=totalCNT) break;
                        
                        auto node = BagCardBg::createBagNode((int)_currentTab, idx, CC_CALLBACK_1(BagView::dealButtonClick, this),this);
                        node->setCascadeOpacityEnabled(true);
                        auto splitSize = panelSize/SPLIT;
                        node->setPosition(Vec2(j*splitSize.width+splitSize.width/2,panelSize.height/2));
                        if (idx == DATA_M->getCardPicType((int)_currentTab))
                        {
                            node->setUse(true,true);
                            nowUseIndex[(int)_currentTab-1] = DATA_M->getCardPicType((int)_currentTab);
                        }
                        panel->addChild(node);
                        _cardBgitems.push_back(node);
                    }
                    // 优化帧率 不该显示时候不显示
                    panel->schedule([panel, scrollViewBG, size](float){
//                            CCLOG("PP1 %f_%f", panel->getPositionX(), panel->getPositionY());
                        auto worldPos = panel->convertToWorldSpaceAR(Vec2::ZERO);
                        auto nodePos = scrollViewBG->convertToNodeSpace(worldPos);
//                            CCLOG("PP2 %f_%f", nodePos.x, nodePos.y);
                        auto flag = nodePos.y < size.height && nodePos.y > -300;
                        panel->setVisible(flag);
                    }, 1.0f/30, "panel_schedule");
                    scrollViewBG->pushBackCustomItem(panel);

                }
                else if(_currentTab == BagView::Tab::POKER_FORE)
                {
                    
                    for (int j=0;j<SPLIT;j++)
                    {
                        auto idx = startIDX*SPLIT+j;
                        if (idx>=totalCNT) break;
                        
                        auto node = BagCardFace::createBagNode((int)_currentTab, idx, CC_CALLBACK_1(BagView::dealButtonClick, this),this);
                        node->setCascadeOpacityEnabled(true);
                        auto splitSize = panelSize/SPLIT;
                        node->setPosition(Vec2(j*splitSize.width+splitSize.width/2,panelSize.height/2));
                        if (idx == DATA_M->getCardPicType((int)_currentTab))
                        {
                            node->setUse(true,true);
                            nowUseIndex[(int)_currentTab-1] = DATA_M->getCardPicType((int)_currentTab);
                        }
                        panel->addChild(node);
                        _cardFaceitems.push_back(node);
                    }
                    scrollViewBG->pushBackCustomItem(panel);
                }
                else if(_currentTab == BagView::Tab::PROPS)
                {
                    for (int j=0;j<SPLIT;j++)
                    {
                        //auto idx = startIDX*SPLIT+j;
                        if (startIDX>=SPLIT) break;
                        
                        auto node = BagMagic::createBagNode((int)_currentTab, 0, CC_CALLBACK_1(BagView::dealButtonClick, this));
                        node->setCascadeOpacityEnabled(true);
                        
                        node->setPosition(Vec2(panelSize.width/2,panelSize.height/2));
                        
                        panel->addChild(node);
                        _magicitems.push_back(node);
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
        }
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

void BagView::updateUI2()
{
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    updateCoin();
    updateDiamond();
}


void BagView::updateMagic()
{
    auto scrollViewBG = getNode<ListView*>("ListView_bg");
    scrollViewBG->setScrollBarEnabled(false);
    scrollViewBG->removeAllChildren();
    scrollViewBG->jumpToTop();
    _items.clear();
    auto size = scrollViewBG->getContentSize();

    int totalCNT = getTotalCNT(_currentTab);
    
    
    int SPLIT = getSPLIT(_currentTab);

    startIDX = 0;
    this->unschedule("create_tab");
    auto func = [this, totalCNT, scrollViewBG,SPLIT](float t){
        auto panel = getNode<Layout*>("Panel_view_magic")->clone();
        auto panelSize = panel->getContentSize();
        auto node = BagNode::createBagNode((int)_currentTab, -1, CC_CALLBACK_1(BagView::dealButtonClick, this));
        node->setCascadeOpacityEnabled(true);
        
        node->setPosition(Vec2(panelSize.width/2,panelSize.height/2));
        
        panel->addChild(node);
        _items.push_back(node);
            
        scrollViewBG->pushBackCustomItem(panel);
        //refush(false);
        this->unschedule("create_Magic");
    };
    schedule(func, 0, "create_Magic");
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

Layout* BagView::getPanelView(Tab tab)
{
    Layout* panelView = 0;
    switch (_currentTab) {
        case Tab::POKER_BACK:
            panelView = getNode<Layout*>("Panel_view_bg");
            break;
        case Tab::POKER_FORE:
            panelView = getNode<Layout*>("Panel_view_zhengmian");
            break;
        case Tab::BACKGROUND:
            panelView = getNode<Layout*>("Panel_view_Changjing");
            break;
        case Tab::MUSIC:
            panelView = getNode<Layout*>("Panel_view_music");
            break;
        case Tab::PROPS:
            panelView = getNode<Layout*>("Panel_view_magic");
            break;
        case Tab::FISH:
            panelView = getNode<Layout*>("Panel_view_Changjing");
            break;
    }
    return panelView;
}

int BagView::getSPLIT(Tab tab)
{
    int SPLIT = 0;
    switch (_currentTab) {
        case Tab::POKER_BACK:
            SPLIT = SPLIT_BG;
            break;
        case Tab::POKER_FORE:
            SPLIT = SPLIT_ZHENGMIAN;
            break;
        case Tab::BACKGROUND:
            SPLIT = SPLIT_CHANGJING;
            break;
        case Tab::PROPS:
            SPLIT = 1;
            break;
        case Tab::FISH:
            SPLIT = SPLIT_FISH;
            break;
    }
    return SPLIT;
}

int BagView::getTotalCNT(Tab tab) {
    int totalCNT = 0;
    switch (_currentTab) {
        case Tab::POKER_BACK:
            totalCNT = CARD_BG_NUM;
            break;
        case Tab::POKER_FORE:
            totalCNT = CARD_FACE_NUM;
            break;
        case Tab::BACKGROUND:
            totalCNT = GAME_BG_NUM;
            break;
        case Tab::PROPS:
            totalCNT = 1;
            break;
        case Tab::FISH:
            totalCNT = FISH_NUM;
            break;
    }
    return totalCNT;
}

//void StoreView::refush(bool isRefushAll) {
//    int coinNum = DATA_M->getCoinNum();
//    getNode<TextBMFont*>("BitmapFontLabel_gold")->setString(StringUtils::toString(coinNum));
//    for (auto item:_items) {
//        item->refush(coinNum);
//    }
//}
void BagView::updateCoin(bool isDelay)
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

void BagView::updateDiamond(bool isDelay)
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

void BagView::updateBagItem1(int index)
{
    getNode("Node_6")->setVisible(false);
    FileNode_BagItem1->setVisible(true);
    getNode("Button_card_item1_get")->setTag(index);
    auto num = DATA_M->getCardFaceNum(index);
    getNode<Button*>("Button_card_item1_get")->setEnabled(num != 0);
    float perent = (float)num/52.f * 100;
    auto LoadingBar_card =  getNode<LoadingBar*>("LoadingBar_card");
    auto Text_cardNum = getNode<Text*>("Text_cardNum");
    LoadingBar_card->setPercent(perent);
    Text_cardNum->setString(StringUtils::format("%d/%d",num,52));
    
    UIUtils::playInnerAction(FileNode_BagItem1,"Start",false);
    auto parent = getNode<ListView*>("ListView_card");
    parent->setScrollBarEnabled(false);
    parent->removeAllChildren();
    parent->jumpToTop();
    auto Panel_card = getNode<Layout*>("Panel_card");
    auto size = Panel_card->getContentSize();
    int i = 0;
    int dx = 0;
    while (i < 52/5 + 1) {
        auto itemVec = Panel_card->clone();
        for(int j = 0, k = 0;j<5;++j,k+=2)
        {
            
            if(dx >= 52)break;
            
            auto card = BagCardFaceItem::createBagNode(2, index,dx, this);
            if (index == DATA_M->getCardPicType((int)_currentTab,dx))
            {
                card->setUse(true,true);
            }
            itemVec->addChild(card);
            card->setPosition(Vec2(size.width/10 + size.width/10*k,size.height*0.5));
            
            dx++;
        }
        parent->pushBackCustomItem(itemVec);
        i++;
    }
    //0-7
    //大于7的
    auto tag = DATA_M->getPropNew(2, index);
    if(tag != -1)
    {
        auto shoptype = tag /100000;
        shoptype = shoptype%10;
        auto index2 = tag / 1000;
        index = index2%100;
        auto randNum = tag%100000;
        randNum = randNum%1000;
        auto itemIdx = randNum/5;
        if(itemIdx <=7)
        {
            parent->jumpToItem(itemIdx, Vec2(0,1), Vec2(0,1));
        }
        else
        {
            parent->jumpToBottom();
        }
    }
    
}
void BagView::updateGameBgNew()
{
    bool is = false;
    for(int i = 0;i < GAME_BG_NUM;++i)
    {
        if(DATA_M->getPropNew(1,i) != -1)
        {
            is = true;
        }
    }
    getNode("img_new_bg_1")->setVisible(is);
}

void BagView::updateCardFaceNew()
{
    bool is = false;
    for(int i = 0;i < CARD_FACE_NUM;++i)
    {
        
        if(DATA_M->getPropNew(2,i) != -1)
        {
            is = true;
        }
    }
    getNode("img_new_bg_23")->setVisible(is);
}

void BagView::updateCardBgNew()
{
    bool is = false;
    for(int i = 0;i < CARD_BG_NUM;++i)
    {
        if(DATA_M->getPropNew(3,i) != -1)
        {
            is = true;
        }
    }
    getNode("img_new_bg_1")->setVisible(is);
}


void BagView::updateMusicNew()
{
    bool is = false;
    for(int i = 0;i<LobbyMusicTotalCNT;++i)
    {
        if(DATA_M->getPropNew(5,i) != -1)
        {
            is = true;
        }
    }
    getNode("img_new_bg_5")->setVisible(is);
}

void BagView::updateMagicNum()
{
    if(!_magicitems.empty())
    {
        auto node = _magicitems.at(0);
        node->updateMagicNum();
    }
}

Node* BagView::getTeachItem(const std::string &name, int idx)
{
    if (name == "bg") {
        return _gameBgitems.at(idx);
    }
    return nullptr;
}

Vec2 BagView::getGoldWorldPoi()
{
    auto goldNode = getNode("img_icon_top_gold");
    auto poi = goldNode->getPosition();
    poi = goldNode->getParent()->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}
Vec2 BagView::getdiamondWorldPoi()
{
    auto diamondNode = getNode("img_icon_top_diamond");
    auto poi = diamondNode->getPosition();
    poi = diamondNode->getParent()->convertToWorldSpace(poi);
    poi = _rootNode->convertToNodeSpace(poi);
    return poi;
}
