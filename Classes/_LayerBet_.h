//
//  _LayerBet_.h
//  iCasino_v2
//
//  Created by DauA on 6/26/14.
//
//

#ifndef __iCasino_v2__LayerBet__
#define __iCasino_v2__LayerBet__

#include <iostream>
#include "cocos2d.h"
#include "FrameBet.h"

USING_NS_CC;
using namespace std;
class BetGame3Cay : public CCLayer
{
private:
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

	CCLayer *layerResuilt;
public:
	~BetGame3Cay();
	virtual void onExit();
	virtual bool init();
	CREATE_FUNC(BetGame3Cay);

	FrameBet* getFrameBetByPos(int pos);
	void setVisibleAllFrameBet();
	void setResuit4AllUser(int pos, string resuilt, string score);
	CCLayer* getLayerResuilt();
};
#endif
