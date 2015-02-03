
#import "UIActivityIndicator.h"

static uint8_t references;

@implementation UIActivityIndicator

+ (void) show
{
    if (references++)
        return;
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
}

+ (void) hide
{
    if ((!references) || (--references))
        return;
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
}

@end
