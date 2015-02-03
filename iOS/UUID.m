
#import <Foundation/Foundation.h>
#import "UUID.h"

@implementation UUID

- (CFUUIDBytes) bytes
{
    return CFUUIDGetUUIDBytes(uuid);
}

- (id) init
{
    if (!(self = [super init]))
        return nil;
    if (!(uuid = CFUUIDCreate(0)))
    {
        [self release];
        return nil;
    }
    return self;
}

- (void) dealloc
{
    if (uuid)
        CFRelease(uuid);
    [super dealloc];
}

@end
