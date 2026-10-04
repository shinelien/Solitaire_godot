#ifndef __IOSIAP_BRIDGE_H__
#define __IOSIAP_BRIDGE_H__

#include "IOSiAP.h"

class IOSiAP_Bridge : public IOSiAPDelegate
{
public:
    // ［请求］获取商品信息
    void requestProducts(std::string &identifier);
   
    // ［请求］付款请求
    void requestPayment(int quantity);

    // ［请求］恢复购买
    void requestRestore();

public:
    IOSiAP_Bridge();
    ~IOSiAP_Bridge();
    
    // ［回调］请求商品信息回调
    virtual void onRequestProductsFinish(void);
    virtual void onRequestProductsError(int code);
    // ［回调］付款结果回调（恢复流程也走这里）
    virtual void onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity);
    // ［回调］恢复购买完成回调
    void onRestoreFinished(bool succeed);
    
    // 检测订阅
    void checkVipStatus();
private:
    IOSiAP             *iap;             // IOSiAp实例
    
    std::string        _identifier;      // 商品编号（获取请求）
    int                _quantity;        // 商品数量（购买请求）
    IOSProduct         *_product;        // 商品信息（返回信息）
    
};

//==========================================================================================

#endif

