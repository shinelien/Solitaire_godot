//
//  BagNode.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/29.
//

#include <stdio.h>
#include "BagNode.h"
#include "AtlasManager.h"
#include "ShopManager.h"
#include "RewardManager.h"
#include "DataManager.h"
#include "SoundManager.h"
#include "SpriteManager.h"

BagNode::BagNode()
:BaseLayer("2020BagItem.csb")
{
    
}
BagNode::~BagNode()
{
    
}
    
BagNode * BagNode::createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback)
{
    auto bagNode = BagNode::createLayerN();
    bagNode->setShopNodeState(shopType, index, clickCallback);
    return bagNode;
}
void BagNode::setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback)
{
    this->shopType = shopType;
    this->index = index;
    this->isBuyed = DATA_M->getShopItemStatus(shopType, index);
    this->isUsing = false;
    
    if (shopType == 1)
    {
        panel_Changjing->setVisible(true);
        panel_item->removeFromParent();
        panel_item_0->removeFromParent();
        panel_zhengmian->removeFromParent();
        panel_Music->removeFromParent();
        panel_Magic->removeFromParent();
        panel_item = nullptr;
        panel_item_0 = nullptr;
        panel_zhengmian = nullptr;
        panel_Music = nullptr;
        panel_Magic = nullptr;
        getNode("Button_gameBg")->setVisible(!isUsing);
        getNode("ui_Lock0_Changjing")->setVisible(!isBuyed);
        //����
        //img_card->loadTexture("card_0_10_1.png", TextureResType::PLIST);
//        img_card->loadTexture(CCString::createWithFormat("game_bg_%d.png", index)->getCString(), TextureResType::PLIST);
        if(index > 13)
        {//动态
//            for(int i = 2;i<12;++i)
//            {
//                if(i == index -12)
//                {
//                    continue;
//                }
//                auto node = getNode(StringUtils::format("FileNode_Changjing%d",i));
//                node->removeFromParent();
//            }
//            auto iconNode = getNode(StringUtils::format("FileNode_Changjing%d",index-12));
//            iconNode->setVisible(true);
//            UIUtils::playInnerAction(iconNode,"loop",true);
//            ShopManager::getInstance()->changeGameBG(iconNode,index-12);
//            img_card->setSpriteFrame(AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", index-12),"car_new_0_1.atlas"));
//            img_card2->setSpriteFrame(AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", index-12),"car_new_0_1.atlas"));
            auto Sprite_Changjing = getNode<Sprite*>("Sprite_Changjing");
            Sprite_Changjing->setVisible(true);
            Sprite_Changjing->setSpriteFrame(AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", index-12),"car_new_0_1.atlas"));
        }
        else
        {
//            for(int i = 2;i<12;++i)
//            {
//                auto node = getNode(StringUtils::format("FileNode_Changjing%d",i));
//                node->removeFromParent();
//            }
            auto Sprite_Changjing = getNode<Sprite*>("Sprite_Changjing");
            Sprite_Changjing->setVisible(true);
            Sprite_Changjing->setSpriteFrame(AtlasManager::getInstance()->getSF(1, 0, 0, index));
        }
    }
    else if (shopType == 2)
    {
        panel_zhengmian->setVisible(true);
        panel_item->removeFromParent();
        panel_item_0->removeFromParent();
        panel_Changjing->removeFromParent();
        panel_Music->removeFromParent();
        panel_Magic->removeFromParent();
        panel_Changjing = nullptr;
        panel_item = nullptr;
        panel_item_0 = nullptr;
        panel_Music = nullptr;
        panel_Magic = nullptr;
        getNode<Button*>("Button_zhengmian")->setTag(shopType * 1000 + index);
        getNode<Button*>("Button_zhengmian")->addClickEventListener(clickCallback);
//        img_card->loadTexture(CCString::createWithFormat("card_%d_13_0.png", index)->getCString(), TextureResType::PLIST);
        auto img_card_face1 = getNode<Sprite*>("img_card_face1");
        auto img_card_face2 = getNode<Sprite*>("img_card_face2");
        img_card_face1->setSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(12, 0, index));
        img_card_face2->setSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(13, 0, index));
        
        auto LoadingBar_face = getNode<LoadingBar*>("LoadingBar_face");
        auto Text_faceNum = getNode<Text*>("Text_faceNum");
        auto num = DATA_M->getCardFaceNum(index);
        float perent = (float)num/52.f * 100;
        LoadingBar_face->setPercent(perent);
        Text_faceNum->setString(StringUtils::format("%d/%d",num,52));
    }
    else if (shopType == 3)
    {
        panel_item->setVisible(isBuyed);
        panel_item_0->setVisible(!isBuyed);
        panel_zhengmian->removeFromParent();
        panel_Changjing->removeFromParent();
        panel_Music->removeFromParent();
        panel_Magic->removeFromParent();
        panel_zhengmian = nullptr;
        panel_Changjing = nullptr;
        panel_zhengmian = nullptr;
        panel_Music = nullptr;
        panel_Magic = nullptr;
//        img_card->loadTexture(CCString::createWithFormat("card_bg_%d.png", index)->getCString(), TextureResType::PLIST);
        img_card->setSpriteFrame(SPRITE_M->getCardBgSpriteFrame(index));
        img_card2->setSpriteFrame(SPRITE_M->getCardBgSpriteFrame(index));
        img_card2->setOpacity(51);
    }
    else if(shopType == 5)
    {
        panel_Music->setVisible(true);
        panel_item->removeFromParent();
        panel_item_0->removeFromParent();
        panel_zhengmian->removeFromParent();
        panel_Changjing->removeFromParent();
        panel_Magic->removeFromParent();
        panel_item = nullptr;
        panel_item_0 = nullptr;
        panel_zhengmian = nullptr;
        panel_Changjing = nullptr;
        panel_Magic = nullptr;
        panel_Music->getChildByName<Button*>("Button_Shop")->addClickEventListener(clickCallback);
        auto Button_music_on = panel_Music->getChildByName("Button_music_on");
        auto Text_music = Button_music_on->getChildByName<Text*>("Text_music");
        Text_music->setString(StringUtils::format("Music0%d",index+1));
    }
    else if(shopType == 6)
    {
        panel_Magic->setVisible(true);
        panel_item->removeFromParent();
        panel_item_0->removeFromParent();
        panel_zhengmian->removeFromParent();
        panel_Changjing->removeFromParent();
        panel_Music->removeFromParent();
        panel_Changjing = nullptr;
        panel_item = nullptr;
        panel_item_0 = nullptr;
        panel_Music = nullptr;
        auto num = REWARD_M->getCNT(RewardManager::RewardType::Magic);
        getNode<Text*>("Text_MagicNum")->setString(StringUtils::format("x%d",num));
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

    if(panel_item)
    {
        panel_item->setTag(shopType * 1000 + index);
        panel_item->addClickEventListener(clickCallback);
    }
    
    updateUI();
}

void BagNode::initUI()
{
    BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    img_card = getNode<Sprite*>("img_card_bg");
    img_card2 = getNode<Sprite*>("img_card_bg2");
    
    panel_item = getNode<Layout*>("panel_item");
    panel_item_0 = getNode<Layout*>("panel_item_0");
    panel_zhengmian = getNode<Layout*>("panel_zhengmian");
    panel_Changjing = getNode<Layout*>("panel_Changjing");
    panel_Music = getNode<Layout*>("panel_Music");
    panel_Magic = getNode<Layout*>("panel_Magic");
    panel_item->setVisible(false);
    panel_item_0->setVisible(false);
    panel_zhengmian->setVisible(false);
    panel_Changjing->setVisible(false);
    panel_Music->setVisible(false);
    panel_Magic->setVisible(false);
    
    Sprite_used_bg = getNode<ImageView*>("Image_used_bg");
    Sprite_used_face = getNode<ImageView*>("Image_used_face");
    Sprite_used_gameBg = getNode<ImageView*>("Image_used_gameBg");
    Sprite_used_music = getNode<ImageView*>("Image_used_music");
    Image_new_bg = getNode<ImageView*>("Image_used_bg");
    Image_new_face = getNode<ImageView*>("Image_used_face");
    Image_new_gameBg = getNode<ImageView*>("Image_used_gameBg");
    Image_new_music = getNode<ImageView*>("Image_used_music");
    Sprite_used_bg->setVisible(false);
    Sprite_used_face->setVisible(false);
    Sprite_used_gameBg->setVisible(false);
    Sprite_used_music->setVisible(false);
    Image_new_bg->setVisible(false);
    Image_new_face->setVisible(false);
    Image_new_gameBg->setVisible(false);
    Image_new_music->setVisible(false);

    //img_card_poi = img_card->getPosition();
    getNode("img_new")->setVisible(false);
}
void BagNode::initData()
{
    BaseLayer::initData();
//    addEvent("event_game_update_item", [this](EventCustom *e){
//        auto node = (BagNode*)e->getUserData();
//        setUse(node == this);
//    });
}

void BagNode::setMusicUse(bool flag)
{
    if (isUsing != flag) {
        isUsing = flag;
        updateUI();
    }
}

void BagNode::selected(bool flag)
{
    if (isUsing != flag) {
        isUsing = flag;
        if (isUsing)
        {
            SOUND_M->playGameBgMusic(StringUtils::format(BGM.c_str(), index));
            DATA_M->setCardPicType(shopType, index);
        }
        updateUI();
    }
}


void BagNode::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
}

void BagNode::updateUI()
{
    //使用时的对号图片

    if(panel_item)
    {
        Sprite_used_bg->setVisible(isUsing);
        //牌背
        getNode("Button_card_bg")->setVisible(!isUsing&&isBuyed);
        getNode<Button*>("Button_card_bgA")->setEnabled(isBuyed);
    }
    if(panel_zhengmian)
    {
        Sprite_used_face->setVisible(isUsing);
    }
    if(panel_Changjing)
    {
        Sprite_used_gameBg->setVisible(isUsing);
        //场景ui
        getNode("Button_gameBg")->setVisible(!isUsing&&isBuyed);
        getNode<Button*>("Button_gameBgA")->setEnabled(isBuyed);
    }
    if(panel_Music)
    {
        Sprite_used_music->setVisible(isUsing);
        panel_Music->getChildByName("ui_Lock0_music")->setVisible(!isBuyed);
        panel_Music->getChildByName("Button_Shop")->setVisible(!isBuyed);
        auto Button_music_on = panel_Music->getChildByName<Button*>("Button_music_on");
        Button_music_on->getChildByName("Button_music")->setVisible(!isUsing&&isBuyed);
        
        Button_music_on->setEnabled(isBuyed);
    }
}

bool BagNode::setUse(bool isUse,bool isInit)
{
    //牌面特别判断 就算没有购买也可以用
    if (!isBuyed || this->isUsing == isUse)
    {
        if(panel_zhengmian)
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

void BagNode::playLightAction()
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
