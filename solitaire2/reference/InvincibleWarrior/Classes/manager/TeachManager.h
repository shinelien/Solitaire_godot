//
// Created by  on 2020/3/20.
//

#ifndef NewSpaceCatSolitaire_TeachManager_H
#define NewSpaceCatSolitaire_TeachManager_H

#include <iostream>
#include <external/json/document.h>
#include "cocos2d.h"

#define TEACH_M TeachManager::getInstance()
class TeachManager {
public:
    virtual ~TeachManager();

    static TeachManager *getInstance();
    std::shared_ptr<rapidjson::Document> clone(const rapidjson::Value &document);
    std::shared_ptr<rapidjson::Document> getPokerData(const std::string &key);

    void startTeach(const std::string &key);
    void nextTeachStep(cocos2d::Node *node = nullptr);
    void endTeach(const std::string &key);
    void addWinTimes();
    void triggerTeach(const std::string &key, cocos2d::Node* lobby); // 检查触发引导
    bool isDailyLevelUnlock();
    bool isTeachBureauOpen();
    bool isTaskUnlock();
    bool isTaskAllEnd();//引导全部结束
    int getTeachBureauIdx(const std::string &teachBureau);
    std::string getCurrentTeachKey() { return _currentTeachKey; }
private:
    TeachManager();

    void init();

    static TeachManager *s_instance;
    rapidjson::Document _config;
    rapidjson::Document _teachConfig;
    std::string _currentTeachKey;
    int _currentIdx;
    bool _isTeaching = false;
public:
    bool isTeaching(const std::string &key = "") const;

    void setIsTeaching(bool isTeaching);
    int _totalWinTimes = 0, _currentTWT = -1, _currentOffset = -1;
};

#endif //NewSpaceCatSolitaire_TeachManager_H
