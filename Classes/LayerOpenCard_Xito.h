//
//  LayerOpenCard_Xito.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerOpenCard_Xito_h
#define demo_LayerOpenCard_Xito_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
#include "GameServer.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;
using namespace Sfs2X;

class LayerOpenCard_Xito
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
private:
	CCMenuItem* btnCard1;
	CCMenuItem* btnCard2;
	string arrCardTypes[4];
public:
	LayerOpenCard_Xito();
	virtual ~LayerOpenCard_Xito();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(LayerOpenCard_Xito);

	// CCBSelectorResolver interfaces
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
	// selector callbacks
	void onButtonCard1(CCObject* pSender);
	void onButtonCard2(CCObject* pSender);
	void setDealCards(string listDeal);
	string convertCard(string strCard);
	string findtypeCard(string listCards);
	vector<string> Dsplit(string &S,const char &str);
	void sendOpenCards(int cardIdx);
};

class LayerOpenCard_XitoLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerOpenCard_XitoLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerOpenCard_Xito);
};

#endif
