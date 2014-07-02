//
//  Lieng.h
//  iCasinov2
//
//  Created by DauA on 5/27/14.
//
//

#ifndef __iCasinov2__Lieng__
#define __iCasinov2__Lieng__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"

#include "LayerAvatar_BaCay.h"
#include "_Button_inGame_.h"
#include "_LayerBet_.h"
#include "_CardBaCay_.h"
#include "_Chat_inGame_.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace Sfs2X;

class Lieng : public CCLayer,public PlayerCallBack{
private:
    string EXT_EVENT_LISTCARD_NTF ;
    string EXT_EVENT_START ;
    string EXT_EVENT_END ;
    string EXT_EVENT_READY_REQ ;
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
    
    string _list_user;
    string _list_cards;
    
    bool flagChiaBai;
    bool real;
    string currentTo;
    string currentBetal;
    int minBet;
	int my_To;
    
    LayerBaCayAvatar *layerAvatars;
	LayerButtonInGame *layerButtons;
	CardBaCay *layerCards;
	BetGame3Cay *layerBet;
	LayerChatInGame *layerChat;
    
public:
    Lieng();
    ~Lieng();
	void onExit();
    void createBackgrounds();
    void createAvatars();
    void createButtons();
	void createNumbers();
	void createLayerBet();
	void createCards();

    //Các hàm xử lý
    void action_UpdateListUser(string lsUser);
    void action_UserRejoinGame(string lsUser);
    void action_LatBai(string listCard,string uid, bool tua);
    
    void action_GameBetNTF(string uid, string gameBet);
    void action_To(string uid,string betal);
    
	bool checkPlaying(string _list);
	void moveButtonRight();
	void resetButtonLocation();
    
    void whenUserReady(string uid);
    void whenUserUnready(string uid);
    void whenGameStart();
    void whenResuiltGame(string rg);
    void whenGameEnd();
	void whenUserBet(string uid, long gameBet);
    
	Button* createButtonWithTitle_Pos(const char *pName, CCPoint pPoint);
	Button* getButtonByTag(int pTag);

    //Các sự kiện Button trong game
    void btn_ready_click(CCObject *sender, TouchEventType type);
    void btn_Unready_click(CCObject *sender, TouchEventType type);
    void btn_XemBai_click(CCObject *sender, TouchEventType type);
    void btn_NanBai_click(CCObject *sender, TouchEventType type);
    void btn_To_click(CCObject *sender, TouchEventType type);
    void btn_Up_click(CCObject *sender, TouchEventType type);
    void btn_Theo_click(CCObject *sender, TouchEventType type);
    
	void callBackFunction_LatBai(CCNode *pSend);
	void callBackFuntion_Endgive(CCNode *pSend);

    //Server
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

};

#endif /* defined(__iCasinov2__Lieng__) */
