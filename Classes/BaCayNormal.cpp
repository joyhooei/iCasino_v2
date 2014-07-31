//
//  BaCayNormal.cpp
//  iCasino_v2
//
//  Created by DauA on 5/20/14.
//
//

#include "BaCayNormal.h"
#include "_Background_inGame_.h"
#include "Requests/ExtensionRequest.h"
#include "_Number_inGame_7u.h"
#include "Nan3Cay.h"
#include "mUtils.h"
#include "_Chat_.h"
#include "SceneManager.h"
#include "AllData.h"

BaCayNormal::BaCayNormal(){

  
    
	EXT_EVENT_LIST_USER_UPDATE = "luu";
	EXT_EVENT_READY_NTF = "rntf";
	EXT_EVENT_START = "s";
	EXT_EVENT_LISTCARD_NTF = "lcntf";
	EXT_EVENT_END = "e";
	EXT_EVENT_GAME_RESULT = "grs";
	EXT_EVENT_UNREADY_NTF = "urntf";
	EXT_EVENT_UNREADY_REQ = "urr";
	EXT_EVENT_READY_REQ = "rr";
	EXT_EVENT_TURNUP_CARD = "tuc";

	flagChiaBai = false;

	_list_cards = "";
	_list_user = "";

	createBackgrounds();
	createAvatars();
	createButtons();
	createCards();
    
    LayerNumberInGame7u *abc = LayerNumberInGame7u::create();
    this->addChild(abc);
    abc->showNumberByPos(kuser1,7000);
    
	layerBet = BetGame3Cay::create();
	this->addChild(layerBet);

	layerChat = LayerChatInGame::create();
	this->addChild(layerChat);

	GameServer::getSingleton().addListeners(this);
	SceneManager::getSingleton().hideLoading();
}

BaCayNormal::~BaCayNormal(){
	GameServer::getSingleton().removeListeners(this);
	this->removeAllComponents();
	CCLOG("Deconstructor 3 Cay Normal --- Jump Here !");
}

void BaCayNormal::onExit()
{
	GameServer::getSingleton().removeListeners(this);
	this->removeAllComponents();
	CCLOG("Deconstructor 3 Cay Normal --- Jump Here !");
}


void BaCayNormal::createBackgrounds(){
	BackgroundInGame *bg = BackgroundInGame::create();
	this->addChild(bg);
	int id = atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str());
	boost::shared_ptr<string> param = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string paramString = param->c_str();
	vector<string> arrInfo = mUtils::splitString(paramString, '@');
	string money = arrInfo.at(0);

	mUtils mu;
	//string name = mu.getGameNameByID(id);
	string name = "Ba Cây Thường";
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

void BaCayNormal::createAvatars(){
	layerAvatars = LayerBaCayAvatar::create();
	layerAvatars->resetAll();
	layerAvatars->getUserByPos(kuser0)->setVisible(true);
	this->addChild(layerAvatars);
}

void BaCayNormal::createButtons(){
	layerbutton = LayerButtonInGame::create();
	this->addChild(layerbutton);

	int w_Button = 129;
	int h_Button = 44;
	int _space = 15;

	Button* btn_Ready = createButtonWithTitle_Pos("Sẵn Sàng",ccp(WIDTH_DESIGN - w_Button - _space,_space));
	Button* btn_Unready	= createButtonWithTitle_Pos("Hủy SS",ccp(WIDTH_DESIGN - w_Button - _space,_space));
	Button* btn_TurnUpAll = createButtonWithTitle_Pos("Lật bài", ccp(WIDTH_DESIGN - w_Button * 2 - _space * 2, _space));
	Button* btn_View = createButtonWithTitle_Pos("Xem Bài", ccp(WIDTH_DESIGN - w_Button - _space, h_Button + _space * 2));
	Button* btn_Squeezing = createButtonWithTitle_Pos("Nặn Bài", ccp(WIDTH_DESIGN - w_Button - _space, _space));

	btn_Ready->addTouchEventListener(this,toucheventselector(BaCayNormal::btn_ready_click));
	btn_Unready->addTouchEventListener(this,toucheventselector(BaCayNormal::btn_Unready_click));
	btn_TurnUpAll->addTouchEventListener(this,toucheventselector(BaCayNormal::btn_btn_Latat));
	btn_View->addTouchEventListener(this,toucheventselector(BaCayNormal::btn_XemBai_click));
	btn_Squeezing->addTouchEventListener(this,toucheventselector(BaCayNormal::btn_NanBai_click));

	btn_Ready->setTag(dTag_btnReady);
	btn_Unready->setTag(dTag_btnUnready);
	btn_TurnUpAll->setTag(dTag_btnTurnAll);
	btn_View->setTag(dTag_btnView);
	btn_Squeezing->setTag(dTag_btnSqueez);

	btn_Ready->setEnabled(false);
	btn_Unready->setEnabled(false);
	btn_TurnUpAll->setEnabled(false);
	btn_View->setEnabled(false);
	btn_Squeezing->setEnabled(false);

	layerbutton->addWidget(btn_Ready);
	layerbutton->addWidget(btn_Unready);
	layerbutton->addWidget(btn_TurnUpAll);
	layerbutton->addWidget(btn_View);
	layerbutton->addWidget(btn_Squeezing);
}

void BaCayNormal::createCards()
{
	layerCards = CardBaCay::create();
	layerCards->setCallbackFunc(this,callfuncN_selector(BaCayNormal::callBackFuntion_Endgive));
	this->addChild(layerCards);
}

Button* BaCayNormal::createButtonWithTitle_Pos(const char *pName, CCPoint pPoint){
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

Button* BaCayNormal::getButtonByTag(int pTag)
{
	if (this->layerbutton->getWidgetByTag(pTag) == NULL)
	{
		return NULL;
	}
	Button* button = (Button*) this->layerbutton->getWidgetByTag(pTag);
	return button;
}

void BaCayNormal::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

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
		boost::shared_ptr<string> lu = param->GetUtfString("lu");
		if (lu != NULL) {
			CCLOG("List user: %s",lu->c_str());
			_list_user = *lu;
			eventListUserUpdate(_list_user);
		}
	}

	else if(strcmp(EXT_EVENT_READY_NTF.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> uid = param->GetUtfString("uid");
		if(uid != NULL){
			whenUserReady(*uid);
		}
	}

	else if (strcmp("e_rntf",cmd->c_str()) == 0)
	{
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

	else if(strcmp(EXT_EVENT_UNREADY_NTF.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> uid = param->GetUtfString("uid");
		if(uid != NULL){
			whenUserUnready(*uid);
		}
	}

	else if(strcmp(EXT_EVENT_START.c_str(), cmd->c_str())==0){
		whenGameStart();
	}
	//Event List cards
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
			_list_cards = _lc;
		}
		if(flagChiaBai){
			CCLOG("Lat bai");
			LatBai(_lc, _uid, _tua);
		}
	}

	else if(strcmp(EXT_EVENT_END.c_str(), cmd->c_str())==0){
		this->whenGameEnd();
	}

	else if(strcmp(EXT_EVENT_GAME_RESULT.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> rg = param->GetUtfString("rg");
        CCLog("rg---%s",rg->c_str());
		if(rg != NULL){
			whenResuiltGame(*rg);
		}
	}
}

void BaCayNormal::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	//     CCLOG("Update User Variables");
	//     boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	//     boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	//     boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	//     
	//     boost::shared_ptr<double> money = ptrNotifiedUser->GetVariable("amf")->GetDoubleValue();
	//     boost::shared_ptr<string> uid = (ptrNotifiedUser->Name());
	//     
	//     if(uid == NULL || money == NULL)
	//         return;
	//     
	//     int _money = (int)(*money);
	//     string _uid = uid->c_str();
	//     
	//     switch (getPosUserByName(_uid, _list_user)) {
	//         case kUserMe:
	// 			layerAvatars->getUserByPos(kUserMe)->setMoney(_money);
	//             break;
	// 		case kUserLeft:
	// 			layerAvatars->getUserByPos(kUserLeft)->setMoney(_money);
	//             break;
	// 		case kUserRight:
	// 			layerAvatars->getUserByPos(kUserRight)->setMoney(_money);
	//             break;
	// 		case kUserTop:
	// 			layerAvatars->getUserByPos(kUserTop)->setMoney(_money);
	//             break;
	//         default:
	//             break;
	//     }
}

void BaCayNormal::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
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

void BaCayNormal::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

}

void BaCayNormal::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLOG("User ExitRoom On Room");
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	//
	if( ptrNotifiedUser->IsItMe() ){
		//close window - tricks by HoangDD
		layerbutton->eventTouchBtnBack(NULL, TOUCH_EVENT_ENDED);
	}
}

// Button Sẵn Sàng Click
void BaCayNormal::btn_ready_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> parameter (new SFSObject());
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_READY_REQ, parameter, lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

// Button Hủy Sẵn Sàng
void BaCayNormal::btn_Unready_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_UNREADY_REQ, params, lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

// Button Lật Bài click
void BaCayNormal::btn_btn_Latat(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_TURNUP_CARD, params, lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

//Button Xem Bài
void BaCayNormal::btn_XemBai_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		if(this->getChildByTag(123) !=NULL){
			this->removeChildByTag(123);
		}
		if(_list_cards!=""){
			layerCards->turnUpAllCards(_list_cards, kuser0);
			getButtonByTag(dTag_btnSqueez)->setEnabled(false);
			getButtonByTag(dTag_btnView)->setEnabled(false);
		}
	}
}

//Button Nặn Bài
void BaCayNormal::btn_NanBai_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		Nan3Cay *BaCay = Nan3Cay::create();
		BaCay->setCallbackFunc(this,callfuncN_selector(BaCayNormal::callBackFunction_LatBai));
		BaCay->initListCardHand(_list_cards);
		BaCay->setTag(123);
		this->addChild(BaCay);
	}
}

void BaCayNormal::callBackFunction_LatBai(CCNode *pSend){
	if(_list_cards != ""){
		layerCards->turnUpAllCards(_list_cards, kuser0);
		getButtonByTag(dTag_btnSqueez)->setEnabled(false);
		getButtonByTag(dTag_btnView)->setEnabled(false);
	}
}

void BaCayNormal::eventListUserUpdate(string listusers)
{
	
	layerAvatars->setListUserForBaCay(listusers);
	layerCards->setMyName(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str());
	layerCards->setListUser(listusers);

	vector<string> arrUser = mUtils::splitString(listusers,';');
	vector<string> first = mUtils::splitString(arrUser[0],'|');

	if(strcmp(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(), first[0].c_str()) == 0)
	{
		getButtonByTag(dTag_btnReady)->setTitleText("Chia Bài");
	}
	else
	{
		getButtonByTag(dTag_btnReady)->setTitleText("Sẵn Sàng");
	}

	whenUserRejoinOrGuess(listusers);
}

void BaCayNormal::whenUserRejoinOrGuess(string listUser){

	vector<string> list = mUtils::splitString(listUser, ';');

	if(strcmp(mUtils::splitString(list[0], '|')[1].c_str(), "1") == 0){
		flagChiaBai = true;
		getButtonByTag(dTag_btnReady)->setEnabled(false);
		getButtonByTag(dTag_btnUnready)->setEnabled(false);
	}
	else
	{
		getButtonByTag(dTag_btnReady)->setEnabled(true);
		getButtonByTag(dTag_btnUnready)->setEnabled(false);
	}

	for(int i=0;i<list.size();i++){
		vector<string> info = mUtils::splitString(list[i], '|');
		if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			if(info[1]== "1" && layerCards->getListCards_0()->count() == 0){
				CCLOG("Me Rejoin");
				layerCards->createCardBack(kuser0);
			}
		}

		else{
			switch (layerAvatars->getPosByName(info[0])) {
			case kuser1:
				if (info[1] == "1" && layerCards->getListCards_1()->count() == 0)
				{
					layerCards->createCardBack(kuser1);
				}
				break;
                case kuser2:
                    if (info[1] == "1" && layerCards->getListCards_2()->count() == 0)
                    {
                        layerCards->createCardBack(kuser2);
                    }
                    break;

                case kuser3:
                    if (info[1] == "1" && layerCards->getListCards_3()->count() == 0)
                    {
                        layerCards->createCardBack(kuser3);
                    }
                    break;

                case kuser4:
                    if (info[1] == "1" && layerCards->getListCards_4()->count() == 0)
                    {
                        layerCards->createCardBack(kuser4);
                    }
                    break;

                case kuser5:
                    if (info[1] == "1" && layerCards->getListCards_5()->count() == 0)
                    {
                        layerCards->createCardBack(kuser5);
                    }
                    break;

                case kuser6:
                    if (info[1] == "1" && layerCards->getListCards_6()->count() == 0)
                    {
                        layerCards->createCardBack(kuser6);
                    }
                    break;

				break;
			default:
				break;
			}
		}
	}
}

void BaCayNormal::whenUserReady(string uid)
{
	layerAvatars->setReady(layerAvatars->getPosByName(uid), true);
	if (strcmp(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(), uid.c_str()) == 0)
	{
		getButtonByTag(dTag_btnReady)->setEnabled(false);
		getButtonByTag(dTag_btnUnready)->setEnabled(true);
	}
}

void BaCayNormal::whenUserUnready(string uid){
	layerAvatars->setReady(layerAvatars->getPosByName(uid), false);
	if (strcmp(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(), uid.c_str()) == 0)
	{
		getButtonByTag(dTag_btnUnready)->setEnabled(false);
		getButtonByTag(dTag_btnReady)->setEnabled(true);
	}
}

void BaCayNormal::whenGameStart(){
	layerAvatars->setUnReadyAllUser();
	getButtonByTag(dTag_btnReady)->setEnabled(false);
	getButtonByTag(dTag_btnUnready)->setEnabled(false);

	if(!flagChiaBai){
		layerCards->givePocker();
	}
}

void BaCayNormal::whenResuiltGame(string rg){
	//dautv3|4|8|3|1000;dautv|1|1|2|-1000

	if (this->getChildByTag(123) != NULL)
	{
		this->removeChildByTag(123);
	}

	LayerNumberInGame7u *layerNumbers = LayerNumberInGame7u::create();
	this->addChild(layerNumbers);

	vector<string> resuilt = mUtils::splitString(rg, ';');

	for(int i = 0; i < resuilt.size(); i++){
		vector<string> info = mUtils::splitString(resuilt[i], '|');
        double mon = atof(info[4].c_str());
		string strResuilt = info[1] + "|" + info[2] + "|" + info[3];
		if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			//layerBet->setResuit4AllUser(kUserMe, "1", strResuilt);
			layerNumbers->showNumberByPos(kuser0,mon);
            
		}
		else{
			int pos = layerAvatars->getPosByName(info[0]);

			switch (pos) {
			case kuser1:
				//layerBet->setResuit4AllUser(kuser1, "1", strResuilt);
				layerNumbers->showNumberByPos(kuser1, mon);
				break;
                    
                case kuser2:
                    layerBet->setResuit4AllUser(kuser2, "1", strResuilt);
                    layerNumbers->showNumberByPos(kuser2, mon);
                    break;
                    
                case kuser3:
                    layerBet->setResuit4AllUser(kuser3, "1", strResuilt);
                    layerNumbers->showNumberByPos(kuser3, mon);
                    break;
                    
                case kuser4:
                    layerBet->setResuit4AllUser(kuser4, "1", strResuilt);
                    layerNumbers->showNumberByPos(kuser4,mon);
                    break;
                    
                case kuser5:
                    layerBet->setResuit4AllUser(kuser5, "1", strResuilt);
                    layerNumbers->showNumberByPos(kuser5,mon);
                    break;
                    
                case kuser6:
                    layerBet->setResuit4AllUser(kuser6, "1", strResuilt);
                    layerNumbers->showNumberByPos(kuser6, mon);
                    break;

			default:
				break;
			}
		}
	}
}

void BaCayNormal::whenGameEnd(){
	layerCards->resetGame();
	layerBet->getLayerResuilt()->removeAllChildrenWithCleanup(true);

	getButtonByTag(dTag_btnReady)->setEnabled(true);

	flagChiaBai = false;
	_list_cards = "";
}

void BaCayNormal::LatBai(string listCard,string uid, bool tua){
	if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
		if(tua){
			if (this->getChildByTag(123) != NULL)
			{
				this->removeChildByTag(123);
			}
			layerCards->turnUpAllCards(listCard, kuser0);
			getButtonByTag(dTag_btnSqueez)->setEnabled(false);
			getButtonByTag(dTag_btnView)->setEnabled(false);
			getButtonByTag(dTag_btnTurnAll)->setEnabled(false);
		}
		else{
			layerCards->turnUpAllCards("0_0-0_0-0_0", kuser0);
			getButtonByTag(dTag_btnSqueez)->setEnabled(true);
			getButtonByTag(dTag_btnView)->setEnabled(true);
			getButtonByTag(dTag_btnTurnAll)->setEnabled(true);
		}
	}
	else
	{
		layerCards->turnUpAllCards(listCard, layerAvatars->getPosByName(uid));
	}
}

void BaCayNormal::callBackFuntion_Endgive(CCNode *pSend)
{
	flagChiaBai =  true;
	getButtonByTag(dTag_btnSqueez)->setEnabled(true);
	getButtonByTag(dTag_btnView)->setEnabled(true);
	getButtonByTag(dTag_btnTurnAll)->setEnabled(true);
}