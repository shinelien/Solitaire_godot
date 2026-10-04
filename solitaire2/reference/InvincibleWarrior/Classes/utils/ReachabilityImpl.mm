//
//  ReachabilityImpl.m
//  hm_client-mobile
//
//  Created by mac on 05/12/2017.
//

#import "ReachabilityImpl.h"
#import "Reachability.h"
#include "DataManager.h"

@interface ReachabilityImpl()
    @property (nonatomic) Reachability *hostReachability;
@end

@implementation ReachabilityImpl

//static ReachabilityImpl* _instance = nil;

+(ReachabilityImpl*) shareInstance
{
    static ReachabilityImpl *sharedData = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedData = [[self alloc] init];
    });
    return sharedData;  
}

- (id)init
{
    self = [super init];
    if (self) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reachabilityChanged:) name:kReachabilityChangedNotification object:nil];
        
        self.hostReachability = [Reachability reachabilityWithHostName:@"www.apple.com"]; // 此处 hostReachability 根据需求可以定义为全局变量或静态变量
        [self.hostReachability startNotifier];
    }
    return self;
}

- (int)currentReachabilityStatus
{
    return [self.hostReachability currentReachabilityStatus];
}

- (BOOL)connectionRequired
{
    return [self.hostReachability connectionRequired];
}

/*!
 * Called by Reachability whenever status changes.
 */
- (void) reachabilityChanged:(NSNotification *)note
{
    Reachability* curReach = [note object];
    NSParameterAssert([curReach isKindOfClass:[Reachability class]]);
    DATA_M->setNetReachable([curReach currentReachabilityStatus]);
    
//    [self updateInterfaceWithReachability:curReach];
}

@end
