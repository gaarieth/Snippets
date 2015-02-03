
#import <Foundation/Foundation.h>
#import "NSURL+Bundle.h"

@implementation NSURL (Bundle)

+ (NSURL*) urlForResource: (NSString*) fileResourceName
           ofType: (NSString*) fileResourceType
{
    NSString* filePath =
        [[NSBundle mainBundle] pathForResource: fileResourceName
                               ofType: fileResourceType];
    if (!filePath)
        return nil;
    return [NSURL fileURLWithPath: filePath isDirectory: NO];
}

@end
