//
//  LayerBet_BaCayChuong.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerBet_BaCayChuong.h"
#include "GameServer.h"
#include "Requests/ExtensionRequest.h"

using namespace Sfs2X;
using namespace cocos2d;
//using namespace CocosDenshion;


LayerBet_BaCayChuong::LayerBet_BaCayChuong()
{
	lblMoney=NULL;
	sliderMoney=NULL;
	spriteMoney=NULL;
}

LayerBet_BaCayChuong::~LayerBet_BaCayChuong()
{
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerBet_BaCayChuong::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCreate", LayerBet_BaCayChuong::onButtonCreate);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerBet_BaCayChuong::onButtonClose);
	return NULL;
}

void LayerBet_BaCayChuong::onButtonCreate(CCObject* pSender)
{
	CCLOG("mTip: %s", lblMoney->getString());
	int gameBet = 1000;
	if(strcmp(lblMoney->getString(), "") != 0){
		gameBet = atoi(lblMoney->getString());
	}
	//EXT_EVENT_GAME_BET_REQ = "gbr";
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutInt("gbv", gameBet);
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest("gbr",params,lastRoom));
	GameServer::getSingleton().getSmartFox()->Send(request);
	this->removeFromParentAndCleanup(true);
}

void LayerBet_BaCayChuong::onButtonClose(CCObject* pSender)
{
	CCLOG("onButtonClose");
	this->removeFromParentAndCleanup(true);
}

void LayerBet_BaCayChuong::valueChanged(CCObject *sender, CCControlEvent controlEvent){
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
bool LayerBet_BaCayChuong::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	//CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sliderMoney", CCControlSlider *, sliderMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sMoney", CCSprite *, spriteMoney);
	//    sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerBet_BaCayChuong::valueChanged), CCControlEventValueChanged);
	return true;
}

void LayerBet_BaCayChuong::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	CCLOG("Imhere onNodeLoaded");
	int max = 0;
	int minBet = 0;

	if (GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue() != NULL) {
		max = (int) *GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue();
	}

	if (GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue() != NULL) {
		minBet =atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue()->c_str());
	}

	CCLOG("max  = %d", max);
	CCLOG("min bet: %d", minBet);

	//sliderMoney
	sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerBet_BaCayChuong::valueChanged), CCControlEventValueChanged);
	sliderMoney->setMinimumValue(minBet);
	sliderMoney->setMaximumValue(max);
	sliderMoney->setValue(1000);
}