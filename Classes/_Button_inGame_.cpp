//
//  _Button_inGame_.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/15/14.
//
//

#include "SceneManager.h"
#include "Requests/LeaveRoomRequest.h"
#include "_Button_inGame_.h"
#include "LayerChatWindow.h"
#include "GameServer.h"
#include "LayerChargeMoney.h"
#include "LayerSettings.h"

#include "Requests/PublicMessageRequest.h"

bool LayerButtonInGame::init() {
	if (!UILayer::init()) return false;

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));

	//    UILayer *layerWidget = UILayer::create();
	//    layerWidget->setAnchorPoint(ccp(0, 0));
	//    layerWidget->setPosition(ccp(0, 0));
	//    this->addChild(layerWidget);

	// Button style 2
	int widButton2 = 52;
	// int heiButton2 = 50;
	int dis = 10;

	Button *btnBack = createButtonWith_Style_Position(1, ccp(dis, dis));
	Button *btnSetting = createButtonWith_Style_Position(2, ccp(dis * 2 + widButton2, dis));
	Button *btnChat = createButtonWith_Style_Position(3, ccp(dis * 3 + widButton2 * 2, dis));
	Button *btnCoin = createButtonWith_Style_Position(4, ccp(dis * 4 + widButton2 * 3, dis));

	btnBack->addTouchEventListener(this, toucheventselector(LayerButtonInGame::eventTouchBtnBack));
	btnSetting->addTouchEventListener(this, toucheventselector(LayerButtonInGame::eventTouchBtnSetting));
	btnChat->addTouchEventListener(this, toucheventselector(LayerButtonInGame::eventTouchBtnChat));
	btnCoin->addTouchEventListener(this, toucheventselector(LayerButtonInGame::eventTouchBtnCoin));

	this->addWidget(btnBack);
	this->addWidget(btnSetting);
	this->addWidget(btnChat);
	this->addWidget(btnCoin);
	//Save game ID

	gameID = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId();

	return true;
}

void LayerButtonInGame::addWidgetEx(Button* node){
	this->addWidget(node);
}

Button* LayerButtonInGame::createButtonWith_Style_Position(int style, CCPoint pPoint) {
	// Create the button
	Button* button = Button::create();
	button->setTouchEnabled(true);
	button->setScale9Enabled(false);
	button->setAnchorPoint(ccp(0, 0));

	switch (style) {
	case 1:
		// back
		button->loadTextures("button_back.png", "button_back.png", "");
		break;
	case 2:
		// setting
		button->loadTextures("button_setting.png", "button_setting.png", "");
		break;
	case 3:
		// chat
		button->loadTextures("button_chat.png", "button_chat.png", "");
		break;
	case 4:
		// coin
		button->loadTextures("button_coin.png", "button_coin.png", "");
		break;

	default:
		break;
	}

	button->setPosition(pPoint);

	return button;
}


void LayerButtonInGame::eventTouchBtnBack(CCObject *pObject, TouchEventType pType){
	if (pType == TOUCH_EVENT_ENDED) {
		CCLOG("Click back");
		if( GameServer::getSingleton().getSmartFox()->LastJoinedRoom()==NULL ){
			SceneManager::getSingleton().gotoMain();
			return;
		} 
		if (gameID == NULL) {
			return;
		}
		string _gameID = gameID->c_str();
		if (_gameID == "109") {
			SceneManager::getSingleton().setBackgroundScreen(false);
		}

		SceneManager::getSingleton().gotoMain();
		LayerMain::getSingleton().gotoChonBanChoi( atol(gameID->c_str()) );

		// leave room
		boost::shared_ptr<IRequest> request (new LeaveRoomRequest());
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void LayerButtonInGame::eventTouchBtnSetting(CCObject *pObject, TouchEventType pType){
	if (pType == TOUCH_EVENT_ENDED){
		CCLOG("Click Setting");
		CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
		CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
		LayerSettings* mLayerSettings;
		if (ccbReader)
		{
			mLayerSettings = (LayerSettings *)ccbReader->readNodeGraphFromFile( "LayerSettings.ccbi" );
			SceneManager::getSingleton().getLayerOnTop()->addChild(mLayerSettings, 1, 1);
			ccbReader->release();
		}
	}
}

void LayerButtonInGame::eventTouchBtnChat(CCObject *pObject, TouchEventType pType){
	if (pType == TOUCH_EVENT_ENDED){
		CCLOG("Click Chat");
		LayerChatWindow* l = SceneManager::getSingleton().getLayerChatWindow();
		l->setCallbackFunc(this,callfuncND_selector(LayerButtonInGame::callbackFromChatWindow));
		SceneManager::getSingleton().showLayerChatWindow();
	}
}

void LayerButtonInGame::eventTouchBtnCoin(CCObject *pObject, TouchEventType pType){
	if (pType == TOUCH_EVENT_ENDED){
		CCLOG("Click Coin"); 
		//
		CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
		CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
		LayerChargeMoney* mLayer;
		if (ccbReader)
		{
			mLayer = (LayerChargeMoney *)ccbReader->readNodeGraphFromFile( "LayerPopupChargeMoney.ccbi" );
			mLayer->setIsPopup(true);
			this->getParent()->addChild(mLayer, 1, 1);
			mLayer->setTouchEnabled(true);
			ccbReader->release();
		}
	}
}

void LayerButtonInGame::callbackFromChatWindow( CCNode*, void* data )
{
	if( strlen((char*)data)==0 )
		return;
	boost::shared_ptr<ISFSObject> parameters(new SFSObject());
	boost::shared_ptr<IRequest> request (new PublicMessageRequest((char*)data, parameters, GameServer::getSingleton().getSmartFox()->LastJoinedRoom())); 
	GameServer::getSingleton().getSmartFox()->Send(request);
}
