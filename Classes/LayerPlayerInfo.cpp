//
//  LayerPlayerInfo.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerPlayerInfo.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerPlayerInfo::LayerPlayerInfo()
{
	lblAMF=NULL;
	lblName=NULL;
	lblSex = NULL;

	btnInviteFriend=NULL;
	btnUnFriend=NULL;
	btnKick=NULL;

	nodeAvatar = NULL;
	//
	GameServer::getSingleton().addListeners(this);
}

LayerPlayerInfo::~LayerPlayerInfo()
{
	GameServer::getSingleton().removeListeners(this);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerPlayerInfo::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerPlayerInfo::onButtonClose);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnInviteFriend", LayerPlayerInfo::onButtonInviteFriend);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUnFriend", LayerPlayerInfo::onButtonUnFriend);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnKick", LayerPlayerInfo::onButtonKick);
    return NULL;
}

void LayerPlayerInfo::onButtonInviteFriend(CCObject* pSender)
{
	CCLOG("onButtonInviteFriend");
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("aI", mFriendID.c_str());
	boost::shared_ptr<IRequest> request (new ExtensionRequest("raaf", params));
	GameServer::getSingleton().getSmartFox()->Send(request);
	//
	this->removeFromParentAndCleanup(true);
}
void LayerPlayerInfo::onButtonUnFriend(CCObject* pSender)
{
	CCLOG("onButtonUnFriend");
	CCLOG("onButtonInviteFriend");
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("aI", mFriendID.c_str());
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rarf", params));
	GameServer::getSingleton().getSmartFox()->Send(request);
	//
	this->removeFromParentAndCleanup(true);
}
void LayerPlayerInfo::onButtonKick(CCObject* pSender)
{
	CCLOG("onButtonKick");
}


void LayerPlayerInfo::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
	this->removeFromParentAndCleanup(true);
}

// CCBMemberVariableAssigner interface
bool LayerPlayerInfo::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblAMF", CCLabelTTF*, lblAMF);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblName", CCLabelTTF*, lblName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblSex", CCLabelTTF*, lblSex);
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnInviteFriend", CCMenuItem*, btnInviteFriend);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnUnFriend", CCMenuItem*, btnUnFriend);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnKick", CCMenuItem*, btnKick);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeAvatar", CCNode*, nodeAvatar);
    return true;
}

void LayerPlayerInfo::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	//
	this->setTouchEnabled(true);
    return;
}

void LayerPlayerInfo::reloadAllDatas()
{
	//
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("aI", mFriendID.c_str());
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rgif", params));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerPlayerInfo::OnExtensionResponse( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if(strcmp("rgif", cmd->c_str())==0){ ////Ti.App.GETACCINFOR_CMD:
		//setName:
		lblName->setString( param->GetUtfString("aN")->c_str() );
		lblSex->setString( param->GetInt("aS")==0?"Giới tính: Nam":"Giới tính: Nữ" );
		lblAMF->setString( mUtils::convertMoneyEx(*param->GetDouble("amf")).c_str()  );
		//Check is friend
		btnUnFriend->setVisible(GameServer::getSingleton().getSmartFox()->BuddyManager()->ContainsBuddy(mFriendID));
		btnInviteFriend->setVisible(!GameServer::getSingleton().getSmartFox()->BuddyManager()->ContainsBuddy(mFriendID));
	}
}

void LayerPlayerInfo::setFriendId( string friendID )
{ 
	mFriendID = friendID;
}

void LayerPlayerInfo::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerPlayerInfo::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerPlayerInfo::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerPlayerInfo::onExit()
{
	CCLayer::onExit();
}

void LayerPlayerInfo::setAvatarImage( CCSprite* avatar)
{
	if( avatar==NULL )
		return;
	return;
	nodeAvatar->addChild(avatar);
}

void LayerPlayerInfo::setIsBossRoom( bool isBoss )
{
	btnInviteFriend->setPositionX( isBoss?85:151 );
	btnUnFriend->setPositionX( isBoss?85:151 );
	btnKick->setVisible( isBoss );
}
