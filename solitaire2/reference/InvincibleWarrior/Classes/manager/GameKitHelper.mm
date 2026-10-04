//
//  GameKitHelper.m
//  hm_solitaire-mobile
//
//  Created by mbp2 on 2018/11/5.
//

#include "GameKitHelper.h"
#import "RootViewController.h"
#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
#import <GameKit/GKGameCenterViewController.h>
#import <Social/Social.h>
#import <MessageUI/MessageUI.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;
static RootViewController* s_viewController;

@interface mailDelegate : NSObject<MFMailComposeViewControllerDelegate>
@end

@implementation mailDelegate
- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(nullable NSError *)error {
    [controller dismissViewControllerAnimated:YES completion:nil];
}
@end

#pragma mark -  GKGameCenterControllerDelegate
@interface gcControllerDelegate : NSObject<GKGameCenterControllerDelegate>

@end

@implementation gcControllerDelegate
- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController{
    [gameCenterViewController dismissViewControllerAnimated:YES completion:nil];
}
@end

void GameKitHelper::setRootViewController(void* viewController) {
    s_viewController = (RootViewController*)viewController;
    authPlayer();
}

//验证授权
int GameKitHelper::authPlayer(){
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    
    localPlayer.authenticateHandler = ^(UIViewController * __nullable viewController, NSError * __nullable error){
        if ([[GKLocalPlayer localPlayer] isAuthenticated]) {
            NSLog(@"%@",@"已经授权！");
        }else if(viewController){
            [s_viewController presentViewController:viewController animated:YES completion:nil];
        }else{
            if (!error) {
                NSLog(@"%@",@"授权OK");
            } else {
                NSLog(@"没有授权");
                NSLog(@"AuthPlayer error :%@",error);
            }
        }
    };
    return 1;
}

// 上传分数给 gameCenter
void GameKitHelper::saveHighScore(const string &ID, int value){
    if ([GKLocalPlayer localPlayer].isAuthenticated) {
        //得到分数的报告
        GKScore *scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier:[NSString stringWithUTF8String:ID.c_str()] ];
        scoreReporter.value = value;
        NSArray<GKScore*> *scoreArray = @[scoreReporter];
        //上传分数
        [GKScore reportScores:scoreArray withCompletionHandler:nil];
        [scoreReporter release];
    }
}

//下载 game center 某一排行榜中的分数及排名情况
void GameKitHelper::downLoadGameCenter(const string &ID, int range, const string &zoneType){
    if ([GKLocalPlayer localPlayer].isAuthenticated == NO) {
        NSLog(@"没有授权，无法获取更多信息");
        return;
    }
    GKLeaderboard *leaderboadRequest = [GKLeaderboard new];
    //设置好友的范围
    leaderboadRequest.playerScope = GKLeaderboardPlayerScopeGlobal;
    //指定那个区域的排行榜
    NSString *type = [[NSString alloc] initWithUTF8String:zoneType.c_str()];
    if ([type isEqualToString:@"today"]) {
        leaderboadRequest.timeScope = GKLeaderboardTimeScopeToday;
        
    }else if([type isEqualToString:@"week"]){
        leaderboadRequest.timeScope = GKLeaderboardTimeScopeWeek;
        
    }else if([type isEqualToString:@"all"]){
        leaderboadRequest.timeScope = GKLeaderboardTimeScopeAllTime;
        
    }
    //哪一个排行榜
    leaderboadRequest.identifier = [[NSString alloc] initWithUTF8String:ID.c_str()];
    //从那个排名到那个排名
    NSInteger location = 1;
    NSInteger length = range;
    leaderboadRequest.range = NSMakeRange(location, length);
    //请求数据
    [leaderboadRequest loadScoresWithCompletionHandler:^(NSArray<GKScore *> * _Nullable scores, NSError * _Nullable error) {
        if (error) {
            NSLog(@"请求分数失败");
            NSLog(@"error = %@",error);
        }else{
            NSLog(@"请求分数成功");
            //定义一个可变字符串存放用户信息
            NSMutableString *userInfo = [NSMutableString string];
            NSString *rankBoardID = nil;
            for (GKScore *score in scores) {
                NSLog(@"");
                //得到排行榜的 id
                NSString *gamecenterID = score.leaderboardIdentifier;
                NSString *playerName = score.player.displayName;
                NSInteger scroeNumb = score.value;
                NSInteger rank = score.rank;
                NSLog(@"排行榜 = %@，玩家名字 = %@，玩家分数 = %zd，玩家排名 = %zd",gamecenterID,playerName,scroeNumb,rank);
                [userInfo appendString:[NSString stringWithFormat:@"玩家名字 = %@，玩家分数 = %zd，玩家排名 = %zd",playerName,scroeNumb,rank]];
                [userInfo appendString:@"\n"];
                rankBoardID = gamecenterID;
            }
            //弹框展示
//            [s_viewController popShowViewWithTitileName:[NSString stringWithFormat:@"%@ 排行榜的信息",rankBoardID] andInfo:userInfo];
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:[NSString stringWithFormat:@"%@ 排行榜的信息",rankBoardID] message:userInfo preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:nil]];
            [s_viewController presentViewController:alert animated:true completion:nil];
        }
    }];
}

void GameKitHelper::showLeaderBoard()
{
    if ([GKLocalPlayer localPlayer].isAuthenticated == NO) {
        NSLog(@"没有授权，无法获取更多信息");
        authPlayer();
        return;
    }
    
    GKGameCenterViewController *gcViewController = [GKGameCenterViewController new];
    gcViewController.gameCenterDelegate = [[gcControllerDelegate alloc] init];
    [s_viewController presentViewController:gcViewController animated:true completion:nil];
}

void GameKitHelper::shareApp()
{
//    UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    // app名称
    NSString *textToShare = [infoDictionary objectForKey:@"CFBundleDisplayName"];
//    NSString *icon = [[infoDictionary valueForKeyPath:@"CFBundleIcons.CFBundlePrimaryIcon.CFBundleIconFiles"] lastObject];
//    UIImage* imageToShare = [UIImage imageNamed:icon];
    
    NSURL *urlToShare = [NSURL URLWithString:@"https://itunes.apple.com/app/solitaire-solo-classic/id1249968208"];
    NSArray *activityItems = @[textToShare, urlToShare];
    UIActivityViewController *activityController=[[UIActivityViewController alloc]initWithActivityItems:activityItems applicationActivities:nil];
    
    //---------
    activityController.completionWithItemsHandler = ^(UIActivityType  _Nullable   activityType,
                                            BOOL completed,
                                            NSArray * _Nullable returnedItems,
                                            NSError * _Nullable activityError) {
        //分享是否成功
        if(completed == YES)
        {
            DATA_M->shareYES();
        }
        NSLog(@"activityType: %@,\n completed: %d,\n returnedItems:%@,\n activityError:%@",activityType,completed,returnedItems,activityError);
    };
    //----------
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        // For iPhone
        [s_viewController presentViewController:activityController animated:YES completion:nil];
    }
    else {
        // For iPad, present it as a popover as you already know
        UIPopoverController *popup = [[UIPopoverController alloc] initWithContentViewController:activityController];
        //Change rect according to where you need to display it. Using a junk value here
        [popup presentPopoverFromRect:CGRectMake(0, s_viewController.view.frame.size.height, 0, 0) inView:s_viewController.view permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
    }
//    [s_viewController presentViewController:activityController animated:YES completion:nil];
}

void GameKitHelper::writComment() {
    Application::getInstance()->openURL("itms-apps://itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&onlyLatestVersion=true&pageNumber=0&sortOrdering=1&id=1249968208");
}

void GameKitHelper::openMail() {
    if ([MFMailComposeViewController canSendMail]) {
        // 创建邮件发送界面
        MFMailComposeViewController *mailCompose = [[MFMailComposeViewController alloc] init];
        // 设置邮件代理
        [mailCompose setMailComposeDelegate:[[mailDelegate alloc] init]];
        // 设置收件人
        [mailCompose setToRecipients:@[@"shinelien@icloud.com"]];
        // 设置邮件主题
        [mailCompose setSubject:@"意见反馈"];
        // 弹出邮件发送视图
        [s_viewController presentViewController:mailCompose animated:YES completion:nil];
    }else{
        [[UIApplication sharedApplication]openURL:[NSURL URLWithString:@"mailto:shinelien@icloud.com?&subject=意见反馈"] options:@{} completionHandler:nil];
    }
}
