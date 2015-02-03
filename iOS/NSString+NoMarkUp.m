
#import "NSString+NoMarkUp.h"

@implementation NSString (NoMarkUp)

- (NSString*) noMarkUp
{
    NSMutableString* s = [NSMutableString.alloc initWithString: self].autorelease;

    NSRange r = {0};

    while ((r = [s rangeOfString: @"<[^>]+>" options: NSRegularExpressionSearch]).location != NSNotFound)
        [s deleteCharactersInRange: r];

    return s;
}

@end
