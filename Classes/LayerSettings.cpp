//
//  LayerSettings.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerSettings.h"
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerSettings::LayerSettings()
{
    lblMoney=NULL;
    sliderMoney=NULL;
    txtPassword=NULL;
    spriteMoney=NULL;
}

LayerSettings::~LayerSettings()
{
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerSettings::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCLOG("onResolveCCBCCMenuItemSelector");
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnSound", LayerSettings::onButtonSound);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnVibrate", LayerSettings::onButtonVibrate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerSettings::onButtonClose);
    return NULL;
}

void LayerSettings::onButtonSound(CCObject* pSender)
{
    CCLOG("onButtonSound");
    CCMenuItemImage* btn = (CCMenuItemImage*)pSender;
    CCLOG("onButtonSound x:%f", btn->getPositionX());
    if( btn->getPositionX()==211 ){
        //disabling, switch to enable
        btn->setPosition(ccp(270, btn->getPositionY()));
    }else{
        //else
        btn->setPosition(ccp(211, btn->getPositionY()));
    }
}

void LayerSettings::onButtonVibrate(CCObject* pSender)
{
    CCLOG("onButtonVibrate");
    CCMenuItemImage* btn = (CCMenuItemImage*)pSender;
    CCLOG("onButtonSound x:%f", btn->getPositionX());
    if( btn->getPositionX()==211 ){
        //disabling, switch to enable
        btn->setPosition(ccp(270, btn->getPositionY()));
    }else{
        //else
        btn->setPosition(ccp(211, btn->getPositionY()));
    }
}

void LayerSettings::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
    this->removeFromParent();
}

// CCBMemberVariableAssigner interface
bool LayerSettings::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    return true;
}

void LayerSettings::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	//
	this->setTouchEnabled(true);
    return;
}

void LayerSettings::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerSettings::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerSettings::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerSettings::onExit()
{
	CCLayer::onExit();
}

void LayerSettings::saveInfo()
{
// 	CCUserDefault *def=CCUserDefault::sharedUserDefault();
// 	def->setStringForKey("username", txtUsername->getText());
// 	def->setStringForKey("password", txtPassword->getText());

//	def->flush();
}

void LayerSettings::getInfo()
{
	CCUserDefault *def=CCUserDefault::sharedUserDefault();
	bool isSoundOn = def->getBoolForKey("sound", true);
	bool isVibrateOn = def->getBoolForKey("vibrate", true);
}
