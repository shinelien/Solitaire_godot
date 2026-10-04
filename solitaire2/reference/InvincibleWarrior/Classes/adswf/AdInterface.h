//
// Created by Cyutao on 2019-07-31.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#ifndef ADSWF_ADINTERFACE_H
#define ADSWF_ADINTERFACE_H

#include <string>
#include <unordered_map>

class AdInterface {
public:
    enum class AdType {
        Banner,
        Intertitial,
        RewardVideo,
        Endl,
    };

    virtual bool init() = 0;    // 初始化
    virtual bool isSupport(AdType adType) { return _supportedAdType.find((int)adType)!=_supportedAdType.end(); }  // 是否支持类型
    virtual bool showAds(AdType adType, const std::string &id) = 0;    // 展示广告
    virtual bool isReady(AdType adType) = 0;
    virtual std::vector<std::string> getReadyAds(AdType adType) = 0;

    virtual void hideAds(AdType adType, const std::string &_id) {}    // 展示广告
    virtual void reloadAds(AdType adType) {}    // 重新加载
    virtual int getDefaultPrice(AdType adType, const std::string &_id = "")  { return 0; }
protected:
    void setSupport(AdType adType) { _supportedAdType[(int)adType] = (int)adType; }

    std::unordered_map<int, int> _supportedAdType;
};


#endif //ADSWF_ADINTERFACE_H
