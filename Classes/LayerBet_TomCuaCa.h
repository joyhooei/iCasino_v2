//
//  LayerBet_TomCuaCa.h
//  demo
//
//  Created by Tuan on 6/25/14.
//
//

#ifndef demo_LayerBet_TomCuaCa_h
#define demo_LayerBet_TomCuaCa_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerBet_TomCuaCa
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
private:
	CCLabelTTF *lblMoney;
	CCControlSlider* sliderMoney;
	CCSprite* spriteMoney;
public:
	int _tag;
	LayerBet_TomCuaCa();
	virtual ~LayerBet_TomCuaCa();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(LayerBet_TomCuaCa);

	// CCBSelectorResolver interfaces
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
	// selector callbacks
	void onButtonCreate(CCObject* pSender);
	void onButtonClose(CCObject* pSender);

	void valueChanged(CCObject *sender, CCControlEvent controlEvent);
	int getAID(int _mtag);
};

class LayerBet_TomCuaCaLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerBet_TomCuaCaLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerBet_TomCuaCa);
};

#endif
