#ifndef __ADS_MANAGER_H__
#define __ADS_MANAGER_H__

#include <iostream>
#include <vector>

class AdsManager
{
public:
    static void createVideoAds(bool init = false);
    static void showVideoAds();
    

    static void createBannerView(bool init = false);
    static void createBannerFBView(bool init = false);
    static void showBanner();

    static void setBannerVisible(bool flag);
    static void createNativeExpressAds(int type = 1);
    static void loadNativeExpressAds(bool init = false);
    static void showNativeExpressAds(int type = 1);
    static void hiedNativeExpressAds(int type = 1);
    
    static void createInterstitial(bool init = false);
    static bool showInterstitial();
    static bool showInterstitialAtLoaded();
    
    static bool haveInterstitials();
    static bool haveRewardVides();
    
    // facebook
    static void createInterstitialFB(bool init = false);
    static bool showInterstitialFB();

    static void setRootViewController(void* _viewController);
    static void createMutliInterstitial();
//    static void reloadMutliInterstitial();
    
    static void initAdsManager(void* _viewController);

    static bool isTest;
    static bool waitWinAction;
    static float getFrameScaleFactor();
    static float bannerHeight;
    static bool bannerVisible, bannerInit, admobBannerEnabled, admobBannerRefresh, nativeInit, AppLoadShowADS;
protected:

};

#endif
