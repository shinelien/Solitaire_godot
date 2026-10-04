//
//  LevelUpView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/29.
//

#ifndef LevelUpView_h
#define LevelUpView_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include <spine/AnimationState.h>
namespace spine {
    class SkeletonAnimation;
}
class LevelUpView : public BaseLayer, public Factory<LevelUpView> {
public:
    enum class Type
    {
        Lobby,
        Game,
    };
    
    enum class RewardType
    {
        Fish,
        FashTank,
        LiWu,
        None,
    };
    LevelUpView();
    virtual ~LevelUpView();
    
    void setData(int lv,int oldLv,float percent1,float percent2,float percentDx,std::function<void()> cb);
    void setIsBar(bool isBar);
    void playUpAni();
    Vec2 getFishWorldPoi();
    bool getIsUnlock();
    void fishMove();
    
    
    void updateDYY();
    void setType(Type type);
    void updateBg();
    void updateUI();
    void updateReward(int ulv);
    //当前等级没有奖励用
    void updateReward();
    void setVisible(bool visible);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    
    
private:
    std::function<void()> _cb = nullptr;
    int _fishType = -1;
    spine::SkeletonAnimation *_skeletonNode;
    bool isBar,isQieHuan;
    int lv,oldLv,dLv;
    float percent1,percent2,percentDx,percent3,percent4;
    LoadingBar* loadingBar_percent;
    TextBMFont* Label_Lv0,*Label_Lv1,*Label_Lv2,*Label_Lv3;
    Node* Node_fish,*Node_jianTou;
    Vector<Node*>_LvBgVec;
    Vector<TextBMFont*>_LabelVec;
    int fishId,unlockLv;
    bool isUnlock;
    float LoadingBarWidth;
    LevelUpView::Type _type;
    bool isUp;
    Sprite*Sprite_BG;
    RewardType _rewardType;
    vector<int> rewardVec;
    vector<vector<string>> peishiVec;
    std::vector<int> _idxVec;
    vector<int> _lvVec;
    int _idx;
};

#endif /* LevelUpView_h */
