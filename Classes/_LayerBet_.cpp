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