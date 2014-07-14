//
//  LayerPlayGameTLMN.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/14/14.
//
//

#include "LayerPlayGameTLMN.h"
#include "SceneManager.h"
#include "mUtils.h"

vector<string> LayerPlayGameTLMN::split(string &S, const char &str) {
	vector<string> arrStr;
	string::iterator t, t2;

	for (t = S.begin(); t < S.end(); ){
		// Lặp từ vị trí bắt đầu
		t2 = find(t, S.end(), str);

		//kể từ vị trí t
		if(t != t2){
			arrStr.push_back(string(t, t2));
		}
		else if (t2 != S.end()) arrStr.push_back("");

		if (t2 == S.end())
		{
			break;
		}


		t = t2 + 1;
	}

	return arrStr;
}

enum EXT_REPONSE {
    EXT_EVENT_USER_JOIN_NOTIF,      // jrntf
    EXT_EVENT_LISTCARD_NTF,         //"lcntf";
    EXT_EVENT_ERROR_READY_NTF,      // = "e_rntf";
    EXT_EVENT_USER_READY_NOTIF,     // = "rdyntf";
    EXT_EVENT_UNREADY_NTF,          // = "urntf";
    EXT_EVENT_READY_RES,            // = "rdres";
    EXT_EVENT_LIST_USER_UPDATE,     // = "luu";
    EXT_EVENT_START_GAME_NOTIF,     // = "strntf";
    EXT_EVENT_DEAL_CARD_NOTIF,      // = "dlcntf";
    EXT_EVENT_USER_LEAVE_NOTIF,     // = "lrntf";
    EXT_EVENT_END_GAME_NOTIF,       // = "endntf";
    EXT_EVENT_AMF_TEST_NOTIF,       // = "cblltf";
    EXT_EVENT_VICTORY_NOTIF,        // = "vicntf";
    EXT_EVENT_NEAD_PLAY_NOTIF,      // = "ndpntf";
    EXT_EVENT_PLAY_CARD_NOTIF,      // = "plcntf";
    EXT_EVENT_GAME_CHANGE_NOTIF,    // = "gchntf";
    EXT_EVENT_PASS_CARD_NOTIF,      // = "pscntf";
    EXT_EVENT_PLAY_CARD_RES,        // = "plcrs";
    //
    EXT_EVENT_READY_REQ,            // = "rr";
    EXT_EVENT_PLAY_CARD_REQ,        // = "plcrq"
    EXT_EVENT_PASS_CARD_REQ         // = "pscrq";
};

int LayerPlayGameTLMN::convertResponseToInt(string inString) {
    if (inString == "jrntf")    return EXT_EVENT_USER_JOIN_NOTIF;
    if (inString == "lcntf")    return EXT_EVENT_LISTCARD_NTF;
    if (inString == "e_rntf")   return EXT_EVENT_ERROR_READY_NTF;
    if (inString == "rdyntf")   return EXT_EVENT_USER_READY_NOTIF;
    if (inString == "urntf")    return EXT_EVENT_UNREADY_NTF;
    if (inString == "rdres")    return EXT_EVENT_READY_RES;
    if (inString == "luu")      return EXT_EVENT_LIST_USER_UPDATE;
    if (inString == "strntf")   return EXT_EVENT_START_GAME_NOTIF;
    if (inString == "dlcntf")   return EXT_EVENT_DEAL_CARD_NOTIF;
    if (inString == "lrntf")    return EXT_EVENT_USER_LEAVE_NOTIF;
    if (inString == "endntf")   return EXT_EVENT_END_GAME_NOTIF;
    if (inString == "cblltf")   return EXT_EVENT_AMF_TEST_NOTIF;
    if (inString == "vicntf")   return EXT_EVENT_VICTORY_NOTIF;
    if (inString == "ndpntf")   return EXT_EVENT_NEAD_PLAY_NOTIF;
    if (inString == "plcntf")   return EXT_EVENT_PLAY_CARD_NOTIF;
    if (inString == "gchntf")   return EXT_EVENT_GAME_CHANGE_NOTIF;
    if (inString == "pscntf")   return EXT_EVENT_PASS_CARD_NOTIF;
    if (inString == "plcrs")    return EXT_EVENT_PLAY_CARD_RES;
    //
    if (inString == "rr")       return EXT_EVENT_READY_REQ;
    if (inString == "plcrq")    return EXT_EVENT_PLAY_CARD_REQ;
    if (inString == "pscrq")    return EXT_EVENT_PASS_CARD_REQ;
    
    return -1;
}

string LayerPlayGameTLMN::convertResponseToString(int inInt) {
    if (inInt == EXT_EVENT_USER_JOIN_NOTIF)     return "jrntf";
    if (inInt == EXT_EVENT_LISTCARD_NTF)        return "lcntf";
    if (inInt == EXT_EVENT_ERROR_READY_NTF)     return "e_rntf";
    if (inInt == EXT_EVENT_USER_READY_NOTIF)    return "rdyntf";
    if (inInt == EXT_EVENT_UNREADY_NTF)         return "urntf";
    if (inInt == EXT_EVENT_READY_RES)           return "rdres";
    if (inInt == EXT_EVENT_LIST_USER_UPDATE)    return "luu";
    if (inInt == EXT_EVENT_START_GAME_NOTIF)    return "strntf";
    if (inInt == EXT_EVENT_DEAL_CARD_NOTIF)     return "dlcntf";
    if (inInt == EXT_EVENT_USER_LEAVE_NOTIF)    return "lrntf";
    if (inInt == EXT_EVENT_END_GAME_NOTIF)      return "endntf";
    if (inInt == EXT_EVENT_AMF_TEST_NOTIF)      return "cblltf";
    if (inInt == EXT_EVENT_VICTORY_NOTIF)       return "vicntf";
    if (inInt == EXT_EVENT_NEAD_PLAY_NOTIF)     return "ndpntf";
    if (inInt == EXT_EVENT_PLAY_CARD_NOTIF)     return "plcntf";
    if (inInt == EXT_EVENT_GAME_CHANGE_NOTIF)   return "gchntf";
    if (inInt == EXT_EVENT_PASS_CARD_NOTIF)     return "pscntf";
    if (inInt == EXT_EVENT_PLAY_CARD_RES)       return "plcrs";
    //
    if (inInt == EXT_EVENT_READY_REQ)           return "rr";
    if (inInt == EXT_EVENT_PLAY_CARD_REQ)       return "plcrq";
    if (inInt == EXT_EVENT_PASS_CARD_REQ)       return "pscrq";
     
    return "";
}

LayerPlayGameTLMN::LayerPlayGameTLMN() {
    this->myName = SceneManager::getSingleton().getMyName();
    this->doTogether = new DoTogether();
    
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(-WIDTH_DESIGN / 2, -HEIGHT_DESIGN / 2));
    this->setTouchEnabled(false);
    
    //
    createBackgrounds();
    createAvatars();
    createButtons();
    createCards();
    createNumbers();
    createChats();
    
    GameServer::getSingleton().addListeners(this);
	SceneManager::getSingleton().hideLoading();
}

LayerPlayGameTLMN::~LayerPlayGameTLMN() {
	GameServer::getSingleton().removeListeners(this);

	arrName.clear();
	arrMoney.clear();
	arrIDTurn.clear();
}

void LayerPlayGameTLMN::onExit() {
	CCLOG("onExit: clean TLMN");

	GameServer::getSingleton().removeListeners(this);

	arrName.clear();
	arrMoney.clear();
	arrIDTurn.clear();
}


void LayerPlayGameTLMN::createBackgrounds() {
    BackgroundInGame *bg = BackgroundInGame::create();
    this->addChild(bg);

	// thông tin bàn chơi và mức cược
	int id = atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str());
	boost::shared_ptr<string> param = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string paramString = param->c_str();
	vector<string> arrInfo = split(paramString, '@');
	string money = arrInfo.at(0);

	mUtils mu;
	CCString *name = mUtils::getGameNameByID(id);
	//string name = "TLMN";
	string moneyConvert = mu.convertMoneyEx(atoi(money.c_str()));

	string result = "";
	if (name->length() > 0 && moneyConvert.length() > 0)
	{
		result = name->getCString();
		result += (" - cược:" + moneyConvert);
	}
	CCLabelTTF *nameGame= CCLabelTTF::create(result.c_str(), "", 16);
	nameGame->setPosition(ccp(400-5, 213+10));
	nameGame->setColor(ccWHITE);
	nameGame->setOpacity(150);
	bg->addChild(nameGame);
}

void LayerPlayGameTLMN::createAvatars() {
    layerAvatars = LayerAvatarInGame::create();
    this->addChild(layerAvatars);
}

void LayerPlayGameTLMN::createButtons() {
    layerButtons = LayerButtonInGame::create();
    this->addChild(layerButtons);
    
    int widButton = 129;
    //int heiButton = 44;
    int space = 10;
    
    // Chia bài
    Button *btnReady = createButtonWithTitle_Position("Sẵn sàng", ccp(WIDTH_DESIGN - space, space));
    Button *btnSortCard = createButtonWithTitle_Position("Xếp", ccp(WIDTH_DESIGN - space, space));
    Button *btnHitCard = createButtonWithTitle_Position("Đánh", ccp(WIDTH_DESIGN - space * 2 - widButton, space));
    Button *btnNextTurn = createButtonWithTitle_Position("Bỏ lượt", ccp(WIDTH_DESIGN - space * 3 - widButton * 2, space));
    
    btnReady->addTouchEventListener(this, toucheventselector(LayerPlayGameTLMN::actionReady));
    btnSortCard->addTouchEventListener(this, toucheventselector(LayerPlayGameTLMN::actionSortCards));
    btnHitCard->addTouchEventListener(this, toucheventselector(LayerPlayGameTLMN::actionHitCards));
    btnNextTurn->addTouchEventListener(this, toucheventselector(LayerPlayGameTLMN::actionNextTurn));
    
    btnReady->setTag(kTagButtonReady);
    btnSortCard->setTag(kTagButtonSort);
    btnHitCard->setTag(kTagButtonHit);
    btnNextTurn->setTag(kTagButtonNextTurn);
    
    btnSortCard->setEnabled(false);
    btnHitCard->setEnabled(false);
    btnNextTurn->setEnabled(false);

//    this->addChild(btnReady);
//    this->addChild(btnSortCard);
//    this->addChild(btnHitCard);
//    this->addChild(btnNextTurn);
    layerButtons->addWidgetEx(btnReady);
    layerButtons->addWidgetEx(btnSortCard);
    layerButtons->addWidgetEx(btnHitCard);
    layerButtons->addWidgetEx(btnNextTurn);
}

void LayerPlayGameTLMN::createNumbers() {
    layerNumbers = LayerNumberInGame::create();
    this->addChild(layerNumbers);
}

void LayerPlayGameTLMN::createCards() {
    layerCards = LayerCardInGame::create();
    layerCards->initCardByTienLen();
    this->addChild(layerCards);
}

void LayerPlayGameTLMN::createChats() {
    layerChats = LayerChatInGame::create();
    this->addChild(layerChats);
}

void LayerPlayGameTLMN::initGame() {
    // khởi tạo các giá trị ban đầu hoặc hiển thị các thông tin cần thiết
    
    // thông tin tiền hiện tại của Users
    for (int i = 0; i < arrName.size(); i++) {
        layerAvatars->setMoney(layerAvatars->getPosByName(arrName[i]), arrMoney[i]);
    }
    arrName.clear();
	arrMoney.clear();

    // unready all
    layerAvatars->setUnReadyAllUser();
}


void LayerPlayGameTLMN::playSound( string soundPath )
{
	if( mUtils::isSoundOn() )
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundPath.c_str());
}


Button* LayerPlayGameTLMN::createButtonWithTitle_Position(const char *title, CCPoint pPoint) {
    // Create the button
    Button* button = Button::create();
    button->setTouchEnabled(true);
    button->setScale9Enabled(false);
    button->loadTextures("ready.png", "ready_selected.png", "");
    button->setTitleText(title);
    button->setTitleColor(ccBLACK);
    button->setTitleFontSize(button->getContentSize().height / 2);
    button->setAnchorPoint(ccp(1, 0));
    
    button->setPosition(pPoint);
    
    return button;
}

Button* LayerPlayGameTLMN::getButtonByTag(int tag) {
    Button *button = (Button*) this->layerButtons->getWidgetByTag(tag);
    return button;
}

void LayerPlayGameTLMN::actionReady(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        CCLOG("clicked ready!");
        layerCards->resetGame();
        
        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_READY_REQ), parameter, lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}

void LayerPlayGameTLMN::actionSortCards(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        CCLOG("sort!");
        layerCards->actionSortCardByTienLen();
    }
}

void LayerPlayGameTLMN::actionHitCards(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        CCLog("danh bai clicked");
        vector<int> arrID = layerCards->getIdCardByClicked();
        
        string listID = "";
        for (int i = 0; i < arrID.size(); i++) {
            if (i != 0) {
                listID += ",";
            }
            ostringstream os;
            CCLog("ID quan bai danh la: %d", arrID[i]);
            os<<arrID[i];
            listID += os.str();
        }
        
            
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        params->PutUtfString("lc", listID);
        boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_PLAY_CARD_REQ), params, lastRoom));
        
        GameServer::getSingleton().getSmartFox()->Send(request);
        
    }
}

void LayerPlayGameTLMN::actionNextTurn(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_PASS_CARD_REQ), params, lastRoom));
        
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}

void LayerPlayGameTLMN::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    this->param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    
    if(strcmp("hbc", cmd->c_str())==0){
        return;
    }
    
    switch(convertResponseToInt(cmd->c_str())) {
        case EXT_EVENT_USER_JOIN_NOTIF:
            event_EXT_EVENT_USER_JOIN_NOTIF();
            break;
            
        case EXT_EVENT_LISTCARD_NTF:
            event_EXT_EVENT_LISTCARD_NTF();
            break;
            
        case EXT_EVENT_ERROR_READY_NTF:
            event_EXT_EVENT_ERROR_READY_NTF();
            break;
            
        case EXT_EVENT_USER_READY_NOTIF :
            event_EXT_EVENT_USER_READY_NOTIF();
            break;
            
        case EXT_EVENT_UNREADY_NTF :
            event_EXT_EVENT_UNREADY_NTF();
            break;
            
        case EXT_EVENT_READY_RES:
            event_EXT_EVENT_READY_RES();
            break;
            
        case EXT_EVENT_LIST_USER_UPDATE:
            event_EXT_EVENT_LIST_USER_UPDATE();
            break;
            
        case EXT_EVENT_START_GAME_NOTIF:
            event_EXT_EVENT_START_GAME_NOTIF();
            break;
            
        case EXT_EVENT_DEAL_CARD_NOTIF:
            event_EXT_EVENT_DEAL_CARD_NOTIF();
            break;
            
        case EXT_EVENT_USER_LEAVE_NOTIF:
            event_EXT_EVENT_USER_LEAVE_NOTIF();
            break;
            
        case EXT_EVENT_END_GAME_NOTIF:
            event_EXT_EVENT_END_GAME_NOTIF();
            break;
            
        case EXT_EVENT_AMF_TEST_NOTIF:
            event_EXT_EVENT_AMF_TEST_NOTIF();
            break;
            
        case EXT_EVENT_VICTORY_NOTIF:
            event_EXT_EVENT_VICTORY_NOTIF();
            break;
            
        case EXT_EVENT_NEAD_PLAY_NOTIF:
            event_EXT_EVENT_NEAD_PLAY_NOTIF();
            break;
            
        case EXT_EVENT_PLAY_CARD_NOTIF:
            event_EXT_EVENT_PLAY_CARD_NOTIF();
            break;
            
        case EXT_EVENT_GAME_CHANGE_NOTIF:
            event_EXT_EVENT_GAME_CHANGE_NOTIF();
            break;
            
        case EXT_EVENT_PASS_CARD_NOTIF:
            event_EXT_EVENT_PASS_CARD_NOTIF();
            break;
            
        case EXT_EVENT_PLAY_CARD_RES:
            event_EXT_EVENT_PLAY_CARD_RES();
            break;
    }
    
}

void LayerPlayGameTLMN::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
    CCLOG("Update User Variables");
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
    boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
    
    //string money = boost::to_string(*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
	int    money = (int) (*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
    string name = boost::to_string(*ptrNotifiedUser->Name());
    
	CCLog("OnSmartFoxUserVariableUpdate: name= %s, money= %d", name.c_str(), money);

    arrName.push_back(name);
    arrMoney.push_back(money);
}

void LayerPlayGameTLMN::OnSmartFoxPublicMessage( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
{
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
	//
	CCLOG("ptrNotifiedMessage: %s", ptrNotifiedMessage->c_str());
	//
	int vt = layerAvatars->getPosByName(ptrNotifiedUser->Name()->c_str());
	layerChats->showChatByPos(vt, ptrNotifiedMessage->c_str());
}

void LayerPlayGameTLMN::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	//
	if( ptrNotifiedUser->IsItMe() ){
		//close window - tricks by HoangDD
		layerButtons->eventTouchBtnBack(NULL, TOUCH_EVENT_ENDED);
	}
}

void LayerPlayGameTLMN::event_EXT_EVENT_USER_JOIN_NOTIF(){
    boost::shared_ptr<string> listUser = param->GetUtfString("lu");
    CCLog("EXT_EVENT_USER_JOIN_NOTIF");
    
    if (listUser != NULL) {
        CCLog("listUser= %s", listUser->c_str());
        
        layerAvatars->setListUserByTienLen(listUser->c_str());
        
        // thông tin tiền hiện tại của Users
        for (int i = 0; i < arrName.size(); i++) {
            layerAvatars->setMoney(layerAvatars->getPosByName(arrName[i]), arrMoney[i]);
        }
    }
}

void LayerPlayGameTLMN::event_EXT_EVENT_LISTCARD_NTF(){
    CCLog("EXT_EVENT_LISTCARD_NTF");
}

void LayerPlayGameTLMN::event_EXT_EVENT_ERROR_READY_NTF(){
    CCLog("event_EXT_EVENT_ERROR_READY_NTF");
}

void LayerPlayGameTLMN::event_EXT_EVENT_USER_READY_NOTIF(){
    boost::shared_ptr<string> fname = param->GetUtfString("uid");
    
    if (fname != NULL) {
        CCLog("EXT_EVENT_USER_READY_NOTIF name= %s", fname->c_str());
        
        layerAvatars->setReady(layerAvatars->getPosByName(fname->c_str()), true);
        if (fname->c_str() == this->myName && strcmp("Sẵn sàng", getButtonByTag(kTagButtonReady)->getTitleText()) == 0) {
            getButtonByTag(kTagButtonReady)->setTitleText("Đã sẵn sàng");
        }
    }
}

void LayerPlayGameTLMN::event_EXT_EVENT_UNREADY_NTF(){
    boost::shared_ptr<string> fname = param->GetUtfString("uid");
    CCLog("EXT_EVENT_UNREADY_NTF name= %s", fname->c_str());
}

void LayerPlayGameTLMN::event_EXT_EVENT_READY_RES(){
    boost::shared_ptr<long> rs = param->GetInt("rslt");
    
    if (rs != NULL) {
        CCLog("event_EXT_EVENT_READY_RES %ld", *rs.get());
        
        int rscode = *rs.get();
        if (rscode != 0) {
            layerChats->showChatByPos(-1, "Đợi người chơi khác!");
        }
    }
}

void LayerPlayGameTLMN::event_EXT_EVENT_LIST_USER_UPDATE(){
    boost::shared_ptr<string> listUser = param->GetUtfString("lu");
	if (listUser == NULL) return;
	layerChats->showChatByPos(-1, "Cập nhật người chơi");
    CCLog("event_EXT_EVENT_LIST_USER_UPDATE %s", listUser->c_str());
}

void LayerPlayGameTLMN::event_EXT_EVENT_START_GAME_NOTIF(){
    CCLog("event_EXT_EVENT_START_GAME_NOTIF");
    
    getButtonByTag(kTagButtonReady)->setEnabled(false);
    getButtonByTag(kTagButtonSort)->setEnabled(true);
    
    initGame();
}

void LayerPlayGameTLMN::event_EXT_EVENT_DEAL_CARD_NOTIF(){
//    // Danh sách bài (chỉ sử dụng cho lần đầu)
//    //Ti.App.EXT_FIELD_CARD_OPEN = "cropn";
//    var isCardOpen = params.cropn;
//    //EXT_FIELD_LIST_CARD = "lc";
//    var lc = params.lc;
//    var uid = params.uid;
    CCLog("event_EXT_EVENT_DEAL_CARD_NOTIF");
    boost::shared_ptr<string> listCard = param->GetUtfString("lc");
    
    if (listCard != NULL) {
        CCLog("listCard= %s", listCard->c_str());
        layerCards->actionDealCard(layerCards->getIDFromString_TienLen(listCard->c_str()));

		playSound("e_card.mp3");
    }
}

void LayerPlayGameTLMN::event_EXT_EVENT_USER_LEAVE_NOTIF(){
    boost::shared_ptr<string> listUser = param->GetUtfString("lu");
    CCLog("event_EXT_EVENT_USER_LEAVE_NOTIF");
          
    if (listUser != NULL){
        CCLog("listUser= %s", listUser->c_str());
        layerAvatars->setListUserByTienLen(listUser->c_str());
    }
}

void LayerPlayGameTLMN::event_EXT_EVENT_END_GAME_NOTIF(){
    CCLog("event_EXT_EVENT_END_GAME_NOTIF");
    layerAvatars->stopAllTimer();
    layerChats->showChatByPos(-1, "Kết thúc");
    layerCards->setGameStarted(false);
    
    getButtonByTag(kTagButtonSort)->setEnabled(false);
    getButtonByTag(kTagButtonHit)->setEnabled(false);
    getButtonByTag(kTagButtonNextTurn)->setEnabled(false);
    
    getButtonByTag(kTagButtonReady)->setTitleText("Sẵn sàng");
    getButtonByTag(kTagButtonReady)->setEnabled(true);

	arrIDTurn.clear();
}

void LayerPlayGameTLMN::event_EXT_EVENT_AMF_TEST_NOTIF(){
//    // sự kiện công/trừ tiền
//    var uid = params.uid;
//    var money = params.amf;
    
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    int money = (int) (*(param->GetDouble("amf")));
	int resson = -1;
	if ((param->GetInt("cbt")) != NULL){
		resson = (int) (*(param->GetInt("cbt")));
		CCLog("resson = %d", resson);
	}
    
    CCLog("event_EXT_EVENT_AMF_TEST_NOTIF");
    if (name != NULL && money != NULL) {
		CCLog("name= %s, money= %d", name->c_str(), money);

        int pos = layerAvatars->getPosByName(name->c_str());
        layerNumbers->showNumberByPos(pos, to_string(money));
		
		if (resson < 0) return;
		string ressonString = "";
		switch (resson) {
			case 1:
				ressonString = "thối 2";
				break;
			case 2:
				ressonString = "người thua bị thối 2";
				break;
			case 3:
				ressonString = "chặn được 2";
				break;
			case 4:
				ressonString = "bị bắt 2";
				break;
			case 5:
				ressonString = "chặn lại 2";
				break;
		}
		CCLog("resson=%d, ressonString=%s", resson, ressonString.c_str());
		layerChats->showChatByPos(pos, ressonString);
    }
}

void LayerPlayGameTLMN::event_EXT_EVENT_VICTORY_NOTIF(){
//    var uid = params.uid;
//    var vicPos = params.vtps;
    
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    boost::shared_ptr<long> vicPos = param->GetInt("vtps");
    boost::shared_ptr<string> listCard = param->GetUtfString("lc");

    CCLog("event_EXT_EVENT_VICTORY_NOTIF");
    
    if (name != NULL && vicPos != NULL) {
        CCLog("name= %s, vicpos= %ld", name->c_str(), *vicPos.get());
        
        string result = "";
        switch (*vicPos.get()) {
            case 1:
                result = "Hết bài- Nhất!";

				if (name->c_str() == myName)
				{
					playSound("thang_roi.mp3");
				}

                break;
                
            case 2:
                result = "Hết bài- Về nhì!";
                break;
            
            case 3:
                result = "Hết bài- Về ba!";
                break; 
                
            case 4:
                result = "Hết bài- Bét!"; 
                break;
            default:
                break;
        }
        
        layerAvatars->setMoney(layerAvatars->getPosByName(name->c_str()), result);
    }

	if (listCard != NULL && name != NULL)
	{
		// hiển thị quân bài trên tay của người chơi cuối
		string lc = listCard->c_str();
		CCLog("lc= %s", lc.c_str());
		if (name->c_str() != myName)
			layerCards->showCardOnHandByPos_List(layerAvatars->getPosByName(name->c_str()), lc);
	}
}

void LayerPlayGameTLMN::event_EXT_EVENT_NEAD_PLAY_NOTIF(){
    // Lượt chơi
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    boost::shared_ptr<long> isfr = param->GetInt("isfr");
    
    CCLog("event_EXT_EVENT_NEAD_PLAY_NOTIF");
    
    if (name != NULL && isfr != NULL) {
        CCLog("name= %s, isfr= %ld",  name->c_str(), *isfr.get());
        
        // timer
        layerAvatars->runTimer(layerAvatars->getPosByName(name->c_str()));
        
        if (name->c_str() == myName) {
            getButtonByTag(kTagButtonHit)->setEnabled(true);
            
            if (*isfr.get() == 0) {
                // duoc phep bo luot
                getButtonByTag(kTagButtonNextTurn)->setEnabled(true);
            }
            else {
                getButtonByTag(kTagButtonNextTurn)->setEnabled(false);
            }
        }
        else {
            getButtonByTag(kTagButtonHit)->setEnabled(false);
            getButtonByTag(kTagButtonNextTurn)->setEnabled(false);
        }
        
        // lượt mới: ẩn các quân đang có trên bàn và release mảng chứa
		isNewTurn = false;
        if (*isfr.get() == 1) {
			isNewTurn = true;
            for (int i = 0; i < arrIDTurn.size(); i++) {
                int id = arrIDTurn[i];
                layerCards->getCardByID(id)->setVisible(false);
            }
            
            doTogether->releaseVector(arrIDTurn);
        }
    }
}

void LayerPlayGameTLMN::event_EXT_EVENT_PLAY_CARD_NOTIF(){
    // Danh sach quan bai danh ra
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    boost::shared_ptr<string> listCard = param->GetUtfString("lc");
    boost::shared_ptr<long> countCard = param->GetInt("cc");
    
    CCLog("event_EXT_EVENT_PLAY_CARD_NOTIF");
    
    if (name != NULL && listCard != NULL && countCard != NULL) {
        CCLog("name= %s, listCard= %s, countCard= %ld", name->c_str(), listCard->c_str(), *countCard.get());
        
        int pos = layerAvatars->getPosByName(name->c_str());
        
        // cap nhat so bai tren tay
        layerCards->setCountCardByPos(pos, *countCard.get());
        
        vector<int> arrID = layerCards->getIDFromString_TienLen(listCard->c_str());
        layerCards->actionHitCardByTienLen(pos, arrID);
        
        // mỗi khi có danh sách các quân bài đánh ra
        // đều đẩy ID vào mảng lưu trữ tạm thời (để dễ xử lý về sau)
        for (int i = 0; i < arrID.size(); i++) {
            arrIDTurn.push_back(arrID[i]);
        }
    }

	// am thanh
	if (isNewTurn) {
		vector<string> arr;
		arr.push_back("danh_di.mp3");
		arr.push_back("thach_danh.mp3");
		int index = rand() % arr.size();
		playSound(arr.at(index));
		arr.clear();
	} else {
		vector<string> arr;
		arr.push_back("chay_dang_troi.mp3");
		arr.push_back("chay_di_dau.mp3");
		arr.push_back("chay_di_dau_2.mp3");
		arr.push_back("con_nua_ne.mp3");
		int index = rand() % arr.size();
		playSound(arr.at(index));
		arr.clear();
	}
}

void LayerPlayGameTLMN::event_EXT_EVENT_GAME_CHANGE_NOTIF(){
    // khi trở lại bàn chơi
    //1000|thanhhv4|1||25_thanhhv4_1_42, 53, 36, 17, 31, 29, 44, 16, 45, 62, 50, 30, 48;22_thanhhv5_0_-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    boost::shared_ptr<string> ginf = param->GetUtfString("ginf");
    
    CCLog("event_EXT_EVENT_GAME_CHANGE_NOTIF");
    if (ginf != NULL) {
        CCLog("%s", ginf->c_str());
        // neu da nhay vao day
		layerChats->showChatByPos(-1, "Dựng lại bàn chơi đã lưu");
        getButtonByTag(kTagButtonReady)->setEnabled(false);
        getButtonByTag(kTagButtonSort)->setEnabled(true);
        
        // bất chấp "bỏ lượt" :D
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_PASS_CARD_REQ), params, lastRoom));
        
        GameServer::getSingleton().getSmartFox()->Send(request);
        //
        
        string list = ginf->c_str();
        vector<string> arrList = layerCards->split(list, '|');
        //doTogether->split(list, '|');
        //
        
        if (arrList.size() >= 5) {
            string tienCuoc = arrList[0];
            string tenUserToiLuot = arrList[1];
            string isfr = arrList[2];
            string listUser_Card = arrList[4];
            
            vector<string> arrInfo =layerCards->split(listUser_Card, ';');
            //doTogether->split(listUser_Card, ';');
            //
            for (int i = 0; i < arrInfo.size(); i++) {
                vector<string> arr = layerCards->split(arrInfo[i], '_');
                //doTogether->split(arrInfo[i], '_');
                //
                
                if (arr.size() < 3) break;
                
                string name = arr[1];
                string flag = arr[2];
                string listID = arr[3];
                
                // chu phong
                layerAvatars->setFlag(layerAvatars->getPosByName(name), (atoi(flag.c_str()) == 1));
                
                // chia bai cho minh
                if (name == myName){
                    layerCards->actionDealCard(layerCards->getIDFromString_TienLen(listID));
                    if (tenUserToiLuot == myName) {
                        getButtonByTag(kTagButtonHit)->setEnabled(true);
                        if (atoi(isfr.c_str()) == 0) {
                            // dc phep bo luot
                            getButtonByTag(kTagButtonNextTurn)->setEnabled(true);
                        }
                    }
                }
            }
        }
        
    }
}

void LayerPlayGameTLMN::event_EXT_EVENT_PASS_CARD_NOTIF(){
    boost::shared_ptr<string> name = param->GetUtfString("uid");
    
    CCLog("event_EXT_EVENT_PASS_CARD_NOTIF");
    if (name != NULL) {
        CCLog("%s", name->c_str());
        
        layerChats->showChatByPos(layerAvatars->getPosByName(name->c_str()), "Bỏ lượt!");

		vector<string> arr;
		arr.push_back("em_tha_do.mp3");
		int index = rand() % arr.size();
		playSound(arr.at(index));
		arr.clear();
    }
}

void LayerPlayGameTLMN::event_EXT_EVENT_PLAY_CARD_RES(){
    boost::shared_ptr<long> rs = param->GetInt("rslt");
    
    CCLog("event_EXT_EVENT_PLAY_CARD_RES");
    if (rs != NULL) {
        CCLog("%ld", *rs.get());
        if (*rs.get() != 0) {
            layerChats->showChatByPos(-1, "Bài đánh không hợp lệ");
        }
    }
}













