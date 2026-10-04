//
//  FishGuideManager.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/30.
//

#ifndef FishGuideManager_h
#define FishGuideManager_h
#include "cocos2d.h"
#include "../AppConstant.h"
using namespace cocos2d;

#define GUIDE_M FishGuideManager::getInstance()
class FishGuideView;
class FishGuideManager
{
public:
    
    ~FishGuideManager();
    static FishGuideManager* getInstance();
    
    enum class GuideType
    {
        
        StartOne,//开局 StartOne
        WinOne,//第一次结算 WinOne
        NoMove,//任意一次无解 NoMove
        Three,//第三局 Three
        LobbyOne,//第一次返回大厅 FashTankOne
        ClickFishShop,//点鱼商店
        FishShopOne,//第一次鱼商店 FishShopOne
        GetFishOne,//第一次鱼进入水里 GetFishOne
        unlockTipsOne,//第一次碎片解锁提示 unlockTipsOne
        getSuiPian,//获得碎片
        unlockOne, //第一次解锁碎片 unlockOne
        
        unlockFashTank,//有场景解锁
        gotoLobby,//返回大厅 FashTankOne
        ClickFashTank,//点击场景引导
        UseFashTank,//点击切换场景引导
        UseFashTankTipsOne,//第一次切换场景提示
        None,
    };
    
    
    bool startGuide(GuideType type,Node* node = nullptr,Vec2 shouPoi = DEFAULTPOS,float btnScale = 1,int idx = -1);
    void nextGuide(GuideType type);
    void endGuide(GuideType type = GuideType::None,FishGuideView* layer = nullptr,int idx = -1);
    
    bool isEnd(GuideType type,int idx = -1);
    bool getIsStartGuide(GuideType type);
    
    bool isStartGuideLv(GuideType type);
    
    void fishMaxGuide();
private:
    FishGuideManager();
    static FishGuideManager* _instance;
    GuideType _guideType = GuideType::None;
    FishGuideView* _layer;
    
    std::vector<bool> isStartGuideVec;
};

#endif /* FishGuideManager_h */
