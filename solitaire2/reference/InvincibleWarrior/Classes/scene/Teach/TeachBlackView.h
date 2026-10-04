//
// Created by  on 2020/3/22.
//

#ifndef NewSpaceCatSolitaire_TeachBlackView_H
#define NewSpaceCatSolitaire_TeachBlackView_H

#include "BaseLayer.h"
#include "Factory.hpp"

class TeachBlackView : public BaseLayer, public Factory<TeachBlackView> {
public:
    virtual ~TeachBlackView();
    TeachBlackView();

    void highlightNode(Node *node, bool hasFinger = true, cocos2d::Vec2 offsetFinger = Vec2::ZERO, bool lock = true, bool once = false, bool underNode = false);
    void fingerOnce(Node *node, cocos2d::Vec2 offsetFinger = Vec2::ZERO, bool end = false);
    void onEnter() override;

    void onExit() override;

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    Node    *_highlightNode = nullptr, *_underNode = nullptr;
    Layout *_blackLayer, *_toptopLayer;
};

#endif //NewSpaceCatSolitaire_TeachBlackView_H
