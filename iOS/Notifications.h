
@interface Notifications : NSObject 

+ (void) registerObserver: (id) observer
         forNotifications: (NSArray*) notificationNames
         useSelector: (SEL) selector;

+ (void) registerObserver: (id) observer
         forNotification: (NSString*) notificationName
         useSelector: (SEL) selector;

+ (void) registerObserver: (id) observer
         forNotification: (NSString*) notificationName
         fromObject: (id) object
         useSelector: (SEL) selector;

+ (void) unregisterObserver: (id) observer
         forNotification: (NSString*) notificationName
         fromObject: (id) object;

+ (void) unregisterObserver: (id) observer;

+ (void) enqueue: (NSString*) notificationName
         withObject: (NSObject*) object;

+ (void) enqueue: (NSString*) notificationName
         withUserInfo: (NSDictionary*) userInfo;

@end
