#include "AdsManager.h"
#import "DataManager.h"
#import "RootViewController.h"
#import "platform/ios/CCEAGLView-ios.h"
#define US_IS 1
#if TARGET_IPHONE_SIMULATOR
#define US_AD_TRADPLUS 0
#else
#define US_AD_TRADPLUS 0
#endif

#if US_IS
#import "IronSource/IronSource.h"
#elif US_AD_TRADPLUS
#import <TradPlusAds/MsSDKUtils.h>
#import <TradPlusAds/MSLogging.h>
#import <TradPlusAds/MsBannerView.h>
#import <TradPlusAds/MsInterstitialAd.h>
#import <TradPlusAds/MsCommon.h>
#import <TradPlusAds/MsRewardedVideoAd.h>
#endif

#include "EventObserver.h"
#if COCOS2D_DEBUG > 0
bool AdsManager::isTest = true;
#else
bool AdsManager::isTest = false;
#endif
bool AdsManager::nativeInit = false;
bool AdsManager::bannerVisible = true;
bool AdsManager::waitWinAction = false;
bool AdsManager::bannerInit = false;
bool AdsManager::admobBannerEnabled = false;
bool AdsManager::admobBannerRefresh = false;
bool AdsManager::AppLoadShowADS = true;
static RootViewController* viewController;
float AdsManager::bannerHeight = 0;
static int is_banner_retry_cnt = 3;
const float DefaultBannerHeight = 50;      // iphone 高度 60
#if US_IS
const float DefaultPadBannerHeight = 90;  // ipad 高度 70
#elif US_AD_TRADPLUS
const float DefaultPadBannerHeight = 50;  // ipad 高度 50
/**
纸牌【视频】0E8D4A0ED45E2E316718DC45EAC79DBC
纸牌【插屏】D908437A42591DEB29240362E216483F
纸牌【banner】E6EFB9467609916806EBD6AA96E52EC7*/
//测试id
//NSString* msBannerID = @"6008C47DF1201CC875F2044E88FCD287"; // banner
//NSString* msInterstitalID = @"063265866B93A4C6F93D1DDF7BF7329B"; // 插屏
//NSString* msRewardVideoID = @"160AFCDF01DDA48CCE0DBDBE69C8C669"; // 视频
NSString* msBannerID = @"E6EFB9467609916806EBD6AA96E52EC7"; // banner
NSString* msInterstitalID = @"D908437A42591DEB29240362E216483F"; // 插屏
NSString* msRewardVideoID = @"0E8D4A0ED45E2E316718DC45EAC79DBC"; // 视频
#else
const float DefaultPadBannerHeight = 50;  // ipad 高度 50
#endif
#if US_IS
ISBannerView *is_bannerView;
#pragma mark - ISBannerDelegate
@interface CustomISBannerDelegate : NSObject<ISBannerDelegate>
@end

@implementation CustomISBannerDelegate
/** Called after a banner ad has been successfully loaded
 */
- (void)bannerDidLoad:(ISBannerView *)bannerView {
    dispatch_async(dispatch_get_main_queue(), ^{
        is_bannerView = bannerView;
        
        CGFloat y = viewController.view.frame.size.height - (is_bannerView.frame.size.height / 2);
        if (@available(ios 11.0, *)) {
            y -= viewController.view.safeAreaInsets.bottom*3/4;
        }
        is_bannerView.center = CGPointMake(viewController.view.frame.size.width / 2, y);
       
        [viewController.view addSubview:is_bannerView];
    
//        AdsManager::bannerHeight = y;
        AdsManager::bannerInit = true;
        AdsManager::setBannerVisible(AdsManager::bannerVisible);
    });
}
/**
 Called after a banner has attempted to load an ad but failed.
 
 @param error The reason for the error
 */
- (void)bannerDidFailToLoadWithError:(NSError *)error {}
/**
 Called after a banner has been clicked.
 */
- (void)didClickBanner {}
/**
 Called when a banner is about to present a full screen content.
 */
- (void)bannerWillPresentScreen {}
/**
 Called after a full screen content has been dismissed.
 */
- (void)bannerDidDismissScreen {}
/**
 Called when a user would be taken out of the application context.
 */
- (void)bannerWillLeaveApplication {}
@end

#pragma mark - ISInterstitialDelegate
@interface CustomISInterstitialDelegate : NSObject<ISInterstitialDelegate>
@end

@implementation CustomISInterstitialDelegate
//Invoked when Interstitial Ad is ready to be shown after load function was //called.
-(void)interstitialDidLoad {
    //EVENT_M->sendEvent("msg_interstitialDidLoad");
    DATA_M->setIsHaveInterstitials(true);//填充完毕 可以显示了
}
//Called each time the Interstitial window has opened successfully.
-(void)interstitialDidShow {

}
// Called if showing the Interstitial for the user has failed.
//You can learn about the reason by examining the ‘error’ value
-(void)interstitialDidFailToShowWithError:(NSError *)error {
    CCLOG("interstitialDidFailToShowWithError:error");
    if (AdsManager::waitWinAction)
    {
        AdsManager::waitWinAction = false;
        EVENT_M->sendEvent("msg_game_showwin");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_showwin");
    }
}
//Called each time the end user has clicked on the Interstitial ad.
-(void)didClickInterstitial {

}
//Called each time the Interstitial window is about to close
-(void)interstitialDidClose {
    [IronSource loadInterstitial];
    if (AdsManager::waitWinAction)
    {
        AdsManager::waitWinAction = false;
        EVENT_M->sendEvent("msg_game_showwin");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_showwin");
    }
}
//Called each time the Interstitial window is about to open
-(void)interstitialDidOpen {

}
//Invoked when there is no Interstitial Ad available after calling load //function. @param error - will contain the failure code and description.
-(void)interstitialDidFailToLoadWithError:(NSError *)error {
    Director::getInstance()->getRunningScene()->scheduleOnce([](float){
        [IronSource loadInterstitial];
    }, 32, "schedule_interstitial_all_retry");
}
@end

#pragma mark - ISRewardedVideoDelegate
@interface CustomISRewardedVideoDelegate : NSObject<ISRewardedVideoDelegate>
@end

@implementation CustomISRewardedVideoDelegate
//Called after a rewarded video has changed its availability.
//@param available The new rewarded video availability. YES if available //and ready to be shown, NO otherwise.
-(void)rewardedVideoHasChangedAvailability:(BOOL)available {
     //Change the in-app 'Traffic Driver' state according to availability.
    SCENE_M->refushGift();
}
// Invoked when the user completed the video and should be rewarded.
// If using server-to-server callbacks you may ignore this events and wait *for the callback from the ironSource server.
//
// @param placementInfo An object that contains the placement's reward name and amount.
//
-(void)didReceiveRewardForPlacement:(ISPlacementInfo *)placementInfo {
    DATA_M->lingqujinbi(0);
}
//Called after a rewarded video has attempted to show but failed.
//@param error The reason for the error
-(void)rewardedVideoDidFailToShowWithError:(NSError *)error {
}
//Called after a rewarded video has been opened.
- (void)rewardedVideoDidOpen {
}
//Called after a rewarded video has been dismissed.
- (void)rewardedVideoDidClose {
    DATA_M->playLingQUAction();
}
//Invoked when the end user clicked on the RewardedVideo ad
- (void)didClickRewardedVideo:(ISPlacementInfo *)placementInfo{
}
//Note: the events DidStart & DidEnd below are not available for all supported rewarded video ad networks. Check which events are available per ad network you choose //to include in your build.
//We recommend only using events which register to ALL ad networks you //include in your build.
 //Called after a rewarded video has started playing.
- (void)rewardedVideoDidStart {
}
//Called after a rewarded video has finished playing.
- (void)rewardedVideoDidEnd {
}
@end
#elif US_AD_TRADPLUS //
MsBannerView* ms_BannerView;
MsInterstitialAd* ms_interstitialAd;
MsRewardedVideoAd* ms_rewardedVideoAd;
#pragma mark - MSBannerDelegate
@interface CustomMSBannerDelegate : NSObject<MsBannerViewDelegate>
@end

@implementation CustomMSBannerDelegate
#pragma mark - <FluteViewDelegate>
- (UIViewController *)viewControllerForPresentingModalView
{
    return viewController;
}

- (void)MsBannerViewLoaded:(MsBannerView *)adView
{
    NSLog(@"%s->%@", __FUNCTION__, [adView getLoadDetailInfo]);
    dispatch_async(dispatch_get_main_queue(), ^{
        AdsManager::bannerInit = true;
        AdsManager::setBannerVisible(AdsManager::bannerVisible);
    });
}
- (void)MsBannerView:(MsBannerView *)adView didFailWithError:(NSError *)error
{
    NSLog(@"%s", __FUNCTION__);
//    dispatch_async(dispatch_get_main_queue(), ^{
//    });
}
- (void)MsBannerViewImpression:(MsBannerView *)adView
{
    NSLog(@"%s", __FUNCTION__);
}
- (void)MsBannerViewDidClick:(MsBannerView *)adView
{
    NSLog(@"%s", __FUNCTION__);
}
@end

static int InterstitialRetryCNT = 0;
#pragma mark - MSInterstitialDelegate
@interface CustomMSInterstitialDelegate : NSObject<MsInterstitialAdDelegate>
@end

@implementation CustomMSInterstitialDelegate
//load 完成
- (void)interstitialAdAllLoaded:(MsInterstitialAd *)interstitialAd readyCount:(int)readyCount
{
    if (readyCount > 0)
    {
        //加载成功，有可供展示的插屏广告。
    }
    else {
        //加载失败，TradPlus后台对应广告位设置的所有三方广告源，全部加载失败。
        Director::getInstance()->getRunningScene()->scheduleOnce([](float){
            [ms_interstitialAd loadAd];
        }, 32, "schedule_interstitial_all_retry");
    }
}

- (void)interstitialAdDidLoad:(MsInterstitialAd *)interstitialAd
{
    NSLog(@"%s->ready:%d", __FUNCTION__, interstitialAd.readyAdCount);
    //EVENT_M->sendEvent("msg_interstitialDidLoad");
    //无网络也会填充 暂时不用此条件
    //DATA_M->setIsHaveInterstitials(true);//填充完毕 可以显示了
//    if (interstitialAd.readyAdCount <= 0)
//    {
//        Director::getInstance()->getRunningScene()->scheduleOnce([](float){
//            [ms_interstitialAd loadAd];
//        }, 15, "schedule_interstitial_retry");
//    }
}

- (void)interstitialAd:(MsInterstitialAd *)interstitialAd didFailWithError:(NSError *)error
{
    NSLog(@"%s->%@", __FUNCTION__, error);
//    Director::getInstance()->getRunningScene()->scheduleOnce([](float){
//        [ms_interstitialAd loadAd];
//    }, 15, "schedule_interstitial_retry");
}

- (void)interstitialAdImpression:(MsInterstitialAd *)interstitialAd
{
    NSLog(@"顺利播放插屏---%s->%@", __FUNCTION__, interstitialAd.channelName);
    DATA_M->stopDelayPlayBtn();//结算防错，3s内成功播放插屏 啧停止延时动作
}

- (void)interstitialAdDidClick:(MsInterstitialAd *)interstitialAd
{
    NSLog(@"%s", __FUNCTION__);
}

- (void)interstitialAdDismissed:(MsInterstitialAd *)interstitialAd
{
    if (AdsManager::waitWinAction)
    {
        AdsManager::waitWinAction = false;
        EVENT_M->sendEvent("msg_game_showwin");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("msg_game_showwin");
    }
    SCENE_M->refushGift();//主要是刷新翻牌icon显示
    InterstitialRetryCNT = 0;
    Director::getInstance()->getRunningScene()->scheduleOnce([](float){
        [ms_interstitialAd loadAd];
    }, 5, "schedule_interstitial_all_retry");
}

@end

static int RewardRetryCNT = 0;
#pragma mark - MSRewardedVideoDelegate
@interface CustomMSRewardedVideoDelegate : NSObject<MsRewardedVideoAdDelegate>
@end

@implementation CustomMSRewardedVideoDelegate
#pragma mark - MsRewardedVideoAdPDelegate implementation
//load 完成
- (void)rewardedVideoAdAllLoaded:(MsRewardedVideoAd *)rewardedVideoAd readyCount:(int)readyCount
{
    if (readyCount > 0)
    {
        //加载成功，有可供展示的插屏广告。
        SCENE_M->refushGift();
    }
    else {
        //加载失败，TradPlus后台对应广告位设置的所有三方广告源，全部加载失败。
        Director::getInstance()->getRunningScene()->scheduleOnce([](float){
            [ms_rewardedVideoAd loadAd];
        }, 32, "schedule_reward_all_retry");
    }
}

- (void)rewardedVideoDidLoadAd:(MsRewardedVideoAd *)rewardedVideoAd
{
    NSLog(@"%s->ready:%d", __FUNCTION__, rewardedVideoAd.readyAdCount);
//    SCENE_M->refushGift();
//    if (rewardedVideoAd.readyAdCount <= 0)
//    {
//        Director::getInstance()->getRunningScene()->scheduleOnce([](float){
//            [ms_rewardedVideoAd loadAd];
//        }, 15, "schedule_reward_retry");
//    }
}

- (void)rewardedVideoAd:(MsRewardedVideoAd *)rewardedVideoAd didFailWithError:(NSError *)error
{
    NSLog(@"%s->%@", __FUNCTION__, error);
//    Director::getInstance()->getRunningScene()->scheduleOnce([](float){
//        [ms_rewardedVideoAd loadAd];
//    }, 15, "schedule_reward_retry");
}

- (void)rewardedVideoAdImpression:(MsRewardedVideoAd *)rewardedVideoAd
{
    NSLog(@"%s", __FUNCTION__);
}

- (void)rewardedVideoAdDidClick:(MsRewardedVideoAd *)rewardedVideoAd
{
    NSLog(@"%s", __FUNCTION__);
}

- (void)rewardedVideoAdShouldReward:(MsRewardedVideoAd *)rewardedVideoAd reward:(MSRewardedVideoReward *)reward
{
    NSLog(@"%s", __FUNCTION__);
    DATA_M->lingqujinbi(0);
}

- (void)rewardedVideoAdDismissed:(MsRewardedVideoAd *)rewardedVideoAd
{
    DATA_M->playLingQUAction();
    RewardRetryCNT = 0;
    Director::getInstance()->getRunningScene()->scheduleOnce([](float){
        [ms_rewardedVideoAd loadAd];
    }, 5, "schedule_reward_diss_retry");
}
@end
#endif

void AdsManager::showBanner() {

}

void AdsManager::createVideoAds(bool init)
{
#if US_AD_TRADPLUS
    ms_rewardedVideoAd = [[MsRewardedVideoAd alloc] init];
    [ms_rewardedVideoAd setAdUnitID:msRewardVideoID];
    //    [self.rewardedVideoAd setAdUnitID:@"DDF77183659993C87A7AB45EA5E5A9AC"];
    ms_rewardedVideoAd.delegate = [[CustomMSRewardedVideoDelegate alloc] init];
    [ms_rewardedVideoAd loadAd];
#endif
}

void AdsManager::showVideoAds()
{
//    WFManager::getInstance()->showHighestAds(AdInterface::AdType::RewardVideo);
    if (haveRewardVides())
    {
#if US_IS
        [IronSource showRewardedVideoWithViewController:viewController];
#elif US_AD_TRADPLUS
        [ms_rewardedVideoAd showAdFromRootViewController:viewController];
#endif
    }
    else {
#if US_AD_TRADPLUS
        [ms_rewardedVideoAd loadAd];
#endif
    }
}
    
void AdsManager::createInterstitial(bool init)
{
#if US_IS
    [IronSource loadInterstitial];
#elif US_AD_TRADPLUS
    ms_interstitialAd = [[MsInterstitialAd alloc] init];
    ms_interstitialAd.delegate = [[CustomMSInterstitialDelegate alloc] init];
    [ms_interstitialAd setAdUnitID:msInterstitalID];
    [ms_interstitialAd loadAd];
#endif
}

void AdsManager::createMutliInterstitial()
{
 
}

bool AdsManager::showInterstitial()
{
//    return WFManager::getInstance()->showHighestAds(AdInterface::AdType::Intertitial);
    if (DATA_M->isVipNoAds()) return false;
    
    if (haveInterstitials())
    {
        DATA_M->setIsHaveInterstitials(false);//进入填充阶段
        //开启广告了
        DATA_M->setPlayAds(true);
#if US_IS
        [IronSource showInterstitialWithViewController:viewController];
#elif US_AD_TRADPLUS
        [ms_interstitialAd showAdFromRootViewController:viewController];
#endif
        return true;
    }
    else
    {
#if US_IS
        [IronSource loadInterstitial];
#elif US_AD_TRADPLUS
        [ms_interstitialAd loadAd];
#endif
    }
    return false;
}

void AdsManager::createBannerFBView(bool init)
{
   
}

void AdsManager::createInterstitialFB(bool init)
{
   
}

bool AdsManager::showInterstitialFB()
{
   
}

void AdsManager::createBannerView(bool init)
{
//    if (init)
//        is_banner_retry_cnt = 3;
    
    if (true/*is_banner_retry_cnt-- > 0*/)
    {
//        GADAdSize gadsize= GADAdSizeFullWidthPortraitWithHeight(GAD_SIZE_320x50.height);
//        CGRect screenRect = [[UIScreen mainScreen] bounds];
//        CGSize screenSize = screenRect.size;
//        ISBannerSize* bannerSize = [[ISBannerSize alloc] initWithWidth:320/*screenSize.width*/ andHeight:UIUtils::IsPad()?DefaultPadBannerHeight:DefaultBannerHeight];
//        ISBannerSize_BANNER
#if US_IS
        [IronSource loadBannerWithViewController:viewController size:ISBannerSize_SMART];
#elif US_AD_TRADPLUS
        ms_BannerView = [[MsBannerView alloc] init];
        ms_BannerView.delegate = [[CustomMSBannerDelegate alloc] init];
        [ms_BannerView setAdUnitID:msBannerID];
        [viewController.view addSubview:ms_BannerView];
        ms_BannerView.hidden = YES;
//        CGRect screenRect = [[UIScreen mainScreen] bounds];
//        CGSize screenSize = screenRect.size;
        ms_BannerView.frame = CGRectMake((viewController.view.frame.size.width-320)/2, viewController.view.frame.size.height-AdsManager::bannerHeight, 320, UIUtils::IsPad()?DefaultPadBannerHeight:DefaultBannerHeight);
        [ms_BannerView loadAd];
#endif
    }
}

void AdsManager::setRootViewController(void* vcontroller)
{
    
}

void AdsManager::initAdsManager(void* _viewController)
{
    // 初始话banner高度
    AdsManager::bannerHeight = UIUtils::IsPad()?DefaultPadBannerHeight:DefaultBannerHeight;
    auto yy = Director::getInstance()->getSafeAreaRect().origin.y;
    AdsManager::bannerHeight += yy>10?25:0;
    
    viewController = (RootViewController*)_viewController;
//    WFManager::getInstance()->init(_viewController);
    /** or for all ad units*/
#if US_IS
    [IronSource setBannerDelegate:[[CustomISBannerDelegate alloc] init]];
    [IronSource setRewardedVideoDelegate:[[CustomISRewardedVideoDelegate alloc] init]];
    [IronSource setInterstitialDelegate:[[CustomISInterstitialDelegate alloc] init]];
    [IronSource initWithAppKey:@"aed6305d" adUnits:@[IS_REWARDED_VIDEO,IS_INTERSTITIAL,IS_BANNER]];
    
    createBannerView();
    createInterstitial();
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    [ISIntegrationHelper validateIntegration];
#endif
#elif US_AD_TRADPLUS
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
//    [MsSDKUtils isTestMode];
    [MsSDKUtils logEnabled:YES];
#endif
    [MsSDKUtils logEnabled:NO];
    [MsSDKUtils msSDKInit:^(NSError *error){
        if (!error)
        {
            //初始化成功
            NSLog(@"tradplus sdk init success!");
        }
    }];
    createBannerView();
    createInterstitial();
    createVideoAds();
#endif
}

void AdsManager::createNativeExpressAds(int type)
{
    
}

void AdsManager::loadNativeExpressAds(bool init)
{
   
}

void AdsManager::showNativeExpressAds(int type)
{
   
}

void AdsManager::hiedNativeExpressAds(int type)
{
   
}

float AdsManager::getFrameScaleFactor()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCEAGLView *eaglview = static_cast<CCEAGLView *>(Director::getInstance()->getOpenGLView()->getEAGLView());
    float scaleFactor = eaglview.contentScaleFactor;
    return scaleFactor;
#endif
    return 1;
}

void AdsManager::setBannerVisible(bool flag) {
    bannerVisible = flag;
    if (AdsManager::bannerInit) {
#if US_IS
        if (is_bannerView) {
            is_bannerView.hidden = !flag;
#elif US_AD_TRADPLUS
        if (ms_BannerView) {
            ms_BannerView.hidden = !flag;
#endif
            NSDictionary *dictM = @{
                @"msg":flag?@"msg_banner_show":@"msg_banner_hide",
                @"height":[[NSNumber alloc] initWithFloat:(AdsManager::bannerHeight)]
            };
            NSData *data = [NSJSONSerialization dataWithJSONObject:dictM options:NSJSONWritingPrettyPrinted error:nil];
            NSString *strM = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
            NSLog(@"%@",strM);
            std::string jsonStr([strM UTF8String]);
            EventCustom event("jni_event_custom_callcppwithstring");
            event.setUserData(__String::create(jsonStr));
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
            [strM release];
        }
    }
}

bool AdsManager::showInterstitialAtLoaded()
{
    static int loadCNT = GETINTEGER("game_load_cnt", 0); // 一次就够了
    if (loadCNT>1 && AdsManager::AppLoadShowADS) {
        AdsManager::AppLoadShowADS = false;
        return AdsManager::showInterstitial();
    }
    return false;
}

bool AdsManager::haveRewardVides()
{
//    return WFManager::getInstance()->isReady(AdInterface::AdType::RewardVideo);
#if US_IS
    return [IronSource hasRewardedVideo];
#elif US_AD_TRADPLUS
    return (ms_rewardedVideoAd && ms_rewardedVideoAd.readyAdCount>0);
#else
    return false;
#endif
}

bool AdsManager::haveInterstitials()
{
    if (DATA_M->isVipNoAds()) return true;
#if US_IS
    return [IronSource hasInterstitial];
#elif US_AD_TRADPLUS
    return (ms_interstitialAd && ms_interstitialAd.readyAdCount>0);
#else
    return false;
#endif
}
