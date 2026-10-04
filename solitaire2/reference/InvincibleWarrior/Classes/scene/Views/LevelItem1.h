
#ifndef SpacecatSolitaireGame_LevelItem_H
#define SpacecatSolitaireGame_LevelItem_H

#include "BaseLayer.h"
#include "Factory.hpp"

class LevelViewHD;
class LevelItem1 : public BaseLayer, public Factory<LevelItem1> {
public:
    virtual ~LevelItem1();
    LevelItem1(LevelViewHD *parentView,std::shared_ptr<rapidjson::Document> value, int idx);

    void onEnter() override;

    void onExit() override;

protected:
    void updateUI();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    LevelViewHD *_parentView;
    std::shared_ptr<rapidjson::Document> _value;
    int _idx;
};

#endif //SpacecatSolitaireGame_LevelItem_H
