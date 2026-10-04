# include "CoinLayer.h"

Scene * CoinLayer::createScene()
{
	return UIUtils::createScene(CoinLayer::create());
}

CoinLayer * CoinLayer::createLayer()
{
	auto coinLayer = CoinLayer::create();
	coinLayer->setName("CoinLayer");
	return coinLayer;
}

bool CoinLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	UIUtils::showDialog(panel_coin, "img_coin");
	this->scheduleUpdate();
	return true;
}

void CoinLayer::initData()
{
    BaseLayer::initData();
    setName("CoinLayer");
	if (DATA_M->getNextFreeCoinTime2() <= 0)
	{
		//免费的
		isHaveFree = true;
	}
	else
	{
		isHaveFree = false;
	}

	if (DATA_M->getNextFreeCoinTime1() <= 0||1)
	{//不限时
		isCanSeeAds = true;
	}
	else
	{
		isCanSeeAds = false;
	}
}

void CoinLayer::update(float dt)
{
	if (!isHaveFree)
	{
		long nextTime = DATA_M->getNextFreeCoinTime2();
		int min = nextTime / 60;
		int sec = nextTime % 60;
		//要显示恢复
		atlasLabel_time->setString(CCString::createWithFormat("00/%02d/%02d", min, sec)->getCString());

		if (nextTime <= 0)
		{
			setIsHaveFree(true);
		}
	}

	if (!isCanSeeAds)
	{
		long nextTime = DATA_M->getNextFreeCoinTime1();
		//要显示恢复
		if (nextTime <= 0)
		{
			setCanSeeAds(true);
		}
	}
}

void CoinLayer::initUI()
{
    auto node = UIUtils::createCSBNode(UIUtils::IsPad()?"pad/CoinLayer_pad.csb":"CoinLayer.csb", "loop", true);
	_rootNode = node;
	doLayout();
	this->addChild(node);
	panel_coin = node->getChildByName("panel_coin");
	INIT_BTN(node,"btn_coin_close", CC_CALLBACK_1(CoinLayer::dealButtonClick, this));
	
	btn_ads = INIT_BTN(node, "btn_ads", CC_CALLBACK_1(CoinLayer::dealButtonClick, this));
	btn_freecoin = INIT_BTN(node, "btn_freecoin", CC_CALLBACK_1(CoinLayer::dealButtonClick, this));

	text_ads = FIND_NODE(Text *, node, "text_ads");
	text_free = FIND_NODE(Text *,node,"text_free");
	atlasLabel_time = FIND_NODE(TextAtlas *, node, "atlasLabel_time");
    //addClickEventListener
    auto panel = _rootNode->getChildByName<Layout*>("Panel_close");
    panel->addClickEventListener(CC_CALLBACK_1(CoinLayer::dealButtonClick, this));
    
	setCanSeeAds(isCanSeeAds);
	setIsHaveFree(isHaveFree);

	// 多语言
//    FIND_NODE(Text *, node, "Text_title")->setString(UIUtils::getStringByName("100068"));
    FIND_NODE(Text *,node,"Text_7")->setString(UIUtils::getStringByName("100000"));
    FIND_NODE(Text *,node,"text_ads")->setString(UIUtils::getStringByName("100001"));
    FIND_NODE(Text *,node,"text_three")->setString(UIUtils::getStringByName("100002"));
    FIND_NODE(Text *,node,"text_left")->setString(UIUtils::getStringByName("100003"));
    FIND_NODE(Text *,node,"text_freecoin")->setString(UIUtils::getStringByName("100004"));
    FIND_NODE(Text *,node,"text_free")->setString(UIUtils::getStringByName("100005"));
    FIND_NODE(Text *,node,"text_three_des")->setString(StringUtils::format("+%ld", DATA_M->getRewardCoin1()));
    FIND_NODE(Text *,node,"text_three_des1")->setString(StringUtils::format("+%ld", DATA_M->getRewardCoin()));
}

void CoinLayer::setCanSeeAds(bool isCanSeeAds)
{
	this->isCanSeeAds = isCanSeeAds;
	if (isCanSeeAds && DATA_M->getHaveVideo())
	{
		btn_ads->setEnabled(true);
		text_ads->setString(UIUtils::getStringByName("lingqu"));
	}
	else
	{
		btn_ads->setEnabled(false);
		text_ads->setString(UIUtils::getStringByName("zanwuship"));
	}
}

void CoinLayer::setIsHaveFree(bool isHaveFree)
{
	this->isHaveFree = isHaveFree;
	if (isHaveFree)
	{
		btn_freecoin->setVisible(true);
		text_free->setVisible(false);
	}
	else
	{
		btn_freecoin->setVisible(false);
		text_free->setVisible(true);
	}
}

void CoinLayer::dealButtonClick(Ref * pSender)
{
	auto dealBtn = dynamic_cast<Widget *>(pSender);
	auto btnName = dealBtn->getName();

	SOUND_M->playBtnClickAudio();

	if ("btn_coin_close" == btnName||"Panel_close" == btnName)
	{
		UIUtils::hideDialog(panel_coin, "img_coin");
		this->runAction(Sequence::create(DelayTime::create(0.4), CallFunc::create([this]{
			SCENE_M->removeLayer(this);
		}), NULL));
	}
	else if ("btn_ads" == btnName)
	{
		//显示广告
//        setCanSeeAds(false);
//        DATA_M->playVideoAds(1);
        DATA_M->playVideoAds(3, (int)DATA_M->getRewardCoin1());
		SCENE_M->removeLayer(this);
	}
	else if ("btn_freecoin" == btnName)
	{
		//显示免费金币界面
        DATA_M->getFreeCoin();
		
		SCENE_M->removeLayer(this);
	}
}
