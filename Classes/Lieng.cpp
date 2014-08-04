//
//  Lieng.cpp
//  iCasinov2
//
//  Created by DauA on 5/27/14.
//
//

#include "Lieng.h"
#include "_Background_inGame_.h"
#include "_Number_Chat_inGame7u.h"
#include "Requests/ExtensionRequest.h"
#include "Nan3Cay.h"
#include "LayerBet_Lieng.h"
#include "SliderCustomLoader.h"
#include "mUtils.h"
#include "_Chat_.h"
#include "SceneManager.h"
#include "AllData.h"

#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())


Lieng::Lieng()
{
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
	real = false;
	flag_Complete_Click = false;

	currentTo = "";
	currentBetal = "";

	string Bet = *GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string strBet = mUtils::splitString(Bet, '@')[0];
	minBet = atoi(strBet.c_str());
	my_To = 0;

	createBackgrounds();
	createAvatars();
	createButtons();
	createLayerBet();
	createCards();

	layerChat = Number_Chat_inGame7u::create();
	this->addChild(layerChat);

	GameServer::getSingleton().addListeners(this);
	SceneManager::getSingleton().hideLoading();
}

Lieng::~Lieng(){
	GameServer::getSingleton().removeListeners(this);
	this->removeAllComponents();
	CCLOG("Deconstructor Lieng ------ JumpHere");
}

void Lieng::onExit()
{
	GameServer::getSingleton().removeListeners(this);
	this->removeAllComponents();
	CCLOG("Deconstructor Lieng ------ JumpHere");
}

void Lieng::createBackgrounds(){
	BackgroundInGame *bg = BackgroundInGame::create();
	this->addChild(bg);
	int id = atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str());
	boost::shared_ptr<string> param = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string paramString = param->c_str();
	vector<string> arrInfo = mUtils::splitString(paramString, '@');
	string money = arrInfo.at(0);

	mUtils mu;
	//string name = mu.getGameNameByID(id);
	string name = "Liêng";
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

void Lieng::createLayerBet()
{
	layerBet = BetGame3Cay::create();
	this->addChild(layerBet);
}

void Lieng::createCards()
{
	layerCards = CardBaCay::create();
	layerCards->setCallbackFunc(this,callfuncN_selector(Lieng::callBackFuntion_Endgive));
	this->addChild(layerCards);
}

void Lieng::createAvatars(){
	layerAvatars = LayerBaCayAvatar::create();
	//layerAvatars->getUserByPos(kUserBot)->setVisible(false);
	layerAvatars->resetAll();
	this->addChild(layerAvatars);
}

void Lieng::createButtons(){
	layerButtons = LayerButtonInGame::create();
	this->addChild(layerButtons);

	int w_Button = 129;
	int h_Button = 44;

	Button* btn_Ready = createButtonWithTitle_Pos("Sẵn Sàng",ccp(WIDTH_DESIGN - w_Button -10, 10));
    btn_Ready->setScale(0.7);
	Button* btn_Unready	= createButtonWithTitle_Pos("Hủy SS",ccp(WIDTH_DESIGN - w_Button - 10, 10));
    btn_Unready->setScale(0.7);
	Button* btn_Complete = createButtonWithTitle_Pos("Xong",ccp(WIDTH_DESIGN - w_Button - 10, 10));
    btn_Complete->setScale(0.7);

	Button* btn_View = createButtonWithTitle_Pos("Xem Bài", ccp(WIDTH_DESIGN - w_Button - 10, 15));
    btn_View->setScale(0.7);
	Button* btn_Squeezing = createButtonWithTitle_Pos("Nặn Bài", ccp(WIDTH_DESIGN - w_Button - 10, h_Button + 20));
    btn_Squeezing->setScale(0.7);

	Button* btn_Fold = createButtonWithTitle_Pos("Úp Bài", ccp(WIDTH_DESIGN - w_Button - 200, 15));
    btn_Fold->setScale(0.7);
	Button* btn_Bet	= createButtonWithTitle_Pos("Tố", ccp(WIDTH_DESIGN - w_Button - 105, 15));
    btn_Bet->setScale(0.7);
	Button* btn_Follow = createButtonWithTitle_Pos("Theo", ccp(WIDTH_DESIGN - w_Button - 105, h_Button + 20));
    btn_Follow->setScale(0.7);

	btn_Ready->addTouchEventListener(this, toucheventselector(Lieng::btn_ready_click));
	btn_Unready->addTouchEventListener(this, toucheventselector(Lieng::btn_Unready_click));
	btn_Complete->addTouchEventListener(this, toucheventselector(Lieng::btn_Complete_click));

	btn_View->addTouchEventListener(this, toucheventselector(Lieng::btn_XemBai_click));
	btn_Squeezing->addTouchEventListener(this, toucheventselector(Lieng::btn_NanBai_click));

	btn_Fold->addTouchEventListener(this, toucheventselector(Lieng::btn_Up_click));
	btn_Bet->addTouchEventListener(this, toucheventselector(Lieng::btn_To_click));
	btn_Follow->addTouchEventListener(this, toucheventselector(Lieng::btn_Theo_click));

	btn_Ready->setTag(dTag_btnReady);
	btn_Unready->setTag(dTag_btnUnready);
	btn_View->setTag(dTag_btnView);
	btn_Squeezing->setTag(dTag_btnSqueez);
	btn_Fold->setTag(dTag_btnFold);
	btn_Bet->setTag(dTag_btnBet);
	btn_Follow->setTag(dTag_btnFollow);
	btn_Complete->setTag(dTag_Complete);

	btn_Ready->setEnabled(false);
	btn_Unready->setEnabled(false);
	btn_View->setEnabled(false);
	btn_Squeezing->setEnabled(false);
	btn_Fold->setEnabled(false);
	btn_Bet->setEnabled(false);
	btn_Follow->setEnabled(false);
	btn_Complete->setEnabled(false);

	layerButtons->addWidget(btn_Ready);
	layerButtons->addWidget(btn_Unready);
	layerButtons->addWidget(btn_View);
	layerButtons->addWidget(btn_Squeezing);
	layerButtons->addWidget(btn_Fold);
	layerButtons->addWidget(btn_Follow);
	layerButtons->addWidget(btn_Bet);
	layerButtons->addWidget(btn_Complete);
}

Button* Lieng::createButtonWithTitle_Pos(const char *pName, CCPoint pPoint)
{
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

Button* Lieng::getButtonByTag(int pTag)
{
	Button* button = (Button*) this->layerButtons->getWidgetByTag(pTag);
	return button;
}


void Lieng::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if(strcmp("hbc", cmd->c_str())==0){
		return;
	}
	CCLOG("cmd = %s",cmd->c_str());

	if(strcmp(EXT_EVENT_LIST_USER_UPDATE.c_str(), cmd->c_str()) == 0){
		layerCards->setMyName(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str());
		boost::shared_ptr<string> lu = param->GetUtfString("lu");
		CCLOG("List user: %s", lu->c_str());
		if (lu != NULL)
		{
			_list_user = lu->c_str();
			action_UpdateListUser(_list_user);
		}
	}

	else if(strcmp(EXT_EVENT_READY_NTF.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> uid = param->GetUtfString("uid");
		string _uid = "";
		if (uid != NULL)
		{
			_uid = uid->c_str();
		}
		whenUserReady(_uid);
	}

	else if(strcmp("urntf", cmd->c_str())==0){
		boost::shared_ptr<string> uid = param->GetUtfString("uid");
		string _uid = "";
		if (uid != NULL)
		{
			_uid = uid->c_str();
		}
		whenUserUnready(_uid);
	}

	else if (strcmp(EXT_EVENT_ERROR_READY_NTF.c_str(),cmd->c_str()) == 0)
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
	// 
	else if(strcmp("nt", cmd->c_str()) == 0){
		boost::shared_ptr<string> uid = param->GetUtfString("uid");
		boost::shared_ptr<long> mb = param->GetInt("mb");
		boost::shared_ptr<string> betal = param->GetUtfString("betal");

		if (uid != NULL)
		{
			currentTo = uid->c_str();
		}
		if (betal != NULL)
		{
			currentBetal = betal->c_str();
		}
		if (mb != NULL)
		{
			minBet = (int)*mb;
		}

		if(!real){
			layerCards->givePocker();
		}
		else{
			action_To(currentTo, currentBetal);
		}
		real = true;
	}

	// Game Start
	else if(strcmp(EXT_EVENT_START.c_str(), cmd->c_str())==0){
		whenGameStart();
	}

	// List Card NTF
	else if(strcmp(EXT_EVENT_LISTCARD_NTF.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> uid = param->GetUtfString("uid");
		boost::shared_ptr<string> lc = param->GetUtfString("lc");
		boost::shared_ptr<bool> tua = param->GetBool("tua");

		string _uid = "";
		string _lc = "";
		bool _tua = false;

		if (uid != NULL)
		{
			_uid = uid->c_str();
		}
		if (lc != NULL)
		{
			_lc = lc->c_str();
		}
		if (tua != NULL)
		{
			_tua = *tua;
		}

		//_list_cards
		if(strcmp(_uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			_list_cards = _lc;
		}

		if(flagChiaBai){
			action_LatBai(_lc, _uid, _tua);
		}

		CCLOG("EXT_EVENT_LISTCARD_NTF");
	}
	//     
	// Game End
	else if(strcmp(EXT_EVENT_END.c_str(), cmd->c_str())==0){
		whenGameEnd();
		CCLOG("EXT_EVENT_END");
	}

	// Game Resuilt
	else if(strcmp(EXT_EVENT_GAME_RESULT.c_str(), cmd->c_str())==0){
		//"rg":"dautv5|1|8|3|2|1000;dautv3|1|8|7|3|1000"
		boost::shared_ptr<string> rg = param->GetUtfString("rg");
		string _resuilt = "";
		if (rg != NULL)
		{
			_resuilt = rg->c_str();
		}
		whenResuiltGame(_resuilt);
		CCLOG("EXT_EVENT_GAME_RESULT");
	}

	//Game Bet NTF
	else if(strcmp("gb_ntf", cmd->c_str())==0){
		boost::shared_ptr<long> gbv = param->GetInt("gbv");
		boost::shared_ptr<string> uid = param->GetUtfString("uid");

		long _gbv = 0;
		string _uid = "";
		if (gbv != NULL)
		{
			_gbv = *gbv;
		}
		if (uid != NULL)
		{
			_uid = uid->c_str();
		}
		if (strcmp(_uid.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0
			&& gbv != NULL)
		{
			my_To = (int)_gbv;
		}

		whenUserBet(_uid, _gbv);
		CCLOG("uid %s, gameBet %ld",_uid.c_str(),_gbv);
	}

}

void Lieng::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLOG("Update User Variables");
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);

	// 	boost::shared_ptr<double> money = ptrNotifiedUser->GetVariable("amf")->GetDoubleValue();
	// 	boost::shared_ptr<string> uid = (ptrNotifiedUser->Name());
	// 
	// 	if(uid == NULL || money == NULL)
	// 		return;
	// 
	// 	int _money = (int)(*money);
	// 	string _uid = uid->c_str();
	// 
	// 	switch (getPosUserByName(_uid, _list_user)) {
	// 	case kUserMe:
	// 		layerAvatars->getUserByPos(kUserMe)->setMoney(_money);
	// 		break;
	// 	case kUserLeft:
	// 		layerAvatars->getUserByPos(kUserLeft)->setMoney(_money);
	// 		break;
	// 	case kUserRight:
	// 		layerAvatars->getUserByPos(kUserRight)->setMoney(_money);
	// 		break;
	// 	case kUserTop:
	// 		layerAvatars->getUserByPos(kUserTop)->setMoney(_money);
	// 		break;
	// 	default:
	// 		break;
	// 	}
}

void Lieng::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
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

void Lieng::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

}

void Lieng::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLOG("User ExitRoom On Room");
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	//
	if( ptrNotifiedUser->IsItMe() ){ 
		//close window - tricks by HoangDD
		layerButtons->eventTouchBtnBack(NULL, TOUCH_EVENT_ENDED);
	}
}

void Lieng::action_UpdateListUser(string lsUser)
{
	layerAvatars->setListUserForBaCay(lsUser);
	layerCards->setListUser(lsUser);
	if (checkPlaying(lsUser))
	{
		real = true;
		flagChiaBai = true;
		getButtonByTag(dTag_btnReady)->setEnabled(false);
	}
	else{
		getButtonByTag(dTag_btnReady)->setEnabled(true);
	}

	action_UserRejoinGame(lsUser);

	layerBet->setVisibleAllFrameBet();

	vector<string> list = mUtils::splitString(_list_user,';');
	for (int i = 0; i < list.size(); i++)
	{
		vector<string> info = mUtils::splitString(list[i],'|');
		int pos = layerAvatars->getPosByName(info[0]);
		string _minbet = mUtils::convertMoneyEx(minBet);
		layerBet->getFrameBetByPos(pos)->setValueBet(_minbet + " $");
		layerBet->getFrameBetByPos(pos)->setVisible(true);
	}
}

void Lieng::action_UserRejoinGame(string lsUser){

	if (checkPlaying(lsUser) && layerCards->getListCards_0()->count() == 0)
	{
		moveButtonRight();
	}

	vector<string> list = mUtils::splitString(lsUser,';');
	for (int i = 0; i < list.size(); i++)
	{
		vector<string> info = mUtils::splitString(list[i],'|');
		if (strcmp(info[0].c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
		{
			if (checkPlaying(lsUser))
			{
				getButtonByTag(dTag_btnReady)->setEnabled(false);
			}

			if (layerCards->getListCards_0()->count() != 3 && info[2] != "0")
			{
				layerCards->createCardBack(kuser0);
			}
		}
		else
		{
			switch(layerAvatars->getPosByName(info[0]))
			{
			case kuser1:
				if (layerCards->getListCards_1()->count() != 3 && info[2] != "0")
				{
					layerCards->createCardBack(kuser1);
				}
            case kuser2:
                if (layerCards->getListCards_1()->count() != 3 && info[2] != "0")
                {
                    layerCards->createCardBack(kuser2);
                }
                case kuser3:
                    if (layerCards->getListCards_1()->count() != 3 && info[2] != "0")
                    {
                        layerCards->createCardBack(kuser3);
                    }
                case kuser4:
                    if (layerCards->getListCards_1()->count() != 3 && info[2] != "0")
                    {
                        layerCards->createCardBack(kuser4);
                    }
                case kuser5:
                    if (layerCards->getListCards_1()->count() != 3 && info[2] != "0")
                    {
                        layerCards->createCardBack(kuser5);
                    }
                case kuser6:
                    if (layerCards->getListCards_1()->count() != 3 && info[2] != "0")
                    {
                        layerCards->createCardBack(kuser6);
                    }
				break;
			}
		}
	}
}

void Lieng::action_LatBai(string listCard,string uid, bool tua)
{
	if (strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
	{
		if (this->getChildByTag(123) != NULL)
		{
			this->removeChildByTag(123);
		}
		getButtonByTag(dTag_btnSqueez)->setEnabled(false);
		getButtonByTag(dTag_btnView)->setEnabled(false);
	}

	int pos = layerAvatars->getPosByName(uid);
	layerCards->turnUpAllCards(listCard, pos);
}

bool Lieng::checkPlaying(string _list){
	CCLOG("Jump to here check playing %s", _list.c_str());
	vector<string> info = mUtils::splitString(_list, ';');
	vector<string> firt = mUtils::splitString(info[0], '|');
	if(strcmp(firt[2].c_str(), "1") == 0)
	{
		return true;
	}
	return false;
}


void Lieng::moveButtonRight(){
	int w_Button = 129;
	int h_Button = 44;

	getButtonByTag(dTag_btnFollow)->setPosition(ccp(WIDTH_DESIGN - w_Button -105 , h_Button + 20));
	getButtonByTag(dTag_btnBet)->setPosition(ccp(WIDTH_DESIGN - w_Button , 10));
	getButtonByTag(dTag_btnFold)->setPosition(ccp(WIDTH_DESIGN - w_Button * 2 - 10, 10));
}

void Lieng::resetButtonLocation(){
	int w_Button = 129;
	int h_Button = 44;

	getButtonByTag(dTag_btnBet)->setPosition(ccp(WIDTH_DESIGN - w_Button -105, 15));
	getButtonByTag(dTag_btnFollow)->setPosition(ccp(WIDTH_DESIGN - w_Button -105, h_Button + 20));
	getButtonByTag(dTag_btnFold)->setPosition(ccp(WIDTH_DESIGN - w_Button - 200, 15));
}



void Lieng::whenUserReady(string uid){
	layerAvatars->setReady(layerAvatars->getPosByName(uid), true);

	if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
		getButtonByTag(dTag_btnReady)->setEnabled(false);
		getButtonByTag(dTag_btnUnready)->setEnabled(true);
	}
}

void Lieng::whenUserUnready(string uid){
	layerAvatars->setReady(layerAvatars->getPosByName(uid), false);

	if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
		getButtonByTag(dTag_btnUnready)->setEnabled(false);
		getButtonByTag(dTag_btnReady)->setEnabled(true);
	}
}

void Lieng::whenGameStart(){
	getButtonByTag(dTag_btnReady)->setEnabled(false);
	getButtonByTag(dTag_btnUnready)->setEnabled(false);
	flag_Complete_Click = false;
	layerAvatars->setUnReadyAllUser();
}

void Lieng::whenGameEnd(){
    
    layerAvatars->stopAllTimer();
	getButtonByTag(dTag_Complete)->setEnabled(true);

	getButtonByTag(dTag_btnUnready)->setEnabled(false);
	getButtonByTag(dTag_btnView)->setEnabled(false);
	getButtonByTag(dTag_btnSqueez)->setEnabled(false);
	getButtonByTag(dTag_btnFold)->setEnabled(false);
	getButtonByTag(dTag_btnFollow)->setEnabled(false);
	getButtonByTag(dTag_btnBet)->setEnabled(false);

	resetButtonLocation();

	string Bet = *GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string strBet = mUtils::splitString(Bet, '@')[0];
	minBet = atoi(strBet.c_str());

	flagChiaBai = false;
	_list_cards = "";
	real = false;
	flag_Complete_Click = true;
	//this->runAction(CCSequence::create(CCDelayTime::create(15),CCCallFunc::create(this, callfunc_selector(Lieng::deleteResuiltGame)),NULL));
}

void Lieng::deleteResuiltGame(){
	//if (flag_Complete_Click == false && checkPlaying(_list_user) == false)
	{
		getButtonByTag(dTag_Complete)->setEnabled(false);
		getButtonByTag(dTag_btnReady)->setEnabled(true);

		layerCards->resetGame();
		layerBet->getLayerResuilt()->removeAllChildrenWithCleanup(true);
	}
}

void Lieng::whenResuiltGame(string rg){
	////"rg":"dautv5|1|8|3|2|1000;dautv3|1|8|7|3|1000"
	CCLOG("resuilt %s", rg.c_str());

	getButtonByTag(dTag_btnBet)->setEnabled(false);
	getButtonByTag(dTag_btnFollow)->setEnabled(false);
	getButtonByTag(dTag_btnFold)->setEnabled(false);

	layerAvatars->stopAllTimer();
	if (this->getChildByTag(234) != NULL)
	{
		this->removeChildByTag(234);
	}

	if (this->getChildByTag(123) != NULL)
	{
		this->removeChildByTag(123);
	}

	Number_Chat_inGame7u *layerNumbers = Number_Chat_inGame7u::create();
	this->addChild(layerNumbers);

	vector<string> resuilt = mUtils::splitString(rg,';');
	for (int i = 0; i < resuilt.size(); i++)
	{
		vector<string> info = mUtils::splitString(resuilt[i],'|');
		string money = "";
		string strResuilt = info[2] + "|" + info[3] + "|" + info[4];
		if(i == 0)
		{
			money = ("+"+info[5]);
		}else{
			money = ("-"+info[5]);
		}

		int pos = layerAvatars->getPosByName(info[0]);
		layerNumbers->showNumberByPos(pos, money);
		layerBet->setResuit4AllUser(pos, info[1],strResuilt);
	}
}

void Lieng::whenUserBet(string uid, long gameBet){
	string _gameBet = mUtils::convertMoneyEx((int)gameBet);
	int pos = layerAvatars->getPosByName(uid);

	layerBet->getFrameBetByPos(pos)->setValueBet(_gameBet + " $");
}

void Lieng::action_To(string uid,string betal){
	layerAvatars->stopAllTimer();

	if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
		layerAvatars->getUserByPos(kuser0)->startTimer();

		getButtonByTag(dTag_btnBet)->setEnabled(false);
		getButtonByTag(dTag_btnFold)->setEnabled(false);
		getButtonByTag(dTag_btnFollow)->setEnabled(false);

		vector<string> typeBet = mUtils::splitString(betal, ',');
		for(int i = 0; i < typeBet.size(); i++){
			if(typeBet[i] == "1"){
				getButtonByTag(dTag_btnBet)->setEnabled(true);
			}
			else if (typeBet[i] == "2"){
				getButtonByTag(dTag_btnFold)->setEnabled(true);
			}
			else if (typeBet[i] == "3"){
				getButtonByTag(dTag_btnFollow)->setEnabled(true);
			}
		}
	}

	else{
		if (this->getChildByTag(234) != NULL)
		{
			this->removeChildByTag(234);
		}
		getButtonByTag(dTag_btnBet)->setEnabled(false);
		getButtonByTag(dTag_btnFold)->setEnabled(false);
		getButtonByTag(dTag_btnFollow)->setEnabled(false);
		//Count Down
		switch(layerAvatars->getPosByName(uid)){
		case kuser1:
			layerAvatars->getUserByPos(kuser1)->startTimer();
			break;
		case kuser2:
			layerAvatars->getUserByPos(kuser2)->startTimer();
			break;
		case kuser3:
			layerAvatars->getUserByPos(kuser3)->startTimer();
			break;
            case kuser4:
                layerAvatars->getUserByPos(kuser4)->startTimer();
			break;
            case kuser5:
                layerAvatars->getUserByPos(kuser5)->startTimer();
			break;
            case kuser6:
                layerAvatars->getUserByPos(kuser6)->startTimer();
			break;}
	}
}

void Lieng::btn_ready_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> parameter (new SFSObject());
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_READY_REQ,parameter,lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void Lieng::btn_Unready_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_UNREADY_REQ,params,lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}
void Lieng::btn_XemBai_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		if(this->getChildByTag(123) !=NULL){
			this->removeChildByTag(123);
		}

		if(_list_cards != ""){
			layerCards->turnUpAllCards(_list_cards, kuser0);
			getButtonByTag(dTag_btnSqueez)->setEnabled(false);
			getButtonByTag(dTag_btnView)->setEnabled(false);
			moveButtonRight();
		}
	}
}

void Lieng::btn_NanBai_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		Nan3Cay *BaCay = Nan3Cay::create();
		BaCay->setCallbackFunc(this,callfuncN_selector(Lieng::callBackFunction_LatBai));
		BaCay->initListCardHand(_list_cards);
		BaCay->setTag(123);
		this->addChild(BaCay);
	}
}

void Lieng::callBackFunction_LatBai(CCNode *pSend){
	if(_list_cards != ""){
		layerCards->turnUpAllCards(_list_cards, kuser0);
		getButtonByTag(dTag_btnSqueez)->setEnabled(false);
		getButtonByTag(dTag_btnView)->setEnabled(false);
		moveButtonRight();
	}
}

void Lieng::callBackFuntion_Endgive(CCNode *pSend)
{
	flagChiaBai = true;
	action_To(currentTo, currentBetal);

	getButtonByTag(dTag_btnSqueez)->setEnabled(true);
	getButtonByTag(dTag_btnView)->setEnabled(true);
}

void Lieng::btn_To_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		cocos2d::extension::CCBReader * ccbReader = NULL;
		CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
		V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);

		ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
		ccNodeLoaderLibrary->registerCCNodeLoader("LayerBet_Lieng",   LayerBet_LiengLoader::loader());
		// read main layer
		ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
		LayerBet_Lieng *betLieng_Layer;
		if (ccbReader)
		{
			betLieng_Layer = (LayerBet_Lieng *)ccbReader->readNodeGraphFromFile( "LayerBet_Lieng.ccbi" );
			betLieng_Layer->setPosition(ccp(10,10));
			CCLOG("Min bet Lieng: %d",minBet);
			CCLOG("My Bet Lieng: %d",my_To);
			betLieng_Layer->setInfoBet(minBet,my_To);
			betLieng_Layer->setTag(234);
			this->addChild(betLieng_Layer);
			ccbReader->release();
		}
	}
}

void Lieng::btn_Up_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		params->PutInt("gbv", minBet);
		params->PutInt("bet", 2);
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_GAME_BET_REQ,params,lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void Lieng::btn_Theo_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		params->PutInt("bet", 3);
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_GAME_BET_REQ,params,lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void Lieng::btn_Complete_click(CCObject *sender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		deleteResuiltGame();
	}
}
