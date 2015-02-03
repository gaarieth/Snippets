
#import <Foundation/Foundation.h>
#import "NSImage+PNG.h"

@implementation NSImage (PNG)

+ (NSImage*) imageFromPNG: (NSData*) data
{
    NSImage* image = [NSImage alloc];
    image = [image initWithData: data];
    return [image autorelease];
}

- (NSData*) toPNG
{
    NSBitmapImageRep *bmp =
        [NSBitmapImageRep imageRepWithData: self.TIFFRepresentation];
    return [bmp representationUsingType: NSPNGFileType properties: nil];
}

- (NSData*) toJPG
{
    NSBitmapImageRep *bmp =
        [NSBitmapImageRep imageRepWithData: self.TIFFRepresentation];
    return [bmp representationUsingType: NSJPEG2000FileType properties: nil];
}

@end
