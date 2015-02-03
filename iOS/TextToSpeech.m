
#import "TextToSpeech.h"

@implementation TextToSpeech

- (id) init
{
    if (self = [super init])
        // VoiceServices.framework iOS 6.1
        // speechSynthesizer = [NSClassFromString(@"VSSpeechSynthesizer") new];
        speechSynthesizer = [AVSpeechSynthesizer new];
    return self;
}

- (void) dealloc
{
    [speechSynthesizer stopSpeakingAtBoundary: AVSpeechBoundaryImmediate];
    [speechSynthesizer release];
    [super dealloc];
}

- (void) say: (NSString*) text
{
    AVSpeechUtterance* utterance = [AVSpeechUtterance.alloc initWithString: text];
    utterance.rate = 0.3f;
    [speechSynthesizer stopSpeakingAtBoundary: AVSpeechBoundaryImmediate];
    [speechSynthesizer speakUtterance: utterance]; // startSpeakingString: text];
    [utterance release];
}

@end
