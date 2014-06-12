//
//  LayerGameChan_XuongU.h
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#ifndef demo_LayerGameChan_XuongU_h
#define demo_LayerGameChan_XuongU_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerGameChan_XuongU
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
, public PlayerCallBack
{
private:
    enum tagLabelInRow{
        tag_RoomID=0,
        tag_Players=1,
        tag_Bet=2,
        tag_Details=3
    };
    enum tagTable{
        tagListXuong=0,
        tagListXuongSelected=1
    };

	CCLabelTTF* lblTime;
    
    CCNode* nodeTableXuong;
    CCTableView* tblXuong;
    
    CCNode* nodeTableListXuongSelected;
    CCTableView* tblListXuongSelected;
public:
    LayerGameChan_XuongU();
    virtual ~LayerGameChan_XuongU();
    
    CREATE_FUNC(LayerGameChan_XuongU);
    
    CCTableViewCell* process4ListXuong(cocos2d::extension::CCTableView *table, unsigned int idx);
    CCTableViewCell* process4XuongSelected(cocos2d::extension::CCTableView *table, unsigned int idx);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonXuong(CCObject* pSender);
    //TABLE VIEW
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    //
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerGameChan_XuongULoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerGameChan_XuongULoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerGameChan_XuongU);
};

#endif
