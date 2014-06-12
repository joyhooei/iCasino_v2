//
//  Lieng.cpp
//  iCasinov2
//
//  Created by DauA on 5/27/14.
//
//

#include "Lieng.h"
#include "_Background_inGame_.h"
#include "_Button_inGame_.h"
#include "_Number_inGame_.h"
#include "Requests/ExtensionRequest.h"
#include "CardChan.h"
#include "Nan3Cay.h"
#include "LayerBet_Lieng.h"
#include "SliderCustomLoader.h"
#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())


Lieng::Lieng():btnNanBai(NULL),btnReady(NULL),btnUnReady(NULL),btnXemBai(NULL),btnTo(NULL),btnUp(NULL){
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
    GameServer::getSingleton().addListeners(this);

    left_Left = 117;
    left_Right = 539;
    left_Top = 328;
    left_Me = 319;
    
    width_card_me = 54;
    height_card_me = 54*1.3;
    height_card_notme = 48*1.3;
    width_card_notme = 48;
    
    bottom_me = 90;
    bottom_card_top = 268;
    bottom_card_l_r = 209;
    
    arrCardTypes[0] = "s";
    arrCardTypes[1] = "c";
    arrCardTypes[2] = "h";
    arrCardTypes[3] = "d";
    
    flagChiaBai = false;
    real = false;
    currentTo = "";
    currentBetal = "";
    demChiaBai = 0;
    
    string Bet = *GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
    string strBet =Dsplit(Bet, '@')[0];
    minBet = atoi(strBet.c_str());
	my_To = 0;
    
    createBackgrounds();
    createAvatars();
    createButtons();
    
    //*Khởi tạo các button trong game////
    uLayer = UILayer::create();
    uLayer->setAnchorPoint(ccp(0, 0));
    uLayer->setPosition(ccp(0, 0));
    this->addChild(uLayer);
    
    //Btn Ready
    btnReady = UIButton::create();
    btnReady->loadTextures("ready.png", "ready_selected.png", "");
    btnReady->setTitleText("Sẵn Sàng");
    btnReady->setAnchorPoint(ccp(0,0));
    btnReady->setPosition(ccp(WIDTH_DESIGN-btnReady->getContentSize().width-20,10));
    btnReady->setTouchEnabled(true);
    btnReady->addTouchEventListener(this, toucheventselector(Lieng::btn_ready_click));
    btnReady->setTitleFontSize(20);
    btnReady->setTitleColor(ccRED);
    uLayer->addWidget(btnReady);
    
    //Btn Unready
    btnUnReady = UIButton::create();
    btnUnReady->loadTextures("ready.png", "ready_selected.png", "");
    btnUnReady->setTitleText("Hủy Sẵn Sàng");
    btnUnReady->setAnchorPoint(ccp(0,0));
    btnUnReady->setPosition(ccp(WIDTH_DESIGN-btnUnReady->getContentSize().width-20,10));
    btnUnReady->setTouchEnabled(false);
    btnUnReady->addTouchEventListener(this, toucheventselector(Lieng::btn_Unready_click));
    btnUnReady->setTitleFontSize(20);
    btnUnReady->setTitleColor(ccRED);
    btnUnReady->setVisible(false);
    uLayer->addWidget(btnUnReady);
    
    //Btn Xem bài
    btnXemBai = UIButton::create();
    btnXemBai->loadTextures("ready.png", "ready_selected.png", "");
    btnXemBai->setTitleText("Xem Bài");
    btnXemBai->setAnchorPoint(ccp(0,0));
    btnXemBai->setPosition(ccp(WIDTH_DESIGN-btnXemBai->getContentSize().width-20,btnXemBai->getContentSize().height+20));
    btnXemBai->setTouchEnabled(false);
    btnXemBai->addTouchEventListener(this, toucheventselector(Lieng::btn_XemBai_click));
    btnXemBai->setVisible(false);
    btnXemBai->setTitleFontSize(20);
    btnXemBai->setTitleColor(ccRED);
    uLayer->addWidget(btnXemBai);
    
    //Btn_Nặn Bài
    btnNanBai = UIButton::create();
    btnNanBai->loadTextures("ready.png", "ready_selected.png", "");
    btnNanBai->setTitleText("Nặn Bài");
    btnNanBai->setAnchorPoint(ccp(0,0));
    btnNanBai->setPosition(ccp(WIDTH_DESIGN-btnNanBai->getContentSize().width-20,10));
    btnNanBai->setTouchEnabled(false);
    btnNanBai->addTouchEventListener(this, toucheventselector(Lieng::btn_NanBai_click));
    btnNanBai->setVisible(false);
    btnNanBai->setTitleFontSize(20);
    btnNanBai->setTitleColor(ccRED);
    uLayer->addWidget(btnNanBai);
    
    //Btn Theo
    btnTheo = UIButton::create();
    btnTheo->loadTextures("ready.png", "ready_selected.png", "");
    btnTheo->setTitleText("Theo");
    btnTheo->setAnchorPoint(ccp(0,0));
    btnTheo->setPosition(ccp(WIDTH_DESIGN-btnTheo->getContentSize().width*2-30,btnTheo->getContentSize().height+20));
    btnTheo->setTouchEnabled(false);
    btnTheo->addTouchEventListener(this, toucheventselector(Lieng::btn_Theo_click));
    btnTheo->setVisible(false);
    btnTheo->setTitleFontSize(20);
    btnTheo->setTitleColor(ccRED);
    uLayer->addWidget(btnTheo);
    
    //Btn Tố
    btnTo = UIButton::create();
    btnTo->loadTextures("ready.png", "ready_selected.png", "");
    btnTo->setTitleText("Tố");
    btnTo->setAnchorPoint(ccp(0,0));
    btnTo->setPosition(ccp(WIDTH_DESIGN-btnTo->getContentSize().width*2-30,10));
    btnTo->setTouchEnabled(false);
    btnTo->addTouchEventListener(this, toucheventselector(Lieng::btn_To_click));
    btnTo->setVisible(false);
    btnTo->setTitleFontSize(20);
    btnTo->setTitleColor(ccRED);
    uLayer->addWidget(btnTo);
    
    //Btn Úp
    btnUp = UIButton::create();
    btnUp->loadTextures("ready.png", "ready_selected.png", "");
    btnUp->setTitleText("Úp Bài");
    btnUp->setAnchorPoint(ccp(0,0));
    btnUp->setPosition(ccp(WIDTH_DESIGN-btnUp->getContentSize().width*3-40,10));
    btnUp->setTouchEnabled(true);
    btnUp->addTouchEventListener(this, toucheventselector(Lieng::btn_Up_click));
    btnUp->setVisible(false);
    btnUp->setTitleFontSize(20);
    btnUp->setTitleColor(ccRED);
    uLayer->addWidget(btnUp);
    
    frameBet_Me = FrameBet::create();
    frameBet_Right = FrameBet::create();
    frameBet_Top = FrameBet::create();
    frameBet_Left = FrameBet::create();
    
    frameBet_Me->setVisible(false);
    frameBet_Right->setVisible(false);
    frameBet_Top->setVisible(false);
    frameBet_Left->setVisible(false);
    
    this->addChild(frameBet_Me);
    this->addChild(frameBet_Right);
    this->addChild(frameBet_Top);
    this->addChild(frameBet_Left);
    
    //Khởi tạo mảng các lá bài
    CARD_ME = new CCArray();
    CARD_LEFT = new CCArray();
    CARD_RIGHT = new CCArray();
    CARD_TOP = new CCArray();

	CARD_ME->retain();
	CARD_LEFT->retain();
	CARD_RIGHT->retain();
	CARD_TOP->retain();
}

Lieng::~Lieng(){
    GameServer::getSingleton().removeListeners(this);
	CARD_TOP->removeAllObjects();
	CARD_ME->removeAllObjects();
	CARD_LEFT->removeAllObjects();
	CARD_RIGHT->removeAllObjects();
    CCLOG("Deconstructor Lieng ------ JumpHere");
}


void Lieng::createBackgrounds(){
    BackgroundInGame *bg = BackgroundInGame::create();
    this->addChild(bg);
}
void Lieng::createAvatars(){
    layerAvatars = LayerAvatarInGame::create();
    layerAvatars->resetAll();
    this->addChild(layerAvatars);
}
void Lieng::createButtons(){
    LayerButtonInGame *button_ingame = LayerButtonInGame::create();
    this->addChild(button_ingame);
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
    
    //List user update
    if(strcmp(EXT_EVENT_LIST_USER_UPDATE.c_str(), cmd->c_str())==0){
        boost::shared_ptr<string> lu = param->GetUtfString("lu");
        CCLOG("List user: %s",lu->c_str());
		if (lu != NULL)
		{
			_list_user = lu->c_str();
		}
		if (checkPlaying(_list_user))
		{
			real = true;
			flagChiaBai = true;
		}
        action_UpdateListUser(_list_user);
		action_UserRejoinGame(_list_user);
    }
    
    //User ready
    else if(strcmp(EXT_EVENT_READY_NTF.c_str(), cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
		string _uid = "";
		if (uid != NULL)
		{
			_uid = uid->c_str();
		}
        whenUserReady(_uid);
		CCLOG("EXT_EVENT_READY_NTF");
    }
    
    //User Unready
    else if(strcmp("urntf", cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
		string _uid = "";
		if (uid != NULL)
		{
			_uid = uid->c_str();
		}
        whenUserUnready(_uid);
		CCLOG("EXT_EVENT_UN_READY_NTF");
    }
    
    else if(strcmp("nt",cmd->c_str())==0){
        //"uid":"dautv3","mb":1000,"betal":"4,1,2"
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
            action_ChiaBai();
        }
        else{
            action_To(currentTo, currentBetal);
        }
        real = true;
    }
    
    // Game Start
    else if(strcmp(EXT_EVENT_START.c_str(), cmd->c_str())==0){
		whenGameStart();
		CCLOG("GAME_EVENT_START");
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

		CCLOG("List card: %s",_lc.c_str() );
		CCLOG("flagChiaBai: %d",flagChiaBai);
        if(flagChiaBai){
			action_LatBai(_lc, _uid, _tua);
        }
		
		CCLOG("EXT_EVENT_LISTCARD_NTF");
    }
    
    // Game End
    else if(strcmp(EXT_EVENT_END.c_str(), cmd->c_str())==0){
        this->whenGameEnd();
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

	boost::shared_ptr<double> money = ptrNotifiedUser->GetVariable("amf")->GetDoubleValue();
	boost::shared_ptr<string> uid = (ptrNotifiedUser->Name());

	if(uid == NULL || money == NULL)
		return;

	int _money = (int)(*money);
	string _uid = uid->c_str();

	switch (getPosUserByName(_uid, _list_user)) {
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

void Lieng::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}

void Lieng::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}

void Lieng::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}

vector<string> Lieng::Dsplit(string &S,const char &str){
    vector<string> arrStr;
    string::iterator t,t2;
    for(t=S.begin();t<S.end();){
        t2=find(t, S.end(),str);
        if(t!=t2)
			arrStr.push_back(string(t,t2));
		if(t2 == S.end())
			break;
        t=t2+1;
    }
    return arrStr;
}

//Action Latbai
void Lieng::action_LatBai(string listCard,string uid, bool tua){
	CCLOG("List cards action lat bai: %s",listCard.c_str());
	if (strcmp(uid.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0)
	{
		createCardMe(listCard);
		btnNanBai->setTouchEnabled(false);
		btnNanBai->setVisible(false);
		btnXemBai->setTouchEnabled(false);
		btnXemBai->setVisible(false);
	}
	else
	{
		switch(getPosUserByName(uid,_list_user)){
			case kUserLeft:
				createCardLeft(listCard);
				break;
			case kUserRight:
				createCardRight(listCard);
				break;
			case kUserTop:
				createCardTop(listCard);
				break;
			default:break;
		}
	}
}

void Lieng::createCardMe(string lc){
	vector<string> lsCards = Dsplit(lc,'-');
	CCLOG("list cards me: %s",lc.c_str());
	CCLOG("size Me: %ld",lsCards.size());
	CCLOG("Array me: %d",CARD_ME->count());

	if(CARD_ME->count()!=3){
		deleteAllCardFromArray(CARD_ME);
		restoreListCard(CARD_ME, width_card_me, height_card_me, left_Me, bottom_me);
	}

	for(int i=0;i<lsCards.size();i++){
		CardChan *pCard = (CardChan*)CARD_ME->objectAtIndex(i);
		if(strcmp(lsCards[i].c_str(), "0_0")==0){
			pCard->loadTexture("card_back.png");
		}
		else{
			vector<string> info = Dsplit(lsCards[i], '_');
			string t = "card_"+findTypeCard(info[0])+"_"+arrCardTypes[atoi(info[1].c_str())]+".png";
			pCard->loadTexture(t.c_str());
		}
	}
}

void Lieng::createCardLeft(string lc){
	vector<string> lsCards = Dsplit(lc,'-');
	CCLOG("size Left: %ld",lsCards.size());
	CCLOG("Array Left: %d",CARD_LEFT->count());
	if(CARD_LEFT->count()!=3){
		deleteAllCardFromArray(CARD_LEFT);
		restoreListCard(CARD_LEFT, width_card_notme, height_card_notme, left_Left, bottom_card_l_r);
	}
	for(int i=0;i<lsCards.size();i++){
		CardChan *pCard = (CardChan*)CARD_LEFT->objectAtIndex(i);
		if(strcmp(lsCards[i].c_str(), "0_0")==0){
			pCard->loadTexture("card_back.png");
		}
		else{
			vector<string> info = Dsplit(lsCards[i], '_');
			string t = "card_"+findTypeCard(info[0])+"_"+arrCardTypes[atoi(info[1].c_str())]+".png";
			pCard->loadTexture(t.c_str());
		}
	}
}

void Lieng::createCardRight(string lc){
	vector<string> lsCards = Dsplit(lc,'-');
	CCLOG("size Right: %ld",lsCards.size());
	CCLOG("Array Right: %d",CARD_RIGHT->count());
	if(CARD_RIGHT->count()!=3){
		deleteAllCardFromArray(CARD_RIGHT);
		restoreListCard(CARD_RIGHT, width_card_notme, height_card_notme, left_Right, bottom_card_l_r);
	}
	for(int i=0;i<lsCards.size();i++){
		CardChan *pCard = (CardChan*)CARD_RIGHT->objectAtIndex(i);
		if(strcmp(lsCards[i].c_str(), "0_0")==0){
			pCard->loadTexture("card_back.png");
		}
		else{
			vector<string> info = Dsplit(lsCards[i], '_');
			string t = "card_"+findTypeCard(info[0])+"_"+arrCardTypes[atoi(info[1].c_str())]+".png";
			pCard->loadTexture(t.c_str());
		}
	}
}

void Lieng::createCardTop(string lc){
	vector<string> lsCards = Dsplit(lc,'-');
	CCLOG("size Top: %ld",lsCards.size());
	CCLOG("Array Top: %d",CARD_TOP->count());
	if(CARD_TOP->count()!=3){
		deleteAllCardFromArray(CARD_TOP);
		restoreListCard(CARD_TOP, width_card_notme, height_card_notme, left_Top, bottom_card_top);
	}
	for(int i=0;i<lsCards.size();i++){
		CardChan *pCard = (CardChan*)CARD_TOP->objectAtIndex(i);
		if(strcmp(lsCards[i].c_str(), "0_0")==0){
			pCard->loadTexture("card_back.png");
		}
		else{
			vector<string> info = Dsplit(lsCards[i], '_');
			string t = "card_"+findTypeCard(info[0])+"_"+arrCardTypes[atoi(info[1].c_str())]+".png";
			pCard->loadTexture(t.c_str());
		}
	}
}

void Lieng::restoreListCard(CCArray *P,float _widtd, float _height, float _left, float _bottom){
	for(int i=0;i<3;i++){
		CardChan *pCard = CardChan::create();
		pCard->loadTexture("card_back.png");
		pCard->setSizeCard(_widtd, _height);
		pCard->setPosition(ccp(_left+i*_widtd,_bottom));
		P->addObject(pCard);
		uLayer->addChild(pCard);
	}
}

void Lieng::deleteAllCardFromArray(cocos2d::CCArray *P){
	if (P == NULL || P->count() == 0)
	{
		return;
	}
	while(P->count()>0){
		CardChan *uu = (CardChan*)P->objectAtIndex(P->count()-1);
		P->removeObject(uu);
		uu->removeFromParentAndCleanup(true);
	}
}

string Lieng::findTypeCard(string card){
	if(card == "11"){
		card = "j";
	}
	else if(card=="1"){
		card = "a";
	}
	else if (card == "12"){
		card = "q";
	}
	else if (card ==  "13"){
		card = "k";
	}
	return card;
}

void Lieng::action_UpdateListUser(string lsUser){
    //List user: dautv4|0|0;dautv3|0|0;
    layerAvatars->resetAll();
    
    frameBet_Me->setVisible(false);
    frameBet_Right->setVisible(false);
    frameBet_Top->setVisible(false);
    frameBet_Left->setVisible(false);
    
    vector<string> listUser;
    
    listUser = Dsplit(lsUser, ';');
    
    boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
    for(int i=0;i<listUser.size();i++){
        if(lastRoom==NULL){
            return;
        }
        if(listUser[i].c_str()==NULL)
            continue;
        string player = listUser[i];
        vector<string> n = Dsplit(player, '|');
        
        if(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])==NULL){
            continue;
        }

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("amf")->GetDoubleValue();
        string betValue = boost::to_string(minBet);
        
		int _money = 0;
		string _name = "";

		if (name != NULL)
		{
			_name = name->c_str();
		}

		if (money != NULL)
		{
			_money = (int)*money;
		}

        if(strcmp(n[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            layerAvatars->getUserByPos(kUserMe)->setName(_name);
            layerAvatars->getUserByPos(kUserMe)->setMoney(_money);
            
            if(n[0] == find_ChuPhong(_list_user)){
                layerAvatars->setFlag(kUserMe, true);
				btnReady->setTitleText("Chia Bài");
            }

			if (n[0] != find_ChuPhong(_list_user))
			{
				btnReady->setTitleText("Sẵn Sàng");
			}
            
            frameBet_Me->setValueBet((betValue+" $").c_str());
            frameBet_Me->setPosition(ccp(75,396));
            frameBet_Me->setVisible(true);
        }
        else{
            switch (getPosUserByName(n[0], _list_user)) {
                case kUserLeft:
					layerAvatars->getUserByPos(kUserLeft)->setVisibleLayerInvite(false);
					layerAvatars->getUserByPos(kUserLeft)->setName(_name);
                    layerAvatars->getUserByPos(kUserLeft)->setMoney(_money);

                    if(n[0] == find_ChuPhong(_list_user)){
                        layerAvatars->setFlag(kUserLeft, true);
                    }
                    
                    frameBet_Left->setValueBet((betValue+" $").c_str());
                    frameBet_Left->setPosition(ccp(109,278));
                    frameBet_Left->setVisible(true);
                    break;
                    
                case kUserRight:
					layerAvatars->getUserByPos(kUserRight)->setVisibleLayerInvite(false);
					layerAvatars->getUserByPos(kUserRight)->setName(_name);
					layerAvatars->getUserByPos(kUserRight)->setMoney(_money);
                    
                    if(n[0] == find_ChuPhong(_list_user)){
                        layerAvatars->setFlag(kUserRight, true);
                    }
                    
                    frameBet_Right->setValueBet((betValue+" $").c_str());
                    frameBet_Right->setPosition(ccp(WIDTH_DESIGN-109-frameBet_Right->getKc_width(),278));
                    frameBet_Right->setVisible(true);
                    break;
                    
                case kUserTop:
					layerAvatars->getUserByPos(kUserTop)->setVisibleLayerInvite(false);
					layerAvatars->getUserByPos(kUserTop)->setName(_name);
					layerAvatars->getUserByPos(kUserTop)->setMoney(_money);
                    
                    if(n[0] == find_ChuPhong(_list_user)){
                        layerAvatars->setFlag(kUserTop, true);
                    }
                    
                    frameBet_Top->setValueBet((betValue+" $").c_str());
                    frameBet_Top->setPosition(ccp(454, 440));
                    frameBet_Top->setVisible(true);
            }
        }
    }
}

void Lieng::action_UserRejoinGame(string lsUser){

	if (checkPlaying(lsUser))
	{
		moveButtonRight();
	}
	vector<string> list = Dsplit(lsUser,';');
	for (int i = 0; i < list.size(); i++)
	{
		vector<string> info = Dsplit(list[i],'|');
		if (strcmp(info[0].c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
		{
			if (checkPlaying(lsUser))
			{
				btnReady->setTouchEnabled(false);
				btnReady->setVisible(false);
			}

			if (CARD_ME->count() != 3 && info[2] != "0")
			{
				deleteAllCardFromArray(CARD_ME);
				restoreListCard(CARD_ME,width_card_me,height_card_me,left_Me,bottom_me);
			}
		}
		else
		{
			switch(getPosUserByName(info[0],_list_user))
			{
			case kUserLeft:
				if (CARD_LEFT->count() != 3 && info[2] != "0")
				{
					deleteAllCardFromArray(CARD_LEFT);
					restoreListCard(CARD_LEFT,width_card_notme,height_card_notme,left_Left,bottom_card_l_r);
				}
				break;
			case kUserRight:
				if (CARD_RIGHT->count() != 3 && info[2] != "0")
				{
					deleteAllCardFromArray(CARD_RIGHT);
					restoreListCard(CARD_RIGHT,width_card_notme,height_card_notme,left_Right,bottom_card_l_r);
				}
				break;
			case kUserTop:
				if (CARD_TOP->count() != 3 && info[2] != "0")
				{
					deleteAllCardFromArray(CARD_TOP);
					restoreListCard(CARD_TOP,width_card_notme,height_card_notme,left_Top,bottom_card_top);
				}
				break;
			}
		}

	}
}

bool Lieng::checkPlaying(string _list){
	vector<string> info = Dsplit(_list,';');
	if(Dsplit(info[0],'|')[2] == "1")
	{
		return true;
	}
	return false;
}


void Lieng::moveButtonRight(){
	btnTheo->setPosition(ccp(WIDTH_DESIGN - btnTheo->getContentSize().width - 20, btnTheo->getContentSize().height + 20));
	btnTo->setPosition(ccp(WIDTH_DESIGN - btnTo->getContentSize().width - 20, 10));
	btnUp->setPosition(ccp(WIDTH_DESIGN - btnUp->getContentSize().width*2 - 30, 10));
}

void Lieng::resetButtonLocation(){
	btnTheo->setPosition(ccp(WIDTH_DESIGN - btnTheo->getContentSize().width * 2 - 30, btnTheo->getContentSize().height + 20));
	btnTo->setPosition(ccp(WIDTH_DESIGN - btnTo->getContentSize().width * 2 - 30, 10));
	btnUp->setPosition(ccp(WIDTH_DESIGN - btnUp->getContentSize().width * 3 - 40, 10));
}

int Lieng::getPosUserByName(string uid,string _list_user){
    int vt = -1;
    vector<string> list;
    if(_list_user.c_str() != NULL && _list_user != ""){
        list = Dsplit(_list_user, ';');
    }
    //Tìm vị trí của mình trong list user
    for(int i=0;i<list.size();i++){
        string _id = Dsplit(list[i], '|')[0];
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
        vector<string> n = Dsplit(player, '|');
        if(strcmp(n[0].c_str(), uid.c_str())==0){
            if(k==vt){
                return kUserMe;
            }
            else if(k==(vt+1)%4){
                return kUserRight;
            }
            else if(k==(vt+2)%4){
                return kUserTop;
            }
            else if(k==(vt+3)%4){
                return kUserLeft;
            }
            break;
        }
    }
    return 0;
}

string Lieng::find_ChuPhong(string listUser){
    vector<string> arrUser = Dsplit(listUser,';');
    vector<string> info = Dsplit(arrUser[0], '|');
    string boosId = info[0];
    return boosId;
}

void Lieng::whenUserReady(string uid){
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        btnReady->setTouchEnabled(false);
        btnReady->setVisible(false);
        // hiện unready
        btnUnReady->setTouchEnabled(true);
        btnUnReady->setVisible(true);
		layerAvatars->getUserByPos(kUserMe)->setReady(true);
    }
    else{
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

void Lieng::whenUserUnready(string uid){
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        btnUnReady->setTouchEnabled(false);
        btnUnReady->setVisible(false);
        //hiện ready
		layerAvatars->getUserByPos(kUserMe)->setReady(false);
        btnReady->setTouchEnabled(true);
        btnReady->setVisible(true);
    }
    else{
        switch (getPosUserByName(uid, _list_user)) {
            case kUserLeft:
				layerAvatars->getUserByPos(kUserLeft)->setReady(false);
                break;
			case kUserRight:
				layerAvatars->getUserByPos(kUserRight)->setReady(false);
				break;
			case kUserTop:
				layerAvatars->getUserByPos(kUserTop)->setReady(false);
				break;
            default:
                break;
        }
    }
}

void Lieng::whenGameStart(){
	btnReady->setTouchEnabled(false);
	btnReady->setVisible(false);
	btnUnReady->setTouchEnabled(false);
	btnUnReady->setVisible(false);

	layerAvatars->setUnReadyAllUser();
}

void Lieng::whenGameEnd(){
    
    //Ẩn hiện các button cần thiết
    btnReady -> setTouchEnabled(true);
    btnReady->setVisible(true);
    
    btnUnReady->setTouchEnabled(false);
    btnUnReady->setVisible(false);
    btnXemBai->setTouchEnabled(false);
    btnXemBai->setVisible(false);
    btnNanBai->setTouchEnabled(false);
    btnNanBai->setVisible(false);
    btnUp->setVisible(false);
    btnUp->setTouchEnabled(false);
    btnTo->setTouchEnabled(false);
    btnTo->setVisible(false);
    btnTheo->setTouchEnabled(false);
    btnTheo->setVisible(false);
    
	resetButtonLocation();

	string Bet = *GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string strBet =Dsplit(Bet, '@')[0];
	minBet = atoi(strBet.c_str());
    
    flagChiaBai = false;
    _list_cards = "";
    demChiaBai = 0;
    real = false;
}

void Lieng::whenResuiltGame(string rg){
	layerAvatars->stopAllTimer();
	CCLOG("Resuilt Game: %s",rg.c_str());
	////"rg":"dautv5|1|8|3|2|1000;dautv3|1|8|7|3|1000"
	vector<string> resuilt = Dsplit(rg,';');
	LayerNumberInGame *layerNumbers = LayerNumberInGame::create();
	this->addChild(layerNumbers);
	for (int i = 0; i < resuilt.size(); i++)
	{
		vector<string> info = Dsplit(resuilt[i],'|');
		string money = "";
		if(i == 0)
		{
			money = ("+"+info[5]);
		}else{
			money = ("-"+info[5]);
		}

		if (strcmp(info[0].c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
		{
			layerNumbers->showNumberByPos(kUserMe,money);
		}
		else
		{
			switch(getPosUserByName(info[0],_list_user)){
			case kUserLeft:
				layerNumbers->showNumberByPos(kUserLeft,money);
				break;
			case kUserRight:
				layerNumbers->showNumberByPos(kUserRight,money);
				break;
			case kUserTop:
				layerNumbers->showNumberByPos(kUserTop,money);
				break;
			}
		}
	}
}

void Lieng::whenUserBet(string uid, long gameBet){
	if (strcmp(uid.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
	{
		frameBet_Me->setValueBet(boost::to_string(gameBet));
	}
	else
	{
		switch(getPosUserByName(uid,_list_user))
		{
		case kUserLeft:
			frameBet_Left->setValueBet(boost::to_string(gameBet));
			break;
		case kUserRight:
			frameBet_Right->setValueBet(boost::to_string(gameBet));
			break;
		case kUserTop:
			frameBet_Top->setValueBet(boost::to_string(gameBet));
			break;
		}
	}
}

void Lieng::action_ChiaBai(){
    //Tạo list user ảo
    string listuser = _list_user+_list_user+_list_user;
    vector<string> arrUser = Dsplit(listuser, ';');
    string player = arrUser[demChiaBai];
    vector<string> info = Dsplit(player, '|');
    if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        demChiaBai++;
        action_AddCard4User(CARD_ME, width_card_me, height_card_me, left_Me, bottom_me, arrUser.size());
    }
    else{
        switch (getPosUserByName(info[0], _list_user)) {
            case kUserLeft:
                demChiaBai++;
                action_AddCard4User(CARD_LEFT, width_card_notme, height_card_notme, left_Left, bottom_card_l_r, arrUser.size());
                break;
            case kUserRight:
                demChiaBai++;
                action_AddCard4User(CARD_RIGHT, width_card_notme, height_card_notme, left_Right, bottom_card_l_r, arrUser.size());
                break;
            case kUserTop:
                demChiaBai++;
                action_AddCard4User(CARD_TOP, width_card_notme, height_card_notme, left_Top, bottom_card_top, arrUser.size());
                break;
            default:
                break;
        }
    }
}

void Lieng::action_AddCard4User(CCArray *P,float _widtd, float _height, float toX, float toY, int countUSer){
    CardChan *card = CardChan::create();
    card->loadTexture("card_back.png");
    card->setSizeCard(width_card_notme, height_card_notme);
    card->setPosition(ccp(WIDTH_DESIGN/2-card->getContentSize().width/2,HEIGHT_DESIGN/2-card->getContentSize().height/2));
    uLayer->addChild(card);
    
    CCMoveBy *newTo = CCMoveTo::create(0.3, ccp(toX+P->count()*_widtd,toY));
    CCScaleBy *scaleTo = CCScaleBy::create(0.3, _widtd/width_card_notme,_height/height_card_notme);
    card->runAction(newTo);
    card->runAction(scaleTo);
    P->addObject(card);
    if(demChiaBai<countUSer){
        this->runAction(CCSequence::create(CCDelayTime::create(0.3),CCCallFunc::create(this, callfunc_selector(Lieng::action_ChiaBai)),NULL));
    }else{
        flagChiaBai = true;
        action_To(currentTo, currentBetal);
        btnNanBai->setTouchEnabled(true);
        btnNanBai->setVisible(true);
        btnXemBai->setVisible(true);
        btnXemBai->setTouchEnabled(true);
    }
}

void Lieng::action_To(string uid,string betal){
	layerAvatars->stopAllTimer();
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
		layerAvatars->getUserByPos(kUserMe)->startTimer();
        btnTo->setVisible(false);
        btnTo->setTouchEnabled(false);
        btnTheo->setVisible(false);
        btnTheo->setTouchEnabled(false);
        btnUp->setVisible(false);
        btnUp->setTouchEnabled(false);
        
        vector<string> typeBet = Dsplit(betal,',');
        for(int i=0;i<typeBet.size();i++){
            if(typeBet[i]=="1"){
                btnTo->setVisible(true);
                btnTo->setTouchEnabled(true);
            }
            else if (typeBet[i] == "2"){
                btnUp->setVisible(true);
                btnUp->setTouchEnabled(true);
            }
            else if (typeBet[i] == "3"){
                btnTheo->setVisible(true);
                btnTheo->setTouchEnabled(true);
            }
        }
    }
    else{
        btnTo->setVisible(false);
        btnTo->setTouchEnabled(false);
        btnTheo->setVisible(false);
        btnTheo->setTouchEnabled(false);
        btnUp->setVisible(false);
        btnUp->setTouchEnabled(false);
        //Count Down
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

void Lieng::btn_ready_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
		deleteAllCardFromArray(CARD_TOP);
		deleteAllCardFromArray(CARD_RIGHT);
		deleteAllCardFromArray(CARD_ME);
		deleteAllCardFromArray(CARD_LEFT);

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
		CCLOG("Xem Bai");
		if(_list_cards != ""){
			createCardMe(_list_cards);
			btnNanBai->setTouchEnabled(false);
			btnNanBai->setVisible(false);
			btnXemBai->setVisible(false);
			btnXemBai->setTouchEnabled(false);
			moveButtonRight();
		}
    }
}
void Lieng::btn_NanBai_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
		CCLOG("Btn Nan Bai");
		Nan3Cay *BaCay = Nan3Cay::create();
		BaCay->initListCardHand(_list_cards);
		this->addChild(BaCay);
    }
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
			//set myTo,minBet
			CCLOG("Min bet Lieng: %d",minBet);
			CCLOG("My Bet Lieng: %d",my_To);
			betLieng_Layer->setInfoBet(minBet,my_To);
			uLayer->addChild(betLieng_Layer);
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
        try {
            boost::shared_ptr<ISFSObject> params (new SFSObject());
            boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
            params->PutInt("bet", 3);
            boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_GAME_BET_REQ,params,lastRoom));
            GameServer::getSingleton().getSmartFox()->Send(request);
        } catch (exception &e) {
            CCLOG("Không bet được, Lỗi: %s",e.what());
        }
    }
}
