//
//  _CardBaCay_.h
//  iCasino_v2
//
//  Created by DauA on 6/24/14.
//
//

#ifndef __iCasino_v2__CardBaCay__
#define __iCasino_v2__CardBaCay__

#include <iostream>
#include "cocos2d.h"
#include "AllData.h"

using namespace cocos2d;
using namespace std;

class CardBaCay : public CCLayer
{
public:
	~CardBaCay();
	void onExit();
	bool init();
	CREATE_FUNC(CardBaCay);

	void initGame();
	void resetGame();

	void givePocker();
	void give_next(CCArray *P, float _width, float _height, float _left, float _bottom, int count);

	//turn up all cards
	void turnUpAllCards(string lc, int pos);
	void turnUpAllCards_Pos(string lc, CCArray *P, float _width, float _height, float _left, float _bottom);

	void createCardBack(int pos);
	void createListCard_Back(CCArray *P, float _width, float _height, float _left, float _bottom);
	void deleteAllCards_FromArray(CCArray *P);

	string findTypeCardByID(string card);

	void setListUser(string listuser);
	void setMyName(string name);

	int getPosUserByName(string pName);

	void setCallbackFunc(CCObject* target, SEL_CallFuncN callfun);

	CCArray* getListCards_Me();
	CCArray* getListCards_Left();
	CCArray* getListCards_Right();
	CCArray* getListCards_Top();
private:
	vector<string> arrCardTypes;

	string myListCards;
	string listUser;
	string myName;

	float leftMe;
	float leftLeft;
	float leftRight;
	float leftTop;
	float bottomMe;
	float bottomLeft;
	float bottomTop;

	float h_card_me;
	float h_card_notme;
	float w_card_me;
	float w_card_notme;

	int count_give;

	CCArray *CARD_ME;
	CCArray *CARD_LEFT;
	CCArray *CARD_RIGHT;
	CCArray *CARD_TOP;

	CCObject* m_callback;
	SEL_CallFuncN m_callbackListener;
};

#endif