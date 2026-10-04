//
//  AtlasManager.cpp
//  WTF-mobile
//
//  Created by KK on 2019/1/21.
//

#include "AtlasManager.h"
#include "DataManager.h"

USING_NS_CC;
AtlasManager* AtlasManager::s_instance = nullptr;
static std::vector<std::string> AtlasNames{"car_0_1.atlas","car_2_3.atlas","car_4_5.atlas","car_6_7.atlas"};
inline std::string getFileName(int shopType, int picType = -1){
//    picType = picType==-1?DATA_M->getCardPicType(shopType):picType;
//    return shopType==2?AtlasNames[picType/2]:"car_6_7.atlas";
    if(shopType == 2||shopType == 5||shopType == 6)
    {
        return "car_new_0_6.atlas";
    }
    return "car_new_0_1.atlas";
    
    //return "car_new_0_1.atlas";
}

inline std::string getKey(int shopType, int number = 0, int color = 0, int picType = -1){
    picType = picType==-1?DATA_M->getCardPicType(shopType):picType;
    switch (shopType) {
        case 6: // 返回花色
        {
            picType = picType == 0?picType:picType+1;
            if(picType == 3)
            {
                return number<=10?StringUtils::format("card_%d_%c", 0,'A'+color):StringUtils::format("card_%d_%c%d",picType, 'A'+color, number);
            }
            else
            {
                return number<=10?StringUtils::format("card_%d_%c", picType,'A'+color):StringUtils::format("card_%d_%c%d",picType, 'A'+color, number);
            }
            
        }
        case 5: // 返回a-13
            return StringUtils::format("card_0%d", number);
        case 4:
            return "Level_card1";
        case 3:
            return StringUtils::format("card_bg_%d", picType);
        case 2:
            return "card_fronts";
//            return StringUtils::format("card_%d_%d_%d", picType, number, color);
        case 1:
            return StringUtils::format("game_bg_%d", picType);
    }
    return "";
}

AtlasManager *AtlasManager::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new AtlasManager();
    }
    return s_instance;
}

AtlasManager::~AtlasManager() {
    // 释放atlas
    for (auto it:_atlasMap) {
        spAtlas_dispose(it.second);
    }
}

AtlasManager::AtlasManager() {
    for (int i=0; i<52; i++) {
//        getSkeletonNode(StringUtils::format("Card%d", i), "res/skeleton.json", "res/skeleton.atlas");
        //
        SkeletonAnimation::readSkeletonDataToCache(StringUtils::format("Card%d", i),"res/pk/skeleton.json", "res/pk/skeleton.atlas");
    }
}

spAtlas* AtlasManager::load(const std::string &path, const std::string &key) {
    auto key_ = key.empty()?path:key;
    auto it = _atlasMap.find(key_);
    if (it == _atlasMap.end()) {
        _atlasMap[key_] = spAtlas_createFromFile(path.c_str(), nullptr);
        return _atlasMap.at(key_);
    }
    return it->second;
}

void AtlasManager::load(const std::string &path, const std::string &key, void *renderObj) {
    auto key_ = key.empty()?path:key;
    auto it = _atlasMap.find(key_);
    if (it == _atlasMap.end()) {
        _atlasMap[key_] = spAtlas_createFromFile(path.c_str(), renderObj);
    }
}

cocos2d::SpriteFrame *AtlasManager::getSF(const std::string &name, const std::string &key) {
    spAtlasRegion *atlasRegion_ = nullptr;
    if (key.empty()) {
        for (auto it:_atlasMap) {
            auto atlasRegion = spAtlas_findRegion(it.second, name.c_str());
            if (atlasRegion!= nullptr) {
                atlasRegion_= atlasRegion;
                break;
            }
        }
    }
    else {
        auto atlas = load(key);
        if (atlas) {
            atlasRegion_ = spAtlas_findRegion(atlas, name.c_str());
        }
    }
    if (atlasRegion_) {
        return SpriteFrame::createWithTexture((Texture2D*)atlasRegion_->page->rendererObject, Rect(atlasRegion_->x, atlasRegion_->y, atlasRegion_->width, atlasRegion_->height), atlasRegion_->rotate, Vec2(atlasRegion_->offsetX, atlasRegion_->offsetY), Size(atlasRegion_->originalWidth, atlasRegion_->originalHeight));
    }
    else {
        return nullptr;
    }
}

cocos2d::SpriteFrame *AtlasManager::getSF(int type, int number, int color, int picType)
{
    return getSF(getKey(type, number, color, picType), getFileName(type, picType));
}

spAtlasRegion* AtlasManager::getRegion(int type, int number, int color,int picType)
{
    spAtlas *atlas = AtlasManager::getInstance()->load(getFileName(type,picType));
    if (atlas) {
        auto key = getKey(type, number, color,picType);
//        CCLOG("FindRegion:%s", key.c_str());
        return spAtlas_findRegion(atlas, key.c_str());
    }
    return nullptr;
}

SkeletonAnimation* AtlasManager::getSkeletonNode(const std::string &key, const std::string &ske, const std::string &data, float scale)
{
//    auto it = _skeletonMap.find(key);
//    if (it == _skeletonMap.end() ) {
//        static auto atlas = spAtlas_createFromFile(data.c_str(), 0);
        auto skeNode = SkeletonAnimation::createWithJsonFile(ske, data, scale);
//        _skeletonMap.insert(key, skeNode);
        return skeNode;
//    }
//    return it->second;
}
