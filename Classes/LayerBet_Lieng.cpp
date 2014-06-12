﻿//
//  LayerBet_Lieng.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerBet_Lieng.h"
#include "Requests/ExtensionRequest.h"
#include "GameServer.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerBet_Lieng::LayerBet_Lieng()
{
    lblMoney=NULL;
    sliderMoney=NULL;
    spriteMoney=NULL;
    
    lblTitle1=NULL;
    lblTitle2=NULL;
    lblTitle3=NULL;

}

LayerBet_Lieng::~LayerBet_Lieng()
{
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerBet_Lieng::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCreate", LayerBet_Lieng::onButtonCreate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerBet_Lieng::onButtonClose);
    return NULL;
}

void LayerBet_Lieng::onButtonCreate(CCObject* pSender)
{
    CCLOG("mTip: %s", lblMoney->getString());
	int gameBet = 1000;
	if (strcmp(lblMoney->getString(),"") != 0)
	{
		gameBet = atoi(lblMoney->getString());
	}

	CCLOG("Game Bet = %d", gameBet);
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutInt("gbv",gameBet);
	params->PutInt("bet",1);
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest("gbr",params,lastRoom));
	GameServer::getSingleton().getSmartFox()->Send(request);
	this->removeFromParentAndCleanup(true);

	//EXT_EVENT_GAME_BET_REQ = "gbr";
}

void LayerBet_Lieng::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
	this->removeFromParentAndCleanup(true);
}

void LayerBet_Lieng::valueChanged(CCObject *sender, CCControlEvent controlEvent){
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float percent =pSlider->getValue()-pSlider->getMinimumValue();
    float max = pSlider->getMaximumValue() - pSlider->getMinimumValue();
    float delta = max;
    float posX =pSlider->getPositionX();
    float sliderWidth =pSlider->getContentSize().width;
    spriteMoney->setPosition(ccp(posX+percent*(sliderWidth/delta), spriteMoney->getPositionY()));
    lblMoney->setString( CCString::createWithFormat("%.0f xu", ceil(pSlider->getValue()))->getCString() );
}

// CCBMemberVariableAssigner interface
bool LayerBet_Lieng::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sliderMoney", CCControlSlider *, sliderMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sMoney", CCSprite *, spriteMoney);
    //
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle1", CCLabelTTF *, lblTitle1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle2", CCLabelTTF *, lblTitle2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblTitle3", CCLabelTTF *, lblTitle3);
    return true;
}

void LayerBet_Lieng::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    //sliderMoney
    return;
}

void LayerBet_Lieng::setInfoBet(int _minBet,int _myBet){
	sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerBet_Lieng::valueChanged), CCControlEventValueChanged);
	int max;
	if (GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue() != NULL) {
		max = (int) *GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue();
	}

	lblTitle1->setString(("Mức tố hiện tại: "+boost::to_string(_minBet)).c_str());
	lblTitle2->setString(("Lượt tố trước của bạn: "+boost::to_string(_myBet)).c_str());
	lblTitle3->setString(("Bạn cần tố thêm: "+boost::to_string(_minBet-_myBet)).c_str());

	sliderMoney->setMinimumValue(_minBet);
	sliderMoney->setMaximumValue(max);
	sliderMoney->setValue(1000);
}