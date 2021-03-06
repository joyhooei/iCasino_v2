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
	EXT_EVENT_RES_PUSH_CARD,
    //
    EXT_EVENT_REQ_JOIN_GAME,
	EXT_EVENT_REQ_LEAVE_GAME,
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
	if (inString == "rspusc") return EXT_EVENT_RES_PUSH_CARD;
    //
    if (inString == "rqjg") return EXT_EVENT_REQ_JOIN_GAME;
	if (inString == "rqlg") return EXT_EVENT_REQ_LEAVE_GAME;
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
	if (inInt == EXT_EVENT_RES_PUSH_CARD) return "rspusc";
    //
    if (inInt == EXT_EVENT_REQ_JOIN_GAME) return  "rqjg";
	if (inInt == EXT_EVENT_REQ_LEAVE_GAME) return "rqlg";
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
	this->isRegistSittingDown = false;
	this->isRegistStandUp = false;
    
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(-WIDTH_DESIGN / 2, -HEIGHT_DESIGN / 2));
    this->setTouchEnabled(false);
    
    //
    this->levelGame = 0;
	this->actionLast = 0;
    
    //
    createBackgrounds();
    createAvatars();
	createCards();
    createButtons();
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
	arrMoneyDouble.clear();

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

Avatar *avatarMe;
vector<double> arrMoneyDoubleTest;
int indexCount = 0;

void LayerPlayGamePhom::createAvatars() {
    layerAvatars = LayerAvatarInGame::create();
    this->addChild(layerAvatars);

	avatarMe = new Avatar(false);
	avatarMe->setVisibleLayerInvite(false);
	//layerAvatars->addChild(avatarMe);

	avatarMe->setPosition(ccp(300, 300));

	arrMoneyDoubleTest.push_back(12);
	arrMoneyDoubleTest.push_back(3412);
	arrMoneyDoubleTest.push_back(90123);
	arrMoneyDoubleTest.push_back(122356);
	arrMoneyDoubleTest.push_back(5435345);
	arrMoneyDoubleTest.push_back(12123502);
	arrMoneyDoubleTest.push_back(435670324);
	arrMoneyDoubleTest.push_back(3450091231); // hơn 3 tỷ
	arrMoneyDoubleTest.push_back(11233242342); // hơn 11 tỷ
	arrMoneyDoubleTest.push_back(121231231231); // 121 tỷ
	arrMoneyDoubleTest.push_back(1212312312314); // 1212 tỷ
	arrMoneyDoubleTest.push_back(12123123123176); // 12123 tỷ
	arrMoneyDoubleTest.push_back(121231231231234); // 121231 tỷ

}

void LayerPlayGamePhom::createButtons() {
    layerButtons = LayerButtonInGame::create();
    this->addChild(layerButtons);
    
    int widButton = 129;
    int heiButton = 44;
    int space = 10;
    
	createButtonWith_Tag_Title_Position(kTagButtonReady, "Sẵn sàng", ccp(WIDTH_DESIGN - space, space));
	createButtonWith_Tag_Title_Position(kTagButtonSort, "Xếp", ccp(WIDTH_DESIGN - space, space));
	createButtonWith_Tag_Title_Position(kTagButtonHit, "Đánh", ccp(WIDTH_DESIGN - space * 2 - widButton, space));
	createButtonWith_Tag_Title_Position(kTagButtonGive, "Bốc", ccp(WIDTH_DESIGN - space, space * 2 + heiButton));
	createButtonWith_Tag_Title_Position(kTagButtonEat, "Ăn", ccp(WIDTH_DESIGN - space * 3 - widButton * 2, space));
	createButtonWith_Tag_Title_Position(kTagButtonPush, "Gửi", ccp(WIDTH_DESIGN - space * 3 - widButton * 2, space));
	createButtonWith_Tag_Title_Position(kTagButtonHaPhom, "Hạ", ccp(WIDTH_DESIGN - space , space * 2 + heiButton));
	createButtonWith_Tag_Title_Position(kTagButtonU, "Ù", ccp(WIDTH_DESIGN - space * 4 - widButton * 3, space));
	createButtonWith_Tag_Title_Position(kTagButtonSitting, "Ngồi chơi", getButtonByTag(kTagButtonReady)->getPosition());
	//
	getButtonByTag(kTagButtonReady)->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionReady));
	getButtonByTag(kTagButtonSort)->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionSortCards));
	getButtonByTag(kTagButtonHit)->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionHitCards));
	getButtonByTag(kTagButtonGive)->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionGiveCards));
	getButtonByTag(kTagButtonEat)->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionEatCards));
	getButtonByTag(kTagButtonHaPhom)->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionHaPhom));
	getButtonByTag(kTagButtonPush)->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionPush));
	getButtonByTag(kTagButtonU)->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionUUU));
	getButtonByTag(kTagButtonSitting)->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionSitting));

	Button *btnStandUp = Button::create();
	btnStandUp->setTouchEnabled(true);
	btnStandUp->setScale9Enabled(false);
	btnStandUp->loadTextures("menu_standup.png", "menu_standup_hover.png", "");
	btnStandUp->setAnchorPoint(ccp(1, 0));
	btnStandUp->setPosition(ccp(WIDTH_DESIGN - space, HEIGHT_DESIGN - space - heiButton));
	btnStandUp->setScale(0.5);
	btnStandUp->setTag(kTagButtonStandUp);
	btnStandUp->setEnabled(false);
	btnStandUp->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionStandUp));
	layerButtons->addWidget(btnStandUp);
	//

}

void LayerPlayGamePhom::createNumbers() {
    layerNumbers = LayerNumberInGame::create();
    this->addChild(layerNumbers);
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
        layerAvatars->setMoney(layerAvatars->getPosByName(arrName[i]), arrMoneyDouble[i]);
    }
    arrName.clear();
	arrMoney.clear();
	arrMoneyDouble.clear();

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

void LayerPlayGamePhom::playSound( string soundPath )
{
	if( mUtils::isSoundOn() )
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundPath.c_str());
}

void LayerPlayGamePhom::createButton_PushMulti_By_CardId(int cardid) {
	
	Card *card = layerCards->getCardByID(cardid);
	if (card==NULL) return;

	Button* button = Button::create();
	button->setTouchEnabled(true);
	button->setScale9Enabled(false);
	button->loadTextures("ready.png", "ready_selected.png", "");
	button->setTitleText("Gửi");
	button->setTitleColor(ccBLACK);
	button->setTitleFontSize(button->getContentSize().height / 2);
	button->setAnchorPoint(ccp(0.5, 0.5));
	button->setScale(0.5);
	button->addTouchEventListener(this, toucheventselector(LayerPlayGamePhom::actionPushMulti));
	button->setPosition(ccp(card->getPositionX()+60, card->getPositionY()+30));
	button->setTag(kTagButtonPushMulti);
	layerButtons->addWidget(button);

	arrButtonCanPush.push_back(button);
}

void LayerPlayGamePhom::createButtonWith_Tag_Title_Position(int tag, const char *title, CCPoint pPoint) {
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
	button->setTag(tag);
	button->setEnabled(false);
    layerButtons->addWidget(button);
}

Button* LayerPlayGamePhom::getButtonByTag(int tag) {
    Button *button = (Button*) this->layerButtons->getWidgetByTag(tag);
    return button;
}

void LayerPlayGamePhom::hideAllButton() {
	getButtonByTag(kTagButtonReady)->setEnabled(false);
	getButtonByTag(kTagButtonSort)->setEnabled(false);
	getButtonByTag(kTagButtonHit)->setEnabled(false);
	getButtonByTag(kTagButtonGive)->setEnabled(false);
	getButtonByTag(kTagButtonEat)->setEnabled(false);
	getButtonByTag(kTagButtonHaPhom)->setEnabled(false);
	getButtonByTag(kTagButtonPush)->setEnabled(false);
	getButtonByTag(kTagButtonU)->setEnabled(false);
	getButtonByTag(kTagButtonSitting)->setEnabled(false);
	getButtonByTag(kTagButtonStandUp)->setEnabled(false);
}

void LayerPlayGamePhom::actionReady(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
       
        layerCards->resetGame();
        
        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_READY_REQ), parameter, lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
        
       /*indexCount++;
	   if (indexCount == arrMoneyDoubleTest.size()) indexCount = 0;
	   avatarMe->setMoney(arrMoneyDoubleTest.at(indexCount));
       
	   layerNumbers->showNumberByPos(-1, arrMoneyDoubleTest.at(indexCount));*/

    }
}

void LayerPlayGamePhom::actionSortCards(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
        CCLOG("sort!");
		int size = arrButtonCanPush.size();
		if (size > 0) {
			for (int i = size-1; i >= 0; i--)
			{
				arrButtonCanPush.at(i)->setVisible(false);
				arrButtonCanPush.at(i)->setTouchEnabled(false);
				layerButtons->removeChild(arrButtonCanPush.at(i), true);
			}
			arrButtonCanPush.clear();
		}
		//
        boost::shared_ptr<ISFSObject> parameter (new SFSObject());
        boost::shared_ptr< Room > lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
        boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_ORDER_CARDS), parameter, lastRoom));
        GameServer::getSingleton().getSmartFox()->Send(request);
        
        layerCards->setAllowSortCard(true);
    }
}

void LayerPlayGamePhom::actionHitCards(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN){
		int size = arrButtonCanPush.size();
		if (size > 0) {
			for (int i = size-1; i >= 0; i--)
			{
				arrButtonCanPush.at(i)->setVisible(false);
				arrButtonCanPush.at(i)->setTouchEnabled(false);
				layerButtons->removeChild(arrButtonCanPush.at(i), true);
			}
			arrButtonCanPush.clear();
		}
		//
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

		int size = arrButtonCanPush.size();
		if (size > 0) {
			for (int i = size-1; i >= 0; i--)
			{
				arrButtonCanPush.at(i)->setVisible(false);
				arrButtonCanPush.at(i)->setTouchEnabled(false);
				layerButtons->removeChild(arrButtonCanPush.at(i), true);
			}
			arrButtonCanPush.clear();
		}
       
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

		// recomment by Sver (giờ ko cần nữa)
		// this->scheduleOnce(schedule_selector(LayerPlayGamePhom::callbackHaPhom), 0.3);
    }
}

void LayerPlayGamePhom::callbackHaPhom(float dt) {
	vector<string> arrListID = layerCards->getID_HaPhom();

	for (int i = 0; i < arrListID.size(); i++) {
		listID_HaPhom = arrListID[i];

		this->scheduleOnce(schedule_selector(LayerPlayGamePhom::callbackHaPhom_stepByStep), 0.3 * i);
	}
}

void LayerPlayGamePhom::callbackHaPhom_stepByStep(float dt){
	if (listID_HaPhom.length() < 2) return;

	boost::shared_ptr<ISFSObject> params (new SFSObject());
	params->PutUtfString("lc", listID_HaPhom);

	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_HANDOFF_PHOM), params, lastRoom));

	GameServer::getSingleton().getSmartFox()->Send(request);

	listID_HaPhom = "";
}


void LayerPlayGamePhom::actionPush(CCObject *pSender, TouchEventType pType) {
    if (pType == TOUCH_EVENT_BEGAN) {
		//
		int size = arrButtonCanPush.size();
		if (size > 0) {
			for (int i = size-1; i >= 0; i--)
			{
				arrButtonCanPush.at(i)->setVisible(false);
				arrButtonCanPush.at(i)->setTouchEnabled(false);
				layerButtons->removeChild(arrButtonCanPush.at(i), true);
			}
			arrButtonCanPush.clear();
		}
		//

        vector<int> arrID = layerCards->getIdCardByClicked();
        unsigned int length = arrID.size();
        
        if (length != 1) {
            layerChats->showChatByPos(-1, "Hãy chọn 1 quân bài để gửi");
        }
        if (length == 1) {
            CCLOG("Danh quan gui co id = %d", arrID[0]);
            
			this->cardid_push = arrID[0];
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

void LayerPlayGamePhom::actionSitting(CCObject *pSender, TouchEventType pType) {
	if (pType == TOUCH_EVENT_BEGAN) {
		isSpector = layerAvatars->isSpectator();
		isStartedGame = layerAvatars->isStartedGame();
		if (isSpector) {
			if (isStartedGame) {
				if (!isRegistSittingDown){
					layerChats->showChatByPos(-1, "Bạn vừa đăng ký tham gia chơi, vui lòng chờ!");
					isRegistSittingDown = true;
				}
			} else {
				// join game
				boost::shared_ptr<IRequest> request (new SpectatorToPlayerRequest());
				GameServer::getSingleton().getSmartFox()->Send(request);
				isRegistSittingDown = false;

				sendRequestJoinGame();
			}
		}

		((Button*) pSender)->setEnabled(false);
	}
}

void LayerPlayGamePhom::actionStandUp(CCObject *pSender, TouchEventType pType) {
	if (pType == TOUCH_EVENT_BEGAN) {
		//return;
		Button *btn = ((Button*) pSender);
		btn->setEnabled(false);


		isSpector = layerAvatars->isSpectator();
		isStartedGame = layerAvatars->isStartedGame();
		if (!isSpector) {
			if (isStartedGame) {
				if (!isRegistStandUp){
					layerChats->showChatByPos(-1, "Bạn vừa đăng ký đứng xem ở ván kế tiếp");
					isRegistStandUp = true;
					CCLog("-------actionStandUp: isRegistStandUp = true");
				}

			} else {
				boost::shared_ptr<IRequest> request (new PlayerToSpectatorRequest());
				GameServer::getSingleton().getSmartFox()->Send(request);
				isRegistStandUp = false;
				
				sendRequestLeaveGame();
			}
		}

	}
}

void LayerPlayGamePhom::actionPushMulti(CCObject *pSender, TouchEventType pType) {
	if (pType == TOUCH_EVENT_BEGAN) {
		CCLog("actionPushMulti");

		// Clicked vào 1 bộ phỏm để gửi tới đó
		CCPoint positionBt = ((Button*) pSender)->getPosition();
		positionBt.setPoint(positionBt.x-60, positionBt.y-30);

		int size = arrButtonCanPush.size();
		if (size == 0) return;
		for (int i = size-1; i >= 0; i--)
		{
			arrButtonCanPush.at(i)->setVisible(false);
			arrButtonCanPush.at(i)->setTouchEnabled(false);
			layerButtons->removeChild(arrButtonCanPush.at(i), true);
		}
		arrButtonCanPush.clear();

		
		//
		vector<string> arrPlayerPhom = mUtils::splitString(this->dstphsString, '/');
		for (int i = 0; i < arrPlayerPhom.size(); i++)
		{
			vector<string> arr = mUtils::splitString(arrPlayerPhom.at(i), ';');
			if (arr.size() < 2) return;
			int idx1 = atoi(arr.at(0).c_str());
			Card *card = layerCards->getCardByID(idx1);
			CCLog("card->getPositionX()= %.1f",card->getPositionX());
			CCLog("card->getPositionY()= %.1f",card->getPositionY());
			//if (card->getPosition().equals(positionBt) == 0) {
			if (card->getPositionX()==positionBt.x && card->getPositionY()==positionBt.y){
				boost::shared_ptr<ISFSObject> params (new SFSObject());

				params->PutByte("cardidx", this->cardid_push);
				string phomidString = arr.at(arr.size()-2);
				params->PutInt("phomid", atol(phomidString.c_str()));
				params->PutUtfString("usrn", arr.at(arr.size() - 1));

				CCLog("phomid=%d, i=%d", atoi(phomidString.c_str()), i);

				boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
				boost::shared_ptr<IRequest> request 
					(new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_PUSH_CARD), params, lastRoom));

				GameServer::getSingleton().getSmartFox()->Send(request);

				break;
			}
		}

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

       case EXT_EVENT_RES_PUSH_CARD:
		   this->event_EXT_EVENT_RES_PUSH_CARD();
           break;
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
	double moneyDouble = (*ptrNotifiedUser->GetVariable("amf")->GetDoubleValue());
	string name = boost::to_string(*ptrNotifiedUser->Name());
   
    arrName.push_back(name);
    arrMoney.push_back(money);
	arrMoneyDouble.push_back(moneyDouble);
}

void LayerPlayGamePhom::sendRequestJoinGame(float dt) {
    sendRequestJoinGame();
}

void LayerPlayGamePhom::sendRequestJoinGame() {
	// join game
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_JOIN_GAME), params, lastRoom));
	GameServer::getSingleton().getSmartFox()->Send(request);
}

void LayerPlayGamePhom::sendRequestLeaveGame() {
	// leave game
	boost::shared_ptr<ISFSObject> params (new SFSObject());
	boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_LEAVE_GAME), params, lastRoom));
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
	isSpector = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(myName)->IsSpectator();

    
    
	if (list != NULL)
	{
		CCLog("EXT_SRVNTF_PLAYER_LIST = %s", list->c_str());

		layerCards->resetGame();
		playSound("ring_ring.mp3");
		layerAvatars->setListUserByPhom(list->c_str());

		if (levelGame == 0) {
			// ban dau thi hien luon
			// thông tin tiền hiện tại của Users
			for (int i = 0; i < arrName.size(); i++) {
				int pos = layerAvatars->getPosByName(arrName[i]);
				if (pos > -1){
					layerAvatars->setMoney(pos, arrMoneyDouble[i]);
				}
			}

			arrName.clear();
			arrMoney.clear();
			arrMoneyDouble.clear();
		}

		// Check: Vào lại bàn đang chơi dở (isStartedGame=true, isSpector=false)
		isStartedGame = layerAvatars->isStartedGame();
		isSpector = layerAvatars->isSpectator();
		if (isStartedGame && !isSpector) {
			layerChats->showChatByPos(-1, "Xây dựng lại bàn chơi");
			getButtonByTag(kTagButtonSitting)->setEnabled(false);
			getButtonByTag(kTagButtonStandUp)->setEnabled(true);
			getButtonByTag(kTagButtonSort)->setEnabled(true);
		} else {
			layerChats->showChatByPos(-1, "Cập nhật lại bàn chơi");
			if (!isSpector) {
				getButtonByTag(kTagButtonReady)->setEnabled(true);
				getButtonByTag(kTagButtonStandUp)->setEnabled(true);
				getButtonByTag(kTagButtonSitting)->setEnabled(false);
			} else {
				getButtonByTag(kTagButtonSitting)->setEnabled(true);
				sendRequestLeaveGame();
			}
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
    playSound("start_game.mp3");

    this->resetGame();

	string mes = "Bắt đầu";
	if (isSpector) mes += ". Bạn là khách, hãy tham gia sau";
	layerChats->showChatByPos(-1, mes);
}

void LayerPlayGamePhom::event_EXT_EVENT_END() {
	layerChats->showChatByPos(-1, "Kết thúc");
    CCLog("EXT_EVENT_END");
	playSound("end_game.mp3");
    
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
    
	layerAvatars->stopAllTimer();

	isSpector = layerAvatars->isSpectator();
	isStartedGame = layerAvatars->isStartedGame();

	if (!isSpector) {
		getButtonByTag(kTagButtonStandUp)->setEnabled(true);
		getButtonByTag(kTagButtonReady)->setTitleText("Sẵn sàng");
		getButtonByTag(kTagButtonReady)->setEnabled(true);
	} else {
		getButtonByTag(kTagButtonStandUp)->setEnabled(false);
		getButtonByTag(kTagButtonReady)->setEnabled(false);
	}

	if (isStartedGame) {
		CCLOG("Game dang choi");
		if (isSpector) {
			CCLOG("Ban la khach");
			getButtonByTag(kTagButtonSort)->setEnabled(false);
			getButtonByTag(kTagButtonStandUp)->setEnabled(false);
			getButtonByTag(kTagButtonSitting)->setEnabled(true);
		}
		else {
			CCLOG("Ban la nguoi choi");
			getButtonByTag(kTagButtonStandUp)->setEnabled(true);
			getButtonByTag(kTagButtonSort)->setEnabled(true);
			getButtonByTag(kTagButtonSitting)->setEnabled(false);
			getButtonByTag(kTagButtonReady)->setEnabled(false);
		}
	}
	else {
		CCLOG("Game chua bat dau");
		// Game đang ko diễn ra, có thể gửi đi thông báo đứng xem
		if (!isSpector && isRegistStandUp) {
			boost::shared_ptr<IRequest> request (new PlayerToSpectatorRequest());
			GameServer::getSingleton().getSmartFox()->Send(request);
			isRegistStandUp = false;
			CCLog("-------Room..: Gửi đi thông báo muốn đứng xem!");

			// leave game
			boost::shared_ptr<ISFSObject> params (new SFSObject());
			boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
			boost::shared_ptr<IRequest> request2 (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_LEAVE_GAME), params, lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request2);
		}

		// có thể gửi đi thông báo muốn ngồi vào bàn chơi
		if (isSpector && isRegistSittingDown) {
			boost::shared_ptr<IRequest> request (new SpectatorToPlayerRequest());
			GameServer::getSingleton().getSmartFox()->Send(request);
			isRegistSittingDown = false;
			CCLog("-------Room..: Gửi đi thông báo muốn ngồi!");

			// join game
			boost::shared_ptr<ISFSObject> params (new SFSObject());
			boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
			boost::shared_ptr<IRequest> request2 (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_JOIN_GAME), params, lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request2);
		}
	}
    
}

void LayerPlayGamePhom::event_EXT_EVENT_GAME_RESULT() {
    boost::shared_ptr<string> resultGame = param->GetUtfString("rg");
    
    //0:28:4:1000:1401329992510:thanhhv4;1:36:5:-1000:1401330005039:thanhhv2;
    CCLog("EXT_EVENT_GAME_RESULT rg= %s.", resultGame->c_str());
    
    if (resultGame == NULL) {
        return;
    }
    
	hideAllButton();
	layerAvatars->stopAllTimer();

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
        else if (this->actionLast != DANH_BAI && this->actionLast != BOC_BAI && this->actionLast != AN_BAI){
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
				ressonString = "Bị ăn";
				break;
			case 1:
				ressonString = "Được ăn";
				break;
			case 2:
				//ressonString = "Kết thúc";
				break;
			case 3:
				ressonString = "Ăn láo";
				break;
			case 4:
				ressonString = "Bị đền làng";
				break;
			case 7:
				ressonString = "Bị ăn chốt";
				break;
			case 8:
				ressonString = "Được ăn chốt";
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

void LayerPlayGamePhom::event_EXT_EVENT_RES_PUSH_CARD() {
	boost::shared_ptr<unsigned char> localChar = param->GetByte("rscode");
	if (localChar==NULL) return;
	int rscode = *(localChar.get());
	CCLog("event_EXT_EVENT_RES_PUSH_CARD rscode = %d", rscode);
	if (rscode == 0) {
		// Gui thanh cong
	} else if (rscode == 29) {
		layerChats->showChatByPos(-1, "Hãy chọn bộ phỏm bạn muốn gửi");

		// co nhieu bo phom thoa man quan bai gui di
		// EXT_FIELD_DESTINATION_PHOMS = "dstphs";      // ds các phỏm có thể gửi bài
		boost::shared_ptr<string> dstphs = param->GetUtfString("dstphs");
		if (dstphs==NULL) return;
		this->dstphsString = (string)dstphs->c_str();
		// dstphs = playerphom1/playerphom2/.../playerphomN
		// playerphom = idx1:idx2:idxn;phomID;userName
		CCLog("dstphsString= | %s |", dstphsString.c_str());

		/*
			Ở đây khi đã xác định được nhưng nơi có thể đc gửi tới,
			ta đặt ở đó những Button mà khi nhấn vào Button đó, 
			tương ứng dữ liệu sẽ được gửi đi
		*/
		vector<string> arrPlayerPhom = mUtils::splitString(this->dstphsString, '/');
		for (int i = 0; i < arrPlayerPhom.size(); i++)
		{
			vector<string> arr = mUtils::splitString(arrPlayerPhom.at(i), ';');
			if (arr.size() == 0) return;
			int idx1 = atoi(arr.at(0).c_str());
			createButton_PushMulti_By_CardId(idx1);
		}
	}
	
	
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

void LayerPlayGamePhom::OnSmartFoxPublicMessage( unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent )
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

void LayerPlayGamePhom::OnSmartFoxUserExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	//
	if( ptrNotifiedUser->IsItMe() ){
		//close window - tricks by HoangDD
		layerButtons->eventTouchBtnBack(NULL, TOUCH_EVENT_ENDED);
	}
}

void LayerPlayGamePhom::OnSmartFoxRoomVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){

	boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEvetnParams)["room"];
	boost::shared_ptr<Room> room = ((boost::static_pointer_cast<Room>(ptrEventParamValueRoom)));
	//
	boost::shared_ptr<RoomVariable> rv = room->GetVariable("params");
	string s = *rv->GetStringValue();
	CCLOG("Room %s update RoomVariables: %s", room->Name()->c_str(), s.c_str());


	vector<string> lstBet = mUtils::splitString( s, '@' );
	lstBet.at(1).compare("1")==0 ? (isStartedGame=true) : (isStartedGame=false);

	isSpector = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(myName)->IsSpectator();
	isSpector = layerAvatars->isSpectator();
	/*if (!isSpector) {
		getButtonByTag(kTagButtonReady)->setTitleText("Sẵn sàng");
		getButtonByTag(kTagButtonReady)->setEnabled(true);
	} else {
		getButtonByTag(kTagButtonReady)->setEnabled(false);
	}

	if (isStartedGame) {
		CCLOG("Game dang choi");
		if (isSpector) {
			CCLOG("Ban la khach");
			getButtonByTag(kTagButtonSort)->setEnabled(false);
			getButtonByTag(kTagButtonStandUp)->setEnabled(false);
			getButtonByTag(kTagButtonSitting)->setEnabled(true);
		}
		else {
			CCLOG("Ban la nguoi choi");
			getButtonByTag(kTagButtonStandUp)->setEnabled(true);
			getButtonByTag(kTagButtonSort)->setEnabled(true);
			getButtonByTag(kTagButtonSitting)->setEnabled(false);
			getButtonByTag(kTagButtonReady)->setEnabled(false);
		}
	}
	else {
		CCLOG("Game chua bat dau");
		// Game đang ko diễn ra, có thể gửi đi thông báo đứng xem
		if (!isSpector && isRegistStandUp) {
			/ *boost::shared_ptr<IRequest> request (new PlayerToSpectatorRequest());
			GameServer::getSingleton().getSmartFox()->Send(request);* /
			isRegistStandUp = false;
			CCLog("-------Room..: Gửi đi thông báo muốn đứng xem!");

			// leave game
			boost::shared_ptr<ISFSObject> params (new SFSObject());
			boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
			boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_LEAVE_GAME), params, lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
		}

		// có thể gửi đi thông báo muốn ngồi vào bàn chơi
		if (isSpector && isRegistSittingDown) {
			/ *boost::shared_ptr<IRequest> request (new SpectatorToPlayerRequest());
			GameServer::getSingleton().getSmartFox()->Send(request);* /
			isRegistSittingDown = false;
			CCLog("-------Room..: Gửi đi thông báo muốn ngồi!");

			// join game
			boost::shared_ptr<ISFSObject> params (new SFSObject());
			boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
			boost::shared_ptr<IRequest> request (new ExtensionRequest(convertResponseToString(EXT_EVENT_REQ_JOIN_GAME), params, lastRoom));
			GameServer::getSingleton().getSmartFox()->Send(request);
		}
	}*/
}

