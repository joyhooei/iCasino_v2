//
//  LayerPlayGameChinessChess.h
//  iCasinov2
//
//  Created by AlexDao on 6/4/14.
//
//

#ifndef iCasinov2_LayerPlayGameChinessChess_h
#define iCasinov2_LayerPlayGameChinessChess_h


#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "AllData.h"
#include "_Chess_.h"
#include "LogicInChess.h"
#include "NotificationCallback.h"
#include "ImageDownloader.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

class LayerPlayGameChinessChess 
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public PlayerCallBack
	, public NotificationCallBack
{
private:
	//Chứa avatar bên màu đỏ
	CCNode* nodeAvatarRed;
	//Tên nguời chơi
	CCLabelTTF* lblNameRed;
	//Tiền
	CCLabelTTF* lblMoneyRed;
	//Tỷ lệ thắng thua
	CCLabelTTF* lblWinRateRed;
	//Tương tự red
	CCNode* nodeAvatarBlack;
	CCLabelTTF* lblNameBlack;
	CCLabelTTF* lblMoneyBlack;
	CCLabelTTF* lblWinRateBlack;
	//Khi tới nguời chơi nào thì sử dụng thằng này, và setVisiable = true
	CCSprite* box_time_focus_red;
	CCSprite* box_time_focus_black;
	//Khi ready, visible thằng này lên
	CCSprite* readyRed;
	//Thời gian tại 1 turn
	CCLabelTTF* lblTimeRed;
	//Thời gian tổng
	CCLabelTTF* lblTotalTimeRed;
	//Tuong tu red
	CCSprite* readyBlack;
	CCLabelTTF* lblTimeBlack;
	CCLabelTTF* lblTotalTimeBlack;
	//Add các quân cờ vào thằng này
	CCNode* nodeTableChess;
	//...
	CCNode* nodePoint;

	CCMenuItem* btnBack;
	CCMenuItem* btnSetting;
	CCMenuItem* btnMoney;
	CCMenuItem* btnChat;
	CCMenuItem* btnLose;
	CCMenuItem* btnPeace;
	CCMenuItem* btnReMove;
	CCMenuItem* btnReady;
	CCMenuItem* btnUnReady;
	//Các label hiển thị số lượng quân cờ còn lại
	CCLabelTTF* lblXeRed_status;
	CCLabelTTF* lblTotRed_status;
	CCLabelTTF* lblMaRed_status;
	CCLabelTTF* lblPhaoRed_status;
	CCLabelTTF* lblTuongRed_status;
	CCLabelTTF* lblSyRed_status;
	CCLabelTTF* lblXeBlack_status;
	CCLabelTTF* lblTotBlack_status;
	CCLabelTTF* lblMaBlack_status;
	CCLabelTTF* lblPhaoBlack_status;
	CCLabelTTF* lblTuongBlack_status;
	CCLabelTTF* lblSyBlack_status;

	// @thanhhv
	UILayer *layerWidget;

	enum EXT_RESPONSE{
		EXT_EVENT_START,            // = "s"
		EXT_EVENT_NEXT_TURN,        // = "nt";
		EXT_EVENT_END,              // = "e"
		EXT_EVENT_READY_NTF,        // = "rntf";
		EXT_EVENT_GAME_RESULT,      // = "grs";
		EXT_EVENT_ERROR_READY_NTF,  // = "e_rntf";
		EXT_EVENT_LIST_USER_UPDATE, // = "luu";
		EXT_EVENT_MOVE_NTF,         // = "mntf";
		EXT_EVENT_FOR_PEACE_NTF,    // = "fpntf";
		//
		EXT_EVENT_READY_REQ,        // = "rr";
		EXT_EVENT_FOR_PEACE,        // = "fp";
		EXT_EVENT_IM_LOSE,          // = "iml"
		EXT_EVENT_MOVE,
		EXT_EVENT_REPLY_FOR_PEACE,  // = "rfp";
		EXT_EVENT_UNDO_MOVE_REQ,	// = "umr";
		EXT_EVENT_REPLY_UNDO_MOVE,	// = "rum";
		EXT_EVENT_UNDO_MOVE_NTF,	// = "umntf";
	};

	enum STYLE_DIALOG {
		DONG_Y_XIN_HOA,
		DONG_Y_XIN_THUA,
		DONG_Y_XIN_DI_LAI,
		DONG_Y_CHO_HOA,
		DONG_Y_CHO_DI_LAI
	};

	int convertResponseToInt(string inString);
	string convertResponseToString(int inInt);

	boost::shared_ptr<ISFSObject> param;

	enum tagButton{
		tagButtonReady = 1
	};

	CCSize sizeScreen;
	float startLeft;
	float startTop;
	float scaleApp;

	CCSprite *tag;
	CCSprite *tag2;
	CCSprite *chieuTuongRed;
	CCSprite *chieuTuongBlack;
// 	CCSprite *iconWin;
// 	CCSprite *iconLose;
	vector<Chess*> arrChess;
	bool isMaster;
	bool isStartedGame;
	bool isIamTheFirst;
	bool isRedChess;  // ktra xem minh la quan do hay quan den

	string myName;
	string nameCurrentTurn;
	int indexCurrent;
	int indexTarget;
	int timeRestBlack;
	int timeRestRed;
	int timeForTurnBlack;
	int timeForTurnRed;
	int timeToReady;

	CCSprite *selected_chess;
	ChessLogic *logicChess;

	ImageDownloader* imagedownloader4Red;
	ImageDownloader* imagedownloader4Black;

public:
	LayerPlayGameChinessChess();
	virtual ~LayerPlayGameChinessChess();

	void loadAllDatas();
	void playSound(string soundPath);

	float getDistant2Point(CCPoint p1, CCPoint p2);
	CCPoint getPositionFromIndex(int id);
	int getIndexFromPosition(CCPoint pos);
	void setPointVisiable(int id, bool isShow);
	//Callback
	void callbackFromChatWindow(CCNode*, void*);
	void notificationCallBack(bool, int tag); 

	CREATE_FUNC(LayerPlayGameChinessChess);

	// CCBSelectorResolver interfaces
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	};

	void onButtonBack(CCObject* pSender);
	void onButtonSetting(CCObject* pSender);
	void onButtonMoney(CCObject* pSender);
	void onButtonChat(CCObject* pSender);
	void onButtonLose(CCObject* pSender);
	void onButtonPeace(CCObject* pSender);
	void onButtonRemove(CCObject* pSender);
	void onButtonReady(CCObject* pSender);
	void onButtonUnReady(CCObject* pSender);
	//Server
	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	virtual void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	virtual void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

	void event_EXT_EVENT_START();             // = “s”();
	void event_EXT_EVENT_NEXT_TURN();         // = "nt"();
	void event_EXT_EVENT_END();               // = "e"
	void event_EXT_EVENT_READY_NTF();         // = "rntf"();
	void event_EXT_EVENT_GAME_RESULT();       // = "grs"();
	void event_EXT_EVENT_ERROR_READY_NTF();   // = "e_rntf"();
	void event_EXT_EVENT_LIST_USER_UPDATE();  // = "luu"();
	void event_EXT_EVENT_MOVE_NTF();          // = "mntf"();
	void event_EXT_EVENT_FOR_PEACE_NTF();     // = "fpntf"();
	void event_EXT_EVENT_UNDO_MOVE_REQ();
	void event_EXT_EVENT_UNDO_MOVE_NTF();

	// @thanhhv
	vector<string> split(string &s, const char &c);
	void addButtons();
	CCPoint convertPoint(CCPoint point);
	CCPoint convertPoint_LayerToTable(CCPoint point);
	CCPoint convertPoint_TableToLayer(CCPoint point);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *event);

	bool isTouchedChess();
	void createChess();
	void refreshChess();
	void drawCanMove(vector<int> arrPos);

	int convertID(int id);
	void moveChess(int fromID, int toID);

	void updateTimer(float dt);
	string convertTimer(int time);

	// hoangdd
	void downLoadImage(string url, string fileName);
	void setAvatarByPath(CCNode *nodeContainer, string path); // đường dẫn ảnh đã được lưu trong máy
	void setAvatarBySprite(CCNode *nodeContainer, CCSprite* img);
	void onImageDownLoaded(CCHttpClient* pSender, CCHttpResponse* pResponse);
	void loadDefaultImage(CCNode *nodeContainer);
};

class LayerPlayGameChinessChessLoader : public cocos2d::extension::CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerPlayGameChinessChessLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerPlayGameChinessChess);
};

#endif
