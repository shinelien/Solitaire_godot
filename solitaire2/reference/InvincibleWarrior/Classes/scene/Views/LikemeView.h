//
//  LikemeView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/24.
//

#ifndef LikemeView_h
#define LikemeView_h

#include "BaseLayer.h"
#include "Factory.hpp"

class LikemeView : public BaseLayer, public Factory<LikemeView> {
public:
    LikemeView();
    virtual ~LikemeView();
    

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    
};

#endif /* LikemeView_h */
