#include "UnityADSManager.h"
#import <UnityAds/UnityAds.h>
#import "RootViewController.h"
#include "DataManager.h"
#include "SceneManager.h"
#include "AdsManager.h"
#include "EventObserver.h"

static RootViewController* viewController;

//static NSString *const kVungleAppID = @"59f850433ee9607158007763";
//static NSString *const kVunglePlacementID01 = @"DEFAULT86678"; // auto cache placement
static NSString *const kVungleAppID = @"2902063";
static NSString *const kVunglePlacementID01 = @"rewardedVideo"; // auto cache placement
static NSString *const kVunglePlacementID02 = @"video"; // auto cache placement
static int ShowCount = 0;

bool UnityADSManager::isAdPlayable = false;
bool UnityADSManager::isAdPlaying = false;
UMONPlacementContent* rewardedVideo = nil;
UMONPlacementContent* interstitialVideo = nil;

@interface UnityADSObserver : NSObject<UnityMonetizationDelegate, UMONShowAdDelegate>

@end

@implementation UnityADSObserver

#pragma mark: UnityMonetizationDelegate

-(void) placementContentReady: (NSString *) placementId placementContent: (UMONPlacementContent *) placementContent {
    // Check and set the available PlacementContent:
//    if ([placementId isEqualToString: kVunglePlacementID01]) {
//        rewardedVideo = placementContent;
//        [rewardedVideo retain];
//    }
//    else if ([placementId isEqualToString: kVunglePlacementID02]) {
//        interstitialVideo = placementContent;
//        [interstitialVideo retain];
//    }
}

-(void) placementContentStateDidChange: (NSString *) placementId placementContent: (UMONPlacementContent *) decision previousState: (UnityMonetizationPlacementContentState) previousState newState: (UnityMonetizationPlacementContentState) newState {
    if ([placementId isEqualToString:kVunglePlacementID01]) {
        if (newState != kPlacementContentStateReady) {
            // Disable showing ads because content isn’t ready anymore
            UnityADSManager::isAdPlayable = false;
        }
        else {
            UnityADSManager::isAdPlayable = true;
            SCENE_M->refushGift();
        }
    }
    else if ([placementId isEqualToString:kVunglePlacementID02]) {
        AdsManager::showInterstitialAtLoaded();
    }
}

-(void) unityServicesDidError: (UnityServicesError) error withMessage: (NSString *) message {
    NSLog (@"UnityMonetization ERROR: %ld - %@", (long) error, message);
}

// Implement the delegate for handling the ad’s finishState
#pragma mark: UMONShowAdDelegate

-(void) unityAdsDidStart: (NSString *) placementId {
    // (Optional) Log or perform some action when the ad starts
    if ([placementId isEqualToString:kVunglePlacementID01])
        UnityADSManager::isAdPlaying = true;
    NSLog (@"Unity ad started for: %@", placementId);
}

-(void) unityAdsDidFinish: (NSString *) placementId withFinishState: (UnityAdsFinishState) finishState {
    // If the ad played in its entirety, and the Placement is rewarded, perform reward logic:
    if ([placementId isEqualToString:kVunglePlacementID02]) {       // 插屏
        if (AdsManager::waitWinAction)
        {
            AdsManager::waitWinAction = false;
            EVENT_M->sendEvent("msg_game_showwin");
            //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_showwin");
        }
    }
    else if (finishState == kUnityAdsFinishStateCompleted
        && [placementId isEqualToString:kVunglePlacementID01]) {
        // Reward player for watching the entire video
        //获得金币
        DATA_M->lingqujinbi(0);
        DATA_M->playLingQUAction();
        UnityADSManager::isAdPlaying = false;
    }
}

@end
UnityADSObserver *delegate = nil;

void UnityADSManager::createVideoAds()
{
    
}

void UnityADSManager::showVideoAds()
{
    if ([UnityMonetization isReady:kVunglePlacementID01]) {
        [[UnityMonetization getPlacementContent:kVunglePlacementID01] show:viewController withDelegate:delegate];
    }
}

bool UnityADSManager::showInterstitialAds()
{
    if ([UnityMonetization isReady:kVunglePlacementID02]) {
        [[UnityMonetization getPlacementContent:kVunglePlacementID02] show:viewController withDelegate:delegate];
        return true;
    }
    else {
        NSLog(@"unity ads wasn't ready");
        return false;
    }
}

void UnityADSManager::initAdsManager(void* _viewController)
{
    setRootViewController(_viewController);
    
    delegate = [[UnityADSObserver alloc] init];
#if COCOS2D_DEBUG>0
    [UnityMonetization initialize:kVungleAppID delegate:delegate testMode:true];
#else
    [UnityMonetization initialize:kVungleAppID delegate:delegate testMode:false];
#endif
}

void UnityADSManager::setRootViewController(void* vcontroller)
{
    viewController = (RootViewController*)vcontroller;
}
