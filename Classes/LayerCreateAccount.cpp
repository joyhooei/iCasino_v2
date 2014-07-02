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
#include "LayerLogin.h"

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
	//
	GameServer::getSingleton().removeListeners(this);
	//CallBack
	if (m_callback && m_callbackListener){
		(m_callbackListener->*m_callback)();
	}
}

void LayerCreateAccount::notificationCallBack(bool isOK, int tag){
	CCLOG("callbackNtf****");
// 	this->setTouchEnabled(true);
// 	if( isOK ){
// 		LayerLogin* layer = SceneManager::getSingleton().getLayerLogin();
// 		layer->setUserAndPassInfo(txtUsername->getText(), txtPassword->getText());
// 	}
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
	//Validate
	if( strlen(txtUsername->getText())<6 ){
		Chat *toast = new Chat("Tài khoản phải lớn hơn 6 ký tự!", -1);
		this->addChild(toast);
		return;
	}
	if( strlen(txtPassword->getText())<6 ){
		Chat *toast = new Chat("Mật khẩu phải lớn hơn 6 ký tự!", -1);
		this->addChild(toast);
		return;
	}
	if( strcmp(txtPassword->getText(), txtRePassword->getText())!=0 ){
		Chat *toast = new Chat("Mật khẩu không trùng!", -1);
		this->addChild(toast);
		return;
	}
	if( strlen(txtEmail->getText())<6 ){
		Chat *toast = new Chat("Email không đúng!", -1);
		this->addChild(toast);
		return;
	}
	//regist
	//Send request
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("aI", txtUsername->getText());
	params->PutUtfString("aN", txtUsername->getText());
	params->PutUtfString("aP", txtPassword->getText());
	params->PutUtfString("aM", txtEmail->getText());
	params->PutInt("aT",  1);
	params->PutInt("aS", isMan?1:0);
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rr", params));
	GameServer::getSingleton().getSmartFox()->Send(request);
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
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if(strcmp("rg", cmd->c_str())==0){
		int rc = *param->GetInt("rc");
		if( rc==0 ){//OK
// 			LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
// 			if( !SceneManager::getSingleton().showNotification() ){
// 				CCLOG("NTF Dialog already open!");
// 				return;
// 			}
// 			CCLOG("lbfree OK");
			//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			LayerLogin* layerLogin = SceneManager::getSingleton().getLayerLogin();
			layerLogin->setUserAndPassInfo(txtUsername->getText(), txtPassword->getText());
			//
			Chat *toast = new Chat("ĐĂNG KÝ THÀNH CÔNG", -1);
			// 				this->removeFromParentAndCleanup(true);
			this->addChild(toast);
			//this->removeFromParentAndCleanup(true);
			//
// 			layer->setNotificationOptions("ĐĂNG KÝ THÀNH CÔNG", 
// 				CCString::createWithFormat("Bạn đã đăng ký tài khoản: %s\n thành công!\n Bạn có muốn đăng nhập ngay?", txtUsername->getText())->getCString()
// 				, true , "Có", 1, NULL );
		}else{//Not OK
			Chat *toast = new Chat(CCString::createWithFormat("ĐĂNG KÝ THẤt BAI \n%s", param->GetUtfString("rd")->c_str())->getCString(), -1);
// 				this->removeFromParentAndCleanup(true);
 			this->addChild(toast);
//				layer->setNotificationOptions("ĐĂNG KÝ THẤt BẠI", 
//					param->GetUtfString("rd")->c_str(), false , "", 1, this 			
		}
	}
}

void LayerCreateAccount::OnSmartFoxConnection( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	CCLOG("Register: OnSmartFoxConnection()");
	//send login
	doLogin();
}

void LayerCreateAccount::OnSmartFoxLogin( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	CCLOG("Register: OnSmartFoxLogin()");
}

void LayerCreateAccount::OnSmartFoxLoginError( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	CCLOG("Register: OnSmartFoxLoginError()");

	Chat *toast = new Chat("Có lỗi kết nối tới server đăng ký!", -1);
	this->removeFromParentAndCleanup(true);
	this->getParent()->addChild(toast);
}

void LayerCreateAccount::connect2RegistZone()
{
	try{
		GameServer::getSingleton().connectToServer(sIpAddress.c_str(), "9933");
	}catch(std::exception const&  ex)
	{
		LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
		if( !SceneManager::getSingleton().showNotification() ){
			CCLOG("NTF Dialog already open!");
			return;
		}
		layer->setNotificationOptions("Lỗi", "Không kết nối được tới server!", false , "", 1, NULL );
	}
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

void LayerCreateAccount::doLogin()
{
	//login zone when connect success
	boost::shared_ptr<IRequest> request (new LoginRequest("", "123456", "RegisterZone"));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerCreateAccount::setCallbackFunc( CCObject* target, SEL_CallFunc callfunc )
{
	m_callbackListener = target;
	m_callback = callfunc;  
}

void LayerCreateAccount::doConnect()
{
	if( GameServer::getSingleton().getSmartFox()->IsConnected() ){
		doLogin();
	}else{
		connect2RegistZone();
	}
}

void LayerCreateAccount::setIpAddress( string sip )
{
	sIpAddress = sip;
}
