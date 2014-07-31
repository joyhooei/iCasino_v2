//
//  _Number_inGame_.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/16/14.
//
//

#include "_Number_inGame_7u.h"

LayerNumberInGame7u::~LayerNumberInGame7u() {
	CCLOG("~~~~LayerNumberInGame7u");
	arrPos.clear();
	arrNumberString.clear();
}
bool LayerNumberInGame7u::init() {
    if (!CCLayer::init()) return false;
    
    this->setAnchorPoint(ccp(0, 0));
	this->isRunning = false;
    
    return true;
}

void LayerNumberInGame7u::showNumberByPos(int pos, string numberString) {
	arrPos.push_back(pos);
	arrNumberString.push_back(numberString);

	if (!isRunning) {
		isRunning = true;
		this->scheduleOnce(schedule_selector(LayerNumberInGame7u::runAction), 1);
	}
}

void LayerNumberInGame7u::showNumberByPos(int pos, double numberDouble) {
	arrPos.push_back(pos);
	arrNumberDouble.push_back(numberDouble);

	if (!isRunning) {
		isRunning = true;
		this->scheduleOnce(schedule_selector(LayerNumberInGame7u::runAction2), 0.5);
	}
}

void LayerNumberInGame7u::runAction(float dt) {
	int dem0 = 0;
	int dem1 = 0;
	int dem2 = 0;
	int dem3 = 0;
    int dem4 = 0;
    int dem5 = 0;
    int dem6 = 0;

	for (int i = 0; i < arrPos.size(); i++)
	{
		int pos = arrPos.at(i);
		string numberString = arrNumberString.at(i);

		Number *number = new Number(numberString);
		CCPoint point;

		switch (pos) {
		case kuser0:
			point.setPoint(300, 200);
			dem0++;
			break;
            case kuser1:
                point.setPoint(400, 500);
                dem1++;
                break;
            case kuser2:
                point.setPoint(10, 175 + dem2 * number->getSize().height);
                dem2++;
                break;
            case kuser3:
                point.setPoint(10, 175 + dem3 * number->getSize().height);
                dem3++;
                break;
            case kuser4:
                point.setPoint(10, 175 + dem4 * number->getSize().height);
                dem4++;
                break;
            case kuser5:
                point.setPoint(10, 175 + dem5 * number->getSize().height);
                dem5++;
                break;
            case kuser6:
                point.setPoint(10, 175 + dem6 * number->getSize().height);
                dem6++;
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

void LayerNumberInGame7u::runAction2(float dt) {
	int dem0 = 0;
	int dem1 = 0;
	int dem2 = 0;
	int dem3 = 0;
    int dem4 = 0;
    int dem5 = 0;
    int dem6 = 0;

	for (int i = 0; i < arrPos.size(); i++)
	{
		int pos = arrPos.at(i);
		double numberDouble = arrNumberDouble.at(i);

		Number *number = new Number(numberDouble);
		CCPoint point;

		switch (pos) {
            case kuser0:
                point.setPoint(WIDTH_DESIGN/2-number->getSize().width/2,80);
                dem0++;
                break;
            case kuser1:
                point.setPoint(10,130);
                dem1++;
                break;
            case kuser2:
                point.setPoint(10, 175 + dem2 * number->getSize().height);
                dem2++;
                break;
            case kuser3:
                point.setPoint(10, 175 + dem3 * number->getSize().height);
                dem3++;
                break;
            case kuser4:
                point.setPoint(10, 175 + dem4 * number->getSize().height);
                dem4++;
                break;
            case kuser5:
                point.setPoint(10, 175 + dem5 * number->getSize().height);
                dem5++;
                break;
            case kuser6:
                point.setPoint(10, 175 + dem6 * number->getSize().height);
                dem6++;
                break;
                
		}
		number->setPositionStart(point);
		this->addChild(number);
	}

	arrPos.clear();
	arrNumberDouble.clear();

	this->isRunning = false;
}

void LayerNumberInGame7u::callbackShowNumber(float dt) {
	isRunning = false;
}