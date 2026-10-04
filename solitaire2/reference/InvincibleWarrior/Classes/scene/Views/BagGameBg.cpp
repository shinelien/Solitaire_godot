//
//  BagGameBg.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/13.
//

#include <stdio.h>
#include "BagGameBg.h"
#include "AtlasManager.h"
#include "ShopManager.h"
#include "RewardManager.h"
#include "BagView.h"
#include "TeachManager.h"
#include "MainLobby.h"
#include "DataManager.h"
#include "SpriteManager.h"
#include "GameBackground.h"
#include "FreeCoinLayer.h"
#include "FishManager.h"
#include "GameViewHD.hpp"
#include "PlayerManager.h"
#include "FishShop.h"
#include "SellFish.h"
#include "FashTankShop.h"
#include "FishGuideManager.h"
#include "GoldShop.h"
#include "FishGuideView.h"

BagGameBg::BagGameBg(FishShop* fishShop,FashTankShop* fashTankShop)
:BaseLayer("2020BagItem_gameBg.csb")
,_fishShop(fishShop)
,_fashTankShop(fashTankShop)
{
    
}
BagGameBg::~BagGameBg()
{
    
}
    
BagGameBg * BagGameBg::createBagNode(int shopType, int index,int type,int fashTankIdx, std::function<void(Ref *)> clickCallback,FishShop* fishShop,FashTankShop* fashTankShop)
{
    auto bagNode = BagGameBg::createLayerN(fishShop,fashTankShop);
    bagNode->setShopNodeState(shopType, index,type,fashTankIdx, clickCallback);
    return bagNode;
}
void BagGameBg::setShopNodeState(int shopType, int index,int type,int fashTankIdx, std::function<void(Ref *)> clickCallback)
{
    isTouch = true;
    _fashTankIdx = fashTankIdx;
    this->shopType = shopType;
    this->index = index;
    _type = type;
    this->isBuyed = DATA_M->getShopItemStatus(shopType, index);
    this->isUsing = false;
    auto newType = _type;
    if(_fishShop)
    {
        newType = newShopIdx[index];
    }
    _price = FISH_M->getPrice(newType);
    //来个等级判断 大于0
    auto lv = PlayerManager::getInstance()->getLevel();
    if(lv > 0&&index == 0&&!GUIDE_M->isEnd(FishGuideManager::GuideType::FishShopOne)&&GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFishShop))
    {//正在进行买鱼引导
        _price = 0;
        isTouch = false;
//        auto label = getNode<TextBMFont*>("BitmapFontLabel_3");
//        label->setString(StringUtils::format("%d",_price));
    }
    _sellPrice = _price/3;
    
    auto unlocklv = FISH_M->getUnlockLv(newType);
    auto unlock = unlocklv > lv&&_fishShop;
    /*
     0      100unlock
     1      200
     2      400
     3      600
     4      800
     5      1000
     6      2000
     7      4000
     8      6000
     9      8000
     10     10000
     11     20000
     12     30000
     13     40000
     14     50000
     
     */
    
    isNew = DATA_M->getFishNew(index);
    
    
    if (shopType == 8)
    {
        panel_Changjing->setVisible(true);
        getNode<Button*>("Button_gameBgA")->setEnabled(!unlock);
        getNode<Button*>("Button_gameBg")->setVisible(!unlock);
        getNode("ui_Lock0_Changjing")->setVisible(unlock);
        getNode("BitmapFontLabel_npc_num")->setVisible(!unlock);
        auto node_fish = getNode("Node_fish");
        
        auto btnSize = getNode<Button*>("Button_gameBgA")->getBoundingBox().size;
        
        float num = FishManager::getInstance()->getNpcNum(newType);
        auto str = UIUtils::getFloatStr(num,1);
        getNode<TextBMFont*>("BitmapFontLabel_npc_num")->setString(str);
        
        auto skeletonNode = FISH_M->getFishSpine(type);
        
        node_fish->addChild(skeletonNode);
        string aniName = "Run";
        
        skeletonNode->setAnimation(0, aniName, true);
        auto spineSize = skeletonNode->getBoundingBox().size;
        
        if(type == 14)
        {
            skeletonNode->setPositionX(466.55f * 0.1f);
            skeletonNode->setScale(0.85f);
        }
        else if(type == 20)
        {
            skeletonNode->setScale(0.9f);
        }
        
        if(unlock)
        {
            skeletonNode->setColor(FishUnlockColor);
        }
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

    auto Text_gameBg = getNode<Text*>("Text_gameBg");
    auto label = getNode<TextBMFont*>("BitmapFontLabel_3");
    getNode("Button_zengjia")->setVisible(false);
    getNode("Button_jianshao")->setVisible(false);
    Text_gameBg->setString(StringUtils::format(Lang("100339").c_str(),unlocklv));
    label->setString(StringUtils::format("%d",_price));
    getNode<Text*>("Text_sell")->setString(Lang("100345"));
//    Text_gameBg->setString(Lang("yihuode"));
    UIUtils::textAdaptiveSize(Text_gameBg,310);
    
    updateUI();
}

void BagGameBg::initUI()
{
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    _price = 0;
    
    
    
    panel_Changjing = getNode<Layout*>("panel_Changjing");
    
    panel_Changjing->setVisible(false);
    
    
    
    //Sprite_used_gameBg = getNode<ImageView*>("Image_used_gameBg");
    Image_new_gameBg = getNode<ImageView*>("img_new_gameBg");
    //Sprite_used_gameBg->setVisible(false);
    Image_new_gameBg->setVisible(false);

    //img_card_poi = img_card->getPosition();
    
}
void BagGameBg::initData()
{
    BaseLayer::initData();
    addEvent("event_game_update_gameBg", [this](EventCustom *e){
        auto node = (BagGameBg*)e->getUserData();
        setUse(node == this);
    });
    

}


void BagGameBg::selected(bool flag)
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


void BagGameBg::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn || !isTouch)return;
    
    auto btnName = btn->getName();
    
    if(btnName == "Button_gameBg")
    {//场景
        auto coin = DATA_M->getCoinNum();
        auto fishNum = DATA_M->getFishNum();
        if(fishNum >= FISH_MAX_NUM)
        {
            //SCENE_M->showTips(Lang("100364"));
            FishGuideManager::getInstance()->fishMaxGuide();
        }
        else if(coin >= _price)
        {
            auto lobby = SCENE_M->getLobby();
            if(index == 0&&GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::FishShopOne)&&GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFishShop))
            {//正在进行买鱼引导
                GUIDE_M->nextGuide(FishGuideManager::GuideType::GetFishOne);
            }
            
            DATA_M->setCoinNum(-_price,false, 205);
            //更新有金币显示
            lobby->updateCoin();
            SCENE_M->getGameView()->updateCoin();
            auto fashTank = SCENE_M->getGameBackground();
            fashTank->addFish(_type);
            
            SCENE_M->removeLayer(_fishShop);
        }
        else
        {
            SCENE_M->showTips(Lang("100096"),false,[this](){
                
            });
            if(!SCENE_M->getFreeCoinLayer())
            {//弹窗
                SCENE_M->addDialog(GoldShop::createLayerN(GoldShop::GoldShopType::None,_fishShop));
                //_fishShop->getNode("Panel_top_0")->setVisible(false);
                _fishShop->setVisible(false);
            }
        }
    }
    else if(btnName == "Button_zengjia")
    {
        auto Text_gameBg = getNode<Text*>("Text_gameBg");
        _price+=2;
        
        Text_gameBg->setString(StringUtils::format("%d",_price));
    }
    else if(btnName == "Button_jianshao")
    {
        auto Text_gameBg = getNode<Text*>("Text_gameBg");
        _price-=2;
        if(_price <= 0)_price = 0;
        Text_gameBg->setString(StringUtils::format("%d",_price));
    }
    else if(btnName == "Button_gameSell")
    {//出售 //弹窗
        if(_fishNum > 0)
        {
            SCENE_M->addDialog(SellFish::createLayerN(this,_fashTankIdx,_type,index,_sellPrice,[this](){
                SCENE_M->getLobby()->updateFishNum();
            }));
        }
    }
}

void BagGameBg::updateUI()
{
    //使用时的对号图片

    
    if(panel_Changjing)
    {
        Image_new_gameBg->setVisible(isNew);
        auto newType = _type;
        if(_fishShop)
        {
            newType = newShopIdx[index];
        }
        auto lv = PlayerManager::getInstance()->getLevel();
        auto unlocklv = FISH_M->getUnlockLv(newType);
        auto unlock = unlocklv > lv&&_fishShop;
        if(_fishShop)
        {//商店
            getNode<Button*>("Button_gameBg")->setVisible(!unlock);
            getNode("Button_gameSell")->setVisible(false);
        }
        else
        {//管理鱼
            getNode("Button_gameBg")->setVisible(false);
            auto Button_gameSell = getNode<Button*>("Button_gameSell");
            Button_gameSell->setVisible(!unlock);
            
            auto isDaily = GETBOOL(StringUtils::format("fish_isDaily_%d_%d", _fashTankIdx,_type).c_str(),false);
            getNode<Text*>("Text_rare")->setVisible(isDaily);
            getNode<Text*>("Text_rare")->setString(Lang("100373"));
            getNode<TextBMFont*>("BitmapFontLabel_sell")->setString(StringUtils::toString(_sellPrice));
            
            
            _fishNum = DATA_M->getFishTypeNum(_type,_fashTankIdx);
            Button_gameSell->setEnabled(_fishNum != 0);
            auto Text_gameBg = getNode<Text*>("Text_gameBg");
            Text_gameBg->setVisible(false);
            //Text_gameBg->setString(StringUtils::format(Lang("100343").c_str(),_fishNum));
        }
    }
}

bool BagGameBg::setUse(bool isUse,bool isInit)
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

void BagGameBg::playLightAction()
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

void BagGameBg::setNew(bool is)
{
    isNew = is;
}

void BagGameBg::updateGuide()
{
    
}
