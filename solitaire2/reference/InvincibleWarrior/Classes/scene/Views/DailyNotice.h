
#ifndef NewSpaceCatSolitaire_DailyNotice_H
#define NewSpaceCatSolitaire_DailyNotice_H

#include "BaseLayer.h"
#include "Factory.hpp"

class DailyNotice : public BaseLayer, public Factory<DailyNotice> {
public:
    virtual ~DailyNotice();
    DailyNotice();

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
};

#endif //NewSpaceCatSolitaire_DailyNotice_H
