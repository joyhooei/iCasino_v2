//
//  LayerFriend.cpp
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#include "LayerFriend.h"
#include "LayerFriendDetails.h"
#include "SliderCustomLoader.h"
#include "TextFieldCustomLoader.h"
#include "SliderCustomLoader.h"
#include "mUtils.h"
#include "LayerInviteFriends.h"
#include "LayerInviteFriendsFacebook.h"
#include "platform/android/jni/Android.h"
#include "SceneManager.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerFriend::LayerFriend()
{
    currTag = tag_friendInfoEnable;
    lblInviteDisable=NULL;
    lblInviteEnable=NULL;
    lblFriendInfoDisable=NULL;
    lblFriendInfoEnable=NULL;
    
    btnFriendInfo_disable=NULL;
    btnInvite_disable=NULL;
    btnFriendInfo_enable=NULL;
    btnInvite_enable=NULL;
    //
    currNodeView = NULL;
    nodeChild = NULL;
    //
}

LayerFriend::~LayerFriend()
{
	removeOldView();
	CCLOG("LayerFriend::~LayerFriend()");

	//
	CC_SAFE_RELEASE(lblInviteDisable);
	CC_SAFE_RELEASE(lblInviteEnable);
	CC_SAFE_RELEASE(lblFriendInfoDisable);
	CC_SAFE_RELEASE(lblFriendInfoEnable);

	CC_SAFE_RELEASE(btnFriendInfo_disable);
	CC_SAFE_RELEASE(btnInvite_disable);
	CC_SAFE_RELEASE(btnFriendInfo_enable);
	CC_SAFE_RELEASE(btnInvite_enable);

	CC_SAFE_RELEASE(currNodeView);
	CC_SAFE_RELEASE(nodeChild);
}

void LayerFriend::removeOldView(){
    if( currNodeView==NULL )
        return;
    currNodeView->removeFromParentAndCleanup(true);
    currNodeView = NULL;
}

void LayerFriend::gotoFriendDetails(){
    removeOldView();
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerFriendDetails* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerFriendDetails *)ccbReader->readNodeGraphFromFile( "LayerFriendDetails.ccbi" );
        nodeChild->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
}

void LayerFriend::gotoInviteFriends(){
    //removeOldView();
	/*CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	LayerInviteFriends* mLayer;
	if (ccbReader)
	{
		mLayer = (LayerInviteFriends *)ccbReader->readNodeGraphFromFile( "LayerInviteFriends.ccbi" );
		nodeChild->getParent()->addChild(mLayer, 1, 1);
		ccbReader->release();
		mLayer->setZOrder(INT_MAX);
	}
    //currNodeView = mLayer;
    //*/
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	inviteFB();
#else
	CCLog("Khong ho tro nen tang nay");
#endif
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerFriend::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
   // CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnFriendInfo_enable", LayerFriend::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnInvite_enable", LayerFriend::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnFriendInfo_disable", LayerFriend::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnInvite_disable", LayerFriend::onButtonClick);
    return NULL;
}

void LayerFriend::disableTabs(tag_SpriteClick newTag){
    lblFriendInfoEnable->setVisible( newTag == tag_friendInfoEnable );
    btnFriendInfo_enable->setVisible( newTag == tag_friendInfoEnable );
    lblFriendInfoDisable->setVisible( newTag != tag_friendInfoEnable );
    btnFriendInfo_disable->setVisible( newTag != tag_friendInfoEnable );
    
    lblInviteEnable->setVisible( newTag == tag_inviteEnable );
    btnInvite_enable->setVisible( newTag == tag_inviteEnable );
    lblInviteDisable->setVisible( newTag != tag_inviteEnable );
    btnInvite_disable->setVisible( newTag != tag_inviteEnable );
    
}

void LayerFriend::onButtonClick(CCObject* pSender)
{
    CCMenuItem* mnu = (CCMenuItem*)pSender;
    int tag = mnu->getTag();
    if( currTag == tag )
        return;
    //
    switch (tag) {
        case tag_friendInfoDisable:
            currTag = tag_friendInfoEnable;
			gotoFriendDetails();
            //
            break;
        case tag_inviteDisable:
// 			CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
// 			CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
// 			ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
// 			LayerInviteFriends* mLayer;
// 			if (ccbReader)
// 			{
// 				mLayer = (LayerInviteFriends *)ccbReader->readNodeGraphFromFile( "LayerInviteFriends.ccbi" );
// 				this->addChild(mLayer, 1, 1);
// 				ccbReader->release();
// 			}
// 			
			gotoInviteFriends();
            //return;
            currTag = tag_inviteEnable;
            break;
    }
    disableTabs(currTag);
    CCLOG("onButtonClick with tag: %d", tag);}

// CCBMemberVariableAssigner interface
bool LayerFriend::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblFriendInfoDisable", CCLabelTTF *, lblFriendInfoDisable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblFriendInfoEnable", CCLabelTTF *, lblFriendInfoEnable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblInviteDisable", CCLabelTTF *, lblInviteDisable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblInviteEnable", CCLabelTTF *, lblInviteEnable);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnFriendInfo_disable", CCMenuItem *, btnFriendInfo_disable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnFriendInfo_enable", CCMenuItem *, btnFriendInfo_enable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnInvite_disable", CCMenuItem *, btnInvite_disable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnInvite_enable", CCMenuItem *, btnInvite_enable);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeChild", CCNode *, nodeChild);

    return true;
}

void LayerFriend::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere LayerFriend::onNodeLoaded");
    gotoFriendDetails();
    return;
}