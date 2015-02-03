
#import <Foundation/Foundation.h>
#import "NSDate+Duration.h"

@implementation NSDate (Duration)

- (NSString*) duration: (NSUInteger) seconds
{
    const uint secondsPerMinute = 60;
    const uint secondsPerHour = 60 * secondsPerMinute;
    const uint secondsPerDay = 24 * secondsPerHour;

    uint days = seconds / secondsPerDay;
    seconds %= secondsPerDay;
    uint hours = seconds / secondsPerHour;
    seconds %= secondsPerHour;
    uint minutes = seconds / secondsPerMinute;
    seconds %= secondsPerMinute;

    return [NSString stringWithFormat: @"%ud %02uh %02um"
                                     , days
                                     , hours
                                     , minutes];
}

- (NSString*) durationTillNow
{
    return [self duration: -[self timeIntervalSinceNow]];
}

- (NSString*) durationTillDate: (NSDate*) date
{
    return [self duration: -[self timeIntervalSinceDate: date]];
}

@end
