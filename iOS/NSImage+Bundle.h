
@interface NSImage (Bundle)

+ (NSImage*) imageFromResource: (NSString*) imageName
             ofType: (NSString*) imageType
             inDirectory: (NSString*) imageDirectory
             atPath: (NSString**) pImagePath;

@end
