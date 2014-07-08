

#include "Android.h"
#include "platform/android/jni/JniHelper.h"

using namespace cocos2d;

extern "C"
{

	void sendSMS(const char* phoneNum, const char* mess)
	{
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t,
			"com/game/simple/Game3",    // fully qualified class name
			"sendSMS",                              // method name
			"(Ljava/lang/String;Ljava/lang/String;)V")) {             // data type of argument

				// jstring - C++ representation of Java String
				jstring _phoneNum = t.env->NewStringUTF(phoneNum);
				jstring _mess = t.env->NewStringUTF(mess);
				// call the method, with arguments
				t.env->CallStaticVoidMethod(t.classID, t.methodID, _phoneNum, _mess);
		}
	}
	void openURL(const char* url)
	{
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t,
			"com/game/simple/Game3",    // fully qualified class name
			"openURL",                              // method name
			"(Ljava/lang/String;)V")) {             // data type of argument

				// jstring - C++ representation of Java String
				jstring _url = t.env->NewStringUTF(url);

				// call the method, with arguments
				t.env->CallStaticVoidMethod(t.classID, t.methodID,_url);
		}
	}
	void sendEmail(const char* address, const char* subject, const char* content)
	{
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t,
			"com/game/simple/Game3",    // fully qualified class name
			"sendEmail",                              // method name
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {             // data type of argument

				// jstring - C++ representation of Java String
				jstring _address = t.env->NewStringUTF(address);
				jstring _subject = t.env->NewStringUTF(subject);
				jstring _content = t.env->NewStringUTF(content);
				// call the method, with arguments
				t.env->CallStaticVoidMethod(t.classID, t.methodID, _address,_subject, _content);
		}
	}
	void openImage()
	{
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t,
			"com/game/simple/Game3",    // fully qualified class name
			"openImage",                              // method name
			"()V")) {             // data type of argument

				// jstring - C++ representation of Java String

				// call the method, with arguments
				t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
	}
	void camera()
	{
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t,
			"com/game/simple/Game3",    // fully qualified class name
			"camera",                              // method name
			"()V")) {             // data type of argument

				// jstring - C++ representation of Java String

				// call the method, with arguments
				t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
	}
	void loginFB()
	{
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t,
			"com/game/simple/Game3",    // fully qualified class name
			"loginFB",                              // method name
			"()V")) {             // data type of argument

				// jstring - C++ representation of Java String

				// call the method, with arguments
				t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
	}
	void shareFB()
	{
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t,
			"com/game/simple/Game3",    // fully qualified class name
			"shareFB",                              // method name
			"()V")) {             // data type of argument

				// jstring - C++ representation of Java String

				// call the method, with arguments
				t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
	}
	void inviteFB()
	{
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t,
			"com/game/simple/Game3",    // fully qualified class name
			"inviteFB",                              // method name
			"()V")) {             // data type of argument

				// jstring - C++ representation of Java String

				// call the method, with arguments
				t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
}
}
