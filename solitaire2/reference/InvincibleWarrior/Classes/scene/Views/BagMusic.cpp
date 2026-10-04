//
//  BagMusic.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/13.
//

#include <stdio.h>
#include "BagMusic.h"
#include "AtlasManager.h"
#include "ShopManager.h"
#include "RewardManager.h"
#include "TaskManager.h"
#include "BagView.h"
#include "DataManager.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "PlayerManager.h"
#include "FreeCoinLayer.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"

BagMusic::BagMusic(BagView* bagView)
:BaseLayer("2020BagItem_music.csb")
,_bagView(bagView)
{
    
}
BagMusic::~BagMusic()
{
    
}
    
BagMusic * BagMusic::createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback,BagView* bagView)
{
    auto bagNode = BagMusic::createLayerN(bagView);
    bagNode->setShopNodeState(shopType, index, clickCallback);
    return bagNode;
}
void BagMusic::setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback)
{
    this->shopType = shopType;
    this->index = index;
    auto isBuy = DATA_M->getShopItemStatus(shopType, index);
    _price = ShopManager::getInstance()->getPrice(shopType,index);
    auto lv = PlayerManager::getInstance()->getLevel();
    auto unlocklv = ShopManager::getInstance()->getUnlockLv(shopType, index);
    auto unlock = unlocklv > lv;
    this->isBuyed = !unlock;
    if(isBuyed&&!isBuy)
    {
        DATA_M->unLockShopItemStatus(shopType,index);
    }
    this->isUsing = index == DATA_M->getCardPicType(shopType);//GETINTEGER("default_bgm", -1);
    if(isUsing)
    {
        aniManager->play("Start", true);
    }
    
    auto newNum = DATA_M->getPropNew(shopType, index);
    isNew = newNum != -1;
    if(shopType == 5)
    {
        getNode("Button_buy")->setVisible(!isBuyed);
        getNode<Button*>("Button_buy")->setEnabled(!unlock);
        getNode("Button_music")->setVisible(isBuyed);
        getNode("ui_Lock0_music")->setVisible(unlock);
        panel_Music->setVisible(true);
    }
    
    getNode<Text*>("Text_music")->setString(StringUtils::format("Music%02d",index+1));
    
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

    
    updateUI();
}

void BagMusic::initUI()
{
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    
    panel_Music = getNode<Layout*>("panel_Music");
    
    panel_Music->setVisible(false);
    
    
    FileNode_music = getNode("FileNode_music");
    aniManager = dynamic_cast<cocostudio::timeline::ActionTimeline *>(FileNode_music->getActionByTag(FileNode_music->getTag()));
    Sprite_used_music = getNode<ImageView*>("Sprite_used_music");
    Image_new_music = getNode<ImageView*>("Image_new_music");
    Sprite_used_music->setVisible(false);
    Image_new_music->setVisible(false);

    //img_card_poi = img_card->getPosition();
    
}
void BagMusic::initData()
{
    BaseLayer::initData();

    addEvent("shop_item_music_select", [this](EventCustom* event){
        auto obj = event->getUserData();
        if(obj == this)
        {
            DATA_M->setPropNew(shopType,index,-1);
            _bagView->updateMusicNew();
            setNew(false);
        }
        
        selected(obj == this);
    });
}

void BagMusic::setMusicUse(bool flag)
{
    if (isUsing != flag) {
        isUsing = flag;
        updateUI();
    }
}

void BagMusic::selected(bool flag)
{
    if (isUsing != flag||1) {
        if(isUsing)
        {
            isUsing = false;
            
            if(index == DATA_M->getCardPicType(shopType))
            {
                DATA_M->setCardPicType(shopType, -1);
                //停止播放
                SOUND_M->stopGameBgMusic();
            }
            
        }
        else
        {
            isUsing = flag;
        }
        if (isUsing)
        {
            
            //累计使用音乐任务数 新手
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::MUSIC);
            //使用音乐的话 解除关闭音乐
            DATA_M->setIsMusic(true);
            aniManager->play("Start", true);
            SOUND_M->playGameBgMusic(StringUtils::format(BGM.c_str(), index));
            DATA_M->setCardPicType(shopType, index);
        }
        else
        {
            aniManager->gotoFrameAndPause(0);
        }
        updateUI();
    }
    else
    {
        
    }
    updateUI();
}


void BagMusic::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
    if (btnName == "Button_music"||btnName == "Button_music_on")
    {
        getEventDispatcher()->dispatchCustomEvent("shop_item_music_select", (void*)this);
    }
    else if(btnName == "Button_buy")
    {
        auto coinNum = DATA_M->getCoinNum();
        if(coinNum >= _price)
        {
            DATA_M->setCoinNum(-_price,false, 206);
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
                SCENE_M->addDialog(FreeCoinLayer::createLayerN(FreeCoinLayer::Type::Gold,_bagView));
                _bagView->getNode("Panel_top_0")->setVisible(false);
            }
        }
    }
}

void BagMusic::updateUI()
{
    //使用时的对号图片

    if(isUsing)
    {
        CCLOG("true");
    }
   
    if(panel_Music)
    {
        auto lv = PlayerManager::getInstance()->getLevel();
        auto unlocklv = ShopManager::getInstance()->getUnlockLv(shopType, index);
        auto unlock = unlocklv > lv;
        getNode("Button_music")->setVisible(isBuyed);
        
        auto Text_use = getNode<Text*>("Text_use");
        Text_use->setString(isUsing?Lang("100336"):Lang("100335"));
        UIUtils::textAdaptiveSize(Text_use,250);
        
        getNode<Button*>("Button_music_on")->setEnabled(isBuyed);
        Sprite_used_music->setVisible(isUsing);
        getNode("Button_buy")->setVisible(!isBuyed);
        
        Image_new_music->setVisible(isNew);
    }
}

bool BagMusic::setUse(bool isUse,bool isInit)
{
    //牌面特别判断 就算没有购买也可以用
    if (!isBuyed || this->isUsing == isUse)
    {
        
        this->isUsing = isUse;
        updateUI();
        if (isUse)
        {
            if (!isInit)
            {
                DATA_M->setCardPicType(shopType, index);
                SPRITE_M->changeCardSkin(shopType);
            }
            return true;
        }
        
        return false;
    }
    this->isUsing = isUse;
    updateUI();
    if (isUse)
    {
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

void BagMusic::playLightAction()
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

void BagMusic::setNew(bool is)
{
    isNew = is;
}
