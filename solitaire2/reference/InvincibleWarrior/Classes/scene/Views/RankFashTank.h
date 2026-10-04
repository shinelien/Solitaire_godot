//
//  RankFashTank.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/12.
//

#ifndef RankFashTank_h
#define RankFashTank_h
#include "BaseLayer.h"
#include "Factory.hpp"
class Fish0;
class RankItem;
class ShadowsFish;
class RankView;
class RankFashTank : public BaseLayer, public Factory<RankFashTank> {
public:
    virtual ~RankFashTank();
    RankFashTank();
    void initRankFashTank(RankItem* rankItem,RankView* rankView);
    void updateUI();
    void updateDYY();
    void onEnter() override;

    void onExit() override;
    
    // 触屏事件
    bool myTouchBegan(Touch * t, Event * e);
    void myTouchMoved(Touch * t, Event * e);
    void myTouchEnded(Touch * t, Event * e);
    void myTouchCancelled(Touch * t, Event * e);
    
    void weishi();
    bool isFishY(Vec2 poi,bool isLeft);
    void createBg();
    
    void clearFish();
    void createFish();
    void fishMove();
    void fishZXMove();
    vector<Vec2> getRoute();
    
    Vec2 PointOnCubicBezier(Vec2* cp, float t);
    std::vector<Vec2> ComputeBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments);
    float BezierLenth(const std::vector<Vec2> &points, int points_count);
    void Update(float dt);
    
    std::vector<bool> updateJiQiFashTankUnlock();
private:
    void initUI() override;

    void initData() override;
    void dealButtonClick(Ref *pSender) override;

private:
    vector<int> _routesFishArr = vector<int>();
    Sprite* gameBg;
    int _randIdx;
    //---------------路线相关-----------------
    
    //鱼父
    Node*Node_Fish;
    //阴影父
    Node*Node_Shadows;
    //出生点
    Node*Node_Start;
    //记录场上的鱼
    Vector<Fish0*> _fishVec;
    Vector<ShadowsFish*> _fishSVec;
    RankItem* _rankItem;
    RankView* _rankView;
    //ceshi
    int ceshiId;
    EventListenerTouchOneByOne* _listener;
    
    //
    int _currentFashTankIdx;
    Node* FileNode_fitting2_7;
    bool _isAngle,_isLeft;
    int scaleY;
    Vec2 _tempSelfPos;
    bool _isJiQiRen;
};

#endif /* RankFashTank_h */
