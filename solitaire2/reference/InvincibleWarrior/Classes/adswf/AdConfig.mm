//
// Created by Cyutao on 2019-08-01.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#include "AdConfig.h"

AdInterface::AdType AdConfig::getAdType() const {
    return _adType;
}

WFManager::Type AdConfig::getType() const {
    return _type;
}

int AdConfig::getPid() const {
    return _pid;
}

int AdConfig::getPrice() const {
    return _price;
}

const std::string &AdConfig::getKey() const {
    return _key;
}

AdConfig::AdConfig(AdInterface::AdType adType, WFManager::Type type, int pid, int price, const std::string &key)
    : _adType(adType), _type(type), _pid(pid), _price(price), _key(key) {
}
