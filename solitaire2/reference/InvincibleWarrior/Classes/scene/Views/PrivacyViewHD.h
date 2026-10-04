
#ifndef SpacecatSolitaireGame_PrivacyViewHD_H
#define SpacecatSolitaireGame_PrivacyViewHD_H

#include "BaseLayer.h"
#include "Factory.hpp"

class PrivacyViewHD : public BaseLayer, public Factory<PrivacyViewHD> {
public:
    virtual ~PrivacyViewHD();
    PrivacyViewHD();

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
};

#endif //SpacecatSolitaireGame_PrivacyViewHD_H
