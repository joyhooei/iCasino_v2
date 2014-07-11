//
//  LayerPlayerInfo.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerPlayerInfo_h
#define demo_LayerPlayerInfo_h


#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "ImageDownloader.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerPlayerInfo
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public PlayerCallBack
{
private:
	CCLabelTTF* lblAMF;
	CCLabelTTF* lblName;
	CCLabelTTF* lblSex;

	CCMenuItem* btnInviteFriend;
	CCMenuItem* btnUnFriend;
	CCMenuItem* btnKick;

	CCNode* nodeAvatar;

	string mFriendID;

	ImageDownloader* imageDownloader;
public:
    LayerPlayerInfo();
	virtual ~LayerPlayerInfo();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	void setFriendId(string friendID);
	void setAvatarImage(CCSprite*);
	void setAvatarUrl(string url);
	void reloadAllDatas();
	void setIsBossRoom(bool isBoss);
    
    CREATE_FUNC(LayerPlayerInfo);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
	void onButtonInviteFriend(CCObject* pSender);
	void onButtonUnFriend(CCObject* pSender);
	void onButtonKick(CCObject* pSender);
	void onButtonClose(CCObject* pSender);
	//Server
	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerPlayerInfoLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerPlayerInfoLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerPlayerInfo);
};

#endif
