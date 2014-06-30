//
//  TomCuaCa.cpp
//  iCasino_v2
//
//  Created by Tuan on 6/23/14.
//
//
#include "TomCuaCa.h"
#include "_Background_inGame_.h"
#include "_Button_inGame_.h"
#include "Requests/ExtensionRequest.h"
#include "_Number_inTomCuaCa.h"
#include "_Chat_inGame_.h"
#include "mUtils.h"
#include "_Chat_.h"
#include "SceneManager.h"
#include "LayerBet_TomCuaCa.h"
#include "SliderCustomLoader.h"



enum TCC_REPONSE {
	EXT_EVENT_USER_JOIN_NOTIF,      // jrntf
	EXT_EVENT_READY_NTF,
	EXT_EVENT_ERROR_READY_NTF,      // = "e_rntf";
	EXT_EVENT_UNREADY_NTF,          // = "urntf";
	EXT_EVENT_READY_RES,            // = "rdres";
	EXT_EVENT_LIST_USER_UPDATE,     // = "luu";
	EXT_EVENT_START,				// = "s";
	EXT_EVENT_USER_LEAVE_NOTIF,     // = "lrntf";
	EXT_EVENT_END,					// = "e";
	EXT_EVENT_AMF_TEST_NOTIF,       // = "cblltf";
	EXT_EVENT_VICTORY_NOTIF,        // = "vicntf";
	EXT_EVENT_READY_REQ,            // = "rr";
	EXT_EVENT_UNREADY_REQ,			// = "urr"
	EXT_EVENT_GAME_RESULT,			// = "grs"
	EXT_EVENT_GAME_BET_NTF			//= "gb_ntf"
};
int TomCuaCa::convertResponseToInt(string inString) {
	if (inString == "jrntf")    return EXT_EVENT_USER_JOIN_NOTIF;
	if (inString == "e_rntf")   return EXT_EVENT_ERROR_READY_NTF;
	if (inString == "rntf")		return EXT_EVENT_READY_NTF;
	if (inString == "grs")		return EXT_EVENT_GAME_RESULT;
	if (inString == "urntf")    return EXT_EVENT_UNREADY_NTF;
	if (inString == "rdres")    return EXT_EVENT_READY_RES;
	if (inString == "urr")		return EXT_EVENT_UNREADY_REQ;
	if (inString == "luu")      return EXT_EVENT_LIST_USER_UPDATE;
	if (inString == "s")		return EXT_EVENT_START;
	if (inString == "gb_ntf")		return EXT_EVENT_GAME_BET_NTF;

	if (inString == "e")   return EXT_EVENT_END;
	if (inString == "cblltf")   return EXT_EVENT_AMF_TEST_NOTIF;
	if (inString == "vicntf")   return EXT_EVENT_VICTORY_NOTIF;

	//
	if (inString == "rr")       return EXT_EVENT_READY_REQ;


	return -1;
}
string TomCuaCa::convertResponseToString(int inInt) {
	if (inInt == EXT_EVENT_USER_JOIN_NOTIF)     return "jrntf";
	if (inInt == EXT_EVENT_GAME_BET_NTF)     return "gb_ntf";
	if (inInt == EXT_EVENT_ERROR_READY_NTF)     return "e_rntf";

	if (inInt == EXT_EVENT_UNREADY_NTF)         return "urntf";
	if (inInt == EXT_EVENT_READY_RES)           return "rdres";
	if (inInt == EXT_EVENT_LIST_USER_UPDATE)    return "luu";
	if (inInt == EXT_EVENT_START)				return "s";
	if (inInt == EXT_EVENT_GAME_RESULT)			return "grs";
	if (inInt == EXT_EVENT_USER_LEAVE_NOTIF)    return "lrntf";
	if (inInt == EXT_EVENT_END)					return "e";
	if (inInt == EXT_EVENT_AMF_TEST_NOTIF)      return "cblltf";
	if (inInt == EXT_EVENT_VICTORY_NOTIF)       return "vicntf";

	//
	if (inInt == EXT_EVENT_READY_REQ)           return "rr";
	if (inInt == EXT_EVENT_UNREADY_REQ)           return "urr";
	if (inInt == EXT_EVENT_READY_NTF)           return "rntf";


	return "";
}
float TomCuaCa::convertResult(string rs)
{
	if(rs == "1") return _kqNai;
	if(rs == "2") return _kqRuou;
	if(rs == "3") return _kqGa;
	if(rs == "4") return _kqCa;
	if(rs == "5") return _kqCua;
	if(rs == "6") return _kqTom;
	return -1;
}
TomCuaCa::TomCuaCa(){

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"sounds/game_tomcuaca/background.mp3", true);
		_count=100;
		
		uLayer = UILayer::create();
		uLayer->addWidget(GUIReader::shareReader()->widgetFromJsonFile("TomCuaCa/scroll/TomCuaCa_1_1.json"));
		
		

		btnReady = UIButton::create();
		btnReady->loadTextures("ready.png", "ready_selected.png", "");
		btnReady->setTitleText("Sẵn Sàng");
		btnReady->setTag(t_ready);
		btnReady->setAnchorPoint(ccp(0,0));
		btnReady->setPosition(ccp(WIDTH_DESIGN-btnReady->getContentSize().width-20,10));
		btnReady->setTouchEnabled(true);
		btnReady->addTouchEventListener(this,(SEL_TouchEvent)&TomCuaCa::clickBtn);
		btnReady->setTitleFontSize(20);
		btnReady->setTitleColor(ccRED);
		
		uLayer->addWidget(btnReady);

		btnUnReady = UIButton::create();
		btnUnReady->loadTextures("ready.png", "ready_selected.png", "");
		btnUnReady->setTitleText("Hủy Sẵn Sàng");
		btnUnReady->setAnchorPoint(ccp(0,0));
		btnUnReady->setPosition(ccp(WIDTH_DESIGN-btnUnReady->getContentSize().width-20,10));
		btnUnReady->setTitleFontSize(20);
		btnUnReady->setTitleColor(ccRED);
		btnUnReady->setTouchEnabled(false);
		btnUnReady->addTouchEventListener(this,(SEL_TouchEvent)&TomCuaCa::clickBtn);
		btnUnReady->setVisible(false);
		btnUnReady->setTag(t_unReady);
		uLayer->addWidget(btnUnReady);
	
		//BUTTON
		btnTom = UIButton::create();
		btnTom->loadTextures("TomCuaCa/Tom.png","TomCuaCa/Tom_payment.png","TomCuaCa/result_tom.png");
		btnTom->setPosition(ccp(260,280));
		btnTom->setTouchEnabled(false);
		btnTom->addTouchEventListener(this,(SEL_TouchEvent)&TomCuaCa::clickBtn);
		btnTom->setTag(t_tom);
		uLayer->addWidget(btnTom);

		btnCua = UIButton::create();
		btnCua->loadTextures("TomCuaCa/Cua.png","TomCuaCa/Cua_payment.png","TomCuaCa/result_cua.png");
		btnCua->setPosition(ccp(400,280));
		btnCua->setTouchEnabled(false);
		btnCua->addTouchEventListener(this,(SEL_TouchEvent)&TomCuaCa::clickBtn);
		btnCua->setTag(t_cua);
		uLayer->addWidget(btnCua);

		btnCa = UIButton::create();
		btnCa->loadTextures("TomCuaCa/Ca.png","TomCuaCa/Ca_payment.png","TomCuaCa/result_ca.png");
		btnCa->setPosition(ccp(540,280));
		btnCa->setTouchEnabled(false);
		btnCa->setTag(t_ca);
		btnCa->addTouchEventListener(this,(SEL_TouchEvent)&TomCuaCa::clickBtn);
		uLayer->addWidget(btnCa);

		btnGa = UIButton::create();
		btnGa->loadTextures("TomCuaCa/Ga.png","TomCuaCa/Ga_payment.png","TomCuaCa/result_ga.png");
		btnGa->setPosition(ccp(260,160));
		btnGa->setTouchEnabled(false);
		btnGa->setTag(t_ga);
		btnGa->addTouchEventListener(this,(SEL_TouchEvent)&TomCuaCa::clickBtn);
		uLayer->addWidget(btnGa);

		btnRuou = UIButton::create();
		btnRuou->loadTextures("TomCuaCa/Ruou.png","TomCuaCa/Ruou_payment.png","TomCuaCa/result_ruou.png");
		btnRuou->setPosition(ccp(400,160));
		btnRuou->setTouchEnabled(false);
		btnRuou->setTag(t_ruou);
		btnRuou->addTouchEventListener(this,(SEL_TouchEvent)&TomCuaCa::clickBtn);
		uLayer->addWidget(btnRuou);

		btnNai = UIButton::create();
		btnNai->loadTextures("TomCuaCa/Nai.png","TomCuaCa/Nai_payment.png","TomCuaCa/result_nai.png");
		btnNai->setPosition(ccp(540,160));
		btnNai->setTouchEnabled(false);
		btnNai->setTag(t_nai);
		btnNai->addTouchEventListener(this,(SEL_TouchEvent)&TomCuaCa::clickBtn);
		uLayer->addWidget(btnNai);

		//loading
		loading = UILoadingBar::create();
		loading->loadTexture("TomCuaCa/loading.png");
		loading->setPosition(ccp(400,370));
		loading->setPercent(100);
		uLayer->addWidget(loading);
		
		// scroll

		scroll1 = dynamic_cast<UIScrollView*>(uLayer->getWidgetByName("scrollView_kq1"));
		scroll2 = dynamic_cast<UIScrollView*>(uLayer->getWidgetByName("scrollView_kq2"));
		scroll3 = dynamic_cast<UIScrollView*>(uLayer->getWidgetByName("scrollView_kq3"));
		scroll1->setTouchEnabled(false);
		scroll2->setTouchEnabled(false);
		scroll3->setTouchEnabled(false);
		
		createBackgrounds();
		createAvatars();
		createButtons();
		
		//frame bet
		betTom = FrameBet::create();
		betTom->setPosition(218,238);
		betTom->setValueBet(" Cuoc");
		uLayer->addChild(betTom);
		
		betCua = FrameBet::create();
		betCua->setPosition(358,238);
		betCua->setValueBet(" Cuoc");
		uLayer->addChild(betCua);

		betCa = FrameBet::create();
		betCa->setPosition(498,238);
		betCa->setValueBet(" Cuoc");
		uLayer->addChild(betCa);

		betGa = FrameBet::create();
		betGa->setPosition(218,118);
		betGa->setValueBet(" Cuoc");
		uLayer->addChild(betGa);

		betRuou = FrameBet::create();
		betRuou->setPosition(358,118);
		betRuou->setValueBet(" Cuoc");
		uLayer->addChild(betRuou);

		betNai = FrameBet::create();
		betNai->setPosition(498,118);
		betNai->setValueBet(" Cuoc");
		uLayer->addChild(betNai);
		
	GameServer::getSingleton().addListeners(this);
	this->addChild(uLayer);

	 _id_me =((boost::shared_ptr<string>)(GameServer::getSingleton().getSmartFox()->MySelf()->Name()));
}
vector<string> TomCuaCa::TCCsplit(string &S,const char &str){
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
void TomCuaCa::updateUser(string list){
	lAvatar->resetAll();
	vector<string> listUser;
	listUser = TCCsplit(list, ';');
	CCLOG("Do dai: %ld",listUser.size());
	boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	for(int i=0;i<listUser.size();i++){
		if(lastRoom==NULL){
			return;
		}
		if(listUser[i].c_str()==NULL)
			continue;
		string player = listUser[i];
		vector<string> n = TCCsplit(player, '|');

		if(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])==NULL){
			continue;
		}

		int _money = 0;
		string _name = "";
		string _url = "imagizer.imageshack.us/v2/96x96q90/822/2u66.jpg";
		

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("amf")->GetDoubleValue();
		boost::shared_ptr<string> url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("aal")->GetStringValue();
		if (name != NULL) {
			_name = name->c_str();
		}
		if(money != NULL){
			_money = (int)*money;
		}
		if (url != NULL)
		{
			//_url = url->c_str();
			CCLOG("Avatar: %s",url->c_str());
		}

		if(strcmp(n[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			
			lAvatar->setName(kUserMe, _name.c_str());
			lAvatar->getUserByPos(kUserMe)->setMoney(_money);
			lAvatar->getUserByPos(kUserMe)->setIcon(_url);


			if(n[0]==find_ChuPhong(_list_user)){
				lAvatar->setPosChuong(kUserMe);
				_time=1;
				lAvatar->setFlag(kUserMe, true);
				btnReady->setTitleText("Bắt đầu");
			}
			else{

				btnReady->setTitleText("Sẵn sàng");
			}
		}
		else{
			switch (getPosUserByName(n[0], _list_user)) {
			case kUserLeft:
				lAvatar->getUserByPos(kUserLeft)->setVisibleLayerInvite(false);
				lAvatar->setName(kUserLeft, _name.c_str());
				lAvatar->getUserByPos(kUserLeft)->setMoney(_money);
				lAvatar->getUserByPos(kUserLeft)->setIcon(_url);
				if(n[0]==find_ChuPhong(_list_user)){
					lAvatar->setFlag(kUserLeft, true);
					lAvatar->setPosChuong(kUserLeft);
					_time=0;
				}
				break;
			case kUserRight:
				lAvatar->getUserByPos(kUserRight)->setVisibleLayerInvite(false);
				lAvatar->setName(kUserRight, _name.c_str());
				lAvatar->getUserByPos(kUserRight)->setMoney(_money);
				lAvatar->getUserByPos(kUserRight)->setIcon(_url);
				if(n[0]==find_ChuPhong(_list_user)){
					lAvatar->setFlag(kUserRight, true);
					lAvatar->setPosChuong(kUserRight);
					_time=0;
				}
				break;
			case kUserTop:
				lAvatar->getUserByPos(kUserTop)->setVisibleLayerInvite(false);
				lAvatar->setName(kUserTop, _name.c_str());
				lAvatar->getUserByPos(kUserTop)->setMoney(_money);
				lAvatar->getUserByPos(kUserTop)->setIcon(_url);
				if(n[0]==find_ChuPhong(_list_user)){
					lAvatar->setFlag(kUserTop, true);
					lAvatar->setPosChuong(kUserTop);
					_time=0;
				}
				break;
			case kUserBot:
				lAvatar->getUserByPos(kUserBot)->setVisibleLayerInvite(false);
				lAvatar->setName(kUserBot, _name.c_str());
				lAvatar->getUserByPos(kUserBot)->setMoney(_money);
				lAvatar->getUserByPos(kUserBot)->setIcon(_url);
				if(n[0]==find_ChuPhong(_list_user)){
					lAvatar->setFlag(kUserBot, true);
					lAvatar->setPosChuong(kUserBot);
					_time=0;
				}
			}
		}
	}
}
string TomCuaCa::find_ChuPhong(string listUser){
	vector<string> arrUser = TCCsplit(listUser,';');
	vector<string> info = TCCsplit(arrUser[0], '|');
	string boosId = info[0];
	return boosId;
}
int	 TomCuaCa::getPosUserByName(string uid,string _list_user){
	int vt = -1;
	vector<string> list;
	if(_list_user.c_str() != NULL && _list_user != ""){
		list = TCCsplit(_list_user, ';');
	}
	//Tìm vị trí của mình trong list user
	for(int i=0;i<list.size();i++){
		string _id = TCCsplit(list[i], '|')[0];
		if(strcmp(_id.c_str(), _id_me->c_str())==0){
			vt = i;
			break;
		}
	}
	// từ đó tìm vị trí của id truyền vào (so với mình)
	for(int k=0;k<list.size();k++){
		if(strcmp(list[k].c_str(), "")==0)
			continue;
		string player = list[k];
		vector<string> n = TCCsplit(player, '|');
		if(strcmp(n[0].c_str(), uid.c_str())==0){
			if(k==vt){
				return kUserMe;
			}
			else if(k==(vt+1)%5){
				return kUserRight;
			}
			else if(k==(vt+2)%5){
				return kUserTop;
			}
			else if(k==(vt+3)%5){
				return kUserLeft;
			}
			else if(k==(vt+4)%5){
				return kUserBot;
			}
			break;
		}
	}
	return 0;
}
void TomCuaCa::whenUserReady(string uid){
	if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
		btnReady->setTouchEnabled(false);
		btnReady->setVisible(false);
		// hiện unready
		btnUnReady->setTouchEnabled(true);
		btnUnReady->setVisible(true);
		lAvatar->getUserByPos(kUserMe)->setReady(true);
	}else{
		switch (getPosUserByName(uid, _list_user)) {
		case kUserLeft:
			lAvatar->getUserByPos(kUserLeft)->setReady(true);
			break;
		case kUserRight:
			lAvatar->getUserByPos(kUserRight)->setReady(true);
			break;
		case kUserTop:
			lAvatar->getUserByPos(kUserTop)->setReady(true);
			break;
		case kUserBot:
			lAvatar->getUserByPos(kUserBot)->setReady(true);
			break;
		default:
			break;
		}
	}
}
void TomCuaCa::whenUserUnready(string uid){
		if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			btnUnReady->setTouchEnabled(false);
			btnUnReady->setVisible(false);
			//hiện ready
			lAvatar->setReady(kUserMe,false);
			btnReady->setTouchEnabled(true);
			btnReady->setVisible(true);
		
		}
		else{
			switch (getPosUserByName(uid, _list_user)) {
			case kUserLeft:
				lAvatar->setReady(kUserLeft,false);
				break;
			case kUserRight:
				lAvatar->setReady(kUserRight,false);
				break;
			case kUserTop:
				lAvatar->setReady(kUserTop,false);
				break;
			case kUserBot:
				lAvatar->setReady(kUserBot,false);
				break;
			default:
				break;
			}
		}
	
}
void TomCuaCa::whenGameStart(){
	btnReady -> setTouchEnabled(false);
	btnReady->setVisible(false);
	btnUnReady->setTouchEnabled(false);
	btnUnReady->setVisible(false);

			CCLog("%d",_time);
			if(_time==1)
			{
				btnTom->setTouchEnabled(false);
				btnCua->setTouchEnabled(false);
				btnCa->setTouchEnabled(false);
				btnGa->setTouchEnabled(false);
				btnRuou->setTouchEnabled(false);
				btnNai->setTouchEnabled(false);
			}
		else
			{
				btnTom->setTouchEnabled(true);
				btnCua->setTouchEnabled(true);
				btnCa->setTouchEnabled(true);
				btnGa->setTouchEnabled(true);
				btnRuou->setTouchEnabled(true);
				btnNai->setTouchEnabled(true);
			}



	this->schedule(schedule_selector(TomCuaCa::update));

	Chat *toast = new Chat("Đặt cược đê....", -1);
	this->addChild(toast);

	CCLog("Game start");
	
	


}
void TomCuaCa::whenResuiltGame(string rg){

	this->unschedule(schedule_selector(TomCuaCa::update));
	
	

	vector<string> resuilt = TCCsplit(rg, '_');
	
	scroll1->scrollToPercentVertical(convertResult(resuilt[0]),6,true);

	scroll2->scrollToPercentVertical(convertResult(resuilt[1]),7,true);

	scroll3->scrollToPercentVertical(convertResult(resuilt[2]),8,true);

	btnTom->setTouchEnabled(false);
	btnCua->setTouchEnabled(false);
	btnCa->setTouchEnabled(false);
	btnGa->setTouchEnabled(false);
	btnRuou->setTouchEnabled(false);
	btnNai->setTouchEnabled(false);
		
	
	

	
		
}
void TomCuaCa::whenGameEnd(){
	NumberInTomCuaCa *layerNumbers = NumberInTomCuaCa::create();
	this->addChild(layerNumbers);
	LayerChatInGame *layerChat = LayerChatInGame::create();
	this->addChild(layerChat);
	
	_count=100;
	loading->setPercent(_count);
	btnReady -> setTouchEnabled(true);
	btnReady->setVisible(true);
	btnUnReady->setTouchEnabled(false);
	btnUnReady->setVisible(false);

	
	scroll1->scrollToTop(0.1,false);

	scroll2->scrollToTop(0.1,false);

	scroll3->scrollToTop(0.1,false);

	betTom->setValueBet("  Cuoc");
	betCua->setValueBet("  Cuoc");
	betCa->setValueBet("  Cuoc");
	betGa->setValueBet("  Cuoc");
	betRuou->setValueBet("  Cuoc");
	betNai->setValueBet("  Cuoc");

	CCLog("End game");
	btnTom->setBright(true);
	btnCua->setBright(true);
	btnCa->setBright(true);
	btnGa->setBright(true);
	btnRuou->setBright(true);
	btnNai->setBright(true);

}
	 TomCuaCa::~TomCuaCa(){
	GameServer::getSingleton().removeListeners(this);
	this->removeAllChildren();
	

}
bool TomCuaCa::init(){
	if(!CCLayer::init()){
		return false;
	}
	

	return true;
}
void TomCuaCa::createBackgrounds(){

	CCSprite *bg = CCSprite::create("back.png");
	bg->setPosition(ccp(WIDTH_DESIGN/2,HEIGHT_DESIGN/2-20));
	this->addChild(bg);
	LayerChatInGame* chat_ = LayerChatInGame::create();
	this->addChild(chat_);
}
void TomCuaCa::createButtons(){

	LayerButtonInGame* lButton = LayerButtonInGame::create();
	uLayer->addChild(lButton);

}
void TomCuaCa::createAvatars(){
	//MY info

	lAvatar = AvatarInTomCuaCa::create();
	
	boost::shared_ptr<User> mySelf = GameServer::getSingleton().getSmartFox()->MySelf();
	boost::shared_ptr<double> inv = mySelf->GetVariable("am")->GetDoubleValue();
	lAvatar->getUserByPos(kUserMe)->setName(mySelf->Name()->c_str());
	lAvatar->getUserByPos(kUserMe)->setMeIsBoss(true);
	lAvatar->getUserByPos(kUserMe)->setFlag(true);
	lAvatar->getUserByPos(kUserMe)->setMoney(*inv);
	
	uLayer->addChild(lAvatar);



}
void TomCuaCa::createChat()
{
	LayerChatInGame *chat = LayerChatInGame::create();
	uLayer->addChild(chat);
	}
void TomCuaCa::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){


	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
	boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));

	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
	boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));


	if(strcmp("hbc", cmd->c_str())==0){
		return;
	}


	CCLog("---------- %s", cmd->c_str());

	switch (convertResponseToInt(cmd->c_str()))
	{
		case EXT_EVENT_LIST_USER_UPDATE:
			{
				boost::shared_ptr<string> lu = param->GetUtfString("lu");
					if (lu != NULL) {
						CCLOG("List user: %s",lu->c_str());
							_list_user = *lu;
				updateUser(*lu);

					}else{
							_list_user = "";
							CCLOG("Không nhận được listuser");
				break;
						}
			}
		case EXT_EVENT_READY_NTF:
			{
				boost::shared_ptr<string> uid = param->GetUtfString("uid");
				if(uid != NULL){
					whenUserReady(*uid);
				
								}
				break;
			}
		case EXT_EVENT_ERROR_READY_NTF:
			{
				boost::shared_ptr<long> errc = param->GetInt("errc");
				if (errc != NULL)
				{
					if (*errc == 30)
					{
						Chat *toast = new Chat("Đợi người chơi khác sẵn sàng", -1);
						this->addChild(toast);
					}
					if (*errc == 29) 
					{
						Chat *toast = new Chat("Không đủ tiền đặt cược",-1);
						this->addChild(toast);
					}
				}
				break;
			}
		case EXT_EVENT_UNREADY_NTF:
			{
				boost::shared_ptr<string> uid = param->GetUtfString("uid");
				if(uid != NULL){
					whenUserUnready(*uid);
								}
				break;
			}
		case EXT_EVENT_START:
			{
			whenGameStart();
			break;
			}
		case EXT_EVENT_END:
			{
				
				whenGameEnd();
				break;
			}
		case EXT_EVENT_GAME_RESULT:
			{
				boost::shared_ptr<string> resul = param->GetUtfString("rg");
				CCLog("--------%s",resul->c_str());
				kq = param->GetUtfString("rgu");
				CCLog("--------%s",kq->c_str());
				vector<string> gameRs = TCCsplit(*resul, '_');
				kq1=gameRs[0];
				kq2=gameRs[1];
				kq3=gameRs[2];
				whenResuiltGame(*resul);

				this->runAction(CCSequence::create(CCDelayTime::create(8),CCCallFunc::create(this, callfunc_selector(TomCuaCa::hienOketqua)),NULL));
				this->runAction(CCSequence::create(CCDelayTime::create(9),CCCallFunc::create(this, callfunc_selector(TomCuaCa::hienKetQua)),NULL));
				
					 
				break;
				}
		case EXT_EVENT_GAME_BET_NTF:
			{
				boost::shared_ptr<long> tienbet = param->GetInt("gbv");
				_tienBet=int(*tienbet);
				CCLog("---Bet: %d",_tienBet);
		
				boost::shared_ptr<long> oCuoc = param->GetInt("aid");
				CCLog("---O cuoc: %d",*oCuoc);

				char _bet[20];
				sprintf (_bet, "%d", _tienBet);
				int _aid=0;
				_aid =int(*oCuoc);
				bet(_aid,_bet);


				break;
			}
		default:
			break;
	}
}
void TomCuaCa::clickBtn(CCObject* obj, TouchEventType type)
{
	UIButton* bTag = (UIButton*)obj;
	int _bTag = bTag->getTag();
	if(type == TOUCH_EVENT_ENDED)
		switch(_bTag)
		{
		case t_ready:
			{
					boost::shared_ptr<ISFSObject> parameter (new SFSObject());
					boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
					boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_READY_REQ),parameter,lastRoom));
					GameServer::getSingleton().getSmartFox()->Send(request);
					CCLog("CLICK READY");
				break;
				}
		case t_unReady:
			{
				boost::shared_ptr<ISFSObject> params (new SFSObject());
				boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
				boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_UNREADY_REQ),params,lastRoom));
				GameServer::getSingleton().getSmartFox()->Send(request);
				CCLog("CLICK UNREADY");
				break;
			}
		case t_tom:
			{
				clickBet(t_tom);

				break;
			}
		case t_cua:
			{
				clickBet(t_cua);
				break;
			}
		case t_ca:
			{
				clickBet(t_ca);
				break;
			}
		case t_ga:
			{
				clickBet(t_ga);
				break;
			}
		case t_ruou:
			{
				clickBet(t_ruou);
				break;
			}
		case t_nai:
			{
				clickBet(t_nai);
				break;
			}
		}

}
void TomCuaCa::update(float dt)
{
	_count-=0.12;
	loading->setPercent(_count);
	if(_count<0){
		Chat *toast = new Chat("Khóa sổ rồi không đặt được nữa đâu!",-1);
		this->addChild(toast);
		}
}
void TomCuaCa::clickBet(int _tag)
{
	cocos2d::extension::CCBReader * ccbReader = NULL;
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);

	// register loaders
	ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
	ccNodeLoaderLibrary->registerCCNodeLoader("LayerBet_BaCayChuong",   LayerBet_TomCuaCaLoader::loader());
	// read main layer
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

	LayerBet_TomCuaCa *popUp;
	

	if (ccbReader)
	{
		popUp = (LayerBet_TomCuaCa *)ccbReader->readNodeGraphFromFile( "LayerBet_BaCayChuong.ccbi" );
		popUp->setPosition(ccp(10,10));
		popUp->getAID(_tag);
		uLayer->addChild(popUp);
		ccbReader->release();
	}
	switch(_tag)
		{
		case t_tom:
			CCLog("bet Tom");
			break;
		case t_cua:
			CCLog("bet cua");
			break;
		case t_ca:
			CCLog("bet ca");
			break;
		case t_ga:
			CCLog("bet ga");
			break;
		case t_ruou:
			CCLog("bet ruou");
			break;
		case t_nai:
			CCLog("bet nai");
			break;
		}
}
void TomCuaCa::bet(int aid, string tienBet)
{
	switch (aid) {
	case 1:
		betNai->setValueBet((tienBet+" $").c_str());
		break;
	case 2:
		betRuou->setValueBet((tienBet+" $").c_str());
		break;
	case 3:
		betGa->setValueBet((tienBet+" $").c_str());
		break;
	case 4:
		betCa->setValueBet((tienBet+" $").c_str());
		break;
	case 5:
		betCua->setValueBet((tienBet+" $").c_str());
		break;
	case 6:
		betTom->setValueBet((tienBet+" $").c_str());
		break;
	default:
		break;
	}

}
void TomCuaCa::setTimer(float dt)
{
		
}
void TomCuaCa::hienKetQua()
{
	NumberInTomCuaCa *layerNumbers = NumberInTomCuaCa::create();
	this->addChild(layerNumbers);
	vector<string> _kq = TCCsplit(*kq, ';');
	for(int i=0;i<_kq.size();i++)
	{
		vector<string> info = TCCsplit(_kq[i], '@');
		string _temp =info[1];
		string _money="";
		string _dola="";

			if(_temp[0]!='-'){_money="+"+info[1]+_dola;}
			else{_money=info[1]+_dola;}

		if(strcmp(info[0].c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0)
		{
			//layerChat->showChatByPos(kUserMe,(info[1]+" Điểm"));
			layerNumbers->showNumberByPos(kUserMe, _money);
			CCLog("me");
		}
		else{
			switch (getPosUserByName(info[0], _list_user))
			{
			case kUserLeft:
				layerNumbers->showNumberByPos(kUserLeft,_money);
				CCLog("left");
				break;
			case kUserRight:
				layerNumbers->showNumberByPos(kUserRight, _money);
				CCLog("righ");
				break;
			case kUserTop:
				layerNumbers->showNumberByPos(kUserTop, _money);
				CCLog("top");
				break;
			case kUserBot:
				layerNumbers->showNumberByPos(kUserBot, _money);
				CCLog("bot");
				break;
			default:
				break;
			}//switch
			}//else
	}//for
}//void
void TomCuaCa::hienOketqua()
{
	CCLog("here");
	if(kq1=="1" || kq2=="1" || kq3=="1")
		btnNai->setBright(false);
	if(kq1=="2" || kq2=="2" || kq3=="2")
		btnRuou->setBright(false);
	if(kq1=="3" || kq2=="3" || kq3=="3")
		btnGa->setBright(false);
	if(kq1=="4" || kq2=="4" || kq3=="4")
		btnCa->setBright(false);
	if(kq1=="5" || kq2=="5" || kq3=="5")
		btnCua->setBright(false);
	if(kq1=="6" || kq2=="6" || kq3=="6")
		btnTom->setBright(false);
}
void TomCuaCa::onExit()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(
		"sounds/game_tomcuaca/background.mp3");
		}