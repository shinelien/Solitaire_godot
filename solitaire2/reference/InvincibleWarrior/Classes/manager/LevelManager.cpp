//
// Created by Cyutao on 2018/10/20.
//

#include "LevelManager.h"
#include "UIUtils.h"
#include <string>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "GameKitHelper.h"
#endif
USING_NS_CC;

static const char* TOTAL_STAR = "TOTAL_STAR";
static const char* LEVEL_STAR = "LEVEL_%d_STAR";
static const char* FULL_LEVEL_STAR = "%d_LEVEL_%d_STAR";
LevelManager* LevelManager::sInstance = nullptr;

LevelManager *LevelManager::getInstance() {
    if (sInstance == nullptr) {
        sInstance = new LevelManager();
        sInstance->init();
    }
    return sInstance;
}

LevelManager::LevelManager() {
    _enumType = {
        "LimitScore",
        "CollectPoker",
        "LimitTime",
        "LimitMoves",
        "TargetPoker",
        "OnePoker",
        "ThreePoker",
        "SpeicalMode",
    };
}

bool LevelManager::init() {
    if (!analysisJsonConfig())
        return false;

    return true;
}

std::string LevelManager::getType(LevelManager::Type type) {
    try {
        return _enumType.at(type);
    }
    catch (std::out_of_range e) {
        return "Error";
    }
}

bool LevelManager::analysisJsonConfig() {
    auto load_str = FileUtils::getInstance()->getStringFromFile("level.json");
    _config.Parse(load_str.c_str());
    if (_config.HasParseError())
    {
        //解析出错
        CCASSERT(true, "解析出现错误");
        return false;
    }

    walkJson(_config);
    return true;
}

void LevelManager::walkJson(rapidjson::Value &value)
{
    switch (value.GetType()) {
        case rapidjson::kNullType:break;
        case rapidjson::kFalseType:break;
        case rapidjson::kTrueType:break;
        case rapidjson::kObjectType:break;
        case rapidjson::kArrayType:break;
        case rapidjson::kStringType:break;
        case rapidjson::kNumberType:break;
    }
}

std::shared_ptr<rapidjson::Document> LevelManager::getLevelData(int group, int sub) {
    auto key = StringUtils::format("level%d", group);
    CCASSERT(_config.HasMember(key.c_str()) && _config[key.c_str()]["data"].IsArray(), "level1 data error!!!");
    return this->clone(_config[key.c_str()]["data"].GetArray()[sub]);
}

std::shared_ptr<rapidjson::Document> LevelManager::getLevelData(int group) {
    auto key = StringUtils::format("level%d", group);
    CCASSERT(_config.HasMember(key.c_str()), "level0 data error!!!");
    return this->clone(_config[key.c_str()]);
}

bool LevelManager::hasLevelGroup(int group) {
    auto key = StringUtils::format("level%d", group);
    return _config.HasMember(key.c_str());
}

LevelManager::~LevelManager() {

}

std::shared_ptr<rapidjson::Document> LevelManager::clone(const rapidjson::Value &document) {
    auto value = std::make_shared<rapidjson::Document>();
    value->CopyFrom(document , value->GetAllocator());
    return value;
}

bool LevelManager::checkLevelComplete(std::shared_ptr<rapidjson::Document> config) {
    return false;
}

bool LevelManager::setLevelComplete(std::shared_ptr<rapidjson::Document> levelData, int star)
{
    return setLevelComplete((*levelData)["group"].GetInt()-1, (*levelData)["sub"].GetInt()-1, star);
}

bool LevelManager::setLevelComplete(int group, int sub, int star) {
    auto key = getLevelKey(group, sub);
    auto fullLevelStar = getFullLevelStar(group, sub);
    if (star>fullLevelStar) {
        auto addStar = star-fullLevelStar;
        setFullLevelStar(group, sub, star);
        auto levelStar = getLevelStar(group);
        setLevelStar(group, levelStar+addStar);
        auto totalStar = getTotalStar();
        CCLOG("Win star %d", star);
        setTotalStar(totalStar+addStar);
    }
//    CCLOG("Level Complete %s-%d", key, xx);
    if (!UserDefault::getInstance()->getBoolForKey(key.c_str(),false))
    {
        UserDefault::getInstance()->setBoolForKey(key.c_str(), true);
//        auto config = getLevelData(group, sub);
//        auto winStar = (*config)["star"].GetInt();

        setCurrentLevel(group, sub);    // 记录最高关卡
        UserDefault::getInstance()->flush();
        return true;
    }
    return false;
}

void LevelManager::setCurrentLevel(int group, int sub) {
    _currentGroup = group;
    _currentSubGroup = sub;
    UserDefault::getInstance()->setIntegerForKey("CurrentGroup", group);
    UserDefault::getInstance()->setIntegerForKey("CurrentSub", sub);
    auto lv = group*10000+sub;
    UIUtils::FIRAnalyticsUserProperty("game_level_currentLevel", toString(lv));
    if (lv == 5 || lv == 10 || lv == 15) {
        ValueMap valueMap1;
        UIUtils::FIRAnalyticsEvent(StringUtils::format("event_game_level_%d", lv),
                                   valueMap1);
    }
}

std::string LevelManager::getLevelKey(int group, int sub) {
//    CCLOG("Level Complete ss:%s", (toString(group) + "_level_" + toString(sub)).c_str());
    return toString(group) + "_level_" + toString(sub);
}

int LevelManager::getTotalStar() {
    return UserDefault::getInstance()->getIntegerForKey(TOTAL_STAR, 0);
}

bool LevelManager::isLevelComplete(std::shared_ptr<rapidjson::Document> levelData) {
    return isLevelComplete((*levelData)["group"].GetInt()-1, (*levelData)["sub"].GetInt()-1);
}

bool LevelManager::isLevelComplete(int group, int sub) {
    auto key = getLevelKey(group, sub);
    auto value = UserDefault::getInstance()->getBoolForKey(getLevelKey(group, sub).c_str(),false);
    CCLOG("isLevelComplete %s__%d", key.c_str(), (int)value);
    return value;
}

void LevelManager::setTotalStar(int starNum) {
    CCLOG("Total star %d", starNum);
    UserDefault::getInstance()->setIntegerForKey(TOTAL_STAR, starNum);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    GameKitHelper::saveHighScore("level_star_rank", starNum);
#endif
    UIUtils::FIRAnalyticsUserProperty("game_level_totalstar",toString(starNum));
}

bool LevelManager::isLevelComplete(int group) {
    return true;  //getTotalStar()>=_config[StringUtils::format("level%d", group).c_str()]["unlock"].GetInt();
}

int LevelManager::getLevelStar(int group) {
    return UserDefault::getInstance()->getIntegerForKey(StringUtils::format(LEVEL_STAR, group).c_str(), 0);
}

int LevelManager::getFullLevelStar(int group, int sub) {
    return UserDefault::getInstance()->getIntegerForKey(StringUtils::format(FULL_LEVEL_STAR, group, sub).c_str(), 0);
}

int LevelManager::getFullLevelStar(std::shared_ptr<rapidjson::Document> levelData) {
    return getFullLevelStar((*levelData)["group"].GetInt()-1, (*levelData)["sub"].GetInt()-1);
}

void LevelManager::setLevelStar(int group, int starNum) {
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format(LEVEL_STAR, group).c_str(), starNum);
}

void LevelManager::setFullLevelStar(int group, int sub, int starNum) {
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format(FULL_LEVEL_STAR, group, sub).c_str(), starNum);
}

int LevelManager::getTotalCNT() {
    if (_config.HasMember("totalCNT"))
        return _config["totalCNT"].GetInt();
    else
        return 0;
}

vector<string> Suit{"♠️","♥️","♣️️","♦️"};
std::string LevelManager::getShowString(std::shared_ptr<rapidjson::Document> config) {
    if (_enumType[Type::LimitScore] == (*config)["type"].GetString()) {
        return Lang_1("100080", (*config)["score"].GetInt());
    }
    else if (_enumType[Type::CollectPoker] == (*config)["type"].GetString()) {
        string showStr{Lang("100081")};
        for (auto &str:(*config)["poker"].GetArray()) {
            vector<string> vec;
            string newStr{str.GetString()};
            UIUtils::split(newStr, '_', vec);
            showStr += Suit[atoi(vec[1].c_str())] + vec[0];
        }
        return showStr;
    }
    else if (_enumType[Type::LimitTime] == (*config)["type"].GetString()) {
        auto limitTime = (*config)["times"].GetInt();
        limitTime = (float)limitTime*2.5f;
        limitTime = limitTime - limitTime%10;
        return Lang_1("100082", limitTime);
    }
    else if (_enumType[Type::LimitMoves] == (*config)["type"].GetString()) {
        return Lang_1("100082", (*config)["moves"].GetInt());
    }
    else if (_enumType[Type::TargetPoker] == (*config)["type"].GetString()) {
        string showStr{Lang("100083")};
//        for (auto &str:(*config)["targetXY"].GetArray()) {
//            vector<string> vec;
//            string newStr{str.GetString()};
//            UIUtils::split(newStr, '_', vec);
//            showStr += Suit[atoi(vec[0].c_str())] + vec[1];
//            StringUtils::format("手机第%d列第%d张")
//        }
        return showStr;
    }
    else if (_enumType[Type::OnePoker] == (*config)["type"].GetString()) {
        return Lang("100084");
    }
    else if (_enumType[Type::ThreePoker] == (*config)["type"].GetString()) {
        return Lang("100085");
    }
    else if (_enumType[Type::SpeicalMode] == (*config)["type"].GetString()) {

    }
    return Lang("100086");
}

std::string LevelManager::getCurrentLevelStar() {
//    auto totalCNT = getTotalCNT();
//    auto lastCompletedLevel = 0;
//    for (int i=0;i<totalCNT;i++) {
//        if (!isLevelComplete(i)) {
//            break;
//        }
//        lastCompletedLevel = i;
//    }
//    auto levelData = getLevelData(lastCompletedLevel);
//    return StringUtils::format("%d / %d", getLevelStar(lastCompletedLevel), (*levelData)["total"].GetInt());
    return StringUtils::toString(getTotalStar());
}

bool LevelManager::isLevelUnLock(int group, int sub) {
//    if (1)
//        return true;
    if (group == 0 && sub == 0)
        return true;
    if (sub == 0) {
        auto key = StringUtils::format("level%d", group-1);
        if (_config.HasMember(key.c_str())) {
            auto size = _config[key.c_str()]["data"].GetArray().Size();
            return UserDefault::getInstance()->getBoolForKey(getLevelKey(group-1, size-1).c_str(),false);
        }
        else
            return false;
    }
    else
        return UserDefault::getInstance()->getBoolForKey(getLevelKey(group, sub-1).c_str(),false);
}

bool LevelManager::isLevelUnLock(std::shared_ptr<rapidjson::Document> levelData) {
    return isLevelUnLock((*levelData)["group"].GetInt()-1, (*levelData)["sub"].GetInt()-1);
}

int LevelManager::getCurrentGroup() {
    return UserDefault::getInstance()->getIntegerForKey("CurrentGroup", 0);
}

int LevelManager::getCurrentSub() {
    return UserDefault::getInstance()->getIntegerForKey("CurrentSub", 0);
}

bool LevelManager::isCurrentLevel(std::shared_ptr<rapidjson::Document> config) {
    return (*config)["group"].GetInt()-1 == _currentGroup && (*config)["sub"].GetInt()-1 == _currentSubGroup;
}
