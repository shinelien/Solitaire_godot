//
//  AdMobManager.hpp
//  AdsWF
//
//  Created by Cyutao on 2019/7/30.
//  Copyright © 2019 Cyutao. All rights reserved.
//

#ifndef AdMobManager_hpp
#define AdMobManager_hpp

#include "AdInterface.h"

class AdMobManager : public AdInterface{
public:
    bool init() override;

    bool showAds(AdType adType, const std::string &id) override;
    void hideAds(AdType adType, const std::string &id) override;

    static bool isTest, admobBannerRefresh, bannerVisible, bannerInit, waitWinAction;
    static float bannerHeight;

    std::vector<std::string> getReadyAds(AdType adType) override;

    int getDefaultPrice(AdType adType, const std::string &_id = "") override;

    bool isReady(AdType adType) override;

    void reloadAds(AdType adType) override;
private:
    void createMutilBanner();
    void createMutliInterstitial();
    void createMutliRewardVideo();
    bool showInterstitial(const std::string &id = "");
    bool showRewardVideo(const std::string &id = "");
    
    void *_viewController;
};

#endif /* AdMobManager_hpp */
