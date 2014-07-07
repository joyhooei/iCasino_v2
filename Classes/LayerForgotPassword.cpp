//
//  LayerForgotPassword.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerForgotPassword.h"
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerForgotPassword::LayerForgotPassword()
{
    txtUsername = NULL;
}

LayerForgotPassword::~LayerForgotPassword()
{
	CC_SAFE_RELEASE(txtUsername);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerForgotPassword::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerForgotPassword::onButtonClose);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnFind", LayerForgotPassword::onButtonFind);
    return NULL;
}

void LayerForgotPassword::onButtonFind(CCObject* pSender)
{
    CCLOG("onButtonFind");
}


void LayerForgotPassword::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
	this->removeFromParentAndCleanup(true);
}

// CCBMemberVariableAssigner interface
bool LayerForgotPassword::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtUsername", CCEditBox*, txtUsername);
    return true;
}

void LayerForgotPassword::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
	initTextField(txtUsername, "Tên tài khoản");
	//
	this->setTouchEnabled(true);
    return;
}

void LayerForgotPassword::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerForgotPassword::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerForgotPassword::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerForgotPassword::onExit()
{
	CCLayer::onExit();
}

void LayerForgotPassword::initTextField( CCEditBox* txt, const char* hintText )
{
	txt->setFontColor(ccBLACK);
	txt->setPlaceholderFontColor(ccBLACK);
	txt->setFont("fonts/Roboto-Regular.ttf", 18);
	txt->setReturnType(kKeyboardReturnTypeDefault);
	txt->setPlaceHolder(hintText);
	txt->setTouchPriority(-128);
}
