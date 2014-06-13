//
//  LayerUserInfo.h
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#ifndef demo_LayerUserInfo_h
#define demo_LayerUserInfo_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerUserInfo
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    enum tag_SpriteClick{
        tag_UserInfoDisable=0,
        tag_ActionDisable=1,
        tag_UserInfoEnable=2,
        tag_ActionEnable=3
    };
    CCLabelTTF* lblActionDisable;
    CCLabelTTF* lblActionEnable;
    CCLabelTTF* lblUserInfoDisable;
    CCLabelTTF* lblUserInfoEnable;
    
    CCMenuItem* btnUserInfo_disable;
    CCMenuItem* btnAction_disable;
    CCMenuItem* btnUserInfo_enable;
    CCMenuItem* btnAction_enable;
    
    tag_SpriteClick currTag;
    
    CCNode* nodeChild;
    CCNode* currNodeView;
    
public:
    LayerUserInfo();
    virtual ~LayerUserInfo();
    
    void gotoUserInfo();
    void gotoAction();
    void removeOldView();
    
    void initTextField(CCEditBox* txt, const char* hintText);
    void disableTabs(tag_SpriteClick);
    
    CREATE_FUNC(LayerUserInfo);
    
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

class LayerUserInfoLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerUserInfoLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerUserInfo);
};

#endif
