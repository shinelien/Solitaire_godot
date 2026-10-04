//
// Created by  on 2019-06-03.
//

#ifndef NewSpaceCatSolitaire_HomeSetting_H
#define NewSpaceCatSolitaire_HomeSetting_H

#include "BaseLayer.h"
#include "Factory.hpp"

class HomeSetting : public BaseLayer, public Factory<HomeSetting> {
public:
    virtual ~HomeSetting();

    void onEnter() override;

    HomeSetting();

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    Node* img_new_lobby_share;
    int setNewNum;
};

#endif //NewSpaceCatSolitaire_HomeSetting_H
