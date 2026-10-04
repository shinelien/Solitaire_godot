#include "GamePayment.h"

//==========================================================================================
// 初始化
//==========================================================================================

GamePayment *GamePayment::getInstance()
{
	static GamePayment _instance;
	return &_instance;
}

GamePayment::GamePayment()
{
    
}

//==========================================================================================
// IAP内购（IOS）
//==========================================================================================

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

// 初始化（获取商品信息）
void GamePayment::req_iap(std::string &identifier)
{
    _iap.requestProducts(identifier);
}

// 付款
void GamePayment::pay_iap(int quantity)
{
    _iap.requestPayment(quantity);
}

// 恢复购买
void GamePayment::restore_iap()
{
    _iap.requestRestore();
}

void GamePayment::checkVipStatus()
{
    _iap.checkVipStatus();
}

#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif

//==========================================================================================
//
//==========================================================================================

