//==========================================================================================
// IOSiAP_Bridge.cpp
// Created by Dolphin Lee.
//==========================================================================================

#include "IOSiAP_Bridge.h"
# include "DataManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//==========================================================================================
// 构造函数
//==========================================================================================

IOSiAP_Bridge::IOSiAP_Bridge()
{
    _quantity = 0;
    _identifier = "";
    _product = nullptr;
    
    // 创建IOSIAP
    iap = new IOSiAP();
    iap->delegate = this;
}

IOSiAP_Bridge::~IOSiAP_Bridge()
{
    delete iap;
}

//==========================================================================================
// 回调函数（IOSIAP返回结果）
//==========================================================================================

// ［回调］获取商品请求成功返回
void IOSiAP_Bridge::onRequestProductsFinish(void)
{
    // 必须在onRequestProductsFinish后才能去请求IAP产品数据
    _product = iap->iOSProductByIdentifier(_identifier);
    
    // 获取成功后即可发起付款请求
    // iap->paymentWithProduct(_product, _quantity);
    this->requestPayment(1);
    // 回调出去
}

// ［回调］获取商品请求失败返回
void IOSiAP_Bridge::onRequestProductsError(int code)
{
    // 这里requestProducts出错了，不能进行后面的所有操作
}

// ［回调］支付结果返回
void IOSiAP_Bridge::onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity)
{
    if (event == IOSIAP_PAYMENT_PURCHASING)
    {
        // 不需要做任何处理
    }
    else if (event == IOSIAP_PAYMENT_PURCHAED)
    {
        // 付款成功 -- 下发道具--在下发中 通知可以继续购买了，不然不能购买
        //DATA_M->buySuccess(identifier);
        //订阅特殊处理
//        if(transaction.originalTransaction){
//             //如果是自动续费的订单originalTransaction会有内容
//        }else{
//             //普通购买，以及 第一次购买 自动订阅
//        }
        DATA_M->setIsBuying(false);
        SCENE_M->removeLoading();
    }
    else if (event == IOSIAP_PAYMENT_FAILED)
    {
        // 付款失败
        DATA_M->setIsBuying(false);
        SCENE_M->removeLoading();
    }
    else if (event == IOSIAP_PAYMENT_RESTORED)
    {
        // 恢复购买
        DATA_M->setIsBuying(true);
        SCENE_M->removeLoading();
    }
}

// ［回调］恢复购买完成回调
void IOSiAP_Bridge::onRestoreFinished(bool succeed)
{
    // 恢复购买完成
}

//==========================================================================================
// 外部调用
//==========================================================================================

// 获取商品信息
void IOSiAP_Bridge::requestProducts(std::string &identifier)
{
    _identifier = identifier;
    
    std::vector<std::string> vIdentifiers;
    vIdentifiers.push_back(_identifier);
    
    // 获取商品信息
    iap->requestProducts(vIdentifiers);
}

// 付款请求
void IOSiAP_Bridge::requestPayment(int quantity)
{
    _quantity = quantity;
    
    if (_product)
    {
        // 支付请求
        iap->paymentWithProduct(_product, _quantity);
    }
}

// ［请求］恢复购买
void IOSiAP_Bridge::requestRestore()
{
    // 恢复请求
    iap->restorePayment();
}

void IOSiAP_Bridge::checkVipStatus()
{
    iap->checkVipStatus();
}

//==========================================================================================
//
//==========================================================================================

#endif
