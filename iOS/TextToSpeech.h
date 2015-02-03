
@interface TextToSpeech : NSObject
{
    AVSpeechSynthesizer* speechSynthesizer;
}

- (void) say: (NSString*) text;

@end
