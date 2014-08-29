//
//  _Avatar_inGame_.cpp
//  iCasino_v2
//
//  Created by Thanhhv on 5/15/14.
//
//

#include "_Avatar_inTomCuaCa.h"
#include "SceneManager.h"
#include "GameServer.h"
#include "LayerPlayGamePhom.h"
#include "LayerPlayGameTLMN.h"

vector<string> getArrSplit1(string &S, const char &str);
vector<string> getArrSplit1(string &S, const char &str){
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

AvatarInTomCuaCa::~AvatarInTomCuaCa(){

}

void AvatarInTomCuaCa::onExit() {
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

bool AvatarInTomCuaCa::init() {
	if (!CCLayer::init()) return false;

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));
	UILayer *ul = UILayer::create();

	this->typeGame = 0;
	this->myName = SceneManager::getSingleton().getMyName();
	this->myAI   = SceneManager::getSingleton().getMyName();
	btn_vaochoi = UIButton::create();
    btn_vaochoi->setTouchEnabled(true);
    btn_vaochoi->loadTextures("ready.png", "ready_selected.png", "");
    btn_vaochoi->setTitleText("Vào bàn");
	
    btn_vaochoi->setPosition(ccp(320,36));
	btn_vaochoi->setTitleFontSize(20);
    btn_vaochoi->addTouchEventListener(this,toucheventselector(LayerBaCayAvatar::vaoBanChoi));
    btn_vaochoi->setEnabled(false);
	btn_vaochoi->setTag(0);
    
	btn_dungday = UIButton::create();
	btn_dungday->setTouchEnabled(true);
	btn_dungday->loadTextures("ready.png", "ready_selected.png", "");
	btn_dungday->setTitleText("Đứng dậy");
	btn_dungday->setPosition(ccp(320,36));
	btn_dungday->setTitleFontSize(20);
	btn_dungday->addTouchEventListener(this,toucheventselector(LayerBaCayAvatar::vaoBanChoi));
	btn_dungday->setEnabled(false);
	btn_dungday->setTag(1);
    ul->addWidget(btn_vaochoi);
    ul->addWidget(btn_dungday);
    
	this->addChild(ul);
    CCLog("this->myName = SceneManager::getSingleton().getMyName() = %s", this->myName.c_str());

	Avatar *me = new Avatar(false);
	Avatar *user1 = new Avatar(false);
	Avatar *user2 = new Avatar(false);
	Avatar *user3 = new Avatar(false);
	Avatar *user4 = new Avatar(false);
    Avatar *user5 = new Avatar(false);

    me->setScale(0.8);
    user1->setScale(0.8);
    user2->setScale(0.8);
    user3->setScale(0.8);
    user4->setScale(0.8);
    user5->setScale(0.8);
    
	me->autorelease();
	user1->autorelease();
	user2->autorelease();
    user3->autorelease();
	user4->autorelease();
    user5->autorelease();

	me->setPosition(ccp(30, 320));
	user1->setPosition(ccp(80,200));
	user2->setPosition(ccp(30,80));
	user3->setPosition(ccp(WIDTH_DESIGN-10-user3->getSizeThis().width,320));
	user4->setPosition(ccp(WIDTH_DESIGN-60-user4->getSizeThis().width,200));
    user5->setPosition(ccp(WIDTH_DESIGN-10-user5->getSizeThis().width,80));
	

	me->setTag(kuser0);
	user1->setTag(kuser1);
	user2->setTag(kuser2);
    user3->setTag(kuser3);
	user4->setTag(kuser4);
    user5->setTag(kuser5);

	this->addChild(me);
	this->addChild(user1);
	this->addChild(user2);
    this->addChild(user3);
	this->addChild(user4);
    this->addChild(user5);

	chuong = UIImageView::create();
    chuong->setScale(0.7);
	chuong->loadTexture("Chuong.png");
	chuong->setTouchEnabled(false);
	chuong->setVisible(false);
	chuong->setAnchorPoint(ccp(0,0));
	chuong->setPosition(ccp(0,0));
	this->addChild(chuong);
	return true;
}

void AvatarInTomCuaCa::setIcon(int pos, char *url){
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setIcon(url);
}

void AvatarInTomCuaCa::setFlag(int pos, bool isShow){
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setFlag(isShow);
}

void AvatarInTomCuaCa::setName(int pos, string name){
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setName(name);
}

void AvatarInTomCuaCa::setMoney(int pos, string money){
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setMoney(money);
}

void AvatarInTomCuaCa::setMoney(int pos, int money) {
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setMoney(money);
}

void AvatarInTomCuaCa::setMoney(int pos, double money) {
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setMoney(money);
}

void AvatarInTomCuaCa::setReady(int pos, bool isReady){
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setReady(isReady);
}

void AvatarInTomCuaCa::setVisibleLayerInvite(int pos, bool isShow) {
	Avatar *user = this->getUserByPos(pos);
	if (user != NULL)
	{
		user->setVisibleLayerInvite(isShow);
	}
}

void AvatarInTomCuaCa::setUnReadyAllUser() {
	setReady(kuser0, false);
	setReady(kuser1, false);
	setReady(kuser2, false);
    setReady(kuser3, false);
	setReady(kuser4, false);
    setReady(kuser5, false);
}

void AvatarInTomCuaCa::resetGame() {
	// Ready status
	setUnReadyAllUser();
}




Avatar* AvatarInTomCuaCa::getUserByPos(int pos){
	if (pos < 0) return NULL;
	if (this->getChildByTag(pos) == NULL) return NULL;
	return (Avatar*) this->getChildByTag(pos);
}

int AvatarInTomCuaCa::getIndexInArrByName(string name) {
	for (int i = 0; i < arrName.size(); i++) {
		if (arrName[i] == name) return i;
	}
	return -1;
}
int AvatarInTomCuaCa::getIndexInArrByAccountID(string aI) {
	for (int i = 0; i < arrAI.size(); i++) {
		if (arrAI[i] == aI) return i;
	}
	return -1;
}
int AvatarInTomCuaCa::getPosByName(string pName) {
    int vt = -1;
	if (this->listUser == "")
	{
		return vt;
	}
	
	vector<string> list = mUtils::splitString(listUser,';');
	for (int i = 0; i < list.size(); i++)
	{
		vector<string> info = mUtils::splitString(list[i],'|');
        
		if ((strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)||isSpect()==true)
		{
			vt = i;
			break;
		}
	}
    
	for (int i = 0; i < list.size(); i++)
	{
		if (strcmp(list[i].c_str(), "") == 0)
		{
			continue;
		}
        
		vector<string> info = mUtils::splitString(list[i],'|');
		if (strcmp(info[0].c_str(), pName.c_str()) == 0)
		{
			if(i == vt){
				return kuser0;
                
			}
			else if(i == (vt + 1) % 6){
				return kuser1;
			}
			else if(i == (vt + 2) % 6){
				return kuser2;
			}
			else if(i == (vt + 3) % 6){
				return kuser3;
			}
            else if(i == (vt + 4) % 6){
				return kuser4;
			}
            else if(i == (vt + 5) % 6){
				return kuser5;
			}

			break;
		}
	}
    
	return -1;
}

string AvatarInTomCuaCa::getNameByPos(int pPos) {
	int pos = getIndexInArrByName(this->myName);

	if (pos == -1) {
		this->isGuess = true;
		if (pPos < arrName.size() && pPos >= 0) return arrName.at(pPos);
	}
	else {
		this->isGuess = false;
		int countUser = arrName.size();
		switch (pPos) {
		case kuser0:
			return this->myName;
			break;
		case kuser1:
			return arrName[(pPos + 1) % 6];
			break;
		case kuser2:
			return arrName[(pPos + 2) % 6];
			break;

		case kuser3:
			return arrName[(pPos + 3) % 6];
			break;
		case kuser4:
			return arrName[(pPos + 4) % 6];
			break;
            case kuser5:
                return arrName[(pPos + 5) % 6];
                break;
		}
	}

	return "";
}
string AvatarInTomCuaCa::getAccountIDByPos(int pPos) {
	int pos = getIndexInArrByAccountID(this->myAI);

	if (pos == -1) {
		this->isGuess = true;
		if (pPos < arrAI.size() && pPos >= 0) return arrAI.at(pPos);
	}
	else {
		this->isGuess = false;
		switch (pPos) {
		case kuser0:
			return this->myAI;
			break;

		case kuser1:
			return arrAI[(pPos + 1) % 6];
			break;

		case kuser2:
			return arrAI[(pPos + 2) % 6];
			break;

		case kuser3:
			return arrAI[(pPos + 3) % 6];
			break;

		case kuser4:
			return arrAI[(pPos + 4) % 6];
			break;
                
            case kuser5:
                return arrAI[(pPos + 5) % 6];
                break;
		}
	}

	return "";
}
void AvatarInTomCuaCa::updateUsers() {
	if (this->listUser == "")
	{
        getUserByPos(kuser0)->setVisibleLayerInvite(true);
		return;
	}
    
	vector<string> arrUser = mUtils::splitString(this->listUser,';');
    
	if (arrUser.size() == 0)
	{
		return;
	}
    
	Avatar *avaMe    = getUserByPos(kuser0);
	Avatar *avaUser1 = getUserByPos(kuser1);
	Avatar *avaUser2 = getUserByPos(kuser2);
	Avatar *avaUser3 = getUserByPos(kuser3);
	Avatar *avaUser4 = getUserByPos(kuser4);
    Avatar *avaUser5 = getUserByPos(kuser5);
   
    
	avaMe->setVisible(true);
	avaMe->setTouchEnabled(false);
	avaMe->setReady(false);
	avaMe->setName("");
	avaMe->setMoney("");
	avaMe->setAI("");
    
	avaUser1->setVisibleLayerInvite(true);
	avaUser1->setReady(false);
	avaUser1->setName("");
	avaUser1->setMoney("");
	avaUser1->setAI("");
	//
	avaUser2->setVisibleLayerInvite(true);
	avaUser2->setReady(false);
	avaUser2->setName("");
	avaUser2->setMoney("");
	avaUser2->setAI("");
	//
	avaUser3->setVisibleLayerInvite(true);
	avaUser3->setReady(false);
	avaUser3->setName("");
	avaUser3->setMoney("");
	avaUser3->setAI("");
	//
	avaUser4->setVisibleLayerInvite(true);
	avaUser4->setReady(false);
	avaUser4->setName("");
	avaUser4->setMoney("");
	avaUser4->setAI("");
    //
    avaUser5->setVisibleLayerInvite(true);
	avaUser5->setReady(false);
	avaUser5->setName("");
	avaUser5->setMoney("");
	avaUser5->setAI("");
    //
    CCLog("avata listuser: %s",this->listUser.c_str());
    
	for (int i = 0; i < arrUser.size(); i++)
	{
		vector<string> info = mUtils::splitString(arrUser[i],'|');
		int pos = getPosByName(info[0]);
        CCLog("avatar pos: %d",pos);
		if (pos < 0)
		{
			continue;
		}
        
		if (GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[0]) != NULL)
		{
			boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[0])->GetVariable("aN")->GetStringValue();
			boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[0])->GetVariable("amf")->GetDoubleValue();
			boost::shared_ptr<string> url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[0])->GetVariable("aal")->GetStringValue();
            
			int _money = (money != NULL) ? (int)*money : 0;
			string _url = (url != NULL) ? url->c_str() : "";
			string _name = (name != NULL) ? name->c_str() : info[0];
            CCLog("update _money = %d",_money);
			Avatar *_user = getUserByPos(pos);
            _user->setVisibleLayerInvite(false);
			_user->setName(_name);
			_user->setFlag(i == 0);
			_user->setAI(info[0]);
            _user->setIcon(_url);
			_user->setMoney(_money);
			//
			bool meIsBoss = (i == 0);
			if(pos == kuser0 && isSpect()!=true){
                
				this->getUserByPos(kuser1)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kuser2)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kuser3)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kuser4)->setMeIsBoss(meIsBoss);
                this->getUserByPos(kuser5)->setMeIsBoss(meIsBoss);
                _user->setVisible(true);
				_user->setTouchEnabled(false);
			}
            
                if(info[3]=="1"&& isStartedGame()!=true)
                    if(i!=0)
                        _user->setReady(true);
            
            
                if(info[3]=="0" || i==0)
                _user->setReady(false);

		}
		
	}//for
}

void AvatarInTomCuaCa::setPosChuong(int pos){
	bool meIsBoss = false;
	switch (pos) {
	case kuser3:
		chuong->setPosition(ccp(WIDTH_DESIGN-115,410));
		chuong->setVisible(true);
		break;
	case kuser4:
		chuong->setPosition(ccp(WIDTH_DESIGN-170,290));
		chuong->setVisible(true);
		break;
	case kuser1:
		chuong->setPosition(ccp(80,290));
		chuong->setVisible(true);
		break;
	case kuser2:
		chuong->setPosition(ccp(30,170));
		chuong->setVisible(true);
        break;
    case kuser5:
        chuong->setPosition(ccp(WIDTH_DESIGN-115,170));
        chuong->setVisible(true);
        break;
	case kuser0:
		chuong->setPosition(ccp(30,410));
		chuong->setVisible(true);
		meIsBoss = true;
		break;
	default:
            chuong->setVisible(false);
		break;
	}
	//
    
	this->getUserByPos(kuser1)->setMeIsBoss(meIsBoss);
    this->getUserByPos(kuser2)->setMeIsBoss(meIsBoss);
    this->getUserByPos(kuser3)->setMeIsBoss(meIsBoss);
	this->getUserByPos(kuser4)->setMeIsBoss(meIsBoss);
    this->getUserByPos(kuser5)->setMeIsBoss(meIsBoss);
}


void AvatarInTomCuaCa::resetAll(){
	setFlag(kuser0, false);
	setFlag(kuser3, false);
	setFlag(kuser4, false);
	setFlag(kuser1, false);
	setFlag(kuser2, false);
    setFlag(kuser5, false);

	setName(kuser0, "");
	setName(kuser3, "");
	setName(kuser4, "");
	setName(kuser1, "");
	setName(kuser2, "");
    setName(kuser5, "");

	setMoney(kuser0, "");
	setMoney(kuser3, "");
	setMoney(kuser4, "");
	setMoney(kuser1, "");
	setMoney(kuser2, "");
    setMoney(kuser5, "");

	

	this->getUserByPos(kuser3)->setVisibleLayerInvite(true);
	this->getUserByPos(kuser4)->setVisibleLayerInvite(true);
	this->getUserByPos(kuser1)->setVisibleLayerInvite(true);
	this->getUserByPos(kuser2)->setVisibleLayerInvite(true);
    this->getUserByPos(kuser5)->setVisibleLayerInvite(true);
}
void AvatarInTomCuaCa::showChatByPos(int pos, string mes)
{
	Chat *newMes = new Chat(mes, pos);
	newMes->setAnchorPoint(ccp(newMes->getContentSize().width/2,0));
	CCPoint point;

	switch (pos) {
	case kuser0:
		point.setPoint(40, 400);
		break;

	case kuser1:
		point.setPoint(40, 280);
		break;

	case kuser2:
		point.setPoint(40, 160);
		break;

	case kuser3:
		point.setPoint(650, 400);
		break;

	case kuser4:
		point.setPoint(650, 280);
		break;
    	case kuser5:
            point.setPoint(650, 160);
            break;
	default:
		point.setPoint((WIDTH_DESIGN - newMes->getSize().width) / 2, (HEIGHT_DESIGN - newMes->getSize().height) / 2);
		newMes->setStatusByServer(true);
		break;
	}

	newMes->setPosition(point);
	this->addChild(newMes);
}
int AvatarInTomCuaCa::getPosByAccountID(string aI) {
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
					return kuser0;
				} else if (i == (pos + 1) % 6) {
					return kuser1;
				} else if (i == (pos + 2) % 6) {
					return kuser2;
				} else if (i == (pos + 3) % 6) {
					return kuser3;
				} else if (i == (pos + 4) % 6) {
					return kuser4;
				} else if (i == (pos + 5) % 6) {
					return kuser5;
				}

				break;
			}
		}
	}

	return -1;
}
bool AvatarInTomCuaCa::isSpect() {
	vector<string> arr = mUtils::splitString(this->listUser, ';');
	int size = arr.size();
	for (int i = 0; i < size; i++){
		vector<string> arrInfo = mUtils::splitString(arr.at(i), '|');
		if (arrInfo.size() < 2) continue;
		string ai = arrInfo.at(0);
		if (strcmp(ai.c_str(), myAI.c_str())==0)
            return false;
	}
    
	return true;
}
bool AvatarInTomCuaCa::isStartedGame()
{
    boost::shared_ptr<Room> ro = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
    vector<string> rParams = mUtils::splitString( *ro->GetVariable("params")->GetStringValue(), '@' );
    //Param: Money@isPlaying@Number Of Player
    //0: rParams.at(0).c_str()
    //1: rParams.at(1).c_str()
    //2: rParams.at(2).c_str()
    bool isStartedGame=true;
    isStartedGame=strcmp(rParams.at(1).c_str(),"0")==0?false:true;
    if(isStartedGame)
        CCLog("Bàn đang chơi");
    else
        CCLog("Bàn chưa chơi");
    
    return isStartedGame;
}
void AvatarInTomCuaCa::vaoBanChoi(CCObject *obj,TouchEventType type)
{
	UIButton *abc = (UIButton*)obj;
	int tag=abc->getTag();
    if(type==TOUCH_EVENT_ENDED)
		if(tag==1)
		{
            //yêu cầu làm khách
            boost::shared_ptr<IRequest> request (new PlayerToSpectatorRequest());
            GameServer::getSingleton().getSmartFox()->Send(request);
            btn_vaochoi->setEnabled(true);
            btn_dungday->setEnabled(false);
            //yêu cầu rời game
            boost::shared_ptr<ISFSObject> params (new SFSObject());
            boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
            boost::shared_ptr<IRequest> req (new ExtensionRequest("rqlg", params, lastRoom));
            GameServer::getSingleton().getSmartFox()->Send(req);
            
			
		}///
        else{
            //yêu cầu vào chơi
            boost::shared_ptr<IRequest> request (new SpectatorToPlayerRequest());
			GameServer::getSingleton().getSmartFox()->Send(request);
			CCLog("da vao");
			btn_vaochoi->setEnabled(false);
			btn_dungday->setEnabled(true);
            //yêu cầu join game
            boost::shared_ptr<ISFSObject> params (new SFSObject());
            boost::shared_ptr<Room> lastRoom = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
            
            boost::shared_ptr<IRequest> req2 (new ExtensionRequest("rqjg", params, lastRoom));
            GameServer::getSingleton().getSmartFox()->Send(req2);
            
        }
}
void AvatarInTomCuaCa::playerToSpec()
{
    CCLog("đang là người chơi...");
	btn_vaochoi->setTouchEnabled(false);
	btn_vaochoi->setEnabled(false);
	btn_dungday->setTouchEnabled(true);
	btn_dungday->setEnabled(true);
    
    
}
void AvatarInTomCuaCa::specToPlayer()
{
    CCLog("đang trống ");
    btn_vaochoi->setTouchEnabled(true);
    btn_vaochoi->setEnabled(true);
	btn_dungday->setTouchEnabled(false);
	btn_dungday->setEnabled(false);
}
void AvatarInTomCuaCa::setListUser(string list)
{
    this->listUser= list;
    updateUsers();
}