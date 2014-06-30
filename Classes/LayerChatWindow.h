#ifndef __LayerChatWindow_SCENE_H__
#define __LayerChatWindow_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class LayerChatWindow : public cocos2d::CCLayer 
{
private:
	int _count;
	UITextField* txtChat;

	CCObject* m_callback;
	SEL_CallFuncND m_callbackListener;
public:
	~LayerChatWindow();
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	void setCallbackFunc(CCObject* target, SEL_CallFuncND callfun);

	virtual bool init(); 
	void dataLoaded(float percent);

	static cocos2d::CCScene* scene();

	// a selector callback
	void onButtonClose(CCObject* pSender, TouchEventType type);
	void onButtonSend(CCObject* pSender, TouchEventType type);
	void onButtonChats(CCObject* pSender, TouchEventType type);

	void OnEmoClick(CCObject* pSender, TouchEventType type);

	UILoadingBar *loadingBar;

	CREATE_FUNC(LayerChatWindow);
};

class LayerChatWindowLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerChatWindowLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerChatWindow);
};

#endif
