//
//  _Chat_.h
//  testcpp2605
//
//  Created by Thanhhv on 5/27/14.
//
//

#ifndef __testcpp2605___Chat___
#define __testcpp2605___Chat___

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "AllData.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

class Chat : public CCLayer {
private:
    string mes;
    int posUser;
    CCSize sizeThis;
    
public:
    Chat(string pMes, int posUser);
    virtual bool init();
    
    void setStatusByServer(bool isServer);
    
    CCSize getSize();
    void formatMes();
    void releaseSafe();
};

#endif /* defined(__testcpp2605___Chat___) */
