
#include "ShopViewHD.h"
#include "ShopNode.h"
#include "CoinLayer.h"
#include "SpriteManager.h"
#include "GameViewHD.hpp"

const string TAB_PRFIX = "Button_tab";
const Size ITEM_SIZE(160,300);

void ShopViewHD::initUI() {
    BaseLayer::initUI();
    doLayout();
    getNode("btn_shop_close")->setVisible(!_isLobby);
    getNode("panel_shop")->setCascadeOpacityEnabled(true);
    _actionManager->play("Start", false);
}

void ShopViewHD::onEnter()
{
    BaseLayer::onEnter();
    for (int i=1;i<=3;i++) {
        _tabBtnVec.push_back(getNode<Button*>(TAB_PRFIX + StringUtils::toString(i)));
                getNode<Text*>(StringUtils::format("text_title%d", i))->setString(Lang(toString(100122+i)));
    }
    getNode<Text*>("text_title")->setString(Lang("100038"));
    setTab(Tab::POKER_BACK);
//    SCENE_M->getGameView()->showNode("Panel_top", false);
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("OpenShop")},
    });
}

void ShopViewHD::onExit()
{
    BaseLayer::onExit();
//    SCENE_M->getGameView()->showNode("Panel_top", true);
}

void ShopViewHD::initData() {
    BaseLayer::initData();
    setName("ShopViewHD");
}

void ShopViewHD::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
    if ("btn_shop_close" == btnName) {
        SOUND_M->playBtnClickAudio();
        //关闭窗口开始累计计时
        SCENE_M->getGameView()->setIsOpenTipsTime(true);
        this->removeFromParent();
    }
    else if (btnName.find(TAB_PRFIX) != string::npos) {
        SOUND_M->playBtnClickAudio();
        setTab((ShopViewHD::Tab)btn->getTag());
    }
    else if ("btn_add" == btnName || "img_btn_coin" == btnName)
    {
        SOUND_M->playBtnClickAudio();
        SCENE_M->addDialog(CoinLayer::createLayer());
    }
    else if (btnName == "select") {
        SOUND_M->playBtnClickAudio();
        int shopType = (int)(btn->getTag() / 1000);
        int selectIndex = btn->getTag() % 1000;
        bool isUse = _items[selectIndex]->setUse(true);
        if (isUse) {
            _items[nowUseIndex[shopType - 1]]->setUse(false);
            nowUseIndex[shopType - 1] = selectIndex;
        }
        if (shopType == 3) {
            SPRITE_M->setShufflingFirst(SpriteManager::ShuffingType::Shuffing);
        }
        UIUtils::FIRAnalyticsUserProperty(StringUtils::format("shop_gamebg_%d", shopType), StringUtils::format("shop_index_%d", selectIndex));
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("ShopSelect")},
            {"value", Value(StringUtils::format("%d_%d", _currentTab, selectIndex))}
        });
    }
    else if (btnName == "buy") {
        SOUND_M->playBtnClickAudio();
//        int shopType = (int) (btn->getTag() / 1000);
        int selectIndex = btn->getTag() % 1000;

        bool isBuy = _items[selectIndex]->buy();
        if (isBuy)
        {
            //购买成功--刷新所有的
            refush(true);
        }
        else {
            SCENE_M->showTips(Lang("100096"));
        }
        ValueMap valueMap;
        valueMap["buy"] = Value(selectIndex);
        UIUtils::FIRAnalyticsEvent("shop_buy", valueMap);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("ShopBuy")},
            {"value", Value(StringUtils::format("%d_%d", _currentTab, selectIndex))}
        });
    }
    else if (btnName == "panel_shop"&&!_isLobby) {
        //关闭窗口开始累计计时
        SCENE_M->getGameView()->setIsOpenTipsTime(true);
        this->removeFromParent();
    }
}

void ShopViewHD::showSelect(int shopType, int shopIndex, const string name) {
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
        bool isBuy = _items[shopIndex]->buy();
        if (isBuy)
        {
            //购买成功--刷新所有的
            refush(true);
        }
        else {
            SCENE_M->showTips(Lang("100096"));
        }
        ValueMap valueMap;
        valueMap["buy"] = Value(shopIndex);
        UIUtils::FIRAnalyticsEvent("shop_buy", valueMap);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("ShopBuy")},
            {"value", Value(StringUtils::format("%d_%d", shopType, shopIndex))}
        });
    }
}

ShopViewHD::ShopViewHD(bool isLobby)
:BaseLayer("NewShop.csb")
,_currentTab(ShopViewHD::Tab::None)
,_isLobby(isLobby)
{
}

ShopViewHD::~ShopViewHD() {

}

void ShopViewHD::setTab(ShopViewHD::Tab tab) {
    if (_currentTab != tab) {
        auto panel_confirm = getNode("Panel_confirm");
        if (panel_confirm)
            panel_confirm->setVisible(false);
        _currentTab = tab;
        for (auto btn:_tabBtnVec) {
            btn->setEnabled((int)tab != btn->getTag());
        }
        updateUI();
    }
}

ShopViewHD::Tab ShopViewHD::getTab() {
    return _currentTab;
}

const int SPLIT = 4;
static int startIDX = 0;
void ShopViewHD::updateUI() {
    auto scrollViewBG = getNode<ListView*>("ListView_bg");
    scrollViewBG->setScrollBarEnabled(false);
    scrollViewBG->removeAllChildren();
    scrollViewBG->jumpToTop();
    _items.clear();
    auto size = scrollViewBG->getContentSize();

    int totalCNT = getTotalCNT(_currentTab);

    startIDX = 0;
    this->unschedule("create_tab");
    auto func = [this, totalCNT, scrollViewBG](float t){
        int i = 0;
        while (startIDX < ceil(totalCNT*1./SPLIT))
        {
            auto panel = getNode<Layout*>("Panel_view")->clone();
            auto panelSize = panel->getContentSize();
            for (int j=0;j<SPLIT;j++)
            {
                auto idx = startIDX*SPLIT+j;
                if (idx>=totalCNT) break;
                
                auto node = ShopNode::createShopNode((int)_currentTab, idx, CC_CALLBACK_1(ShopViewHD::dealButtonClick, this));
                node->setCascadeOpacityEnabled(true);
                auto splitSize = panelSize/SPLIT;
                node->setPosition(Vec2(j*splitSize.width+splitSize.width/2,panelSize.height/2));
                if (idx == DATA_M->getCardPicType((int)_currentTab))
                {
                    node->setUse(true,true);
                    nowUseIndex[(int)_currentTab-1] = DATA_M->getCardPicType((int)_currentTab);
                }
                panel->addChild(node);
                _items.push_back(node);
            }
            scrollViewBG->pushBackCustomItem(panel);
            ++startIDX;
            if (++i>=3) {
                refush(false);
                return;
            }
        }
        refush(false);
        this->unschedule("create_tab");
    };
    schedule(func, 0, "create_tab");
    func(0);
}

int ShopViewHD::getTotalCNT(Tab tab) {
    int totalCNT = 0;
    switch (_currentTab) {
        case Tab::POKER_BACK:
            totalCNT = GAME_BG_NUM;
            break;
        case Tab::POKER_FORE:
            totalCNT = CARD_FACE_NUM;
            break;
        case Tab::BACKGROUND:
            totalCNT = CARD_BG_NUM;
            break;
    }
    return totalCNT;
}

void ShopViewHD::refush(bool isRefushAll) {
    int coinNum = DATA_M->getCoinNum();
    getNode<TextBMFont*>("BitmapFontLabel_coin")->setString(StringUtils::toString(coinNum));
    for (auto item:_items) {
        item->refush(coinNum);
    }
}
