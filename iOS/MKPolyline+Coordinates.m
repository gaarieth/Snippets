
#import "MKPolyline+Coordinates.h"
#import <objc/runtime.h>

@implementation MKPolyline (Coordinates)

- (CLLocationCoordinate2D) getCoord: (NSUInteger) i
{
    CLLocationCoordinate2D c = {0};

    [self getCoordinates: &c range: NSMakeRange(i, 1)];

    return c;
}

const char A = OBJC_ASSOCIATION_RETAIN_NONATOMIC;
const char S = 0;
const char T = 0;

- (CLLocationCoordinate2D) sourceCoord
{
    return [objc_getAssociatedObject(self, &S) coordinate];
}

- (void) setSourceCoord: (CLLocationCoordinate2D) c
{
    CLLocation* location =
        [CLLocation.alloc initWithLatitude: c.latitude longitude: c.longitude];
    objc_setAssociatedObject(self, &S, location.autorelease, A);
}

- (CLLocationCoordinate2D) targetCoord
{
    return [objc_getAssociatedObject(self, &T) coordinate];
}

- (void) setTargetCoord: (CLLocationCoordinate2D) c
{
    CLLocation* location =
        [CLLocation.alloc initWithLatitude: c.latitude longitude: c.longitude];
    objc_setAssociatedObject(self, &T, location.autorelease, A);
}

- (CLLocationCoordinate2D) firstCoord
{
    return [self getCoord: 0];
}

- (CLLocationCoordinate2D) lastCoord
{
    return [self getCoord: (self.pointCount - 1)];
}

@end
