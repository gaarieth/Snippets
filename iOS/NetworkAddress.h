
@interface NetworkAddress : NSObject
{
}

+ (NSArray*) allAddresses;

+ (NSString*) ipAddressOfPeer: (NSFileHandle*) peer;

@end
