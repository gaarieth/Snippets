
#import <Foundation/Foundation.h>
#import "NSString+FileContent.h"

@implementation NSString (FileContent)

+ (NSString*) stringFromFileContent: (NSString*) filePath
{
    return [NSString stringWithContentsOfFile: filePath
                     encoding: NSUTF8StringEncoding
                     error: nil];
}

@end
