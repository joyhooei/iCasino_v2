//
//  LayerUserInfo_Details.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerUserInfo_Details_h
#define demo_LayerUserInfo_Details_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "StructHistory.h"
#include "GameServer.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerUserInfo_Details
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
, public PlayerCallBack
{
private:
    enum tagLabelInCell{
        tag_NameGame,
        tag_Level,
        tag_WinLose
    };
    
    cocos2d::CCLabelTTF *lblName;
    cocos2d::CCLabelTTF *lblAMF;
    cocos2d::CCLabelTTF *lblAM;
    cocos2d::CCLabelTTF *lblID;
    cocos2d::CCLabelTTF *lblLevel;
    
    CCNode* nodeTableHistory;
    CCTableView* tblHistory;
    
    StructHistory historys[11];
    
    CCBReader * ccbReader;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary;
public:
    LayerUserInfo_Details();
    virtual ~LayerUserInfo_Details();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerUserInfo_Details, create);
    
//    CREATE_FUNC(LayerUserInfo_Details);
    
    void loadAllMyDatas();
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
    // selector callbacks
    void onButtonUpdate(CCObject* pSender);
    void onButtonLogout(CCObject* pSender);
    
    void valueChanged(CCObject *sender, CCControlEvent controlEvent);
    //TABLE VIEW
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    //Server
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerUserInfo_DetailsLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerUserInfo_DetailsLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerUserInfo_Details);
};

#endif
