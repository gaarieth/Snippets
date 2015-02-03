
#import <Foundation/Foundation.h>
#import "NSURL+Bundle.h"
#import "SystemSoundPlayer.h"

@implementation SystemSoundPlayer

- (void) dealloc
{
    AudioServicesDisposeSystemSoundID(soundId);

    [super dealloc];
}

- (id) initWithSoundResource: (NSString*) resourceName
       ofType: (NSString*) resourceType
{
    if (!(self = [super init]))
    	return nil;

    CFURLRef url =
        (CFURLRef) [NSURL urlForResource: resourceName ofType: resourceType];

    UInt32 sessionCategory = kAudioSessionCategory_AmbientSound;
    AudioSessionSetProperty(kAudioSessionProperty_AudioCategory,
                            sizeof (sessionCategory),
                            &sessionCategory);

    AudioServicesCreateSystemSoundID(url, &soundId);

    return self;
}

- (void) playSystemSound
{
    AudioServicesPlaySystemSound(soundId);
}

@end
