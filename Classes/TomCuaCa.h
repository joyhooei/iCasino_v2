#ifndef __TOMCUACA_SCENE_H__
#define __TOMCUACA_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;


#define _kqNai 100
#define _kqRuou 95.8 
#define _kqGa 91.75 
#define _kqCa 87.45
#define _kqCua 83.27
#define _kqTom 79.2
class TomCuaCa : public cocos2d::CCLayer
{
private:
	int _count;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
	void click(CCObject* pSender, TouchEventType type);
    
	UILoadingBar *loadingBar;

	CREATE_FUNC(TomCuaCa);
	void update(float dt);
};

#endif
