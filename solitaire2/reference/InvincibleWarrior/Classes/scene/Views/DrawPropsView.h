//
//  DrawPropsView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/6.
//

#ifndef DrawPropsView_h
#define DrawPropsView_h
#include "BaseLayer.h"
#include "Factory.hpp"

class DrawPropsView : public BaseLayer, public Factory<DrawPropsView>
{
public:
    enum class ViewType
    {
        None,
        Home,
        Daily,
        SevenGold,
        SevenDiamond,
    };
    DrawPropsView(std::vector<int> idxVec,DrawPropsView::ViewType type);
    ~DrawPropsView();
    void initSprite();
    void nodeAni();
    
    virtual void onExit() override;
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    void goaway();
private:
    std::vector<int> _idxVec;
    int tag;
    DrawPropsView::ViewType _type;
    
    int isGold;
    bool isBuy;
};

#endif /* DrawPropsView_h */
