
#import "LabelCell.h"

@implementation LabelCell

- (UILabel*) label
{
    return (UILabel*) super.accessoryView;
}

- (id) initWithStyle: (UITableViewCellStyle) style reuseIdentifier: (NSString*) s
{
    if (self = [super initWithStyle: style reuseIdentifier: s])
        super.accessoryView = UILabel.new.autorelease;
    return self;
}

@end
