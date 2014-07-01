//
//  LayerCreateAccount.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerCreateAccount_h
#define demo_LayerCreateAccount_h


#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "NotificationCallback.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;
using namespace std;

class LayerCreateAccount
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public PlayerCallBack
, public NotificationCallBack
{
private:
    CCEditBox* txtUsername;
    CCEditBox* txtPassword;
    CCEditBox* txtRePassword;
    CCEditBox* txtPhone;
    CCEditBox* txtEmail;
    bool isMan;

	CCObject* m_callbackListener;
	SEL_CallFunc m_callback;

	string sIpAddress;
public:
    LayerCreateAccount();
	virtual ~LayerCreateAccount();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	void setCallbackFunc(CCObject* target, SEL_CallFunc callfun);

	void doLogin();
	void doConnect();

	void setIpAddress(string sip);
    
	void notificationCallBack(bool, int tag);
    void initTextField(CCEditBox* txt, const char* hintText);

	void connect2RegistZone();
    
    CREATE_FUNC(LayerCreateAccount);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonSex(CCObject* pSender);
    void onButtonCreate(CCObject* pSender);
	void onButtonClose(CCObject* pSender);
	//Server
	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerCreateAccountLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerCreateAccountLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerCreateAccount);
};


#endif
