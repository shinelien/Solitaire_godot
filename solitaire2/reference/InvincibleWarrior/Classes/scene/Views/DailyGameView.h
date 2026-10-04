//
//  DailyGameView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/12.
//

#ifndef DailyGameView_h
#define DailyGameView_h
#include "BaseLayer.h"
#include "Factory.hpp"

class GameViewHD;
class MainLobby;
class DailyNode;
class DailyMoreView;
class DailyGameView : public BaseLayer, public Factory<DailyGameView> {
public:
    virtual ~DailyGameView();
    DailyGameView(DailyNode*selectedNode,DailyMoreView* dailyView);
    void setDailyNode(DailyNode* node);
    void updateUI();
    void updateDYY();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    DailyNode*_selectedNode;
    DailyMoreView* _dailyView;
    
public:
    void onEnter() override;

    void onExit() override;
};

#endif /* DailyGameView_h */
