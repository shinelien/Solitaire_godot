#ifndef __VUNGLE_MANAGER_H__
#define __VUNGLE_MANAGER_H__

#include <iostream>
#include <vector>

class VungleManager
{
public:
    static void createVideoAds();
    static void showVideoAds();
    
    static void setRootViewController(void* _viewController);
    static void initAdsManager(void* _viewController);
    
    static bool isAdPlayable;
    static bool isAdPlaying;
protected:


};

#endif
