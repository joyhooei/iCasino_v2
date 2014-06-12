//
//  LayerChangePassword.h
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#ifndef demo_LayerChangePassword_h
#define demo_LayerChangePassword_h


#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "NotificationCallback.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerChangePassword
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public PlayerCallBack
, public NotificationCallBack
{
private:
    CCEditBox* txtOldPassword;
    CCEditBox* txtNewPassword;
    CCEditBox* txtRePassword;
public:
    LayerChangePassword();
    virtual ~LayerChangePassword();
    
    void initTextField(CCEditBox* txt, const char* hintText);
    void loadAllMyDatas();
    
    CREATE_FUNC(LayerChangePassword);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonUpdate(CCObject* pSender);
    //Server
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerChangePasswordLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerChangePasswordLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerChangePassword);
};

#endif
