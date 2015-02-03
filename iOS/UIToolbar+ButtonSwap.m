
#import <Foundation/Foundation.h>
#import "UIToolbar+ButtonSwap.h"

@implementation UIToolbar (ButtonSwap)

- (void) swapButton: (UIBarButtonItem*) button atIndex: (NSUInteger) index
{
    NSMutableArray* toolBarItems = [self.items mutableCopy];
    [toolBarItems replaceObjectAtIndex: index withObject: button];
    self.items = toolBarItems;
    [toolBarItems release];
}

@end
