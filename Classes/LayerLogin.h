//
//  LayerLogin.h
//  demo
//
//  Created by AlexDao on 5/30/14.
//
//

#ifndef demo_LayerLogin_h
#define demo_LayerLogin_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerLogin
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public PlayerCallBack
{
private:
    //CCLabelTTF* lblCuPhap;
    CCLabelTTF* lblDauSo;
    CCEditBox* txtUsername;
    CCEditBox* txtPassword;
    
	UICheckBox* chkSaveInfo;

    CCBReader * ccbReader;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary;
public:
    LayerLogin();
    virtual ~LayerLogin();
    
	void selectedStateEvent(CCObject* pSender, CheckBoxEventType type);    
    
    void doLogin();
    void initTextField(CCEditBox* txt, const char* hintText);

	void readInfo();
	void saveInfo();
    
    CREATE_FUNC(LayerLogin);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonLogin(CCObject* pSender);
    void onButtonLoginWithFacebook(CCObject* pSender);
    void onButtonCreateAccount(CCObject* pSender);
protected:
    void OnSmartFoxConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerLoginLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerLoginLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerLogin);
};

#endif
