//
//  SMS
//  GetSocial
//
//  Created by Tuan on 24/03/13.
//
//
#import "SendSMS.h"


@implementation SendSMS

-(void) sendInAppSMS
{//check if the device can send text messages
    if(![MFMessageComposeViewController canSendText]) {
        UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Thiết bị không hỗ trợ!" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
        return;
    }
    
    //set receipients
    NSArray *recipients = [NSArray arrayWithObjects:@"",@"",@"", nil];
    
    //set message text
    NSString * message = @"Let's play iCasino with me! ";
    
    MFMessageComposeViewController *messageController = [[MFMessageComposeViewController alloc] init];
    AppController* appDelegate = (AppController* )[[UIApplication sharedApplication] delegate];
    RootViewController* root = [appDelegate viewController];
    messageController.messageComposeDelegate = root;
    [messageController setRecipients:recipients];
    [messageController setBody:message];
    
    [root presentViewController:messageController animated:YES completion:^{}];
    
}


- (void)sendSMS:(NSString *)bodyOfMessage recipientList:(NSArray *)recipients
{
    MFMessageComposeViewController *messageController = [[[MFMessageComposeViewController alloc] init] autorelease];
    if([MFMessageComposeViewController canSendText])
    {
        messageController.body = bodyOfMessage;
		messageController.recipients = recipients;
        AppController* appDelegate = (AppController* )[[UIApplication sharedApplication] delegate];
        RootViewController* root = [appDelegate viewController];
        messageController.messageComposeDelegate = root;
        [root presentViewController:messageController animated:YES completion:^{}];
    }
}


@end
