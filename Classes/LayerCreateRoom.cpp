//
//  LayerCreateRoom.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerCreateRoom.h"
#include "Requests/ExtensionRequest.h"
#include <stdio.h>
#include <math.h>
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerCreateRoom::LayerCreateRoom()
{
    lblMoney = NULL;
    sliderMoney = NULL;
    txtPassword = NULL;
    spriteMoney = NULL;
    
    m_gameID = -1;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerCreateRoom::~LayerCreateRoom()
{
    GameServer::getSingleton().removeListeners(this);
}

void LayerCreateRoom::setGameID(int gameID){
    m_gameID = gameID;
}

//void LayerCreateRoom::loadAllMyDatas(){
//    //Send request
//    
//}

// CCBSelectorResolver interface
SEL_MenuHandler LayerCreateRoom::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCreate", LayerCreateRoom::onButtonCreate);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerCreateRoom::onButtonClose);
    return NULL;
}

void LayerCreateRoom::onButtonCreate(CCObject* pSender)
{
    CCLOG("Tạo bàn chơi mới");
    boost::shared_ptr<ISFSObject> roomConfig (new SFSObject());
	roomConfig->PutUtfString("rpass", "");
	//HoangDD comment
    roomConfig->PutUtfString("params", CCString::createWithFormat("%.0f@", 1000*floor(sliderMoney->getValue()))->getCString());
    roomConfig->PutUtfString("gid", CCString::createWithFormat("%d", m_gameID)->getCString());
    //sendRequest
    boost::shared_ptr<IRequest> request (new ExtensionRequest("rcroom",roomConfig));
    GameServer::getSingleton().getSmartFox()->Send(request);
	//
	this->removeFromParentAndCleanup(true);
}

void LayerCreateRoom::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
    this->removeFromParentAndCleanup(true);
}

void LayerCreateRoom::valueChanged(CCObject *sender, CCControlEvent controlEvent){
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float percent =pSlider->getValue()-pSlider->getMinimumValue();
    float max = pSlider->getMaximumValue() - pSlider->getMinimumValue();
    float delta = max;
    float posX =pSlider->getPositionX();
    float sliderWidth =pSlider->getContentSize().width;
    spriteMoney->setPosition(ccp(posX+percent*(sliderWidth/delta), spriteMoney->getPositionY()));
	//HoangDD comment
    lblMoney->setString( CCString::createWithFormat("%.0f xu", floor(pSlider->getValue())*1000)->getCString() );
}

// CCBMemberVariableAssigner interface
bool LayerCreateRoom::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sliderMoney", CCControlSlider *, sliderMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sMoney", CCSprite *, spriteMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtPassword", CCEditBox*, txtPassword);
//    sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerCreateRoom::valueChanged), CCControlEventValueChanged);
    return true;
}

void LayerCreateRoom::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    //sliderMoney
    sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerCreateRoom::valueChanged), CCControlEventValueChanged);
    //
    boost::shared_ptr<double> am, amf;
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    if( myself==NULL || myself->GetVariable("am")==NULL || myself->GetVariable("amf")==NULL ){
        return;
    }
    amf = myself->GetVariable("amf")->GetDoubleValue();

    sliderMoney->setMinimumValue(1);
	//HoangDD comment
    sliderMoney->setMaximumValue(floor(*amf/4000));
    sliderMoney->setValue(1);
	sliderMoney->setTouchPriority(-128);
    //Init textfield
    txtPassword->setFontColor(ccBLACK);
    txtPassword->setPlaceholderFontColor(ccBLACK);
    txtPassword->setMaxLength(17);
    txtPassword->setFont("fonts/Roboto-Regular.ttf", 18);
    txtPassword->setReturnType(kKeyboardReturnTypeDone);
    txtPassword->setPlaceHolder("Mật khẩu");
    txtPassword->setInputFlag(kEditBoxInputFlagPassword);
	txtPassword->setTouchPriority(-128);
	//
	this->setTouchEnabled(true);
    return;
}

void LayerCreateRoom::OnSmartFoxRoomCreationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("OnSmartFoxRoomCreationError");
}

void LayerCreateRoom::OnSmartFoxRoomAdd(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("OnSmartFoxRoomAdd");
//    this->removeFromParentAndCleanup(true);
}

void LayerCreateRoom::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LayerCreateRoom::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerCreateRoom::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerCreateRoom::onExit()
{
	CCLayer::onExit();
}

