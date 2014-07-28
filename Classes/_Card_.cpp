//
//  Card.cpp
//  iCasinoCard
//
//  Created by ;; on 5/8/14.
//
//
//
#include "_Card_.h"
//

Card::Card(const char *filename) {
    this->initWithFile(filename);
    initialize();
}

void Card::initialize() {
    this->setVisible(false);
    
    this->sizeCard = CCSizeMake(66, 88);
    this->isTouched = false;
    this->isClicked = false;
    this->isPhom = false;
    this->isEat =  false;
    
    this->scaleX = sizeCard.width / this->getContentSize().width;
    this->scaleY = sizeCard.height / this->getContentSize().height;
    
    this->setScaleCard(this->scaleX, this->scaleY);
    
    this->setOpacity(255);
    this->setColor(ccWHITE);
    // TienLen
    this->setRotation(0);
}

void Card::resetStatus() {
    initialize();
}

void Card::setTouched(bool isTouched) {
    this->isTouched = isTouched;
}

bool Card::getTouched() {
    return this->isTouched;
}

void Card::setClicked(bool isClicked) {
    this->isClicked = isClicked;
}

bool Card::getClicked() {
    return this->isClicked;
}

void Card::setPhom(bool isPhom) {
    this->isPhom = isPhom;
}

bool Card::getPhom() {
    return this->isPhom;
}

void Card::setEat(bool isEat) {
    this->isEat = isEat;
}

bool Card::getEat() {
    return this->isEat;
}

void Card::setSize(float wid, float hei) {
    this->sizeCard.setSize(wid, hei);
}

CCSize Card::getSize() {
    return this->sizeCard;
}

void Card::setURL(string url) {
    this->url = url;
}

string Card::getURL() {
    return this->url;
}

void Card::setID(int id) {
    this->id = id;
}

int Card::getID(){
    return this->id;
}

void Card::setScaleCard(float scaleX, float scaleY) {
    this->setScaleX(scaleX);
    this->setScaleY(scaleY);
}


CCSize Card::getScaleCard() {
    return CCSize(scaleX, scaleY);
}

float Card::getScaleCardX() {
    return this->scaleX;
}

float Card::getScaleCardY() {
    return this->scaleY;
}

void Card::setCardAte() {
    //this->setOpacity(180);
	this->setColor(ccc3(70, 255, 180));
}

