//
//  LayerBet_BaCayChuong.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerBet_BaCayChuong_h
#define demo_LayerBet_BaCayChuong_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerBet_BaCayChuong
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
	LayerBet_BaCayChuong();
	virtual ~LayerBet_BaCayChuong();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(LayerBet_BaCayChuong);

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
};

class LayerBet_BaCayChuongLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerBet_BaCayChuongLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerBet_BaCayChuong);
};

#endif
