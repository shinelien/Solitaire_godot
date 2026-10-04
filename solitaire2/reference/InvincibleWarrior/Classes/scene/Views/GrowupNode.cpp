//
//  GrowupNode.cpp
//  SpacecatSolitaireGame-mobile
//
//  Created by Cyutao on 2018/11/18.
//

#include "GrowupNode.h"

using namespace cocos2d;
using namespace cocos2d::ui;

GrowupNode::GrowupNode()
{
    
}

void GrowupNode::startGrouwup(TextBMFont *label, int startNum, int endNum, float time,std::string str, std::function<void()> callFunc)
{
    labelBMF = label;
    _cb = callFunc;
    auto speed = (endNum - startNum) / time;
    _currentNum = startNum;
    label->setString(str + StringUtils::toString(_currentNum));
    label->schedule([this, label, startNum,endNum, speed,str, callFunc](float t) {
        _currentNum+=speed*t;
        if(startNum<=endNum)
        {
            if (_currentNum>=endNum) {
                _currentNum = endNum;
                label->unschedule("schedule_label_update");
                if (callFunc)
                    callFunc();
            }
        }
        else
        {
            if (_currentNum<=endNum) {
                _currentNum = endNum;
                label->unschedule("schedule_label_update");
                if (callFunc)
                    callFunc();
            }
        }
        
        label->setString(str + StringUtils::toString((int)_currentNum));
    }, 0, "schedule_label_update");
}

void GrowupNode::startGrouwup(Text *label, int startNum, int endNum, float time, std::function<void()> callFunc)
{
    labelText = label;
    _cb = callFunc;
    auto speed = (endNum - startNum) / time;
    _currentNum = startNum;
    label->setString(StringUtils::toString(_currentNum));
    label->schedule([this, label,startNum, endNum, speed, callFunc](float t) {
        _currentNum+=speed*t;
        if(startNum<=endNum)
        {
            if (_currentNum>=endNum) {
                _currentNum = endNum;
                label->unschedule("schedule_label_update");
                if (callFunc)
                    callFunc();
            }
        }
        else
        {
            if (_currentNum<=endNum) {
                _currentNum = endNum;
                label->unschedule("schedule_label_update");
                if (callFunc)
                    callFunc();
            }
        }
        
        label->setString(StringUtils::toString((int)_currentNum));
    }, 0, "schedule_label_update");
}


void GrowupNode::unTextSchedule()
{
    if(labelBMF)
    {
        labelBMF->unschedule("schedule_label_update");
    }
    if(labelText)
    {
        labelText->unschedule("schedule_label_update");
    }
    if(_cb)
    {
        _cb();
    }
}
