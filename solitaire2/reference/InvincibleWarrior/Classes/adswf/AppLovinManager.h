//
// Created by Cyutao on 2019-07-31.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#ifndef ADSWF_APPLOVINMANAGER_H
#define ADSWF_APPLOVINMANAGER_H

#include "AdInterface.h"

class AppLovinManager : public AdInterface{
public:
    bool init() override;

    static void createVideoAds();
    static void createInterstitialAd();

    bool showAds(AdType adType, const std::string &id) override;

    std::vector<std::string> getReadyAds(AdType adType) override;

    bool isReady(AdType adType) override;

private:
    void showInterstitialAd();

    void showVideoAds();
};


#endif //ADSWF_APPLOVINMANAGER_H
