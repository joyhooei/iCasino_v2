//
//  LayerBorrowMoney.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerBorrowMoney.h"
#include "Requests/ExtensionRequest.h"
#include "SceneManager.h"
#include "mUtils.h"
using namespace cocos2d;
//using namespace CocosDenshion;


LayerBorrowMoney::LayerBorrowMoney()
{
    lblMoney = NULL;
    lblCurrentMoney = NULL;
    lblCanBorrow = NULL;
    
    sliderMoney = NULL;
    spriteMoney = NULL;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerBorrowMoney::~LayerBorrowMoney()
{
    GameServer::getSingleton().removeListeners(this);
	//
	CC_SAFE_RELEASE(lblMoney);
	CC_SAFE_RELEASE(lblCurrentMoney);
	CC_SAFE_RELEASE(lblCanBorrow);

	CC_SAFE_RELEASE(sliderMoney);
	CC_SAFE_RELEASE(spriteMoney);
}

void LayerBorrowMoney::loadAllMyDatas(){
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //Send request
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    boost::shared_ptr<IRequest> request (new ExtensionRequest("clbi", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerBorrowMoney::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUpdateInfo", LayerBorrowMoney::onButtonCreate);
    return NULL;
}

void LayerBorrowMoney::onButtonCreate(CCObject* pSender)
{
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //Send request
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    params->PutLong("amf", ceil(sliderMoney->getValue()));
    boost::shared_ptr<IRequest> request (new ExtensionRequest("lbfree", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerBorrowMoney::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
}

void LayerBorrowMoney::valueChanged(CCObject *sender, CCControlEvent controlEvent){
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
bool LayerBorrowMoney::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblMoney", CCLabelTTF *, lblMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblCurrentMoney", CCLabelTTF *, lblCurrentMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblCanBorrow", CCLabelTTF *, lblCanBorrow);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sliderMoney", CCControlSlider *, sliderMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sMoney", CCSprite *, spriteMoney);
    return true; 
}

void LayerBorrowMoney::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    //sliderMoney
    sliderMoney->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerBorrowMoney::valueChanged), CCControlEventValueChanged);
    sliderMoney->setMinimumValue(100);
    sliderMoney->setMaximumValue(1000);
    sliderMoney->setValue(100);
    return;
}

void LayerBorrowMoney::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    if(strcmp("clbi", cmd->c_str())==0){ //clbi response
        //aMLBl
        long aMLBl = *param->GetLong("aMLBl");
        //aLBl
        long aLBl = *param->GetLong("aLBl");
        CCLOG("clbi aMLBl=%lf aLBl=%ld", *param->GetLong("aMLBl"), aLBl);
        //set to slider
        sliderMoney->setMinimumValue(0);
        sliderMoney->setMaximumValue(aMLBl);
        //set to label
        lblCanBorrow->setString( mUtils::convertMoneyEx(aMLBl).c_str() );
        lblCurrentMoney->setString(  mUtils::convertMoneyEx(aLBl).c_str() );
    }else if( strcmp("lbfree", cmd->c_str())==0 ){
		LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
		if( !SceneManager::getSingleton().showNotification() ){
			CCLOG("NTF Dialog already open!");
			return;
		}
        if( *param->GetInt("rc")==0 ){//OK
            CCLOG("lbfree OK");
			layer->setNotificationOptions("VAY TIỀN THÀNH CÔNG", 
				"Vay tiền thành công!", false , "", 1, this );
			loadAllMyDatas();
        }else{//Not OK
            CCLOG("lbfree Not OK - error: %s", param->GetUtfString("rd")->c_str());
			layer->setNotificationOptions("VAY TIỀN THẤt BẠI", 
				 param->GetUtfString("rd")->c_str(), false , "", 1, this );
        }
    }
}

void LayerBorrowMoney::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    //get the user parameter of the event
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
    
	//if self
//	if ( ptrNotifiedUser->IsItMe() == true )
//		loadMinMaxMoney();
}

void LayerBorrowMoney::notificationCallBack( bool isOK, int tag )
{

}
