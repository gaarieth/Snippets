
#import <Foundation/Foundation.h>
#import "NSApplication+Delegate.h"

@implementation NSApplication (Delegate)

+ (NSObject<NSApplicationDelegate>*) applicationDelegate
{
    return [NSApplication sharedApplication].delegate;
}

@end
