//
// Created by Cyutao on 2019/1/12.
//

#ifndef NEWSPACECATSOLITAIRE_DAILYMANAGER_H
#define NEWSPACECATSOLITAIRE_DAILYMANAGER_H

static const char *const Daily_Notify_Key = "daily_notify_key";

#include "SqlCommon.h"
#include "SqlTable.h"
#include "SqlDatabase.h"
#include <external/json/document.h>
#include "cocos2d.h"
#include <string>
#include <vector>
#include "json/writer.h"

class Date {
public:
    Date();
    Date(tm *tt);
    Date(int y, int m, int d);
    
    const int Year() const { return year; }
    const int Month() const { return month; }
    const int Day() const { return day; }
    const int DayOfYear() const;
    std::string name() const { return cocos2d::StringUtils::format("%04d-%02d-%02d", year, month, day); }
    void NextMonth();
    void PreMonth();
    int subMonth(const Date &date);
    
    bool operator > (const Date &a) const{
        if (year > a.year) {
            return true;
        }
        else if (year == a.year) {
            return DayOfYear() > a.DayOfYear();
        }
        else {
            return false;
        }
    }
    bool operator == (Date &a) const{
        return year == a.year && month==a.month && day == a.day;
    }
private:
    int year, month, day;
};

static Date NoneDate;

class DailyManager {
public:
    static DailyManager *getInstance();
    static inline bool isLeayYear(int year) { return (year % 4 == 0 && year % 100 !=0)||(year % 400 ==0 ); }
    int getDays(int year, int month);
    int getCurrentDays();
    Date today();
    int CaculateWeekDay(int y, int m, int d);
    int getDayOfYeay(const Date &date);
    std::string getDeckByDay(int dayofyear, const std::string &mode);
    bool isDailyCompleted(const Date &date, const std::string &mode = "");
    int getCompleteCNT(const Date &date);
    int getMonthCompleteCNT(const Date &date);
    int getMonthPlayCNT(const Date &date);
    
    int getMonthDiamondCNT(const Date &date);
    int getTotalDiamondCNT();
    
    bool complete();
    void setCurrentDaily(const Date &date, const std::string &mode);
    std::string getMode(const std::string &mode) {
        return (mode=="3"||mode=="4")?"3":mode; // 3 和 4二选一
    }
    void setNotifyOpen(bool open);
    bool isNotifyOpen() {
        return  _notifyOpen;
    }
    void initConfig();
    
    
    void updateDailyRewards(Date date);
    void setDailyRewardCompleted(Date date,int idx,bool isCompleted);
    bool getDailyRewardCompleted(int idx);
private:
    DailyManager();
    void initDatabase();
    void init();
    
public:
    virtual ~DailyManager();
    //获取当前关卡
    Date getCurrentDate() { return _currentDate; }
    std::string getCurrentMode() { return _currentMode; }
    void insertLog(const std::string &method, const std::string &log);
    int getLogs(rapidjson::Writer<rapidjson::StringBuffer> &writer);
private:

    static DailyManager *s_instance;
    std::shared_ptr<sql::Database> _db;
    std::shared_ptr<sql::Table> _dailyTb;
    // log
    std::shared_ptr<sql::Database> _dbLog;
    std::shared_ptr<sql::Table> _logTb;
    rapidjson::Document _config;
    Date _currentDate;
    std::string _currentMode;
    bool _notifyOpen;
    
    
    //记录每日奖励三个阶段
    bool dailyRewards[3];
    
};


#endif //NEWSPACECATSOLITAIRE_DAILYMANAGER_H
