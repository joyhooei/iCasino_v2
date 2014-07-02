//
//  LayerCurrencyExchange.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerCurrencyExchange.h"
#include "Requests/ExtensionRequest.h"
#include "SceneManager.h"
#include <math.h>
#include "mUtils.h"
using namespace cocos2d;
//using namespace CocosDenshion;


LayerCurrencyExchange::LayerCurrencyExchange()
{
    lblMoney = NULL;
    lblCurrentMoney = NULL;
    lblCanBorrow = NULL;
    
    sliderMoney = NULL;
    spriteMoney = NULL;
    
    nodeMoney = NULL;
    
    rate = 1;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerCurrencyExchange::~LayerCurrencyExchange()
{
    GameServer::getSingleton().removeListeners(this);
}

void LayerCurrencyExchange::loadAllMyDatas(){
    loadMinMaxMoney();
    //RequestGetRateMoneyFree
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //Send request
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    boost::shared_ptr<IRequest> request (new ExtensionRequest("reqGRMNF", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerCurrencyExchange::loadMinMaxMoney(){
    boost::shared_ptr<double> am;
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    if( myself==NULL || myself->GetVariable("am")==NULL || myself->GetVariable("amf")==NULL ){
        CCLOG("myself %s= NULL | myself->GetVariable(am) %s= NULL | myself->GetVariable(amf)%s=NULL",
              myself==NULL?"=":"!", myself->GetVariable("am")==NULL?"=":"!", myself->GetVariable("amf")==NULL?"=":"!");
        return;
    }
    am = myself->GetVariable("am")->GetDoubleValue();
    //
    sliderMoney->setMinimumValue(0);
    sliderMoney->setMaximumValue(*am);
    sliderMoney->setValue(0);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerCurrencyExchange::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUpdateInfo", LayerCurrencyExchange::onButtonCreate);
    return NULL;
}

void LayerCurrencyExchange::onButtonCreate(CCObject* pSender)
{
	if( sliderMoney->getValue()==0 )
		return;
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //Send request
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    params->PutLong("amf", sliderMoney->getValue());
    boost::shared_ptr<IRequest> request (new ExtensionRequest("lqbtofree", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerCurrencyExchange::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
}

void LayerCurrencyExchange::valueChanged(CCObject *sender, CCControlEvent controlEvent){
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float percent =pSlider->getValue()-pSlider->getMinimumValue();
    float max = pSlider->getMaximumValue() - pSlider->getMinimumValue();
    float delta = max;
    float posX =pSlider->getPositionX();
    float sliderWidth =pSlider->getContentSize().width;
	nodeMoney->setPosition(ccp(posX+percent*(sliderWidth/delta), nodeMoney->getPositionY()));
	//HoangDD comment
    lblMoney->setString( CCString::createWithFormat("%schips=%sxu", mUtils::convertMoneyEx( floor(pSlider->getValue()) ).c_str()
		, mUtils::convertMoneyEx( floor(pSlider->getValue())*rate).c_str() )->getCString() );
}

// CCBMemberVariableAssigner interface
bool LayerCurrencyExchange::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblCurrentMoney", CCLabelTTF *, lblCurrentMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblCanBorrow", CCLabelTTF *, lblCanBorrow);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeMoney", CCNode *, nodeMoney);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sliderMoney", CCControlSlider *, sliderMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sMoney", CCSprite *, spriteMoney);
    return true; 
}

void LayerCurrencyExchange::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    //sliderMoney
    sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerCurrencyExchange::valueChanged), CCControlEventValueChanged);
    sliderMoney->setMinimumValue(100);
    sliderMoney->setMaximumValue(1000);
    sliderMoney->setValue(100);
    return;
}

void LayerCurrencyExchange::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    if(strcmp("reqGRMNF", cmd->c_str())==0){ // RequestGetRateMoneyFree: respGRMNF response
        //aMLBl
        rate = *param->GetInt("respGRMNF");
        sliderMoney->setValue(0);
    }else if( strcmp("lqbtofree", cmd->c_str())==0 ){
		LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
		if( !SceneManager::getSingleton().showNotification() ){
			CCLOG("NTF Dialog already open!");
			return;
		}
        if( *param->GetInt("rc")==0 ){//OK
            CCLOG("lbfree OK");
			layer->setNotificationOptions("ĐỔI TIỀN THÀNH CÔNG", 
				"Đổi tiền thành công!", false , "", 1, this );
        }else{//Not OK
            CCLOG("lbfree Not OK - error: %s", param->GetUtfString("rd")->c_str());
			layer->setNotificationOptions("ĐỔI TIỀN THẤt BẠI", 
				param->GetUtfString("rd")->c_str(), false , "", 1, this );
        }
    }
}

void LayerCurrencyExchange::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    //get the user parameter of the event
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
    
	//if self
	if ( ptrNotifiedUser->IsItMe() == true )
		loadMinMaxMoney();
}

void LayerCurrencyExchange::notificationCallBack( bool isOK, int tag )
{

}
