//
//  LayerEmailDetails.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerEmailDetails.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"
#include "LayerMain.h"
#include "_Chat_.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerEmailDetails::LayerEmailDetails()
{
	lblTitle = NULL;
	lblDate = NULL;
	lblContents = NULL;

	m_idMsg = -1;
	//
	GameServer::getSingleton().addListeners(this);
}

LayerEmailDetails::~LayerEmailDetails()
{
	CC_SAFE_RELEASE(lblTitle);
	CC_SAFE_RELEASE(lblDate);
	CC_SAFE_RELEASE(lblContents);
	//
	GameServer::getSingleton().removeListeners(this);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerEmailDetails::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	CCLOG("onResolveCCBCCMenuItemSelector %s", pSelectorName);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnReply", LayerEmailDetails::onButtonReply);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnDelete", LayerEmailDetails::onButtonDelete);
	return NULL;
}

void LayerEmailDetails::onButtonDelete(CCObject* pSender)
{
	//DeleteMessageInner: dmi
	//aI: account Id
	//miid: messages Id
	boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
	//Send request
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("aI", myself->Name());
	params->PutLong("miid", m_idMsg);
	boost::shared_ptr<IRequest> request (new ExtensionRequest("dmi", params));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerEmailDetails::onButtonReply(CCObject* pSender)
{
	boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
	if( strcmp( myself->Name()->c_str(), m_fromUser.c_str()) == 0 ){
		Chat *toast = new Chat("Bạn không thể trả lời thư này!", -1);
		this->getParent()->addChild(toast);
		return;
	}
	LayerMain::getSingleton().gotoComposeMail(m_fromUser, "Trả lời", lblContents->getString());
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

void LayerEmailDetails::setDatas( int idMsg, string fromUser, string toUser, string date, string contents )
{
	boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
	if( strcmp( myself->Name()->c_str(), fromUser.c_str()) == 0 ){
		lblTitle->setString( CCString::createWithFormat( "Thư gửi tới %s", toUser.c_str() )->getCString() );
	}else
		lblTitle->setString( CCString::createWithFormat( "Thư nhận được từ %s", fromUser.c_str() )->getCString() );
	lblContents->setString( contents.c_str() );
	lblDate->setString( CCString::createWithFormat( "Người gửi: %s / Gửi tới: %s / Ngày gửi: %s", fromUser.c_str(), toUser.c_str(), date.c_str() )->getCString() );
	m_idMsg = idMsg;
	m_fromUser = fromUser;
	m_toUser = toUser;
}

void LayerEmailDetails::OnExtensionResponse( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if(strcmp("dmi", cmd->c_str())==0){ //dmi response
		LayerMain::getSingleton().gotoMail();
	}
}
