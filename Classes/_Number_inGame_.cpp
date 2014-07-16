//
//  _Number_inGame_.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/16/14.
//
//

#include "_Number_inGame_.h"

LayerNumberInGame::~LayerNumberInGame() {
	CCLOG("~~~~LayerNumberInGame");
	arrPos.clear();
	arrNumberString.clear();
}
bool LayerNumberInGame::init() {
    if (!CCLayer::init()) return false;
    
    this->setAnchorPoint(ccp(0, 0));
	this->isRunning = false;
    
    return true;
}

void LayerNumberInGame::showNumberByPos(int pos, string numberString) {
	arrPos.push_back(pos);
	arrNumberString.push_back(numberString);

	if (!isRunning) {
		isRunning = true;
		this->scheduleOnce(schedule_selector(LayerNumberInGame::runAction), 1);
	}
}

void LayerNumberInGame::showNumberByPos(int pos, double numberDouble) {
	arrPos.push_back(pos);
	arrNumberDouble.push_back(numberDouble);

	if (!isRunning) {
		isRunning = true;
		this->scheduleOnce(schedule_selector(LayerNumberInGame::runAction2), 0.5);
	}
}

void LayerNumberInGame::runAction(float dt) {
	int demMe = 0;
	int demLeft = 0;
	int demRight = 0;
	int demTop = 0;

	for (int i = 0; i < arrPos.size(); i++)
	{
		int pos = arrPos.at(i);
		string numberString = arrNumberString.at(i);

		Number *number = new Number(numberString);
		CCPoint point;

		switch (pos) {
		case kUserLeft:
			point.setPoint(10, 175 + demLeft * number->getSize().height);
			demLeft++;
			break;

		case kUserRight:
			point.setPoint(WIDTH_DESIGN - number->getSize().width - 10, 175 + demRight * number->getSize().height);
			demRight++;
			break;

		case kUserTop:
			point.setPoint((WIDTH_DESIGN - number->getSize().width) / 2, 343 + demTop * number->getSize().height);
			demTop++;
			break;

		case kUserBot: case kUserMe:
			point.setPoint((WIDTH_DESIGN - number->getSize().width) / 2, 70 + demMe * number->getSize().height);
			demMe++;
			break;
		}
		number->setPositionStart(point);
		this->addChild(number);
	}
	
	arrPos.clear();
	arrNumberString.clear();

	this->isRunning = false;
	//this->scheduleOnce(schedule_selector(LayerNumberInGame::callbackShowNumber), 3);
}

void LayerNumberInGame::runAction2(float dt) {
	int demMe = 0;
	int demLeft = 0;
	int demRight = 0;
	int demTop = 0;

	for (int i = 0; i < arrPos.size(); i++)
	{
		int pos = arrPos.at(i);
		double numberDouble = arrNumberDouble.at(i);

		Number *number = new Number(numberDouble);
		CCPoint point;

		switch (pos) {
		case kUserLeft:
			point.setPoint(10, 175 + demLeft * number->getSize().height);
			demLeft++;
			break;

		case kUserRight:
			point.setPoint(WIDTH_DESIGN - number->getSize().width - 10, 175 + demRight * number->getSize().height);
			demRight++;
			break;

		case kUserTop:
			point.setPoint((WIDTH_DESIGN - number->getSize().width) / 2, 343 + demTop * number->getSize().height);
			demTop++;
			break;

		case kUserBot: case kUserMe:
			point.setPoint((WIDTH_DESIGN - number->getSize().width) / 2, 70 + demMe * number->getSize().height);
			demMe++;
			break;
		}
		number->setPositionStart(point);
		this->addChild(number);
	}

	arrPos.clear();
	arrNumberDouble.clear();

	this->isRunning = false;
}

void LayerNumberInGame::callbackShowNumber(float dt) {
	isRunning = false;
}