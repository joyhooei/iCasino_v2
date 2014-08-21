//
//  LayerEmailDetails.h
//  iCasino_v2
//
//  Created by HoangDD on 5/15/14.
//
//  Create buttons: Back, Seting, Chat, Coin in a Game
//  This is a CCLayer:
// anchorPoint = 0, 0
// position = 0, 0
//

#ifndef __iCasino_v2___LayerEmailDetails___
#define __iCasino_v2___LayerEmailDetails___

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerEmailDetails
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
private:
	CCLabelTTF* lblTitle;
	CCLabelTTF* lblDate;
	CCLabelTTF* lblContents;

public:
	LayerEmailDetails();
	virtual ~LayerEmailDetails();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	void initTextField(CCEditBox* txt, const char* hintText);

	CREATE_FUNC(LayerEmailDetails);

	// CCBSelectorResolver interfaces
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};

	// selector callbacks
	void onButtonDelete(CCObject* pSender);
	void onButtonReply(CCObject* pSender);
};

class LayerEmailDetailsLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerEmailDetailsLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerEmailDetails);
};

#endif /* defined(__iCasino_v2___LayerEmailDetails___) */
