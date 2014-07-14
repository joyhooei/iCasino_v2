//
//  LayerUpdateInfo.cpp
//  demo
//
//  Created by AlexDao on 5/24/14.
//
//

#include "LayerUpdateInfo.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"
#include "LayerNotification.h"
#include "SceneManager.h"
using namespace cocos2d;
//using namespace CocosDenshion;


LayerUpdateInfo::LayerUpdateInfo()
{
    isMan = true;
    txtName=NULL;
    txtStatus=NULL;
    txtPhoneNumber=NULL;
    txtFavour=NULL;
    txtEmail=NULL;
    btnSex = NULL;
    //
    GameServer::getSingleton().addListeners(this);
}

LayerUpdateInfo::~LayerUpdateInfo()
{
    GameServer::getSingleton().removeListeners(this);
    //
    CC_SAFE_RELEASE(txtName);
    CC_SAFE_RELEASE(txtStatus);
    CC_SAFE_RELEASE(txtPhoneNumber);
    CC_SAFE_RELEASE(txtFavour);
    CC_SAFE_RELEASE(txtEmail);
    CC_SAFE_RELEASE(btnSex);
}

void LayerUpdateInfo::loadAllMyDatas(){
    //Send request
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    boost::shared_ptr<IRequest> request (new ExtensionRequest("rgaci", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerUpdateInfo::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnSex", LayerUpdateInfo::onButtonSex);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerUpdateInfo::onButtonClose);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUpdate", LayerUpdateInfo::onButtonUpdate);
    return NULL;
}

void LayerUpdateInfo::onButtonSex(CCObject* pSender)
{
    CCMenuItemImage* btn = (CCMenuItemImage*)pSender;
    if( btn->getPositionX()==140 ){
        //disabling, switch to enable
        btn->setPosition(ccp(198, btn->getPositionY()));
        isMan = false;
    }else{
        //else
        btn->setPosition(ccp(140, btn->getPositionY()));
        isMan = true;
    }
    CCLOG("onButtonSex isMan: %s", isMan?"true":"false");
}

void LayerUpdateInfo::onButtonUpdate(CCObject* pSender)
{
    if( !mUtils::isValidEmailAddress( txtEmail->getText() ) ){
        CCLOG("LayerUpdateInfo::onButtonUpdate email: %s is not valid!", txtEmail->getText());
    }
    //Send request
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aI", myself->Name());
    params->PutUtfString("aN", txtName->getText());
	params->PutUtfString("aM", txtEmail->getText());
	params->PutUtfString("aMo", txtPhoneNumber->getText());
    params->PutInt("aSt", 1);
    params->PutInt("aT", 1);
    params->PutInt("aS", btnSex->getPositionX()==198);
    boost::shared_ptr<IRequest> request (new ExtensionRequest("rua", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}


void LayerUpdateInfo::onButtonClose(CCObject* pSender)
{
    CCLOG("onButtonClose");
    this->removeFromParentAndCleanup(true);
}

// CCBMemberVariableAssigner interface
bool LayerUpdateInfo::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtEmail", CCEditBox*, txtEmail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtFavour", CCEditBox*, txtFavour);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtName", CCEditBox*, txtName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtPhoneNumber", CCEditBox*, txtPhoneNumber);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtStatus", CCEditBox*, txtStatus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnSex", CCMenuItem*, btnSex);

    return true;
}

void LayerUpdateInfo::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    //Init textfield
    initTextField(txtEmail, "Email");
    txtEmail->setInputMode(kEditBoxInputModeEmailAddr);
    initTextField(txtFavour, "Sở thích");
    initTextField(txtName, "Họ tên");
    initTextField(txtPhoneNumber, "Số điện thoại");
    txtPhoneNumber->setInputMode(kEditBoxInputModePhoneNumber);
    initTextField(txtStatus, "Trạng thái");
    txtStatus->setReturnType(kKeyboardReturnTypeDone);
    
    txtFavour->setVisible(false);
    txtStatus->setVisible(false);
	//
	this->setTouchEnabled(true);
    return;
}

void LayerUpdateInfo::initTextField(CCEditBox* txt, const char* hintText){
    txt->setFontColor(ccBLACK);
    txt->setPlaceholderFontColor(ccBLACK);
    txt->setFont("Roboto-Regular.ttf", 18);
    txt->setReturnType(kKeyboardReturnTypeDefault);
	txt->setPlaceHolder(hintText);
	txt->setInputMode(kEditBoxInputModeAny);
	txt->setInputFlag(kEditBoxInputFlagSensitive);
	txt->setTouchPriority(-128);
}

void LayerUpdateInfo::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	CCLOG("LayerUpdateInfo::OnExtensionResponse: cmd = %s", cmd->c_str());
    if(strcmp("gaic", cmd->c_str())==0){
        //Insert datas to textfield
        txtName->setText( param->GetUtfString("aN")->c_str() );
        txtPhoneNumber->setText( param->GetUtfString("aMo")->c_str() );
        txtEmail->setText( param->GetUtfString("aM")->c_str() );
        txtFavour->setText( "" );
        txtStatus->setText( "" );
        btnSex->setPosition(ccp(*param->GetBool("aS")==true ? 198 : 140, btnSex->getPositionY()));
	}else if(strcmp("uac", cmd->c_str())==0){
		LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
		if( !SceneManager::getSingleton().showNotification() ){
			CCLOG("NTF Dialog already open!");
			return;
		}
		this->setTouchEnabled(false);
		if( *param->GetInt("rc")==0 ){//OK
			CCLOG("lbfree OK");
			layer->setNotificationOptions("CẬP NHẬT THÔNG TIN", 
				"Cập nhật thông tin thành công!", false , "", 1, this );
		}else{//Not OK
			CCLOG("lbfree Not OK - error: %s", param->GetUtfString("rd")->c_str());
			layer->setNotificationOptions("CẬP NHẬT THÔNG TIN THẤt BẠI", 
				param->GetUtfString("rd")->c_str(), false , "", 1, this );
		}
	}
}

void LayerUpdateInfo::registerWithTouchDispatcher( void )
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool LayerUpdateInfo::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerUpdateInfo::onEnter()
{
	CCLayer::onEnter();
	//
	this->runAction(mUtils::getActionOpenPopup());
}

void LayerUpdateInfo::onExit()
{
	CCLayer::onExit();
}
