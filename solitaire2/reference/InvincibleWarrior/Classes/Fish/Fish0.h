//
//  Fish0.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/4/17.
//

#ifndef Fish0_h
#define Fish0_h
# include "cocos2d.h"
# include "BaseLayer.h"
#include "Factory.hpp"
#include "DataManager.h"
#include <spine/AnimationState.h>
namespace spine {
    class SkeletonAnimation;
}
class RankFashTank;
class ShadowsFish;
class GameBackground;
class Fish0 : public BaseLayer , public Factory<Fish0>
{
public:
    
    enum class FishAniType
    {
        LOOP,
        RUN,
        UP,
        HAPPY,
    };
    
    enum class FishMoveType
    {
        None,
        LOOP,
        RUN,
        UP,
        HAPPY,
        Stay,
        Rush,
        Admission,
        Admission2,
        WeiShi,
        Stop,
        Die,
    };
    
    enum class EmojiType
    {
        happy,
        money,
        ele,
        fanu,
    };
    
    static Fish0* createFish(GameBackground* fishTank,RankFashTank* rankFashTank,int id,DataManager::FishType type,int offlineTime = 0);
    
    Fish0(GameBackground* fishTank,RankFashTank* rankFashTank,int id,DataManager::FishType type,int offlineTime);//
    
    ~Fish0();
    
    virtual void initUI() override;
    virtual void initData() override;
    
    
    
    void Update(float dt);
    void updateSec(float dt);
    void updateText(float dt);
    vector<Vec2> getRoute();
    
    void fishMove();
    void fishZXMove();
    Rect getWorldRect();
    void jiaSu();
    void setShadows(ShadowsFish* shadows)
    {
        _shadows = shadows;
    }
    
    long getTime();
    long getDieTime();
    void updateHp();
    
    void setFishHp(int hp);
    int getFishHp();
    
    void restoreHp(int hp);
    void setType(DataManager::FishType type)
    {
        _type = type;
    }
    DataManager::FishType getFishType()
    {
        return _type;
    }
    int getFishId();
    void setFishId(int id);
    void deleteSelf();
    
    //----------------行动相关
    void fishStay();
    void fishRush();
    void fishStop();
    Vec2 PointOnCubicBezier(Vec2* cp, float t);
     
    std::vector<Vec2> ComputeBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments);
    
    float BezierLenth(const std::vector<Vec2> &points, int points_count);
    
    void fishAdmission();
    
    bool getIsStart() { return isStart; }
    bool getIsLeft() { return _isLeft; }
    bool getIsTouch() { return _isTouch; }
    bool getIsDie() { return _isDie; }
    bool getIsJinShi() { return _isJinShi; }
    
    void fishPlayAni(string aniName,bool loop,float speed = 1);
    
    bool getIsWeiShi();
    bool getIsMaxHp();
    void weiShi(Vec2 poi,bool isEnd,string str = "");
    void resumeMove();
    
    TargetedAction* chiFanAction(Vec2 normalized);
    
    void dieStart();
    void dieAction();
    void resurrection();
    void setFishMoveType(FishMoveType type);
    void showDuiHua(string str,EmojiType type);
    
    //每日奖励
    void setIsDaily(bool isDaily,bool isRank = false);
    bool getIsDaily() { return _isDaily; }
    void updateDYY();
private:
    FishMoveType _fishMoveType;
    FishAniType _fishAniType;
    float moveSpeed;
    spine::SkeletonAnimation *_skeletonNode;
    spTrackEntry* _spTrackEntry;
    DataManager::FishType _type;
    int _fishId;
    float _speed;
    GameBackground* _fishTank;
    RankFashTank* _rankFashTank;
    ShadowsFish* _shadows;
    vector<Vec2> routeVec;
    vector<Vec2> routeVec2;
    Vec2 targetPos;
    int vecIdx = 0;
    Node* npcPrefabs;
    Node* parent;
    Node* FileNode_DuiHua;
    Sprite* Sprite_DuiHua,*Sprite_emoji;

    int _idx,_idx2;
    float _time = 0;
    //方向
    bool _isLeft,_oldIsLeft;
    bool _isTouch;
    //在吃东西了
    bool _isJinShi;
    //吃东西时不要算角度了
    bool _isAngle;
    //吃东西时的朝向
    Vec2 _jinShiNormalized;
    //取4个点
    Vec2 poi0,poi1,poi2,poi3;
    
    //需要四个点。
    Vec2 CatmullRomVec[4];
    
    Sprite * _fishIcon = nullptr;
    //
    Speed* _fishActionSpeed;
    Vec2 _tempSelfPos,weiShiTempSelfPos;
    bool _isJiaSu, isStart, isAngle,isStop,isStopJiaSu;
    float _jiaSuTime;
    int scaleY;
    //血量 一分钟扣1
    int _fishHp,_fishMaxHp;
    //等级
    int _fishLv;
    LoadingBar* _loadingBar;
    Node* Node_loadingBar;
    //记录时间
    long _fishTime;
    //死亡
    int _dieTime;
    bool _isDie,_isTempDie;
    
    float thinkTime,thinkTempTime;
    //速度缓慢减少速度
    float tempSpeed;
    float move2Time;
    float stopTime,stopTempTime,stopMaxTime,stopMaxTempTime;
    Vec2 move2Vec;
    
    //是不是大鱼
    bool isDaYu;
    
    //对话
    Text* _duiHua;
    ImageView* Image_DuiHua;
    //血量进度条变化
    bool isBar;
    float _percent,_percent2,percentDx;
    int _fashTankIdx;
    //每日获得的鱼
    Text* Text_rare;
    bool _isDaily;
    //对话 逐字显示
    vector<char> _duiHuaVec;
    
    int _duiHuaIndex;
    bool _isPlayText;
    
    //----------测试
    bool isceshi = false;
    Vec2 ceshiVec;
    
    Vec2 ceshiAVec[4];
    
    
    int ceshiId = 0;
    
    
};

#endif /* Fish0_h */
