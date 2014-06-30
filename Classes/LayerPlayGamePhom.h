//
//  LayerPlayGamePhom.h
//  iCasino_v2
//
//  Created by Thanhhv on 5/14/14.
//
//

#ifndef __iCasino_v2__LayerPlayGamePhom__
#define __iCasino_v2__LayerPlayGamePhom__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "AllData.h"
#include "GameServer.h"
//
#include "_Background_inGame_.h"
#include "_Button_inGame_.h"
#include "_Avatar_inGame_.h"
#include "_Number_inGame_.h"
#include "_Card_inGame_.h"
#include "_Chat_inGame_.h"

#include "Requests/ExtensionRequest.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace boost;

class LayerPlayGamePhom : public CCLayer, public PlayerCallBack
{
private:
    enum EXT_RESPONSE {
        //
        EXT_SRVNTF_PUBLIC_MESSAGE = 0,
        EXT_SRVNTF_PRIVATE_MESSAGE,
        EXT_SRVNTF_GAME_MASTER_INFO,
        EXT_SRVNTF_READY,
        EXT_SRVNTF_PLAYER_LIST,
        EXT_SRVNTF_RECOMMENDED_CARDSETS,
        EXT_EVENT_START,
        EXT_EVENT_END,
        EXT_EVENT_GAME_RESULT,
        EXT_EVENT_LISTCARD_NTF,
        EXT_EVENT_COIN_NTF,
        EXT_SRVNTF_CURRENT_PLAYING_USER,
        EXT_SRVNTF_END_PLAYING_GAME,
        EXT_SRVNTF_GAME_INFO,
        EXT_EVENT_READY_RES,
        EXT_EVENT_READY_REQ,
        EXT_SRVNTF_USER_READY,
        EXT_SRVNTF_CARD_ORIGINATION,
        EXT_EVENT_RES_DRAW_CARD,
        EXT_EVENT_RES_TAKE_CARD,
        EXT_EVENT_RES_DISCARD,
        EXT_EVENT_RES_HANDOFF_PHOM,
        EXT_EVENT_RES_END_PLAYING,
        EXT_EVENT_RES_SET_BET,
        EXT_EVENT_RES_U,
        EXT_SRVNTF_CAN_TAKE,
        EXT_SRVNTF_PLAYER_REPLAY,
        EXT_SRVNTF_U_9,
        EXT_SRVNTF_COIN_CHANGE,
        EXT_EVENT_RES_ORDER_CARDS,
        //
        EXT_EVENT_REQ_JOIN_GAME,
        EXT_EVENT_REQ_ORDER_CARDS,
        EXT_EVENT_REQ_DRAW_CARD,
        EXT_EVENT_REQ_DISCARD,
        EXT_EVENT_REQ_TAKE_CARD,
        EXT_EVENT_REQ_HANDOFF_PHOM,
        EXT_EVENT_REQ_PUSH_CARD,
        EXT_EVENT_REQ_U,
        //
        CARD_ORIGINATION_BY_TAKEN = 1, // ăn được
        CARD_ORIGINATION_BY_DRAWN = 2, // bốc từ nọc
        CARD_ORIGINATION_BY_TRANSFERED = 3, // quân bài chuyển
        CARD_ORIGINATION_BY_DEALT = 4, // chia bài
        CARD_ORIGINATION_BY_HANDOFF = 5, // chia bài
        CARD_ORIGINATION_BY_PUSHED = 6, // chia bài
        CARD_ORIGINATION_BY_UNKOWN = 7, // chia bài
    };

	enum ACTION_LAST {
		DANH_BAI=1,
		BOC_BAI,
		AN_BAI,
		XEP_BAI,
		HA_PHOM,
		SAN_SANG,
		START_GAME,
		END_GAME
	};

    int actionLast;
    string myName;
    string currentPlaying;
	string listID_HaPhom;
    
    // mảng lưu các tên và thông tin tương ứng để hiển thị
    vector<string> arrName;
    vector<int> arrMoney;
    
	boost::shared_ptr<ISFSObject> param;
    LayerAvatarInGame   *layerAvatars;
    LayerCardInGame     *layerCards;
    LayerButtonInGame   *layerButtons;
    LayerNumberInGame   *layerNumbers;
    LayerChatInGame     *layerChats;
    int levelGame;

public:
    LayerPlayGamePhom();
    ~LayerPlayGamePhom();
	virtual void onExit();
    
    void createBackgrounds();
    void createAvatars();
    void createButtons();
    void createNumbers();
    void createCards();
    void createChats();
    
    void initGame();
    void resetGame();
	void playSound(string soundPath);
    
    int    convertResponseToInt(string inString);
    string convertResponseToString(int inInt);
    Button* createButtonWithTitle_Position(const char *title, CCPoint pPoint);
    Button* getButtonByTag(int tag);
    
    // actions
    void actionReady(CCObject *pSender, TouchEventType pType);
    void actionSortCards(CCObject *pSender, TouchEventType pType);
    void actionHitCards(CCObject *pSender, TouchEventType pType);
    void actionGiveCards(CCObject *pSender, TouchEventType pType);
    void actionEatCards(CCObject *pSender, TouchEventType pType);
    void actionHaPhom(CCObject *pSender, TouchEventType pType);
	void callbackHaPhom(float dt);
	void callbackHaPhom_stepByStep(float dt);
    void actionPush(CCObject *pSender, TouchEventType pType);
    void actionUUU(CCObject *pSender, TouchEventType pType);
    
    // event server
    virtual void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	virtual void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	virtual void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    
    void sendRequestJoinGame(float dt);
    vector<string> split(string &S, const char &str);
    
    void event_EXT_SRVNTF_PUBLIC_MESSAGE();
    void event_EXT_SRVNTF_PRIVATE_MESSAGE();
    void event_EXT_SRVNTF_GAME_MASTER_INFO();
    void event_EXT_SRVNTF_READY();
    void event_EXT_EVENT_READY_RES();
    void event_EXT_SRVNTF_PLAYER_LIST();
    void event_EXT_SRVNTF_RECOMMENDED_CARDSETS();
    void event_EXT_EVENT_START();
    void event_EXT_EVENT_END();
    void event_EXT_EVENT_GAME_RESULT();
    void event_EXT_EVENT_LISTCARD_NTF();
    void event_EXT_EVENT_COIN_NTF();
    void event_EXT_SRVNTF_CURRENT_PLAYING_USER();
    void event_EXT_SRVNTF_END_PLAYING_GAME();
    void event_EXT_SRVNTF_GAME_INFO();
    void event_EXT_SRVNTF_USER_READY();
    void event_EXT_SRVNTF_CARD_ORIGINATION();
    void event_EXT_EVENT_RES_DRAW_CARD();
    void event_EXT_EVENT_RES_TAKE_CARD();
    void event_EXT_EVENT_RES_DISCARD();
    void event_EXT_EVENT_RES_HANDOFF_PHOM();
    void event_EXT_EVENT_RES_END_PLAYING();
    void event_EXT_EVENT_RES_SET_BET();
    void event_EXT_EVENT_RES_U();
    void event_EXT_SRVNTF_CAN_TAKE();
    void event_EXT_SRVNTF_PLAYER_REPLAY();
    void event_EXT_SRVNTF_U_9();
};

#endif /* defined(__iCasino_v2__LayerPlayGamePhom__) */
