//
//  _Card_inGame_.h
//  iCasino_v2
//
//  Created by DauTV on 6/9/14.
//
//

#ifndef __iCasino_v2___NanBaCay___
#define __iCasino_v2___NanBaCay___

#include <iostream>
#include "cocos2d.h"
#include "AllData.h"
#include "CardChan.h"

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;
class Nan3Cay : public CCLayer{
private:
	CCSize sizeScreen;
	CCSize disTouchBegan;
	CCPoint pointTouchBegan;

	float bottomCard;
	float leftCard;
	float rightCard;

	float widthCard;
	float heightCard;

	float scaleApp;
	float startLeft;
	float startTop;

	//Nan 3 Cay
	float dx,dy;
	int _index,_where;
	bool isTouched;

	//Bat dau nan 3 cay
	float deltaX;
	float deltaY;
	float sX;
	float sY;
	float xcu;
	float ycu;

	int cardIndex;

	//Touch move
	int cardIndex_under;
	bool flag_move;
	int flag_left,flag_right;
	int count_move;

	//Touch end
	int vt;

	string arrCardTypes[4];
	CCArray *cardOnhand;

	UIButton *btnBack;

	CCObject* m_callback;
	SEL_CallFuncN m_callbackListener;

public:
	Nan3Cay();
	Nan3Cay(CCObject *pSender);
	~Nan3Cay();
	bool init();
	CREATE_FUNC(Nan3Cay);

	void initListCardHand(string lsCards);
	string findTypeCard(string card);
	vector<string> Dsplit(string &S,const char &str);

	bool isTouch(CardChan *card, CCPoint tap);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void btnBack_click(CCObject *psender, TouchEventType type);

	void movePockerFinish(CardChan *pCard,int pos);
	void closeLayerNanBai();

	void setCallbackFunc(CCObject* target, SEL_CallFuncN callfun);
};

#endif;