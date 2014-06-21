//
//  LayerGameChan_KetQua.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerGameChan_KetQua.h"
#include "GameServer.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"

using namespace Sfs2X;
using namespace cocos2d;
//using namespace CocosDenshion;


LayerGameChan_KetQua::LayerGameChan_KetQua()
{
	lblThongBao=NULL;
	lblMoney=NULL;
}

LayerGameChan_KetQua::~LayerGameChan_KetQua()
{
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerGameChan_KetQua::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnXemNoc", LayerGameChan_KetQua::onButtonXemNoc);
	return NULL;
}

void LayerGameChan_KetQua::onButtonXemNoc(CCObject* pSender)
{
	CCLOG("onButtonXemNoc");
	this->removeFromParentAndCleanup(true);
}

// CCBMemberVariableAssigner interface
bool LayerGameChan_KetQua::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblThongBao", CCLabelTTF *, lblThongBao);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
	return true;
}

void LayerGameChan_KetQua::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	CCLOG("Imhere onNodeLoaded");

	this->setTouchEnabled(true);
}

void LayerGameChan_KetQua::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerGameChan_KetQua::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerGameChan_KetQua::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerGameChan_KetQua::onExit()
{
	CCLayer::onExit();
}