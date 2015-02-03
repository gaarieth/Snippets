
#import <Foundation/Foundation.h>
#import "NSFileManager+FileAttributes.h"

@implementation NSFileManager (FileAttributes)

+ (NSDate*) modificationDateOfFile: (NSString*) pathToFile
{
    NSFileManager* defaultFileManager = [NSFileManager defaultManager];
    NSDictionary* fileAttributes =
        [defaultFileManager attributesOfItemAtPath: pathToFile
                            error: nil];
    return [fileAttributes objectForKey: NSFileModificationDate];
}

@end
