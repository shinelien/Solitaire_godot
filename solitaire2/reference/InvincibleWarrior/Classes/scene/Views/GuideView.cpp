
#include "GuideView.h"
#include "SceneManager.h"

void GuideView::initUI() {
    BaseLayer::initUI();
    doLayout();
    //    auto sp = Sprite::createWithSpriteFrameName("daily/Daily_bar0.png");
        ProgressTimer_percent = ProgressTimer::create(Sprite::createWithSpriteFrameName("Ui_Task2.png"));
        auto loadingbar = getNode<LoadingBar*>("LoadingBar_percent");
        loadingbar->setPercent(0);
        loadingbar->addChild(ProgressTimer_percent);
        ProgressTimer_percent->setPosition(loadingbar->getContentSize()/2);
    //    loadingbar->getParent()->addChild(sp);
        //设置进度条的模式
        //kCCProgressTimerTypeBar表示条形模式
        //默认的模式是kCCProgressTimerTypeRadial(圆圈模式)
        ProgressTimer_percent->setType(ProgressTimer::Type::BAR);
        //设置进度条变化的方向
        //setMidpoint默认在左边
        //ccp(1,0)表示在X轴方向上有变化,在y轴方向上没变化
        //ccp(0,1)表示在X轴方向上没有变化,在y轴方向上有变化
        ProgressTimer_percent->setBarChangeRate(Vec2(1,0));
        //从哪个方向开始变化
        //ccp(0,0)表示从左边开始变化
        ProgressTimer_percent->setMidpoint(Vec2(0,0));
    //    ProgressTimer_percent->setPercentage(50);
    auto dailyManager = DailyManager::getInstance();
    auto monthCompleteCNT = dailyManager->getMonthCompleteCNT(_current);
    auto days = dailyManager->getDays(_current.Year(), _current.Month());
    
    getNode<TextBMFont*>("BMFont_road1")->setString(StringUtils::toString(7));
    getNode<TextBMFont*>("BMFont_road2")->setString(StringUtils::toString(14));
    getNode<TextBMFont*>("BMFont_road3")->setString(StringUtils::toString(21));
    getNode<TextBMFont*>("BMFont_road4")->setString(StringUtils::toString(days));
    //摆放奖杯 Node_Bar_tro_1
    auto size = loadingbar->getBoundingBox().size;
    //1
    auto x1 = size.width * 7.f / (float)days;
    getNode("Node_Bar_tro_1")->setPositionX(x1);
    //2
    auto x2 = size.width * 14.f / (float)days;
    getNode("Node_Bar_tro_2")->setPositionX(x2);
    //3
    auto x3 = size.width * 21.f / (float)days;
    getNode("Node_Bar_tro_3")->setPositionX(x3);
    //4
    auto x4 = size.width;
    getNode("Node_Bar_tro_4")->setPositionX(x4);
    
    auto percent = (float)monthCompleteCNT/(float)days * 100.0f;
    runProgress(0.2f,percent);
    getNode<Text*>("Text_time")->setString(StringUtils::format("%d.%d",_current.Year(),_current.Month()));
    getNode<Text*>("Text_total1")->setString(toString(monthCompleteCNT));
    getNode<Text*>("Text_total2_1")->setString("/");
    getNode<Text*>("Text_total1_0")->setString(toString(monthCompleteCNT));
    getNode<Text*>("Text_total2")->setString(toString(days));
    auto Text_title = getNode<Text*>("Text_title");
    Text_title->setString(Lang("100155"));
    UIUtils::textAdaptiveSize(Text_title,440);
    getNode<Text*>("Text_content")->setString(Lang("100161"));
    getNode<Text*>("Text_known")->setString(Lang("100162"));
}

void GuideView::initData() {
    BaseLayer::initData();
    setName("GuideView");
}

void GuideView::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();

    if(btnName == "Button_get"||btnName == "panel_daily")
    {
        SCENE_M->removeLayer(this);
    }
    
}

GuideView::GuideView(Date date)
:BaseLayer("guide.csb")
,_current(date)
{
}

GuideView::~GuideView()
{
}

GuideView* GuideView::showGuid(GuideView::GuideType type,Date date) {
    auto view = GuideView::createLayerN(date);
    view->setGuideType(type);

    SCENE_M->addDialog(view);
    
    return view;
}

void GuideView::setGuideType(GuideView::GuideType type) {
    _guideType = type;
    switch (type) {
        case GuideType::NewTeach:
            _actionManager->play("start1", false);
            break;
        case GuideType::DailyTeach:
            _actionManager->play("start0", false);
            break;
    }
}
void GuideView::runProgress(float time,float percent)
{
    ProgressTimer_percent->runAction(ProgressTo::create(time, percent));
}
