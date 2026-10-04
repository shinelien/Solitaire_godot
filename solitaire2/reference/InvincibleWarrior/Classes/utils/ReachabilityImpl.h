//
//  ReachabilityImpl.h
//  hm_client
//
//  Created by mac on 05/12/2017.
//

#ifndef ReachabilityImpl_h
#define ReachabilityImpl_h

#import <Foundation/Foundation.h>

@interface ReachabilityImpl : NSObject
+(ReachabilityImpl*) shareInstance;
- (int)currentReachabilityStatus;
- (BOOL)connectionRequired;
@end

#endif /* ReachabilityImpl_h */
