//
//  SMS
//  GetSocial
//
//  Created by Tuan
//
//
#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>
#import "RootViewController.h"
#import "AppController.h"


@interface SendSMS : UIViewController<UINavigationControllerDelegate>

-(void) sendInAppSMS;
- (void)sendSMS:(NSString *)bodyOfMessage recipientList:(NSArray *)recipients;
@end