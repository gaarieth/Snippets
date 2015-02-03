
#import <Foundation/Foundation.h>
#import "UIApplication+Delegate.h"

@implementation UIApplication (Delegate)

+ (NSObject<UIApplicationDelegate>*) applicationDelegate
{
    return UIApplication.sharedApplication.delegate;
}

@end
