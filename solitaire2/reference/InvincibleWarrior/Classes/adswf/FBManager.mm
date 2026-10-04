//
// Created by Cyutao on 2019-07-30.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FBAudienceNetwork/FBAudienceNetwork.h>

#include "FBManager.h"
#import "WFManager.h"
#include "AdsManager.h"
#include "AdmobManager.h"
#include <vector>

#define DefaultRetryCNT 3

float FBManager::bannerHeight = 0.f;
bool FBManager::admobBannerRefresh = false;
FBAdView* bannerView = nil;
static int _bannerIdx=0, _interIdx=0, _rewardIdx=0;

static NSArray *bannerArray = [NSArray arrayWithObjects:@"700249183703463_711512392577142", @"700249183703463_711513745910340", @"700249183703463_711513845910330", @"700249183703463_711513985910316", nil];
static NSArray *interArray = [NSArray arrayWithObjects:@"700249183703463_711084749286573", @"700249183703463_711085202619861", @"700249183703463_711085369286511", @"700249183703463_711086112619770", nil];
static NSArray *videoArray = [NSArray arrayWithObjects:@"700249183703463_956915781370134", @"700249183703463_956915984703447", @"700249183703463_956916101370102", @"700249183703463_956916208036758", nil];

static NSMutableArray *GADBannerArray = [[NSMutableArray alloc] init];      // banner数组
static std::vector<int> BannerRetryCNT; // 重试次数
static NSMutableArray *interstitialArray = [[NSMutableArray alloc] init];   // 插屏数组
static std::vector<int> retryCNT;   // 重试次数
static NSMutableArray *GADRewardVideoArray = [[NSMutableArray alloc] init];   // 激励视频数组
static std::vector<int> RewardRetryCNT; // 重试次数

// banner
static void reloadBanner(FBAdView *t_bannerView);
static void reloadMutilBanner(FBAdView *t_bannerView = nullptr);
static void reloadMutilBannerSync(bool init);
static void showHighestBanner(FBAdView *t_bannerView = nullptr);
// interstitial
static void reloadInterstitial(FBInterstitialAd *t_interstitial);
static void reloadMutliInterstitialSync(bool init);
static void recreateInterstitial(FBInterstitialAd *t_interstitial);
static void reloadMutliInterstitial(FBInterstitialAd *reloadInterstitial = nullptr);
// rewardvideo
static void reloadRewardVideo(FBRewardedVideoAd *rewardedAd);
static void reloadMutliRewardVideoSync(bool init);
static void recreateRewardVideo(FBRewardedVideoAd *t_interstitial);
static void reloadMutliRewardVideo(FBRewardedVideoAd *rewardedAd = nullptr);

@interface FBAudienceNetworkObserver : NSObject<FBInterstitialAdDelegate, FBAdViewDelegate, FBRewardedVideoAdDelegate>
@end

@implementation FBAudienceNetworkObserver
- (void)interstitialAdDidLoad:(FBInterstitialAd *)interstitialAd
{
//    self.adStatusLabel.text = @"Ad failed to load. Check console for details.";
//    fbinterstitialAd = interstitialAd;
}

- (void)interstitialAd:(FBInterstitialAd *)interstitialAd didFailWithError:(NSError *)error
{
    NSLog(@"Ad failed to load(%@)", error);
//    AdsManager::createInterstitialFB();
//    reloadInterstitial(interstitialAd);
    reloadMutliInterstitialSync(false);
}

- (void)interstitialAdWillLogImpression:(FBInterstitialAd *)interstitialAd
{
    NSLog(@"The user sees the add");
// Use this function as indication for a user's impression on the ad.
}

- (void)interstitialAdDidClick:(FBInterstitialAd *)interstitialAd
{
    NSLog(@"The user clicked on the ad and will be taken to its destination");
// Use this function as indication for a user's click on the ad.
}

- (void)interstitialAdWillClose:(FBInterstitialAd *)interstitialAd
{
    NSLog(@"The user clicked on the close button, the ad is just about to close");
// Consider to add code here to resume your app's flow
}

- (void)interstitialAdDidClose:(FBInterstitialAd *)interstitialAd
{
    NSLog(@"Interstitial had been closed");
// Consider to add code here to resume your app's flow
//    reloadMutliInterstitial(interstitialAd);
    recreateInterstitial(interstitialAd);
    reloadMutliInterstitialSync(true);
    if (AdsManager::waitWinAction)
    {
        AdsManager::waitWinAction = false;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_showwin");
    }
}
// banner
- (void)adView:(FBAdView *)adView didFailWithError:(NSError *)error
{
    NSLog(@"Ad failed to load");
//    reloadBanner(adView);
    reloadMutilBannerSync(false);
}

- (void)adViewDidLoad:(FBAdView *)adView
{
    NSLog(@"Ad was loaded and ready to be displayed");
//AdsManager::showBanner();
    showHighestBanner(adView);
}

- (void)adViewDidClick:(FBAdView *)adView
{
    NSLog(@"Banner ad was clicked.");
}

- (void)adViewDidFinishHandlingClick:(FBAdView *)adView
{
    NSLog(@"Banner ad did finish click handling.");
}

- (void)adViewWillLogImpression:(FBAdView *)adView
{
    NSLog(@"Banner ad impression is being captured.");
}
// reward
- (void)rewardedVideoAd:(FBRewardedVideoAd *)rewardedVideoAd didFailWithError:(NSError *)error
{
    NSLog(@"Rewarded video ad failed to load");
//    reloadRewardVideo(rewardedVideoAd);
    reloadMutliRewardVideoSync(false);
}

- (void)rewardedVideoAdDidLoad:(FBRewardedVideoAd *)rewardedVideoAd
{
    NSLog(@"Video ad is loaded and ready to be displayed");
    SCENE_M->refushGift();
}

- (void)rewardedVideoAdDidClick:(FBRewardedVideoAd *)rewardedVideoAd
{
    NSLog(@"Video ad clicked");
}

- (void)rewardedVideoAdVideoComplete:(FBRewardedVideoAd *)rewardedVideoAd;
{
    NSLog(@"Rewarded Video ad video complete - this is called after a full video view, before the ad end card is shown. You can use this event to initialize your reward");
    //获得金币
    DATA_M->lingqujinbi(0);
}

- (void)rewardedVideoAdDidClose:(FBRewardedVideoAd *)rewardedVideoAd
{
    NSLog(@"Rewarded Video ad closed - this can be triggered by closing the application, or closing the video end card");
    DATA_M->playLingQUAction();
    //    reloadMutliRewardVideo(rewardedVideoAd);
    recreateRewardVideo(rewardedVideoAd);
    reloadMutliRewardVideoSync(true);
}
@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////
bool FBManager::init() {
    setSupport(AdType::Banner);
    setSupport(AdType::Intertitial);
    setSupport(AdType::RewardVideo);
    // init
    createMutilBanner();
    createMutliInterstitial();
    createMutliRewardVideo();
    return true;
}

static FBAudienceNetworkObserver *s_fbObserver = [[FBAudienceNetworkObserver alloc] init];
void FBManager::createMutilBanner() {
    UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
    for (NSString *interID in bannerArray) {
        FBAdView *fbbannerView = [[FBAdView alloc] initWithPlacementID:interID
                                                      adSize:kFBAdSizeHeight50Banner
                                          rootViewController:viewController];
        fbbannerView.frame = CGRectMake(0, viewController.view.frame.size.height-AdMobManager::bannerHeight, viewController.view.frame.size.width, kFBAdSizeHeight50Banner.size.height);
        fbbannerView.delegate = s_fbObserver;

        [GADBannerArray addObject:fbbannerView];
        BannerRetryCNT.push_back(DefaultRetryCNT);
    }
    reloadMutilBannerSync(true);
}

// banner
static void reloadBanner(FBAdView *t_bannerView) {
    auto idx = [GADBannerArray indexOfObject:t_bannerView];
    if (--BannerRetryCNT[idx] <= 0)
    {
        return;
    }

    t_bannerView.hidden = YES;
    [t_bannerView loadAd];
}

void reloadMutilBannerSync(bool init)
{
    if (init)
    {
        _bannerIdx = 0;
    }
    if (_bannerIdx >= GADBannerArray.count)
    {
        return;
    }
    BannerRetryCNT[_bannerIdx] = DefaultRetryCNT;
    FBAdView *t_bannerView = [GADBannerArray objectAtIndex:_bannerIdx++];
    reloadBanner(t_bannerView);
}
//
//static void reloadMutilBanner(FBAdView *t_bannerView) {
//    for (int i=0; i<GADBannerArray.count; i++) {
//        BannerRetryCNT[i] = DefaultRetryCNT;
//        FBAdView *t_bannerView = [GADBannerArray objectAtIndex:i];
//        if (t_bannerView != bannerView)
//            reloadBanner(t_bannerView);
//    }
//}

static void showHighestBanner(FBAdView *t_bannerView) {
    auto idx = [GADBannerArray indexOfObject:t_bannerView];
    NSString* key = [bannerArray objectAtIndex:idx];    // 获取 id
    if (WFManager::getInstance()->showHighestBanner([key UTF8String], WFManager::Type::Facebook, nullptr)) {
        if (bannerView != nil && bannerView.superview != nil) {
            bannerView.hidden = YES;
            [bannerView removeFromSuperview];
        }
        bannerView = t_bannerView;
        UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
        [viewController.view addSubview:bannerView];
        bannerView.hidden = !WFManager::bannerVisible;
    }
    else if (bannerView == t_bannerView && bannerView.hidden == NO) { // 刷新？？？
        if (FBManager::admobBannerRefresh) {
//            reloadMutilBanner();
            reloadMutilBannerSync(false);
            FBManager::admobBannerRefresh = false;
        }
        else {
            FBManager::admobBannerRefresh = true;
        }
    }
}

void FBManager::createMutliInterstitial() {
    for (NSString *interID in interArray) {
        FBInterstitialAd* fbinterstitialAd = [[FBInterstitialAd alloc] initWithPlacementID:interID];
        fbinterstitialAd.delegate = s_fbObserver;
        [interstitialArray addObject:fbinterstitialAd];
        retryCNT.push_back(DefaultRetryCNT);
    }
//    reloadMutliInterstitial();
    reloadMutliInterstitialSync(true);
}

static void recreateInterstitial(FBInterstitialAd *t_interstitial)
{
    NSUInteger idx = [interstitialArray indexOfObject:t_interstitial];
    if (idx>=0 && idx<interArray.count)
    {
        retryCNT[idx] =  DefaultRetryCNT;
        FBInterstitialAd *newinterstitial = [[FBInterstitialAd alloc] initWithPlacementID:[interArray objectAtIndex:idx]];
        newinterstitial.delegate = s_fbObserver;
    //            [t_interstitial.delegate release];
        [t_interstitial release];
        t_interstitial = newinterstitial;
        [interstitialArray replaceObjectAtIndex:idx withObject:newinterstitial];
    }
}

static void reloadMutliInterstitialSync(bool init)
{
    if (init)
    {
        _interIdx = 0;
    }
    if (_interIdx >= interstitialArray.count)
    {
        return;
    }
    retryCNT[_interIdx] =  DefaultRetryCNT;
    FBInterstitialAd *t_interstitial = [interstitialArray objectAtIndex:_interIdx++];
    reloadInterstitial(t_interstitial);
}

// interstitial
static void reloadInterstitial(FBInterstitialAd *t_interstitial) {
    if (t_interstitial.isAdValid)
        return;
    // 失败请求不会超过DefaultRetryCNT次
    auto idx = [interstitialArray indexOfObject:t_interstitial];
    if (--retryCNT[idx] <= 0)
        return;

    [t_interstitial loadAd];
}

//static void reloadMutliInterstitial(FBInterstitialAd *adinterstitial) {
//    for (int i = 0; i<interstitialArray.count;i++) {
//        retryCNT[i] =  DefaultRetryCNT;
//        FBInterstitialAd *t_interstitial = [interstitialArray objectAtIndex:i];
//        if (adinterstitial != nullptr && adinterstitial == t_interstitial) {
//            FBInterstitialAd *newinterstitial = [[FBInterstitialAd alloc] initWithPlacementID:[interArray objectAtIndex:i]];
//            newinterstitial.delegate = s_fbObserver;
//            [t_interstitial release];
//            t_interstitial = newinterstitial;
//            [interstitialArray replaceObjectAtIndex:i withObject:newinterstitial];
//        }
//        if (!t_interstitial.isAdValid) {
//            reloadInterstitial(t_interstitial);
//        }
//    }
//}

bool FBManager::showInterstitial() {
    for (FBInterstitialAd *t_interstitial in interstitialArray) {
        if (t_interstitial.isAdValid) {
            UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
            [t_interstitial showAdFromRootViewController:viewController];
            return true;
        }
    }
    NSLog(@"Ad wasn't ready");
//    reloadMutliInterstitial();
    reloadMutliInterstitialSync(true);
    return false;
}

bool FBManager::showRewardVideo() {
    for (FBRewardedVideoAd *t_rewardedAd in GADRewardVideoArray) {
        if (t_rewardedAd.isAdValid) {
            UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
            [t_rewardedAd showAdFromRootViewController:viewController];
            return true;
        }
    }
    NSLog(@"Ad wasn't ready");
//    reloadMutliRewardVideo();
    reloadMutliRewardVideoSync(true);
    return false;
}

void FBManager::createMutliRewardVideo() {
    for (NSString *adUnitId in videoArray) {
        FBRewardedVideoAd *rewardedAd = [[FBRewardedVideoAd alloc] initWithPlacementID:adUnitId];
        rewardedAd.delegate = s_fbObserver;

        [GADRewardVideoArray addObject:rewardedAd];
        RewardRetryCNT.push_back(DefaultRetryCNT);
    }
//    reloadMutliRewardVideo();
    reloadMutliRewardVideoSync(true);
}

bool FBManager::showAds(AdInterface::AdType adType, const std::string &id) {
    switch (adType) {
        case AdType::Intertitial:
            return showInterstitial();
        case AdType::RewardVideo:
            showRewardVideo();
            break;
    }
    return false;
}

void FBManager::hideAds(AdInterface::AdType adType, const std::string &id) {
    switch (adType) {
        case AdType::Banner:
            auto idx = [bannerArray indexOfObject:[NSString stringWithUTF8String:id.c_str()]];
            FBAdView* bannerView1 = [GADBannerArray objectAtIndex:idx];    // 获取 id
            if (bannerView1 != nil && bannerView1.superview != nil) {   // 隐藏banner
                bannerView1.hidden = YES;
                [bannerView1 removeFromSuperview];
            }
            if (bannerView1 == bannerView) {
                bannerView = nil;
            }
            break;
    };
}

std::vector<std::string> FBManager::getReadyAds(AdInterface::AdType adType) {
    std::vector<std::string> readyAdsVec;
    if (adType == AdInterface::AdType::Intertitial) {
        for (int i = 0; i<interstitialArray.count;i++) {
            FBInterstitialAd *t_interstitial = [interstitialArray objectAtIndex:i];
            if (t_interstitial.isAdValid) {
                NSString* key = [interArray objectAtIndex:i];
                readyAdsVec.push_back([key UTF8String]);
            }
        }
    }
    else if (adType == AdInterface::AdType::RewardVideo) {
        for (int i = 0; i<GADRewardVideoArray.count;i++) {
            FBRewardedVideoAd *t_interstitial = [GADRewardVideoArray objectAtIndex:i];
            if (t_interstitial.isAdValid) {
                NSString* key = [videoArray objectAtIndex:i];
                readyAdsVec.push_back([key UTF8String]);
            }
        }
    }
    return readyAdsVec;
}

void FBManager::reloadAds(AdInterface::AdType adType) {
    AdInterface::reloadAds(adType);
    switch (adType) {
        case AdType ::Banner:
//            reloadMutilBanner();
            reloadMutilBannerSync(true);
            break;
        case AdType::Intertitial:
            reloadMutliInterstitialSync(true);
        case AdType::RewardVideo:
            reloadMutliRewardVideoSync(true);
            break;
    }
}

int FBManager::getDefaultPrice(AdInterface::AdType adType, const std::string &_id) {
    switch (adType) {
        case AdType::Banner:
            int idx = [bannerArray indexOfObject:[NSString stringWithUTF8String:_id.c_str()]];
            return idx+1;
    }
    return AdInterface::getDefaultPrice(adType);
}

bool FBManager::isReady(AdInterface::AdType adType) {
    switch (adType) {
        case AdType::Intertitial:
            for (FBInterstitialAd *t_interstitial in interstitialArray) {
                if (t_interstitial.isAdValid) {
                    return true;
                }
            }
            break;
        case AdType::RewardVideo:
            for (FBRewardedVideoAd *t_rewardedAd in GADRewardVideoArray) {
                if (t_rewardedAd.isAdValid) {
                    return true;
                }
            }
            break;
    }
    reloadAds(adType);
    return false;
}

// rewardvideo
static void reloadRewardVideo(FBRewardedVideoAd *rewardedAd) {
    if (rewardedAd.isAdValid)
        return;
    auto idx = [GADRewardVideoArray indexOfObject:rewardedAd];
    if (--RewardRetryCNT[idx] <= 0)
    {
        return;
    }

    [rewardedAd loadAd];
}

void reloadMutliRewardVideoSync(bool init)
{
    if (init)
    {
        _rewardIdx = 0;
    }
    if (_rewardIdx >= GADRewardVideoArray.count)
    {
        return;
    }
    
    RewardRetryCNT[_rewardIdx] =  DefaultRetryCNT;
    FBRewardedVideoAd *t_rewardedAd = [GADRewardVideoArray objectAtIndex:_rewardIdx++];
    reloadRewardVideo(t_rewardedAd);
}

void recreateRewardVideo(FBRewardedVideoAd *rewardedAd)
{
    NSUInteger idx = [GADRewardVideoArray indexOfObject:rewardedAd];
        retryCNT[idx] =  DefaultRetryCNT;
    FBRewardedVideoAd *newrewardAd = [[FBRewardedVideoAd alloc] initWithPlacementID:[videoArray objectAtIndex:idx]];
    newrewardAd.delegate = s_fbObserver;
    [rewardedAd release];
    [GADRewardVideoArray replaceObjectAtIndex:idx withObject:newrewardAd];
}
//
//static void reloadMutliRewardVideo(FBRewardedVideoAd *rewardedAd) {
//    for (int i = 0; i<GADRewardVideoArray.count;i++) {
//        RewardRetryCNT[i] =  DefaultRetryCNT;
//        FBRewardedVideoAd *t_rewardedAd = [GADRewardVideoArray objectAtIndex:i];
//        if (rewardedAd != nullptr && rewardedAd == t_rewardedAd) {
//            FBRewardedVideoAd *newrewardAd = [[FBRewardedVideoAd alloc] initWithPlacementID:[videoArray objectAtIndex:i]];
//            newrewardAd.delegate = [[FBAudienceNetworkObserver alloc] init];
//            t_rewardedAd = newrewardAd;
//
//            [GADRewardVideoArray replaceObjectAtIndex:i withObject:newrewardAd];
//        }
//        if (!t_rewardedAd.isAdValid) {
//            reloadRewardVideo(t_rewardedAd);
//        }
//    }
//}
