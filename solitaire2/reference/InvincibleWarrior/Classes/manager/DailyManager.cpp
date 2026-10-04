//
// Created by Cyutao on 2019/1/12.
//

#include "DailyManager.h"
#include "SqlField.h"
#include "GameKitHelper.h"
#include "UIUtils.h"
#include "json/writer.h"

#include <vector>

using namespace std;
using namespace sql;
USING_NS_CC;

DailyManager* DailyManager::s_instance = nullptr;

Field definition_tbDaily[] =
    {
        Field(FIELD_KEY),
        Field("date", type_date, flag_not_null),
        Field("mode", type_text, flag_not_null),
        Field("completed", type_bool, flag_not_null),
        Field(DEFINITION_END),
    };
Field definition_tbLog[] =
    {
        Field(FIELD_KEY),
        Field("idx", type_int, flag_not_null),
        Field("method", type_text, flag_not_null),
        Field("log", type_text, flag_not_null),
        Field(DEFINITION_END),
    };

Date::Date():
year(1900)
,month(1)
,day(1)
{
    
}

Date::Date(tm *tt):
year(tt->tm_year+1900)
,month(tt->tm_mon+1)
,day(tt->tm_mday)
{
    
}

Date::Date(int y, int m, int d):
year(y)
,month(m)
,day(d)
{
    
}

void Date::NextMonth()
{
    if (month==12) {
        month=1;
        ++year;
    }
    else {
        ++month;
    }
}

void Date::PreMonth()
{
    if (month==1) {
        month=12;
        --year;
    }
    else {
        --month;
    }
}

int Date::subMonth(const Date &date)
{
    return (month+12-date.Month())%12;
}

const int Date::DayOfYear() const {
    static int a[12]={0,-2,-1,-1,0,0,1,2,2,3,3,4};
    int add = month>2&&(!(year%4&&year%100)||!(year%400));
    return 30*(month-1)+day+a[month-1]+add;
}

DailyManager *DailyManager::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new DailyManager();
        s_instance->init();
    }
    return s_instance;
}

DailyManager::DailyManager() {
    _notifyOpen = GETBOOL(Daily_Notify_Key, false);
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("challenge.plist", "challenge.png");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("jiangbei.plist", "jiangbei.png");
}

vector<int> DayOfMonth{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int DailyManager::getDays(int year, int month) {
    int days = DayOfMonth[month-1];
    if (month == 2) {
        return days + (isLeayYear(year)?1:0);
    }
    else {
        return days;
    }
}

Date DailyManager::today() {
    // 基于当前系统的当前日期/时间
    time_t now = std::time(0);
    CCLOG("1970 到目前经过秒数:%ld", now);
    tm *ltm = localtime(&now);
    return Date(ltm);
}

int DailyManager::getCurrentDays() {
    auto date = getCurrentDate();
    return getDays(date.Year(), date.Month());
}


int DailyManager::CaculateWeekDay(int y, int m, int d) {
    if (m == 1 || m == 2) {
        m += 12;
        y--;
    }
    int iWeek = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
//    switch (iWeek)
//    {
//        case 0: cout << "星期一" << endl; break;
//        case 1: cout << "星期二" << endl; break;
//        case 2: cout << "星期三" << endl; break;
//        case 3: cout << "星期四" << endl; break;
//        case 4: cout << "星期五" << endl; break;
//        case 5: cout << "星期六" << endl; break;
//        case 6: cout << "星期日" << endl; break;
//    }
    return iWeek==6?0:(iWeek+1);
}

void DailyManager::initDatabase() {
    _db = std::make_shared<sql::Database>();
    _dbLog = std::make_shared<sql::Database>();
    try {
        auto wirtablePath = FileUtils::getInstance()->getWritablePath();
        CCLOG("wirtablePath:%s", wirtablePath.c_str());
//        if (!_db->open(wirtablePath+"setting.db")) {
        if (!_db->open(wirtablePath+"setting_new.db")) {
            CCAssert(1, _db->errMsg().c_str());
        }
        
        _dailyTb = std::make_shared<sql::Table>(_db->getHandle(), "daily", definition_tbDaily);
        if (!_dailyTb->exists()) {
            _dailyTb->create();
        }
        
        if (!_dbLog->open(wirtablePath+"llll2g.db")) {
            CCAssert(1, _dbLog->errMsg().c_str());
        }
        _logTb = std::make_shared<sql::Table>(_dbLog->getHandle(), "log", definition_tbLog);
        if (!_logTb->exists()) {
            _logTb->create();
        }
    }
    catch (Exception e) {
        CCLOG("DB open faild:%s", e.msg().c_str());
    }
}

DailyManager::~DailyManager() {

}

void DailyManager::initConfig() {
    auto load_str = FileUtils::getInstance()->getStringFromFile("daily.json");
    _config.Parse(load_str.c_str());
    if (_config.HasParseError())
    {
        //解析出错
        CCASSERT(true, "解析出现错误");
        return;
    }
}

void DailyManager::init() {
    initConfig();
    initDatabase();
}

std::string DailyManager::getDeckByDay(int dayofyear, const std::string &mode) {
    return _config["config"].GetArray()[dayofyear].GetObject()[mode.c_str()].GetObject()["decks"].GetString();
}

int DailyManager::getDayOfYeay(const Date &date) {
    return 0;
}

//select Distinct(date), count(date) from daily where completed == 0 and date between date('2019-01-16','start of month','+1 second') and date('2019-01-16','start of month','+1 month','-1 day')
bool DailyManager::isDailyCompleted(const Date &date, const std::string &mode) {
    if (mode.empty()) {
        _dailyTb->open("date == \"" + date.name() + "\" and completed == 1");
        return _dailyTb->recordCount()>=3;
    }
    else {
        _dailyTb->open("date == \"" + date.name() + "\" and mode == \"" + mode + "\" and completed == 1");
        return _dailyTb->recordCount()>0;
    }
}
// 3 4d都是大师模式 只不过一个三张一个是四张
void DailyManager::setCurrentDaily(const Date &date, const std::string &mode) {
    _currentDate = date;
    _currentMode = mode;
}

// 暂存log
void DailyManager::insertLog(const std::string &method, const std::string &log) {
    Record record(_logTb->fields());
    auto idx = GETINTEGER("log_idx", 0);
    record.setInteger("idx", idx);
    record.setString("method", method);
    record.setString("log", log);
    _logTb->addRecord(&record);
    SETINTEGER("log_idx", ++idx);
}

int DailyManager::getLogs(rapidjson::Writer<rapidjson::StringBuffer> &writer) {
    int l = 0;
    try {
        RecordSet recordSet(_dbLog->getHandle(), definition_tbLog);
        auto result = recordSet.query(StringUtils::format("select * from log order by idx asc").c_str());
        if (result && recordSet.count() > 0)
        {
            l = recordSet.count();
            writer.Key("l");
            writer.StartArray();
            for (int i = 0; i<recordSet.count(); i++) {
                writer.StartObject();
                auto record = recordSet.getRecord(i);
                auto idx = int(record->getValue(1)->asInteger());
                writer.Key("idx");
                writer.Int(idx);
                auto method = record->getValue(2)->asString();
                writer.Key("m");
                writer.String(method.c_str());
                auto log = record->getValue(3)->asString();
                writer.Key("d");
                writer.RawValue(log.c_str(), log.size(), rapidjson::kObjectType);
                writer.EndObject();
            }
            writer.EndArray();
            _logTb->truncate(); // 清空吧
        }
    }
    catch (Exception e) {
        CCLOG("DB error:%s", e.msg().c_str());
    }
    return l;
}

bool DailyManager::complete() {
    if (!isDailyCompleted(_currentDate, _currentMode)) {
        Record record(_dailyTb->fields());
        record.setString("date", _currentDate.name());
        record.setString("mode", _currentMode);
        record.setBool("completed", true);
        
        _dailyTb->addRecord(&record);
        
        auto totalDiamonCNT = getTotalDiamondCNT();
        GameKitHelper::saveHighScore("maximum_diamon", totalDiamonCNT);
        
        cocos2d::ValueMap valueMap;
        valueMap["level"] = cocos2d::Value(_currentDate.name());
        valueMap["mode"] = cocos2d::Value(_currentMode);
        valueMap["win"] = cocos2d::Value(true);
        UIUtils::FIRAnalyticsEvent("event_gameview_dailycomplete", valueMap);
        return true;
    }
    
    return false;
}

int DailyManager::getCompleteCNT(const Date &date) {
    _dailyTb->open("date == \"" + date.name() + "\" and completed == 1");
    return _dailyTb->recordCount();
}

int DailyManager::getMonthCompleteCNT(const Date &date) {
//    _dailyTb->open(StringUtils::format("completed == 1 and date between date('%s','start of month','+1 second') and date('%s','start of month','+1 month','-1 day') group by date having count('date') > 2", date.name().c_str(), date.name().c_str()));
//    return _dailyTb->recordCount();
    return getMonthPlayCNT(date);
}

int DailyManager::getMonthPlayCNT(const Date &date) {
    _dailyTb->open(StringUtils::format("completed == 1 and date between date('%s','start of month','+1 second') and date('%s','start of month','+1 month','-1 day') group by date having count('date') > 0", date.name().c_str(), date.name().c_str()));
    return _dailyTb->recordCount();
}

int DailyManager::getMonthDiamondCNT(const Date &date)
{
    _dailyTb->open(StringUtils::format("completed == 1 and date between date('%s','start of month','+1 second') and date('%s','start of month','+1 month','-1 day') group by date having count('date') == 2", date.name().c_str(), date.name().c_str()));
    auto oneDiamondCNT = _dailyTb->recordCount();
    _dailyTb->open(StringUtils::format("completed == 1 and date between date('%s','start of month','+1 second') and date('%s','start of month','+1 month','-1 day') group by date having count('date') >= 3", date.name().c_str(), date.name().c_str()));
    auto threeDiamondCNT = _dailyTb->recordCount();
    return oneDiamondCNT+threeDiamondCNT*3;
}

int DailyManager::getTotalDiamondCNT()
{
    _dailyTb->open("completed == 1 group by date having count('date') == 2");
    auto oneDiamondCNT = _dailyTb->recordCount();
    _dailyTb->open("completed == 1 group by date having count('date') >= 3");
    auto threeDiamondCNT = _dailyTb->recordCount();
    return oneDiamondCNT+threeDiamondCNT*3;
}

void DailyManager::setNotifyOpen(bool open) {
    if (_notifyOpen != open) {
        _notifyOpen = open;
        SETBOOL(Daily_Notify_Key, open);
        UIUtils::unregistNotify(Daily_Notify_Key);
        if (open) {
            UIUtils::registNotify(4.5*60*60, Daily_Notify_Key, "daily");
        }
    }
}

void DailyManager::updateDailyRewards(Date date)
{
    for(int i = 0;i < 3;++i)
    {
        dailyRewards[i] = GETBOOL(StringUtils::format("year_%d_month_%d_id_%d",date.Year(),date.Month(),i).c_str(),false);
    }
}

void DailyManager::setDailyRewardCompleted(Date date,int idx,bool isCompleted)
{
    dailyRewards[idx] = isCompleted;
    SETBOOL(StringUtils::format("year_%d_month_%d_id_%d",date.Year(),date.Month(),idx).c_str(),isCompleted);
}

bool DailyManager::getDailyRewardCompleted(int idx)
{
    return dailyRewards[idx];
}
