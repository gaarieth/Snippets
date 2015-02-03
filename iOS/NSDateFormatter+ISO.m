
#import <Foundation/Foundation.h>
#import "NSDateFormatter+ISO.h"

@implementation NSDateFormatter (ISO)

+ (NSDateFormatter*) dateTimeFormatter
{
    static NSDateFormatter* dateFormatter = nil;
    if (dateFormatter == nil)
    {
        dateFormatter = [NSDateFormatter new];
        [dateFormatter setDateFormat: @"yyyy-MM-dd HH:mm:ss"];
    }
    return dateFormatter;
}

+ (NSDateFormatter*) dateOnlyFormatter
{
    static NSDateFormatter* dateFormatter = nil;
    if (dateFormatter == nil)
    {
        dateFormatter = [NSDateFormatter new];
        [dateFormatter setDateFormat: @"yyyy-MM-dd"];
    }
    return dateFormatter;
}

+ (NSString*) dateTimeToString: (NSDate*) date
{
    return [[self dateTimeFormatter] stringFromDate: date];
}

+ (NSString*) dateToString: (NSDate*) date
{
    return [[self dateOnlyFormatter] stringFromDate: date];
}

+ (NSDate*) stringToDateTime: (NSString*) string
{
    return [[self dateTimeFormatter] dateFromString: string];
}

+ (NSDate*) stringToDate: (NSString*) string
{
    return [[self dateOnlyFormatter] dateFromString: string];
}

@end
