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

	void playSound(string pathSound);

	int getPosUserByName(string pName);

	void setCallbackFunc(CCObject* target, SEL_CallFuncN callfun);


    
    CCArray* getListCards_0();
    CCArray* getListCards_1();
    CCArray* getListCards_2();
    CCArray* getListCards_3();
    CCArray* getListCards_4();
    CCArray* getListCards_5();
    CCArray* getListCards_6();
    
private:
	vector<string> arrCardTypes;

	string myListCards;
	string listUser;
	string myName;

    //
    float xCardPos_me;
    float yCardPos_me;
    float xCardPos_u1;
    float yCardPos_u1;
    float xCardPos_u2;
    float yCardPos_u2;
    float xCardPos_u3;
    float yCardPos_u3;
    float xCardPos_u4;
    float yCardPos_u4;
    float xCardPos_u5;
    float yCardPos_u5;
    float xCardPos_u6;
    float yCardPos_u6;

	float h_card_me;
	float h_card_notme;
	float w_card_me;
	float w_card_notme;

	int count_give;

    
    CCArray *CARD_0;
    CCArray *CARD_1;
    CCArray *CARD_2;
    CCArray *CARD_3;
    CCArray *CARD_4;
    CCArray *CARD_5;
    CCArray *CARD_6;

	CCObject* m_callback;
	SEL_CallFuncN m_callbackListener;
};

#endif