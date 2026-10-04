//
//  GameBackground.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/4/17.
//

#ifndef _GameBackground_h
#define _GameBackground_h

#include "BaseLayer.h"
#include "Factory.hpp"
class Fish0;
class ShadowsFish;
class RewardNode;
class GameBackground : public BaseLayer, public Factory<GameBackground> {
public:
    
    enum class RewardType
    {
        GOLD,
        EXP,
        MAGIC,
        
        NONE,
    };
    
    
    virtual ~GameBackground();
    GameBackground();
    void updateUI();
    void updateWeiShi();
    void updateDYY();
    void onEnter() override;

    void onExit() override;
    
    // 触屏事件
    // 触屏事件
    virtual bool onTouchBegan(Touch * t, Event * e) override;
    virtual void onTouchMoved(Touch * t, Event * e) override;
    virtual void onTouchEnded(Touch * t, Event * e) override;
    virtual void onTouchCancelled(Touch * t, Event * e) override;
    
    void weishi();
    void addFish(int type = -1,bool isDaily = false);
    void delateFish();
    void deleteFish(Fish0* fish);
    void deleteFish(int fishType,int fashTank);
    
    void jiasu();
    void jiansu();
    void stop();
    bool isFishY(Vec2 poi,bool isLeft);
    
    //指定配饰播放动画
    void updateBg(int unlockLv);
    void updateBg();
    void createBg();
    void clearFish();
    void createFish();
    void showBuild(bool isShow);
    
    //点鱼奖励
    void clickFishReward(Vec2 poi,Fish0* _fish = NULL);
    //这个奖励领了 移除他
    void deleteReward();
    void fishMove();
    void fishZXMove(bool isAniEnd = false);
    vector<Vec2> getRoute();
    
    Vec2 PointOnCubicBezier(Vec2* cp, float t);
    std::vector<Vec2> ComputeBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments);
    float BezierLenth(const std::vector<Vec2> &points, int points_count);
    void Update(float dt);
    Vec2 getPeiShiWorldPoi(int idx);
    void updateBuild();
    void hideBuild();
    
    void updateBuildComplete();
    vector<int> getFishIsDaily();
    bool getIsMaxHp();
    void showGuide();
private:
    void initUI() override;

    void initData() override;
    void dealButtonClick(Ref *pSender) override;

private:
    vector<int> _routesFishArr = vector<int>();

    int _randIdx;
    //---------------路线相关-----------------
    //喂食节点
    Node* Node_siliao,*Node_weishi,*Sprite_complete;
    //鱼父
    Node*Node_Fish;
    //阴影父
    Node*Node_Shadows;
    //出生点
    Node*Node_Start;
    //记录场上的鱼
    Vector<Fish0*> _fishVec;
    Vector<ShadowsFish*> _fishSVec;
    Vector<RewardNode*> _rewardVec;
    Sprite* gameBg;
    //当前使用的场景idx
    int _currentFashTankIdx;
    //场景音乐
    int SceneMusicID = -1;
    //是否是第一次点击掉落
    bool isStartClick;
    RewardType _rewardType;
    Fish0* _clickFish;
    //ceshi
    int ceshiId;
    //
    Node* FileNode_fitting2_7;
    bool _isAngle,_isLeft;
    int scaleY;
    Vec2 _tempSelfPos;
    Node* Node_build;
    Sprite* Sprite_chuiZi,*Sprite_chanZi;
    bool _isBuild,_isComplete;
    Button*Button_build;
};


#endif /* _2021MainLobby_h */
