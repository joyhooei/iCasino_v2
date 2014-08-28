//
//  MailSender.h
//  GetSocial
//
//  Created by Mikel Eizagirre on 24/03/13.
//
//

#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>
#import "RootViewController.h"
#import "AppController.h"

@interface MailSender : UIViewController <UINavigationControllerDelegate>

- (void) sendMailUsingInAppMailer:(const char *)score;
- (void) sendMailUsingExternalApp:(const char *)score;

@end
