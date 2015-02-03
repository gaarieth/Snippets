
@interface MapRegion : NSObject
{
@private
    CLLocationDegrees n, s, w, e;
}

- (BOOL) hasCoordinate: (CLLocationCoordinate2D) coordinate;

- (void) addCoordinate: (CLLocationCoordinate2D) coordinate;

- (void) addCoordinate: (CLLocationCoordinate2D) coordinate
         withRadius: (CLLocationDistance) radius;

- (MKCoordinateRegion) region;

- (void) reset;

@end
