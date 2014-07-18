//
//  _Avatar_inGame_.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/15/14.
//
//

#include "_Avatar_inGame_.h"
#include "SceneManager.h"
#include "GameServer.h"
#include "LayerPlayGamePhom.h"
#include "LayerPlayGameTLMN.h"

vector<string> getArrSplit(string &S, const char &str);
vector<string> getArrSplit(string &S, const char &str){
    vector<string> arrStr;
    string::iterator t,t2;
    
    for (t = S.begin(); t < S.end(); ){
        // Lặp từ vị trí bắt đầu
        t2=find(t, S.end(),str); // Tìm vị trí space ' ' đầu tiên
        //kể từ vị trí t
        if(t!=t2)
            arrStr.push_back(string(t,t2));
		else if (t2 != S.end())
		{
			arrStr.push_back("");
		}

		if (t2 == S.end())
		{
			break;
		} 

        t=t2+1; // chuyển sang vị trí sau
    }
    return arrStr;
}

LayerAvatarInGame::~LayerAvatarInGame(){
	
}

void LayerAvatarInGame::onExit() {
	CCLOG("onExit: clean LayerAvatarInGame");
	
	arrName.clear();
	arrFlag.clear();
	arrURL.clear();
	arrAI.clear();
	arrMoney.clear();
	arrMoneyDouble.clear();
	if (chuong) {
		chuong->release();
		chuong=NULL;
	}
}

bool LayerAvatarInGame::init() {
    if (!CCLayer::init()) return false;
    
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(0, 0));
    
	this->typeGame = 0;
	this->myName = SceneManager::getSingleton().getMyName();
	this->myAI   = SceneManager::getSingleton().getMyName();

	CCLog("this->myName = SceneManager::getSingleton().getMyName() = %s", this->myName.c_str());

    Avatar *me = new Avatar(true);
    Avatar *left = new Avatar(false);
    Avatar *right = new Avatar(false);
    Avatar *top = new Avatar(false);
	Avatar *bottom = new Avatar(false);

	me->autorelease();
	left->autorelease();
	right->autorelease();
	top->autorelease();
	bottom->autorelease();
    
    me->setPosition(ccp(10, HEIGHT_DESIGN - 10 - me->getSizeThis().height));
    left->setPosition(ccp(10, HEIGHT_DESIGN / 2 - left->getSizeThis().height / 2));
    right->setPosition(ccp(WIDTH_DESIGN - 10 - right->getSizeThis().width, HEIGHT_DESIGN / 2 - left->getSizeThis().height / 2));
    top->setPosition(ccp(WIDTH_DESIGN / 2 - top->getSizeThis().width / 2, HEIGHT_DESIGN - 10 - top->getSizeThis().height));
    bottom->setPosition(ccp(top->getPositionX(), 10));

    me->setTag(kUserMe);
    left->setTag(kUserLeft);
    right->setTag(kUserRight);
    top->setTag(kUserTop);
    bottom->setTag(kUserBot);

    this->addChild(me);
    this->addChild(left);
    this->addChild(right);
    this->addChild(top);
	this->addChild(bottom);
    
    chuong = UIImageView::create();
    chuong->loadTexture("Chuong.png");
    chuong->setTouchEnabled(false);
    chuong->setVisible(false);
    chuong->setAnchorPoint(ccp(0,0));
    chuong->setPosition(ccp(0,0));
    this->addChild(chuong);
    
	


    return true;
}

void LayerAvatarInGame::setIcon(int pos, char *url){
    if (this->getUserByPos(pos) == NULL) return;
    this->getUserByPos(pos)->setIcon(url);
}

void LayerAvatarInGame::setFlag(int pos, bool isShow){
    if (this->getUserByPos(pos) == NULL) return;
    this->getUserByPos(pos)->setFlag(isShow);
}

void LayerAvatarInGame::setName(int pos, string name){
    if (this->getUserByPos(pos) == NULL) return;
    this->getUserByPos(pos)->setName(name);
}

void LayerAvatarInGame::setMoney(int pos, string money){
    if (this->getUserByPos(pos) == NULL) return;
    this->getUserByPos(pos)->setMoney(money);
}

void LayerAvatarInGame::setMoney(int pos, int money) {
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setMoney(money);
}

void LayerAvatarInGame::setMoney(int pos, double money) {
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setMoney(money);
}

void LayerAvatarInGame::setReady(int pos, bool isReady){
    if (this->getUserByPos(pos) == NULL) return;
    this->getUserByPos(pos)->setReady(isReady);
}

void LayerAvatarInGame::setVisibleLayerInvite(int pos, bool isShow) {
	Avatar *user = this->getUserByPos(pos);
	if (user != NULL)
	{
		user->setVisibleLayerInvite(isShow);
	}
}

void LayerAvatarInGame::setUnReadyAllUser() {
    setReady(kUserMe, false);
    setReady(kUserLeft, false);
    setReady(kUserRight, false);
    setReady(kUserTop, false);
	setReady(kUserBot, false);
}

void LayerAvatarInGame::resetGame() {
    // Ready status
    setUnReadyAllUser();
}

void LayerAvatarInGame::setListUserByPhom(string listUser) {
    //resetGame();
    this->typeGame = PHOM;
    this->listUser = listUser;
    const char c1 = ';';
    const char c2 = ':';
    formatAndStore(c1, c2);
}

void LayerAvatarInGame::setListUserByTienLen(string listUser) {
    //resetGame();
    this->typeGame= TIEN_LEN;
    this->listUser = listUser;
    const char c1 = '-';
    const char c2 = '_';
    formatAndStore(c1, c2);
}

void LayerAvatarInGame::formatAndStore(const char &c1, const char &c2) {
    vector<string> arrUsers = getArrSplit(this->listUser, c1);

    // release arr
    arrName.clear();
    arrFlag.clear();
    arrURL.clear();
    arrAI.clear();
	arrMoney.clear();
	arrMoneyDouble.clear();

    for (int i = 0; i < arrUsers.size(); i++) {
        vector<string> arr = getArrSplit(arrUsers[i], c2);
		if (arr.size() < 3)
		{
			continue;
		}
        string id = arr[0];
        string name = arr[1];
        string flag = arr[2];
        
		arrFlag.push_back(flag);

        // url icon
        boost::shared_ptr<User> userInfo = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(name);
		
		if (userInfo == NULL){
			arrAI.push_back(name);
			arrName.push_back(name);
			arrURL.push_back("");
			arrMoney.push_back(0);
			arrMoneyDouble.push_back(0);
			continue;
		}

		// url
		boost::shared_ptr<string> url = userInfo->GetVariable("aal")->GetStringValue();
        arrURL.push_back(url->c_str());

		// Money
		boost::shared_ptr<double> amf = userInfo->GetVariable("amf")->GetDoubleValue();
		arrMoneyDouble.push_back(*amf);
		arrMoney.push_back(((int)(*amf)));

		// account ID
		boost::shared_ptr<string> aI = userInfo->Name();
		if (aI != NULL){
			CCLog("---------aI= %s", aI->c_str());
			arrAI.push_back(aI->c_str());
		}

		// account Name
		boost::shared_ptr<string> aN = userInfo->GetVariable("aN")->GetStringValue();
		if (aN != NULL) {
			CCLog("---------aN= %s", aN->c_str());
			arrName.push_back(aN->c_str());
		}
    }
    
    updateUsers();
}

Avatar* LayerAvatarInGame::getUserByPos(int pos){
	if (pos < 0) return NULL;
    if (this->getChildByTag(pos) == NULL) return NULL;
    return (Avatar*) this->getChildByTag(pos);
}

int LayerAvatarInGame::getIndexInArrByName(string name) {
    for (int i = 0; i < arrName.size(); i++) {
        if (arrName[i] == name) return i;
    }
    return -1;
}

int LayerAvatarInGame::getIndexInArrByAccountID(string aI) {
	for (int i = 0; i < arrAI.size(); i++) {
		if (arrAI[i] == aI) return i;
	}
	return -1;
}

int LayerAvatarInGame::getPosByName(string pName) {
	
	return getPosByAccountID(pName);

	//
    int pos = getIndexInArrByName(this->myName);
    
	if (pos == -1)
	{
		isGuess = true;
		return (getIndexInArrByName(pName));
	}
    // tra lai vi tri
	else{
		isGuess = false;
		int countUser = arrName.size();
        for (int i = 0; i < countUser; i++) {
            if (arrName[i] == pName) {
                if (i == pos) {
                    return kUserMe;
                } else if (i == (pos + 1) % countUser) {
                    return kUserRight;
                } else if (i == (pos + 2) % countUser) {
                    return kUserTop;
                } else if (i == (pos + 3) % countUser) {
                    return kUserLeft;
                }
                
                break;
            }
        }
    }
    
    return -1;
}

int LayerAvatarInGame::getPosByAccountID(string aI) {
	int pos = getIndexInArrByAccountID(this->myAI);
	//CCLog("getPosByAccountID aI=%s, myAI=%s, pos=%d", aI.c_str(), myAI.c_str(), pos);

	if (pos == -1)
	{
		isGuess = true;
		return (getIndexInArrByAccountID(aI));
	}
	// tra lai vi tri
	else{
		isGuess = false;
		int countUser = arrAI.size();
		for (int i = 0; i < countUser; i++) {
			if (arrAI[i] == aI) {
				if (i == pos) {
					return kUserMe;
				} else if (i == (pos + 1) % countUser) {
					return kUserRight;
				} else if (i == (pos + 2) % countUser) {
					return kUserTop;
				} else if (i == (pos + 3) % countUser) {
					return kUserLeft;
				}

				break;
			}
		}
	}

	return -1;
}


string LayerAvatarInGame::getNameByPos(int pPos) {
    int pos = getIndexInArrByName(this->myName);
    
	if (pos == -1) {
		this->isGuess = true;
		if (pPos < arrName.size() && pPos >= 0) return arrName.at(pPos);
	}
	else {
		this->isGuess = false;
		int countUser = arrName.size();
        switch (pPos) {
            case kUserMe:
                return this->myName;
                break;
            
            case kUserRight:
                return arrName[(pPos + 1) % countUser];
                break;
                
            case kUserTop:
                return arrName[(pPos + 2) % countUser];
                break;
                
            case kUserLeft:
                return arrName[(pPos + 3) % countUser];
                break;
        }
    }

	return "";
}

string LayerAvatarInGame::getAccountIDByPos(int pPos) {
	int pos = getIndexInArrByAccountID(this->myAI);

	if (pos == -1) {
		this->isGuess = true;
		if (pPos < arrAI.size() && pPos >= 0) return arrAI.at(pPos);
	}
	else {
		this->isGuess = false;
		int countUser = arrAI.size();
		switch (pPos) {
		case kUserMe:
			return this->myAI;
			break;

		case kUserRight:
			return arrAI[(pPos + 1) % countUser];
			break;

		case kUserTop:
			return arrAI[(pPos + 2) % countUser];
			break;

		case kUserLeft:
			return arrAI[(pPos + 3) % countUser];
			break;
		}
	}

	return "";
}

void LayerAvatarInGame::updateUsers() {
    if (arrName.size() != arrFlag.size() || arrName.size() != arrURL.size() || arrURL.size() != arrAI.size()) {
        return;
    }

	// Mỗi khi nhảy tới đây thì cần làm 2 việc sau:
	// 1. Làm "sạch" toàn bộ các Avatar: 
	//   1.1 Avatar của mình: ẩn đi, 
	//						  trạng thái ready=false, BtnReady -> title="Sẵn sàng", -> visible=false???
	//                        ai="";
	//	 1.2 Avatar user khác hiện lên các InviteUser, ready=false
	//   1.3 Toàn bộ thông tin về tiền được reset
	// 2. Cập nhật lại thông tin: 
	//   2.0: 
	//	 2.1: nếu của mình thì hiện lên Avatar, BtnReady->visible=true 
	//   2.2: các user khác thì cập nhật & ẩn đi Invite
    // ---

	// 1. Làm "sạch"
	Avatar *avaMe = getUserByPos(kUserMe);
	Avatar *avaLeft = getUserByPos(kUserLeft);
	Avatar *avaRight = getUserByPos(kUserRight);
	Avatar *avaTop = getUserByPos(kUserTop);
	Avatar *avaBot = getUserByPos(kUserBot);

	avaMe->setVisible(false);
	avaMe->setTouchEnabled(false);
	//avaMe->setReady(false);
	avaMe->setName("");
	avaMe->setMoney("");
	avaMe->setAI("");
	/*Button *btnReady=NULL;
	LayerPlayGamePhom *layerGamePhom;
	LayerPlayGameTLMN *layerGameTLMN;
	switch (this->typeGame) {
		case PHOM:
			layerGamePhom = SceneManager::getSingleton().getLayerGamePhom();
			btnReady = layerGamePhom->getButtonByTag(kTagButtonReady);
			break;
		case TIEN_LEN:
			layerGameTLMN = SceneManager::getSingleton().getLayerGameTLMN();
			btnReady = layerGameTLMN->getButtonByTag(kTagButtonReady);
			break;
	}
	if (btnReady == NULL) return;
	btnReady->setTitleText("Sẵn sàng");
	btnReady->setEnabled(false);*/

	avaLeft->setVisibleLayerInvite(true);
	avaLeft->setReady(false);
	avaLeft->setName("");
	avaLeft->setMoney("");
	avaLeft->setAI("");
	//
	avaRight->setVisibleLayerInvite(true);
	avaRight->setReady(false);
	avaRight->setName("");
	avaRight->setMoney("");
	avaRight->setAI("");
	//
	avaTop->setVisibleLayerInvite(true);
	avaTop->setReady(false);
	avaTop->setName("");
	avaTop->setMoney("");
	avaTop->setAI("");
	//
	avaBot->setVisibleLayerInvite(true);
	avaBot->setReady(false);
	avaBot->setName("");
	avaBot->setMoney("");
	avaBot->setAI("");

	// 2. Update info :D
    int length = arrName.size();
    for (int i = 0; i < length; i++) {
        string name = arrName[i];
        string flag = arrFlag[i];
        string url  = arrURL[i];
        string aI = arrAI[i];
		int money = arrMoney[i];
		double moneyDouble = arrMoneyDouble.at(i);

        int pos = getPosByAccountID(aI);
		CCLog("------pos=%d", pos);
        if (pos < 0)
            break;
		if (!isGuess){
			getUserByPos(kUserBot)->setVisible(false); 
			getUserByPos(kUserBot)->setTouchEnabled(false);
			getUserByPos(kUserBot)->setPositionY(-200);
		}
		else {
			getUserByPos(kUserBot)->setVisible(true);
			getUserByPos(kUserBot)->setTouchEnabled(true);
			getUserByPos(kUserBot)->setPositionY(10);
		}
			Avatar *user = getUserByPos(pos);
			user->setName(name);
			user->setFlag(atoi(flag.c_str()) == 1);
			//
			bool meIsBoss = (atoi(flag.c_str()) == 1);
			if(pos == kUserMe){
				this->getUserByPos(kUserLeft)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kUserRight)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kUserBot)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kUserTop)->setMeIsBoss(meIsBoss);
			}
			user->setIcon(url);
			user->setAI(aI);
			user->setMoney(money);
			user->setMoney(moneyDouble);

			if (pos == kUserMe)
			{
				user->setVisible(true);
				user->setTouchEnabled(true);
				//btnReady->setEnabled(true);
			}
			else {
				user->setVisibleLayerInvite(false);
			}
    }
}

void LayerAvatarInGame::runTimer(int posUser) {
    stopAllTimer();
    getUserByPos(posUser)->startTimer();
}

void LayerAvatarInGame::stopAllTimer() {
    getUserByPos(kUserMe)->stopTimer();
    getUserByPos(kUserLeft)->stopTimer();
    getUserByPos(kUserRight)->stopTimer();
    getUserByPos(kUserTop)->stopTimer();
}


void LayerAvatarInGame::setPosChuong(int pos){
	bool meIsBoss = false;
    switch (pos) {
        case kUserLeft:
            chuong->setPosition(ccp(101,175));
            chuong->setVisible(true);
            break;
        case kUserRight:
            chuong->setPosition(ccp(678,175));
            chuong->setVisible(true);
            break;
        case kUserTop:
            chuong->setPosition(ccp(445,345));
            chuong->setVisible(true);
            break;
        case kUserBot:
            break;
        case kUserMe:
            chuong->setPosition(ccp(175,420));
            chuong->setVisible(true);
			meIsBoss = true;
            break;
        default:
            break;
    }
    //
	this->getUserByPos(kUserLeft)->setMeIsBoss(meIsBoss);
	this->getUserByPos(kUserRight)->setMeIsBoss(meIsBoss);
	this->getUserByPos(kUserBot)->setMeIsBoss(meIsBoss);
	this->getUserByPos(kUserTop)->setMeIsBoss(meIsBoss);
}


void LayerAvatarInGame::resetAll(){
    setFlag(kUserMe, false);
    setFlag(kUserLeft, false);
    setFlag(kUserRight, false);
    setFlag(kUserTop, false);
    
    setName(kUserMe, "");
    setName(kUserLeft, "");
    setName(kUserRight, "");
    setName(kUserTop, "");
    
    setMoney(kUserMe, "");
    setMoney(kUserLeft, "");
    setMoney(kUserRight, "");
    setMoney(kUserTop, "");

	this->getUserByPos(kUserLeft)->setVisibleLayerInvite(true);
	this->getUserByPos(kUserRight)->setVisibleLayerInvite(true);
	this->getUserByPos(kUserTop)->setVisibleLayerInvite(true);
}