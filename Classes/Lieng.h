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
#include "AllData.h"
#include "_Avatar_inGame_.h"
#include "FrameBet.h"

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

    // Vi tri cac la bai
    float left_Left;
    float left_Right;
    float left_Top ;
    float height_card_notme ;
    float width_card_notme ;
    
    float bottom_card_l_r ;
    float bottom_card_top ;
    
    float left_Me ;
    float width_card_me ;
    float height_card_me ;
    float bottom_me ;
    
    string _list_user;
    string _list_cards;
    string arrCardTypes[4];
    
    bool flagChiaBai;
    bool real;
    string currentTo;
    string currentBetal;
    int demChiaBai;
    int minBet;
	int my_To;
    // Các Button trong game
    //Các button trong game
    UILayer *uLayer;
    UIButton *btnReady;
    UIButton *btnUnReady;
    UIButton *btnXemBai;
    UIButton *btnNanBai;
    UIButton *btnTo;
    UIButton *btnUp;
    UIButton *btnTheo;
    
    LayerAvatarInGame *layerAvatars;
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
    Lieng();
    ~Lieng();
    void createBackgrounds();
    void createAvatars();
    void createButtons();
    void createNumbers();

    vector<string> Dsplit(string &S,const char &str);
    //Các hàm xử lý
    void action_UpdateListUser(string lsUser);
    void action_UserRejoinGame(string lsUser);
    void action_LatBai(string listCard,string uid, bool tua);
    void action_ChiaBai();
    void action_AddCard4User(CCArray *P,float _widtd, float _height, float toX, float toY, int countUSer);
    void action_GameBetNTF(string uid, string gameBet);
    void action_To(string uid,string betal);
    
    string find_ChuPhong(string listUser);
    string findTypeCard(string card);
	bool checkPlaying(string _list);
	void moveButtonRight();
	void resetButtonLocation();
    //Reconnect
    void restoreListCard(CCArray *P,float _widtd, float _height, float _left, float _bottom);
    
    int getPosUserByName(string uid,string _list_user);
    
    void whenUserReady(string uid);
    void whenUserUnready(string uid);
    void whenGameStart();
    void whenResuiltGame(string rg);
    void whenGameEnd();
	void whenUserBet(string uid, long gameBet);
    
    // Tạo các list cards
    void createCardMe(string lc);
    void createCardLeft(string lc);
    void createCardRight(string lc);
    void createCardTop(string lc);
    void deleteAllCardFromArray(cocos2d::CCArray *P);
    
    //Các sự kiện Button trong game
    void btn_ready_click(CCObject *sender, TouchEventType type);
    void btn_Unready_click(CCObject *sender, TouchEventType type);
    void btn_XemBai_click(CCObject *sender, TouchEventType type);
    void btn_NanBai_click(CCObject *sender, TouchEventType type);
    void btn_To_click(CCObject *sender, TouchEventType type);
    void btn_Up_click(CCObject *sender, TouchEventType type);
    void btn_Theo_click(CCObject *sender, TouchEventType type);
    
	void callBackFunction_LatBai(CCNode *pSend);

    //Server
    void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
    void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

};

#endif /* defined(__iCasinov2__Lieng__) */
