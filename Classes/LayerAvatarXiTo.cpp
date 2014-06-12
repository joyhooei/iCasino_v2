//
//  LayerAvatarXiTo.cpp
//  iCasinov2
//
//  Created by DauA on 5/28/14.
//
//

#include "LayerAvatarXiTo.h"
#include "AllData.h"
LayerAvatarXiTo::LayerAvatarXiTo(){
    
}

LayerAvatarXiTo::~LayerAvatarXiTo(){
    
}

bool LayerAvatarXiTo::init(){
    if(!CCLayer::init()){
        return false;
    }
    
    widthAvatar = 90;
	heightAvatar = 125;
    this->setAnchorPoint(ccp(0,0));
    
    bt_card_me = 87;
    bt_card_bottom = 211;
    bt_card_top = 350;
    
    lf_card_me = 280;
    lf_card_left_bottom = 113;
    lf_card_left_top = 178;
    
    //User_me
    me = new Avatar(false);
    me->setScaleX(widthAvatar/me->getSizeThis().width);
    me->setScaleY(heightAvatar/me->getSizeThis().height);
    me->setPosition(ccp(180,70));
    
    //User Left-Bottom
    left_bottom = new Avatar(false);
    left_bottom->setScaleX(widthAvatar/left_bottom->getSizeThis().width);
    left_bottom->setScaleY(heightAvatar/left_bottom->getSizeThis().height);
    left_bottom->setPosition(ccp(13,180));
    
    //User Right-Bottom
    right_bottom = new Avatar(false);
    right_bottom->setScaleX(widthAvatar/right_bottom->getSizeThis().width);
    right_bottom->setScaleY(heightAvatar/right_bottom->getSizeThis().height);
    right_bottom->setPosition(ccp(WIDTH_DESIGN-13-right_bottom->getSizeThis().width*right_bottom->getScaleX(),180));
    
    //User Left Top
    left_top = new Avatar(false);
    left_top->setScaleX(widthAvatar/left_top->getSizeThis().width);
    left_top->setScaleY(heightAvatar/left_top->getSizeThis().height);
    left_top->setPosition(ccp(84,330));
    
    //User Right Top
    right_top = new Avatar(false);
    right_top->setScaleX(widthAvatar/right_top->getSizeThis().width);
    right_top->setScaleY(heightAvatar/right_top->getSizeThis().height);
    right_top->setPosition(ccp(WIDTH_DESIGN-84-right_top->getSizeThis().width*right_top->getScaleX(),330));
    
    resetAll();
    
    this->addChild(me);
    this->addChild(left_bottom);
    this->addChild(right_bottom);
    this->addChild(left_top);
    this->addChild(right_top);
    
    return true;
}

void LayerAvatarXiTo::resetAll(){
    setFlag(user_me, false);
    setFlag(user_rightBottom, false);
    setFlag(user_rightTop, false);
    setFlag(user_leftTop, false);
    setFlag(user_leftBottom, false);
    
    setName(user_me, "");
    setName(user_rightBottom, "");
    setName(user_rightTop, "");
    setName(user_leftTop, "");
    setName(user_leftBottom, "");
    
    setMoney(user_me, "");
    setMoney(user_rightBottom, "");
    setMoney(user_rightTop, "");
    setMoney(user_leftTop, "");
    setMoney(user_leftBottom, "");

	this->getUserByPos(user_me)->setVisibleLayerInvite(true);
	this->getUserByPos(user_leftTop)->setVisibleLayerInvite(true);
	this->getUserByPos(user_leftBottom)->setVisibleLayerInvite(true);
	this->getUserByPos(user_rightTop)->setVisibleLayerInvite(true);
	this->getUserByPos(user_rightBottom)->setVisibleLayerInvite(true);
	
}

void LayerAvatarXiTo::setIcon(int pos,const char *url){
    //this->getUserByPos(pos)->setIcon(url);
}
void LayerAvatarXiTo::setFlag(int pos, bool isShow){
    this->getUserByPos(pos)->setFlag(isShow);
}
void LayerAvatarXiTo::setName(int pos,const char *name){
    this->getUserByPos(pos)->setName(name);
}
void LayerAvatarXiTo::setMoney(int pos,const char *money){
    this->getUserByPos(pos)->setMoney(money);
}

void LayerAvatarXiTo::stopAllTimer(){
    me->stopTimer();
    right_bottom->stopTimer();
    left_bottom->stopTimer();
    right_top->stopTimer();
    left_top->stopTimer();
}

void LayerAvatarXiTo::setUnReadyAllUser(){
	this->getUserByPos(user_me)->setReady(false);
	this->getUserByPos(user_leftBottom)->setReady(false);
	this->getUserByPos(user_leftTop)->setReady(false);
	this->getUserByPos(user_rightBottom)->setReady(false);
	this->getUserByPos(user_rightTop)->setReady(false);
}

void LayerAvatarXiTo::showNunberByPos(int pos, string numberString){
    Number *number = new Number(numberString);
    CCPoint point;
    
    switch (pos) {
        case user_rightTop:
            point.setPoint((WIDTH_DESIGN-number->getSize().width - lf_card_left_top), bt_card_top);
            break;
            
        case user_rightBottom:
            point.setPoint(WIDTH_DESIGN - number->getSize().width - lf_card_left_bottom, bt_card_bottom);
            break;
            
        case user_leftTop:
            point.setPoint(lf_card_left_top, bt_card_top);
            break;
            
        case user_leftBottom:
            point.setPoint(lf_card_left_bottom, bt_card_bottom);
            break;
            
        case user_me:
            point.setPoint(lf_card_me, bt_card_me);
            break;
    }
    number->setPositionStart(point);
    this->addChild(number);
}

Avatar* LayerAvatarXiTo::getUserByPos(int pos){
    switch (pos) {
        case user_me:
            return me;
            break;
        case user_rightBottom:
            return right_bottom;
            break;
        case user_rightTop:
            return right_top;
            break;
        case user_leftBottom:
            return left_bottom;
            break;
        case user_leftTop:
            return left_top;
            break;
        default:
            return NULL;
            break;
    }
}