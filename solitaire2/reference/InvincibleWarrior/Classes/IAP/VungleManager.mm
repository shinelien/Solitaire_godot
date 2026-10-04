#include "VungleManager.h"
// #import <VungleSDK/VungleSDK.h>
//#import "RootViewController.h"
//#include "DataManager.h"
//#include "SceneManager.h"
//
//static RootViewController* viewController;
//
////static NSString *const kVungleAppID = @"59f850433ee9607158007763";
////static NSString *const kVunglePlacementID01 = @"DEFAULT86678"; // auto cache placement
//static NSString *const kVungleAppID = @"5944bec9073309813500015c";
//static NSString *const kVunglePlacementID01 = @"74333-3054275"; // auto cache placement
//static int ShowCount = 0;
//
//bool VungleManager::isAdPlayable = false;
//bool VungleManager::isAdPlaying = false;
//
//@interface VungleTransactionObserver : NSObject<VungleSDKDelegate>
//
//@end
//
//@implementation VungleTransactionObserver
//
//- (void)vungleAdPlayabilityUpdate:(BOOL)isAdPlayable placementID:(nullable NSString *)placementID
//{
//    if ([placementID isEqualToString:kVunglePlacementID01]) {
//        VungleManager::isAdPlayable = isAdPlayable;
//        if (isAdPlayable)
//            SCENE_M->refushGift();
//    }
//}
//
//- (void)vungleWillShowAdForPlacementID:(nullable NSString *)placementID
//{
//    VungleManager::isAdPlaying = true;
//}
//
//- (void)vungleWillCloseAdWithViewInfo:(nonnull VungleViewInfo *)info placementID:(nonnull NSString *)placementID
//{
//    VungleManager::isAdPlaying = false;
//    if ([info.completedView boolValue] == YES)
//    {
//        //获得金币
//        DATA_M->lingqujinbi(0);
//        DATA_M->playLingQUAction();
//    }
//}
//
//- (void)vungleDidCloseAdWithViewInfo:(VungleViewInfo *)info placementID:(NSString *)placementID
//{
//    VungleManager::createVideoAds();
//}
//
//- (void)vungleSDKDidInitialize
//{
//    
//}
//
//- (void)vungleSDKFailedToInitializeWithError:(NSError *)error
//{
//    
//}
//
//@end
//
//void VungleManager::createVideoAds()
//{
//    NSError* error;
//    [[VungleSDK sharedSDK] loadPlacementWithID:kVunglePlacementID01 error:&error];
//}
//
//void VungleManager::showVideoAds()
//{
//    VungleManager::isAdPlayable = false;
//    VungleManager::isAdPlaying = true;
//    
//    VungleSDK* sdk = [VungleSDK sharedSDK];
//    NSError *error;
//    [sdk playAd:viewController options:nil placementID:kVunglePlacementID01 error:&error];
//    if (error) {
//        VungleManager::isAdPlaying = false;
//        NSLog(@"Error encountered playing ad: %@", error);
//    }
//}
//
//void VungleManager::initAdsManager(void* _viewController)
//{
//    setRootViewController(_viewController);
//    
//    NSError* error;
//    NSArray* placementIDsArray = @[kVunglePlacementID01];
//    VungleSDK* sdk = [VungleSDK sharedSDK];
//    [sdk startWithAppId:kVungleAppID placements:placementIDsArray error:&error];
//    
//    VungleTransactionObserver *delegate = [[VungleTransactionObserver alloc] init];
//    [[VungleSDK sharedSDK] setDelegate:delegate];
//}
//
//void VungleManager::setRootViewController(void* vcontroller)
//{
//    viewController = (RootViewController*)vcontroller;
//}
