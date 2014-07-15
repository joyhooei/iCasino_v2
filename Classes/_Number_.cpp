//
//  Number.cpp
//  iCasinoCard
//
//  Created by Thanhhv on 5/9/14.
//
//

#include "_Number_.h"

Number::Number(string pNumberString) {
    this->numberString = pNumberString;
    init();
}

Number::Number(double pNumberDouble) {
	// dựa vào số double mà tạo ra chuỗi kí tự tương ứng (vd: 1.34e+006 -> "1340000")
	this->numberString = mUtils::convertMoneyFromDoubleToString(pNumberDouble);
	init();
}

Number::~Number(){}

bool Number::init(){
    if ( !CCLayer::init() )
        return false;

    this->setAnchorPoint(ccp(0, 0));
    this->setNumbersWithString(this->numberString);
    
    return true;
}

void Number::setNumbersWithString(string pNumberString) {
    removeAllChildrenWithCleanup(true);
    this->numberString = pNumberString;

	// trim
	pNumberString.erase(0, pNumberString.find_first_not_of(' '));
	pNumberString.erase(pNumberString.find_last_not_of(' ') + 1);

	int widNum = 32;
	int heiNum = 33;

	int length = pNumberString.length();
	setSize(widNum * length, heiNum);

	// kiểm tra xem dãy số có hợp lệ hay không?!
	// dãy số hợp lệ là dãy số:
	//	- các phần từ 1 trở đi đều là 1 c/số (từ 0->9)
	if (length == 0) return;
	else {
		for (int i = 1; i < length; i++)
		{
			if (pNumberString[i] < '0' || pNumberString[i] > '9') return;
		}
	}
	
    

    for (int i = 0; i < length; i++) {
        CCSprite *num = getNumberWithChar(pNumberString[i]);
		if (num == NULL) continue;
        num->setAnchorPoint(ccp(0, 0));
        num->setPosition(ccp(i * widNum, 0));
        this->addChild(num);
    }
}

void Number::startRunAction() {
    this->runAction(CCSequence::create(//CCDelayTime::create(0.7), 
									   CCMoveTo::create(0.5, ccp(this->pointStart.x, this->pointStart.y + 90)), 
									   CCDelayTime::create(3), 
									   CCRemoveSelf::create(), 
									   NULL));
}

void Number::startRunAction(float toY){
	this->runAction(CCSequence::create(//CCDelayTime::create(0.7), 
		CCMoveTo::create(0.5, ccp(this->pointStart.x, this->pointStart.y + toY)), 
		CCDelayTime::create(3), 
		CCRemoveSelf::create(), 
		NULL));	
}

CCSprite* Number::getNumberWithChar(char a) {
    
	CCSprite *numSprite =NULL;
    string url = "";
	boolean isRight = true;
    
    switch (a) {
        case '+':
            url = "cong.png";
            style = "";
            break;
            
        case '-':
            url = "tru.png";
            style = "lose/";
            break;
            
        default:
			if (a >= '0' && a <= '9'){
				ostringstream oss;
				oss << a;
				url += oss.str();
				url += ".png";
			}
			else {
				isRight = false;
			}
            break;
    }
    
    url = style + url;
    
	if (isRight)
	{
		numSprite = CCSprite::create(url.c_str());
		numSprite->setAnchorPoint(ccp(0, 0));
	}
    
    return numSprite;
}

// --------------
// setter, getter

void Number::setSize(int wid, int hei) {
    this->sizeThis.setSize(wid, hei);
}

CCSize Number::getSize() {
    return this->sizeThis;
}

void Number::setPositionStart(CCPoint pPointStart){
    this->pointStart = pPointStart;
    
    this->setPosition(pPointStart);
    startRunAction();
}

void Number::setPositionStart(CCPoint pPointStart, float toY)
{
	this->pointStart = pPointStart;

	this->setPosition(pPointStart);
	startRunAction(toY);
}

CCPoint Number::getPositionStart() {
    return this->pointStart;
}