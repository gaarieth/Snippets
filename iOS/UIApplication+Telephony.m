
#import <Foundation/Foundation.h>
#import "UIApplication+Telephony.h"
#import "UIAlertView+SimpleAlerts.h"

@implementation UIApplication (Telephony)

+ (void) makeCall: (NSString*) number
{
    NSURL* url =
        [NSURL URLWithString: [NSString stringWithFormat: @"tel://%@", number]];
    UIApplication* application = UIApplication.sharedApplication;
    if ([application canOpenURL: url])
        [application openURL: url];
    else
        [UIAlertView showMessage: @"Telephony Not Available"];
}

@end
