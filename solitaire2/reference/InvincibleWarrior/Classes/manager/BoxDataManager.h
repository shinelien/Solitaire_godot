//
// Created by  on 2020/3/26.
//

#ifndef NewSpaceCatSolitaire_BoxDataManager_H
#define NewSpaceCatSolitaire_BoxDataManager_H

#include <iostream>
#include <external/json/document.h>
#include "cocos2d.h"

USING_NS_CC;
#define BOX_M BoxDataManager::getInstance()
class BoxDataManager {
public:
    enum class LotteryType{
        Gold,
        Gem,
        Daily,
        Star
    };
    enum class LotteryTimes{
        One,
        Five,
        Daily,
        Star
    };
    virtual ~BoxDataManager();

    static BoxDataManager *getInstance();

    ValueVector startLottery(LotteryType lotteryType, LotteryTimes lotteryTimes, int money);
    std::string getKey(LotteryType lotteryType);
    std::string getKey(LotteryTimes lotteryTimes);
    
    void startTest();
    void startTest1();
    bool analysisJsonConfig();
private:
    BoxDataManager();

    void init();
    ValueMap lotteryOnce(const rapidjson::Value &doc, const char* key);
    
    static BoxDataManager *s_instance;

    rapidjson::Document _config;
    std::string _simpleResults;
    bool _isChongFu = false;
};

#endif //NewSpaceCatSolitaire_BoxDataManager_H
