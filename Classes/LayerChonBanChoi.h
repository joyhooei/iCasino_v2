//
//  LayerChonBanChoi.h
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#ifndef demo_LayerChonBanChoi_h
#define demo_LayerChonBanChoi_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "NotificationCallback.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerChonBanChoi
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
, public PlayerCallBack
, public NotificationCallBack
{
private:
    enum tagLabelInRow{
        tag_RoomID=0,
        tag_Players=1,
        tag_Bet=2,
        tag_Details=3,
		tag_Lock = 4
    };
    enum tagFriends{
        tagListRoom=0,
        tagListPlay=1
    };
	enum tagNotification{
		tagComfirmInvite = 100
	};
    
    cocos2d::CCLabelTTF *lblTitle;
    
    CCNode* nodeTableRooms;
    CCTableView* tblRooms;
    
    CCNode* nodeTableListRooms;
    CCTableView* tblListRooms;
    
    int m_gID;

	int mRoomID4Invite;
public:
    LayerChonBanChoi();
    virtual ~LayerChonBanChoi();
    
	CREATE_FUNC(LayerChonBanChoi);

	void joinRoomByID(int rID);

	void notificationCallBack(bool isOK, int tag);
    
    void setGameID(int gID);
    
    CCNode* createLabel4Cell(int tag, const char* text, CCSize size, CCPoint point);
    
    CCLabelTTF* getLabelFromTagID(CCTableViewCell *cell, int tag);
    
    CCTableViewCell* process4ListRooms(cocos2d::extension::CCTableView *table, unsigned int idx);
    CCTableViewCell* process4Rooms(cocos2d::extension::CCTableView *table, unsigned int idx);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonCreate(CCObject* pSender);
    void onButtonRefresh(CCObject* pSender);
    void onButtonChoiNgay(CCObject* pSender);
    
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

class LayerChonBanChoiLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerChonBanChoiLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerChonBanChoi);
};

#endif
