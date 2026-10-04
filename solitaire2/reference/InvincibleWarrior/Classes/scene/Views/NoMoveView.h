//
//  NoMoveView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/4.
//

#ifndef NoMoveView_h
#define NoMoveView_h
#include "BaseLayer.h"
#include "Factory.hpp"

class NoMoveView : public BaseLayer, public Factory<NoMoveView> {
public:
    
    virtual ~NoMoveView();
    NoMoveView();
    //限制次数
    void xianZhi();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    std::function<void()> _cb;
    bool isClose;
};

#endif /* NoMoveView_h */
