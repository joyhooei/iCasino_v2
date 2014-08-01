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
	string getTricks(string trick);
};
#endif
