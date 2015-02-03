
#import "MKUserLocation+OK.h"

@implementation MKUserLocation (OK)

- (BOOL) locationOK: (CLLocationCoordinate2D*) pCoordinate
{
    if (pCoordinate)
        *pCoordinate = self.location.coordinate;

    return (self.location &&
            (self.location.horizontalAccuracy >= 0) &&
            CLLocationCoordinate2DIsValid(self.location.coordinate));
}

@end
