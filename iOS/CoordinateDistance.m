
#import "CoordinateDistance.h"

CLLocationDistance CoordinateDistance
(
    CLLocationCoordinate2D c1,
    CLLocationCoordinate2D c2
)
{
    CLLocation* l1 =
        [CLLocation.alloc initWithLatitude: c1.latitude
                          longitude: c1.longitude].autorelease;
    CLLocation* l2 =
        [CLLocation.alloc initWithLatitude: c2.latitude
                          longitude: c2.longitude].autorelease;
    return [l2 distanceFromLocation: l1];
}
