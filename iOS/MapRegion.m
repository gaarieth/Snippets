
#import "MapRegion.h"

@implementation MapRegion

- (id) init
{
    if (self = [super init])
        [self reset];
    return self;
}

- (BOOL) hasCoordinate: (CLLocationCoordinate2D) coordinate
{
    return (CLLocationCoordinate2DIsValid(coordinate) &&
            (n >= coordinate.latitude) &&
            (s <= coordinate.latitude) &&
            (w >= coordinate.longitude) &&
            (e <= coordinate.longitude));
}

- (void) addCoordinate: (CLLocationCoordinate2D) coordinate
{
    if (!CLLocationCoordinate2DIsValid(coordinate))
        return;
    n = MAX(n, coordinate.latitude);
    s = MIN(s, coordinate.latitude);
    w = MIN(w, coordinate.longitude);
    e = MAX(e, coordinate.longitude);
}

- (void) addCoordinate: (CLLocationCoordinate2D) coordinate
         withRadius: (CLLocationDistance) radius;
{
    if (radius < 1)
    {
        [self addCoordinate: coordinate];

        return;
    }

    if (!CLLocationCoordinate2DIsValid(coordinate))
        return;

    double deltaMapPoints =
        radius * MKMapPointsPerMeterAtLatitude(coordinate.latitude);

    MKMapPoint mapPoint = MKMapPointForCoordinate(coordinate);

    // TODO: (w > e)

    mapPoint.y -= deltaMapPoints;
    [self addCoordinate: MKCoordinateForMapPoint(mapPoint)];
    mapPoint.y += deltaMapPoints;

    mapPoint.y += deltaMapPoints;
    [self addCoordinate: MKCoordinateForMapPoint(mapPoint)];
    mapPoint.y -= deltaMapPoints;

    mapPoint.x -= deltaMapPoints;
    [self addCoordinate: MKCoordinateForMapPoint(mapPoint)];
    mapPoint.x += deltaMapPoints;

    mapPoint.x += deltaMapPoints;
    [self addCoordinate: MKCoordinateForMapPoint(mapPoint)];
    mapPoint.x -= deltaMapPoints;
}

- (MKCoordinateRegion) region
{
    MKCoordinateRegion region =
    {
        (n + s) / 2,
        (w + e) / 2,
        (n - s) * 1.2f,
        (e - w) * 1.2f
    };

    // TODO: (w > e)

    if ((n ==  -90) ||
        (s ==   90) ||
        (w ==  180) ||
        (e == -180))
    {
        region.center.latitude = 0;
        region.center.longitude = 0;
        region.span.latitudeDelta = 90;
        region.span.longitudeDelta = 180;

        return region;
    }

    return region;
}

- (void) reset
{
    n =  -90;
    s =   90;
    w =  180;
    e = -180;
}

@end
