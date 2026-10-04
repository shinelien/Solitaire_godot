//
//  ShareRewardView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/26.
//

#ifndef ShareRewardView_h
#define ShareRewardView_h
#include "BaseLayer.h"
#include "Factory.hpp"

class ShareRewardView : public BaseLayer, public Factory<ShareRewardView>
{
public:
    enum class Type
    {
        None,
        Home,
        Daily,
    };
    ShareRewardView(ShareRewardView::Type type);
    ~ShareRewardView();
    void updateUI();
    
    void onEnter();
    void onExit();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    ShareRewardView::Type _type = ShareRewardView::Type::None;
    int rewardNum;
    int goldNum;
};
#endif /* ShareRewardView_h */

