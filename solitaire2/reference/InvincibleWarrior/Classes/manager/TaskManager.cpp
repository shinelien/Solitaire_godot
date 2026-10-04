//
//  TaskManager.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/25.
//

#include <stdio.h>
#include "TaskManager.h"
#include "UIUtils.h"
#include "MainLobby.h"
#include "DataManager.h"

using namespace std;
vector<int> tempNewTaskNumVec{
    1,
    1,
    3,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
};

vector<int> tempDayTaskNumVec{
    1,
    3,
    1,
    3,
    1,
    1,
    1,
    1,
    5,
    1,
    3,
};

TaskManager* TaskManager::getInstance()
{
    if(!_taskManager)
    {
        _taskManager = new TaskManager();
    }
    
    return _taskManager;
}

TaskManager* TaskManager::_taskManager = nullptr;

TaskManager::TaskManager()
{
    game_yday = GETINTEGER("game_yday",0);
    auto yday = DATA_M->getYDay();
    if(game_yday!=yday)
    {//刷新任务
        SETINTEGER("game_yday",yday);
        
        //第二天了， 刷新翻牌次数
        SETINTEGER("fanPaiNum",3);
        SETINTEGER("storeNewNum",1);
        SETINTEGER("taskNewNum",1);
        SETINTEGER("sevenNewNum",1);
        SETINTEGER("lunPanNum",4);
        isYday = true;
        setTaskZero();
    }
    else
    {
        //setTaskZero();
        isYday = false;
    }
    
    
    _oldPercent = GETFLOAT("_oldPercent",1);
    _taskNum = GETINTEGER("_taskNum",1);
    //---------------------新增---------------------------
    //SETBOOL(StringUtils::format("newTask%d",13).c_str(),false);
    for(int i = 0;i<(int)NewbieTaskType::NONE;++i)
    {//新手任务是否完成
        newTaskVec.push_back(GETBOOL(StringUtils::format("newTask%d",i).c_str(),false));
    }
    //SETBOOL(StringUtils::format("newTaskNum%d",13).c_str(),0);
    for(int i = 0;i<(int)NewbieTaskType::NONE;++i)
    {//新手任务完成度
        newTaskNumVec.push_back(GETINTEGER(StringUtils::format("newTaskNum%d",i).c_str(),0));
    }
    //SETBOOL(StringUtils::format("newIsTask%d",13).c_str(),false);
    for(int i = 0;i<(int)NewbieTaskType::NONE;++i)
    {//新手任务是否领过
        newIsTaskVec.push_back(GETBOOL(StringUtils::format("newIsTask%d",i).c_str(),false));
    }
    
    //怎样补充任务列表 
    
    for(int i = 0;i<(int)DayTaskType::NONE;++i)
    {//每日任务是否完成
        dayTaskVec.push_back(GETBOOL(StringUtils::format("dayTask%d",i).c_str(),false));
    }
    
    for(int i = 0;i<(int)DayTaskType::NONE;++i)
    {//每日任务完成度
        dayTaskNumVec.push_back(GETINTEGER(StringUtils::format("dayTaskNum%d",i).c_str(),0));
    }
    
    for(int i = 0;i<(int)DayTaskType::NONE;++i)
    {//每日任务是否领过
        dayIsTaskVec.push_back(GETBOOL(StringUtils::format("dayIsTask%d",i).c_str(),false));
    }
    
    
    for(int i = 0;i<newTaskVec.size();++i)
    {
        if(!newIsTaskVec.at(i))
        {//存入新手任务中未完成的任务
            allTaskVec.push_back(i);
        }
    }
    
    for(int i = 0;i<dayTaskVec.size();++i)
    {
        if(!dayIsTaskVec.at(i))
        {//存入每日任务中未完成的任务。+100 区分两种类型任务
            allTaskVec.push_back(i+100);
        }
    }
    
    if(allTaskVec.size()<3)
    {//补位
        for(int i = dayTaskVec.size()-1;i>=0;--i)
        {
            if(allTaskVec.size() < 3)
            {
                bool is = false;
                for(int j = 0;j < allTaskVec.size();++j)
                {
                    if(i == allTaskVec.at(j)-100)
                    {
                        is = true;
                        break;
                    }
                }
                if(!is)
                {//没有重复
                    allTaskVec.push_back(i+100);
                }
            }
            else
            {
                break;
            }
        }
    }
    
    //保证容器里有三个任务 不管是否完成并且打开 奖杯算一个
    
    if(allTaskVec.size() == 3)
    {//判断里面有几个奖杯
        int num = 0;
        for(auto id:allTaskVec)
        {
            if(id < 100&&id>=10)
            {//算一个
                num++;
            }
        }
        if(num > 1)
        {//补位
            for(int i = dayTaskVec.size()-1;i>=0;--i)
            {
                if(allTaskVec.size() < 3 + num-1)
                {
                    bool is = false;
                    for(int j = 0;j < allTaskVec.size();++j)
                    {
                        if(i == allTaskVec.at(j)-100)
                        {
                            is = true;
                            break;
                        }
                    }
                    if(!is)
                    {//没有重复
                        allTaskVec.push_back(i+100);
                    }
                }
                else
                {
                    break;
                }
            }
            //排序
            sort(allTaskVec.begin(), allTaskVec.end());
        }
    }
    
    
//    _id1 = GETINTEGER("TaskId1",-1);
//    _id2 = GETINTEGER("TaskId2",-1);
//    _id3 = GETINTEGER("TaskId3",-1);
    
    
    //分配任务
    getTask1();
    getTask2();
    getTask3();
}

TaskManager::~TaskManager()
{
    
}

//清零
void TaskManager::setTaskZero()
{
    SETFLOAT("_oldPercent",1);
    
    for(int i = 0;i<(int)DayTaskType::NONE;++i)
    {//每日任务是否完成
        SETBOOL(StringUtils::format("dayTask%d",i).c_str(),false);
    }
    
    for(int i = 0;i<(int)DayTaskType::NONE;++i)
    {//每日任务完成度
        SETINTEGER(StringUtils::format("dayTaskNum%d",i).c_str(),0);
    }
    
    for(int i = 0;i<(int)DayTaskType::NONE;++i)
    {//每日任务是否领过
        SETBOOL(StringUtils::format("dayIsTask%d",i).c_str(),false);
    }
    
    FLUSH();
}

float TaskManager::getTaskPercent(bool isOld)
{
    if(isOld)
    {
        return _oldPercent;
    }
    else
    {
//        int num = 0;
//        for(int i = 0;i<3;++i)
//        {
//            if(isTask(i))
//            {
//                num++;
//            }
//        }
//        auto percent = (float)num / 3;
//        _oldPercent = percent;
//        SETFLOAT("_oldPercent",_oldPercent);
//        return percent;
    }
    
}

void TaskManager::setOldPercent(float percent)
{
    _oldPercent = percent;
    if(_oldPercent>99)
    {
        _taskNum = 1;
        SETINTEGER("_taskNum",1);
        _oldPercent = 1;
    }
    SETFLOAT("_oldPercent",_oldPercent);
}

 bool TaskManager::getIsYday()
{
    return isYday;
}
//----------------------
//0 1 2
//怎么分配任务。假如只有新手任务
int TaskManager::getTask1(bool isTask1,bool isTask2,bool isTask3)
{
    if(allTaskVec.size() > 2)
    {
        int id = 0;
        _id1 = -1;
        if(isTask1||isTask2||isTask3)
        {//有完成的才进来
            if(isTask1)
            {//本身完成了 id！=0 是0是1是2
                if(isTask2&&isTask3)
                {//都完成了 是0
                    _id1 = 0;
                }
                else if(isTask2&&!isTask3)
                {//1号2号都完成了 3号没完成 是1
                    _id1 = 1;
                }
                else if(!isTask2&&!isTask3)
                {//都没完成 是2 铜奖跳到钻石奖
                    _id1 = 2;
                }
                else if(!isTask2&&isTask3)
                {//1号和3号完成了 2号没完成 是1
                    _id1 = 1;
                }
            }
            else
            {//本身没完成  是0
                _id1 = -1;
            }
            //SETINTEGER("TaskId1",_id1);
        }
        
        
        
        
        if(_id1!=-1)
        {
            id = _id1;
        }
        if(_taskType1 >= 10&&_taskType1 <= 12&&isTask1)
        {//10 11 12 13 这个任务是奖杯
            return ++_taskType1;
        }
        _taskType1 = allTaskVec.at(id);//第一个任务
        
        int i = id;
        if(i>=100)i -=100;
        while(i < allTaskVec.size())
        {//10 11 12 13
            if((int)TaskManager::NewbieTaskType::BRONZEREWARD == _taskType2||(int)TaskManager::NewbieTaskType::SILVERAWARD == _taskType2||(int)TaskManager::NewbieTaskType::GOLDAWARD == _taskType2||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == _taskType2||(int)TaskManager::NewbieTaskType::BRONZEREWARD == _taskType3||(int)TaskManager::NewbieTaskType::SILVERAWARD == _taskType3||(int)TaskManager::NewbieTaskType::GOLDAWARD == _taskType3||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == _taskType3)
            {//铜奖 银奖 金奖 钻石奖
                if(((int)TaskManager::NewbieTaskType::BRONZEREWARD == _taskType1||(int)TaskManager::NewbieTaskType::SILVERAWARD == _taskType1||(int)TaskManager::NewbieTaskType::GOLDAWARD == _taskType1||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == _taskType1)||_taskType1 == _taskType2||_taskType1 == _taskType3)
                {
                    _taskType1 = allTaskVec.at(i);
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
            i++;
        }
        return _taskType1;
    }
    return -1;
}
int TaskManager::getTask2(bool isTask1,bool isTask2,bool isTask3)
{
    if(allTaskVec.size() > 2)
    {
        int id = 1;
        _id2 = -1;
        
        if(isTask1||isTask2||isTask3)
        {//有完成的才进来
            if(isTask2)
            {//本身完成了
                if(isTask1&&isTask3)
                {//1号和3号都完成了 是0
                    _id2 = 0;
                }
                else if(isTask1&&!isTask3)
                {//1号完成3号没完成 是2
                    _id2 = 2;
                }
                else if(!isTask1&&isTask3)
                {//1号n没完成3号完成 是1
                    _id2 = 1;
                }
                else if(!isTask1&&!isTask3)
                {//1号3号都没完成 是2
                    _id2 = 2;
                }
            }
            else
            {//本身没完成
                if(isTask1)
                {//1号完成了 是0
                    _id2 = 0;
                }
                else
                {//1号没完成 是1
                    _id2 = -1;
                }
            }
            //SETINTEGER("TaskId2",_id2);
        }
        
        
        if(_id2 != -1)
        {
            id = _id2;
        }
        if(_taskType2 >= 10&&_taskType2 <= 12&&isTask2)
        {//10 11 12 13 这个任务是奖杯
            return ++_taskType2;
        }
        _taskType2 = allTaskVec.at(id);//第二个任务
        int i = id;
        if(i>=100)i -=100;
        while(i < allTaskVec.size())
        {
            if((int)TaskManager::NewbieTaskType::BRONZEREWARD == _taskType1||(int)TaskManager::NewbieTaskType::SILVERAWARD == _taskType1||(int)TaskManager::NewbieTaskType::GOLDAWARD == _taskType1||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == _taskType1||(int)TaskManager::NewbieTaskType::BRONZEREWARD == _taskType3||(int)TaskManager::NewbieTaskType::SILVERAWARD == _taskType3||(int)TaskManager::NewbieTaskType::GOLDAWARD == _taskType3||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == _taskType3||_taskType1==_taskType2)
            {//铜奖 银奖 金奖 钻石奖'
                if(((int)TaskManager::NewbieTaskType::BRONZEREWARD == _taskType2||(int)TaskManager::NewbieTaskType::SILVERAWARD == _taskType2||(int)TaskManager::NewbieTaskType::GOLDAWARD == _taskType2||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == _taskType2)||_taskType1==_taskType2||_taskType2 == _taskType3)
                {
                    _taskType2 = allTaskVec.at(i);
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
            i++;
        }
        
        return _taskType2;
    }
    return -1;
}
int TaskManager::getTask3(bool isTask1,bool isTask2,bool isTask3)
{
    if(allTaskVec.size() > 2)
    {
        int id = 2;
        _id3 = -1;
        if(isTask1||isTask2||isTask3)
        {//有完成的才进来
            if(isTask3)
            {//本身完成了
                if(isTask1&&isTask2)
                {//1号和2号都完成了 是2
                    _id3 = 2;
                }
                else if(isTask1&&!isTask2)
                {//1号完成2号没完成 是1
                    _id3 = 1;
                }
                else if(!isTask1&&isTask2)
                {//1号没完成2号完成 是1
                    _id3 = 1;
                }
                else if(!isTask1&&!isTask2)
                {//1号和3号都没完成 是2
                    _id3 = 2;
                }
            }
            else
            {//本身没完成
                if(isTask1&&isTask2)
                {//12都完成了 是0
                    _id3 = 0;
                }
                else if(!isTask1&&isTask2)
                {//1没完成2完成 是1
                    _id3 = 1;
                }
                else if(isTask1&&!isTask2)
                {//1完成2没完成 是1
                    _id3 = 1;
                }
                else if(!isTask1&&!isTask2)
                {//12都没完成 是2
                    _id3 = -1;
                }
            }
            //SETINTEGER("TaskId3",_id3);
        }
        
        if(_id3 != -1)
        {
            id = _id3;
        }
        if(_taskType3 >= 10&&_taskType3 <= 12&&isTask3)
        {//10 11 12 13 这个任务是奖杯
            return ++_taskType3;
        }
        _taskType3 = allTaskVec.at(id);//第三个任务
        int i = id;
        if(i>=100)i -=100;
        while(i < allTaskVec.size())
        {//不是奖杯 也不是>=100
            if(((int)TaskManager::NewbieTaskType::BRONZEREWARD == _taskType2||(int)TaskManager::NewbieTaskType::SILVERAWARD == _taskType2||(int)TaskManager::NewbieTaskType::GOLDAWARD == _taskType2||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == _taskType2)||((int)TaskManager::NewbieTaskType::BRONZEREWARD == _taskType1||(int)TaskManager::NewbieTaskType::SILVERAWARD == _taskType1||(int)TaskManager::NewbieTaskType::GOLDAWARD == _taskType1||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == _taskType1)||_taskType3==_taskType2||_taskType3==_taskType1)
            {//铜奖 银奖 金奖 钻石奖
                if((int)TaskManager::NewbieTaskType::BRONZEREWARD == _taskType3||(int)TaskManager::NewbieTaskType::SILVERAWARD == _taskType3||(int)TaskManager::NewbieTaskType::GOLDAWARD == _taskType3||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == _taskType3||_taskType3==_taskType2||_taskType1==_taskType3)
                {
                    _taskType3 = allTaskVec.at(i);
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
            i++;
        }
        return _taskType3;
    }
    return -1;
}

int TaskManager::getTaskNum(TaskManager::NewbieTaskType type)
{
    return MIN(newTaskNumVec.at((int)type), tempNewTaskNumVec.at((int)type));
}
int TaskManager::getTaskNum(TaskManager::DayTaskType type)
{
    return MIN(dayTaskNumVec.at((int)type), tempDayTaskNumVec.at((int)type));
}

int TaskManager::getTaskMaxNum(TaskManager::NewbieTaskType type)
{
    return tempNewTaskNumVec.at((int)type);
}
int TaskManager::getTaskMaxNum(TaskManager::DayTaskType type)
{
    return tempDayTaskNumVec.at((int)type);
}


//判断任务是否完成

bool TaskManager::getIsTask(int type)
{
    if(type < 100)
    {
        return getIsTask((TaskManager::NewbieTaskType)type);
    }
    else
    {
        return getIsTask((TaskManager::DayTaskType)(type-100));
    }
}
bool TaskManager::getIsTask(TaskManager::NewbieTaskType type)
{
    return newTaskVec.at((int)type);
}
bool TaskManager::getIsTask(TaskManager::DayTaskType type)
{
    return dayTaskVec.at((int)type);
}

//累计任务完成度  判断任务完成
void TaskManager::addTaskNum(int type)
{
    //任务禁用，取消累积完成度
    return;
    auto lobby = SCENE_M->getLobby();
    if(_taskType1 == type||_taskType2 == type||_taskType3 == type)
    {
        if(type < 100)
        {
            auto &NumVec = newTaskNumVec;
            //任务累计一次
            auto num = NumVec.at(type);
            NumVec.at(type) = ++num;
            SETINTEGER(StringUtils::format("newTaskNum%d",type).c_str(),num);
            if(num >= tempNewTaskNumVec.at(type))
            {//任务完成
                if(lobby)
                {
                    lobby->showTaskNew();
                }
                
                auto &vec = newTaskVec;
                vec.at(type) = true;
                SETBOOL(StringUtils::format("newTask%d",type).c_str(),true);
            }
        }
        else
        {
            type = type-100;
            auto &NumVec = dayTaskNumVec;
            //任务累计一次
            auto num = NumVec.at(type);
            NumVec.at(type) = ++num;
            SETINTEGER(StringUtils::format("dayTaskNum%d",type).c_str(),num);
            if(num >= tempDayTaskNumVec.at(type))
            {//任务完成
                if(lobby)
                {
                    lobby->showTaskNew();
                }
                auto &vec = dayTaskVec;
                vec.at(type) = true;
                SETBOOL(StringUtils::format("dayTask%d",type).c_str(),true);
            }
        }
    }
    else if((int)TaskManager::NewbieTaskType::BRONZEREWARD == type||(int)TaskManager::NewbieTaskType::SILVERAWARD == type||(int)TaskManager::NewbieTaskType::GOLDAWARD == type||(int)TaskManager::NewbieTaskType::DIAMONDAWARD == type)
    {//奖杯可以累积
        auto &NumVec = newTaskNumVec;
        //任务累计一次
        auto num = NumVec.at(type);
        NumVec.at(type) = ++num;
        SETINTEGER(StringUtils::format("newTaskNum%d",type).c_str(),num);
        if(num >= tempNewTaskNumVec.at(type))
        {//任务完成
            auto &vec = newTaskVec;
            vec.at(type) = true;
            SETBOOL(StringUtils::format("newTask%d",type).c_str(),true);
        }
    }
}

void TaskManager::addTaskADS()
{//新手任务 观看视频
    auto lobby = SCENE_M->getLobby();
    if((int)TaskManager::NewbieTaskType::ADSORDAILY == _taskType1||(int)TaskManager::NewbieTaskType::ADSORDAILY == _taskType2||(int)TaskManager::NewbieTaskType::ADSORDAILY == _taskType3)
    {
        if(lobby)
        {
            lobby->showTaskNew();
        }
    }
    auto &vec = newTaskVec;
    vec.at((int)NewbieTaskType::ADSORDAILY) = true;
    SETBOOL(StringUtils::format("newTask%d",(int)NewbieTaskType::ADSORDAILY).c_str(),true);
}



void TaskManager::removeAllTaskVec(int type)
{//任务完成移除allTaskVec 并且领过了
    if(getAllTaskNum() > 3)
    {
        vector<int>::iterator it = allTaskVec.begin();
        while(it != allTaskVec.end())
        {
            auto n = *it;
            if(n == type)
            {
                it = allTaskVec.erase(it);
                if(type<100)
                {
                    auto &NumVec = newIsTaskVec;
                    //任务累计一次
                    
                    NumVec.at(type) = true;
                    SETINTEGER(StringUtils::format("newIsTask%d",type).c_str(),true);
                }
                else
                {
                    auto &NumVec = dayIsTaskVec;
                    //任务累计一次
                    
                    NumVec.at(type-100) = true;
                    SETINTEGER(StringUtils::format("dayIsTask%d",type-100).c_str(),true);
                }
            }
            else
            {
                it++;
            }
        }
    }
    else
    {
        if(type >= 10&&type < 14&&allTaskVec.size() > 3)
        {
            vector<int>::iterator it = allTaskVec.begin();
            while(it != allTaskVec.end())
            {
                auto n = *it;
                if(n == type)
                {
                    it = allTaskVec.erase(it);
                    auto &NumVec = newIsTaskVec;
                    //任务累计一次
                    NumVec.at(type) = true;
                    SETINTEGER(StringUtils::format("newIsTask%d",type).c_str(),true);
                }
                else
                {
                    it++;
                }
            }
        }
        if(type<100)
        {
            auto &NumVec = newIsTaskVec;
            //任务累计一次
            
            NumVec.at(type) = true;
            SETINTEGER(StringUtils::format("newIsTask%d",type).c_str(),true);
        }
        else
        {
            auto &NumVec = dayIsTaskVec;
            //任务累计一次
            
            NumVec.at(type-100) = true;
            SETINTEGER(StringUtils::format("dayIsTask%d",type-100).c_str(),true);
        }
    }
    ValueMap valueMap{
        {"key", Value("TaskComplete")},
        {"value", Value(type)},
    };
    UIUtils::FIRFirestoreAdd("operator", valueMap);
}

//宝箱是否打开
bool TaskManager::getIsTaskBox(int type)
{
    if(type < 100)
    {
        return newIsTaskVec.at(type);
    }
    else
    {
        return dayIsTaskVec.at(type-100);
    }
}

void TaskManager::addTaskNum()
{
    _taskNum++;
    SETINTEGER("_taskNum",_taskNum);
}
int TaskManager::getTaskNum()
{
    return _taskNum;
}

int TaskManager::getAllTaskNum()
{
    if(allTaskVec.size()>3)
    {
        int num = 0;
        for(auto id : allTaskVec)
        {
            if(id<100&&id>=10)
            {
                num++;
            }
        }
        if(allTaskVec.size()-num == 2)
        {
            return 3;
        }
    }
    return allTaskVec.size();
}

void TaskManager::clearTaskType()
{
    _taskType1 = -1;
    _taskType2 = -1;
    _taskType3 = -1;
}

bool TaskManager::getIsUpdateTask(int type)
{
    bool is = true;
    for(auto id:allTaskVec)
    {
        if(id == type)
        {
            is = false;
        }
    }
    //没有在容器中
    return is;
}


bool TaskManager::getIsEndTask(int type1,int type2,int type3)
{
    auto endTask = allTaskVec.at(allTaskVec.size()-1);
    
    //如果任务中有奖杯 并且没有到钻石奖 并且完成了，可以刷新
    bool is1 = false;
    bool is2 = false;
    bool is3 =  false;
    if(type1>=10&&type1<14)
    {
         is1 = getIsTask(type1);
    }
    else if(type2>=10&&type2<14)
    {
         is2 = getIsTask(type2);
    }
    else if(type3>=10&&type3<14)
    {
         is3 = getIsTask(type3);
    }
    if(is1||is2||is3)
    {
        return true;
    }
    //当前完成的任务不是任务列表中最后一个任务
    return endTask != type1&&endTask != type2&&endTask != type3;
}

