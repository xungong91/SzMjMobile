#import <UIKit/UIKit.h>
#import "WXApi.h"

@class RootViewController;

@interface AppController : UIResponder <UIApplicationDelegate, WXApiDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

