//
// Created by Cyutao on 2019-03-26.
//

#ifndef NEWSPACECATSOLITAIRE_PLAYERMANAGER_H
#define NEWSPACECATSOLITAIRE_PLAYERMANAGER_H

#include <external/json/document.h>
#include "cocos2d.h"
#include <string>
#include <vector>

class PlayerManager {
public:
    static PlayerManager* getInstance();
    
    void init();
    int getLevel() { return _level; }
    int getOldLevel() { return _oldLevel; }
    float getExp();
    bool addExp(float exp);
//    bool unlock();   // 需要转转 真正的解锁 4/4 1/1
    float getPercent(bool old = false);
    //返回当前分段等级
    string getPartLv(int lv);
//    std::shared_ptr<rapidjson::Document> getUnlockInfo();
//    std::string getPreUnlockIconName(int lv);
//    std::string getUnlockIconName(int lv);
//    std::string getCurUnlockIconName(int lv);
//    bool isItemUnlock(int itemType, int itemId);
private:
    PlayerManager();
    virtual ~PlayerManager();

    rapidjson::Document _config;
    static PlayerManager* s_instance;
    int _level = 1, _oldLevel = 1;
    float _exp = 0.f, _oldExp = 0.f;
    std::unordered_map<std::string, int> _unlockLv;
};


#endif //NEWSPACECATSOLITAIRE_PLAYERMANAGER_H
