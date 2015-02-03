
#import <Foundation/Foundation.h>
#import "NSBundle+FileNames.h"

@implementation NSBundle (FileNames)

+ (NSArray*) fileNamesAtPath: (NSString*) resourcePath
             fullPath: (NSString**) filePath
{
    *filePath = resourcePath =
        [[NSBundle mainBundle] pathForResource: resourcePath ofType: nil];
    if (!resourcePath)
        return nil;
    NSFileManager* fileManager = [NSFileManager defaultManager];
    return [fileManager contentsOfDirectoryAtPath: resourcePath error: nil];
}

@end
