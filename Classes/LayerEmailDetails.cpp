//
//  LayerEmailDetails.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerEmailDetails.h"
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerEmailDetails::LayerEmailDetails()
{
	lblTitle = NULL;
	lblDate = NULL;
	lblContents = NULL;
}

LayerEmailDetails::~LayerEmailDetails()
{
	CC_SAFE_RELEASE(lblTitle);
	CC_SAFE_RELEASE(lblDate);
	CC_SAFE_RELEASE(lblContents);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerEmailDetails::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerEmailDetails::onButtonReply);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnReply", LayerEmailDetails::onButtonDelete);
	return NULL;
}

void LayerEmailDetails::onButtonDelete(CCObject* pSender)
{
	CCLOG("onButtonFind");
}


void LayerEmailDetails::onButtonReply(CCObject* pSender)
{
	CCLOG("onButtonClose");
	this->removeFromParentAndCleanup(true);
}

// CCBMemberVariableAssigner interface
bool LayerEmailDetails::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle", CCLabelTTF*, lblTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblDate", CCLabelTTF*, lblDate);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblContents", CCLabelTTF*, lblContents);
	return true;
}

void LayerEmailDetails::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
// 	CCLOG("Imhere onNodeLoaded");
// 	initTextField(txtUsername, "Tên tài khoản");
// 	//
// 	this->setTouchEnabled(true);
	return;
}

void LayerEmailDetails::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerEmailDetails::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerEmailDetails::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerEmailDetails::onExit()
{
	CCLayer::onExit();
}

void LayerEmailDetails::initTextField( CCEditBox* txt, const char* hintText )
{
	txt->setFontColor(ccBLACK);
	txt->setPlaceholderFontColor(ccBLACK);
	txt->setFont("fonts/Roboto-Regular.ttf", 18);
	txt->setReturnType(kKeyboardReturnTypeDefault);
	txt->setInputFlag(kEditBoxInputFlagSensitive);
	txt->setPlaceHolder(hintText);
	txt->setTouchPriority(-128);
}
