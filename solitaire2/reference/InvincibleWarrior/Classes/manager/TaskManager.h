//
//  TaskManager.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/25.
//

#ifndef TaskManager_h
#define TaskManager_h
#include "cocos2d.h"
# define TASK_M TaskManager::getInstance()
//最大活跃度
static float percentMax = 300;

using namespace std;
class TaskManager
{
public:
    
    
    
    enum class NewbieTaskType
    {
        GAMEBG,//使用背景
        CLASSIC,//完成一场经典
        ADSORDAILY,//观看一次视频，或三次每日挑战
        GOLDBOX,//开启一个黄金箱子
        MAGIC,//使用一次魔法棒
        CARDBG,//使用一次牌背
        CARDFACE,//使用一次牌面
        MUSIC,//使用一次音乐
        //LEVEL,//完成一次关卡
        DAILY,//完成一次每日挑战
        DIAMONDBOX,//使用一次钻石箱子
        BRONZEREWARD,//铜奖11
        SILVERAWARD,//银奖12
        GOLDAWARD,//金奖13
        DIAMONDAWARD,//钻石奖14
        NONE,
    };
    
    enum class DayTaskType
    {
        ONECLASSIC,//一次经典
        THREECLASSIC,//三次经典
        ONEDAILY,//一次每日
        THREEDAILY,//三次每日
        GOLDBOX,//黄金箱子
        DIAMONDBOX,//钻石箱子
        DAILYMIDDLE,//中等难度挑战
        DAILYEXPERT,//专家模式挑战
        FIVEHARD,//五次困难对局
        THREEHUO,//1次活局三张
        THREEHARD,//1次困难三张
        NONE,
    };
    
    
    void addNewTask(TaskManager::NewbieTaskType type);
    
    static TaskManager* getInstance();
    ~TaskManager();
    //清零
    void setTaskZero();
    float getTaskPercent(bool isOld = false);
    void setOldPercent(float percent);
    bool getIsYday();
    
    
    //分配任务
    int getTask1(bool isTask1 = false,bool isTask2 = false,bool isTask3 = false);
    int getTask2(bool isTask1 = false,bool isTask2 = false,bool isTask3 = false);
    int getTask3(bool isTask1 = false,bool isTask2 = false,bool isTask3 = false);
    
    //判断任务是否完成
    bool getIsTask(int type);
    bool getIsTask(TaskManager::NewbieTaskType type);
    bool getIsTask(TaskManager::DayTaskType type);
    //获取任务完成度
    int getTaskNum(TaskManager::NewbieTaskType type);
    int getTaskNum(TaskManager::DayTaskType type);
    int getTaskMaxNum(TaskManager::NewbieTaskType type);
    int getTaskMaxNum(TaskManager::DayTaskType type);
    
    //累计任务完成度
    void addTaskNum(int type);
    
    //新手任务 观看视频任务完成度
    void addTaskADS();
    
    //任务完成移除allTaskVec
    void removeAllTaskVec(int type);
    //宝箱是否打开
    bool getIsTaskBox(int type);
    
    void addTaskNum();
    int getTaskNum();
    
    //返回剩余任务数
    int getAllTaskNum();
    //任务窗口关闭， 清空任务记录， 打开时重新分配
    void clearTaskType();
    
    //倒数第三个任务刷新缺少的条件
    bool getIsUpdateTask(int type);
    bool getIsEndTask(int type1,int type2,int type3);
private:
    TaskManager();
    static TaskManager* _taskManager;
    
    //记录当天yday
    int game_yday;
    float _oldPercent;
    bool isYday;
    
    //任务完成个数
    int _taskNum;
    
    //记录新手任务是否完成
    vector<bool> newTaskVec;
    //记录新手任务完成度
    vector<int> newTaskNumVec;
    //是否领过了
    vector<bool> newIsTaskVec;
    
    //记录每日任务是否完成s
    vector<bool> dayTaskVec;
    //记录每日任务完成度
    vector<int> dayTaskNumVec;
    //记录每日任务是否领过了
    vector<bool> dayIsTaskVec;
    
    //接收所有任务的容器
    vector<int> allTaskVec;
    //是否领过了
    vector<bool> allIsTaskVec;
    
    //当前的三个任务
    int _taskType1;
    int _taskType2;
    int _taskType3;
    //任务下标
    int _id1,_id2,_id3;
};


#endif /* TaskManager_h */
