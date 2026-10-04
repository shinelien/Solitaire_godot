//
// Created by Cyutao on 2019-07-31.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#ifndef ADSWF_UNITYMANAGER_H
#define ADSWF_UNITYMANAGER_H

#include "AdInterface.h"

class UnityManager : public  AdInterface{
public:
    bool init() override;

    std::vector<std::string> getReadyAds(AdType adType) override;

    bool showAds(AdType adType, const std::string &id) override;

    bool isReady(AdType adType) override;

private:
    void createVideoAds();
    void showVideoAds();
    bool showInterstitialAds();
};


#endif //ADSWF_UNITYMANAGER_H
