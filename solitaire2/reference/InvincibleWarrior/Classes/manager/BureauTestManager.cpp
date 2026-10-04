//
//  BureauTestManager.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by 陈 玉涛 on 2020/2/19.
//

#include "BureauTestManager.h"
#include "UIUtils.h"
using namespace std;
using namespace sql;
USING_NS_CC;

BureauTestManager* BureauTestManager::s_instance = nullptr;
Field definition_tbPokerData[] =
{
    Field(FIELD_KEY),
    Field("data", type_text, flag_primary_key),
    Field("type", type_int, flag_not_null),
    Field("move_count", type_int, flag_not_null),
    Field("percent", type_int, flag_not_null),
    Field("move_steps", type_text, flag_not_null),
    Field("win_bureau", type_text, flag_not_null),
    Field(DEFINITION_END),
};

BureauTestManager::BureauTestManager()
{

}

BureauTestManager::~BureauTestManager()
{
	
}

BureauTestManager *BureauTestManager::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new BureauTestManager();
        s_instance->init();
    }
    return s_instance;
}
/*
sqlite3* dbFile = NULL;
std::string path;
path = FileUtils::getInstance()->fullPathForFilename("db1.db");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
path  = FileUtils::getInstance()->getWritablePath();
path  += "/db1.db";
FILE* file = fopen(path.c_str(), "r");
if (file == nullptr)    {
ssize_t size;
const char* data = (char*)
FileUtils::getInstance()->getFileData("db1.db", "rb", &size);
file = fopen(path.c_str(), "wb");
fwrite(data, size, 1, file);
CC_SAFE_DELETE_ARRAY(data);
}
fclose(file);
#endifCCLOG("数据库路径：%s", path.c_str());
int resultOK = sqlite3_open(path.c_str(), &dbFile);
if (resultOK != SQLITE_OK) {
sqlite3_close(dbFile);
CCLOG("数据库打开失败: %d", resultOK);
return;}
 * */
const string DBNewName = "bureau_new1000_p.db";
void BureauTestManager::moveFileToWriteablPath() {
    if (true) return; // 不玩了
    if (FileUtils::getInstance()->isFileExist(DBNewName)) return;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    auto dbPath = FileUtils::getInstance()->fullPathForFilename("data/bureau_new1000_o.db");
    auto path  = FileUtils::getInstance()->getWritablePath();
    path += "/" + DBNewName;
    FILE* file = fopen(path.c_str(), "r");
    CCLOG("12111111");
    if (file == nullptr)    {
        CCLOG("12111112");
        ssize_t size;
        const char* data = (char*) FileUtils::getInstance()->getFileData(dbPath, "rb", &size);
        CCLOG("12111112-%d", size);
        CCLOG("12111113");
        file = fopen(path.c_str(), "wb");
        CCLOG("12111114");
        fwrite(data, size, 1, file);
        CCLOG("12111115");
        CC_SAFE_DELETE_ARRAY(data);
    }
    CCLOG("12111116");
    fclose(file);
#endif
}

void BureauTestManager::init() {
    /*moveFileToWriteablPath();
    _db = std::make_shared<sql::Database>();
    _db_o = std::make_shared<sql::Database>();
    try {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        auto dbPath = FileUtils::getInstance()->fullPathForFilename(DBNewName);
#else
        auto dbPath = FileUtils::getInstance()->fullPathForFilename("data/bureau_new1000_o.db");
#endif
        auto exist = FileUtils::getInstance()->isFileExist(dbPath);
        CCLOG("db path %s:%d", dbPath.c_str(), (int)exist);
        if (!_db_o->open(dbPath)) {
            CCLOG("111");
            CCAssert(1, _db_o->errMsg().c_str());
        }
        CCLOG("222");

//        dbPath = FileUtils::getInstance()->fullPathForFilename("data/bureau_new1000.db");
//        CCLOG("wirtablePath:%s", dbPath.c_str());
//        if (!_db->open(dbPath)) {
//            CCAssert(1, _db->errMsg().c_str());
//        }
    }
    catch (Exception e) {
        CCLOG("DB open faild:%s", e.msg().c_str());
    }*/
    getXXXConfig();
}

cocos2d::ValueMap BureauTestManager::getBureauData(int steps, int percent) {
//    _dailyTb->open(StringUtils::format("move_count = %d and percent = %d", steps, percent).c_str());
    ValueMap valueMap;
    RecordSet recordSet(_db->getHandle(), definition_tbPokerData);
    auto result = recordSet.query(StringUtils::format("select * from poker_data where move_count >= %d and percent = %d ORDER BY RANDOM() limit 1", steps, percent).c_str());
    if (result && recordSet.count() > 0)
    {
        auto record = recordSet.getRecord(0);
        valueMap["data"] = cocos2d::Value(record->getValue(0)->asString());
        valueMap["type"] = cocos2d::Value(record->getValue(1)->asString());
        valueMap["move_count"] = cocos2d::Value(int(record->getValue(2)->asInteger()));
        valueMap["percent"] = cocos2d::Value(int(record->getValue(3)->asInteger()));
        valueMap["move_steps"] = cocos2d::Value(record->getValue(4)->asString());
    }
    return valueMap;
}

cocos2d::ValueMap BureauTestManager::getBureauData(const std::string &data)
{
    ValueMap valueMap;
    RecordSet recordSet(_db->getHandle(), definition_tbPokerData);
    auto result = recordSet.query(StringUtils::format("select * from poker_data where data = '%s'", data.c_str()).c_str());
    if (result && recordSet.count() > 0)
    {
        auto record = recordSet.getRecord(0);
        valueMap["data"] = cocos2d::Value(record->getValue(0)->asString());
        valueMap["type"] = cocos2d::Value(record->getValue(1)->asString());
        valueMap["move_count"] = cocos2d::Value(int(record->getValue(2)->asInteger()));
        valueMap["percent"] = cocos2d::Value(int(record->getValue(3)->asInteger()));
        valueMap["move_steps"] = cocos2d::Value(record->getValue(4)->asString());
    }
    return valueMap;
}

cocos2d::ValueMap BureauTestManager::getHardBureauData(int steps1, int steps2, int percent1, int percent2)
{
    ValueMap valueMap;
    RecordSet recordSet(_db_o->getHandle(), definition_tbPokerData);
    auto result = recordSet.query(StringUtils::format("select count(*) from poker_data where move_count > %d and move_count <= %d and percent > %d and percent <= %d", steps1, steps2, percent1, percent2).c_str());
    if (result) {
        int totalCNT = UIUtils::stoii(recordSet.getRecord(0)->getValue(0)->asString());
        CCLOG("offset is %d", totalCNT);
        result = recordSet.query(StringUtils::format("select * from poker_data where move_count > %d and move_count <= %d and percent > %d and percent <= %d LIMIT 1 OFFSET %d", steps1, steps2, percent1, percent2, random(0, totalCNT)).c_str());
        if (result && recordSet.count() > 0)
        {
            auto record = recordSet.getRecord(0);
            valueMap["data"] = cocos2d::Value(record->getValue(0)->asString());
            valueMap["move_count"] = cocos2d::Value(int(record->getValue(2)->asInteger()));
            valueMap["percent"] = cocos2d::Value(int(record->getValue(3)->asInteger()));
        }
    }
    return valueMap;
}

void BureauTestManager::getXXXConfig() {
    auto jsonName = "data/xxx.json";
    auto load_str = FileUtils::getInstance()->getStringFromFile(jsonName);

    rapidjson::Document d;
    //    std::string load_str((const char *)data.getBytes(), data.getSize());
    d.Parse<0>(load_str.c_str());
    if (d.HasParseError())
    {
        CCLOGERROR("wtf read xxx.json error");
        return;
    }

    if (d.IsObject())
    {
        for (int i=190;i<=1000;i++) {
            string key = toString(i);
            if (d.HasMember(key.c_str())) {
                auto array = d[key.c_str()].GetArray();
                _bureauRangMap[i] = std::make_shared<Vec2Int>(array[0].GetInt(), array[1].GetInt());
            }
        }
//        if (d.HasMember(attName))
//        {
//            const rapidjson::Value &ddd = d[attName];
//            return ddd.GetInt();
//        }
    }
//    return defaultValue;
}

int BureauTestManager::getHardBureauData(int percent1, int percent2) {
    percent2 = MIN(percent2, 1000);
    percent1 = MAX(percent1, 190);
    auto r1 = _bureauRangMap.at(percent1);
    auto r2 = _bureauRangMap.at(percent2);
    int idx = cocos2d::random(r2->x, r1->y);
    return idx;
}

Vec2Int::Vec2Int(int x, int y) : x(x), y(y) {}
