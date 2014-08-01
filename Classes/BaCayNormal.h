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
#include "LayerAvatar_BaCay.h"
#include "_CardBaCay_.h"
#include "_LayerBet_.h"
#include "_Button_inGame_.h"
#include "_Number_Chat_inGame7u.h"

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

	string _list_user;
	string _list_cards;

	bool flagChiaBai;


	LayerBaCayAvatar *layerAvatars;
	LayerButtonInGame *layerbutton;
	CardBaCay *layerCards;
	Number_Chat_inGame7u *layerNumberChat;
	BetGame3Cay *layerBet;

public:
	BaCayNormal();
	~BaCayNormal();
	void onExit();

	void createBackgrounds();
	void createAvatars();
	void createButtons();
	void createNumbers();
	void createCards();

	//Reconnect
	void eventListUserUpdate(string listusers);
	void whenUserRejoinOrGuess(string listUser);

	void LatBai(string listCard,string uid, bool tua);

	void whenUserReady(string uid);
	void whenUserUnready(string uid);
	void whenGameStart();
	void whenResuiltGame(string rg);
	void whenGameEnd();

	Button* createButtonWithTitle_Pos(const char *pName, CCPoint pPoint);
	Button* getButtonByTag(int pTag);

	//Các sự kiện Button trong game
	void btn_ready_click(CCObject *sender, TouchEventType type);
	void btn_Unready_click(CCObject *sender, TouchEventType type);
	void btn_btn_Latat(CCObject *sender, TouchEventType type);
	void btn_XemBai_click(CCObject *sender, TouchEventType type);
	void btn_NanBai_click(CCObject *sender, TouchEventType type);

	void callBackFunction_LatBai(CCNode *pSend);
	void callBackFuntion_Endgive(CCNode *pSend);

	//Server
	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

#endif /* defined(__iCasino_v2__BaCayNormal__) */
