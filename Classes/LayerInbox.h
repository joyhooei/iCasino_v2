//
//  LayerInbox.h
//  iCasinov2
//
//  Created by AlexDao on 6/3/14.
//
//

#ifndef iCasinov2_LayerInbox_h
#define iCasinov2_LayerInbox_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "StructHistory.h"
#include "GameServer.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerInbox
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
        tag_User,
        tag_Date,
        tag_Content,
        tag_Delete
    };
    
    struct StructEmail{
        long id;
        string user;
        string datetime;
        string content;
    };
    
    vector<StructEmail> lstEmails;
    
    CCNode* nodeTableEmail;
    CCTableView* tblEmail;
    
    CCBReader * ccbReader;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary;
    
    int countOfEmail;
public:
    LayerInbox();
    virtual ~LayerInbox();
    
    CREATE_FUNC(LayerInbox);
    
    void loadAllMyDatas();
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonCreate(CCObject* pSender);
    void onButtonRefresh(CCObject* pSender);
    
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

class LayerInboxLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerInboxLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerInbox);
};

#endif
