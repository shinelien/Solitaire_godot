//
//  Currency.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/22.
//

#ifndef Currency_h
#define Currency_h
#include "CacheNode.h"
# include "ui/CocosGUI.h"
# include"cocostudio/CocoStudio.h"
USING_NS_TIMELINE;

class Currency : public CacheNode<Currency>
{
public:
    Currency();
    ~Currency();
    bool init();
    virtual void cacheInit();
    virtual void onEnter();
    virtual void onExit();
    void playAni(std::string name,bool isLoop,std::function<void()> cb = nullptr);
private:
    cocostudio::timeline::ActionTimeline* actionManager;
    Node* rootNode;
};

#endif /* Currency_h */
