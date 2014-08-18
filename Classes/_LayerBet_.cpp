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
    this->removeAllComponents();
    this->removeAllChildren();
}

bool BetGame3Cay::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));

	FrameBet *bme = FrameBet::create();
	FrameBet *spec = FrameBet::create();
	FrameBet *buser1 = FrameBet::create();
    FrameBet *buser2 = FrameBet::create();
    FrameBet *buser3 = FrameBet::create();
    FrameBet *buser4 = FrameBet::create();
    FrameBet *buser5 = FrameBet::create();
    FrameBet *buser6 = FrameBet::create();

	//FrameBet *bottom = FrameBet::create();

	bme->setPosition(ccp(440,70));
	bme->setScale(0.8);
	spec->setPosition(CCPointZero);
	buser1->setPosition(ccp(110,115));
	buser1->setScale(0.8);
	buser2->setPosition(ccp(110,350));
	buser2->setScale(0.8);
	buser3->setPosition(ccp(325, 383));
	buser3->setScale(0.8);
    buser4->setPosition(ccp(555, 383));
	buser4->setScale(0.8);
    buser5->setPosition(ccp(660, 390));
	buser5->setScale(0.8);
    buser6->setPosition(ccp(660, 220));
	buser6->setScale(0.8);

	bme->setTag(kuser0);
	spec->setTag(100);
	buser1->setTag(kuser1);
    buser2->setTag(kuser2);
    buser3->setTag(kuser3);
    buser4->setTag(kuser4);
    buser5->setTag(kuser5);
    buser6->setTag(kuser6);


	bme->setVisible(false);
	spec->setVisible(false);
    buser1->setVisible(false);
     buser2->setVisible(false);
     buser3->setVisible(false);
     buser4->setVisible(false);
     buser5->setVisible(false);
     buser6->setVisible(false);


	this->addChild(bme);
	this->addChild(spec);
	this->addChild(buser1);
    this->addChild(buser2);
    this->addChild(buser3);
    this->addChild(buser4);
    this->addChild(buser5);
    this->addChild(buser6);
	

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
	if(pos==-1)
		pos=100;
	if (this->getChildByTag(pos) == NULL) 
	{
		return NULL; 
	}
		return (FrameBet*)this->getChildByTag(pos);

}

void BetGame3Cay::setVisibleAllFrameBet()
{
	getFrameBetByPos(kuser0)->setVisible(false);
	getFrameBetByPos(kuser1)->setVisible(false);
	getFrameBetByPos(kuser2)->setVisible(false);
	getFrameBetByPos(kuser3)->setVisible(false);
    getFrameBetByPos(kuser4)->setVisible(false);
    getFrameBetByPos(kuser5)->setVisible(false);
    getFrameBetByPos(kuser6)->setVisible(false);
}

void BetGame3Cay::setResuit4AllUser(int pos, string resuilt, string score){
	float x = -1, y = -1;
	switch(pos){
	case kuser0:
		x = 490;
		y = 50;
		break;
	case kuser1:
        x = 160;
		y = 155;
		break;
	case kuser2:
		x = 160;
		y = 325;
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
        x = 630;
        y = 340;
        break;
    case kuser6:
        x = 635;
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