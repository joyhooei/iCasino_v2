//
//  LayerChanGame.h
//  iCasinov2
//
//  Created by DauA on 6/4/14.
//
//

#ifndef __iCasinov2__LayerChanGame__
#define __iCasinov2__LayerChanGame__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServer.h"
#include "_Avatar_inGame_.h"
#include "FrameBet.h"
#include "NotificationCallback.h"
#include "_Button_inGame_.h"
#include "_Layer_CardChan_.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace Sfs2X;

enum{
	ANBAO_REASON_NO_PROBLEM = 0,
	ANBAO_REASON_AN_CA_DOI_CHO,
	ANBAO_REASON_BO_AN_CUATREN_BUT_AN_CUATRI,
	ANBAO_REASON_DISCARD_SAMEAS_CUATREN_CUATRI_DUOITAY,
	ANBAO_REASON_ANCA_DANHCA,
	ANBAO_TREOTRANH,
	ANBAO_DANH_1_CA_CHI_DUOC_AN_CHAN,
	ANBAO_REASON_BOCHAN_ANCA,
	ANBAO_REASON_DANHBAI_GIONG_CHANCA_DA_AN,
	ANBAO_REASON_DOI_U_BACHTHUCHI,
	ANBAO_REASON_BOCHAN_DANHCHAN,   // bỏ không ăn 1 quân làm chắn, sau lại đánh đi đúng cây đó.
	ANBAO_REASON_BOCHAN_ANCHAN,
	ANBAO_REASON_BOCA_ANCA,
	ANBAO_REASON_DANHCA_ANCA,        // đánh đi 1 cạ sau đó lại ăn 1 cạ khác
	ANBAO_REASON_XECA_ANCA,           // xé cạ ăn cạ
	ANBAO_REASON_XECHAN_ANCA,        // xé chắn, ăn chắn
	ANBAO_REASON_DANH_ROILAI_AN,
	ANBAO_REASON_DANH_DI_DOI_CHAN,
	ANBAO_REASON_AN_ROILAI_DANH,
	ANBAO_REASON_ANCA_ROILAI_DANH_QUAN_CUNG_HANG,
	ANBAO_REASON_CHIUDUOC_NHUNG_LAI_ANTHUONG,
	ANBAO_REASON_AN_CHON_CA, 
	ANBAO_REASON_CO_CHAN_CAU_CA,     // có chắn cấu cạ: Lấy 1 quân trong chắn sẵn có để ăn cạ.
	ANBAO_REASON_U_NHUNG_KHONG_XUONG,  // Có thể Ù nhưng lại quên, hoặc ko xướng -> ngồi im không được xướng Ù nữa.
	ANBAO_REASON_HO_U_LAO,           // chưa Ù đã hô Ù - bị đền làng
	ANBAO_REASON_XUONG_SAI_CUOC,
};

class LayerChanGame : public CCLayer,public PlayerCallBack, public NotificationCallBack{
private:
	//Gửi đi
	string EXT_EVENT_READY_REQ;
	string EXT_EVENT_REQ_DISCARD;
	string EXT_EVENT_REQ_DRAW_CARD;
	string EXT_EVENT_REQ_TAKE_CARD;
	string EXT_EVENT_REQ_DUOI_CARD;
	string EXT_EVENT_REQ_TRENTAY_DETAIL;

	//Nhận về
	string EXT_SRVNTF_GAME_MASTER_INFO;
	string EXT_SRVNTF_PLAYER_LIST;
	string EXT_SRVNTF_USER_READY;
	string EXT_EVENT_START;
	string EXT_EVENT_END;
	string EXT_EVENT_LISTCARD_NTF;
	string EXT_SRVNTF_ONHAND_DETAILS;
	string EXT_SRVNTF_CURRENT_PLAYING_USER;
	string EXT_SRVNTF_NOC_COUNT;
	string EXT_SRVNTF_CARD_ORIGINATION;
	string EXT_EVENT_RES_DRAW_CARD;
	string EXT_EVENT_RES_DUOI_CARD;
	string EXT_EVENT_RES_TAKE_CARD;
	string EXT_SRVNTF_ANBAO;
	string EXT_EVENT_RES_DISCARD;
	string EXT_EVENT_GAME_RESULT;
	string EXT_SRVNTF_ONE_EXPECTING_U;
	string EXT_SRVNTF_ONE_EXPECTING_CHIU;
	string EXT_EVENT_RES_U;
	string EXT_EVENT_REQ_U;
	string EXT_EVENT_REQ_CHIU_CARD;
	//Xem nọc
	string EXT_EVENT_REQ_NOC_DETAIL;
	//Chíu thành công
	string EXT_EVENT_RES_CHIU_CARD;

	//Server gửi bản tin bốc cái
	string EXT_SRVNTF_BOC_CAI;
	//Client gửi yêu cầu bốc cái
	string EXT_EVENT_REQ_BOC_CAI;

	boost::shared_ptr<ISFSObject> param;
	string _list_user;
	string mylistCard;
	string currentPlayer;

	bool flagChiaBai;
	bool flagChiu;
	bool flagTraCuaToMe;
	bool flag_MeDraw;
	bool flag_AnBao;
	string reason_anbao;

	bool flag_Top;
	bool flag_Bottom;
	bool flag_Left;
	bool flag_Right;
	
	int countBocCai;
	int countDiscard;
	int countUser;
	int _noccount;
	
	LayerAvatarInGame *layerAvatars;
	LayerButtonInGame *layerButtons;

	_Layer_CardChan_ *layerCardChan;

	UILabel *lblDetail;
	CCProgressTimer *timer_Me;

public:
	LayerChanGame();
	~LayerChanGame();
	void onExit();
	
	void createAvatars();
	void createCards();
	void createButtons();
	void sendRequestJoinGame(float dt);

	void eventGameStart();
	void eventGameEnd();
	void eventGameResuilt();
	void eventBocCai();
	void eventListCard();
	void delayListCardFirst(CCObject *data);

	void eventDisCards();
	void eventOne_ExpectingU();

	void eventCard_NguoiU();
	void eventCard_ConTrongNoc();

	void notificationCallBack(bool isOK, int tag);

	int getPosUserByName(string uid,string _list_user);
	int getPosUserByName_ImGuess(string uid);

	string getNamePlayer(string uid);

	void updateUser(string list);
	void updateUser_ImGuess();
	void updateUser_ImPlayer();

	void updateUser2Player(vector<string> arrUser);
	void updateUser2Player_ImGuess(vector<string> arrUser);
	void updateUser2Player_ImPlayer(vector<string> arrUser);

	bool IamGuess();

	void setInfoAvatar(int pos,string aI,string name, int money, string url);

	void whenUserTakeCards(long rscode);
	void setCurrentPlayer(string uid,int _count);
	void setUserReady(string uid);
	void error_AnBao(long rscode, string uid);
	void setEndGame();
	
	void whenConguoi_ChoU(string uid);
	void whenConguoi_Chiu(string uid);
	void XuongU();

	void waitPlayer_ReqU(string uid, string lc);
	void wait10s(CCObject *data);

	void resuiltGame(string resuilt);
	void displayResuitGame(CCObject *data);

	void displayLayerKetQua(string resuilt);

	void eventTakeCards(string f_user, string t_user, string cardnu, string cardsu, int crdorg);
	void eventTakeCards_Showing(string f_user, string t_user, string cardnu, string cardsu, int crdorg);
	void eventTakeCards_Playing(string f_user, string t_user, string cardnu, string cardsu, int crdorg);

	void btn_ready_click(CCObject *sender, TouchEventType type);
	void btn_take_click(CCObject *sender, TouchEventType type);
	void btn_boc_click(CCObject *sender, TouchEventType type);
	void btn_eate_click(CCObject *sender, TouchEventType type);
	void btn_Duoi_click(CCObject *sender, TouchEventType type);
	void btn_U_Click(CCObject *sender, TouchEventType type);
	void btn_Chiu_Click(CCObject *sender, TouchEventType type);

	void hideAllButton();
	void resetPositionButton();

	void playSounds(string url);
	vector<string> splitString(string &S,const char &str);

	Button* createButtonWithTitle_Pos(const char *pName, CCPoint pPoint);
	Button* createButton_Chan(const char* pName, CCPoint pPoint, const char* pTexture,const char* pTextureSelect, int _posChild);
	Button* getButtonByTag(int pTag);

	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

	void startTimer_Me();
	void callbackTimer(CCNode *pSender);
	void stopTimer_Me();
	void callBackFunction_LatBai(CCNode *pSend);

	string identifyCuoc_sac(string _cuoc);
};

#endif /* defined(__iCasinov2__LayerChanGame__) */
