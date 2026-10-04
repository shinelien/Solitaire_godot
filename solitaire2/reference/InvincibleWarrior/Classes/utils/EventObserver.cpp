//
// Created by Cyutao on 2018/11/20.
//

#include "EventObserver.h"

EventObserver *EventObserver::s_instance = nullptr;
EventObserver *EventObserver::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new (std::nothrow)EventObserver();
    }
    return s_instance;
}

long getCLASSID(void *thiz)
{
    return (long)thiz;
}

void EventObserver::addListener(const std::string &key, const ObserverListenerFunc listener, void *thiz) {
    if (_isSendingEvent)
    {
        _waitInsert.push_back({key, thiz, listener});
        return;
    }
    auto it = _listeners.find(key);
    if (it != _listeners.end()) {
        it->second[getCLASSID(thiz)] = listener;
    }
    else {
        std::unordered_map<long, ObserverListenerFunc> subListeners;
        subListeners[getCLASSID(thiz)] = listener;
        _listeners[key] = subListeners;
    }
}

void EventObserver::removeListener(const std::string &key, void *thiz) {
    if (_isSendingEvent)
    {
        _waitRemove.push_back({key, thiz, nullptr});
        return;
    }
    auto it = _listeners.find(key);
    if (it != _listeners.end()) {
        auto subIt = it->second.find(getCLASSID(thiz));
        if (subIt != it->second.end()) {
            it->second.erase(subIt);
        }
    }
}

void EventObserver::sendEvent(const std::string &key, void *obj)
{
    cocos2d:: ValueMap valueMap;
    sendEvent(key, valueMap, obj);
}

void EventObserver::sendEvent(const std::string &key, cocos2d::ValueMap params, void *obj) {
    auto it = _listeners.find(key);
    if (it != _listeners.end()) {
        _isSendingEvent = true;
        for (auto &subIt:it->second) {
            if (subIt.second) subIt.second(params, obj);
        }
        _isSendingEvent = false;
    }
    for (auto &t: _waitRemove) {
        removeListener(std::get<0>(t), std::get<1>(t));
    }
    _waitRemove.clear();
    for (auto &t: _waitInsert) {
        addListener(std::get<0>(t), std::get<2>(t), std::get<1>(t));
    }
    _waitInsert.clear();
}

EventObserver::EventObserver() {

}

EventObserver::~EventObserver() {
    _listeners.clear();
}
