//
//  BaCayChuong.h
//  iCasinov2
//
//  Created by DauA on 5/23/14.
//
//

#ifndef __iCasinov2__BaCayChuong__
#define __iCasinov2__BaCayChuong__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "AllData.h"
#include "_Avatar_inGame_.h"
#include "FrameBet.h"
#include "_Chat_inGame_.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace Sfs2X;

class BaCayChuong : public CCLayer,public PlayerCallBack{
private:
	string EXT_EVENT_LISTCARD_NTF ;
	string EXT_EVENT_START ;//= "s";
	string EXT_EVENT_END ;//= "e";
	string EXT_EVENT_READY_REQ ;//= "rr";
	string EXT_EVENT_READY_RES ;//= "rdres";
	string EXT_EVENT_UNREADY_REQ ;//= "urr";
	string EXT_EVENT_ERROR_READY_NTF ;//= "e_rntf";
	string EXT_EVENT_READY_NTF ;//= "rntf";
	string EXT_EVENT_UNREADY_NTF ;//= "urntf";
	string EXT_EVENT_TURNUP_CARD ;//= "tuc";
	string EXT_EVENT_LIST_USER_UPDATE ;//= "luu";
	string EXT_EVENT_GAME_RESULT ;//= "grs";
	string EXT_EVENT_GAME_BET_REQ ;//= "gbr";
	string EXT_EVENT_GAME_BET_ERROR_NOTIFY ;//= "e_bntf";
	string EXT_EVENT_GAME_BET_NTF ;//= "gb_ntf";
	string EXT_EVENT_DEAL_CARD_REQ ;//= "dcrq";
	string EXT_EVENT_DEAL_CARD_RES ;//= "dcrs";
	string EXT_EVENT_SELECT_OPEN_CARD_REQ ;//= "slstrq";
	string EXT_EVENT_SELECT_OPEN_CARD_RES ;//= "slsrrs";
	string EXT_EVENT_RAISE_REQ ;//= "rsrq";
	string EXT_EVENT_RAISE_RES ;//= "rsrs";
	string EXT_EVENT_FOLD_REQ ;//= "fdrq";
	string EXT_EVENT_FOLD_RES ;//= "fdrs";
	float left_Left;
	float left_Right;
	float left_Top ;
	float height_card_notme ;
	float width_card_notme ;

	float bottom_card_l_r ;
	float bottom_card_top ;

	/*-------Vi trí các lá bài của mình------------*/
	float left_Me ;
	float width_card_me ;
	float height_card_me ;
	float bottom_me ;

	string _list_user;
	string _list_cards;
	bool flagChiaBai ;
	bool flagDatCuoc ;
	int demChiaBai;
	string arrCardTypes[4];


	//Các button trong game
	UILayer *uLayer;
	UIButton *btnReady;
	UIButton *btnDatCuoc;
	UIButton *btnUnReady;
	UIButton *btnLattat;
	UIButton *btnXemBai;
	UIButton *btnNanBai;

	LayerAvatarInGame *layerAvatars;
	LayerChatInGame *layerChat;
	//Mảng chứa các lá bài của người chơi
	CCArray *CARD_ME;
	CCArray *CARD_LEFT;
	CCArray *CARD_RIGHT;
	CCArray *CARD_TOP;

	//GameBet các người chơi
	FrameBet *frameBet_Me;
	FrameBet *frameBet_Left;
	FrameBet *frameBet_Right;
	FrameBet *frameBet_Top;
public:
	BaCayChuong();
	~BaCayChuong();
	CREATE_FUNC(BaCayChuong);
	bool init();

	void createBackgrounds();
	void createAvatars();
	void createButtons();
	void createNumbers();
	void createCards();
	void createLayerChat();


	vector<string> Dsplit(string &S,const char &str);
	//Các hàm xử lý
	void action_UpdateListUser(string lsUser);
	void action_UserRejoinGame(string lsUser);
	void action_LatBai(string listCard,string uid, bool tua);
	void action_ChiaBai();
	void action_AddCard4User(CCArray *P,float _widtd, float _height, float toX, float toY, int countUSer);
	void action_GameBetNTF(string uid, string gameBet);

	string find_ChuPhong(string listUser);
	string find_Chuong(string listUser);
	string findTypeCard(string card);
	//Reconnect
	void restoreListCard(CCArray *P,float _widtd, float _height, float _left, float _bottom);

	string fn_format_money_2(string re);

	int getPosUserByName(string uid,string _list_user);

	void whenUserReady(string uid);
	void whenUserUnready(string uid);
	void whenGameStart();
	void whenResuiltGame(string rg);
	void whenGameEnd();

	// Tạo các list cards
	void createCardMe(string lc);
	void createCardLeft(string lc);
	void createCardRight(string lc);
	void createCardTop(string lc);
	void deleteAllCardFromArray(cocos2d::CCArray *P);

	//Các sự kiện Button trong game
	void btn_ready_click(CCObject *sender, TouchEventType type);
	void btn_Unready_click(CCObject *sender, TouchEventType type);
	void btn_DatCuoc_click(CCObject *sender, TouchEventType type);
	void btn_btn_Latat(CCObject *sender, TouchEventType type);
	void btn_XemBai_click(CCObject *sender, TouchEventType type);
	void btn_NanBai_click(CCObject *sender, TouchEventType type);

	void callBackFunction_LatBai(CCNode *pSend);

	//Server
	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

#endif /* defined(__iCasinov2__BaCayChuong__) */
