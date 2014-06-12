//
//  LayerChargeMoney.h
//  demo
//
//  Created by AlexDao on 5/30/14.
//
//

#ifndef demo_LayerChargeMoney_h
#define demo_LayerChargeMoney_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "NotificationCallback.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerChargeMoney
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public PlayerCallBack
, public NotificationCallBack
{
private:
    enum tagButtonState{
        tag_viettel=0,
        tag_mobi=2,
        tag_vina=1
    };
    CCLabelTTF* lblCuPhap;
    CCLabelTTF* lblDauSo;
    CCEditBox* txtMaThe;
    CCEditBox* txtSoThe;
    
    CCMenuItem* btnViettelStatus;
    CCMenuItem* btnVinaStatus;
    CCMenuItem* btnMobiStatus;
    tagButtonState currState;
    
    CCSprite* arrow_left;
    
    CCBReader * ccbReader;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary;
public:
    LayerChargeMoney();
    virtual ~LayerChargeMoney();

	void notificationCallBack(bool isOK, int tag);
    
    void setButtonState(tagButtonState);
    void initTextField(CCEditBox* txt, const char* hintText);
    
    CREATE_FUNC(LayerChargeMoney);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonViettelClick(CCObject* pSender);
    void onButtonVinaClick(CCObject* pSender);
    void onButtonMobiClick(CCObject* pSender);
    void onButtonOKClick(CCObject* pSender);
    void onButtonSMSClick(CCObject* pSender);
    void onButtonTyGiaClick(CCObject* pSender);
    //Server
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerChargeMoneyLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerChargeMoneyLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerChargeMoney);
};

#endif
