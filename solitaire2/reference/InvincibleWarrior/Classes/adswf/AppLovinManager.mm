//
// Created by Cyutao on 2019-07-31.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#include "AppLovinManager.h"
#include <vector>
#import <AppLovinSDK/AppLovinSDK.h>

static ALAd *alad = nil;
#pragma mark - Ad Load Delegate
@interface ALObserver : NSObject<ALAdLoadDelegate, ALAdDisplayDelegate, ALAdVideoPlaybackDelegate, ALAdRewardDelegate>
@end

@implementation ALObserver
- (void)adService:(nonnull ALAdService *)adService didLoadAd:(nonnull ALAd *)ad
{
    // We now have an interstitial ad we can show!
    alad = ad;
    SCENE_M->refushGift();
}

- (void)adService:(nonnull ALAdService *)adService didFailToLoadAdWithError:(int)code
{
    // Look at ALErrorCodes.h for the list of error codes.
}
#pragma mark - ALAdDisplayDelegate Methods

- (void)ad:(ALAd *)ad wasClickedIn:(UIView *)view {}
- (void)ad:(ALAd *)ad wasDisplayedIn:(UIView *)view {
    
}

- (void)ad:(ALAd *)ad wasHiddenIn:(UIView *)view
{
    // The user has closed the ad. We must preload the next rewarded video.
    AppLovinManager::createInterstitialAd();
    AppLovinManager::createVideoAds();
}
// reward
- (void)rewardValidationRequestForAd:(ALAd *)ad didSucceedWithResponse:(NSDictionary *)response
{

}

- (void)rewardValidationRequestForAd:(ALAd *)ad didExceedQuotaWithResponse:(NSDictionary *)response
{

}

- (void)rewardValidationRequestForAd:(ALAd *)ad wasRejectedWithResponse:(NSDictionary *)response
{

}

- (void)rewardValidationRequestForAd:(ALAd *)ad didFailWithError:(NSInteger)responseCode
{

}
@end

bool AppLovinManager::init() {
    setSupport(AdType::Intertitial);
    setSupport(AdType::RewardVideo);

    [ALSdk initializeSdk];
    return true;
}

static ALObserver *delegate = [[ALObserver alloc] init];
void AppLovinManager::createInterstitialAd() {
    alad = nil;
    [[ALSdk shared].adService loadNextAd: [ALAdSize sizeInterstitial] andNotify: delegate];
}

void AppLovinManager::showInterstitialAd() {
    if (alad) {
        // Optional: Assign delegates
        [ALInterstitialAd shared].adDisplayDelegate = delegate;
        [ALInterstitialAd shared].adVideoPlaybackDelegate = delegate;

        [[ALInterstitialAd shared] showAd:alad];
    }
}

void AppLovinManager::createVideoAds() {
    // Preload call using a load delegate
    [ALIncentivizedInterstitialAd shared].adDisplayDelegate = delegate;
    [ALIncentivizedInterstitialAd preloadAndNotify: delegate];
}

void AppLovinManager::showVideoAds() {
    if ( [ALIncentivizedInterstitialAd isReadyForDisplay] )
    {
        // If you want to use a reward delegate, set it here. For this example, we will use nil.
        [ALIncentivizedInterstitialAd showAndNotify: delegate];
    }
    else
    {
        // No rewarded video is ready. Perform failover logic, etc.
        [ALIncentivizedInterstitialAd preloadAndNotify: delegate];
    }
}

bool AppLovinManager::showAds(AdInterface::AdType adType, const std::string &id) {
    return false;
}

std::vector<std::string> AppLovinManager::getReadyAds(AdInterface::AdType adType) {
    std::vector<std::string> readyAdsVec;
    if ( [ALIncentivizedInterstitialAd isReadyForDisplay] ) {
        readyAdsVec.push_back("al_reward_video");
    }
    else if (alad != nil) {
        readyAdsVec.push_back("al_interstitial");
    }
    return readyAdsVec;
}

bool AppLovinManager::isReady(AdInterface::AdType adType) {
    return false;
}
