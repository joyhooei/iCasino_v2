//
//  LayerLogin.cpp
//  demo
//
//  Created by AlexDao on 5/30/14.
//
//

#include "LayerLogin.h"
#include "LayerCreateAccount.h"
#include "LayerForgotPassword.h"
#include "Requests/LoginRequest.h"
#include "SceneManager.h"
#include "_Chat_.h"
#include "LayerPlayerInfo.h"
#include "LayerPasswordRoom.h"
#include "LayerGameChan_XuongU.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerLogin::LayerLogin()
{
    txtPassword = NULL;
    txtUsername = NULL;

	chkSaveInfo = NULL;
    
    ccbReader = NULL;
    ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    // register loaders
    ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerCreateAccount",   LayerCreateAccountLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerForgotPassword",   LayerForgotPasswordLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerPlayerInfo",   LayerPlayerInfoLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerPasswordRoom",   LayerPasswordRoomLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerGameChan_XuongU",   LayerGameChan_XuongULoader::loader());
    //
    GameServer::getSingleton().addListeners(this);
}

LayerLogin::~LayerLogin()
{
    GameServer::getSingleton().removeListeners(this);
}

void LayerLogin::readInfo(){
	CCUserDefault *def=CCUserDefault::sharedUserDefault();
	string username = def->getStringForKey("username", "");
	string password = def->getStringForKey("password", "");

	txtUsername->setText(username.c_str());
	txtPassword->setText(password.c_str());

	chkSaveInfo->setSelectedState(true);
}

void LayerLogin::saveInfo(){
	CCUserDefault *def=CCUserDefault::sharedUserDefault();
	def->setStringForKey("username", txtUsername->getText());
	def->setStringForKey("password", txtPassword->getText());

	def->flush();
}

void LayerLogin::doLogin(){
    //login zone when connect success
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
	//add the params
	parameters->PutUtfString("LT", "normal");
	parameters->PutUtfString("LSK", "");
	boost::shared_ptr<IRequest> request (new LoginRequest(txtUsername->getText(), txtPassword->getText(), "GameZone1", parameters));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerLogin::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    //CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnLogin", LayerLogin::onButtonLogin);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnLoginFB", LayerLogin::onButtonLoginWithFacebook);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnCreateAccount", LayerLogin::onButtonCreateAccount);
    return NULL;
}

void LayerLogin::onButtonLogin(CCObject* pSender){
	if( strcmp( txtUsername->getText(), "")==0 || strcmp( txtPassword->getText(), "")==0  ){
		Chat *toast = new Chat("Bạn chưa nhập vào tên đăng nhập hoặc mật khẩu!", -1);
		this->addChild(toast);
		return;
	}
//    SceneManager::getSingleton().gotoMain();
//    return;
    if( !GameServer::getSingleton().getSmartFox()->IsConnected() )
        GameServer::getSingleton().connectToServer("bestteam.no-ip.biz", "9933");
    else{
        doLogin();
    }
}

void LayerLogin::onButtonLoginWithFacebook(CCObject* pSender){
//    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//    * mLayer;
//    if (ccbReader)
//    {
//        mLayer = (LayerChooseGame *)ccbReader->readNodeGraphFromFile( "LayerChooseGame.ccbi" );
//        this->addChild(mLayer, 1, 1);
//        ccbReader->release();
//    }
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerGameChan_XuongU* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerGameChan_XuongU *)ccbReader->readNodeGraphFromFile( "LayerGameChan_XuongU.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
}
void LayerLogin::onButtonCreateAccount(CCObject* pSender){
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerCreateAccount* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerCreateAccount *)ccbReader->readNodeGraphFromFile( "LayerCreateAccount.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
}

// CCBMemberVariableAssigner interface
bool LayerLogin::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtUsername", CCEditBox *, txtUsername);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtPassword", CCEditBox*, txtPassword);
    
    return true;
}

void LayerLogin::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    //CCLOG("Imhere onNodeLoaded");
    //Init textfield
    initTextField(txtUsername, "Tên đăng nhập");
    txtUsername->setInputFlag(kEditBoxInputFlagSensitive);
    initTextField(txtPassword, "Mật khẩu");
    txtPassword->setInputFlag(kEditBoxInputFlagPassword);
    //Set default data
    txtUsername->setText("dautv3");
    txtPassword->setText("123456");

//     txtUsername->setText("thanhhv1");
//     txtPassword->setText("123");

	UILayer* uiLayer = UILayer::create();
	this->addChild(uiLayer);
	//create check box
	chkSaveInfo = UICheckBox::create();
	chkSaveInfo->setTouchEnabled(true);
	chkSaveInfo->setScale(0.7f, 0.7f);
	chkSaveInfo->loadTextures("avatars/select_box.png",
		"avatars/select_box.png",
		"avatars/select_box_choose.png",
		"avatars/select_box.png",
		"avatars/select_box_choose.png");
	chkSaveInfo->setPosition(ccp(260, 27));
	chkSaveInfo->addEventListenerCheckBox(this, checkboxselectedeventselector(LayerLogin::selectedStateEvent));
	uiLayer->addWidget(chkSaveInfo);
	//Create label for checkbox
	CCLabelTTF* lblSaveInfo = CCLabelTTF::create();
	lblSaveInfo->setString("Lưu thông tin");
	lblSaveInfo->setFontSize(14);
	lblSaveInfo->setFontName("Roboto-Bold");
	lblSaveInfo->setAnchorPoint(ccp(0,0.5));
	lblSaveInfo->setPosition(ccp( 275, 27 ));
	this->addChild(lblSaveInfo);

    //
	readInfo();
	//
    this->setTouchEnabled(true);
    return;
}

void LayerLogin::initTextField(CCEditBox* txt, const char* hintText){
    txt->setFontColor(ccBLACK);
    txt->setPlaceholderFontColor(ccBLACK);
    txt->setFont("fonts/Roboto-Regular.ttf", 18);
    txt->setReturnType(kKeyboardReturnTypeDefault);
    txt->setPlaceHolder(hintText);
}

void LayerLogin::selectedStateEvent(CCObject* pSender, CheckBoxEventType type){
	CCLOG("selectedStateEvent: %s", type==CHECKBOX_STATE_EVENT_SELECTED?"Checked":"UnCheck");
}

void LayerLogin::OnSmartFoxConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
    CCLog("LayerLogin: OnSmartFoxConnection");
    doLogin();
}

void LayerLogin::OnSmartFoxLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("LayerLogin::OnSmartFoxLogin() - Login OK");
    if( chkSaveInfo->getSelectedState() ){//save info
		saveInfo();
	}
    SceneManager::getSingleton().gotoMain();
}
void LayerLogin::OnSmartFoxLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("LayerLogin::OnSmartFoxLoginError() - Login error");
    
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
	boost::shared_ptr<string> message (new string("OnSmartFoxLoginError Failure: " +  *ptrErrorMessage + " !"));
    CCLog("Error string: %s", message->c_str());
    
    Chat *toast = new Chat("Tên đăng nhập hoặc mật khẩu không đúng!", -1);
    this->addChild(toast);
}
