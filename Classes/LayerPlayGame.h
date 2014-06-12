//
//  LayerPlayGame.h
//  iCasino_v2
//
//  Created by Thanhhv on 5/14/14.
//
//

#ifndef __iCasino_v2__LayerPlayGame__
#define __iCasino_v2__LayerPlayGame__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "AllData.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class LayerPlayGame : public CCLayer
{
private:
    CCLabelTTF *titleGame;

public:
    LayerPlayGame();
    ~LayerPlayGame();
    
    CREATE_FUNC(LayerPlayGame);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    
    void onTouchButton(CCObject *pSender, TouchEventType pType);
    void setTitleGame(char *ti);
};

#endif /* defined(__iCasino_v2__LayerPlayGame__) */
