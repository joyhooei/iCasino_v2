//
//  BaCayChuong.cpp
//  iCasinov2
//
//  Created by DauA on 5/23/14.
//
//

#include "BaCayChuong.h"
#include "_Background_inGame_.h"
#include "_Button_inGame_.h"
#include "Requests/ExtensionRequest.h"
#include "CardChan.h" 
#include "_Number_inGame_.h"
#include "SliderCustomLoader.h"
#include "LayerBet_BaCayChuong.h"
#include "Nan3Cay.h"
//#include "mUtils.h"

#define V_REGISTER_LOADER_GLUE(NODE_LIBRARY, CLASS) NODE_LIBRARY->registerCCNodeLoader(#CLASS, CLASS##Loader::loader())


BaCayChuong::BaCayChuong():CARD_LEFT(NULL),CARD_RIGHT(NULL),CARD_TOP(NULL),CARD_ME(NULL),
btnLattat(NULL),
btnXemBai(NULL),
btnNanBai(NULL),
btnReady(NULL),
btnUnReady(NULL),
btnDatCuoc(NULL),
frameBet_Left(NULL),
frameBet_Right(NULL),
frameBet_Top(NULL),
frameBet_Me(NULL){
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
     left_Left = 117;
     left_Right = 539;
     left_Top = 328;
     height_card_notme = 48 * 1.3;
     width_card_notme = 48;
    
     bottom_card_l_r = 209;
     bottom_card_top = 268;
    
    /*-------Vi trí các lá bài của mình------------*/
     left_Me = 319;
     width_card_me = 54;
     height_card_me = 54 * 1.3;
     bottom_me = 90;
    
     flagChiaBai = false;
     flagDatCuoc = false;
    arrCardTypes[0] = "s";
    arrCardTypes[1] = "c";
    arrCardTypes[2] = "h";
    arrCardTypes[3] = "d";
    
    //Add Listener
    GameServer::getSingleton().addListeners(this);
    
    
    
    //Khởi tạo các thông số ban đầu
    string _list_user = "";
    string _list_cards = "";
    flagChiaBai = false;
    flagDatCuoc = false;
    demChiaBai = 0;
    
    //**Tạo bàn chơi
    createBackgrounds();
    createAvatars();
    createButtons();
    
    //*Khởi tạo các button trong game////
    uLayer = UILayer::create();
    uLayer->setAnchorPoint(ccp(0, 0));
    uLayer->setPosition(ccp(0, 0));
    this->addChild(uLayer);
    
    //Btn_Ready
    btnReady = UIButton::create();
    btnReady->loadTextures("ready.png", "ready_selected.png", "");
    btnReady->setTitleText("Sẵn Sàng");
    btnReady->setAnchorPoint(ccp(0,0));
    btnReady->setPosition(ccp(WIDTH_DESIGN-btnReady->getContentSize().width-20,10));
    btnReady->setTouchEnabled(true);
    btnReady->addTouchEventListener(this, toucheventselector(BaCayChuong::btn_ready_click));
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
    btnUnReady->addTouchEventListener(this, toucheventselector(BaCayChuong::btn_Unready_click));
    btnUnReady->setTitleFontSize(20);
    btnUnReady->setTitleColor(ccRED);
    btnUnReady->setVisible(false);
    uLayer->addWidget(btnUnReady);
    
    //Button Đặt cược
    btnDatCuoc = UIButton::create();
    btnDatCuoc->loadTextures("ready.png", "ready_selected.png", "");
    btnDatCuoc->setTitleText("Đặt Cược");
    btnDatCuoc->setAnchorPoint(ccp(0,0));
    btnDatCuoc->setPosition(ccp(WIDTH_DESIGN-btnDatCuoc->getContentSize().width*2-40,10));
    btnDatCuoc->setTouchEnabled(true);
    btnDatCuoc->addTouchEventListener(this, toucheventselector(BaCayChuong::btn_DatCuoc_click));
    btnDatCuoc->setVisible(true);
    btnDatCuoc->setTitleFontSize(20);
    btnDatCuoc->setTitleColor(ccRED);
    uLayer->addWidget(btnDatCuoc);
    
    //Btn_Lật tất
    btnLattat = UIButton::create();
    btnLattat->loadTextures("ready.png", "ready_selected.png", "");
    btnLattat->setTitleText("Lật Bài");
    btnLattat->setAnchorPoint(ccp(0,0));
    btnLattat->setPosition(ccp(WIDTH_DESIGN-btnLattat->getContentSize().width*2-40,10));
    btnLattat->setTouchEnabled(false);
    btnLattat->addTouchEventListener(this, toucheventselector(BaCayChuong::btn_btn_Latat));
    btnLattat->setVisible(false);
    btnLattat->setTitleFontSize(20);
    btnLattat->setTitleColor(ccRED);
    uLayer->addWidget(btnLattat);
    
    //Btn Xem bài
    btnXemBai = UIButton::create();
    btnXemBai->loadTextures("ready.png", "ready_selected.png", "");
    btnXemBai->setTitleText("Xem Bài");
    btnXemBai->setAnchorPoint(ccp(0,0));
    btnXemBai->setPosition(ccp(WIDTH_DESIGN-btnXemBai->getContentSize().width-20,btnXemBai->getContentSize().height+20));
    btnXemBai->setTouchEnabled(false);
    btnXemBai->addTouchEventListener(this, toucheventselector(BaCayChuong::btn_XemBai_click));
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
    btnNanBai->addTouchEventListener(this, toucheventselector(BaCayChuong::btn_NanBai_click));
    btnNanBai->setVisible(false);
    btnNanBai->setTitleFontSize(20);
    btnNanBai->setTitleColor(ccRED);
    uLayer->addWidget(btnNanBai);
    
    //Khởi tạo mảng các lá bài
    CARD_ME = new CCArray();
    CARD_LEFT = new CCArray();
    CARD_RIGHT = new CCArray();
    CARD_TOP = new CCArray();
    
    CARD_ME->retain();
    CARD_LEFT->retain();
    CARD_TOP->retain();
    CARD_RIGHT->retain();
    
//    FrameBet *bet1 = FrameBet::create();
//    bet1->setPosition(ccp(left_Me, 240));
//    bet1->setValueBet("1.000.000 $");
//    this->addChild(bet1);
    
    frameBet_Right = FrameBet::create();
    frameBet_Left = FrameBet::create();
    frameBet_Me = FrameBet::create();
    frameBet_Top = FrameBet::create();
    
    frameBet_Left->setVisible(false);
    frameBet_Right->setVisible(false);
    frameBet_Top->setVisible(false);
    frameBet_Me->setVisible(false);
    
    this->addChild(frameBet_Me);
    this->addChild(frameBet_Right);
    this->addChild(frameBet_Top);
    this->addChild(frameBet_Left);
//    btn_btn_Latat();
    
}

BaCayChuong::~BaCayChuong(){
    GameServer::getSingleton().removeListeners(this);
    CARD_ME->removeAllObjects();
    CARD_ME = NULL;
    CARD_LEFT->removeAllObjects();
    CARD_LEFT = NULL;
    CARD_RIGHT->removeAllObjects();
    CARD_RIGHT = NULL;
    CARD_TOP->removeAllObjects();
    CARD_TOP = NULL;
    this->removeAllChildrenWithCleanup(true);
    this->removeAllComponents();
    CCLOG("Deconstructor 3 Cay Chuong --- Jump Here !");
}

//* init bàn chơi
bool BaCayChuong::init(){
    if(!CCLayer::init()){
        return false;
    }
    
    return true;
}

void BaCayChuong::createBackgrounds(){
    BackgroundInGame *bg = BackgroundInGame::create();
    this->addChild(bg);
}
void BaCayChuong::createAvatars(){
    layerAvatars = LayerAvatarInGame::create();
    this->addChild(layerAvatars);
}
void BaCayChuong::createButtons(){
    LayerButtonInGame *layerButtons = LayerButtonInGame::create();
    this->addChild(layerButtons);
}

void BaCayChuong::createLayerChat(){
	layerChat = LayerChatInGame::create();
	this->addChild(layerChat);
}

//***********Sự kiện Server**************///

void BaCayChuong::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
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
        string _lu = "";
        if (lu != NULL) {
            _lu = lu->c_str();
        }
        if(lu != NULL){
            CCLOG("List user: %s",lu->c_str());
            _list_user = _lu;
            action_UpdateListUser(_lu);
            action_UserRejoinGame(_lu);
        }else{
            CCLOG("List user NULL");
        }
    }
    
    //User ready
    else if(strcmp(EXT_EVENT_READY_NTF.c_str(), cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        if(uid != NULL){
           whenUserReady(*uid);
        }else{
            CCLOG("uid NULL");
        }
    }
    
    //User Unready
    else if(strcmp("urntf", cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        if (uid != NULL) {
            whenUserUnready(*uid);
        }else{
            CCLOG("uid unready NULL");
        }
    }
    
    // Game Start
    else if(strcmp(EXT_EVENT_START.c_str(), cmd->c_str())==0){
        whenGameStart();
        if(!flagChiaBai){
            action_ChiaBai();
        }
		CCLOG("EXT_EVENT_START");
    }
    
    // List Card NTF
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
        
        //_list_cards
        if(strcmp(uid->c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            _list_cards = lc->c_str();
        }
        if(flagChiaBai){
            CCLOG("Lat bai");
            action_LatBai(_lc, _uid,_tua);
        }
        
    }
    
    // Game End
    else if(strcmp(EXT_EVENT_END.c_str(), cmd->c_str())==0){
        this->whenGameEnd();
    }
    
    // Game Resuilt
    else if(strcmp(EXT_EVENT_GAME_RESULT.c_str(), cmd->c_str())==0){
        boost::shared_ptr<string> rg = param->GetUtfString("rg");
        if(rg != NULL){
            CCLOG("Result: %s",rg->c_str());
            whenResuiltGame(*rg);
        }else{
            CCLOG("Không nhận được Result");
        }
    }
    
    //Game Bet NTF
    else if(strcmp("gb_ntf", cmd->c_str())==0){
        CCLOG("Dat cuoc");
        //gbv":1000,"uid":"thanhhv3
        boost::shared_ptr<long> gbv = param->GetInt("gbv");
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        
        string _gbv = "";
        string _uid = "";
        
        if(gbv != NULL){
            _gbv = boost::to_string(*gbv);
        }
        if( uid != NULL){
            _uid = uid->c_str();
        }
        
        action_GameBetNTF(_uid,_gbv);
    }
}


void BaCayChuong::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
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
void BaCayChuong::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}
void BaCayChuong::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}
void BaCayChuong::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}

//****** Một số hàm cần thiết********//
// function split string
vector<string> BaCayChuong::Dsplit(string &S,const char &str){
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

//Get pos user by name
int BaCayChuong::getPosUserByName(string uid,string _list_user){
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

// Tìm chủ phòng
string BaCayChuong::find_ChuPhong(string listUser){
    vector<string> arrUser = Dsplit(listUser,';');
    vector<string> info = Dsplit(arrUser[0], '|');
    string boosId = info[0];
    return boosId;
}

//Tìm chương
string BaCayChuong::find_Chuong(string listUser){
    string chuong = "";
    if(_list_user!=""){
        vector<string> arrUser = Dsplit(listUser, ';');
        for(int i=0;i<arrUser.size();i++){
            if(arrUser[i]=="")
                continue;
            vector<string> info = Dsplit(arrUser[i], '|');
            if(info[1] == "0"){
                chuong = info[0];
                break;
            }
        }
    }
    return chuong;
}

//Tìm lá bài
string BaCayChuong::findTypeCard(string card){
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

//******* Xử lý sự kiện nhận được ************///
//Update list user
void BaCayChuong::action_UpdateListUser(string lsUser){
    layerAvatars->resetAll();
    frameBet_Me->setVisible(false);
    frameBet_Left->setVisible(false);
    frameBet_Right->setVisible(false);
    frameBet_Top->setVisible(false);
    
    CCLOG("id chuong : %s",find_Chuong(_list_user).c_str());

    if(strcmp(GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str(),find_Chuong(_list_user).c_str())==0){
		
        layerAvatars->setPosChuong(kUserMe);
        btnDatCuoc->setTouchEnabled(false);
        btnDatCuoc->setVisible(false);
        btnReady->setTitleText("Chia Bài");
    }
    else{
        btnReady->setTitleText("Sẵn Sàng");
        btnDatCuoc->setTouchEnabled(true);
        btnDatCuoc->setVisible(true);
    }
    
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
        
        string _name = "";
		string _url = "";
		int _test = 0;
        
		boost::shared_ptr<string> url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("aal")->GetStringValue();
		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("aN")->GetStringValue();
        boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])->GetVariable("amf")->GetDoubleValue();
        
        if (name != NULL) {
            _name = name->c_str();
        }
        if(money != NULL){
			_test = (int)*money;
        }
        if (url != NULL)
        {
			_url = url->c_str();
        }
        

        if(strcmp(n[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			layerAvatars->getUserByPos(kUserMe)->setVisibleLayerInvite(false);
            layerAvatars->setName(kUserMe, _name.c_str());
			layerAvatars->getUserByPos(kUserMe)->setIcon(_url);
			layerAvatars->getUserByPos(kUserMe)->setMoney(_test);
            
            frameBet_Me->setValueBet((n[2]+" $").c_str());
            frameBet_Me->setPosition(ccp(75,396));
            frameBet_Me->setVisible(true);
            
            if(n[0] == find_ChuPhong(_list_user)){
                layerAvatars->setFlag(kUserMe, true);
            }
            if(n[0] == find_Chuong(_list_user)){
                btnReady->setTitleText("Chia Bài");
				frameBet_Me->setVisible(false);
            }
            if(n[0] != find_Chuong(_list_user)){
                btnReady->setTitleText("Sẵn sàng");
				frameBet_Me->setVisible(true);
            }
        }
        else{
            switch (getPosUserByName(n[0], _list_user)) {
                case kUserLeft:
					layerAvatars->getUserByPos(kUserLeft)->setVisibleLayerInvite(false);
                    layerAvatars->setName(kUserLeft, _name.c_str());
                    layerAvatars->getUserByPos(kUserLeft)->setMoney(_test);
					layerAvatars->getUserByPos(kUserLeft)->setIcon(_url);
                    
                    frameBet_Left->setValueBet((n[2]+" $").c_str());
                    frameBet_Left->setPosition(ccp(109,278));
                    frameBet_Left->setVisible(true);
                    
                    if(n[0]==find_ChuPhong(_list_user)){
                        layerAvatars->setFlag(kUserLeft, true);
                    }
                    if(n[0]==find_Chuong(_list_user)){
                        layerAvatars->setPosChuong(kUserLeft);
                        frameBet_Left->setVisible(false);
                    }
                    break;
                case kUserRight:
					layerAvatars->getUserByPos(kUserRight)->setVisibleLayerInvite(false);
                    layerAvatars->setName(kUserRight, _name.c_str());
                    layerAvatars->getUserByPos(kUserRight)->setMoney(_test);
					layerAvatars->getUserByPos(kUserRight)->setIcon(_url);
                    
                    frameBet_Right->setValueBet((n[2]+" $").c_str());
                    frameBet_Right->setPosition(ccp(WIDTH_DESIGN-109-frameBet_Right->getKc_width(),278));
                    frameBet_Right->setVisible(true);
                    
                    if(n[0]==find_ChuPhong(_list_user)){
                        layerAvatars->setFlag(kUserRight, true);
                    }
                    if(n[0]==find_Chuong(_list_user)){
                        layerAvatars->setPosChuong(kUserRight);
                        frameBet_Right->setVisible(false);
                    }
                    break;
                case kUserTop:
					layerAvatars->getUserByPos(kUserTop)->setVisibleLayerInvite(false);
                    layerAvatars->setName(kUserTop, _name.c_str());
                    layerAvatars->getUserByPos(kUserTop)->setMoney(_test);
					layerAvatars->getUserByPos(kUserTop)->setIcon(_url);
                    
                    frameBet_Top->setValueBet((n[2]+" $").c_str());
                    frameBet_Top->setPosition(ccp(454, 440));
                    frameBet_Top->setVisible(true);
                    
                    if(n[0]==find_ChuPhong(_list_user)){
                        layerAvatars->setFlag(kUserTop, true);
                    }
                    if(n[0]==find_Chuong(_list_user)){
                        layerAvatars->setPosChuong(kUserTop);
                        frameBet_Top->setVisible(false);
                    }
                    break;
            }
        }
    }
}

//Reconect game
void BaCayChuong::action_UserRejoinGame(string lsUser){
    vector<string> list = Dsplit(lsUser, ';');
    
    for(int k=0;k<list.size();k++){
        CCLOG("Jump here: %s",list[k].c_str());
    }

    if(strcmp(Dsplit(list[0], '|')[3].c_str(), "1")==0){
        flagChiaBai = true;
        btnReady->setTouchEnabled(false);
        btnReady->setVisible(false);
        btnUnReady->setTouchEnabled(false);
        btnUnReady->setVisible(false);
        btnDatCuoc->setVisible(false);
        btnDatCuoc->setTouchEnabled(false);
    }
    
    for(int i=0;i<list.size();i++){
        vector<string> info = Dsplit(list[i], '|');
        if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            if(info[3]== "1" && CARD_ME->count() == 0){
                CCLOG("Me Rejoin");
                restoreListCard(CARD_ME, width_card_me, height_card_me, left_Me, bottom_me);
                CCLOG(" CARD_ME: %d",CARD_ME->count());
            }
        }
        else{
            switch (getPosUserByName(info[0], _list_user)) {
                case kUserLeft:
                    if(info[3]=="1" && CARD_LEFT->count() == 0){
                        CCLOG("Left Rejoin");
                        restoreListCard(CARD_LEFT, width_card_notme, height_card_notme, left_Left, bottom_card_l_r);
                    }
                    break;
                case kUserRight:
                    if(info[3]=="1" && CARD_RIGHT->count() == 0){
                        CCLOG("Right Rejoin");
                        restoreListCard(CARD_RIGHT, width_card_notme, height_card_notme, left_Right, bottom_card_l_r);
                    }
                    break;
                case kUserTop:
                    if(info[3]=="1" && CARD_TOP->count() == 0){
                        CCLOG("Top Rejoin");
                        restoreListCard(CARD_TOP, width_card_notme, height_card_notme, left_Top, bottom_card_top);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

// Restore listcard
void BaCayChuong::restoreListCard(CCArray *P,float _widtd, float _height, float _left, float _bottom){
    for(int i=0;i<3;i++){
        CardChan *pCard = CardChan::create();
        pCard->loadTexture("card_back.png");
        pCard->setSizeCard(_widtd, _height);
        pCard->setPosition(ccp(_left+i*_widtd,_bottom));
        P->addObject(pCard);
        uLayer->addChild(pCard);
    }
}

// Game Bet Notifications
void BaCayChuong::action_GameBetNTF(string uid, string gameBet){
    switch (getPosUserByName(uid, _list_user)) {
        case kUserMe:
            frameBet_Me->setValueBet((gameBet+" $").c_str());
            break;
        case kUserLeft:
            frameBet_Left->setValueBet((gameBet+" $").c_str());
            break;
        case kUserRight:
            frameBet_Right->setValueBet((gameBet+" $").c_str());
            break;
        case kUserTop:
            frameBet_Top->setValueBet((gameBet+" $").c_str());
            break;
        default:
            break;
    }
}

//Action Lật bài
void BaCayChuong::action_LatBai(string listCard,string uid, bool tua){
    CCLOG("Nhay vao lat bai ?????");
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        if(tua){
            createCardMe(listCard);
            btnNanBai->setTouchEnabled(false);
            btnNanBai->setVisible(false);
            btnXemBai->setTouchEnabled(false);
            btnXemBai->setVisible(false);
            btnLattat->setVisible(false);
            btnLattat->setTouchEnabled(false);
        }
        else{
            createCardMe("0_0-0_0-0_0");
            btnNanBai->setTouchEnabled(true);
            btnNanBai->setVisible(true);
            btnXemBai->setTouchEnabled(true);
            btnXemBai->setVisible(true);
            btnLattat->setVisible(true);
            btnLattat->setTouchEnabled(true);
        }
    }
    else
    {
        switch (getPosUserByName(uid, _list_user)) {
            case kUserLeft:
                createCardLeft(listCard);
                break;
            case kUserRight:
                createCardRight(listCard);
                break;
            case kUserTop:
                createCardTop(listCard);
                break;
        }
    }
}

void BaCayChuong::createCardMe(string lc){
    vector<string> lsCards = Dsplit(lc,'-');
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

void BaCayChuong::createCardLeft(string lc){
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

void BaCayChuong::createCardRight(string lc){
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

void BaCayChuong::createCardTop(string lc){
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

void BaCayChuong::action_ChiaBai(){
	CCLOG("nhay vao day lan thu: %d",demChiaBai);
    //Tạo list user ảo
    string listuser = _list_user+_list_user+_list_user;
    vector<string> arrUser = Dsplit(listuser, ';');
    string player = arrUser[demChiaBai];
    vector<string> info = Dsplit(player, '|');
	CCLOG("Jumpe here");
    if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        demChiaBai++;
        action_AddCard4User(CARD_ME, width_card_me, height_card_me, left_Me, bottom_me, arrUser.size());
		CCLOG("Nhay vao me truoc");
    }
    else{
		CCLOG("Nguoi khac");
        switch (getPosUserByName(info[0], _list_user)) {
            case kUserLeft:
				CCLOG("Nguoi ben trai");
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
void BaCayChuong::action_AddCard4User(CCArray *P,float _widtd, float _height, float toX, float toY, int countUSer){
	CCLOG("Nhay vao add card P->count = %d",P->count());
    CardChan *card = CardChan::create();
    card->loadTexture("card_back.png");
    card->setSizeCard(width_card_notme, height_card_notme);
    card->setPosition(ccp(WIDTH_DESIGN/2-card->getContentSize().width/2,HEIGHT_DESIGN/2-card->getContentSize().height/2));
    uLayer->addChild(card);
    CCLOG("Here Hihihi");

	CCMoveBy *test = CCMoveBy::create(0.3,ccp(100,100));

    CCMoveBy *newTo = CCMoveTo::create(0.3, ccp(toX+P->count()*_widtd,toY));
    CCScaleBy *scaleTo = CCScaleBy::create(0.3, _widtd/width_card_notme,_height/height_card_notme);
    card->runAction(newTo);
    card->runAction(scaleTo);
    P->addObject(card);
    if(demChiaBai<countUSer){
		CCLOG("demchiaBai: %d, countUser: %d",demChiaBai,countUSer);
        this->runAction(CCSequence::create(CCDelayTime::create(0.3),CCCallFunc::create(this, callfunc_selector(BaCayChuong::action_ChiaBai)),NULL));
    }else{
        flagChiaBai = true;
        btnNanBai->setTouchEnabled(true);
        btnNanBai->setVisible(true);
        btnXemBai->setVisible(true);
        btnXemBai->setTouchEnabled(true);
        btnLattat->setTouchEnabled(true);
        btnLattat->setVisible(true);
    }
}


// user ready
void BaCayChuong::whenUserReady(string uid){
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        btnReady->setTouchEnabled(false);
        btnReady->setVisible(false);
        // hiện unready
		layerAvatars->setReady(kUserMe,true);
        btnUnReady->setTouchEnabled(true);
        btnUnReady->setVisible(true);
        flagDatCuoc = true;
    }
    else{
        switch (getPosUserByName(uid, _list_user)) {
            case kUserLeft:
                layerAvatars->setReady(kUserLeft,true);
                break;
			case kUserRight:
				layerAvatars->setReady(kUserRight,true);
				break;
			case kUserTop:
				layerAvatars->setReady(kUserTop,true);
				break;
            default:
                break;
        }
    }
}

//user unready
void BaCayChuong::whenUserUnready(string uid){
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        btnUnReady->setTouchEnabled(false);
        btnUnReady->setVisible(false);
        //hiện ready
		layerAvatars->setReady(kUserMe,false);
        btnReady->setTouchEnabled(true);
        btnReady->setVisible(true);
        flagDatCuoc = false;
    }
    else{
        switch (getPosUserByName(uid, _list_user)) {
            case kUserLeft:
                layerAvatars->setReady(kUserLeft,false);
                break;
			case kUserRight:
				layerAvatars->setReady(kUserRight,false);
				break;
			case kUserTop:
				layerAvatars->setReady(kUserTop,false);
				break;
            default:
                break;
        }
    }
}

// start game
void BaCayChuong::whenGameStart(){
	btnReady->setTouchEnabled(false);
	btnReady->setVisible(false);
	btnUnReady->setTouchEnabled(false);
	btnUnReady->setVisible(false);
	btnDatCuoc->setTouchEnabled(false);
	btnDatCuoc->setVisible(false);
    layerAvatars->setUnReadyAllUser();
}

// resuilt game
void BaCayChuong::whenResuiltGame(string rg){
    //thanhhv3|3|3|2|1000;dautv3|2|1|1|-1000
    LayerNumberInGame *layerNumbers = LayerNumberInGame::create();
	LayerChatInGame *Chatdd = LayerChatInGame::create();
    this->addChild(layerNumbers);
	this->addChild(Chatdd);
    vector<string> resuilt = Dsplit(rg, ';');
    for(int i=0;i<resuilt.size();i++){
        vector<string> info = Dsplit(resuilt[i], '|');
        if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
			Chatdd->showChatByPos(kUserMe,(info[1] +" Điểm"));
			layerNumbers->showNumberByPos(kUserMe, info[4]);
        }
        else{
            switch (getPosUserByName(info[0], _list_user)) {
                case kUserLeft:
					Chatdd->showChatByPos(kUserLeft,(info[1] +" Điểm"));
                    layerNumbers->showNumberByPos(kUserLeft, info[4]);
                    break;
                case kUserRight:
					Chatdd->showChatByPos(kUserRight,(info[1] +" Điểm"));
                    layerNumbers->showNumberByPos(kUserRight, info[4]);
                    break;
                case kUserTop:
					Chatdd->showChatByPos(kUserTop,(info[1] +" Điểm"));
                    layerNumbers->showNumberByPos(kUserTop, info[4]);
                    break;
                default:
                    break;
            }
        }
    }
}

// end game
void BaCayChuong::whenGameEnd(){
    
    //Ẩn hiện các button cần thiết
    btnReady -> setTouchEnabled(true);
    btnReady->setVisible(true);
    btnDatCuoc->setTouchEnabled(true);
    btnDatCuoc->setVisible(true);
    
    btnUnReady->setTouchEnabled(false);
    btnUnReady->setVisible(false);
    btnXemBai->setTouchEnabled(false);
    btnXemBai->setVisible(false);
    btnNanBai->setTouchEnabled(false);
    btnNanBai->setVisible(false);
    btnLattat->setTouchEnabled(false);
    btnLattat->setVisible(false);
    
    deleteAllCardFromArray(CARD_TOP);
    deleteAllCardFromArray(CARD_RIGHT);
    deleteAllCardFromArray(CARD_ME);
    deleteAllCardFromArray(CARD_LEFT);
    
   
    demChiaBai = 0;
    flagDatCuoc = false;
    flagChiaBai = false;
    _list_cards = "";
}

void BaCayChuong::deleteAllCardFromArray(cocos2d::CCArray *P){
    while(P->count()>0){
        CardChan *uu = (CardChan*)P->objectAtIndex(P->count()-1);
        P->removeObject(uu);
        uLayer->removeChild(uu);
    }
}

//**-Sự kiện các button click----///
void BaCayChuong::btn_ready_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_READY_REQ,parameter,lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}
void BaCayChuong::btn_Unready_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_UNREADY_REQ,params,lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}
void BaCayChuong::btn_DatCuoc_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        if(!flagDatCuoc){
            cocos2d::extension::CCBReader * ccbReader = NULL;
            CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
            V_REGISTER_LOADER_GLUE(ccNodeLoaderLibrary, SliderCustom);
            
            // register loaders
            ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
            ccNodeLoaderLibrary->registerCCNodeLoader("LayerBet_BaCayChuong",   LayerBet_BaCayChuongLoader::loader());
            // read main layer
            ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
            
            LayerBet_BaCayChuong *popUp;
            
            if (ccbReader)
            {
                popUp = (LayerBet_BaCayChuong *)ccbReader->readNodeGraphFromFile( "LayerBet_BaCayChuong.ccbi" );
                popUp->setPosition(ccp(10,10));
                uLayer->addChild(popUp);
                ccbReader->release();
            }
        }else{
            CCLOG("Bạn đã sẵn sàng, không thể đặt cược");
        }
    }
}
void BaCayChuong::btn_btn_Latat(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_TURNUP_CARD,params,lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}
void BaCayChuong::btn_XemBai_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        if(_list_cards != ""){
            createCardMe(_list_cards);
            btnNanBai->setTouchEnabled(false);
            btnNanBai->setVisible(false);
            btnXemBai->setVisible(false);
            btnXemBai->setTouchEnabled(false);
        }
    }
}
void BaCayChuong::btn_NanBai_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        CCLOG("Btn Nan Bai");
		Nan3Cay *BaCay = Nan3Cay::create();
		BaCay->initListCardHand(_list_cards);
		this->addChild(BaCay);
	}
}

string BaCayChuong::fn_format_money_2(string re){
    int r = atoi(re.c_str());
    string money = "";
    if (r < 1000) {
        return  re + "$";
    }
    if (r > 1000 && r <= 999999) {
        string _dv = "";
        int dv = r - (r / 1000) * 1000;
        if (dv < 10) {
            _dv = "00" + boost::to_string(dv);
        }
        if (dv >= 10 && dv <100) {
            _dv = "0" + boost::to_string(dv);
        }
        return boost::to_string(r/1000) + "," +_dv + "$";
    }
    if (r > 1000000) {
        int dv1 = (r % 1000000) / 1000;
        string _dv1 = "";
        if (dv1 < 10) {
            _dv1 = "0" + boost::to_string(dv1);
        }
        int dv2 = r % 1000;
        string _dv2 = "";
        if (dv2 < 10) {
            _dv2 = "00" + boost::to_string(dv2);
        }
        if (dv2 >= 10 && dv2 <100) {
            _dv2 = "0" + boost::to_string(dv2);
        }
        
        return boost::to_string(r / 1000000) + "," + _dv1 + "," + _dv2 + "$";
    }
}
