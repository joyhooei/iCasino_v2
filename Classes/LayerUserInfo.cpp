//
//  LayerUserInfo.cpp
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#include "LayerUserInfo.h"
#include "SliderCustomLoader.h"
#include "TextFieldCustomLoader.h"

#include "LayerUserInfo_Details.h"
#include "LayerChangeAvatar.h"
#include "LayerBuyAvatar.h"
#include "LayerChangePassword.h"
#include "LayerAction.h"
//#include "LayerAc

using namespace cocos2d;
//using namespace CocosDenshion;


LayerUserInfo::LayerUserInfo()
{
    currTag = tag_UserInfoEnable;
    lblActionDisable = NULL;
    lblActionEnable = NULL;
    lblUserInfoDisable = NULL;
    lblUserInfoEnable = NULL;
    
    btnUserInfo_disable = NULL;
    btnAction_disable = NULL;
    btnUserInfo_enable = NULL;
    btnAction_enable = NULL;
    
    currNodeView = NULL;
    nodeChild = NULL;
    
    ccbReader = NULL;
    ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//    V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);
//    V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, TextFieldCustom);
    // register loaders
    ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerUserInfo_Details",   LayerUserInfo_DetailsLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerChangeAvatar",   LayerChangeAvatarLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerBuyAvatar",   LayerBuyAvatarLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerChangePassword",   LayerChangePasswordLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerAction",   LayerActionLoader::loader());
}

LayerUserInfo::~LayerUserInfo()
{
}

void LayerUserInfo::gotoUserInfo(){
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerUserInfo_Details* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerUserInfo_Details *)ccbReader->readNodeGraphFromFile( "LayerUserInfo_Details.ccbi" );
        nodeChild->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
    mLayer->loadAllMyDatas();
}

void LayerUserInfo::gotoAction(){
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerAction* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerAction *)ccbReader->readNodeGraphFromFile( "LayerAction.ccbi" );
        nodeChild->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    mLayer->loadAllMyDatas();
    currNodeView = mLayer;
}

void LayerUserInfo::removeOldView(){
    if( currNodeView==NULL )
        return;
    //    nodeChild->removeChild(currNodeView);
    currNodeView->removeFromParentAndCleanup(true);
//    CC_SAFE_RELEASE(currNodeView);
    //    try{
    //        currNodeView->release()();
    //    }catch(...){
    //
    //    }
    currNodeView = NULL;
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerUserInfo::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
  //  CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUserInfo_enable", LayerUserInfo::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnAction_enable", LayerUserInfo::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUserInfo_disable", LayerUserInfo::onButtonClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnAction_disable", LayerUserInfo::onButtonClick);
    return NULL;
}

void LayerUserInfo::disableTabs(tag_SpriteClick newTag){
    lblUserInfoEnable->setVisible( newTag == tag_UserInfoEnable );
    btnUserInfo_enable->setVisible( newTag == tag_UserInfoEnable );
    lblUserInfoDisable->setVisible( newTag != tag_UserInfoEnable );
    btnUserInfo_disable->setVisible( newTag != tag_UserInfoEnable );
    
    lblActionEnable->setVisible( newTag == tag_ActionEnable );
    btnAction_enable->setVisible( newTag == tag_ActionEnable );
    lblActionDisable->setVisible( newTag != tag_ActionEnable );
    btnAction_disable->setVisible( newTag != tag_ActionEnable );
    
}

void LayerUserInfo::onButtonClick(CCObject* pSender)
{
    CCMenuItem* mnu = (CCMenuItem*)pSender;
    int tag = mnu->getTag();
    if( currTag == tag )
        return;
    //
    switch (tag) {
        case tag_UserInfoDisable:
            currTag = tag_UserInfoEnable;
            gotoUserInfo();
            //
            break;
        case tag_ActionDisable:
            currTag = tag_ActionEnable;
            gotoAction();
            break;
    }
    disableTabs(currTag);
    CCLOG("onButtonClick with tag: %d %s", tag, lblUserInfoDisable->getString());
}

// CCBMemberVariableAssigner interface
bool LayerUserInfo::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblUserInfoDisable", CCLabelTTF *, lblUserInfoDisable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblUserInfoEnable", CCLabelTTF *, lblUserInfoEnable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblActionDisable", CCLabelTTF *, lblActionDisable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblActionEnable", CCLabelTTF *, lblActionEnable);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnUserInfo_disable", CCMenuItem *, btnUserInfo_disable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnUserInfo_enable", CCMenuItem *, btnUserInfo_enable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnAction_disable", CCMenuItem *, btnAction_disable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnAction_enable", CCMenuItem *, btnAction_enable);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeChild", CCNode *, nodeChild);
    return true;
}

void LayerUserInfo::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    gotoUserInfo();
    return;
}