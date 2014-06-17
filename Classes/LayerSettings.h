//
//  LayerSettings.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerSettings_h
#define demo_LayerSettings_h


#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerSettings
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    cocos2d::CCLabelTTF *lblMoney;
    CCControlSlider* sliderMoney;
    cocos2d::extension::CCEditBox* txtPassword;
    CCSprite* spriteMoney;

	CCMenuItem* btnVibrate;
	CCMenuItem* btnSound;
public:
    LayerSettings();
	virtual ~LayerSettings();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	void saveInfo();
	void getInfo();
    
    CREATE_FUNC(LayerSettings);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
    // selector callbacks
    void onButtonSound(CCObject* pSender);
    void onButtonVibrate(CCObject* pSender);
    void onButtonClose(CCObject* pSender);
};

class LayerSettingsLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerSettingsLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerSettings);
};

#endif
