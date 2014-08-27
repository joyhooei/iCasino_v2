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
#include "mUtils.h"
#include "AllData.h"

using namespace Sfs2X;
using namespace cocos2d;
//using namespace CocosDenshion;


LayerBet_BaCayChuong::LayerBet_BaCayChuong()
{
	lblMoney=NULL;
	sliderMoney=NULL;
	spriteMoney=NULL;

	_styleGame = kGameBaCayChuong;
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
	float sliderWidth =sliderMoney->getContentSize().width;
	gameBet = ceil(sliderMoney->getValue())*1000;

	CCLOG("gameBet= %d", gameBet);

	if (_styleGame == kGameBaCayChuong) {
		//EXT_EVENT_GAME_BET_REQ = "gbr";
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		params->PutInt("gbv", gameBet);
		boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest("gbr",params,lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	} else if (_styleGame == kGameCoTuong) {
		boost::shared_ptr<ISFSObject> parameter (new SFSObject());
		parameter->PutLong("amf", gameBet);
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest("umr", parameter, lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
	
	CCLog("Done!");
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
	lblMoney->setString( CCString::createWithFormat("%s xu", mUtils::convertMoneyEx(ceil(pSlider->getValue())*1000).c_str())->getCString() );

	// 	CCControlSlider* pSlider = (CCControlSlider*)sender;
	// 	float percent =pSlider->getValue()-pSlider->getMinimumValue();
	// 	float max = pSlider->getMaximumValue() - pSlider->getMinimumValue();
	// 	float delta = max;
	// 	float posX =pSlider->getPositionX();
	// 	float sliderWidth =pSlider->getContentSize().width;
	// 	spriteMoney->setPosition(ccp(posX+percent*(sliderWidth/delta), spriteMoney->getPositionY()));
	// 	//HoangDD comment
	// 	lblMoney->setString( CCString::createWithFormat("%.0f xu", floor(pSlider->getValue())*1000)->getCString() );
}

void LayerBet_BaCayChuong::setStyleGame(int styleGame) {
	_styleGame = styleGame;
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
	double max = 0;
	int minBet = 0;

	if (GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue() != NULL) {
		max = (int) *GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue();
	}

	if (GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue() != NULL) {
		minBet =atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue()->c_str());
	}

	//sliderMoney
	sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerBet_BaCayChuong::valueChanged), CCControlEventValueChanged);
	sliderMoney->setMinimumValue(1);
	sliderMoney->setMaximumValue(floor(max/1000));
	sliderMoney->setValue(1);

	sliderMoney->setTouchPriority(-128);

	this->setTouchEnabled(true);
}

void LayerBet_BaCayChuong::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerBet_BaCayChuong::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerBet_BaCayChuong::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerBet_BaCayChuong::onExit()
{
	CCLayer::onExit();
}