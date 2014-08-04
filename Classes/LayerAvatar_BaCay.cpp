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

LayerBaCayAvatar::~LayerBaCayAvatar()
{

}

bool LayerBaCayAvatar::init()
{
	if (!CCLayer::init()) return false;

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));

	this->myName = SceneManager::getSingleton().getMyName();

	Avatar *me = new Avatar(false);
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
    
    me->setScale(0.9);
    user1->setScale(0.9);
    user2->setScale(0.9);
    user3->setScale(0.9);
    user4->setScale(0.9);
    user5->setScale(0.9);
    user6->setScale(0.9);
    

	this->addChild(me);

	this->addChild(user1);
	this->addChild(user2);
	this->addChild(user3);
	this->addChild(user4);
    this->addChild(user5);
    this->addChild(user6);

	chuong = UIImageView::create();
	chuong->loadTexture("Chuong.png");
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
		chuong->setPosition(ccp(30,210));
            
		chuong->setVisible(true);
		break;
	case kuser2:
		chuong->setPosition(ccp(30,380));
		chuong->setVisible(true);
		break;
	case kuser3:
		chuong->setPosition(ccp(240,460));
		chuong->setVisible(true);
		break;
	case kuser4:
        chuong->setPosition(ccp(540,460));
        chuong->setVisible(true);
		break;
	case kuser5:
		chuong->setPosition(ccp(WIDTH_DESIGN-125,380));
		chuong->setVisible(true);
		break;
    case kuser6:
        chuong->setPosition(ccp(WIDTH_DESIGN-125,210));
        chuong->setVisible(true);
        break;
    case kuser0:
        chuong->setPosition(ccp(370,110));
        chuong->setVisible(true);
       
        break;
	default:
		break;
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
		if (strcmp(info[0].c_str(), GameServer::getSingleton().getSmartFox()->MySelf()->Name()->c_str()) == 0)
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
                
				this->getUserByPos(kuser1)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kuser2)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kuser3)->setMeIsBoss(meIsBoss);
				this->getUserByPos(kuser4)->setMeIsBoss(meIsBoss);
                this->getUserByPos(kuser5)->setMeIsBoss(meIsBoss);
                this->getUserByPos(kuser6)->setMeIsBoss(meIsBoss);
			}
			//
			_user->setIcon(_url);
			//user->setAI(aI);
			_user->setMoney(_money);

			if (pos == kuser0)
			{
				_user->setVisible(true);
				_user->setTouchEnabled(false);
			}
			else {
				_user->setVisibleLayerInvite(false);
			}
		}
	}
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
    
}