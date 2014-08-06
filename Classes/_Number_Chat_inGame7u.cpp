//
//  _Number_inGame_.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/16/14.
//
//

#include "_Number_Chat_inGame7u.h"
#include "_Chat_.h"
Number_Chat_inGame7u::~Number_Chat_inGame7u() {
	CCLOG("~~~~Number_Chat_inGame7u");
	arrPos.clear();
	arrNumberString.clear();
}
bool Number_Chat_inGame7u::init() {
    if (!CCLayer::init()) return false;
    
    this->setAnchorPoint(ccp(0, 0));
	this->isRunning = false;
    
    return true;
}

void Number_Chat_inGame7u::showNumberByPos(int pos, string numberString) {
	arrPos.push_back(pos);
	arrNumberString.push_back(numberString);

	if (!isRunning) {
		isRunning = true;
		this->scheduleOnce(schedule_selector(Number_Chat_inGame7u::runAction), 1);
	}
}

void Number_Chat_inGame7u::showNumberByPos(int pos, double numberDouble) {
	arrPos.push_back(pos);
	arrNumberDouble.push_back(numberDouble);

	if (!isRunning) {
		isRunning = true;
		this->scheduleOnce(schedule_selector(Number_Chat_inGame7u::runAction2), 0.5);
	}
}

void Number_Chat_inGame7u::runAction(float dt) {
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
		number->setScale(0.6);
		CCPoint point;

		switch (pos) {
            case kuser0:
                point.setPoint(WIDTH_DESIGN/2-number->getSize().width/2+60,80);
                dem0++;
                break;
            case kuser1:
                point.setPoint(10,130);
                dem1++;
                break;
            case kuser2:
                point.setPoint(10, 280);
                dem2++;
                break;
            case kuser3:
                point.setPoint(210, 360);
                dem3++;
                break;
            case kuser4:
                point.setPoint(450, 360);
                dem4++;
                break;
            case kuser5:
                point.setPoint(650, 280);
                dem5++;
                break;
            case kuser6:
                point.setPoint(650,110);
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

void Number_Chat_inGame7u::runAction2(float dt) {
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
			CCLog("---%u",numberDouble);
		Number *number = new Number(numberDouble);
		if(numberDouble>1000000)
			{
				CCLog("---%u",numberDouble);
		number->setScale(0.5);
		}
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
                point.setPoint(10, 280);
                dem2++;
                break;
            case kuser3:
                point.setPoint(210, 360);
                dem3++;
                break;
            case kuser4:
                point.setPoint(450, 360);
                dem4++;
                break;
            case kuser5:
                point.setPoint(650, 280);
                dem5++;
                break;
            case kuser6:
                point.setPoint(650,110);
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

void Number_Chat_inGame7u::callbackShowNumber(float dt) {
	isRunning = false;
}
void Number_Chat_inGame7u::showChatByPos(int pos, string mes) {
    Chat *newMes = new Chat(mes, kuser0);
    newMes->setStatusByServer(false);
    
    CCPoint point;
    
    
    switch (pos) {
        case kuser0:
            point.setPoint(WIDTH_DESIGN/2, 120);
            break;
        case kuser1:
            point.setPoint((newMes->getSize().width)/2 , 230);
            break;
        case kuser2:
            point.setPoint((newMes->getSize().width)/2, 400);
            break;
        case kuser3:
            point.setPoint(180+newMes->getSize().width/2, 420);
            break;
        case kuser4:
            point.setPoint(400+newMes->getSize().width/2, 420);
            break;
        case kuser5:
            point.setPoint(WIDTH_DESIGN - newMes->getSize().width, 400);
            break;
        case kuser6:
            point.setPoint(WIDTH_DESIGN - newMes->getSize().width, 230);
            break;
            
        default:
            point.setPoint((WIDTH_DESIGN - newMes->getSize().width) / 2, (HEIGHT_DESIGN - newMes->getSize().height) / 2);
            newMes->setStatusByServer(true);
            break;
    }
    
    newMes->setPosition(point);
    this->addChild(newMes);
}