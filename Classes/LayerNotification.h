//
//  LayerNotification.h
//  demo
//
//  Created by AlexDao on 5/30/14.
//
//

#ifndef demo_LayerNotification_h
#define demo_LayerNotification_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "NotificationCallBack.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

typedef std::map< int , NotificationCallBack * > NotificationCallBackMap;
typedef std::map< int , NotificationCallBack * >::iterator NotificationCallBackMapIter;
typedef std::pair< int , NotificationCallBack * > NotificationCallBackMapPair;

class LayerNotification
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    CCLabelTTF* lblTitle;
    CCLabelTTF* lblDetails;
    CCLabelTTF* lblOK;
    CCLabelTTF* lblCancel;
    
    CCMenuItem* btnOK;
    CCMenuItem* btnCancel;

	CCMenu* mnuParent;

	NotificationCallBackMap mCallBack;
	int mCallBackIndex;

	int currTag;
	void setTitle(const char* title);
	void setMessage(const char* msg);
	void setTwoButton(bool isTwoButton);
	void setButtonOkTitle(const char* title);
	void setTag(int tag);
	void addListeners( NotificationCallBack * callBack );
public:
    LayerNotification();
	virtual ~LayerNotification();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();
    
    CREATE_FUNC(LayerNotification);

	void setNotificationOptions(const char* title, const char* msg, bool isTwoButton, const char* titleButtonOK, int tag, NotificationCallBack * callBack);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
    // selector callbacks
    void onButtonOKClick(CCObject* pSender);
    void onButtonCancelClick(CCObject* pSender);
};

class LayerNotificationLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerNotificationLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerNotification);
};

#endif
