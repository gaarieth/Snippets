
#import "NSStream+RunLoop.h"

@implementation NSStream (RunLoop)

- (void) scheduleInRunLoop
{
    [self scheduleInRunLoop: [NSRunLoop currentRunLoop]
          forMode: NSDefaultRunLoopMode];
}

- (void) removeFromRunLoop
{
    [self removeFromRunLoop: [NSRunLoop currentRunLoop]
          forMode: NSDefaultRunLoopMode];
}

@end
