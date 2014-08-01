//
//  _Number_inGame_.h
//  iCasino_v2
//
//  Created by Thanhhv on 5/16/14.
//
//

#ifndef __iCasino_v2___Number_Chat_inGame7u__
#define __iCasino_v2___Number_Chat_inGame7u__

#include <iostream>

#include "cocos2d.h"
#include "AllData.h"
#include "_Number_.h"

using namespace std;
using namespace cocos2d;

class Number_Chat_inGame7u : public CCLayer
{
private:
    vector<int> arrPos;
    vector<string> arrNumberString;
	vector<double> arrNumberDouble;
	bool isRunning;
    
public:
	~Number_Chat_inGame7u();
    bool init();
    CREATE_FUNC(Number_Chat_inGame7u);
    
    void showNumberByPos(int pos, string numberString);
	void showNumberByPos(int pos, double numberDouble);
	void runAction(float dt);
	void runAction2(float dt);
    void callbackShowNumber(float dt);
    void showChatByPos(int pos, string mes);
};

#endif /* defined(__iCasino_v2___Number_inGame___) */
