//
// Created by Cyutao on 2018/10/20.
//

#ifndef SPACECATSOLITAIREGAME_LEVELMANAGER_H
#define SPACECATSOLITAIREGAME_LEVELMANAGER_H

#include <external/json/document.h>
#include "cocos2d.h"
#include <string>
#include <vector>

class LevelManager {
public:
    enum Type {
        LimitScore,
        CollectPoker,
        LimitTime,
        LimitMoves,
        TargetPoker,
        OnePoker,
        ThreePoker,
        SpeicalMode,
    };

    static LevelManager* getInstance();
    std::string getType(Type type);
    std::shared_ptr<rapidjson::Document> getLevelData(int group, int sub);
    std::shared_ptr<rapidjson::Document> getLevelData(int group);
    bool hasLevelGroup(int group);
    std::shared_ptr<rapidjson::Document> clone(const rapidjson::Value &document);
    bool checkLevelComplete(std::shared_ptr<rapidjson::Document> config);
    bool setLevelComplete(int group = -1, int sub = -1, int star = 0);
    bool setLevelComplete(std::shared_ptr<rapidjson::Document> levelData, int star);
    void setCurrentLevel(int group, int sub);
    bool isCurrentLevel(std::shared_ptr<rapidjson::Document> config);
    int getCurrentGroup();
    int getCurrentSub();
    std::string getLevelKey(int group, int sub);
    void setTotalStar(int starNum);
    int getTotalStar();
    
    int getLevelStar(int group);
    void setLevelStar(int group, int starNum);
    int getFullLevelStar(int group, int sub);
    int getFullLevelStar(std::shared_ptr<rapidjson::Document> levelData);
    void setFullLevelStar(int group, int sub, int starNum);
    
    bool isLevelComplete(std::shared_ptr<rapidjson::Document> levelData);
    bool isLevelComplete(int group, int sub);
    bool isLevelComplete(int group);
    bool isLevelUnLock(int group, int sub);
    bool isLevelUnLock(std::shared_ptr<rapidjson::Document> levelData);
    int getTotalCNT();
    std::string getShowString(std::shared_ptr<rapidjson::Document> config);
    std::string getCurrentLevelStar();
    bool analysisJsonConfig();
protected:
    bool init();
    void walkJson(rapidjson::Value &value);

private:
    LevelManager();

public:
    virtual ~LevelManager();

private:
    static LevelManager* sInstance;
    cocos2d::ValueMap _localData;
    rapidjson::Document _config;
    std::vector<std::string> _enumType;
    int _currentGroup, _currentSubGroup;
};


#endif //SPACECATSOLITAIREGAME_LEVELMANAGER_H
