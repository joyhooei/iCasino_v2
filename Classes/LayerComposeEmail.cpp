//
//  LayerComposeEmail.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerComposeEmail.h"
#include "mUtils.h"
#include "Requests/ExtensionRequest.h"
#include "LayerMain.h"
#include "_Chat_.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerComposeEmail::LayerComposeEmail()
{
	nodeTitle = NULL;
	nodeTo = NULL;
	nodeContents = NULL;
	nodeTextContent = NULL;
	//
	GameServer::getSingleton().addListeners(this);
}

LayerComposeEmail::~LayerComposeEmail()
{
	CC_SAFE_RELEASE(nodeTitle);
	CC_SAFE_RELEASE(nodeTo);
	CC_SAFE_RELEASE(nodeContents);
	CC_SAFE_RELEASE(nodeTextContent);
	//
	GameServer::getSingleton().removeListeners(this);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerComposeEmail::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
 	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnSend", LayerComposeEmail::onButtonSend);
	return NULL;
}

void LayerComposeEmail::onButtonFind(CCObject* pSender)
{
	CCLOG("onButtonFind");
}


void LayerComposeEmail::onButtonSend(CCObject* pSender)
{
	boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
	if( strcmp( myself->Name()->c_str(), txtTo->getText()) == 0 || strlen( txtTo->getText() ) < 6 ){
		Chat *toast = new Chat("Người nhận không đúng!", -1);
		this->addChild(toast);
		return;
	}
	if( strlen( txtContent->getText() ) == 0 ){
		Chat *toast = new Chat("Nội dung không được để trống!", -1);
		this->addChild(toast);
		return;
	}

	//sendmi: Send message
	//aI 
	// aR
	// scontent
	//Send request
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("aR", txtTo->getText());
	params->PutUtfString("scontent", txtContent->getText());
	params->PutUtfString("aI", myself->Name());
	boost::shared_ptr<IRequest> request (new ExtensionRequest("sendmi", params));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBMemberVariableAssigner interface
bool LayerComposeEmail::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTitle", CCNode*, nodeTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTo", CCNode*, nodeTo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeContents", CCNode*, nodeContents);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeTextContent", CCNode*, nodeTextContent);
	return true;
}

void LayerComposeEmail::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	//Create textfield
	txtTitle = CCEditBox::create(nodeTitle->getContentSize(), CCScale9Sprite::create("input.png"));
	initTextField(txtTitle, "Tieu de");
	txtTitle->setPosition( ccp( 0, nodeTitle->getContentSize().height ) );
	nodeTitle->addChild( txtTitle );
	//Create textfield
	txtTo = CCEditBox::create(nodeTo->getContentSize(), CCScale9Sprite::create("input.png"));
	initTextField(txtTo, "Gửi tới");
	txtTo->setPosition( ccp( 0, nodeTo->getContentSize().height ) );
	nodeTo->addChild( txtTo );
	//Create textfield
	txtContent = CCEditBox::create(nodeContents->getContentSize(), CCScale9Sprite::create("input.png"));
	initTextField(txtContent, "Nội dung");
	txtContent->setPosition( ccp( 0, nodeContents->getContentSize().height ) );
	nodeContents->addChild( txtContent );

	nodeContents->removeChild( nodeTextContent, true );
// 	CCLOG("Imhere onNodeLoaded");
// 	initTextField(txtUsername, "Tên tài khoản");
// 	//
// 	this->setTouchEnabled(true);
	return;
}

void LayerComposeEmail::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerComposeEmail::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerComposeEmail::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerComposeEmail::onExit()
{
	CCLayer::onExit();
}

void LayerComposeEmail::initTextField( CCEditBox* txt, const char* hintText )
{
	txt->setFontColor(ccBLACK);
	txt->setPlaceholderFontColor(ccBLACK);
	txt->setFont("fonts/Roboto-Regular.ttf", 18);
	txt->setReturnType(kKeyboardReturnTypeDefault);
	txt->setInputFlag(kEditBoxInputFlagSensitive);
	txt->setPlaceHolder(hintText);
	txt->setTouchPriority(-128);
	txt->setAnchorPoint(ccp(0, 1));
}

void LayerComposeEmail::setDatas( string toUser, string title, string contents )
{
	txtTo->setText( toUser.c_str() );
	txtContent->setText( contents.c_str() );
}

void LayerComposeEmail::OnExtensionResponse( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if(strcmp("sendmi", cmd->c_str())==0){ //dmi response
		LayerMain::getSingleton().gotoMail();
	}
}
