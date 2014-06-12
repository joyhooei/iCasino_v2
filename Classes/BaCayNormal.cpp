//
//  BaCayNormal.cpp
//  iCasino_v2
//
//  Created by DauA on 5/20/14.
//
//

#include "BaCayNormal.h"
#include "_Background_inGame_.h"
#include "_Button_inGame_.h"
#include "Requests/ExtensionRequest.h"
#include "CardChan.h"
#include "_Number_inGame_.h"
#include "Nan3Cay.h"
#include "_Chat_inGame_.h"
#include "mUtils.h"
#include "_Chat_.h"

BaCayNormal::BaCayNormal():CARD_RIGHT(NULL),CARD_ME(NULL),CARD_TOP(NULL),CARD_LEFT(NULL){
    
    EXT_EVENT_LIST_USER_UPDATE = "luu";
    EXT_EVENT_READY_NTF = "rntf";
    EXT_EVENT_START = "s";
    EXT_EVENT_LISTCARD_NTF = "lcntf";
    EXT_EVENT_END = "e";
    EXT_EVENT_GAME_RESULT = "grs";
    EXT_EVENT_UNREADY_NTF = "urntf";
    EXT_EVENT_UNREADY_REQ = "urr";
    EXT_EVENT_READY_REQ = "rr";
    EXT_EVENT_TURNUP_CARD = "tuc";
    
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
    
    GameServer::getSingleton().addListeners(this);
    
    _id_me =((boost::shared_ptr<string>)(GameServer::getSingleton().getSmartFox()->MySelf()->Name()));
    demChiaBai = 0;
    _list_cards = "";
    _list_user = "";
    
    boost::shared_ptr<User> mySelf = GameServer::getSingleton().getSmartFox()->MySelf();
    
    CCLOG("Ten %s",mySelf->Name()->c_str());
    boost::shared_ptr<double> inv = mySelf->GetVariable("am")->GetDoubleValue();
    CCLOG("Tien %f",*inv);
    CCLOG("Tien %s",mySelf->GetVariable("aal")->GetStringValue()->c_str());
    
    createBackgrounds();
    createAvatars();
    createButtons();
    
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
    btnReady->addTouchEventListener(this, toucheventselector(BaCayNormal::btn_ready_click));
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
    btnUnReady->addTouchEventListener(this, toucheventselector(BaCayNormal::btn_Unready_click));
    btnUnReady->setTitleFontSize(20);
    btnUnReady->setTitleColor(ccRED);
    btnUnReady->setVisible(false);
    uLayer->addWidget(btnUnReady);
    
    
    //Btn_Lật tất
    btnLattat = UIButton::create();
    btnLattat->loadTextures("ready.png", "ready_selected.png", "");
    btnLattat->setTitleText("Lật Bài");
    btnLattat->setAnchorPoint(ccp(0,0));
    btnLattat->setPosition(ccp(WIDTH_DESIGN-btnLattat->getContentSize().width*2-40,10));
    btnLattat->setTouchEnabled(false);
    btnLattat->addTouchEventListener(this, toucheventselector(BaCayNormal::btn_btn_Latat));
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
    btnXemBai->addTouchEventListener(this, toucheventselector(BaCayNormal::btn_XemBai_click));
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
    btnNanBai->addTouchEventListener(this, toucheventselector(BaCayNormal::btn_NanBai_click));
    btnNanBai->setVisible(false);
    btnNanBai->setTitleFontSize(20);
    btnNanBai->setTitleColor(ccRED);
    uLayer->addWidget(btnNanBai);
    
    //Khởi tạo mảng các lá bài
    CARD_ME = new CCArray();
    CARD_LEFT = new CCArray();
    CARD_RIGHT = new CCArray();
    CARD_TOP = new CCArray();

}

BaCayNormal::~BaCayNormal(){
    GameServer::getSingleton().removeListeners(this);
    CCLOG("Deconstructor 3 Cay Normal");
}

void BaCayNormal::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
}

// Hàm cắt 1 chuỗi
vector<string> BaCayNormal::Dsplit(string &S,const char &str){
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

bool BaCayNormal::init(){
    if(!CCLayer::init()){
        return false;
    }
    
    return true;
}

void BaCayNormal::onTouchButton(CCObject *pSender, TouchEventType pType){
    
}

void BaCayNormal::createBackgrounds(){
    BackgroundInGame *bg = BackgroundInGame::create();
    this->addChild(bg);
}

void BaCayNormal::createAvatars(){
    layerAvatars = LayerAvatarInGame::create();
    this->addChild(layerAvatars);
}

void BaCayNormal::createButtons(){
    LayerButtonInGame *layerButtons = LayerButtonInGame::create();
    this->addChild(layerButtons);
}

//Update list user
void BaCayNormal::updateUser(string list){
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
        vector<string> n = Dsplit(player, '|');
        
        if(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(n[0])==NULL){
            continue;
        }
        
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
        }
        if (url != NULL)
        {
			_url = url->c_str();
			CCLOG("Avatar: %s",url->c_str());
        }
        
        if(strcmp(n[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            layerAvatars->setName(kUserMe, _name.c_str());
            layerAvatars->getUserByPos(kUserMe)->setMoney(_money);
			layerAvatars->getUserByPos(kUserMe)->setIcon(_url);
			

            if(n[0]==find_ChuPhong(_list_user)){
                layerAvatars->setFlag(kUserMe, true);
                btnReady->setTitleText("Chia Bài");
            }
            else{
                btnReady->setTitleText("Sẵn sàng");
            }
        }
        else{
            switch (getPosUserByName(n[0], _list_user)) {
                case kUserLeft:
					layerAvatars->getUserByPos(kUserLeft)->setVisibleLayerInvite(false);
                    layerAvatars->setName(kUserLeft, _name.c_str());
                    layerAvatars->getUserByPos(kUserLeft)->setMoney(_money);
					layerAvatars->getUserByPos(kUserLeft)->setIcon(_url);
                    if(n[0]==find_ChuPhong(_list_user)){
                        layerAvatars->setFlag(kUserLeft, true);
                    }
                    break;
                case kUserRight:
					layerAvatars->getUserByPos(kUserRight)->setVisibleLayerInvite(false);
                    layerAvatars->setName(kUserRight, _name.c_str());
                    layerAvatars->getUserByPos(kUserRight)->setMoney(_money);
					layerAvatars->getUserByPos(kUserRight)->setIcon(_url);
                    if(n[0]==find_ChuPhong(_list_user)){
                        layerAvatars->setFlag(kUserRight, true);
                    }
                    break;
                case kUserTop:
					layerAvatars->getUserByPos(kUserTop)->setVisibleLayerInvite(false);
                    layerAvatars->setName(kUserTop, _name.c_str());
                    layerAvatars->getUserByPos(kUserTop)->setMoney(_money);
					layerAvatars->getUserByPos(kUserTop)->setIcon(_url);
                    if(n[0]==find_ChuPhong(_list_user)){
                        layerAvatars->setFlag(kUserTop, true);
                    }
                    break;
            }
        }
    }
}

//Khôi phục hoặc vẽ bàn chơi khi người chơi mất kết nối hoặc có khách re join room
void BaCayNormal::whenUserRejoinOrGuess(string listUser){
    vector<string> list = Dsplit(listUser, ';');
    if(strcmp(Dsplit(list[0], '|')[1].c_str(), "1")==0){
        flagChiaBai = true;
        btnReady->setTouchEnabled(false);
        btnReady->setVisible(false);
        btnUnReady->setTouchEnabled(false);
        btnUnReady->setVisible(false);
    }
    for(int i=0;i<list.size();i++){
        vector<string> info = Dsplit(list[i], '|');
        if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            if((info[1]== "1") && CARD_ME->count() == 0){
                restoreListCard(CARD_ME, width_card_me, height_card_me, left_Me, bottom_me);
            }
        }
        else{
                switch (getPosUserByName(info[0], _list_user)) {
                    case kUserLeft:
                        if(info[1]=="1" && CARD_LEFT->count() == 0){
                            restoreListCard(CARD_LEFT, width_card_notme, height_card_notme, left_Left, bottom_card_l_r);
                        }
                        break;
                    case kUserRight:
                        if(info[1]=="1" && CARD_RIGHT->count() == 0){
                            restoreListCard(CARD_RIGHT, width_card_notme, height_card_notme, left_Right, bottom_card_l_r);
                        }
                        break;
                    case kUserTop:
                        if(info[1]=="1" && CARD_TOP->count() == 0){
                            restoreListCard(CARD_TOP, width_card_notme, height_card_notme, left_Top, bottom_card_top);
                        }
                        break;
                    default:
                        break;
                }
            }
    }
}
//Khôi phục danh sách các lá bài
void BaCayNormal::restoreListCard(CCArray *P,float _widtd, float _height, float _left, float _bottom){
    for(int i=0;i<3;i++){
        CardChan *pCard = CardChan::create();
        pCard->loadTexture("card_back.png");
        pCard->setSizeCard(_widtd, _height);
        pCard->setPosition(ccp(_left+i*_widtd,_bottom));
        P->addObject(pCard);
        uLayer->addChild(pCard);
    }
    CCLOG("Size of Array: %u",P->count());
}

// Tìm chủ phòng
string BaCayNormal::find_ChuPhong(string listUser){
    vector<string> arrUser = Dsplit(listUser,';');
    vector<string> info = Dsplit(arrUser[0], '|');
    string boosId = info[0];
    return boosId;
}

// tìm vị trí người chơi so với mình
int BaCayNormal::getPosUserByName(string uid,string _list_user){
    int vt = -1;
    vector<string> list;
    if(_list_user.c_str() != NULL && _list_user != ""){
        list = Dsplit(_list_user, ';');
    }
    //Tìm vị trí của mình trong list user
    for(int i=0;i<list.size();i++){
        string _id = Dsplit(list[i], '|')[0];
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

//Update Event
void BaCayNormal::updateEvent( float dt ){
    GameServer::getSingleton().updateEvent();
}

// Xử lý các respone Server
void BaCayNormal::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    
    if(strcmp("hbc", cmd->c_str())==0){
        return;
    }
    CCLOG("cmd = %s",cmd->c_str());
    
    //list user update
    if(strcmp(EXT_EVENT_LIST_USER_UPDATE.c_str(), cmd->c_str())==0){
        boost::shared_ptr<string> lu = param->GetUtfString("lu");
        if (lu != NULL) {
            CCLOG("List user: %s",lu->c_str());
            _list_user = *lu;
            updateUser(*lu);
            whenUserRejoinOrGuess(*lu);
        }else{
            _list_user = "";
            CCLOG("Không nhận được listuser");
        }
    }
    
    //user ready
    else if(strcmp(EXT_EVENT_READY_NTF.c_str(), cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        if(uid != NULL){
            whenUserReady(*uid);
        }
    }
    
	//ready error
	else if (strcmp("e_rntf",cmd->c_str()) == 0)
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

    //user unready
    else if(strcmp(EXT_EVENT_UNREADY_NTF.c_str(), cmd->c_str())==0){
        boost::shared_ptr<string> uid = param->GetUtfString("uid");
        if(uid != NULL){
            whenUserUnready(*uid);
        }
    }
    
    //game start
    else if(strcmp(EXT_EVENT_START.c_str(), cmd->c_str())==0){
        btnReady->setTouchEnabled(false);
        btnReady->setVisible(false);
        btnUnReady->setTouchEnabled(false);
        btnUnReady->setVisible(false);
        
        if(!flagChiaBai){
            chiaBai();
        }
    }
    //Event List cards
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
        
        if(strcmp(uid->c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            _list_cards = _lc;
        }
        if(flagChiaBai){
            CCLOG("Lat bai");
            LatBai(_lc, _uid, _tua);
        }
    }
    
    // End game
    else if(strcmp(EXT_EVENT_END.c_str(), cmd->c_str())==0){
        this->whenGameEnd();
    }
    
    //Resuilt game
    else if(strcmp(EXT_EVENT_GAME_RESULT.c_str(), cmd->c_str())==0){
        boost::shared_ptr<string> rg = param->GetUtfString("rg");
        if(rg != NULL){
            whenResuiltGame(*rg);
        }
    }
}//End of Extensions Responds

//OnVariableUpdate
void BaCayNormal::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
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
void BaCayNormal::OnSmartFoxPublicMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}
void BaCayNormal::OnSmartFoxConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    
}
void BaCayNormal::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    CCLOG("User ExitRoom On Room");
}


/*** CÁC BUTTON TRONG GAME ********/
// Button Sẵn Sàng Click
void BaCayNormal::btn_ready_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_READY_REQ,parameter,lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}

// Button Hủy Sẵn Sàng
void BaCayNormal::btn_Unready_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_UNREADY_REQ,params,lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}

// Button Lật Bài click
void BaCayNormal::btn_btn_Latat(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(EXT_EVENT_TURNUP_CARD,params,lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}

//Button Xem Bài
void BaCayNormal::btn_XemBai_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
        if(_list_cards!=""){
            createCardMe(_list_cards);
            btnNanBai->setTouchEnabled(false);
            btnNanBai->setVisible(false);
            btnXemBai->setVisible(false);
            btnXemBai->setTouchEnabled(false);
        }
    }
}

//Button Nặn Bài
void BaCayNormal::btn_NanBai_click(CCObject *sender, TouchEventType type){
    if(type == TOUCH_EVENT_ENDED){
		CCLOG("Btn Nan Bai");
		Nan3Cay *BaCay = Nan3Cay::create();
		BaCay->setCallbackFunc(this,callfuncN_selector(BaCayNormal::callBackFunction_LatBai));
		BaCay->initListCardHand(_list_cards);
		this->addChild(BaCay);
    }
}

void BaCayNormal::callBackFunction_LatBai(CCNode *pSend){
	if(_list_cards!=""){
		createCardMe(_list_cards);
		btnNanBai->setTouchEnabled(false);
		btnNanBai->setVisible(false);
		btnXemBai->setVisible(false);
		btnXemBai->setTouchEnabled(false);
	}
	else{
		CCLOG("Not OK");
	}
}
/******** End Button ------------------*/


/*********** Các function Xử lý game -------------*///

//Khi 1 người chơi Sẵn Sàng
void BaCayNormal::whenUserReady(string uid){
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        btnReady->setTouchEnabled(false);
        btnReady->setVisible(false);
        // hiện unready
        btnUnReady->setTouchEnabled(true);
        btnUnReady->setVisible(true);
    }
    else{
        switch (getPosUserByName(uid, _list_user)) {
            case kUserLeft:
                //Ẩn hiện Avartar
                break;
            default:
                break;
        }
    }
}

//Khi 1 người chơi hủy Sẵn Sàng
void BaCayNormal::whenUserUnready(string uid){
    if(strcmp(uid.c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
        btnUnReady->setTouchEnabled(false);
        btnUnReady->setVisible(false);
        //hiện ready
        btnReady->setTouchEnabled(true);
        btnReady->setVisible(true);
    }
    else{
        switch (getPosUserByName(uid, _list_user)) {
            case kUserLeft:
                //Ẩn hiện Avartar
                break;
            default:
                break;
        }
    }
}

//Khi GameStart
void BaCayNormal::whenGameStart(){
    btnReady -> setTouchEnabled(false);
    btnReady->setVisible(false);
    btnUnReady->setTouchEnabled(false);
    btnUnReady->setVisible(false);
    
//    btnXemBai->setTouchEnabled(true);
//    btnXemBai->setVisible(true);
//    btnNanBai->setTouchEnabled(true);
//    btnNanBai->setVisible(true);
    btnLattat->setTouchEnabled(true);
    btnLattat->setVisible(true);
}

//Resuilt Game
void BaCayNormal::whenResuiltGame(string rg){
    LayerNumberInGame *layerNumbers = LayerNumberInGame::create();
    this->addChild(layerNumbers);
	LayerChatInGame *layerChat = LayerChatInGame::create();
	this->addChild(layerChat);
    //dautv3|4|8|3|1000;dautv|1|1|2|-1000
    vector<string> resuilt = Dsplit(rg, ';');
    for(int i=0;i<resuilt.size();i++){
        vector<string> info = Dsplit(resuilt[i], '|');
        if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            layerChat->showChatByPos(kUserMe,(info[1]+" Điểm"));
			layerNumbers->showNumberByPos(kUserMe, info[4]);
        }
        else{
            switch (getPosUserByName(info[0], _list_user)) {
                case kUserLeft:
					layerChat->showChatByPos(kUserLeft,(info[1]+" Điểm"));
                    layerNumbers->showNumberByPos(kUserLeft, info[4]);
                    break;
                case kUserRight:
					layerChat->showChatByPos(kUserRight,(info[1]+" Điểm"));
                    layerNumbers->showNumberByPos(kUserRight, info[4]);
                    break;
                case kUserTop:
					layerChat->showChatByPos(kUserTop,(info[1]+" Điểm"));
                    layerNumbers->showNumberByPos(kUserTop, info[4]);
                    break;
                default:
                    break;
            }
        }
    }
}
//Khi GameEnd
void BaCayNormal::whenGameEnd(){
    //Ẩn hiện các button cần thiết
    btnReady -> setTouchEnabled(true);
    btnReady->setVisible(true);
    
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
    
    flagChiaBai = false;
    demChiaBai = 0;
    _list_cards = "";
}

// chia Bài
void BaCayNormal::chiaBai(){
    //Tạo list user ảo
    string listuser = _list_user+_list_user+_list_user;
    vector<string> arrUser = Dsplit(listuser, ';');
        string player = arrUser[demChiaBai];
        vector<string> info = Dsplit(player, '|');
        if(strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str())==0){
            demChiaBai++;
            addCard4User(CARD_ME, width_card_me, height_card_me, left_Me, bottom_me, arrUser.size());
        }
        else{
            switch (getPosUserByName(info[0], _list_user)) {
                case kUserLeft:
                    demChiaBai++;
                    addCard4User(CARD_LEFT, width_card_notme, height_card_notme, left_Left, bottom_card_l_r, arrUser.size());
                    break;
                case kUserRight:
                    demChiaBai++;
                    addCard4User(CARD_RIGHT, width_card_notme, height_card_notme, left_Right, bottom_card_l_r, arrUser.size());
                    break;
                case kUserTop:
                    demChiaBai++;
                    addCard4User(CARD_TOP, width_card_notme, height_card_notme, left_Top, bottom_card_top, arrUser.size());
                    break;
                default:
                    break;
            }
        }
    
}
//Add thêm 1 lá bài cho người chơi
void BaCayNormal::addCard4User(CCArray *P,float _widtd, float _height, float toX, float toY, int countUSer){
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
        this->runAction(CCSequence::create(CCDelayTime::create(0.3),CCCallFunc::create(this, callfunc_selector(BaCayNormal::chiaBai)),NULL));
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

string arrCardTypes[] = {"s", "c", "h", "d"};

string findTypeCard(string card){
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

//Function Lật bài
void BaCayNormal::LatBai(string listCard,string uid, bool tua){
    CCLOG("Nhảy vào Lật bài");
    CCLOG("*********************************");
    CCLOG("Me: %d",CARD_ME->count());
    CCLOG("Left: %d",CARD_LEFT->count());
    CCLOG("Right: %d",CARD_RIGHT->count());
    CCLOG("Top: %d",CARD_TOP->count());
    CCLOG("*********************************");
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
    else{
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

void BaCayNormal::createCardMe(string lc){
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

void BaCayNormal::createCardLeft(string lc){
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

void BaCayNormal::createCardRight(string lc){
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

void BaCayNormal::createCardTop(string lc){
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

void BaCayNormal::deleteAllCardFromArray(cocos2d::CCArray *P){
    while(P->count()>0){
        CardChan *uu = (CardChan*)P->objectAtIndex(P->count()-1);
        P->removeObject(uu);
        uLayer->removeChild(uu);
    }
}






