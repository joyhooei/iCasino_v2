//
//  LayerChargeMoney.cpp
//  demo
//
//  Created by AlexDao on 5/30/14.
//
//

#include "LayerChargeMoney.h"
#include "Requests/ExtensionRequest.h"
#include "LayerSMS.h"
#include "LayerTyGia.h"
#include "mUtils.h"
#include "SceneManager.h"
#include "_Chat_.h"
using namespace cocos2d;
//using namespace CocosDenshion;


LayerChargeMoney::LayerChargeMoney()
{
    lblCuPhap = NULL;
    lblDauSo = NULL;
    txtMaThe = NULL;
    txtSoThe = NULL;
    btnViettelStatus = NULL;
    btnVinaStatus = NULL;
    btnMobiStatus = NULL;
    arrow_left = NULL;
    
    currState = tag_viettel;

	isPopup = false;
    //
    GameServer::getSingleton().addListeners(this);

}

LayerChargeMoney::~LayerChargeMoney()
{
    GameServer::getSingleton().removeListeners(this);
	//
	CC_SAFE_RELEASE(lblCuPhap);
	CC_SAFE_RELEASE(lblDauSo);
	CC_SAFE_RELEASE(txtMaThe);
	CC_SAFE_RELEASE(txtSoThe);
	CC_SAFE_RELEASE(btnViettelStatus);
	CC_SAFE_RELEASE(btnVinaStatus);
	CC_SAFE_RELEASE(btnMobiStatus);
	CC_SAFE_RELEASE(arrow_left);
}

void LayerChargeMoney::notificationCallBack(bool isOK, int tag){
	CCLOG("callbackNtf****");
}

void LayerChargeMoney::setButtonState( tagButtonState tag){
    btnMobiStatus->setEnabled(tag_mobi == tag);
    btnViettelStatus->setEnabled(tag_viettel == tag);
    btnVinaStatus->setEnabled(tag_vina == tag);
    //
    float y = 0;
    switch (tag) {
        case tag_viettel:
            y = 196;
            break;
        case tag_mobi:
            y = 75;
            break;
        case tag_vina:
            y = 135;
            break;
    }
    arrow_left->setPosition(ccp( arrow_left->getPositionX(), y ));
}

// CCBSelectorResolver interface
SEL_MenuHandler LayerChargeMoney::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    //CCLOG("Imhere onResolveCCBCCMenuItemSelector: %s", pSelectorName);
// 	if( strcmp( pSelectorName, "btnExchange" )==0 ){
// 		CCMenuItem* btnExchange = dynamic_cast<CCMenuItem*>(pTarget);
// 		CCLOG("btnExchange w: %lf h:%lf", btnExchange->getContentSize().width, btnExchange->getContentSize().height);
// 	}
	CCLOG("pSelectorName: %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnViettel", LayerChargeMoney::onButtonViettelClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnViettelStatus", LayerChargeMoney::onButtonViettelClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnVina", LayerChargeMoney::onButtonVinaClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnVinaStatus", LayerChargeMoney::onButtonVinaClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnMobi", LayerChargeMoney::onButtonMobiClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnMobiStatus", LayerChargeMoney::onButtonMobiClick);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnOK", LayerChargeMoney::onButtonOKClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnSMS", LayerChargeMoney::onButtonSMSClick);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnTyGia", LayerChargeMoney::onButtonTyGiaClick);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnClose", LayerChargeMoney::onButtonCloseClick);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "btnExchange", LayerChargeMoney::onButtonExchangeClick);
    return NULL;
}

void LayerChargeMoney::onButtonCloseClick( CCObject* pSender )
{
	CCLOG("onButtonCloseClick");
	this->removeFromParentAndCleanup(true);
}

void LayerChargeMoney::onButtonExchangeClick(CCObject* pSender){
	CCLOG("onButtonExchangeClick");
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	ccNodeLoaderLibrary->unregisterCCNodeLoader("LayerSMS");
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerSMS",   LayerTyGiaLoader::loader());
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	LayerTyGia* mLayer;
	if (ccbReader)
	{
		mLayer = (LayerTyGia *)ccbReader->readNodeGraphFromFile( "LayerSMS.ccbi" );
		this->addChild(mLayer, 1, 1);
		//        SceneManager::getSingleton().showLayer(mLayer);
		ccbReader->release();
	}
}

void LayerChargeMoney::onButtonViettelClick(CCObject* pSender){
    setButtonState(tag_viettel);
}
void LayerChargeMoney::onButtonVinaClick(CCObject* pSender){
    setButtonState(tag_vina);
}
void LayerChargeMoney::onButtonMobiClick(CCObject* pSender){
    setButtonState(tag_mobi);
}
void LayerChargeMoney::onButtonOKClick(CCObject* pSender){
    CCLOG("onButtonOKClick");
    if( strcmp( txtMaThe->getText(), "") ==0 || strlen(txtMaThe->getText())!=14 ){
		CCLOG("LayerChargeMoney::onButtonOKClick -- ERROR - txtMaThe is invalid");
		Chat *toast = new Chat("Mã thẻ phải là 14 ký tự!", -1);
		this->addChild(toast);
    }
    if( strcmp( txtSoThe->getText(), "") ==0 || strlen(txtSoThe->getText())!=14 ){
		CCLOG("LayerChargeMoney::onButtonOKClick -- ERROR - txtSoThe is invalid");
		Chat *toast = new Chat("Số thẻ phải là 14 ký tự!", -1);
		this->addChild(toast);
    }
    //issues
    CCString *issues = CCStringMake("VT");
    if( btnMobiStatus->isEnabled() )
        issues = CCStringMake("MOBI");
    else if( btnVinaStatus->isEnabled() )
        issues = CCStringMake("VINA");
    //send request
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    params->PutUtfString("issuer", issues->getCString());
    params->PutUtfString("cardserial", txtSoThe->getText());
    params->PutUtfString("cardcode", txtMaThe->getText());
    boost::shared_ptr<IRequest> request (new ExtensionRequest("rv", params));
    GameServer::getSingleton().getSmartFox()->Send(request);
}
void LayerChargeMoney::onButtonSMSClick(CCObject* pSender){
    CCLOG("onButtonSMSClick");
    //
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
    ccNodeLoaderLibrary->unregisterCCNodeLoader("LayerSMS");
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerSMS",   LayerSMSLoader::loader());
    CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerSMS* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerSMS *)ccbReader->readNodeGraphFromFile( "LayerSMS.ccbi" );
        this->addChild(mLayer, 1, 1);
        ccbReader->release();
    }
}
void LayerChargeMoney::onButtonTyGiaClick(CCObject* pSender){
    CCLOG("onButtonTyGiaClick");
    //
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
    ccNodeLoaderLibrary->unregisterCCNodeLoader("LayerSMS");
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerSMS",   LayerTyGiaLoader::loader());
    CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    LayerTyGia* mLayer;
    if (ccbReader)
    {
        mLayer = (LayerTyGia *)ccbReader->readNodeGraphFromFile( "LayerSMS.ccbi" );
        this->addChild(mLayer, 1, 1);
//        SceneManager::getSingleton().showLayer(mLayer);
        ccbReader->release();
    }
}

// CCBMemberVariableAssigner interface
bool LayerChargeMoney::onAssignCCBMemberVariable(CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCLOG("Imhere onAssignCCBMemberVariable: %s", pMemberVariableName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblCuPhap", CCLabelTTF *, lblCuPhap);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lblDauSo", CCLabelTTF *, lblDauSo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "arrow_left", CCSprite*, arrow_left);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtMaThe", CCEditBox *, txtMaThe);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "txtSoThe", CCEditBox*, txtSoThe);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnMobiStatus", CCMenuItem *, btnMobiStatus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnVinaStatus", CCMenuItem *, btnVinaStatus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "btnViettelStatus", CCMenuItem *, btnViettelStatus);
    return true;
}

void LayerChargeMoney::onNodeLoaded( CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    CCLOG("Imhere onNodeLoaded");
    //Disable two buttons
    setButtonState(tag_viettel);
    //init textfield
    initTextField(txtMaThe, "Mã thẻ");
    initTextField(txtSoThe, "Số thẻ");
    
    //demo
    txtMaThe->setText("12345678901234");
    txtSoThe->setText("01234567891234");
    return;
}

void LayerChargeMoney::initTextField(CCEditBox* txt, const char* hintText){
    txt->setFontColor(ccBLACK);
    txt->setPlaceholderFontColor(ccBLACK);
    txt->setFont("fonts/Roboto-Regular.ttf", 18);
    txt->setReturnType(kKeyboardReturnTypeDefault);
	txt->setPlaceHolder(hintText);
	txt->setInputMode(kEditBoxInputModeAny);
	txt->setTouchPriority(-128);
}

void LayerChargeMoney::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    CCLOG( "OnExtensionResponse %s", cmd->c_str() );
	if(strcmp("rg", cmd->c_str())==0){//OK	
		LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
		if( !SceneManager::getSingleton().showNotification() ){
			CCLOG("NTF Dialog already open!");
			return;
		}
        if( *param->GetInt("rc")==1 ){
			layer->setNotificationOptions("NẠP THẺ THÀNH CÔNG", 
				"Nạp thẻ thành công!", false , "", 1, this );
			CCLOG("Nap the OK");
        }else{
			CCLOG("Nap the NOT OK %s", "i dont no");
			layer->setNotificationOptions("NẠP THẺ THẤT BẠI", 
				"Nạp thẻ thất bại", false , "", 1, this );
        }
    }
}

void LayerChargeMoney::setIsPopup( bool b )
{
	isPopup = b;
}

void LayerChargeMoney::registerWithTouchDispatcher( void )
{
	if( isPopup ){
		CCLOG("isPopup: %s", isPopup?"true":"false");
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -127, true);
	}
}

bool LayerChargeMoney::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void LayerChargeMoney::onEnter()
{
	CCLayer::onEnter();
	//
	if( isPopup )
		this->runAction(mUtils::getActionOpenPopup());
}

void LayerChargeMoney::onExit()
{
	CCLayer::onExit();
}
