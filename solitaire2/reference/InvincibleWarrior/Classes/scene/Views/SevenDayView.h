//
//  SevenDayView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/26.
//

#ifndef SevenDayView_h
#define SevenDayView_h

#include "BaseLayer.h"
#include "Factory.hpp"

class SevenDayView : public BaseLayer, public Factory<SevenDayView>
{
public:
    
    enum class Type
    {
        Home,
        Daily,
        None,
    };
    
    SevenDayView(SevenDayView::Type type = SevenDayView::Type::None);
    ~SevenDayView();
    void updateUI();
    
    bool lianXu();
    void getReward(int num = 1);
    void updateDay();
    void initDay();
    void updateAD();
    
    void updateCoin(bool isDelay = false);
    void updateDiamond(bool isDelay = false);
    void onEnter() override;
    void onExit() override;
    void oneOpen();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    int lastYDay;
    int lastYear;
    int RewardDays;//当前奖励天数1-7
    std::vector<bool> isGetReward;
    std::vector<bool> isGetRewardAD;
    Text* Text_time;
    SevenDayView::Type _type;
    int _diamondNum,_coinNum;
    vector<int> idxVec;
    int fangCuo = 10;
    bool _isGetClicked = false;
    bool isAniEnd;
};

#endif /* SevenDayView_h */
