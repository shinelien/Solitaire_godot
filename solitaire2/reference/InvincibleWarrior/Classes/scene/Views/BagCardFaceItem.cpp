//
//  BagCardFaceItem.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/22.
//

#include <stdio.h>
#include "BagCardFaceItem.h"
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
BagCardFaceItem::BagCardFaceItem(BagView* bagView)
:BaseLayer("2021BagItem_cardFace.csb")
,_bagView(bagView)
{
    
}
BagCardFaceItem::~BagCardFaceItem()
{
    
}
    
BagCardFaceItem * BagCardFaceItem::createBagNode(int shopType, int index,int id, BagView* bagView)
{
    auto bagNode = BagCardFaceItem::createLayerN(bagView);
    bagNode->setShopNodeState(shopType, index,id);
    return bagNode;
}
void BagCardFaceItem::setShopNodeState(int shopType, int index,int id)
{
        
    this->shopType = shopType;
    this->index = index;
    this->id = id;
    this->isBuyed = DATA_M->getCardFaceStatus(shopType, index,id);

    //card->setOpacity(isBuy?255:50);
    
    this->isUsing = false;
    auto num = id%13+1;
    auto col = id/13;
    
    auto _sprite1 = getNode<Sprite*>("Sprite_face");
    auto _sprite2 = getNode<Sprite*>("Sprite_num");
    auto _sprite3 = getNode<Sprite*>("Sprite_color");
    _sprite1->setSpriteFrame(AtlasManager::getInstance()->getSF(2, num, col, index));
    _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5, num, col, index));
    _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6, num, col, index));
    _sprite2->setColor(UIUtils::getCardColor(col));
    auto size2 = _sprite2->getContentSize();
    _sprite2->setPositionX(size2.width*0.5f);
    _sprite1->setOpacity(isBuyed?255:50);
    updateUI();
}

void BagCardFaceItem::initUI()
{
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    
    panel_item = getNode<Layout*>("Panel_1");
    panel_item->setVisible(true);
    
    
    Sprite_used_bg = getNode<ImageView*>("Sprite_used_bg");
    Sprite_used_bg->setVisible(false);
    auto Text_card_face = getNode<Text*>("Text_card_face");
    Text_card_face->setString(Lang("yihuode"));
    UIUtils::textAdaptiveSize(Text_card_face,240);

}
void BagCardFaceItem::initData()
{
    BaseLayer::initData();
    addEvent("event_game_update_cardFaceItem", [this](EventCustom *e){
        auto node = (BagCardFaceItem*)e->getUserData();
        if(node == this)
        {
            DATA_M->setPropNew(shopType,index,-1);
            _bagView->updateCardBgNew();
            setNew(false);
        }
        setUse(node == this);
    });
}

void BagCardFaceItem::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
    if(btnName == "Button_card_face")
    {//牌背
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_update_cardFaceItem",(void*)this);
    }
    
}

void BagCardFaceItem::updateUI()
{
    //使用时的对号图片

    if(panel_item)
    {
        getNode("Button_card_face")->setVisible(!isUsing&&isBuyed);
        Sprite_used_bg->setVisible(isUsing);
    }
    
}

bool BagCardFaceItem::setUse(bool isUse,bool isInit)
{
    this->isUsing = isUse;
    updateUI();
    if (isUse)
    {
        if (!isInit)
        {
            DATA_M->setCardPicType(shopType, index,id);
            SPRITE_M->changeCardSkin(shopType);
        }
        
        return true;
    }
    else
    {
        
    }
    return false;
}

void BagCardFaceItem::setNew(bool is)
{
    isNew = is;
}
