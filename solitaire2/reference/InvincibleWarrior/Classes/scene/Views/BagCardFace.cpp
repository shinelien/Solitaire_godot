//
//  BagCardFace.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/13.
//

#include <stdio.h>
#include "BagCardFace.h"
#include "AtlasManager.h"
#include "ShopManager.h"
#include "RewardManager.h"
#include "BagView.h"
#include "DataManager.h"
#include "SpriteManager.h"
#include "CardSprite.h"

BagCardFace::BagCardFace(BagView* bagView)
:BaseLayer("2020BagItem_cardFace.csb")
,_bagView(bagView)
{
    
}
BagCardFace::~BagCardFace()
{
    
}
    
BagCardFace * BagCardFace::createBagNode(int shopType, int index, std::function<void(Ref *)> clickCallback,BagView* bagView)
{
    auto bagNode = BagCardFace::createLayerN(bagView);
    bagNode->setShopNodeState(shopType, index, clickCallback);
    return bagNode;
}
void BagCardFace::setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback)
{
    this->shopType = shopType;
    this->index = index;
    this->isBuyed = DATA_M->getShopItemStatus(shopType, index);
    this->isUsing = false;
    
    auto newNum = DATA_M->getPropNew(shopType, index);
    isNew = newNum != -1;
    
    if (shopType == 2)
    {
        panel_zhengmian->setVisible(true);
        
        getNode<Button*>("Button_zhengmian")->setTag(shopType * 1000 + index);
        getNode<Button*>("Button_zhengmian")->addClickEventListener(clickCallback);
//        img_card->loadTexture(CCString::createWithFormat("card_%d_13_0.png", index)->getCString(), TextureResType::PLIST);
        auto img_card_face1 = getNode<Sprite*>("img_card_face1");
        auto img_card_face2 = getNode<Sprite*>("img_card_face2");
        auto num = 12;
        auto card1 = UIUtils::createCSBNode("card/CardFace.csb");
        auto card2 = UIUtils::createCSBNode("card/CardFace.csb");
        auto _sprite1 = card1->getChildByName<Sprite*>("Sprite_face");
        auto _sprite2 = _sprite1->getChildByName<Sprite*>("Sprite_num");
        auto _sprite3 = _sprite1->getChildByName<Sprite*>("Sprite_color");
        _sprite1->setSpriteFrame(AtlasManager::getInstance()->getSF(2, num, 0, index));
        _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5, num, 0, index));
        _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6, num, 0, index));
        _sprite2->setColor(UIUtils::getCardColor(0));
        card1->setPosition(img_card_face1->getContentSize()*0.5f);
        _sprite3->setPosition(Vec2(_sprite1->getContentSize().width*0.5f-1,_sprite1->getContentSize().height*0.5f-5));
        img_card_face1->addChild(card1);

        auto size2 = _sprite2->getContentSize();
        _sprite2->setPositionX(size2.width*0.5f);
        num = 13;
        auto _sprite4 = card2->getChildByName<Sprite*>("Sprite_face");
        auto _sprite5 = _sprite4->getChildByName<Sprite*>("Sprite_num");
        auto _sprite6 = _sprite4->getChildByName<Sprite*>("Sprite_color");
        _sprite4->setSpriteFrame(AtlasManager::getInstance()->getSF(2, num, 0, index));
        _sprite5->setSpriteFrame(AtlasManager::getInstance()->getSF(5, num, 0, index));
        _sprite6->setSpriteFrame(AtlasManager::getInstance()->getSF(6, num, 0, index));
        _sprite5->setColor(UIUtils::getCardColor(0));
        img_card_face2->addChild(card2);
        card2->setPosition(img_card_face2->getContentSize()*0.5f);
        _sprite6->setPosition(Vec2(_sprite4->getContentSize().width*0.5f-1,_sprite4->getContentSize().height*0.5f-5));

        auto size5 = _sprite5->getContentSize();
        _sprite5->setPositionX(size5.width*0.5f);
        
        auto LoadingBar_face = getNode<LoadingBar*>("LoadingBar_face");
        auto Text_faceNum = getNode<Text*>("Text_faceNum");
        num = DATA_M->getCardFaceNum(index);
        float perent = (float)num/52.f * 100;
        LoadingBar_face->setPercent(perent);
        Text_faceNum->setString(StringUtils::format("%d/%d",num,52));
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

void BagCardFace::initUI()
{
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    
    panel_zhengmian = getNode<Layout*>("panel_zhengmian");
    panel_zhengmian->setVisible(false);
    
    
   
    Sprite_used_face = getNode<ImageView*>("Image_used_face");
    Image_new_face = getNode<ImageView*>("img_new_face");
    Sprite_used_face->setVisible(false);
    Image_new_face->setVisible(false);
    

    //img_card_poi = img_card->getPosition();
}
void BagCardFace::initData()
{
    BaseLayer::initData();

}

void BagCardFace::selected(bool flag)
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


void BagCardFace::dealButtonClick(Ref *pSender)
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

void BagCardFace::updateUI()
{
    //使用时的对号图片

   
    if(panel_zhengmian)
    {
        //Sprite_used_face->setVisible(isUsing);
        
        Image_new_face->setVisible(isNew);
        
    }
}

bool BagCardFace::setUse(bool isUse,bool isInit)
{
    //牌面特别判断 就算没有购买也可以用
    if (!isBuyed ||isUse)
    {
        this->isUsing = isUse;
        if(panel_zhengmian)
        {
            this->isUsing = isUse;
            updateUI();
            if (isUse)
            {
                if (!isInit)
                {
                    for(int i = 0;i < 52;++i)
                    {
                        auto isBuy = DATA_M->getCardFaceStatus(shopType, index,i);
                        if(isBuy)
                        {
                            DATA_M->setCardPicType(shopType, index,i);
                        }
                    }
                    
                    SPRITE_M->changeCardSkin(shopType);
                }
                return true;
            }
        }
        return false;
    }
    else
    {
        this->isUsing = false;
    }
    
    updateUI();
    
    return false;
}

void BagCardFace::playLightAction()
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

void BagCardFace::setNew(bool is)
{
    isNew = is;
    updateUI();
}
