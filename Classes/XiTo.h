//
//  XiTo.h
//  iCasinov2
//
//  Created by DauA on 5/28/14.
//
//

#ifndef __iCasinov2__XiTo__
#define __iCasinov2__XiTo__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "AllData.h"
#include "LayerAvatarXiTo.h"
#include "_Button_inGame_.h"
#include "_Card_.h"
#include "FrameBet.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace Sfs2X;

enum {
    GAME_TABLE_STATUS_BET_FOLD,
    GAME_TABLE_STATUS_BET_RAISE,
    GAME_TABLE_STATUS_BET_NONE,
    GAME_TABLE_STATUS_BET_QUATER,
    GAME_TABLE_STATUS_BET_HAFT,
    GAME_TABLE_STATUS_BET_FOLLOW,
    GAME_TABLE_STATUS_BET_DOUBLE,
    GAME_TABLE_STATUS_BET_ALL,
};

class XiTo : public CCLayer,public PlayerCallBack{
private:
    string EXT_EVENT_SELECT_OPEN_CARD_REQ;
    string EXT_EVENT_READY_REQ;
    string EXT_EVENT_RAISE_REQ;
    //* Vị trí các lá bài
    float bt_card_me;
    float bt_card_bottom;
    float bt_card_top;
    
    float lf_card_me;
    float lf_card_left_bottom;
    float lf_card_left_top;
    float lf_card_right_bottom;
    float lf_card_right_top;
    
    //Kích thước cá lá bài
    float w_card_me;
    float h_card_me;
    float w_card_notme;
    float h_card_notme;
    
	CCLayer *layerFrameBet;
	CCLayer *layerLabelVictype;

    UIImageView *frameBetTotal;
    UILabel *labelBetTotal;
	UIImageView *frameBet_Me;
	UILabel *labelBet_Me;
    
    
    LayerAvatarXiTo *layerAvatar;
    LayerButtonInGame *layerButtons;

	Label *suggest;

    int luotChia;
    int chiathem;
    int luotChiathem;
	int count_player;
    
    string _list_user;
    string my_DealCards;
    string list_dealCards_allUser;

    bool chooseCard;
    bool setDeal;
    bool flag_StartGame;

    vector<string> arrCardTypes;
    
    string uidTo;
    string typeTo;
    
    CCArray *CARD_ME;
    CCArray *CARD_LEFT_BOTTOM;
    CCArray *CARD_LEFT_TOP;
    CCArray *CARD_RIGHT_BOTTOM;
    CCArray *CARD_RIGHT_TOP;
    
    CCArray *B1;
    CCArray *B2;
    CCArray *B3;
    
public:
    XiTo();
    ~XiTo();
	void onExit();
    void createAvatar();
    void createBackground();
    void createButtons();
    void createFrameBets();

    static void setChooseCard(bool _state);
    string convertCard(string strCard);
    string findTypeCard(string listCards);
    
    int getPosUserByName(string uid, string _list_user);

    void updateUsers(string listUser);
	void setInfoAvatar(int pos, string name, int money, int vt, string aI, string avatar);

    void userReJoinGame(string roomInfo);
	
	void when_playerBet(string uid, long bet, long betValue, long betTotal);
	FrameBet* getFrameBetByTag(int fTag);
	void setBet_Inpos(int pos, CCArray *P, long bet, long betValue);

    void when_userReady(string uid);
    
    void popupXito(string myDealCard);
    void chiaBai();
    void giveDealCardsForPlayer(CCArray *P,float _left,float _width,float _height,float _bottom,int l);
    void OpenOneDealCards(string uid,string crdvl);
    void chiaThem1LaBai();
    void addCardsForUser(CCArray *P,float _width,float _height,float _top,float _left,string _img,int l);
    void restoreListCard_Reconnected(CCArray *P, string lc, bool _state, float _left, float _bottom, float _width, float _height);
    
	void setHide_AllFrameBet();

    void moveDealCard(Card *c,float _left, float _bottom);
    void moveDealCard_Me(string _lc);
	void moveDealCard_NotMe(int pos, string listcards);
	void moveDealCard_Pos(CCArray *P, string listcards, float _left, float _width, float _bottom);

    void setButtonBet(string uid, string lsBet);
    void openAllCard(string uid, string lc);
    
    void setIDListCard(CCArray *P,string lc);
    void setListCards(CCArray *P, string lc);
    void setDisplayValueListCard(CCArray *P,string lc);
    void setVictoryType(string uid,long vicType, string lc);
    void setMoneyAnimate(string uid, string amf);
    void displayPosWinner(int pos);

	string getTypeListCards(long type);
	void displaySuggestions();

	void createLabelVictype(int pos, long vicType);

    void sendOpenCard();
    void sendBetNTF(int typeBet);
    
    void whenEndGame();
    void deleteAllCardFromArray(cocos2d::CCArray *P);
    void setVisibleButtonPlay();
    
    void btn_ready_click(CCObject *sender, TouchEventType type);
	void btn_JoinGame_click(CCObject *sender, TouchEventType type);
	void btn_StandUp_click(CCObject *sender, TouchEventType type);

    void btn_To_click(CCObject *sender, TouchEventType type);
    void btn_Theo_click(CCObject *sender, TouchEventType type);
    void btn_Up_click(CCObject *sender, TouchEventType type);
    void btn_Nhuong_click(CCObject *sender, TouchEventType type);
    void btn_To1_2_click(CCObject *sender, TouchEventType type);
    void btn_To1_4_click(CCObject *sender, TouchEventType type);
    void btn_To_X2_click(CCObject *sender, TouchEventType type);
    void btn_To_All_click(CCObject *sender, TouchEventType type);
    
	Button* createButtonWithTitle_Pos(const char *pName, CCPoint pPoint);
	Button* getButtonByTag(int pTag);
	int getTagButton(int iTag);

    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

#endif /* defined(__iCasinov2__XiTo__) */
