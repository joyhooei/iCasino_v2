//
//  LayerBet_Lieng.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerBet_Lieng_h
#define demo_LayerBet_Lieng_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerBet_Lieng
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    CCLabelTTF *lblMoney;
    CCControlSlider* sliderMoney;
    CCSprite* spriteMoney;
    
    CCLabelTTF* lblTitle1;
    CCLabelTTF* lblTitle2;
    CCLabelTTF* lblTitle3;

public:
    LayerBet_Lieng();
    virtual ~LayerBet_Lieng();
    
    CREATE_FUNC(LayerBet_Lieng);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};

	void setInfoBet(int _minBet,int _myBet);

    // selector callbacks
    void onButtonCreate(CCObject* pSender);
    void onButtonClose(CCObject* pSender);
    
    void valueChanged(CCObject *sender, CCControlEvent controlEvent);
};

class LayerBet_LiengLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerBet_LiengLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerBet_Lieng);
};

#endif
