//
//  LayerLichSuGiaoDich.h
//  demo
//
//  Created by AlexDao on 5/29/14. 
//
//

#ifndef demo_LayerLichSuGiaoDich_h
#define demo_LayerLichSuGiaoDich_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerLichSuGiaoDich
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
, public PlayerCallBack

{
private:
    CCNode* nodeHistory;
    CCTableView* tblHistory;
    enum {
        tag_cellTime,
        tag_cellAmount,
        tag_cellDetails
	};

	struct StructHistory{
		string transID;
		string accId;
		string ip;
		string accId2;
		string transType;
		string amount;
		string transErr;
		string transErrDetail;
		string status;
		string cardSerial;
		string cardPin;
		string lastUpdateTime;
	};
	vector<StructHistory> lstHistory;
public:
    LayerLichSuGiaoDich();
    virtual ~LayerLichSuGiaoDich();
    
    void loadAllDatas();
    
    CCNode* createLabel4Cell(int tag, const char* text, CCSize size, CCPoint point);
    CCLabelTTF* getLabelFromTagID(CCTableViewCell *cell, int tag);
    
    CREATE_FUNC(LayerLichSuGiaoDich);
    
    // CCBSelectorResolver interfaces
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
    
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

class LayerLichSuGiaoDichLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerLichSuGiaoDichLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerLichSuGiaoDich);
};
#endif
