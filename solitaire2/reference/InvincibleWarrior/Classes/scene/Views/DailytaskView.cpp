//
//  DailytaskView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/25.
//

#include <stdio.h>
#include "DailytaskView.h"
#include "TaskManager.h"
#include "MainLobby.h"
#include "GameViewHD.hpp"
#include "RewardManager.h"
#include "PlayerManager.h"
#include "HomeView.h"
#include "TeachManager.h"
#include "GrowupNode.h"
#include "BagView.h"
//事件
#include "EventObserver.h"


/*
 "100207" : "每日任务",
 "100208" : "使用1次背景",
 "100209" : "完成1局经典模式",
 "100210" : "观看看1次视频或完成3次每日挑战",
 "100211" : "抽取1次黄金宝箱",
 "100212" : "使用1次魔法棒",
 "100213" : "使用1次牌背",
 "100214" : "使用1次牌面",
 "100215" : "使用1次音乐",
 "100216" : "挑战1次关卡",
 "100217" : "挑战1次每日挑战",
 "100218" : "抽取1次钻石宝箱",
 "100219" : "挑战模式获得1个铜奖",
 "100220" : "挑战模式获得1个银奖",
 "100221" : "挑战模式获得1个金奖",
 "100222" : "挑战模式获得1个钻石奖",
 
 "100223" : "完成1次经典模式",
 "100224" : "完成3次经典模式",
 "100225" : "完成1次每日挑战",
 "100226" : "完成3次每日挑战",
 "100227" : "抽取1次黄金宝箱",
 "100228" : "抽取1次钻石宝箱",
 "100229" : "完成中级挑战",
 "100230" : "完成专家挑战",
 "100231" : "完成5次困难",
 "100232" : "完成1次三张牌经典模式",
 "100233" : "完成3次三张牌困难模式",
 */



//奖励
int goldNumArr[] = {75,100,125};
int diamondNumArr[] = {75,100,125};

int DailytaskView::getGoldNum(int id)
{
    if(id == 0)
    {//1 -10
        return 10;
    }
    else if(id == 1)
    {
        return 15;
    }
    else if(id == 2)
    {
        return 25;
    }
    return 25;
}

int DailytaskView::getDiamondNum(int id)
{
    if(id == 0)
    {
        return 0;
    }
    else if(id == 1)
    {//20-50
        return 0;
    }
    else if(id == 2)
    {//50s-100
        return 0;
    }
    return 0;
}

DailytaskView::DailytaskView(std::function<void()> cb)
:BaseLayer("2020Dailytask.csb")
,_cb(cb)
,isBar(false)
,_taskType1(-1)
,_taskType2(-1)
,_taskType3(-1)
,fangCuoNum(0)
,_mainLobby(nullptr)
{
    _boxNum = GETINTEGER("task_boxNum",0);
}

DailytaskView::~DailytaskView()
{
    
}

void DailytaskView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    FileNode_task1 = getNode("FileNode_task1");
    FileNode_task2 = getNode("FileNode_task2");
    FileNode_task3 = getNode("FileNode_task3");
    Panel_7 = getNode("Panel_7");
    
    LoadingBar_task = getNode<LoadingBar*>("LoadingBar_task");
    
    getNode("Button_getGold")->setVisible(false);
    getNode("Button_getDiamond")->setVisible(false);
    LoadingBar_task1 = dynamic_cast<LoadingBar*>(UIUtils::seekNodeByName(FileNode_task1,"LoadingBar_task1"));
    LoadingBar_task2 = dynamic_cast<LoadingBar*>(UIUtils::seekNodeByName(FileNode_task2,"LoadingBar_task1"));
    LoadingBar_task3 = dynamic_cast<LoadingBar*>(UIUtils::seekNodeByName(FileNode_task3,"LoadingBar_task1"));
    Text_TaskNum1 = dynamic_cast<Text*>(UIUtils::seekNodeByName(FileNode_task1,"Text_TaskNum1"));
    Text_TaskNum2 = dynamic_cast<Text*>(UIUtils::seekNodeByName(FileNode_task2,"Text_TaskNum1"));
    Text_TaskNum3 = dynamic_cast<Text*>(UIUtils::seekNodeByName(FileNode_task3,"Text_TaskNum1"));
    
    Text_miaoshu1 = dynamic_cast<Text*>(UIUtils::seekNodeByName(FileNode_task1,"Text_miaoshu"));
    Text_miaoshu2 = dynamic_cast<Text*>(UIUtils::seekNodeByName(FileNode_task2,"Text_miaoshu"));
    Text_miaoshu3 = dynamic_cast<Text*>(UIUtils::seekNodeByName(FileNode_task3,"Text_miaoshu"));
    
    Text_15_reward1 = dynamic_cast<Text*>(UIUtils::seekNodeByName(FileNode_task1,"Text_15_reward"));
    Text_15_reward2 = dynamic_cast<Text*>(UIUtils::seekNodeByName(FileNode_task2,"Text_15_reward"));
    Text_15_reward3 = dynamic_cast<Text*>(UIUtils::seekNodeByName(FileNode_task3,"Text_15_reward"));
    
    
    auto Button_Task1 = dynamic_cast<Button*>(UIUtils::seekNodeByName(FileNode_task1,"Button_Task1"));
    Button_Task1->setName("Button_Task1");
    auto Button_Task2 = dynamic_cast<Button*>(UIUtils::seekNodeByName(FileNode_task2,"Button_Task1"));
    Button_Task2->setName("Button_Task2");
    auto Button_Task3 = dynamic_cast<Button*>(UIUtils::seekNodeByName(FileNode_task3,"Button_Task1"));
    Button_Task3->setName("Button_Task3");
    TaskBox_1 = getNode<Sprite*>("TaskBox_1");
    TaskBox_2 = getNode<Sprite*>("TaskBox_2");
    TaskBox_3 = getNode<Sprite*>("TaskBox3");
    
    Panel_Box1 = getNode("Particle_crownlight_Box1");
    Panel_Box2 = getNode("Particle_crownlight_Box2");
    Panel_Box3 = getNode("Particle_crownlight_Box3");

    playAni("Start0",false);

    _gameView = SCENE_M->getGameView();
    _mainLobby = SCENE_M->getLobby();
    //用户打开了， 隐藏提示
    if(_mainLobby)
    {
        _mainLobby->updateTaskNew();
    }
    
    
    TASK_M->clearTaskType();
    
    _actionManager->setFrameEventCallFunc([this](Frame* f){
        auto event = dynamic_cast<EventFrame*>(f);
        auto msg = event->getEvent();
        if(msg.find("box") != string::npos)
        {
            auto idstr = msg[3];
            if(idstr == '1')
            {
                SOUND_M->playEffectMusic(EffectBoxOpen);
            }
            auto Sprite_Box = getNode<Sprite*>("Sprite_GoldBox");
            if(_boxNum == 1)
            {//Box3_%s
                Sprite_Box->setSpriteFrame(StringUtils::format("Box_%c.png",idstr));
            }
            else if(_boxNum == 2)
            {//Box5_%s
                Sprite_Box->setSpriteFrame(StringUtils::format("Box2_%c.png",idstr));
            }
            else if(_boxNum == 3)
            {//Box5_%s
                Sprite_Box->setSpriteFrame(StringUtils::format("Box3_%c.png",idstr));
            }
        }
    });
    
    schedule([this](float dt){
        if(isBar)
        {
            percentB+=66.66*dt;
            if(percentB>percentE)
            {
                if(_boxNum == 1)
                {
                    TaskBox_1->setSpriteFrame("Box_2.png");
                    Panel_Box1->setVisible(true);
                }
                else if(_boxNum == 2)
                {
                    TaskBox_2->setSpriteFrame("Box2_2.png");
                    Panel_Box2->setVisible(true);
                }
                else if(_boxNum == 3)
                {
                    TaskBox_3->setSpriteFrame("Box3_2.png");
                    Panel_Box3->setVisible(true);
                }
                
                
                percentB = percentE;
                isBar = false;
                getNode("Panel_7")->setVisible(true);
                getNode("Button_getTaskGold")->setVisible(false);
                playAni("Start1",false,[this](){
                    if(_boxNum >= 3)_boxNum = 0;
                    SETINTEGER("task_boxNum",_boxNum);
                    auto lobby = SCENE_M->getLobby();
                    //金币飞出Sprite_GoldBox起始点弄
                    auto Sprite_GoldBox = getNode("Sprite_GoldBox");
                    auto startPoi = Sprite_GoldBox->getPosition();
                    startPoi = Sprite_GoldBox->getParent()->convertToWorldSpace(startPoi);
                    //startPoi.x -= 80;
                    
                    //目标点
                    auto Money_Gold_0_262_0 = getNode("img_icon_top_gold");
                    auto targetPoi = Money_Gold_0_262_0->getPosition();
                    targetPoi = Money_Gold_0_262_0->getParent()->convertToWorldSpace(targetPoi);
                    
                    //DATA_M->setCoinNum(_coinNum,false);
                    
                    auto coin = _coinNum;
                    lobby->goldAni(_coinNum,this,startPoi,[this,lobby,coin](){
                        getNode("Button_getTaskGold")->setVisible(true);
                        
                        DATA_M->setCoinNum(coin, true, 126);
                        ValueMap valueMap{
                            {"isTime",Value{true}}
                        };
                        //更新有金币显示
                        EVENT_M->sendEvent("event_game_update_coin",valueMap);
                        //updateCoin(true);
                        //lobby->updateCoin();
                        
                    },[this](){
                        //SOUND_M->playEffectMusic(EffectGetCoin);
                        
                        auto FileNode_gold = getNode("FileNode_gold");
                        FileNode_gold->setVisible(true);
                        auto img_icon_gold = getNode("img_icon_top_gold");
                        img_icon_gold->setVisible(false);
                        UIUtils::playInnerAction(FileNode_gold,"Gold",false);
                    },[this](){
                        //SOUND_M->playEffectMusic(EffectGetCoin);
                        isReward = false;
                        auto FileNode_gold = getNode("FileNode_gold");
                        FileNode_gold->setVisible(false);
                        auto img_icon_gold = getNode("img_icon_top_gold");
                        img_icon_gold->setVisible(true);
                    });
                    
                    //startPoi.x += 160;
//                    auto diamond = _diamondNum;
//                    lobby->diamondAni(_diamondNum,this,startPoi,[this,lobby,diamond](){
//                        getNode("Button_getTaskGold")->setVisible(true);
//                        
//                        //更新有金币显示
//                        DATA_M->setDiamond(diamond);
//                        ValueMap valueMap{
//                            {"isTime",Value{true}}
//                        };
//                        //更新有金币显示
//                        EVENT_M->sendEvent("event_game_update_diamond",valueMap);
////                        SCENE_M->getLobby()->updateDiamond();
////                        updateDiamond(true);
//                    
//                    },[lobby,this](){
//                        //home
//                        //SOUND_M->playEffectMusic(EffectGetGem);
//                      
//                        auto FileNode_gold = getNode("FileNode_diamond");
//                        FileNode_gold->setVisible(true);
//                        auto img_icon_gold = getNode("img_icon_top_diamond");
//                        img_icon_gold->setVisible(false);
//                        UIUtils::playInnerAction(FileNode_gold,"Baoshi",false);
//                    },[lobby,this](){
//                        //home
//                        //SOUND_M->playEffectMusic(EffectGetGem);
//                        isReward = false;
//                        auto FileNode_gold = getNode("FileNode_diamond");
//                        FileNode_gold->setVisible(false);
//                        auto img_icon_gold = getNode("img_icon_top_diamond");
//                        img_icon_gold->setVisible(true);
//                    });
                    //领取过奖励了//移除这个任务
                    TASK_M->removeAllTaskVec(_tempTaskType);
                });
            }
            LoadingBar_task->setPercent(percentB);
        }
    }, 0.03, "scheduler_update_bar");
    
    //修正金币与钻石图片位置
    auto Text_getGoldNum = getNode<Text*>("Text_getGoldNum");
    //auto Text_getDiamond = getNode<Text*>("Text_getDiamond");
    Text_getGoldNum->setString("+50");
    //Text_getDiamond->setString("+50");
    
    auto goldSize = Text_getGoldNum->getBoundingBox().size;
    //Text_getDiamond->setPositionY(goldSize.height*-0.31);
    //auto GemSize = Text_getDiamond->getBoundingBox().size;
    getNode("Money_Gold_1")->setPosition(Vec2(goldSize.width*-0.04,goldSize.height*0.53));
    //getNode("Money_Gold_2")->setPosition(Vec2(GemSize.width*-0.04,GemSize.height*0.53));
    
    //初始化任务完成度
    isTask1 = false;
    isTask2 = false;
    isTask3 = false;
    
    updateCoin();
    updateDiamond(); 
    
    updateUI();
    
    TEACH_M->nextTeachStep(this);
    //多语言
    Text_15_reward1->setString(Lang("100159"));
    Text_15_reward2->setString(Lang("100159"));
    Text_15_reward3->setString(Lang("100159"));
    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    getNode<Text*>("Text_DayTask")->setString(Lang("100207"));
    getNode<Text*>("Text_OK")->setString(Lang("100170"));
}

void DailytaskView::initData()
{
    BaseLayer::initData();
    setName("DailytaskView");
    
    EVENT_M->addListener("event_game_update_coin", [this](ValueMap valueMap, void *obj){
        if(!valueMap.empty())
        {
            auto isTime = valueMap["isTime"].asBool();
            this->updateCoin(isTime);
        }
        else
        {
            this->updateCoin();
        }
    },this);
    EVENT_M->addListener("event_game_update_diamond", [this](ValueMap valueMap, void *obj){
        if(!valueMap.empty())
        {
            auto isTime = valueMap["isTime"].asBool();
            this->updateDiamond(isTime);
        }
        else
        {
            this->updateDiamond();
        }
    },this);
//    addEvent("event_game_update_coin", [this](EventCustom *e){
//        auto isTime = (bool)e->getUserData();
//        this->updateCoin(isTime);
//    });
//    addEvent("event_game_update_diamond", [this](EventCustom *e){
//        auto isTime = (bool)e->getUserData();
//        this->updateDiamond(isTime);
//    });
}

void DailytaskView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn||isReward)return;
    
    auto name = btn->getName();
    
    
    
    if(name == "Button_close"||name == "Panel_bg_0")
    {
        if(_cb)
        {
            _cb();
        }
        TEACH_M->nextTeachStep(SCENE_M->getLobby());
        SCENE_M->removeLayer(this);
        UIUtils::FIRFirestoreAdd("operator", {
            {"key", Value("DailytaskView")},
            {"value", Value("no")},
            {"v1", Value(DATA_M->getHaveVideo())}
        });
    }
    else if(name == "Image_task")
    {//领取宝箱
        auto tag = btn->getTag();
        //openBox(tag);
    }
    else if(name == "Button_getTaskGold")
    {
        //DATA_M->setCoinNum(_coinNum,true);
        //DATA_M->showCoinTips(num);
        getNode("Panel_7")->setVisible(false);
        openBox(0);
    }
    if(_cb)return;
    if(name == "Button_Task1")
    {//开始任务
        
        jumpLayer(_taskType1);
        
        if(TEACH_M->isTeaching())
        {//任务。关闭
            TEACH_M->nextTeachStep(SCENE_M->getLobby());
        }
        SCENE_M->removeLayer(this);
    }
    else if(name == "Button_Task2")
    {//开始任务
        jumpLayer(_taskType2);
        if(TEACH_M->isTeaching())
        {//任务。关闭
            TEACH_M->nextTeachStep(SCENE_M->getLobby());
        }
        SCENE_M->removeLayer(this);
    }
    else if(name == "Button_Task3")
    {//开始任务
        jumpLayer(_taskType3);
        if(TEACH_M->isTeaching())
        {//任务。关闭
            TEACH_M->nextTeachStep(SCENE_M->getLobby());
        }
        SCENE_M->removeLayer(this);
    }
    
}

void DailytaskView::updateUI()
{
    if(fangCuoNum >= 8)
    {
        return;
    }
    auto taskManager = TaskManager::getInstance();
    
    //第一次刷新都是false。第二次刷新新任务
    //如果剩余任务数==3则不刷新
    if(TASK_M->getAllTaskNum() != 3)
    {//
        if(isTask1)
        {//第一个任务  其余都刷新
            UIUtils::playInnerAction(FileNode_task1,"Start1",false);
            
        }
        if(isTask2)
        {//第二个任务。第二第三刷新
            
            UIUtils::playInnerAction(FileNode_task2,"Start1",false);
            
        }
        if(isTask3)
        {//第三个任务。
            UIUtils::playInnerAction(FileNode_task3,"Start1",false);
        }
    }
    else
    {
        if(_taskType1 != -1&&TASK_M->getIsUpdateTask(_taskType1))
        {//判断这个任务打开没有box
            UIUtils::playInnerAction(FileNode_task1,"Start1",false);
        }
        
        if(_taskType2 != -1&&TASK_M->getIsUpdateTask(_taskType2))
        {//判断这个任务打开没有box
            UIUtils::playInnerAction(FileNode_task2,"Start1",false);
        }
        
        if(_taskType3 != -1&&TASK_M->getIsUpdateTask(_taskType3))
        {//判断这个任务打开没有box
            UIUtils::playInnerAction(FileNode_task3,"Start1",false);
        }
    }
    
    vector<string> newTaskNameVec{
        Lang("100208"),
        Lang("100209"),
        Lang("100210"),
        Lang("100211"),
        Lang("100212"),
        Lang("100213"),
        Lang("100214"),
        Lang("100215"),
        //Lang("100216"),
        Lang("100217"),
        Lang("100218"),
        Lang("100219"),
        Lang("100220"),
        Lang("100221"),
        Lang("100222"),
    };

    vector<string> dayTaskNameVec{
        Lang("100223"),
        Lang("100224"),
        Lang("100225"),
        Lang("100226"),
        Lang("100227"),
        Lang("100228"),
        Lang("100229"),
        Lang("100230"),
        Lang("100231"),
        Lang("100232"),
        Lang("100233"),
        "",
        "",
        "",
        "",
    };
    
    //分配任务。 0 1 2。  0号任务完成了 1变到0。2变到1
//    int ceshi = 108;
//    _taskType1 = ceshi;
//    _taskType2 = ceshi+1;
//    _taskType3 = ceshi+2;
    _taskType1 = taskManager->getTask1(isTask1,isTask2,isTask3);
    _taskType2 = taskManager->getTask2(isTask1,isTask2,isTask3);
    _taskType3 = taskManager->getTask3(isTask1,isTask2,isTask3);
    
    //||TASK_M->getIsEndTask(_taskType1,_taskType2,_taskType3)
    int num1 = 0;
    int max1 = 0;
    int num2 = 0;
    int max2 = 0;
    int num3 = 0;
    int max3 = 0;
    string name1 = "";
    string name2 = "";
    string name3 = "";
    //获取任务数据
    if(_taskType1<100)
    {
        num1 = taskManager->getTaskNum((TaskManager::NewbieTaskType)(_taskType1));
        max1 = taskManager->getTaskMaxNum((TaskManager::NewbieTaskType)(_taskType1));
        name1 = newTaskNameVec.at(_taskType1);
    }
    else
    {
        num1 = taskManager->getTaskNum((TaskManager::DayTaskType)(_taskType1-100));
        max1 = taskManager->getTaskMaxNum((TaskManager::DayTaskType)(_taskType1-100));
        name1 = dayTaskNameVec.at(_taskType1-100);
    }
    
    if(_taskType2<100)
    {
        num2 = taskManager->getTaskNum((TaskManager::NewbieTaskType)(_taskType2));
        max2 = taskManager->getTaskMaxNum((TaskManager::NewbieTaskType)(_taskType2));
        name2 = newTaskNameVec.at(_taskType2);
    }
    else
    {
        num2 = taskManager->getTaskNum((TaskManager::DayTaskType)(_taskType2-100));
        max2 = taskManager->getTaskMaxNum((TaskManager::DayTaskType)(_taskType2-100));
        name2 = dayTaskNameVec.at(_taskType2-100);
    }
    
    if(_taskType3<100)
    {
        num3 = taskManager->getTaskNum((TaskManager::NewbieTaskType)(_taskType3));
        max3 = taskManager->getTaskMaxNum((TaskManager::NewbieTaskType)(_taskType3));
        name3 = newTaskNameVec.at(_taskType3);
    }
    else
    {
        num3 = taskManager->getTaskNum((TaskManager::DayTaskType)(_taskType3-100));
        max3 = taskManager->getTaskMaxNum((TaskManager::DayTaskType)(_taskType3-100));
        name3 = dayTaskNameVec.at(_taskType3-100);
    }
    //完成度
    Text_TaskNum1->setString(StringUtils::format("%d/%d",num1,max1));
    Text_TaskNum2->setString(StringUtils::format("%d/%d",num2,max2));
    Text_TaskNum3->setString(StringUtils::format("%d/%d",num3,max3));
    //完成度
    LoadingBar_task1->setPercent((float)num1/(float)max1 * 100);
    LoadingBar_task2->setPercent((float)num2/(float)max2 * 100);
    LoadingBar_task3->setPercent((float)num3/(float)max3 * 100);
    //描述控制字体大小
    Text_miaoshu1->setFontSize(getFontSize(_taskType1));
    Text_miaoshu2->setFontSize(getFontSize(_taskType2));
    Text_miaoshu3->setFontSize(getFontSize(_taskType3));

    Text_miaoshu1->setString(name1);
    Text_miaoshu2->setString(name2);
    Text_miaoshu3->setString(name3);
    
    //任务是否完成
    isTask1 = taskManager->getIsTask(_taskType1);
    isTask2 = taskManager->getIsTask(_taskType2);
    isTask3 = taskManager->getIsTask(_taskType3);
    if(isTask1)
    {
        LoadingBar_task1->setPercent(100);
        Text_TaskNum1->setString(StringUtils::format("%d/%d",max1,max1));
    }
    if(isTask2)
    {
        LoadingBar_task2->setPercent(100);
        Text_TaskNum2->setString(StringUtils::format("%d/%d",max2,max2));
    }
    if(isTask3)
    {
        LoadingBar_task3->setPercent(100);
        Text_TaskNum3->setString(StringUtils::format("%d/%d",max3,max3));
    }
    //宝箱是否打开
    isBox1 = taskManager->getIsTaskBox(_taskType1);
    isBox2 = taskManager->getIsTaskBox(_taskType2);
    isBox3 = taskManager->getIsTaskBox(_taskType3);
    
    if(isBox1)
    {
        UIUtils::playInnerAction(FileNode_task1,"idle",false);
    }
    if(isBox2)
    {
        UIUtils::playInnerAction(FileNode_task2,"idle",false);
    }
    if(isBox3)
    {
        UIUtils::playInnerAction(FileNode_task3,"idle",false);
    }
    
    int pNum = 0;
    if(isTask1)
    {
        pNum++;
    }
    if(isTask2)
    {
        pNum++;
    }
    if(isTask3)
    {
        pNum++;
    }
    percentB = taskManager->getTaskPercent(true);
    LoadingBar_task->setPercent(percentB);
    //-----------防错，  防止开错宝箱
    if(percentB < 30)
    {
        _boxNum = 0;
    }
    else if(percentB < 60)
    {
        _boxNum = 1;
    }
    else if(percentB < 90)
    {
        _boxNum = 2;
    }
    //------------------------
    TaskBox_1->setSpriteFrame("Box_0.png");
    TaskBox_2->setSpriteFrame("Box2_0.png");
    TaskBox_3->setSpriteFrame("Box3_0.png");
    Panel_Box1->setVisible(false);
    Panel_Box2->setVisible(false);
    Panel_Box3->setVisible(false);
    
    if(_boxNum == 1)
    {
        TaskBox_1->setSpriteFrame("Box_2.png");
        Panel_Box1->setVisible(true);
    }
    else if(_boxNum == 2)
    {
        TaskBox_1->setSpriteFrame("Box_2.png");
        Panel_Box1->setVisible(true);
        TaskBox_2->setSpriteFrame("Box2_2.png");
        Panel_Box2->setVisible(true);
    }

    
    if(!_cb)
    {
//        auto percent = taskManager->getTaskPercent();
//        LoadingBar_task->setPercent(percent);
        openBox(0);
    }
    else
    {
        openBox(0);
    }
    getNode("Button_close")->setVisible(!_cb);
    
    getNode<TextBMFont*>("BitmapFontLabel_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
    updateCoin();
    updateDiamond();
}

void DailytaskView::openBox(int idx)
{
    if(_boxNum == 0)
    {
        percentB = TASK_M->getTaskPercent(true);
        LoadingBar_task->setPercent(percentB);
        TaskBox_1->setSpriteFrame("Box_0.png");
        TaskBox_2->setSpriteFrame("Box2_0.png");
        TaskBox_3->setSpriteFrame("Box3_0.png");
        Panel_Box1->setVisible(false);
        Panel_Box2->setVisible(false);
        Panel_Box3->setVisible(false);
    }
    
    
    //跑一次
    if(_cb||1)
    {//游戏结束弹出
        Panel_7->setOpacity(0);
        auto taskManager = TaskManager::getInstance();
        //奖励防错
        //auto id = taskManager->getTaskNum();
        //判断活跃度
        bool is = true;
        if(isTask1&&!isBox1)
        {
            taskManager->addTaskNum();
            _tempTaskType = _taskType1;
            isBox1 = true;
            //taskManager->setTaskBox(0, true);
            _coinNum = getGoldNum(_boxNum);
            _diamondNum = getDiamondNum(_boxNum);
            is = false;
            taskId = 1;
        }
        else if(isTask2&&!isBox2)
        {
            taskManager->addTaskNum();
            _tempTaskType = _taskType2;
            isBox2 = true;
            //taskManager->setTaskBox(1, true);
            _coinNum = getGoldNum(_boxNum);
            _diamondNum = getDiamondNum(_boxNum);
            is = false;
            taskId = 2;
        }
        else if(isTask3&&!isBox3)
        {
            taskManager->addTaskNum();
            _tempTaskType = _taskType3;
            isBox3 = true;
            //taskManager->setTaskBox(2, true);
            _coinNum = getGoldNum(_boxNum);
            _diamondNum = getDiamondNum(_boxNum);
            is = false;
            taskId = 3;
        }
        
        if(is)
        {
            if(_cb)
            {
                _cb();
                SCENE_M->removeLayer(this);
            }
            //点击确定后 判断是否还有未打开的宝箱
            //SCENE_M->removeLayer(this);
            //宝箱是否打开

            if(TASK_M->getAllTaskNum() != 3)
            {
                if((isTask1)||(isTask2)||(isTask3))
                {
                    fangCuoNum++;
                    updateUI();//更新任务
                    TEACH_M->nextTeachStep(this);
                }
            }
            else
            {//判断
                if((isTask1&&!isBox1)||(isTask2&&!isBox2)||(isTask3&&!isBox3)||
                   TASK_M->getIsEndTask(_taskType1,_taskType2,_taskType3))
                {
                    fangCuoNum++;
                    updateUI();//更新任务
                }
            }
            return;
        }
        
        
        SOUND_M->playEffectMusic(EffectTask);
        isReward = true;
        _boxNum++;
        SETINTEGER("task_boxNum",_boxNum);
        if(_boxNum == 1)
        {
            getNode<Text*>("Text_getGoldNum")->setString(StringUtils::format("+%d",_coinNum).c_str());
            
            //getNode<Text*>("Text_getDiamond")->setVisible(false);
            getNode<Sprite*>("Money_Gold_1")->setSpriteFrame("Money/Gold_0.png");
        }
        else if(_boxNum == 2)
        {
//            getNode<Text*>("Text_getGoldNum")->setString(StringUtils::format("+%d",_diamondNum).c_str());
//
//            //getNode<Text*>("Text_getDiamond")->setVisible(false);
//            getNode<Sprite*>("Money_Gold_1")->setSpriteFrame("Money/Baoshi_10.png");
            getNode<Text*>("Text_getGoldNum")->setString(StringUtils::format("+%d",_coinNum).c_str());
            
            //getNode<Text*>("Text_getDiamond")->setVisible(false);
            getNode<Sprite*>("Money_Gold_1")->setSpriteFrame("Money/Gold_0.png");
        }
        else if(_boxNum == 3)
        {
            getNode<Sprite*>("Money_Gold_1")->setSpriteFrame("Money/Gold_0.png");
            getNode<Text*>("Text_getGoldNum")->setString(StringUtils::format("+%d",_coinNum).c_str());
            
//            getNode<Text*>("Text_getDiamond")->setVisible(true);
//            getNode<Text*>("Text_getDiamond")->setString(StringUtils::format("+%d",_diamondNum).c_str());
        }
        
        
        auto node = this->getNode(StringUtils::format("FileNode_task%d",taskId));
        UIUtils::playInnerAction(node,"Start0",false,[node,this,taskManager](){
            //翻面后活跃度
           //初始点
            auto image_3 = UIUtils::seekNodeByName(node,"Image_3");
            auto startPoi = image_3->getContentSize()*0.5;
            startPoi = image_3->convertToWorldSpace(startPoi);
            //目标点
            //DATA_M->setCoinNum(_coinNum,true);
            auto Ui_Task = getNode("Ui_Task");
            auto targetPoi = Ui_Task->getPosition();
            targetPoi = Ui_Task->getParent()->convertToWorldSpace(targetPoi);
            //targetPoi = _rootNode->convertToNodeSpace(targetPoi);
            std::vector<Vec2> itemVec1;
            DATA_M->randVec(20,&itemVec1,100);
            REWARD_M->rewardItemAction(20,targetPoi,startPoi,itemVec1,[this,taskManager,node](){
                percentB = taskManager->getTaskPercent(true);
                percentE = percentB+33.33f;//taskManager->getTaskPercent();//
                taskManager->setOldPercent(percentE);
                LoadingBar_task->setPercent(percentB);
                isBar = true;
            },"Activity",this,[this](){
                //SOUND_M->playEffectMusic(EffectGetGem);
            },[this](){
                //SOUND_M->playEffectMusic(EffectGetGem);
            });
            UIUtils::removeLastFrameFunc(node);//防错
        });//完成任务翻面
    }
}


void DailytaskView::updateCoin(bool isDelay)
{
    auto text = getNode<TextBMFont*>("BitmapFontLabel_gold");
    auto vec = text->getChildren();
    for(auto child:vec)
    {
        auto grouwup = dynamic_cast<GrowupNode*>(child);
        if(grouwup)
        {
            grouwup->unTextSchedule();
        }
    }
    if(isDelay)
    {//2.45
        //auto text = getNode<TextBMFont*>("BitmapFontLabel_gold");
        auto str = text->getString();
        _coinNum2 = UIUtils::stoii(str);
        auto num = DATA_M->getCoinNum();
        auto tempNum = num - _coinNum2;
        if(tempNum <= 0)
        {
            text->setString(StringUtils::toString(num));
            return;
        }
        float time = 0;
        if(tempNum >= 15)
        {
            time = 0.75/FLYSPEED;
        }
        else
        {
            time = 0.05/FLYSPEED * tempNum;
        }
        auto grouwup = GrowupNode::create();
        text->addChild(grouwup);
        grouwup->startGrouwup(text, _coinNum2, num, time, "",[this, grouwup](){
            //UIUtils::playInnerAction(FileNode_gold, "jump", false);
            grouwup->removeFromParent();
        });
    }
    else
    {
        int coinNum = DATA_M->getCoinNum();
        text->setString(StringUtils::toString(coinNum));
    }
}

void DailytaskView::updateDiamond(bool isDelay)
{
//    auto text = getNode<TextBMFont*>("BitmapFontLabel_diamond");
//    auto vec = text->getChildren();
//    for(auto child:vec)
//    {
//        auto grouwup = dynamic_cast<GrowupNode*>(child);
//        if(grouwup)
//        {
//            grouwup->unTextSchedule();
//        }
//    }
//    if(isDelay)
//    {
//        //auto text = getNode<TextBMFont*>("BitmapFontLabel_diamond");
//        auto str = text->getString();
//        _diamondNum2 = UIUtils::stoii(str);
//        auto num = DATA_M->getDiamond();
//        auto tempNum = num - _diamondNum2;
//        if(tempNum <= 0)
//        {
//            text->setString(StringUtils::toString(num));
//            return;
//        }
//        float time = 0;
//        if(tempNum >= 15)
//        {
//            time = 0.75/FLYSPEED;
//        }
//        else
//        {
//            time = 0.05/FLYSPEED * tempNum;
//        }
//        auto grouwup = GrowupNode::create();
//        text->addChild(grouwup);
//        grouwup->startGrouwup(text, _diamondNum2, num, time, [this, grouwup](){
//            //UIUtils::playInnerAction(FileNode_gold, "jump", false);
//            grouwup->removeFromParent();
//        });
//    }
//    else
//    {
//        int diamondNum = DATA_M->getDiamond();
//        text->setString(StringUtils::toString(diamondNum));
//    }
}

void DailytaskView::onEnter()
{
    BaseLayer::onEnter();
    UIUtils::FIRAnalyticsEventWithPrefix("DailytaskView");
}
void DailytaskView::onExit()
{
    BaseLayer::onExit();
    if(_boxNum >= 3)_boxNum = 0;
    SETINTEGER("task_boxNum",_boxNum);
    EVENT_M->removeListener("event_game_update_coin",this);
    EVENT_M->removeListener("event_game_update_diamond",this);
//    SCENE_M->getLobby()->isShowTop(true);
}

void DailytaskView::jumpLayer(int type)
{
    auto isunlock = TEACH_M->isDailyLevelUnlock();
    if(!isunlock)
    {
        return;
    }
    TEACH_M->endTeach("");
    if(type < 100)
    {
        if((int)TaskManager::NewbieTaskType::CLASSIC == type||(int)TaskManager::NewbieTaskType::MAGIC == type)
        {//转到经典模式  使用魔法棒
            //更新ui。 单张三张 困难简单
            auto home = dynamic_cast<HomeView*>(_mainLobby->setTab(MainLobby::Tab::Home));
            home->setHard(true);
            home->setMode(true);
            DATA_M->setGameType(DataManager::GameType::Huo);
            DATA_M->setIsThreeModel(false);
            _mainLobby->startGame(true);
        }
        else if((int)TaskManager::NewbieTaskType::DAILY == type||(int)TaskManager::NewbieTaskType::ADSORDAILY == type||(int)TaskManager::NewbieTaskType::BRONZEREWARD == type||(int)TaskManager::NewbieTaskType::SILVERAWARD == type||(int)TaskManager::NewbieTaskType::GOLDAWARD == type||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == type)
        {//转到挑战  奖杯也转
//            _mainLobby->setTab(MainLobby::Tab::Daily);
//            _mainLobby->startDaily();
        }
//        else if((int)TaskManager::NewbieTaskType::LEVEL == type)
//        {//转到关卡
//            _mainLobby->setTab(MainLobby::Tab::Level);
//            _mainLobby->startLevel();
//        }
        else if((int)TaskManager::NewbieTaskType::GOLDBOX == type||(int)TaskManager::NewbieTaskType::DIAMONDBOX == type)
        {//跳转商店
//            _mainLobby->setTab(MainLobby::Tab::Store);
        }
        else if((int)TaskManager::NewbieTaskType::GAMEBG == type)
        {//转到背包 背景
/*
 None,
 BACKGROUND,
 POKER_FORE,
 POKER_BACK,
 POKER,
 MUSIC,
 PROPS,
 */
            _mainLobby->showBag((int)BagView::Tab::FASHTANK);
        }
        else if((int)TaskManager::NewbieTaskType::CARDBG == type)
        {//牌背
            _mainLobby->showBag((int)BagView::Tab::POKER_BACK);
        }
        else if((int)TaskManager::NewbieTaskType::CARDFACE == type)
        {//牌面
            _mainLobby->showBag((int)BagView::Tab::POKER_FORE);
        }
        else if((int)TaskManager::NewbieTaskType::MUSIC == type)
        {//音乐
            _mainLobby->showBag((int)BagView::Tab::MUSIC);
        }
    }
    else
    {
        type -= 100;
        if((int)TaskManager::DayTaskType::ONECLASSIC == type||(int)TaskManager::DayTaskType::THREECLASSIC == type)
        {//转到经典模式
//            auto home = dynamic_cast<HomeView*>(_mainLobby->setTab(MainLobby::Tab::Home));
//            home->setHard(true);
//            home->setMode(true);
            DATA_M->setGameType(DataManager::GameType::Huo);
            DATA_M->setIsThreeModel(false);
            //更新ui。 单张三张 困难简单
            _mainLobby->startGame(true);
        }
        else if((int)TaskManager::DayTaskType::FIVEHARD == type)
        {//困难模式
//            auto home = dynamic_cast<HomeView*>(_mainLobby->setTab(MainLobby::Tab::Home));
//            home->setHard(false);
//            home->setMode(true);
//            DATA_M->setGameType(DataManager::GameType::Random);
//            DATA_M->setIsThreeModel(false);
//            //更新ui。 单张三张 困难简单
//            _mainLobby->startGame(true);
        }
        else if((int)TaskManager::DayTaskType::THREEHUO == type)
        {//活局三张
//            auto home = dynamic_cast<HomeView*>(_mainLobby->setTab(MainLobby::Tab::Home));
//            home->setHard(true);
//            home->setMode(false);
//            DATA_M->setGameType(DataManager::GameType::Huo);
//            DATA_M->setIsThreeModel(true);
//            //更新ui。 单张三张 困难简单
//            _mainLobby->startGame(true);
        }
        else if((int)TaskManager::DayTaskType::THREEHARD == type)
        {//困难三张
//            auto home = dynamic_cast<HomeView*>(_mainLobby->setTab(MainLobby::Tab::Home));
//            home->setHard(false);
//            home->setMode(false);
//            DATA_M->setGameType(DataManager::GameType::Random);
//            DATA_M->setIsThreeModel(true);
//            //更新ui。 单张三张 困难简单
//            _mainLobby->startGame(true);
        }
        else if((int)TaskManager::DayTaskType::ONEDAILY == type||(int)TaskManager::DayTaskType::THREEDAILY == type||(int)TaskManager::DayTaskType::DAILYEXPERT == type||(int)TaskManager::DayTaskType::DAILYMIDDLE == type)
        {//转到挑战
//            _mainLobby->setTab(MainLobby::Tab::Daily);
//            _mainLobby->startDaily();
        }
        else if(0)
        {//转到关卡
//            _mainLobby->setTab(MainLobby::Tab::Level);
//            _mainLobby->startLevel();
        }
        else if((int)TaskManager::DayTaskType::GOLDBOX == type||(int)TaskManager::DayTaskType::DIAMONDBOX == type)
        {//跳转商店
//            _mainLobby->setTab(MainLobby::Tab::Store);
        }
        else if(0)
        {//转到背包
            //_mainLobby->showBag();
        }
    }
}

float DailytaskView::getFontSize(int type)
{
    //需要判断全部语言
    auto languageCode = DATA_M->getAllDyyStr();
    
    
    if(type == 2)
    {
        if(languageCode == "zh")
        {
            return 50;
        }
        else if(languageCode == "tw")
        {
            return 50;
        }
        else if(languageCode == "en")
        {
            return 50;
        }
        else if(languageCode == "ko")
        {
            return 45;
        }
        else if(languageCode == "ja")
        {
            return 48;
        }
        else if(languageCode == "fr")
        {
            return 48;
        }
        else if(languageCode == "de")
        {
            return 40;
        }
        else if(languageCode == "ru")
        {
            return 38;
        }
    }
    if(type == 1||type == 10||type == 11||type == 12||type == 101||type == 109)
    {
        if(languageCode == "ru")
        {
            return 38;
        }
    }
    else if(type == 9)
    {
        if(languageCode == "de")
        {
            return 48;
        }
    }
    else if(type == 109||type == 110)
    {
        if(languageCode == "fr")
        {
            return 50;
        }
        else if(languageCode == "de")
        {
            return 50;
        }
    }
    
    return 50;
}
