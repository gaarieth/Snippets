
@interface AudioPlayer : NSObject
{
@private
    AVAudioPlayer* avAudioPlayer;
}

- (id) initWithAudioResource: (NSString*) resourceName
       ofType: (NSString*) resourceType;

@end
