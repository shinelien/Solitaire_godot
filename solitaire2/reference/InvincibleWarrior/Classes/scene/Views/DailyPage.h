//
// Created by  on 2020/3/16.
//

#ifndef NewSpaceCatSolitaire_DailyPage_H
#define NewSpaceCatSolitaire_DailyPage_H

#include "BaseLayer.h"
#include "Factory.hpp"

class DailyPage : public BaseLayer, public Factory<DailyPage> {
public:
    virtual ~DailyPage();
    DailyPage(int idx);

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    
    int _idx;
};

#endif //NewSpaceCatSolitaire_DailyPage_H
