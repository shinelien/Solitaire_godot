//
//  BagCardBg.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/13.
//

#include <stdio.h>
#include "BagCardBg.h"
#include "AtlasManager.h"
#include "ShopManager.h"
#include "RewardManager.h"
#include "BagView.h"
#include "EventObserver.h"
#include "DataManager.h"
#include "SpriteManager.h"
#include "PlayerManager.h"
#include "FreeCoinLayer.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
#include "GoldShop.h"
BagCardBg::BagCardBg(BagView* bagView)
:BaseLayer("2020BagItem_cardBg.csb")
,_bagView(bagView)
{
    
}
BagCardBg::~BagCardBg()
{
    
}
    
BagCardBg * BagCardBg::createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback,BagView* bagView)
{
    auto bagNode = BagCardBg::createLayerN(bagView);
    bagNode->setShopNodeState(shopType, index, clickCallback);
    return bagNode;
}
void BagCardBg::setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback)
{
        
    this->shopType = shopType;
    this->index = index;
    this->isBuyed = DATA_M->getShopItemStatus(shopType, index);
    this->isUsing = false;
    
    _price = ShopManager::getInstance()->getPrice(shopType,index);
    auto lv = PlayerManager::getInstance()->getLevel();
    auto unlocklv = ShopManager::getInstance()->getUnlockLv(shopType, index);
    auto unlock = unlocklv > lv;
    auto newNum = DATA_M->getPropNew(shopType, index);
    
    isNew = newNum != -1;
    
    if (shopType == 3)
    {
        getNode("Button_buy")->setVisible(!isBuyed);
        getNode<Button*>("Button_buy")->setEnabled(!unlock);
        getNode("ui_Lock0_Changjing")->setVisible(unlock);
        img_card->setSpriteFrame(SPRITE_M->getCardBgSpriteFrame(index));
    }
    
    auto Text_ = getNode<TextBMFont*>("BitmapFontLabel_1");
    auto Text_buy = getNode<Text*>("Text_buy");
    if(unlock)
    {
        Text_->setVisible(false);
        Text_buy->setVisible(true);
        Text_buy->setString(StringUtils::format(Lang("100339").c_str(),unlocklv));
    }
    else
    {
        Text_->setVisible(true);
        Text_buy->setVisible(false);
        Text_->setString(StringUtils::format("%d",_price));
    }

    if(panel_item)
    {
        panel_item->setTag(shopType * 1000 + index);
        panel_item->addClickEventListener(clickCallback);
    }
    
    updateUI();
}

void BagCardBg::initUI()
{
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    img_card = getNode<Sprite*>("img_card_bg");
    
    panel_item = getNode<Layout*>("panel_item");
    
    panel_item->setVisible(true);
    
    
    Sprite_used_bg = getNode<ImageView*>("Sprite_used_bg");
    
    Image_new_bg = getNode<ImageView*>("img_new_bg");
    
    Sprite_used_bg->setVisible(false);
    
    Image_new_bg->setVisible(false);
    

    //img_card_poi = img_card->getPosition();
    
    auto Text_card_bg = getNode<Text*>("Text_card_bg");
    Text_card_bg->setString(Lang("yihuode"));
    UIUtils::textAdaptiveSize(Text_card_bg,240);
}
void BagCardBg::initData()
{
    BaseLayer::initData();
    addEvent("event_game_update_cardBg", [this](EventCustom *e){
        auto node = (BagCardBg*)e->getUserData();
        if(node == this)
        {
            DATA_M->setPropNew(shopType,index,-1);
            _bagView->updateCardBgNew();
            setNew(false);
        }
        setUse(node == this);
    });
}

void BagCardBg::selected(bool flag)
{
    if (isUsing != flag) {
        isUsing = flag;
        if (isUsing)
        {
            
            DATA_M->setCardPicType(shopType, index);
        }
        updateUI();
    }
}


void BagCardBg::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
    if(btnName == "Button_card_bg")
    {//牌背
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_update_cardBg",(void*)this);
    }
    else if(btnName == "Button_buy")
    {
        auto coinNum = DATA_M->getCoinNum();
        if(coinNum >= _price)
        {
            DATA_M->setCoinNum(-_price,false, 204);
            //更新有金币显示
            SCENE_M->getLobby()->updateCoin();
            SCENE_M->getGameView()->updateCoin();
            _bagView->updateCoin();
            isBuyed = true;
            DATA_M->unLockShopItemStatus(shopType,index);
            updateUI();
        }
        else
        {
            SCENE_M->showTips(Lang("100096"),false,[this](){
                
            });
            if(!SCENE_M->getFreeCoinLayer())
            {//弹窗
//                SCENE_M->addDialog(FreeCoinLayer::createLayerN(FreeCoinLayer::Type::Gold,_bagView));
//                _bagView->getNode("Panel_top_0")->setVisible(false);
                SCENE_M->addDialog(GoldShop::createLayerN(GoldShop::GoldShopType::None,_bagView));
                _bagView->setVisible(false);
            }
        }
    }
}

void BagCardBg::updateUI()
{
    //使用时的对号图片

    if(panel_item)
    {
        auto lv = PlayerManager::getInstance()->getLevel();
        auto unlocklv = ShopManager::getInstance()->getUnlockLv(shopType, index);
        auto unlock = unlocklv > lv;
        Sprite_used_bg->setVisible(isUsing);
        //牌背
        getNode("Button_card_bg")->setVisible(!unlock&&!isUsing&&isBuyed);
        //只有使用中才亮
        getNode<Button*>("Button_card_bgA")->setEnabled(!unlock&&isBuyed&&isUsing);
        getNode("Button_buy")->setVisible(!isBuyed);
        Image_new_bg->setVisible(isNew);
        //全部显示是224
        //隐藏按钮文本156
        //隐藏按钮文本+锁头 156
        //隐藏按钮文本+卡背 86
        
        //img_card->setVisible(false);
    }
    
}

bool BagCardBg::setUse(bool isUse,bool isInit)
{
    this->isUsing = isUse;
    updateUI();
    if (isUse)
    {
        auto id = DATA_M->getCardPicType(shopType);
        if (!isInit)
        {
            DATA_M->setCardPicType(shopType, index);
            SPRITE_M->changeCardSkin(shopType);
        }
        return true;
    }
    else
    {
        
    }
    return false;
}

void BagCardBg::playLightAction()
{
//    img_light_1->setVisible(true);
//    img_light_2->setVisible(true);
//
//    img_light_1->setRotation(CCRANDOM_0_1() * 360);
//    img_light_2->setRotation(CCRANDOM_0_1() * 360);
//
//    img_light_1->runAction(RepeatForever::create(Sequence::create(Spawn::create(RotateBy::create(2, -72), FadeIn::create(2), NULL), Spawn::create(RotateBy::create(2, -72), FadeOut::create(2), NULL), NULL)));
//    img_light_2->runAction(RepeatForever::create(Sequence::create(Spawn::create(RotateBy::create(2, 72), FadeOut::create(2), NULL), Spawn::create(RotateBy::create(2, 72), FadeIn::create(2), NULL), NULL)));
    img_card->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1, Point(0, 10)), MoveBy::create(1, Point(0, -10)), MoveBy::create(1, Point(0, 10)), MoveBy::create(1, Point(0, -10)), NULL)));
}

void BagCardBg::setNew(bool is)
{
    isNew = is;
}
