//
//  AtlasManager.hpp
//  WTF-mobile
//
//  Created by KK on 2019/1/21.
//

#ifndef AtlasManager_hpp
#define AtlasManager_hpp

#include "cocos2d.h"
#include <spine/spine-cocos2dx.h>

using namespace spine;

class AtlasManager {
public:
    static AtlasManager* getInstance();
    spAtlas* load(const std::string &path, const std::string &key = "");
    void load(const std::string &path, const std::string &key, void *renderObj); // 用于loading 加载
    cocos2d::SpriteFrame *getSF(const std::string &name, const std::string &key = "");
    cocos2d::SpriteFrame *getSF(int type, int number = 0, int color = 0, int picType = -1);
    spAtlasRegion* getRegion(int type, int number = 0, int color = 0,int picType = -1);
    SkeletonAnimation* getSkeletonNode(const std::string &key, const std::string &ske, const std::string &data, float scale = 1);
protected:
    ~AtlasManager();
private:
    AtlasManager();
    std::unordered_map<std::string, spAtlas*> _atlasMap;
    cocos2d::Map<std::string, SkeletonAnimation*> _skeletonMap;

    static AtlasManager* s_instance;
};


#endif /* AtlasManager_hpp */
