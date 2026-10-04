//
// Created by Cyutao on 2019-07-30.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#ifndef ADSWF_FBMANAGER_H
#define ADSWF_FBMANAGER_H

#include "AdInterface.h"

class FBManager : public AdInterface{
public:
    bool init() override;

    bool showAds(AdType adType, const std::string &id) override;
    void hideAds(AdType adType, const std::string &id) override;

    std::vector<std::string> getReadyAds(AdType adType) override;

    bool isReady(AdType adType) override;

    int getDefaultPrice(AdType adType, const std::string &_id = "") override;

    static bool isTest, admobBannerRefresh, bannerVisible, bannerInit, waitWinAction;
    static float bannerHeight;

    void reloadAds(AdType adType) override;

private:
    void createMutilBanner();
    void createMutliInterstitial();
    void createMutliRewardVideo();
    bool showInterstitial();
    bool showRewardVideo();
};


#endif //ADSWF_FBMANAGER_H
