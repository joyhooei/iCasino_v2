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
#include "LayerAvatar_BaCay.h"
#include "_CardBaCay_.h"
#include "_LayerBet_.h"
#include "_Number_Chat_inGame7u.h"
#include "_Button_inGame_.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace Sfs2X; 

class BaCayChuong : public CCLayer,public PlayerCallBack{
private:
	string EXT_EVENT_LISTCARD_NTF ;
	string EXT_EVENT_START;
	string EXT_EVENT_END;
	string EXT_EVENT_READY_REQ;
	string EXT_EVENT_READY_RES ;
	string EXT_EVENT_UNREADY_REQ ;
	string EXT_EVENT_ERROR_READY_NTF ;
	string EXT_EVENT_READY_NTF ;
	string EXT_EVENT_UNREADY_NTF ;
	string EXT_EVENT_TURNUP_CARD ;
	string EXT_EVENT_LIST_USER_UPDATE ;
	string EXT_EVENT_GAME_RESULT ;
	string EXT_EVENT_GAME_BET_REQ ;
	string EXT_EVENT_GAME_BET_ERROR_NOTIFY ;
	string EXT_EVENT_GAME_BET_NTF ;
	string EXT_EVENT_DEAL_CARD_REQ ;
	string EXT_EVENT_DEAL_CARD_RES ;
	string EXT_EVENT_SELECT_OPEN_CARD_REQ ;
	string EXT_EVENT_SELECT_OPEN_CARD_RES ;
	string EXT_EVENT_RAISE_REQ ;
	string EXT_EVENT_RAISE_RES ;
	string EXT_EVENT_FOLD_REQ ;
	string EXT_EVENT_FOLD_RES ;

	string _list_cards;
	string _list_users;

	bool flagChiaBai ;
	bool flagDatCuoc ;

	LayerBaCayAvatar *layerAvatars;
	Number_Chat_inGame7u *layerChat;
	LayerButtonInGame *layerButtons;
	CardBaCay *layerCard;
	BetGame3Cay *layerBet;

public:
	BaCayChuong();
	~BaCayChuong();
	void onExit();

	void createBackgrounds();
	void createAvatars();
	void createButtons();
	void createNumbers();
	void createCards();
	void createLayerBet();
	void createLayerChat();

	void eventListUser(string listusers);
	void eventGameBet_NTF(string uid, int gbv);

	void action_UserRejoinGame(string lsUser);
	void action_LatBai(string listCard,string uid, bool tua);

	string find_Chuong(string listUser);

	void whenGameStart();
	void whenGameEnd();
	void whenResuiltGame(string rg);

	Button* createButtonWithTitle_Pos(const char *pName, CCPoint pPoint);
	Button* getButtonByTag(int pTag);

	//Các sự kiện Button trong game
	void btn_ready_click(CCObject *sender, TouchEventType type);
	void btn_Unready_click(CCObject *sender, TouchEventType type);
	void btn_DatCuoc_click(CCObject *sender, TouchEventType type);
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
    
    //spec
    void specMode();
};

#endif /* defined(__iCasinov2__BaCayChuong__) */
