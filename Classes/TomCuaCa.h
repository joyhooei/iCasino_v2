#ifndef __TOMCUACA_SCENE_H__
#define __TOMCUACA_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

#include "AllData.h"
#include "GameServer.h"
//
#include "_Background_inGame_.h"
#include "_Button_inGame_.h"
#include "_Avatar_inGame_.h"
#include "_Number_inGame_.h"
#include "_Card_inGame_.h"
#include "_Chat_inGame_.h"

#include "Requests/ExtensionRequest.h"

#include "SceneManager.h"
#include "mUtils.h"
using namespace cocos2d::extension;

#define _kqNai 100
#define _kqRuou 95.8 
#define _kqGa 91.75 
#define _kqCa 87.45
#define _kqCua 83.27
#define _kqTom 79.2
class TomCuaCa : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
	void click(CCObject* pSender, ui::TouchEventType type);
    
    // implement the "static node()" method manually
	CREATE_FUNC(TomCuaCa);
	
};

#endif
