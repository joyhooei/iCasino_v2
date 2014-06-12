//
//  LayerServices.h
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#ifndef demo_LayerServices_h
#define demo_LayerServices_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerServices
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    enum tag_SpriteClick{
        tag_Games=0,
        tag_Shop=1,
        tag_Rank=2,
        tag_Guide=3,
        tag_Chat=4
    };
public:
    LayerServices();
    virtual ~LayerServices();
    
    void initTextField(CCEditBox* txt, const char* hintText);
    void disableTabs(tag_SpriteClick);
    
    CREATE_FUNC(LayerServices);
    
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

class LayerServicesLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerServicesLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerServices);
};


#endif
