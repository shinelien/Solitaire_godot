//
// Created by Cyutao on 2019-08-01.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#ifndef ADSWF_ADCONFIG_H
#define ADSWF_ADCONFIG_H

#include "WFManager.h"
#include "AdInterface.h"
class AdConfig {
public:
    AdConfig(AdInterface::AdType adType, WFManager::Type type, int pid, int price, const std::string &key);

    bool operator>(const AdConfig& config) {
        return _price > config._price;
    }
private:
    AdInterface::AdType _adType;
    WFManager::Type _type;
public:
    AdInterface::AdType getAdType() const;

    WFManager::Type getType() const;

    int getPid() const;

    int getPrice() const;

    const std::string &getKey() const;

private:
    int _pid, _price;
    std::string _key;
};


#endif //ADSWF_ADCONFIG_H
