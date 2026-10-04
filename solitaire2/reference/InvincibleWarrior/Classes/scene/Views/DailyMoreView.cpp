//
//  DailyMoreView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/17.
//

#include <stdio.h>
#include "DailyMoreView.h"
#include "SoundManager.h"
#include "DailyNode.h"
#include "DailyGameView.h"
#include "FishManager.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "GameBackground.h"
#include "MainLobby.h"
#include "FishManager.h"
#include "PlayerManager.h"
#include "FishGuideManager.h"
const auto VSpace = 16;
const auto HSpace = 28;
const auto TotalRow = 5;
Vec2 DailyMoreView::GetPosition(int x, int y)
{
    return Vec2((x+0.5)*(110+HSpace), (y+0.5)*(108+VSpace));
}

Vec2 DailyMoreView::GetPosition(int x)
{
    return Vec2((x) * 170 + 85, 94);//Vec2((x+0.5)*(110+HSpace), (y+0.5)*(108+VSpace));
}

int DailyMoreView::gouRound(int value, int max)
{
    auto t = value % max;
    return t == 0?1:t;
}

DailyMoreView::DailyMoreView(Date current)
:BaseLayer("2020Daily_riqi.csb")
,_current(current)
{
    FileNode_start = NULL;
}

DailyMoreView::~DailyMoreView()
{
    
}

void DailyMoreView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    setLocalZOrder(2);
    //    auto sp = Sprite::createWithSpriteFrameName("daily/Daily_bar0.png");
        ProgressTimer_percent = ProgressTimer::create(Sprite::createWithSpriteFrameName("daily/Daily_bar1.png"));
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
    
    
    _toDay = DailyManager::getInstance()->today();
    _maxday = Date(_toDay.Year(), 12, 31);
    if(_current.Month()==1)
    {
        getNode<Button*>("Button_modeLeft1")->setEnabled(false);
    }
    else if(_current.Month()==12||_toDay.Month() == _current.Month())
    {
        getNode<Button*>("Button_modeRight")->setEnabled(false);
    }
    
    
    LoadingBar_StarBox = getNode<LoadingBar*>("LoadingBar_StarBox");
    BitmapFontLabel_StarNum = getNode<TextBMFont*>("BitmapFontLabel_StarNum");
    BitmapFontLabel_StarNumMax = getNode<TextBMFont*>("BitmapFontLabel_StarNumMax");
    Node_fish = getNode("Node_fish");
    
    
    /*
     根据当前解锁数量，比如解锁了5个鱼，就是5.解锁了3个鱼就是3.随着解锁第几个鱼来算

     判断当前解锁的数量，1阶段 X x 20%-35%（随机）=四舍五入。 例如解锁第五个鱼。 5x35%=1.75（四舍五入=2）就是第二个鱼类

     2阶段 X x 34%-79%（随机）=四舍五入。

     3阶段 X x 80%-95%（随机）=四舍五入。
     15
     */
    
    fishIds.clear();
    vector<int> fishIds1{
        20,35,
    };
    vector<int> fishIds2{
        34,79,
    };
    vector<int> fishIds3{
        80,95,
    };
    fishIds.push_back(fishIds1);
    fishIds.push_back(fishIds2);
    fishIds.push_back(fishIds3);
    
    
    
    
    playAni("Start0", false);
    setVisible(true);
    updateUI(_current);
    setMoreUI(_current.Year(),_current.Month(),_current.Day());
    updateDYY();
}

void DailyMoreView::updateDYY()
{
    getNode<Text*>("Text_start11")->setString(Lang("100150"));
    string weekday[] = {Lang("100316"),Lang("100310"),Lang("100311"),Lang("100312"),Lang("100313"),Lang("100314"),Lang("100315")};
    for(int i = 1;i<8;i++)
    {
        if(i == 7)
        {
            getNode<Text*>(StringUtils::format("Text_week%d",i))->setString(weekday[0]);
        }
        else
        {
            getNode<Text*>(StringUtils::format("Text_week%d",i))->setString(weekday[i]);
        }
    }
    getNode<Text*>("Text_Star_miaoshu")->setString(Lang("100372"));
    
    getNode<Text*>("Text_getFish")->setString(Lang("100186"));
    getNode<Text*>("Text_rare")->setString(Lang("100373"));
}

void DailyMoreView::initData()
{
    BaseLayer::initData();
    setName("DailyMoreView");
}

void DailyMoreView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto btnName = btn->getName();
    if(dynamic_cast<Button*>(btn))
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
    }
       
    if(btnName == "Button_close"||btnName == "Panel_out")
    {//场景
        //SCENE_M->removeLayer(this);
        auto lobby = SCENE_M->getLobby();
        if(lobby->isVisible())
        {
            lobby->openReward(false);
        }
        
//        this->setVisible(false);
        
        this->removeFromParent();
    }
    else if (btnName == "Button_modeLeft1") {
        leftMore();
    }
    else if (btnName == "Button_modeRight") {
        rightMore();
    }
    else if(btnName == "Button_start")
    {
        showStart();
        this->setVisible(false);
    }
    else if(btnName == "Button_getFish")
    {//得到鱼
        auto fishNum = DATA_M->getFishNum();
        if(fishNum >= FISH_MAX_NUM)
        {
            //SCENE_M->showTips(Lang("100364"));
            FishGuideManager::getInstance()->fishMaxGuide();
        }
        else
        {
            auto lobby = SCENE_M->getLobby();
            if(lobby->isVisible())
            {
                lobby->openReward(false);
            }
            auto fashTank = SCENE_M->getGameBackground();
            
            fashTank->addFish(newShopIdx[_currentFishkIdx],true);

            //记录这个阶段完成了
            DailyManager::getInstance()->setDailyRewardCompleted(_current,_jieduan,true);
            
//            this->setVisible(false);
            this->removeFromParent();
        }
    }
}
void DailyMoreView::runProgress(float time,float percent)
{
    ProgressTimer_percent->runAction(ProgressTo::create(time, percent));
}

void DailyMoreView::updateUI(Date date)
{
    //auto isVip = DATA_M->isVipNoAds();
    if(date.Month()==1)
    {
        getNode<Button*>("Button_modeLeft1")->setEnabled(false);
    }
    else if((date.Month()==12||_toDay.Month() == date.Month()))//&&!isVip)
    {
        getNode<Button*>("Button_modeRight")->setEnabled(false);
    }
    else
    {
        getNode<Button*>("Button_modeLeft1")->setEnabled(true);
        getNode<Button*>("Button_modeRight")->setEnabled(true);
    }
    
    
}

void DailyMoreView::onEnter()
{
    BaseLayer::onEnter();
}

void DailyMoreView::onExit()
{
    BaseLayer::onExit();
}

void DailyMoreView::setMoreUI(int year, int month, int selectDay_)
{
    auto root = this->getNode("Panel_container");
    root->removeAllChildren();
    auto dailyManager = DailyManager::getInstance();
    int week = dailyManager->CaculateWeekDay(year, month, 1);
    int days = dailyManager->getDays(year, month);
    int selectedDay = selectDay_;
//    auto isVip = DATA_M->isVipNoAds();
//    auto today = isVip?_maxday:_toDay;
    auto today = _toDay;
    if (selectedDay == 0) {
        if ((_current.Year() == _toDay.Year() && _current.Month() == _toDay.Month())) {
            selectedDay = today.Day();//MAX(_today.Day(), _current.Day());
        }
        else if(_current.Year() == _toDay.Year() && _current.Month() > _toDay.Month())
        {
            selectedDay = 1;
        }
        else {
            selectedDay = days;
        }
    }

    for (int i=0; i<days; i++) {
        int idx = i+week;
        int day = i+1;
        Date date(year, month, day);
        auto dailyNode = DailyNode::createLayerN(this, date,DailyNode::Type::month);
        //auto mode = toString("1");
        if (date > today) {
            dailyNode->setState(DailyNode::State::Closed);
        }
        else {
            bool complete = dailyManager->isDailyCompleted(date);
            dailyNode->setState(complete?DailyNode::State::Completed:DailyNode::State::Open);
        }
        root->addChild(dailyNode);
        dailyNode->setSelected(day == selectedDay);
        int x = idx%7, y = TotalRow-ceil(idx/7);
        dailyNode->setPosition(GetPosition(x, y));
    }
    
    for(int i = 1;i < 8;i++)
    {
        int x = i%7, y = TotalRow-ceil(i/7);
        auto poi = GetPosition(x, y);
        poi = root->convertToWorldSpace(poi);
        
        auto node = getNode<Text*>(StringUtils::format("Text_week%d",i));
        poi = node->getParent()->convertToNodeSpace(poi);
        node->setPositionX(poi.x);
    }
    getNode<TextBMFont*>("BMFont_road4")->setString(toString(days));
    // 🏆
    getNode<Sprite*>("Sprite_iconTrophyDiamon")->setSpriteFrame(StringUtils::format("iconJiangBei_%02d.png", gouRound(_current.Month(), 4)));//无资源
    //getNode<Text*>("Text_title_0")->setString(StringUtils::format("%d.%d",year, month));//Lang_2("100157", year, month)
    this->getNode<Text*>("Text_title2")->setString(Lang_2("100157", year, month));
    
    //更新id
    for(int i = 0;i < 3;++i)
    {
        rewardIds[i] = GETINTEGER(StringUtils::format("rewardId_%d_%d_%d",year,month,i).c_str(),-1);
    }
    
    
    //刷新年份月份对应的完成度
    dailyManager->updateDailyRewards(Date(year,month,1));
    
    //查询这个月份的完成度
    int completeNum = 0;
    for(int i = 0;i < days;++i)
    {
        int day = i+1;
        Date date(year, month, day);
        for (int i=1; i<=4; ++i) {
            bool complete = dailyManager->isDailyCompleted(date, toString(i));
            if(complete)
            {
                completeNum++;
            }
        }
    }
    //三个阶段 14 28 60
    //给鱼5-6 7-8 10-11
    _jieduan = -1;
    jieduanVec.clear();
    jieduanVec.push_back(14);
    jieduanVec.push_back(36);
    auto num = MIN(74,days*3);
    jieduanVec.push_back(num);
    
    for(int i = 0;i < 3;++i)
    {
        auto isCompleted = dailyManager->getDailyRewardCompleted(i);
        if(!isCompleted)
        {
            _jieduan = i;
            break;
        }
    }
    Node_fish->removeAllChildren();
    if(_jieduan != -1)
    {
        //初始化奖励
        auto rewardId = rewardIds[_jieduan];
        if(rewardId == -1)
        {//
            auto vec = fishIds.at(_jieduan);
            
            auto min = vec.at(0);
            auto max = vec.at(1);
            auto lv = PlayerManager::getInstance()->getLevel();
            auto fishIdx = FishManager::getInstance()->getMaxFishIdx(lv);
            auto rand = (float)random(min, max)/100.f;
            auto idx = std::round(fishIdx * rand);
            auto randId = newShopIdx[idx];
            rewardIds[_jieduan] = randId;
            rewardId = randId;
            SETINTEGER(StringUtils::format("rewardId_%d_%d_%d",year,month,_jieduan).c_str(),randId);
        }
        
        auto max = jieduanVec.at(_jieduan);
        auto min = MIN(completeNum,max);
        auto minP = _jieduan != 0?jieduanVec.at(_jieduan-1):0;
        auto dx = max - minP;
        auto percent = (float)(min-minP)/(float)dx * 100;
        LoadingBar_StarBox->setPercent(percent);
        
        _currentFishkIdx = rewardId;
        if(rewardId != -1)
        {
            //创建鱼
            //auto idx = newShopIdx[rewardId];
            auto skeletonNode = FISH_M->getFishSpine(rewardId);
            Node_fish->addChild(skeletonNode);
            string aniName = "Run";
            
            skeletonNode->setAnimation(0, aniName, true);
            if(rewardId == 14)
            {
                skeletonNode->setPositionX(466.55f * 0.1f);
                skeletonNode->setScale(0.85f);
            }
        }
        
        BitmapFontLabel_StarNum->setString(StringUtils::toString(min));
        BitmapFontLabel_StarNumMax->setString(StringUtils::toString(max));
        getNode("Button_getFish")->setVisible(min == max);
    }
    else
    {
        LoadingBar_StarBox->setPercent(100);
        auto num = jieduanVec.at(2);
        BitmapFontLabel_StarNum->setString(StringUtils::toString(num));
        BitmapFontLabel_StarNumMax->setString(StringUtils::toString(num));
        getNode("Button_getFish")->setVisible(false);
    }
}

void DailyMoreView::leftMore()
{
     if(_current.Month() == 1)
     {
         return;
     }
    if(_current.Month() == 2)
    {
        getNode<Button*>("Button_modeLeft1")->setEnabled(false);
    }
    getNode<Button*>("Button_modeRight")->setEnabled(true);
     _current.PreMonth();
     setMoreUI(_current.Year(), _current.Month(),0);
}
void DailyMoreView::rightMore()
{
    if(_current.Month() == 12||_current.Month() >= _toDay.Month())
    {
        return;
    }
    if(_current.Month() == 11||_toDay.Month() - _current.Month() == 1)
    {
        getNode<Button*>("Button_modeRight")->setEnabled(false);
    }
    getNode<Button*>("Button_modeLeft1")->setEnabled(true);
    _current.NextMonth();
    setMoreUI(_current.Year(), _current.Month(),0);
}

void DailyMoreView::showStart()
{
    if(!FileNode_start)
    {
        FileNode_start = DailyGameView::createLayerN(_selectedNode,this);//getNode("FileNode_start");//null
        SCENE_M->addDialog(FileNode_start,false,3);
    }
    showSelectDialog();
}

void DailyMoreView::showSelectDialog(bool isCompletedView, int tag)
{
    if(!FileNode_start)
    {
        FileNode_start = DailyGameView::createLayerN(_selectedNode,this);//getNode("FileNode_start");//null
        SCENE_M->addDialog(FileNode_start,false,3);
    }
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
            auto btnStart = FileNode_start->getNode<Button*>(StringUtils::format("Button_start%d", i));
            btnStart->loadTextures(btnImgName0, btnImgName1, btnImgName0, Widget::TextureResType::PLIST);
            auto Text_Name = btnStart->getChildByName<Text*>("Text_Name");
            Text_Name->setString(complete?Lang("100149"):Lang("100150"));
            UIUtils::textAdaptiveSize(Text_Name, 230);
            if (i!=4) {
                FileNode_start->getNode<Text*>(StringUtils::format("Text_rewardTitle%d", i))->setString(Lang(complete?"100151":"100152"));
            }
            FileNode_start->getNode(StringUtils::format("Level_win%d", i))->setVisible(complete);
        }
        auto cnt = DailyManager::getInstance()->getCompleteCNT(date);
        FileNode_start->getNode<LoadingBar*>("LoadingBar_rewardPercent")->setPercent(cnt/3.0f * 100);
    }
}

void DailyMoreView::setCurrentSelectNode(DailyNode *selectNode) {
    if (_selectedNode != selectNode||1) {
        _selectedNode = selectNode;
        updateUI();
    }
}

void DailyMoreView::updateUI()
{
    if(_selectedNode)
    {//更新more信息
        _current = _selectedNode->getDate();
    }
}

std::string DailyMoreView::getTrophy(int monthCompleteCNT, int days)
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

void DailyMoreView::setFileNodeStart(DailyGameView* start)
{
    FileNode_start = start;
}
