//
//  LayerMain.cpp
//  demo
//
//  Created by AlexDao on 5/29/14.
//
//

#include "LayerMain.h"
#include "LayerUserInfo.h"
#include "LayerMoney.h"
#include "LayerFriend.h"
#include "LayerSettings.h"
#include "LayerFriendDetails.h"
#include "LayerServices.h"
#include "LayerChooseGame.h"
#include "LayerChonBanChoi.h"
#include "LayerInbox.h"
#include "SliderCustomLoader.h"
#include "TextFieldCustomLoader.h"
#include "LayerChatRoom.h"
#include "LayerEmailDetails.h"
#include "LayerComposeEmail.h"

#include "SceneManager.h"

#include "Requests/LogoutRequest.h"
#include "mUtils.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "platform/android/jni/Android.h"
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "IOS.h"
#endif
template<> LayerMain* SingLeton<LayerMain>::mSingleton = 0;

LayerMain* LayerMain::getSingletonPtr(void)
{
	return mSingleton;
}
LayerMain& LayerMain::getSingleton(void)
{
	assert( mSingleton );  return ( *mSingleton );
}

LayerMain::LayerMain()
{
	imageDownloader = new ImageDownloader();

    lblAM = NULL;
    lblAMF = NULL;
    lblCountOfMails = NULL;
    lblName = NULL;
    nodeAvatar= NULL;
    
    currNodeView = NULL;
    
    ccbReader = NULL;
    ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);
    V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, TextFieldCustom);
    
    // register loaders
    ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerUserInfo",   LayerUserInfoLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerMoney",   LayerMoneyLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerFriend",   LayerFriendLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerSettings",   LayerSettingsLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerFriendDetails",   LayerFriendDetailsLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerServices",   LayerServicesLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerChooseGame",   LayerChooseGameLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerChonBanChoi",   LayerChonBanChoiLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerInbox",   LayerInboxLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerChatRoom",   LayerChatRoomLoader::loader());
	CCLOG("LayerMain::LayerMain()");


    //
    GameServer::getSingleton().addListeners(this);
    //

    gotoServices();
}

LayerMain::~LayerMain()
{

    //
    GameServer::getSingleton().removeListeners(this);
    
}

void LayerMain::loadAllMyDatas(){
    boost::shared_ptr<double> am, amf;
    boost::shared_ptr<string> aal;
    boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
	if( myself==NULL )
		return;
    if( myself==NULL || myself->GetVariable("am")==NULL || myself->GetVariable("amf")==NULL ){
        CCLOG("myself %s= NULL | myself->GetVariable(am) %s= NULL | myself->GetVariable(amf)%s=NULL",
              myself==NULL?"=":"!", myself->GetVariable("am")==NULL?"=":"!", myself->GetVariable("amf")==NULL?"=":"!");
        return;
    }
    am = myself->GetVariable("am")->GetDoubleValue();
    amf = myself->GetVariable("amf")->GetDoubleValue();
    aal = myself->GetVariable("aal")->GetStringValue();
    //Set Name
    lblName->setString( GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("aN")->GetStringValue()->c_str() );
    lblAMF->setString( mUtils::convertMoneyEx(*amf).c_str() );
    lblAM->setString( mUtils::convertMoneyEx(*am).c_str() );
    //Set avatar
    imageDownloader->setPointerNodeImage( nodeAvatar );
	imageDownloader->downLoadImage(*aal);
}

void LayerMain::gotoServices(){
    CCLOG("%d", currViewTag);
    if( currViewTag == tag_Service )
        return;
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerServices* mLayerServices;
    if (ccbReader)
    {
        mLayerServices = (LayerServices *)ccbReader->readNodeGraphFromFile( "LayerServices.ccbi" );
        this->addChild(mLayerServices, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayerServices;
    currViewTag = tag_Service;
}

void LayerMain::gotoChooseGame(){
    if( currViewTag == tag_ChooseGame )
        return;
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerChooseGame* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerChooseGame *)ccbReader->readNodeGraphFromFile( "LayerChooseGame.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
    currViewTag = tag_ChooseGame;
}
void LayerMain::gotoChonBanChoi(int gID){
    if( currViewTag == tag_ChonBanChoi )
        return;
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerChonBanChoi* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerChonBanChoi *)ccbReader->readNodeGraphFromFile( "LayerChonBanChoi.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
    currViewTag = tag_ChonBanChoi;
    mLayer->setGameID(gID);
}

void LayerMain::gotoUserInfo(){
    if( currViewTag == tag_UserInfo )
        return;
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerUserInfo* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerUserInfo *)ccbReader->readNodeGraphFromFile( "LayerUserInfo.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
    currViewTag = tag_UserInfo;
}

void LayerMain::gotoMoney(){
    if( currViewTag == tag_Money )
        return;
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerMoney* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerMoney *)ccbReader->readNodeGraphFromFile( "LayerMoney.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
    currViewTag = tag_Money;
}

void LayerMain::gotoTransferMoney( string toUser )
{
	removeOldView();
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	LayerMoney* mLayer;
	if (ccbReader)
	{
		mLayer = (LayerMoney *)ccbReader->readNodeGraphFromFile( "LayerMoney.ccbi" );
		this->addChild(mLayer, 1, 1);
		ccbReader->release();
		mLayer->gotoTransfer( toUser );
	}
	currNodeView = mLayer;
	currViewTag = tag_Money;
}

void LayerMain::gotoMail(){
    if( currViewTag == tag_Mail )
        return;
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerInbox* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerInbox *)ccbReader->readNodeGraphFromFile( "LayerInbox.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    mLayer->loadAllMyDatas();
    currNodeView = mLayer;
    currViewTag = tag_Mail;
}

void LayerMain::gotoFriends(){
    if( currViewTag == tag_Friends )
        return;
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerFriend* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerFriend *)ccbReader->readNodeGraphFromFile( "LayerFriend.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
    currViewTag = tag_Friends;
}

void LayerMain::gotoGuide(){
    return;
    if( currViewTag == tag_Guide )
        return;
    removeOldView();
//    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//    LayerFriend* mLayer;
//    if (ccbReader)
//    {
//        mLayer = (LayerFriend *)ccbReader->readNodeGraphFromFile( "LayerFriend.ccbi" );
//        this->addChild(mLayer, 1, 1);
//        ccbReader->release();
//    }
//    currNodeView = mLayer;
//    currViewTag = tag_Friends;
}

void LayerMain::gotoChat(){
    if( currViewTag == tag_ChatRoom )
        return;
    removeOldView();
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerChatRoom* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerChatRoom *)ccbReader->readNodeGraphFromFile( "LayerChatRoom.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
    currNodeView = mLayer;
    currViewTag = tag_Friends;
}

void LayerMain::gotoShop(){
    return;
    if( currViewTag == tag_Shop )
        return;
    removeOldView();
//    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//    LayerFriend* mLayer;
//    if (ccbReader)
//    {
//        mLayer = (LayerFriend *)ccbReader->readNodeGraphFromFile( "LayerFriend.ccbi" );
//        this->addChild(mLayer, 1, 1);
//        ccbReader->release();
//    }
//    currNodeView = mLayer;
//    currViewTag = tag_Friends;
}

void LayerMain::gotoRank(){
    return;
    if( currViewTag == tag_Rank )
        return;
    removeOldView();
//    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//    LayerFriend* mLayer;
//    if (ccbReader)
//    {
//        mLayer = (LayerFriend *)ccbReader->readNodeGraphFromFile( "LayerFriend.ccbi" );
//        this->addChild(mLayer, 1, 1);
//        ccbReader->release();
//    }
//    currNodeView = mLayer;
//    currViewTag = tag_Friends;
}

void LayerMain::logoutAndExit(){
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    turnOffAd();
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    IOS::turnOffAD();
#endif
    removeOldView();
    boost::shared_ptr<IRequest> request (new LogoutRequest());
    //
    SceneManager::getSingleton().gotoLogin();
    currViewTag = tag_ChatRoom;
    CCLOG("Logout");

    GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerMain::removeOldView(){
    if( currNodeView==NULL )
        return;
    currNodeView->removeFromParentAndCleanup(true);
//    try{
//        currNodeView->release()();
//    }catch(...){
//        
//    }
    currNodeView = NULL;
}

void LayerMain::closeOldView(){
    removeOldView();
    boost::shared_ptr<IRequest> request (new LogoutRequest());
    //
    switch(currViewTag){
        case tag_Service:
            SceneManager::getSingleton().gotoLogin();
            currViewTag = tag_ChatRoom;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
            turnOffAd();
#endif
            CCLOG("Logout");
            GameServer::getSingleton().getSmartFox()->Send(request);
            break;
        case tag_Money:
        case tag_Mail:
        case tag_Friends:
        case tag_Rank:
        case tag_ChatRoom:
        case tag_Guide:
        case tag_UserInfo:
        case tag_Shop:
            gotoServices();
            break;
        case tag_ChooseGame:
            gotoServices();
            break;
        case tag_ChonBanChoi:
            gotoChooseGame();
            break;
		case tag_EmailDetails:
		case tag_ComposeEmail:
			gotoMail();
			break;
    }
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerMain::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    //CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnUserInfo", LayerMain::onButtonUserInfo);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnMoney", LayerMain::onButtonMoney);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnMail", LayerMain::onButtonMail);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnFriend", LayerMain::onButtonFriends);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnSettings", LayerMain::onButtonSettings);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnBack", LayerMain::onButtonBack);
    return NULL;
}

void LayerMain::onButtonUserInfo(CCObject* pSender)
{
    CCLOG("onButtonUserInfo");
    gotoUserInfo();
}
void LayerMain::onButtonMoney(CCObject* pSender)
{
    CCLOG("onButtonMoney");
    gotoMoney();
}
void LayerMain::onButtonMail(CCObject* pSender)
{
    CCLOG("onButtonMail");
    gotoMail();
}
void LayerMain::onButtonFriends(CCObject* pSender)
{
    CCLOG("onButtonFriends");
    gotoFriends();
}
void LayerMain::onButtonSettings(CCObject* pSender)
{
    CCLOG("onButtonSettings");
    // read main layer
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerSettings* mLayerSettings;
    if (ccbReader)
    {
        mLayerSettings = (LayerSettings *)ccbReader->readNodeGraphFromFile( "LayerSettings.ccbi" );
        this->addChild(mLayerSettings, 1, 1);
        ccbReader->release();
    }
}
void LayerMain::onButtonBack(CCObject* pSender)
{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    turnOnAd();
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    IOS::turnOnAD();
#endif
    CCLOG("onButtonBack");
    closeOldView();
}

// CCBMemberVariableAssigner interface
bool LayerMain::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblAM", CCLabelTTF *, lblAM);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblAMF", CCLabelTTF *, lblAMF);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblCountOfMails", CCLabelTTF *, lblCountOfMails);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblName", CCLabelTTF *, lblName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nodeAvatar", CCNode *, nodeAvatar);
    return true;
}

void LayerMain::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
	CCLOG("LayerMain - onNodeLoaded");
	this->setKeypadEnabled(true);
	//
	nodeAvatar->setContentSize(ccp(nodeAvatar->getContentSize().width+4, nodeAvatar->getContentSize().height+1.8));
	nodeAvatar->setPositionY(nodeAvatar->getPositionY()+1);
	nodeAvatar->setPositionX(nodeAvatar->getPositionX()-2);
    return;
}

void LayerMain::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    //get the user parameter of the event
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
    
	//if self
	if ( ptrNotifiedUser->IsItMe() == true )
		loadAllMyDatas();
}

// void LayerMain::loadDefaultImage(){
//     CCSprite* pSprite = CCSprite::createWithSpriteFrameName("assest/icon_default.png");
//     pSprite->setAnchorPoint(ccp(0, 0));
//     pSprite->cocos2d::CCNode::setScale(nodeAvatar->getContentSize().width/pSprite->getContentSize().width, nodeAvatar->getContentSize().height/pSprite->getContentSize().height);
//     //Call callback
//     nodeAvatar->removeAllChildrenWithCleanup(true);
//     //
//     nodeAvatar->addChild(pSprite);
// }
// 
// void LayerMain::downLoadImage(string url, string fileName){
//     if( url.compare("")==0 || fileName=="" ){
//         loadDefaultImage();
//         return;
//     }
// 	//Check filename existed ?
// 	std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
// 	writablePath.append( fileName );
// 	std::ifstream f(writablePath.c_str());
// 	if(f){
// 		//existed
// 		CCSprite* pSprite = NULL;
// 		try{
// 			pSprite = CCSprite::create("abcxyz");
// 		}catch(...){
// 			return;
// 		}
// 		if( pSprite==NULL )
// 			return;
// 		pSprite->setAnchorPoint(ccp(0, 0));
// 		pSprite->cocos2d::CCNode::setScale(nodeAvatar->getContentSize().width/pSprite->getContentSize().width, nodeAvatar->getContentSize().height/pSprite->getContentSize().height);
// 		//Call callback
// 		nodeAvatar->removeAllChildrenWithCleanup(true);
// 		//
// 		nodeAvatar->addChild(pSprite);
// 		CCLOG("fileName: %s existed", fileName.c_str());
// 		return;
// 	}
// 	//
//     CCHttpRequest* request = new CCHttpRequest();
//     request->setUrl(url.c_str());
//     request->setRequestType(CCHttpRequest::kHttpGet);
//     request->setResponseCallback(this, httpresponse_selector(LayerMain::onImageDownLoaded));
//     request->setTag(fileName.c_str());
//     CCHttpClient::getInstance()->send(request);
//     request->release();
// }
// 
// void LayerMain::onImageDownLoaded(CCHttpClient* pSender, CCHttpResponse* pResponse){
//     CCHttpResponse* response = pResponse;
//     
//     if (!response)
//     {
//         CCLog("No Response");
//         loadDefaultImage();
//         return ;
//     }
//     int statusCode = response->getResponseCode();
//     
//     char statusString[64] = {};
//     sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
//     CCLog("response code: %d", statusCode);
//     
//     if (!response->isSucceed())
//     {
//         CCLog("response failed");
//         CCLog("error buffer: %s", response->getErrorBuffer());
//         loadDefaultImage();
//         return;
//     }
//     std::vector<char>*buffer = response->getResponseData();
//     
//     
//     CCImage * img=new CCImage();
//     img->initWithImageData(&(buffer->front()), buffer->size());
//     
//     // Save image file to device.
//     std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
//     writablePath.append(response->getHttpRequest()->getTag());
//     // add this line
//     img->saveToFile(writablePath.c_str());
//     
//     //Now create Sprite from downloaded image
//     CCSprite* pSprite = CCSprite::create(writablePath.c_str());
//     pSprite->setAnchorPoint(ccp(0, 0));
//     pSprite->cocos2d::CCNode::setScale(nodeAvatar->getContentSize().width/pSprite->getContentSize().width, nodeAvatar->getContentSize().height/pSprite->getContentSize().height);
//     //Call callback
//     nodeAvatar->removeAllChildrenWithCleanup(true);
//     //
//     nodeAvatar->addChild(pSprite);
// }

void LayerMain::autoJoinGameWithID( int gID, int rID )
{
	gotoChonBanChoi(gID);
	if( currViewTag==tag_ChonBanChoi ){
		LayerChonBanChoi* cLayer = (LayerChonBanChoi*)currNodeView;
		cLayer->joinRoomByID(rID);
	}
}

void LayerMain::keyBackClicked()
{
	if( SceneManager::getSingleton().getCurrentLayerTag() != tag_LayerMain )
		return;
	CCLOG("LayerMain::keyBackClicked()");
	closeOldView();
}

void LayerMain::gotoMailDetails(int idMsg, string fromUser, string toUser, string date, string contents)
{
	if( currViewTag == tag_EmailDetails )
		return;
	removeOldView();
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	LayerEmailDetails* mLayer;
	if (ccbReader)
	{
		mLayer = (LayerEmailDetails *)ccbReader->readNodeGraphFromFile( "LayerEmailDetails.ccbi" );
		this->addChild(mLayer, 1, 1);
		ccbReader->release();
		mLayer->setDatas(idMsg, fromUser, toUser, date, contents);
	}
	currNodeView = mLayer;
	currViewTag = tag_EmailDetails;
}

void LayerMain::gotoComposeMail(string toUser, string title, string contents)
{
	if( currViewTag == tag_ComposeEmail )
		return;
	removeOldView();
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	LayerComposeEmail* mLayer;
	if (ccbReader)
	{
		mLayer = (LayerComposeEmail *)ccbReader->readNodeGraphFromFile( "LayerComposeEmail.ccbi" );
		this->addChild(mLayer, 1, 1);
		ccbReader->release();
		mLayer->setDatas(toUser, title, contents);
	}
	currNodeView = mLayer;
	currViewTag = tag_ComposeEmail;
}
