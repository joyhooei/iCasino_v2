//
//  LayerChanGame.cpp
//  iCasinov2
//
//  Created by DauA on 6/4/14.
//
//

#include "LayerChanGame.h"
#include "_Background_inGame_.h"
#include "_Button_inGame_.h"
#include "Requests/ExtensionRequest.h"
#include "CardChan.h"
#include "_Chat_.h"

LayerChanGame::LayerChanGame(){
	CCLOG("Nhay vao chan Game");
	EXT_EVENT_REQ_DISCARD = "rqhofc";
	EXT_EVENT_READY_REQ = "rr";
	EXT_EVENT_REQ_DRAW_CARD = "rqdrwc";
	EXT_EVENT_REQ_TAKE_CARD = "rqtkc";
	EXT_EVENT_REQ_DUOI_CARD = "rqduoic";

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
	bottom_d_top = HEIGHT_DESIGN - 10 - h_card + 25;

	GameServer::getSingleton().addListeners(this);
	this->scheduleOnce(schedule_selector(LayerChanGame::sendRequestJoinGame),1.0f);
	createButtons();
	createAvatars();

	uLayer = UILayer::create();
	uLayer->setAnchorPoint(ccp(0, 0));
	uLayer->setPosition(ccp(0, 0));
	this->addChild(uLayer);

	//Btn Ready
	btnReady = UIButton::create();
	btnReady->loadTextures("ready.png", "ready_selected.png", "");
	btnReady->setTitleText("Sẵn Sàng");
	btnReady->setAnchorPoint(ccp(0,0));
	btnReady->setPosition(ccp(WIDTH_DESIGN-btnReady->getContentSize().width-20,20));
	btnReady->setTouchEnabled(true);
	btnReady->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_ready_click));
	btnReady->setTitleFontSize(20);
	btnReady->setTitleColor(ccRED);
	btnReady->setVisible(true);
	uLayer->addWidget(btnReady);

	//btn Take
	btnTake = UIButton::create();
	btnTake->loadTextures("ready.png", "ready_selected.png", "");
	btnTake->setTitleText("Đánh");
	btnTake->setAnchorPoint(ccp(0,0));
	btnTake->setPosition(ccp(WIDTH_DESIGN-btnTake->getContentSize().width-20,20));
	btnTake->setTouchEnabled(false);
	btnTake->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_take_click));
	btnTake->setTitleFontSize(20);
	btnTake->setTitleColor(ccRED);
	btnTake->setVisible(false);
	uLayer->addWidget(btnTake);

	//btn Bốc
	btnBoc = UIButton::create();
	btnBoc->loadTextures("ready.png", "ready_selected.png", "");
	btnBoc->setTitleText("Bốc");
	btnBoc->setAnchorPoint(ccp(0,0));
	btnBoc->setPosition(ccp(WIDTH_DESIGN-btnBoc->getContentSize().width-20,btnBoc->getContentSize().height + 30));
	btnBoc->setTouchEnabled(false);
	btnBoc->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_boc_click));
	btnBoc->setTitleFontSize(20);
	btnBoc->setTitleColor(ccRED);
	btnBoc->setVisible(false);
	uLayer->addWidget(btnBoc);

	//btn Dưới
	btnDuoi = UIButton::create();
	btnDuoi->loadTextures("ready.png", "ready_selected.png", "");
	btnDuoi->setTitleText("Dưới");
	btnDuoi->setAnchorPoint(ccp(0,0));
	btnDuoi->setPosition(ccp(WIDTH_DESIGN-btnDuoi->getContentSize().width-20,btnDuoi->getContentSize().height*2+40));
	btnDuoi->setTouchEnabled(false);
	btnDuoi->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_Duoi_click));
	btnDuoi->setTitleFontSize(20);
	btnDuoi->setTitleColor(ccRED);
	btnDuoi->setVisible(false);
	uLayer->addWidget(btnDuoi);

	//btn Eate
	btnEate = UIButton::create();
	btnEate->loadTextures("ready.png", "ready_selected.png", "");
	btnEate->setTitleText("Ăn");
	btnEate->setAnchorPoint(ccp(0,0));
	btnEate->setPosition(ccp(WIDTH_DESIGN-btnEate->getContentSize().width-20,btnEate->getContentSize().height*2+40));
	btnEate->setTouchEnabled(false);
	btnEate->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_eate_click));
	btnEate->setTitleFontSize(20);
	btnEate->setTitleColor(ccRED);
	btnEate->setVisible(false);
	uLayer->addWidget(btnEate);

	//btn Ù
	btnU = UIButton::create();
	btnU->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
	btnU->setTitleText("Ù");
	btnU->setAnchorPoint(ccp(0,0));
	btnU->setPosition(ccp(WIDTH_DESIGN-btnEate->getContentSize().width - btnU->getContentSize().width - 30, 20));
	btnU->setTouchEnabled(false);
	btnU->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_U_Click));
	btnU->setTitleFontSize(20);
	btnU->setTitleColor(ccRED);
	btnU->setVisible(false);
	uLayer->addWidget(btnU);

	//btn Chíu
	btnChiu = UIButton::create();
	btnChiu->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
	btnChiu->setTitleText("Chíu");
	btnChiu->setAnchorPoint(ccp(0,0));
	btnChiu->setPosition(ccp(WIDTH_DESIGN-btnEate->getContentSize().width - btnChiu->getContentSize().width - 30, btnChiu->getContentSize().height + 30));
	btnChiu->setTouchEnabled(false);
	btnChiu->addTouchEventListener(this, toucheventselector(LayerChanGame::btn_Chiu_Click));
	btnChiu->setTitleFontSize(20);
	btnChiu->setTitleColor(ccRED);
	btnChiu->setVisible(false);
	uLayer->addWidget(btnChiu);

	lblDetail = UILabel::create();
	lblDetail->setText("");
	lblDetail->setFontSize(20);
	lblDetail->setAnchorPoint(ccp(0, 0));
	lblDetail->setPosition(ccp(20, HEIGHT_DESIGN-lblDetail->getContentSize().height-20));
	lblDetail->setColor(ccRED);
	uLayer->addChild(lblDetail);

	//INIT ARRAY CARD ALL USER
	CARD_ME = new CCArray();
	CARD_C_ME = new CCArray();
	CARD_C_LEFT = new CCArray();
	CARD_C_RIGHT = new CCArray();
	CARD_C_TOP = new CCArray();

	CARD_D_ME_top = new CCArray();
	CARD_D_LEFT_top = new CCArray();
	CARD_D_RIGHT_top = new CCArray();
	CARD_D_TOP_top = new CCArray();

	CARD_D_ME_bottom = new CCArray();
	CARD_D_LEFT_bottom = new CCArray();
	CARD_D_RIGHT_bottom = new CCArray();
	CARD_D_TOP_bottom = new CCArray();

	CARD_ME->retain();

	CARD_C_ME->retain();
	CARD_C_LEFT->retain();
	CARD_C_RIGHT->retain();
	CARD_C_TOP->retain();

	CARD_D_ME_top->retain();
	CARD_D_LEFT_top->retain();
	CARD_D_RIGHT_top->retain();
	CARD_D_TOP_top->retain();

	CARD_D_ME_bottom->retain();
	CARD_D_LEFT_bottom->retain();
	CARD_D_RIGHT_bottom->retain();
	CARD_D_TOP_bottom->retain();
}

LayerChanGame::~LayerChanGame(){
	CCLOG("Deconstructor Game Chan");
	CARD_ME->removeAllObjects();
	CARD_ME = NULL;

	CARD_D_ME_top->removeAllObjects();
	CARD_D_ME_top = NULL;

	CARD_C_ME->removeAllObjects();
	CARD_C_ME = NULL;

	CARD_D_LEFT_top->removeAllObjects();
	CARD_D_LEFT_top = NULL;

	CARD_C_LEFT->removeAllObjects();
	CARD_C_LEFT = NULL;

	CARD_D_RIGHT_top->removeAllObjects();
	CARD_D_RIGHT_top = NULL;

	CARD_C_RIGHT->removeAllObjects();
	CARD_C_RIGHT = NULL;

	CARD_D_TOP_top->removeAllObjects();
	CARD_D_TOP_top = NULL;

	CARD_C_TOP->removeAllObjects();
	CARD_C_TOP = NULL;

	CARD_D_ME_bottom->removeAllObjects();
	CARD_D_ME_bottom = NULL;

	CARD_D_LEFT_bottom->removeAllObjects();
	CARD_D_LEFT_bottom = NULL;

	CARD_D_RIGHT_bottom->removeAllObjects();
	CARD_D_RIGHT_bottom = NULL;

	CARD_D_TOP_bottom->removeAllObjects();
	CARD_D_TOP_bottom = NULL;

	GameServer::getSingleton().removeListeners(this);
}

void LayerChanGame::createButtons(){
	LayerButtonInGame *bt = LayerButtonInGame::create();
	this->addChild(bt);
}
void LayerChanGame::createAvatars(){
	layerAvatars = LayerAvatarInGame::create();
	layerAvatars->resetAll();
	layerAvatars->getUserByPos(kUserMe)->setVisible(false);
	layerAvatars->getUserByPos(kUserBot)->setVisible(false);
	this->addChild(layerAvatars);
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
				btnBoc->setTouchEnabled(false);
				btnBoc->setVisible(false);
				btnEate->setPosition(btnBoc->getPosition());
				btnDuoi->setVisible(true);
				btnDuoi->setTouchEnabled(true);
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
	
	//Bao U
	else if(strcmp(EXT_EVENT_RES_U.c_str(),cmd->c_str()) == 0)
	{
		boost::shared_ptr<long> rscode = param->GetInt("rscode");
		if (rscode != NULL)
		{
			if (*rscode == 0)
			{
				CCLOG("Co the xuong U");
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

	//Resuilt game
	else if (strcmp(EXT_EVENT_GAME_RESULT.c_str(),cmd->c_str())==0){
		boost::shared_ptr<string> rg = param->GetUtfString("rg");
		if( rg != NULL){
			CCLOG("Resuilt game: %s",rg->c_str());
			layerAvatars->stopAllTimer();
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
			if(k==vt){
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

		string _money = "";
		string _name = "";

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("amf")->GetDoubleValue();

		if (name != NULL) {
			_name = name->c_str();
		}
		if(money != NULL){
			_money = boost::to_string(*money);
		}

		if(strcmp(n[1].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			layerAvatars->setName(kUserMe, _name);
			layerAvatars->setMoney(kUserMe,_money.c_str());
		}
		else{
			switch (getPosUserByName(n[1], _list_user)) {
			case kUserLeft:
				layerAvatars->getUserByPos(kUserLeft)->setVisibleLayerInvite(false);
				layerAvatars->setName(kUserLeft, _name);
				layerAvatars->setMoney(kUserLeft,_money.c_str());
				break;
			case kUserRight:
				layerAvatars->getUserByPos(kUserRight)->setVisibleLayerInvite(false);
				layerAvatars->setName(kUserRight, _name);
				layerAvatars->setMoney(kUserRight,_money.c_str());
				break;
			case kUserTop:
				layerAvatars->getUserByPos(kUserTop)->setVisibleLayerInvite(false);
				layerAvatars->setName(kUserTop, _name);
				layerAvatars->setMoney(kUserTop,_money.c_str());
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
		while (i <= list.size()) {
			if (i<list.size()) {
				vector<string> info = Dsplit(list[i], ':');
				CardChan *pCard = CardChan::create();
				pCard->setID(i);
				pCard->setNumber(atoi(info[1].c_str()));
				pCard->setSuite(atoi(info[2].c_str()));
				pCard->setFlag(false);
				pCard->loadTexture(findTypeCard(info[1], info[2]).c_str());
				pCard->setSizeCard(w_cardhand, h_cardhand);
				pCard->setPosition(ccp(400,80));
				pCard->setRotation(-(250/19)*(19/2));
				pCard->setTouchEnabled(true);
				pCard->setZOrder(150+i);
				pCard->addTouchEventListener(this, toucheventselector(LayerChanGame::CardTouch));
				CARD_ME->addObject(pCard);
				uLayer->addWidget(pCard);
				_coutZorder++;
				i++;
			}else{
				CCLOG("Xoay Bai");
				rotateListCards();
				for (int i=0; i<CARD_ME->count();i++)
				{
					CardChan *pCard = (CardChan*)CARD_ME->objectAtIndex(i);
					CCLOG("zOrder %d : %d",i,pCard->getZOrder());
				}

				break;
			}
		}//end while
	}
}

//sort myListCard
void LayerChanGame::sortMyListCards(string listCards){
	
	CCLOG("List card me: %d",CARD_ME->count());
	CCLOG("List card: %s",listCards.c_str());
	vector<string> list = Dsplit(listCards, ';');
	CCLOG("list.length: %d", (int)list.size());
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

void LayerChanGame::takeCards(string f_user, string t_user, string cardnu, string cardsu, int crdorg){
	switch (crdorg) {
	case CARD_ORIGINATION_CHIA_BAI:
		break;
	case CARD_ORIGINATION_BOC_NOC:
		action_BocNoc(t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_AN_CUA_TREN:
		action_AnCuaTren(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_AN_CUA_TRI:
		action_AnCuaTri(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_CHIU:
		action_ChiuBai(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_TRA_CUA:
		action_TraCua(f_user, t_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_BY_DISCARD:
		action_DanhBai(f_user, cardnu, cardsu);
		break;
	case CARD_ORIGINATION_BY_DUOI:
		break;
	case CARD_ORIGINATION_BY_TRANSFER_TREN_2_DUOI:
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
	CardChan *pCard = CardChan::create();
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setSizeCard(w_card, h_card);
	pCard->setPosition(ccp(WIDTH_DESIGN/2 - w_card/2, HEIGHT_DESIGN/2 - h_card/2));
	pCard->setZOrder(_coutZorder);
	_coutZorder++;
	uLayer->addChild(pCard);

	float toX = -1;
	float toY = -1;
	int f = -1;
	int pos = getPosUserByName(t_user, _list_user);
	if(strcmp(t_user.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
		CCLOG("Me Draw");
		toX = left_chi_me + (float)CARD_C_ME->count() * w_card;
		toY = bottom_chi_me;
		f = kUserMe;
	}
	else{
		switch (pos) {
		case kUserLeft:
			CCLOG("Left Draw");
			toX = left_chi_left + (float)CARD_C_LEFT->count() * w_card;
			toY = bottom_chi_left;
			f = kUserLeft;
			break;
		case kUserRight:
			toX = left_chi_right - (float)CARD_C_RIGHT->count() * w_card;
			toY = bottom_chi_right;
			f = kUserRight;
			break;
		case kUserTop:
			toX = left_chi_top + (float)CARD_C_TOP->count() * w_card;
			toY = bottom_chi_top;
			f = kUserTop;
			break;
		default:
			break;
		}
	}

	//Animation
	CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));
	pCard->runAction(moveTo);
	switch (f) {
	case kUserMe:
		CARD_C_ME->addObject(pCard);
		break;
	case kUserLeft:
		CARD_C_LEFT->addObject(pCard);
		break;
	case kUserRight:
		CARD_C_RIGHT->addObject(pCard);
		break;
	case kUserTop:
		CARD_C_TOP->addObject(pCard);
		break;
	default:
		break;
	}
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
	CCLOG("zOrder: %d",fcard->getZOrder());
	if (fcard == NULL) {
		return;
	}

	if (strcmp(t_user.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
		toX = (float)CARD_D_ME_top->count() * w_card + left_d_me;
		toY = bottom_d_me - 25;
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

	CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));
	CCActionInterval *rotateTo = CCRotateBy::create(0.4, -(fcard->getRotation()));
	fcard->runAction(moveTo);
	fcard->runAction(rotateTo);

	switch (f) {
	case kUserMe:
		CARD_D_ME_top->addObject(fcard);
		break;
	case kUserLeft:
		CARD_D_LEFT_top->addObject(fcard);
		break;
	case kUserRight:
		CARD_D_RIGHT_top->addObject(fcard);
		break;
	case kUserTop:
		CARD_D_TOP_top->addObject(fcard);
		break;
	default:
		break;
	}
}

void LayerChanGame::action_AnCuaTri(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Ăn cửa trì");
	action_AnCuaTren(f_user, f_user, cardnu, cardsu);
}

void LayerChanGame::action_ChiuBai(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Chíu bài");
}

void LayerChanGame::action_TraCua(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Trả cửa");
	int fpos = -1;
	int tpos = -1;
	fpos = getPosUserByName(f_user,_list_user);
	tpos = getPosUserByName(t_user,_list_user);
	if (strcmp(f_user.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
	{
		action_TraCua_ME(tpos, cardnu, cardsu);
	}
	else
	{
		action_TraCua_NOTME(fpos, tpos, cardnu, cardsu);
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
	CardChan* pCard = CardChan::create();
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setSizeCard(w_card, h_card);
	pCard->setTouchEnabled(false);

	//Xac dinh vi tri
	switch (fpos) {
	case kUserLeft:
		pCard->setPosition(ccp(33, 171));
		break;
	case kUserRight:
		pCard->setPosition(ccp(732, 171));
		break;
	case kUserTop:
		pCard->setPosition(ccp(33, 171));
		break;
	default:
		break;
	}
	uLayer->addChild(pCard);

	//di chuyen den:
	float toX = -1;
	float toY = -1;
	int f = -1;

	switch(tpos){
	case kUserMe:
		toX = (float)CARD_C_ME->count() * w_card + left_chi_me;
		toY = bottom_chi_me;
		f = kUserMe;
		break;
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
		toX = (float)CARD_C_TOP->count() * w_card + left_chi_top;
		toY = bottom_chi_top;
		f = kUserTop;
		break;
	default:
		break;
	}
	
	CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));
	pCard->runAction(moveTo);

	switch(f){
	case kUserMe:
		CARD_C_ME->addObject(pCard);
		break;
	case kUserLeft:
		CARD_C_LEFT->addObject(pCard);
		break;
	case kUserRight:
		CARD_C_RIGHT->addObject(pCard);
		break;
	case kUserTop:
		CARD_C_TOP->addObject(pCard);
		break;
	default:
		break;
	}

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
			CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp((float)CARD_C_ME->count()*w_card+left_chi_me, bottom_chi_me));
			CCActionInterval *rotateTo = CCRotateBy::create(0.4, rotate);
			CCActionInterval *scaleBy = CCScaleBy::create(0.4, w_card/w_cardhand,h_card/h_cardhand);
			pCard->runAction(moveTo);
			pCard->runAction(rotateTo);
			pCard->runAction(scaleBy);
			CARD_ME->removeObject(pCard);
			CARD_C_ME->addObject(pCard);
			this->refreshListCard();
		}
	}
}
//Người khác đánh
void LayerChanGame::action_DanhBai_NOTME(int pos,string cardnu,string cardsu){
	CCLOG("Người khác đánh bài");
	CardChan* pCard = CardChan::create();
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setSizeCard(w_card, h_card);
	pCard->setTouchEnabled(false);

	float toX = -1;
	float toY = -1;
	int f = -1;
	switch (pos) {
	case kUserLeft:
		pCard->setPosition(ccp(33, 171));
		toX = (float)CARD_C_LEFT->count() * w_card + left_chi_left;
		toY = bottom_chi_left;
		f = kUserLeft;
		break;
	case kUserRight:
		pCard->setPosition(ccp(732, 171));
		toX =left_chi_right - (float)CARD_C_RIGHT->count() * w_card;
		toY = bottom_chi_right;
		f = kUserRight;
		break;
	case kUserTop:
		pCard->setPosition(ccp(33, 171));
		toX = (float)CARD_C_TOP->count() * w_card + left_chi_top;
		toY = bottom_chi_top;
		f = kUserRight;
		break;
	default:
		break;
	}
	uLayer->addChild(pCard);
	CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp(toX,toY));
	pCard->runAction(moveTo);
	switch (f) {
	case kUserLeft:
		CARD_C_LEFT->addObject(pCard);
		break;
	case kUserRight:
		CARD_C_RIGHT->addObject(pCard);
		break;
	case kUserTop:
		CARD_C_TOP->addObject(pCard);
		break;
	default:
		break;
	}
}

//Chuyển bài từ trên tay xuống dưới tay
void LayerChanGame::action_ChuyenBai(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Chuyển bài từ trên xuống dưới tay");
	int pos = getPosUserByName(t_user, _list_user);
	if (strcmp(t_user.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
		action_ChuyenBai_ME(pos,cardnu,cardsu);
	}else{
		action_ChuyenBai_NOTME(pos,cardnu,cardsu);
	}
}

void LayerChanGame::action_ChuyenBai_ME(int pos, string cardnu, string cardsu){
	CCObject *t;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *pCard =  dynamic_cast<CardChan*>(t);
		if (pCard->getFlag() && pCard->getNumber() == atoi(cardnu.c_str()) && pCard->getSuite() == atoi(cardsu.c_str())) {

			float rotate = -(pCard->getRotation());
			CCActionInterval *moveTo = CCMoveTo::create(0.4, ccp(CARD_D_ME_bottom->count()*w_card+left_d_me, bottom_d_me));
			CCActionInterval *rotateTo = CCRotateBy::create(0.4, rotate);
			CCActionInterval *scaleBy = CCScaleBy::create(0.4, w_card/w_cardhand,h_card/h_cardhand);

			CCLOG("zOrder card hand: %d",pCard->getZOrder());
			pCard->runAction(moveTo);
			pCard->runAction(rotateTo);
			pCard->runAction(scaleBy);

			CARD_ME->removeObject(pCard);
			CARD_D_ME_bottom->addObject(pCard);
			this->refreshListCard();
		}
	}
}

void LayerChanGame::action_ChuyenBai_NOTME(int pos, string cardnu, string cardsu){
	CardChan *pCard = CardChan::create();
	pCard->loadTexture(findTypeCard(cardnu, cardsu).c_str());
	pCard->setZOrder(_coutZorder);
	_coutZorder++;
	pCard->setSizeCard(w_card, h_card);

	float toX = -1;
	float toY = -1;
	int f = -1;

	switch (pos) {
	case kUserLeft:
		pCard->setPosition(ccp(layerAvatars->getUserByPos(kUserLeft)->getPosition().x, layerAvatars->getUserByPos(kUserLeft)->getPosition().y));
		toX = (float)CARD_D_LEFT_bottom->count() * w_card + left_d_left;
		toY = bottom_d_left - 25;
		f = kUserLeft;
		break;
	case kUserRight:
		pCard->setPosition(ccp(layerAvatars->getUserByPos(kUserRight)->getPosition().x, layerAvatars->getUserByPos(kUserRight)->getPosition().y));
		toX = left_d_right - (float)CARD_D_RIGHT_bottom->count() * w_card;
		toY = bottom_d_right - 25;
		f = kUserRight;
		break;
	case kUserTop:
		pCard->setPosition(ccp(layerAvatars->getUserByPos(kUserTop)->getPosition().x, layerAvatars->getUserByPos(kUserTop)->getPosition().y));
		toX = (float)CARD_D_TOP_bottom->count() * w_card + left_d_top;
		toY = bottom_d_top - 25;
		f = kUserTop;
		break;
	default:
		break;
	}

	uLayer->addChild(pCard);
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

void LayerChanGame::action_An_U(string f_user, string t_user, string cardnu, string cardsu){
	CCLOG("Ăn Ù");
	action_AnCuaTren(f_user,t_user,cardnu,cardsu);
}

string LayerChanGame::findTypeCard(string number,string suite){
	string str = "";
	str += number+"_"+suite+".png";
	return str;
}

//Refresh cards
void LayerChanGame::refreshListCard(){
	float countCard = (float)CARD_ME->count();
	float start = (-countCard/2)*goc;
	CCObject *t;
	int cou = 0;
	CCARRAY_FOREACH(CARD_ME, t){
		CardChan *uu = dynamic_cast<CardChan*>(t);
		float rotate =start+cou*goc;
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
		fcard = (CardChan*)CARD_C_ME->objectAtIndex(CARD_C_ME->count()-1);
		CARD_C_ME->removeObjectAtIndex(CARD_C_ME->count()-1);
		break;
	case kUserLeft:
		fcard = (CardChan*)CARD_C_LEFT->objectAtIndex(CARD_C_LEFT->count()-1);
		CARD_C_LEFT->removeObjectAtIndex(CARD_C_LEFT->count()-1);
		break;
	case kUserRight:
		fcard = (CardChan*)CARD_C_RIGHT->objectAtIndex(CARD_C_RIGHT->count()-1);
		CARD_C_RIGHT->removeObjectAtIndex(CARD_C_RIGHT->count()-1);
		break;
	case kUserTop:
		fcard = (CardChan*)CARD_C_TOP->objectAtIndex(CARD_C_TOP->count()-1);
		CARD_C_TOP->removeObjectAtIndex(CARD_C_TOP->count()-1);
		break;
	default:
		break;
	}
	return fcard;
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
					pCard->setPosition(ccp(p.x+20*sin((rotate*PI)/180),p.y+20*cos((rotate*PI)/180)));
					pCard->setFlag(true);
				}else{
					pCard->setPosition(ccp(400, 80));
					pCard->setFlag(false);
				}
			}
			else{
				pCard->setPosition(ccp(400, 80));
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
		btnEate->setTouchEnabled(false);
		btnEate->setVisible(false);
		btnBoc->setVisible(false);
		btnBoc->setTouchEnabled(false);
		btnDuoi->setTouchEnabled(false);
		btnDuoi->setVisible(false);
	}else{
		CCLOG("Ăn không đúng Chắn, Cạ");
	}
}

// set current player
void LayerChanGame::setCurrentPlayer(string uid,int _count){
	layerAvatars->stopAllTimer();
	if (strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0) {
		btnReady->setTouchEnabled(false);
		btnReady->setVisible(false);
		btnTake->setVisible(true);
		btnTake->setTouchEnabled(true);
		if (_count == 0) {
			btnEate->setTouchEnabled(false);
			btnEate->setVisible(false);
			btnBoc->setVisible(false);
			btnBoc->setTouchEnabled(false);
		}else{
			btnEate->setPosition(btnDuoi->getPosition());
			btnEate->setTouchEnabled(true);
			btnEate->setVisible(true);
			btnBoc->setVisible(true);
			btnBoc->setTouchEnabled(true);
		}
	}
	else{
		btnTake->setVisible(false);
		btnTake->setTouchEnabled(false);
		btnEate->setTouchEnabled(false);
		btnEate->setVisible(false);
		btnBoc->setVisible(false);
		btnBoc->setTouchEnabled(false);
		btnDuoi->setVisible(false);
		btnDuoi->setTouchEnabled(false);
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
		btnReady->setTouchEnabled(false);
		btnReady->setVisible(false);
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
	switch(t){
	case ANBAO_REASON_NO_PROBLEM:
		break;
	case ANBAO_REASON_AN_CA_DOI_CHO:
		CCLOG("Lỗi ăn báo: Ăn cạ đổi chờ");
		break;
	case ANBAO_REASON_BO_AN_CUATREN_BUT_AN_CUATRI:
		CCLOG("Lỗi ăn báo: không ăn cửa trên nhưng lại ăn cửa trì");
		break;
	case ANBAO_REASON_DISCARD_SAMEAS_CUATREN_CUATRI_DUOITAY:
		CCLOG("Lỗi ăn báo: Đánh đi 1 con đã có ở cửa trên, cửa trì hoặc dưới tay");
		break;
	case ANBAO_REASON_ANCA_DANHCA:
		CCLOG("Lỗi ăn báo: Ăn cạ đánh cạ");
		break;
	case ANBAO_TREOTRANH:
		CCLOG("Lỗi ăn báo: Treo tranh");
		break;
	case ANBAO_DANH_1_CA_CHI_DUOC_AN_CHAN:
		CCLOG("Lỗi ăn báo: Đã đánh cạ đi thì chỉ được Ăn chắn");
		break;
	case ANBAO_REASON_BOCHAN_ANCA:
		CCLOG("Lỗi ăn báo: Bỏ Chắn ăn cạ");
		break;
	case ANBAO_REASON_DANHBAI_GIONG_CHANCA_DA_AN:
		CCLOG("Lỗi ăn báo: Đánh đi lá bài giống chắn hoặc Cạ đã ăn");
		break;
	case ANBAO_REASON_DOI_U_BACHTHUCHI:
		CCLOG("Lỗi ăn báo: Đợi Ăn Ù Bạch thủ Chi");
		break;
	case ANBAO_REASON_BOCHAN_DANHCHAN:
		CCLOG("Lỗi ăn báo: Bỏ Chắn đánh chắn");
		break;
	case ANBAO_REASON_BOCHAN_ANCHAN:
		CCLOG("Lỗi ăn báo: Bỏ Chắn Ăn Chắn");
		break;
	case ANBAO_REASON_BOCA_ANCA:
		CCLOG("Lỗi ăn báo: Bỏ Chắn Ăn Cạ");
		break;
	case ANBAO_REASON_DANHCA_ANCA:
		CCLOG("Lỗi ăn báo: Đánh Cạ Ăn Cạ");
		break;
	case ANBAO_REASON_XECA_ANCA:
		CCLOG("Lỗi ăn báo: Xé cạ Ăn Cạ");
		break;
	case ANBAO_REASON_XECHAN_ANCA:
		CCLOG("Lỗi ăn báo: Xé Chắn Ăn Cạ");
		break;
	case ANBAO_REASON_DANH_ROILAI_AN:
		CCLOG("Lỗi ăn báo: Đánh đi 1 con sau lại ăn đúng con đó");
		break;
	case ANBAO_REASON_DANH_DI_DOI_CHAN:
		CCLOG("Lỗi ăn báo: Đánh đi cả đôi Chắn");
		break;
	case ANBAO_REASON_AN_ROILAI_DANH:
		CCLOG("Lỗi ăn báo: Ăn một con rồi lại đánh đi con đó");
		break;
	case ANBAO_REASON_ANCA_ROILAI_DANH_QUAN_CUNG_HANG:
		CCLOG("Lỗi ăn báo: Ăn cạ rồi lại đánh 1 con cùng hàng");
		break;
	case ANBAO_REASON_CHIUDUOC_NHUNG_LAI_ANTHUONG:
		CCLOG("Lỗi ăn báo: Chíu được nhưng lại ăn thường");
		break;
	case ANBAO_REASON_AN_CHON_CA:
		CCLOG("Lỗi ăn báo: Ăn cạ Chọn Cạ");
		break;
	case ANBAO_REASON_CO_CHAN_CAU_CA:
		CCLOG("Lỗi ăn báo: có Chắn Cấu Cạ");
		break;
	}
}

//Khi co nguoi cho U
void LayerChanGame::whenConguoi_ChoU(string uid){
	string myName = "";
	myName = GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str();

	if(strcmp(uid.c_str(),myName.c_str()) == 0){
		// Hiển thị button Ù
		btnU->setVisible(true);
		btnU->setTouchEnabled(true);
		if(strcmp(myName.c_str(),currentPlayer.c_str()) == 0)
		{
			
		}
		else
		{
			btnEate->setVisible(true);
			btnEate->setTouchEnabled(true);
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
		btnChiu->setVisible(true);
		btnChiu->setTouchEnabled(true);
	}
	else
	{
		if(strcmp(myName.c_str(),currentPlayer.c_str()) == 0){
			hideAllButton();
		}
	}
}

//set End Game
void LayerChanGame::setEndGame(){
	currentPlayer = "";
	mylistCard = "";

	flagChiaBai = false;
	countDiscard = 0;
	_coutZorder = 0;

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

	btnBoc->setVisible(false);
	btnBoc->setTouchEnabled(false);
	btnDuoi->setTouchEnabled(false);
	btnDuoi->setVisible(false);
	btnEate->setVisible(false);
	btnEate->setTouchEnabled(false);
	btnTake->setTouchEnabled(false);
	btnTake->setVisible(false);

	btnReady->setTouchEnabled(true);
	btnReady->setVisible(true);
}

void LayerChanGame::deleteAllCardFromArray(CCArray *P){
	while(P->count()>0){
		CardChan *uu = (CardChan*)P->objectAtIndex(P->count()-1);
		P->removeObject(uu);
		uu->removeFromParentAndCleanup(true);
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
	btnReady->setVisible(false);
	btnReady->setTouchEnabled(false);

	btnEate->setVisible(false);
	btnEate->setTouchEnabled(false);

	btnBoc->setVisible(false);
	btnBoc->setTouchEnabled(false);

	btnDuoi->setVisible(false);
	btnDuoi->setTouchEnabled(false);

	btnTake->setVisible(false);
	btnTake->setTouchEnabled(false);

	btnChiu->setVisible(false);
	btnChiu->setTouchEnabled(false);

	btnU->setVisible(false);
	btnU->setTouchEnabled(false);
}
void LayerChanGame::resetPositionButton(){

}