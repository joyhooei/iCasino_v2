//
//  LayerNotification.cpp
//  demo
//
//  Created by AlexDao on 5/30/14.
//
//

#include "LayerNotification.h"
#include "SceneManager.h"
#include "mUtils.h"
using namespace cocos2d;
//using namespace CocosDenshion;


LayerNotification::LayerNotification()
{
    lblCancel = NULL;
    lblDetails = NULL;
    lblOK = NULL;
    lblTitle = NULL;
    btnCancel = NULL;
    btnOK = NULL;

	currTag = -1;
}

LayerNotification::~LayerNotification()
{
}

void LayerNotification::setTitle(const char* title){
	lblTitle->setString(title);
}

void LayerNotification::setMessage(const char* msg){
	lblDetails->setString(msg);
}

void LayerNotification::setTwoButton(bool isTwoButton){
	btnOK->setVisible(isTwoButton);
	lblOK->setVisible(isTwoButton);

	CCLOG("posX: %lf", lblCancel->getPositionX());

	btnCancel->setPositionX( isTwoButton?191:130 );
	lblCancel->setPositionX( isTwoButton?247:187 );
}

void LayerNotification::addListeners( NotificationCallBack * callBack )
{
	mCallBack.clear();
	if ( callBack == NULL )
		return;

	mCallBack.insert(NotificationCallBackMapPair(mCallBackIndex++,callBack));
}


void LayerNotification::setButtonOkTitle(const char* title){
	lblOK->setString(title);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerNotification::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    //CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCancel", LayerNotification::onButtonCancelClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnOK", LayerNotification::onButtonOKClick);
    return NULL;
}
void LayerNotification::onButtonCancelClick(CCObject* pSender){
    //this->removeFromParent();
	//callback
	NotificationCallBackMapIter iTer = mCallBack.begin();
	for ( ; iTer != mCallBack.end() ; iTer ++ ){
		iTer->second->notificationCallBack(false, currTag);
	}
	//Hide this
	SceneManager::getSingleton().hideNotification();
}
void LayerNotification::onButtonOKClick(CCObject* pSender)
{
	NotificationCallBackMapIter iTer = mCallBack.begin();
	for ( ; iTer != mCallBack.end() ; iTer ++ ){
		iTer->second->notificationCallBack(true, currTag);
	}

	SceneManager::getSingleton().hideNotification();
}

// CCBMemberVariableAssigner interface
bool LayerNotification::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblCancel", CCLabelTTF *, lblCancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblOK", CCLabelTTF *, lblOK);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblDetails", CCLabelTTF *, lblDetails);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle", CCLabelTTF *, lblTitle);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnOK", CCMenuItem *, btnOK);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnCancel", CCMenuItem *, btnCancel);
    return true;
}

void LayerNotification::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    return;
}

void LayerNotification::setTag( int tag )
{
	currTag = tag;
}

void LayerNotification::setNotificationOptions( const char* title, const char* msg, bool isTwoButton, const char* titleButtonOK, int tag, NotificationCallBack * callBack )
{
	setTitle(title);
	setMessage(msg);
	setTwoButton(isTwoButton);
	setButtonOkTitle(titleButtonOK);
	setTag(tag);
	addListeners(callBack);
}

void LayerNotification::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerNotification::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerNotification::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerNotification::onExit()
{
	CCLayer::onExit();
}
