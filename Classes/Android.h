/*
 * Android.h
 *create by Tuan 8/7/2014
 */
 
#ifndef ANDROID_H_
#define ANDROID_H_



extern "C"
{
    extern void sendSMS(const char* phoneNum ,const char* mess);
	extern void openURL(const char* url);
	extern void sendEmail(const char* address, const char* subject, const char* mail);
	extern void openImage();
	extern void camera();
	extern void loginFB();
	extern void shareFB();
	extern void inviteFB();
}
 
#endif /* ANDROID_H_ */ 
