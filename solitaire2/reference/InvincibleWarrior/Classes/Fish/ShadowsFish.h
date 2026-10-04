//
//  ShadowsFish.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/4/19.
//

#ifndef ShadowsFish_h
#define ShadowsFish_h

# include "cocos2d.h"
# include "BaseLayer.h"
#include "Factory.hpp"
class Fish0;
class ShadowsFish : public BaseLayer , public Factory<ShadowsFish>
{
public:
    ShadowsFish(Fish0* fish);
    ~ShadowsFish();
    virtual void initUI() override;
    virtual void initData() override;
    void shadowsInit();
    void Update(float dt);
    void deSelf();
    static ShadowsFish* createShadows(Fish0* fish);
private:
    Sprite* shadowsIcon;
    Fish0* _fish0;
    int ceshi = 0;
};

#endif /* ShadowsFish_h */
