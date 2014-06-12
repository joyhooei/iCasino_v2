//
//  LayerCurrencyExchange.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerCurrencyExchange_h
#define demo_LayerCurrencyExchange_h


#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "NotificationCallback.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerCurrencyExchange
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public PlayerCallBack
, public NotificationCallBack
{
private:
    CCLabelTTF *lblMoney;
    CCLabelTTF *lblCurrentMoney;
    CCLabelTTF *lblCanBorrow;
    
    CCNode* nodeMoney;
    
    CCControlSlider* sliderMoney;
    CCSprite* spriteMoney;
    
    int rate;
public:
    LayerCurrencyExchange();
	virtual ~LayerCurrencyExchange();

	void notificationCallBack(bool isOK, int tag);
    
    void loadAllMyDatas();
    
    void loadMinMaxMoney();
    
    CREATE_FUNC(LayerCurrencyExchange);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonCreate(CCObject* pSender);
    void onButtonClose(CCObject* pSender);
    
    void valueChanged(CCObject *sender, CCControlEvent controlEvent);
    //Server
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerCurrencyExchangeLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerCurrencyExchangeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerCurrencyExchange);
};


#endif
