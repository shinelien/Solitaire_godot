//
//  MultipleRewardView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/26.
//

#ifndef MultipleRewardView_h
#define MultipleRewardView_h
#include "BaseLayer.h"
#include "Factory.hpp"

class MultipleRewardView : public BaseLayer, public Factory<MultipleRewardView>
{
public:
    MultipleRewardView(std::function<void()> cb,std::function<void()> cb2, bool isTeach = false,int coin = 100);
    ~MultipleRewardView();
    void updateUI();
    
    
    void onEnter() override;
    void onExit() override;
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    std::function<void()> _cb;
    std::function<void()> _cb2;
    Node* FileNode_Gold,*FileNode_Diamond;
    bool _isTeach;
    bool isAds = false;
    int _coinNum;
};

#endif /* MultipleRewardView_h */
//5 0 5 5 5 0 7//目前是 经历变动后第一次7倍弹出
//0 0 0 0 0 0 0 0 0 7

// 7 7 5 5 5
//7 7 5 5 5 5 5 0 5
//7 5 5 5 5 5 5 
