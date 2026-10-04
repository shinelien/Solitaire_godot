//
//  AdMobManager.cpp
//  AdsWF
//
//  Created by Cyutao on 2019/7/30.
//  Copyright © 2019 Cyutao. All rights reserved.
//

#import <GoogleMobileAds/GoogleMobileAds.h>

#include "AdMobManager.h"
#import "WFManager.h"
#include <vector>
#import <string>
#include "AdsManager.h"

#define DefaultRetryCNT 3 // 错误后重试次数

bool AdMobManager::admobBannerRefresh = false;
float AdMobManager::bannerHeight = 70.f;
bool AdMobManager::bannerVisible = false;
bool AdMobManager::bannerInit = false;
bool AdMobManager::waitWinAction = false;
static int _bannerIdx=0, _interIdx=0, _rewardIdx=0;

static NSArray *TestDevices = @[ kGADSimulatorID, [[[UIDevice currentDevice] identifierForVendor] UUIDString], @"b6d87ccd44e9a9e7455595f525c6c5a8", @"d478470a432e668d35e9abc6e78f17d3"];

static NSString *const kAdmobAppID = @"ca-app-pub-4064979991272731~6179494805";
static NSArray *bannerArray = [NSArray arrayWithObjects:@"ca-app-pub-4064979991272731/7072740937", @"ca-app-pub-4064979991272731/3013242270", @"ca-app-pub-4064979991272731/6508390888", nil];
static NSArray *interArray = [NSArray arrayWithObjects:@"ca-app-pub-4064979991272731/1853802338", @"ca-app-pub-4064979991272731/7483804476", @"ca-app-pub-4064979991272731/9839053811", nil];
static NSArray *videoArray = [NSArray arrayWithObjects:@"ca-app-pub-4064979991272731/6651193209", @"ca-app-pub-4064979991272731/3422394637", @"ca-app-pub-4064979991272731/4571824771", nil];
static NSArray *nativeArray = [NSArray arrayWithObjects:@"ca-app-pub-4064979991272731/7746300339", @"ca-app-pub-4064979991272731/4353850232", @"ca-app-pub-4064979991272731/1536115209", @"ca-app-pub-4064979991272731/8484666932", nil];

static GADInterstitial * interstitial = nil; //插屏
static GADBannerView * bannerView = nil;//底条
static GADRewardedAd * rewardVideo = nil;//视频

static NSMutableArray *GADBannerArray = [[NSMutableArray alloc] init];      // banner数组
static std::vector<int> BannerRetryCNT; // 重试次数
static NSMutableArray *interstitialArray = [[NSMutableArray alloc] init];   // 插屏数组
static std::vector<int> retryCNT;   // 重试次数
static NSMutableArray *GADRewardVideoArray = [[NSMutableArray alloc] init];   // 激励视频数组
static std::vector<int> RewardRetryCNT; // 重试次数

// banner
static void reloadBanner(GADBannerView *t_bannerView);
static void reloadMutilBanner(GADBannerView *t_bannerView = nullptr);
static void reloadMutilBannerSync(bool init);
static void showHighestBanner(GADBannerView *t_bannerView = nullptr);
// interstitial
static void reloadInterstitial(GADInterstitial *t_interstitial);
static void reloadMutliInterstitialSync(bool init);
static void recreateInterstitial(GADInterstitial *t_interstitial);
static void reloadMutliInterstitial(GADInterstitial *t_interstitial = nullptr);
// rewardvideo
static void reloadRewardVideo(GADRewardedAd *rewardedAd);
static void reloadMutliRewardVideoSync(bool init);
static void recreateRewardVideo(GADRewardedAd *t_interstitial);
static void reloadMutliRewardVideo(GADRewardedAd *rewardedAd = nullptr);


#pragma mark banner回调
@interface bannerADSObserver : NSObject<GADBannerViewDelegate>
@end

@implementation bannerADSObserver
/// Tells the delegate an ad request loaded an ad.
- (void)adViewDidReceiveAd:(GADBannerView *)adView {
    NSLog(@"adViewDidReceiveAd");
    showHighestBanner(adView);
}

/// Tells the delegate an ad request failed.
- (void)adView:(GADBannerView *)adView
didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"adView:didFailToReceiveAdWithError: %@", [error localizedDescription]);
//    adView.hidden = YES;
//    if (error.code != kGADErrorNoFill) // 如果没有填充
//    reloadBanner(adView);
    reloadMutilBannerSync(false);
}
@end

#pragma mark intersititial
@interface interstitialDelegate : NSObject<GADInterstitialDelegate>
@end

@implementation interstitialDelegate
/// Tells the delegate an ad request succeeded.
- (void)interstitialDidReceiveAd:(GADInterstitial *)ad {
    NSLog(@"interstitialDidReceiveAd");
}

/// Tells the delegate an ad request failed.
- (void)interstitial:(GADInterstitial *)ad
didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"interstitial:didFailToReceiveAdWithError: %@", [error localizedDescription]);
//    AdsManager::createInterstitial();
//    reloadInterstitial(ad);
    reloadMutliInterstitialSync(false);
}

/// Tells the delegate that an interstitial will be presented.
- (void)interstitialWillPresentScreen:(GADInterstitial *)ad {
    NSLog(@"interstitialWillPresentScreen");
}

/// Tells the delegate the interstitial is to be animated off the screen.
- (void)interstitialWillDismissScreen:(GADInterstitial *)ad {
    NSLog(@"interstitialWillDismissScreen");
    DATA_M->setPlayAds(false);
}

/// Tells the delegate the interstitial had been animated off the screen.
- (void)interstitialDidDismissScreen:(GADInterstitial *)ad {
    NSLog(@"interstitialDidDismissScreen");
//    AdsManager::createInterstitial(true);
//    reloadMutliInterstitial(ad);
    recreateInterstitial(ad);     // 加载过了重新创建
    reloadMutliInterstitialSync(true);
    if (AdsManager::waitWinAction)
    {
        AdsManager::waitWinAction = false;
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_showwin");
    }
}

/// Tells the delegate that a user click will open another app
/// (such as the App Store), backgrounding the current app.
- (void)interstitialWillLeaveApplication:(GADInterstitial *)ad {
    NSLog(@"interstitialWillLeaveApplication");
}
@end

#pragma mark rewardvideo
@interface rewardVideoDelegate : NSObject<GADRewardedAdDelegate>
@end

@implementation rewardVideoDelegate
/// Tells the delegate that the user earned a reward.
- (void)rewardedAd:(GADRewardedAd *)rewardedAd userDidEarnReward:(GADAdReward *)reward {
    // TODO: Reward the user.
    NSLog(@"rewardedAd:userDidEarnReward:");
    DATA_M->lingqujinbi(0);
}

/// Tells the delegate that the rewarded ad was presented.
- (void)rewardedAdDidPresent:(GADRewardedAd *)rewardedAd {
    NSLog(@"rewardedAdDidPresent:");
}

/// Tells the delegate that the rewarded ad failed to present.
- (void)rewardedAd:(GADRewardedAd *)rewardedAd didFailToPresentWithError:(NSError *)error {
    NSLog(@"rewardedAd:didFailToPresentWithError");
}

/// Tells the delegate that the rewarded ad was dismissed.
- (void)rewardedAdDidDismiss:(GADRewardedAd *)rewardedAd {
    NSLog(@"rewardedAdDidDismiss:");
    DATA_M->playLingQUAction();
    //    reloadMutliRewardVideo(rewardedAd);
    recreateRewardVideo(rewardedAd);
    reloadMutliInterstitialSync(true);
}
@end

bool AdMobManager::init()
{
    setSupport(AdType::Banner);
    setSupport(AdType::Intertitial);
    setSupport(AdType::RewardVideo);
    // 初始话广告
    createMutilBanner();
    createMutliInterstitial();
    createMutliRewardVideo();
    return true;
}

static bannerADSObserver* bannerDelegate = [[bannerADSObserver alloc] init];
void AdMobManager::createMutilBanner() {
    UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
    for (NSString *interID in bannerArray) {
        GADBannerView *t_bannerView = [[GADBannerView alloc] initWithAdSize:GADAdSizeFullWidthPortraitWithHeight(GAD_SIZE_320x50.height) origin:CGPointMake(/*(viewController.view.frame.size.width-kGADAdSizeBanner.size.width)/2*/0 , viewController.view.frame.size.height-AdMobManager::bannerHeight)];
        t_bannerView.delegate = bannerDelegate;
        t_bannerView.rootViewController = viewController;
        t_bannerView.adUnitID = interID;

        [GADBannerArray addObject:t_bannerView];
        BannerRetryCNT.push_back(DefaultRetryCNT);
    }
    reloadMutilBannerSync(true);
}

//void reloadMutilBanner(GADBannerView *t_bannerView)
//{
//    for (int i=0; i<GADBannerArray.count; i++) {
//        BannerRetryCNT[i] = DefaultRetryCNT;
//        GADBannerView *t_bannerView = [GADBannerArray objectAtIndex:i];
//        if (t_bannerView != bannerView)
//            reloadBanner(t_bannerView);
//    }
//}

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
    GADBannerView *t_bannerView = [GADBannerArray objectAtIndex:_bannerIdx++];
    reloadBanner(t_bannerView);
}


void reloadBanner(GADBannerView *t_bannerView)
{
    auto idx = [GADBannerArray indexOfObject:t_bannerView];
    if (--BannerRetryCNT[idx] <= 0)
    {
        return;
    }

    GADRequest *request = [GADRequest request];
    if(WFManager::isTest)
    {
        request.testDevices = TestDevices;
    }
    t_bannerView.hidden = YES;
    [t_bannerView loadRequest:request];
}

void showHighestBanner(GADBannerView *t_bannerView)
{
    auto idx = [GADBannerArray indexOfObject:t_bannerView];
    NSString* key = [bannerArray objectAtIndex:idx];    // 获取 id
    if (WFManager::getInstance()->showHighestBanner([key UTF8String], WFManager::Type::Admob, nullptr)) {
        if (bannerView != nil && bannerView.superview != nil) {
            bannerView.hidden = YES;
            [bannerView removeFromSuperview];
        }
        bannerView = t_bannerView;
        UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
        [viewController.view addSubview:bannerView];
        bannerView.hidden = NO; //!AdsManager::bannerVisible;
    }
    else if (bannerView == t_bannerView && bannerView.hidden == NO) { // 刷新？？？
        if (AdMobManager::admobBannerRefresh) {
            reloadMutilBannerSync(true);
            AdMobManager::admobBannerRefresh = false;
        }
        else {
            AdMobManager::admobBannerRefresh = true;
        }
    }
}

// 插屏的创建和重试
static interstitialDelegate* s_interstitialDelegate = [[interstitialDelegate alloc] init];
void AdMobManager::createMutliInterstitial() {
    for (NSString *interID in interArray) {
        GADInterstitial *t_interstitial = [[GADInterstitial alloc] initWithAdUnitID:interID];
        t_interstitial.delegate = s_interstitialDelegate;
        [interstitialArray addObject:t_interstitial];
        retryCNT.push_back(DefaultRetryCNT);
    }
    reloadMutliInterstitialSync(true);
}

static void reloadMutliInterstitial(GADInterstitial *adinterstitial)
{
    for (int i = 0; i<interstitialArray.count;i++) {
        retryCNT[i] =  DefaultRetryCNT;
        GADInterstitial *t_interstitial = [interstitialArray objectAtIndex:i];
        if (adinterstitial != nullptr && adinterstitial == t_interstitial) {
            GADInterstitial *newinterstitial = [[GADInterstitial alloc] initWithAdUnitID:[interArray objectAtIndex:i]];
            newinterstitial.delegate = s_interstitialDelegate;
//            [t_interstitial.delegate release];
            [t_interstitial release];
            t_interstitial = newinterstitial;
            [interstitialArray replaceObjectAtIndex:i withObject:newinterstitial];
        }
        if (!t_interstitial.isReady) {
            reloadInterstitial(t_interstitial);
        }
    }
}

static void recreateInterstitial(GADInterstitial *t_interstitial)
{
    NSUInteger idx = [interstitialArray indexOfObject:t_interstitial];
    if (idx>=0 && idx<interArray.count)
    {
        retryCNT[idx] =  DefaultRetryCNT;
        GADInterstitial *newinterstitial = [[GADInterstitial alloc] initWithAdUnitID:[interArray objectAtIndex:idx]];
        newinterstitial.delegate = s_interstitialDelegate;
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
    GADInterstitial *t_interstitial = [interstitialArray objectAtIndex:_interIdx++];
    reloadInterstitial(t_interstitial);
}

static void reloadInterstitial(GADInterstitial *t_interstitial)
{
    if ([t_interstitial isReady])
        return;
    // 失败请求不会超过DefaultRetryCNT次
    auto idx = [interstitialArray indexOfObject:t_interstitial];
    if (--retryCNT[idx] <= 0)
        return;

    GADRequest *request = [GADRequest request];
    if(WFManager::isTest)
    {
        request.testDevices = TestDevices;
    }

    [t_interstitial loadRequest:request];
}

bool AdMobManager::showInterstitial(const std::string &_id)
{
    if (_id.empty()) {
        for (GADInterstitial *t_interstitial in interstitialArray) {
            if (t_interstitial.isReady) {
                UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
                [t_interstitial presentFromRootViewController:viewController];
                return true;
            }
        }
    }
    else {
        auto idx = [interArray indexOfObject:[NSString stringWithUTF8String:_id.c_str()]];
        GADInterstitial* interstitial = [interstitialArray objectAtIndex:idx];
        UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
        [interstitial presentFromRootViewController:viewController];
        return true;
    }
    NSLog(@"Ad wasn't ready");
//    reloadMutliInterstitial();
    reloadMutliInterstitialSync(true);
    return false;
}

void AdMobManager::createMutliRewardVideo() {
    for (NSString *adUnitId in videoArray) {
        GADRewardedAd *rewardedAd = [[GADRewardedAd alloc] initWithAdUnitID:adUnitId];

        [GADRewardVideoArray addObject:rewardedAd];
        RewardRetryCNT.push_back(DefaultRetryCNT);
    }
//    reloadMutliRewardVideo();
    reloadMutliRewardVideoSync(true);
}

static rewardVideoDelegate* s_rewardVideoDelegate = [[rewardVideoDelegate alloc] init];
bool AdMobManager::showRewardVideo(const std::string &_id) {
    if (_id.empty()) {
        for (GADRewardedAd *t_rewardedAd in GADRewardVideoArray) {
            if (t_rewardedAd.isReady) {
                UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
                [t_rewardedAd presentFromRootViewController:viewController delegate:s_rewardVideoDelegate];
                return true;
            }
        }
    }
    else {
        auto idx = [videoArray indexOfObject:[NSString stringWithUTF8String:_id.c_str()]];
        GADRewardedAd* rewardedAd = [GADRewardVideoArray objectAtIndex:idx];
        UIViewController* viewController = (UIViewController*)WFManager::getViewControl();
        [rewardedAd presentFromRootViewController:viewController delegate:s_rewardVideoDelegate];
        return true;
    }
    NSLog(@"Ad wasn't ready");
//    reloadMutliRewardVideo();
    reloadMutliRewardVideoSync(true);
    return false;
}

bool AdMobManager::showAds(AdInterface::AdType adType, const std::string &_id) {
    switch (adType) {
        case AdType ::Banner:
            break;
        case AdType::Intertitial:
            return showInterstitial(_id);
        case AdType::RewardVideo:
            showRewardVideo(_id);
            break;
    }
    return false;
}

void AdMobManager::hideAds(AdInterface::AdType adType, const std::string &_id) {
    switch (adType) {
        case AdType::Banner:
            auto idx = [bannerArray indexOfObject:[NSString stringWithUTF8String:_id.c_str()]];
            GADBannerView* bannerView1 = [GADBannerArray objectAtIndex:idx];    // 获取 id
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

std::vector<std::string> AdMobManager::getReadyAds(AdInterface::AdType adType) {
    std::vector<std::string> readyAdsVec;
    if (adType == AdInterface::AdType::Intertitial) {
        for (int i = 0; i<interstitialArray.count;i++) {
            GADInterstitial *t_interstitial = [interstitialArray objectAtIndex:i];
            if (t_interstitial.isReady) {
                NSString* key = [interArray objectAtIndex:i];
                readyAdsVec.push_back([key UTF8String]);
            }
        }
    }
    else if (adType == AdInterface::AdType::RewardVideo) {
        for (int i = 0; i<GADRewardVideoArray.count;i++) {
            GADRewardedAd *t_interstitial = [GADRewardVideoArray objectAtIndex:i];
            if (t_interstitial.isReady) {
                NSString* key = [videoArray objectAtIndex:i];
                readyAdsVec.push_back([key UTF8String]);
            }
        }
    }
    return readyAdsVec;
}

void AdMobManager::reloadAds(AdInterface::AdType adType) {
    AdInterface::reloadAds(adType);
    switch (adType) {
        case AdType ::Banner:
            break;
        case AdType::Intertitial:
            reloadMutliInterstitialSync(true);
        case AdType::RewardVideo:
            reloadMutliRewardVideoSync(true);
            break;
    }
}

int AdMobManager::getDefaultPrice(AdInterface::AdType adType, const std::string &_id) {
    switch (adType) {
        case AdType::Banner:
            int idx = [bannerArray indexOfObject:[NSString stringWithUTF8String:_id.c_str()]];
            return idx+1;
    }
    return AdInterface::getDefaultPrice(adType);
}

bool AdMobManager::isReady(AdInterface::AdType adType) {
    switch (adType) {
        case AdType::Intertitial:
            for (GADInterstitial *t_interstitial in interstitialArray) {
                if (t_interstitial.isReady) {
                    return true;
                }
            }
            break;
        case AdType::RewardVideo:
            for (GADRewardedAd *t_rewardedAd in GADRewardVideoArray) {
                if (t_rewardedAd.isReady) {
                    return true;
                }
            }
            break;
    }
    reloadAds(adType);
    return false;
}

//void reloadMutliRewardVideo(GADRewardedAd *rewardedAd) {
//    for (int i = 0; i<GADRewardVideoArray.count;i++) {
//        RewardRetryCNT[i] =  DefaultRetryCNT;
//        GADRewardedAd *t_rewardedAd = [GADRewardVideoArray objectAtIndex:i];
//        if (rewardedAd != nullptr && rewardedAd == t_rewardedAd) {
//            GADRewardedAd *newrewardAd = [[GADRewardedAd alloc] initWithAdUnitID:[videoArray objectAtIndex:i]];
//            t_rewardedAd = newrewardAd;
//            [GADRewardVideoArray replaceObjectAtIndex:i withObject:newrewardAd];
//        }
//        if (!t_rewardedAd.isReady) {
//            reloadRewardVideo(t_rewardedAd);
//        }
//    }
//}

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
    GADRewardedAd *t_rewardedAd = [GADRewardVideoArray objectAtIndex:_rewardIdx++];
    reloadRewardVideo(t_rewardedAd);
}

void recreateRewardVideo(GADRewardedAd *rewardedAd)
{
    NSUInteger idx = [GADRewardVideoArray indexOfObject:rewardedAd];
    retryCNT[idx] =  DefaultRetryCNT;
    GADRewardedAd *newrewardAd = [[GADRewardedAd alloc] initWithAdUnitID:[videoArray objectAtIndex:idx]];
    [rewardedAd release];
    [GADRewardVideoArray replaceObjectAtIndex:idx withObject:newrewardAd];
}

void reloadRewardVideo(GADRewardedAd *rewardedAd) {
    if ([rewardedAd isReady])
        return;
    auto idx = [GADRewardVideoArray indexOfObject:rewardedAd];
    if (--RewardRetryCNT[idx] <= 0)
    {
        return;
    }

    DFPRequest *request = [DFPRequest request];
    if(WFManager::isTest)
    {
        request.testDevices = TestDevices;
    }

    [rewardedAd loadRequest:request completionHandler:^(GADRequestError * _Nullable error) {
        if (error) {
            // Handle ad failed to load case.
//            reloadRewardVideo(rewardedAd);
            reloadMutliRewardVideoSync(false);
        } else {
            // Ad successfully loaded.
        }
    }];
}
