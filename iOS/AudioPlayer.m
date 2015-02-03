
#import <Foundation/Foundation.h>
#import "NSURL+Bundle.h"
#import "AudioPlayer.h"

@implementation AudioPlayer

- (void) dealloc
{
    [avAudioPlayer stop];
    [avAudioPlayer release];
    [super dealloc];
}

- (id) initWithAudioResource: (NSString*) resourceName
       ofType: (NSString*) resourceType
{
    if (!(self = [super init]))
    	return nil;

    NSURL* url = [NSURL urlForResource: resourceName ofType: resourceType];

    avAudioPlayer = [AVAudioPlayer alloc];
    avAudioPlayer = [avAudioPlayer initWithContentsOfURL: url error: nil];

    [avAudioPlayer play];

    return self;
}

@end
