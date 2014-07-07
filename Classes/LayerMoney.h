//
//  LayerMoney.h
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#ifndef demo_LayerMoney_h
#define demo_LayerMoney_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;
using namespace std;

class LayerMoney
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    enum tag_SpriteClick{
        tag_ChargeDisable=0,
        tag_HistoryDisable=1,
        tag_TransferDisable=2,
        tag_LoanDisable=3,
        tag_ExchangeDisable=4,
        tag_ChargeEnable=5,
        tag_HistoryEnable=6,
        tag_TransferEnable=7,
        tag_LoanEnable=8,
        tag_ExchangeEnable=9,
    };
    CCLabelTTF* lblChargeDisable;
    CCLabelTTF* lblHistoryDisable;
    CCLabelTTF* lblTransferDisable;
    CCLabelTTF* lblLoanDisable;
    CCLabelTTF* lblExchangeDisable;
    
    CCLabelTTF* lblChargeEnable;
    CCLabelTTF* lblHistoryEnable;
    CCLabelTTF* lblTransferEnable;
    CCLabelTTF* lblLoanEnable;
    CCLabelTTF* lblExchangeEnable;
    
    CCMenuItem* btnCharge_enable;
    CCMenuItem* btnHistory_enable;
    CCMenuItem* btnTransfer_enable;
    CCMenuItem* btnLoan_enable;
    CCMenuItem* btnExchange_enable;
    
    CCMenuItem* btnCharge_disable;
    CCMenuItem* btnHistory_disable;
    CCMenuItem* btnTransfer_disable;
    CCMenuItem* btnLoan_disable;
    CCMenuItem* btnExchange_disable;
    
    CCNode* nodeChild;
    
    tag_SpriteClick currTag;
    
    CCNode* currNodeView;
public:
    LayerMoney();
    virtual ~LayerMoney();
    
    void initTextField(CCEditBox* txt, const char* hintText);
    void disableTabs(tag_SpriteClick);
    
    void gotoChargeMoney();
    void gotoHistory();
    void gotoTransfer(string toUser);
    void gotoBorrow();
    void gotoExchange();
    
    void removeOldView();
    
    CREATE_FUNC(LayerMoney);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
    // selector callbacks
    void onButtonClick(CCObject* pSender);
};

class LayerMoneyLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerMoneyLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerMoney);
};


#endif
