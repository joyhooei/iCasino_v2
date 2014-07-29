//
//  LayerGameChan_XuongU2.h
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#ifndef demo_LayerGameChan_XuongU22_h
#define demo_LayerGameChan_XuongU2_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerGameChan_XuongU2
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public PlayerCallBack
{
private:

	vector<string> lstCuoc;

	CCLabelTTF* lblTime;
	CCLabelTTF* lblTitle;

	CCArray *ListCuoc;
public:
    LayerGameChan_XuongU2();
    virtual ~LayerGameChan_XuongU2();
    
    CREATE_FUNC(LayerGameChan_XuongU2);
    
    CCTableViewCell* process4ListXuong(cocos2d::extension::CCTableView *table, unsigned int idx);
    CCTableViewCell* process4XuongSelected(cocos2d::extension::CCTableView *table, unsigned int idx);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonXuong(CCObject* pSender);
	//
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

	void ItemXuong_Click(CCObject *sender, TouchEventType type);
	string getValuesCuoc(int idx);
};

class ButtonXuong : public UIButton{
private:
	int idx;
	bool isClicked;
public:
	virtual bool init();
	CREATE_FUNC(ButtonXuong);
	void setID(int idx);
	int getID();
	void setClicked(bool isClicked);
	bool getClicked();
};

class LayerGameChan_XuongU2Loader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerGameChan_XuongU2Loader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerGameChan_XuongU2);
};

#endif
