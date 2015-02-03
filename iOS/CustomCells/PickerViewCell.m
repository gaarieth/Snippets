
#import "PickerViewCell.h"

@implementation PickerViewCell

- (UIPickerView*) pickerView
{
    return (UIPickerView*) super.textField.inputView;
}

- (id) initWithStyle: (UITableViewCellStyle) style reuseIdentifier: (NSString*) s
{
    if (self = [super initWithStyle: style reuseIdentifier: s])
        super.textField.inputView = UIPickerView.new.autorelease;
    return self;
}

@end
