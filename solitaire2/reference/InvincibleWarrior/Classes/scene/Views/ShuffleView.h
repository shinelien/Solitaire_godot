//
//  ShuffleView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/1.
//

#ifndef ShuffleView_h
#define ShuffleView_h
#include "BaseLayer.h"
#include "Factory.hpp"

class ShuffleView : public BaseLayer, public Factory<ShuffleView> {
public:
    
    
    enum class Type
    {
        Bag,
        None,
    };
    
    virtual ~ShuffleView();
    ShuffleView(ShuffleView::Type type = ShuffleView::Type::None);
    //限制次数
    void xianZhi();
    
    void onEnter() override;
    void onExit() override;
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    
    void addMagic();
private:
    std::function<void()> _cb;
    int _day;
    int _xianZhiNum;
    int _getNum;
    int _goldNum;
    ShuffleView::Type _type;
    std::function<void()> _InterstitialCB = nullptr;
};

#endif /* ShuffleView_h */
