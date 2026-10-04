//
// Created by  on 2020/3/24.
//

#ifndef NewSpaceCatSolitaire_WinLayerTeach_H
#define NewSpaceCatSolitaire_WinLayerTeach_H

#include "BaseLayer.h"
#include "Factory.hpp"

class WinLayerTeach : public BaseLayer, public Factory<WinLayerTeach> {
public:
    virtual ~WinLayerTeach();
    WinLayerTeach();

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
};

#endif //NewSpaceCatSolitaire_WinLayerTeach_H
