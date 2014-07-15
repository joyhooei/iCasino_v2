//
//  LayerInviteFriends.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerInviteFriends.h"
#include "GameServer.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"
#include "platform/android/jni/Android.h"

using namespace Sfs2X;
using namespace cocos2d;

//using namespace CocosDenshion;

LayerInviteFriends::LayerInviteFriends()
{
	lblThongBao=NULL;
	lblMoney=NULL;
	
}

LayerInviteFriends::~LayerInviteFriends()
{
	CCLOG("LayerInviteFriends::~LayerInviteFriends()");
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerInviteFriends::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	//CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnFacebook", LayerInviteFriends::onButtonFacebook);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnGmail", LayerInviteFriends::onButtonGmail);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnSMS", LayerInviteFriends::onButtonSMS);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerInviteFriends::onButtonClose);
	return NULL;
}

void LayerInviteFriends::onButtonFacebook(CCObject* pSender){
	CCLOG("onButtonFacebook");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	inviteFB();
#else
	CCLog("Ko ho tro nen tang nay !");
#endif

}
void LayerInviteFriends::onButtonGmail(CCObject* pSender){
	CCLOG("onButtonGmail");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	sendEmail("","Play iCasino","Play with meeee");
#else
	CCLog("Ko ho tro nen tang nay !");
#endif

}
void LayerInviteFriends::onButtonSMS(CCObject* pSender){
	CCLOG("onButtonSMS");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	sendSMS("","Play iCasino with me!");
#else
	CCLog("Ko ho tro nen tang nay !");
#endif
}

void LayerInviteFriends::onButtonClose(CCObject* pSender){
	CCLOG("onButtonClose");
	this->removeFromParentAndCleanup(true);
}

// CCBMemberVariableAssigner interface
bool LayerInviteFriends::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	//CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblThongBao", CCLabelTTF *, lblThongBao);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
	return true;
}

void LayerInviteFriends::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	CCLOG("Imhere onNodeLoaded");

	this->setTouchEnabled(true);
}

void LayerInviteFriends::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerInviteFriends::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerInviteFriends::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerInviteFriends::onExit()
{
	CCLayer::onExit();
}
