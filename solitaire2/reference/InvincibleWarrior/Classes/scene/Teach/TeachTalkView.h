//
// Created by  on 2020/3/20.
//

#ifndef NewSpaceCatSolitaire_TeachTalkView_H
#define NewSpaceCatSolitaire_TeachTalkView_H

#include "BaseLayer.h"
#include "Factory.hpp"
#include <external/json/document.h>

class CardSprite;
class TeachTalkView : public BaseLayer, public Factory<TeachTalkView> {
public:
    virtual ~TeachTalkView();
    TeachTalkView(std::shared_ptr<rapidjson::Document> teachConfig);

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    void dumpString();

public:
    bool onTouchBegan(Touch *t, Event *e) override;

private:

    CardSprite* _canMoveCard = nullptr;
public:
    void onEnter() override;

    void onExit() override;

public:
    void onTouchEnded(Touch *t, Event *e) override;

private:
    std::string _content, _type;
    std::vector<string> _dump;
    float _curIdx;
    bool _isEnd = false;
    std::shared_ptr<rapidjson::Document> _teachConfig;
    std::vector<CardSprite*> _hilghtCard;
};

#endif //NewSpaceCatSolitaire_TeachTalkView_H
