//
//  MailSender.m
//  GetSocial
//
//  Created by Mikel Eizagirre on 24/03/13.
//
//

#import "MailSender.h"
#import "../cocos2dx/platform/ios/EAGLView.h"

@implementation MailSender

-(void) sendMailUsingExternalApp:(const char *)score
{
    NSString *message = [NSString stringWithFormat:@"<p>%s</p>",score];
    [self sendEmailTo:@""
               withCC:@""
              withBCC:@""
          withSubject:@"Play iCasino !"
             withBody:message];
}


- (void)sendEmailTo:(NSString*)to withCC:(NSString*)cc withBCC:(NSString*)bcc withSubject:(NSString*)subject withBody:(NSString*)body {
	NSString * url = [NSString stringWithFormat:@"mailto:?to=%@&cc=%@&bcc=%@&subject=%@&body=%@",
					  [to stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding],
					  [cc stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding],
					  [bcc stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding],
					  [subject stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding],
					  [body stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding]];
    
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
}

- (void)sendMailUsingInAppMailer:(const char *)score
{
    if ([MFMailComposeViewController canSendMail])
    {
        MFMailComposeViewController *mailer = [[MFMailComposeViewController alloc] init];
        AppController* appDelegate = (AppController* )[[UIApplication sharedApplication] delegate];
        RootViewController* root = [appDelegate viewController];
        mailer.mailComposeDelegate = root;
        
        [mailer setSubject:@"Play iCasino !"];
        
        NSString *emailBody = [NSString stringWithFormat:@"<p>%s!</p>",score];

        [mailer setMessageBody:emailBody isHTML:YES];
        
        [root presentViewController:mailer animated:YES completion:^{}];

        
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Thất bại"
                                                        message:@"Thiết bị không hỗ trợ !"
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles: nil];
        [alert show];
        [alert release];
    }
    
}



@end
