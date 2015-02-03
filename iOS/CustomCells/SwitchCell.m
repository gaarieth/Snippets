
#import "SwitchCell.h"

@implementation SwitchCell

- (UISwitch*) switchControl
{
    return (UISwitch*) super.accessoryView;
}

- (id) initWithStyle: (UITableViewCellStyle) style reuseIdentifier: (NSString*) s
{
    if (self = [super initWithStyle: style reuseIdentifier: s])
        super.accessoryView = UISwitch.new.autorelease;
    return self;
}

@end
