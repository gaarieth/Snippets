
#import <Foundation/Foundation.h>
#import "Notifications.h"

@implementation Notifications

+ (void) registerObserver: (id) observer
         forNotifications: (NSArray*) notificationNames
         useSelector: (SEL) selector
{
    for (NSString* notificationName in notificationNames)
    {
        [self registerObserver: observer
              forNotification: notificationName
              useSelector: selector];
    }
}

+ (void) registerObserver: (id) observer
         forNotification: (NSString*) notificationName
         useSelector: (SEL) selector
{
   [self registerObserver: observer
         forNotification: notificationName
         fromObject: nil
         useSelector: selector];
}

+ (void) registerObserver: (id) observer
         forNotification: (NSString*) notificationName
         fromObject: (id) object
         useSelector: (SEL) selector
{
    NSNotificationCenter* defaultCenter = [NSNotificationCenter defaultCenter];

    [defaultCenter addObserver: observer
                   selector: selector
                   name: notificationName
                   object: object];
}

+ (void) unregisterObserver: (id) observer
         forNotification: (NSString*) notificationName
         fromObject: (id) object
{
    NSNotificationCenter* defaultCenter = [NSNotificationCenter defaultCenter];

    [defaultCenter removeObserver: observer
                   name: notificationName
                   object: object];
}

+ (void) unregisterObserver: (id) observer
{
    NSNotificationCenter* defaultCenter = [NSNotificationCenter defaultCenter];

    [defaultCenter removeObserver: observer];
}

+ (void) enqueue: (NSNotification*) notification
{
    NSNotificationQueue* notificationQueue = [NSNotificationQueue defaultQueue];

    [notificationQueue enqueueNotification: notification
                       postingStyle: NSPostWhenIdle
                       coalesceMask: NSNotificationNoCoalescing
                       forModes: nil];
}

+ (void) enqueue: (NSString*) notificationName
         withObject: (NSObject*) object
{
    NSNotification* notification =
        [NSNotification notificationWithName: notificationName
                        object: object
                        userInfo: nil];

    [self enqueue: notification];
}

+ (void) enqueue: (NSString*) notificationName
         withUserInfo: (NSDictionary*) userInfo
{
    NSNotification* notification =
        [NSNotification notificationWithName: notificationName
                        object: nil
                        userInfo: userInfo];

    [self enqueue: notification];
}

@end
