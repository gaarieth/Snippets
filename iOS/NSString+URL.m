
#import <Foundation/Foundation.h>
#import "NSString+URL.h"

@implementation NSString (URL)

- (NSString*) urlEncode
{
    return [self stringByAddingPercentEscapesUsingEncoding: NSUTF8StringEncoding];
}

- (NSString*) urlDecode
{
    return [self stringByReplacingPercentEscapesUsingEncoding: NSUTF8StringEncoding];
}

@end
