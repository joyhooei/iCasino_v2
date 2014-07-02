//
//  LayerFriendDetailsDetails.h
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#ifndef demo_LayerFriendDetails_h
#define demo_LayerFriendDetails_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "StructHistory.h"
#include "GameServer.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerFriendDetails
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
, public PlayerCallBack
{
private:
    enum tagTableView{
        tag_Historys=0,
        tag_Friends=1
    };
    enum tagLabelInCell{
        tag_NameGame,
        tag_Level,
        tag_WinLose
    };
    enum tagFriendCell{
        tag_avatar,
        tag_NameFriend,
        tag_OnlineState,
		tag_OnlineStateImage
    };
    enum tag_SpriteClick{
        tag_friendInfoDisable=0,
        tag_inviteDisable=1,
        tag_friendInfoEnable=2,
        tag_inviteEnable=3
    };
    CCLabelTTF* lblSex;
    CCLabelTTF* lblXu;
    CCLabelTTF* lblOnline;
    CCLabelTTF* lblName;
    
    CCSprite* spriteOnline;
    
    CCNode* nodeTableHistory;
    CCTableView* tblHistory;
    CCNode* nodeFriends;
    CCTableView* tblFriends;
    
    StructHistory historys[20];
    
    int rowsHistoryCount;
    int rowsFriendsCount;

	string currFriendID;

	int mCurrentRoomIndex;
public:
    LayerFriendDetails();
    virtual ~LayerFriendDetails();
    
    void initTextField(CCEditBox* txt, const char* hintText);
    CCSprite* loadDefaultImage(CCSize s, CCPoint p);

	void loadFirstCell();
    
    CCTableViewCell* createCell4History(CCTableView *table, int idx);
    CCTableViewCell* createCell4Friends(CCTableView *table, int idx);
    
    CREATE_FUNC(LayerFriendDetails);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){return NULL;};
    // selector callbacks
    void onButtonSMS(CCObject* pSender);
    void onButtonTransferMoney(CCObject* pSender);
    void onButtonUnInvite(CCObject* pSender);
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

class LayerFriendDetailsLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerFriendDetailsLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerFriendDetails);
};

#endif
