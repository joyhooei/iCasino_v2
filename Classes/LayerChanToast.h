#ifndef __Chan___Toast___
#define __Chan___Toast___
#include "cocos2d.h"
#include "cocos-ext.h"
#include <iostream>

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class LayerChanToast : public CCLayer
{
public:
	static CCArray arrObject;
	static int count;
	static string curentString;
	~LayerChanToast();
	LayerChanToast(string mess);
	void showMessage(CCNode *target);
	void dissmiss(CCObject *sender);
	static void showToast(CCNode *target, string message, float duration);
	static void resetStaticVariables();
private:
	int count_mess;
	CCArray *Queue;
};

#endif