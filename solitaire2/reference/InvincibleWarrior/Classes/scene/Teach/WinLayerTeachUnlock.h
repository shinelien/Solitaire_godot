//
// Created by  on 2020/3/28.
//

#ifndef NewSpaceCatSolitaire_WinLayerTeachUnlock_H
#define NewSpaceCatSolitaire_WinLayerTeachUnlock_H

#include "BaseLayer.h"
#include "Factory.hpp"

class WinLayerTeachUnlock : public BaseLayer, public Factory<WinLayerTeachUnlock> {
public:
    virtual ~WinLayerTeachUnlock();
    WinLayerTeachUnlock(std::function<void()> cb);

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    std::function<void()> _cb;
};

#endif //NewSpaceCatSolitaire_WinLayerTeachUnlock_H
