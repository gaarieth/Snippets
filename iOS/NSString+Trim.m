
#import <Foundation/Foundation.h>
#import "NSString+Trim.h"

@implementation NSString (Trim)

- (NSString*) trim
{
    NSCharacterSet* noWhiteSpace =
        [NSCharacterSet whitespaceAndNewlineCharacterSet];

    return [self stringByTrimmingCharactersInSet: noWhiteSpace];
}

@end
