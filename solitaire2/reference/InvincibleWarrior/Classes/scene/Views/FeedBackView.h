
#ifndef SpacecatSolitaireGame_FeedBackView_H
#define SpacecatSolitaireGame_FeedBackView_H

#include "BaseLayer.h"
#include "Factory.hpp"

class FeedBackView : public BaseLayer, public Factory<FeedBackView> {
public:
    virtual ~FeedBackView();
    FeedBackView();
    void updataUI(int id);
    virtual void onExit() override;
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
};

#endif //SpacecatSolitaireGame_FeedBackView_H
