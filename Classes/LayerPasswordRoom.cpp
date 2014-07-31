//
//  LayerPasswordRoom.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerPasswordRoom.h"
#include "mUtils.h"
#include "Requests/JoinRoomRequest.h"
#include "GameServer.h"
#include "boost/smart_ptr/make_shared.hpp"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerPasswordRoom::LayerPasswordRoom()
{
    txtPassword = NULL;
}

LayerPasswordRoom::~LayerPasswordRoom()
{
	CC_SAFE_RELEASE(txtPassword);
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
	boost::shared_ptr<Room> ro = GameServer::getSingleton().getSmartFox()->GetRoomById( roomID );
	if( ro==NULL ){
		CCLOG("ROOM NOT EXIST!!!");
		this->removeFromParentAndCleanup(true);
		return;
	}
	//Get room variables
	boost::shared_ptr<RoomVariable> rv = ro->GetVariable("params");
	vector<string> lstParams = mUtils::splitString( *rv->GetStringValue(), '@' );
	// counting players
	int currPlayers = atoi( lstParams.at(2).c_str() );
	int numOfPlayers = atoi ( boost::to_string(ro->MaxUsers()).c_str() );
	// get idroom to left
	int a = -1;
	if( GameServer::getSingleton().getSmartFox()->LastJoinedRoom() ){
		a = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->Id();
	}
	boost::shared_ptr<long int> id2Left = boost::make_shared<long int>(a);
	//
	boost::shared_ptr<IRequest> request (new JoinRoomRequest(ro, txtPassword->getText(), id2Left, currPlayers==numOfPlayers));
	GameServer::getSingleton().getSmartFox()->Send(request);

	this->removeFromParentAndCleanup(true);
}


void LayerPasswordRoom::onButtonClose(CCObject* pSender)
{
	CCLOG("onButtonClose");
	this->removeFromParentAndCleanup(true);
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
	initTextField(txtPassword, "Mat khau");
	this->setTouchEnabled(true);
// 	txtPassword->setInputFlag(kEditBoxInputFlagSensitive    
	return;
}

void LayerPasswordRoom::initTextField(CCEditBox* txt, const char* hintText){
	txt->setFontColor(ccBLACK);
	txt->setPlaceholderFontColor(ccBLACK);
	txt->setFont("fonts/Roboto-Regular.ttf", 18);
	txt->setReturnType(kKeyboardReturnTypeDefault);
	txt->setInputFlag(kEditBoxInputFlagSensitive);
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
