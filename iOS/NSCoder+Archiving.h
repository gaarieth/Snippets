
@interface NSCoder (Archiving)

+ (NSData*) archiveObject: (NSObject<NSCoding>*) object
            withId: (NSNumber*) objectId;

+ (NSObject<NSCoding>*) unarchiveObject: (NSData*) data
                        withId: (NSNumber**) pObjectId;

@end
