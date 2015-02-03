
#import "PeoplePickerViewController.h"
#import "UIAlertView+SimpleAlerts.h"

@implementation PeoplePickerViewController

- (void) launchPeoplePickerView: (SEL) selector
         forProperty: (const ABPropertyID*) pPropertyId
{
    propertySelector = selector;

    static ABPeoplePickerNavigationController* peoplePicker = nil;
    if (peoplePicker)
        [peoplePicker popToRootViewControllerAnimated: YES];
    else
    {
        static dispatch_once_t onceToken = 0;

        dispatch_once(&onceToken, ^
        {
            peoplePicker = [ABPeoplePickerNavigationController new];
        });
    } // TODO: https://discussions.apple.com/message/23628142

    peoplePicker.peoplePickerDelegate = self;

    [super presentViewController: peoplePicker animated: YES completion:
    ^()
    {
        propertyId = [[NSNumber numberWithInt: *pPropertyId] retain];

        peoplePicker.displayedProperties = [NSArray arrayWithObject: propertyId];
    }];
}

- (void) dismissPeoplePickerView: (CFTypeRef) multiValue index: (CFIndex) i
{
    [super dismissViewControllerAnimated: YES completion: (multiValue ?
    ^()
    {
        NSString* singleValue = ABMultiValueCopyValueAtIndex(multiValue, i);
        [self performSelector: propertySelector withObject: singleValue];
        CFRelease(singleValue);
    } : nil)];

    [propertyId release];
}

- (void) peoplePickerNavigationControllerDidCancel: (ABPeoplePickerNavigationController*) picker
{
    [self dismissPeoplePickerView: nil index: 0];
}

- (BOOL) peoplePickerNavigationController: (ABPeoplePickerNavigationController*) picker
         shouldContinueAfterSelectingPerson: (ABRecordRef) person
{
    BOOL b = NO;

    CFTypeRef multiValue = ABRecordCopyValue(person, propertyId.intValue);
    if (ABMultiValueGetCount(multiValue) == 1)
        [self dismissPeoplePickerView: multiValue index: 0];
    else
        b = YES;
    CFRelease(multiValue);

    return b;
}

- (BOOL) peoplePickerNavigationController: (ABPeoplePickerNavigationController*) picker
         shouldContinueAfterSelectingPerson: (ABRecordRef) person
         property: (ABPropertyID) property
         identifier: (ABMultiValueIdentifier) identifier
{
    CFTypeRef multiValue = ABRecordCopyValue(person, property);
    [self dismissPeoplePickerView: multiValue
          index: ABMultiValueGetIndexForIdentifier(multiValue, identifier)];
    CFRelease(multiValue);

    return NO;
}

@end
