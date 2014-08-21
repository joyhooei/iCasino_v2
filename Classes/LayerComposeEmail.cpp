//
//  LayerComposeEmail.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerComposeEmail.h"
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerComposeEmail::LayerComposeEmail()
{
	nodeTitle = NULL;
	nodeTo = NULL;
	nodeContents = NULL;
	nodeTextContent = NULL;
}

LayerComposeEmail::~LayerComposeEmail()
{
	CC_SAFE_RELEASE(nodeTitle);
	CC_SAFE_RELEASE(nodeTo);
	CC_SAFE_RELEASE(nodeContents);
	CC_SAFE_RELEASE(nodeTextContent);
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
	CCLOG("onButtonClose");
	this->removeFromParentAndCleanup(true);
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
