# include "RuleLayer.h"

Scene * RuleLayer::createScene()
{
	return UIUtils::createScene(RuleLayer::create());
}

RuleLayer * RuleLayer::createLayer(BaseLayer* layer)
{
	auto countLayer = new RuleLayer(layer);
    countLayer->init();
	countLayer->setName("RuleLayer");
	return countLayer;
}

bool RuleLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	return true;
}

void RuleLayer::initUI()
{
    BaseLayer::initUI();
    doLayout();
    _actionManager->play("loop", true);
    auto node = _rootNode;

	INIT_BTN(node,"btn_close", CC_CALLBACK_1(RuleLayer::dealButtonClick, this));
	auto scrollView_rule = FIND_NODE(ScrollView *,node,"scrollView_rule");
	scrollView_rule->setScrollBarEnabled(false);

	// 处理多语言
	FIND_NODE(Text *,node,"Text_1")->setString(UIUtils::getStringByName("100054"));
//    FIND_NODE(Button *,node,"btn_close")->setTitleText(UIUtils::getStringByName("100064"));
//    FIND_NODE(Text *,node,"text_rule")->setString(UIUtils::getStringByName("100055"));
    
    for (int i=0; i<=8; i++) {
        FIND_NODE(Text*, node, StringUtils::format("text_rule%d", i))->setString(UIUtils::getStringByName(StringUtils::format("1001%d", 40+i)));
    }
}
void RuleLayer::initData()
{
    BaseLayer::initData();
    setName("RuleLayer");
}
void RuleLayer::dealButtonClick(Ref * pSender)
{
	auto dealBtn = dynamic_cast<Widget *>(pSender);
	auto btnName = dealBtn->getName();

    if (dynamic_cast<Button*>(pSender))
        SOUND_M->playBtnClickAudio();

	if ("btn_close" == btnName||"Panel_out" == btnName)
	{
        if(_layer)
        {
            _layer->setVisible(true);
            _layer->playAni("Start", false);
        }
		SCENE_M->removeLayerByName("RuleLayer");
	}
}

RuleLayer::RuleLayer(BaseLayer* layer):
BaseLayer("RuleLayer.csb")
,_layer(layer)
{
    
}

RuleLayer::~RuleLayer()
{
    
}
