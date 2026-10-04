//
//  ThreeModelTips.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/22.
//

#ifndef ThreeModelTips_h
#define ThreeModelTips_h
#include "BaseLayer.h"
#include "Factory.hpp"

class ThreeModelTips : public BaseLayer, public Factory<ThreeModelTips>
{
public:
    ThreeModelTips(BaseLayer* layer = NULL);
    ~ThreeModelTips();
    void updateUI();
    
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    BaseLayer* _layer;
};

#endif /* ThreeModelTips_h */
