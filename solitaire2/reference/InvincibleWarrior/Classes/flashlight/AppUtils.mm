//
//  OpenUrl.m
//  Oc_Cpp
//
//  Created by Himi on 12-4-10.
//  Copyright (c) 2012年 Himi. All rights reserved.
//

#include "AppUtils.h"
#include "AdSupport/ASIdentifierManager.h"
#include "GTMBase64.h"
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>

void AppUtils::openAUrl(const char* url)
{
//    NSString *astring = [[NSString alloc] initWithCString:url encoding:NSUTF8StringEncoding];
    NSString *astring = [NSString stringWithCString:url encoding:NSUTF8StringEncoding];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:astring]];
}

const char* AppUtils::getIdfa()
{
    NSString *idfa = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
    const char* idfachar = [idfa UTF8String];
    return idfachar;
}

const char* AppUtils::getMacAddress()
{
    int                 mib[6];
    size_t              len;
    char                *buf;
    unsigned char       *ptr;
    struct if_msghdr    *ifm;
    struct sockaddr_dl  *sdl;
    
    mib[0] = CTL_NET;
    mib[1] = AF_ROUTE;
    mib[2] = 0;
    mib[3] = AF_LINK;
    mib[4] = NET_RT_IFLIST;
    
    if ((mib[5] = if_nametoindex("en0")) == 0) {
        printf("Error: if_nametoindex error/n");
        return NULL;
    }
    
    if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 1/n");
        return NULL;
    }
    
    if ((buf = (char*)malloc(len)) == NULL) {
        printf("Could not allocate memory. error!/n");
        return NULL;
    }
    
    if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 2");
        return NULL;
    }
    
    ifm = (struct if_msghdr *)buf;
    sdl = (struct sockaddr_dl *)(ifm + 1);
    ptr = (unsigned char *)LLADDR(sdl);
    //NSString* outstring = [NSString stringWimacAddressthFormat:@"%02x:%02x:%02x:%02x:%02x:%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
    NSString* outstring = [NSString stringWithFormat:@"%02x:%02x:%02x:%02x:%02x:%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
    
    free(buf);
    
    const char* macAddress = [[outstring uppercaseString] UTF8String];
    return macAddress;
}

float AppUtils::getIosVersion()
{
    return [[UIDevice currentDevice].systemVersion floatValue];
}

void AppUtils::clearApplicationIconBadgeNumber()
{
    [[UIApplication sharedApplication] setApplicationIconBadgeNumber:0];
}

const char* AppUtils::getBundleIdentifier()
{
    NSString *bundleIdentifier = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleIdentifier"];
    const char* identifierchar = [bundleIdentifier UTF8String];
    return identifierchar;
}

bool AppUtils::isIPad()
{
    return (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) ? true : false;
}

void AppUtils::setScreenAutoLocked(bool bValue)
{
    if (bValue)
    {
        [UIApplication sharedApplication].idleTimerDisabled = NO;
    }
    else
    {
        [UIApplication sharedApplication].idleTimerDisabled = YES;
    }
}

const char* AppUtils::base64Encode(const char* data, unsigned int len, unsigned int& returnLen)
{
    NSData *encodeData = [GTMBase64 encodeBytes:data length:len];
    returnLen = (unsigned int)[encodeData length];
    return (const char*)[encodeData bytes];
}

const char* AppUtils::base64Decode(const char* data, unsigned int len, unsigned int& returnLen)
{
    NSData *decodeData = [GTMBase64 decodeBytes:data length:len];
    returnLen = (unsigned int)[decodeData length];
    return (const char*)[decodeData bytes];
}

bool AppUtils::removeDir(const char* dirPath)
{
    NSString *nsDirPath = [NSString stringWithCString:dirPath encoding:NSUTF8StringEncoding];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    BOOL b = [fileManager removeItemAtPath:nsDirPath error:nil];
    
    return b ? true : false;
}

bool AppUtils::extractDataByTag(std::string strData, std::string& strRet, std::string strTag, std::string strPreTag, std::string strPostTag)
{
    //定位Tag
    long nIndex = strData.find(strTag);
    if (nIndex == -1)
    {
        return false;
    }
    strData = strData.substr(nIndex + strTag.length());
    
    //定位PreTag
    nIndex = strData.find(strPreTag);
    if(nIndex == -1)
    {
        return false;
    }
    strData = strData.substr(nIndex + strPreTag.length());
    
    if(!(strPostTag == ""))
    {
        nIndex = strData.find(strPostTag);
        if (nIndex == -1)
        {
            return false;
        }
        strRet = strData.substr(0, nIndex);
    }
    else
    {
        strRet = strData;
    }
    
    return true;
}

