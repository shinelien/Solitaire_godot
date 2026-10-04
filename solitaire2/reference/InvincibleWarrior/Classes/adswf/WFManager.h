//
// Created by Cyutao on 2019-07-30.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#ifndef ADSWF_ADSMANAGER_H
#define ADSWF_ADSMANAGER_H

#include <unordered_map>
#include "AdInterface.h"

class AdConfig;
class WFManager {
public:
    enum class Type{
        Admob,
        Facebook,
        Unity,
        AppLovin,
        Endl,
    };

    static WFManager *getInstance();

    void init(void * viewController);
    static void * getViewControl();
    static void setBannerVisible(bool visible) {}
    
    // banner
    bool showHighestBanner(const std::string &key, Type type, std::function<void()> cb = nullptr);
    void hideBanner(const std::string &key, Type type);
    void showBanner(const std::string &key, Type type);

    bool showHighestAds(AdInterface::AdType adType, Type type = Type::Endl);
    bool showInertitial(Type type = Type::Endl);
    bool showRewardVideo(Type type = Type::Endl);
    bool isReady(AdInterface::AdType adType, Type type = Type::Endl);
    
    int getPrice(Type type, const std::string &key = "");

    static bool bannerVisible, bannerInit, nativeInit, isTest;
private:
    WFManager();
    void pushManager(Type type);
    void setConfigs();
    
    std::shared_ptr<AdInterface> getManager(Type type);

    std::unordered_map<int, std::shared_ptr<AdInterface>> _adManagers;
    std::unordered_map<std::string, std::shared_ptr<AdConfig>> _adConfigs;
    std::string _currentConfig;
    // banner
    Type _currentBannerType = Type::Endl;
    std::string _currentBannerKey;
};


#endif //ADSWF_ADSMANAGER_H
