//
//  UIUtils.c
//  SpacecatSolitaireGame-mobile
//
//  Created by Cyutao on 2018/9/21.
//

#include "UIUtils.h"
#include "DataManager.h"
#include "FeedBackView.h"
#include "LikemeView.h"
#include "SceneManager.h"

#import "ReachabilityImpl.h"
#import <StoreKit/StoreKit.h>
#import "Firebase.h"
#import "GameKitHelper.h"
#import "AppController.h"
#import "NSObject+NSLocalNotification.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#import <AdSupport/AdSupport.h>
#include "sys/utsname.h"
#include "PlayerManager.h"
#include "GameBackground.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::network;

int UIUtils::getNetworkState()
{
    return [[ReachabilityImpl shareInstance] currentReachabilityStatus];
}

void UIUtils::requestReview() {
    auto flag = UserDefault::getInstance()->getBoolForKey("feedback_flag", false);
    if (!flag) {
//#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
        auto cnt = DATA_M->getAppStartCNT();
        if (cnt >= 10 && cnt % 10 ==0 )
        {
//            SCENE_M->addDialog(FeedBackView::createLayerN());
            //SCENE_M->addDialog(LikemeView::createLayerN());
#ifdef __IPHONE_10_3
            if ([UIDevice currentDevice].systemVersion.floatValue >= 10.3) {//面临问题就是评价完之后，还让用户评价
                [[UIApplication sharedApplication].keyWindow endEditing:YES];
                [SKStoreReviewController requestReview];
            }
//#else
//            SCENE_M->addDialog(LikemeView::createLayerN());
            
#endif
        }
//#endif
    }
}

void UIUtils::FIRAnalyticsEvent(const std::string &eventName, const ValueMap &params)
{
    @autoreleasepool {
        NSMutableDictionary *MDic = [[[NSMutableDictionary alloc] initWithCapacity:0] autorelease];
        for (auto item:params) {
            switch (item.second.getType()) {
                case Value::Type::STRING:
                    [MDic setObject:[NSString stringWithUTF8String:item.second.asString().c_str()] forKey:[NSString stringWithUTF8String:item.first.c_str()]];
                    break;
                case Value::Type::INTEGER:
                    [MDic setObject:[NSNumber numberWithInt:item.second.asInt()] forKey:[NSString stringWithUTF8String:item.first.c_str()]];
                    break;
                case Value::Type::FLOAT:
                    [MDic setObject:[NSNumber numberWithInt:item.second.asFloat()] forKey:[NSString stringWithUTF8String:item.first.c_str()]];
                    break;
                default:
                    [MDic setObject:[NSString stringWithUTF8String:item.second.asString().c_str()] forKey:[NSString stringWithUTF8String:item.first.c_str()]];
                    break;
            }
        }
        //    [MDic setObject:@"world" forKey:@"hello"];
        [FIRAnalytics logEventWithName: [NSString stringWithUTF8String:eventName.c_str()]
                            parameters:MDic];
    }
}

void UIUtils::FIRAnalyticsUserProperty(const std::string &key, const std::string &property)
{
    [FIRAnalytics setUserPropertyString:[NSString stringWithUTF8String:property.c_str()] forName:[NSString stringWithUTF8String:key.c_str()]];
}

void UIUtils::FIRAnalyticsTrackScreens(const std::string &name) {
    [FIRAnalytics setScreenName:[NSString stringWithUTF8String:name.c_str()] screenClass:[NSString stringWithUTF8String:name.c_str()]];
}

void UIUtils::calIAP(const std::string &id, bool isSub) {
    auto date = StringUtils::format("{\"orderId\":\"GPA.3363-0565-2774-55761\",\"packageName\":\"com.cn.spacecate.solitaire2k\",\"productId\":\"%s\",\"purchaseTime\":1622189494132,\"purchaseState\":0,\"purchaseToken\":\"gmlppegnelimbgghilbjnglj.AO-J1OyhKExzbkE2DkcHZBlJS-3i5AB8DLMjun4zPxOvMkeA7Z98UHF2g2VdUxUqPdZa3oEWAWbEv8uGGJ1DQDuz2BDcA2Qx36u1GP6XOD63Sd3j9KXzUIY\",\"acknowledged\":false,\"msg\":\"game_purchase\"}", id.c_str());
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("jni_event_custom_callcppwithstring", (void*)__String::create(date.c_str()));
}

std::string UIUtils::getProduct(const std::string &id) {
//    return "{\"productId\":\"gold_0\",\"type\":\"inapp\",\"price\":\"HK$8.00\",\"price_amount_micros\":8000000,\"price_currency_code\":\"HKD\",\"title\":\"Gold (Solitaire 2021)\",\"description\":\"Get gold 100\",\"skuDetailsToken\":\"AEuhp4KFrLxPFPv6yEUqE88qw7d5BKDi2QRjOx3YyuANCAFx65Od5QSG6_DaUk9AMac=\"}";
    return "";
}

void UIUtils::openMail() {
    GameKitHelper::openMail();
}

void UIUtils::shareApp() {
    GameKitHelper::shareApp();
}

void UIUtils::writComment() {
    GameKitHelper::writComment();
}

void UIUtils::showSetting()
{
    //跳转到“About”(关于本机)页面
    NSURL * url = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
    if([[UIApplication sharedApplication] canOpenURL:url]) {
        NSURL*url =[NSURL URLWithString:UIApplicationOpenSettingsURLString];
        [[UIApplication sharedApplication] openURL:url];
    }
}

void UIUtils::registNotify(float time, const std::string& key, const std::string& content, bool isDelay)
{
    if (isDelay)
    {
        NSString * randomNotify= [NSString stringWithUTF8String:content.c_str()];
//        [AppController registerLocalNotificationWith:time content:NSLocalizedString([NSString stringWithUTF8String:content.c_str()], @"") key: [NSString stringWithUTF8String:key.c_str()]];
        
        // 创建一个本地推送//
        UILocalNotification *notification = [[[UILocalNotification alloc] init] autorelease];
        //设置delalt秒之后//
        NSDate *pushDate = [NSDate dateWithTimeIntervalSinceNow:time];
        if (notification != nil)
        {
            // 设置推送时间//
            notification.fireDate = pushDate;
            // 设置时区//
            notification.timeZone = [NSTimeZone defaultTimeZone];
            // 设置重复间隔//
            
            notification.repeatInterval = 0;
            
            // 推送声音//
            notification.soundName = UILocalNotificationDefaultSoundName;
            // 推送内容//
            notification.alertBody = [NSString stringWithUTF8String: [randomNotify UTF8String]];
            //显示在icon上的红色圈中的数子//
            notification.applicationIconBadgeNumber = 1;
            //设置userinfo 方便在之后需要撤销的时候使用//
            NSDictionary *info = [NSDictionary dictionaryWithObject:[NSString stringWithUTF8String: key.c_str()] forKey:@"DDNoticfykey"];
            notification.userInfo = info;
            //添加推送到UIApplication//
            UIApplication *app = [UIApplication sharedApplication];
            [app scheduleLocalNotification:notification];
        }
    }
    else
    {
        [AppController registerLocalNotification:time content:NSLocalizedString([NSString stringWithUTF8String:content.c_str()], @"") key: [NSString stringWithUTF8String:key.c_str()]];     // 下午6点
    }
}

void UIUtils::unregistNotify(const std::string& key)
{
    // 获得 UIApplication
    UIApplication *app = [UIApplication sharedApplication];
    app.applicationIconBadgeNumber = 0;
    //获取本地推送数组
    NSArray *localArray = [app scheduledLocalNotifications];
    //声明本地通知对象
    UILocalNotification *localNotification = nil;
    
    if (localArray)
    {
        for (UILocalNotification *noti in localArray)
        {
            NSDictionary *dict = noti.userInfo;
            if (dict) {
                NSString* keys = [[[NSString alloc] initWithUTF8String: key.c_str()] autorelease];
                NSString* inKey = [dict objectForKey:@"DDNoticfykey"];
                
                if ([inKey isEqualToString:keys])
                {
                    //NSLog(@"remove1 %@,%@",keys,inKey);
                    [app cancelLocalNotification: noti];
                    if (localNotification){
                        [localNotification release];
                        localNotification = nil;
                    }
                    localNotification = [noti retain];
                    break;
                }
                
            }
        }
        //判断是否找到已经存在的相同key的推送
        if (!localNotification) {
            //不存在初始化
            localNotification = [[UILocalNotification alloc] init];
        }
        
        if (localNotification) {
            //不推送 取消推送
            [app cancelLocalNotification:localNotification];
            [localNotification release];
            return;
        }
    }
    [AppController cancelLocalNotificationWithKey:[NSString stringWithUTF8String:key.c_str()]];
}

std::string UIUtils::getDeviceModel(){
    struct utsname systemInfo;
    uname(&systemInfo);
    NSString *deviceString = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    const char * model = [deviceString UTF8String];
    return model;
}

std::string UIUtils::getUtcTimeZone()
{
    NSTimeZone *zone = [NSTimeZone systemTimeZone];
//    NSTimeZone *timeZone = [NSTimeZone timeZoneWithAbbreviation:@"UTC"];
    return [zone.name UTF8String];
}

std::string UIUtils::getAD()
{
    NSString *idfa = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
    return [idfa UTF8String];
}

std::string UIUtils::getVersion()
{
    return [[[[NSBundle mainBundle]infoDictionary] objectForKey:@"CFBundleShortVersionString"] UTF8String];
}

std::string UIUtils::getVersionCode()
{
    return [[[[NSBundle mainBundle]infoDictionary] objectForKey:@"CFBundleVersion"] UTF8String];
}

std::string UIUtils::getPackageName()
{
    return [[[[NSBundle mainBundle]infoDictionary] objectForKey:@"CFBundleIdentifier"] UTF8String];
}

bool UIUtils::getFirConfig(const std::string &key)
{
    return false;
}

std::string UIUtils::getCountryID() {
    //语言_国家
    NSString *locale = [[NSLocale currentLocale] localeIdentifier];
    NSLog(@"current locale: %@",locale);
//    NSRange startRange = [locale rangeOfString:@"_"];
//    NSString *result = [locale stringByReplacingCharactersInRange:NSMakeRange(0,startRange.length+1) withString:[[NSLocale preferredLanguages] objectAtIndex:0]];
//    NSLog(@"current locale result: %@",result);
    std::string str = [locale UTF8String];
    auto vec = UIUtils::split(str, "_");
    if(vec.size() > 1)
    {
        return vec.at(1);
    }
    return [locale UTF8String];
}


