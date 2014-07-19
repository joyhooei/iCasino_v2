
#ifndef __iCasinov2__LayerCardChan__
#define __iCasinov2__LayerCardChan__

#include "CardChan.h"
#include "cocos2d.h"
#include "mUtils.h"
#include <iostream>

using namespace std;
USING_NS_CC;

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

class _Layer_CardChan_ : public CCLayer
{
private:

	float w_cardhand;
	float h_cardhand;
	float w_card;
	float h_card;
	float goc;
	int _coutZorder;

	UILayer *uLayer;

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

	CCObject* m_callback;
	SEL_CallFuncN m_callbackListener;

public:
	_Layer_CardChan_();
	~_Layer_CardChan_();
	bool init();

	CREATE_FUNC(_Layer_CardChan_);

	void createAllCards();
	void resetAllCards();

	void setMyListCards(string listCards);
	void rotateListCards();
	void refreshListCard();
	void CardTouch(CCObject *pSender,TouchEventType type);

	void sortMyListCards(string listCards);
	void resortCard_CuaTri_Alluser(int pos);
	void animateCards(CCArray *P, float _left, float _bottom, float _kc);
	string findTypeCard(string number,string suite);
	string getNameCard(int number, int suite);

	void addCard_toCuaTri(CCNode* sender, void* data);
	void addCard_toDuoiTay_top(CCNode *sender, void *data);
	void swapZorder(CCArray* P1, CCArray* P2, int _count, bool _state);


	void removeAllCardFromArray(CCArray *P);

	void takeCards(int f_pos, int t_pos, string cardnu, string cardsu, int crdorg);
	void action_BocNoc(int t_pos,string cardnu, string cardsu);
	void action_AnCuaTren(int f_user, int t_user, string cardnu, string cardsu);
	void action_AnCuaTri(int f_user, int t_user, string cardnu, string cardsu);
	void action_ChiuBai(int f_user, int t_user, string cardnu, string cardsu);
	void action_TraCua(int f_user, int t_user, string cardnu, string cardsu);
	void action_TraCua_ME(int tpos, string cardnu, string cardsu);
	void action_TraCua_NOTME(int fpos, int tpos, string cardnu, string cardsu);

	void action_DanhBai(int f_user, string cardnu, string cardsu);
	void action_DanhBai_ME(string cardnu,string cardsu);
	void action_DanhBai_NOTME(int pos,string cardnu,string cardsu);

	void action_ChuyenBai(int f_user, int t_user, string cardnu, string cardsu);
	void action_ChuyenBai_ME(int pos, string cardnu, string cardsu);
	void action_ChuyenBai_NOTME(int pos, string cardnu, string cardsu);
	void action_ChuyenBai_Chiu(int pos, string cardnu, string cardsu);

	void action_An_U(int f_user, int t_user, string cardnu, string cardsu);

	CardChan* getCardFromPos_take(int pos);

	void doDisCards();
	void doChiuCard();

	void playSounds(string url);
	void setCallbackFunc(CCObject* target, SEL_CallFuncN callfun);
};

#endif 