//
//  ChallengeModeView.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/10/24.
//

#ifndef ChallengeModeView_h
#define ChallengeModeView_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include <spine/AnimationState.h>
namespace spine {
    class SkeletonAnimation;
}

class FishGuideManager;
class ChallengeModeView : public BaseLayer, public Factory<ChallengeModeView>
{
public:
    enum class Type
    {
        Lobby,
        Game,
    };
    ChallengeModeView(Type type);
    ~ChallengeModeView();
    
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    
    void onEnter() override;
    void onExit() override;
    
    void fishMove();
    int getTextSize();
private:
    spine::SkeletonAnimation *_skeletonNode;
    Node* Node_fish;
    LoadingBar* loadingBar_percent;
    bool _isComplete,isBar;
    float percent1,percent2,percentDx;
    int _oldNum,_num;
    int fishId;
    Type _type;
    TextBMFont *text_StarHour, *text_StarNumMin;
};

#endif /* ChallengeModeView_h */
