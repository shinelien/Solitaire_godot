//
//  BagMagic.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/13.
//

#include <stdio.h>
#include "BagMagic.h"
#include "AtlasManager.h"
#include "ShopManager.h"
#include "RewardManager.h"
#include "DataManager.h"

BagMagic::BagMagic()
:BaseLayer("2020BagItem_magic.csb")
{
    
}
BagMagic::~BagMagic()
{
    
}
    
BagMagic * BagMagic::createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback)
{
    auto bagNode = BagMagic::createLayerN();
    bagNode->setShopNodeState(shopType, index, clickCallback);
    return bagNode;
}
void BagMagic::setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback)
{
    this->shopType = shopType;
    this->index = index;
    this->isBuyed = DATA_M->getShopItemStatus(shopType, index);
    this->isUsing = false;
    
    
    if(shopType == 6)
    {
        panel_Magic->setVisible(true);
        
        auto num = REWARD_M->getCNT(RewardManager::RewardType::Magic);
        getNode<Text*>("Text_MagicNum")->setString(StringUtils::format("x%d",num));
        getNode<Button*>("Button_magicA")->addClickEventListener(clickCallback);
        getNode<Button*>("Button_magic")->addClickEventListener(clickCallback);
    }
    if (isBuyed)
    {
        //panel_item->setName("select");
//        text_item->setString(UIUtils::getStringByName("yihuode"));
//        text_item->setVisible(true);
    }
//    else
//    {
//        panel_item->setName("buy");
//        img_coin->setVisible(true);
//        atlasLabel_num->setString(toString(price));
//    }

   
    
    updateUI();
}

void BagMagic::initUI()
{
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    
    panel_Magic = getNode<Layout*>("panel_Magic");
   
    panel_Magic->setVisible(false);
    
    getNode<Text*>("Text_19")->setString(Lang("100186"));
}
void BagMagic::initData()
{
    BaseLayer::initData();
//    addEvent("event_game_update_item", [this](EventCustom *e){
//        auto node = (BagNode*)e->getUserData();
//        setUse(node == this);
//    });
    
    
}

void BagMagic::selected(bool flag)
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


void BagMagic::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
    if(btnName == "Button_gameBg"||btnName == "Button_gameBgA")
    {//场景
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_update_item",(void*)this);
    }
    else if(btnName == "Button_card_bgA"||btnName == "Button_card_bg")
    {//牌背
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_update_item",(void*)this);
    }
}

void BagMagic::updateUI()
{
    //使用时的对号图片

    
}

void BagMagic::updateMagicNum()
{
    auto num = REWARD_M->getCNT(RewardManager::RewardType::Magic);
    getNode<Text*>("Text_MagicNum")->setString(StringUtils::format("x%d",num));
}
