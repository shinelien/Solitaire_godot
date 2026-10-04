//
//  ShopManager.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by 陈 玉涛 on 2019/4/3.
//

#include "ShopManager.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "AtlasManager.h"
#include "UIUtils.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "EventObserver.h"
#include "FishManager.h"
using namespace spine;
using namespace std;
USING_NS_CC;
ShopManager* ShopManager::s_instance = nullptr;
ShopManager* ShopManager::getInstance()
{
    if (s_instance == nullptr) {
        s_instance = new ShopManager();
        s_instance->init();
    }
    return s_instance;
}

ShopManager::ShopManager()
{
    
}

void ShopManager::init() {
//    auto load_str = FileUtils::getInstance()->getStringFromFile("ShopData.json");
//    _config.Parse(load_str.c_str());
//    if (_config.HasParseError())
//    {
//        //解析出错
//        CCASSERT(true, "解析出现错误");
//    }
    
    auto load_str = FileUtils::getInstance()->getStringFromFile("data/shop2021.json");
    _shopConfig.Parse(load_str.c_str());
    if (_shopConfig.HasParseError())
    {
        //解析出错
        CCASSERT(true, "解析出现错误");
        return;
    }
    
    
    auto musicArr = _shopConfig["Music"].GetArray();
    auto cardArr = _shopConfig["CardBg"].GetArray();
    
}

const int DynamicGameBGTag = 1001011;
const int DynamicGameTopTag = 1001012;
const int DynamicGameSpineTag = 1001013;
void ShopManager::removeBG(cocos2d::Sprite* gameBg, cocos2d::Node* gamePanel)
{
    gameBg->removeChildByTag(DynamicGameBGTag);
    gamePanel->removeChildByTag(DynamicGameTopTag);
    gamePanel->removeChildByTag(DynamicGameSpineTag);
}
void ShopManager::changeGameBG(cocos2d::Sprite* gameBg, cocos2d::Node* gamePanel, int idx)
{
    gameBg->removeChildByTag(DynamicGameBGTag);
    gamePanel->removeChildByTag(DynamicGameTopTag);
    gamePanel->removeChildByTag(DynamicGameSpineTag);
    
    auto config = _config["gametheme"].GetArray()[idx].GetObject();
    string type = config["type"].GetString();
    if (type == "csb") {
        string csbFile = config["csb"].GetString();
        string csbAni = config["csbAni"].GetString();
        CCAssert(!csbFile.empty() && !csbAni.empty(), "csb must not be empty");
        if (!csbFile.empty() && !csbAni.empty()) {
            
            auto node = UIUtils::createCSBNode(csbFile + (UIUtils::IsPad()?"_pad.csb":".csb"), "loop", true);
            node->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            //auto panel = node->getChildByName("Panel_2");
            //auto sp = panel->getChildByName<Sprite*>("desktop10_33");
            //auto fr = sp->getSpriteFrame();
            gameBg->addChild(node, 0, DynamicGameBGTag);
            auto safeArea = Director::getInstance()->getSafeAreaRect();
            node->setContentSize(safeArea.size);
            if(UIUtils::IsPad())
            {
                node->setPosition(Vec2(safeArea.size.width*0.5f,safeArea.size.height*0.5f));
            }
            else
            {
                node->setPosition(Vec2(safeArea.size.width*0.5f,safeArea.size.height*0.5f));
            }
            
            cocos2d::ui::Helper::doLayout(node);
            auto top = node->getChildByName("Panel_top");
            if (top) {
                auto worldPos = top->getPosition();
                top->removeFromParentAndCleanup(false);
                gamePanel->addChild(top, 101, DynamicGameTopTag);
                top->setPosition(gamePanel->convertToNodeSpace(worldPos));
                if(UIUtils::IsPad())
                {//缩放了0.86  top放大至1
                    top->setScale(1.f/0.86f);
                }
                else
                {
                    top->setScale(1);
                }
            }
            
            
//            top = node->getChildByName("Panel_2");
//            if (top) {
//                auto worldPos = top->getPosition();
//                top->removeFromParentAndCleanup(false);
//                gamePanel->addChild(top, 101, DynamicGameTopTag);
//                top->setPosition(gamePanel->convertToNodeSpace(worldPos));
//            }
        }
    }
    else if (type == "image") {
        string image = config["image"].GetString();
        gameBg->setSpriteFrame(Sprite::create(image)->getSpriteFrame());
    }
    
    _color3bVec.clear(); // 清理颜色
    if (config.HasMember("color")) {
        auto colors = config["color"].GetArray();
        for (int i=0; i<colors.Size(); ++i) {
            string colorStr = colors[i].GetString();
            vector<string> colorVec;
            UIUtils::split(colorStr, '/', colorVec);
            _color3bVec.push_back(Color3B(UIUtils::stoii(colorVec[0]), UIUtils::stoii(colorVec[1]), UIUtils::stoii(colorVec[2])));
        }
        _color3bIdx = -1;
        //游戏开始后开始变色
        changeColor(gameBg);
    }
    
    if (config.HasMember("spine") && config.HasMember("spineAni")) {
        if (config["spine"].GetType() == rapidjson::Type::kStringType) {
            string spineFile = config["spine"].GetString();
            string spineAni = config["spineAni"].GetString();
            CCAssert(!spineFile.empty() && !spineAni.empty(), "spine must not be empty");
            if (!spineFile.empty() && !spineAni.empty()) {
                auto padding = config["spinePos"].GetArray();
                auto skeNode = SkeletonAnimation::createWithJsonFile(spineFile+".json", spineFile+".atlas", 1.f);
    //            skeNode->setDebugBonesEnabled(true);
                //层次
                auto node = gameBg->getChildByTag(DynamicGameBGTag);
                node->addChild(skeNode, 102, DynamicGameSpineTag);
                skeNode->setAnimation(0, spineAni, true);
                auto winSize = Director::getInstance()->getWinSize();
                auto pos = Vec2(padding[0].GetInt(), winSize.height-padding[1].GetInt());
                auto poi = node->convertToNodeSpace(pos);
                skeNode->setPosition(poi);
            }
        }
        else if (config["spine"].GetType() == rapidjson::Type::kArrayType) {
            auto spineFileArray = config["spine"].GetArray();
            auto spineAniArray = config["spineAni"].GetArray();
            auto spineNodeArray = config["spineNode"].GetArray();
            for (int i=0; i<spineFileArray.Size(); ++i) {
                string spineFile = spineFileArray[i].GetString();
                string spineAni = spineAniArray[i].GetString();
                string spineNode = spineNodeArray[i].GetString();
                auto node = gameBg->getChildByTag(DynamicGameBGTag);
                auto top = gamePanel->getChildByName("Panel_top");
                if (top) {
                    top->enumerateChildren("//" + spineNode, [spineFile, spineAni](Node* target)->bool{
                        auto skeNode = SkeletonAnimation::createWithJsonFile(spineFile+".json", spineFile+".atlas", 1.f);
                        //            skeNode->setDebugBonesEnabled(true);
                        target->addChild(skeNode, 102, DynamicGameSpineTag);
                        skeNode->setAnimation(0, spineAni, true);
                        return true;
                    });
                }
            }
        }
    }
    EVENT_M->sendEvent("event_game_scene_change");
    //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_scene_change");
}

void ShopManager::changeGameBG(cocos2d::Node* iconNode, int idx)
{
    auto config = _config["gametheme"].GetArray()[idx].GetObject();
    string type = config["type"].GetString();
    _color3bVec.clear(); // 清理颜色
    if (config.HasMember("color")) {
        auto colors = config["color"].GetArray();
        for (int i=0; i<colors.Size(); ++i) {
            string colorStr = colors[i].GetString();
            vector<string> colorVec;
            UIUtils::split(colorStr, '/', colorVec);
            _color3bVec.push_back(Color3B(UIUtils::stoii(colorVec[0]), UIUtils::stoii(colorVec[1]), UIUtils::stoii(colorVec[2])));
        }
        //游戏开始后开始变色
        changeColor(iconNode);
    }
    
    if (config.HasMember("spine") && config.HasMember("spineAni")) {
        if (config["spine"].GetType() == rapidjson::Type::kStringType) {
            string spineFile = config["spine"].GetString();
            string spineAni = config["spineAni"].GetString();
            CCAssert(!spineFile.empty() && !spineAni.empty(), "spine must not be empty");
            if (!spineFile.empty() && !spineAni.empty()) {
                auto padding = config["spinePos"].GetArray();
                auto skeNode = SkeletonAnimation::createWithJsonFile(spineFile+".json", spineFile+".atlas", 1.f);
    //            skeNode->setDebugBonesEnabled(true);
                //层次
                
                iconNode->addChild(skeNode, 102, DynamicGameSpineTag);
                skeNode->setAnimation(0, spineAni, true);
                auto winSize = Director::getInstance()->getWinSize();
                auto pos = Vec2(padding[0].GetInt(), winSize.height-padding[1].GetInt());
                auto poi = iconNode->convertToNodeSpace(pos);
                skeNode->setPosition(poi);
            }
        }
        else if (config["spine"].GetType() == rapidjson::Type::kArrayType) {
            auto spineFileArray = config["spine"].GetArray();
            auto spineAniArray = config["spineAni"].GetArray();
            auto spineNodeArray = config["spineNode"].GetArray();
            for (int i=0; i<spineFileArray.Size(); ++i) {
                string spineFile = spineFileArray[i].GetString();
                string spineAni = spineAniArray[i].GetString();
                string spineNode = spineNodeArray[i].GetString();
                
                auto top = iconNode->getChildByName("Panel_top");
                if (top) {
                    top->enumerateChildren("//" + spineNode, [spineFile, spineAni](Node* target)->bool{
                        auto skeNode = SkeletonAnimation::createWithJsonFile(spineFile+".json", spineFile+".atlas", 1.f);
                        //            skeNode->setDebugBonesEnabled(true);
                        target->addChild(skeNode, 102, DynamicGameSpineTag);
                        skeNode->setAnimation(0, spineAni, true);
                        return true;
                    });
                }
            }
        }
    }
}

std::string ShopManager::getSceneEffect(int idx) {
    auto config = _config["gametheme"].GetArray()[idx].GetObject();
    return string(config["bgm"].GetString()) + EffectPrefix;
}

std::string ShopManager::getSceneMusic(int idx) {
    auto config = _config["gametheme"].GetArray()[idx].GetObject();
    if (config.HasMember("music"))
        return string(config["music"].GetString()) + EffectPrefix;
    else
        return "";
}

void ShopManager::changeColor(cocos2d::Node* gameBg)
{
    if (!_color3bVec.empty()) {
        _color3bIdx++;
        if(_color3bIdx > _color3bVec.size()-1)
        {
            _color3bIdx = 0;
        }
        Color3B randomColor = _color3bVec.at(_color3bIdx);
        gameBg->enumerateChildren("//Basic1", [randomColor](Node* target)->bool{
            target->runAction(TintTo::create(1, randomColor.r, randomColor.g, randomColor.b));
            return true;
        });
    }
}

SpriteFrame* ShopManager::getSF(int shopType, int index) {
    if (shopType == 1)   //  场景
    {
        return (AtlasManager::getInstance()->getSF(1, 0, 0, index));
    }
    else if (shopType == 2) // 牌正面
    {
        return (SPRITE_M->getCardSpriteFrameByNumAndColor(13, 0, index));
    }
    else if (shopType == 3)  // 牌背面
    {
        return (SPRITE_M->getCardBgSpriteFrame(index));
    }
    else if (shopType == 4)
    {
        return SpriteFrameCache::getInstance()->getSpriteFrameByName("Musicicon.png");
    }
    return nullptr;
}

int ShopManager::getPrice(int shopType,int idx)
{
    
    if(shopType == 3)
    {
        auto array = _shopConfig["CardBg"].GetArray();
        if(idx >= array.Size()) return 0;
        return array[idx]["price"].GetInt();
    }
    else if(shopType == 5)
    {
        auto array = _shopConfig["Music"].GetArray();
        if(idx >= array.Size()) return 0;
        return array[idx]["price"].GetInt();
    }
    
    
    return -1;
}

int ShopManager::getUnlockLv(int shopType,int idx)
{
    
    if(shopType == 3)
    {
        auto array = _shopConfig["CardBg"].GetArray();
        if(idx >= array.Size()) return 0;
        return array[idx]["unlock"].GetInt();
    }
    else if(shopType == 5)
    {
        auto array = _shopConfig["Music"].GetArray();
        if(idx >= array.Size()) return 0;
        return array[idx]["unlock"].GetInt();
    }
    
    return -1;
}

int ShopManager::getFashTankUnlockLv(int idx)
{
    auto array = _shopConfig["FashTank"].GetArray();
    if(idx >= array.Size()) return -1;
    return array[idx]["unlock"].GetInt();
}

string ShopManager::getFashTankFishNum(int idx)
{
    auto array = _shopConfig["FashTank"].GetArray();
    if(idx >= array.Size()) return "";
    return array[idx]["unlockFish"].GetString();
}

int ShopManager::getFashTankUnlockNum(int idx)
{
    auto array = _shopConfig["FashTank"].GetArray();
    if(idx >= array.Size()) return 0;
    auto fishStr = array[idx]["unlockFish"].GetString();
    auto fishVec = UIUtils::split(fishStr,",");
    if(fishVec.at(0) == "") return 0;
    
    return (int)fishVec.size();
}

int ShopManager::getMaxFashTankIdx(int lv)
{
    auto array = _shopConfig["FashTank"].GetArray();
    int idx = 0;
    for(int i = 0;i < array.Size();++i)
    {
        auto templv = array[i]["unlock"].GetInt();
        if(lv < templv)
        {
            break;
        }
        idx = i;
    }
    return idx;
}

int ShopManager::getlvProp(int shopType,int lv)
{
    int idx = -1;
    if(shopType == 3)
    {
        auto array = _shopConfig["CardBg"].GetArray();
        
        for(int i = 1;i < array.Size();++i)
        {
            auto templv = array[i]["unlock"].GetInt();
            if(lv < templv)
            {
                break;
            }
            idx = i;
        }
    }
    else if(shopType == 5)
    {
        auto array = _shopConfig["Music"].GetArray();
        for(int i = 0;i < array.Size();++i)
        {
            auto templv = array[i]["unlock"].GetInt();
            if(lv < templv)
            {
                break;
            }
            idx = i;
        }
    }
    return idx;
}


vector<int> ShopManager::getLvUnlock(int lv)
{
    auto cardBgArray = _shopConfig["CardBg"].GetArray();
    bool isLiWu = false;
    bool isFish = false;
    bool isFashTank = false;
    for(int i = 0;i < cardBgArray.Size();++i)
    {
        auto unlockLv = cardBgArray[i]["unlock"].GetInt();
        if(lv == unlockLv)
        {
            isLiWu = true;
            break;
        }
    }
    auto musicArray = _shopConfig["Music"].GetArray();
    for(int i = 0;i < musicArray.Size();++i)
    {
        auto unlockLv = musicArray[i]["unlock"].GetInt();
        if(lv == unlockLv)
        {
            isLiWu = true;
            break;
        }
    }
    
    auto fashTankArray = _shopConfig["FashTank"].GetArray();
    for(int i = 0;i < fashTankArray.Size();++i)
    {
        if(isFashTank)break;
        auto unlock = fashTankArray[i]["unlock"].GetInt();
        if(lv == unlock)
        {
            isFashTank = true;
            break;
        }
    }
    
    auto fishManager = FishManager::getInstance();
    //不是-1 就是有鱼
    isFish = fishManager->getLvUnlock(lv) != -1;
    
    int type = -1;
    vector<int> vec;
    
    
    if(isFish)
    {
        type = 0;
        vec.push_back(type);
    }
    
    if(isFashTank)
    {
        type = 1;
        vec.push_back(type);
    }
    
    if(isLiWu)
    {
        type = 2;
        vec.push_back(type);
    }
    
    return vec;
}
