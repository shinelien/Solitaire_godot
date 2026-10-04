# include "CountLayer.h"
#include "ScoreManager.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
Scene * CountLayer::createScene()
{
	return UIUtils::createScene(CountLayer::create());
}

CountLayer * CountLayer::createLayer()
{
	auto countLayer = CountLayer::create();
	countLayer->setName("CountLayer");
	return countLayer;
}

bool CountLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	return true;
}

void CountLayer::initData()
{
    BaseLayer::initData();
    setName("CountLayer");

}

static const std::map<ScoreManager::Type, int> StatisticsTypeIDX{
	{ScoreManager::Type::WINCNT, 1},
	{ScoreManager::Type::FAILDCNT, 2},
	{ScoreManager::Type::BESTWINTIME, 4},
	{ScoreManager::Type::LONEGESTTIME, 5},
	{ScoreManager::Type::WINMINMOVES, 6},
	{ScoreManager::Type::WINMAXMOVES, 7},
	{ScoreManager::Type::WINNOMOVES, 8},
	{ScoreManager::Type::TOTALSCORE, 9},
	{ScoreManager::Type::WINNINGSNT, 10},
	{ScoreManager::Type::LONGESTWINNINGSCNT, 11},
	{ScoreManager::Type::TOTALTIME, 12},
    {ScoreManager::Type::HighestWeiJiaSiScore, 13},
};
void CountLayer::initUI()
{
    BaseLayer::initUI();
    doLayout();
    _actionManager->play("start", false);
    auto node = _rootNode;
	panel_count = node->getChildByName("panel_count");

	panel_num_1 = FIND_NODE(Node *, node, "panel_num_1"); 
	panel_num_2 = FIND_NODE(Node *, node, "panel_num_2");

	INIT_BTN(node,"btn_close", CC_CALLBACK_1(CountLayer::dealButtonClick, this));
    auto pageView_container = FIND_NODE(PageView *, node, "PageView_container");
    pageView_container->setIndicatorEnabled(true);
    pageView_container->addEventListener([this](Ref*ref, PageView::EventType type){
        if(type == PageView::EventType::TURNING)
        {
            auto page = dynamic_cast<PageView*>(ref);
            auto id = page->getCurrentPageIndex();//setCurrentPageIndex
            if(id == 0)
            {
                getNode<Sprite*>("Sprite_2")->setSpriteFrame("game_ui statistics1.png");
                getNode<Sprite*>("Sprite_3")->setSpriteFrame("game_ui statistics2.png");
            }
            else if(id == 1)
            {
                getNode<Sprite*>("Sprite_2")->setSpriteFrame("game_ui statistics2.png");
                getNode<Sprite*>("Sprite_3")->setSpriteFrame("game_ui statistics1.png");
            }
        }
    });
	
	auto showStatistics = [this](int gameType) {
        for (auto &it:StatisticsTypeIDX) {
            auto rootPanel = gameType==1?panel_num_1:panel_num_2;
            auto atlas = FIND_NODE(Text *, rootPanel, StringUtils::format("atlasLabel_%d",it.second));

            auto data = ScoreManager::getInstance()->getScore(gameType, it.first);
            if (it.first == ScoreManager::Type::BESTWINTIME || it.first == ScoreManager::Type::LONEGESTTIME || it.first == ScoreManager::Type::TOTALTIME) {
                int min = data / 60;
                int sec = data % 60;
                atlas->setString(StringUtils::format("%02d:%02d", min, sec));
            }
            else if (it.first == ScoreManager::Type::WINCNT || it.first == ScoreManager::Type::FAILDCNT) {
                auto winRate = ScoreManager::getInstance()->getRate(gameType, it.first);
                auto sp = Sprite::createWithSpriteFrameName("game_ui statistics0.png");
                bool isWin = it.first == ScoreManager::Type::WINCNT;
                sp->setColor(isWin?Color3B::GREEN:Color3B::RED);
                auto progressTimer = ProgressTimer::create(sp);
                progressTimer->setType(ProgressTimer::Type::RADIAL);
                auto node = FIND_NODE(Node *, rootPanel, isWin?"Node_win":"Node_lose");
                node->addChild(progressTimer);
                progressTimer->setScaleX(isWin?1:-1);
                progressTimer->setPercentage(winRate);
                atlas->setString(StringUtils::format("%d(%.2f%%)", data, winRate));
            }
            else {
                atlas->setString(StringUtils::toString(data));
            }
        }
	};
    showStatistics(1);      // 初始化一张牌
    showStatistics(2);      // 初始化三张牌
    

	// 多语言
	FIND_NODE(Button *,node,"btn_close")->setTitleText(UIUtils::getStringByName("100064"));
	FIND_NODE(Text *,node,"Text_1")->setString(UIUtils::getStringByName("100006"));
	FIND_NODE(Text *,node,"Text_2")->setString(UIUtils::getStringByName("100007"));
	FIND_NODE(Text *,node,"Text_3")->setString(UIUtils::getStringByName("100008"));
	FIND_NODE(Text *,node,"Text_3_0")->setString(UIUtils::getStringByName("100009"));
//    FIND_NODE(Text *,node,"Text_3_1")->setString(UIUtils::getStringByName("100010"));
	FIND_NODE(Text *,node,"Text_3_1_0")->setString(UIUtils::getStringByName("100011"));
	FIND_NODE(Text *,node,"Text_3_1_0_0")->setString(UIUtils::getStringByName("100012"));
	FIND_NODE(Text *,node,"Text_3_1_0_0_0")->setString(UIUtils::getStringByName("100013"));
    auto Text_3_1_0_0_0_0 = FIND_NODE(Text *,node,"Text_3_1_0_0_0_0");
    Text_3_1_0_0_0_0->setString(UIUtils::getStringByName("100014"));
    UIUtils::textAdaptiveSize(Text_3_1_0_0_0_0,560);
	FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_0")->setString(UIUtils::getStringByName("100015"));
	FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_0_0")->setString(UIUtils::getStringByName("100016"));
	FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_0_0_0")->setString(UIUtils::getStringByName("100017"));
    auto Text_3_1_0_0_0_0_0_0_0_0_0 = FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_0_0_0_0");
    Text_3_1_0_0_0_0_0_0_0_0_0->setString(UIUtils::getStringByName("100018"));
    UIUtils::textAdaptiveSize(Text_3_1_0_0_0_0_0_0_0_0_0,560);
	FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_0_0_0_0_0")->setString(UIUtils::getStringByName("100019"));
    
	FIND_NODE(Text *,node,"Text_2_1")->setString(UIUtils::getStringByName("100020"));
	FIND_NODE(Text *,node,"Text_3_2")->setString(UIUtils::getStringByName("100021"));
	FIND_NODE(Text *,node,"Text_3_0_1")->setString(UIUtils::getStringByName("100022"));
//    FIND_NODE(Text *,node,"Text_3_1_1")->setString(UIUtils::getStringByName("100023"));
	FIND_NODE(Text *,node,"Text_3_1_0_1")->setString(UIUtils::getStringByName("100024"));
	FIND_NODE(Text *,node,"Text_3_1_0_0_1")->setString(UIUtils::getStringByName("100025"));
	FIND_NODE(Text *,node,"Text_3_1_0_0_0_1")->setString(UIUtils::getStringByName("100026"));
    auto Text_3_1_0_0_0_0_1 = FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_1");
    Text_3_1_0_0_0_0_1->setString(UIUtils::getStringByName("100027"));
    UIUtils::textAdaptiveSize(Text_3_1_0_0_0_0_1,560);
	FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_1")->setString(UIUtils::getStringByName("100028"));
	FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_0_0_1")->setString(UIUtils::getStringByName("100029"));
	FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_0_0_0_1")->setString(UIUtils::getStringByName("100030"));
    auto Text_3_1_0_0_0_0_0_0_0_0_0_1 = FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_0_0_0_0_1");
    Text_3_1_0_0_0_0_0_0_0_0_0_1->setString(UIUtils::getStringByName("100031"));
    UIUtils::textAdaptiveSize(Text_3_1_0_0_0_0_0_0_0_0_0_1,560);
	FIND_NODE(Text *,node,"Text_3_1_0_0_0_0_0_0_0_0_0_0_1")->setString(UIUtils::getStringByName("100032"));
    
    //FIND_NODE(Text *,node,"Text_VegasScore")->setString(UIUtils::getStringByName("100019"));
}

void CountLayer::dealButtonClick(Ref * pSender)
{
	auto dealBtn = dynamic_cast<Widget *>(pSender);
	auto btnName = dealBtn->getName();

	if ("btn_close" == btnName||"panel_count" == btnName)
	{
        //关闭窗口开始累计计时
        SCENE_M->getGameView()->setIsOpenTipsTime(true);
		SCENE_M->removeLayerByName("CountLayer");
        SOUND_M->playBtnClickAudio();
	}
}

void CountLayer::dealButtonTouch(Ref * pSender, Widget::TouchEventType touchType)
{
	auto btn = static_cast<Button *>(pSender);
	switch (touchType)
	{
	case Widget::TouchEventType::BEGAN:
		btn->setScale(1.1);
		break;
	case Widget::TouchEventType::ENDED:
		btn->setScale(1);
		break;
	case Widget::TouchEventType::CANCELED:
		btn->setScale(1);
		break;
	case Widget::TouchEventType::MOVED:
		break;
	default:
		break;
	}
}

CountLayer::CountLayer()
:BaseLayer("CountLayer.csb"){
}

void CountLayer::onExit()
{
    BaseLayer::onExit();
}
