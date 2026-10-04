# include "ShopNode.h"
#include "SpriteManager.h"
#include "DataManager.h"
#include "AtlasManager.h"

ShopNode::ShopNode()
{

}

ShopNode::~ShopNode()
{

}

ShopNode * ShopNode::createShopNode(int shopType, int index, std::function<void(Ref *)> clickCallback)
{
	auto shopNode = ShopNode::create();
	shopNode->setShopNodeState(shopType, index, clickCallback);
	return shopNode;
}

bool ShopNode::init()
{
	if (!Widget::init())
	{
		return false;
	}
	isTouchMove = false;
	this->initUI();

	return true;
}

void ShopNode::initUI()
{
	auto node = UIUtils::createCSBNode("ItemNode.csb");

	panel_item = FIND_NODE(Layout *, node, "panel_item");
	panel_item->removeFromParentAndCleanup(false);
	this->addChild(panel_item);

//    img_light_1 = FIND_NODE(ImageView *, this, "img_light_1");
//    img_light_2 = FIND_NODE(ImageView *, this, "img_light_2");
//    img_light_1->setVisible(false);
//    img_light_2->setVisible(false);

	img_card = FIND_NODE(Sprite *, this, "img_card");
    img_card_poi = img_card->getPosition();
//    img_card->ignoreContentAdaptWithSize(true);

	img_coin = FIND_NODE(ImageView *, this, "img_coin");
	img_new = FIND_NODE(ImageView *, this, "img_new");

	text_item = FIND_NODE(Text *, this, "text_item");
	atlasLabel_num = FIND_NODE(TextBMFont *, this, "atlasLabel_num");
    Sprite_used = FIND_NODE(Sprite *, this, "Sprite_used");
    Button_buy = FIND_NODE(Button *, this, "Button_buy");
    Button_use = FIND_NODE(Button *, this, "Button_use");
    Button_use->setVisible(false);
	img_new->setVisible(false);
	img_coin->setVisible(false);
	text_item->setVisible(false);

	// 处理多语言
	FIND_NODE(Text *,this,"text_item")->setString(UIUtils::getStringByName("100053"));
}

void ShopNode::setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback)
{
	this->shopType = shopType;
	this->index = index;
	this->isBuyed = DATA_M->getShopItemStatus(shopType, index);
	this->isUsing = false;
	this->price = DATA_M->getShopItemPrice(shopType, index);
	if (shopType == 1)
	{
		//����
		//img_card->loadTexture("card_0_10_1.png", TextureResType::PLIST);
//        img_card->loadTexture(CCString::createWithFormat("game_bg_%d.png", index)->getCString(), TextureResType::PLIST);
        if(index > 13)
        {//动态
            img_card->setSpriteFrame(AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", index-12),"car_new_0_1.atlas"));
        }
        else
        {
            img_card->setSpriteFrame(AtlasManager::getInstance()->getSF(1, 0, 0, index));
        }
        
	}
	else if (shopType == 2)
	{
//        img_card->loadTexture(CCString::createWithFormat("card_%d_13_0.png", index)->getCString(), TextureResType::PLIST);
        img_card->setSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(13, 0, index));
	}
	else if (shopType == 3)
	{
//        img_card->loadTexture(CCString::createWithFormat("card_bg_%d.png", index)->getCString(), TextureResType::PLIST);
        img_card->setSpriteFrame(SPRITE_M->getCardBgSpriteFrame(index));
	}

	if (isBuyed)
	{
		panel_item->setName("select");
		text_item->setString(UIUtils::getStringByName("yihuode"));
		text_item->setVisible(true);
	}
	else
	{
		panel_item->setName("buy");
		img_coin->setVisible(true);
		atlasLabel_num->setString(toString(price));
	}

	panel_item->setTag(shopType * 1000 + index);
	panel_item->addClickEventListener(clickCallback);
    updateUI();
}

bool ShopNode::buy()
{
	if (price <= DATA_M->getCoinNum())
	{
		//ֱ�ӹ���
		DATA_M->unLockShopItemStatus(shopType,index);
		DATA_M->setCoinNum(-price,false,201);
		isBuyed = true;
		panel_item->setName("select");
		text_item->setString(UIUtils::getStringByName("yihuode"));
//		text_item->setVisible(true);
		img_coin->setVisible(false);

		SCENE_M->showTips(UIUtils::getStringByName("goumaichengg"));

		return true;
	}
	return false;
}

bool ShopNode::setUse(bool isUse,bool isInit)
{
	if (!isBuyed || this->isUsing == isUse)
	{
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


		text_item->setString(UIUtils::getStringByName("shiyongzhong"));
		text_item->setColor(Color3B::GREEN);
        playLightAction();

		return true;
	}
	else
	{
		text_item->setString(UIUtils::getStringByName("yihuode"));
		text_item->setColor(Color3B::WHITE);

		//ֹͣ�˶�
//        img_light_1->stopAllActions();
//        img_light_2->stopAllActions();
		img_card->stopAllActions();
		img_card->setPosition(img_card_poi);
//        img_light_1->setVisible(false);
//        img_light_2->setVisible(false);
	}
	return false;
}

void ShopNode::playLightAction()
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
void ShopNode::playSelectAction()
{

}

void ShopNode::dealButtonClick(Ref * pSender)
{
	auto dealBtn = dynamic_cast<Button *>(pSender);
	auto btnName = dealBtn->getName();

	SOUND_M->playBtnClickAudio();

	if ("btn_level" == btnName)
	{
	}
}

void ShopNode::refush(int coinNum)
{
	if (isBuyed)
	{
        updateUI();
		return;
	}

	if (coinNum < price)
	{
		atlasLabel_num->setColor(Color3B::RED);
	}
	else
	{
		atlasLabel_num->setColor(Color3B::WHITE);
	}
}

void ShopNode::updateUI()
{
    Sprite_used->setVisible(isUsing);
//    Button_use->setVisible(!isUsing && isBuyed);
    Button_buy->setVisible(!isUsing && !isBuyed);
}
