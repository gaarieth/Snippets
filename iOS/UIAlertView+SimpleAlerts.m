
#import <Foundation/Foundation.h>
#import "UIAlertView+SimpleAlerts.h"

@implementation UIAlertView (SimpleAlerts)

+ (UIAlertView*) showMessage: (NSString*) message
{
    UIAlertView* alertView = [UIAlertView alloc];
    alertView =
        [alertView initWithTitle: NSProcessInfo.processInfo.processName
                   message: message
                   delegate: nil
                   cancelButtonTitle: @"OK"
                   otherButtonTitles: nil];
    [alertView show];
    return [alertView autorelease];
}

@end
