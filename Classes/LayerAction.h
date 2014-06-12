//
//  LayerAction.h
//  iCasinov2
//
//  Created by AlexDao on 6/6/14.
//
//

#ifndef iCasinov2_LayerAction_h
#define iCasinov2_LayerAction_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "LayerChangeAvatar.h"
#include "LayerBuyAvatar.h"
#include "LayerChangePassword.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerAction
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public PlayerCallBack
{
private:
    enum{
        tag_layerChangeAvatar = 0,
        tag_layerChangePassword = 1,
        tag_layerBuyAvatar = 2
    };
    LayerChangeAvatar* layerChangeAvatar;
    LayerChangePassword* layerChangePassword;
    LayerBuyAvatar* layerBuyAvatar;
public:
    LayerAction();
    virtual ~LayerAction();
    
    void loadAllMyDatas();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerAction, create);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
    // selector callbacks
    void onButtonChangeAvatar(CCObject* pSender);
    void onButtonChangePassword(CCObject* pSender);
    void onButtonBuyAvatar(CCObject* pSender);
    //Server
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerActionLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerActionLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerAction);
};

#endif
