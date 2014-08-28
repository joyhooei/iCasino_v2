#include "IOS.h"
#import "../cocos2dx/platform/ios/EAGLView.h" 

#import "MailSender.h"
#import "SendSMS.h"
#import "Image.h"
#import "MyFacebook.h"
#import "AppController.h"

void IOS::trySendAnEMail(const char *score, bool usingInternalApp)
{
    MailSender *mailSender = [MailSender alloc];
    if (usingInternalApp) {
        [mailSender sendMailUsingInAppMailer:score];
    }
    else{
        [mailSender sendMailUsingExternalApp:score];
    }
}
void IOS::trySendSMS()
{
    SendSMS *sms = [SendSMS alloc];
    
    [sms sendSMS:@"test" recipientList:[NSArray arrayWithObjects:@"0650454323",@"0434320943",@"0560984122", nil]];
    //[sms sendInAppSMS];
}
void IOS::tryOpenImage()
{
    Image *a = [Image alloc];
    [a openImage];
}
void IOS::loginFB()
{
    MyFacebook *fb = [MyFacebook alloc];
    [fb inviteFriends];
}
void IOS::turnOnAD()
{
    AppController* app = (AppController* )[[UIApplication sharedApplication] delegate];
    [app turnOnAD];
}
void IOS::turnOffAD()
{
    AppController* app = (AppController* )[[UIApplication sharedApplication] delegate];
    [app turnOffAD];
}
void IOS::showInterAD()
{
    AppController* app = (AppController* )[[UIApplication sharedApplication] delegate];
    [app showInterAD];
}






