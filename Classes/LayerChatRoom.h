//
//  LayerChatRoom.h
//  iCasinov2
//
//  Created by AlexDao on 6/3/14.
//
//

#ifndef iCasinov2_LayerChatRoom_h
#define iCasinov2_LayerChatRoom_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerChatRoom
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
        tag_Content=0
    };
    enum tagChatRoom{
        tagListRoom=0,
        tagListContent=1
    };

    cocos2d::CCLabelTTF *lblTitle;
    
    CCNode* nodeListRooms;
    CCTableView* tblListRooms;
    
    CCNode* nodeListContents;
    CCTableView* tblListContents;
    
    int m_gID;
public:
    LayerChatRoom();
    virtual ~LayerChatRoom();
    
    CREATE_FUNC(LayerChatRoom);
    
    void setGameID(int gID);
    
    CCNode* createLabel4Cell(int tag, const char* text, CCSize size, CCPoint point);
    
    CCLabelTTF* getLabelFromTagID(CCTableViewCell *cell, int tag);
    
    CCTableViewCell* process4ListRooms(cocos2d::extension::CCTableView *table, unsigned int idx);
    CCTableViewCell* process4ListContents(cocos2d::extension::CCTableView *table, unsigned int idx);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonChat(CCObject* pSender);
  
    void valueChanged(CCObject *sender, CCControlEvent controlEvent);
    //TABLE VIEW
    void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
    void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    //
    void OnSmartFoxRoomJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxRoomJoinError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxRoomAdd(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxInvitation(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

class LayerChatRoomLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerChatRoomLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerChatRoom);
};

#endif
