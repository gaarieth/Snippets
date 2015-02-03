
#import "MessageUIViewController.h"
#import "UIAlertView+SimpleAlerts.h"

@implementation MessageUIViewController

- (void) launchTextMessageView: (NSString*) contactNumber
         withMessage: (NSString*) message
{
    if (!MFMessageComposeViewController.canSendText)
    {
        [UIAlertView showMessage: @"Text Messaging Not Available"];
        return;
    }
    MFMessageComposeViewController* messageView =
        [MFMessageComposeViewController new];
    messageView.messageComposeDelegate = self;
    if (contactNumber)
        messageView.recipients = [NSArray arrayWithObject: contactNumber];
    messageView.body = message;
    [super presentViewController: messageView animated: YES completion: nil];
    [messageView release];
}

- (void) launchMailMessageView: (NSString*) eMailAddress
         withMessage: (NSString*) message
         isHTML: (BOOL) isHTML
{
    if (!MFMailComposeViewController.canSendMail)
    {
        [UIAlertView showMessage: @"Mail Messaging Not Available"];
        return;
    }
    MFMailComposeViewController* mailView =
        [MFMailComposeViewController new];
    mailView.mailComposeDelegate = self;
    if (eMailAddress)
        mailView.toRecipients = [NSArray arrayWithObject: eMailAddress];
    mailView.subject = NSProcessInfo.processInfo.processName;
    [mailView setMessageBody: message isHTML: isHTML];
    [super presentViewController: mailView animated: YES completion: nil];
    [mailView release];
}

- (void) messageComposeViewController: (MFMessageComposeViewController*) controller
         didFinishWithResult: (MessageComposeResult) result
{
    if (result == MessageComposeResultFailed)
        [UIAlertView showMessage: @"Text Message Failed"];
    [super dismissViewControllerAnimated: YES completion: nil];
}

- (void) mailComposeController: (MFMailComposeViewController*) controller
         didFinishWithResult: (MFMailComposeResult) result
         error: (NSError*) error
{
    if (result == MFMailComposeResultFailed)
        [UIAlertView showMessage: @"Mail Message Failed"];
    [super dismissViewControllerAnimated: YES completion: nil];
}

@end
