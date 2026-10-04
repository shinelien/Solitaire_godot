
#ifndef NewSpaceCatSolitaire_GuideView_H
#define NewSpaceCatSolitaire_GuideView_H

#include "BaseLayer.h"
#include "Factory.hpp"
#include "DailyManager.h"
class GuideView : public BaseLayer, public Factory<GuideView> {
public:
    enum class GuideType {
        NewTeach,
        DailyTeach
    };

    virtual ~GuideView();
    GuideView(Date date);
    void setGuideType(GuideType type);
    static GuideView* showGuid(GuideType type,Date date);
    void runProgress(float time,float percent);
    
    
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    ProgressTimer *ProgressTimer_percent = nullptr;
    GuideType _guideType;
    Date _current;
};

#endif //NewSpaceCatSolitaire_GuideView_H
