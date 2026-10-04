//
//  DailyMoreView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/17.
//

#ifndef DailyMoreView_h
#define DailyMoreView_h

#include "BaseLayer.h"
#include "Factory.hpp"
#include "DailyManager.h"
#include <spine/AnimationState.h>
namespace spine {
    class SkeletonAnimation;
}

class DailyNode;
class DailyGameView;
class DailyMoreView : public BaseLayer, public Factory<DailyMoreView> {
public:
    DailyMoreView(Date current);
    virtual ~DailyMoreView();
    
    void runProgress(float time,float percent);
    void updateUI(Date date);
    void updateUI();
    void setMoreUI(int year, int month, int selectDay_);
    void showStart();

    void showSelectDialog(bool isCompletedView = false, int tag = 1);
    void updateDYY();
    void leftMore();
    void rightMore();
    void setCurrentSelectNode(DailyNode *selectNode);
    std::string getTrophy(int monthCompleteCNT, int days);
    Vec2 GetPosition(int x, int y);

    Vec2 GetPosition(int x);

    int gouRound(int value, int max);
    void setFileNodeStart(DailyGameView* start);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    ProgressTimer *ProgressTimer_percent = nullptr;
    Date _current;
    Date _toDay,_maxday;
    DailyGameView* FileNode_start;
    DailyNode *_selectedNode = nullptr;
public:
    void onEnter() override;

    void onExit() override;
    
    LoadingBar* LoadingBar_StarBox;
    TextBMFont* BitmapFontLabel_StarNum,*BitmapFontLabel_StarNumMax;
    
    int _jieduan;
    Node* Node_fish;
    //记录奖品id
    int rewardIds[3];
    vector<int> jieduanVec;
    vector<vector<int>> fishIds;
    int _currentFishkIdx;
};

#endif /* DailyMoreView_h */
