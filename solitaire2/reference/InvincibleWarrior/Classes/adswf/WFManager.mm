//
// Created by Cyutao on 2019-07-30.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#import <iostream>
#import <vector>
#include "WFManager.h"
#include "AdmobManager.h"
#include "FBManager.h"
#include "UnityManager.h"
#include "AppLovinManager.h"
#include "AdConfig.h"
#import "Firebase.h"
#import <AdSupport/ASIdentifierManager.h>
#include "cocos2d.h"

using namespace std;

#if COCOS2D_DEBUG > 0
bool WFManager::isTest = true;
#else
bool WFManager::isTest = false;
#endif

bool WFManager::bannerVisible = true;
bool WFManager::bannerInit = false;
bool WFManager::nativeInit = false;

static FIRRemoteConfig* firbaseConfig = [FIRRemoteConfig remoteConfig];

static void * s_viewController = nil;

// 读取本地JSON文件
NSDictionary *readLocalFileWithName(NSString *name) {
    // 获取文件路径
    NSString *path = [[NSBundle mainBundle] pathForResource:name ofType:@"json"];
    // 将文件数据化
    NSData *data = [[NSData alloc] initWithContentsOfFile:path];
    if (data == nil)
    {
        return @{};
    }
    else
    {
        // 对数据进行JSON格式化并返回字典形式
        return [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:nil];
    }
}

void WFManager::init(void * viewController) {
    s_viewController = viewController;

    [FIRApp configure];
    
    firbaseConfig = [FIRRemoteConfig remoteConfig];
    NSDictionary* waterfall = readLocalFileWithName([NSString stringWithUTF8String:"waterfall"]); //@{@"dynamic_waterfall": @"{\"hello\" : 1}"}
    [firbaseConfig setDefaults:waterfall];
    
    [firbaseConfig fetchWithCompletionHandler:^(FIRRemoteConfigFetchStatus status, NSError * _Nullable error) {
       if (status == FIRRemoteConfigFetchStatusSuccess)
       {
           setConfigs();
       }
    }];
    setConfigs();
    
    // 初始话banner高度
    AdMobManager::bannerHeight = GAD_SIZE_320x50.height;
    auto yy = Director::getInstance()->getSafeAreaRect().origin.y;
    AdMobManager::bannerHeight += yy>10?20:0;
    
    pushManager(Type::Admob);
    pushManager(Type::Facebook);
    pushManager(Type::Unity);
//    pushManager(Type::AppLovin);
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    NSString *idfa = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
    cocos2d::log("[xxx idfa:%s]", [idfa UTF8String]);
#endif
}

void *WFManager::getViewControl() {
    return s_viewController;
}

void WFManager::pushManager(WFManager::Type type) {
    shared_ptr<AdInterface> adManager = nullptr;
    switch (type) {
        case Type::Admob:
            adManager = make_shared<AdMobManager>();
            break;
        case Type::Facebook:
            adManager = make_shared<FBManager>();
            break;
        case Type::Unity:
            adManager = make_shared<UnityManager>();
            break;
        case Type::AppLovin:
            adManager = make_shared<AppLovinManager>();
            break;
    }
    if (adManager != nullptr) {
        adManager->init();
    }
    _adManagers[(int)type] = adManager;
}

WFManager::WFManager() {
}

WFManager *WFManager::getInstance() {
    static WFManager instance;
    return &instance;
}

bool WFManager::showInertitial(WFManager::Type type) {
    return showHighestAds(AdInterface::AdType::Intertitial, type);
}

bool WFManager::showRewardVideo(WFManager::Type type) {
    return showHighestAds(AdInterface::AdType::RewardVideo, type);
}

bool WFManager::isReady(AdInterface::AdType adType, Type type)
{
    auto adManager = getManager(type);
    if (adManager) {
        return adManager->isReady(adType);
    }
    else {
        for (int i = (int)Type::Admob; i < (int)Type::Endl; ++i) {
            auto it = _adManagers.find(i);
            if (it == _adManagers.end()) continue;  // 按顺序来
            
            auto adManager = it->second;
            if (adManager->isReady(adType))
            {
                cocos2d::log("[wfmanager]%d(%d) ready to show!!!", i, adType);
                return true;
            }
        }
    }
    return false;
}

std::shared_ptr<AdInterface> WFManager::getManager(WFManager::Type type) {
    auto it = _adManagers.find((int)type);
    if (it == _adManagers.end())
    {
        return nullptr;
    }
    else {
        return it->second;
    }
}

// 如果修改 枚举修改此处⚠️
WFManager::Type getType(int type) {
    switch (type) {
        case 0:
            return WFManager::Type::Admob;
        case 1:
            return WFManager::Type::Facebook;
        case 2:
            return WFManager::Type::Unity;
        case 3:
            return WFManager::Type::AppLovin;
        default:
            return WFManager::Type::Endl;
    }
}

// 如果修改 枚举修改此处⚠️
WFManager::Type getType(const string type) {
    if (type == "admob")
        return WFManager::Type::Admob;
    else if (type == "facebook")
        return WFManager::Type::Facebook;
    else if (type == "unity")
        return WFManager::Type::Unity;
    else if (type == "applovin")
        return WFManager::Type::AppLovin;
    
    return WFManager::Type::Endl;
}

shared_ptr<AdConfig> getConfig(AdInterface::AdType adType, NSDictionary* obj)
{
    NSLog(@"obj:%@", obj);
    string type = [[obj valueForKey:@"type"] UTF8String];
    int pid = [[obj valueForKey:@"pid"] intValue];
    int price = [[obj valueForKey:@"price"] intValue];
    string key = [[obj valueForKey:@"r"] UTF8String];
    return make_shared<AdConfig>(adType, getType(type), pid, price, key);
}

void WFManager::setConfigs() {
    [firbaseConfig activateFetched]; // 激活新的配置
    auto configStr = [firbaseConfig[@"dynamic_waterfall"].stringValue UTF8String];
    if (_currentConfig != configStr) {
        _currentConfig = configStr;
        _adConfigs.clear();
        NSString *responseString = [NSString stringWithUTF8String:configStr];
        NSData *jsonData = [responseString dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:nil];
        NSLog(@"%@",dic);
        for (NSDictionary * obj in dic[@"banner"]) {
            string key = [[obj valueForKey:@"r"] UTF8String];
            _adConfigs[key] = getConfig(AdInterface::AdType::Banner, obj);
        }
        for (NSDictionary * obj in dic[@"interstitial"]) {
            string key = [[obj valueForKey:@"r"] UTF8String];
            _adConfigs[key] = getConfig(AdInterface::AdType::Intertitial, obj);
        }
        for (NSDictionary * obj in dic[@"reward"]) {
            string key = [[obj valueForKey:@"r"] UTF8String];
            _adConfigs[key] = getConfig(AdInterface::AdType::RewardVideo, obj);
        }
    }
}

bool WFManager::showHighestBanner(const std::string &key, WFManager::Type type, function<void()> cb) {
    // 价高者得
    if (_currentBannerType == Type::Endl || getPrice(type, key) > getPrice(_currentBannerType, _currentBannerKey))
    {
        _currentBannerKey = key;
        _currentBannerType = type;

        if (bannerInit) {
            hideBanner(key, type);
        }
        bannerInit = true;
        if (cb) { cb(); }

        NSDictionary *dictM = @{
            @"msg":@"msg_banner_show",
            @"height":[[NSNumber alloc] initWithFloat:(AdMobManager::bannerHeight)]
        };
        NSData *data = [NSJSONSerialization dataWithJSONObject:dictM options:NSJSONWritingPrettyPrinted error:nil];
        NSString *strM = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
        NSLog(@"%@",strM);
        std::string jsonStr([strM UTF8String]);
        EventCustom event("jni_event_custom_callcppwithstring");
        event.setUserData((void*)jsonStr.c_str());
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        [strM release];
        return true;
    }
    return false;
}

void WFManager::hideBanner(const std::string &key, WFManager::Type type) {
    auto adManager = getManager(type);
    if (adManager != nullptr && adManager->isSupport(AdInterface::AdType::Banner)) {
        adManager->showAds(AdInterface::AdType::Banner, key);
    }
}

void WFManager::showBanner(const std::string &key, WFManager::Type type) {
    auto adManager = getManager(type);
    if (adManager != nullptr && adManager->isSupport(AdInterface::AdType::Banner)) {
        adManager->hideAds(AdInterface::AdType::Banner, key);
    }
}

bool WFManager::showHighestAds(AdInterface::AdType adType, WFManager::Type type) {
    if (type != Type::Endl) {
        auto adManager = getManager(type);
        if (adManager != nullptr) {
            adManager->showAds(adType, "");
            return true;
        }
    }
    else {
        int highestPrice = 0;
        string highestKey;
        bool rightConfig = _adConfigs.size() > 0;
        shared_ptr<AdInterface> highestAd = nullptr;
//        for (auto it:_adManagers) {
        for (int i = (int)Type::Admob; i < (int)Type::Endl; ++i) {
            auto it = _adManagers.find(i);
            if (it == _adManagers.end()) continue;  // 按顺序来
            
            auto adManager = it->second;
            adManager->reloadAds(adType); // 重新加载下广告
            vector<string> readyAdsVec = adManager->getReadyAds(adType);
            for (int j = 0; j < readyAdsVec.size(); ++j) {
                auto key = readyAdsVec.at(j);
                if (rightConfig) {
                    auto it = _adConfigs.find(key);
                    if (it != _adConfigs.end()) {
                        auto price = it->second->getPrice();
                        if (price > highestPrice)
                        {
                            highestPrice = price;
                            highestKey = key;
                            highestAd = adManager;
                        }
                    }
                    else if (highestAd == nullptr)
                    {
                        highestKey = key;
                        highestAd = adManager;
                    }
                }
                else {
                    return adManager->showAds(adType, highestKey);
                }
            }
        }
        if (highestAd)
            return highestAd->showAds(adType, highestKey);
    }
    return false;
}

int WFManager::getPrice(WFManager::Type type, const string &key) {
    auto adManager = getManager(type);
    if (adManager) {
        auto it = _adConfigs.find(key);
        if (it != _adConfigs.end()) {
            return it->second->getPrice();
        }
        else {
            return adManager->getDefaultPrice(AdInterface::AdType::Banner, key);
        }
    }
    return 0;
}
