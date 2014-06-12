//
//  LayerPasswordRoom.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerPasswordRoom.h"
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerPasswordRoom::LayerPasswordRoom()
{
    txtPassword = NULL;
}

LayerPasswordRoom::~LayerPasswordRoom()
{
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerPasswordRoom::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerPasswordRoom::onButtonClose);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnConfirm", LayerPasswordRoom::onButtonConfirm);
    return NULL;
}

void LayerPasswordRoom::onButtonConfirm(CCObject* pSender)
{
    CCLOG("onButtonConfirm");
}


void LayerPasswordRoom::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
}

// CCBMemberVariableAssigner interface
bool LayerPasswordRoom::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtPassword", CCEditBox*, txtPassword);
    return true;
}

void LayerPasswordRoom::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	CCLOG("Imhere onNodeLoaded");
	//
	this->setTouchEnabled(true);
// 	initTextField(txtPassword, "Mật khẩu");
// 	txtPassword->setInputFlag(kEditBoxInputFlagSensitive    
	return;
}

void LayerPasswordRoom::initTextField(CCEditBox* txt, const char* hintText){
	txt->setFontColor(ccBLACK);
	txt->setPlaceholderFontColor(ccBLACK);
	txt->setFont("fonts/Roboto-Regular.ttf", 18);
	txt->setReturnType(kKeyboardReturnTypeDefault);
	txt->setPlaceHolder(hintText);
	txt->setTouchPriority(-128);
}

void LayerPasswordRoom::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerPasswordRoom::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerPasswordRoom::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerPasswordRoom::onExit()
{
	CCLayer::onExit();
}
