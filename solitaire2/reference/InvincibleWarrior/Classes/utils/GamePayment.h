#ifndef __GAME_PAYMENT_H__
#define __GAME_PAYMENT_H__

#include "cocos2d.h"
USING_NS_CC;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSiAP_Bridge.h"
#else // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#endif

class GamePayment
{
public:
    static GamePayment *getInstance();
    
protected:
    GamePayment();
    // IAP内购(IOS)
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
public:
    // 请求商品信息
    void req_iap(std::string &identifier);
    
    // 购买请求
    void pay_iap(int quantity);
    
    // 恢复购买
    void restore_iap();
    
    void checkVipStatus();
private:
    IOSiAP_Bridge _iap;
#endif

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif
};

#endif

