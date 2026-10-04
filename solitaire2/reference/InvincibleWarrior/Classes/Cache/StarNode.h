//
//  StarNode.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/7.
//

#ifndef StarNode_h
#define StarNode_h
#include "CacheNode.h"
# include "ui/CocosGUI.h"
# include"cocostudio/CocoStudio.h"
USING_NS_TIMELINE;

class StarNode : public CacheNode<StarNode>
{
public:
    StarNode();
    ~StarNode();
    bool init();
    virtual void cacheInit();
    virtual void onEnter();
    virtual void onExit();
    void playAni(std::string name,bool isLoop,float time,std::function<void()> cb = nullptr);
private:
    cocostudio::timeline::ActionTimeline* actionManager;
    Node* rootNode;
};


#endif /* StarNode_h */
