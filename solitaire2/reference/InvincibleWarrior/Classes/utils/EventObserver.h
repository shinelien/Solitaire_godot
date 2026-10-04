//
// Created by Cyutao on 2018/11/20.
//

#ifndef SPACECATSOLITAIREGAME_EVENTOBSERVER_H
#define SPACECATSOLITAIREGAME_EVENTOBSERVER_H

#define EVENT_M EventObserver::getInstance()

#include <unordered_map>
#include <vector>
#include <string>
#include "cocos2d.h"

using ObserverListenerFunc = std::function<void(cocos2d::ValueMap, void *)>;
class EventObserver {
public:
    static EventObserver* getInstance();

    void addListener(const std::string &key, const ObserverListenerFunc listener, void *thiz = 0);
    void removeListener(const std::string &key, void *thiz = 0);
    void sendEvent(const std::string &key, cocos2d::ValueMap params, void *obj = nullptr);
    void sendEvent(const std::string &key, void *obj = nullptr);
private:
    EventObserver();
    virtual ~EventObserver();
    static EventObserver* s_instance;

    bool _isSendingEvent = false;
    std::unordered_map<std::string, std::unordered_map<long, ObserverListenerFunc >> _listeners;
//    std::unordered_map<long, ObserverListenerFunc> _waitInsert, _waitRemove;
    std::vector<std::tuple<std::string, void *, ObserverListenerFunc>> _waitInsert, _waitRemove;
};
#define OB_M EventObserver::getInstance()

#endif //SPACECATSOLITAIREGAME_EVENTOBSERVER_H
