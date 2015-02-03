
@interface MKPolyline (Coordinates)

@property (nonatomic, assign) CLLocationCoordinate2D sourceCoord;
@property (nonatomic, assign) CLLocationCoordinate2D targetCoord;

@property (nonatomic, readonly) CLLocationCoordinate2D firstCoord;
@property (nonatomic, readonly) CLLocationCoordinate2D lastCoord;

@end
