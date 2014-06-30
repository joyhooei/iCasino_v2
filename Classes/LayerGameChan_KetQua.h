//
//  LayerGameChan_KetQua.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerGameChan_KetQua_h
#define demo_LayerGameChan_KetQua_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerGameChan_KetQua
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
private:
	CCLabelTTF *lblThongBao;
	CCLabelTTF* lblMoney;
public:
	LayerGameChan_KetQua();
	virtual ~LayerGameChan_KetQua();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(LayerGameChan_KetQua);

	// CCBSelectorResolver interfaces
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
	// selector callbacks
	void onButtonXemNoc(CCObject* pSender);
};

class LayerGameChan_KetQuaLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerGameChan_KetQuaLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerGameChan_KetQua);
};

#endif
