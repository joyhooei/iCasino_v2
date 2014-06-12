//
//  BaCayNormal.h
//  iCasino_v2
//
//  Created by DauA on 5/20/14.
//
//

#ifndef __iCasino_v2__BaCayNormal__
#define __iCasino_v2__BaCayNormal__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "AllData.h"
#include "_Avatar_inGame_.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace Sfs2X;

class BaCayNormal : public CCLayer,public PlayerCallBack{
private:

	string EXT_EVENT_LIST_USER_UPDATE;
	string EXT_EVENT_READY_NTF;
	string EXT_EVENT_START;
	string EXT_EVENT_LISTCARD_NTF;
	string EXT_EVENT_END;
	string EXT_EVENT_GAME_RESULT;
	string EXT_EVENT_UNREADY_NTF;
	string EXT_EVENT_UNREADY_REQ;
	string EXT_EVENT_READY_REQ;
	string EXT_EVENT_TURNUP_CARD;
	float left_Left ;
	float left_Right;
	float left_Top ;
	float height_card_notme ;
	float width_card_notme ;

	float bottom_card_l_r ;
	float bottom_card_top ;

	/*-------Vi trí các lá bài của mình------------*/
	float left_Me;
	float width_card_me;
	float height_card_me;
	float bottom_me;

	boost::shared_ptr<string> _id_me;
	string _list_user;
	string _list_cards;
	bool flagChiaBai;
	int demChiaBai;

	//Các button trong game
	UILayer *uLayer;
	UIButton *btnReady;
	UIButton *btnUnReady;
	UIButton *btnLattat;
	UIButton *btnXemBai;
	UIButton *btnNanBai;

	LayerAvatarInGame *layerAvatars;

	//Mảng chứa các lá bài của người chơi
	CCArray *CARD_ME;
	CCArray *CARD_LEFT;
	CCArray *CARD_RIGHT;
	CCArray *CARD_TOP;
public:
	BaCayNormal();
	~BaCayNormal();
	CREATE_FUNC(BaCayNormal);
	bool init();
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	void onTouchButton(CCObject *pSender, TouchEventType pType);
	void createBackgrounds();
	void createAvatars();
	void createButtons();
	void createNumbers();
	void createCards();


	vector<string> Dsplit(string &S,const char &str);
	//Các hàm xử lý
	void updateUser(string list);
	string find_ChuPhong(string listUser);

	//Reconnect
	void whenUserRejoinOrGuess(string listUser);
	void restoreListCard(CCArray *P,float _widtd, float _height, float _left, float _bottom);

	int getPosUserByName(string uid,string _list_user);
	void EventListCard();
	void LatBai(string listCard,string uid, bool tua);
	void chiaBai();
	void addCard4User(CCArray *P,float _widtd, float _height, float toX, float toY, int countUSer);

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
	void btn_btn_Latat(CCObject *sender, TouchEventType type);
	void btn_XemBai_click(CCObject *sender, TouchEventType type);
	void btn_NanBai_click(CCObject *sender, TouchEventType type);

	//Server
	void updateEvent( float dt );
	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

#endif /* defined(__iCasino_v2__BaCayNormal__) */
