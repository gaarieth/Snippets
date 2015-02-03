
#import "CustomCell.h"

@implementation CustomCell

- (void) layoutSubviews
{
    [super layoutSubviews];

    const float W = super.bounds.size.width;
    const float X = super.accessoryView.frame.origin.y; // super.textLabel.frame.origin.x;

    CGRect f = super.accessoryView.frame;
    f.size.width = MIN(W - super.textLabel.bounds.size.width - X * 3,
                       super.accessoryView.intrinsicContentSize.width);
    f.origin.x = W - f.size.width - X;
    super.accessoryView.frame = f;
}

@end
