
#ifndef SpacecatSolitaireGame_LevelItem0_H
#define SpacecatSolitaireGame_LevelItem0_H

#include "BaseLayer.h"
#include "Factory.hpp"

class LevelViewHD;
class LevelItem0 : public BaseLayer, public Factory<LevelItem0> {
public:
    virtual ~LevelItem0();
    LevelItem0(LevelViewHD *parentView, int idx);

    void setLock(bool lock);

protected:
    void updateUI();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    int _idx;
public:
    void onEnter() override;

    void onExit() override;

private:
    bool _isLock;
    std::shared_ptr<rapidjson::Document> _value;
    LevelViewHD *_parentView;
};

#endif //SpacecatSolitaireGame_LevelItem0_H
