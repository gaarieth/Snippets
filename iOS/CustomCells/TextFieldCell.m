
#import "TextFieldCell.h"

@implementation TextFieldCell

- (UITextField*) textField
{
    return (UITextField*) super.accessoryView;
}

- (id) initWithStyle: (UITableViewCellStyle) style reuseIdentifier: (NSString*) s
{
    if (self = [super initWithStyle: style reuseIdentifier: s])
        super.accessoryView = UITextField.new.autorelease;
    return self;
}

- (void) toggle1stResponder
{
    if (self.textField.isFirstResponder)
        [self.textField resignFirstResponder];
    else
        [self.textField becomeFirstResponder];
}

@end
