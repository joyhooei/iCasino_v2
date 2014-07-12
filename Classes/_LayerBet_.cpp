//
//  _LayerBet_.cpp
//  iCasino_v2
//
//  Created by DauA on 6/26/14.
//
//

#include "_LayerBet_.h"
#include "AllData.h"
#include "mUtils.h"

BetGame3Cay::~BetGame3Cay()
{

}

void BetGame3Cay::onExit()
{

}

bool BetGame3Cay::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));

	FrameBet *me = FrameBet::create();
	FrameBet *left = FrameBet::create();
	FrameBet *right = FrameBet::create();
	FrameBet *top = FrameBet::create();
	//FrameBet *bottom = FrameBet::create();

	me->setPosition(ccp(75,396));
	left->setPosition(ccp(109,278));
	right->setPosition(ccp(WIDTH_DESIGN-109-right->getKc_width(),278));
	top->setPosition(ccp(454, 440));

	me->setTag(kUserMe);
	left->setTag(kUserLeft);
	right->setTag(kUserRight);
	top->setTag(kUserTop);

	me->setVisible(false);
	left->setVisible(false);
	right->setVisible(false);
	top->setVisible(false);

	this->addChild(me);
	this->addChild(left);
	this->addChild(right);
	this->addChild(top);

	leftMe = 346;
	leftLeft = 145;
	leftRight = 563;
	leftTop = 352;
	bottomMe = 125.1; 
	bottomLeft = 240.2;
	bottomTop = 299.2;

	w_card_me = 54;
	w_card_notme = 48;
	h_card_me = 54 * 1.3;
	h_card_notme = 48 * 1.3;

	layerResuilt = CCLayer::create();
	layerResuilt->setAnchorPoint(ccp(0, 0));
	layerResuilt->setPosition(ccp(0, 0));
	this->addChild(layerResuilt);

	return true;
}

FrameBet* BetGame3Cay::getFrameBetByPos(int pos)
{
	if (this->getChildByTag(pos) == NULL) 
	{
		return NULL; 
	}
	return (FrameBet*)this->getChildByTag(pos);
}

void BetGame3Cay::setVisibleAllFrameBet()
{
	getFrameBetByPos(kUserMe)->setVisible(false);
	getFrameBetByPos(kUserLeft)->setVisible(false);
	getFrameBetByPos(kUserRight)->setVisible(false);
	getFrameBetByPos(kUserTop)->setVisible(false);
}

void BetGame3Cay::setResuit4AllUser(int pos, string resuilt, string score){
	float x = -1, y = -1;
	switch(pos){
	case kUserMe:
		x = 400;
		y = bottomMe - h_card_me / 2 - 10;
		break;
	case kUserLeft:
		x = leftLeft + (w_card_notme * 3) / 2;
		y = bottomLeft - h_card_notme / 2 - 10;
		break;
	case kUserRight:
		x = leftRight + (w_card_notme * 3) / 2;
		y = bottomLeft - h_card_notme / 2 - 10;
		break;
	case kUserTop:
		x = 400;
		y = bottomTop - h_card_notme / 2 - 10;
		break;
	}

	string txt = "";

	if (atoi(resuilt.c_str()) == 1)
	{
		txt = score + " điểm";
	} else {
		switch(atoi(resuilt.c_str())){
		case 2:
			txt = "Bộ Đội";
			break;
		case 3:
			txt = "Sáp";
			break;
		case 4:
			txt = "Liêng";
			break;
		case 5:
			txt = "Úp bỏ";
			break;
		}
	}

	Label *ketqua = Label::create();
	ketqua->setFontName("Marker Felt.ttf");
	ketqua->setText(txt);
	ketqua->setColor(ccc3(239,235,117));
	ketqua->setFontSize(22);
	ketqua->setPosition(ccp(x, y));
	layerResuilt->addChild(ketqua);
}

CCLayer* BetGame3Cay::getLayerResuilt(){
	return this->layerResuilt;
}