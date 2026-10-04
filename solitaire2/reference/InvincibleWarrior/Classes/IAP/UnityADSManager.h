#ifndef __UNITYADS_MANAGER_H__
#define __UNITYADS_MANAGER_H__

#include <iostream>
#include <vector>

class UnityADSManager
{
public:
    static void createVideoAds();
    static void showVideoAds();
    static bool showInterstitialAds();
    
    static void setRootViewController(void* _viewController);
    static void initAdsManager(void* _viewController);
    
    static bool isAdPlayable;
    static bool isAdPlaying;
protected:


};

#endif
