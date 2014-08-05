//
//  FrameBet.cpp
//  iCasinov2
//
//  Created by DauA on 5/26/14.
//
//

#include "FrameBet.h"

//constructor default
FrameBet::FrameBet():iconXu(NULL),frame(NULL),money(NULL){
    
}

//Deconstructor
FrameBet::~FrameBet(){
    if (iconXu)
    {
		iconXu->release();
		iconXu = NULL;
    }

	if (frame)
	{
		frame->release();
		frame = NULL;
	}
	if (money)
	{
		money->release();
		money = NULL;
	}

	CCLOG("FrameBet Deconstructor");
}

//init
bool FrameBet::init(){
    if(!CCLayer::init()){
        return false;
    }
    this->setAnchorPoint(ccp(0,0));
    frame = UIImageView::create();
    frame->loadTexture("frame_Bet.png");
    frame->setAnchorPoint(ccp(0,0));
    frame->setPosition(ccp(10,0));
    this->addChild(frame);
    
    iconXu = CCSprite::create("icon_money.png");
    iconXu->setAnchorPoint(ccp(0,0));
    iconXu->setPosition(ccp(0,0));
    this->addChild(iconXu);
    
    money = UILabel::create();
    money->setPosition(ccp(10,frame->getContentSize().height/2));
    money->setFontSize(16);
    money->setAnchorPoint(ccp(0,0.5));
    if(money->getContentSize().width>frame->getContentSize().width){
        frame->setScaleX((money->getContentSize().width+15)/frame->getContentSize().width);
        money->setScaleX(1/frame->getScaleX());
        money->setPosition(ccp(10/frame->getScaleX(),frame->getContentSize().height/2));
    }
    frame->addChild(this->money);
    return true;
}

// Set Frame size
void FrameBet::setFrameSize(float toSize){
    float y = frame->getContentSize().width;
    if(toSize*8>y){
        frame->setScaleX(toSize*8/y);
        frame->setContentSize(CCSizeMake(toSize*8, frame->getContentSize().height));
    }
    else{
    }
}

// SetValue Bet
void FrameBet::setValueBet(std::string value){
    money->setText(value);
	money->setTextHorizontalAlignment(CCTextAlignment::kCCTextAlignmentRight);
    if(money->getContentSize().width>frame->getContentSize().width){
        frame->setScaleX((money->getContentSize().width+15)/frame->getContentSize().width);
        money->setScaleX(1/frame->getScaleX());
        money->setPosition(ccp(10/frame->getScaleX(),frame->getContentSize().height/2));
    }
}

float FrameBet::getKc_width(){
    return frame->getContentSize().width*frame->getScaleX()+15;
}




