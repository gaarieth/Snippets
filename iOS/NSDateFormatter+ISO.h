
@interface NSDateFormatter (ISO)

+ (NSDateFormatter*) dateTimeFormatter;
+ (NSDateFormatter*) dateOnlyFormatter;

+ (NSString*) dateTimeToString: (NSDate*) date;
+ (NSString*) dateToString: (NSDate*) date;
+ (NSDate*) stringToDateTime: (NSString*) string;
+ (NSDate*) stringToDate: (NSString*) string;

@end
