
#import <Foundation/Foundation.h>
#import "NSImage+Bundle.h"

@implementation NSImage (Bundle)

+ (NSImage*) imageFromResource: (NSString*) imageName
             ofType: (NSString*) imageType
             inDirectory: (NSString*) imageDirectory
             atPath: (NSString**) pImagePath;
{
    NSString* filePath =
        [[NSBundle mainBundle] pathForResource: imageName
                               ofType: imageType
                               inDirectory: imageDirectory];
    if (pImagePath)
        *pImagePath = filePath;
    if (!filePath)
        return nil;
    return [[[NSImage new] initWithContentsOfFile: filePath] autorelease];
}

@end
