
#import <Foundation/Foundation.h>
#import "NSCoder+Archiving.h"

@implementation NSCoder (Archiving)

+ (NSData*) archiveObject: (NSObject<NSCoding>*) object
            withId: (NSNumber*) objectId
{
    NSMutableData* data = [NSMutableData data];
    NSKeyedArchiver* archiver =
        [[NSKeyedArchiver alloc] initForWritingWithMutableData: data];
    [archiver encodeObject: objectId];
    [archiver encodeObject: object];
    [archiver finishEncoding];
    [archiver release];
    return data;
}

+ (NSObject<NSCoding>*) unarchiveObject: (NSData*) data
                        withId: (NSNumber**) pObjectId
{
    NSKeyedUnarchiver* unarchiver =
        [[NSKeyedUnarchiver alloc] initForReadingWithData: data];
    *pObjectId = [unarchiver decodeObject];
    NSObject<NSCoding>* object = [unarchiver decodeObject];
    [unarchiver finishDecoding];
    [unarchiver release];
    return object;
}

@end
