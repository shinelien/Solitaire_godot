//
// Created by Cyutao on 2019-07-31.
// Copyright (c) 2019 Cyutao. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import <UnityAds/UnityAds.h>
//#include "UnityManager.h"
//#include <vector>
//#import "WFManager.h"
//#include "AdsManager.h"
//
//static UIViewController* viewController;
//
//static NSString *const kVungleAppID = @"2902063";
//static NSString *const kVunglePlacementID01 = @"rewardedVideo"; // auto cache placement
//static NSString *const kVunglePlacementID02 = @"video"; // auto cache placement
//
//static UMONPlacementContent* rewardedVideo = nil;
//static UMONPlacementContent* interstitialVideo = nil;
//
//@interface UnityADSObserver : NSObject<UnityAdsDelegate>
//
//@end
//
//@implementation UnityADSObserver
//
//#pragma mark: UnityMonetizationDelegate
//
//-(void) placementContentReady: (NSString *) placementId placementContent: (UMONPlacementContent *) placementContent {
//    // Check and set the available PlacementContent:
////    if ([placementId isEqualToString: kVunglePlacementID01]) {
////        rewardedVideo = placementContent;
////        [rewardedVideo retain];
////    }
////    else if ([placementId isEqualToString: kVunglePlacementID02]) {
////        interstitialVideo = placementContent;
////        [interstitialVideo retain];
////    }
//}
//
//-(void) placementContentStateDidChange: (NSString *) placementId placementContent: (UMONPlacementContent *) decision previousState: (UnityMonetizationPlacementContentState) previousState newState: (UnityMonetizationPlacementContentState) newState {
//    if ([placementId isEqualToString:kVunglePlacementID01]) {
//        if (newState != kPlacementContentStateReady) {
//            // Disable showing ads because content isn’t ready anymore
//        }
//        else {
//            SCENE_M->refushGift();
//        }
//    }
//    else if ([placementId isEqualToString:kVunglePlacementID02]) {
////        AdsManager::showInterstitialAtLoaded();
//    }
//}
//
//-(void) unityServicesDidError: (UnityServicesError) error withMessage: (NSString *) message {
//    NSLog (@"UnityMonetization ERROR: %ld - %@", (long) error, message);
//}
//
//// Implement the delegate for handling the ad’s finishState
//#pragma mark: UMONShowAdDelegate
//
//-(void) unityAdsDidStart: (NSString *) placementId {
//    // (Optional) Log or perform some action when the ad starts
////    if ([placementId isEqualToString:kVunglePlacementID01])
////        UnityADSManager::isAdPlaying = true;
//    NSLog (@"Unity ad started for: %@", placementId);
//}
//
//-(void) unityAdsDidFinish: (NSString *) placementId withFinishState: (UnityAdsFinishState) finishState {
//    // If the ad played in its entirety, and the Placement is rewarded, perform reward logic:
//    if ([placementId isEqualToString:kVunglePlacementID02]) {       // 插屏
//        if (AdsManager::waitWinAction)
//        {
//            AdsManager::waitWinAction = false;
//            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_showwin");
//        }
//    }
//    else if (finishState == kUnityAdsFinishStateCompleted
//        && [placementId isEqualToString:kVunglePlacementID01]) {
//        // Reward player for watching the entire video
//        //获得金币
//        DATA_M->lingqujinbi(0);
//        DATA_M->playLingQUAction();
//    }
//}
//
//@end
//
//bool UnityManager::init() {
//    setSupport(AdType::Intertitial);
//    setSupport(AdType::RewardVideo);
//
//    viewController = (UIViewController *)WFManager::getViewControl();
//    createVideoAds();
//    return true;
//}
//
//static UnityADSObserver *delegate = [[UnityADSObserver alloc] init];
//void UnityManager::createVideoAds() {
//#if COCOS2D_DEBUG>0
//    [UnityAds initialize:kVungleAppID delegate:delegate testMode:true];
//#else
//    [UnityAds initialize:kVungleAppID delegate:delegate testMode:false];
//#endif
//}
//
//void UnityManager::showVideoAds() {
//    if ([UnityAds isReady:kVunglePlacementID01]) {
//        [UnityAds show:viewController placementId:kVunglePlacementID01];
////        [static_cast<UMONShowAdPlacementContent *>([UnityAds getPlacementContent:kVunglePlacementID01]) show:viewController withDelegate:delegate];
//    }
//    else {
//        NSLog(@"unity ads wasn't ready");
//    }
//}
//
//bool UnityManager::showInterstitialAds() {
//    if ([UnityAds isReady:kVunglePlacementID02]) {
//        [UnityAds show:viewController placementId:kVunglePlacementID02];
////        [static_cast<UMONShowAdPlacementContent *>([UnityAds getPlacementContent:kVunglePlacementID02]) show:viewController withDelegate:delegate];
//        return true;
//    }
//    else {
//        NSLog(@"unity ads wasn't ready");
//        return false;
//    }
//}
//
//bool UnityManager::showAds(AdInterface::AdType adType, const std::string &id) {
//    switch (adType) {
//        case AdType::Intertitial:
//            return showInterstitialAds();
//        case AdType::RewardVideo:
//            showVideoAds();
//            break;
//    }
//    return false;
//}
//
//std::vector<std::string> UnityManager::getReadyAds(AdInterface::AdType adType) {
//    std::vector<std::string> readyAdsVec;
//    if ([UnityAds isReady:kVunglePlacementID01]) {
//        readyAdsVec.push_back("unity_reward_video");
//    }
//    else if ([UnityAds isReady:kVunglePlacementID02]) {
//        readyAdsVec.push_back("unity_interstitial");
//    }
//    return readyAdsVec;
//}
//
//bool UnityManager::isReady(AdInterface::AdType adType) {
//    switch (adType) {
//        case AdType::Intertitial:
//            return [UnityAds isReady:kVunglePlacementID02];
//            break;
//        case AdType::RewardVideo:
//            return [UnityAds isReady:kVunglePlacementID01];
//            break;
//    }
//    return false;
//}
