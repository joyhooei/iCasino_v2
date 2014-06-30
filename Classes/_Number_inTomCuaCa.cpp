//
//  _Number_inGame_.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/16/14.
//
//

#include "_Number_inTomCuaCa.h"

NumberInTomCuaCa::~NumberInTomCuaCa() {
	CCLOG("~~~~LayerNumberInGame");
	arrPos.clear();
	arrNumberString.clear();
}
bool NumberInTomCuaCa::init() {
    if (!CCLayer::init()) return false;
    
    this->setAnchorPoint(ccp(0, 0));
	this->isRunning = false;
    
    return true;
}

void NumberInTomCuaCa::showNumberByPos(int pos, string numberString) {
	arrPos.push_back(pos);
	arrNumberString.push_back(numberString);

	if (!isRunning) {
		isRunning = true;
		this->scheduleOnce(schedule_selector(NumberInTomCuaCa::runAction), 1);
	}
}

void NumberInTomCuaCa::runAction(float dt) {
	int demMe = 0;
	int demLeft = 0;
	int demRight = 0;
	int demTop = 0;
	int demBot=0;

	for (int i = 0; i < arrPos.size(); i++)
	{
		int pos = arrPos.at(i);
		string numberString = arrNumberString.at(i);

		Number *number = new Number(numberString);
		CCPoint point;

		switch (pos) {
		case kUserLeft:
			point.setPoint(650, 250 + demLeft * number->getSize().height);
			demLeft++;
			break;

		case kUserRight:
			point.setPoint(700-number->getSize().width/2, 80 + demRight * number->getSize().height);
			demRight++;
			break;

		case kUserTop:
			point.setPoint(50, 250 + demTop * number->getSize().height);
			demTop++;
			break;

		case kUserBot: 
			point.setPoint(30, 80 + demTop * number->getSize().height);
			demBot++;
			break;

		case kUserMe:
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

void NumberInTomCuaCa::callbackShowNumber(float dt) {
	isRunning = false;
}