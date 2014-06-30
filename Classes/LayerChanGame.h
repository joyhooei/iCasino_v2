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
#include "AllData.h"
#include "_Avatar_inGame_.h"
#include "FrameBet.h"
#include "CardChan.h"
#include "NotificationCallback.h"

#define PI 3.141592653589
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace Sfs2X;

enum{
	CARD_ORIGINATION_CHIA_BAI = 0,
	CARD_ORIGINATION_BOC_NOC,
	CARD_ORIGINATION_AN_CUA_TREN,
	CARD_ORIGINATION_AN_CUA_TRI,
	CARD_ORIGINATION_CHIU,
	CARD_ORIGINATION_TRA_CUA,
	CARD_ORIGINATION_BY_DISCARD,
	// discard
	CARD_ORIGINATION_BY_DUOI,
	// đánh đi cây bài vừa bốc nọc ở cửa trì
	CARD_ORIGINATION_BY_AN_DUOI,
	CARD_ORIGINATION_BY_TRANSFER_TREN_2_DUOI
};

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
};

class LayerChanGame : public CCLayer,public PlayerCallBack, public NotificationCallBack{
private:
	//Recei
	string EXT_EVENT_READY_REQ;
	string EXT_EVENT_REQ_DISCARD;
	string EXT_EVENT_REQ_DRAW_CARD;
	string EXT_EVENT_REQ_TAKE_CARD;
	string EXT_EVENT_REQ_DUOI_CARD;
	string EXT_EVENT_REQ_TRENTAY_DETAIL;

	//send
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
	//xem noc
	string EXT_EVENT_REQ_NOC_DETAIL;
	//chiu thanh cong
	string EXT_EVENT_RES_CHIU_CARD;

	string _list_user;
	string mylistCard;
	string currentPlayer;

	bool gameStarted;
	bool flagChiaBai;

	int countDiscard;

	float w_cardhand;
	float h_cardhand;
	float w_card;
	float h_card;
	float goc;
	int _coutZorder;

	//Khoảng cách các lá bài cửa trì khi đã bốc đủ 8 lá
	//Ban đầu khoảng cách là w_card
	float kc_me;
	float kc_left;
	float kc_right;
	float kc_top;

	//Vi tri cac la bai cua tri
	float left_chi_left;
	float left_chi_right;
	float left_chi_me;
	float left_chi_top;

	float bottom_chi_left;
	float bottom_chi_right;
	float bottom_chi_me;
	float bottom_chi_top;

	float left_d_me;
	float left_d_top;
	float left_d_left;
	float left_d_right;

	float bottom_d_me;
	float bottom_d_left;
	float bottom_d_right;
	float bottom_d_top;

	int count_chiu_me;
	int count_chiu_left;
	int count_chiu_right;
	int count_chiu_top;

	LayerAvatarInGame *layerAvatars;

	UILayer *uLayer;
	UIButton *btnReady;
	UIButton *btnTake;
	UIButton *btnBoc;
	UIButton *btnEate;
	UIButton *btnDuoi;
	UIButton *btnU;
	UIButton *btnChiu;
	UILabel *lblDetail;


	CCArray *CARD_ME;

	CCArray *CARD_C_ME;
	CCArray *CARD_C_LEFT;
	CCArray *CARD_C_RIGHT;
	CCArray *CARD_C_TOP;

	CCArray *CARD_D_ME_top;
	CCArray *CARD_D_LEFT_top;
	CCArray *CARD_D_RIGHT_top;
	CCArray *CARD_D_TOP_top;

	CCArray *CARD_D_ME_bottom;
	CCArray *CARD_D_LEFT_bottom;
	CCArray *CARD_D_RIGHT_bottom;
	CCArray *CARD_D_TOP_bottom;

	CCArray *ALL_CARDS;

public:
	LayerChanGame();
	~LayerChanGame();
	void onExit();
	void createAllCards();
	void resetAllCards();
	void createButtons();
	void createAvatars();
	void sendRequestJoinGame(float dt);

	void notificationCallBack(bool isOK, int tag);

	vector<string> Dsplit(string &S,const char &str);
	int getPosUserByName(string uid,string _list_user);
	void updateUser(string list);

	void setMyListCards(string listCards);
	void rotateListCards();
	void sortMyListCards(string listCards);
	void resortCard_CuaTri_Alluser(int pos);
	void animateCards(CCArray *P, float _left, float _bottom, float _kc);
	string findTypeCard(string number,string suite);
	string getNameCard(int number, int suite);
	void whenUserTakeCards(long rscode);
	void setCurrentPlayer(string uid,int _count);
	void setUserReady(string uid);
	void error_AnBao(long rscode);
	void setEndGame();
	void whenConguoi_ChoU(string uid);
	void whenConguoi_Chiu(string uid);
	void XuongU();
	void resuiltGame(string resuilt);

	void deleteAllCardFromArray(CCArray *P);

	void takeCards(string f_user, string t_user, string cardnu, string cardsu, int crdorg);
	void action_BocNoc(string t_user,string cardnu, string cardsu);
	void action_AnCuaTren(string f_user, string t_user, string cardnu, string cardsu);
	void action_AnCuaTri(string f_user, string t_user, string cardnu, string cardsu);
	void action_ChiuBai(string f_user, string t_user, string cardnu, string cardsu);
	void action_TraCua(string f_user, string t_user, string cardnu, string cardsu);
	void action_TraCua_ME(int tpos, string cardnu, string cardsu);
	void action_TraCua_NOTME(int fpos, int tpos, string cardnu, string cardsu);

	void action_DanhBai(string f_user, string cardnu, string cardsu);
	void action_DanhBai_ME(string cardnu,string cardsu);
	void action_DanhBai_NOTME(int pos,string cardnu,string cardsu);

	void action_ChuyenBai(string f_user, string t_user, string cardnu, string cardsu);
	void action_ChuyenBai_ME(int pos, string cardnu, string cardsu);
	void action_ChuyenBai_NOTME(int pos, string cardnu, string cardsu);
	void action_ChuyenBai_Chiu(int pos, string cardnu, string cardsu);

	void action_An_U(string f_user, string t_user, string cardnu, string cardsu);

	CardChan* getCardFromPos_take(int pos);

	void refreshListCard();
	void addCard_toCuaTri(CCNode* sender, void* data);
	void addCard_toDuoiTay_top(CCNode *sender, void *data);
	void swapZorder(CCArray* P1, CCArray* P2, int _count, bool _state);

	void btn_ready_click(CCObject *sender, TouchEventType type);
	void btn_take_click(CCObject *sender, TouchEventType type);
	void btn_boc_click(CCObject *sender, TouchEventType type);
	void btn_eate_click(CCObject *sender, TouchEventType type);
	void btn_Duoi_click(CCObject *sender, TouchEventType type);
	void btn_U_Click(CCObject *sender, TouchEventType type);
	void btn_Chiu_Click(CCObject *sender, TouchEventType type);

	void hideAllButton();
	void resetPositionButton();

	void CardTouch(CCObject *pSender,TouchEventType type);

	void OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	void OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);

};

#endif /* defined(__iCasinov2__LayerChanGame__) */
