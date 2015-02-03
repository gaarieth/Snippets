
#import "DatePickerCell.h"

@implementation DatePickerCell

- (UIDatePicker*) datePicker
{
    return (UIDatePicker*) super.textField.inputView;
}

- (id) initWithStyle: (UITableViewCellStyle) style reuseIdentifier: (NSString*) s
{
    if (!(self = [super initWithStyle: style reuseIdentifier: s]))
        return nil;
    super.textField.inputView = UIDatePicker.new.autorelease;
    self.datePicker.datePickerMode = UIDatePickerModeDate;
    return self;
}

@end
