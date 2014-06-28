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

	listUser = "";

	return true;
}

void LayerBaCayAvatar::onExit()
{

}

void LayerBaCayAvatar::setIcon (int pos, char *url)
{
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setIcon(url);
}

void LayerBaCayAvatar::setFlag (int pos, bool isShow)
{
	if (this->getUserByPos(pos) == NULL) return;
	this->getUserByPos(pos)->setFlag(isShow);
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

void LayerBaCayAvatar::setPosChuong(int pos)
{
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

void LayerBaCayAvatar::setUnReadyAllUser()
{
	setReady(kUserMe, false);
	setReady(kUserLeft, false);
	setReady(kUserRight, false);
	setReady(kUserTop, false);
	setReady(kUserBot, false);
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

	CCLOG("vt = %d",vt);

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
				return kUserMe;
			}
			else if(i == (vt + 1) % 4){
				return kUserRight;
			}
			else if(i == (vt + 2) % 4){
				return kUserTop;
			}
			else if(i == (vt + 3) % 4){
				return kUserLeft;
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

	Avatar *avaMe = getUserByPos(kUserMe);
	Avatar *avaLeft = getUserByPos(kUserLeft);
	Avatar *avaRight = getUserByPos(kUserRight);
	Avatar *avaTop = getUserByPos(kUserTop);
	Avatar *avaBot = getUserByPos(kUserBot);

	avaMe->setVisible(false);
	avaMe->setTouchEnabled(false);
	avaMe->setReady(false);
	avaMe->setName("");
	avaMe->setMoney("");
	avaMe->setAI("");

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

	for (int i = 0; i < arrUser.size(); i++)
	{
		vector<string> info = mUtils::splitString(arrUser[i],'|');
		int pos = getPosByName(info[0]);
		if (pos < 0)
		{
			break;
		}

		boost::shared_ptr<string> name = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[0])->GetVariable("aN")->GetStringValue();
		boost::shared_ptr<double> money = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[0])->GetVariable("amf")->GetDoubleValue();
		boost::shared_ptr<string> url = GameServer::getSingleton().getSmartFox()->LastJoinedRoom()->GetUserByName(info[0])->GetVariable("aal")->GetStringValue();

		int _money = (money != NULL) ? (int)*money : 0;
		string _url = (url != NULL) ? url->c_str() : "";
		string _name = (name != NULL) ? name->c_str() : info[0];

		Avatar *user = getUserByPos(pos);
		user->setName(_name);
		user->setFlag(i == 0);
		user->setIcon(_url);
		//user->setAI(aI);
		user->setMoney(_money);

		if (pos == kUserMe)
		{
			user->setVisible(true);
			user->setTouchEnabled(true);
		}
		else {
			user->setVisibleLayerInvite(false);
		}
	}
}

string LayerBaCayAvatar::getNameByPos(int pos)
{
	return "";
}

Avatar* LayerBaCayAvatar::getUserByPos(int pos)
{
	if (this->getChildByTag(pos) == NULL) return NULL;
	return (Avatar*) this->getChildByTag(pos);
}

void LayerBaCayAvatar::runTimer(int posUser)
{
	stopAllTimer();
	getUserByPos(posUser)->startTimer();
}

void LayerBaCayAvatar::stopAllTimer()
{
	getUserByPos(kUserMe)->stopTimer();
	getUserByPos(kUserLeft)->stopTimer();
	getUserByPos(kUserRight)->stopTimer();
	getUserByPos(kUserTop)->stopTimer();
}