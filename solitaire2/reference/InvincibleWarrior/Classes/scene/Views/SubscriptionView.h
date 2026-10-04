//
//  SubscriptionView.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2020/7/17.
//

#ifndef SubscriptionView_h
#define SubscriptionView_h
#include "BaseLayer.h"
#include "Factory.hpp"

class SubscriptionView : public BaseLayer, public Factory<SubscriptionView> {
public:
    SubscriptionView();
    virtual ~SubscriptionView();
    

private:
    void initUI() override;
    void initData() override;

public:
    void onEnter() override;

    void onExit() override;

private:
    void dealButtonClick(Ref *pSender) override;
    void updateUI();
private:
    
};

#endif /* SubscriptionView_h */
