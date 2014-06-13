//
//  LayerFriend.h
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#ifndef demo_LayerFriend_h
#define demo_LayerFriend_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerFriend
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    enum tag_SpriteClick{
        tag_friendInfoDisable=0,
        tag_inviteDisable=1,
        tag_friendInfoEnable=2,
        tag_inviteEnable=3
    };
    CCLabelTTF* lblInviteDisable;
    CCLabelTTF* lblInviteEnable;
    CCLabelTTF* lblFriendInfoDisable;
    CCLabelTTF* lblFriendInfoEnable;
    
    CCMenuItem* btnFriendInfo_disable;
    CCMenuItem* btnInvite_disable;
    CCMenuItem* btnFriendInfo_enable;
    CCMenuItem* btnInvite_enable;
    
    tag_SpriteClick currTag;
    
    CCNode * nodeChild;
    
    CCNode* currNodeView;
public:
    LayerFriend();
    virtual ~LayerFriend();
    
    void initTextField(CCEditBox* txt, const char* hintText);
    void disableTabs(tag_SpriteClick);
    
    void removeOldView();
    
    void gotoFriendDetails();
    void gotoInviteFriends();
    
    CREATE_FUNC(LayerFriend);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonClick(CCObject* pSender);
};

class LayerFriendLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerFriendLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerFriend);
};

#endif
