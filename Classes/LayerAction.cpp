//
//  LayerAction.cpp
//  iCasinov2
//
//  Created by AlexDao on 6/6/14.
//
//

#include "LayerAction.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"
using namespace cocos2d;
//using namespace CocosDenshion;


LayerAction::LayerAction()
{
    layerChangeAvatar = NULL;
    layerChangePassword = NULL;
    layerBuyAvatar = NULL;
    
    CCLOG("asfnjsdfn");
    //
    GameServer::getSingleton().addListeners(this);
}

LayerAction::~LayerAction()
{
    GameServer::getSingleton().removeListeners(this);
    //
    CC_SAFE_RELEASE(layerChangeAvatar);
    CC_SAFE_RELEASE(layerChangePassword);
    CC_SAFE_RELEASE(layerBuyAvatar);
}

void LayerAction::loadAllMyDatas(){
    CCLOG("*****************************");
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerAction::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnChangeAvatar", LayerAction::onButtonChangeAvatar);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnBuyAvatar", LayerAction::onButtonBuyAvatar);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnChangePassword", LayerAction::onButtonChangePassword);
    return NULL;
}

void LayerAction::onButtonChangeAvatar(CCObject* pSender)
{
    CCLOG("onButtonChangeAvatar");
    layerChangePassword->setVisible(false);
    layerBuyAvatar->setVisible(false);
    layerChangeAvatar->setVisible(true);
}

void LayerAction::onButtonChangePassword(CCObject* pSender)
{
    CCLOG("onButtonChangePassword");
    layerChangePassword->setVisible(true);
    layerBuyAvatar->setVisible(false);
    layerChangeAvatar->setVisible(false);
    layerChangePassword->loadAllMyDatas();
}


void LayerAction::onButtonBuyAvatar(CCObject* pSender)
{
    CCLOG("onButtonBuyAvatar");
    layerChangePassword->setVisible(false);
    layerBuyAvatar->setVisible(true);
    layerChangeAvatar->setVisible(false);
}

// CCBMemberVariableAssigner interface
bool LayerAction::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LayerChangePassword", LayerChangePassword*, layerChangePassword);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LayerBuyAvatar", LayerBuyAvatar*, layerBuyAvatar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LayerChangeAvatar", LayerChangeAvatar*, layerChangeAvatar);
    return true;
}

void LayerAction::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    layerChangeAvatar->loadAllMyDatas();
    layerBuyAvatar->loadAllMyDatas();
    //
    layerChangePassword->setVisible(true);
    layerBuyAvatar->setVisible(false);
    layerChangeAvatar->setVisible(false);
    return;
}

void LayerAction::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
}