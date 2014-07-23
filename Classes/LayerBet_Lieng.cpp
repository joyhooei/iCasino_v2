//
//  LayerBet_Lieng.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerBet_Lieng.h"
#include "Requests/ExtensionRequest.h"
#include "GameServer.h"
#include "mUtils.h"

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
	CCLOG("am value: %lf", ceil(sliderMoney->getValue()) );
	int gameBet = 1000;
	if (strcmp(lblMoney->getString(),"") != 0)
	{
		gameBet = atoi(lblMoney->getString()) * 1000;
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
	 	//lblMoney->setString( CCString::createWithFormat("%.0f xu", floor(pSlider->getValue())*1000)->getCString() );

		lblMoney->setString( CCString::createWithFormat("%s", mUtils::convertMoneyEx(ceil(pSlider->getValue())*1000).c_str() )->getCString() );

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
	sliderMoney->setTouchPriority(-128);

	this->setTouchEnabled(true);
    //sliderMoney
    return;
}

void LayerBet_Lieng::setInfoBet(int _minBet,int _myBet){
	sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerBet_Lieng::valueChanged), CCControlEventValueChanged);
	float max;
	if (GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue() != NULL) {
		max =  *GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue();
	}

	lblTitle1->setString(("Mức tố hiện tại: " + mUtils::convertMoneyEx(_minBet)).c_str());
	lblTitle2->setString(("Lượt tố trước của bạn: " + mUtils::convertMoneyEx(_myBet)).c_str());
	lblTitle3->setString(("Bạn cần tố thêm: " + mUtils::convertMoneyEx(_minBet - _myBet)).c_str());

	sliderMoney->setMinimumValue(_minBet/1000);
	sliderMoney->setMaximumValue(floor(max/1000));
	sliderMoney->setValue(1);
	sliderMoney->setTouchPriority(-128);
}

void LayerBet_Lieng::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerBet_Lieng::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerBet_Lieng::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerBet_Lieng::onExit()
{
	CCLayer::onExit();
}