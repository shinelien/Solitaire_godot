//
// Created by Cyutao on 2019-03-26.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "utils/UIUtils.h"
#endif
#include "PlayerManager.h"
#include "LevelManager.h"

PlayerManager* PlayerManager::s_instance = nullptr;
PlayerManager::~PlayerManager() {

}

PlayerManager::PlayerManager() {
}

PlayerManager *PlayerManager::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new PlayerManager();
        s_instance->init();
    }
    return s_instance;
}

void PlayerManager::init() {
    _exp = GETINTEGER("fish_player_exp", 1);
    _level = GETINTEGER("fish_player_level", 0);
    auto load_str = FileUtils::getInstance()->getStringFromFile("player.json");
    _config.Parse(load_str.c_str());
    if (_config.HasParseError())
    {
        //解析出错
        CCASSERT(true, "解析出现错误");
        return;
    }
    // 等级解锁
//    auto array = _config["unlocklv"].GetArray();
//    for (int i=0;i<array.Size();i++) {
//        auto obj = array[i].GetObject();
//        string key = StringUtils::format("%d_%d", obj["itemType"].GetInt(), obj["itemId"].GetInt());
//        bool defaultUnlock = obj.HasMember("default") && (strcmp(obj["default"].GetString(), "TRUE") == 0);
//        _unlockLv[key] = defaultUnlock?0:obj["unlocklv"].GetInt();
//    }
}

float PlayerManager::getExp()
{
    auto arr = _config["lv"].GetArray();
    return arr[MIN(_level, arr.Size()-1)].GetObject()["exp"].GetInt();
}

bool PlayerManager::addExp(float exp) {
    // 缓存旧数据
    _oldLevel = _level;
    _oldExp = _exp;
    auto arr = _config["lv"].GetArray();
    int lvUpExp = arr[MIN(_level, arr.Size()-1)].GetObject()["exp"].GetInt();
    
    _exp+=exp;
    if(_level >= arr.Size() - 1&&_exp>=lvUpExp)
    {//等级封顶了。先累计经验。
        //等级保持不变
        //经验累积够了 就不要累计了 经验保持满值
        //例：100级。经验20000
        _exp = lvUpExp;
        SETINTEGER("fish_player_exp", _exp);
        return false;
    }
    bool levelUp = false;
    while (_exp>=lvUpExp) {
        levelUp = true;
        _exp -= lvUpExp;
        ++_level;
        lvUpExp = arr[MIN(_level, arr.Size()-1)].GetObject()["exp"].GetInt();
    };
    SETINTEGER("fish_player_exp", _exp);
    SETINTEGER("fish_player_level", _level);
    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, [this](void*){
        UIUtils::FIRAnalyticsEvent("player_addexp", {
            {"exp", Value(_exp)},
            {"level", Value(_level)},
        });
        UIUtils::FIRFirestoreAddOP("player_addexp", toString(_exp), toString(_level));
        UIUtils::FIRFirestoreAdd("set", { // 新版用暂时diamon 代替 lv
            {"table", Value("info")},
            {"kkey", Value("diamond")},
            {"value", Value(_level)},
        });
    }, nullptr, []{});
    return levelUp;
}

float PlayerManager::getPercent(bool old)
{
    auto arr = _config["lv"].GetArray();
    if (old)
        return MIN(100, _oldExp / arr[MIN(_oldLevel, arr.Size()-1)].GetObject()["exp"].GetInt() * 100);
    else
        return _exp / arr[MIN(_level, arr.Size()-1)].GetObject()["exp"].GetInt() * 100;
}

//返回当前分段等级
string PlayerManager::getPartLv(int lv)
{
    auto arr = _config["lv"].GetArray();
    if(arr.Size() <= lv)return "0";
    return arr[lv].GetObject()["partLv"].GetString();
}

//std::shared_ptr<rapidjson::Document> PlayerManager::getUnlockInfo() {
//    auto arr = _config["lv"].GetArray();
//    auto unlockKey = arr[MIN(_oldLevel, arr.Size()-1)].GetObject()["unlock"].GetString();
//    return LevelManager::getInstance()->clone(_config["unlock"][unlockKey]);
//}
//
//const vector<string> ImageNames {
//    "",
//    "ui_lockcon2.png",
//    "ui_lockcon0.png",
//    "ui_lockcon1.png",
//    "ui_lockcon3.png",
//};
//std::string PlayerManager::getUnlockIconName(int lv) {
//    auto arr = _config["lv"].GetArray();
//    auto unlockKey = arr[MIN(lv, arr.Size()-1)].GetObject()["unlock"].GetString();
//    auto itemType = _config["unlock"][unlockKey].GetObject()["itemType"].GetInt();
//    return ImageNames.at(itemType);
//}
//
//std::string PlayerManager::getPreUnlockIconName(int lv) {
//    if (lv == 1) {
//        return "";
//    }
//    return getUnlockIconName(lv-1);
//}
//
//std::string PlayerManager::getCurUnlockIconName(int lv) {
//    return getUnlockIconName(lv);
//}

//bool PlayerManager::unlock() {
//    auto arr = _config["lv"].GetArray();
//    auto unlockKey = arr[MIN(_oldLevel, arr.Size()-1)].GetObject()["unlock"].GetString();
//    return _config["unlock"][unlockKey].GetObject()["total"].GetInt() == _config["unlock"][unlockKey].GetObject()["sub"].GetInt();
//}

//bool PlayerManager::isItemUnlock(int itemType, int itemId) {
//    auto key = StringUtils::format("%d_%d", itemType, itemId);
//    if (_unlockLv.find(key) != _unlockLv.end())
//        return _level>=_unlockLv[key];
//    else
//        return true;
//}


