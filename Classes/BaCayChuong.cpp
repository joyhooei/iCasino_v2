//
//  BaCayChuong.cpp
//  iCasinov2
//
//  Created by DauA on 5/23/14.
//
//

#include "BaCayChuong.h"
#include "_Background_inGame_.h"
#include "Requests/ExtensionRequest.h"
#include "_Number_inGame_.h"
#include "SliderCustomLoader.h"
#include "LayerBet_BaCayChuong.h"
#include "Nan3Cay.h"
#include "_Chat_.h"
#include "mUtils.h"
#include "SceneManager.h"
#include "AllData.h"

#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())


BaCayChuong::BaCayChuong(){
	EXT_EVENT_LISTCARD_NTF = "lcntf";
	EXT_EVENT_START = "s";
	EXT_EVENT_END = "e";
	EXT_EVENT_READY_REQ = "rr";
	EXT_EVENT_READY_RES = "rdres";
	EXT_EVENT_UNREADY_REQ = "urr";
	EXT_EVENT_ERROR_READY_NTF = "e_rntf";
	EXT_EVENT_READY_NTF = "rntf";
	EXT_EVENT_UNREADY_NTF = "urntf";
	EXT_EVENT_TURNUP_CARD = "tuc";
	EXT_EVENT_LIST_USER_UPDATE = "luu";
	EXT_EVENT_GAME_RESULT = "grs";
	EXT_EVENT_GAME_BET_REQ = "gbr";
	EXT_EVENT_GAME_BET_ERROR_NOTIFY = "e_bntf";
	EXT_EVENT_GAME_BET_NTF = "gb_ntf";
	EXT_EVENT_DEAL_CARD_REQ = "dcrq";
	EXT_EVENT_DEAL_CARD_RES = "dcrs";
	EXT_EVENT_SELECT_OPEN_CARD_REQ = "slstrq";
	EXT_EVENT_SELECT_OPEN_CARD_RES = "slsrrs";
	EXT_EVENT_RAISE_REQ = "rsrq";
	EXT_EVENT_RAISE_RES = "rsrs";
	EXT_EVENT_FOLD_REQ = "fdrq";
	EXT_EVENT_FOLD_RES = "fdrs";

	flagChiaBai = false;
	flagDatCuoc = false;

	_list_cards = "";
	_list_users = "";

	createBackgrounds();
	createAvatars();
	createButtons();
	createCards();
	createLayerBet();

	layerChat = LayerChatInGame::create();
	this->addChild(layerChat);

	CCLOG("Da khoi tao het cac du lieu can thiet ....");
	GameServer::getSingleton().addListeners(this);
	SceneManager::getSingleton().hideLoading();
}

BaCayChuong::~BaCayChuong(){
	GameServer::getSingleton().removeListeners(this);
	this->removeAllComponents();
	CCLOG("Deconstructor 3 Cay Chuong --- Jump Here !");
}

void BaCayChuong::onExit()
{
	GameServer::getSingleton().removeListeners(this);
	this->removeAllComponents();
	CCLOG("Deconstructor 3 Cay Chuong --- Jump Here !");
}

void BaCayChuong::createBackgrounds(){
	BackgroundInGame *bg = BackgroundInGame::create();
	this->addChild(bg);
	int id = atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str());
	boost::shared_ptr<string> param = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string paramString = param->c_str();
	vector<string> arrInfo = mUtils::splitString(paramString, '@');
	string money = arrInfo.at(0);

	mUtils mu;
	//string name = mu.getGameNameByID(id);
	string name = "Ba Cây Chương";
	string moneyConvert = mu.convertMoneyEx(atoi(money.c_str()));

	string result = "";
	if (name.length() > 0 && moneyConvert.length() > 0)
	{
		result = name + " - cược:" + moneyConvert;
	}
	CCLabelTTF *nameGame= CCLabelTTF::create(result.c_str(), "", 16);
	nameGame->setPosition(ccp(400-5, 213+10));
	nameGame->setColor(ccWHITE);
	nameGame->setOpacity(150);
	bg->addChild(nameGame);
}

void BaCayChuong::createCards(){
	layerCard = CardBaCay::create();
	layerCard->setCallbackFunc(this,callfuncN_selector(BaCayChuong::callBackFuntion_Endgive));
	this->addChild(layerCard);
}

void BaCayChuong::createAvatars(){
	layerAvatars = LayerBaCayAvatar::create();
	layerAvatars->resetAll();
	layerAvatars->getUserByPos(kUserBot)->setVisible(false);
	this->addChild(layerAvatars);
}

void BaCayChuong::createLayerBet()
{
	layerBet = BetGame3Cay::create();
	this->addChild(layerBet);
}

void BaCayChuong::createButtons(){
	layerButtons = LayerButtonInGame::create();
	this->addChild(layerButtons);

	int w_Button = 129;
	int h_Button = 44;
	int _space = 15;

	Button* btn_Ready = createButtonWithTitle_Pos("Sẵn Sàng",ccp(WIDTH_DESIGN - w_Button - _space,_space));
	Button* btn_Unready	= createButtonWithTitle_Pos("Hủy SS",ccp(WIDTH_DESIGN - w_Button - _space,_space));
	Button* btn_Bet	= createButtonWithTitle_Pos("Đặt cược", ccp(WIDTH_DESIGN - w_Button * 2 - _space * 2 ,_space));
	Button* btn_TurnUpAll = createButtonWithTitle_Pos("Lật bài", ccp(WIDTH_DESIGN - w_Button * 2 - _space * 2, _space));
	Button* btn_View = createButtonWithTitle_Pos("Xem Bài", ccp(WIDTH_DESIGN - w_Button - _space, h_Button + _space * 2));
	Button* btn_Squeezing = createButtonWithTitle_Pos("Nặn Bài", ccp(WIDTH_DESIGN - w_Button - _space, _space));

	btn_Ready->addTouchEventListener(this,toucheventselector(BaCayChuong::btn_ready_click));
	btn_Unready->addTouchEventListener(this,toucheventselector(BaCayChuong::btn_Unready_click));
	btn_Bet->addTouchEventListener(this,toucheventselector(BaCayChuong::btn_DatCuoc_click));
	btn_TurnUpAll->addTouchEventListener(this,toucheventselector(BaCayChuong::btn_btn_Latat));
	btn_View->addTouchEventListener(this,toucheventselector(BaCayChuong::btn_XemBai_click));
	btn_Squeezing->addTouchEventListener(this,toucheventselector(BaCayChuong::btn_NanBai_click));

	btn_Ready->setTag(dTag_btnReady);
	btn_Unready->setTag(dTag_btnUnready);
	btn_Bet->setTag(dTag_btnBet);
	btn_TurnUpAll->setTag(dTag_btnTurnAll);
	btn_View->setTag(dTag_btnView);
	btn_Squeezing->setTag(dTag_btnSqueez);

	btn_Ready->setEnabled(false);
	btn_Unready->setEnabled(false);
	btn_Bet->setEnabled(false);
	btn_TurnUpAll->setEnabled(false);
	btn_View->setEnabled(false);
	btn_Squeezing->setEnabled(false);

	layerButtons->addWidget(btn_Ready);
	layerButtons->addWidget(btn_Unready);
	layerButtons->addWidget(btn_Bet);
	layerButtons->addWidget(btn_TurnUpAll);
	layerButtons->addWidget(btn_View);
	layerButtons->addWidget(btn_Squeezing);
}

Button* BaCayChuong::createButtonWithTitle_Pos(const char *pName, CCPoint pPoint){
	Button* button = Button::create();
	button->setTouchEnabled(true);
	button->setScale9Enabled(false);
	button->loadTextures("ready.png", "ready_selected.png", "");
	button->setTitleText(pName);
	button->setTitleColor(ccRED);
	button->setTitleFontSize(20);
	button->setTitleFontSize(button->getContentSize().height / 2);
	button->setAnchorPoint(ccp(0, 0));
	button->setPosition(pPoint);

	return button;
}

Button* BaCayChuong::getButtonByTag(int pTag){
	Button* button = (Button*) this->layerButtons->getWidgetByTag(pTag);
	return button;
}

void BaCayChuong::createLayerChat(){
	layerChat = LayerChatInGame::create();
	this->addChild(layerChat);
}

//***********Sự kiện Server**************///

void BaCayChuong::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));

	if(strcmp("hbc", cmd->c_str())==0){
		return;
	}
	CCLOG("cmd = %s",cmd->c_str());

	if(strcmp(EXT_EVENT_LIST_USER_UPDATE.c_str(), cmd->c_str())==0){
		layerCard->setMyName(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str());
		boost::shared_ptr<string> lu = param->GetUtfString("lu");
		if (lu != NULL) {
			_list_users = lu->c_str();
			eventListUser(_list_users);
		}	
	}

	else if(strcmp(EXT_EVENT_READY_NTF.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> uid = param->GetUtfString("uid");
		if(uid != NULL){
			layerAvatars->setReady(layerAvatars->getPosByName(uid->c_str()),true);
			if (strcmp(uid->c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
			{
				flagDatCuoc = true;
				getButtonByTag(dTag_btnReady)->setEnabled(false);
				getButtonByTag(dTag_btnUnready)->setEnabled(true);
			}
		}else{
		}
	}

	else if(strcmp("urntf", cmd->c_str())==0){
		boost::shared_ptr<string> uid = param->GetUtfString("uid");
		if (uid != NULL) {
			layerAvatars->setReady(layerAvatars->getPosByName(uid->c_str()),false);
			if (strcmp(uid->c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
			{
				flagDatCuoc = false;
				getButtonByTag(dTag_btnReady)->setEnabled(true);
				getButtonByTag(dTag_btnUnready)->setEnabled(false);
			}
		}else{
		}
	}

	else if(strcmp(EXT_EVENT_START.c_str(), cmd->c_str())==0){
		whenGameStart();
		if(!flagChiaBai){
			layerCard->givePocker();
		}
	}

	else if(strcmp(EXT_EVENT_ERROR_READY_NTF.c_str(),cmd->c_str()) == 0){
		boost::shared_ptr<long> errc = param->GetInt("errc");
		if (errc != NULL)
		{
			if (*errc == 30)
			{
				Chat *toast = new Chat("Đợi người chơi khác sẵn sàng", -1);
				this->addChild(toast);
			}
		}
	}

	else if(strcmp(EXT_EVENT_LISTCARD_NTF.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> uid = param->GetUtfString("uid");
		boost::shared_ptr<string> lc = param->GetUtfString("lc");
		boost::shared_ptr<bool> tua = param->GetBool("tua");

		string _uid = "";
		string _lc = "";
		bool _tua = false;

		if(uid != NULL){
			_uid = uid->c_str();
		}
		if(lc != NULL){
			_lc = lc->c_str();
		}
		if(tua != NULL){
			_tua = *tua;
		}

		if(strcmp(uid->c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			_list_cards = lc->c_str();
		}
		if(flagChiaBai){
			action_LatBai(_lc, _uid,_tua);
		}
	}

	else if(strcmp(EXT_EVENT_END.c_str(), cmd->c_str())==0){
		this->whenGameEnd();
	}

	else if(strcmp(EXT_EVENT_GAME_RESULT.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> rg = param->GetUtfString("rg");
		if(rg != NULL){
			whenResuiltGame(*rg);
		}
	}
	
	else if(strcmp("gb_ntf", cmd->c_str())==0){
		CCLOG("Dat cuoc");
		//gbv":1000,"uid":"thanhhv3
		boost::shared_ptr<long> gbv = param->GetInt("gbv");
		boost::shared_ptr<string> uid = param->GetUtfString("uid");

		string _gbv = "";
		string _uid = "";   

		if(gbv != NULL){
			_gbv = boost::to_string(*gbv);
		}
		if( uid != NULL){
			_uid = uid->c_str();
		}

        eventGameBet_NTF(_uid, _gbv);
	}
}


void BaCayChuong::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLOG("Update User Variables");
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);

	boost::shared_ptr<double> money = ptrNotifiedUser->GetVariable("amf")->GetDoubleValue();
	boost::shared_ptr<string> uid = (ptrNotifiedUser->Name());

	if(uid == NULL || money == NULL)
		return;

	int _money = (int)(*money);

	switch(layerAvatars->getPosByName(uid->c_str()))
	{
	case kUserMe:
		layerAvatars->getUserByPos(kUserMe)->setMoney(_money);
		break;
	case kUserLeft:
		layerAvatars->getUserByPos(kUserLeft)->setMoney(_money);
		break;
	case kUserRight:
		layerAvatars->getUserByPos(kUserRight)->setMoney(_money);
		break;
	case kUserTop:
		layerAvatars->getUserByPos(kUserTop)->setMoney(_money);
		break;
	default:
		break;
	}
}


void BaCayChuong::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
	//
	CCLOG("ptrNotifiedMessage: %s", ptrNotifiedMessage->c_str());
	int pos = layerAvatars->getPosByName(ptrNotifiedUser->Name()->c_str());
	if (pos == -1)
	{
		return;
	}
	layerChat->showChatByPos(pos, ptrNotifiedMessage->c_str());
}

void BaCayChuong::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

}

void BaCayChuong::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	//
	if( ptrNotifiedUser->IsItMe() ){
		//close window - tricks by HoangDD
		layerButtons->eventTouchBtnBack(NULL, TOUCH_EVENT_ENDED);
	}
}

// // //Tìm chương
string BaCayChuong::find_Chuong(string listUser){
    string chuong = ""; 
    if(_list_users != ""){
        vector<string> arrUser = mUtils::splitString(listUser, ';');
        for(int i=0;i<arrUser.size();i++){
            if(arrUser[i]=="")
                continue;
            vector<string> info = mUtils::splitString(arrUser[i], '|');
            if(info[1] == "0"){
                chuong = info[0];
                break;
            }
        }
    }
    return chuong;
}

// //******* Xử lý sự kiện nhận được ************///

void BaCayChuong::eventListUser(string listusers)
{
	layerAvatars->setListUserForBaCay(listusers);
	layerAvatars->setPosChuong(layerAvatars->getPosByName(find_Chuong(listusers)));
	layerCard->setListUser(listusers);
	if(strcmp(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(), find_Chuong(listusers).c_str()) == 0)
	{
		getButtonByTag(dTag_btnBet)->setEnabled(false);
		getButtonByTag(dTag_btnReady)->setTitleText("Chia Bài");
	}
	else
	{
		getButtonByTag(dTag_btnBet)->setEnabled(true);
		getButtonByTag(dTag_btnReady)->setTitleText("Sẵn Sàng");
	}
	action_UserRejoinGame(listusers);
	
	//Hiển thị các FrameBet của người chơi
	layerBet->setVisibleAllFrameBet();
	
	vector<string> list = mUtils::splitString(listusers,';');
	for (int i = 0; i< list.size(); i++)
	{
		vector<string> info = mUtils::splitString(list[i],'|');
		int pos = layerAvatars->getPosByName(info[0]);
		layerBet->getFrameBetByPos(pos)->setValueBet(info[2]+" $");
		layerBet->getFrameBetByPos(pos)->setVisible(true);
	}
}

void BaCayChuong::eventGameBet_NTF(string uid, string gbv)
{
	int pos = layerAvatars->getPosByName(uid);
	layerBet->getFrameBetByPos(pos)->setValueBet(gbv + " $");
}

void BaCayChuong::action_UserRejoinGame(string lsUser){
	vector<string> list = mUtils::splitString(lsUser, ';');

	if(strcmp(mUtils::splitString(list[0], '|')[3].c_str(), "1") == 0){
		flagChiaBai = true;
		getButtonByTag(dTag_btnReady)->setEnabled(false);
		getButtonByTag(dTag_btnUnready)->setEnabled(false);
		getButtonByTag(dTag_btnBet)->setEnabled(false);
	}
	else
	{
		getButtonByTag(dTag_btnReady)->setEnabled(true);
	}

	for(int i = 0; i < list.size(); i++){
		vector<string> info = mUtils::splitString(list[i], '|');
		if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			if(info[3]== "1" && layerCard->getListCards_Me()->count() == 0){
				CCLOG("Me Rejoin");
				layerCard->createCardBack(kUserMe);
			}
		}
		else{
			switch (layerAvatars->getPosByName(info[0])) {
			case kUserLeft:
				if(info[3] == "1" && layerCard->getListCards_Left()->count() == 0){
					layerCard->createCardBack(kUserLeft);	
				}
				break;

			case kUserRight:
				if(info[3] == "1" && layerCard->getListCards_Right()->count() == 0){
					layerCard->createCardBack(kUserRight);	
				}
				break;

			case kUserTop:
				if(info[3] == "1" && layerCard->getListCards_Top()->count() == 0){
					layerCard->createCardBack(kUserTop);
				}
				break;

			default:
				break;
			}
		}
	}
}

void BaCayChuong::action_LatBai(string listCard,string uid, bool tua){
	if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
		if(tua){
			if(this->getChildByTag(123) !=NULL){
				this->removeChildByTag(123);
			}
			layerCard->turnUpAllCards(listCard, kUserMe);
			getButtonByTag(dTag_btnSqueez)->setEnabled(false);
			getButtonByTag(dTag_btnView)->setEnabled(false);
			getButtonByTag(dTag_btnTurnAll)->setEnabled(false);
		}
		else{
			layerCard->turnUpAllCards("0_0-0_0-0_0", kUserMe);
			getButtonByTag(dTag_btnSqueez)->setEnabled(true);
			getButtonByTag(dTag_btnView)->setEnabled(true);
			getButtonByTag(dTag_btnTurnAll)->setEnabled(true);
		}
	}
	else
	{
		layerCard->turnUpAllCards(listCard, layerAvatars->getPosByName(uid));
	}
}


void BaCayChuong::whenGameStart(){
	getButtonByTag(dTag_btnReady)->setEnabled(false);
	getButtonByTag(dTag_btnUnready)->setEnabled(false);
	getButtonByTag(dTag_btnBet)->setEnabled(false);
	layerAvatars->setUnReadyAllUser();
}

void BaCayChuong::whenResuiltGame(string rg){
	//thanhhv3|3|3|2|1000;dautv3|2|1|1|-1000
	if (this->getChildByTag(123) != NULL)
	{
		this->removeChildByTag(123);
	}

	LayerNumberInGame *layerNumbers = LayerNumberInGame::create();
	this->addChild(layerNumbers);

	vector<string> resuilt = mUtils::splitString(rg, ';');
	for(int i = 0; i < resuilt.size(); i++){
		vector<string> info = mUtils::splitString(resuilt[i], '|');

		if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
			layerChat->showChatByPos(kUserMe,(info[1] +" Điểm"));
			layerNumbers->showNumberByPos(kUserMe, info[4]);
		}
		else
		{
			int pos = layerAvatars->getPosByName(info[0]);
			switch (pos) {
			case kUserLeft:
				layerChat->showChatByPos(kUserLeft,(info[1] +" Điểm"));
				layerNumbers->showNumberByPos(kUserLeft, info[4]);
				break;
			case kUserRight:
				layerChat->showChatByPos(kUserRight,(info[1] +" Điểm"));
				layerNumbers->showNumberByPos(kUserRight, info[4]);
				break;
			case kUserTop:
				layerChat->showChatByPos(kUserTop,(info[1] +" Điểm"));
				layerNumbers->showNumberByPos(kUserTop, info[4]);
				break;
			default:
				break;
			}
		}
	}
}

void BaCayChuong::whenGameEnd(){

	layerCard->resetGame();

	getButtonByTag(dTag_btnReady)->setEnabled(true);
	flagDatCuoc = false;
	flagChiaBai = false;
	_list_cards = "";
}

void BaCayChuong::btn_ready_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		CCLOG("btnReady");
		boost::shared_ptr<ISFSObject> parameter (new SFSObject());
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_READY_REQ, parameter, lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void BaCayChuong::btn_Unready_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_UNREADY_REQ, params, lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void BaCayChuong::btn_DatCuoc_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		if(!flagDatCuoc){
			cocos2d::extension::CCBReader * ccbReader = NULL;
			CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
			V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);

			// register loaders
			ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
			ccNodeLoaderLibrary->registerCCNodeLoader("LayerBet_BaCayChuong",   LayerBet_BaCayChuongLoader::loader());
			// read main layer
			ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

			LayerBet_BaCayChuong *popUp;

			if (ccbReader)
			{
				popUp = (LayerBet_BaCayChuong *)ccbReader->readNodeGraphFromFile( "LayerBet_BaCayChuong.ccbi" );
				popUp->setPosition(ccp(10,10));
				this->addChild(popUp);
				ccbReader->release();
			}
		}else{
			Chat *toast = new Chat("Bạn đã sẵn sàng, không thể đặt cược", -1);
			this->addChild(toast);
		}
	}
}

void BaCayChuong::btn_btn_Latat(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_TURNUP_CARD,params,lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void BaCayChuong::btn_XemBai_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		if(_list_cards != ""){
			layerCard->turnUpAllCards(_list_cards, kUserMe);
			getButtonByTag(dTag_btnSqueez)->setEnabled(false);
			getButtonByTag(dTag_btnView)->setEnabled(false);
		}
	}
}

void BaCayChuong::btn_NanBai_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		Nan3Cay *BaCay = Nan3Cay::create();
		BaCay->setCallbackFunc(this,callfuncN_selector(BaCayChuong::callBackFunction_LatBai));
		BaCay->initListCardHand(_list_cards);
		BaCay->setTag(123);
		this->addChild(BaCay);
	}
}
// 
void BaCayChuong::callBackFunction_LatBai(CCNode *pSend){
	if(_list_cards != ""){
		layerCard->turnUpAllCards(_list_cards, kUserMe);
		getButtonByTag(dTag_btnSqueez)->setEnabled(false);
		getButtonByTag(dTag_btnView)->setEnabled(false);
	}
}

void BaCayChuong::callBackFuntion_Endgive(CCNode *pSend)
{
	CCLOG("Nhay vao call back");
	flagChiaBai = true;
	getButtonByTag(dTag_btnSqueez)->setEnabled(true);
	getButtonByTag(dTag_btnView)->setEnabled(true);
	getButtonByTag(dTag_btnTurnAll)->setEnabled(true);
}
