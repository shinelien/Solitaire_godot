//
//  HSpriteOC.h
//  Oc_Cpp
//
//  Created by Himi  on 12-4-10.
//  Copyright (c) 2012年 Himi. All rights reserved.
//


#ifndef  _APP_UTILS_H_
#define  _APP_UTILS_H_

//#import <Foundation/Foundation.h>
#include "cocos2d.h"

/**
 @brief    The cocos2d Application.
 
 The reason to implement with private inheritance is to hide some interface details of CCDirector.
 */
class AppUtils : public cocos2d::Ref
{
public:
    static void openAUrl(const char* url);
    
    static const char* getIdfa();
    
    static const char* getMacAddress();
    
    static float getIosVersion();
    
    static void clearApplicationIconBadgeNumber();
    
    static const char* getBundleIdentifier();
    
    static bool isIPad();
    
    static void setScreenAutoLocked(bool bValue);
    
    static const char* base64Encode(const char* data, unsigned int len, unsigned int& returnLen);
    static const char* base64Decode(const char* data, unsigned int len, unsigned int& returnLen);
    
    static bool removeDir(const char* dirPath);
    
    static bool extractDataByTag(std::string strData, std::string& strRet, std::string strTag, std::string strPreTag, std::string strPostTag);

};

#endif // _APP_UTILS_H_
