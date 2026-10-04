#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

#import "IOSiAP.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface iAPProductsRequestDelegate : NSObject<SKProductsRequestDelegate>
@property (nonatomic, assign) IOSiAP *iosiap;
@end

@implementation iAPProductsRequestDelegate

- (void)productsRequest:(SKProductsRequest *)request
     didReceiveResponse:(SKProductsResponse *)response
{
    // release old
    if (_iosiap->skProducts) {
        [(NSArray *)(_iosiap->skProducts) release];
    }
    // record new product
    _iosiap->skProducts = [response.products retain];
    
    for (int index = 0; index < [response.products count]; index++) {
        SKProduct *skProduct = [response.products objectAtIndex:index];
        
        // check is valid
        bool isValid = true;
        for (NSString *invalidIdentifier in response.invalidProductIdentifiers) {
            NSLog(@"invalidIdentifier:%@", invalidIdentifier);
            if ([skProduct.productIdentifier isEqualToString:invalidIdentifier]) {
                isValid = false;
                break;
            }
        }
        
        IOSProduct *iosProduct = new IOSProduct;
        iosProduct->productIdentifier = std::string([skProduct.productIdentifier UTF8String]);
        iosProduct->localizedTitle = std::string(skProduct.localizedTitle?[skProduct.localizedTitle UTF8String]:"default");
        iosProduct->localizedDescription = std::string(skProduct.localizedDescription?[skProduct.localizedDescription UTF8String]:"default");
        
        // locale price to string
        NSNumberFormatter *formatter = [[NSNumberFormatter alloc] init];
        [formatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
        [formatter setNumberStyle:NSNumberFormatterCurrencyStyle];
        [formatter setLocale:skProduct.priceLocale];
        NSString *priceStr = [formatter stringFromNumber:skProduct.price];
        [formatter release];
        iosProduct->localizedPrice = std::string([priceStr UTF8String]);
        
        iosProduct->index = index;
        iosProduct->isValid = isValid;
        _iosiap->iOSProducts.push_back(iosProduct);
    }
}

- (void)requestDidFinish:(SKRequest *)request
{
    _iosiap->delegate->onRequestProductsFinish();
    [request.delegate release];
    [request release];
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    NSLog(@"%@", error);
    _iosiap->delegate->onRequestProductsError([error code]);
}

@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface iAPTransactionObserver : NSObject<SKPaymentTransactionObserver>
@property (nonatomic, assign) IOSiAP *iosiap;
@property (nonatomic, assign) SKPaymentTransaction *transaction;
@end

@implementation iAPTransactionObserver

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions) {
        std::string identifier([transaction.payment.productIdentifier UTF8String]);
        IOSiAPPaymentEvent event;
        
        switch (transaction.transactionState) {
            case SKPaymentTransactionStatePurchasing:
                event = IOSIAP_PAYMENT_PURCHASING;
                return;
            case SKPaymentTransactionStatePurchased:
                event = IOSIAP_PAYMENT_PURCHAED;
                if (transaction.originalTransaction)
                {
                    //如果是自动续费的订单originalTransaction会有内容
                    NSLog(@"自动续费的订单,originalTransaction = %@", transaction.originalTransaction);
//                    string key = StringUtils::format("iap_%s", identifier.c_str());
//                    UserDefault::getInstance()->setStringForKey(key.c_str(), transaction.originalTransaction);
                }
                else{
                    //普通购买，以及 第一次购买 自动订阅
                }
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                event = IOSIAP_PAYMENT_FAILED;
                NSLog(@"==ios payment error:%@", transaction.error);
                break;
            case SKPaymentTransactionStateRestored:
                // NOTE: consumble payment is NOT restorable
                event = IOSIAP_PAYMENT_RESTORED;
                break;
        }
        
        _iosiap->delegate->onPaymentEvent(identifier, event, transaction.payment.quantity);
        if (event != IOSIAP_PAYMENT_PURCHASING && event != IOSIAP_PAYMENT_PURCHAED) {
            [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
        }
    }
}

// 交易结束,当交易结束后还要去appstore上验证支付信息是否都正确,只有所有都正确后,我们就可以给用户方法我们的虚拟物品了。
- (void)completeTransaction:(SKPaymentTransaction *)transaction {
    // 验证凭据，获取到苹果返回的交易凭据
    self.transaction = transaction;
    _iosiap->checkVipStatus(transaction);
    
//    https://sandbox.itunes.apple.com/verifyReceipt
//    https://buy.itunes.apple.com/verifyReceipt
}

- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions) {
        std::string identifier([transaction.payment.productIdentifier UTF8String]);
        _iosiap->delegate->onPaymentEvent(identifier, IOSIAP_PAYMENT_REMOVED, transaction.payment.quantity);
    }
}

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error
{
    
    _iosiap->delegate->onRestoreFinished(false);
    //NSLog(@"restore completed transactions failded.");
}

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue
{
    _iosiap->delegate->onRestoreFinished(true);
    //NSLog(@"restore completed transactions finished.");
}

@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

IOSiAP::IOSiAP():
skProducts(nullptr),
delegate(nullptr)
{
    skTransactionObserver = [[iAPTransactionObserver alloc] init];
    ((iAPTransactionObserver *)skTransactionObserver).iosiap = this;
    [[SKPaymentQueue defaultQueue] addTransactionObserver:(iAPTransactionObserver *)skTransactionObserver];
}

IOSiAP::~IOSiAP()
{
    if (skProducts) {
        [(NSArray *)(skProducts) release];
    }
    
    std::vector <IOSProduct *>::iterator iterator;
    for (iterator = iOSProducts.begin(); iterator != iOSProducts.end(); iterator++) {
        IOSProduct *iosProduct = *iterator;
        delete iosProduct;
    }
    
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:(iAPTransactionObserver *)skTransactionObserver];
    [(iAPTransactionObserver *)skTransactionObserver release];
}

IOSProduct *IOSiAP::iOSProductByIdentifier(std::string &identifier)
{
    std::vector <IOSProduct *>::iterator iterator;
    for (iterator = iOSProducts.begin(); iterator != iOSProducts.end(); iterator++) {
        IOSProduct *iosProduct = *iterator;
        if (iosProduct->productIdentifier == identifier) {
            return iosProduct;
        }
    }

    return nullptr;
}

void IOSiAP::requestProducts(std::vector <std::string> &productIdentifiers)
{
    NSLog(@"获取商品信息");
    NSMutableSet *set = [NSMutableSet setWithCapacity:productIdentifiers.size()];
    std::vector <std::string>::iterator iterator;
    for (iterator = productIdentifiers.begin(); iterator != productIdentifiers.end(); iterator++) {
        [set addObject:[NSString stringWithUTF8String:(*iterator).c_str()]];
    }
    SKProductsRequest *productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:set];
    iAPProductsRequestDelegate *delegate = [[iAPProductsRequestDelegate alloc] init];
    delegate.iosiap = this;
    productsRequest.delegate = delegate;
    [productsRequest start];
}

void IOSiAP::paymentWithProduct(IOSProduct *iosProduct, int quantity)
{
    SKProduct *skProduct = [(NSArray *)(skProducts) objectAtIndex:iosProduct->index];
    SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:skProduct];
    payment.quantity = quantity;
    
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

void IOSiAP::restorePayment()
{
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

void IOSiAP::checkVipStatus(void *transaction)
{
    if (transaction)
        [((SKPaymentTransaction*)transaction) retain];
    NSURL *receiptURL = [[NSBundle mainBundle] appStoreReceiptURL];// appStoreReceiptURL iOS7.0增加的，购买交易完成后，会将凭据存放在该地址
    NSData *receiptData = [NSData dataWithContentsOfURL:receiptURL];// 从沙盒中获取到购买凭据
    if (receiptData && [receiptData length] > 0) { // 有票就验证一发
//        if (transaction) {
//            NSString * str = [[NSString alloc] initWithData:((SKPaymentTransaction*)transaction).transactionReceipt encoding:NSUTF8StringEncoding];
////            NSString *environment = [self environmentForReceipt:str];
//            NSLog(@"----- 完成交易调用的方法completeTransaction 1--------%@",str);
//        }
        NSString *encodeStr = [receiptData base64EncodedStringWithOptions:NSDataBase64EncodingEndLineWithLineFeed];// BASE64 常用的编码方案，通常用于数据传输，以及加密算法的基础算法，传输过程中能够保证数据传输的稳定性，BASE64是可以编码和解码的
        NSLog(@"----- 完成交易调用的方法completeTransaction 1--------%@", encodeStr);
//        UIUtils::httpPost("http://192.168.2.245:8595/check", {
        UIUtils::httpPost("http://api.spacecat.top:8595/check", {
            {"t",Value([encodeStr UTF8String])},
            {"id",Value(NoAdKey)}
        },
        [this, transaction](cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response){
            auto resCode = response->getResponseCode();
            CCLOG("res code:%ld", resCode);
            if (resCode == 200) // 成功了
            {
                auto resData = response->getResponseData();
                NSData *data = [[NSData alloc] initWithBytes:resData->data() length:resData->size()];
                if (data) {
                    NSError *error = nil;
                    NSDictionary* result = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
                    if (error != nil)
                        NSLog(@"\n%@", [error localizedDescription]);
                    else {
                        NSNumber *res = [result objectForKey:@"res"];
                        if (res)
                        {
                            int resValue = [res intValue];
                            if (resValue == 1) { // 还在订阅啊
                                CCLOG("订阅成功了!!!!");
                                NSNumber *startTime = [result objectForKey:@"st"];
                                NSNumber *endTime = [result objectForKey:@"et"];
                                NSNumber *pid = [result objectForKey:@"pid"];
                                DATA_M->setVipNoAds(true, startTime?[startTime longLongValue]:0, endTime?[endTime longLongValue]:0, pid?[pid intValue]:0);
                                if (transaction) {
                                    SCENE_M->showTips(Lang("100325"));
                                }
                            }
                            else {
                                CCLOG("订阅没了!!!!");
                                DATA_M->setVipNoAds(false);
                            }
                        }
                    }
                    if (transaction) {
                        NSLog(@"----- 完成交易调用的方法completeTransaction 2--------%@", transaction);
                        [[SKPaymentQueue defaultQueue] finishTransaction: (SKPaymentTransaction*)transaction];
                        [((SKPaymentTransaction*)transaction) release];
                    }
                }
                else {
                    reCheckVipStatus(transaction);
                }
            }
            else { // 服务器有毛病!!! 还是没网了😂
                reCheckVipStatus(transaction);
            }
        });
    }
}

void IOSiAP::reCheckVipStatus(void *transaction)
{
    if (transaction) {
        Director::getInstance()->getRunningScene()->unschedule("schedule_iap_retry");
        Director::getInstance()->getRunningScene()->scheduleOnce([this, transaction](float t){
            this->checkVipStatus(transaction);
        }, 5, "schedule_iap_retry"); // 5s 来一次
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
