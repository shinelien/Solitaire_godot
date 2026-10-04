//
//  ShopManager.hpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by 陈 玉涛 on 2019/4/3.
//

#ifndef ShopManager_hpp
#define ShopManager_hpp

#include <external/json/document.h>
#include "cocos2d.h"
#include <string>
#include <vector>

class ShopManager {
public:
    static ShopManager* getInstance();
    
    void changeGameBG(cocos2d::Sprite* gameBg, cocos2d::Node* gamePanel, int idx);
    void changeGameBG(cocos2d::Node* iconNode, int idx);
    std::string getSceneEffect(int idx);
    std::string getSceneMusic(int idx);
    void changeColor(cocos2d::Node* gameBg);
    cocos2d::SpriteFrame* getSF(int shopType, int index);
    void removeBG(cocos2d::Sprite* gameBg, cocos2d::Node* gamePanel);
    
    int getPrice(int shopType,int idx);
    int getUnlockLv(int shopType,int idx);
    int getFashTankUnlockLv(int idx);
    std::string getFashTankFishNum(int idx);
    int getFashTankUnlockNum(int idx);
    int getMaxFashTankIdx(int lv);
    std::vector<int> getLvUnlock(int lv);
    int getlvProp(int shopType,int lv);
    
    
protected:
    void init();
private:
    ShopManager();
    
    static ShopManager* s_instance;
    rapidjson::Document _config;
    rapidjson::Document _shopConfig;
    std::vector<cocos2d::Color3B> _color3bVec;
    int _color3bIdx = 0;
};

#endif /* ShopManager_hpp */
