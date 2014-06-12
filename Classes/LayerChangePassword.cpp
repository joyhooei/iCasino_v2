//
//  LayerChangePassword.cpp
//  demo
//
//  Created by AlexDao on 5/26/14.
//
//

#include "LayerChangePassword.h"
#include "Requests/ExtensionRequest.h"
#include "SceneManager.h"
#include "_Chat_.h"

LayerChangePassword::LayerChangePassword()
{
    txtOldPassword=NULL;
    txtNewPassword=NULL;
	txtRePassword=NULL;
	GameServer::getSingleton().addListeners(this);
}

LayerChangePassword::~LayerChangePassword()
{
	GameServer::getSingleton().removeListeners(this);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerChangePassword::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUpdateInfo", LayerChangePassword::onButtonUpdate);
    return NULL;
}

void LayerChangePassword::loadAllMyDatas(){
    txtNewPassword->setText("");
    txtOldPassword->setText("");
    txtRePassword->setText("");
}

void LayerChangePassword::onButtonUpdate(CCObject* pSender)
{
    CCLOG("onButtonUpdate");
    //Validate
	int len1 = strlen( txtOldPassword->getText() );
	int len2 = strlen( txtRePassword->getText() );
	int len3 = strlen( txtNewPassword->getText() );
	if(len1<6 || len1 >24 || len2<6 || len2 >24 || len3<6 || len3 >24){
		Chat *toast = new Chat("Mật khẩu phải dài 6-24 ký tự!", -1);
		this->getParent()->addChild(toast);
		return;
	}
	if(strcmp(txtNewPassword->getText(), txtRePassword->getText())!=0){
		Chat *toast = new Chat("Xác nhận mật khẩu không đúng!", -1);
		this->getParent()->addChild(toast);
		return;
	}
    //Send request
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
    //Send request
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("aP", txtOldPassword->getText());
    params->PutUtfString("aNP", txtNewPassword->getText());
    boost::shared_ptr<IRequest> request (new ExtensionRequest("rcp", params)); //Change password
    GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBMemberVariableAssigner interface
bool LayerChangePassword::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtOldPassword", CCEditBox*, txtOldPassword);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtNewPassword", CCEditBox*, txtNewPassword);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtRePassword", CCEditBox*, txtRePassword);
    return true;
}

void LayerChangePassword::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    //Init textfield
    initTextField(txtOldPassword, "Mật khẩu cũ");
    txtOldPassword->setInputFlag(kEditBoxInputFlagPassword);
    initTextField(txtNewPassword, "Mật khẩu mới");
    txtNewPassword->setInputFlag(kEditBoxInputFlagPassword);
    initTextField(txtRePassword, "Gõ lại mật khẩu");
    txtRePassword->setInputFlag(kEditBoxInputFlagPassword);
    return;
}

void LayerChangePassword::initTextField(CCEditBox* txt, const char* hintText){
    txt->setFontColor(ccBLACK);
    txt->setPlaceholderFontColor(ccBLACK);
    txt->setFont("fonts/Roboto-Regular.ttf", 18);
    txt->setReturnType(kKeyboardReturnTypeDefault);
	txt->setPlaceHolder(hintText);
	txt->setInputMode(kEditBoxInputModeAny);
}

void LayerChangePassword::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    if(strcmp("cpc", cmd->c_str())==0){
		LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
		if( !SceneManager::getSingleton().showNotification() ){
			CCLOG("NTF Dialog already open!");
			return;
		}
		if( *param->GetInt("rc")==0 ){//OK
			CCLOG("lbfree OK");
			layer->setNotificationOptions("ĐỔI MẬT KHẨU THÀNH CÔNG", 
				"Đổi mật khẩu thành công!", false , "", 1, this );
		}else{//Not OK
			CCLOG("lbfree Not OK - error: %s", param->GetUtfString("rd")->c_str());
			layer->setNotificationOptions("ĐỔI MẬT KHẨU THẤt BẠI", 
				param->GetUtfString("rd")->c_str(), false , "", 1, this );
		}
    }
}
