
#import "MessageUIViewController.h"

@interface PeoplePickerViewController : MessageUIViewController
<
    ABPeoplePickerNavigationControllerDelegate
>
{
    NSNumber* propertyId;
    SEL propertySelector;
}

- (void) launchPeoplePickerView: (SEL) selector
         forProperty: (const ABPropertyID*) pPropertyId;

@end
