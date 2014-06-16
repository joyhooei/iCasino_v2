#include "SceneManager.h"
#include "Requests/ExtensionRequest.h"
#include "mUtils.h"
#include "SliderCustomLoader.h"
#include "TextFieldCustomLoader.h"
#include "TextFieldCustomPopUpLoader.h"
#include "LayerPlayGameChinessChess.h"
#include "LayerPlayerInfo.h"
#include "LayerCreateRoom.h"
#include "LayerFriendDetails.h"

#include "LayerChargeMoney.h"
#include "LayerLichSuGiaoDich.h"
#include "LayerTransferMoney.h"
#include "LayerCurrencyExchange.h"
#include "LayerBorrowMoney.h"

#include "LayerUserInfo_Details.h"
#include "LayerChangeAvatar.h"
#include "LayerBuyAvatar.h"
#include "LayerChangePassword.h"
#include "LayerAction.h"
#include "_Chat_.h"

#include "LayerUpdateInfo.h"

#include "LayerCreateAccount.h"

template<> SceneManager* SingLeton<SceneManager>::mSingleton = 0;
SceneManager* SceneManager::getSingletonPtr(void)
{
	return mSingleton;
}
SceneManager& SceneManager::getSingleton(void)
{
	assert( mSingleton );
	return ( *mSingleton );
}

SceneManager::SceneManager()
	: mGameTLMB(NULL)
	, mGameTLMN(NULL)
	, mGamePhom(NULL)
	, layerNotification(NULL)
{}

CCScene* SceneManager::createScene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	CCSize sizeScreen = CCDirector::sharedDirector()->getVisibleSize();
	// set Scale app
	float scaleX = sizeScreen.width / WIDTH_DESIGN;
	float scaleY = sizeScreen.height / HEIGHT_DESIGN;
	float scaleMin = (scaleX < scaleY) ? scaleX : scaleY;
	scene->setScale(scaleMin);

	// 'layer' is an autorelease object
	SceneManager *layer = SceneManager::create();
	scene->addChild(layer);

	// VERSION
	CCLabelTTF *nameVersion = CCLabelTTF::create("ver-1.0.0", "", 16);
	nameVersion->setColor(ccWHITE);
	nameVersion->setPosition(ccp(10 + nameVersion->getContentSize().width / 2, 20));
	scene->addChild(nameVersion);

	// return the scene
	return scene;
}

bool SceneManager::init() {
	if (!CCLayer::init()) return false;

	// initialize - begin
	vector<string> searchPaths;
	searchPaths.push_back("avatars");
	searchPaths.push_back("backgrounds");
	searchPaths.push_back("buttons");
	searchPaths.push_back("cards");
	searchPaths.push_back("numbers");
	searchPaths.push_back("in_games");
	searchPaths.push_back("Login");
	searchPaths.push_back("ChonBanChoi");
	searchPaths.push_back("Main");
	searchPaths.push_back("MainLayer");
	searchPaths.push_back("iconGame");
	searchPaths.push_back("ccbi");
	searchPaths.push_back("fonts");
	searchPaths.push_back("card_Chan");
	searchPaths.push_back("Nan3Cay");
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

	SIZE_SCREEN = CCDirector::sharedDirector()->getVisibleSize();

	// Add updateEvent for this class - Important
	this->schedule(schedule_selector(SceneManager::updateEvent));

	// initialize - end
	//
	/// ----------
	this->setAnchorPoint(ccp(0.5, 0.5));
	this->setPosition(ccp(SIZE_SCREEN.width / 2, SIZE_SCREEN.height / 2));

	// add background
	background = CCSprite::create("background.png");
	background->setAnchorPoint(ccp(0.5, 0.5));
	background->setPosition(ccp(0, 0));
	this->addChild(background);

	background_Chan = NULL;

	// set Scale app
	float scaleX = SIZE_SCREEN.width / WIDTH_DESIGN;
	float scaleY = SIZE_SCREEN.height / HEIGHT_DESIGN;
	float scaleMin = (scaleX < scaleY) ? scaleX : scaleY;
	float scaleMax = (scaleX > scaleY) ? scaleX : scaleY;

	background->setScale(scaleMax / scaleMin);
	this->schedule(schedule_selector(SceneManager::updateEvent));
	GameServer::getSingleton().addListeners(this);

	//Init class for loader ccbi files
	ccbReader = NULL;
	ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);
	V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, TextFieldCustom);
	V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, TextFieldCustomPopUp);

	// register loaders
	ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerMain",   LayerMainLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerLogin",   LayerLoginLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerNotification",   LayerNotificationLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerGameCoTuong",   LayerPlayGameChinessChessLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerCreateAccount",   LayerCreateAccountLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerPlayerInfo",   LayerPlayerInfoLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerCreateRoom",   LayerCreateRoomLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerFriendDetails",   LayerFriendDetailsLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerTransferMoney",   LayerTransferMoneyLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerCurrencyExchange",   LayerCurrencyExchangeLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerBorrowMoney",   LayerBorrowMoneyLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerLichSuGiaoDich",   LayerLichSuGiaoDichLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerChargeMoney",   LayerChargeMoneyLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerUserInfo_Details",   LayerUserInfo_DetailsLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerChangeAvatar",   LayerChangeAvatarLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerBuyAvatar",   LayerBuyAvatarLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerChangePassword",   LayerChangePasswordLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerAction",   LayerActionLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerUpdateInfo",   LayerUpdateInfoLoader::loader());

	// Add LayerLogin
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	if (ccbReader)
	{
		layerLogin = (LayerLogin *)ccbReader->readNodeGraphFromFile( "LayerLogin.ccbi" );
		ccbReader->release();
	}
	// Add LayerMain
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	if (ccbReader)
	{
		layerMain = (LayerMain *)ccbReader->readNodeGraphFromFile( "LayerMain.ccbi" );
		ccbReader->release();
	}
	// Add LayerNotification
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	if (ccbReader)
	{
		layerNotification = (LayerNotification *)ccbReader->readNodeGraphFromFile( "LayerNotification.ccbi" );
		ccbReader->release();
	}

	this->addChild(layerLogin, zorder_LayerLogin, tag_LayerLogin);
	this->addChild(layerMain, zorder_LayerMain, tag_LayerMain);
	this->addChild(layerNotification, zorder_LayerNotification, tag_LayerNotification);

	// Layer Đầu tiên: Login
	hideNotification();
	gotoLogin();

	return true;
}

//Hiện 1 layer
bool SceneManager::showLayer(CCLayer *pLayer) {
	if (pLayer == NULL) return false;
	pLayer->setPosition(ccp(-WIDTH_DESIGN / 2, -HEIGHT_DESIGN / 2));
	pLayer->setVisible(true);
	return true;
}

// Ẩn 1 Layer
bool SceneManager::hideLayer(CCLayer *pLayer) {
	if (pLayer == NULL) return false;
	pLayer->setPosition(ccp(SIZE_SCREEN.width, pLayer->getPositionY()));
	pLayer->setVisible(false);
	return true;
}

bool SceneManager::showNotification(){
	if( layerNotification->isVisible() )
		return false;
	layerNotification->setAnchorPoint(ccp(0, 0));
	layerNotification->setPosition(ccp(-WIDTH_DESIGN / 2, -HEIGHT_DESIGN / 2));
	//layerNotification->setPosition(ccp(SIZE_SCREEN.width/2, SIZE_SCREEN.width/2));
	layerNotification->setVisible(true);
	return true;
}

bool SceneManager::hideNotification(){
	layerNotification->setPosition(ccp(SIZE_SCREEN.width, layerNotification->getPositionY()));
	layerNotification->setVisible(false);

	return true;
}

// Đến màn hình login
void SceneManager::gotoLogin() {
	showLayer(layerLogin);
	hideLayer(layerMain);
}

// Đến Main
void SceneManager::gotoMain() {
	releaseCurrentLayerGame();
	showLayer(layerMain);
	layerMain->gotoServices();
	layerMain->loadAllMyDatas();
	hideLayer(layerLogin);
}

// Go to Game
void SceneManager::gotoGameByTag(int typeGame) {
	CCLOG("typeGame: %d", typeGame);
	switch (typeGame) {
	case kGameTienLenMienNam:

		mGameTLMN = new LayerPlayGameTLMN();
		this->addChild(mGameTLMN, zorder_LayerGaming, tag_LayerGaming);
		showLayer(mGameTLMN);

		break;
	case kGameTienLenMienBac:

		mGameTLMN = new LayerPlayGameTLMN();
		this->addChild(mGameTLMN, zorder_LayerGaming, tag_LayerGaming);
		showLayer(mGameTLMN);

		break;
	case kGamePhom:

		mGamePhom = new LayerPlayGamePhom();
		this->addChild(mGamePhom, zorder_LayerGaming, tag_LayerGaming);
		showLayer(mGamePhom);
		break;
	case kGameBaCay:
		CCLOG("Ba Cây Thường");
		mBaCayNormal = new BaCayNormal();
		this->addChild(mBaCayNormal,zorder_LayerGaming, tag_LayerGaming);
		showLayer(mBaCayNormal);
		break;
	case kGameBaCayChuong:
		CCLOG("Ba Cây Chương");
		mBaCayChuong = new BaCayChuong();
		this->addChild(mBaCayChuong,zorder_LayerGaming, tag_LayerGaming);
		showLayer(mBaCayChuong);
		break;
	case kGameLieng:
		CCLOG("Liêng");
		mGameLieng = new Lieng();
		this->addChild(mGameLieng,zorder_LayerGaming, tag_LayerGaming);
		showLayer(mGameLieng);
		break;
	case kGameXiTo:
		mGameXiTo = new XiTo();
		this->addChild(mGameXiTo,zorder_LayerGaming, tag_LayerGaming);
		showLayer(mGameXiTo);
		break;
	case kGameCoTuong:
		ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
		LayerPlayGameChinessChess* mLayer;
		if (ccbReader)
		{
			mLayer = (LayerPlayGameChinessChess *)ccbReader->readNodeGraphFromFile( "LayerGameCoTuong.ccbi" );
			mLayer->setPosition(ccp(-WIDTH_DESIGN / 2, -HEIGHT_DESIGN / 2));
			this->addChild(mLayer, 1, 1);
			ccbReader->release();
		}
		break;
	case kGameChan:
		mGameChan = new LayerChanGame();
		this->setBackgroundScreen(true);
		this->addChild(mGameChan,zorder_LayerGaming, tag_LayerGaming);
		showLayer(mGameChan);
		break;
	}

	hideLayer(layerMain);
}

void SceneManager::releaseCurrentLayerGame() {
	CCNode *child = NULL;
	child = this->getChildByTag(tag_LayerGaming);
	if (child == NULL) {
		CCLog("You did not play the Game!");
	}
	else {
		// this->removeChildByTag(tag_LayerGaming, true);
		child->removeFromParentAndCleanup(true);
		//CC_SAFE_RELEASE(child);
		CCLog("You played the Game!");
	}
}

// exit
void SceneManager::exitScene()
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

// server
void SceneManager::updateEvent(float dt) {
	GameServer::getSingleton().updateEvent();
}

void SceneManager::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];

	if(strcmp("hbc", ptrNotifiedCmd->c_str())==0){
		//        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
		//        //sendRequest
		//        boost::shared_ptr<IRequest> request (new ExtensionRequest("ghbres",parameter));
		//        GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void SceneManager::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLog("OnSmartFoxConnectionLost");
	disconnectFromServer();
}
void SceneManager::OnSmartFoxDisconnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLog("OnSmartFoxDisconnection");
	disconnectFromServer();
}
void SceneManager::OnSmartFoxSocketError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLog("OnSmartFoxSocketError");
	disconnectFromServer();
}

string SceneManager::getMyName() {
	return (GameServer::getSingleton().getSmartFox()->MySelf()->Name())->c_str();
}

void SceneManager::setBackgroundScreen(bool _state){
	if (_state) {
		background_Chan = CCSprite::create("backChan.png");
		background_Chan->setAnchorPoint(ccp(0.5, 0.5));
		background_Chan->setPosition(ccp(0, 0));
		this->addChild(background_Chan);

		// set Scale app
		float scaleX = SIZE_SCREEN.width / WIDTH_DESIGN;
		float scaleY = SIZE_SCREEN.height / HEIGHT_DESIGN;
		float scaleMin = (scaleX < scaleY) ? scaleX : scaleY;
		float scaleMax = (scaleX > scaleY) ? scaleX : scaleY;

		background_Chan->setScale(scaleMax / scaleMin);
	}
	else{
		if (background_Chan != NULL) {
			this->removeChild(background_Chan);
		}
	}

}

void SceneManager::disconnectFromServer()
{
	//Close all current view
	releaseCurrentLayerGame();
	hideNotification();
	gotoLogin();
	layerMain->removeOldView();
	layerMain->setCurrentViewTagDefault();
	//
	Chat *toast = new Chat("Mất kết nối!", -1);
	layerLogin->addChild(toast);
}
