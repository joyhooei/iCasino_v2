//
//  LayerChanGame.cpp
//  iCasinov2
//
//  Created by DauA on 6/4/14.
//
//

#include "LayerChanGame.h"
#include "_Background_inGame_.h"
#include "Requests/ExtensionRequest.h"
#include "CardChan.h"
#include "_Chat_.h"
#include "LayerGameChan_XuongU.h"
#include "SliderCustomLoader.h"
#include "SceneManager.h"
#include "LayerGameChan_KetQua.h"
#include "AllData.h"

#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())

LayerChanGame::LayerChanGame(){
	CCLOG("Nhay vao chan Game");
	EXT_EVENT_REQ_DISCARD = "rqhofc";
	EXT_EVENT_READY_REQ = "rr";
	EXT_EVENT_REQ_DRAW_CARD = "rqdrwc";
	EXT_EVENT_REQ_TAKE_CARD = "rqtkc";
	EXT_EVENT_REQ_DUOI_CARD = "rqduoic";
	EXT_EVENT_REQ_TRENTAY_DETAIL = "rqttdtl";

	EXT_SRVNTF_GAME_MASTER_INFO = "ntfgminfo";
	EXT_SRVNTF_PLAYER_LIST = "ntfpllst";
	EXT_SRVNTF_USER_READY = "ntfurd";
	EXT_EVENT_START = "s";
	EXT_EVENT_END = "e";
	EXT_EVENT_LISTCARD_NTF = "lcntf";
	EXT_SRVNTF_ONHAND_DETAILS = "ntfohdetl";
	EXT_SRVNTF_CURRENT_PLAYING_USER = "ntfcurpu";
	EXT_SRVNTF_NOC_COUNT = "ntfnoccnt";
	EXT_SRVNTF_CARD_ORIGINATION = "ntfcorg";
	EXT_EVENT_RES_DRAW_CARD = "rsdrwc";
	EXT_EVENT_RES_DUOI_CARD = "rsduoic";
	EXT_EVENT_RES_TAKE_CARD = "rstkc";
	EXT_SRVNTF_ANBAO = "ntfanbao";
	EXT_EVENT_RES_DISCARD = "rshofc";
	EXT_EVENT_GAME_RESULT = "grs";
	EXT_SRVNTF_ONE_EXPECTING_U = "ntfoeu";
	EXT_SRVNTF_ONE_EXPECTING_CHIU = "ntfoechiu";	
	EXT_EVENT_RES_U = "rsU";
	EXT_EVENT_REQ_U = "rqU";
	EXT_EVENT_REQ_CHIU_CARD = "rqchiuc";
	EXT_EVENT_REQ_NOC_DETAIL = "rqnocdtl"; 
	EXT_EVENT_RES_CHIU_CARD = "rschiuc";

	_list_user = "";
	mylistCard = "";
	currentPlayer = "";

	gameStarted = false;
	flagChiaBai = false;

	countDiscard = 0;

	w_cardhand = 34;
	h_cardhand = 125;
	w_card = 25;
	h_card = 75;
	goc = float(250/19);
	_coutZorder = 0;

	// Vi tri cac la bai cua tri
	left_chi_left = (110);
	left_chi_right = (670);
	left_chi_me = (500);
	left_chi_top = (350) - w_card;

	bottom_chi_left = 206;
	bottom_chi_right = 253;
	bottom_chi_me = 172;
	bottom_chi_top = 290;

	//Vi tri cac la bai duoi tay
	left_d_me = 16;
	left_d_top = 448;
	left_d_left = 16;
	left_d_right = WIDTH_DESIGN - 16 - w_card;

	bottom_d_me = 85;
	bottom_d_left = 360;
	bottom_d_right = 360;
	bottom_d_top = 400;

	//đếm số chíu của từng người chơi
	count_chiu_me = 0;
	count_chiu_left = 0;
	count_chiu_right = 0;
	count_chiu_top = 0;

	//Khoảng cách lá bài cửa trì
	kc_me = kc_left = kc_right = kc_top = w_card;

	createButtons();
	createAvatars();

	uLayer = UILayer::create();
	uLayer->setAnchorPoint(ccp(0, 0));
	uLayer->setPosition(ccp(0, 0));
	this->addChild(uLayer);

	lblDetail = UILabel::create();
	lblDetail->setText("");
	lblDetail->setFontSize(20);
	lblDetail->setAnchorPoint(ccp(0, 0));
	lblDetail->setPosition(ccp(20, HEIGHT_DESIGN-lblDetail->getContentSize().height-20));
	lblDetail->setColor(ccRED);
	uLayer->addChild(lblDetail);

	//INIT ARRAY CARD ALL USER

	ALL_CARDS = CCArray::create();
	ALL_CARDS->retain();
	createAllCards();

	CARD_ME = CCArray::create();
	CARD_ME->retain();

	CARD_C_ME = CCArray::create();
	CARD_C_ME->retain();

	CARD_C_LEFT = CCArray::create();
	CARD_C_LEFT->retain();

	CARD_C_RIGHT = CCArray::create();
	CARD_C_RIGHT->retain();

	CARD_C_TOP = CCArray::create();
	CARD_C_TOP->retain();

	CARD_D_ME_top = CCArray::create();
	CARD_D_ME_top->retain();

	CARD_D_LEFT_top = CCArray::create();
	CARD_D_LEFT_top->retain();

	CARD_D_RIGHT_top = CCArray::create();
	CARD_D_RIGHT_top->retain();

	CARD_D_TOP_top = CCArray::create();
	CARD_D_TOP_top->retain();

	CARD_D_ME_bottom = CCArray::create();
	CARD_D_ME_bottom->retain();

	CARD_D_LEFT_bottom = CCArray::create();
	CARD_D_LEFT_bottom->retain();

	CARD_D_RIGHT_bottom = CCArray::create();
	CARD_D_RIGHT_bottom->retain();

	CARD_D_TOP_bottom = CCArray::create();
	CARD_D_TOP_bottom->retain();


	GameServer::getSingleton().addListeners(this);
	this->scheduleOnce(schedule_selector(LayerChanGame::sendRequestJoinGame),1.0f);
	SceneManager::getSingleton().hideLoading();
}

LayerChanGame::~LayerChanGame(){
	CCLOG("Deconstructor Game Chan");
	CARD_ME->removeAllObjects();
	CARD_ME->release();

	CARD_D_ME_top->removeAllObjects();
	CARD_D_ME_top->release();

	CARD_C_ME->removeAllObjects();
	CARD_C_ME->release();

	CARD_D_LEFT_top->removeAllObjects();
	CARD_D_LEFT_top->release();

	CARD_C_LEFT->removeAllObjects();
	CARD_C_LEFT->release();

	CARD_D_RIGHT_top->removeAllObjects();
	CARD_D_RIGHT_top->release();

	CARD_C_RIGHT->removeAllObjects();
	CARD_C_RIGHT->release();

	CARD_D_TOP_top->removeAllObjects();
	CARD_D_TOP_top->release();

	CARD_C_TOP->removeAllObjects();
	CARD_C_TOP->release();

	CARD_D_ME_bottom->removeAllObjects();
	CARD_D_ME_bottom->release();

	CARD_D_LEFT_bottom->removeAllObjects();
	CARD_D_LEFT_bottom->release();

	CARD_D_RIGHT_bottom->removeAllObjects();
	CARD_D_RIGHT_bottom->release();

	CARD_D_TOP_bottom->removeAllObjects();
	CARD_D_TOP_bottom->release();

	ALL_CARDS->removeAllObjects();
	ALL_CARDS->release();
	GameServer::getSingleton().removeListeners(this);
}

void LayerChanGame::onExit()
{
	CCLOG("Deconstructor Game Chan");
	CARD_ME->removeAllObjects();
	CARD_ME->release();

	CARD_D_ME_top->removeAllObjects();
	CARD_D_ME_top->release();

	CARD_C_ME->removeAllObjects();
	CARD_C_ME->release();

	CARD_D_LEFT_top->removeAllObjects();
	CARD_D_LEFT_top->release();

	CARD_C_LEFT->removeAllObjects();
	CARD_C_LEFT->release();

	CARD_D_RIGHT_top->removeAllObjects();
	CARD_D_RIGHT_top->release();

	CARD_C_RIGHT->removeAllObjects();
	CARD_C_RIGHT->release();

	CARD_D_TOP_top->removeAllObjects();
	CARD_D_TOP_top->release();

	CARD_C_TOP->removeAllObjects();
	CARD_C_TOP->release();

	CARD_D_ME_bottom->removeAllObjects();
	CARD_D_ME_bottom->release();

	CARD_D_LEFT_bottom->removeAllObjects();
	CARD_D_LEFT_bottom->release();

	CARD_D_RIGHT_bottom->removeAllObjects();
	CARD_D_RIGHT_bottom->release();

	CARD_D_TOP_bottom->removeAllObjects();
	CARD_D_TOP_bottom->release();

	ALL_CARDS->removeAllObjects();
	ALL_CARDS->release();
	GameServer::getSingleton().removeListeners(this);
}

void LayerChanGame::createButtons(){
	layerButtons = LayerButtonInGame::create();
	this->addChild(layerButtons);

	int w_Button = 129;
	int h_Button = 44;
	int _space = 20;

	Button *btnReady = createButtonWithTitle_Pos("Sẵn Sàng",ccp(WIDTH_DESIGN - w_Button - _space, _space));
	Button *btnTake = createButtonWithTitle_Pos("Đánh",ccp(WIDTH_DESIGN - w_Button - _space, _space));
	Button *btnBoc = createButtonWithTitle_Pos("Bốc", ccp(WIDTH_DESIGN - w_Button - _space, h_Button + 30));
	Button *btnDuoi = createButtonWithTitle_Pos("Dưới", ccp(WIDTH_DESIGN - w_Button - _space, h_Button * 2 + 40));
	Button *btnEate = createButtonWithTitle_Pos("Ăn", ccp(WIDTH_DESIGN - w_Button - _space, h_Button * 2 + 40));
	Button *btnU = createButtonWithTitle_Pos("Ù", ccp(WIDTH_DESIGN - w_Button * 2 - 30, 20));
	Button *btnChiu = createButtonWithTitle_Pos("Chíu", ccp(WIDTH_DESIGN - w_Button * 2 - 30, h_Button + 30));

	btnReady->setEnabled(true);
	btnTake->setEnabled(false);
	btnBoc->setEnabled(false);
	btnDuoi->setEnabled(false);
	btnEate->setEnabled(false);
	btnU->setEnabled(false);
	btnChiu->setEnabled(false);

	btnReady->setTag(cTag_btnReady);
	btnTake->setTag(cTag_btnTake);
	btnBoc->setTag(cTag_btnBoc);
	btnDuoi->setTag(cTag_btnDuoi);
	btnEate->setTag(cTag_btnEate);
	btnU->setTag(cTag_btnU);
	btnChiu->setTag(cTag_btnChiu);

	btnReady->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_ready_click));
	btnTake->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_take_click));
	btnBoc->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_boc_click));
	btnDuoi->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_Duoi_click));
	btnEate->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_eate_click));
	btnU->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_U_Click));
	btnChiu->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_Chiu_Click));

	layerButtons->addWidget(btnReady);
	layerButtons->addWidget(btnTake);
	layerButtons->addWidget(btnBoc);
	layerButtons->addWidget(btnDuoi);
	layerButtons->addWidget(btnEate);
	layerButtons->addWidget(btnU);
	layerButtons->addWidget(btnChiu);

}
void LayerChanGame::createAvatars(){
	layerAvatars = LayerAvatarInGame::create();
	layerAvatars->resetAll();
	layerAvatars->getUserByPos(kUserMe)->setVisible(false);
	layerAvatars->getUserByPos(kUserBot)->setVisible(false);
	layerAvatars->getUserByPos(kUserBot)->setTouchEnabled(false);
	layerAvatars->getUserByPos(kUserLeft)->setPositionY(layerAvatars->getUserByPos(kUserLeft)->getPositionY() + 30);
	layerAvatars->getUserByPos(kUserRight)->setPositionY(layerAvatars->getUserByPos(kUserRight)->getPositionY() + 30);
	this->addChild(layerAvatars);
}

void LayerChanGame::createAllCards()
{
	for(int i = 0; i < 100; i++)
	{
		CardChan *pCard = CardChan::create();
		pCard->setZOrder(i);
		pCard->loadTexture("3_2.png");
		pCard->setVisible(false);
		pCard->setRotation(0);
		pCard->setTouchEnabled(false);
		uLayer->addWidget(pCard);
		ALL_CARDS->addObject(pCard);
	}
}

void LayerChanGame::resetAllCards()
{
	CCLOG("ALL_CARD %d",ALL_CARDS->count());
	for(int i = 0; i < (int)ALL_CARDS->count(); i++)
	{
		CardChan *pCard = (CardChan*)ALL_CARDS->objectAtIndex(i);
		pCard->setVisible(false);
		pCard->setTouchEnabled(false);
		pCard->setZOrder(i);
	}
}

void LayerChanGame::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
	if(strcmp("hbc", cmd->c_str())==0){
		return;
	}
	CCLOG("cmd = %s",cmd->c_str());

	//player list
	if(strcmp(EXT_SRVNTF_PLAYER_LIST.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> lu = param->GetUtfString("lu");
		string _lu = "";
		if( lu != NULL){
			_lu = lu->c_str();
			_list_user = lu->c_str();
			updateUser(_list_user);
			CCLOG("List user update: %s",_list_user.c_str());
			CCLOG("EXT_SRVNTF_PLAYER_LIST");
		}
	}

	//user ready
	else if (strcmp(EXT_SRVNTF_USER_READY.c_str(),cmd->c_str())==0){
		boost::shared_ptr<string> user = param->GetUtfString("usrn");
		string _user = "";
		if (user != NULL) {
			_user = user->c_str();
			setUserReady(_user);
		}

		//wwhen user list user
		CCLOG("user ready: %s",_user.c_str());
		CCLOG("EXT_SRVNTF_USER_READY");
	}

	// game start
	else if (strcmp(EXT_EVENT_START.c_str(), cmd->c_str())==0){
		gameStarted = true;
		layerAvatars->setUnReadyAllUser();
		CCLOG("EXT_EVENT_START");
	}

	//list card ntf
	else if(strcmp(EXT_EVENT_LISTCARD_NTF.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> usrn = param->GetUtfString("usrn");
		boost::shared_ptr<string> lc = param->GetUtfString("lc");

		string _usrn = "";
		string _lc = "";

		if (usrn != NULL) {
			_usrn = usrn->c_str();
		}
		if (lc != NULL){
			_lc = lc->c_str();
		}

		if (!flagChiaBai) {
			if (strcmp(_usrn.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
				//Display my list cards
				setMyListCards(_lc);
				flagChiaBai = true;
			}
		}else{
			if (strcmp(_usrn.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
				mylistCard = Dsplit(_lc, '/')[0];
				if (mylistCard != "") {
					sortMyListCards(mylistCard);
				}
			}
		}
		CCLOG("EXT_EVENT_LISTCARD_NTF");
	}

	//noc count
	else if (strcmp(EXT_SRVNTF_NOC_COUNT.c_str(), cmd->c_str())==0){
		boost::shared_ptr<long> noccount = param->GetInt("noccount");
		if (noccount != NULL) {
			CCLOG("noc count: %ld",*noccount);
		}
		CCLOG("EXT_SRVNTF_NOC_COUNT");
	}

	//chi tiet (detail ca la bao tren tay)
	else if (strcmp(EXT_SRVNTF_ONHAND_DETAILS.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> ohdetl = param->GetUtfString("ohdetl");
		boost::shared_ptr<string> usrn = param->GetUtfString("usrn");

		string _ohdetl = "";
		string _usrn = "";
		if (ohdetl != NULL) {
			_ohdetl = ohdetl->c_str();
		}
		if (usrn != NULL) {
			_usrn = usrn->c_str();
		}
		if (strcmp(_usrn.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
			CCLOG("detail %s: ",_ohdetl.c_str());
			////Mô tả các lá bài trên tay: Chắn:Ba Đầu:Cạ:Què
			vector<string> detail = Dsplit(_ohdetl, ':');
			lblDetail->setText("Chắn: "+detail[0]+" Ba Đầu: "+detail[1]+" Cạ: "+detail[2]+ " Què: "+detail[3]);
		}
		CCLOG("EXT_SRVNTF_ONHAND_DETAILS");
	}

	//current player
	else if (strcmp(EXT_SRVNTF_CURRENT_PLAYING_USER.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> usrn = param->GetUtfString("usrn");
		if (usrn != NULL) {
			currentPlayer = usrn->c_str();
			setCurrentPlayer(currentPlayer,countDiscard);
		}
		CCLOG("EXT_SRVNTF_CURRENT_PLAYING_USER");
	}

	//boc noc
	else if (strcmp(EXT_EVENT_RES_DRAW_CARD.c_str(), cmd->c_str())==0){
		boost::shared_ptr<long> rescode = param->GetInt("rscode");
		if(rescode != NULL){
			CCLOG("Resuilt code Draw: %ld",*rescode);
			if (*rescode == 0) {

				getButtonByTag(cTag_btnBoc)->setEnabled(false);
				getButtonByTag(cTag_btnEate)->setPosition(getButtonByTag(cTag_btnBoc)->getPosition());
				getButtonByTag(cTag_btnDuoi)->setEnabled(true);
			}
		}
		CCLOG("EXT_EVENT_RES_DRAW_CARD");
	}

	//dưới card
	else if(strcmp(EXT_EVENT_RES_DUOI_CARD.c_str(), cmd->c_str())==0){
		boost::shared_ptr<long> rescode = param->GetInt("rscode");
		if (rescode != NULL) {

		}
		CCLOG("EXT_EVENT_RES_DUOI_CARD");
	}

	//TakeCards
	else if (strcmp(EXT_EVENT_RES_TAKE_CARD.c_str(), cmd->c_str())==0){
		boost::shared_ptr<long> rescode = param->GetInt("rscode");
		if (rescode != NULL) {
			whenUserTakeCards(*rescode);
		}
		CCLOG("EXT_EVENT_RES_TAKE_CARD");
	}

	//card origition
	else if (strcmp(EXT_SRVNTF_CARD_ORIGINATION.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> f_user = param->GetUtfString("funa");
		boost::shared_ptr<string> t_user = param->GetUtfString("tuna");

		boost::shared_ptr<unsigned char> cardnu = param->GetByte("cardnu");
		boost::shared_ptr<unsigned char> cardsu = param->GetByte("cardsu");
		boost::shared_ptr<unsigned char> crdorg = param->GetByte("crdorg");

		string _f_user = "";
		string _t_user = "";
		string _cardnu = "";
		string _cardsu = "";
		int _crdorg = -1;

		if (f_user != NULL) {
			_f_user = f_user->c_str();
		}
		if (t_user != NULL) {
			_t_user = t_user->c_str();
		}
		if (cardnu != NULL) {
			int number = *cardnu;
			_cardnu = boost::to_string(number);
			CCLOG("cardnu: %s",_cardnu.c_str());
		}
		if (cardsu != NULL) {
			int suite = *cardsu;
			_cardsu = boost::to_string(suite);
			CCLOG("cardsu: %s",_cardsu.c_str());
		}
		if (crdorg != NULL) {
			_crdorg = *crdorg;
			CCLOG("crdorg: %d",_crdorg);
		}
		if(_crdorg == 6){
			countDiscard++;
		}
		takeCards(_f_user,_t_user,_cardnu,_cardsu,_crdorg);
		CCLOG("EXT_SRVNTF_CARD_ORIGINATION");
	}

	//An bao
	else if (strcmp(EXT_SRVNTF_ANBAO.c_str(),cmd->c_str())==0){
		boost::shared_ptr<long> anbaores = param->GetInt("anbaores");
		if (anbaores != NULL) {
			error_AnBao(*anbaores);
		}
		CCLOG("EXT_SRVNTF_ANBAO");
	}

	// Chíu
	else if (strcmp(EXT_SRVNTF_ONE_EXPECTING_CHIU.c_str(),cmd->c_str()) == 0)
	{
		boost::shared_ptr<string> usrn = param->GetUtfString("usrn");
		if (usrn != NULL)
		{
			CCLOG("Co nguoi chiu: %s",usrn->c_str());
			whenConguoi_Chiu(usrn->c_str());
		}
		CCLOG("EXT_SRVNTF_ONE_EXPECTING_CHIU");
	}
	
	//Bao chiu thanh cong
	else if(strcmp(EXT_EVENT_RES_CHIU_CARD.c_str(),cmd->c_str()) == 0)
	{
		boost::shared_ptr<long> rscode = param->GetInt("rscode");
		if (rscode != NULL)
		{
			if (*rscode == 0)
			{
				getButtonByTag(cTag_btnChiu)->setEnabled(false);
				getButtonByTag(cTag_btnTake)->setEnabled(true);
			}
		}
	}

	//Bao U
	else if(strcmp(EXT_EVENT_RES_U.c_str(),cmd->c_str()) == 0)
	{
		boost::shared_ptr<long> rscode = param->GetInt("rscode");
		if (rscode != NULL)
		{
			if (*rscode == 0)
			{
				CCLOG("Co the xuong U");
				XuongU();
				// Bao U
			}
			
		}
		
	}

	//Bao co the u
	else if (strcmp(EXT_SRVNTF_ONE_EXPECTING_U.c_str(), cmd->c_str())==0){
		boost::shared_ptr<string> usrn = param->GetUtfString("usrn");
		if (usrn != NULL) {
			whenConguoi_ChoU(usrn->c_str());
			CCLOG("nguoi cho U: %s",usrn->c_str());
		}
		CCLOG("EXT_SRVNTF_ONE_EXPECTING_U");
	}
	//Danh bai
	else if (strcmp(EXT_EVENT_RES_DISCARD.c_str(), cmd->c_str())==0){
		boost::shared_ptr<long> rscode = param->GetInt("rscode");
		if (rscode != NULL) {
			if (*rscode != 0) {
				CCLOG("Không đánh được !");
			}
		}
		CCLOG("EXT_EVENT_RES_DISCARD");
	}

	//Bài trên tay người Ù
	else if (strcmp("ntfttdetl", cmd->c_str()) == 0)
	{
		boost::shared_ptr<string> usrn = param->GetUtfString("usrn");
		boost::shared_ptr<string> lc = param->GetUtfString("lc");

		CCLOG("nguoi U: %s", usrn->c_str());
		CCLOG("Bai tren tay: %s", lc->c_str());
	}

	//Bài còn trong nọc
	else if(strcmp("ntfnocdetl", cmd->c_str()) == 0){
		boost::shared_ptr<string> nocdetl = param->GetUtfString("nocdetl");
		if (nocdetl != NULL)
		{
			CCLOG("noc detail: %s", nocdetl->c_str());
		}
	}

	//Resuilt game
	else if (strcmp(EXT_EVENT_GAME_RESULT.c_str(),cmd->c_str())==0){
		boost::shared_ptr<string> rg = param->GetUtfString("rg");
		if( rg != NULL){
			CCLOG("Resuilt game: %s",rg->c_str());
			layerAvatars->stopAllTimer();
			resuiltGame(rg->c_str());
		}
		CCLOG("EXT_EVENT_GAME_RESULT");
	}

	// game end
	else if (strcmp(EXT_EVENT_END.c_str(), cmd->c_str())==0){
		setEndGame();
		CCLOG("EXT_EVENT_END");
	}


}//end extensions

void LayerChanGame::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

}

void LayerChanGame::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

}

void LayerChanGame::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

}
void LayerChanGame::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

}

//Send Request join game
void LayerChanGame::sendRequestJoinGame(float dt){
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest("rqjg", params, lastRoom));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

// Hàm cắt 1 chuỗi
vector<string> LayerChanGame::Dsplit(string &S,const char &str){
	vector<string> arrStr;
	string::iterator t,t2;
	for(t=S.begin();t<S.end();){
		// Lặp từ vị trí bắt đầu
		t2=find(t, S.end(),str); // Tìm vị trí space ' ' đầu tiên
		//kể từ vị trí t
		if(t!=t2)
			arrStr.push_back(string(t,t2));
		if(t2 == S.end())
			break;
		t=t2+1; // chuyển sang vị trí sau
	}
	return arrStr;
}

// tìm vị trí người chơi so với mình
int LayerChanGame::getPosUserByName(string uid,string _list_user){
	int vt = -1;
	vector<string> list;
	if(_list_user.c_str() != NULL && _list_user != ""){
		list = Dsplit(_list_user, ';');
	}
	//Tìm vị trí của mình trong list user
	for(int i=0;i<list.size();i++){
		string _id = Dsplit(list[i], ':')[1];
		if(strcmp(_id.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			vt = i;
			break;
		}
	}
	// từ đó tìm vị trí của id truyền vào (so với mình)
	for(int k=0;k<list.size();k++){
		if(strcmp(list[k].c_str(), "")==0)
			continue;
		string player = list[k];
		vector<string> n = Dsplit(player, ':');
		if(strcmp(n[1].c_str(), uid.c_str())==0){
			if(k == vt){
				return kUserMe;
			}
			else if(k == (vt + 1) % 4){
				return kUserRight;
			}
			else if(k == (vt + 2) % 4){
				return kUserTop;
			}
			else if(k == (vt + 3) % 4){
				return kUserLeft;
			}
			break;
		}
	}
	return vt;
}

//Update list user
void LayerChanGame::updateUser(string list){
	//31:dautv:1;27:dautv3:0
	//    layerAvatars->resetAll();
	layerAvatars->resetAll();
	vector<string> listUser;
	listUser = Dsplit(list, ';');
	CCLOG("Do dai: %ld",listUser.size());
	boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	for(int i=0;i<listUser.size();i++){
		if(lastRoom==NULL){
			return;
		}
		if(listUser[i].c_str()==NULL)
			continue;
		string player = listUser[i];
		vector<string> n = Dsplit(player, ':');

		if(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])==NULL){
			continue;
		}

		int _money = 0;
		string _name = "";

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("amf")->GetDoubleValue();

		if (name != NULL) {
			_name = name->c_str();
		}
		if(money != NULL){
			_money = (int)(*money);
		}

		if(strcmp(n[1].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			layerAvatars->setName(kUserMe, _name);
			layerAvatars->getUserByPos(kUserMe)->setMoney(_money);
		}
		else{
			switch (getPosUserByName(n[1], _list_user)) {
			case kUserLeft:
				layerAvatars->getUserByPos(kUserLeft)->setVisibleLayerInvite(false);
				layerAvatars->setName(kUserLeft, _name);
				layerAvatars->getUserByPos(kUserLeft)->setMoney(_money);
				break;
			case kUserRight:
				layerAvatars->getUserByPos(kUserRight)->setVisibleLayerInvite(false);
				layerAvatars->setName(kUserRight, _name);
				layerAvatars->getUserByPos(kUserRight)->setMoney(_money);
				break;
			case kUserTop:
				layerAvatars->getUserByPos(kUserTop)->setVisibleLayerInvite(false);
				layerAvatars->setName(kUserTop, _name);
				layerAvatars->getUserByPos(kUserTop)->setMoney(_money);
				break;
			}
		}
	}
}

void LayerChanGame::setMyListCards(string listCards){
	if (gameStarted) {
		string card_Hand = Dsplit(listCards, '/')[0];
		vector<string> list = Dsplit(card_Hand, ';');

		int i = 0;
		int list_size = (int)list.size();
		while (i <= list.size()) {
			if (i<list.size()) {
				vector<string> info = Dsplit(list[i], ':');
				//CardChan *pCard = CardChan::create();
				CardChan *pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
				pCard->setID(i);
				pCard->setNumber(atoi(info[1].c_str()));
				pCard->setSuite(atoi(info[2].c_str()));
				pCard->setFlag(false);
				pCard->loadTexture(findTypeCard(info[1], info[2]).c_str());
				pCard->setSizeCard(w_cardhand, h_cardhand);
				pCard->setPosition(ccp(400,90));
				float start = (list_size % 2 == 0) ? (float)list_size : (float)(list_size - 1);
				pCard->setRotation(-((start) / 2 * goc));
				pCard->setTouchEnabled(true);
				pCard->setVisible(true);
				pCard->addTouchEventListener(this, toucheventselector(LayerChanGame::CardTouch));
				CARD_ME->addObject(pCard);
				_coutZorder++;
				i++;
			}else{
				rotateListCards();
				break;
			}
		}//end while
	}
}

//sort myListCard
void LayerChanGame::sortMyListCards(string listCards){
	vector<string> list = Dsplit(listCards, ';');
	if ((int)list.size() > (int)CARD_ME->count())
	{
		setMyListCards(listCards);
	}
	
	for(int i=0;i<list.size();i++){
		vector<string> info = Dsplit(list[i], ':');
		CardChan* pCard = (CardChan*)CARD_ME->objectAtIndex(i);
		pCard->setNumber(atoi(info[1].c_str()));
		pCard->setSuite(atoi(info[2].c_str()));
		pCard->setFlag(false);
		pCard->loadTexture(findTypeCard(info[1], info[2]).c_str());
	}
}

void LayerChanGame::rotateListCards(){
	CCObject *t;
	int dem = 0;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *card = dynamic_cast<CardChan*>(t);
		CCActionInterval *action = CCRotateBy::create(0.8, dem*goc);
		card->runAction(CCSequence::create(action,NULL));
		dem++;
	}
}

void LayerChanGame::resortCard_CuaTri_Alluser(int pos){
	switch(pos){
	case kUserMe:
		if (CARD_C_ME->count() > 8)
		{
			kc_me = (w_card * 8) / (CARD_C_ME->count());
			animateCards(CARD_C_ME, left_chi_me, bottom_chi_me, kc_me);
		}
		break;
	case kUserLeft:
		if (CARD_C_LEFT->count() > 8)
		{
			kc_left = (w_card * 8) / (CARD_C_LEFT->count());
			animateCards(CARD_C_LEFT, left_chi_left, bottom_chi_left, kc_left);
		}
		break;
	case kUserRight:
		if (CARD_C_RIGHT->count() > 8)
		{
			kc_right = (w_card * 8) / (CARD_C_RIGHT->count());
 			animateCards(CARD_C_RIGHT, left_chi_right, bottom_chi_right, -kc_right);
		}
		break;
	case kUserTop:
		if (CARD_C_TOP->count() > 8)
		{
			kc_top = (w_card * 8) / (CARD_C_TOP->count());
 			animateCards(CARD_C_TOP, left_chi_top, bottom_chi_top,  -kc_top);
		}
		break;
	}
}

void LayerChanGame::animateCards(CCArray *P, float _left, float _bottom, float _kc){
	if (P->count() == 0)
	{
		return;
	}

	CCObject *t;
	int dem = 0;
	CCARRAY_FOREACH(P, t){
		CardChan *card = dynamic_cast<CardChan*>(t);
		CARD_D_TOP_bottom->addObject(card);
		CCActionInterval *moveTo = CCMoveTo::create(0.5,ccp((_left + _kc * dem),_bottom));
 		card->runAction(moveTo);
		dem++;
	}

	// sort zOrder
	for (int i = 0; i < P->count() - 1; i++)
	{
		for (int j = i + 1; j < P->count(); j++)
		{
			CardChan *iCard = (CardChan*)P->objectAtIndex(i);
			CardChan *jCard = (CardChan*)P->objectAtIndex(j);
			if (iCard->getZOrder() > jCard->getZOrder())
			{
				int temp = iCard->getZOrder();
				iCard->setZOrder(jCard->getZOrder());
				jCard->setZOrder(temp);
			}
		}
	}
}

void LayerChanGame::takeCards(string f_user, string t_user, string cardnu, string cardsu, int crdorg){
	CCLOG("From user: %s, to user: %s",f_user.c_str(),t_user.c_str());
	switch (crdorg) {
	case CARD_ORIGINATION_CHIA_BAI:
		break;
	case CARD_ORIGINATION_BOC_NOC:
		CCLOG("Bốc nọc");
		action_BocNoc(t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_AN_CUA_TREN:
		CCLOG("Ăn cửa trên");
		action_AnCuaTren(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_AN_CUA_TRI:
		CCLOG("Ăn cửa trì");
		action_AnCuaTri(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_CHIU:
		CCLOG("Chíu");
		action_ChiuBai(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_TRA_CUA:
		CCLOG("Trả cửa");
		action_TraCua(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_BY_DISCARD:
		CCLOG("Đánh bài");
		action_DanhBai(f_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_BY_DUOI:
		CCLOG("Dưới");
		break;
	case CARD_ORIGINATION_BY_TRANSFER_TREN_2_DUOI:
		CCLOG("Chuyển bài");
		action_ChuyenBai(f_user, t_user, cardnu, cardsu);
		break;
	case 10:
		action_An_U(f_user, t_user, cardnu, cardsu);
		break;
	default:
		break;
	}
}

void LayerChanGame::action_BocNoc(string t_user,string cardnu, string cardsu){
	CCLOG("Bốc Nọc %s",t_user.c_str());
	CardChan *pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
	_coutZorder++;
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setNumber(atoi(cardnu.c_str()));
	pCard->setSuite(atoi(cardsu.c_str()));
	pCard->setSizeCard(w_card, h_card);
	pCard->setPosition(ccp(WIDTH_DESIGN/2 - w_card/2, HEIGHT_DESIGN/2 - h_card/2));
	pCard->setVisible(true);

	float toX = -1;
	float toY = -1;
	int f = -1;
	int pos = getPosUserByName(t_user, _list_user);
	if(strcmp(t_user.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
		CCLOG("Me Draw");
		toX = left_chi_me + (float)CARD_C_ME->count() * kc_me;
		toY = bottom_chi_me;
		f = kUserMe;
	}
	else{
		switch (pos) {
		case kUserLeft:
			toX = left_chi_left + (float)CARD_C_LEFT->count() * kc_left;
			toY = bottom_chi_left;
			f = kUserLeft;
			break;
		case kUserRight:
			toX = left_chi_right - (float)CARD_C_RIGHT->count() * kc_right;
			toY = bottom_chi_right;
			f = kUserRight;
			break;
		case kUserTop:
			toX = left_chi_top - (float)CARD_C_TOP->count() * kc_top;
			toY = bottom_chi_top;
			f = kUserTop;
			break;
		default:
			break;
		}
	}

	//Animation
	CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(toX,toY));
	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(LayerChanGame::addCard_toCuaTri),(void*)value);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	pCard->runAction(CCSequence::create(delay,moveTo,callfun,NULL));
}

void LayerChanGame::action_AnCuaTren(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Ăn cửa trên");
	int fpos = -1;
	int tpos = -1;
	float toX = -1;
	float toY = -1;
	int f = -1;
	fpos = getPosUserByName(f_user, _list_user);
	tpos = getPosUserByName(t_user, _list_user);
	CardChan* fcard = getCardFromPos_take(fpos);
	if (fcard == NULL) {
		return;
	}

	if (strcmp(t_user.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
		toX = (float)CARD_D_ME_top->count() * w_card + left_d_me;
		toY = bottom_d_me;
		f = kUserMe;
	}
	else{
		switch (tpos) {
		case kUserLeft:
			toX = (float)CARD_D_LEFT_top->count() * w_card + left_d_left;
			toY = bottom_d_left;
			f = kUserLeft;
			break;
		case kUserRight:
			toX = left_d_right - (float)CARD_D_RIGHT_top->count() * w_card;
			toY = bottom_d_right;
			f = kUserRight;
			break;
		case kUserTop:
			toX = (float)CARD_D_TOP_top->count() * w_card + left_d_top;
			toY = bottom_d_top;
			f = kUserTop;
			break;
		default:
			break;
		}
	}

	//animation
	CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(toX,toY));
	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(LayerChanGame::addCard_toDuoiTay_top),(void*)value);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	fcard->runAction(CCSequence::create(delay,moveTo,callfun,NULL));
}

void LayerChanGame::action_AnCuaTri(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Ăn cửa trì");
	action_AnCuaTren(f_user, f_user, cardnu, cardsu);
}

void LayerChanGame::action_ChiuBai(string f_user, string t_user, string cardnu, string cardsu){
	int fpos = -1;
	int tpos = -1;
	fpos = getPosUserByName(f_user,_list_user);
	tpos = getPosUserByName(t_user,_list_user);
	CardChan *fcard = NULL;
	fcard = getCardFromPos_take(fpos);
	if (fcard == NULL)
	{
		return;
	}

	float toX = -1;
	float toY = -1;
	int f = -1;

	switch(tpos)
	{
	case kUserMe:
		toX = (float)CARD_D_ME_top->count() * w_card + left_d_me;
		toY = bottom_d_me;
		f = kUserMe;
		break;
	case kUserLeft:
		toX = (float)CARD_D_LEFT_top->count() * w_card + left_d_left;
		toY = bottom_d_left;
		f = kUserLeft;
		break;
	case kUserRight:
		toX = left_d_right - (float)CARD_D_RIGHT_top->count() * w_card;
		toY = bottom_d_right;
		f = kUserRight;
		break;
	case kUserTop:
		toX = (float)CARD_D_TOP_top->count() * w_card + left_d_top;
		toY = bottom_d_top;
		f = kUserTop;
		break;
	default:
		break;
	}

	//animation
	CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(toX,toY));
	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(LayerChanGame::addCard_toDuoiTay_top),(void*)value);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	fcard->runAction(CCSequence::create(delay,moveTo,callfun,NULL));

}

void LayerChanGame::action_TraCua(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Trả cửa");
	int fpos = -1;
	int tpos = -1;
	fpos = getPosUserByName(f_user,_list_user);
	tpos = getPosUserByName(t_user,_list_user);

	if(t_user == "")
	{
		action_DanhBai(f_user, cardnu, cardsu);
	}

	else
	{
		if (strcmp(f_user.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
		{
			action_TraCua_ME(tpos, cardnu, cardsu);
		}
		else
		{
			action_TraCua_NOTME(fpos, tpos, cardnu, cardsu);
		}
	}
}

void LayerChanGame::action_TraCua_ME(int tpos, string cardnu, string cardsu){
	CCObject *t;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *pCard =  dynamic_cast<CardChan*>(t);
		if (pCard->getFlag() && pCard->getNumber() == atoi(cardnu.c_str()) && pCard->getSuite() == atoi(cardsu.c_str())) {
			float rotate = -(pCard->getRotation());
			CCActionInterval *rotateTo = CCRotateBy::create(0.4, rotate);
			CCActionInterval *scaleBy = CCScaleBy::create(0.4, w_card/w_cardhand,h_card/h_cardhand);
			
			float toX = 0;
			float toY = 0;
			int f = -1;
			switch(tpos){
			case kUserLeft:
				toX = (float)CARD_C_LEFT->count() * w_card + left_chi_left;
				toY = bottom_chi_left;
				f = kUserLeft;
				break;
			case kUserRight:
				toX = (float)CARD_C_RIGHT->count() * w_card + left_chi_right;
				toY = bottom_chi_right;
				f = kUserRight;
				break;
			case kUserTop:
				toX = (float)CARD_C_LEFT->count() * w_card + left_chi_top;
				toY = bottom_chi_top;
				f = kUserTop;
				break;
			}
			CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));

			pCard->runAction(moveTo);
			pCard->runAction(rotateTo);
			pCard->runAction(scaleBy);
			CARD_ME->removeObject(pCard);
			switch(f){
			case kUserLeft:
				CARD_C_LEFT->addObject(pCard);
				break;
			case kUserRight:
				CARD_C_RIGHT->addObject(pCard);
				break;
			case kUserTop:
				CARD_C_TOP->addObject(pCard);
				break;
			}
			this->refreshListCard();
		}
	}
}

void LayerChanGame::action_TraCua_NOTME(int fpos, int tpos, string cardnu, string cardsu){
	CardChan *pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
	_coutZorder++;
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setSizeCard(w_card, h_card);
	pCard->setTouchEnabled(false);

	//Xac dinh vi tri
	switch (fpos) {
	case kUserLeft:
		pCard->setPosition(ccp(33, layerAvatars->getUserByPos(kUserLeft)->getPositionY()));
		break;
	case kUserRight:
		pCard->setPosition(ccp(732, layerAvatars->getUserByPos(kUserRight)->getPositionY()));
		break;
	case kUserTop:
		pCard->setPosition(ccp(240, layerAvatars->getUserByPos(kUserTop)->getPositionY()));
		break;
	default:
		break;
	}

	pCard->setVisible(true);

	//di chuyen den:
	float toX = -1;
	float toY = -1;
	int f = -1;

	switch(tpos){
	case kUserMe:
		toX = (float)CARD_C_ME->count() * kc_me + left_chi_me;
		toY = bottom_chi_me;
		f = kUserMe;
		break;
	case kUserLeft:
		toX = (float)CARD_C_LEFT->count() * kc_left + left_chi_left;
		toY = bottom_chi_left;
		f = kUserLeft;
		break;
	case kUserRight:
		toX = left_chi_right - (float)CARD_C_RIGHT->count() * kc_right ;
		toY = bottom_chi_right;
		f = kUserRight;
		break;
	case kUserTop:
		toX = left_chi_top - (float)CARD_C_TOP->count() * kc_top;
		toY = bottom_chi_top;
		f = kUserTop;
		break;
	default:
		break;
	}
	
	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(LayerChanGame::addCard_toCuaTri),(void*)value);
	CCMoveTo *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));
	pCard->runAction(moveTo);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	pCard->runAction(CCSequence::create(delay,moveTo,callfun,NULL));
}

//** Đánh bài ***//
void LayerChanGame::action_DanhBai(string f_user, string cardnu, string cardsu){
	CCLOG("Đánh bài");
	if (strcmp(f_user.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
		action_DanhBai_ME(cardnu, cardsu);
	}
	else{
		int pos = getPosUserByName(f_user, _list_user);
		action_DanhBai_NOTME(pos, cardnu, cardsu);
	}
}
//Tôi đánh
void LayerChanGame::action_DanhBai_ME(string cardnu,string cardsu){
	CCLOG("Tôi đánh");
	CCObject *t;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *pCard =  dynamic_cast<CardChan*>(t);
		if (pCard->getFlag() && pCard->getNumber() == atoi(cardnu.c_str()) && pCard->getSuite() == atoi(cardsu.c_str())) {
			float rotate = -(pCard->getRotation());
			CCActionInterval *rotateTo = CCRotateBy::create(0.3, rotate);
			CCActionInterval *scaleBy = CCScaleBy::create(0.3, w_card/w_cardhand,h_card/h_cardhand);
			pCard->runAction(rotateTo);
			pCard->runAction(scaleBy);
			CARD_ME->removeObject(pCard);
			//Animation
			CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp((float)CARD_C_ME->count() * kc_me + left_chi_me, bottom_chi_me));
			int *value = new int(kUserMe);
			CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(LayerChanGame::addCard_toCuaTri),(void*)value);
			CCDelayTime *delay = CCDelayTime::create(0.3);
			pCard->runAction(CCSequence::create(delay,moveTo,callfun,NULL));
			this->refreshListCard();
		}
	}
}
//Người khác đánh
void LayerChanGame::action_DanhBai_NOTME(int pos,string cardnu,string cardsu){
	CCLOG("Người khác đánh bài");
	CardChan *pCard = (CardChan*)ALL_CARDS->objectAtIndex(_coutZorder);
	_coutZorder++;
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setSizeCard(w_card, h_card);

	float toX = -1;
	float toY = -1;
	int f = -1;
	switch (pos) {
	case kUserLeft:
		pCard->setPosition(ccp(33, layerAvatars->getUserByPos(kUserLeft)->getPositionY()));
		toX = (float)CARD_C_LEFT->count() * kc_left + left_chi_left;
		toY = bottom_chi_left;
		f = kUserLeft;
		break;
	case kUserRight:
		pCard->setPosition(ccp(732, layerAvatars->getUserByPos(kUserRight)->getPositionY()));
		toX = left_chi_right - (float)CARD_C_RIGHT->count() * kc_right;
		toY = bottom_chi_right;
		f = kUserRight;
		break;
	case kUserTop:
		pCard->setPosition(ccp(400, layerAvatars->getUserByPos(kUserTop)->getPositionY()));
		toX = left_chi_top - (float)CARD_C_TOP->count() * kc_top;
		toY = bottom_chi_top;
		f = kUserTop;
		break;
	default:
		break;
	}

	pCard->setVisible(true);
	//////////////////////////////////////////////////////////////////////////
	//Animation
	CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(toX,toY));
	int *value = new int(f);
	CCCallFuncND *callfun = CCCallFuncND::create(this, callfuncND_selector(LayerChanGame::addCard_toCuaTri),(void*)value);
	CCDelayTime *delay = CCDelayTime::create(0.3);
	pCard->runAction(CCSequence::create(delay,moveTo,callfun,NULL));
}

//Chuyển bài từ trên tay xuống dưới tay
void LayerChanGame::action_ChuyenBai(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Chuyển bài từ trên xuống dưới tay");
	int pos = getPosUserByName(t_user, _list_user);
	if( f_user != "" && t_user != "")
	{
		if (strcmp(t_user.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
			action_ChuyenBai_ME(pos,cardnu,cardsu);
		}else{
			action_ChuyenBai_NOTME(pos,cardnu,cardsu);
		}
	}
	if (f_user == "")
	{
		action_ChuyenBai_Chiu(pos, cardnu, cardsu);
	}
}

void LayerChanGame::action_ChuyenBai_ME(int pos, string cardnu, string cardsu){
	CCObject *t;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *pCard =  dynamic_cast<CardChan*>(t);
		if (pCard->getFlag() && pCard->getNumber() == atoi(cardnu.c_str()) && pCard->getSuite() == atoi(cardsu.c_str())) {

			float rotate = -(pCard->getRotation());
			int tmp = 0;
			tmp = count_chiu_me > 0 ? count_chiu_me - 1 : 0;
			CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp((CARD_D_ME_bottom->count() - tmp) * w_card + left_d_me, bottom_d_me - 25));
			CCActionInterval *rotateTo = CCRotateBy::create(0.4, rotate);
			CCActionInterval *scaleBy = CCScaleBy::create(0.4, w_card / w_cardhand,h_card / h_cardhand);

			CCLOG("zOrder card hand: %d",pCard->getZOrder());
			pCard->runAction(moveTo);
			pCard->runAction(rotateTo);
			pCard->runAction(scaleBy);
			pCard->setTouchEnabled(false);

			CARD_ME->removeObject(pCard);
			CARD_D_ME_bottom->addObject(pCard);
			this->refreshListCard();
		}
	}
}

void LayerChanGame::action_ChuyenBai_NOTME(int pos, string cardnu, string cardsu){
	CCLOG("Chuyen bai tu tren tay xuong duoi tay binh thuong");
	CardChan *pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
	_coutZorder++;
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setSizeCard(w_card, h_card);

	float toX = -1;
	float toY = -1;
	int f = -1;
	int tmp = 0;

	switch (pos) {
	case kUserLeft:
		pCard->setPosition(ccp(layerAvatars->getUserByPos(kUserLeft)->getPosition().x, layerAvatars->getUserByPos(kUserLeft)->getPosition().y));
		tmp = count_chiu_left > 0 ? count_chiu_left - 1 : 0;
		toX = (float)(CARD_D_LEFT_bottom->count() - tmp) * w_card + left_d_left;
		toY = bottom_d_left - 25;
		f = kUserLeft;
		break;
	case kUserRight:
		pCard->setPosition(ccp(layerAvatars->getUserByPos(kUserRight)->getPosition().x, layerAvatars->getUserByPos(kUserRight)->getPosition().y));
		tmp = count_chiu_right > 0 ? count_chiu_right - 1 : 0;
		toX = left_d_right - (float)(CARD_D_RIGHT_bottom->count() - tmp) * w_card;
		toY = bottom_d_right - 25;
		f = kUserRight;
		break;
	case kUserTop:
		pCard->setPosition(ccp(layerAvatars->getUserByPos(kUserTop)->getPosition().x, layerAvatars->getUserByPos(kUserTop)->getPosition().y));
		tmp = count_chiu_top > 0 ? count_chiu_top - 1 : 0;
		toX = (float)(CARD_D_TOP_bottom->count() - tmp) * w_card + left_d_top;
		toY = bottom_d_top - 25;
		f = kUserTop;
		break;
	default:
		break;
	}

	pCard->setVisible(true);

	CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));
	pCard->runAction(moveTo);
	switch (f) {
	case kUserLeft:
		CARD_D_LEFT_bottom->addObject(pCard);
		break;
	case kUserRight:
		CARD_D_RIGHT_bottom->addObject(pCard);
		break;
	case kUserTop:
		CARD_D_TOP_bottom->addObject(pCard);
		break;
	default:
		break;
	}
}

void LayerChanGame::action_ChuyenBai_Chiu(int pos, string cardnu, string cardsu){

	CCLOG("Chuyen bai thu tren tay xuong duoi tay khi chiu");
	CardChan *pCard = NULL;

	float toX = -1;
	float toY = -1;
	int f = -1;

	int myPos = getPosUserByName(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(),_list_user);
	if (pos == myPos)
	{
		CCLOG("Chuyen bai khi minh chiu");
		CCLOG("cardnu = %d, cardsu = %d", atoi(cardnu.c_str()), atoi(cardsu.c_str()));
		for(int i = 0; i < CARD_ME->count(); i++)
		{
			CardChan *cards = (CardChan *)CARD_ME->objectAtIndex(i);
			if (cards->getNumber() == atoi(cardnu.c_str()) && cards->getSuite() == atoi(cardsu.c_str()))
			{
				cards->setTouchEnabled(false);
				cards->setVisible(false);
				pCard = (CardChan *)CARD_ME->objectAtIndex(i);
				pCard->setRotation(0);
				CARD_ME->removeObjectAtIndex(i);
				CCLOG("Jump here");
				break;
			}
		}
		refreshListCard();
		toX = (float)(CARD_D_ME_bottom->count() - count_chiu_me) * w_card + left_d_me;
		toY = (bottom_d_me) - (25 /2) * count_chiu_me;
		count_chiu_me++;
		f = kUserMe;
	}
	else
	{
		CCLOG("Chuyen bai khi nguoi khac chiu");
		pCard = (CardChan *)ALL_CARDS->objectAtIndex(_coutZorder);
		_coutZorder++;
		pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
		pCard->setSizeCard(w_card, h_card);

		switch(pos){
		case kUserLeft:
			pCard->setPosition(ccp(layerAvatars->getUserByPos(kUserLeft)->getPosition().x, layerAvatars->getUserByPos(kUserLeft)->getPosition().y));
			toX = (float)(CARD_D_LEFT_bottom->count() - count_chiu_left) * w_card + left_d_left;
			toY = (bottom_d_left) - (25 /2) * (count_chiu_left + 1);
			count_chiu_left++;
			f = kUserLeft;
			break;
		case kUserRight:
			pCard->setPosition(ccp(layerAvatars->getUserByPos(kUserRight)->getPosition().x, layerAvatars->getUserByPos(kUserRight)->getPosition().y));
			toX = left_d_right - (float)(CARD_D_RIGHT_bottom->count() - count_chiu_right) * w_card;
			toY = bottom_d_right - (25 / 2) * (count_chiu_right + 1);
			count_chiu_right++;
			f = kUserRight;
			break;
		case kUserTop:
			pCard->setPosition(ccp(layerAvatars->getUserByPos(kUserTop)->getPosition().x, layerAvatars->getUserByPos(kUserTop)->getPosition().y));
			toX = (float)(CARD_D_TOP_bottom->count() - count_chiu_top) * w_card + left_d_top;
			toY = bottom_d_top - (25 / 2) * (count_chiu_top + 1);
			count_chiu_top++;
			f = kUserTop;
			break;
		default:
			break;
		}
	}
	
	pCard->setVisible(true);
	float _rotate = -(pCard->getRotation());
	CCLOG("rotate: %f",pCard->getRotation());
	float scaleX = (f == kUserMe) ? w_card / w_cardhand : 1;
	float scaleY = (f == kUserMe) ? h_card / h_cardhand : 1;

	CCActionInterval *moveto = CCMoveTo::create(0.3, ccp(toX, toY));
	CCActionInterval *scaleBy = CCScaleBy::create(0.3, scaleX, scaleY);
	CCActionInterval *rotateBy = CCRotateBy::create(0.3,_rotate);
	pCard->runAction(moveto);
	pCard->runAction(scaleBy);
	pCard->runAction(rotateBy);

	switch(f)
	{
	case kUserMe:
		CARD_D_ME_bottom->addObject(pCard);
		break;
	case kUserLeft:
		CARD_D_LEFT_bottom->addObject(pCard);
		break;
	case kUserRight:
		CARD_D_RIGHT_bottom->addObject(pCard);
		break;
	case kUserTop:
		CARD_D_TOP_bottom->addObject(pCard);
		break;
	default:
		break;
	}
}

void LayerChanGame::action_An_U(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Ăn Ù");
	action_AnCuaTren(f_user,t_user,cardnu,cardsu);
}

string LayerChanGame::findTypeCard(string number,string suite){
	string str = "";
	str += number+"_"+suite+".png";
	return str;
}

//add card vao cua tri
void LayerChanGame::addCard_toCuaTri(CCNode* sender, void* data){
	int *f = (int*) data; 
	CardChan *pCard = (CardChan*) sender;
	switch(*f)
	{
	case kUserMe:
		CARD_C_ME->addObject(pCard);
		CCLOG("Add them 1 card cua chi user me, CARD_C_ME %d",CARD_C_ME->count());
		resortCard_CuaTri_Alluser(kUserMe);
		//Hien Button an,vs button dưới
		if (strcmp(currentPlayer.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
		{
			getButtonByTag(cTag_btnBoc)->setEnabled(false);
			getButtonByTag(cTag_btnEate)->setPosition(getButtonByTag(cTag_btnBoc)->getPosition());
			getButtonByTag(cTag_btnDuoi)->setEnabled(true);
		}
		break;
	case kUserLeft:
		CARD_C_LEFT->addObject(pCard);
		CCLOG("Add them 1 card cua chi user left, CARD_C_LEFT %d",CARD_C_LEFT->count());
		resortCard_CuaTri_Alluser(kUserLeft);
		break;
	case kUserRight:
		CARD_C_RIGHT->addObject(pCard);
		CCLOG("Add them 1 card cua chi user right, CARD_C_RIGHT %d",CARD_C_RIGHT->count());
		resortCard_CuaTri_Alluser(kUserRight);
		break;
	case kUserTop:
		CARD_C_TOP->addObject(pCard);
		CCLOG("Add them 1 card cua chi user top, CARD_C_TOP %d",CARD_C_TOP->count());
		resortCard_CuaTri_Alluser(kUserTop);
		break;
	default:
		break;
	}
}

//add card vao bai duoi tay phia tren
void LayerChanGame::addCard_toDuoiTay_top(CCNode *sender, void *data){
	int *f = (int*) data; 
	CardChan *fcard = (CardChan*) sender;
	switch(*f)
	{
	case kUserMe:
		CARD_D_ME_top->addObject(fcard);
		swapZorder(CARD_D_ME_bottom, CARD_D_ME_top, count_chiu_me, false);
			break;
	case kUserLeft:
		CARD_D_LEFT_top->addObject(fcard);
		swapZorder(CARD_D_LEFT_bottom, CARD_D_LEFT_top, count_chiu_left, false);
		break;
	case kUserRight:
		CARD_D_RIGHT_top->addObject(fcard);
		swapZorder(CARD_D_RIGHT_bottom, CARD_D_RIGHT_top, count_chiu_right, false);
		break;
	case kUserTop:
		CARD_D_TOP_top->addObject(fcard);
		swapZorder(CARD_D_TOP_bottom, CARD_D_TOP_top, count_chiu_top, false);
		break;
	default:
		break;
	}
}

void LayerChanGame::swapZorder(CCArray* P1, CCArray* P2, int _count, bool _state){
	//D_Bottom vs D_top
	if (!_state)
	{
		if (P1->count() >= P2->count())
		{
			CardChan *pCard = (CardChan*)P2->objectAtIndex(P2->count() - 1);
			CardChan *qCard = (CardChan*)P1->objectAtIndex(P2->count() - 1);
			if (pCard->getZOrder() > qCard->getZOrder())
			{
				int _zorder = -1;
				_zorder = pCard->getZOrder();
				pCard->setZOrder(qCard->getZOrder());
				qCard->setZOrder(_zorder);
			}
		}
	}
	//D_Top vs D_Bottom
	else
	{
		if ((P1->count() - _count) <= P2->count())
		{
			CardChan *pCard = (CardChan*)P1->lastObject();
			CardChan *qCard = (CardChan*)P2->objectAtIndex(P1->count() - 1 - _count);
			if (pCard->getZOrder() < qCard->getZOrder())
			{
				int _zorder = -1;
				_zorder = pCard->getZOrder();
				pCard->setZOrder(qCard->getZOrder());
				qCard->setZOrder(_zorder);
			}
		}
	}
}
//Refresh cards
void LayerChanGame::refreshListCard(){
	float countCard = (float)CARD_ME->count();
	float start = (-countCard / 2) * goc;
	CCObject *t;
	int cou = 0;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *uu = dynamic_cast<CardChan*>(t);
		float rotate = start + cou * goc;
		float oldAngle = uu->getRotation();
		CCActionInterval *rr = CCRotateBy::create(0.4, rotate-oldAngle);
		uu->runAction(CCSequence::create(rr,NULL));
		cou++;
	}
}

//get Card Form ArrayCard
CardChan* LayerChanGame::getCardFromPos_take(int pos){
	CardChan* fcard = NULL;
	switch (pos) {
	case kUserMe:
		fcard = (CardChan*)CARD_C_ME->lastObject();
		CARD_C_ME->removeLastObject();
		break;
	case kUserLeft:
		fcard = (CardChan*)CARD_C_LEFT->lastObject();
		CARD_C_LEFT->removeLastObject();
		break;
	case kUserRight:
		fcard = (CardChan*)CARD_C_RIGHT->lastObject();
		CARD_C_RIGHT->removeLastObject();
		break;
	case kUserTop:
		fcard = (CardChan*)CARD_C_TOP->lastObject();
		CARD_C_TOP->removeLastObject();
		break;
	default:
		break;
	}
	return fcard;
}

Button* LayerChanGame::createButtonWithTitle_Pos(const char *pName, CCPoint pPoint){
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

Button* LayerChanGame::getButtonByTag(int pTag){
	Button* button = (Button*) this->layerButtons->getWidgetByTag(pTag);
	return button;
}

//Card Touch
void LayerChanGame::CardTouch(CCObject *pSender,TouchEventType type){
	if (type == TOUCH_EVENT_ENDED) {
		CardChan *pChan = (CardChan*)pSender;
		CCObject *t;
		CCARRAY_FOREACH(CARD_ME, t){
			CardChan *pCard = dynamic_cast<CardChan*>(t);
			if (pCard->getNumber() == pChan->getNumber() && pCard->getSuite() == pChan->getSuite() && pCard->getID() == pChan->getID()) {
				if(!pCard->getFlag()){
					CCLOG("%s",getNameCard(pCard->getNumber(), pCard->getSuite()).c_str());
					CCPoint p = pChan->getPosition();
					float rotate = pChan->getRotation();
					pCard->setPosition(ccp(p.x + 20 * sin((rotate * PI) / 180), p.y + 20 * cos((rotate * PI) / 180)));
					pCard->setFlag(true);
				}else{
					pCard->setPosition(ccp(400, 90));
					pCard->setFlag(false);
				}
			}
			else{
				pCard->setPosition(ccp(400, 90));
				pCard->setFlag(false);
			}
		}
	}
}

string LayerChanGame::getNameCard(int number, int suite){
	string str = "";
	//sui 2:sach 0:vạn 1 văn
	switch (number) {
	case 2:
		str += "Nhị";
		break;
	case 3:
		str += "Tam";
		break;
	case 4:
		str += "Tứ";
		break;
	case 5:
		str += "Ngũ";
		break;
	case 6:
		str += "Lục";
		break;
	case 7:
		str += "Thất";
		break;
	case 8:
		str += "Bát";
		break;
	case 9:
		str += "Cửu";
		break;
	default:

		str += "Chi";
		break;
	}

	switch (suite) {
	case 0:
		str+= " Vạn";
		break;
	case 1:
		str+= " Văn";
		break;
	case 2:
		str+= " Sách";
		break;
	default:
		str+= " Chi";
		break;
	}
	return str;
}

//When user take Cards
void LayerChanGame::whenUserTakeCards(long rscode){
	if(rscode == 0){
		getButtonByTag(cTag_btnEate)->setEnabled(false);
		getButtonByTag(cTag_btnBoc)->setEnabled(false);
		getButtonByTag(cTag_btnDuoi)->setEnabled(false);
	}else{
		CCLOG("Ăn không đúng Chắn, Cạ");
		Chat *toast = new Chat("Ăn không đúng Chắn Cạ", -1);
		this->addChild(toast);
	}
}

// set current player
void LayerChanGame::setCurrentPlayer(string uid,int _count){
	layerAvatars->stopAllTimer();
	if (strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
		getButtonByTag(cTag_btnReady)->setEnabled(false);
		getButtonByTag(cTag_btnTake)->setEnabled(true);
		if (_count == 0) {
			getButtonByTag(cTag_btnEate)->setEnabled(false);
			getButtonByTag(cTag_btnBoc)->setEnabled(false);
		}else{
			getButtonByTag(cTag_btnEate)->setPosition(getButtonByTag(cTag_btnDuoi)->getPosition());
			getButtonByTag(cTag_btnEate)->setEnabled(true);
			getButtonByTag(cTag_btnBoc)->setEnabled(true);
		}
	}
	else{
		getButtonByTag(cTag_btnTake)->setEnabled(false);
		getButtonByTag(cTag_btnEate)->setEnabled(false);
		getButtonByTag(cTag_btnBoc)->setEnabled(false);
		getButtonByTag(cTag_btnDuoi)->setEnabled(false);

		switch (getPosUserByName(uid, _list_user)) {
		case kUserLeft:
			layerAvatars->getUserByPos(kUserLeft)->startTimer();
			break;
		case kUserRight:
			layerAvatars->getUserByPos(kUserRight)->startTimer();
			break;
		case kUserTop:
			layerAvatars->getUserByPos(kUserTop)->startTimer();
			break;
		default:
			break;
		}
	}
}

//set user ready
void LayerChanGame::setUserReady(string uid){
	if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
		getButtonByTag(cTag_btnReady)->setEnabled(false);
	}else{
		switch (getPosUserByName(uid, _list_user)) {
		case kUserLeft:
			layerAvatars->getUserByPos(kUserLeft)->setReady(true);
			break;
		case kUserRight:
			layerAvatars->getUserByPos(kUserRight)->setReady(true);
			break;
		case kUserTop:
			layerAvatars->getUserByPos(kUserTop)->setReady(true);
			break;
		default:
			break;
		}
	}
}

//Display loi an bao
void LayerChanGame::error_AnBao(long rscode){
	int t = (int)rscode;
	string str = "";
	switch(t){
	case ANBAO_REASON_NO_PROBLEM:
		break;
	case ANBAO_REASON_AN_CA_DOI_CHO:
		CCLOG("Lỗi ăn báo: Ăn cạ đổi chờ");
		str = "Lỗi ăn báo: Ăn cạ đổi chờ";
		break;
	case ANBAO_REASON_BO_AN_CUATREN_BUT_AN_CUATRI:
		CCLOG("Lỗi ăn báo: không ăn cửa trên nhưng lại ăn cửa trì");
		str = "Lỗi ăn báo: không ăn cửa trên nhưng lại ăn cửa trì";
		break;
	case ANBAO_REASON_DISCARD_SAMEAS_CUATREN_CUATRI_DUOITAY:
		CCLOG("Lỗi ăn báo: Đánh đi 1 con đã có ở cửa trên, cửa trì hoặc dưới tay");
		str = "Lỗi ăn báo: Đánh đi 1 con đã có ở cửa trên, cửa trì hoặc dưới tay";
		break;
	case ANBAO_REASON_ANCA_DANHCA:
		CCLOG("Lỗi ăn báo: Ăn cạ đánh cạ");
		str = "Lỗi ăn báo: Ăn cạ đánh cạ";
		break;
	case ANBAO_TREOTRANH:
		CCLOG("Lỗi ăn báo: Treo tranh");
		str = "Lỗi ăn báo: Treo tranh";
		break;
	case ANBAO_DANH_1_CA_CHI_DUOC_AN_CHAN:
		CCLOG("Lỗi ăn báo: Đã đánh cạ đi thì chỉ được Ăn chắn");
		str = "Lỗi ăn báo: Đã đánh cạ đi thì chỉ được Ăn chắn";
		break;
	case ANBAO_REASON_BOCHAN_ANCA:
		CCLOG("Lỗi ăn báo: Bỏ Chắn ăn cạ");
		str = "Lỗi ăn báo: Bỏ Chắn ăn cạ";
		break;
	case ANBAO_REASON_DANHBAI_GIONG_CHANCA_DA_AN:
		CCLOG("Lỗi ăn báo: Đánh đi lá bài giống chắn hoặc Cạ đã ăn");
		str = "Lỗi ăn báo: Đánh đi lá bài giống chắn hoặc Cạ đã ăn";
		break;
	case ANBAO_REASON_DOI_U_BACHTHUCHI:
		CCLOG("Lỗi ăn báo: Đợi Ăn Ù Bạch thủ Chi");
		str = "Lỗi ăn báo: Đợi Ăn Ù Bạch thủ Chi";
		break;
	case ANBAO_REASON_BOCHAN_DANHCHAN:
		CCLOG("Lỗi ăn báo: Bỏ Chắn đánh chắn");
		str = "Lỗi ăn báo: Bỏ Chắn đánh chắn";
		break;
	case ANBAO_REASON_BOCHAN_ANCHAN:
		CCLOG("Lỗi ăn báo: Bỏ Chắn Ăn Chắn");
		str = "Lỗi ăn báo: Bỏ Chắn Ăn Chắn";
		break;
	case ANBAO_REASON_BOCA_ANCA:
		CCLOG("Lỗi ăn báo: Bỏ Chắn Ăn Cạ");
		str = "Lỗi ăn báo: Bỏ Chắn Ăn Cạ";
		break;
	case ANBAO_REASON_DANHCA_ANCA:
		CCLOG("Lỗi ăn báo: Đánh Cạ Ăn Cạ");
		str = "Lỗi ăn báo: Đánh Cạ Ăn Cạ";
		break;
	case ANBAO_REASON_XECA_ANCA:
		CCLOG("Lỗi ăn báo: Xé cạ Ăn Cạ");
		str = "Lỗi ăn báo: Xé cạ Ăn Cạ";
		break;
	case ANBAO_REASON_XECHAN_ANCA:
		CCLOG("Lỗi ăn báo: Xé Chắn Ăn Cạ");
		str = "Lỗi ăn báo: Xé Chắn Ăn Cạ";
		break;
	case ANBAO_REASON_DANH_ROILAI_AN:
		CCLOG("Lỗi ăn báo: Đánh đi 1 con sau lại ăn đúng con đó");
		str = "Lỗi ăn báo: Đánh đi 1 con sau lại ăn đúng con đó";
		break;
	case ANBAO_REASON_DANH_DI_DOI_CHAN:
		CCLOG("Lỗi ăn báo: Đánh đi cả đôi Chắn");
		str = "Lỗi ăn báo: Đánh đi cả đôi Chắn";
		break;
	case ANBAO_REASON_AN_ROILAI_DANH:
		CCLOG("Lỗi ăn báo: Ăn một con rồi lại đánh đi con đó");
		str = "Lỗi ăn báo: Ăn một con rồi lại đánh đi con đó";
		break;
	case ANBAO_REASON_ANCA_ROILAI_DANH_QUAN_CUNG_HANG:
		CCLOG("Lỗi ăn báo: Ăn cạ rồi lại đánh 1 con cùng hàng");
		str = "Lỗi ăn báo: Ăn cạ rồi lại đánh 1 con cùng hàng";
		break;
	case ANBAO_REASON_CHIUDUOC_NHUNG_LAI_ANTHUONG:
		CCLOG("Lỗi ăn báo: Chíu được nhưng lại ăn thường");
		str = "Lỗi ăn báo: Chíu được nhưng lại ăn thường";
		break;
	case ANBAO_REASON_AN_CHON_CA:
		CCLOG("Lỗi ăn báo: Ăn cạ Chọn Cạ");
		str = "Lỗi ăn báo: Ăn cạ Chọn Cạ";
		break;
	case ANBAO_REASON_CO_CHAN_CAU_CA:
		CCLOG("Lỗi ăn báo: có Chắn Cấu Cạ");
		str = "ăn báo: có Chắn Cấu Cạ";
		break;
	}

	LayerNotification* layer = SceneManager::getSingleton().getLayerNotification();
	if( !SceneManager::getSingleton().showNotification() ){
		CCLOG("NTF Dialog already open!");
		return;
	}
	layer->setNotificationOptions("Lỗi", (str+ ",\n không thể báo ù ván này !").c_str(), false , "", 1, this );
}

//Khi co nguoi cho U
void LayerChanGame::whenConguoi_ChoU(string uid){
	string myName = "";
	myName = GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str();

	if(strcmp(uid.c_str(),myName.c_str()) == 0){
		// Hiển thị button Ù
		getButtonByTag(cTag_btnU)->setEnabled(true);
		if(strcmp(myName.c_str(),currentPlayer.c_str()) == 0)
		{
			
		}
		else
		{
			getButtonByTag(cTag_btnEate)->setEnabled(true);
		}

	}else{
		Chat *toast = new Chat(""+uid+" Đang chờ Ù, Đợi nhà này sướng", -1);
		this->addChild(toast);

		hideAllButton();

		//start timer của người chơi chờ Ù
		switch(getPosUserByName(uid,_list_user)){
			case kUserLeft:
				layerAvatars->getUserByPos(kUserLeft)->startTimer();
				break;
			case kUserRight:
				layerAvatars->getUserByPos(kUserRight)->startTimer();
				break;
			case kUserTop:
				layerAvatars->getUserByPos(kUserTop)->startTimer();
				break;
		}
	}
}

//Co nguoi co the chiu
void LayerChanGame::whenConguoi_Chiu(string uid){
	string myName = "";
	myName = GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str();

	if (strcmp(uid.c_str(),myName.c_str()) == 0)
	{
		getButtonByTag(cTag_btnChiu)->setEnabled(true);
	}
	else
	{
		if(strcmp(myName.c_str(),currentPlayer.c_str()) == 0){
			hideAllButton();
		}
	}
}


//Xuong U
void LayerChanGame::XuongU(){
	cocos2d::extension::CCBReader * ccbReader = NULL;
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);

	// register loaders
	ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerGameChan_XuongU",   LayerGameChan_XuongULoader::loader());
	// read main layer
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

	LayerGameChan_XuongU *popUp;

	if (ccbReader)
	{
		popUp = (LayerGameChan_XuongU *)ccbReader->readNodeGraphFromFile( "LayerGameChan_XuongU.ccbi" );
		popUp->setPosition(ccp(10,10));
		popUp->setZOrder(_coutZorder+1);
		uLayer->addChild(popUp);
		ccbReader->release();
	}
}


void LayerChanGame::resuiltGame(string resuilt)
{
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = SceneManager::getSingleton().getNodeLoaderLibrary();
	CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerGameChan_KetQua",   LayerGameChan_KetQuaLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	LayerGameChan_KetQua* mLayer;
	if (ccbReader)
	{
		mLayer = (LayerGameChan_KetQua *)ccbReader->readNodeGraphFromFile( "LayerGameChan_KetQua.ccbi" );
		this->addChild(mLayer, 1, 1);
		//        SceneManager::getSingleton().showLayer(mLayer);
		ccbReader->release();
	}
}

void LayerChanGame::notificationCallBack(bool isOK, int tag){
	CCLOG("callbackNtf****");
}

//set End Game
void LayerChanGame::setEndGame(){
	currentPlayer = "";
	mylistCard = "";

	kc_top = kc_right = kc_me = kc_left = w_card;

	flagChiaBai = false;
	countDiscard = 0;
	_coutZorder = 0;

	count_chiu_me = 0;
	count_chiu_left = 0;
	count_chiu_right = 0;
	count_chiu_top = 0;

	resetAllCards();

	deleteAllCardFromArray(CARD_ME);

	deleteAllCardFromArray(CARD_C_ME);
	deleteAllCardFromArray(CARD_C_LEFT);
	deleteAllCardFromArray(CARD_C_RIGHT);
	deleteAllCardFromArray(CARD_C_TOP);

	deleteAllCardFromArray(CARD_D_LEFT_bottom);
	deleteAllCardFromArray(CARD_D_ME_bottom);
	deleteAllCardFromArray(CARD_D_RIGHT_bottom);
	deleteAllCardFromArray(CARD_D_TOP_bottom);

	deleteAllCardFromArray(CARD_D_TOP_top);
	deleteAllCardFromArray(CARD_D_RIGHT_top);
	deleteAllCardFromArray(CARD_D_ME_top);
	deleteAllCardFromArray(CARD_D_LEFT_top);


	getButtonByTag(cTag_btnBoc)->setEnabled(false);
	getButtonByTag(cTag_btnDuoi)->setEnabled(false);
	getButtonByTag(cTag_btnEate)->setEnabled(false);
	getButtonByTag(cTag_btnTake)->setEnabled(false);
	getButtonByTag(cTag_btnU)->setEnabled(false);
	getButtonByTag(cTag_btnChiu)->setEnabled(false);
	getButtonByTag(cTag_btnReady)->setEnabled(true);
}

void LayerChanGame::deleteAllCardFromArray(CCArray *P){
	while(P->count()>0){
		CardChan *uu = (CardChan*)P->objectAtIndex(P->count()-1);
		P->removeObject(uu);
	}
}

//btn Ready
void LayerChanGame::btn_ready_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> parameter (new SFSObject());
		boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_READY_REQ,parameter,lastRoom));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

//btn Take Cards
void LayerChanGame::btn_take_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		CCLOG("Btn Take Click");
		boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		int count = 0;
		for (int i=0; i<CARD_ME->count(); i++) {
			CardChan *pCard = (CardChan*)CARD_ME->objectAtIndex(i);
			if (pCard->getFlag()) {
				count++;
				boost::shared_ptr<ISFSObject> params (new SFSObject());
				params->PutByte("cardnu", pCard->getNumber());
				params->PutByte("cardsu", pCard->getSuite());
				boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_REQ_DISCARD,params,lastRoom));
				GameServer::getSingleton().getSmartFox()->Send(request);
			}
		}
		if (count == 0) {
			CCLOG("Chọn 1 lá bài để đánh");
			Chat *toast = new Chat("Chọn 1 lá bài để đánh",-1);
			this->addChild(toast);
		}
		else{
			count = 0;
		}
	}
}

//btn Bốc bài
void LayerChanGame::btn_boc_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		//EXT_EVENT_REQ_DRAW_CARD
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr<Room> lstRooms = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_REQ_DRAW_CARD,params,lstRooms));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

//Btn Dưới bài

void LayerChanGame::btn_Duoi_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr<Room> lstRooms = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_REQ_DUOI_CARD,params,lstRooms));
		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

//btn Ăn bài
void LayerChanGame::btn_eate_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		//EXT_EVENT_REQ_TAKE_CARD
		boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		int count = 0;
		for (int i=0; i<CARD_ME->count(); i++) {
			CardChan *pCard = (CardChan*)CARD_ME->objectAtIndex(i);
			if (pCard->getFlag()) {
				count++;
				boost::shared_ptr<ISFSObject> params (new SFSObject());
				params->PutByte("cardnu", pCard->getNumber());
				params->PutByte("cardsu", pCard->getSuite());
				boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_REQ_TAKE_CARD,params,lastRoom));
				GameServer::getSingleton().getSmartFox()->Send(request);
			}
		}
		if (count == 0) {
			Chat *toast = new Chat("Chọn 1 lá bài để ăn", -1);
			this->addChild(toast);
		}
		else{
			count = 0;
		}
	}
}

void LayerChanGame::btn_U_Click(CCObject *sender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		CCLOG("Send U to server !");
		boost::shared_ptr<Room> lstRooms = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr<IRequest> resObj (new ExtensionRequest(EXT_EVENT_REQ_U,params,lstRooms));
		GameServer::getSingleton().getSmartFox()->Send(resObj);
	}
}

void LayerChanGame::btn_Chiu_Click(CCObject *sender, TouchEventType type){
	if (type = TOUCH_EVENT_ENDED)
	{
		boost::shared_ptr<Room> lstRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		int count = 0;
		for(int i = 0; i < (int)CARD_ME->count(); i++)
		{
			CardChan *pCard = (CardChan*)CARD_ME->objectAtIndex(i);
			if (pCard->getFlag())
			{
				count++;
				boost::shared_ptr<ISFSObject> params (new SFSObject());
				params->PutByte("cardnu", pCard->getNumber());
				params->PutByte("cardsu", pCard->getSuite());
				boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_REQ_CHIU_CARD,params,lstRoom));
				GameServer::getSingleton().getSmartFox()->Send(request);
			}
		}
		if (count == 0)
		{
			Chat *toast = new Chat("Chọn 1 lá bài để chíu", -1);
			this->addChild(toast);
		}
		else
		{
			count == 0;
		}
	}
}

void LayerChanGame::hideAllButton(){
	getButtonByTag(cTag_btnReady)->setEnabled(false);
	getButtonByTag(cTag_btnEate)->setEnabled(false);
	getButtonByTag(cTag_btnBoc)->setEnabled(false);
	getButtonByTag(cTag_btnDuoi)->setEnabled(false);
	getButtonByTag(cTag_btnTake)->setEnabled(false);
	getButtonByTag(cTag_btnChiu)->setEnabled(false);
	getButtonByTag(cTag_btnU)->setEnabled(false);
}
void LayerChanGame::resetPositionButton(){

}