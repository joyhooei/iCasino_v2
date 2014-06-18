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

    for (int i = 0; i < length; i++) {
        CCSprite *num = getNumberWithChar(pNumberString[i]);
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

CCSprite* Number::getNumberWithChar(char a) {
    
    string url = "";
    
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
            ostringstream oss;
            oss << a;
            url += oss.str();
            url += ".png";
            break;
    }
    
    url = style + url;
    
    CCSprite *numSprite = CCSprite::create(url.c_str());
    numSprite->setAnchorPoint(ccp(0, 0));
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

CCPoint Number::getPositionStart() {
    return this->pointStart;
}