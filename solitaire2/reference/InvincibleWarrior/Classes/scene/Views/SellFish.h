//
//  SellFish.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/18.
//

#ifndef SellFish_h
#define SellFish_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include "TeachInterface.h"

class BagGameBg;
class MainLobby;
class BagGameBg;
class SellFish : public BaseLayer, public Factory<SellFish>
{
public:
    
    SellFish(BagGameBg* bagGameBg,int fashTankIdx,int fishType,int index,int price,std::function<void()> cb);
    ~SellFish();
    void onEnter() override;
    void onExit() override;
    void updateUI();
    void nodeAni();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    int _fishType;
    int _fashTankIdx;
    int _price,_index;
    std::function<void()> _cb;
    BagGameBg* _bagGameBg;
};


#endif /* SellFish_h */
