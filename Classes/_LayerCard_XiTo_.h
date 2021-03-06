
//
//  _LayerCard_XiTo_.h
//  iCasinov2
//
//  Created by DauA on 6/28/14.
//
//

#ifndef __iCasinov2__LayerCard_XiTo__
#define __iCasinov2__LayerCard_XiTo__

#include <iostream>
#include "cocos2d.h"
#include "AllData.h"

using namespace cocos2d;
using namespace std;

class LayerCardXiTo : public CCLayer
{
public:
	~LayerCardXiTo();
	void onExit();
	bool init();
	CREATE_FUNC(LayerCardXiTo);

	void initGame();
	void resetGame();

	void givePocker();
	void giveDeal(CCArray *P, float _width, float _height, float _left, float _bottom, int num);
	void givePocker_next();

	void setListUser(string listusers);
	void setMyName(string myname);
	void setMyListCard(string listcards);

	int getPosUserByName(string uid);

	string convertCard(string strCard);
	string findTypeCard(string listCards);

	void deleteAllCard_FromArray(CCArray *P);

	void setCallbackFunc(CCObject* target, SEL_CallFuncN callfun);
private:
	vector<string> arrCardTypes;

	string myListCards;
	string listUser;
	string myName;

	int count_give;

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

	CCArray *CARD_ME;
	CCArray *CARD_LEFT_BOTTOM;
	CCArray *CARD_LEFT_TOP;
	CCArray *CARD_RIGHT_BOTTOM;
	CCArray *CARD_RIGHT_TOP;

	CCObject* m_callback;
	SEL_CallFuncN m_callbackListener;
};

#endif
