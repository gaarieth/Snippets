
@interface MessageUIViewController : UIViewController
<
    MFMessageComposeViewControllerDelegate,
    MFMailComposeViewControllerDelegate
>

- (void) launchTextMessageView: (NSString*) contactNumber
         withMessage: (NSString*) message;
- (void) launchMailMessageView: (NSString*) eMailAddress
         withMessage: (NSString*) message
         isHTML: (BOOL) isHTML;

@end
