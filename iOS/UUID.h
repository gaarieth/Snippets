
@interface UUID : NSObject
{
    CFUUIDRef uuid;
}

@property (nonatomic, readonly) CFUUIDBytes bytes;

@end
