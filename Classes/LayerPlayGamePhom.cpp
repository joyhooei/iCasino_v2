//
//  LayerPlayGamePhom.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/14/14.
//
//

#include "LayerPlayGamePhom.h"
#include "SceneManager.h"
#include "mUtils.h"

enum EXT_RESPONSE {
    //
    EXT_SRVNTF_PUBLIC_MESSAGE = 0,
    EXT_SRVNTF_PRIVATE_MESSAGE,
    EXT_SRVNTF_GAME_MASTER_INFO,
    EXT_SRVNTF_READY,
    EXT_SRVNTF_PLAYER_LIST,
    EXT_SRVNTF_RECOMMENDED_CARDSETS,
    EXT_EVENT_START,
    EXT_EVENT_END,
    EXT_EVENT_GAME_RESULT,
    EXT_EVENT_LISTCARD_NTF,
    EXT_EVENT_COIN_NTF,
    EXT_SRVNTF_CURRENT_PLAYING_USER,
    EXT_SRVNTF_END_PLAYING_GAME,
    EXT_SRVNTF_GAME_INFO,
    EXT_EVENT_READY_RES,
    EXT_EVENT_READY_REQ,
    EXT_SRVNTF_USER_READY,
    EXT_SRVNTF_CARD_ORIGINATION,
    EXT_EVENT_RES_DRAW_CARD,
    EXT_EVENT_RES_TAKE_CARD,
    EXT_EVENT_RES_DISCARD,
    EXT_EVENT_RES_HANDOFF_PHOM,
    EXT_EVENT_RES_END_PLAYING,
    EXT_EVENT_RES_SET_BET,
    EXT_EVENT_RES_U,
    EXT_SRVNTF_CAN_TAKE,
    EXT_SRVNTF_PLAYER_REPLAY,
    EXT_SRVNTF_U_9,
    EXT_SRVNTF_COIN_CHANGE,
    EXT_EVENT_RES_ORDER_CARDS,
    //
    EXT_EVENT_REQ_JOIN_GAME,
    EXT_EVENT_REQ_ORDER_CARDS,
    EXT_EVENT_REQ_DRAW_CARD,
    EXT_EVENT_REQ_DISCARD,
    EXT_EVENT_REQ_TAKE_CARD,
    EXT_EVENT_REQ_HANDOFF_PHOM,
    EXT_EVENT_REQ_PUSH_CARD,
    EXT_EVENT_REQ_U,
    //
    CARD_ORIGINATION_BY_TAKEN = 1, // ăn được
	CARD_ORIGINATION_BY_DRAWN = 2, // bốc từ nọc
	CARD_ORIGINATION_BY_TRANSFERED = 3, // quân bài chuyển
	CARD_ORIGINATION_BY_DEALT = 4, // chia bài
	CARD_ORIGINATION_BY_HANDOFF = 5, // chia bài
	CARD_ORIGINATION_BY_PUSHED = 6, // chia bài
	CARD_ORIGINATION_BY_UNKOWN = 7, // chia bài
};

int LayerPlayGamePhom::convertResponseToInt(string inString) {
    if (inString == "ntfpubmsg") return  EXT_SRVNTF_PUBLIC_MESSAGE;
    if (inString == "ntfprvmsg") return  EXT_SRVNTF_PRIVATE_MESSAGE;
    if (inString == "ntfgminfo") return  EXT_SRVNTF_GAME_MASTER_INFO;
    if (inString == "rsr") return  EXT_SRVNTF_READY;
    if (inString == "ntfpllst") return  EXT_SRVNTF_PLAYER_LIST;
    if (inString == "ntfrcrds") return  EXT_SRVNTF_RECOMMENDED_CARDSETS;
    if (inString == "s") return  EXT_EVENT_START;
    if (inString == "e") return  EXT_EVENT_END;
    if (inString == "grs") return  EXT_EVENT_GAME_RESULT;
    if (inString == "lcntf") return  EXT_EVENT_LISTCARD_NTF;
    if (inString == "ntfcoinch") return  EXT_EVENT_COIN_NTF;
    if (inString == "ntfcurpu") return  EXT_SRVNTF_CURRENT_PLAYING_USER;
    if (inString == "ntfepla") return  EXT_SRVNTF_END_PLAYING_GAME;
    if (inString == "ntfginfo") return  EXT_SRVNTF_GAME_INFO;
    if (inString == "rr") return EXT_EVENT_READY_REQ;
    if (inString == "rdres") return  EXT_EVENT_READY_RES;
    if (inString == "ntfurd") return  EXT_SRVNTF_USER_READY;
    if (inString == "ntfcorg") return  EXT_SRVNTF_CARD_ORIGINATION;
    if (inString == "rsdrwc") return  EXT_EVENT_RES_DRAW_CARD;
    if (inString == "rstkc") return  EXT_EVENT_RES_TAKE_CARD;
    if (inString == "rshofc") return  EXT_EVENT_RES_DISCARD;
    if (inString == "rshofp") return  EXT_EVENT_RES_HANDOFF_PHOM;
    if (inString == "rsenpl") return  EXT_EVENT_RES_END_PLAYING;
    if (inString == "rssbet") return  EXT_EVENT_RES_SET_BET;
    if (inString == "rsU") return  EXT_EVENT_RES_U;
    if (inString == "ntfcantk") return  EXT_SRVNTF_CAN_TAKE;
    if (inString == "ntfrpl") return  EXT_SRVNTF_PLAYER_REPLAY;
    if (inString == "ntfu9") return  EXT_SRVNTF_U_9;
    if (inString == "rsodrc") return  EXT_EVENT_RES_ORDER_CARDS;
    //
    if (inString == "rqjg") return EXT_EVENT_REQ_JOIN_GAME;
    if (inString == "rodrc") return EXT_EVENT_REQ_ORDER_CARDS;
    if (inString == "rqdrwc") return EXT_EVENT_REQ_DRAW_CARD;
    if (inString == "rqhofc") return EXT_EVENT_REQ_DISCARD;
    if (inString == "rqtkc") return EXT_EVENT_REQ_TAKE_CARD;
    if (inString == "rqhofp") return EXT_EVENT_REQ_HANDOFF_PHOM;
    if (inString == "rqpusc") return EXT_EVENT_REQ_PUSH_CARD;
    if (inString == "rqU") return EXT_EVENT_REQ_U;
    
    return -1;
}

string LayerPlayGamePhom::convertResponseToString(int inInt) {
    if (inInt == EXT_SRVNTF_PUBLIC_MESSAGE) return "ntfpubmsg";
    if (inInt == EXT_SRVNTF_PRIVATE_MESSAGE) return "ntfprvmsg";
    if (inInt == EXT_SRVNTF_GAME_MASTER_INFO) return "ntfgminfo";
    if (inInt == EXT_SRVNTF_READY) return  "rsr";
    if (inInt == EXT_SRVNTF_PLAYER_LIST) return  "ntfpllst";
    if (inInt == EXT_SRVNTF_RECOMMENDED_CARDSETS) return  "ntfrcrds";
    if (inInt == EXT_EVENT_START) return  "s";
    if (inInt == EXT_EVENT_END) return  "e";
    if (inInt == EXT_EVENT_GAME_RESULT) return  "grs";
    if (inInt == EXT_EVENT_LISTCARD_NTF) return  "lcntf";
    if (inInt == EXT_EVENT_COIN_NTF) return  "ntfcoinch";
    if (inInt == EXT_SRVNTF_CURRENT_PLAYING_USER) return  "ntfcurpu";
    if (inInt == EXT_SRVNTF_END_PLAYING_GAME) return  "ntfepla";
    if (inInt == EXT_SRVNTF_GAME_INFO) return  "ntfginfo";
    if (inInt == EXT_EVENT_READY_REQ) return "rr";
    if (inInt == EXT_EVENT_READY_RES) return  "rdres";
    if (inInt == EXT_SRVNTF_USER_READY) return  "ntfurd";
    if (inInt == EXT_SRVNTF_CARD_ORIGINATION) return  "ntfcorg";
    if (inInt == EXT_EVENT_RES_DRAW_CARD) return  "rsdrwc";
    if (inInt == EXT_EVENT_RES_TAKE_CARD) return  "rstkc";
    if (inInt == EXT_EVENT_RES_DISCARD) return  "rshofc";
    if (inInt == EXT_EVENT_RES_HANDOFF_PHOM) return  "rshofp";
    if (inInt == EXT_EVENT_RES_END_PLAYING) return  "rsenpl";
    if (inInt == EXT_EVENT_RES_SET_BET) return  "rssbet";
    if (inInt == EXT_EVENT_RES_U) return  "rsU";
    if (inInt == EXT_SRVNTF_CAN_TAKE) return  "ntfcantk";
    if (inInt == EXT_SRVNTF_PLAYER_REPLAY) return  "ntfrpl";
    if (inInt == EXT_SRVNTF_U_9) return  "ntfu9";
    if (inInt == EXT_EVENT_RES_ORDER_CARDS) return  "rsodrc";
    //
    if (inInt == EXT_EVENT_REQ_JOIN_GAME) return  "rqjg";
    if (inInt == EXT_EVENT_REQ_ORDER_CARDS) return "rodrc";
    if (inInt == EXT_EVENT_REQ_DRAW_CARD) return "rqdrwc";
    if (inInt == EXT_EVENT_REQ_DISCARD) return "rqhofc";
    if (inInt == EXT_EVENT_REQ_TAKE_CARD) return "rqtkc";
    if (inInt == EXT_EVENT_REQ_HANDOFF_PHOM) return "rqhofp";
    if (inInt == EXT_EVENT_REQ_PUSH_CARD) return "rqpusc";
    if (inInt == EXT_EVENT_REQ_U) return "rqU";
    
    return "";
}

LayerPlayGamePhom::LayerPlayGamePhom() {
    
    this->myName = SceneManager::getSingleton().getMyName();
    
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(-WIDTH_DESIGN / 2, -HEIGHT_DESIGN / 2));
    this->setTouchEnabled(false);
    
    //
    this->levelGame = 0;
	this->actionLast = 0;
    
    //
    createBackgrounds();
    createAvatars();
    createButtons();
    createCards();
    createNumbers();
    createChats();
    
    GameServer::getSingleton().addListeners(this);
    //
    this->scheduleOnce(schedule_selector(LayerPlayGamePhom::sendRequestJoinGame), 1.0f);
	SceneManager::getSingleton().hideLoading();
}

LayerPlayGamePhom::~LayerPlayGamePhom() {
	CCLOG("~~~~LayerPlayGamePhom");
}

void LayerPlayGamePhom::onExit() {
	CCLOG("onExit: clean LayerPlayGamePhom");

	GameServer::getSingleton().removeListeners(this);

	arrName.clear();
	arrMoney.clear();

	//layerAvatars->removeFromParentAndCleanup(true);
	/*
	if (layerAvatars)
	{
		layerAvatars->release();
		layerAvatars=NULL;
	}
	if (layerCards)
	{
		layerCards->release();
		layerCards=NULL;
	}
	if (layerButtons)
	{
		layerButtons->release();
		layerButtons=NULL;
	}
	if (layerNumbers)
	{
		layerNumbers->release();
		layerNumbers=NULL;
	}
	if (layerChats)
	{
		layerChats->release();
		layerChats=NULL;
	}
	*/
}

void LayerPlayGamePhom::createBackgrounds() {
    BackgroundInGame *bg = BackgroundInGame::create();
    this->addChild(bg);

	// thông tin bàn chơi và mức cược
	int id = atoi(GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GroupId()->c_str());
	boost::shared_ptr<string> param = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetVariable("params")->GetStringValue();
	string paramString = param->c_str();
	vector<string> arrInfo = split(paramString, '@');
	string money = arrInfo.at(0);

	mUtils mu;
	//string name = mu.getGameNameByID(id);
	string name = "Phỏm";
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

void LayerPlayGamePhom::createAvatars() {
    layerAvatars = LayerAvatarInGame::create();
    this->addChild(layerAvatars);
}

void LayerPlayGamePhom::createButtons() {
    layerButtons = LayerButtonInGame::create();
    this->addChild(layerButtons);
    
    int widButton = 129;
    int heiButton = 44;
    int space = 10;
    
    // Chia bài
    Button *btnReady = createButtonWithTitle_Position("Sẵn sàng", ccp(WIDTH_DESIGN - space, space));
    Button *btnSortCard = createButtonWithTitle_Position("Xếp", ccp(WIDTH_DESIGN - space, space));
    Button *btnHitCard = createButtonWithTitle_Position("Đánh", ccp(WIDTH_DESIGN - space * 2 - widButton, space));
    Button *btnGiveCard = createButtonWithTitle_Position("Bốc", ccp(WIDTH_DESIGN - space, space * 2 + heiButton));
    Button *btnEatCard = createButtonWithTitle_Position("Ăn", ccp(WIDTH_DESIGN - space * 3 - widButton * 2, space));
    Button *btnPush = createButtonWithTitle_Position("Gửi", ccp(WIDTH_DESIGN - space * 3 - widButton * 2, space));
    Button *btnHaPhom = createButtonWithTitle_Position("Hạ", ccp(WIDTH_DESIGN - space , space * 2 + heiButton));
    Button *btnUUU = createButtonWithTitle_Position("Ù", ccp(WIDTH_DESIGN - space * 4 - widButton * 3, space));
    
    btnReady->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionReady));
    btnSortCard->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionSortCards));
    btnHitCard->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionHitCards));
    btnGiveCard->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionGiveCards));
    btnEatCard->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionEatCards));
    btnHaPhom->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionHaPhom));
    btnPush->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionPush));
    btnUUU->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionUUU));
    
    btnReady->setTag(kTagButtonReady);
    btnSortCard->setTag(kTagButtonSort);
    btnHitCard->setTag(kTagButtonHit);
    btnGiveCard->setTag(kTagButtonGive);
    btnEatCard->setTag(kTagButtonEat);
    btnHaPhom->setTag(kTagButtonHaPhom);
    btnPush->setTag(kTagButtonPush);
    btnUUU->setTag(kTagButtonU);
    
    btnSortCard->setEnabled(false);
    btnHitCard->setEnabled(false);
    btnGiveCard->setEnabled(false);
    btnEatCard->setEnabled(false);
    btnHaPhom->setEnabled(false);
    btnPush->setEnabled(false);
    btnUUU->setEnabled(false);
    
    layerButtons->addWidget(btnSortCard);
    layerButtons->addWidget(btnHitCard);
    layerButtons->addWidget(btnGiveCard);
    layerButtons->addWidget(btnEatCard);
    layerButtons->addWidget(btnHaPhom);
    layerButtons->addWidget(btnPush);
    layerButtons->addWidget(btnUUU);
    layerButtons->addWidget(btnReady);
}

void LayerPlayGamePhom::createNumbers() {
    layerNumbers = LayerNumberInGame::create();
    this->addChild(layerNumbers);
    
//    vector<string> data;
//    data.push_back("1111324");
//    data.push_back("22256");
//    data.push_back("333");
//    data.push_back("44413434344");
//    data.push_back("55500000004");
//    data.push_back("666104");
//    data.push_back("777");
//    for (int i = 0; i < data.size(); i++) {
//        layerNumbers->showNumberByPos(kUserMe, data[i]);
//    }
}

void LayerPlayGamePhom::createCards() {
    layerCards = LayerCardInGame::create();
    layerCards->initCardByPhom();
    this->addChild(layerCards);
}

void LayerPlayGamePhom::createChats() {
    layerChats = LayerChatInGame::create();
    this->addChild(layerChats);
}

void LayerPlayGamePhom::initGame() {
    // khởi tạo các giá trị ban đầu hoặc hiển thị các thông tin cần thiết
	this->actionLast = 0;
    
    // thông tin tiền hiện tại của Users
    for (int i = 0; i < arrName.size(); i++) {
        layerAvatars->setMoney(layerAvatars->getPosByName(arrName[i]), arrMoney[i]);
    }
    arrName.clear();
	arrMoney.clear();

    // unready all
    layerAvatars->setUnReadyAllUser();
}

void LayerPlayGamePhom::resetGame() {
	initGame();

    layerCards->resetGame();
    layerAvatars->resetGame();
    
    getButtonByTag(kTagButtonReady)->setEnabled(false);
    getButtonByTag(kTagButtonSort)->setEnabled(false);
    
    this->currentPlaying = "";
}

void LayerPlayGameTLMN::playeSound( string soundPath )
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundPath.c_str());
}

Button* LayerPlayGamePhom::createButtonWithTitle_Position(const char *title, CCPoint pPoint) {
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

Button* LayerPlayGamePhom::getButtonByTag(int tag) {
    Button *button = (Button*) this->layerButtons->getWidgetByTag(tag);
    return button;
}

void LayerPlayGamePhom::actionReady(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        CCLOG("clicked ready!");
        layerCards->resetGame();
        
        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_READY_REQ), parameter, lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
        
//        vector<string> arr;
//        arr.push_back("helo");
//        arr.push_back(":D");
//        arr.push_back("Xin chao!!!! Nuoc cong hoa xa hoi Viet Nam, Doc lap tu do hanh phuc.......... HI!");
//        arr.push_back("Xin chờ người chơi khác");
//        arr.push_back("Bỏ lượt");
//        arr.push_back("Quân bài không hợp lệ");
//        // test
//        int rd = rand() % 4 - 1;
//        //layerChats->showChatByPos(rd, arr[rand() % arr.size()]);
//        
//        Chat *toast = new Chat("Chờ người chơi khác", -1);
//        layerChats->addChild(toast);
        
    }
}

void LayerPlayGamePhom::actionSortCards(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        CCLOG("sort!");
        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_ORDER_CARDS), parameter, lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
        
        layerCards->setAllowSortCard(true);
    }
}

void LayerPlayGamePhom::actionHitCards(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        
        vector<int> arrID = layerCards->getIdCardByClicked();
        unsigned int length = arrID.size();

        if (length != 1) {
            layerChats->showChatByPos(-1, "Hãy chọn 1 quân bài để đánh");
        }
		else {
            boost::shared_ptr<ISFSObject> params (new SFSObject());
            params->PutByte("cardidx", arrID[0]);
            boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
            boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_DISCARD), params, lastRoom));
            
            GameServer::getSingleton().getSmartFox()->Send(request);
        }
        
    }
}

void LayerPlayGamePhom::actionGiveCards(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_DRAW_CARD), params, lastRoom));
        
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}

void LayerPlayGamePhom::actionEatCards(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        params->PutByte("cardidx", layerCards->getIdCardCanEat());
        boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_TAKE_CARD), params, lastRoom));
        
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}

void LayerPlayGamePhom::actionHaPhom(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
       
		// Phòng trường hợp "xấu" nhất, ta cứ gửi các quân bài đang được chọn
		// rồi sau đó mới gừi các quân được xếp bởi sv
		vector<int> arrID = layerCards->getIdCardByClicked();
		string listID;
		int length = arrID.size();
		if (length < 3)
		{
			return;
		}
		for (int i = 0; i < length; i++) {
			listID += boost::to_string(arrID[i]);
			if (i != length - 1) listID += ":";
		}

		CCLog("callbackHaPhom listID= %s", listID.c_str());
		boost::shared_ptr<ISFSObject> params (new SFSObject());
		params->PutUtfString("lc", listID);
		boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_HANDOFF_PHOM), params, lastRoom));

		GameServer::getSingleton().getSmartFox()->Send(request);

		// recomment by Sver
		this->scheduleOnce(schedule_selector(LayerPlayGamePhom::callbackHaPhom), 0.3);
    }
}

void LayerPlayGamePhom::callbackHaPhom(float dt) {
	vector<string> arrListID = layerCards->getID_HaPhom();

	for (int i = 0; i < arrListID.size(); i++) {
		string listID = arrListID[i];

		boost::shared_ptr<ISFSObject> params (new SFSObject());
		params->PutUtfString("lc", listID);

		boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
		boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_HANDOFF_PHOM), params, lastRoom));

		GameServer::getSingleton().getSmartFox()->Send(request);
	}
}

void LayerPlayGamePhom::actionPush(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN) {
        vector<int> arrID = layerCards->getIdCardByClicked();
        unsigned int length = arrID.size();
        
        if (length != 1) {
            layerChats->showChatByPos(-1, "Hãy chọn 1 quân bài để gửi");
        }
        if (length == 1) {
            CCLOG("Danh quan gui co id = %d", arrID[0]);
            
            boost::shared_ptr<ISFSObject> params (new SFSObject());
            params->PutByte("cardidx", arrID[0]);
            boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
            boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_PUSH_CARD), params, lastRoom));
            
            GameServer::getSingleton().getSmartFox()->Send(request);
        }
    }
}

void LayerPlayGamePhom::actionUUU(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN) {
        CCLog("UU");
        
        boost::shared_ptr<ISFSObject> params (new SFSObject());
        boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_U), params, lastRoom));
        
        GameServer::getSingleton().getSmartFox()->Send(request);
    }
}

void LayerPlayGamePhom::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    this->param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    
    if(strcmp("hbc", cmd->c_str())==0){
        return;
    }
    
    switch(convertResponseToInt(cmd->c_str())) {
            
        case EXT_SRVNTF_PUBLIC_MESSAGE:
            this->event_EXT_SRVNTF_PUBLIC_MESSAGE();
            break;
            
        case EXT_SRVNTF_PRIVATE_MESSAGE:
            this->event_EXT_SRVNTF_PRIVATE_MESSAGE();
            break;
            
        case EXT_SRVNTF_GAME_MASTER_INFO:
            this->event_EXT_SRVNTF_GAME_MASTER_INFO();
            break;
            
        case EXT_SRVNTF_READY:
            this->event_EXT_SRVNTF_READY();
            break;
            
        case EXT_EVENT_READY_RES:
            this->event_EXT_EVENT_READY_RES();
            break;
            
        case EXT_SRVNTF_PLAYER_LIST:
            this->event_EXT_SRVNTF_PLAYER_LIST();
            break;
            
        case EXT_SRVNTF_RECOMMENDED_CARDSETS:
            this->event_EXT_SRVNTF_RECOMMENDED_CARDSETS();
            break;
            
        case EXT_EVENT_START:
            this->event_EXT_EVENT_START();
            break;
            
        case EXT_EVENT_END:
            this->event_EXT_EVENT_END();
            break;
            
        case EXT_EVENT_GAME_RESULT:
            this->event_EXT_EVENT_GAME_RESULT();
            break;
            
        case EXT_EVENT_LISTCARD_NTF:
            this->event_EXT_EVENT_LISTCARD_NTF();
            break;
            
        case EXT_EVENT_COIN_NTF: // bản tin cộng, trừ tiền
            this->event_EXT_EVENT_COIN_NTF();
            break;
            
        case EXT_SRVNTF_CURRENT_PLAYING_USER:
            this->event_EXT_SRVNTF_CURRENT_PLAYING_USER();
            break;
            
        case EXT_SRVNTF_END_PLAYING_GAME:
            this->event_EXT_SRVNTF_END_PLAYING_GAME();
            break;
            
        case EXT_SRVNTF_GAME_INFO:
            this->event_EXT_SRVNTF_GAME_INFO();
            break;
            
        case EXT_SRVNTF_USER_READY:
            event_EXT_SRVNTF_USER_READY();
            break;
         
        // tung quan bai
        case EXT_SRVNTF_CARD_ORIGINATION:
            this->event_EXT_SRVNTF_CARD_ORIGINATION();
            break;
            
			//List event response message
        case EXT_EVENT_RES_DRAW_CARD:
            this->event_EXT_EVENT_RES_DRAW_CARD();
            break;
            
        case EXT_EVENT_RES_TAKE_CARD:
            this->event_EXT_EVENT_RES_TAKE_CARD();
            break;
            
        case EXT_EVENT_RES_DISCARD:
            this->event_EXT_EVENT_RES_DISCARD();
            break;
            
        case EXT_EVENT_RES_HANDOFF_PHOM:
            this->event_EXT_EVENT_RES_HANDOFF_PHOM();
            break;
            
        case EXT_EVENT_RES_END_PLAYING:
            this->event_EXT_EVENT_RES_END_PLAYING();
            break;
            
        case EXT_EVENT_RES_SET_BET:
            this->event_EXT_EVENT_RES_SET_BET();
            break;
            
        case EXT_EVENT_RES_U:
            this->event_EXT_EVENT_RES_U();
            break;
//
//        case  EXT_EVENT_RES_PUSH_CARD:
////            var rscode = params.rscode;
////            if (rscode != 0) {
////                 g_mLog.addLog( LOG_ERROR, "cmd = EXT_EVENT_RES_PUSH_CARD ERROR rscode:" + rscode);
////            }
//            break;
        case EXT_SRVNTF_CAN_TAKE:
            this->event_EXT_SRVNTF_CAN_TAKE();
            break;
            
        case  EXT_SRVNTF_PLAYER_REPLAY:
            this->event_EXT_SRVNTF_PLAYER_REPLAY();
            break;
            
        case  EXT_SRVNTF_U_9:
            this->event_EXT_SRVNTF_U_9();
            break;
            
        default:
            CCLog("LOG_ERROR %s", cmd->c_str());
            break;
    }
}

void LayerPlayGamePhom::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
    
    
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
    boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
    
    int    money = (int) (*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
	string name = boost::to_string(*ptrNotifiedUser->Name());
	
	CCLOG("Update User Variables size of arrName=%d", arrName.size());
    CCLOG("name=%s, money=%d", name.c_str(), money);
   
	if (arrName.size() > 4) {
		//arrName.clear();
		//arrMoney.clear();
	}
    arrName.push_back(name);
    arrMoney.push_back(money);
}

void LayerPlayGamePhom::sendRequestJoinGame(float dt) {
    // join game
    boost::shared_ptr<ISFSObject> params (new SFSObject());
    boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
    boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_JOIN_GAME), params, lastRoom));
    
    GameServer::getSingleton().getSmartFox()->Send(request);
}

vector<string> LayerPlayGamePhom::split(string &S, const char &str) {
    vector<string> arrStr;
    string::iterator t, t2;
    
    for (t = S.begin(); t < S.end(); ){
        // Lặp từ vị trí bắt đầu
        t2 = find(t, S.end(), str);
        
        //kể từ vị trí t
        if(t != t2){
            arrStr.push_back(string(t, t2));
        }
        else if(t2 != S.end()) arrStr.push_back("");

		if (t2 == S.end())
		{
			break;
		}

        t = t2 + 1;
    }
    
    return arrStr;
}

void LayerPlayGamePhom::event_EXT_SRVNTF_PUBLIC_MESSAGE(){
    
}

void LayerPlayGamePhom::event_EXT_SRVNTF_PRIVATE_MESSAGE() {
    
}

void LayerPlayGamePhom::event_EXT_SRVNTF_GAME_MASTER_INFO() {
    boost::shared_ptr<long> rscode = param->GetInt("rscode");
    
    if (rscode != NULL) {
		int codeInt = (int) *rscode;
        if (codeInt != 0) {
            layerChats->showChatByPos(-1, "Đợi chờ là hạnh phúc :P");
        }
    }
    
}

void LayerPlayGamePhom::event_EXT_SRVNTF_READY() {
    
}

void LayerPlayGamePhom::event_EXT_EVENT_READY_RES() {
 
}

void LayerPlayGamePhom::event_EXT_SRVNTF_PLAYER_LIST() {
    boost::shared_ptr<string> list = param->GetUtfString("lu");
    CCLog("EXT_SRVNTF_PLAYER_LIST = %s", list->c_str());
    
	if (list != NULL)
	{
		layerChats->showChatByPos(-1, "Cập nhật người chơi");
		layerAvatars->setListUserByPhom(list->c_str());
		//layerCards->resetGame();
		//this->resetGame();
		//this->initGame();

		if (levelGame == 0) {
			// ban dau thi hien luon
			// thông tin tiền hiện tại của Users
			for (int i = 0; i < arrName.size(); i++) {
				int pos = layerAvatars->getPosByName(arrName[i]);
				if (pos > -1){
					layerAvatars->setMoney(pos, arrMoney[i]);
				}
			}

			arrName.clear();
			arrMoney.clear();
		}
	}
    
}

void LayerPlayGamePhom::event_EXT_SRVNTF_RECOMMENDED_CARDSETS() {
    // Danh sách gợi ý các quân bài hạ phỏm dành riêng cho mình
    // chỉ nhảy vào đây khi trên tay có phỏm
    // ẩn các nút cho tới khi các quân bài được xếp gợi ý
    getButtonByTag(kTagButtonSort)->setEnabled(false);
    getButtonByTag(kTagButtonHit)->setEnabled(false);
//    btnHaPhom->setEnabled(true);
//    btnPush->setEnabled(true);
    
    boost::shared_ptr<string> listcard = param->GetUtfString("crdss");
    CCLog("EXT_SRVNTF_RECOMMENDED_CARDSETS listcard= %s", listcard->c_str());
    
	layerChats->showChatByPos(-1, "Hãy hạ phỏm trước khi đánh!");
    layerCards->event_EXT_SRVNTF_RECOMMENDED_CARDSETS(listcard->c_str());
}

void LayerPlayGamePhom::event_EXT_EVENT_START() {
    CCLog("EXT_EVENT_START");
    
    this->resetGame();
    this->initGame();
}

void LayerPlayGamePhom::event_EXT_EVENT_END() {
    CCLog("EXT_EVENT_END");
    
    levelGame++;
    
    layerCards->setGameStarted(false);
	layerCards->showCardOnHandAll();
    
    getButtonByTag(kTagButtonSort)->setEnabled(false);
    getButtonByTag(kTagButtonHit)->setEnabled(false);
    getButtonByTag(kTagButtonGive)->setEnabled(false);
    getButtonByTag(kTagButtonEat)->setEnabled(false);
    getButtonByTag(kTagButtonHaPhom)->setEnabled(false);
    getButtonByTag(kTagButtonPush)->setEnabled(false);
    getButtonByTag(kTagButtonU)->setEnabled(false);
    
    
    getButtonByTag(kTagButtonReady)->setTitleText("Sẵn sàng");
    getButtonByTag(kTagButtonReady)->setEnabled(true);
    
    layerAvatars->stopAllTimer();

}

void LayerPlayGamePhom::event_EXT_EVENT_GAME_RESULT() {
    boost::shared_ptr<string> resultGame = param->GetUtfString("rg");
    
    //0:28:4:1000:1401329992510:thanhhv4;1:36:5:-1000:1401330005039:thanhhv2;
    CCLog("EXT_EVENT_GAME_RESULT rg= %s.", resultGame->c_str());
    
    if (resultGame == NULL) {
        return;
    }
    
    string rg = resultGame->c_str();
    
    // tam thoi chi hien thi diem ở ô tiền
    vector<string> listString = split(rg, ';');
    for (int i = 0; i < listString.size(); i++) {
        if (listString[i].length() < 5) {
            break;
        }
        
        vector<string> arrInfo = split(listString[i], ':');
        int size = arrInfo.size();
        
        if (size >= 6){
            int score = atoi(arrInfo[1].c_str());
			int xepHang = atoi(arrInfo[2].c_str());
            string name = arrInfo[5];
            int pos = this->layerAvatars->getPosByName(name);
            
            ostringstream oss;
            oss<<score;
            string scoreString = oss.str() + " điểm - ";
            if (score < 0) scoreString = "";
            
			switch (xepHang) {
			case 0:
				scoreString += "Ù 0 điểm!";
				break;
			case 1:
				scoreString += "Ù tròn 10 cây!";
				break;
			case 2:
				scoreString += "Ù 9 cây!";
				break;
			case 3:
				scoreString += "Ù khan!";
				break;
			case 4:
				scoreString += "Nhất";
				break;
			case 5:
				scoreString += "Nhì";
				break;
			case 6:
				scoreString += "Ba";
				break;
			case 7:
				scoreString += "Bét";
				break;
			case 8:
				scoreString += "Cháy! - Thua";
				break;
			case 9:
				scoreString += "Ù đền!";
				break;
			default:
				scoreString += "Cháy! - Thắng";
				break;
			}

            this->layerAvatars->setMoney(pos, scoreString);
        }
    }
}

void LayerPlayGamePhom::event_EXT_EVENT_LISTCARD_NTF() {
    boost::shared_ptr<string> fname = param->GetUtfString("usrn");
    boost::shared_ptr<string> listString = param->GetUtfString("lc");
    
    CCLog("EXT_EVENT_LISTCARD_NTF name= %s, lc= %s", fname->c_str(), listString->c_str());
    layerCards->eventListcardNTF(layerAvatars->getPosByName(fname->c_str()), listString->c_str());
    
    //
    if (this->currentPlaying == myName) {
        // khi tới lượt mình thì có 2 trường hợp:
        //      1. Đánh (lượt đầu và đc đánh trước)
        //      2. Không đánh (bốc hoặc ăn rồi mới đánh)        
        if (layerCards->getCountCardOnHand() == 10) {
            getButtonByTag(kTagButtonHit)->setEnabled(true);
        }
        else if (this->actionLast != DANH_BAI){
            getButtonByTag(kTagButtonGive)->setEnabled(true);
        }
        
    }
}

void LayerPlayGamePhom::event_EXT_EVENT_COIN_NTF() {
    CCLog("EXT_EVENT_COIN_NTF");
    boost::shared_ptr<string> fname = param->GetUtfString("usrn");
    boost::shared_ptr<long> coin = param->GetInt("coinch");
	boost::shared_ptr<long> coinchr = param->GetInt("coinchr");
    
	if (fname == NULL || coin == NULL) {
		return;
	}

	if (coinchr != NULL)
	{
		CCLOG("coinchr= %ld", *coinchr);
		string ressonString = "";
		switch (*coinchr) {
			case 0:
				ressonString = "Bị ăn bài";
				break;
			case 1:
				ressonString = "Ăn bài";
				break;
			case 2:
				//ressonString = "Kết thúc";
				break;
			case 3:
				ressonString = "Ăn láo";
				break;
			case 4:
				ressonString = "Đền làng";
				break;
		}

		if (ressonString.length() > 0) {
			layerChats->showChatByPos(layerAvatars->getPosByName(fname->c_str()), ressonString);
		}
	}
    
    CCLog("name= %s, coin= %ld", fname->c_str(), *coin);
    
    layerNumbers->showNumberByPos(layerAvatars->getPosByName(fname->c_str()), boost::to_string(*coin));
}

void LayerPlayGamePhom::event_EXT_SRVNTF_CURRENT_PLAYING_USER() {
    boost::shared_ptr<string> fname = param->GetUtfString("usrn");
    CCLog("EXT_SRVNTF_CURRENT_PLAYING_USER name= %s", fname->c_str());
    
    layerAvatars->runTimer(layerAvatars->getPosByName(fname->c_str()));
    
    this->currentPlaying = fname->c_str();

    //
    if (this->currentPlaying == myName) {
        // khi tới lượt mình thì có 2 trường hợp:
        //      1. Đánh (lượt đầu và đc đánh trước)
        //      2. Không đánh (bốc hoặc ăn rồi mới đánh)
        CCLog("getCountCardOnHand = %d", layerCards->getCountCardOnHand());
        
        if (layerCards->getCountCardOnHand() == 10) {
            getButtonByTag(kTagButtonHit)->setEnabled(true);
        }
        else {
            getButtonByTag(kTagButtonGive)->setEnabled(true);
        }
    }
    else {
        getButtonByTag(kTagButtonU)->setEnabled(false);
    }
}

void LayerPlayGamePhom::event_EXT_SRVNTF_END_PLAYING_GAME() {
    boost::shared_ptr<string> fname = param->GetUtfString("usrn");
    if (fname == NULL) return;
    
    CCLog("EXT_SRVNTF_END_PLAYING_GAME name= %s", fname->c_str());
}

void LayerPlayGamePhom::event_EXT_SRVNTF_GAME_INFO() {
    
}

void LayerPlayGamePhom::event_EXT_SRVNTF_USER_READY() {
    boost::shared_ptr<string> fname = param->GetUtfString("usrn");
    
    if (fname != NULL) {
        CCLog("EXT_SRVNTF_USER_READY %s", fname->c_str());
        
        layerAvatars->setReady(layerAvatars->getPosByName(fname->c_str()), true);
        if (fname->c_str() == this->myName && strcmp("Sẵn sàng", getButtonByTag(kTagButtonReady)->getTitleText()) == 0) {
            getButtonByTag(kTagButtonReady)->setTitleText("Đã sẵn sàng");
			this->actionLast = SAN_SANG;
        }
    }
}

void LayerPlayGamePhom::event_EXT_SRVNTF_CARD_ORIGINATION() {
    boost::shared_ptr<unsigned char> fuid = param->GetByte("fuid");
    boost::shared_ptr<unsigned char> tuid = param->GetByte("tuid");
    boost::shared_ptr<string> fname = param->GetUtfString("funa");
    boost::shared_ptr<string> tname = param->GetUtfString("tuna");
    boost::shared_ptr<unsigned char> localChar = param->GetByte("crdorg");
    boost::shared_ptr<unsigned char> cardid = param->GetByte("cardidx");
    
    CCLOG("EXT_SRVNTF_CARD_ORIGINATION");
    if (fname == NULL || tname == NULL || localChar == NULL || cardid == NULL) return;
    
    switch(*localChar.get()) {
        case CARD_ORIGINATION_BY_TAKEN:
            break;
            
        case CARD_ORIGINATION_BY_DRAWN:
            // bốc bài
            layerCards -> actionGiveCard(layerAvatars->getPosByName(tname->c_str()), *(cardid.get()));
            break;
            
        case  CARD_ORIGINATION_BY_TRANSFERED:
            // chuyển bài
            layerCards -> actionTransferedCard(layerAvatars->getPosByName(fname->c_str()), layerAvatars->getPosByName(tname->c_str()), *(cardid.get()));
            
            break;
            
        case  CARD_ORIGINATION_BY_DEALT:
            break;
            
        case  CARD_ORIGINATION_BY_HANDOFF:
            CCLog("CARD_ORIGINATION_BY_HANDOFF %d.", *(tuid.get()));
            
            // tuid = -1
            if (*(tuid.get()) == 255){
                // đánh bài
                layerCards -> actionHitCard(layerAvatars->getPosByName(fname->c_str()), *(cardid.get()));
				if (fname->c_str() == myName)
					this->actionLast = DANH_BAI;
			}
            else{
                // ăn bài
                layerCards -> actionEatCard(layerAvatars->getPosByName(fname->c_str()), layerAvatars->getPosByName(tname->c_str()), *(cardid.get()));
				//this->actionLast = AN_BAI;
			}
            
            break;
            
        case  CARD_ORIGINATION_BY_UNKOWN:
            break;
            
        case  CARD_ORIGINATION_BY_PUSHED:
            // gửi bài
            layerCards -> actionPushCard(layerAvatars->getPosByName(fname->c_str()), layerAvatars->getPosByName(tname->c_str()), *(cardid.get()));
            
            break;
            
    }
}

void LayerPlayGamePhom::event_EXT_EVENT_RES_DRAW_CARD() {
    boost::shared_ptr<unsigned char> localChar = param->GetByte("rscode");
    CCLog("EXT_EVENT_RES_DRAW_CARD rscode = %d", *(localChar.get()));
    
    if (*localChar.get() == 0) {

        // bốc bài thành công
        getButtonByTag(kTagButtonGive)->setEnabled(false);
        getButtonByTag(kTagButtonEat)->setEnabled(false);
        getButtonByTag(kTagButtonHit)->setEnabled(true);
		this->actionLast = BOC_BAI;
    }
    else {
         layerChats->showChatByPos(-1, "Không được bốc");
    }
}

void LayerPlayGamePhom::event_EXT_EVENT_RES_TAKE_CARD() {
    boost::shared_ptr<unsigned char> localChar = param->GetByte("rscode");
    CCLog("EXT_EVENT_RES_TAKE_CARD rscode = %d", *(localChar.get()));
    
    if (*localChar.get() == 0) {
        // an bài thành công
        getButtonByTag(kTagButtonGive)->setEnabled(false);
        getButtonByTag(kTagButtonEat)->setEnabled(false);
        getButtonByTag(kTagButtonHit)->setEnabled(true);
		this->actionLast = AN_BAI;
    }
    else {
        layerChats->showChatByPos(-1, "Không ăn được");
    }
}

void LayerPlayGamePhom::event_EXT_EVENT_RES_DISCARD() {
    boost::shared_ptr<unsigned char> localChar = param->GetByte("rscode");
    CCLog("EXT_EVENT_RES_DISCARD rscode = %d", *(localChar.get()));
    
    if (*localChar.get() == 0) {
        // danh bài thành công
        getButtonByTag(kTagButtonGive)->setEnabled(false);
        getButtonByTag(kTagButtonEat)->setEnabled(false);
        getButtonByTag(kTagButtonHit)->setEnabled(false);
        getButtonByTag(kTagButtonHaPhom)->setEnabled(false);
        getButtonByTag(kTagButtonPush)->setEnabled(false);
        getButtonByTag(kTagButtonU)->setEnabled(false);

		this->actionLast = DANH_BAI;
    }
    else {
        layerChats->showChatByPos(-1, "Bài đánh không hợp lệ");
    }
}

void LayerPlayGamePhom::event_EXT_EVENT_RES_HANDOFF_PHOM() {
    // mỗi lần hạ phỏm thành công là sắp xếp lại
    
    boost::shared_ptr<unsigned char> localChar = param->GetByte("rscode");
    CCLog("EXT_EVENT_RES_HANDOFF_PHOM rscode = %d", *(localChar.get()));
    
    if (*localChar.get() == 0) {
		this->actionLast = HA_PHOM;
    }
	else {
		//layerChats->showChatByPos(-1, "Phỏm không hợp lệ");
	}
}

void LayerPlayGamePhom::event_EXT_EVENT_RES_END_PLAYING() {
    
}

void LayerPlayGamePhom::event_EXT_EVENT_RES_SET_BET() {
    
}

void LayerPlayGamePhom::event_EXT_EVENT_RES_U() {
    
}

void LayerPlayGamePhom::event_EXT_SRVNTF_CAN_TAKE() {
    boost::shared_ptr<unsigned char> cardid = param->GetByte("cardidx");
    layerCards->setIdCardCanEat(*(cardid.get()));
    
    getButtonByTag(kTagButtonEat)->setEnabled(true);
}

void LayerPlayGamePhom::event_EXT_SRVNTF_PLAYER_REPLAY() {
    boost::shared_ptr<string> fname = param->GetUtfString("usrn");
    if (fname->c_str() == myName) {
        layerChats->showChatByPos(-1, "Được tái hạ");
    }
}

void LayerPlayGamePhom::event_EXT_SRVNTF_U_9() {
    getButtonByTag(kTagButtonU)->setEnabled(true);
}


