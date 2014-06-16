//
//  CustomTableViewCell.cpp
//  AppDemo
//
//  Created by DauA on 5/5/14.
//
//

#include "CustomTableViewCell.h"
USING_NS_CC;
void CustomTableViewCell::draw(){
    
}

void CustomTableViewCell::setRoomId(long idx){
    roomID = idx;
}
long CustomTableViewCell::getRoomId(){
    return roomID;
}

CustomTableViewCell::CustomTableViewCell(CCSize s) : CCTableViewCell()
{
	m_currSize= s;
	isSelected = false;
}

void CustomTableViewCell::setSelectedState( bool isSelected )
{
	this->isSelected = isSelected;
	if(isSelected){
		if( this->getChildByTag(tag_NodeColor)!=NULL )
			return;
		CCLayerColor* node = new CCLayerColor();
		node->setTag(tag_NodeColor);
		node->initWithColor( ccc4(0,0,0,255));
		node->setPosition(ccp(0, 0));
		node->setAnchorPoint(ccp(0, 0));
		node->setContentSize(m_currSize);
		node->setZOrder(-1);
		this->addChild(node);
	}else{
		this->removeChildByTag(tag_NodeColor, true);
	}
}

bool CustomTableViewCell::getSelectedState()
{
	return isSelected;
}

void CustomTableViewCell::setStringObject( string val )
{
	sValue = val;
}

string CustomTableViewCell::getStringObject()
{
	return sValue;
}
