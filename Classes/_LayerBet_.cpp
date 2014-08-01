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

    //
    xCardPos_me=370;
    yCardPos_me=175;
    xCardPos_u1=140;
    yCardPos_u1=205;
    xCardPos_u2=140;
    yCardPos_u2=302;
    xCardPos_u3=264;
    yCardPos_u3=345;
    xCardPos_u4=492;
    yCardPos_u4=345;
    xCardPos_u5=610;
    yCardPos_u5=302;
    xCardPos_u6=605;
    yCardPos_u6=205;
	
	w_card_me = 50;
	w_card_notme = 30;
	h_card_me = 50 * 1.3;
	h_card_notme = 30 * 1.3;

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
	case kuser0:
		x = 500;
		y = 70;
		break;
	case kuser1:
        x = 170;
		y = 160;
		break;
	case kuser2:
		x = 170;
		y = 340;
		break;
	case kuser3:
		x = 300;
		y = 310;
		break;
    case kuser4:
        x = 525;
        y = 310;
        break;
    case kuser5:
        x = 650;
        y = 330;
        break;
    case kuser6:
        x = 650;
        y = 160;
        break;
	}

	string txt = "";

	if (atoi(resuilt.c_str()) == 1)
	{
		vector<string> arr = mUtils::splitString(score,'|');

		txt = arr[0] + " - " + arr[1] + " " + getTricks(arr[2]);
		if (atoi(arr[1].c_str()) == 1)
		{
			txt = arr[0] + " - Át " + getTricks(arr[2]);
		}
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

	CCLabelTTF *ket =  CCLabelTTF::create(txt.c_str(), "fonts/UVNDaLat_R.TTF", 22.0);
	ket->setColor(ccc3(239,235,117));
	ket->setPosition(ccp(x, y));
	layerResuilt->addChild(ket);
}

CCLayer* BetGame3Cay::getLayerResuilt(){
	return this->layerResuilt;
}

string BetGame3Cay::getTricks(string trick){
	switch(atoi(trick.c_str())){
	case 0:
		return "Bích";
	case 1:
		return "Tép";
	case 2:
		return "Cơ";
	case 3:
		return "Dô";
	default:
		return "";
	}
	return "";
}