//
//  FishManager.h
//  NewSpaceCatSolitaire-mobile
//
//  Created by 宋 on 2021/4/28.
//

#ifndef FishManager_h
#define FishManager_h
#include <external/json/document.h>
#include "cocos2d.h"
#include <string>
#include <vector>
#include <spine/AnimationState.h>
namespace spine {
    class SkeletonAnimation;
}
using namespace cocos2d;
# define FISH_M FishManager::getInstance()

class FishManager
{
public:
    static FishManager* getInstance();
    void init();
    
    int getPrice(int idx);
    int getUnlockLv(int idx);
    spine::SkeletonAnimation * getFishSpine(int type);
    void setIsEle(bool ele) { isEle = ele; };
    bool getIsEle() { return isEle; }
    int getLvUnlock(int lv);
    int getMaxFishIdx(int lv);
    float getNpcNum(int idx);
private:
    FishManager();
    ~FishManager();
    rapidjson::Document _config;
    static FishManager* s_instance;
    bool isEle;
};

#endif /* FishManager_h */
