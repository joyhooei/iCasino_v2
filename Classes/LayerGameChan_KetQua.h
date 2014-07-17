//
//  LayerGameChan_KetQua.h
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#ifndef demo_LayerGameChan_KetQua_h
#define demo_LayerGameChan_KetQua_h

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerGameChan_KetQua
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public PlayerCallBack
{
private:
	CCLabelTTF *lblThongBao;
	CCLabelTTF* lblMoney;

	CCArray *CARD_NOC;
	CCArray *CARD_WINNER;

	string EXT_EVENT_REQ_TRENTAY_DETAIL;
	string EXT_EVENT_REQ_NOC_DETAIL;// = "rqnocdtl";

	string list_noc;
public:
	LayerGameChan_KetQua();
	virtual ~LayerGameChan_KetQua();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(LayerGameChan_KetQua);

	void setPlayer_U(string uid);
	void setValueNoc(string _list);

	string identifyCuoc_sac(string _cuoc);
	// CCBSelectorResolver interfaces
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};
	// selector callbacks
	string findTypeCard(string number,string suite);
	void rotateListCards(CCArray *P);
	void setCard_Noc(string listnoc);
	void setListCard_WinnerUser(string listcard);

	void displayListCard_Noc(CCArray *P);
	void displayListCard_Winner(string listcard);

	void onButtonXemNoc(CCObject* pSender);
	void closePopUp();

	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

};

class LayerGameChan_KetQuaLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerGameChan_KetQuaLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerGameChan_KetQua);
};

#endif
