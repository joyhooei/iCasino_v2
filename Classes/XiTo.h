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
#include "FrameBet.h"
#include "CardChan.h"

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
    
    //Vị trí các FrameBet
    float left_FB_LT;
    float left_FB_LB;
    float bottom_TOP;
    float bottom_BOTTOM;
    
    UILayer *uLayer;
    UIButton *btnReady;
    //Úp - Theo - Nhường - Tố
    UIButton *btn_To;
    UIButton *btn_Theo;
    UIButton *btn_Up;
    UIButton *btn_Nhuong;
    
    //Tố 1/4 - Tố 1/2
    UIButton *btn_To1_4;
    UIButton *btn_To1_2;
    
    //Tố tất cả, Tố X2
    UIButton *btn_ToTatCa;
    UIButton *btn_ToX2;
    
    UIImageView *frameBetTotal;
    UILabel *labelBetTotal;
    FrameBet *frameBet_Right_Top;
    FrameBet *frameBet_Right_Bottom;
    FrameBet *frameBet_Left_Top;
    FrameBet *frameBet_Left_Bottom;
    
    
    LayerAvatarXiTo *layerAvatar;
    
    int luotChia;
    int chiathem;
    int luotChiathem;
    
    string _list_user;
    string my_DealCards;
    string list_dealCards_allUser;
    bool chooseCard;
    bool setDeal;
    bool flag_StartGame;
    string arrCardTypes[4];
    
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
    void createButton();
    
    static void setChooseCard(bool _state);
    vector<string> Dsplit(string &S,const char &str);
    string convertCard(string strCard);
    string findTypeCard(string listCards);
    
    int getPosUserByName(string uid, string _list_user);
    string find_RoomBoss(string list);
    void updateUsers(string listUser);
    void userReJoinGame(string roomInfo);
    
    void when_userReady(string uid);
    void when_playerBet(string uid, long bet, long betValue, long betTotal);
    
    void setPlayerBet(long bet, long betValue, int _pos);
    
    void popupXito(string myDealCard);
    void chiaBai();
    void giveDealCardsForPlayer(CCArray *P,float _left,float _width,float _height,float _bottom,int l);
    void OpenOneDealCards(string uid,string crdvl);
    void chiaThem1LaBai();
    void addCardsForUser(CCArray *P,float _width,float _height,float _top,float _left,string _img,int l);
    void restoreListCard_Reconnected(CCArray *P, string lc, bool _state, float _left, float _bottom, float _width, float _height);
    
    void moveDealCard(CardChan *c,float _left, float _bottom);
    void moveDealCard_Me(string _lc);
    void moveDealCard_Left_Bottom(string _lc);
    void moveDealCard_Left_Top(string _lc);
    void moveDealCard_Right_Bottom(string _lc);
    void moveDealCard_Right_Top(string _lc);
    
    void setButtonBet(string uid, string lsBet);
    void openAllCard(string uid, string lc);
    
    void setIDListCard(CCArray *P,string lc);
    void setListCards(CCArray *P, string lc);
    void setDisplayValueListCard(CCArray *P,string lc);
    void setVictoryType(string uid,long vicType, string lc);
    void setMoneyAnimate(string uid, string amf);
    
    void sendOpenCard();
    void sendBetNTF(int typeBet);
    
    void whenEndGame();
    void deleteAllCardFromArray(cocos2d::CCArray *P);
    void setVisibleButtonPlay();
    
    void btn_ready_click(CCObject *sender, TouchEventType type);
    void btn_To_click(CCObject *sender, TouchEventType type);
    void btn_Theo_click(CCObject *sender, TouchEventType type);
    void btn_Up_click(CCObject *sender, TouchEventType type);
    void btn_Nhuong_click(CCObject *sender, TouchEventType type);
    void btn_To1_2_click(CCObject *sender, TouchEventType type);
    void btn_To1_4_click(CCObject *sender, TouchEventType type);
    void btn_To_X2_click(CCObject *sender, TouchEventType type);
    void btn_To_All_click(CCObject *sender, TouchEventType type);
    
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
};

#endif /* defined(__iCasinov2__XiTo__) */
