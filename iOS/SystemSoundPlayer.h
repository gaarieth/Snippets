
@interface SystemSoundPlayer : NSObject
{
@private
    SystemSoundID soundId;
}

- (id) initWithSoundResource: (NSString*) resourceName
       ofType: (NSString*) resourceType;

- (void) playSystemSound;

@end
