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
#include "LayerGameChan_XuongU2.h"
#include "SliderCustomLoader.h"
#include "SceneManager.h"
#include "LayerGameChan_KetQua.h"
#include "Layer_GivePocker_Chan.h"
#include "AllData.h"

#include "LayerChanToast.h"

#define kTag_layerGive 200
#define PI 3.141592653589
#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())

LayerChanGame::LayerChanGame(){
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

	EXT_SRVNTF_BOC_CAI = "ntfbocc";
	EXT_EVENT_REQ_BOC_CAI = "rqbocc";

	_list_user = "";
	mylistCard = "";
	currentPlayer = "";

	countBocCai = 0;
	countDiscard = 0;
	countUser = 0;
	_noccount = -1;

	flagChiaBai = false;
	flagTraCuaToMe = false;
	flag_MeDraw = false;
	flag_AnBao = false;

	reason_anbao = "";

	flag_Top = false;
	flag_Bottom = false;
	flag_Left = false;
	flag_Right = false;

	createAvatars();
	createCards();
	createButtons();
	

	lblDetail = UILabel::create();
	lblDetail->setText("");
	lblDetail->setFontSize(20);
	lblDetail->setAnchorPoint(ccp(0, 0));
	lblDetail->setPosition(ccp(20, HEIGHT_DESIGN-lblDetail->getContentSize().height - 30));
	lblDetail->setColor(ccRED);
	this->addChild(lblDetail);

	GameServer::getSingleton().addListeners(this);
	this->scheduleOnce(schedule_selector(LayerChanGame::sendRequestJoinGame),1.0f);

	SceneManager::getSingleton().hideLoading();
}

vector<string> LayerChanGame::splitString(string &S,const char &str){
	vector<string> arrStr;
	string::iterator t,t2;
	for(t=S.begin();t<S.end();){
		// Lặp từ vị trí bắt đầu
		t2=find(t, S.end(),str); // Tìm vị trí space ' ' đầu tiên
		//kể từ vị trí t
		if(t!=t2)
			arrStr.push_back(string(t,t2));
		else  if( t2 != S.end() )
			arrStr.push_back("");
		if( t2 == S.end() )
			break;
		t=t2+1; // chuyển sang vị trí sau
	}
	return arrStr;
}

void LayerChanGame::displayLayerKetQua(string resuilt){
	LayerGameChan_KetQua *kq = LayerGameChan_KetQua::create();
	kq->setTag(171);
	kq->displayResuilt(resuilt);
	this->addChild(kq);
}

LayerChanGame::~LayerChanGame(){
	GameServer::getSingleton().removeListeners(this);
}

void LayerChanGame::onExit()
{
	CCLOG("Deconstructor Game Chan");
	LayerChanToast::resetStaticVariables();
	SceneManager::getSingleton().setBackgroundScreen(false);
	GameServer::getSingleton().removeListeners(this);
}

void LayerChanGame::createAvatars(){

	//w : h = 0.72
	float width_Ava = 90;
	float height_Ava = 125;

	layerAvatars = LayerAvatarInGame::create();
	layerAvatars->resetAll();
	layerAvatars->getUserByPos(kUserMe)->setVisible(false);
	layerAvatars->getUserByPos(kUserBot)->setVisible(true);
	//layerAvatars->getUserByPos(kUserBot)->setPositionY(-200);
	layerAvatars->getUserByPos(kUserBot)->setTouchEnabled(false);

	CCSize oldSize = layerAvatars->getUserByPos(kUserRight)->getSizeThis();

	layerAvatars->getUserByPos(kUserBot)->setScaleX(width_Ava / oldSize.width);
	layerAvatars->getUserByPos(kUserBot)->setScaleY(height_Ava / oldSize.height);

	layerAvatars->getUserByPos(kUserLeft)->setScaleX(width_Ava / oldSize.width);
	layerAvatars->getUserByPos(kUserLeft)->setScaleY(height_Ava / oldSize.height);
	layerAvatars->getUserByPos(kUserLeft)->setPosition(ccp(10, HEIGHT_DESIGN / 2 - height_Ava / 2 + 30));

	layerAvatars->getUserByPos(kUserRight)->setScaleX(width_Ava / oldSize.width);
	layerAvatars->getUserByPos(kUserRight)->setScaleY(height_Ava / oldSize.height);
	layerAvatars->getUserByPos(kUserRight)->setPosition(ccp(WIDTH_DESIGN - width_Ava - 10, HEIGHT_DESIGN / 2 - height_Ava / 2 + 30));

	layerAvatars->getUserByPos(kUserTop)->setScaleX(width_Ava / oldSize.width);
	layerAvatars->getUserByPos(kUserTop)->setScaleY(height_Ava / oldSize.height);
	layerAvatars->getUserByPos(kUserTop)->setPosition(ccp(WIDTH_DESIGN / 2 - width_Ava / 2, HEIGHT_DESIGN - height_Ava - 10));

	this->addChild(layerAvatars);
}

void LayerChanGame::createCards(){
	layerCardChan = _Layer_CardChan_::create(); 
	this->addChild(layerCardChan);
}

void LayerChanGame::createButtons(){
	layerButtons = LayerButtonInGame::create();
	layerButtons->hideButtonInChanGame();
	this->addChild(layerButtons);

	CCSprite * time = CCSprite::create("timerme.png");
	timer_Me = CCProgressTimer::create(time);
	timer_Me->setAnchorPoint(ccp(0.5,0));
	timer_Me->setType(kCCProgressTimerTypeRadial);
	timer_Me->setPosition(ccp(WIDTH_DESIGN/2, 3.5));
	this->addChild(timer_Me);

	int w_Button = 129;
	int h_Button = 44;
	int _space = 20;

	Button *btnReady = createButtonWithTitle_Pos("Sẵn Sàng",ccp(WIDTH_DESIGN - w_Button - _space, _space));
	Button *btnBoc = createButton_Chan("Bốc",ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2 + 5),"U.png","U_press.png",-1);

	Button *btnEate = createButton_Chan("Ăn", ccp(WIDTH_DESIGN/ 2, 60), "an.png", "an_press.png", -1);
	Button *btnU = createButton_Chan("Ù", ccp(WIDTH_DESIGN/ 2, 10), "U.png", "U_press.png", -1);
	Button *btnChiu = createButton_Chan("Chíu", ccp(WIDTH_DESIGN / 2 - btnU->getContentSize().width / 2 - 75 / 2 + 9, 7), "chiu.png", "chiu_press.png", 1);
	Button *btnTake = createButton_Chan("Đánh", ccp(WIDTH_DESIGN / 2 + btnU->getContentSize().width / 2 + 75 / 2 - 9, 7), "danh.png", "danh_press.png", 2);
	Button *btnDuoi = createButton_Chan("Dưới", ccp(WIDTH_DESIGN / 2 + btnU->getContentSize().width / 2 + 75 / 2 - 9, 7), "danh.png", "danh_press.png", 2);

	btnReady->setEnabled(true);
	btnBoc->setEnabled(false);

	btnEate->setEnabled(false);
	btnU->setEnabled(false);
	btnChiu->setEnabled(false);
	btnTake->setEnabled(false);
	btnDuoi->setEnabled(false);

	btnReady->setTag(cTag_btnReady);
	btnBoc->setTag(cTag_btnBoc);

	btnEate->setTag(cTag_btnEate);
	btnU->setTag(cTag_btnU);
	btnChiu->setTag(cTag_btnChiu);
	btnTake->setTag(cTag_btnTake);
	btnDuoi->setTag(cTag_btnDuoi);

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

void LayerChanGame::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	this->param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
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
			
			layerCardChan->resetAllCards();
			layerAvatars->stopAllTimer();
			hideAllButton();
			getButtonByTag(cTag_btnU)->setEnabled(false);
			getButtonByTag(cTag_btnChiu)->setEnabled(false);

			updateUser(_list_user);
			CCLOG("List user update: %s",_list_user.c_str());
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
		CCLOG("user ready: %s",_user.c_str());
		CCLOG("EXT_SRVNTF_USER_READY");
	}

	//Bốc cái
	else if (strcmp(EXT_SRVNTF_BOC_CAI.c_str(), cmd->c_str()) == 0)
	{
		eventBocCai();
	}

	else if (strcmp(EXT_EVENT_START.c_str(), cmd->c_str()) == 0)
	{
		eventGameStart();
	}

	else if(strcmp(EXT_EVENT_LISTCARD_NTF.c_str(), cmd->c_str()) == 0)
	{
		eventListCard();
	}

	//noc count
	else if (strcmp(EXT_SRVNTF_NOC_COUNT.c_str(), cmd->c_str()) == 0){
		boost::shared_ptr<long> noccount = param->GetInt("noccount");
		if (noccount != NULL) {
			CCLOG("noc count: %ld",*noccount);
			_noccount = (int)*noccount;
			layerCardChan->setCountNoc((int)_noccount);
			
			if (_noccount == 0)
			{
				getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
				getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

				getButtonByTag(cTag_btnChiu)->loadTextureNormal("chiu_Disable.png");
				getButtonByTag(cTag_btnChiu)->setTouchEnabled(false);

				getButtonByTag(cTag_btnDuoi)->loadTextureNormal("danh_Disable.png");
				getButtonByTag(cTag_btnDuoi)->setTouchEnabled(false);

				getButtonByTag(cTag_btnTake)->loadTextureNormal("danh_Disable.png");
				getButtonByTag(cTag_btnTake)->setTouchEnabled(false);

				getButtonByTag(cTag_btnEate)->loadTextureNormal("an_Disable.png");
				getButtonByTag(cTag_btnEate)->setTouchEnabled(false);

				LayerChanToast::showToast(this, "Đã bốc hết nọc, đợi xem có nhà nào báo Ù không !", 4);

				layerAvatars->stopAllTimer();
				stopTimer_Me();
			}
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
			vector<string> detail = mUtils::splitString(_ohdetl, ':');
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
				if (_noccount == 0)
				{
					return;
				}
				getButtonByTag(cTag_btnTake)->setEnabled(false);

				getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
				getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

				getButtonByTag(cTag_btnEate)->loadTextureNormal("an.png");
				getButtonByTag(cTag_btnEate)->setTouchEnabled(true);

				getButtonByTag(cTag_btnDuoi)->loadTextureNormal("danh.png");
				getButtonByTag(cTag_btnDuoi)->setEnabled(true);
				getButtonByTag(cTag_btnDuoi)->setTouchEnabled(true);
			}
		}
		CCLOG("EXT_EVENT_RES_DRAW_CARD");
	}

	//dưới card
	else if(strcmp(EXT_EVENT_RES_DUOI_CARD.c_str(), cmd->c_str()) == 0){
		boost::shared_ptr<long> rescode = param->GetInt("rscode");
		if (rescode != NULL) {
			CCLOG("duoi rescode = %d",*rescode);
			if(*rescode == 0){
				flagTraCuaToMe = false;
			}
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

		eventTakeCards(_f_user, _t_user, _cardnu, _cardsu, _crdorg);
		CCLOG("EXT_SRVNTF_CARD_ORIGINATION");
	}

	//An bao
	else if (strcmp(EXT_SRVNTF_ANBAO.c_str(),cmd->c_str())==0){
		boost::shared_ptr<long> anbaores = param->GetInt("anbaores");
		boost::shared_ptr<string> usrn = param->GetUtfString("usrn");

		if (anbaores != NULL && usrn != NULL) {
			CCLOG("resuilt code %ld", *anbaores);
			error_AnBao(*anbaores, usrn->c_str());
			//usrn
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
		CCLOG("Chiu thanh cong ! current user %s",currentPlayer.c_str());
		//Nếu mình là người chíu mình sẽ nhận được bản tin này.
		boost::shared_ptr<long> rscode = param->GetInt("rscode");
		if (rscode != NULL)
		{
			if (*rscode == 0)
			{
				getButtonByTag(cTag_btnDuoi)->setEnabled(false);

				getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
				getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

				getButtonByTag(cTag_btnEate)->loadTextureNormal("an_Disable.png");
				getButtonByTag(cTag_btnEate)->setTouchEnabled(false);

				getButtonByTag(cTag_btnTake)->loadTextureNormal("danh.png");
				getButtonByTag(cTag_btnTake)->setEnabled(true);
				getButtonByTag(cTag_btnTake)->setTouchEnabled(true);

				layerCardChan->refreshListCard();
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

			}

		}

	}

	//Bao co the u
	else if (strcmp(EXT_SRVNTF_ONE_EXPECTING_U.c_str(), cmd->c_str()) == 0){
		eventOne_ExpectingU();
	}

	//Danh bai
	else if (strcmp(EXT_EVENT_RES_DISCARD.c_str(), cmd->c_str()) == 0)
	{
		eventDisCards();
	}

	//Bài trên tay người Ù
	else if (strcmp("ntfttdetl", cmd->c_str()) == 0)
	{
		eventCard_NguoiU();
	}

	//Bài còn trong nọc
	else if(strcmp("ntfnocdetl", cmd->c_str()) == 0)
	{
		eventCard_ConTrongNoc();
	}

	else if (strcmp(EXT_EVENT_GAME_RESULT.c_str(),cmd->c_str()) == 0)
	{
		eventGameResuilt();
	}

	else if (strcmp(EXT_EVENT_END.c_str(), cmd->c_str()) == 0)
	{
		eventGameEnd();
	}

	else if(strcmp("rntf",cmd->c_str()) == 0){
		layerAvatars->stopAllBlinkAvatar();
		if (this->getChildByTag(172) != NULL)
		{
			this->removeChildByTag(172);
		}
	}
}//end extensions

void LayerChanGame::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLOG("user variables update !");
}

void LayerChanGame::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLOG("message from user !");
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

void LayerChanGame::eventGameStart(){
	layerAvatars->setUnReadyAllUser();
	CCLOG("EXT_EVENT_START");
}

void LayerChanGame::eventGameEnd(){
	countBocCai = 0;
	flag_AnBao = false;
	reason_anbao = "";
	stopTimer_Me();
	this->runAction(CCSequence::create(CCDelayTime::create(7), CCCallFunc::create(this, callfunc_selector(LayerChanGame::setEndGame)), NULL));
	CCLOG("EXT_EVENT_END");
}

void LayerChanGame::eventGameResuilt(){
	boost::shared_ptr<string> rg = param->GetUtfString("rg");
	if( rg != NULL){
		CCLOG("Resuilt game: %s",rg->c_str());
		layerAvatars->stopAllTimer();
		resuiltGame(rg->c_str());
	}

	CCLOG("EXT_EVENT_GAME_RESULT");
}

void LayerChanGame::eventBocCai(){
	LayerChanToast::resetStaticVariables();
	boost::shared_ptr<string> usrn = param->GetUtfString("usrn");
	if (usrn != NULL)
	{
		countBocCai++;
		if(countBocCai == 1)
		{
			getButtonByTag(cTag_btnReady)->setEnabled(false);

			Layer_GivePocker_Chan *layerGive = Layer_GivePocker_Chan::create();
			bool iBoc = false;
			if (strcmp(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(), usrn->c_str()) == 0)
			{
				iBoc = true;
			}
			layerGive->setIsPlayerBocCai(iBoc);
			layerGive->setPlayerBocCai(usrn->c_str());
			layerGive->setListusers(_list_user);
			layerGive->setTag(kTag_layerGive);
			this->addChild(layerGive);
			layerGive->startGivePocker();
		}
	}
	CCLOG("EXT_SRVNTF_BOC_CAI");
}

void LayerChanGame::eventListCard(){
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

	CCLog("uid: %s, listcards: %s", _usrn.c_str(), _lc.c_str());
	vector<string> str = mUtils::splitString(_lc,'/');
	for (int i = 0; i < str.size(); i++)
	{
		CCLog("%d : %s", i, str.at(i).c_str());
	}
	if (IamGuess())
	{
		int pos = getPosUserByName_ImGuess(_usrn);
		if (pos == -1)
		{
			return;
		}
		if (countUser == 2)
		{
			if (pos != kUserBot)
			{
				pos = kUserTop;
			}
		}
		layerCardChan->createOrRestoreListCards(pos, _lc);
	}
	else
	{
		if (!flagChiaBai) {
			if (strcmp(_usrn.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0) {
				CCString *p = CCString::create(_lc);
				CCCallFuncO *callfun = CCCallFuncO::create(this, callfuncO_selector(LayerChanGame::delayListCardFirst),p);
				CCDelayTime *delay = CCDelayTime::create(0.9);
				this->runAction(CCSequence::create(delay, callfun, NULL));
				flagChiaBai = true;
			}
		}
		else
		{
			if (strcmp(_usrn.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0) {
				mylistCard = mUtils::splitString(_lc, '/')[0];
				if (mylistCard != "") {
					layerCardChan->sortMyListCards(mylistCard);
				}
			}
		}
	}
}

void LayerChanGame::delayListCardFirst(CCObject *data){
	layerAvatars->getUserByPos(kUserBot)->setPositionY(-200);

	CCString *resuilt = (CCString *) data;
	string _lc = string(resuilt->getCString());

	if (this->getChildByTag(kTag_layerGive) != NULL)
	{
		this->removeChildByTag(kTag_layerGive);
	}

	layerCardChan->setMyListCards(_lc);
	getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
	getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);
	getButtonByTag(cTag_btnBoc)->setEnabled(true);

	getButtonByTag(cTag_btnU)->setEnabled(true);

	getButtonByTag(cTag_btnChiu)->loadTextureNormal("chiu_Disable.png");
	getButtonByTag(cTag_btnChiu)->setTouchEnabled(false);
	getButtonByTag(cTag_btnChiu)->setEnabled(flag_AnBao ? false : true);

	getButtonByTag(cTag_btnEate)->loadTextureNormal("an_Disable.png");
	getButtonByTag(cTag_btnEate)->setTouchEnabled(false);
	getButtonByTag(cTag_btnEate)->setEnabled(true);

	getButtonByTag(cTag_btnTake)->loadTextureNormal("danh_Disable.png");
	getButtonByTag(cTag_btnTake)->setTouchEnabled(false);
	getButtonByTag(cTag_btnTake)->setEnabled(true);
}

void LayerChanGame::eventDisCards(){
	boost::shared_ptr<long> rscode = param->GetInt("rscode");
	if (rscode != NULL) {
		if (*rscode != 0) {
			CCLOG("Không đánh được !");
		}
		else
		{
			flagTraCuaToMe = false;
		}
	}
	CCLOG("EXT_EVENT_RES_DISCARD");
}

void LayerChanGame::eventOne_ExpectingU(){
	boost::shared_ptr<string> usrn = param->GetUtfString("usrn");
	if (usrn != NULL) {
		whenConguoi_ChoU(usrn->c_str());
		CCLOG("nguoi cho U: %s",usrn->c_str());
	}
	CCLOG("EXT_SRVNTF_ONE_EXPECTING_U");
}

void LayerChanGame::eventCard_NguoiU(){
	boost::shared_ptr<string> usrn = param->GetUtfString("usrn");
	boost::shared_ptr<string> lc = param->GetUtfString("lc");

	if (usrn == NULL || lc == NULL)
	{
		return;
	}

	if (strcmp(usrn->c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) != 0)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/Chan/uroi.mp3");
		waitPlayer_ReqU(usrn->c_str(), lc->c_str());
	} else {
		hideAllButton();
		getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
		getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);
		getButtonByTag(cTag_btnBoc)->setEnabled(true);

		getButtonByTag(cTag_btnU)->setEnabled(false);
		getButtonByTag(cTag_btnChiu)->setEnabled(false);
		LayerChanToast::showToast(this, "Bạn đã báo Ù lá bài này, đợi xem có nhà nào báo ù nữa không !", 4);
		this->runAction(CCSequence::create(CCDelayTime::create(6.0),CCCallFunc::create(this, callfunc_selector(LayerChanGame::XuongU)),NULL));
	}
}

void LayerChanGame::eventCard_ConTrongNoc(){
	boost::shared_ptr<string> nocdetl = param->GetUtfString("nocdetl");
	if (nocdetl != NULL)
	{
		stopTimer_Me();
		CCLOG("Các lá bài còn trong nọc: %s", nocdetl->c_str());
		layerCardChan->setListNoc(nocdetl->c_str());
		getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
		getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

		getButtonByTag(cTag_btnTake)->loadTextureNormal("danh_Disable.png");
		getButtonByTag(cTag_btnTake)->setTouchEnabled(false);

		getButtonByTag(cTag_btnDuoi)->loadTextureNormal("danh_Disable.png");
		getButtonByTag(cTag_btnDuoi)->setTouchEnabled(false);

		getButtonByTag(cTag_btnChiu)->loadTextureNormal("chiu_Disable.png");
		getButtonByTag(cTag_btnChiu)->setTouchEnabled(false);

		getButtonByTag(cTag_btnEate)->loadTextureNormal("an_Disable.png");
		getButtonByTag(cTag_btnEate)->setTouchEnabled(false);
	}
}

// tìm vị trí người chơi so với mình
int LayerChanGame::getPosUserByName(string uid,string _list_user){
	int vt = -1;
	vector<string> list;
	if(_list_user.c_str() != NULL && _list_user != ""){
		list = mUtils::splitString(_list_user, ';');
	}

	for(int i = 0; i < list.size(); i++){
		string _id = mUtils::splitString(list[i], ':')[1];
		
		if(strcmp(_id.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
			vt = i;
			break;
		}
	}

	for(int k = 0; k < list.size(); k++){
		if(strcmp(list[k].c_str(), "")==0)
			continue;
		string player = list[k];
		vector<string> n = mUtils::splitString(player, ':');
		if(strcmp(n[1].c_str(), uid.c_str()) == 0){
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

	return -1;
}

int LayerChanGame::getPosUserByName_ImGuess(string uid){
	vector<string> list;
	if(_list_user.c_str() != NULL && _list_user != ""){
		list = mUtils::splitString(_list_user, ';');
	}

	for(int k = 0; k < list.size(); k++){
		if(strcmp(list[k].c_str(), "") == 0)
			continue;
		string player = list[k];
		vector<string> n = mUtils::splitString(player, ':');
		if(strcmp(n[1].c_str(), uid.c_str()) == 0){
			switch(k){
			case 0:
				return kUserBot;
			case 1:
				return kUserRight;
			case 2:
				return kUserTop;
			case 3:
				return kUserLeft;
			default:
				return -1;
			}
		}
	}
	return -1;
}

string LayerChanGame::getNamePlayer(string uid){
	boost::shared_ptr<Room> room = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	if (room == NULL)
	{
		return uid;
	}
	boost::shared_ptr<User> user = room->GetUserByName(uid);
	if (user == NULL)
	{
		return uid;
	}
	boost::shared_ptr<string> name = user->GetVariable("aN")->GetStringValue();
	return name->c_str();
}

//Update list users
void LayerChanGame::updateUser(string list){
	//31:dautv:1;27:dautv3:0
	layerAvatars->resetAll();
	vector<string> listUser;
	listUser = mUtils::splitString(list, ';');
	countUser = listUser.size();

	if(countUser == 2){
		updateUser2Player(listUser);
	}
	else
	{
		if (IamGuess() == true)
		{
			updateUser_ImGuess();
		}
		else
		{
			updateUser_ImPlayer();
		}
	}
}

//Update list user nếu mình là khách xem
void LayerChanGame::updateUser_ImGuess(){
	getButtonByTag(cTag_btnReady)->setEnabled(false);
	boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	vector<string> listUser;
	listUser = mUtils::splitString(_list_user, ';');
	for (int i = 0; i < listUser.size(); i++)
	{
		if (lastRoom == NULL)
		{
			return;
		}
		vector<string> info = mUtils::splitString(listUser[i], ':');
		if(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1]) == NULL){
			continue;
		}
		int _money = 0;
		string _name = "";
		string _url = "";

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1])->GetVariable("amf")->GetDoubleValue();
		boost::shared_ptr<string> url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1])->GetVariable("aal")->GetStringValue();

		if (name != NULL) {
			_name = name->c_str();
		}
		if(money != NULL){
			_money = (int)(*money);
		}
		if(url != NULL){
			_url = url->c_str();
		}
		int pos = getPosUserByName_ImGuess(info[1]);
		if (pos != -1)
		{
			setInfoAvatar(pos, info[1], _name, _money, _url);
		}
	}
}

//update list user nếu mình là người chơi
void LayerChanGame::updateUser_ImPlayer(){
	vector<string> listUser;
	listUser = mUtils::splitString(_list_user, ';');
	boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	for (int i = 0; i < listUser.size(); i++)
	{
		if(lastRoom == NULL){
			return;
		}
		if(listUser[i].c_str() == NULL)
			continue;
		string player = listUser[i];
		vector<string> n = mUtils::splitString(player, ':');

		if(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1]) == NULL){
			continue;
		}

		int _money = 0;
		string _name = "";
		string _url = "";

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("amf")->GetDoubleValue();
		boost::shared_ptr<string> url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("aal")->GetStringValue();

		if (name != NULL) {
			_name = name->c_str();
		}
		if(money != NULL){
			_money = (int)(*money);
		}
		if(url != NULL){
			_url = url->c_str();
		}

		if(strcmp(n[1].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
			if (countBocCai == 0)
			{
				getButtonByTag(cTag_btnReady)->setEnabled(true);
			}
			else
			{
				getButtonByTag(cTag_btnReady)->setEnabled(false);
			}
			setInfoAvatar(kUserBot, n[1], _name, _money, _url);			
		}
		else
		{
			switch (getPosUserByName(n[1], _list_user)) {
			case kUserLeft:
				setInfoAvatar(kUserLeft, n[1], _name, _money, _url);
				break;
			case kUserRight:
				setInfoAvatar(kUserRight, n[1], _name, _money, _url);
				break;
			case kUserTop:
				setInfoAvatar(kUserTop, n[1], _name, _money, _url);
				break;
			}
		}
	}
}

//Update list users khi chỉ có 2 người chơi
void LayerChanGame::updateUser2Player(vector<string> arrUser){
	boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	if (lastRoom == NULL)
	{
		return;
	}
	if (IamGuess() == true)
	{
		updateUser2Player_ImGuess(arrUser);
	}
	else
	{
		updateUser2Player_ImPlayer(arrUser);
	}
}

void LayerChanGame::updateUser2Player_ImGuess(vector<string> arrUser){
	getButtonByTag(cTag_btnReady)->setEnabled(false);
	for (int i = 0; i < arrUser.size(); i++)
	{
		if (strcmp(arrUser[i].c_str(), "") == 0)
		{
			continue;
		}
		vector<string> info = mUtils::splitString(arrUser[i],':');
		if(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1]) == NULL){
			continue;
		}
		int _money = 0;
		string _name = "";
		string _url = "";

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1])->GetVariable("amf")->GetDoubleValue();
		boost::shared_ptr<string> url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1])->GetVariable("aal")->GetStringValue();

		if (name != NULL) {
			_name = name->c_str();
		}
		if(money != NULL){
			_money = (int)(*money);
		}
		if(url != NULL){
			_url = url->c_str();
		}
		if (i == 0)
		{
			setInfoAvatar(kUserBot, info[1], _name, _money, _url);
		}
		else
		{
			setInfoAvatar(kUserTop, info[1], _name, _money, _url);
		}
	}
}

void LayerChanGame::updateUser2Player_ImPlayer(vector<string> arrUser){
	for (int i = 0; i < arrUser.size(); i++ )
	{
		if (strcmp(arrUser[i].c_str(),"") == 0)
		{
			continue;
		}
		vector<string> info = mUtils::splitString(arrUser[i],':');
		if(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1]) == NULL){
			continue;
		}

		int _money = 0;
		string _name = "";
		string _url = "";

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1])->GetVariable("amf")->GetDoubleValue();
		boost::shared_ptr<string> url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[1])->GetVariable("aal")->GetStringValue();

		if (name != NULL) {
			_name = name->c_str();
		}
		if(money != NULL){
			_money = (int)(*money);
		}
		if(url != NULL){
			_url = url->c_str();
		}

		int pos = getPosUserByName(info[1], _list_user);
		if (pos == kUserMe)
		{
			if (countBocCai == 0)
			{
				getButtonByTag(cTag_btnReady)->setEnabled(true);
			}
			else
			{
				getButtonByTag(cTag_btnReady)->setEnabled(false);
			}
			setInfoAvatar(kUserBot, info[1], _name, _money, _url);	
		}
		else{
			setInfoAvatar(kUserTop, info[1], _name, _money, _url);
		}
	}
}

//Check xem mình là khách hay người chơi
bool LayerChanGame::IamGuess(){
	vector<string> listUser = mUtils::splitString(_list_user, ';');
	for (int i = 0; i < listUser.size(); i++)
	{
		vector<string> info = mUtils::splitString(listUser.at(i),':');
		if (strcmp(info[1].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
		{
			return false;
		}
	}
	return true;
}

void LayerChanGame::setInfoAvatar(int pos,string aI,string name, int money, string url){
	layerAvatars->getUserByPos(pos)->setVisibleLayerInvite(false);
	layerAvatars->getUserByPos(pos)->setAI(aI);
	layerAvatars->getUserByPos(pos)->setName(name);
	layerAvatars->getUserByPos(pos)->setMoney(money);
	layerAvatars->getUserByPos(pos)->setIcon(url);
}

//Các sự kiện đánh bài của người chơi
void LayerChanGame::eventTakeCards(string f_user, string t_user, string cardnu, string cardsu, int crdorg){
	if (IamGuess() == true)
	{
		eventTakeCards_Showing(f_user, t_user, cardnu, cardsu, crdorg);
	}
	else
	{
		eventTakeCards_Playing(f_user, t_user, cardnu, cardsu, crdorg);
	}
}

//các sự kiện đánh bài nếu mình đang xem (là khách)
void LayerChanGame::eventTakeCards_Showing(string f_user, string t_user, string cardnu, string cardsu, int crdorg){
	hideAllButton();
	getButtonByTag(cTag_btnChiu)->setEnabled(false);
	getButtonByTag(cTag_btnU)->setEnabled(false);
	int fpos = getPosUserByName_ImGuess(f_user);
	int tpos = getPosUserByName_ImGuess(t_user);
	if(countUser == 2)
	{
		if (fpos != -1)
		{
			fpos = (fpos == kUserBot) ? kUserBot : kUserTop;
		}
		tpos = (tpos == kUserBot) ? kUserBot : kUserTop;
	}

	//Vẽ lại bàn chơi ở đây, trước khi có các thao tác đánh bài.
	layerCardChan->takeCards(fpos, tpos, cardnu, cardsu, crdorg);
}

//các sự kiện đánh bài nếu mình đang chơi (là người chơi)
void LayerChanGame::eventTakeCards_Playing(string f_user, string t_user, string cardnu, string cardsu, int crdorg){
	CCLOG("From user: %s, to user: %s",f_user.c_str(),t_user.c_str());
	CCLOG("count user = %d", countUser);
	int fpos = getPosUserByName(f_user, _list_user);
	int tpos = getPosUserByName(t_user, _list_user);

	if(countUser == 2){
		if (fpos != -1)
		{
			fpos = (fpos == kUserMe) ? kUserMe : kUserTop;
		}
		tpos = (tpos == kUserMe) ? kUserMe : kUserTop;
	}

	CCLOG("From %d to %d", fpos, tpos);
	layerCardChan->takeCards(fpos, tpos, cardnu, cardsu, crdorg);
	if(_noccount == 0) return;

	//Xet các trường hợp để hiển thị các Button
	if(tpos == kUserMe){
		if (crdorg == 3 || crdorg == 2)
		{
			getButtonByTag(cTag_btnDuoi)->setEnabled(false);
			getButtonByTag(cTag_btnTake)->loadTextureNormal("danh.png");
			getButtonByTag(cTag_btnTake)->setEnabled(true);
			getButtonByTag(cTag_btnTake)->setTouchEnabled(true);
		}
	}

	//Nếu người khác trả cửa vào cửa của mình
	if(crdorg == 1 || crdorg == 2 || crdorg == 3)
	{
		flagTraCuaToMe = false;
	}
	if(crdorg == 5){
		if (tpos == kUserMe)
		{
			flag_MeDraw = false;
		}
		if(fpos != kUserMe && tpos == kUserMe){
			CCLOG("Nguoi khac tra cua vao cua chi cua minh");
			flagTraCuaToMe = true;
		}
		getButtonByTag(cTag_btnChiu)->loadTextureNormal(flag_AnBao ? "chiu_Disable.png" : "chiu.png");
		getButtonByTag(cTag_btnChiu)->setTouchEnabled(!flag_AnBao);
	}

	//Khi có người đánh bài
	if(crdorg == 6){
		if (fpos == kUserMe)
		{
			getButtonByTag(cTag_btnChiu)->loadTextureNormal("chiu_Disable.png");
			getButtonByTag(cTag_btnChiu)->setTouchEnabled(!flag_AnBao);
			flag_MeDraw = false;
		}
		else
		{
			getButtonByTag(cTag_btnChiu)->loadTextureNormal(flag_AnBao ? "chiu_Disable.png" : "chiu.png");
			getButtonByTag(cTag_btnChiu)->setTouchEnabled(!flag_AnBao);
		}
	}

	//Khi có người Bốc bài thành công
	if (crdorg == 1)
	{
		getButtonByTag(cTag_btnChiu)->loadTextureNormal(flag_AnBao ? "chiu_Disable.png" : "chiu.png");
		getButtonByTag(cTag_btnChiu)->setTouchEnabled(!flag_AnBao);
		if (tpos == kUserMe)
		{
			flag_MeDraw = true;
		}
	}

	//Khi có 1 người Dưới bài
	if(crdorg == 7){
		if (tpos == kUserMe)
		{
			getButtonByTag(cTag_btnChiu)->loadTextureNormal("chiu_Disable.png");
			getButtonByTag(cTag_btnChiu)->setTouchEnabled(!flag_AnBao);
			flag_MeDraw = false;
		}
	}

	//Nếu mình ăn một lá bài
	if (crdorg == 9 && tpos == kUserMe)
	{
		getButtonByTag(cTag_btnChiu)->loadTextureNormal("chiu_Disable.png");
		getButtonByTag(cTag_btnChiu)->setTouchEnabled(false);
	}
}

//Tạo các button chức năng
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

//Tạo các button chức năng
Button* LayerChanGame::createButton_Chan(const char* pName, CCPoint pPoint, const char* pTexture, const char* pTextureSelect, int _posChild){
	Button* button = Button::create();
	button->setTouchEnabled(true);
	button->setScale9Enabled(false);
	button->loadTextures(pTexture, pTextureSelect, "");

	button->setAnchorPoint(ccp(0.5, 0));
	button->setPosition(pPoint);

	UILabelBMFont *lbl = UILabelBMFont::create();
	lbl->setFntFile("tttt.fnt");
	lbl->setText(pName);
	lbl->setColor(ccRED);
	lbl->setScale(0.8);
	lbl->setPositionY(button->getContentSize().height / 2 + 3);
	if(_posChild == 1){
		//button Chiu
		lbl->setPositionX(-4.0);
	}
	if (_posChild == 2)
	{
		//Button Danh, Duoi
		lbl->setPositionX(4.0);
	}
	button->addChild(lbl);
	return button;
}

Button* LayerChanGame::getButtonByTag(int pTag){
	Button* button = (Button*) this->layerButtons->getWidgetByTag(pTag);
	return button;
}

void LayerChanGame::playSounds(string url){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(("sounds/Chan/"+url).c_str());
}

//When user take Cards
void LayerChanGame::whenUserTakeCards(long rscode){
	if(rscode == 0){
		getButtonByTag(cTag_btnEate)->loadTextureNormal("an_Disable.png");
		getButtonByTag(cTag_btnEate)->setTouchEnabled(false);

		getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
		getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

		getButtonByTag(cTag_btnTake)->setEnabled(false);
		getButtonByTag(cTag_btnDuoi)->loadTextureNormal("danh_Disable.png");
		getButtonByTag(cTag_btnTake)->setEnabled(true);
		getButtonByTag(cTag_btnDuoi)->setTouchEnabled(false);
	}else{
		CCLOG("Ăn không đúng Chắn, Cạ");
		LayerChanToast::showToast(this, "Ăn không đúng Chắn Cạ", 4);
	}
}

// set current player
void LayerChanGame::setCurrentPlayer(string uid,int _count){
	layerAvatars->stopAllTimer();
	if(IamGuess() == true)
	{
		int posUser = getPosUserByName_ImGuess(uid);
		if (countUser == 2)
		{
			if (posUser != kUserBot)
			{
				layerAvatars->getUserByPos(kUserTop)->startTimer();
			}
			else
			{
				layerAvatars->getUserByPos(kUserBot)->startTimer();
			}
		}
		else
		{
			layerAvatars->getUserByPos(posUser)->startTimer();
		}
		return;
	}

	CCLOG("Current user %s", uid.c_str());
	stopTimer_Me();

	if (strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0) {

		if (flag_AnBao == true)
		{
			LayerChanToast::showToast(this, "Bạn bị báo do: "+ reason_anbao +" không được chơi nữa !", 4);
			getButtonByTag(cTag_btnU)->loadTextureNormal("U_Disable.png");
			getButtonByTag(cTag_btnU)->setTouchEnabled(false);

			getButtonByTag(cTag_btnTake)->loadTextureNormal("danh_Disable.png");
			getButtonByTag(cTag_btnTake)->setTouchEnabled(false);

			getButtonByTag(cTag_btnEate)->loadTextureNormal("an_Disable.png");
			getButtonByTag(cTag_btnEate)->setTouchEnabled(false);

			getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
			getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

			getButtonByTag(cTag_btnDuoi)->loadTextureNormal("danh_Disable.png");
			getButtonByTag(cTag_btnDuoi)->setTouchEnabled(false);
			return;
		}

		startTimer_Me();
		getButtonByTag(cTag_btnReady)->setEnabled(false);

		if(flag_MeDraw == true){
			getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
			getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

			getButtonByTag(cTag_btnDuoi)->loadTextureNormal("danh.png");
			getButtonByTag(cTag_btnDuoi)->setTouchEnabled(true);
			getButtonByTag(cTag_btnDuoi)->setEnabled(true);
			getButtonByTag(cTag_btnTake)->setEnabled(false);
			return;
		}
		
		getButtonByTag(cTag_btnDuoi)->setEnabled(false);
		getButtonByTag(cTag_btnTake)->loadTextureNormal("danh_Disable.png");
		getButtonByTag(cTag_btnTake)->setEnabled(true);
		getButtonByTag(cTag_btnTake)->setTouchEnabled(false);

		if (_count == 0) {
			getButtonByTag(cTag_btnEate)->loadTextureNormal("an_Disable.png");
			getButtonByTag(cTag_btnEate)->setTouchEnabled(false);

			getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
			getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

			getButtonByTag(cTag_btnTake)->loadTextureNormal("danh.png");
			getButtonByTag(cTag_btnTake)->setEnabled(true);
			getButtonByTag(cTag_btnTake)->setTouchEnabled(true);

		}else{
			getButtonByTag(cTag_btnEate)->loadTextureNormal("an.png");
			getButtonByTag(cTag_btnEate)->setTouchEnabled(true);

			getButtonByTag(cTag_btnBoc)->loadTextureNormal("U.png");
			getButtonByTag(cTag_btnBoc)->setTouchEnabled(true);
		}

		//Nếu người khác chíu con bài mình vừa bốc lên
		//Sau đó trả cửa 1 con vào cửa trì của mình thì hiện button Dưới
		if (flagTraCuaToMe == true)
		{
			getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
			getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

			getButtonByTag(cTag_btnTake)->setEnabled(false);
			getButtonByTag(cTag_btnDuoi)->loadTextureNormal("danh.png");
			getButtonByTag(cTag_btnDuoi)->setTouchEnabled(true);
			getButtonByTag(cTag_btnDuoi)->setEnabled(true);
			return;
		}
		
	}
	//Lượt chơi của người khác
	else{
		getButtonByTag(cTag_btnTake)->loadTextureNormal("danh_Disable.png");
		getButtonByTag(cTag_btnTake)->setTouchEnabled(false);

		getButtonByTag(cTag_btnEate)->loadTextureNormal("an_Disable.png");
		getButtonByTag(cTag_btnEate)->setTouchEnabled(false);

		getButtonByTag(cTag_btnBoc)->loadTextureNormal("U_Disable.png");
		getButtonByTag(cTag_btnBoc)->setTouchEnabled(false);

		getButtonByTag(cTag_btnDuoi)->loadTextureNormal("danh_Disable.png");
		getButtonByTag(cTag_btnDuoi)->setTouchEnabled(false);

		int pos = getPosUserByName(uid, _list_user);
		if (countUser == 2)
		{
			layerAvatars->getUserByPos(kUserTop)->startTimer();
		}
		else
		{
			switch (pos) {
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
}

//set user ready
void LayerChanGame::setUserReady(string uid){
	if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
	{
		if (this->getChildByTag(171)!=NULL)
		{
			this->removeChildByTag(171);
		}
	}
	int pos = getPosUserByName(uid, _list_user);
	if (countUser == 2)
	{
		if (pos != kUserMe)
		{
			layerAvatars->getUserByPos(kUserTop)->setReady(true);
		}
		else
		{
			getButtonByTag(cTag_btnReady)->setEnabled(false);
			layerAvatars->getUserByPos(kUserBot)->setReady(true);
		}
	}
	else
	{
		switch (pos) {
		case kUserMe:
			getButtonByTag(cTag_btnReady)->setEnabled(false);
			layerAvatars->getUserByPos(kUserBot)->setReady(true);
			break;
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
void LayerChanGame::error_AnBao(long rscode, string uid){
	int t = (int)rscode;

	string str = "";
	switch(t){
	case ANBAO_REASON_NO_PROBLEM:
		break;
	case ANBAO_REASON_AN_CA_DOI_CHO:
		str = "Lỗi ăn báo: Ăn cạ đổi chờ";
		break;
	case ANBAO_REASON_BO_AN_CUATREN_BUT_AN_CUATRI:
		str = "Lỗi ăn báo: không ăn cửa trên nhưng lại ăn cửa trì";
		break;
	case ANBAO_REASON_DISCARD_SAMEAS_CUATREN_CUATRI_DUOITAY:
		str = "Lỗi ăn báo: Đánh đi 1 con đã có ở cửa trên, cửa trì hoặc dưới tay";
		break;
	case ANBAO_REASON_ANCA_DANHCA:
		str = "Lỗi ăn báo: Ăn cạ đánh cạ";
		break;
	case ANBAO_TREOTRANH:
		str = "Lỗi ăn báo: Treo tranh";
		break;
	case ANBAO_DANH_1_CA_CHI_DUOC_AN_CHAN:
		str = "Lỗi ăn báo: Đã đánh cạ đi thì chỉ được Ăn chắn";
		break;
	case ANBAO_REASON_BOCHAN_ANCA:
		str = "Lỗi ăn báo: Bỏ Chắn ăn cạ";
		break;
	case ANBAO_REASON_DANHBAI_GIONG_CHANCA_DA_AN:
		str = "Lỗi ăn báo: Đánh đi lá bài giống chắn hoặc Cạ đã ăn";
		break;
	case ANBAO_REASON_DOI_U_BACHTHUCHI:
		str = "Lỗi ăn báo: Đợi Ăn Ù Bạch thủ Chi";
		break;
	case ANBAO_REASON_BOCHAN_DANHCHAN:
		str = "Lỗi ăn báo: Bỏ Chắn đánh chắn";
		break;
	case ANBAO_REASON_BOCHAN_ANCHAN:
		str = "Lỗi ăn báo: Bỏ Chắn Ăn Chắn";
		break;
	case ANBAO_REASON_BOCA_ANCA:
		str = "Lỗi ăn báo: Bỏ Chắn Ăn Cạ";
		break;
	case ANBAO_REASON_DANHCA_ANCA:
		str = "Lỗi ăn báo: Đánh Cạ Ăn Cạ";
		break;
	case ANBAO_REASON_XECA_ANCA:
		str = "Lỗi ăn báo: Xé cạ Ăn Cạ";
		break;
	case ANBAO_REASON_XECHAN_ANCA:
		str = "Lỗi ăn báo: Xé Chắn Ăn Cạ";
		break;
	case ANBAO_REASON_DANH_ROILAI_AN:
		str = "Lỗi ăn báo: Đánh đi 1 con sau lại ăn đúng con đó";
		break;
	case ANBAO_REASON_DANH_DI_DOI_CHAN:
		str = "Lỗi ăn báo: Đánh đi cả đôi Chắn";
		break;
	case ANBAO_REASON_AN_ROILAI_DANH:
		str = "Lỗi ăn báo: Ăn một con rồi lại đánh đi con đó";
		break;
	case ANBAO_REASON_ANCA_ROILAI_DANH_QUAN_CUNG_HANG:
		str = "Lỗi ăn báo: Ăn cạ rồi lại đánh 1 con cùng hàng";
		break;
	case ANBAO_REASON_CHIUDUOC_NHUNG_LAI_ANTHUONG:
		str = "Lỗi ăn báo: Chíu được nhưng lại ăn thường";
		break;
	case ANBAO_REASON_AN_CHON_CA:
		str = "Lỗi ăn báo: Ăn cạ Chọn Cạ";
		break;
	case ANBAO_REASON_CO_CHAN_CAU_CA:
		str = "ăn báo: có Chắn Cấu Cạ";
		break;
	case ANBAO_REASON_U_NHUNG_KHONG_XUONG:
		str = "Ù nhưng không Xướng";
		break;
	case ANBAO_REASON_HO_U_LAO:
		str = "Ù Láo";
		break;
	case ANBAO_REASON_XUONG_SAI_CUOC:
		str = "Xướng sai cước ";
		break;
	}

	if (strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) != 0)
	{
		LayerChanToast::showToast(this, "" + getNamePlayer(uid) + " bị ngồi im do " + str, 4);

		if (!IamGuess())
		{
			int posAnBao = getPosUserByName(uid.c_str(), _list_user);
			if (posAnBao == -1)
			{
				return;
			}

			if (countUser == 2)
			{
				layerAvatars->getUserByPos(kUserTop)->setLblNTFChan("Bị \nBáo");
				layerAvatars->getUserByPos(kUserTop)->getLblNTFChan()->setVisible(true);
			}
			else
			{
				layerAvatars->getUserByPos(posAnBao)->setLblNTFChan("Bị \nBáo");
				layerAvatars->getUserByPos(posAnBao)->getLblNTFChan()->setVisible(true);
			}
		}
		else
		{
			int posAnbao = getPosUserByName_ImGuess(uid);
			if (countUser == 2)
			{
				if (posAnbao == kUserBot)
				{
					layerAvatars->getUserByPos(kUserBot)->setLblNTFChan("Bị \nBáo");
					layerAvatars->getUserByPos(kUserBot)->getLblNTFChan()->setVisible(true);
				}
				else
				{
					layerAvatars->getUserByPos(kUserTop)->setLblNTFChan("Bị \nBáo");
					layerAvatars->getUserByPos(kUserTop)->getLblNTFChan()->setVisible(true);
				}
			}
			else
			{
				layerAvatars->getUserByPos(posAnbao)->setLblNTFChan("Bị \nBáo");
				layerAvatars->getUserByPos(posAnbao)->getLblNTFChan()->setVisible(true);
			}
		}
		return;
	}
	else
	{
		if (rscode != ANBAO_REASON_AN_CA_DOI_CHO &&
			rscode != ANBAO_TREOTRANH &&
			rscode != ANBAO_REASON_CO_CHAN_CAU_CA &&
			rscode != ANBAO_REASON_AN_CHON_CA &&
			rscode != ANBAO_REASON_CHIUDUOC_NHUNG_LAI_ANTHUONG)
		{
			flag_AnBao = true;
			reason_anbao = str;
			LayerChanToast::showToast(this, str, 4 );
			getButtonByTag(cTag_btnU)->loadTextureNormal("U_Disable.png");
			getButtonByTag(cTag_btnU)->setTouchEnabled(false);
			getButtonByTag(cTag_btnChiu)->loadTextureNormal("chiu_Disable.png");
			getButtonByTag(cTag_btnChiu)->setTouchEnabled(!flag_AnBao);
		}
	}
}

//Khi co nguoi cho U
void LayerChanGame::whenConguoi_ChoU(string uid){
	string myName = "";
	myName = GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str();

	stopTimer_Me();
	layerAvatars->stopAllTimer();

	if(strcmp(uid.c_str(),myName.c_str()) == 0){
		LayerChanToast::showToast(this, "Bạn có thể Ù lá bài này", 4);
		if(strcmp(myName.c_str(),currentPlayer.c_str()) == 0)
		{

		}
		else
		{
			
		}
	}else{

		LayerChanToast::showToast(this, "" + getNamePlayer(uid) + " Đang chờ Ù, Đợi nhà này sướng", 4);

		//start timer của người chơi chờ Ù
		if (countUser == 2)
		{
			if (getPosUserByName(uid,_list_user) == kUserMe)
			{
				//startTimer_Me();
			}
			else
			{
				layerAvatars->getUserByPos(kUserTop)->startTimer();
			}
			
		}else{
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
}

//Co nguoi co the chiu
void LayerChanGame::whenConguoi_Chiu(string uid){
	string myName = "";
	myName = GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str();

	if (strcmp(uid.c_str(), myName.c_str()) == 0)
	{
		LayerChanToast::showToast(this, "Có thể chíu lá bài này", 4);
	}
	else
	{
		if(strcmp(myName.c_str(), currentPlayer.c_str()) == 0)
		{
			LayerChanToast::showToast(this, "test, " + getNamePlayer(uid) + " chíu, chờ xíu", 4);
		}
	}
}

//Xuong U
void LayerChanGame::XuongU(){

	layerCardChan->scaleCardsHand_whenU();
	layerCardChan->moveCardChi_whenU();

	cocos2d::extension::CCBReader * ccbReader = NULL;
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);

	// register loaders
	ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerGameChan_XuongU2",   LayerGameChan_XuongU2Loader::loader());
	// read main layer
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

	LayerGameChan_XuongU2 *popUp;

	if (ccbReader)
	{
		popUp = (LayerGameChan_XuongU2 *)ccbReader->readNodeGraphFromFile( "LayerGameChan_XuongU2.ccbi" );
		popUp->setPosition(ccp(10,10));
		popUp->setTag(172);
		this->addChild(popUp);
		ccbReader->release();
	}
}

void LayerChanGame::resuiltGame(string resuilt)
{
	vector<string> arrResuilt = splitString(resuilt,';');

	string _cuoc = (strcmp(arrResuilt[4].c_str(), "") != 0) ? arrResuilt[4] : arrResuilt[5];
	vector<string> arrCuoc = splitString(_cuoc, ':');

	string ketqua = "";

	for(int  i = 0; i < arrCuoc.size(); i++){
		ketqua += identifyCuoc_sac(arrCuoc[i]);
		if (identifyCuoc_sac(arrCuoc[i]) != "")
		{
			ketqua += " ";
		}
	}

	CCLOG("ket cuoc: %s",ketqua.c_str());
	CCLabelBMFont *lblCuoc = CCLabelBMFont::create();
	lblCuoc->setFntFile("tttt.fnt");
	lblCuoc->setString(ketqua.c_str());

	lblCuoc->setAnchorPoint(ccp(0.5, 0.5));

	lblCuoc->setColor(ccRED);
	lblCuoc->setPosition(ccp(WIDTH_DESIGN / 2, HEIGHT_DESIGN / 2 + 130));
	lblCuoc->setTag(201);
	this->addChild(lblCuoc);

	CCActionInterval *scale = CCScaleTo::create(0.5, 1.5);
	lblCuoc->runAction(scale);

	CCString *p = CCString::create(resuilt);
	CCCallFuncO *callfun = CCCallFuncO::create(this, callfuncO_selector(LayerChanGame::displayResuitGame),p);
	CCDelayTime *delay = CCDelayTime::create(6.0);
	this->runAction(CCSequence::create(delay, callfun, NULL));
}

void LayerChanGame::setEndGame(){
	layerAvatars->stopAllTimer();
	layerAvatars->getUserByPos(kUserLeft)->getLblNTFChan()->setVisible(false);
	layerAvatars->getUserByPos(kUserRight)->getLblNTFChan()->setVisible(false);
	layerAvatars->getUserByPos(kUserTop)->getLblNTFChan()->setVisible(false);
	layerAvatars->getUserByPos(kUserBot)->getLblNTFChan()->setVisible(false);

	stopTimer_Me();
	currentPlayer = "";
	mylistCard = "";

	flagChiaBai = false;
	flagTraCuaToMe = false;
	flag_MeDraw = false;

	countDiscard = 0;
	_noccount = -1;

	layerCardChan->resetAllCards();
	layerAvatars->getUserByPos(kUserBot)->setPositionY(10);

	getButtonByTag(cTag_btnBoc)->loadTextureNormal("U.png");
	getButtonByTag(cTag_btnBoc)->setTouchEnabled(true);
	getButtonByTag(cTag_btnBoc)->setEnabled(false);

	getButtonByTag(cTag_btnDuoi)->loadTextureNormal("danh.png");
	getButtonByTag(cTag_btnDuoi)->setTouchEnabled(true);
	getButtonByTag(cTag_btnDuoi)->setEnabled(false);

	getButtonByTag(cTag_btnEate)->loadTextureNormal("an.png");
	getButtonByTag(cTag_btnEate)->setTouchEnabled(true);
	getButtonByTag(cTag_btnEate)->setEnabled(false);

	getButtonByTag(cTag_btnTake)->loadTextureNormal("danh.png");
	getButtonByTag(cTag_btnTake)->setTouchEnabled(true);
	getButtonByTag(cTag_btnTake)->setEnabled(false);

	getButtonByTag(cTag_btnChiu)->loadTextureNormal("chiu.png");
	getButtonByTag(cTag_btnChiu)->setTouchEnabled(true);
	getButtonByTag(cTag_btnChiu)->setEnabled(false);

	getButtonByTag(cTag_btnU)->loadTextureNormal("U.png");
	getButtonByTag(cTag_btnU)->setTouchEnabled(true);
	getButtonByTag(cTag_btnU)->setEnabled(false);

	getButtonByTag(cTag_btnReady)->setEnabled(true);

	if (this->getChildByTag(201) != NULL)
	{
		this->removeChildByTag(201);
	}
}

void LayerChanGame::displayResuitGame(CCObject *data){
	CCString *resuilt = (CCString *) data;
	string str = string(resuilt->getCString());
	displayLayerKetQua(str);
}

void LayerChanGame::waitPlayer_ReqU(string uid, string lc){

	LayerChanToast::showToast(this, "" + getNamePlayer(uid) + " Đã Ù lá bài này, Đợi xem ai báo Ù nữa hay không !", 4);

	string strRe = uid + "|" + lc;

	CCString *p = CCString::create(strRe);
	//hideAllButton();
	CCCallFuncO *callfun = CCCallFuncO::create(this, callfuncO_selector(LayerChanGame::wait10s),p);
	CCDelayTime *delay = CCDelayTime::create(6.0);
	this->runAction(CCSequence::create(delay, callfun, NULL));
}

void LayerChanGame::wait10s(CCObject *data){
	layerAvatars->stopAllTimer();
	CCString *lc = (CCString *) data;
	string strRe = ((CCString *) data)->getCString();
	vector<string> arrRe = mUtils::splitString(strRe, '|');

	string uid = arrRe.at(0);
	if (IamGuess() == true)
	{
		int pos = getPosUserByName_ImGuess(uid);
		if (countUser == 2)
		{
			if (pos != kUserBot)
			{
				layerAvatars->getUserByPos(kUserTop)->setBlinkAvatar();
			}
			else
			{
				layerAvatars->getUserByPos(kUserBot)->setBlinkAvatar();
			}
		}
		else
		{
			layerAvatars->getUserByPos(pos)->setBlinkAvatar();
		}
	}
	else
	{
		int pos = getPosUserByName(uid, _list_user);
		if(mUtils::splitString(_list_user, ';').size() == 2)
		{
			if (pos != kUserMe)
			{
				layerAvatars->getUserByPos(kUserTop)->setBlinkAvatar();
			}
		}
		else
		{
			if (pos != -1 && pos != kUserMe)
			{
				layerAvatars->getUserByPos(pos)->setBlinkAvatar();
			}
		}
		layerCardChan->scaleCardsHand_whenU();
	}
	
	string str = arrRe.at(1);
	layerCardChan->setCardsResuilt(str);
	getButtonByTag(cTag_btnChiu)->setEnabled(false);
	getButtonByTag(cTag_btnU)->setEnabled(false);
	getButtonByTag(cTag_btnTake)->setEnabled(false);
	getButtonByTag(cTag_btnDuoi)->setEnabled(false);
	getButtonByTag(cTag_btnEate)->setEnabled(false);
	getButtonByTag(cTag_btnBoc)->setEnabled(false);
}

void LayerChanGame::notificationCallBack(bool isOK, int tag){
	CCLOG("callbackNtf****");
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
		layerCardChan->doDisCards();
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
		layerCardChan->doDuoiCard();
	}
}

//btn Ăn bài
void LayerChanGame::btn_eate_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		layerCardChan->doEateCard();
	}
}

void LayerChanGame::btn_U_Click(CCObject *sender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		CCLOG("Send U to server !");
		boost::shared_ptr<Room> lstRooms = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		boost::shared_ptr<IRequest> resObj (new ExtensionRequest(EXT_EVENT_REQ_U, params, lstRooms));
		GameServer::getSingleton().getSmartFox()->Send(resObj);
	}
}

void LayerChanGame::btn_Chiu_Click(CCObject *sender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		layerCardChan->doChiuCard();
	}
}

void LayerChanGame::hideAllButton(){
	getButtonByTag(cTag_btnReady)->setEnabled(false);

	//getButtonByTag(cTag_btnBoc)->setEnabled(false);
	getButtonByTag(cTag_btnBoc)->setEnabled(false);

	getButtonByTag(cTag_btnEate)->loadTextureNormal("an_Disable.png");
	getButtonByTag(cTag_btnEate)->setTouchEnabled(false);
	getButtonByTag(cTag_btnEate)->setEnabled(false);
	getButtonByTag(cTag_btnDuoi)->setEnabled(false);
	getButtonByTag(cTag_btnTake)->setEnabled(false);
}
void LayerChanGame::resetPositionButton(){

}

void LayerChanGame::callBackFunction_LatBai(CCNode *pSend){
	if (strcmp(currentPlayer.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
	{
		getButtonByTag(cTag_btnBoc)->setEnabled(false);
		getButtonByTag(cTag_btnEate)->setEnabled(true);
		getButtonByTag(cTag_btnDuoi)->setEnabled(true);
	}
}

void LayerChanGame::startTimer_Me(){
	stopTimer_Me();
	CCProgressTo *actionTimer = CCProgressTo::create(60, 100);
	timer_Me->runAction(CCSequence::create(actionTimer,
		CCCallFuncN::create(this, callfuncN_selector(LayerChanGame::callbackTimer)),
		NULL));
}
void LayerChanGame::callbackTimer(CCNode *pSender){
	stopTimer_Me();
}
void LayerChanGame::stopTimer_Me(){

	if (timer_Me == NULL) {
		return;
	}

	if (timer_Me->numberOfRunningActions() > 0) {
		timer_Me->stopAllActions();
	}
	timer_Me->setPercentage(0);
}

string LayerChanGame::identifyCuoc_sac(string _cuoc){
	int cuoc = atoi(_cuoc.c_str());
	switch(cuoc){
	case 0:
		return "Xuông";
	case 1:
		return "Thông";
	case 2:
		return "Chì";
	case 3:
		return "Thiên Ù";
	case 4:
		return "Địa Ù";
	case 5:
		return "Tôm";
	case 6:
		return "Lèo";
	case 7:
		return "Bạch Định";
	case 8:
		return "Tám Đỏ";
	case 9:
		return "Kính Tứ Chi";
	case 10:
		return "Thập thành";
	case 11:
		return "Có Thiên Khai";
	case 12:
		return "Ăn Bòn";
	case 13:
		return "Ù Bòn";
	case 14:
		return "Có Chíu";
	case 15:
		return "Chíu Ù";
	case 16:
		return "Bạch Thủ";
	case 17:
		return "Hoa Rơi cửa phật";
	case 18:
		return "Nhà lầu xe hơi, hoa rơi cửa phật";
	case 19:
		return "Cá lội sân đình";
	case 20:
		return "Cá nhảy đầu thuyền";
	case 21:
		return "Chùa đổ nát hoa";
	case 22:
		return "Đôi Lèo";
	case 23:
		return "Đôi tám đỏ";
	case 24:
		return "Đôi Tôm";
	case 25:
		return "Bạch thủ Chi";
	}
	return "";
}