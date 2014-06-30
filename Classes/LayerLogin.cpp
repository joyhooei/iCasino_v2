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
#include "Requests/LogoutRequest.h"
#include "SceneManager.h"
#include "_Chat_.h"
#include "mUtils.h"

using namespace cocos2d;
//using namespace CocosDenshion;


LayerLogin::LayerLogin()
{
    txtPassword = NULL;
    txtUsername = NULL;

	chkSaveInfo = NULL;

	LSK = "";

	isRegistPopupShown = false;
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
	parameters->PutUtfString("LSK", LSK.c_str());
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
// 	std::string str ("There are two needles in this haystack with needles.");
// 	std::string str2 ("needle");
// 	std::size_t found = str.find(str2);
// 	if (found!=std::string::npos)
// 		CCLOG("Found  it %d", found);
// 	else
// 		CCLOG("Cannot found!");
	vector<string> lstRegx ;
	for( int i = 1; i<=16; i++ ){
		char buff[10];
		sprintf(buff, "(%d)", i);
		lstRegx.push_back(buff);
	}
	string S = "(1)abc xyz(2)(15)he he";
	vector<string> lst = mUtils::splitStringByListRegex(S, lstRegx);
	for( int i = 0; i<lst.size(); i++ ){
		CCLOG("***%d*** %s", i, lst.at(i).c_str());
	}
//    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//    * mLayer;
//    if (ccbReader)
//    {
//        mLayer = (LayerChooseGame *)ccbReader->readNodeGraphFromFile( "LayerChooseGame.ccbi" );
//        this->addChild(mLayer, 1, 1);
//        ccbReader->release();
//    }
//     ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//     LayerGameChan_XuongU* mLayer;
//     if (ccbReader)
//     {
//         mLayer = (LayerGameChan_XuongU *)ccbReader->readNodeGraphFromFile( "LayerGameChan_XuongU.ccbi" );
//         this->addChild(mLayer, 1, 1);
//         ccbReader->release();
//     }
}
void LayerLogin::onButtonCreateAccount(CCObject* pSender){
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
    CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerCreateAccount* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerCreateAccount *)ccbReader->readNodeGraphFromFile( "LayerCreateAccount.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
		//
		isRegistPopupShown = true;
		mLayer->setCallbackFunc(this, callfunc_selector(LayerLogin::popupCallback));
		mLayer->doConnect();
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
	this->setKeypadEnabled(true);
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
	if( isRegistPopupShown ) 
		return;
    CCLog("LayerLogin: OnSmartFoxConnection");
    doLogin();
}

void LayerLogin::OnSmartFoxLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	if( isRegistPopupShown ) 
		return;
    CCLOG("LayerLogin::OnSmartFoxLogin() - Login OK");
    if( chkSaveInfo->getSelectedState() ){//save info
		saveInfo();
	}
	//Read param, check already play game, if true, gotoGame
	/*
	* Check aSt: . If not playing game, value = "null"
	* account_id,zone_id,room_id,status,updated_time,game_id
	*/
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueDatas = (*ptrEventParams)["data"];
	boost::shared_ptr<ISFSObject> datas = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueDatas)));
	SceneManager::getSingleton().gotoMain();
	if( datas==NULL )
		return;
	boost::shared_ptr<string> ast = datas->GetUtfString("aSt");
	LSK = *datas->GetUtfString("LSK");
	//
	if( ast==NULL ){
		return;
	}
	//
	vector<string> lstDatas = mUtils::splitString(*ast, ',');
	if( lstDatas.size()!=0 ){
		mRoomID = atoi( lstDatas.at(2).c_str() );
		mGameID = atoi( lstDatas.at(5).c_str() );
		//Check room is existed
		if( GameServer::getSingleton().getSmartFox()->GetRoomById(mRoomID)==NULL ){
			return;
		}
		LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
		if( !SceneManager::getSingleton().showNotification() ){
			CCLOG("NTF Dialog already open!");
			return;
		}
		//if true
		layer->setNotificationOptions("VÀO LẠI BÀN CHƠI", 
			CCString::createWithFormat("Bạn đang chơi %s!\n Bạn có muốn vào lại phòng?", mUtils::getGameNameByID(mGameID)->getCString())->getCString()
			, true , "ĐỒNG Ý", tagConfirmReJoinGame, this );
	}
}
void LayerLogin::OnSmartFoxLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	if( isRegistPopupShown ) 
		return;
    CCLOG("LayerLogin::OnSmartFoxLoginError() - Login error");
    
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
	boost::shared_ptr<string> message (new string("OnSmartFoxLoginError Failure: " +  *ptrErrorMessage + " !"));
    CCLog("Error string: %s", message->c_str());
    
    Chat *toast = new Chat(message->c_str(), -1);
    this->addChild(toast);
}

void LayerLogin::popupCallback(  )
{
	isRegistPopupShown = false;
	////
	if( GameServer::getSingleton().getSmartFox() == NULL) 
		return;
	if( GameServer::getSingleton().getSmartFox()->MySelf()==NULL )
		return;
	boost::shared_ptr<IRequest> request (new LogoutRequest());
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerLogin::setUserAndPassInfo( const char* username, const char* password )
{
	txtUsername->setText(username);
	txtPassword->setText(password);
}

void LayerLogin::notificationCallBack( bool isOK, int tag )
{
	switch(tag){
	case tagConfirmReJoinGame:
		if( isOK ){
			LayerMain::getSingleton().autoJoinGameWithID(mGameID, mRoomID);
		}
		break;
	case tagCloseApp:
		if( isOK ){
			SceneManager::getSingleton().exitScene();
		}
		break;
	}
}

void LayerLogin::keyBackClicked()
{
	if( SceneManager::getSingleton().getCurrentLayerTag() != tag_LayerLogin )
		return;
	CCLOG("LayerLogin::keyBackClicked()");
	LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
	if( !SceneManager::getSingleton().showNotification() ){
		CCLOG("NTF Dialog already open!");
		return;
	}
	//if true
	layer->setNotificationOptions("THOÁT ỨNG DỤNG", 
		"Bạn có muốn thoát?"
		, true , "ĐỒNG Ý", tagCloseApp, this );
}
