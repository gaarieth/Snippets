
#import <Foundation/Foundation.h>
#import "NSString+Bundle.h"
#import "NSString+FileContent.h"

@implementation NSString (Bundle)

+ (NSString*) stringFromResource: (NSString*) resourceFileName
              ofType: (NSString*) fileType
{
    NSString* filePath =
        [[NSBundle mainBundle] pathForResource: resourceFileName ofType: fileType];
    return (filePath ? [NSString stringFromFileContent: filePath] : nil);
}

@end
