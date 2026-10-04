//
//  NPCCeShi.h
//  SolitaireClassicGame
//
//  Created by lien on 2019/8/3.
//

#ifndef NpcSprite_h
#define NpcSprite_h
#include "CacheNode.h"
#include "BaseLayer.h"

class Gold;
class NPCManager;
class NpcSprite : public CacheNode<NpcSprite>
{
public:
    NpcSprite();
    ~NpcSprite();
    bool init();
    virtual void cacheInit();
    virtual void onEnter();
    virtual void onExit();
    void setPath(Vector<Node*> pathVec,int pathIdx,bool isHide);
    void myUpdate(float dt);
    Vec2 getWorldPoi();
    Vec2 getNodePoi(Vec2 pos);
    Rect getWorldRect();
    
private:
    void playUpAni();
    void playDownAni();
    void playLeftAni();
    void playRightAni();
    
    Node* Node_Npc;
    
    bool isStart;
    int xiaBiao;
    Vec2 targetPoi;
    Vec2 startPoi;
    bool isTarget;
    bool isUp;
    bool isDown;
    bool isLeft;
    bool isRight;
    Vector<Node*> _pathVec;
    Vec2 _normalized;
    float speed;//每次移动的距离
    int _pathIdx;
    int _npcId;
    bool isFront,_isHide,_isStop;    
    int _randHide;
    ActionTimeline* actionManager;
    Sprite* Sprite_1;
};

#endif /* NPCCeShi_h */
