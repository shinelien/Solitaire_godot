//
// Created by  on 2020/3/20.
//

#include "TeachManager.h"
#include "SceneManager.h"
#include "TeachTalkView.h"
#include "TeachBlackView.h"
#include "TeachInterface.h"
#include "SpriteManager.h"
USING_NS_CC;

TeachManager *TeachManager::s_instance = nullptr;

TeachManager *TeachManager::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new TeachManager();
        s_instance->init();
    }
    return s_instance;
}

void TeachManager::init() {
    _totalWinTimes = UserDefault::getInstance()->getIntegerForKey("teach_win_times_key", 0);
    auto load_str = FileUtils::getInstance()->getStringFromFile("teachBureau.json");
    _config.Parse(load_str.c_str());
    if (_config.HasParseError()) {
        //解析出错
        CCASSERT(true, "解析出现错误");
    }
}

TeachManager::TeachManager() {
}

TeachManager::~TeachManager() {

}

// 获取扑克槽数据
std::shared_ptr<rapidjson::Document> TeachManager::getPokerData(const std::string &key) {
    CCASSERT(_config.HasMember(key.c_str()), "teachBureau data error!!!");
    return this->clone(_config[key.c_str()]);
}

std::shared_ptr<rapidjson::Document> TeachManager::clone(const rapidjson::Value &document) {
    auto value = std::make_shared<rapidjson::Document>();
    value->CopyFrom(document , value->GetAllocator());
    return value;
}
// 开始了一个教学
void TeachManager::startTeach(const std::string &key) {
    _isTeaching = true;
    _currentTeachKey = key;
    _currentIdx = 0;
    auto load_str = FileUtils::getInstance()->getStringFromFile("teachData.json");
    _teachConfig.Parse(load_str.c_str());
    if (_teachConfig.HasParseError()) {
        //解析出错
        CCASSERT(true, "解析出现错误");
        return;
    }
    nextTeachStep();
    
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("teachStart")},
        {"value", Value(_currentTeachKey)},
        {"v1", Value(_totalWinTimes)},
    });
}
// 下一步
void TeachManager::nextTeachStep(cocos2d::Node *node) {
    if (!_isTeaching) return;
    if (_currentTeachKey.empty() || !_teachConfig.HasMember(_currentTeachKey.c_str())) {
        endTeach(_currentTeachKey);
        return;
    }//
    
    auto array = _teachConfig[_currentTeachKey.c_str()].GetArray();
    if ("firstBureau" != _currentTeachKey || _currentIdx>=array.Size()) {
        endTeach(_currentTeachKey);
        return;
    }
    
    CCLOG("teach current key:%s idx:%d", _currentTeachKey.c_str(), _currentIdx);
    SCENE_M->removeLayerByName("TeachBlackView");
    auto obj = array[_currentIdx++].GetObject();
    string type = obj["type"].GetString();
    int next = obj.HasMember("next")?obj["next"].GetInt():0;
    bool save = obj.HasMember("save")?obj["save"].GetBool():false;
    if (type == "talk" || type == "poker" || type == "autowin") {
        auto newObj = clone(obj);
        SCENE_M->addTeachDialog(TeachTalkView::createLayerN(newObj));
    }
    else if(type == "button" || type == "item") {
        auto blackLayer = TeachBlackView::createLayerN();
//        SCENE_M->removeLayerByName(blackLayer->getName().c_str());
        SCENE_M->addTeachDialog(blackLayer);
        
        string nodeName = obj["node"].GetString();
        Node* nodeDest = nullptr;
        if (type == "item") {
            auto teachInterface = dynamic_cast<TeachInterface*>(node);
            if (teachInterface) {
                nodeDest = teachInterface->getTeachItem(nodeName, obj.HasMember("idx")?obj["idx"].GetInt():0);
            }
        }
        else {
            auto baseLayer = dynamic_cast<BaseLayer*>(node);
            if (baseLayer) {
                nodeDest = baseLayer->getNode(nodeName);
            }
        }
        if (!nodeDest) {
            nodeDest = UIUtils::seekNodeByName(node, nodeName);
        }
        if (nodeDest) {
            bool hasFinger = obj.HasMember("finger")?obj["finger"].GetBool():true;
            float x = obj.HasMember("offset")?obj["offset"].GetObject()["x"].GetFloat():0;
            if (UIUtils::IsPad())
                x = obj.HasMember("padoffset")?obj["padoffset"].GetObject()["x"].GetFloat():0;
            float y = obj.HasMember("offset")?obj["offset"].GetObject()["y"].GetFloat():0;
            if (UIUtils::IsPad())
                y = obj.HasMember("padoffset")?obj["padoffset"].GetObject()["y"].GetFloat():0;
            bool isLock = obj.HasMember("lock")?obj["lock"].GetBool():true;
            bool fingerOnce = obj.HasMember("fingerOnce")?obj["fingerOnce"].GetBool():false;
            bool allowOnce = obj.HasMember("allowOnce")?obj["allowOnce"].GetBool():false;
            bool end = obj.HasMember("end")?obj["end"].GetBool():false;
            bool under = obj.HasMember("under")?obj["under"].GetBool():false;
            if (fingerOnce)
                blackLayer->fingerOnce(nodeDest, Vec2(x, y), end);
            else
                blackLayer->highlightNode(nodeDest, hasFinger, Vec2(x, y), isLock, allowOnce, under);
        }
    }
    else if (type == "lock") {
        auto blackLayer = TeachBlackView::createLayerN();
        //        SCENE_M->removeLayerByName(blackLayer->getName().c_str());
        SCENE_M->addTeachDialog(blackLayer);
    }
    
    if (save) {
        UserDefault::getInstance()->setBoolForKey(StringUtils::format("teach_%s_completed_key", _currentTeachKey.c_str()).c_str(), true);
    }
    if (next == -1) {
        endTeach(_currentTeachKey);
    }
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("teachWorking")},
        {"value", Value(_currentTeachKey)},
        {"v1", Value(_currentIdx)},
    });
}

void TeachManager::endTeach(const std::string &key) {
    _isTeaching = false;
    SCENE_M->removeLayerByName("TeachBlackView");
    UserDefault::getInstance()->setBoolForKey(StringUtils::format("teach_%s_completed_key", _currentTeachKey.c_str()).c_str(), true);
    if (_currentTeachKey == "firstBureau") {
        //DATA_M->setCardPicType(1,0);
        SPRITE_M->changeCardSkin(1,true);
    }
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("teachEnd")},
        {"value", Value(_currentTeachKey)},
    });
    _currentTeachKey = "";
}

bool TeachManager::isTeaching(const std::string &key) const {
    if (!key.empty()) {
        if (key == _currentTeachKey)
            return _isTeaching;
        else
            return false;
    }
    else
        return _isTeaching;
}

void TeachManager::setIsTeaching(bool isTeaching) {
    _isTeaching = isTeaching;
}

// 可以触发新的引导
void TeachManager::addWinTimes()
{
    if (_totalWinTimes > 4) return;
    
    /* 先不关闭引导*/
    if (_totalWinTimes == 0) { // 第1次win后的引导
        startTeach("win_times1");
    }
    else if (_totalWinTimes == 1) { // 第2次win后的引导
        UserDefault::getInstance()->setBoolForKey(StringUtils::format("teach_%s_completed_key", "firstBureau").c_str(), true); // 赢了一关就不需要引导牌局了
        startTeach("win_times2");
    }
    UserDefault::getInstance()->setIntegerForKey("teach_win_times_key", ++_totalWinTimes);
}

bool TeachManager::isDailyLevelUnlock()
{
//    return _totalWinTimes>1;
    return true;
}

bool TeachManager::isTeachBureauOpen()
{
    return /*_totalWinTimes<2 &&*/ !UserDefault::getInstance()->getBoolForKey("teach_firstBureau_completed_key", false);
}

bool TeachManager::isTaskUnlock()
{
//    return _totalWinTimes>0;
    return true;
}

bool TeachManager::isTaskAllEnd()
{
    std::string key = "lobby_times2";
    auto keyCompleted = UserDefault::getInstance()->getBoolForKey(StringUtils::format("teach_%s_completed_key", key.c_str()).c_str(), false);
    return keyCompleted;
}

void TeachManager::triggerTeach(const std::string &key, cocos2d::Node* lobby)
{
    // 先关闭新手引导
    auto keyCompleted = UserDefault::getInstance()->getBoolForKey(StringUtils::format("teach_%s_completed_key", key.c_str()).c_str(), false);
//    auto preKeyCompleted = UserDefault::getInstance()->getBoolForKey(StringUtils::format("teach_%s_completed_key", preKey.c_str()).c_str(), false);
    if (!keyCompleted && _totalWinTimes==2) {
        startTeach(key);
        nextTeachStep(lobby);
    }
}

// 前两局固定0 1 新游戏顺序从3 4 5 6 7 8 
int TeachManager::getTeachBureauIdx(const std::string &teachBureau)
{
//    if (_totalWinTimes == 0) {
//        return 0;
//    }
    if (_currentTWT != _totalWinTimes) {
        _currentTWT = MIN(1, _totalWinTimes);
        _currentOffset = 0;
    }
    int cnt = (int)MAX(1, floor(teachBureau.size()/53));
    int idx = clampf(_currentTWT+((_currentTWT==0&&_currentOffset!=0)?1:0)+_currentOffset, 0, cnt-1);
    ++_currentOffset;
    return idx;
}
