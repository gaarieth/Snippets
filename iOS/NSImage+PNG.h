
@interface NSImage (PNG)

+ (NSImage*) imageFromPNG: (NSData*) data;

- (NSData*) toPNG;

- (NSData*) toJPG;

@end
