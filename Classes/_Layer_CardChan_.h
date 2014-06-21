#pragma once
#ifndef __iCasinov2__LayerCardChan__
#define __iCasinov2__LayerCardChan__

#include "CardChan.h"
#include "LayerChanGame.h"
#include "cocos2d.h"
#include "mUtils.h"
#include <iostream>

using namespace std;
USING_NS_CC;

class _Layer_CardChan_ : public CCLayer
{
private:
	CCArray *allCards;
public:
	_Layer_CardChan_();
	~_Layer_CardChan_();
	bool init();

	void initAllCard();
	void resetGame();

	void rotateListCard();
	void setMyListCard();

};

#endif 