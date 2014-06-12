//
//  LayerTransferMoney.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerTransferMoney.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"
#include "SceneManager.h"
#include "_Chat_.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerTransferMoney::LayerTransferMoney()
{
    lblMoney = NULL;
    txtTransferTo = NULL;
    
    sliderMoney = NULL;
    spriteMoney = NULL;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerTransferMoney::~LayerTransferMoney()
{
    GameServer::getSingleton().removeListeners(this);
}

void LayerTransferMoney::loadMinMaxMoney(){
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
    sliderMoney->setMaximumValue((*am));
    sliderMoney->setValue(0);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerTransferMoney::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUpdateInfo", LayerTransferMoney::onButtonCreate);
    return NULL;
}

void LayerTransferMoney::onButtonCreate(CCObject* pSender)
{
	//Validate
	if( strlen( txtTransferTo->getText() ) == 0 ){
		Chat *toast = new Chat("Chưa biết địa chỉ chuyển tới!", -1);
		this->addChild(toast);
		return;
	}
    //Send request
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    params->PutUtfString("aR", txtTransferTo->getText());
    params->PutLong("am", sliderMoney->getValue());
    boost::shared_ptr<IRequest> request (new ExtensionRequest("tfbalance", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerTransferMoney::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
}

void LayerTransferMoney::valueChanged(CCObject *sender, CCControlEvent controlEvent){
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float percent =pSlider->getValue()-pSlider->getMinimumValue();
    float max = pSlider->getMaximumValue() - pSlider->getMinimumValue();
    float delta = max;
    float posX =pSlider->getPositionX();
    float sliderWidth =pSlider->getContentSize().width;
    spriteMoney->setPosition(ccp(posX+percent*(sliderWidth/delta), spriteMoney->getPositionY()));
    lblMoney->setString( CCString::createWithFormat("%s xu", mUtils::convertMoneyEx(ceil(pSlider->getValue())).c_str() )->getCString() );
}

// CCBMemberVariableAssigner interface
bool LayerTransferMoney::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtTransferTo", CCEditBox*, txtTransferTo);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sliderMoney", CCControlSlider *, sliderMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sMoney", CCSprite *, spriteMoney);
    return true; 
}

void LayerTransferMoney::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    //sliderMoney
    sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerTransferMoney::valueChanged), CCControlEventValueChanged);
    sliderMoney->setMinimumValue(100);
    sliderMoney->setMaximumValue(1000);
    sliderMoney->setValue(100);
    //Init textfield
    txtTransferTo->setFontColor(ccBLACK);
    txtTransferTo->setPlaceholderFontColor(ccBLACK);
    txtTransferTo->setMaxLength(17);
    txtTransferTo->setFont("fonts/Roboto-Regular.ttf", 18);
    txtTransferTo->setReturnType(kKeyboardReturnTypeDone);
    txtTransferTo->setPlaceHolder("Người nhận");
    //
    loadMinMaxMoney();
    return;
}

void LayerTransferMoney::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    if(strcmp("tfbalance", cmd->c_str())==0){ //tfbalance response
		CCLOG("tfbalance rc(int)=%d rc(long)=", *param->GetInt("rc"));
		LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
		if( !SceneManager::getSingleton().showNotification() ){
			CCLOG("NTF Dialog already open!");
			return;
		}
        if( *param->GetInt("rc")==0 ){//OK
			CCLOG("tfbalance OK");
			layer->setNotificationOptions("CHUYỂN TIỀN THÀNH CÔNG", 
				"Chuyển tiền thành công!", false , "", 1, this );
        }else{//Not OK
			CCLOG("tfbalance Not OK");
			layer->setNotificationOptions("CHUYỂN TIỀN THẤt BẠI", 
				param->GetUtfString("rd")->c_str(), false , "", 1, this );
        }
    }
}

void LayerTransferMoney::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    //get the user parameter of the event
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
    
	//if self
	if ( ptrNotifiedUser->IsItMe() == true )
		loadMinMaxMoney();
}

void LayerTransferMoney::notificationCallBack( bool isOK, int tag )
{

}
