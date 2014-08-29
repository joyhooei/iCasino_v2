//PrintMessage.h
#ifndef __PRINTMESSAGE_H__
#define __PRINTMESSAGE_H__

#include <stddef.h>

class IOS
{
public:
    static void turnOnAD();
    static void turnOffAD();
    static void showInterAD();
    static void trySendAnEMail(const char *score, bool usingInternalApp);
    static void loginFB();
    static bool tryIsInternetConnection();
    static void trySendSMS();
    static void tryOpenImage();
    static void inviteFB();

};

#endif//__PRINTMESSAGE_H__