//
// Created by  on 2020/5/16.
//

#ifndef NewSpaceCatSolitaire_LoadingView_H
#define NewSpaceCatSolitaire_LoadingView_H

#include "BaseLayer.h"
#include "Factory.hpp"

class LoadingView : public BaseLayer, public Factory<LoadingView> {
public:
    virtual ~LoadingView();
    LoadingView();
    void onEnter() override;
    void onExit() override;
    
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
};

#endif //NewSpaceCatSolitaire_LoadingView_H
