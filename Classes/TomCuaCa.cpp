//
//  TomCuaCa.cpp
//  iCasino_v2
//
//  Created by Tuan on 6/23/14.
//
//
#include "TomCuaCa.h"
#include "_Avatar_.h"
#include "_Background_inGame_.h"
#include "_Button_inGame_.h"
#include "Requests/ExtensionRequest.h"
#include "_Number_inTomCuaCa.h"
#include "mUtils.h"
#include "_Chat_.h"
#include "SceneManager.h"
#include "LayerBet_TomCuaCa.h"
#include "SliderCustomLoader.h"
#include "Requests/LeaveRoomRequest.h"

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
	EXT_EVENT_GAME_BET_NTF,			//= "gb_ntf"
	EXT_REQUEST_TOKEN				// = "ire"
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
	if (inString == "gb_ntf")	return EXT_EVENT_GAME_BET_NTF;

	if (inString == "e")		return EXT_EVENT_END;
	if (inString == "cblltf")   return EXT_EVENT_AMF_TEST_NOTIF;
	if (inString == "vicntf")   return EXT_EVENT_VICTORY_NOTIF;
	if (inString == "ire")		return EXT_REQUEST_TOKEN;

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
	if (inInt == EXT_REQUEST_TOKEN)           return "ire";

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


	if(mUtils::isSoundOn())
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/game_tomcuaca/back.mp3",true);
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
		
		
		
		//frame bet
		betTom = FrameBet::create();
		betTom->setPosition(218,238);
		
		betTom->setValueBet("  Cược");
		uLayer->addChild(betTom);
		
		betCua = FrameBet::create();
		betCua->setPosition(358,238);
		betCua->setValueBet("  Cược");
		uLayer->addChild(betCua);

		betCa = FrameBet::create();
		betCa->setPosition(498,238);
		betCa->setValueBet("  Cược");
		uLayer->addChild(betCa);

		betGa = FrameBet::create();
		betGa->setPosition(218,118);
		betGa->setValueBet("  Cược");
		uLayer->addChild(betGa);

		betRuou = FrameBet::create();
		betRuou->setPosition(358,118);
		betRuou->setValueBet("  Cược");
		uLayer->addChild(betRuou);

		betNai = FrameBet::create();
		betNai->setPosition(498,118);
		betNai->setValueBet("  Cược");
		uLayer->addChild(betNai);
		
	GameServer::getSingleton().addListeners(this);
	createBackgrounds();
	createAvatars();
	createButtons();
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
    lAvatar->setListUser(list);
	vector<string> listUser;
	listUser = TCCsplit(list, ';');
	CCLOG("Do dai: %ld",listUser.size());
	
	boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
    isSpector = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())->IsSpectator();
    isSpector=lAvatar->isSpect();
    if(lAvatar->isSpect()==true)
    {
		nameGame->setString("Bạn đang xem...");
		
        if(listUser.size()<7)
        {
            CCLog("here");
           if(lAvatar->isStartedGame()!=true)
                lAvatar->specToPlayer();
            
        }
        else
        {
            lAvatar->btn_dungday->setEnabled(false);
            lAvatar->btn_vaochoi->setEnabled(false);
            lAvatar->btn_vaochoi->setTouchEnabled(false);
            lButton->getButtonByTag(103)->setTouchEnabled(true);
            
        }
        
        specMode();
    }else
    {
        nameGame->setString(result.c_str());
        if(lAvatar->isStartedGame()!=true)
            lAvatar->playerToSpec();
        btnReady->setTouchEnabled(true);
        btnUnReady->setTouchEnabled(true);
        btnTom->setTouchEnabled(true);
        btnCua->setTouchEnabled(true);
        btnCa->setTouchEnabled(true);
        btnGa->setTouchEnabled(true);
        btnRuou->setTouchEnabled(true);
        btnNai->setTouchEnabled(true);
        
    }
	
    if(strcmp(list.c_str(),"")==0)
    {
        CCLog("return here");
        lAvatar->setPosChuong(-1);
        return;
    }
    lAvatar->setPosChuong(lAvatar->getPosByName(find_ChuPhong(list)));
	if(strcmp(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(), (find_ChuPhong(list).c_str())) == 0)
	{
        _time=1;
        lAvatar->setFlag(kuser0, true);
		//lButton->getButtonByTag(dTag_btnBet)->setEnabled(false);
		btnReady->setTitleText("Bắt đầu");
	}
	else
	{
		//lButton->getButtonByTag(dTag_btnBet)->setEnabled(true);
        btnReady->setTitleText("Sẵn sàng");
	}

   /* if(strcmp(list.c_str(),"")==0)
    {
        CCLog("return here");
        return;
    }
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
		double mon;
		int _money = 0;
		string _name = "";
		string _url = "";

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("amf")->GetDoubleValue();
		boost::shared_ptr<string> url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("aal")->GetStringValue();
		if (name != NULL) {
			_name = name->c_str();
		}
		if(money != NULL){
			_money = (int)*money;
			mon= (int)*money;
		}
		if (url != NULL) {
			_url=url->c_str();
		}

        if(strcmp(n[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			
            lAvatar->getUserByPos(kuser0)->setVisibleLayerInvite(false);
			lAvatar->setName(kuser0, _name.c_str());
			lAvatar->getUserByPos(kuser0)->setMoney(mon);
			lAvatar->getUserByPos(kuser0)->setIcon(_url);
			lAvatar->getUserByPos(kuser0)->setAI(n[0]);

			if(n[0]==find_ChuPhong(_list_user)){
				lAvatar->setPosChuong(kuser0);
				_time=1;
				lAvatar->setFlag(kuser0, true);
				btnReady->setTitleText("Bắt đầu");
				}
			else{
				btnReady->setTitleText("Sẵn sàng");
				}
		}
		else{
			
			switch (getPosUserByName(n[0], _list_user)) {
			case kuser3:
				lAvatar->getUserByPos(kuser3)->setVisibleLayerInvite(false);
				lAvatar->setName(kuser3, _name.c_str());
				lAvatar->getUserByPos(kuser3)->setMoney(mon);
				lAvatar->getUserByPos(kuser3)->setIcon(_url);
				lAvatar->getUserByPos(kuser3)->setAI(n[0]);
				if(n[0]==find_ChuPhong(_list_user)){
					lAvatar->setFlag(kuser3, true);
					lAvatar->setPosChuong(kuser3);
					_time=0;
				}
				break;
			case kuser4:
				lAvatar->getUserByPos(kuser4)->setVisibleLayerInvite(false);
				lAvatar->setName(kuser4, _name.c_str());
				lAvatar->getUserByPos(kuser4)->setMoney(mon);
				lAvatar->getUserByPos(kuser4)->setIcon(_url);
				lAvatar->getUserByPos(kuser4)->setAI(n[0]);
				if(n[0]==find_ChuPhong(_list_user)){
					lAvatar->setFlag(kuser4, true);
					lAvatar->setPosChuong(kuser4);
					_time=0;
				}
				break;
			case kuser1:
				lAvatar->getUserByPos(kuser1)->setVisibleLayerInvite(false);
				lAvatar->setName(kuser1, _name.c_str());
				lAvatar->getUserByPos(kuser1)->setMoney(mon);
				lAvatar->getUserByPos(kuser1)->setIcon(_url);
				lAvatar->getUserByPos(kuser1)->setAI(n[0]);
				if(n[0]==find_ChuPhong(_list_user)){
					lAvatar->setFlag(kuser1, true);
					lAvatar->setPosChuong(kuser1);
					_time=0;
				}
				break;
			case kuser2:
				lAvatar->getUserByPos(kuser2)->setVisibleLayerInvite(false);
				lAvatar->setName(kuser2, _name.c_str());
				lAvatar->getUserByPos(kuser2)->setMoney(mon);
				lAvatar->getUserByPos(kuser2)->setIcon(_url);
				lAvatar->getUserByPos(kuser2)->setAI(n[0]);
				if(n[0]==find_ChuPhong(_list_user)){
					lAvatar->setFlag(kuser2, true);
					lAvatar->setPosChuong(kuser2);
					_time=0;
				}
                break;
                case kuser5:
                    lAvatar->getUserByPos(kuser5)->setVisibleLayerInvite(false);
                    lAvatar->setName(kuser5, _name.c_str());
                    lAvatar->getUserByPos(kuser5)->setMoney(mon);
                    lAvatar->getUserByPos(kuser5)->setIcon(_url);
                    lAvatar->getUserByPos(kuser5)->setAI(n[0]);
                    if(n[0]==find_ChuPhong(_list_user)){
                        lAvatar->setFlag(kuser5, true);
                        lAvatar->setPosChuong(kuser5);
                        _time=0;
                    }
                    break;
			}//switch
			//else
		}
	}*/
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
		else
			vt=0;
	}
	// từ đó tìm vị trí của id truyền vào (so với mình)
	for(int k=0;k<list.size();k++){
		if(strcmp(list[k].c_str(), "")==0)
			continue;
		string player = list[k];
		vector<string> n = TCCsplit(player, '|');
		if(strcmp(n[0].c_str(), uid.c_str())==0){
			if(k==vt){
				return kuser0;
			}
			else if(k==(vt+1)%6){
				return kuser1;
			}
			else if(k==(vt+2)%6){
				return kuser2;
			}
			else if(k==(vt+3)%6){
				return kuser3;
			}
			else if(k==(vt+4)%6){
				return kuser4;
			}
            else if(k==(vt+5)%6){
				return kuser5;
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
		lAvatar->getUserByPos(kuser0)->setReady(true);
	}else{
		switch (getPosUserByName(uid, _list_user)) {
		case kuser3:
			lAvatar->getUserByPos(kuser3)->setReady(true);
			break;
		case kuser4:
			lAvatar->getUserByPos(kuser4)->setReady(true);
			break;
		case kuser1:
			lAvatar->getUserByPos(kuser1)->setReady(true);
			break;
		case kuser2:
			lAvatar->getUserByPos(kuser2)->setReady(true);
			break;
            case kuser5:
                lAvatar->getUserByPos(kuser5)->setReady(true);
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
			lAvatar->setReady(kuser0,false);
			btnReady->setTouchEnabled(true);
			btnReady->setVisible(true);
		
		}
		else{
			switch (getPosUserByName(uid, _list_user)) {
			case kuser3:
				lAvatar->setReady(kuser3,false);
				break;
			case kuser4:
				lAvatar->setReady(kuser4,false);
				break;
			case kuser1:
				lAvatar->setReady(kuser1,false);
				break;
			case kuser2:
				lAvatar->setReady(kuser2,false);
				break;
                case kuser5:
                    lAvatar->setReady(kuser5,false);
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

	this->scheduleUpdate();
	

	Chat *toast = new Chat("Đặt cược đê các bác...", -1);
	this->addChild(toast);

	CCLog("Game start");
	
}
void TomCuaCa::whenResuiltGame(string rg){

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("sounds/game_tomcuaca/back.mp3");
	this->unscheduleUpdate();
	loading->setPercent(0);
	playSound("sounds/game_tomcuaca/quay.mp3");
	
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
	_count=100;
	loading->setPercent(_count);
	btnReady -> setTouchEnabled(true);
	btnReady->setVisible(true);
	btnUnReady->setTouchEnabled(false);
	btnUnReady->setVisible(false);

	
	scroll1->scrollToTop(0.1,false);

	scroll2->scrollToTop(0.1,false);

	scroll3->scrollToTop(0.1,false);

	betTom->setValueBet("  Cược");
	betCua->setValueBet("  Cược");
	betCa->setValueBet("  Cược");
	betGa->setValueBet("  Cược");
	betRuou->setValueBet("  Cược");
	betNai->setValueBet("  Cược");

	CCLog("End game");
	btnTom->setBright(true);
	btnCua->setBright(true);
	btnCa->setBright(true);
	btnGa->setBright(true);
	btnRuou->setBright(true);
	btnNai->setBright(true);
	lAvatar->setReady(kuser0,false);
	lAvatar->setReady(kuser1,false);
	lAvatar->setReady(kuser3,false);
	lAvatar->setReady(kuser4,false);
	lAvatar->setReady(kuser2,false);
	if(mUtils::isSoundOn())
		{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/game_tomcuaca/back.mp3",true);
	}
}
TomCuaCa::~TomCuaCa(){
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("sounds/game_tomcuaca/back.mp3");
	GameServer::getSingleton().removeListeners(this);
	this->removeAllChildren();
	this->removeAllComponents();
	
}
bool TomCuaCa::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCLog("on init");
	for (int i = 0; i < arrName.size(); i++) {
		lAvatar->setMoney(lAvatar->getPosByName(arrName[i]), arrMoneyDouble[i]);
	}
    isSpector=false;
	arrName.clear();
	arrMoney.clear();
	arrMoneyDouble.clear();
	return true;
	lAvatar->setUnReadyAllUser();
}
void TomCuaCa::createBackgrounds(){

	CCSprite *bg = CCSprite::create("back.png");
	bg->setPosition(ccp(WIDTH_DESIGN/2,HEIGHT_DESIGN/2-20));
	this->addChild(bg);
	// thông tin bàn chơi và mức cược
	int id = atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str());
	boost::shared_ptr<string> param = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string paramString = param->c_str();
	vector<string> arrInfo = TCCsplit(paramString, '@');
	string money = arrInfo.at(0);

	mUtils mu;
	CCString *name = mUtils::getGameNameByID(id);
	
	string moneyConvert = mu.convertMoneyEx(atoi(money.c_str()));

	result = "";
	if (name->length() > 0 && moneyConvert.length() > 0)
	{
		result = name->getCString();
		result += (" - cược:" + moneyConvert);
	}
	nameGame= CCLabelTTF::create(result.c_str(), "", 16);
	nameGame->setPosition(ccp(400, 222));
	nameGame->setColor(ccWHITE);
	nameGame->setOpacity(150);
	uLayer->addChild(nameGame);
	
}
void TomCuaCa::createButtons(){

	lButton = LayerButtonInGame::create();
	uLayer->addChild(lButton);

}
void TomCuaCa::createAvatars(){
	//MY info

	lAvatar = AvatarInTomCuaCa::create();
    lAvatar->resetAll();
	uLayer->addChild(lAvatar);
	
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
							updateUser(_list_user);
                        

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
				CCLog("---O cuoc: %ld",*oCuoc);

				char _bet[20];
				sprintf (_bet, "%d", _tienBet);
				int _aid=0;
				_aid =int(*oCuoc);
				bet(_aid,_bet);

				break;
			}
		case EXT_REQUEST_TOKEN:
			{
			boost::shared_ptr<string> token = param->GetUtfString("ire");
			CCLog("----%s",token->c_str());

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
		Chat *toast = new Chat("Khóa sổ rồi ko đặt được nữa đâu!",-1);
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
		
		playSound("sounds/game_tomcuaca/datcuoc.mp3");
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

	double mon = atoi(tienBet.c_str());
	string bet_ = convertMoneyFromDouble_Detail(mon);
	CCLog("-----%s",bet_.c_str());
	switch (aid) {
	case 1:
		betNai->setValueBet((bet_+" $").c_str());
		break;
	case 2:
		betRuou->setValueBet((bet_+" $").c_str());
		break;
	case 3:
		betGa->setValueBet((bet_+" $").c_str());
		break;
	case 4:
		betCa->setValueBet((bet_+" $").c_str());
		break;
	case 5:
		betCua->setValueBet((bet_+" $").c_str());
		break;
	case 6:
		betTom->setValueBet((bet_+" $").c_str());
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
		
		//double mon =atoi(info[1].c_str());
		string _money="";

			if(_temp[0]!='-'){_money="+"+info[1];}
			else{_money=info[1];}

		if(strcmp(info[0].c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0)
		{
			
			layerNumbers->showNumberByPos(kuser0, _money);
			if(_temp[0]!='-'){
				
				playSound("sounds/game_tomcuaca/win.mp3");
			}
			else{
				
				playSound("sounds/game_tomcuaca/lose.mp3");
			}
			CCLog("me");
		}
		else{
			switch (getPosUserByName(info[0], _list_user))
			{
			case kuser3:
				layerNumbers->showNumberByPos(kuser3,_money);
				CCLog("left");
				break;
			case kuser4:
				layerNumbers->showNumberByPos(kuser4, _money);
				CCLog("righ");
				break;
			case kuser1:
				layerNumbers->showNumberByPos(kuser1, _money);
				CCLog("top");
				break;
			case kuser2:
				layerNumbers->showNumberByPos(kuser2, _money);
				CCLog("bot");
				break;
                case kuser5:
                    layerNumbers->showNumberByPos(kuser5, _money);
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
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("sounds/game_tomcuaca/back.mp3");
	GameServer::getSingleton().removeListeners(this);
	this->removeAllComponents();
	
}
void TomCuaCa::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
	//
	CCLOG("ptrNotifiedMessage: %s", ptrNotifiedMessage->c_str());
	int pos =getPosUserByName(ptrNotifiedUser->Name()->c_str(),_list_user);
	if (pos == -1)
	{
		return;
	}
	lAvatar->showChatByPos(pos, ptrNotifiedMessage->c_str());
	playSound("sounds/game_tomcuaca/chat.mp3");
}
void TomCuaCa::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	CCLOG("User ExitRoom On Room");
	
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	//
	if( ptrNotifiedUser->IsItMe() ){
		//close window - tricks by HoangDD
		lButton->eventTouchBtnBack(NULL, TOUCH_EVENT_ENDED);
		CCLog("im exit");
	}
	updateUser(_list_user);
}

void TomCuaCa::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	//CCLOG("Update User Variables");
	//boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	//boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	//boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);

	////string money = boost::to_string(*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
	//int    money = (int) (*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
	//double moneyDouble = (*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
	//string name = boost::to_string(*ptrNotifiedUser->Name());
	//CCLog("OnSmartFoxUserVariableUpdate: name= %s, money= %d", name.c_str(), money);
	//arrName.push_back(name);
	//arrMoney.push_back(money);
	//arrMoneyDouble.push_back(moneyDouble);
  //  isSpector = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())->IsSpectator();
    //isSpector = lAvatar->isSpect();

}
void TomCuaCa::playSound( string soundPath )
{
	if( mUtils::isSoundOn() )
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundPath.c_str());
}
string TomCuaCa::convertMoney(int money){

	ostringstream oss;
	/// 
	if (money < 1000) {
		oss.clear();
		oss<<money;
		return (oss.str() + "");
	}
	else if (money >= 1000 && money <= 999999) {
		string hangTram;
		string hangNghin;

		ostringstream oss1;
		// Nghin
		oss1.clear();
		oss1<<(money / 1000);
		hangNghin = oss1.str();

		ostringstream oss2;
		// tram
		int hTram = (money % 1000);
		oss2.clear();
		oss2<<hTram;
		if (hTram < 10) {
			hangTram = "00";
		}
		else if (hTram >= 10 && hTram < 100) {
			hangTram = "0";
		}
		hangTram += oss2.str();

		return (hangNghin + "," + hangTram + "");
	}
	else if (money >= 1000000) {
		string hangTrieu;
		string hangNghin;
		string hangTram;

		ostringstream oss1;
		// Trieu
		oss1.clear();
		oss1<<(money / 1000000);
		hangTrieu = oss1.str();

		// Nghin
		int hNghin = (money - (money / 1000000) * 1000000) / 1000;
		ostringstream oss2;
		oss2.clear();
		oss2<<hNghin;

		if (hNghin < 10)
		{
			hangNghin = "00";
		}
		else if (hNghin >= 10 && hNghin < 100)
		{
			hangNghin = "0";
		}
		hangNghin += oss2.str();

		// Tram
		int hTram = (money % 1000);
		ostringstream oss3;
		oss3.clear();
		oss3<<hTram;

		if (hTram < 10)
		{
			hangTram = "00";
		}
		else if (hTram >= 10 && hTram < 100)
		{
			hangTram = "0";
		}
		hangTram += oss3.str();

		return (hangTrieu + "," + hangNghin + "," + hangTram + "");
	}

	return "";
}

string TomCuaCa::convertMoneyFromDouble(double money) {
	// tiền tỷ
	if (money >= 1000000000) {
		int ti = money / 1000000000;
		ostringstream os;
		os<<ti;
		return (os.str() + " tỷ");
	} else if (money >= 1000000) {
		// tiền triệu
		int ti = money / 1000000;
		ostringstream os;
		os<<ti;
		return (os.str() + " triệu");
	} else if (money >= 1000) {
		string hangTram;
		string hangNghin;

		// Nghin
		ostringstream oss1;
		oss1.clear();
		oss1<<(int)(money / 1000);
		hangNghin = oss1.str();

		ostringstream oss2;
		// tram
		int hTram = ((int)money % 1000);
		oss2.clear();
		oss2<<hTram;
		if (hTram < 10) {
			hangTram = "00";
		}
		else if (hTram >= 10 && hTram < 100) {
			hangTram = "0";
		}
		hangTram += oss2.str();

		return (hangNghin + "," + hangTram + " xu");
	} else {
		ostringstream os;
		os<<money;
		return (os.str() + " xu");
	}

	return "!";
}

string TomCuaCa::convertMoneyFromDouble_Detail(double money) {
	if (money < 1000) {
		ostringstream os;
		os<<money;
		return (os.str());
	}
	else {
		money = money / 1000;

		if (money > 2000000000) {
			return convertMoneyFromDouble(money * 1000);
		}
		else return (convertMoney((int)money) + "k");
	}


}
void TomCuaCa::specMode()
{
	CCLog("spec mode");
    
	btnReady->setEnabled(false);
    btnUnReady->setEnabled(false);
    lButton->getButtonByTag(103)->setTouchEnabled(true);
    
    
    btnReady->setTouchEnabled(false);
    btnUnReady->setTouchEnabled(false);
    btnTom->setTouchEnabled(false);
    btnCua->setTouchEnabled(false);
    btnCa->setTouchEnabled(false);
    btnGa->setTouchEnabled(false);
    btnRuou->setTouchEnabled(false);
    btnNai->setTouchEnabled(false);
   
    
}