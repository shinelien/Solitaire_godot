//
//  FashTankSwith.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/29.
//

#ifndef FashTankSwitch_h
#define FashTankSwitch_h
#include "BaseLayer.h"
#include "Factory.hpp"

class FashTankSwitch : public BaseLayer, public Factory<FashTankSwitch>
{
public:
    FashTankSwitch(int fashTankIdx);
    ~FashTankSwitch();
    
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    
    void onEnter() override;
    void onExit() override;
private:
    int _fashTankIdx;
};
#endif /* FashTankSwith_h */
