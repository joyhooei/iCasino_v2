//
//  XiTo.cpp
//  iCasinov2
//
//  Created by DauA on 5/28/14.
//
//

#include "XiTo.h"
#include "_Background_inGame_.h"
#include "_Button_inGame_.h"
#include "LayerOpenCard_Xito.h"
#include "SliderCustomLoader.h"
#include "_Number_.h"
#include "Requests/ExtensionRequest.h"
#include "_Chat_.h"
#include "mUtils.h"

#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())

XiTo::XiTo():luotChia(0),chiathem(0){
    EXT_EVENT_SELECT_OPEN_CARD_REQ = "slstrq";
    EXT_EVENT_READY_REQ = "rr";
    EXT_EVENT_RAISE_REQ = "rsrq";
    GameServer::getSingleton().addListeners(this);
    
    bt_card_me = 87;
    bt_card_bottom = 211;
    bt_card_top = 350;
    
    lf_card_me = 280;
    lf_card_left_bottom = 113;
    lf_card_left_top = 178;
    lf_card_right_bottom = 507;
    lf_card_right_top = 447;
    
    w_card_me = 67;
    h_card_me = 87;
    w_card_notme = 48;
    h_card_notme = 62;
    
    left_FB_LT = 175;
    left_FB_LB = 105;
    bottom_TOP = 432;
    bottom_BOTTOM = 282;
    
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
    
    arrCardTypes[0] = "h";
    arrCardTypes[1] = "s";
    arrCardTypes[2] = "c";
    arrCardTypes[3] = "d";
    
   // string arrCardTypes[4] = {"h","s","c","d"};
    
    createBackground();
    createButton();
    createAvatar();
    
    B1 = new CCArray();
    B2 = new CCArray();
    B3 = new CCArray();
    B1->retain();
    B2->retain();
    B3->retain();
    
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
    btnReady->addTouchEventListener(this, toucheventselector(XiTo::btn_ready_click));
    btnReady->setTitleFontSize(20);
    btnReady->setTitleColor(ccRED);
    btnReady->setVisible(true);
    uLayer->addWidget(btnReady);
    
    //*****Btn Playe Game
    //Btn Úp bài
    btn_Up = UIButton::create();
    btn_Up->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
    btn_Up->setTag(GAME_TABLE_STATUS_BET_FOLD);
    btn_Up->setTitleText("Úp");
    btn_Up->setAnchorPoint(ccp(0,0));
    btn_Up->setPosition(ccp(WIDTH_DESIGN-btnReady->getContentSize().width-20,10));
    btn_Up->setTouchEnabled(false);
    btn_Up->addTouchEventListener(this, toucheventselector(XiTo::btn_Up_click));
    btn_Up->setTitleFontSize(20);
    btn_Up->setTitleColor(ccRED);
    btn_Up->setVisible(false);
    B1->addObject(btn_Up);
    uLayer->addWidget(btn_Up);
    
    //Btn Nhường
    btn_Nhuong = UIButton::create();
    btn_Nhuong->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
    btn_Nhuong->setTag(GAME_TABLE_STATUS_BET_NONE);
    btn_Nhuong->setTitleText("Nhường");
    btn_Nhuong->setAnchorPoint(ccp(0,0));
    btn_Nhuong->setPosition(ccp(WIDTH_DESIGN-btnReady->getContentSize().width*2-40,10));
    btn_Nhuong->setTouchEnabled(false);
    btn_Nhuong->addTouchEventListener(this, toucheventselector(XiTo::btn_Nhuong_click));
    btn_Nhuong->setTitleFontSize(20);
    btn_Nhuong->setTitleColor(ccRED);
    btn_Nhuong->setVisible(false);
    B1->addObject(btn_Nhuong);
    uLayer->addWidget(btn_Nhuong);
    
    //Btn Tố
    btn_To = UIButton::create();
    btn_To->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
    btn_To->setTag(GAME_TABLE_STATUS_BET_RAISE);
    btn_To->setTitleText("Tố");
    btn_To->setAnchorPoint(ccp(0,0));
    btn_To->setPosition(ccp(WIDTH_DESIGN-btn_To->getContentSize().width*3-60,10));
    btn_To->setTouchEnabled(false);
    btn_To->addTouchEventListener(this, toucheventselector(XiTo::btn_To_click));
    btn_To->setTitleFontSize(20);
    btn_To->setTitleColor(ccRED);
    btn_To->setVisible(false);
    B1->addObject(btn_To);
    uLayer->addWidget(btn_To);
    
    //Btn Theo
    btn_Theo = UIButton::create();
    btn_Theo->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
    btn_Theo->setTag(GAME_TABLE_STATUS_BET_FOLLOW);
    btn_Theo->setTitleText("Theo");
    btn_Theo->setAnchorPoint(ccp(0,0));
    btn_Theo->setPosition(ccp(WIDTH_DESIGN-btn_Theo->getContentSize().width*4-80,10));
    btn_Theo->setTouchEnabled(false);
    btn_Theo->addTouchEventListener(this, toucheventselector(XiTo::btn_Theo_click));
    btn_Theo->setTitleFontSize(20);
    btn_Theo->setTitleColor(ccRED);
    btn_Theo->setVisible(false);
    B1->addObject(btn_Theo);
    uLayer->addWidget(btn_Theo);
    
    //Btn To 1/2
    btn_To1_2 = UIButton::create();
    btn_To1_2->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
    btn_To1_2->setTag(GAME_TABLE_STATUS_BET_HAFT);
    btn_To1_2->setTitleText("Tố 1/2");
    btn_To1_2->setAnchorPoint(ccp(0,0));
    btn_To1_2->setPosition(ccp(WIDTH_DESIGN-btn_To1_2->getContentSize().width-20,btn_To1_2->getContentSize().height+20));
    btn_To1_2->setTouchEnabled(false);
    btn_To1_2->addTouchEventListener(this, toucheventselector(XiTo::btn_To1_2_click));
    btn_To1_2->setTitleFontSize(20);
    btn_To1_2->setTitleColor(ccRED);
    btn_To1_2->setVisible(false);
    B2->addObject(btn_To1_2);
    uLayer->addWidget(btn_To1_2);
    
    //btn to 1/4
    btn_To1_4 = UIButton::create();
    btn_To1_4->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
    btn_To1_4->setTag(GAME_TABLE_STATUS_BET_QUATER);
    btn_To1_4->setTitleText("Tố 1/4");
    btn_To1_4->setAnchorPoint(ccp(0,0));
    btn_To1_4->setPosition(ccp(WIDTH_DESIGN-btn_To1_4->getContentSize().width*2-40,btn_To1_4->getContentSize().height+20));
    btn_To1_4->setTouchEnabled(false);
    btn_To1_4->addTouchEventListener(this, toucheventselector(XiTo::btn_To1_4_click));
    btn_To1_4->setTitleFontSize(20);
    btn_To1_4->setTitleColor(ccRED);
    btn_To1_4->setVisible(false);
    B2->addObject(btn_To1_4);
    uLayer->addWidget(btn_To1_4);
    
    //Btn To tat ca
    btn_ToTatCa = UIButton::create();
    btn_ToTatCa->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
    btn_ToTatCa->setTag(GAME_TABLE_STATUS_BET_ALL);
    btn_ToTatCa->setTitleText("Tố tất cả");
    btn_ToTatCa->setAnchorPoint(ccp(0,0));
    btn_ToTatCa->setPosition(ccp(WIDTH_DESIGN-btn_ToTatCa->getContentSize().width-20,btn_ToTatCa->getContentSize().height*2+30));
    btn_ToTatCa->setTouchEnabled(false);
    btn_ToTatCa->addTouchEventListener(this, toucheventselector(XiTo::btn_To_All_click));
    btn_ToTatCa->setTitleFontSize(20);
    btn_ToTatCa->setTitleColor(ccRED);
    btn_ToTatCa->setVisible(false);
    B3->addObject(btn_ToTatCa);
    uLayer->addWidget(btn_ToTatCa);
    
    //Btn To x2
    btn_ToX2 = UIButton::create();
    btn_ToX2->loadTextures("btnXiTo.png", "btnXiTo_press.png", "");
    btn_ToX2->setTag(GAME_TABLE_STATUS_BET_DOUBLE);
    btn_ToX2->setTitleText("Tố X2");
    btn_ToX2->setAnchorPoint(ccp(0,0));
    btn_ToX2->setPosition(ccp(WIDTH_DESIGN-btn_ToX2->getContentSize().width*2-40,btn_ToX2->getContentSize().height*2+30));
    btn_ToX2->setTouchEnabled(false);
    btn_ToX2->addTouchEventListener(this, toucheventselector(XiTo::btn_To_X2_click));
    btn_ToX2->setTitleFontSize(20);
    btn_ToX2->setTitleColor(ccRED);
    btn_ToX2->setVisible(false);
    B3->addObject(btn_ToX2);
    uLayer->addWidget(btn_ToX2);
    
    
    //*** Khởi tạo các FrameBet Trong Game
    //Frame Bet Total
    frameBetTotal = UIImageView::create();
    frameBetTotal->loadTexture("theo.png");
    frameBetTotal->setAnchorPoint(ccp(0,0));
    frameBetTotal->setPosition(ccp(WIDTH_DESIGN/2 - frameBetTotal->getContentSize().width/2,HEIGHT_DESIGN/2));
    labelBetTotal = UILabel::create();
    labelBetTotal->setFontSize(15);
    labelBetTotal->setColor(ccWHITE);
    labelBetTotal->setPosition(ccp(frameBetTotal->getContentSize().width/2, frameBetTotal->getContentSize().height/2));
    frameBetTotal->addChild(labelBetTotal);
    frameBetTotal->setVisible(false);
    uLayer->addChild(frameBetTotal);
    
    //FrameBet từng Player
    frameBet_Right_Top = FrameBet::create();
    frameBet_Right_Bottom = FrameBet::create();
    frameBet_Left_Top = FrameBet::create();
    frameBet_Left_Bottom = FrameBet::create();
    
    frameBet_Left_Top->setPosition(ccp(left_FB_LT,bottom_TOP));
    frameBet_Left_Bottom->setPosition(ccp(left_FB_LB, bottom_BOTTOM));
    frameBet_Right_Bottom->setPosition(ccp(WIDTH_DESIGN-left_FB_LB-frameBet_Right_Bottom->getKc_width(),bottom_BOTTOM));
    frameBet_Right_Top->setPosition(ccp(WIDTH_DESIGN-left_FB_LT-frameBet_Right_Top->getKc_width(), bottom_TOP));
    
    frameBet_Right_Bottom->setVisible(false);
    frameBet_Right_Top->setVisible(false);
    frameBet_Left_Top->setVisible(false);
    frameBet_Left_Bottom->setVisible(false);
    
    uLayer->addChild(frameBet_Right_Bottom);
    uLayer->addChild(frameBet_Right_Top);
    uLayer->addChild(frameBet_Left_Top);
    uLayer->addChild(frameBet_Left_Bottom);
    
    //****** Khởi tạo mảng các lá bài
    CARD_ME = new CCArray();
    CARD_LEFT_BOTTOM = new CCArray();
    CARD_LEFT_TOP = new CCArray();
    CARD_RIGHT_BOTTOM = new CCArray();
    CARD_RIGHT_TOP = new CCArray();
    
    CARD_ME->retain();
    CARD_LEFT_BOTTOM->retain();
    CARD_LEFT_TOP->retain();
    CARD_RIGHT_BOTTOM->retain();
    CARD_RIGHT_TOP->retain();
}

XiTo::~XiTo(){
    GameServer::getSingleton().removeListeners(this);
    CARD_ME->removeAllObjects();
    CARD_ME = NULL;
    CARD_RIGHT_BOTTOM->removeAllObjects();
    CARD_RIGHT_BOTTOM = NULL;
    CARD_RIGHT_TOP->removeAllObjects();
    CARD_RIGHT_TOP = NULL;
    CARD_LEFT_TOP->removeAllObjects();
    CARD_LEFT_TOP = NULL;
    CARD_LEFT_BOTTOM->removeAllObjects();
    CARD_LEFT_BOTTOM = NULL;
    this->removeAllChildrenWithCleanup(true);
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
	vector<string> arrInfo = Dsplit(paramString, '@');
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
void XiTo::createButton(){
    LayerButtonInGame *button_ingame = LayerButtonInGame::create();
    this->addChild(button_ingame);
}

vector<string> XiTo::Dsplit(string &S,const char &str){
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

int XiTo::getPosUserByName(string uid, string _list_user){
    int vt = -1;
    vector<string> list;
    if(_list_user!=""){
        list = Dsplit(_list_user, ';');
    }
    //Tìm vị trí của mình trong list user
    for(int i=0;i<list.size();i++){
        string _id = Dsplit(list[i], '_')[1];
        if(strcmp(_id.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            vt = i;
            break;
        }
    }
    
    //Tìm vị trí các người chơi
    for(int k=0;k<list.size();k++){
        if(strcmp(list[k].c_str(), "")==0){
            continue;
        }
        string player = list[k];
        vector<string> n = Dsplit(player, '_');
        if(strcmp(n[1].c_str(), uid.c_str())==0){
            if(k==vt){
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
    return 0;
}

string XiTo::find_RoomBoss(string list){
    vector<string> arrUser = Dsplit(list,';');
    vector<string> info = Dsplit(arrUser[0],'_');
    string boosId = info[1];
    return boosId;
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
            CCLOG("list user update: %s",lu->c_str());
            CCLOG("Nguoi ra khoi phong: %s",uid->c_str());
            _list_user = *lu;
            updateUsers(_list_user);
        }else{
            CCLOG("Khong nhan duoc list user");
        }
    }
    
    //user ready
    else if (strcmp("rdyntf", cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        CCLOG("user ready: %s",uid->c_str());
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
        btnReady->setTouchEnabled(false);
        btnReady->setVisible(false);
        flag_StartGame = true;
        chiaBai();
    }
    
    
    //Deal Card (2 la bai dau tien cua minh
    //EXT_EVENT_DEAL_CARD_NOTIF
    else if(strcmp("dlcntf", cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        boost::shared_ptr<string> lc = param->GetUtfString("lc");
        boost::shared_ptr<bool> isOpenCard = param->GetBool("cropn");
        CCLOG("uid: %s them card: %s",uid->c_str(),lc->c_str());
        CCLOG("card convert: %s",convertCard(lc->c_str()).c_str());
        setDeal = false;
        if(!setDeal){
            CCLOG("list card: %s",list_dealCards_allUser.c_str());
            list_dealCards_allUser+=*uid+"_"+*lc+"-";
        }
        if(chooseCard == true && strcmp(uid->c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            my_DealCards = *lc;
            list_dealCards_allUser = "";
            CCLOG("delete list_dealcard");
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
    else if(strcmp("ndrntf", cmd->c_str())==0){
        btnReady->setTouchEnabled(false);
        btnReady->setVisible(false);
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
            //Hien thi cac Button Bet
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
            _amf = boost::to_string(*amf);
            if(*amf > 0){
                _amf = "+"+boost::to_string(*amf);
            }
        }
        CCLOG("uid %s, amf %s",_uid.c_str(),_amf.c_str());
        setMoneyAnimate(_uid,_amf);
        CCLOG("App.EXT_EVENT_AMF_TEST_NOTIF");
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
        
        vector<string> btr = Dsplit(_ginf, '|');
        _list_user = btr[3];
        userReJoinGame(_ginf);
        
        if(betal != NULL){
            _betal = betal->c_str();
        }
        
        CCLOG("Room Info : %s",_ginf.c_str());
        CCLOG("betal: %s",_betal.c_str());
        
        if(_betal != "NULL"){
            setButtonBet(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(), _betal.c_str());
        }
    }
    
    //End Game
    else if(strcmp("endntf", cmd->c_str())==0){
        whenEndGame();
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
    
}
void XiTo::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}
void XiTo::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}

//Update user
void XiTo::updateUsers(string listUser){
    layerAvatar->resetAll();
    vector<string> list = Dsplit(listUser, ';');
    boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
    for(int i=0; i <list.size(); i++){
        if(lastRoom==NULL){
            return;
        }
        
        if(list[i] == ""){
            continue;
        }
        
        string player = list[i];
        vector<string> n = Dsplit(player, '_');
        if(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])==NULL){
            continue;
        }
        
        int money = 0;
        boost::shared_ptr<string> name;
        
        if(strcmp(n[1].c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			layerAvatar->getUserByPos(user_me)->setVisibleLayerInvite(false);
            layerAvatar->setName(user_me, GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("aN")->GetStringValue()->c_str());
            layerAvatar->getUserByPos(user_me)->setMoney((int)(*GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue()));
			layerAvatar->getUserByPos(user_me)->setMoney((int)*GameServer::getSingleton().getSmartFox()->MySelf()->GetVariable("amf")->GetDoubleValue());
			
			if(n[1]==find_RoomBoss(_list_user)){
                layerAvatar->setFlag(user_me, true);
                btnReady->setTitleText("Chia Bài");
            }
            if(n[1]!=find_RoomBoss(_list_user)){
                btnReady->setTitleText("Sẵn Sàng");
            }
        }
        else{
            name =  GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("aN")->GetStringValue();
            money = (int)*GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[1])->GetVariable("amf")->GetDoubleValue();
            
            switch (getPosUserByName(n[1], _list_user)) {
                case user_leftBottom:
					layerAvatar->getUserByPos(user_leftBottom)->setVisibleLayerInvite(false);
                    layerAvatar->setName(user_leftBottom, name->c_str());
                    layerAvatar->getUserByPos(user_leftBottom)->setMoney(money);
                    if(n[1] == find_RoomBoss(_list_user)){
                        layerAvatar->setFlag(user_leftBottom, true);
                    }
                    break;
                case user_leftTop:
					layerAvatar->getUserByPos(user_leftTop)->setVisibleLayerInvite(false);
                    layerAvatar->setName(user_leftTop, name->c_str());
                    layerAvatar->getUserByPos(user_leftTop)->setMoney(money);
                    if(n[1]==find_RoomBoss(_list_user)){
                        layerAvatar->setFlag(user_leftTop, true);
                    }
                    break;
                case user_rightBottom:
					layerAvatar->getUserByPos(user_rightBottom)->setVisibleLayerInvite(false);
                    layerAvatar->setName(user_rightBottom, name->c_str());
                    layerAvatar->getUserByPos(user_rightBottom)->setMoney(money);
                    if(n[1]==find_RoomBoss(_list_user)){
                        layerAvatar->setFlag(user_rightBottom, true);
                    }
                    break;
                case user_rightTop:
					layerAvatar->getUserByPos(user_rightTop)->setVisibleLayerInvite(false);
                    layerAvatar->setName(user_rightTop, name->c_str());
                    layerAvatar->getUserByPos(user_rightTop)->setMoney(money);
                    if(n[1]==find_RoomBoss(_list_user)){
                        layerAvatar->setFlag(user_rightTop, true);
                    }
                    break;
            }
        }
    }
}

void XiTo::userReJoinGame(string roomInfo){
    vector<string>  info = Dsplit(roomInfo, '|');
    vector<string> arrUser = Dsplit(info[3], ';');
    for(int i=0;i<arrUser.size();i++){
        CCLOG("user %d: %s",i,arrUser[i].c_str());
    }
    CCLOG("I'm come back here");
    
    vector<string> str = Dsplit(arrUser[0], '_');
    
    if(str.size()>=6){
        setDeal = true;
        chooseCard = false;
		btnReady->setVisible(false);
		btnReady->setTouchEnabled(false);

        luotChiathem = (int)Dsplit(Dsplit(arrUser[0], '_')[5], ',').size();
        CCLOG("luot chia: %d",luotChiathem);
        for(int i=0;i<arrUser.size();i++){
            vector<string> n = Dsplit(arrUser[i], '_');
            if(n.size()>=6){
                vector<string> l_cards = Dsplit(n[5], ',');
                int countF = 0;
                
                for(int t=0; t<l_cards.size(); t++){
                    if(atoi(l_cards[t].c_str())<0){
                        countF++;
                        string temp;
                        temp = l_cards[0];
                        l_cards[0] = l_cards[t];
                        l_cards[t] = temp;
                    }
                }//end for t
                
                string str_newCards = "";
                for(int t1=0; t1<l_cards.size(); t1++){
                    CCLOG("i = %d, card: %s",t1,l_cards[t1].c_str());
                    str_newCards+=l_cards[t1]+",";
                }
                CCLOG("str_newCards = %s",str_newCards.c_str());
                
                if(strcmp(n[1].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
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
            CardChan *pCard = CardChan::create();
            pCard->loadTexture("card_back.png");
            pCard->setSizeCard(_width, _height);
            pCard->setPosition(ccp(_left+i*_width/3*2,_bottom));
            uLayer->addChild(pCard);
            P->addObject(pCard);
        }
    }else{
        string lsCards = convertCard(lc);
        vector<string> arrCards = Dsplit(lsCards, '-');
        for(int i=0;i<arrCards.size();i++){
            if(arrCards[i] != ""){
                CardChan *pCard = CardChan::create();
                if(arrCards[i] == "0_0"){
                    pCard->loadTexture("card_back.png");
                }else{
                    pCard->loadTexture(findTypeCard(arrCards[i]).c_str());
                }
                pCard->setSizeCard(_width, _height);
                pCard->setPosition(ccp(_left+i*_width/3*2,_bottom));
                uLayer->addChild(pCard);
                P->addObject(pCard);
            }
        }
    }
}


void XiTo::when_userReady(string uid){
    if(strcmp(uid.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        btnReady->setVisible(false);
        btnReady->setTouchEnabled(false);
		layerAvatar->getUserByPos(user_me)->setReady(true);
    }
    else{
        switch(getPosUserByName(uid,_list_user)){
		case user_leftBottom:
			layerAvatar->getUserByPos(user_leftBottom)->setReady(true);
			break;
		case user_leftTop:
			layerAvatar->getUserByPos(user_leftTop)->setReady(true);
			break;
		case user_rightBottom:
			layerAvatar->getUserByPos(user_rightBottom)->setReady(true);
			break;
		case user_rightTop:
			layerAvatar->getUserByPos(user_rightTop)->setReady(true);
			break;
		}
    }
}

// Khi nhan được 1 người Bet
void XiTo::when_playerBet(string uid, long bet, long betValue, long betTotal){
    if(bet != 0 && bet != 2){
		string t = mUtils::convertMoneyEx(betTotal);
		CCLOG("TTTTT = %s",t.c_str());
        labelBetTotal->setText(("Tổng: "+t+" $").c_str());
        frameBetTotal->setVisible(true);
    }
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        //SetMyBet
    }
    else{
        switch (getPosUserByName(uid, _list_user)) {
            case user_leftBottom:
                setPlayerBet(bet, betValue, user_leftBottom);
                break;
            case user_leftTop:
                setPlayerBet(bet, betValue, user_leftTop);
                break;
            case user_rightBottom:
                setPlayerBet(bet, betValue, user_rightBottom);
                break;
            case user_rightTop:
                setPlayerBet(bet, betValue, user_rightTop);
                break;
            default:
                break;
        }
    }
}

//Set Bet For Player
void XiTo::setPlayerBet(long bet, long betValue, int _pos){
    switch(_pos){
        case user_me:
            if (bet == 0) {
                for (int i=0; i<CARD_ME->count(); i++) {
                    CardChan* pCard = (CardChan*)CARD_ME->objectAtIndex(i);
                    pCard->loadTexture("card_back.png");
                }
            }
            break;
            
        case user_leftBottom:
            if (bet == 0) {
                for (int i=0; i<CARD_LEFT_BOTTOM->count(); i++) {
                    CardChan* pCard = (CardChan*)CARD_LEFT_BOTTOM->objectAtIndex(i);
                    pCard->loadTexture("card_back.png");
                }
                frameBet_Left_Bottom->setVisible(false);
            }
            else{
                frameBet_Left_Bottom->setValueBet((mUtils::convertMoneyEx((int)betValue)+" $").c_str());
                frameBet_Left_Bottom->setVisible(true);
            }
            break;
            
        case user_leftTop:
            if (bet == 0) {
                for (int i=0; i<CARD_LEFT_TOP->count(); i++) {
                    CardChan* pCard = (CardChan*)CARD_LEFT_TOP->objectAtIndex(i);
                    pCard->loadTexture("card_back.png");
                }
                frameBet_Left_Top->setVisible(false);
            }
            else{
                frameBet_Left_Top->setValueBet((mUtils::convertMoneyEx((int)betValue)+" $").c_str());
                frameBet_Left_Top->setVisible(true);
            }
            break;
            
        case user_rightTop:
            if (bet == 0) {
                for (int i=0; i<CARD_RIGHT_TOP->count(); i++) {
                    CardChan* pCard = (CardChan*)CARD_RIGHT_TOP->objectAtIndex(i);
                    pCard->loadTexture("card_back.png");
                }
                frameBet_Right_Top->setVisible(false);
            }
            else{
                frameBet_Right_Top->setValueBet((mUtils::convertMoneyEx((int)betValue)+" $").c_str());
                frameBet_Right_Top->setVisible(true);
            }
            break;
            
        case user_rightBottom:
            if (bet == 0) {
                for (int i=0; i<CARD_RIGHT_BOTTOM->count(); i++) {
                    CardChan* pCard = (CardChan*)CARD_RIGHT_BOTTOM->objectAtIndex(i);
                    pCard->loadTexture("card_back.png");
                }
                frameBet_Right_Bottom->setVisible(false);
            }
            else{
                frameBet_Right_Bottom->setValueBet((mUtils::convertMoneyEx((int)betValue)+" $").c_str());
                frameBet_Right_Bottom->setVisible(true);
            }
            break;
            
        default:
            break;
    }
}

//Open All Card
void XiTo::openAllCard(string uid, string lc){
    string strCards = convertCard(lc);
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        CCLOG("Me, lc: %s (%s)",lc.c_str(),strCards.c_str());
        setIDListCard(CARD_ME, lc);
        setListCards(CARD_ME, strCards);
    }else{
        switch (getPosUserByName(uid, _list_user)) {
            case user_leftBottom:
                setIDListCard(CARD_LEFT_BOTTOM, lc);
                setListCards(CARD_LEFT_BOTTOM, strCards);
                CCLOG("Left Bottom, lc: %s (%s)",lc.c_str(),strCards.c_str());
                break;
            case user_leftTop:
                setIDListCard(CARD_LEFT_TOP, lc);
                setListCards(CARD_LEFT_TOP, strCards);
                CCLOG("Left Top, lc: %s (%s)",lc.c_str(),strCards.c_str());
                break;
            case user_rightBottom:
                setIDListCard(CARD_RIGHT_BOTTOM, lc);
                setListCards(CARD_RIGHT_BOTTOM, strCards);
                CCLOG("Right Bottom, lc: %s (%s)",lc.c_str(),strCards.c_str());
                break;
            case user_rightTop:
                setIDListCard(CARD_RIGHT_TOP, lc);
                setListCards(CARD_RIGHT_TOP, strCards);
                CCLOG("Right Top, lc: %s (%s)",lc.c_str(),strCards.c_str());
                break;
            default:
                break;
        }
    }
}

void XiTo::setListCards(CCArray *P, string lc){
    vector<string> arrCard = Dsplit(lc, '-');
    if(P->count()>=arrCard.size()){
        for(int i=0;i<arrCard.size();i++){
            CardChan *pCard = (CardChan*)P->objectAtIndex(i);
            if(arrCard[i]=="0_0"){
                pCard->loadTexture("card_back.png");
            }
            else{
                pCard->loadTexture(findTypeCard(arrCard[i]).c_str());
            }
        }
    }else{
        // Add when Reconect ...
    }
}

void XiTo::setIDListCard(CCArray *P,string lc){
    vector<string> arrID = Dsplit(lc, ',');
    CCLOG("size: %lu",arrID.size());
    if(P->count()>=arrID.size()){
        for (int i=0; i<arrID.size(); i++) {
            CardChan *pCard = (CardChan*)P->objectAtIndex(i);
            pCard->setID(atoi(arrID[i].c_str()));
        }
    }else{
        // After
    }
}

void XiTo::setDisplayValueListCard(CCArray *P,string lc){
    CCLOG("lc = %s",lc.c_str());
    if(lc != ""){
        CCLOG("Jump setDisplay lc != '' ");
        CCLOG("P->count() = %d",P->count());
        vector<string> arrID = Dsplit(lc, ',');
        
        for (int i=0; i<P->count(); i++) {
            CardChan* pCard = (CardChan*)P->objectAtIndex(i);
            CCLOG("here i %d",i);
            for (int j=0; j<arrID.size(); j++) {
                CCLOG("here j %d",j);
                if (pCard->getID()==atoi(arrID[j].c_str())) {
                    pCard->setFlag(true);
                }
            }
        }
        //Xu ly
        for (int k=0; k<P->count(); k++) {
            CardChan *pC = (CardChan*)P->objectAtIndex(k);
            if(!pC->getFlag()){
                pC->setOpacity(200);
            }
        }
    }
}

void XiTo::setVictoryType(string uid,long vicType, string lc){
    if(strcmp(uid.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        setDisplayValueListCard(CARD_ME, lc);
    }else
    {
        switch (getPosUserByName(uid, _list_user)) {
            case user_leftBottom:
                setDisplayValueListCard(CARD_LEFT_BOTTOM, lc);
                break;
            case user_leftTop:
                setDisplayValueListCard(CARD_LEFT_TOP, lc);
                break;
            case user_rightBottom:
                setDisplayValueListCard(CARD_RIGHT_BOTTOM, lc);
                break;
            case user_rightTop:
                setDisplayValueListCard(CARD_RIGHT_TOP, lc);
                break;
            default:
                break;
        }
    }
}

//set Money animation
void XiTo::setMoneyAnimate(string uid, string amf){
    layerAvatar->stopAllTimer();
     Number *number = new Number(amf);
     CCPoint point;
    
    if(strcmp(uid.c_str(),GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        point.setPoint(lf_card_me, bt_card_me);
    }else{
        switch (getPosUserByName(uid, _list_user)) {
            case user_rightTop:
                point.setPoint((WIDTH_DESIGN-number->getSize().width - lf_card_left_top), bt_card_top);
                break;
                
            case user_rightBottom:
                point.setPoint(WIDTH_DESIGN - number->getSize().width - lf_card_left_bottom, bt_card_bottom);
                break;
                
            case user_leftTop:
                point.setPoint(lf_card_left_top, bt_card_top);
                break;
                
            case user_leftBottom:
                point.setPoint(lf_card_left_bottom, bt_card_bottom);
                break;
            default:
                break;
        }
    }
    
    number->setPositionStart(point);
    uLayer->addChild(number);
}


string XiTo::convertCard(string strCard){
    vector<string> arrCards = Dsplit(strCard,',');
    string str = "";
    
    for(int i=0;i<arrCards.size();i++){
        if(arrCards[i]!=""){
            int a = atoi(arrCards[i].c_str());
            if(a==-1){
                str+="0_0-";
            }
            else{
                int num = a/4 + 7;
                string cardId = "";
                int type = a%4;
                
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
    CCLOG("lc %s",listCards.c_str());
    vector<string> info = Dsplit(listCards, '_');
    CCLOG("card: %s, type %s",info[0].c_str(),info[1].c_str());
    string url = "card_"+info[0] + "_" + arrCardTypes[atoi(info[1].c_str())]+".png";
    return url;
}

void XiTo::chiaBai(){
    vector<string> realUser = Dsplit(_list_user, ';');
    CCLOG("So nguoi choi: %lu",realUser.size());
    string listUser_vitural = _list_user;
    listUser_vitural+=";"+_list_user;
    vector<string> data = Dsplit(listUser_vitural, ';');
    int num = (int)data.size();
    
    CCLOG("Luot chia = %d",luotChia);
    vector<string> info = Dsplit(data[luotChia], '_');
    if(strcmp(info[1].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
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
    CardChan *pCard = CardChan::create();
    pCard->loadTexture("card_back.png");
    pCard->setSizeCard(w_card_notme, h_card_notme);
    pCard->setPosition(ccp(WIDTH_DESIGN/2-w_card_notme/2,HEIGHT_DESIGN-h_card_notme));
    uLayer->addChild(pCard);
    
    CCMoveBy *newTo = CCMoveTo::create(0.3, ccp(_left+P->count()*_width,_bottom));
    CCScaleBy *scaleTo = CCScaleBy::create(0.3, _width/w_card_notme,_height/h_card_notme);
    pCard->runAction(newTo);
    pCard->runAction(scaleTo);
    P->addObject(pCard);
    CCLOG("Card me: %d",CARD_ME->count());
    if(luotChia<l){
        this->runAction(CCSequence::create(CCDelayTime::create(0.3),CCCallFunc::create(this, callfunc_selector(XiTo::chiaBai)),NULL));
    }
    else{
        //Hien thi 2 la bai cua minh
        CCLOG("deal card me: %s",my_DealCards.c_str());
        CCLOG("dealCards convert: %s",convertCard(my_DealCards).c_str());
        vector<string> deal = Dsplit(my_DealCards, ',');
        string strDeal = convertCard(my_DealCards);
        vector<string> arr = Dsplit(strDeal, '-');
        CCLOG("Xac thuc %lu",arr.size());
        for(int i = 0;i<arr.size();i++){
            CardChan *pXiTo = (CardChan*)CARD_ME->objectAtIndex(i);
            pXiTo->loadTexture(findTypeCard(arr[i]).c_str());
            CCLOG("set ID Cards: %d",atoi(deal[i].c_str()));
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
        uLayer->addChild(popUp);
        ccbReader->release();
    }
}

void XiTo::OpenOneDealCards(string uid,string crdvl){
    CCLOG("Nguoi mo bai: %s la bai %s - (%s)",uid.c_str(),crdvl.c_str(),convertCard(crdvl).c_str());
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        CCLOG("Ben trong OpenDeal Card: %d",CARD_ME->count());
//        moveDealCard_Me(convertCard(crdvl));
        moveDealCard_Me(crdvl);
    }
    else{
        switch(getPosUserByName(uid, _list_user)){
            case user_leftBottom:
                moveDealCard_Left_Bottom(convertCard(crdvl));
                break;
            case user_leftTop:
                moveDealCard_Left_Top(convertCard(crdvl));
                break;
            case user_rightBottom:
                moveDealCard_Right_Bottom(convertCard(crdvl));
                break;
            case user_rightTop:
                moveDealCard_Right_Top(convertCard(crdvl));
                break;
            default:
                break;
        }
    }
}

void XiTo::moveDealCard(CardChan *c,float _left, float _bottom){
    CCMoveBy *newTo = CCMoveTo::create(0.4, ccp(_left,_bottom));
    c->runAction(newTo);
}
void XiTo::moveDealCard_Me(string _lc){
    CCLOG("trước khi mở: ");
	if (CARD_ME->count() != 2)
	{
		return;
	}
	
    for (int i=0; i<CARD_ME->count(); i++) {
        CardChan *pCards = (CardChan*)CARD_ME->objectAtIndex(i);
        CCLOG("id: %d",pCards->getID());
        if(pCards->getID()!=atoi(_lc.c_str()) && i != 0){
            CardChan *qCards = (CardChan*)CARD_ME->objectAtIndex(0);
            CARD_ME->replaceObjectAtIndex(0, pCards);
            CARD_ME->replaceObjectAtIndex(i, qCards);
        }
    }
    
    CardChan *pc = (CardChan*)CARD_ME->objectAtIndex(0);
    pc->setOpacity(180);
    moveDealCard(pc, lf_card_me, bt_card_me);
    
    CardChan* pc1 = (CardChan*)CARD_ME->objectAtIndex(1);
    moveDealCard(pc1, lf_card_me+w_card_me/3*2, bt_card_me);
    int oldZ = pc->getZOrder();
    pc->setZOrder(pc1->getZOrder());
    pc1->setZOrder(oldZ);
}

void XiTo::moveDealCard_Left_Bottom(string _lc){
    vector<string> theCard = Dsplit(_lc, '-');
    vector<string> info = Dsplit(theCard[0], '_');
    CardChan *pCard = (CardChan*)CARD_LEFT_BOTTOM->objectAtIndex(1);
    pCard->loadTexture(findTypeCard(_lc).c_str());
    CCObject *d;
    int dem = 0;
    CCARRAY_FOREACH(CARD_LEFT_BOTTOM, d){
        CardChan *uu = dynamic_cast<CardChan*>(d);
        moveDealCard(uu, lf_card_left_bottom+dem*(w_card_notme/3*2), bt_card_bottom);
        dem++;
    }
}
void XiTo::moveDealCard_Left_Top(string _lc){
    vector<string> theCard = Dsplit(_lc, '-');
    vector<string> info = Dsplit(theCard[0], '_');
    CardChan *pCard = (CardChan*)CARD_LEFT_TOP->objectAtIndex(1);
    pCard->loadTexture(findTypeCard(_lc).c_str());
    CCObject *d;
    int dem = 0;
    CCARRAY_FOREACH(CARD_LEFT_TOP, d){
        CardChan *uu = dynamic_cast<CardChan*>(d);
        moveDealCard(uu, lf_card_left_top+dem*(w_card_notme/3*2), bt_card_top);
        dem++;
    }
}
void XiTo::moveDealCard_Right_Bottom(string _lc){
    vector<string> theCard = Dsplit(_lc, '-');
    vector<string> info = Dsplit(theCard[0], '_');
    CardChan *pCard = (CardChan*)CARD_RIGHT_BOTTOM->objectAtIndex(1);
    pCard->loadTexture(findTypeCard(_lc).c_str());
    CCObject *d;
    int dem = 0;
    CCARRAY_FOREACH(CARD_RIGHT_BOTTOM, d){
        CardChan *uu = dynamic_cast<CardChan*>(d);
        moveDealCard(uu, lf_card_right_bottom+dem*(w_card_notme/3*2), bt_card_bottom);
        dem++;
    }
}
void XiTo::moveDealCard_Right_Top(string _lc){
    vector<string> theCard = Dsplit(_lc, '-');
    vector<string> info = Dsplit(theCard[0], '_');
    CardChan *pCard = (CardChan*)CARD_RIGHT_TOP->objectAtIndex(1);
    pCard->loadTexture(findTypeCard(_lc).c_str());
    CCObject *d;
    int dem = 0;
    CCARRAY_FOREACH(CARD_RIGHT_TOP, d){
        CardChan *uu = dynamic_cast<CardChan*>(d);
        moveDealCard(uu, lf_card_right_top+dem*(w_card_notme/3*2), bt_card_top);
        dem++;
    }
}


void XiTo::chiaThem1LaBai(){
    string UID_BET = uidTo;
    string styleAllow_Bet = typeTo;
    //dautv_24-thanhhv3_12-dautv3_7-
    if(list_dealCards_allUser == "")
        return;
    string listDealCards = list_dealCards_allUser;
    vector<string> arrGive = Dsplit(listDealCards, '-');
    int realUser = (int)arrGive.size();
    CCLOG("So nguoi choi %d",realUser);
    CCLOG("so list Card ao: %s",list_dealCards_allUser.c_str());
    
    vector<string> info = Dsplit(arrGive[chiathem], '_');
    
    string url = findTypeCard(convertCard(info[1]));
    CCLOG("url = %s",url.c_str());
    
    if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        // Chia them bai cho minh
        CCLOG("Baif thêm cho mình: %s",convertCard(info[1]).c_str());
        chiathem++;
        addCardsForUser(CARD_ME, w_card_me, h_card_me, bt_card_me, lf_card_me, url, realUser);
    }
    else{
        // Chia them bai cho nguoi khac
        switch (getPosUserByName(info[0], _list_user)) {
            case user_leftBottom:
                CCLOG("Bài thêm Trái - Dưới: %s",convertCard(info[1]).c_str());
                chiathem++;
                addCardsForUser(CARD_LEFT_BOTTOM, w_card_notme, h_card_notme, bt_card_bottom, lf_card_left_bottom, url, realUser);
                break;
            case user_leftTop:
                CCLOG("Bài thêm Trái - Trên: %s",convertCard(info[1]).c_str());
                chiathem++;
                addCardsForUser(CARD_LEFT_TOP, w_card_notme, h_card_notme, bt_card_top, lf_card_left_top, url, realUser);
                break;
            case user_rightBottom:
                CCLOG("Bài thêm Phải - Dưới: %s",convertCard(info[1]).c_str());
                chiathem++;
                addCardsForUser(CARD_RIGHT_BOTTOM, w_card_notme, h_card_notme, bt_card_bottom, lf_card_right_bottom, url, realUser);
                break;
            case user_rightTop:
                CCLOG("Bài thêm Phải - Trên: %s",convertCard(info[1]).c_str());
                chiathem++;
                addCardsForUser(CARD_RIGHT_TOP, w_card_notme, h_card_notme, bt_card_top, lf_card_right_top, url, realUser);
                break;
            default:
                break;
        }
    }
    
}

/*
 CardChan *pCard = CardChan::create();
 pCard->loadTexture("card_back.png");
 pCard->setSizeCard(w_card_notme, h_card_notme);
 pCard->setPosition(ccp(WIDTH_DESIGN/2-w_card_notme/2,HEIGHT_DESIGN-h_card_notme));
 uLayer->addChild(pCard);
 
 CCMoveBy *newTo = CCMoveTo::create(0.3, ccp(_left+P->count()*_width,_bottom));
 CCScaleBy *scaleTo = CCScaleBy::create(0.3, _width/w_card_notme,_height/h_card_notme);*/

void XiTo::addCardsForUser(CCArray *P,float _width,float _height,float _bottom,float _left,string _img,int l){
    CardChan *pCard = CardChan::create();
    pCard->loadTexture(_img.c_str());
    pCard->setSizeCard(w_card_notme, h_card_notme);
    pCard->setPosition(ccp(WIDTH_DESIGN/2-w_card_notme/2,HEIGHT_DESIGN-h_card_notme));
    uLayer->addChild(pCard);
    
    CCMoveBy *newTo = CCMoveTo::create(0.4, ccp(_left+P->count()*_width/3*2,_bottom));
    CCScaleBy *scaleTo = CCScaleBy::create(0.3, _width/w_card_notme,_height/h_card_notme);
    
    pCard->runAction(newTo);
    pCard->runAction(scaleTo);
    P->addObject(pCard);
    if(chiathem<l){
        this->runAction(CCSequence::create(CCDelayTime::create(0.4),CCCallFunc::create(this, callfunc_selector(XiTo::chiaThem1LaBai)),NULL));
    }
    else{
        luotChiathem++;
        CCLOG("Chia xong nhay vao to");
        setButtonBet(uidTo, typeTo);
        chiathem = 0;
        list_dealCards_allUser = "";
    }
}

//Set button Bet
void XiTo::setButtonBet(string uid, string lsBet){
    layerAvatar->stopAllTimer();
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        btnReady->setVisible(false);
        btnReady->setTouchEnabled(false);
        int dem1 = 0;
        int dem2 = 0;
        int dem3 = 0;
        float width_Option = 90;
        vector<string> listBetType = Dsplit(lsBet, ',');
        
        for (int i=0; i<B1->count(); i++) {
            UIButton *bt = (UIButton*)B1->objectAtIndex(i);
            for (int j=0; j<listBetType.size(); j++) {
                if (bt->getTag() == atoi(listBetType[j].c_str())) {
                    bt->setPosition(ccp(WIDTH_DESIGN-btn_Nhuong->getContentSize().width*(dem1+1)-20*(dem1+1),10));
//                    bt->setPosition(ccp(WIDTH_DESIGN-width_Option*dem1-(dem1+1)*20,0));
                    bt->setTouchEnabled(true);
                    bt->setVisible(true);
                    dem1++;
                }
            }
        }
        
        for (int i=0; i<B2->count(); i++) {
            UIButton *bt = (UIButton*)B2->objectAtIndex(i);
            for (int j=0; j<listBetType.size(); j++) {
                if (bt->getTag() == atoi(listBetType[j].c_str())) {
                    bt->setPosition(ccp(WIDTH_DESIGN-width_Option*(dem2+1)-(dem2+1)*20,44+20));
                    bt->setTouchEnabled(true);
                    bt->setVisible(true);
                    dem2++;
                }
            }
        }
        
        for (int i=0; i<B3->count(); i++) {
            UIButton *bt = (UIButton*)B3->objectAtIndex(i);
            for (int j=0; j<listBetType.size(); j++) {
                if (bt->getTag() == atoi(listBetType[j].c_str())) {
                    bt->setPosition(ccp(WIDTH_DESIGN-width_Option*(dem3+1)-(dem3+1)*20,44*2+30));
                    bt->setTouchEnabled(true);
                    bt->setVisible(true);
                    dem3++;
                }
            }
        }
        layerAvatar->getUserByPos(user_me)->startTimer();
    }
    else{
        setVisibleButtonPlay();
        switch (getPosUserByName(uid, _list_user)) {
            case user_leftBottom:
                layerAvatar->getUserByPos(user_leftBottom)->startTimer();
                break;
            case user_leftTop:
                layerAvatar->getUserByPos(user_leftTop)->startTimer();
                break;
            case user_rightTop:
                layerAvatar->getUserByPos(user_rightTop)->startTimer();
                break;
            case user_rightBottom:
                layerAvatar->getUserByPos(user_rightBottom)->startTimer();
                break;
            default:
                break;
        }
    }
}

void XiTo::whenEndGame(){
    
    setVisibleButtonPlay();
    
    deleteAllCardFromArray(CARD_ME);
    deleteAllCardFromArray(CARD_LEFT_TOP);
    deleteAllCardFromArray(CARD_LEFT_BOTTOM);
    deleteAllCardFromArray(CARD_RIGHT_BOTTOM);
    deleteAllCardFromArray(CARD_RIGHT_TOP);
    
    frameBet_Right_Top->setVisible(false);
    frameBet_Right_Bottom->setVisible(false);
    frameBet_Left_Top->setVisible(false);
    frameBet_Left_Bottom->setVisible(false);
    frameBetTotal->setVisible(false);
    
    btnReady->setTouchEnabled(true);
    btnReady->setVisible(true);
    
    luotChiathem = 2;
    chooseCard = true;
    luotChia = 0;
    
    
}
void XiTo::deleteAllCardFromArray(cocos2d::CCArray *P){
    while(P->count()>0){
        CardChan *uu = (CardChan*)P->objectAtIndex(P->count()-1);
        P->removeObject(uu);
        uLayer->removeChild(uu);
    }
}

void XiTo::setVisibleButtonPlay(){
    btn_To->setTouchEnabled(false);
    btn_To->setVisible(false);
    
    btn_Theo->setTouchEnabled(false);
    btn_Theo->setVisible(false);
    
    btn_Up->setTouchEnabled(false);
    btn_Up->setVisible(false);
    
    btn_Nhuong->setTouchEnabled(false);
    btn_Nhuong->setVisible(false);
    
    //Tố 1/4 - Tố 1/2
    btn_To1_4->setTouchEnabled(false);
    btn_To1_4->setVisible(false);
    
    btn_To1_2->setTouchEnabled(false);
    btn_To1_2->setVisible(false);
    //Tố tất cả, Tố X2
    btn_ToTatCa->setTouchEnabled(false);
    btn_ToTatCa->setVisible(false);
    
    btn_ToX2->setTouchEnabled(false);
    btn_ToX2->setVisible(false);
}

void XiTo::btn_ready_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
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
        if(type == TOUCH_EVENT_ENDED){
            sendBetNTF(GAME_TABLE_STATUS_BET_FOLD);
        }
    }
}
void XiTo::btn_Nhuong_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        if(type == TOUCH_EVENT_ENDED){
            sendBetNTF(GAME_TABLE_STATUS_BET_NONE);
        }
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





