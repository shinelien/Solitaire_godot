//
//  FishManager.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by 宋 on 2021/4/28.
//

#include <stdio.h>
#include "FishManager.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "DataManager.h"
FishManager* FishManager::s_instance = nullptr;
FishManager* FishManager::getInstance()
{
    if (s_instance == nullptr) {
        s_instance = new FishManager();
        s_instance->init();
    }
    return s_instance;
}

FishManager::FishManager()
{
    for (int i=0; i<FISH_NUM; i++) {
        auto jsonpath = StringUtils::format("res/fish/fish%d/skeleton.json",i);
        auto atlaspath = StringUtils::format("res/fish/fish%d/skeleton.atlas",i);
        if(i > 3&&i < 7)
        {
            jsonpath = "res/fish/fish4-5-6/skeleton.json";
//            atlaspath = "res/fish/fish4-5-6/skeleton.atlas";
        }
        else if(i > 6&&i < 9)
        {
            jsonpath = "res/fish/fish7-8/skeleton.json";
//            atlaspath = "res/fish/fish7-8/skeleton.atlas";
        }
        else if(i > 8&&i < 11)
        {
            jsonpath = "res/fish/fish9-10/skeleton.json";
//            atlaspath = "res/fish/fish9-10/skeleton.atlas";
        }
        else if(i > 11&&i < 14)
        {
            jsonpath = "res/fish/fish12-13/skeleton.json";
//            atlaspath = "res/fish/fish12-13/skeleton.atlas";
        }
        atlaspath = "res/fish18_shark.atlas";
        spine::SkeletonAnimation::readSkeletonDataToCache(StringUtils::format("Fish_%d", i),jsonpath,atlaspath);
    }
    
    spine::SkeletonAnimation::readSkeletonDataToCache("fishwin","res/pk/fishspine.json","res/pk/fishspine.atlas");
    
    isEle = false;
}

FishManager::~FishManager()
{
    
}

void FishManager::init()
{
    auto load_str = FileUtils::getInstance()->getStringFromFile("fish.json");
    _config.Parse(load_str.c_str());
    if (_config.HasParseError())
    {
        //解析出错
        CCASSERT(true, "解析出现错误");
        return;
    }
    
}

int FishManager::getPrice(int idx)
{
    auto array = _config["totalCNT"].GetArray();
    if(idx >= array.Size()) return 0;
    return array[idx]["price"].GetInt();
}

int FishManager::getUnlockLv(int idx)
{
    auto array = _config["totalCNT"].GetArray();
    if(idx >= array.Size()) return 0;
    return array[idx]["unlock"].GetInt();
}



spine::SkeletonAnimation * FishManager::getFishSpine(int type)
{
//    auto jsonpath = StringUtils::format("res/fish/fish%d/skeleton.json",type);
//    auto atlaspath = StringUtils::format("res/fish/fish%d/skeleton.atlas",type);
//    if((int)type > 3&&(int)type < 7)
//    {
//        jsonpath = "res/fish/fish4-5-6/skeleton.json";
//        atlaspath = "res/fish/fish4-5-6/skeleton.atlas";
//    }
//    else if((int)type > 6&&(int)type < 9)
//    {
//        jsonpath = "res/fish/fish7-8/skeleton.json";
//        atlaspath = "res/fish/fish7-8/skeleton.atlas";
//    }
//    else if((int)type > 8&&(int)type < 11)
//    {
//        jsonpath = "res/fish/fish9-10/skeleton.json";
//        atlaspath = "res/fish/fish9-10/skeleton.atlas";
//    }
//    else if((int)type > 11&&(int)type < 14)
//    {
//        jsonpath = "res/fish/fish12-13/skeleton.json";
//        atlaspath = "res/fish/fish12-13/skeleton.atlas";
//    }
    auto skeletonNode = spine::SkeletonAnimation::createFromCache(StringUtils::format("Fish_%d", type));
    //auto skeletonNode = spine::SkeletonAnimation::createWithJsonFile(jsonpath, atlaspath, 1.f);
    
    if(type == (int)DataManager::FishType::Fish4)
    {
        skeletonNode->setSkin("douyu1");
    }
    else if(type == (int)DataManager::FishType::Fish5)
    {
        skeletonNode->setSkin("douyu2");
    }
    else if(type == (int)DataManager::FishType::Fish6)
    {
        skeletonNode->setSkin("douyu3");
    }
    else if(type == (int)DataManager::FishType::Fish7)
    {
        skeletonNode->setSkin("taiyangyu");
    }
    else if(type == (int)DataManager::FishType::Fish8)
    {
        skeletonNode->setSkin("tiaowenyu");
    }
    else if(type == (int)DataManager::FishType::Fish9)
    {
        skeletonNode->setSkin("hudieyu1");
    }
    else if(type == (int)DataManager::FishType::Fish10)
    {
        skeletonNode->setSkin("hudieyu2");
    }
    else if(type == (int)DataManager::FishType::Fish11)
    {
        skeletonNode->setSkin("xipanyu");
    }
    else if(type == (int)DataManager::FishType::Fish12)
    {
        skeletonNode->setSkin("diaoyu");
    }
    else if(type == (int)DataManager::FishType::Fish13)
    {
        skeletonNode->setSkin("wuguoyu");
    }
    else if(type == (int)DataManager::FishType::Fish14)
    {
        skeletonNode->setSkin("shayu");
    }
    return skeletonNode;
}

int FishManager::getLvUnlock(int lv)
{
    int type = -1;
    auto array = _config["totalCNT"].GetArray();
    for(int i = 0;i < array.Size();++i)
    {
        auto unlockLv = array[i]["unlock"].GetInt();
        if(lv == unlockLv)
        {
            type = unlockLv;
            break;
        }
    }
    
    return type;
}

int FishManager::getMaxFishIdx(int lv)
{
    int idx = 0;
    auto array = _config["totalCNT"].GetArray();
    for(int i = 0;i < array.Size();++i)
    {
        auto unlockLv = array[i]["unlock"].GetInt();
        if(lv >= unlockLv)
        {
            idx++;
        }
    }
    return idx;
}

float FishManager::getNpcNum(int idx)
{
    auto array = _config["totalCNT"].GetArray();
    if(idx >= array.Size()) return 0;
    auto str = array[idx]["npcNum"].GetString();
    float f = 0;
    if(str != "")
    {
        f = std::stof(str);
    }
    return f;
}
