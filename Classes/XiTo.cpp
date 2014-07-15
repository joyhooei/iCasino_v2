//
//  XiTo.cpp
//  iCasinov2
//
//  Created by DauA on 5/28/14.
//
//

#include "XiTo.h"
#include "_Background_inGame_.h"
#include "LayerOpenCard_Xito.h"
#include "SliderCustomLoader.h"
#include "_Number_.h"
#include "Requests/ExtensionRequest.h"
#include "_Chat_.h"
#include "mUtils.h"
#include "SceneManager.h"

#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())

XiTo::XiTo():luotChia(0),chiathem(0){
    EXT_EVENT_SELECT_OPEN_CARD_REQ = "slstrq";
    EXT_EVENT_READY_REQ = "rr";
    EXT_EVENT_RAISE_REQ = "rsrq";
    
    bt_card_me = 130.5;
    bt_card_bottom = 242;
    bt_card_top = 381;
    
    lf_card_me = 313.5;
    lf_card_left_bottom = 137;
    lf_card_left_top = 202;
    lf_card_right_bottom = 531;
    lf_card_right_top = 471;
    
    w_card_me = 67;
    h_card_me = 87;
    w_card_notme = 48;
    h_card_notme = 62;

    _list_user = "";
    my_DealCards = "";
    list_dealCards_allUser = "";
    
    chooseCard = true;
    setDeal = false;
    flag_StartGame = false;
    luotChia = 0;
    chiathem = 0;
    luotChiathem = 2;
    
    uidTo = "";
    typeTo = "";
    
	arrCardTypes.push_back("h");
	arrCardTypes.push_back("s");
	arrCardTypes.push_back("c");
	arrCardTypes.push_back("d");
    
    createBackground();
    createAvatar();
    createButtons();
	createFrameBets();

    //****** Khởi tạo mảng các lá bài
    CARD_ME = CCArray::create();
    CARD_LEFT_BOTTOM = CCArray::create();
    CARD_LEFT_TOP = CCArray::create();
    CARD_RIGHT_BOTTOM = CCArray::create();
    CARD_RIGHT_TOP = CCArray::create();
    
    CARD_ME->retain();
    CARD_LEFT_BOTTOM->retain();
    CARD_LEFT_TOP->retain();
    CARD_RIGHT_BOTTOM->retain();
    CARD_RIGHT_TOP->retain();

// 	Label *addLabel = Label::create();
// 	addLabel->setFontName("Marker Felt.ttf");
// 	addLabel->setText("Thùng Phá Sảnh");
// 	addLabel->setColor(ccc3(239,235,117));
// 	addLabel->setFontSize(20);
// 	addLabel->setPosition(ccp(460, 200));
// 	this->addChild(addLabel);

	GameServer::getSingleton().addListeners(this);
	SceneManager::getSingleton().hideLoading();
	getButtonByTag(dTag_btnReady)->setEnabled(true);
}

XiTo::~XiTo(){
    GameServer::getSingleton().removeListeners(this);
    CARD_ME->removeAllObjects();
    CARD_ME = NULL;
	CARD_ME->release();
    CARD_RIGHT_BOTTOM->removeAllObjects();
    CARD_RIGHT_BOTTOM = NULL;
	CARD_RIGHT_BOTTOM->release();
    CARD_RIGHT_TOP->removeAllObjects();
    CARD_RIGHT_TOP = NULL;
	CARD_RIGHT_TOP->release();
    CARD_LEFT_TOP->removeAllObjects();
    CARD_LEFT_TOP = NULL;
	CARD_LEFT_TOP->release();
    CARD_LEFT_BOTTOM->removeAllObjects();
    CARD_LEFT_BOTTOM = NULL;
	CARD_LEFT_BOTTOM->release();
	B1->release();
	B2->release();
	B3->release();

    this->removeAllComponents();
    CCLOG("Deconstructor----- Jump Here");
}

void XiTo::onExit()
{
	GameServer::getSingleton().removeListeners(this);
	CARD_ME->removeAllObjects();
	CARD_ME->release();
	CARD_RIGHT_BOTTOM->removeAllObjects();
	CARD_RIGHT_BOTTOM->release();
	CARD_RIGHT_TOP->removeAllObjects();
	CARD_RIGHT_TOP->release();
	CARD_LEFT_TOP->removeAllObjects();
	CARD_LEFT_TOP->release();
	CARD_LEFT_BOTTOM->removeAllObjects();
	CARD_LEFT_BOTTOM->release();

	B1->release();
	B2->release();
	B3->release();

	this->removeAllComponents();
	CCLOG("Deconstructor----- Jump Here");
}

void XiTo::createAvatar(){
    layerAvatar = LayerAvatarXiTo::create();
    this->addChild(layerAvatar);
}

void XiTo::createBackground(){
    BackgroundInGame *bg = BackgroundInGame::create();
    this->addChild(bg);
	int id = atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str());
	boost::shared_ptr<string> param = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string paramString = param->c_str();
	vector<string> arrInfo = mUtils::splitString(paramString, '@');
	string money = arrInfo.at(0);

	mUtils mu;
	//string name = mu.getGameNameByID(id);
	string name = "Xì Tố";
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

void XiTo::createButtons(){
    layerButtons = LayerButtonInGame::create();
    this->addChild(layerButtons);

	B1 = CCArray::create();
	B2 = CCArray::create();
	B3 = CCArray::create();
	B1->retain();
	B2->retain();
	B3->retain();

	float w_Button = 90;
	float h_Button = 44;

	Button* btnReady = createButtonWithTitle_Pos("Sẵn Sàng",ccp(WIDTH_DESIGN - w_Button - 20, 10));
	Button* btnFold = createButtonWithTitle_Pos("Úp", ccp(WIDTH_DESIGN - w_Button - 20, 10));
	Button* btnGive = createButtonWithTitle_Pos("Nhường", ccp(WIDTH_DESIGN - w_Button * 2 - 40, 10));
	Button* btnBet = createButtonWithTitle_Pos("Tố", ccp(WIDTH_DESIGN - w_Button * 3 - 60, 10));
	Button* btnFollow = createButtonWithTitle_Pos("Theo", ccp(WIDTH_DESIGN - w_Button * 4 - 80, 10));
	Button* btnHaft = createButtonWithTitle_Pos("Tố 1/2", ccp(WIDTH_DESIGN - w_Button - 20, h_Button + 20));
	Button* btnQuater = createButtonWithTitle_Pos("Tố 1/4", ccp(WIDTH_DESIGN - w_Button * 2 - 40, h_Button + 20));
	Button* btnAll = createButtonWithTitle_Pos("Tố tất cả", ccp(WIDTH_DESIGN - w_Button - 20, h_Button * 2 + 30));
	Button* btnDouble = createButtonWithTitle_Pos("X2", ccp(WIDTH_DESIGN - w_Button*2 - 40, h_Button*2 + 30));

	btnReady->addTouchEventListener(this, toucheventselector(XiTo::btn_ready_click));
	btnFold->addTouchEventListener(this, toucheventselector(XiTo::btn_Up_click));
	btnFollow->addTouchEventListener(this, toucheventselector(XiTo::btn_Theo_click));
	btnGive->addTouchEventListener(this, toucheventselector(XiTo::btn_Nhuong_click));
	btnBet->addTouchEventListener(this, toucheventselector(XiTo::btn_To_click));
	btnHaft->addTouchEventListener(this, toucheventselector(XiTo::btn_To1_2_click));
	btnQuater->addTouchEventListener(this, toucheventselector(XiTo::btn_To1_4_click));
	btnAll->addTouchEventListener(this, toucheventselector(XiTo::btn_To_All_click));
	btnDouble->addTouchEventListener(this, toucheventselector(XiTo::btn_To_X2_click));

	btnReady->setTag(dTag_btnReady);
	btnFold->setTag(dTag_btnFold);
	btnFollow->setTag(dTag_btnFollow);
	btnGive->setTag(dTag_btnGive);
	btnBet->setTag(dTag_btnBet);
	btnHaft->setTag(dTag_btnHaft);
	btnQuater->setTag(dTag_btnQuatar);
	btnAll->setTag(dTag_btnAll);
	btnDouble->setTag(dTag_btnDouble);

	B1->addObject(btnFold);
	B1->addObject(btnGive);
	B1->addObject(btnBet);
	B1->addObject(btnFollow);

	B2->addObject(btnHaft);
	B2->addObject(btnQuater);

	B3->addObject(btnAll);
	B3->addObject(btnDouble);

	btnReady->setEnabled(false);
	btnFold->setEnabled(false);
	btnFollow->setEnabled(false);
	btnGive->setEnabled(false);
	btnBet->setEnabled(false);
	btnHaft->setEnabled(false);
	btnQuater->setEnabled(false);
	btnAll->setEnabled(false);
	btnDouble->setEnabled(false);

	layerButtons->addWidget(btnReady);
	layerButtons->addWidget(btnFold);
	layerButtons->addWidget(btnFollow);
	layerButtons->addWidget(btnGive);
	layerButtons->addWidget(btnBet);
	layerButtons->addWidget(btnHaft);
	layerButtons->addWidget(btnQuater);
	layerButtons->addWidget(btnAll);
	layerButtons->addWidget(btnDouble);

}

void XiTo::createFrameBets(){
	float left_FB_LT = 175;
	float left_FB_LB = 105;
	float bottom_TOP = 432;
	float bottom_BOTTOM = 282;

	//Layer frame bet
	layerFrameBet = CCLayer::create();
	layerFrameBet->setAnchorPoint(ccp(0, 0));
	layerFrameBet->setPosition(ccp(0, 0));
	layerFrameBet->setTouchEnabled(false);
	this->addChild(layerFrameBet);

	//layer victory type
	layerLabelVictype = CCLayer::create();
	layerLabelVictype->setAnchorPoint(ccp(0, 0));
	layerLabelVictype->setPosition(ccp(0, 0));
	layerLabelVictype->setTouchEnabled(false);
	this->addChild(layerLabelVictype);

	frameBetTotal = UIImageView::create();
	frameBetTotal->loadTexture("theo.png");
	frameBetTotal->setAnchorPoint(ccp(0,0));
	frameBetTotal->setPosition(ccp(WIDTH_DESIGN/2 - frameBetTotal->getContentSize().width/2,280));
	labelBetTotal = UILabel::create();
	labelBetTotal->setFontSize(15);
	labelBetTotal->setColor(ccWHITE);
	labelBetTotal->setPosition(ccp(frameBetTotal->getContentSize().width/2, frameBetTotal->getContentSize().height/2));
	frameBetTotal->addChild(labelBetTotal);
	frameBetTotal->setVisible(false);
	layerFrameBet->addChild(frameBetTotal);

	frameBet_Me = UIImageView::create();
	frameBet_Me->loadTexture("theo.png");
	frameBet_Me->setAnchorPoint(ccp(0,0));
	frameBet_Me->setPosition(ccp(WIDTH_DESIGN / 2 - frameBet_Me->getContentSize().width/2, frameBetTotal->getPositionY() - HEIGHT_DESIGN / 15));
	
	labelBet_Me = UILabel::create();
	labelBet_Me->setFontSize(15);
	labelBet_Me->setColor(ccWHITE);
	labelBet_Me->setPosition(ccp(frameBet_Me->getContentSize().width/2, frameBet_Me->getContentSize().height/2));
	frameBet_Me->addChild(labelBet_Me);
	frameBet_Me->setVisible(false);
	layerFrameBet->addChild(frameBet_Me);


	FrameBet* frameBet_Right_Top = FrameBet::create();
	FrameBet* frameBet_Right_Bottom = FrameBet::create();
	FrameBet* frameBet_Left_Top = FrameBet::create();
	FrameBet* frameBet_Left_Bottom = FrameBet::create();

	frameBet_Left_Top->setPosition(ccp(left_FB_LT,bottom_TOP));
	frameBet_Left_Bottom->setPosition(ccp(left_FB_LB, bottom_BOTTOM));
	frameBet_Right_Bottom->setPosition(ccp(WIDTH_DESIGN-left_FB_LB - frameBet_Right_Bottom->getKc_width(), bottom_BOTTOM));
	frameBet_Right_Top->setPosition(ccp(WIDTH_DESIGN-left_FB_LT - frameBet_Right_Top->getKc_width(), bottom_TOP));

	frameBet_Right_Bottom->setTag(user_rightBottom);
	frameBet_Right_Top->setTag(user_rightTop);
	frameBet_Left_Top->setTag(user_leftTop);
	frameBet_Left_Bottom->setTag(user_leftBottom);

	frameBet_Right_Bottom->setVisible(false);
	frameBet_Right_Top->setVisible(false);
	frameBet_Left_Top->setVisible(false);
	frameBet_Left_Bottom->setVisible(false);

	layerFrameBet->addChild(frameBet_Right_Bottom);
	layerFrameBet->addChild(frameBet_Right_Top);
	layerFrameBet->addChild(frameBet_Left_Top);
	layerFrameBet->addChild(frameBet_Left_Bottom);
}

void XiTo::setHide_AllFrameBet(){
	frameBet_Me->setVisible(false);
	getFrameBetByTag(user_leftBottom)->setVisible(false);
	getFrameBetByTag(user_leftTop)->setVisible(false);
	getFrameBetByTag(user_rightBottom)->setVisible(false);
	getFrameBetByTag(user_rightTop)->setVisible(false);
}

int XiTo::getPosUserByName(string uid, string _list_user){
    int vt = -1;
    vector<string> list;
    if(_list_user != ""){
        list = mUtils::splitString(_list_user, ';');
    }
    //Tìm vị trí của mình trong list user
    for(int i = 0; i < list.size(); i++){
        string _id = mUtils::splitString(list[i], '_')[1];
        if(strcmp(_id.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
            vt = i;
            break;
        }
    }
    
    //Tìm vị trí các người chơi
    for(int k = 0; k < list.size(); k++){
        if(strcmp(list[k].c_str(), "")==0){
            continue;
        }
        string player = list[k];
        vector<string> n = mUtils::splitString(player, '_');
        if(strcmp(n[1].c_str(), uid.c_str())==0){
            if(k == vt){
                return 0;
            }
            else if(k == (vt+1) % 5){
                return user_rightBottom;
            }
            else if(k == (vt+2) % 5){
                return user_rightTop;
            }
            else if(k == (vt+3) % 5){
                return user_leftTop;
            }
            else if(k ==( vt+4) % 5){
                return user_leftBottom;
            }
        }
    }
    return -1;
}

void XiTo::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    if(strcmp("hbc", cmd->c_str())==0){
        return;
    }
    CCLOG("cmd = %s",cmd->c_str());
    
    //user join room
    if(strcmp("jrntf",cmd->c_str())==0){
        boost::shared_ptr<string> lu = param->GetUtfString("lu");
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        CCLOG("list user update: %s",lu->c_str());
        CCLOG("Nguoi moi vao phong: %s",uid->c_str());
        _list_user = *lu;
        updateUsers(_list_user);
    }
    
    //user leave room
    else if(strcmp("lrntf",cmd->c_str())==0){
        boost::shared_ptr<string> lu = param->GetUtfString("lu");
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        if(lu != NULL){
            _list_user = *lu;
            updateUsers(_list_user);
        }
    }
    
    //user ready
    else if (strcmp("rdyntf", cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        when_userReady(*uid);
    }
    
    // Bet total when Endgame
    else if (strcmp("sfstntf", cmd->c_str())==0){
        boost::shared_ptr<long> bettt = param->GetInt("bettt");
        int _bettt = 0;

        if(bettt != NULL){
            _bettt = (int)(*bettt);
        }
        labelBetTotal->setText(("Tổng: "+mUtils::convertMoneyEx(_bettt)+" $").c_str());
        frameBetTotal->setVisible(true);
    }
    
    //game start
    else if (strcmp("strntf", cmd->c_str())==0){
        CCLOG("Game Start");
		layerAvatar->setUnReadyAllUser();
		getButtonByTag(dTag_btnReady)->setEnabled(false);
        flag_StartGame = true;
        chiaBai();
    }
    
    
    //Deal Card (2 la bai dau tien cua minh
    //EXT_EVENT_DEAL_CARD_NOTIF
    else if(strcmp("dlcntf", cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        boost::shared_ptr<string> lc = param->GetUtfString("lc");
        boost::shared_ptr<bool> isOpenCard = param->GetBool("cropn");
        setDeal = false;

        if(!setDeal){
            list_dealCards_allUser+=*uid+"_"+*lc+"-";
        }
        if(chooseCard == true && strcmp(uid->c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            my_DealCards = *lc;
            list_dealCards_allUser = "";
        }
    }
    
    //Mot nguoi mo deal card
    else if(strcmp("opcntf", cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        boost::shared_ptr<long> crdvl = param->GetInt("crdvl");
        CCLOG("Card mo deal card: %d",CARD_ME->count());
        
        string _uid = "";
        long _crdvl = -1;
        if(uid != NULL){
            _uid = uid->c_str();
        }
        if(crdvl != NULL){
            _crdvl = *crdvl;
        }
        
        OpenOneDealCards(_uid, boost::to_string(_crdvl));
        
    }
    
    //Luot nguoi to
    else if(strcmp("ndrntf", cmd->c_str()) == 0){
		getButtonByTag(dTag_btnReady)->setEnabled(false);
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        boost::shared_ptr<string> typeAllow = param->GetUtfString("betal");
        
        if (uid == NULL || typeAllow == NULL) {
            return;
        }
        uidTo = *uid;
        typeTo = *typeAllow;
        
        if(!setDeal){
            chiaThem1LaBai();
        }
        else{
            setButtonBet(*uid, *typeAllow);
        }
        setDeal = true;
    }

	//Error ready
	else if (strcmp("rdres",cmd->c_str()) == 0)
	{
		boost::shared_ptr<long> rslt = param->GetInt("rslt");
		if (rslt != NULL)
		{
			if (*rslt == 7)
			{
				Chat *toast = new Chat("Đợi người chơi khác sẵn sàng",-1);
				this->addChild(toast);
			}
		}
	}
    
    //Bet info of user
    else if(strcmp("rsntf", cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        boost::shared_ptr<long> bet = param->GetInt("bet");
        boost::shared_ptr<long> betvl = param->GetInt("betvl");
        boost::shared_ptr<long> bettt = param->GetInt("bettt");
        
        string _uid = "";
        long _bet = -1;
        long _betvl = 0;
        long _bettt = 0;
        
        if(uid != NULL){
            _uid = uid->c_str();
        }
        if(bet != NULL){
            _bet = *bet;
        }
        if(betvl != NULL){
            _betvl = *betvl;
        }
        if(bettt != NULL){
            _bettt = *bettt;
        }
        
        when_playerBet(_uid, _bet, _betvl, _bettt);
        CCLOG("uid: %s typeBet: %ld betValue: %ld betTotal %ld",uid->c_str(),*bet,*betvl,*bettt);
        CCLOG("EXT_EVENT_RAISE_NOTIF");
    }
    
    // Open All Card
    else if(strcmp("opaltf", cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        boost::shared_ptr<string> lc = param->GetUtfString("lc");
        //hide All Button
        
        string _uid = "";
        string _lc = "";
        if(uid != NULL){
            _uid = uid->c_str();
        }
        if(lc != NULL){
            _lc = lc->c_str();
        }
        
        openAllCard(_uid,_lc);
        CCLOG("OPEN ALL CARD EVENT");
    }
    
    // Victory Notifies
    else if (strcmp("vicntf", cmd->c_str())==0){
        layerAvatar->stopAllTimer();
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        boost::shared_ptr<string> lc = param->GetUtfString("lc");
        boost::shared_ptr<long> victype = param->GetInt("vttp");
        
        string _uid = "";
        string _lc = "";
        long _vicType = -1;
        
        if(uid != NULL){
            _uid = uid->c_str();
        }
        
        if(lc != NULL){
            _lc = lc->c_str();
        }
        
        if(victype != NULL){
            _vicType = *victype;
        }
        
        setVictoryType(_uid,_vicType,_lc);
        CCLOG("EXT_EVENT_VICTORY_NOTIF");
    }
    
    //----
    else if(strcmp("cblltf", cmd->c_str())==0){
        //{"uid":"dautv","amf":-4000}
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        boost::shared_ptr<double> amf = param->GetDouble("amf");
        
        string _uid = "";
        string _amf = "0";
        if(uid != NULL){
            _uid = uid->c_str();
        }
        if(amf != NULL){

			char ch[100];
			sprintf(ch, "%.0f", *amf);
			_amf = string(ch);
			if(*amf > 0){
				_amf = "+" + boost::to_string(*amf);
				_amf = "+" + string(ch);
			}
			if(*amf > 0){
				int pos = getPosUserByName(_uid,_list_user);
				displayPosWinner(pos);
			}
        }
        CCLOG("uid %s, amf %s",_uid.c_str(),_amf.c_str());
        setMoneyAnimate(_uid,_amf);
        CCLOG("App.EXT_EVENT_AMF_TEST_NOTIF %s",_amf.c_str());
    }
    
    // co nguoi vao lai phong
    else if(strcmp("gchntf",cmd->c_str())==0){
        CCLOG("EXT_EVENT_GAME_CHANGE_NOTIF");
        boost::shared_ptr<string> ginf = param->GetUtfString("ginf");
        boost::shared_ptr<string> betal = param->GetUtfString("betal");
        
        if(ginf == NULL){
            return;
        }
        
        string _ginf = ginf->c_str();
        string _betal = "NULL";
        
        vector<string> btr = mUtils::splitString(_ginf, '|');
        _list_user = btr[3];
        userReJoinGame(_ginf);
        
        if(betal != NULL){
            _betal = betal->c_str();
        }
        
        if(_betal != "NULL"){
            setButtonBet(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(), _betal.c_str());
        }
    }
    
    //End Game
    else if(strcmp("endntf", cmd->c_str())==0){
        //whenEndGame();
		setVisibleButtonPlay();
		getButtonByTag(dTag_btnReady)->setEnabled(true);
    }
    
}

void XiTo::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
    boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
    
	int money = (int)(*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
    string uid = boost::to_string(*ptrNotifiedUser->Name());
    
    switch (getPosUserByName(uid, _list_user)) {
        case user_me:
            layerAvatar->getUserByPos(user_me)->setMoney(money);
            break;
        case user_leftBottom:
			layerAvatar->getUserByPos(user_leftBottom)->setMoney(money);
            break;
        case user_leftTop:
            layerAvatar->getUserByPos(user_leftTop)->setMoney(money);
            break;
        case user_rightBottom:
            layerAvatar->getUserByPos(user_rightBottom)->setMoney(money);
            break;
        case user_rightTop:
			layerAvatar->getUserByPos(user_rightTop)->setMoney(money);
            break;
        default:
            break;
    }
}

void XiTo::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
	//
	CCLOG("ptrNotifiedMessage: %s", ptrNotifiedMessage->c_str());
	int pos = getPosUserByName(ptrNotifiedUser->Name()->c_str(), _list_user);
	if (pos == -1)
	{
		return;
	}
	//ptrNotifiedMessage->c_str()
	layerAvatar->showChatByPos(pos, ptrNotifiedMessage->c_str());
}

void XiTo::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}

void XiTo::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
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

void XiTo::updateUsers(string listUser){
    layerAvatar->resetAll();

    vector<string> list = mUtils::splitString(listUser, ';');
    boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();

    for(int i = 0; i < list.size(); i++){
        if(lastRoom == NULL){
            return;
        }
        
        if(list[i] == ""){
            continue;
        }
        
        string player = list[i];
        vector<string> n = mUtils::splitString(player, '_');

        int money = 0;
        boost::shared_ptr<string> name;
        boost::shared_ptr<string> url;
		if (GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1]) != NULL)
		{
			name =  GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("aN")->GetStringValue();
			money = (int)*GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("amf")->GetDoubleValue();
			url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("aal")->GetStringValue();
			
			int pos = getPosUserByName(n[1], _list_user);
			setInfoAvatar(pos, name->c_str(), money, i, n[1], url->c_str());

			if (strcmp(n[1].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
			{
				if( i == 0){
					layerAvatar->setFlag(user_me, true);
					getButtonByTag(dTag_btnReady)->setTitleText("Chia Bài");
				}
				else{
					getButtonByTag(dTag_btnReady)->setTitleText("Sẵn Sàng");
				}
			}
		}
    }
}

void XiTo::setInfoAvatar(int pos, string name, int money, int vt, string aI, string avatar)
{
	if (pos == -1)
	{
		return;
	}

	if (pos == user_me)
	{
		bool meIsBoss = (vt == 0);
		layerAvatar->getUserByPos(user_leftTop)->setMeIsBoss(meIsBoss);
		layerAvatar->getUserByPos(user_leftBottom)->setMeIsBoss(meIsBoss);
		layerAvatar->getUserByPos(user_rightTop)->setMeIsBoss(meIsBoss);
		layerAvatar->getUserByPos(user_rightBottom)->setMeIsBoss(meIsBoss);
		layerAvatar->getUserByPos(user_me)->setMeIsBoss(false);
	}

	layerAvatar->getUserByPos(pos)->setVisibleLayerInvite(false);
	layerAvatar->getUserByPos(pos)->setAI(aI);
	layerAvatar->getUserByPos(pos)->setIcon(avatar);
	layerAvatar->getUserByPos(pos)->setMoney(money);
	layerAvatar->getUserByPos(pos)->setName(name);
	layerAvatar->getUserByPos(pos)->setFlag(vt == 0);
}

void XiTo::userReJoinGame(string roomInfo){
    vector<string>  info = mUtils::splitString(roomInfo, '|');
    vector<string> arrUser = mUtils::splitString(info[3], ';');
    vector<string> str = mUtils::splitString(arrUser[0], '_');
    
    if(str.size() >= 6){
        setDeal = true;
        chooseCard = false;
		getButtonByTag(dTag_btnReady)->setEnabled(false);

        luotChiathem = (int)mUtils::splitString(mUtils::splitString(arrUser[0], '_')[5], ',').size();
        for(int i = 0; i < arrUser.size(); i++){
            vector<string> n = mUtils::splitString(arrUser[i], '_');

            if(n.size() >= 6){
                vector<string> l_cards = mUtils::splitString(n[5], ',');
                int countF = 0;
                
                for(int t = 0; t < l_cards.size(); t++){
                    if(atoi(l_cards[t].c_str()) < 0){
                        countF++;
                        string temp;
                        temp = l_cards[0];
                        l_cards[0] = l_cards[t];
                        l_cards[t] = temp;
                    }
                }//end for t
                
                string str_newCards = "";
                for(int t1 = 0; t1 < l_cards.size(); t1++){
                    str_newCards += l_cards[t1] + ",";
                }
                
                if(strcmp(n[1].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
                    if(countF == 2){
                        restoreListCard_Reconnected(CARD_ME, str_newCards, false, lf_card_me, bt_card_me, w_card_me, h_card_me);
                    }else{
                        restoreListCard_Reconnected(CARD_ME, str_newCards, true, lf_card_me, bt_card_me, w_card_me, h_card_me);
                    }
                }else{
                    switch(getPosUserByName(n[1], info[3])){
                        case user_leftBottom:
                            if(countF == 2){
                                restoreListCard_Reconnected(CARD_LEFT_BOTTOM, str_newCards, false, lf_card_left_bottom, bt_card_bottom, w_card_notme, h_card_notme);
                            }else{
                                restoreListCard_Reconnected(CARD_LEFT_BOTTOM, str_newCards, true, lf_card_left_bottom, bt_card_bottom, w_card_notme, h_card_notme);
                            }
                            break;
                            
                        case user_leftTop:
                            if(countF == 2){
                                restoreListCard_Reconnected(CARD_LEFT_TOP, str_newCards, false, lf_card_left_top, bt_card_top, w_card_notme, h_card_notme);
                            }else{
                                restoreListCard_Reconnected(CARD_LEFT_TOP, str_newCards, true, lf_card_left_top, bt_card_top, w_card_notme, h_card_notme);
                            }
                            break;
                            
                        case user_rightBottom:
                            if(countF == 2){
                                restoreListCard_Reconnected(CARD_RIGHT_BOTTOM, str_newCards, false, lf_card_right_bottom, bt_card_bottom, w_card_notme, h_card_notme);
                            }else{
                                restoreListCard_Reconnected(CARD_RIGHT_BOTTOM, str_newCards, true, lf_card_right_bottom, bt_card_bottom, w_card_notme, h_card_notme);
                            }
                            break;
                            
                        case user_rightTop:
                            if(countF == 2){
                                restoreListCard_Reconnected(CARD_RIGHT_TOP, str_newCards, false, lf_card_right_top, bt_card_top, w_card_notme, h_card_notme);
                            }else{
                                restoreListCard_Reconnected(CARD_RIGHT_TOP, str_newCards, true, lf_card_right_top, bt_card_top, w_card_notme, h_card_notme);
                            }
                            break;
                    }
                }
            }//end if
        }//end for
    }//end if
    else{
        // Làm mờ Avatar
    }
}

void XiTo::restoreListCard_Reconnected(CCArray *P, string lc, bool _state, float _left, float _bottom, float _width, float _height){
    if(!_state){
        for(int i = 0; i < 2; i++){
			Card *pCard = new Card("card_back.png");
			pCard->setScaleCard(_width / pCard->getContentSize().width, _height / pCard->getContentSize().height);
            pCard->setPosition(ccp(_left + i * _width / 3 * 2, _bottom));
			pCard->setVisible(true);
            this->addChild(pCard);
            P->addObject(pCard);
        }
    }else{
        string lsCards = convertCard(lc);
        vector<string> arrCards = mUtils::splitString(lsCards, '-');

        for(int i = 0; i < arrCards.size(); i++){
            if(arrCards[i] != ""){
				Card *pCard = new Card("card_back.png");
                if(arrCards[i] != "0_0"){
					pCard->initWithFile(findTypeCard(arrCards[i]).c_str());
                }
				pCard->setScaleCard(_width / pCard->getContentSize().width, _height / pCard->getContentSize().height);
                pCard->setPosition(ccp(_left + i * _width / 3 * 2, _bottom));
				pCard->setVisible(true);
                this->addChild(pCard);
                P->addObject(pCard);
            }
        }
    }
}

void XiTo::when_userReady(string uid){
	int pos = getPosUserByName(uid, _list_user);
	if (pos == -1)
	{
		return;
	}
    if(strcmp(uid.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
        getButtonByTag(dTag_btnReady)->setEnabled(false);
    }
	layerAvatar->getUserByPos(pos)->setReady(true);
}

void XiTo::when_playerBet(string uid, long bet, long betValue, long betTotal){

	string betTyleString = "";
	switch( bet ){
	case GAME_TABLE_STATUS_BET_FOLD:
		betTyleString = "Úp bỏ";
		break;
	case GAME_TABLE_STATUS_BET_RAISE:
		betTyleString = "Tố";
		break;
	case GAME_TABLE_STATUS_BET_NONE:
		betTyleString = "Nhường tố";
		break;
	case GAME_TABLE_STATUS_BET_QUATER:
		betTyleString = "Tố 1/4";
		break;
	case GAME_TABLE_STATUS_BET_HAFT:
		betTyleString = "Tố một nửa";
		break;
	case GAME_TABLE_STATUS_BET_FOLLOW:
		betTyleString = "Theo";
		break;
	case GAME_TABLE_STATUS_BET_DOUBLE:
		betTyleString = "Tố gấp đôi";
		break;
	case GAME_TABLE_STATUS_BET_ALL:
		betTyleString = "Tố tất cả";
		break;
	}

	int pos = getPosUserByName(uid, _list_user);
	layerAvatar->showChatByPos(pos, betTyleString);

    if(bet != 0 && bet != 2){
		string t = mUtils::convertMoneyEx(betTotal);
        labelBetTotal->setText(("Tổng: "+t+" $").c_str());
        frameBetTotal->setVisible(true);
    }

    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        setBet_Inpos(user_me, CARD_ME, bet, betValue);
    }
    else{
        switch (getPosUserByName(uid, _list_user)) {
            case user_leftBottom:
                setBet_Inpos(user_leftBottom, CARD_LEFT_BOTTOM, bet, betValue);
                break;
            case user_leftTop:
                 setBet_Inpos(user_leftTop, CARD_LEFT_TOP, bet, betValue);
                break;
            case user_rightBottom:
                 setBet_Inpos(user_rightBottom, CARD_RIGHT_BOTTOM, bet, betValue);
                break;
            case user_rightTop:
                 setBet_Inpos(user_rightTop, CARD_RIGHT_TOP, bet, betValue);
                break;
            default:
                break;
        }
    }
}

void XiTo::setBet_Inpos(int pos, CCArray *P, long bet, long betValue)
{

	if (pos == -1)
	{
		return;
	}

	if (pos == user_me)
	{
		labelBet_Me->setText(("Theo "+mUtils::convertMoneyEx((int)betValue)+" $").c_str());
		frameBet_Me->setVisible(true);
	}
	else
	{
		if (bet == 0)
		{
			for (int i = 0; i < P->count(); i++) {
				Card* pCard = (Card*)P->objectAtIndex(i);
				pCard->initWithFile("card_back.png");
			}
			getFrameBetByTag(pos)->setVisible(false);
		} else {
			getFrameBetByTag(pos)->setValueBet((mUtils::convertMoneyEx((int)betValue)+" $").c_str());
			getFrameBetByTag(pos)->setVisible(true);
		}
	}
}

void XiTo::displayPosWinner(int pos){

	float fromX = -1;
	float fromY = -1;
	float toX = -1;

	switch(pos){
	case user_me:
		fromX = lf_card_me - h_card_me;
		fromY = bt_card_me;
		toX = fromX + (w_card_me/ 3 * 2) * 5 + h_card_me;
		break;
	case user_leftBottom:
		fromX = layerAvatar->getUserByPos(user_leftBottom)->getPositionX() + w_card_notme;
		fromY = bt_card_bottom;
		toX = fromX + (w_card_notme/ 3 * 2) * 5 + w_card_notme;
		break;
	case user_leftTop:
		fromX = layerAvatar->getUserByPos(user_leftTop)->getPositionX() + w_card_notme;
		fromY = bt_card_top;
		toX = fromX + (w_card_notme/ 3 * 2) * 5 + w_card_notme;
		break;
	case user_rightBottom:
		fromX = layerAvatar->getUserByPos(user_rightBottom)->getPositionX() + w_card_notme;
		fromY = bt_card_bottom;
		toX = fromX - (w_card_notme/ 3 * 2) * 5 - w_card_notme;
		break;
	case user_rightTop:
		fromX = layerAvatar->getUserByPos(user_rightTop)->getPositionX() + w_card_notme;
		fromY = bt_card_top;
		toX = fromX - (w_card_notme/ 3 * 2) * 5 - w_card_notme;
		break;
	}

	CCParticleFlower *m_emitter = CCParticleFlower::create();
	m_emitter->retain();
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("vicntf.png") );
	m_emitter->setPosition(ccp(fromX, fromY));
	m_emitter->setTag(333);
	this->addChild(m_emitter);

	CCActionInterval *moveto = CCMoveTo::create(0.9, ccp(toX,fromY));
	CCActionInterval *moveBack = CCMoveTo::create(0.9, ccp(fromX, fromY));

	m_emitter->runAction(CCSequence::create(moveto, moveBack, NULL));

}

void XiTo::openAllCard(string uid, string lc){
    string strCards = convertCard(lc);
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
        setIDListCard(CARD_ME, lc);
        setListCards(CARD_ME, strCards);
    }else{
        switch (getPosUserByName(uid, _list_user)) {
            case user_leftBottom:
                setIDListCard(CARD_LEFT_BOTTOM, lc);
                setListCards(CARD_LEFT_BOTTOM, strCards);
                break;
            case user_leftTop:
                setIDListCard(CARD_LEFT_TOP, lc);
                setListCards(CARD_LEFT_TOP, strCards);
                break;
            case user_rightBottom:
                setIDListCard(CARD_RIGHT_BOTTOM, lc);
				setListCards(CARD_RIGHT_BOTTOM, strCards);
                break;
            case user_rightTop:
                setIDListCard(CARD_RIGHT_TOP, lc);
				setListCards(CARD_RIGHT_TOP, strCards);
                break;
            default:
                break;
        }
    }
}

void XiTo::setListCards(CCArray *P, string lc){
    vector<string> arrCard = mUtils::splitString(lc, '-');
    if(P->count() >= arrCard.size()){
        for(int i = 0; i < arrCard.size(); i++){
            Card *pCard = (Card*)P->objectAtIndex(i);
            if(arrCard[i] == "0_0"){
				pCard->initWithFile("card_back.png");
            }
            else{
                pCard->initWithFile(findTypeCard(arrCard[i]).c_str());
            }
        }
    }else{
    }
}

void XiTo::setIDListCard(CCArray *P,string lc){
    vector<string> arrID = mUtils::splitString(lc, ',');
    if(P->count() >= arrID.size()){
        for (int i = 0; i < arrID.size(); i++) {
            Card *pCard = (Card*)P->objectAtIndex(i);
            pCard->setID(atoi(arrID[i].c_str()));
        }
    }else{
        // After
    }
}

void XiTo::setDisplayValueListCard(CCArray *P,string lc){

    if(lc != ""){
        vector<string> arrID = mUtils::splitString(lc, ',');
        
        for (int i = 0; i < P->count(); i++) {
            Card* pCard = (Card*)P->objectAtIndex(i);
            for (int j = 0; j < arrID.size(); j++) {
                if (pCard->getID() == atoi(arrID[j].c_str())) {
                    pCard->setClicked(true);
                }
            }
        }
        
        for (int k = 0; k < P->count(); k++) {
            Card *pC = (Card*)P->objectAtIndex(k);
            if( !pC->getClicked() ){
                pC->setOpacity(200);
            }
        }
    }
}

void XiTo::setVictoryType(string uid,long vicType, string lc){
    if(strcmp(uid.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
        setDisplayValueListCard(CARD_ME, lc);
		createLabelVictype(user_me, vicType);
    }else
    {
        switch (getPosUserByName(uid, _list_user)) {
            case user_leftBottom:
				setDisplayValueListCard(CARD_LEFT_BOTTOM, lc);
				createLabelVictype(user_leftBottom, vicType);
                break;
            case user_leftTop:
				setDisplayValueListCard(CARD_LEFT_TOP, lc);
				createLabelVictype(user_leftTop, vicType);
                break;
            case user_rightBottom:
				setDisplayValueListCard(CARD_RIGHT_BOTTOM, lc);
				createLabelVictype(user_rightBottom, vicType);
                break;
            case user_rightTop:
				setDisplayValueListCard(CARD_RIGHT_TOP, lc);
				createLabelVictype(user_rightTop, vicType);
                break;
            default:
                break;
        }
    }
}

void XiTo::createLabelVictype(int pos, long vicType){
	if (pos != user_me)
	{
		getFrameBetByTag(pos)->setVisible(false);
	}
	// set Pos
	float x = -1, y = -1;
	switch(pos){
	case user_me:
		x = lf_card_me - w_card_me / 2;
		y = bt_card_me + h_card_me/2 + 4;
		break;

	case user_leftTop:
		x = lf_card_left_top - w_card_notme / 2;
		y = bt_card_top + h_card_notme/2 + 4;
		break;

	case user_leftBottom:
		x = lf_card_left_bottom - w_card_notme / 2;
		y = bt_card_bottom + h_card_notme/2 + 4;
		break;

	case user_rightTop:
		x = lf_card_right_top - w_card_notme / 2;
		y = bt_card_top + h_card_notme/2 + 4;
		break;

	case user_rightBottom:
		x = lf_card_right_bottom - w_card_notme / 2;
		y = bt_card_bottom + h_card_notme/2 + 4;
		break;

	default:
		break;
	}

	//Settext
	string txt = "";
	switch(vicType){
	case 1:
		txt = "Mậu thầu";
		break;
	case 2:
		txt = "Đôi";
		break;
	case 3:
		txt = "Thú";
		break;
	case 4:
		txt = "Sám Cô";
		break;
	case 5:
		txt = "Sảnh";
		break;
	case 6:
		txt = "Thùng";
		break;
	case 7:
		txt = "Cũ Lũ";
		break;
	case 8:
		txt = "Tứ Quý";
		break;
	case 9:
		txt = "Thùng Phá Sảnh";
		break;
	}

	Label *vic = Label::create();
	vic->setFontName("fonts/UVNDaLat_R.TTF");
	vic->setText(txt);
	vic->setColor(ccc3(239,235,117));
	vic->setFontSize(22);
	vic->setAnchorPoint(ccp(0,0));
	vic->setPosition(ccp(x, y));
	layerLabelVictype->addChild(vic);
}

void XiTo::setMoneyAnimate(string uid, string amf){
    layerAvatar->stopAllTimer();
     Number *number = new Number(amf);
     CCPoint point;
    
    if(strcmp(uid.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        point.setPoint(lf_card_me, layerAvatar->getUserByPos(user_me)->getPositionY());
    }else{
        switch (getPosUserByName(uid, _list_user)) {
            case user_rightTop:
                point.setPoint((WIDTH_DESIGN-number->getSize().width - lf_card_left_top), layerAvatar->getUserByPos(user_rightTop)->getPositionY() - 10);
                break;
                
            case user_rightBottom:
                point.setPoint(WIDTH_DESIGN - number->getSize().width - lf_card_left_bottom, layerAvatar->getUserByPos(user_rightBottom)->getPositionY());
                break;
                
            case user_leftTop:
                point.setPoint(lf_card_left_top, layerAvatar->getUserByPos(user_leftTop)->getPositionY() - 10);
                break;
                
            case user_leftBottom:
                point.setPoint(lf_card_left_bottom, layerAvatar->getUserByPos(user_leftBottom)->getPositionY());
                break;
            default:
                break;
        }
    }
    
    number->setPositionStart(point, 90);
    this->addChild(number);
}

string XiTo::convertCard(string strCard){
    vector<string> arrCards = mUtils::splitString(strCard,',');
    string str = "";
    
    for(int i=0;i<arrCards.size();i++){
        if(arrCards[i] != ""){
            int a = atoi(arrCards.at(i).c_str());
            if(a == -1){
                str += "0_0-";
            }
            else{
                int num = a / 4 + 7;
                string cardId = "";
                int type = a % 4;
                
                if(type == 0){
                    num--;
                    cardId+=boost::to_string(num);
                }
                
                if(num == 14){
                    num = 1;
                    cardId = "a";
                }
                else if(num == 13){
                    cardId = "k";
                }
                else if(num == 12){
                    cardId = "q";
                }
                else if(num == 11){
                    cardId = "j";
                }
                else{
                    cardId = boost::to_string(num);
                }
                str += cardId + "_" + boost::to_string(type) + "-";
            }
        }
    }
    
    return str;
}

string XiTo::findTypeCard(string listCards){
    vector<string> info = mUtils::splitString(listCards, '_');
    string url = "card_" + info[0] + "_" + arrCardTypes[atoi(info[1].c_str())] + ".png";
    return url;
}

void XiTo::chiaBai(){
    vector<string> realUser = mUtils::splitString(_list_user, ';');
    string listUser_vitural = _list_user;
    listUser_vitural+=";"+_list_user;
    vector<string> data = mUtils::splitString(listUser_vitural, ';');
    int num = (int)data.size();
    
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/deal_card.mp3");
    vector<string> info = mUtils::splitString(data[luotChia], '_');
    if(strcmp(info[1].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
        luotChia++;
        giveDealCardsForPlayer(CARD_ME, lf_card_me, w_card_me, h_card_me, bt_card_me, num);
    }
    else{
        switch(getPosUserByName(info[1], _list_user)){
            case user_leftBottom:
                luotChia++;
                giveDealCardsForPlayer(CARD_LEFT_BOTTOM, lf_card_left_bottom, w_card_notme, h_card_notme, bt_card_bottom, num);
                break;
            case user_leftTop:
                luotChia++;
                giveDealCardsForPlayer(CARD_LEFT_TOP, lf_card_left_top, w_card_notme, h_card_notme, bt_card_top, num);
                break;
            case user_rightBottom:
                luotChia++;
                giveDealCardsForPlayer(CARD_RIGHT_BOTTOM, lf_card_right_bottom, w_card_notme, h_card_notme, bt_card_bottom, num);
                break;
            case user_rightTop:
                luotChia++;
                giveDealCardsForPlayer(CARD_RIGHT_TOP, lf_card_right_top, w_card_notme, h_card_notme, bt_card_top, num);
                break;
        }
    }
    
}

void XiTo::giveDealCardsForPlayer(CCArray *P,float _left,float _width,float _height,float _bottom,int l){
	Card *pCard = new Card("card_back.png");
	pCard->setScaleCard(w_card_notme / pCard->getContentSize().width, h_card_notme / pCard->getContentSize().height);
    pCard->setPosition(ccp(WIDTH_DESIGN / 2 - w_card_notme / 2, HEIGHT_DESIGN - h_card_notme));
	pCard->setVisible(true);
    this->addChild(pCard);
    
    CCMoveBy *newTo = CCMoveTo::create(0.3, ccp(_left + P->count() * _width, _bottom));
    CCScaleBy *scaleTo = CCScaleBy::create(0.3, _width / w_card_notme, _height / h_card_notme);

    pCard->runAction(newTo);
    pCard->runAction(scaleTo);
    P->addObject(pCard);

    if(luotChia < l){
        this->runAction(CCSequence::create(CCDelayTime::create(0.3), CCCallFunc::create(this, callfunc_selector(XiTo::chiaBai)), NULL));
    }
    else{
        vector<string> deal = mUtils::splitString(my_DealCards, ',');
        string strDeal = convertCard(my_DealCards);
        vector<string> arr = mUtils::splitString(strDeal, '-');

        for(int i = 0; i < arr.size(); i++){
            Card *pXiTo = (Card*)CARD_ME->objectAtIndex(i);
			pXiTo->initWithFile(findTypeCard(arr[i]).c_str());
            pXiTo->setID(atoi(deal[i].c_str()));
        }
        
        // Delay Send Cards
        this->runAction(CCSequence::create(CCDelayTime::create(1),CCCallFunc::create(this, callfunc_selector(XiTo::sendOpenCard)),NULL));
    }
}

void XiTo::sendOpenCard(){
    chooseCard = false;
    popupXito(my_DealCards);
}

void XiTo::popupXito(string myDealCard){
    cocos2d::extension::CCBReader * ccbReader = NULL;
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);
    
    // register loaders
    ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
    ccNodeLoaderLibrary->registerCCNodeLoader("LayerOpenCard_Xito",   LayerOpenCard_XitoLoader::loader());
    // read main layer
    ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    LayerOpenCard_Xito *popUp;
    
    if (ccbReader)
    {
        popUp = (LayerOpenCard_Xito *)ccbReader->readNodeGraphFromFile( "LayerOpenCard_Xito.ccbi" );
        popUp->setPosition(ccp(10,10));
        popUp->setDealCards(myDealCard);
		popUp->setTag(444);
        this->addChild(popUp);
        ccbReader->release();
    }
}

void XiTo::OpenOneDealCards(string uid,string crdvl){
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
		if (this->getChildByTag(444) != NULL)
		{
			this->removeChildByTag(444);
			CCLOG("Jumpe to here and remove !");
		}
        moveDealCard_Me(crdvl);
    }
    else{
		int pos = getPosUserByName(uid, _list_user);
		moveDealCard_NotMe(pos, convertCard(crdvl));
    }
}

void XiTo::moveDealCard(Card *c,float _left, float _bottom){
    CCMoveBy *newTo = CCMoveTo::create(0.4, ccp(_left,_bottom));
    c->runAction(newTo);
}

void XiTo::moveDealCard_Me(string _lc){
	if (CARD_ME->count() != 2)
	{
		return;
	}
	
    for (int i = 0; i < CARD_ME->count(); i++) {
        Card *pCards = (Card*)CARD_ME->objectAtIndex(i);
        if(pCards->getID() != atoi(_lc.c_str()) && i != 0){
            Card *qCards = (Card*)CARD_ME->objectAtIndex(0);
            CARD_ME->replaceObjectAtIndex(0, pCards);
            CARD_ME->replaceObjectAtIndex(i, qCards);
        }
    }
    
    Card *pc = (Card*)CARD_ME->objectAtIndex(0);
    pc->setOpacity(180);
    moveDealCard(pc, lf_card_me, bt_card_me);
    
    Card* pc1 = (Card*)CARD_ME->objectAtIndex(1);
    moveDealCard(pc1, lf_card_me + w_card_me / 3 * 2, bt_card_me);

    int oldZ = pc->getZOrder();
    pc->setZOrder(pc1->getZOrder());
    pc1->setZOrder(oldZ);
}

void XiTo::moveDealCard_NotMe(int pos, string listcards){
	switch(pos){
	case user_leftTop:
		moveDealCard_Pos(CARD_LEFT_TOP, listcards, lf_card_left_top, w_card_notme, bt_card_top);
		break;
	case user_leftBottom:
		moveDealCard_Pos(CARD_LEFT_BOTTOM, listcards, lf_card_left_bottom, w_card_notme, bt_card_bottom);
		break;
	case user_rightTop:
		moveDealCard_Pos(CARD_RIGHT_TOP, listcards, lf_card_right_top, w_card_notme, bt_card_top);
		break;
	case user_rightBottom:
		moveDealCard_Pos(CARD_RIGHT_BOTTOM, listcards, lf_card_right_bottom, w_card_notme, bt_card_bottom);
		break;
	default:
		break;
	}
}

void XiTo::moveDealCard_Pos(CCArray *P, string listcards, float _left, float _width, float _bottom)
{
	if (P->count() == 0)
	{
		return;
	}

	vector<string> theCard = mUtils::splitString(listcards, '-');
	vector<string> info = mUtils::splitString(theCard[0], '_');

	Card *pCard = (Card*)P->objectAtIndex(1);
	pCard->initWithFile(findTypeCard(listcards).c_str());

	CCObject *obj;
	int dem = 0;
	CCARRAY_FOREACH(P, obj){
		Card *card = dynamic_cast<Card*>(obj);
		moveDealCard(card, _left + dem * (w_card_notme / 3 * 2), _bottom);
		dem++;
	}
}

void XiTo::chiaThem1LaBai(){

	setHide_AllFrameBet();

    string UID_BET = uidTo;
    string styleAllow_Bet = typeTo;
    //dautv_24-thanhhv3_12-dautv3_7-

    if(list_dealCards_allUser == "")
        return;

    string listDealCards = list_dealCards_allUser;
    vector<string> arrGive = mUtils::splitString(listDealCards, '-');
    int realUser = (int)arrGive.size();
    
    vector<string> info = mUtils::splitString(arrGive[chiathem], '_');
    
    string url = findTypeCard(convertCard(info[1]));
    
    if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        addCardsForUser(CARD_ME, w_card_me, h_card_me, bt_card_me, lf_card_me, url, realUser);
    }
    else{
        switch (getPosUserByName(info[0], _list_user)) {
            case user_leftBottom:
                addCardsForUser(CARD_LEFT_BOTTOM, w_card_notme, h_card_notme, bt_card_bottom, lf_card_left_bottom, url, realUser);
                break;
            case user_leftTop:
                addCardsForUser(CARD_LEFT_TOP, w_card_notme, h_card_notme, bt_card_top, lf_card_left_top, url, realUser);
                break;
            case user_rightBottom:
                addCardsForUser(CARD_RIGHT_BOTTOM, w_card_notme, h_card_notme, bt_card_bottom, lf_card_right_bottom, url, realUser);
                break;
            case user_rightTop:
                addCardsForUser(CARD_RIGHT_TOP, w_card_notme, h_card_notme, bt_card_top, lf_card_right_top, url, realUser);
                break;
            default:
                break;
        }
    }
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/deal_card.mp3");
}

void XiTo::addCardsForUser(CCArray *P,float _width,float _height,float _bottom,float _left,string _img,int l){
    
	chiathem++;
	
	Card *pCard = new Card(_img.c_str());
    pCard->setScaleCard(w_card_notme / pCard->getContentSize().width, h_card_notme / pCard->getContentSize().height);
    pCard->setPosition(ccp(WIDTH_DESIGN / 2 - w_card_notme / 2, HEIGHT_DESIGN - h_card_notme));
    pCard->setVisible(true);
	this->addChild(pCard);
    
    CCMoveBy *newTo = CCMoveTo::create(0.3, ccp(_left + P->count() * _width / 3 * 2, _bottom));
    CCScaleBy *scaleTo = CCScaleBy::create(0.3, _width / w_card_notme, _height / h_card_notme);
    
    pCard->runAction(newTo);
    pCard->runAction(scaleTo);
    P->addObject(pCard);

    if(chiathem < l){
        this->runAction(CCSequence::create(CCDelayTime::create(0.3),CCCallFunc::create(this, callfunc_selector(XiTo::chiaThem1LaBai)),NULL));
    }
    else{
        luotChiathem++;
        setButtonBet(uidTo, typeTo);
        chiathem = 0;
        list_dealCards_allUser = "";
    }
}

void XiTo::setButtonBet(string uid, string lsBet){
    layerAvatar->stopAllTimer();
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0){
		getButtonByTag(dTag_btnReady)->setEnabled(false);

        int dem1 = 0;
        int dem2 = 0;
        int dem3 = 0;
        float w_Button = 90;

        vector<string> listBetType = mUtils::splitString(lsBet, ',');
        
        for (int i = 0; i < B1->count(); i++) {
            UIButton *bt = (UIButton*)B1->objectAtIndex(i);
            for (int j = 0; j < listBetType.size(); j++) {

				int tag = atoi(listBetType[j].c_str());
                if (bt->getTag() == getTagButton(tag)) {
                    bt->setPosition(ccp(WIDTH_DESIGN - w_Button * (dem1 + 1) - 20 * (dem1 + 1), 10));
                    bt->setEnabled(true);
                    dem1++;
                }
            }
        }
        
        for (int i = 0; i < B2->count(); i++) {
            UIButton *bt = (UIButton*)B2->objectAtIndex(i);
            for (int j = 0; j < listBetType.size(); j++) {

				int tag = atoi(listBetType[j].c_str());
                if (bt->getTag() == getTagButton(tag)) {
                    bt->setPosition(ccp(WIDTH_DESIGN - w_Button * (dem2 + 1) - (dem2 + 1) * 20, 44 + 20));
                    bt->setEnabled(true);
                    dem2++;
                }
            }
        }
        
        for (int i = 0; i < B3->count(); i++) {
            UIButton *bt = (UIButton*)B3->objectAtIndex(i);
            for (int j = 0; j < listBetType.size(); j++) {

				int tag = atoi(listBetType[j].c_str());
                if (bt->getTag() == getTagButton(tag)) {
                    bt->setPosition(ccp(WIDTH_DESIGN - w_Button * (dem3 + 1) - (dem3 + 1) * 20, 44 * 2 + 30));
					bt->setEnabled(true);
                    dem3++;
                }
            }
        }

        layerAvatar->getUserByPos(user_me)->startTimer();
    }
    else{
        setVisibleButtonPlay();
		int pos = getPosUserByName(uid, _list_user);
		if (pos == -1)
		{
			return;
		}
		layerAvatar->getUserByPos(pos)->startTimer();
    }
}

void XiTo::whenEndGame(){

    deleteAllCardFromArray(CARD_ME);
    deleteAllCardFromArray(CARD_LEFT_TOP);
    deleteAllCardFromArray(CARD_LEFT_BOTTOM);
    deleteAllCardFromArray(CARD_RIGHT_BOTTOM);
    deleteAllCardFromArray(CARD_RIGHT_TOP);
    
	getFrameBetByTag(user_leftTop)->setVisible(false);
	getFrameBetByTag(user_leftBottom)->setVisible(false);
	getFrameBetByTag(user_rightBottom)->setVisible(false);
	getFrameBetByTag(user_rightTop)->setVisible(false);
    frameBetTotal->setVisible(false);
	frameBet_Me->setVisible(false);

	layerLabelVictype->removeAllChildrenWithCleanup(true);
	if (this->getChildByTag(333) != NULL)
	{
		this->removeChildByTag(333);
	}

    luotChiathem = 2;
    chooseCard = true;
    luotChia = 0;
}

void XiTo::deleteAllCardFromArray(CCArray *P){
    while(P->count() > 0){
        Card *pCard = (Card *)P->lastObject();
        P->removeLastObject();
        pCard->removeFromParentAndCleanup(true);
    }
}

void XiTo::setVisibleButtonPlay(){
	getButtonByTag(dTag_btnBet)->setEnabled(false);
    getButtonByTag(dTag_btnFollow)->setEnabled(false);
    getButtonByTag(dTag_btnFold)->setEnabled(false);
    getButtonByTag(dTag_btnGive)->setEnabled(false);
    getButtonByTag(dTag_btnQuatar)->setEnabled(false);
    getButtonByTag(dTag_btnHaft)->setEnabled(false);
    getButtonByTag(dTag_btnAll)->setEnabled(false);
    getButtonByTag(dTag_btnDouble)->setEnabled(false);
}

void XiTo::btn_ready_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){

		whenEndGame();

        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_READY_REQ,parameter,lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}

void XiTo::btn_To_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        sendBetNTF(GAME_TABLE_STATUS_BET_RAISE);
    }
}

void XiTo::btn_Theo_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        sendBetNTF(GAME_TABLE_STATUS_BET_FOLLOW);
    }
}

void XiTo::btn_Up_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		sendBetNTF(GAME_TABLE_STATUS_BET_FOLD);
	}
}

void XiTo::btn_Nhuong_click(CCObject *sender, TouchEventType type){
	if(type == TOUCH_EVENT_ENDED){
		sendBetNTF(GAME_TABLE_STATUS_BET_NONE);
	}
}

void XiTo::btn_To1_2_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        sendBetNTF(GAME_TABLE_STATUS_BET_HAFT);
    }
}

void XiTo::btn_To1_4_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        sendBetNTF(GAME_TABLE_STATUS_BET_QUATER);
    }
}

void XiTo::btn_To_X2_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        sendBetNTF(GAME_TABLE_STATUS_BET_DOUBLE);
    }
}

void XiTo::btn_To_All_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        sendBetNTF(GAME_TABLE_STATUS_BET_ALL);
    }
}

void XiTo::sendBetNTF(int typeBet){
    boost::shared_ptr<ISFSObject> param (new SFSObject());
    switch(typeBet){
        case GAME_TABLE_STATUS_BET_FOLD:
            param->PutInt("bet", GAME_TABLE_STATUS_BET_FOLD);
            break;
        case GAME_TABLE_STATUS_BET_RAISE:
            param->PutInt("bet", GAME_TABLE_STATUS_BET_RAISE);
            break;
        case GAME_TABLE_STATUS_BET_NONE:
            param->PutInt("bet", GAME_TABLE_STATUS_BET_NONE);
            break;
        case GAME_TABLE_STATUS_BET_QUATER:
            param->PutInt("bet", GAME_TABLE_STATUS_BET_QUATER);
            break;
        case GAME_TABLE_STATUS_BET_HAFT:
            param->PutInt("bet", GAME_TABLE_STATUS_BET_HAFT);
            break;
        case GAME_TABLE_STATUS_BET_FOLLOW:
            param->PutInt("bet", GAME_TABLE_STATUS_BET_FOLLOW);
            break;
        case GAME_TABLE_STATUS_BET_DOUBLE:
            param->PutInt("bet", GAME_TABLE_STATUS_BET_DOUBLE);
            break;
        case GAME_TABLE_STATUS_BET_ALL:
            param->PutInt("bet", GAME_TABLE_STATUS_BET_ALL);
            break;
    }
    boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
    boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_RAISE_REQ,param,lastRoom));
    GameServer::getSingleton().getSmartFox()->Send(request);
    setVisibleButtonPlay();
}

Button* XiTo::createButtonWithTitle_Pos(const char *pName, CCPoint pPoint) {

	Button* button = Button::create();
	button->setTouchEnabled(true);
	button->setScale9Enabled(false);
	button->loadTextures("ready.png", "ready_selected.png", "");
	button->setTitleText(pName);
	button->setTitleColor(ccRED);
	button->setTitleFontSize(20);
	button->setTitleFontSize(button->getContentSize().height / 2);
	button->setAnchorPoint(ccp(0, 0));
	button->setScaleX(90 / button->getContentSize().width);

	button->setPosition(pPoint);

	return button;
}

Button* XiTo::getButtonByTag(int pTag) {
	if (this->layerButtons->getWidgetByTag(pTag) == NULL)
	{
		return NULL;
	}
	Button* button = (Button*) this->layerButtons->getWidgetByTag(pTag);
	return button;
}

int XiTo::getTagButton(int iTag){
	switch(iTag)
	{
	case GAME_TABLE_STATUS_BET_FOLD:
		return dTag_btnFold;
		break;
	case GAME_TABLE_STATUS_BET_RAISE:
		return dTag_btnBet;
		break;
	case GAME_TABLE_STATUS_BET_NONE:
		return dTag_btnGive;
		break;
	case GAME_TABLE_STATUS_BET_QUATER:
		return dTag_btnQuatar;
		break;
	case GAME_TABLE_STATUS_BET_HAFT:
		return dTag_btnHaft;
		break;
	case GAME_TABLE_STATUS_BET_FOLLOW:
		return dTag_btnFollow;
		break;
	case GAME_TABLE_STATUS_BET_DOUBLE:
		return dTag_btnDouble;
		break;
	case GAME_TABLE_STATUS_BET_ALL:
		return dTag_btnAll;
		break;
	}
	return -1;
}

FrameBet* XiTo::getFrameBetByTag(int fTag)
{
	if (this->layerFrameBet->getChildByTag(fTag) == NULL)
	{
		return NULL;
	}
	FrameBet* frameBet = (FrameBet*) this->layerFrameBet->getChildByTag(fTag);
	return frameBet;
}


