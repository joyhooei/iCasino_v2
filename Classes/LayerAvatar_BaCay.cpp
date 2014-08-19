//
//  LayerAvatar_BaCay.cpp
//  iCasino_v2
//
//  Created by DauA on 6/26/14.
// 
//
// 

#include "LayerAvatar_BaCay.h"
#include "SceneManager.h"
#include "GameServer.h"
#include "mUtils.h"
#include "AllData.h"
#include "Requests/SpectatorToPlayerRequest.h"
#include "Requests/PlayerToSpectatorRequest.h"

LayerBaCayAvatar::~LayerBaCayAvatar()
{

}

bool LayerBaCayAvatar::init()
{
	if (!CCLayer::init()) return false;
	myself = GameServer::getSingleton().getSmartFox()->MySelf();
	UILayer *ul = UILayer::create();
    
    this->myName = SceneManager::getSingleton().getMyName();
	this->myAI   = SceneManager::getSingleton().getMyName().c_str();
	this->isSpector = GameServer::getSingleton().getSmartFox()->UserManager()->GetUserByName(myName)->IsSpectator();
    
    btn_vaochoi = UIButton::create();
    btn_vaochoi->setTouchEnabled(true);
    btn_vaochoi->loadTextures("ready.png", "ready_selected.png", "");
    btn_vaochoi->setTitleText("Vào bàn");
	btn_vaochoi->setScale(0.8);
    btn_vaochoi->setPosition(ccp(65,87));
	btn_vaochoi->setTitleFontSize(20);
    btn_vaochoi->addTouchEventListener(this,toucheventselector(LayerBaCayAvatar::vaoBanChoi));
    btn_vaochoi->setEnabled(false);
	btn_vaochoi->setTag(0);

	btn_dungday = UIButton::create();
	btn_dungday->setTouchEnabled(true);
	btn_dungday->loadTextures("ready.png", "ready_selected.png", "");
	btn_dungday->setTitleText("Đứng dậy");
	btn_dungday->setScale(0.8);
	btn_dungday->setPosition(ccp(65,87));
	btn_dungday->setTitleFontSize(20);
	btn_dungday->addTouchEventListener(this,toucheventselector(LayerBaCayAvatar::vaoBanChoi));
	btn_dungday->setEnabled(false);
	btn_dungday->setTag(1);

    ul->addWidget(btn_dungday);
	ul->addWidget(btn_vaochoi);
    this->addChild(ul);
    
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));

	this->myName = SceneManager::getSingleton().getMyName();

	Avatar *me = new Avatar(false);
    me->setTouchEnabled(false);
	Avatar *user1 = new Avatar(false);
	Avatar *user2 = new Avatar(false);
	Avatar *user3 = new Avatar(false);
	Avatar *user4 = new Avatar(false);
    Avatar *user5 = new Avatar(false);
    Avatar *user6 = new Avatar(false);

	me->autorelease();
	user1->autorelease();
	user2->autorelease();
	user3->autorelease();
	user4->autorelease();
    user5->autorelease();
    user6->autorelease();

	

    me->setPosition(ccp(WIDTH_DESIGN/2-me->getSizeThis().width/2+25,10));
    user1->setPosition(ccp(40, 110));
    user2->setPosition(ccp(40, HEIGHT_DESIGN-200));
    user3->setPosition(ccp(250, 360));
    user4->setPosition(ccp(WIDTH_DESIGN-320, 360));
    user5->setPosition(ccp(WIDTH_DESIGN-120, HEIGHT_DESIGN-200));
    user6->setPosition(ccp(WIDTH_DESIGN-120,110));
    
    
	me->setTag(kuser0);
	user1->setTag(kuser1);
    user2->setTag(kuser2);
    user3->setTag(kuser3);
    user4->setTag(kuser4);
    user5->setTag(kuser5);
    user6->setTag(kuser6);
    
    me->setScale(0.7);
    user1->setScale(0.7);
    user2->setScale(0.7);
    user3->setScale(0.7);
    user4->setScale(0.7);
    user5->setScale(0.7);
    user6->setScale(0.7);
    

	this->addChild(me);

	this->addChild(user1);
	this->addChild(user2);
	this->addChild(user3);
	this->addChild(user4);
    this->addChild(user5);
    this->addChild(user6);

	chuong = UIImageView::create();
	chuong->loadTexture("Chuong.png");
    chuong->setScale(0.7);
	chuong->setTouchEnabled(false);
	chuong->setVisible(false);
	chuong->setAnchorPoint(ccp(0,0));
	chuong->setPosition(ccp(0,0));
	this->addChild(chuong);

	listUser = "";

	return true;
}

void LayerBaCayAvatar::onExit()
{

	if (chuong) {
		chuong->release();
		chuong=NULL;
	}


}

void LayerBaCayAvatar::setIcon (int pos, char *url)
{
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setIcon(url);
}

void LayerBaCayAvatar::setFlag (int pos, bool isShow)
{
	bool meIsBoss = isShow;
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setFlag(isShow);
	//
	if(pos == kuser0){
		//
		this->getUserByPos(kuser1)->setMeIsBoss(meIsBoss);
		this->getUserByPos(kuser2)->setMeIsBoss(meIsBoss);
		this->getUserByPos(kuser3)->setMeIsBoss(meIsBoss);
		this->getUserByPos(kuser4)->setMeIsBoss(meIsBoss);
        this->getUserByPos(kuser5)->setMeIsBoss(meIsBoss);
        this->getUserByPos(kuser6)->setMeIsBoss(meIsBoss);
	}
}

void LayerBaCayAvatar::setName (int pos, string name)
{
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setName(name);
}

void LayerBaCayAvatar::setMoney(int pos, string money)
{
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setMoney(money);
}

void LayerBaCayAvatar::setMoney(int pos, int money)
{
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setMoney(money);
}

void LayerBaCayAvatar::setReady(int pos, bool isReady)
{
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setReady(isReady);
}

void LayerBaCayAvatar::setVisibleLayerInvite(int pos, bool isShow)
{
	Avatar *user = this->getUserByPos(pos);
	if (user != NULL)
	{
		user->setVisibleLayerInvite(isShow);
	}
}

void LayerBaCayAvatar::resetAll()
{
	setFlag(kuser0, false);
	setFlag(kuser1, false);
	setFlag(kuser2, false);
	setFlag(kuser3, false);
    setFlag(kuser4, false);
    setFlag(kuser5, false);
    setFlag(kuser6, false);

	setName(kuser0, "");
	setName(kuser1, "");
	setName(kuser2, "");
	setName(kuser3, "");
    setName(kuser4, "");
    setName(kuser5, "");
    setName(kuser6, "");

	setMoney(kuser0, "");
	setMoney(kuser1, "");
	setMoney(kuser2, "");
	setMoney(kuser3, "");
    setMoney(kuser4, "");
    setMoney(kuser5, "");
    setMoney(kuser6, "");

	this->getUserByPos(kuser1)->setVisibleLayerInvite(true);
	this->getUserByPos(kuser2)->setVisibleLayerInvite(true);
	this->getUserByPos(kuser3)->setVisibleLayerInvite(true);
    this->getUserByPos(kuser4)->setVisibleLayerInvite(true);
    this->getUserByPos(kuser5)->setVisibleLayerInvite(true);
    this->getUserByPos(kuser6)->setVisibleLayerInvite(true);
}

void LayerBaCayAvatar::setPosChuong(int pos)
{
	switch (pos) {
	case kuser1:
		chuong->setPosition(ccp(32,190));
		chuong->setVisible(true);
		break;
	case kuser2:
		chuong->setPosition(ccp(32,360));
		chuong->setVisible(true);
		break;
	case kuser3:
		chuong->setPosition(ccp(243,440));
		chuong->setVisible(true);
		break;
	case kuser4:
        chuong->setPosition(ccp(478,440));
        chuong->setVisible(true);
		break;
	case kuser5:
		chuong->setPosition(ccp(WIDTH_DESIGN-125,360));
		chuong->setVisible(true);
		break;
    case kuser6:
        chuong->setPosition(ccp(WIDTH_DESIGN-125,190));
        chuong->setVisible(true);
        break;
    case kuser0:
        chuong->setPosition(ccp(370,90));
        chuong->setVisible(true);
        break;
	default:
		break;
	}
    if(strcmp(listUser.c_str(),"")==0)
    {
        CCLog("lu-%s, pos-%d",listUser.c_str(),pos);
        chuong->setVisible(false);
    }
}

void LayerBaCayAvatar::setUnReadyAllUser()
{
	setReady(kuser0, false);
	setReady(kuser1, false);
	setReady(kuser2, false);
	setReady(kuser3, false);
	setReady(kuser4, false);
    setReady(kuser5, false);
    setReady(kuser6, false);
}

void LayerBaCayAvatar::resetGame()
{
	setUnReadyAllUser();
}

int LayerBaCayAvatar::getPosByName(string name)
{
	int vt = -1;
	if (listUser == "")
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
		if (strcmp(info[0].c_str(), name.c_str()) == 0)
		{
			if(i == vt){
				return kuser0;
    
			}
			else if(i == (vt + 1) % 7){
				return kuser1;
			}
			else if(i == (vt + 2) % 7){
				return kuser2;
			}
			else if(i == (vt + 3) % 7){
				return kuser3;
			}
            else if(i == (vt + 4) % 7){
				return kuser4;
			}
            else if(i == (vt + 5) % 7){
				return kuser5;
			}
            else if(i == (vt + 6) % 7){
				return kuser6;
			}
			break;
		}
	}

	return -1;
}

void LayerBaCayAvatar::setListUserForBaCay(string listUser)
{
	this->listUser = listUser;
	updateUsers();
}

void LayerBaCayAvatar::updateUsers()
{
	if (listUser == "")
	{
        getUserByPos(kuser0)->setVisibleLayerInvite(true);
		return;
	}
   
  
    
	vector<string> arrUser = mUtils::splitString(listUser,';');


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
    Avatar *avaUser6 = getUserByPos(kuser6);

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
    avaUser6->setVisibleLayerInvite(true);
	avaUser6->setReady(false);
	avaUser6->setName("");
	avaUser6->setMoney("");
	avaUser6->setAI("");
    
	for (int i = 0; i < arrUser.size(); i++)
	{
		vector<string> info = mUtils::splitString(arrUser[i],'|');
        int _pos = info.size();
		int pos = getPosByName(info[0]);
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

			Avatar *_user = getUserByPos(pos);
            _user->setVisibleLayerInvite(false);
			_user->setName(_name);
			_user->setFlag(i == 0);
			_user->setAI(info[0]);
			//
			bool meIsBoss = (i == 0);
			if(pos == kuser0){
                _user->setVisible(true);
				_user->setTouchEnabled(false);
				this->getUserByPos(kuser1)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kuser2)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kuser3)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kuser4)->setMeIsBoss(meIsBoss);
                this->getUserByPos(kuser5)->setMeIsBoss(meIsBoss);
                this->getUserByPos(kuser6)->setMeIsBoss(meIsBoss);
			}
            if(i!=0){
                if(strcmp(info[_pos-1].c_str(), "1")==0){
                        _user->setReady(true);
                }
            }
                _user->setIcon(_url);
                _user->setMoney(_money);
            if(strcmp(info[1].c_str(),"0")==0)
                _user->setReady(false);
		}
		
	}//for

}

string LayerBaCayAvatar::getNameByPos(int pos)
{
	return "";
}

Avatar* LayerBaCayAvatar::getUserByPos(int pos)
{
	if (this->getChildByTag(pos) == NULL)
    {
        return NULL;
        CCLog("tag null");
    }
	return (Avatar*) this->getChildByTag(pos);
}

void LayerBaCayAvatar::runTimer(int posUser)
{
	stopAllTimer();
	getUserByPos(posUser)->startTimer();
}

void LayerBaCayAvatar::stopAllTimer()
{
	getUserByPos(kuser0)->stopTimer();
	getUserByPos(kuser1)->stopTimer();
	getUserByPos(kuser2)->stopTimer();
	getUserByPos(kuser3)->stopTimer();
    getUserByPos(kuser4)->stopTimer();
    getUserByPos(kuser5)->stopTimer();
    getUserByPos(kuser6)->stopTimer();
    
}
void LayerBaCayAvatar::vaoBanChoi(CCObject *obj,TouchEventType type)
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
void LayerBaCayAvatar::playerToSpec()
{
    CCLog("đang là người chơi...");
	btn_vaochoi->setTouchEnabled(false);
	btn_vaochoi->setEnabled(false);
	btn_dungday->setTouchEnabled(true);
	btn_dungday->setEnabled(true);

    
}
void LayerBaCayAvatar::specToPlayer()
{
    CCLog("đang trống ");
    btn_vaochoi->setTouchEnabled(true);
    btn_vaochoi->setEnabled(true);
	btn_dungday->setTouchEnabled(false);
	btn_dungday->setEnabled(false);
}
bool LayerBaCayAvatar::isSpect() {
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
bool LayerBaCayAvatar::isStartedGame()
{
	boost::shared_ptr<Room> room = GameServer::getSingleton().getSmartFox()->LastJoinedRoom();
	boost::shared_ptr<RoomVariable> rv = room->GetVariable("params");
	string s = *rv->GetStringValue();
    
	vector<string> lstBet = mUtils::splitString( s, '@' );
	bool isStartedGame=false;
	lstBet.at(1).compare("1")==0 ? (isStartedGame=true) : (isStartedGame=false);
	if (isStartedGame) {
		CCLog("Ban dang choi!");
	} else CCLog("Ban chua choi!");
    
	return isStartedGame;
}