//
//  CardChan.cpp
//  AppDemo
//
//  Created by DauA on 5/13/14.
//
//

#include "CardChan.h"

CardChan::CardChan():id_card(0),flag(false),number(0),suite(0){

}

CardChan::~CardChan(){

}

bool CardChan::init(){
	if(!UIImageView::init()){
		return false;
	}
	flag = false;
	id_card = 0;
	number = 0;
	suite = 0;
	return true;
}

bool CardChan::getFlag(){
	return this->flag;
}

int CardChan::getID(){
	return this->id_card;
}

void CardChan::setFlag(bool b){
	this->flag = b;
}

void CardChan::setID(int n){
	this->id_card = n;
}

void CardChan::setSizeCard(float toWidth, float toHeight){
	this->setAnchorPoint(ccp(0.5,0));
	float oldWidth = this->getContentSize().width;
	float oldHeight = this->getContentSize().height;
	this->setScaleX(toWidth/oldWidth);
	this->setScaleY(toHeight/oldHeight);
	this->setSize(CCSizeMake(toWidth, toHeight));
}

void CardChan::setNumber(int num){
	number = num;
}

void CardChan::setSuite(int sui){
	suite = sui;
}

int CardChan::getNumber(){
	return number;
}

int CardChan::getSuite(){
	return suite;
}


