
#import "SegmentedControlCell.h"

@implementation SegmentedControlCell

- (UISegmentedControl*) segmentedControl
{
    return (UISegmentedControl*) super.accessoryView;
}

- (id) initWithStyle: (UITableViewCellStyle) style reuseIdentifier: (NSString*) s
{
    if (self = [super initWithStyle: style reuseIdentifier: s])
        super.accessoryView = UISegmentedControl.new.autorelease;
    return self;
}

@end
