//
//  LayerCreateAccount.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerCreateAccount.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"
#include "Requests/LoginRequest.h"
#include "Requests/LogoutRequest.h"
#include "_Chat_.h"
#include "SceneManager.h"
#include <string.h>

using namespace cocos2d;
//using namespace CocosDenshion;


LayerCreateAccount::LayerCreateAccount()
{
    isMan = true;
    txtUsername=NULL;
    txtPassword=NULL;
    txtRePassword=NULL;
    txtPhone=NULL;
    txtEmail=NULL;

}

LayerCreateAccount::~LayerCreateAccount()
{

	boost::shared_ptr<IRequest> request (new LogoutRequest());

	GameServer::getSingleton().getSmartFox()->Send(request);
	if( GameServer::getSingleton().getSmartFox() == NULL) 
		return;
	GameServer::getSingleton().removeListeners(this);
}

void LayerCreateAccount::notificationCallBack(bool isOK, int tag){
	CCLOG("callbackNtf****");
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerCreateAccount::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnSex", LayerCreateAccount::onButtonSex);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerCreateAccount::onButtonClose);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCreate", LayerCreateAccount::onButtonCreate);
    return NULL;
}

void LayerCreateAccount::onButtonSex(CCObject* pSender)
{
    CCMenuItemImage* btn = (CCMenuItemImage*)pSender;
    if( btn->getPositionX()==140 ){
        //disabling, switch to enable
        btn->setPosition(ccp(198, btn->getPositionY()));
        isMan = false;
    }else{
        //else
        btn->setPosition(ccp(140, btn->getPositionY()));
        isMan = true;
    }
    CCLOG("onButtonSex isMan: %s", isMan?"true":"false");
}

void LayerCreateAccount::onButtonCreate(CCObject* pSender)
{
	
}


void LayerCreateAccount::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
    this->removeFromParentAndCleanup(true);
}

// CCBMemberVariableAssigner interface
bool LayerCreateAccount::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtEmail", CCEditBox*, txtEmail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtPassword", CCEditBox*, txtPassword);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtUsername", CCEditBox*, txtUsername);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtPhone", CCEditBox*, txtPhone);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtRePassword", CCEditBox*, txtRePassword);
    return true;
}

void LayerCreateAccount::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    //Init textfield
    initTextField(txtEmail, "Email");
    txtEmail->setInputMode(kEditBoxInputModeEmailAddr);
    initTextField(txtUsername, "Tên đăng nhập");
    initTextField(txtPassword, "Mật khẩu");
    txtPassword->setInputFlag(kEditBoxInputFlagPassword);
    initTextField(txtRePassword, "Gõ lại mật khẩu");
    txtRePassword->setInputFlag(kEditBoxInputFlagPassword);
    initTextField(txtPhone, "Điện thoại");
    txtPhone->setInputMode(kEditBoxInputModePhoneNumber);
	//
	txtEmail->setText("a@a.com");
	txtPassword->setText("123456");
	txtPhone->setText("1234567890");
	txtRePassword->setText("123456");
	txtUsername->setText("hoangdd1");
	//Init game server with zone Regist
	GameServer::getSingleton().addListeners(this);
	this->setTouchEnabled(true);
	//registerWithTouchDispatcher();
    return;
}

void LayerCreateAccount::initTextField(CCEditBox* txt, const char* hintText){
    txt->setFontColor(ccBLACK);
    txt->setPlaceholderFontColor(ccBLACK);
    txt->setFont("fonts/Roboto-Regular.ttf", 18);
    txt->setReturnType(kKeyboardReturnTypeDefault);
	txt->setPlaceHolder(hintText);
	txt->setTouchPriority(-128);
	txt->setInputMode(kEditBoxInputModeAny);
}

void LayerCreateAccount::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	
}

void LayerCreateAccount::OnSmartFoxConnection( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	CCLOG("Register: OnSmartFoxConnection()");
	//send login

	boost::shared_ptr<IRequest> request (new LoginRequest("", "", "RegisterZone"));

	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerCreateAccount::OnSmartFoxLogin( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	CCLOG("Register: OnSmartFoxLogin()");
}

void LayerCreateAccount::connect2RegistZone()
{
	GameServer::getSingleton().connectToServer("bestteam.no-ip.biz", "9933");
}

void LayerCreateAccount::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerCreateAccount::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerCreateAccount::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerCreateAccount::onExit()
{
	CCLayer::onExit();
}
