#include "DailyView.h"
#include "DailyNode.h"
#include "GameViewHD.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdsManager.h"
#endif
#include "GuideView.h"
#include "MainLobby.h"
#include "BagView.h"
//任务
#include "DailytaskView.h"
//星星宝箱
#include "StarBoxView.h"
//分享奖励
#include "ShareRewardView.h"
//领取金币
#include "FreeCoinLayer.h"
#include "PlayerManager.h"
#include "FanPaiRewardView.h"
//签到
#include "SevenDayView.h"
#include "GrowupNode.h"
#include "DailyGameView.h"
#include "DailyMoreView.h"

#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "DailyPage.h"

#include "TaskManager.h"

#include "EventObserver.h"

const auto VSpace = 16;
const auto HSpace = 28;
const auto TotalRow = 5;
const float itemWidth = 170;
Vec2 GetPosition(int x, int y)
{
    return Vec2((x+0.5)*(110+HSpace), (y+0.5)*(108+VSpace));
}

Vec2 GetPosition(int x)
{
    return Vec2((x) * 170 + 85, 94);//Vec2((x+0.5)*(110+HSpace), (y+0.5)*(108+VSpace));
}

const std::vector<std::string> Skeletons{"flag0", "flagL", "flagR"};
static bool PlayOnce = true;
void DailyView::initUI() {
    BaseLayer::initUI();
    doLayout();

    
    _lobby = SCENE_M->getLobby();
    pageView = getNode<PageView*>("PageView_1");
    pageView->setTouchEnabled(true);
    pageView->addEventListenerScrollView(this, scrollvieweventselector(DailyView::scrollEvent));
    pageView->setScrollDuration(0.5f);
    pageRect =  pageView->getBoundingBox();
    pageRect.origin = pageView->getParent()->convertToWorldSpace(pageRect.origin);
    pageSize = pageRect.size;
    
    pageNum = 0;
    pageView->addEventListener([this](Ref*ref, PageView::EventType type){
        if(type == PageView::EventType::TURNING)
        {//只创建三个
            auto page = dynamic_cast<PageView*>(ref);
            updatePage(page);
        }
    });
    
    //page按钮
    
    Button_hardRight = getNode<Button*>("Button_hardRight");
    Button_hardLeft1 = getNode<Button*>("Button_hardLeft1");

    
    
    //FileNode_start = getNode("FileNode_start");
    FileNode_trophy = getNode("FileNode_trophy");
    FileNode_crown = getNode("FileNode_crown");
    auto currentDate = DailyManager::getInstance()->getCurrentDate();
    _today = DailyManager::getInstance()->today();
    _maxday = Date(_today.Year(), 12, 31);
    _current = currentDate==NoneDate?_today:currentDate;
    _current2 = _current;
    
    setMonthUI(_current.Year(), _current.Month(),_current.Day());
    
    
    //多语言
    updateDYY();
    getNode<Text*>("Text_total2_1")->setString("/");
}

int gouRound(int value, int max)
{
    auto t = value % max;
    return t == 0?1:t;
}

void DailyView::scrollEvent(Ref* pageView, ScrollviewEventType type)
{
    auto daysPageView = (PageView*)pageView;
    if(type == SCROLLVIEW_EVENT_SCROLLING_BEGAN) {
        daysPageView->setEnabled(false);
        //允许跳转
        isJump = true;
        isUpdatePage = false;
    }
    else if(type == SCROLLVIEW_EVENT_AUTOSCROLL_ENDED1) {
        auto page = dynamic_cast<PageView*>(pageView);
        //问题。滑动了 但是没有翻页
        auto idx = page->getCurrentPageIndex();
        
        daysPageView->setEnabled(true);
        if(_currentIndex == idx)return;
        //最终修改 大概 如果没有进入updatePage 则补充进入 在开始滑动时与按钮点击时变为false 在updatePage()里变为true
        if(!isUpdatePage)
        {
            updatePage(page);
        }

        
        //滑动结束处理 第二步
//        daysPageView->setInnerContainerPosition(Vec2(-680, 0));
        auto id = daysPageView->getCurrentPageIndex();
        if(isUpdateDay)
        {
            Button_hardRight->setEnabled(false);
        }
        else
        {
            if(isPageRun)
            {
                if(isPageLeft)
                {//往左翻页没走page的回调。在此更新内容
                    auto items = daysPageView->getItems();
                    auto idx = pageItemNum<=2?id:1;
                    auto item = items.at(idx);
                    auto vec = item->getChildren();
                    auto dailyNode = dynamic_cast<DailyNode*>(vec.at(0));
                    for(auto item:items)
                    {
                        auto vec = item->getChildren();
                        for(auto node:vec)
                        {
                            auto dailyNode2 = dynamic_cast<DailyNode*>(node);
                            if(dailyNode2)
                            {
                                dailyNode2->setSelected(dailyNode2 == dailyNode);
                            }
                        }
                    }
                    Button_hardRight->setEnabled(true);
                }
                else if(isPageRight)
                {//往右翻页没走page的回调。在此更新内容
                    auto items = daysPageView->getItems();
                    auto item = items.at(1);
                    auto vec = item->getChildren();
                    auto dailyNode = dynamic_cast<DailyNode*>(vec.at(0));
                    for(auto item:items)
                    {
                        auto vec = item->getChildren();
                        for(auto node:vec)
                        {
                            auto dailyNode2 = dynamic_cast<DailyNode*>(node);
                            if(dailyNode2)
                            {
                                dailyNode2->setSelected(dailyNode2 == dailyNode);
                            }
                        }
                    }
                    Button_hardLeft1->setEnabled(true);
                }
                
                if(id == 1&&pageItemNum==2)
                {
                    Button_hardRight->setEnabled(false);
                }
                else if(id == 0&&pageItemNum==2)
                {
                    Button_hardLeft1->setEnabled(false);
                }
                else if(isJump)
                {
                    daysPageView->setCurrentPageIndex(1);
                }
            }
        }
        //记录当前页
        _currentIndex = page->getCurrentPageIndex();
        isPageRun = false;//运动结束
    }
}

void DailyView::setMoreUI(int year, int month, int selectDay_,bool isPage)
{
    if(!Panel_more)return;
    auto root = Panel_more->getNode("Panel_container");
    root->removeAllChildren();
    int week = DailyManager::getInstance()->CaculateWeekDay(year, month, 1);
    int days = DailyManager::getInstance()->getDays(year, month);
    int selectedDay = selectDay_;
    auto isVip = DATA_M->isVipNoAds();
    auto today = isVip?_maxday:_today;
    if (selectedDay == 0) {
        if ((_current.Year() == today.Year() && _current.Month() == today.Month())) {
            selectedDay = today.Day();//MAX(_today.Day(), _current.Day());
        }
        else if(_current.Year() == today.Year() && _current.Month() > today.Month())
        {
            selectedDay = 1;
        }
        else {
            selectedDay = days;
        }
    }

    if(isPage)
    {//更新page显示
        setPageUI(year, month,selectedDay);
    }
    
//    for (int i=0; i<days; i++) {
//        int idx = i+week;
//        int day = i+1;
//        Date date(year, month, day);
//        auto dailyNode = DailyNode::createLayerN(this, date,DailyNode::Type::month);
//        //auto mode = toString("1");
//        if (date > today) {
//            dailyNode->setState(DailyNode::State::Closed);
//        }
//        else {
//            bool complete = DailyManager::getInstance()->isDailyCompleted(date);
//            dailyNode->setState(complete?DailyNode::State::Completed:DailyNode::State::Open);
//        }
//        root->addChild(dailyNode);
//        dailyNode->setSelected(day == selectedDay);
//        int x = idx%7, y = TotalRow-ceil(idx/7);
//        dailyNode->setPosition(GetPosition(x, y));
//    }
    Panel_more->getNode<TextBMFont*>("BMFont_road4")->setString(toString(days));
    // 🏆
    Panel_more->getNode<Sprite*>("Sprite_iconTrophyDiamon")->setSpriteFrame(StringUtils::format("iconJiangBei_%02d.png", gouRound(_current.Month(), 4)));//无资源
    getNode<Text*>("Text_title_0")->setString(StringUtils::format("%d.%d",year, month));//Lang_2("100157", year, month)
    Panel_more->getNode<Text*>("Text_title2")->setString(Lang_2("100157", year, month));
}



bool DailyView::updateDate(Date date)
{
    auto isVip = DATA_M->isVipNoAds();
    auto today = isVip?_maxday:_today;
    //计算第三容器中的日期 是否大于当天
    if(date > today)
    {//大于超过当天
        return true;
    }
    else
    {
        auto dailyManager = DailyManager::getInstance();
        auto dayMax = dailyManager->getDays(date.Year(), date.Month());
        for(int i = 0;i < 4;++i)
        {
            auto day = date.Day()+i;
            if(day > dayMax&&date.Month() == today.Month())
            {//超过本月 超过当天
                //return true;
            }
            else
            {//没有超过本月
                Date tempDate(date.Year(),date.Month(),day);
                if(tempDate > today&&i==0)
                {//超过当天
                    return true;
                }
            }
        }
        if(date.Day()%4 == 0)
        {//如果是4
            //第三容器中元素没有大于当天 算出第四容器第一元素日期
            //求第四容器第一元素
            int day = date.Day();
            auto mDay = day%4;//13  余 1
            mDay = mDay==0?4:mDay;
            auto tempDay1 = day - mDay + 1;//是第二容器第一个元素 13
            
            auto day4 = dailyManager->getDays(date.Year() ,date.Month());
            int tempDay4 = 0;
            auto Month4 = 0;
            auto year4 = 0;
            if(tempDay1 + 4 > day4)
            {
                if(_current.Month() == 12)
                {
                    Month4 = 1;//月份归1
                    year4 = _current.Year()+1;//年份增1
                }
                else
                {
                    year4 = _current.Year();
                    Month4 = _current.Month() + 1;//月份增1
                }
                tempDay4 = 1;
            }
            else
            {
                year4 = _current.Year();
                Month4 = _current.Month();
                tempDay4 = tempDay1 + 4;
            }
            Date date4(year4,Month4,tempDay4);
            if(date4 > today)
            {//第四容器中第一元素大于当天
                return true;
            }
        }
        
    }
    return false;//没有超过当天
}

void DailyView::setMonthUI(int year, int month, int selectDay_)
{
    auto isVip = DATA_M->isVipNoAds();
    auto today = isVip?_maxday:_today;
    int days = DailyManager::getInstance()->getDays(year, month);
    int selectedDay = selectDay_;
    if (selectedDay == 0) {
        if (_current.Year() == _today.Year() && _current.Month() == _today.Month()) {
            selectedDay = MAX(_today.Day(), _current.Day());
        }
        else if(_current.Year() == _today.Year() && _current.Month() > _today.Month())
        {
            selectedDay = 1;
        }
        else {
            selectedDay = days;
        }
    }
    
    setMoreUI(year,month,selectDay_);
    
    auto root2 = pageView;

    root2->removeAllChildren();
    DailyNode* item = nullptr;
    //
    auto dailyManager = DailyManager::getInstance();
    int j = 0;
    int day = _current.Day();
    auto Month1 = 0;
    auto year1 = 0;
    auto tempDay1 = 0;
    auto dayMax1 = 0;
    
    Month1 = _current.Month();
    year1 = _current.Year();
    auto mDay = day%4;//13  余 1
    mDay = mDay==0?4:mDay;
    tempDay1 = day - mDay + 1;//是第二容器第一个元素 13
    dayMax1 = dailyManager->getDays(_current.Year(), _current.Month());
    
    //求第一容器第一元素
    int tempDay2 = 0;
    auto Month2 = 0;
    auto year2 = 0;
    int day2 = 0;
    auto dayMax2 = 0;
    
    
    //求第三容器第一元素
    auto day3 = dailyManager->getDays(_current.Year() ,_current.Month());
    int tempDay3 = 0;
    auto Month3 = 0;
    auto year3 = 0;
    auto dayMax3 = 0;
    //是否是年初
    bool isNianChu = false;
    
    if(_current.Year() == today.Year()&&(today.Month() != 1||(today.Month()==1&&today.Day() > 8)))
    {//不是年初
        pageItemNum = 3;
        if(tempDay1 == 1)
        {//算前面的q日期
            if(_current.Month() == 1)
            {
                year2 = _current.Year() - 1;
                Month2 = 12;
                day2 = dailyManager->getDays(year2,12);
            }
            else
            {
                year2 = _current.Year();
                Month2 = _current.Month() - 1;
                day2 = dailyManager->getDays(year2,Month2);
            }
            auto mDay = day2%4;//31  余 3   31-3
            mDay = mDay==0?4:mDay;
            tempDay2 = day2 - mDay + 1;//29
        }
        else
        {
            year2 = _current.Year();
            Month2 = _current.Month();
            tempDay2 = tempDay1 - 4;
        }
        dayMax2 = dailyManager->getDays(year2, Month2);
        
        if(tempDay1 + 4 > day3)
        {
            if(_current.Month() == 12)
            {
                Month3 = 1;//月份归1
                year3 = _current.Year()+1;//年份增1
            }
            else
            {
                year3 = _current.Year();
                Month3 = _current.Month() + 1;//月份增1
            }
            tempDay3 = 1;
        }
        else
        {
            year3 = _current.Year();
            Month3 = _current.Month();
            tempDay3 = tempDay1 + 4;
        }
        dayMax3 = dailyManager->getDays(year3, Month3);
        
        
        //计算第三容器中元素日期是否超过当天
        isUpdateDay = updateDate(Date(year3,Month3,tempDay3));
        if(isUpdateDay)
        {//超过了
            //顺位往后移动
            
            tempDay3 = tempDay1;
            dayMax3 = dayMax1;
            year3 = year1;
            Month3 = Month1;
            
            tempDay1 = tempDay2;
            dayMax1 = dayMax2;
            year1 = year2;
            Month1 = Month2;
            
            //计算第一容器中第一元素
            
            if(tempDay1 == 1)
            {//算前面的q日期
                if(_current.Month() == 1)
                {
                    year2 = _current.Year() - 1;
                    Month2 = 12;
                    day2 = dailyManager->getDays(year2,12);
                }
                else
                {
                    year2 = _current.Year();
                    Month2 = _current.Month() - 1;
                    day2 = dailyManager->getDays(year2,Month2);
                }
                auto mDay = day2%4;//31  余 3   31-3
                mDay = mDay==0?4:mDay;
                tempDay2 = day2 - mDay + 1;//29
            }
            else
            {//第二元素不是月初， 那第一元素月份等于第二元素月份
                year2 = _current.Year();
                Month2 = Month1;
                tempDay2 = tempDay1 - 4;
            }
            dayMax2 = dailyManager->getDays(year2, Month2);
        }
    }
    else if(_current.Year() == today.Year()&&(_current.Month() == 1&&_current.Day() < 5))
    {//是年初
        pageItemNum = 1;
        tempDay2 = tempDay1;
        Month2 = Month1;
        year2 = year1;
        dayMax2 = dayMax1;
        
        tempDay1 = tempDay2 + 4;
        Month1 = Month2;
        year1 = year2;
        dayMax1 = dayMax2;
        
        
        tempDay3 = tempDay1+4;
        Month3 = Month1;
        year3 = year1;
        dayMax3 = dayMax1;
        
        isNianChu = true;
    }
    else if(_current.Year() == today.Year()&&(_current.Month() == 1&&_current.Day() < 9))
    {//是年初
        pageItemNum = 2;
        tempDay2 = 1;
        Month2 = Month1;
        year2 = year1;
        dayMax2 = dayMax1;
        
        tempDay1 = tempDay2 + 4;
        Month1 = Month2;
        year1 = year2;
        dayMax1 = dayMax2;
        
        
        tempDay3 = tempDay1+4;
        Month3 = Month1;
        year3 = year1;
        dayMax3 = dayMax1;
    }
    
    
    while(j < pageItemNum)
    {
        int tempDay = 0;
        int dayMax = 0;
        if(j == 0)
        {
            tempDay = tempDay2;
            dayMax = dayMax2;
        }
        else if(j == 1)
        {
            dayMax = dayMax1;
            tempDay = tempDay1;
        }
        else if(j == 2)
        {
            tempDay = tempDay3;
            dayMax = dayMax3;
        }
        auto layout = Layout::create();
        layout->setContentSize(root2->getContentSize());
        for(int k = 0;k<4;++k)
        {
            int tempYear = 0;
            int tempMonth = 0;
            
            if(j == 0)
            {
                tempYear = year2;
                tempMonth = Month2;
            }
            else if(j == 1)
            {
                tempYear = year1;
                tempMonth = Month1;
            }
            else if(j == 2)
            {
                tempYear = year3;
                tempMonth = Month3;
            }
            int day = k+tempDay;
            
            Date date;
            if(day > dayMax)
            {//没有日期了
                date = Date(tempYear, tempMonth, dayMax);
            }
            else
            {
                date = Date(tempYear, tempMonth, day);
            }
            
//            auto dailyNode = DailyNode::createLayerN(this, date,DailyNode::Type::day);
//            //auto mode = toString("1");
//            if(day > dayMax)
//            {//没有日期了
//                dailyNode->setState(DailyNode::State::Closed);
//                dailyNode->setVisible(false);
//            }
//            else if (date > today) {
//                dailyNode->setState(DailyNode::State::Closed);
//            }
//            else {
//                bool complete = DailyManager::getInstance()->isDailyCompleted(date);
//                dailyNode->setState(complete?DailyNode::State::Completed:DailyNode::State::Open);
//            }
//            layout->addChild(dailyNode,0,100);
//
//            dailyNode->setSelected(day == selectedDay);
//            if(day == selectedDay)
//            {
//                item = dailyNode;
//            }
//            dailyNode->setPosition(GetPosition(k));
        }
        root2->addPage(layout);
        j++;
    }
    if(pageItemNum == 2)
    {
        Button_hardRight->setEnabled(false);
    }
    else if(pageItemNum == 1)
    {
        Button_hardLeft1->setEnabled(false);
        Button_hardRight->setEnabled(false);
    }
    if(isUpdateDay)
    {//超过了
        root2->setCurrentPageIndex(2);
        //Button_hardLeft1->setEnabled(true);
        Button_hardRight->setEnabled(false);
    }
    else if(isNianChu)
    {//左右按钮都禁用  禁止翻页
        pageView->setTouchEnabled(false);
        root2->setCurrentPageIndex(0);
        Button_hardLeft1->setEnabled(false);
        Button_hardRight->setEnabled(false);
    }
    else
    {
        root2->setCurrentPageIndex(1);
    }
    _currentIndex = pageView->getCurrentPageIndex();
//    for (int i=0; i<days; i++) {
//        int idx = i+week;
//        int day = i+1;
//        Date date(year, month, day);
//
//        auto dailyNode = DailyNode::createLayerN(this, date,DailyNode::Type::day);
//        auto mode = toString("1");
//        if (date > _today) {
//            dailyNode->setState(DailyNode::State::Closed);
//        }
//        else {
//            bool complete = DailyManager::getInstance()->isDailyCompleted(date);
//            dailyNode->setState(complete?DailyNode::State::Completed:DailyNode::State::Open);
//        }
//        root2->addChild(dailyNode);
//        dailyNode->setSelected(day == selectedDay);
//        if(day == selectedDay)
//        {
//            item = dailyNode;
//        }
//        dailyNode->setPosition(GetPosition(i));
//        //dailyNode->updateUI();
//    }
//
//    updataScrollPoi(item);
    getNode<Text*>("Text_title_0")->setString(StringUtils::format("%d.%d",year, month));//Lang_2("100157", year, month));
    //getNode<Text*>("Text_title2")->setString(Lang_2("100157", year, month));
    updateUI(days);
}



void DailyView::setPageUI(int year, int month, int selectDay_)
{//设置page到指定日期
    auto isVip = DATA_M->isVipNoAds();
    auto today = isVip?_maxday:_today;
    auto vec = pageView->getItems();
    int days = DailyManager::getInstance()->getDays(year, month);
    int selectedDay = selectDay_;
    if (selectedDay == 0) {
        if (_current.Year() == today.Year() && _current.Month() == today.Month()) {
            selectedDay = MAX(today.Day(), _current.Day());
        }
        else if(_current.Year() == today.Year() && _current.Month() > today.Month())
        {
            selectedDay = 1;
        }
        else {
            selectedDay = days;
        }
    }

    
    //计算q日期
    auto dailyManager = DailyManager::getInstance();
    auto dayMax = dailyManager->getDays(today.Year(), 12);
    auto dayMaxM = dayMax%4;//13  余 1
    dayMaxM = dayMaxM==0?4:dayMaxM;
    auto tempDayMax = dayMax - dayMaxM + 1;//计算最后一天时 第三容器第一元素
    
    
    Date dateA(year,month,selectedDay);
    _current2 = dateA;
    //第二容器第一元素
    int tempDay1 = 0;
    auto Month1 = month;
    auto year1 = year;
    int day1 = 0;
    int dayMax1 = dailyManager->getDays(dateA.Year(), dateA.Month());
    
    //求第一容器第一元素
    int tempDay2 = 0;
    auto Month2 = 0;
    auto year2 = 0;
    int day2 = 0;
    int dayMax2 = 0;
    
    //求第三容器第一元素
    auto day3 = dailyManager->getDays(dateA.Year() ,dateA.Month());
    auto mDay3 = day3%4;
    mDay3 = mDay3==0?4:mDay3;
    int tempDay3 = day3 - mDay3 + 1;
    auto Month3 = 0;
    auto year3 = 0;
    auto dayMax3 = 0;
    //被选中的日期是年初
    bool isNianChu = false;
    
    if(pageItemNum == 1)
    {
        dateA;
        //
        tempDay2 = 1;
        Month2 = Month1;
        year2 = year1;
        dayMax2 = dayMax1;
        
        tempDay1 = tempDay2 + 4;
        Month1 = Month2;
        year1 = year2;
        dayMax1 = dayMax2;
        
        
        tempDay3 = tempDay1+4;
        Month3 = Month1;
        year3 = year1;
        dayMax3 = dayMax1;
    }
    else if(pageItemNum == 2)
    {
        dateA;
        //
        tempDay2 = 1;
        Month2 = Month1;
        year2 = year1;
        dayMax2 = dayMax1;
        
        tempDay1 = tempDay2 + 4;
        Month1 = Month2;
        year1 = year2;
        dayMax1 = dayMax2;
        
        
        tempDay3 = tempDay1+4;
        Month3 = Month1;
        year3 = year1;
        dayMax3 = dayMax1;
    }
    else
    {
        if(month == 1&&selectDay_<=4)
        {//限制右移
            isNianChu = true;
            Button_hardLeft1->setEnabled(false);
            pageView->scrollToPage(0);
            tempDay2 = 1;
            Month2 = 1;
            year2 = today.Year();
            day2 = 0;
            dayMax2 = dailyManager->getDays(year2 ,Month2);
            
            tempDay1 = tempDay2+4;
            Month1 = Month2;
            year1 = year2;
            day1 = 0;
            dayMax1 = dayMax2;
            
            tempDay3 = tempDay1 + 4;
            Month3 = Month2;
            year3 = year2;
            dayMax3 = dayMax2;
        }
        else if(month == 12&&selectDay_ >= tempDayMax)
        {//限制左移
            Button_hardRight->setEnabled(false);
            pageView->scrollToPage(2);
            tempDay3 = tempDayMax;
            Month3 = 12;
            year3 = today.Year();
            dayMax3 = dailyManager->getDays(year3 ,Month3);
            
            tempDay2 = tempDayMax - 4;
            Month2 = Month3;
            year2 = year3;
            day2 = 0;
            dayMax2 = dayMax3;
            
            tempDay1 = tempDay2-4;
            Month1 = Month2;
            year1 = year2;
            day1 = 0;
            dayMax1 = dayMax2;
        }
        else
        {
            Button_hardLeft1->setEnabled(true);
            Button_hardRight->setEnabled(true);
            Month1 = month;
            year1 = year;
            day1 = dateA.Day();
            auto mDay1 = day1%4;//13  余 1
            mDay1 = mDay1==0?4:mDay1;
            tempDay1 = day1 - mDay1 + 1;//是第二容器第一个元素 13
            dayMax1 = dailyManager->getDays(dateA.Year(), dateA.Month());
            
            if(tempDay1 == 1)
            {//算前面的q日期
                if(dateA.Month() == 1)
                {
                    year2 = dateA.Year() - 1;
                    Month2 = 12;
                    day2 = dailyManager->getDays(year2,12);
                }
                else
                {
                    year2 = dateA.Year();
                    Month2 = dateA.Month() - 1;
                    day2 = dailyManager->getDays(year2,Month2);
                }
                auto mDay = day2%4;//31  余 3   31-3
                mDay = mDay==0?4:mDay;
                tempDay2 = day2 - mDay + 1;//29
            }
            else
            {
                year2 = dateA.Year();
                Month2 = dateA.Month();
                tempDay2 = tempDay1 - 4;
            }
            dayMax2 = dailyManager->getDays(year2, Month2);
            if(tempDay1 + 4 > day3)
            {
                if(dateA.Month() == 12)
                {
                    Month3 = 1;//月份归1
                    year3 = dateA.Year()+1;//年份增1
                }
                else
                {
                    year3 = dateA.Year();
                    Month3 = dateA.Month() + 1;//月份增1
                }
                tempDay3 = 1;
            }
            else
            {
                year3 = dateA.Year();
                Month3 = dateA.Month();
                tempDay3 = tempDay1 + 4;
            }
            dayMax3 = dailyManager->getDays(year3, Month3);
            
            isUpdateDay = updateDate(Date(year3,Month3,tempDay3));
            if(isUpdateDay)
            {//超过了
                //顺位往后移动
                
                tempDay3 = tempDay1;
                dayMax3 = dayMax1;
                year3 = year1;
                Month3 = Month1;
                
                tempDay1 = tempDay2;
                dayMax1 = dayMax2;
                year1 = year2;
                Month1 = Month2;
                
                //计算第一容器中第一元素
                
                if(tempDay1 == 1)
                {//算前面的q日期
                    if(_current.Month() == 1)
                    {
                        year2 = _current.Year() - 1;
                        Month2 = 12;
                        day2 = dailyManager->getDays(year2,12);
                    }
                    else
                    {
                        year2 = _current.Year();
                        Month2 = _current.Month() - 1;
                        day2 = dailyManager->getDays(year2,Month2);
                    }
                    auto mDay = day2%4;//31  余 3   31-3
                    mDay = mDay==0?4:mDay;
                    tempDay2 = day2 - mDay + 1;//29
                }
                else
                {//第二元素不是月初， 那第一元素月份等于第二元素月份
                    year2 = _current.Year();
                    Month2 = Month1;
                    tempDay2 = tempDay1 - 4;
                }
                dayMax2 = dailyManager->getDays(year2, Month2);
            }
        }
    }
    
    
    
    
    
    int j = 0;
    while (j<pageItemNum) {
        auto item = vec.at(j);
        auto itemVec = item->getChildren();
        int tempDay = 0;
        int dayMax = 0;
        if(j == 0)
        {
            tempDay = tempDay2;
            dayMax = dayMax2;
        }
        else if(j == 1)
        {
            dayMax = dayMax1;
            tempDay = tempDay1;
        }
        else if(j == 2)
        {
            tempDay = tempDay3;
            dayMax = dayMax3;
        }
        for(int k = 0;k<itemVec.size();++k)
        {
            auto node = itemVec.at(k);
            int tempYear = 0;
            int tempMonth = 0;
            
            if(j == 0)
            {
                tempYear = year2;
                tempMonth = Month2;
            }
            else if(j == 1)
            {
                tempYear = year1;
                tempMonth = Month1;
            }
            else if(j == 2)
            {
                tempYear = year3;
                tempMonth = Month3;
            }
            int day = k+tempDay;
            auto dailyNode = dynamic_cast<DailyNode*>(node);
            if(day > dayMax)
            {
                dailyNode->setVisible(false);
            }
            else
            {
                dailyNode->setVisible(true);
                Date date(tempYear, tempMonth, day);
                dailyNode->setDate(date);
                if(k == 0&&j==2)
                {
                    //getEventDispatcher()->dispatchCustomEvent("msg_daily_node", (void*)dailyNode2);
                }
                if (date > today) {
                    dailyNode->setState(DailyNode::State::Closed);
                }
                else {
                    bool complete = DailyManager::getInstance()->isDailyCompleted(date);
                    dailyNode->setState(complete?DailyNode::State::Completed:DailyNode::State::Open);
                    //dailyNode->setSelected(k == 0&&j==1);
                    dailyNode->setSelected(false);
                    dailyNode->setSelected(date == dateA);
                    
                }
            }
        }
        j++;
    }
    
    
    if(isUpdateDay)
    {//超过了
        //Button_hardLeft1->setEnabled(true);
        Button_hardRight->setEnabled(false);
        pageView->setCurrentPageIndex(2);
    }
    else if(pageItemNum <= 2)
    {
        if(dateA.Day() < 5)
        {
            pageView->setCurrentPageIndex(0);
            Button_hardLeft1->setEnabled(false);
            Button_hardRight->setEnabled(true);
        }
        else
        {
            pageView->setCurrentPageIndex(1);
            Button_hardLeft1->setEnabled(true);
            Button_hardRight->setEnabled(false);
        }
    }
    else
    {
        if(month == 1&&selectDay_<=4)
        {//限制右移
            pageView->setCurrentPageIndex(0);
        }
        else if(month == 12&&selectDay_>=29)
        {
            pageView->setCurrentPageIndex(2);
        }
        else
        {
            pageView->setCurrentPageIndex(1);
        }
        
    }
    //记录当前页
    _currentIndex = pageView->getCurrentPageIndex();
    
    getNode<Text*>("Text_title_0")->setString(StringUtils::format("%d.%d",year, month));//Lang_2("100157", year, month));
    //getNode<Text*>("Text_title2")->setString(Lang_2("100157", year, month));
    
    // 🏆的影子
    auto monthCompleteCNT = DailyManager::getInstance()->getMonthCompleteCNT(_current);
    auto trophyName = getTrophyShadow(monthCompleteCNT, days);
    getNode<Sprite*>("Trophylight")->setSpriteFrame(trophyName);//无资源
    updateUI(days);
    
    
}

std::string DailyView::getTrophyShadow(int monthCompleteCNT, int days)
{
    if (monthCompleteCNT == days) {
        return StringUtils::format("JiangBeilight_%d.png",gouRound(_current.Month(), 4));
        
    }
    else if (monthCompleteCNT>=21) {
        return "JiangBeilight_1.png";
    }
    else if (monthCompleteCNT>=14) {
        return "JiangBeilight_1.png";
    }
    else if (monthCompleteCNT>=7) {
        return "JiangBeilight_1.png";
    }
    return "JiangBeilight_1.png";
}

std::string DailyView::getTrophy(int monthCompleteCNT, int days)
{
    if (monthCompleteCNT == days) {
        return StringUtils::format("JiangBei_%d.png", gouRound(_current.Month(), 4));
    }
    else if (monthCompleteCNT>=21) {
        return "JiangBei_102.png";
    }
    else if (monthCompleteCNT>=14) {
        return "JiangBei_101.png";
    }
    else if (monthCompleteCNT>=7) {
        return "JiangBei_100.png";
    }
    return "JiangBei_100.png";
}

void DailyView::initData() {
    BaseLayer::initData();
    setName("DailyView");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("challenge.plist");
    EVENT_M->addListener("event_home_updateui", [this](ValueMap valueMap, void *obj){
        this->updateUI();
    },this);
//    addEvent("event_home_updateui", [this](EventCustom *){
//        this->updateUI();
//    });
    
    DATA_M->hasRedPoint(true, DataManager::GameType::Daily); // z重置时间
}

void DailyView::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    
    if(dynamic_cast<Button*>(btn))
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
    }
    
    auto btnName = btn->getName();
//    if (dynamic_cast<Layout*>(pSender) == nullptr)
//        SOUND_M->playBtnClickAudio();
    if (btnName == "btn_close") {
        this->removeFromParent();
    }
    else if (btnName == "Button_left") {
        if(_current.Month() == 1)return;
        _current.PreMonth();
        
        setMoreUI(_current.Year(), _current.Month(),0,true);
//        showCompleteAni();
    }
    else if (btnName == "Button_right") {
        if(_current.Month() == 12)return;
        _current.NextMonth();
        setMoreUI(_current.Year(), _current.Month(),0,true);
    }
    else if (btnName == "Button_start") {
        //SCENE_M->getGameView()->startDaily("");
        //this->removeFromParent();
        showStart();
    }
    else if (btnName == "btn_dailyclose"||btnName == "Panel_out") {
        FileNode_start->setVisible(false);
    }
    else if (btnName == "Button_get") {
        FileNode_start->setVisible(false);
        showCompleteAni();
    }
    else if (btnName == "btn_help") {
        GuideView::showGuid(GuideView::GuideType::DailyTeach,_current);
    }
    else if (btnName.find("Button_start") != string::npos) {
        if (_selectedNode) {
            getNode("Panel_more")->setVisible(false);
            SCENE_M->getGameView()->gamePause(true);
            SCENE_M->getGameView()->setVisible(true);
            auto date = _selectedNode->getDate();
            int dayofyear = date.DayOfYear();
            string num{btnName.back()};
            auto deck = DailyManager::getInstance()->getDeckByDay(dayofyear, num);
            DailyManager::getInstance()->setCurrentDaily(date, num);
            SCENE_M->getGameView()->startDaily(deck, num);
            //
            getNode("FileNode_start")->setVisible(false);
            if(_lobby)
            {
                _lobby->setVisible(false);
            }
            else
            {
                this->removeFromParent();
            }
            
            UIUtils::FIRFirestoreAdd("operator", {
                {"key", Value("daily_start")},
                {"value", Value(date.name())}
            });
        }
    }
    else if(btnName == "Button_57")
    {
//        if(!Panel_more)
//        {
//            Panel_more = DailyMoreView::createLayerN(this,&_current2);
//            SCENE_M->addDialog(Panel_more,false,2);
//        }
//        Panel_more->playAni("Start0", false);
//        Panel_more->setVisible(true);
//        Panel_more->updateUI(_current);
//        setMoreUI(_current2.Year(),_current2.Month(),_current2.Day());
    }
    else if(btnName == "Button_58")
    {
        getNode("Panel_more")->setVisible(false);
        //_actionManager->play("start", false);
    }
    else if(btnName == "Button_hardLeft1")
    {//容器左移 移动五个
        if(!isPageRun)
        {
            isUpdatePage = false;
            if(!Button_hardRight->isEnabled())
            {//没有走回调// 更新
                isPageLeft = true;//防错，
                isUpdateDay = false;
                if(pageItemNum == 2)
                {
                    pageView->scrollToPage(0);
                }
                else
                {
                    pageView->scrollToPage(1);
                }
                
            }
            else
            {
                isJump = true;
                pageView->scrollToPage(0);
            }
            
            Button_hardRight->setEnabled(true);
            isPageRun = true;
            pageView->setEnabled(false);
        }
        
    }
    else if(btnName == "Button_hardRight")
    {//容器右移

        if(!isPageRun)
        {
            isUpdatePage = false;
            isPageRight_2 = true;
            if(!Button_hardLeft1->isEnabled())
            {//没有走回调// 更新
                isPageRight = true;//防错，
                pageView->scrollToPage(1);
            }
            else
            {
                isJump = true;
                pageView->scrollToPage(2);
            }
            Button_hardLeft1->setEnabled(true);
            isPageRun = true;
            pageView->setEnabled(false);
        }
    }
    else if(btnName == "Button_toDay")
    {//更新日期 到当天
        setToDay();
    }
}
void DailyView::showStart()
{
//    if(!FileNode_start)
//    {
//        FileNode_start = DailyGameView::createLayerN(_selectedNode,this);//getNode("FileNode_start");//null
//        SCENE_M->addDialog(FileNode_start,false,3);
//    }
//    showSelectDialog();
}

void DailyView::hideMore()
{
    if(Panel_more)
    Panel_more->setVisible(false);
}
/*
 Crown_up1 是皇冠+宝石
 Trophy_1 奖杯
 Crown_1 皇冠
 */
void DailyView::showCompleteAni()
{
    //切换月份时更新此值
    _monthCompleteCNT = DailyManager::getInstance()->getMonthCompleteCNT(_current);
    _monthPlayCNT = DailyManager::getInstance()->getMonthPlayCNT(_current);
    auto cnt = DailyManager::getInstance()->getCompleteCNT(_current);
    int days = DailyManager::getInstance()->getDays(_current.Year(), _current.Month());
    cocostudio::timeline::ActionTimeline *actionManager = nullptr;
    getNode("Node_CrownNo")->setVisible(false);
    SCENE_M->lockScreen([this](Ref*){
        
        //都不跳过
        return;
        //如果是奖杯动画不跳过 条件不可以
        if(!FileNode_crown->isVisible())return;
        aniEventCB(false);
        completeCB();
        UIUtils::playInnerAction(FileNode_crown, "idle", false);
        UIUtils::playInnerAction(FileNode_trophy, "idle", false);
        if (_effectID != -1) {
            SOUND_M->stopEffectMusic(_effectID);
            _effectID = -1;
        }
        SCENE_M->unlockScreen();
    });
    
    
    
    // 更新🏆的影子
    auto monthCompleteCNT = DailyManager::getInstance()->getMonthCompleteCNT(_current);
    auto trophyName = getTrophyShadow(monthCompleteCNT, days);
    getNode<Sprite*>("Trophylight")->setSpriteFrame(trophyName);//无资源
    //updateUI(days);
    
    
    if (_tag == 2) {   // 获得🏆
        FileNode_trophy->setVisible(true);
        FileNode_crown->setVisible(false);
        _effectID = SOUND_M->playEffectMusic(EffectThrophy);
        actionManager = UIUtils::playInnerAction(FileNode_trophy, _monthCompleteCNT > 7?"up":"start0", false);
        if(_monthCompleteCNT == 7)
        {
            //累计铜奖杯任务数 新手
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::BRONZEREWARD);
        }
    }
    else if (cnt == 1 && _monthCompleteCNT > 7 && (_monthCompleteCNT==14||_monthCompleteCNT==21||_monthCompleteCNT==days)) { // 🏆升级
        //        actionManager = UIUtils::playInnerAction(FileNode_trophy, "up", false);
        if(_monthCompleteCNT == 14)
        {
            //累计银奖杯任务数 新手
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::SILVERAWARD);
        }
        else if(_monthCompleteCNT == 21)
        {
            //累计金奖杯任务数 新手
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::GOLDAWARD);
        }
        else if(_monthCompleteCNT == days)
        {
            //累计钻石奖杯任务数 新手
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::DIAMONDAWARD);
        }
        
        _tag = 2;
        SCENE_M->unlockScreen();
        showSelectDialog(true, 2);
    }
    else if (_monthCompleteCNT > 7 || FileNode_trophy->isVisible()) {   // 没升级 隐藏🏆先
        UIUtils::playInnerAction(FileNode_trophy, "out", false, [this, cnt](){
            FileNode_crown->setVisible(true);
            getNode("Node_CrownWin")->setVisible(true);
            _effectID = SOUND_M->playEffectMusic(cnt == 1?EffectCrown:EffectCrownUp);
            UIUtils::removeLastFrameFunc(FileNode_trophy);
            UIUtils::playInnerAction(FileNode_crown, cnt == 1?"start1":"start", false, [this](){
                FileNode_crown->setVisible(false);
                UIUtils::playInnerAction(FileNode_trophy, "start1", false);
                UIUtils::removeLastFrameFunc(FileNode_crown);//防错
            })->setFrameEventCallFunc([this](Frame *frame){
                auto eventFrame = (EventFrame*)frame;
                if (eventFrame->getEvent() == "event_crownupdate")
                {
                    aniEventCB();
                    completeCB();
                }
            });
        });
    }
    else if (cnt == 1) { // 第一次完成 从问好变过来
        getNode("Node_CrownWin")->setVisible(true);
        _effectID = SOUND_M->playEffectMusic(EffectCrown);
        actionManager = UIUtils::playInnerAction(FileNode_crown, "start1", false, CC_CALLBACK_0(DailyView::crownComplete, this)); //, CC_CALLBACK_0(DailyView::completeCB, this));
    }
    else {  // 加宝石
        
        FileNode_trophy->setVisible(false);
        FileNode_crown->setVisible(true);
        _effectID = SOUND_M->playEffectMusic(EffectCrownUp);
        actionManager = UIUtils::playInnerAction(FileNode_crown, "start", false, CC_CALLBACK_0(DailyView::crownComplete, this)); //, CC_CALLBACK_0(DailyView::completeCB, this));
    }
    if (actionManager) {
        actionManager->setFrameEventCallFunc([this](Frame *frame){
            auto eventFrame = (EventFrame*)frame;
            if (eventFrame->getEvent() == "event_crownupdate")
            {
                aniEventCB();
                completeCB();
            }
        });
    }
}
void DailyView::clearFileNodeStart()
{
    FileNode_start = nullptr;
}
void DailyView::clearPanelMoret()
{
    Panel_more = nullptr;
}
void DailyView::showSelectDialog(bool isCompletedView, int tag)
{
//    if(!FileNode_start)
//    {
//        FileNode_start = DailyGameView::createLayerN(_selectedNode,this);//getNode("FileNode_start");//null
//        SCENE_M->addDialog(FileNode_start,false,3);
//    }
    
    _tag = tag;
    FileNode_start->setVisible(true);
    FileNode_start->setDailyNode(_selectedNode);
    //再次进来的时候 没有动画了
    FileNode_start->playAni( _tag==1?"start":"start0", false);
//    UIUtils::playInnerAction(FileNode_start, _tag==1?"start":"start0", false);
    FileNode_start->getNode("panel_set")->setVisible(!isCompletedView);
    FileNode_start->getNode("panel_dailyget")->setVisible(isCompletedView);
    FileNode_start->getNode("Crown_100")->setVisible(tag == 1);
    FileNode_start->getNode("Trophy_100")->setVisible(tag == 2);
    FileNode_start->getNode<Text*>("Text_rewardTitle")->setString(Lang("100152"));
    if (isCompletedView) {  // 结束逻辑
        if (tag == 1) {
            auto cnt = DailyManager::getInstance()->getCompleteCNT(_current);
            for (int i=1; i<=3; i++) {
                if (i==1) {
                    FileNode_start->getNode(StringUtils::format("Node_gemd%d", i))->setVisible(cnt>1);
                }
                else {
                    FileNode_start->getNode(StringUtils::format("Node_gemd%d", i))->setVisible(cnt>=3);
                }
            }
            FileNode_start->getNode<Text*>("Text_getCrownContent")->setString(Lang("100174"));
        }
        else if (tag == 2) {
            auto monthCompleteCNT = DailyManager::getInstance()->getMonthCompleteCNT(_current);
            int days = DailyManager::getInstance()->getDays(_current.Year(), _current.Month());
            FileNode_start->getNode<Sprite*>("Trophy_100")->setSpriteFrame(getTrophy(monthCompleteCNT, days));
            FileNode_start->getNode<Text*>("Text_getCrownContent")->setString(Lang("100175"));
        }
    }
    else if (_selectedNode) {
        //FileNode_start->updateUI();
        auto date = _selectedNode->getDate();
        for (int i=1; i<=4; ++i) {
            bool complete = DailyManager::getInstance()->isDailyCompleted(date, toString(i));
            string btnImgName0 = complete?"btn_blue0.png":"btn_gre0.png";
            string btnImgName1 = complete?"btn_blue1.png":"btn_gre1.png";
//            getNode(StringUtils::format("Sprite_cown%d", i))->setVisible(complete);
//            getNode<Button*>(StringUtils::format("Button_start%d", i))->setEnabled(!complete);
            auto btnStart = FileNode_start->getNode<Button*>(StringUtils::format("Button_start%d", i));
            btnStart->loadTextures(btnImgName0, btnImgName1, btnImgName0, Widget::TextureResType::PLIST);
            auto Text_Name = btnStart->getChildByName<Text*>("Text_Name");
            Text_Name->setString(complete?Lang("100149"):Lang("100150"));
            UIUtils::textAdaptiveSize(Text_Name, 230);
            if (i!=4) {
                FileNode_start->getNode<Text*>(StringUtils::format("Text_rewardTitle%d", i))->setString(Lang(complete?"100151":"100152"));
            }
            FileNode_start->getNode(StringUtils::format("Level_win%d", i))->setVisible(complete);
//            if (i>=3) {
//                complete = DailyManager::getInstance()->isDailyCompleted(date, toString(4));
//                auto btnStart4 = getNode<Button*>(StringUtils::format("Button_start%d", 4));
//                btnStart4->loadTextures(btnImgName0, btnImgName1, btnImgName0, Widget::TextureResType::PLIST);
//                btnStart4->getChildByName<Text*>("Text_Name")->setString(complete?Lang("100149"):Lang("100150"));
//                //                getNode<Text*>(StringUtils::format("Text_rewardTitle%d", 4))->setString(Lang(complete?"100151":"100152"));
//                getNode(StringUtils::format("Level_win%d", 4))->setVisible(complete);
//            }
        }
        auto cnt = DailyManager::getInstance()->getCompleteCNT(date);
        FileNode_start->getNode<LoadingBar*>("LoadingBar_rewardPercent")->setPercent(cnt/3.0f * 100);
    }
}

DailyView::DailyView(MainLobby* lobby)
:BaseLayer("2020HomeView_Daily.csb")
,_lobby(lobby)
,FileNode_start(nullptr)
,_currentIndex(-1)
{
}

DailyView::~DailyView() {

}

void DailyView::setCurrentSelectNode(DailyNode *selectNode) {
    if (_selectedNode != selectNode||1) {
        _selectedNode = selectNode;
        updateUI();
    }
}

float DailyView::getPercent(int current, int days)
{
//    return days/31.0f*current/days * 100;
    return current*1.0f/days * 100;
}

void DailyView::updateUI(int days, bool isComplete) {
    bool isQieHuan = false;
    if(_selectedNode)
    {//更新more信息
        _current2 = _selectedNode->getDate();
        if(_current2.Month()!=_current.Month())
        {//切换月份
            _monthCompleteCNT = DailyManager::getInstance()->getMonthCompleteCNT(_current2);
            isQieHuan = true;
        }
        _current = _current2;
    }
    
    
    auto dailyManager = DailyManager::getInstance();
    auto monthCompleteCNT = dailyManager->getMonthCompleteCNT(_current);
    int dayMax = DailyManager::getInstance()->getDays(_current.Year(), _current.Month());
    auto diamonCNT = dailyManager->getMonthDiamondCNT(_current);
    getNode("Image_diamondBG")->setVisible(diamonCNT>0);
    getNode<Text*>("Text_total1")->setString(toString(monthCompleteCNT));
    getNode<Text*>("Text_total1_0")->setString(toString(monthCompleteCNT));
    getNode<Text*>("Text_total2")->setString(toString(dayMax));
    if (days != 0||isQieHuan) {
        
        days = DailyManager::getInstance()->getDays(_current.Year(), _current.Month());
        //auto subMonth = _today.subMonth(_current);
        //getNode<Button*>("Button_right")->setEnabled(subMonth != 0);//null
        //getNode<Button*>("Button_left")->setEnabled(_current.Month() != 1);//null
        
        // 百分比逻辑
//        getNode<LoadingBar*>("LoadingBar_percent")->setPercent();
        auto percent = getPercent(monthCompleteCNT, days);
        if(Panel_more)
            Panel_more->runProgress(0.2f, percent);
        getNode<Sprite*>("Sprite_trophy")->setSpriteFrame(getTrophy(monthCompleteCNT, days));//无资源
        
        getNode<Text*>("Text_diamond")->setString(StringUtils::format("x%d", diamonCNT));
    }
    
    auto selectDate = _selectedNode->getDate();
    auto cnt = DailyManager::getInstance()->getCompleteCNT(selectDate);
    for (int i=1; i<=3; i++) {
        if (i==1) {
//            getNode(StringUtils::format("Node_diamond%d", i))->setVisible(cnt>1);//null
            getNode(StringUtils::format("Node_crownGem%d", i))->setVisible(cnt>1);//null
        }
        else {
//            getNode(StringUtils::format("Node_diamond%d", i))->setVisible(cnt>=3);//null
            getNode(StringUtils::format("Node_crownGem%d", i))->setVisible(cnt>=3);//null
        }
    }
    //auto sp = Sprite::create("ui_Crownicon1.png");
    //getNode<ImageView*>("Image_crownicon")->loadTexture(cnt>0?"ui_beijingicon1.png":"ui_beijingicon0.png", TextureResType::PLIST);//无资源//null
    //getNode<Text*>("Text_show")->setString(cnt>=1?Lang("100152"):Lang("100151"));//null
    //getNode<Text*>("Text_date")->setString(selectDate.name());//null

    if (!isComplete) {
        if (monthCompleteCNT>=7) {
            FileNode_trophy->setVisible(true);
            FileNode_crown->setVisible(false);
        }
        else {
            FileNode_trophy->setVisible(false);
            FileNode_crown->setVisible(true);
            getNode("Node_CrownNo")->setVisible(cnt==0);
            getNode("Node_CrownWin")->setVisible(cnt>0);
            if (cnt==0) {
                UIUtils::playInnerAction(FileNode_crown, "loop1", true);
            }
            else {
                UIUtils::playInnerAction(FileNode_crown, "loop", true);
            }
        }
    }
    getNode<Text*>("Text_title_0")->setString(StringUtils::format("%d.%d",_current.Year(), _current.Month()));//Lang_2("100157", _current.Year(), _current.Month()));
}

DailyView* DailyView::showComplete() {
    _current = DailyManager::getInstance()->getCurrentDate();
    //ceshi
//    setMonthUI(_current.Year(), _current.Month(), _current.Day());
    bool firstComplete = DailyManager::getInstance()->complete();
//    auto cnt = DailyManager::getInstance()->getCompleteCNT(_current);
    if (firstComplete) {
        showSelectDialog(true);
    }
    return this;
}

void DailyView::onEnter() {
    BaseLayer::onEnter();
    playAni("In",false);
    updateUI();
    UIUtils::FIRAnalyticsEventWithPrefix("DailyView");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    AdsManager::setBannerVisible(false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    DATA_M->showNativeAds(0);
#endif
}

void DailyView::onExit() {
    BaseLayer::onExit();
    playAni("Out",false);
    
    EVENT_M->removeListener("event_home_updateui",this);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    AdsManager::setBannerVisible(true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    DATA_M->hideNativeAds(0);
#endif
}

void DailyView::completeCB() {
    auto cb = [this]() {
        _selectedNode->showWin();
//        FileNode_trophy->setVisible(_monthCompleteCNT>=7);
//        FileNode_crown->setVisible(_monthCompleteCNT<7);
        SCENE_M->unlockScreen();
    };
    
    auto cnt = DailyManager::getInstance()->getCompleteCNT(_current);
    if (cnt==1 && _monthCompleteCNT==7 && _tag == 1) {
//        auto actionManager = UIUtils::playInnerAction(FileNode_trophy, "start0", false);
//        actionManager->setFrameEventCallFunc([this, cb](Frame *frame){
//            auto eventFrame = (EventFrame*)frame;
//            if (eventFrame->getEvent() == "event_crownupdate")
//            {
//                _current = DailyManager::getInstance()->getCurrentDate();
//                int days = DailyManager::getInstance()->getDays(_current.Year(), _current.Month());
//                updateUI(days, true);
//                cb();
//            }
//        });
        showSelectDialog(true, 2);
        SCENE_M->unlockScreen();
    }
    else {
        cb();
    }
    //            updateUI();
}

void DailyView::aniEventCB(bool completed) {
    auto cnt = DailyManager::getInstance()->getCompleteCNT(_current);
    if (_monthCompleteCNT!=7 || cnt!=1 || _tag == 2) {
        _current = DailyManager::getInstance()->getCurrentDate();
        int days = DailyManager::getInstance()->getDays(_current.Year(), _current.Month());
        updateUI(days, completed);
    }
}

void DailyView::crownComplete() {
    auto actionManager = UIUtils::playInnerAction(FileNode_crown, "loop", true);
    actionManager->setLastFrameCallFunc(nullptr);
}


void DailyView::updataScrollPoi(DailyNode* item)
{
    if(!item)return;
//    auto parent = item->getParent();
//    //滚动容器item定位
//    auto innerContainer = scrollView->getInnerContainer();
//    auto vec = parent->getChildren();
//    auto innervec = innerContainer->getChildren();
//    auto id = innervec.getIndex(item);
//    int idx = id%4;
//
//    if(parent != innerContainer)
//    {//找出对应的
//        auto innervec = innerContainer->getChildren();
//        if(vec.size()!=innervec.size())return;
//        auto id2 = vec.getIndex(item);
//        idx = id2%4;
//        item = static_cast<DailyNode*>(innervec.at(id2));
//    }
//    auto size = scrollView->getContentSize();
//    Vec2 acPoi = size*0.1;
//    acPoi = scrollView->convertToWorldSpace(acPoi);
//    acPoi = innerContainer->convertToNodeSpace(acPoi);
//    auto vecPoi = scrollView->getInnerContainerPosition();
//    auto nodePoi = item->getPosition();
//    float dx2 = 0;
//    for(int i = 0,j =0;i<5;++i,++j)
//    {
//        if(idx == j)
//        {
//            dx2 = i * itemWidth;
//        }
//    }
//    auto dx = acPoi.x-nodePoi.x + dx2;
//    vecPoi.x+=dx;
//    scrollView->setInnerContainerPosition(vecPoi);
}

void DailyView::updateDYY()
{
    //    getNode<LoadingBar*>("LoadingBar_percent")->setPercent(0);
        
        //getNode("panel_dailyget")->setVisible(false);//null
        //getNode<Text*>("Text_notify")->setString(Lang("100164"));//null
        getNode<Text*>("Text_start")->setString(Lang("100150"));//null new
        getNode<Text*>("Text_uncomplete")->setString(Lang("100151"));
    auto Text_ti1 = getNode<Text*>("Text_ti1");
    Text_ti1->setString(Lang("100289"));
    
    UIUtils::textAdaptiveSize(Text_ti1,140);
    if(Panel_more)
    {
        Panel_more->updateDYY();
    }
    
    auto items = pageView->getItems();
    
    for(auto item:items)
    {//
        auto vec = item->getChildren();
        for(auto node:vec)
        {
            auto dailyNode = dynamic_cast<DailyNode*>(node);
            if(dailyNode)
            {
                dailyNode->updateDYY();
            }
        }
    }
    
    //
        ////null
        ////null
    //    UIUtils::playInnerAction(FileNode_crown, "loop", true);
        UIUtils::playInnerAction(FileNode_trophy, "idle", false);
        
    //    for (auto name:Skeletons) {
    //        auto skeletonNode = spine::SkeletonAnimation::createWithJsonFile("res/flag.json", "res/flag.atlas", 1.f);
    //        getNode(StringUtils::format("Node_%s", name.c_str()))->addChild(skeletonNode);
    //        skeletonNode->setAnimation(0, name, true);
    //    }//null
        
        
    
    if(FileNode_start)
    {
        FileNode_start->updateDYY();
        
    }
        
}

Date DailyView::getSelectedNode()
{
    auto isVip = DATA_M->isVipNoAds();
    auto today = isVip?_maxday:_today;
    return today;
}

void DailyView::hideStart()
{
    //getNode("Panel_more")->setVisible(false);
    //FileNode_start->setVisible(false);
}


void DailyView::updatePage(PageView* page)
{
    isUpdatePage = true;
    isPageRun = true;
    isPageLeft = false;
    isPageRight = false;
    isPageRight_2 = false;
    isToDay = false;
    auto id = page->getCurrentPageIndex();//setCurrentPageIndex
    if(id == 1)
    {
        auto vec = page->getItems();
        auto item = vec.at(id);
        auto itemVec = item->getChildren();
        auto dailyNode0 = dynamic_cast<DailyNode*>(itemVec.at(0));
        auto date = dailyNode0->getDate();
        if(pageItemNum == 2)
        {
            isUpdateDay = updateDate(date);
        }
        else
        {
            isUpdateDay = false;
        }
        for(auto item:vec)
        {
            auto itemVec = item->getChildren();
            for(auto node:itemVec)
            {
                auto dailyNode = dynamic_cast<DailyNode*>(node);
                dailyNode->setSelected(false);
                if(isToDay)
                {
                    auto date = dailyNode->getDate();
                    dailyNode->setSelected(date == _today);
                }
                else
                {
                    dailyNode->setSelected(dailyNode0 == dailyNode);
                }
                
            }
        }
        if(pageItemNum == 2)
        {
            Button_hardLeft1->setEnabled(true);
        }
        else
        {
            Button_hardLeft1->setEnabled(true);
            Button_hardRight->setEnabled(true);
        }
        getNode<Text*>("Text_title_0")->setString(StringUtils::format("%d.%d",date.Year(), date.Month()));//Lang_2("100157", date.Year(), date.Month()));
    }
    else
    {
        auto isVip = DATA_M->isVipNoAds();
        auto today = isVip?_maxday:_today;
        auto vec = page->getItems();
        auto item = vec.at(id);
        auto itemVec = item->getChildren();
        auto dailyNode = dynamic_cast<DailyNode*>(itemVec.at(0));
        
        auto dateA = dailyNode->getDate();
        
        auto dailyManager = DailyManager::getInstance();
        auto dayMax = dailyManager->getDays(_today.Year(), 12);
        auto dayMaxM = dayMax%4;//13  余 1
        dayMaxM = dayMaxM==0?4:dayMaxM;
        auto tempDayMax = dayMax - dayMaxM + 1;//是第二容器第一个元素 13
        
        if(dateA.Month() == 1&&dateA.Day() == 1)
        {//今年第一天
            Button_hardLeft1->setEnabled(false);
            Button_hardRight->setEnabled(true);
            for(auto item:vec)
            {//事件被拦截
                auto nodeVec = item->getChildren();
                for(auto node:nodeVec)
                {
                    auto dailyNode3 = dynamic_cast<DailyNode*>(node);
                    dailyNode3->setSelected(false);
                    dailyNode3->setSelected(dailyNode == dailyNode3);
                }
            }
            
            isJump = false;
            return;
        }
        else if(dateA.Month() == 12&&dateA.Day() == tempDayMax)
        {//今年最后一天
            Button_hardLeft1->setEnabled(true);
            Button_hardRight->setEnabled(false);
            for(auto item:vec)
            {//事件被拦截
                auto nodeVec = item->getChildren();
                for(auto node:nodeVec)
                {
                    auto dailyNode3 = dynamic_cast<DailyNode*>(node);
                    dailyNode3->setSelected(false);
                    dailyNode3->setSelected(dailyNode == dailyNode3);
                }
            }
            isJump = false;
            return;
        }
        else if(0)
        {//还没有开启天数 查询第三容器所有
            
        }
        else
        {//没有到边界
            Button_hardLeft1->setEnabled(true);
            Button_hardRight->setEnabled(true);
        }

        int day = dateA.Day();
        auto Month1 = dateA.Month();
        auto year1 = dateA.Year();
        auto mDay = day%4;//13  余 1
        mDay = mDay==0?4:mDay;
        auto tempDay1 = day - mDay + 1;//是第二容器第一个元素 13
        auto dayMax1 = dailyManager->getDays(dateA.Year(), dateA.Month());
        //求第一容器第一元素
        int tempDay2 = 0;
        auto Month2 = 0;
        auto year2 = 0;
        int day2 = 0;
        
        if(tempDay1 == 1)
        {//算前面的q日期
            if(dateA.Month() == 1)
            {
                year2 = dateA.Year() - 1;
                Month2 = 12;
                day2 = dailyManager->getDays(year2,12);
            }
            else
            {
                year2 = dateA.Year();
                Month2 = dateA.Month() - 1;
                day2 = dailyManager->getDays(year2,Month2);
            }
            auto mDay = day2%4;//31  余 3   31-3
            mDay = mDay==0?4:mDay;
            tempDay2 = day2 - mDay + 1;//29
        }
        else
        {
            year2 = dateA.Year();
            Month2 = dateA.Month();
            tempDay2 = tempDay1 - 4;
        }
        auto dayMax2 = dailyManager->getDays(year2, Month2);
        
        //求第三容器第一元素
        auto day3 = dailyManager->getDays(dateA.Year() ,dateA.Month());
        auto mDay3 = day3%4;
        mDay3 = mDay3==0?4:mDay3;
        int tempDay3 = day3 - mDay3 + 1;
        auto Month3 = 0;
        auto year3 = 0;
        if(tempDay1 + 4 > day3)
        {
            if(dateA.Month() == 12)
            {
                Month3 = 1;//月份归1
                year3 = dateA.Year()+1;//年份增1
            }
            else
            {
                year3 = dateA.Year();
                Month3 = dateA.Month() + 1;//月份增1
            }
            tempDay3 = 1;
        }
        else
        {
            year3 = dateA.Year();
            Month3 = dateA.Month();
            tempDay3 = tempDay1 + 4;
        }
        
        auto dayMax3 = dailyManager->getDays(year3, Month3);
        isUpdateDay = updateDate(Date(year3,Month3,tempDay3));
        auto item2 = vec.at(isUpdateDay?id:1);
        auto itemVec2 = item2->getChildren();
        auto node2 = itemVec2.at(0);
        auto dailyNode2 = dynamic_cast<DailyNode*>(node2);
        
        //计算第三容器中元素日期是否超过当天
        
        if(isUpdateDay)
        {//超过了
            //顺位往后移动
            
            tempDay3 = tempDay1;
            dayMax3 = dayMax1;
            year3 = year1;
            Month3 = Month1;
            
            tempDay1 = tempDay2;
            dayMax1 = dayMax2;
            year1 = year2;
            Month1 = Month2;
            
            //计算第一容器中第一元素
            
            if(tempDay1 == 1)
            {//算前面的q日期
                if(_current.Month() == 1)
                {
                    year2 = _current.Year() - 1;
                    Month2 = 12;
                    day2 = dailyManager->getDays(year2,12);
                }
                else
                {
                    year2 = _current.Year();
                    Month2 = _current.Month() - 1;
                    day2 = dailyManager->getDays(year2,Month2);
                }
                auto mDay = day2%4;//31  余 3   31-3
                mDay = mDay==0?4:mDay;
                tempDay2 = day2 - mDay + 1;//29
            }
            else
            {//第二元素不是月初， 那第一元素月份等于第二元素月份
                year2 = _current.Year();
                Month2 = Month1;
                tempDay2 = tempDay1 - 4;
            }
            dayMax2 = dailyManager->getDays(year2, Month2);
        }
        
        
        int j = 0;
        pageNum++;
        if(pageNum == 1)
        {//第一次进来更新 id1
            int tempDay = 0;
            int dayMax = 0;
            int tempYear = 0;
            int tempMonth = 0;
            
            tempYear = year1;
            tempMonth = Month1;
            dayMax = dayMax1;
            tempDay = tempDay1;
            //更新当前日期
            _current2 = Date(tempYear,tempMonth,tempDay);
            
            auto item = vec.at(1);
            auto itemVec = item->getChildren();
            for(int k = 0;k<itemVec.size();++k)
            {
                auto node = itemVec.at(k);
                
                auto dailyNode = dynamic_cast<DailyNode*>(node);
                int day = k+tempDay;
                if(day > dayMax)
                {
                    dailyNode->setVisible(false);
                }
                else
                {
                    dailyNode->setVisible(true);
                    Date date(tempYear, tempMonth, day);
                    dailyNode->setDate(date);
                    if (date > today) {
                        dailyNode->setState(DailyNode::State::Closed);
                    }
                    else {
                        bool complete = DailyManager::getInstance()->isDailyCompleted(date);
                        dailyNode->setState(complete?DailyNode::State::Completed:DailyNode::State::Open);
                        //dailyNode->setSelected(false);
                        if(k == 0&&pageNum==1)
                        {
                            for(auto item:vec)
                            {//事件被拦截
                                auto nodeVec = item->getChildren();
                                for(auto node:nodeVec)
                                {
                                    auto dailyNode3 = dynamic_cast<DailyNode*>(node);
                                    dailyNode3->setSelected(false);
                                    dailyNode3->setSelected(dailyNode2 == dailyNode3);
                                }
                            }
                        }
                    }
                }
            }
            
        }
        if(pageNum == 2||1)
        {//第二次进来更新 id0 id2
            
            
            pageNum = 0;
            while (j<pageItemNum) {
                auto item = vec.at(j);
                auto itemVec = item->getChildren();
                int tempDay = 0;
                int dayMax = 0;
                if(j == 0)
                {
                    tempDay = tempDay2;
                    dayMax = dayMax2;
                }
                else if(j == 1)
                {
                    dayMax = dayMax1;
                    tempDay = tempDay1;
                }
                else if(j == 2)
                {
                    tempDay = tempDay3;
                    dayMax = dayMax3;
                }
                for(int k = 0;k<itemVec.size();++k)
                {
                    auto node = itemVec.at(k);
                    int tempYear = 0;
                    int tempMonth = 0;
                    
                    if(j == 0)
                    {
                        tempYear = year2;
                        tempMonth = Month2;
                    }
                    else if(j == 1)
                    {
                        tempYear = dateA.Year();
                        tempMonth = dateA.Month();
                    }
                    else if(j == 2)
                    {
                        tempYear = year3;
                        tempMonth = Month3;
                    }
                    int day = k+tempDay;
                    auto dailyNode = dynamic_cast<DailyNode*>(node);
                    if(day > dayMax)
                    {
                        dailyNode->setVisible(false);
                    }
                    else
                    {
                        dailyNode->setVisible(true);
                        Date date(tempYear, tempMonth, day);
                        dailyNode->setDate(date);
                        if(k == 0&&j==2)
                        {
                            EVENT_M->sendEvent("msg_daily_node", (void*)dailyNode2);
                        }
                        if (date > today) {
                            dailyNode->setState(DailyNode::State::Closed);
                        }
                        else {
                            bool complete = DailyManager::getInstance()->isDailyCompleted(date);
                            dailyNode->setState(complete?DailyNode::State::Completed:DailyNode::State::Open);
                            //dailyNode->setSelected(k == 0&&j==1);
                            //dailyNode->setSelected(k == 0&&pageNum==1);
                            //dailyNode->setSelected(false);
                            
                        }
                    }
                }
                j+=2;
            }
        }
        if(pageNum == 1||1)
        {
            
            getNode<Text*>("Text_title_0")->setString(StringUtils::format("%d.%d",dateA.Year(), dateA.Month()));//Lang_2("100157", dateA.Year(), dateA.Month()));
            //getNode<Text*>("Text_title2")->setString(Lang_2("100157",dateA.Year(), dateA.Month()));
            if(isPageRun)
            {
                //isPageRun = false;//运动结束
                //page->setCurrentPageIndex(1);
            }
            //pageView->setEnabled(true);
        }
    }
}

void DailyView::setToDay()
{//更新日期到今天
    //pageView;
    if(_selectedNode->getDate() == _today)return;
    isToDay = true;
    setPageUI(_today.Year(),_today.Month(),_today.Day());
}

void DailyView::leftMore()
{
     if(_current.Month() == 1)
     {
         return;
     }
    if(_current.Month() == 2)
    {
        Panel_more->getNode<Button*>("Button_modeLeft1")->setEnabled(false);
    }
    Panel_more->getNode<Button*>("Button_modeRight")->setEnabled(true);
     _current.PreMonth();
     setMoreUI(_current.Year(), _current.Month(),0,true);
}
void DailyView::rightMore()
{
    if(_current.Month() == 12||_current.Month() >= _today.Month())
    {
        return;
    }
    if(_current.Month() == 11||_today.Month() - _current.Month() == 1)
    {
        Panel_more->getNode<Button*>("Button_modeRight")->setEnabled(false);
    }
    Panel_more->getNode<Button*>("Button_modeLeft1")->setEnabled(true);
    _current.NextMonth();
    setMoreUI(_current.Year(), _current.Month(),0,true);
}

void DailyView::filterSimpleDate()
{//从新的一天开始算
    auto isVip = DATA_M->isVipNoAds();
    auto today = isVip?_maxday:_today;
    auto toDayYear = today.Year();
    auto toDayMonth = today.Month();
    auto toDay = today.Day();
    int tempDay = 0;
    int tempMonth = 0;
    int month = toDayMonth;
    while (month > 0) {
        auto days = DailyManager::getInstance()->getDays(_current.Year(), month);
        for(int i = days;i>0;--i)
        {
            Date date(toDayYear,month,i);
            if(date > today)
            {
                continue;
            }
            //判断是否有完成
            auto cnt = DailyManager::getInstance()->getCompleteCNT(date);
            if(cnt == 0)
            {//记录这个日期
                tempDay = i;
                tempMonth = month;
                break;
            }
        }
        if(tempDay!=0)
        {//有存入日期 跳出s
            break;
        }
        //这个月份没有选到日期
        month--;
    }
    if(tempDay != 0)
    {
        Date date(toDayYear,tempMonth,tempDay);
        setPageUI(toDayYear,tempMonth,tempDay);
    }
}
