//
//  LayerBet_TomCuaCa.cpp
//  demo
//
//  Created by Tuan on 6/25/14.
//
//

#include "LayerBet_TomCuaCa.h"
#include "GameServer.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"

using namespace Sfs2X;
using namespace cocos2d;
//using namespace CocosDenshion;


LayerBet_TomCuaCa::LayerBet_TomCuaCa()
{
	lblMoney=NULL;
	sliderMoney=NULL;
	spriteMoney=NULL;
}

LayerBet_TomCuaCa::~LayerBet_TomCuaCa()
{
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerBet_TomCuaCa::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCreate", LayerBet_TomCuaCa::onButtonCreate);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerBet_TomCuaCa::onButtonClose);
	return NULL;
}

void LayerBet_TomCuaCa::onButtonCreate(CCObject* pSender)
{
	
	CCLOG("mTip: %s", lblMoney->getString());
	//float myTien = floor(sliderMoney->getValue());
	double gameBet = floor(sliderMoney->getValue()/1000)*1000;
	//EXT_EVENT_GAME_BET_REQ = "gbr";
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutInt("aid",_tag);
	params->PutInt("gbv", gameBet);
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest("gbr",params,lastRoom));
	GameServer::getSingleton().getSmartFox()->Send(request);
	CCLog("-- aid: %d",_tag);
	this->removeFromParentAndCleanup(true);
}

void LayerBet_TomCuaCa::onButtonClose(CCObject* pSender)
{
	CCLOG("onButtonClose");
	this->removeFromParentAndCleanup(true);
}

void LayerBet_TomCuaCa::valueChanged(CCObject *sender, CCControlEvent controlEvent){
	CCControlSlider* pSlider = (CCControlSlider*)sender;
	float percent =pSlider->getValue()-pSlider->getMinimumValue();
	float max = pSlider->getMaximumValue() - pSlider->getMinimumValue();
	float delta = max;
	float posX =pSlider->getPositionX();
	float sliderWidth =pSlider->getContentSize().width;
	spriteMoney->setPosition(ccp(posX+percent*(sliderWidth/delta), spriteMoney->getPositionY()));
	//lblMoney->setString( CCString::createWithFormat("%.0f xu", ceil(pSlider->getValue()))->getCString() );
	float myTien = floor(pSlider->getValue());
	float myTien2 = floor((myTien/1000));
	lblMoney->setString( CCString::createWithFormat("%s xu", mUtils::convertMoneyEx(myTien2*1000).c_str())->getCString() );
	CCLog("--%f",pSlider->getValue());
}

// CCBMemberVariableAssigner interface
bool LayerBet_TomCuaCa::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	//CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sliderMoney", CCControlSlider *, sliderMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sMoney", CCSprite *, spriteMoney);
	//    sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerBet_BaCayChuong::valueChanged), CCControlEventValueChanged);
	return true;
}

void LayerBet_TomCuaCa::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
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
	sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerBet_TomCuaCa::valueChanged), CCControlEventValueChanged);
	sliderMoney->setMinimumValue(minBet);
	sliderMoney->setMaximumValue(max);
	sliderMoney->setValue(1000);

	sliderMoney->setTouchPriority(-128);

	this->setTouchEnabled(true);
}

void LayerBet_TomCuaCa::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerBet_TomCuaCa::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerBet_TomCuaCa::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerBet_TomCuaCa::onExit()
{
	CCLayer::onExit();
}
int LayerBet_TomCuaCa::getAID(int _mtag)
{
	switch(_mtag)
		{
	case 20001:
		return _tag=6;
		break;
	case 20002:
		return _tag=5;
		break;
	case 20003:
		return _tag=4;
		break;
	case 20004:
		return _tag=3;
		break;
	case 20005:
		return _tag=2;
		break;
	case 20006:
		return _tag=1;
		break;
		}

	return _tag=-1;

}